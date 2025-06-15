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
static pHSE_Context gHSEContext = NULL;

void Hse_Task_Init(uint32_t TaskCount, pHSE_Context pHSEContext) {
    gTaskCount  = TaskCount;
    gHSEContext = pHSEContext;
    for (Hse_Task_ID index = 0; index < gTaskCount; index++) {
        gHSEContext[index].isUsed = false;
    }
}

Hse_Task_ID Hse_Task_GetFreeSlot(void) {
    for (Hse_Task_ID index = 0; index < gTaskCount; index++) {
        if (!gHSEContext[index].isUsed) {
            gHSEContext[index].isUsed              = true;
            gHSEContext[index].SrvDescriptor.srvId = HSE_SRV_ID_INVALID;
            return index;
        }
    }
    return gTaskCount;
}

void Hse_Task_Release(Hse_Task_ID Id) {
    if (Id < gTaskCount) {
        gHSEContext[Id].isUsed = false;
    }
}

static hseSrvResponse_t Hse_Task_SyncRequestChannel(Hse_Task_ID Id, uint8_t u8MuInstance,
                                                    uint8_t u8MuChannel, uint32_t u32Timeout) {
    if ((Id < gTaskCount) && (gHSEContext[Id].isUsed) &&
        (gHSEContext[Id].SrvDescriptor.srvId != HSE_SRV_ID_INVALID)) {
        Hse_Ip_ReqType request = {
            .eReqType       = HSE_IP_REQTYPE_SYNC,
            .pfCallback     = NULL,
            .pCallbackParam = NULL,
            .u32Timeout     = u32Timeout,
        };

        return Hse_Ip_ServiceRequest(u8MuInstance, u8MuChannel, &request,
                                     &gHSEContext[Id].SrvDescriptor);
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
