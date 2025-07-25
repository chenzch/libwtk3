//---------------------------------------------------------------------------------------------------------------------
//
// WTMEC CORPORATION CONFIDENTIAL
// ________________________________
//
// [2025] Wtmec Corporation
// All Rights Reserved.
//
// NOTICE: This is an unpublished work of authorship, which contains trade secrets.
// Wtmec Corporation owns all rights to this work and intends to maintain it in confidence to
// preserve its trade secret status. Wtmec Corporation reserves the right, under the copyright
// laws of the United States or those of any other country that may have jurisdiction, to protect
// this work as an unpublished work, in the event of an inadvertent or deliberate unauthorized
// publication. Wtmec Corporation also reserves its rights under all copyright laws to protect
// this work as a published work, when appropriate. Those having access to this work may not copy
// it, use it, modify it, or disclose the information contained in it without the written
// authorization of Wtmec Corporation.
//
//---------------------------------------------------------------------------------------------------------------------
#include <stdint.h>
#include <stdbool.h>
// Dummy define for S32K344 to skip error check. Do not use HSE_PLATFORM in this project
#define CPU_S32K344
#include "hse_interface.h"
#include "Hse_Ip.h"
#include "libwtk3.h"

#define HSE_SRV_ID_INVALID (0)

static uint32_t     gTaskCount  = 0;
static HSE_Context *gHSEContext = NULL;
static HSE_Task    *gTasks      = NULL;

void Hse_Task_Init(uint32_t TaskCount, HSE_Task *pHSE_Task, HSE_Context *pHSEContext) {
    gTaskCount  = TaskCount;
    gHSEContext = pHSEContext;
    gTasks      = pHSE_Task;
    for (Hse_Task_ID index = 0; index < gTaskCount; index++) {
        gTasks[index].isUsed = false;
    }
}

Hse_Task_ID Hse_Task_GetFreeSlot(void) {
    for (Hse_Task_ID index = 0; index < gTaskCount; index++) {
        if (!gTasks[index].isUsed) {
            gTasks[index].isUsed                   = true;
            gHSEContext[index].SrvDescriptor.srvId = HSE_SRV_ID_INVALID;
            return index;
        }
    }
    return gTaskCount;
}

void Hse_Task_Release(Hse_Task_ID Id) {
    if (Id < gTaskCount) {
        gTasks[Id].isUsed = false;
    }
}

static hseSrvResponse_t Hse_Task_SyncRequestChannel(Hse_Task_ID Id, uint8_t u8MuInstance,
                                                    uint8_t u8MuChannel, uint32_t u32Timeout) {
    if ((Id < gTaskCount) && (gTasks[Id].isUsed) &&
        (gHSEContext[Id].SrvDescriptor.srvId != HSE_SRV_ID_INVALID)) {
        gTasks[Id].SrvRequest.eReqType       = HSE_IP_REQTYPE_SYNC;
        gTasks[Id].SrvRequest.pfCallback     = NULL;
        gTasks[Id].SrvRequest.pCallbackParam = NULL;
        gTasks[Id].SrvRequest.u32Timeout     = u32Timeout;

        gTasks[Id].SrvResponse = Hse_Ip_ServiceRequest(
            u8MuInstance, u8MuChannel, &gTasks[Id].SrvRequest, &gHSEContext[Id].SrvDescriptor);

        return gTasks[Id].SrvResponse;
    }
    return HSE_SRV_RSP_GENERAL_ERROR;
}

hseSrvResponse_t Hse_Task_MasterRequest(Hse_Task_ID Id, uint8_t u8MuInstance, uint32_t u32Timeout) {
    return Hse_Task_SyncRequestChannel(Id, u8MuInstance, 0, u32Timeout);
}

hseSrvResponse_t Hse_Task_SyncRequest(Hse_Task_ID Id, uint8_t u8MuInstance, uint32_t u32Timeout) {
    uint8_t u8MuChannel = Hse_Ip_GetFreeChannel(u8MuInstance);

    if (HSE_IP_INVALID_MU_CHANNEL_U8 != u8MuChannel) {
        return Hse_Task_SyncRequestChannel(Id, u8MuInstance, u8MuChannel, u32Timeout);
    }
    return HSE_SRV_RSP_GENERAL_ERROR;
}

static void Hse_Callback(uint8_t u8MuInstance, uint8_t u8MuChannel, hseSrvResponse_t HseResponse,
                         void *pCallbackParam) {
    Hse_Task_ID Id = (Hse_Task_ID)((uint32_t)pCallbackParam & 0xFF);
    if ((Id < gTaskCount) && (gTasks[Id].isUsed)) {
        gTasks[Id].SrvResponse = (hseSrvResponse_t)HseResponse;
    }
}

hseSrvResponse_t Hse_Task_AsyncRequest(Hse_Task_ID Id, uint8_t u8MuInstance, bool useInterrupt) {
    uint8_t u8MuChannel = Hse_Ip_GetFreeChannel(u8MuInstance);

    if ((HSE_IP_INVALID_MU_CHANNEL_U8 != u8MuChannel) && (Id < gTaskCount) && (gTasks[Id].isUsed) &&
        (gHSEContext[Id].SrvDescriptor.srvId != HSE_SRV_ID_INVALID)) {
        if (useInterrupt) {
            gTasks[Id].SrvRequest.eReqType = HSE_IP_REQTYPE_ASYNC_IRQ;
        } else {
            gTasks[Id].SrvRequest.eReqType = HSE_IP_REQTYPE_ASYNC_POLL;
        }
        gTasks[Id].SrvRequest.pfCallback     = Hse_Callback;
        gTasks[Id].SrvRequest.pCallbackParam = (void *)(uint32_t)Id;
        gTasks[Id].SrvRequest.u32Timeout     = -1U;
        gTasks[Id].SrvResponse               = HSE_SRV_RSP_BUSY;

        return Hse_Ip_ServiceRequest(u8MuInstance, u8MuChannel, &gTasks[Id].SrvRequest,
                                     &gHSEContext[Id].SrvDescriptor);
    }
    return HSE_SRV_RSP_GENERAL_ERROR;
}

hseSrvResponse_t Hse_Task_GetResponse(Hse_Task_ID Id, uint8_t u8MuInstance) {
    if ((Id < gTaskCount) && (gTasks[Id].isUsed)) {
        if (gTasks[Id].SrvRequest.eReqType == HSE_IP_REQTYPE_ASYNC_POLL) {
            Hse_Ip_MainFunction(u8MuInstance);
        }
        return gTasks[Id].SrvResponse;
    } else {
        return HSE_SRV_RSP_GENERAL_ERROR;
    }
}

hseAttrMUConfig_t *Hse_GetMuConfig(Hse_Task_ID Id) {
    if (Id < gTaskCount) {
        hseSrvDescriptor_t *pHseSrvDescriptor = &gHSEContext[Id].SrvDescriptor;
        HOST_ADDR           RetVal = HSE_PTR_TO_HOST_ADDR(&gHSEContext[Id].Data.Hse_MuConfig);

        pHseSrvDescriptor->srvId                     = HSE_SRV_ID_SET_ATTR;
        pHseSrvDescriptor->hseSrv.setAttrReq.attrId  = HSE_MU_CONFIG_ATTR_ID;
        pHseSrvDescriptor->hseSrv.setAttrReq.attrLen = sizeof(hseAttrMUConfig_t);
        pHseSrvDescriptor->hseSrv.setAttrReq.pAttr   = RetVal;
        return (hseAttrMUConfig_t *)RetVal;
    }
    return NULL;
}

hseAttrCapabilities_t *Hse_GetCapabilities(Hse_Task_ID Id) {
    if (Id < gTaskCount) {
        hseSrvDescriptor_t *pHseSrvDescriptor = &gHSEContext[Id].SrvDescriptor;
        HOST_ADDR RetVal = HSE_PTR_TO_HOST_ADDR(&gHSEContext[Id].Data.Hse_AttrCapabilities);

        pHseSrvDescriptor->srvId                     = HSE_SRV_ID_GET_ATTR;
        pHseSrvDescriptor->hseSrv.getAttrReq.attrId  = HSE_CAPABILITIES_ATTR_ID;
        pHseSrvDescriptor->hseSrv.getAttrReq.attrLen = sizeof(hseAttrCapabilities_t);
        pHseSrvDescriptor->hseSrv.getAttrReq.pAttr   = RetVal;
        return (hseAttrCapabilities_t *)RetVal;
    }
    return NULL;
}

hseAttrFwVersion_t *Hse_GetFwVersion(Hse_Task_ID Id) {
    if (Id < gTaskCount) {
        hseSrvDescriptor_t *pHseSrvDescriptor = &gHSEContext[Id].SrvDescriptor;
        HOST_ADDR           RetVal = HSE_PTR_TO_HOST_ADDR(&gHSEContext[Id].Data.Hse_FwVersion);

        pHseSrvDescriptor->srvId                     = HSE_SRV_ID_GET_ATTR;
        pHseSrvDescriptor->hseSrv.getAttrReq.attrId  = HSE_FW_VERSION_ATTR_ID;
        pHseSrvDescriptor->hseSrv.getAttrReq.attrLen = sizeof(hseAttrFwVersion_t);
        pHseSrvDescriptor->hseSrv.getAttrReq.pAttr   = RetVal;
        return (hseAttrFwVersion_t *)RetVal;
    }
    return NULL;
}

bool Hse_GetRandomBuffer(Hse_Task_ID Id, uint8_t Level, uint8_t *pBuffer, uint32_t Size) {
    if ((Id < gTaskCount) || (Level > HSE_RNG_CLASS_PTG3)) {
        hseSrvDescriptor_t *pHseSrvDescriptor = &gHSEContext[Id].SrvDescriptor;
        HOST_ADDR           RetVal            = HSE_PTR_TO_HOST_ADDR(pBuffer);

        pHseSrvDescriptor->srvId                                  = HSE_SRV_ID_GET_RANDOM_NUM;
        pHseSrvDescriptor->hseSrv.getRandomNumReq.rngClass        = Level;
        pHseSrvDescriptor->hseSrv.getRandomNumReq.randomNumLength = Size;
        pHseSrvDescriptor->hseSrv.getRandomNumReq.pRandomNum      = RetVal;
        return true;
    } else {
        return false;
    }
}

void Hse_ActivatePassiveBlock(Hse_Task_ID Id) {
    if (Id < gTaskCount) {
        gHSEContext[Id].SrvDescriptor.srvId = HSE_SRV_ID_ACTIVATE_PASSIVE_BLOCK;
    }
}
