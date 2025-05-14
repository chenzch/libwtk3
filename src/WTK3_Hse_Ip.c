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
#define S32K344
#include "hse_interface.h"
#include "Hse_Ip.h"
#include "libwtk3.h"

#define HSE_SRV_ID_INVALID (0)
static struct {
    bool           is_used;
    Hse_Ip_ReqType request;
} gHseRequests[MAX_HSE_TASK_NUM];

#define CRYPTO_43_HSE_START_SEC_VAR_CLEARED_UNSPECIFIED_NO_CACHEABLE
#include "Crypto_43_HSE_MemMap.h"

static union {
    uint8_t               Hse_Buffer[MAX_HSE_MAX_BUFFER_SIZE];
    hseAttrCapabilities_t Hse_AttrCapabilities;
    hseAttrMUConfig_t     Hse_MuConfig;
} gHseData[MAX_HSE_TASK_NUM];

#define CRYPTO_43_HSE_STOP_SEC_VAR_CLEARED_UNSPECIFIED_NO_CACHEABLE
#include "Crypto_43_HSE_MemMap.h"

#define CRYPTO_43_HSE_START_SEC_VAR_SHARED_CLEARED_UNSPECIFIED_NO_CACHEABLE
#include "Crypto_43_HSE_MemMap.h"

static hseSrvDescriptor_t gHseSrvDescriptor[MAX_HSE_TASK_NUM];

#define CRYPTO_43_HSE_STOP_SEC_VAR_SHARED_CLEARED_UNSPECIFIED_NO_CACHEABLE
#include "Crypto_43_HSE_MemMap.h"

void Hse_Task_Init(void) {
    for (Hse_Task_ID index = 0; index < MAX_HSE_TASK_NUM; index++) {
        gHseRequests[index].is_used = false;
    }
}

Hse_Task_ID Hse_Task_GetFreeSlot(void) {
    for (Hse_Task_ID index = 0; index < MAX_HSE_TASK_NUM; index++) {
        if (!gHseRequests[index].is_used) {
            gHseRequests[index].is_used    = true;
            gHseSrvDescriptor[index].srvId = HSE_SRV_ID_INVALID;
            return index;
        }
    }
    return MAX_HSE_TASK_NUM;
}

void Hse_Task_Release(Hse_Task_ID Id) {
    if (Id < MAX_HSE_TASK_NUM) {
        gHseRequests[Id].is_used = false;
        return;
    }
}

static hseSrvResponse_t Hse_Task_SyncRequestChannel(Hse_Task_ID Id, uint8_t u8MuInstance,
                                                    uint8_t u8MuChannel, uint32_t u32Timeout) {
    if ((Id < MAX_HSE_TASK_NUM) && (gHseRequests[Id].is_used) &&
        (gHseSrvDescriptor[Id].srvId != HSE_SRV_ID_INVALID)) {

        gHseRequests[Id].request.eReqType       = HSE_IP_REQTYPE_SYNC;
        gHseRequests[Id].request.pfCallback     = NULL;
        gHseRequests[Id].request.pCallbackParam = NULL;
        gHseRequests[Id].request.u32Timeout     = u32Timeout;

        return Hse_Ip_ServiceRequest(u8MuInstance, u8MuChannel, &gHseRequests[Id].request,
                                     &gHseSrvDescriptor[Id]);
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
    if (Id < MAX_HSE_TASK_NUM) {
        hseSrvDescriptor_t *pHseSrvDescriptor = &gHseSrvDescriptor[Id];
        HOST_ADDR           RetVal            = HSE_PTR_TO_HOST_ADDR(&gHseData[Id].Hse_MuConfig);
        pHseSrvDescriptor->srvId              = HSE_SRV_ID_SET_ATTR;
        pHseSrvDescriptor->hseSrv.setAttrReq.attrId  = HSE_MU_CONFIG_ATTR_ID;
        pHseSrvDescriptor->hseSrv.setAttrReq.attrLen = sizeof(hseAttrMUConfig_t);
        pHseSrvDescriptor->hseSrv.setAttrReq.pAttr   = RetVal;
        return (hseAttrMUConfig_t *)RetVal;
    }
    return NULL;
}

hseAttrCapabilities_t *Hse_GetCapabilities(Hse_Task_ID Id) {
    if (Id < MAX_HSE_TASK_NUM) {
        hseSrvDescriptor_t *pHseSrvDescriptor = &gHseSrvDescriptor[Id];
        HOST_ADDR           RetVal = HSE_PTR_TO_HOST_ADDR(&gHseData[Id].Hse_AttrCapabilities);
        pHseSrvDescriptor->srvId   = HSE_SRV_ID_GET_ATTR;
        pHseSrvDescriptor->hseSrv.getAttrReq.attrId  = HSE_CAPABILITIES_ATTR_ID;
        pHseSrvDescriptor->hseSrv.getAttrReq.attrLen = sizeof(hseAttrCapabilities_t);
        pHseSrvDescriptor->hseSrv.getAttrReq.pAttr   = RetVal;
        return (hseAttrCapabilities_t *)RetVal;
    }
    return NULL;
}

uint8_t *Hse_GetRandomBuffer(Hse_Task_ID Id, uint8_t Level, uint32_t Size) {
    if ((Id < MAX_HSE_TASK_NUM) || (Level > HSE_RNG_CLASS_PTG3) ||
        (Size > MAX_HSE_MAX_BUFFER_SIZE)) {
        hseSrvDescriptor_t *pHseSrvDescriptor = &gHseSrvDescriptor[Id];
        HOST_ADDR           RetVal            = HSE_PTR_TO_HOST_ADDR(&gHseData[Id].Hse_Buffer[0]);
        pHseSrvDescriptor->srvId              = HSE_SRV_ID_GET_RANDOM_NUM;
        pHseSrvDescriptor->hseSrv.getRandomNumReq.rngClass        = Level;
        pHseSrvDescriptor->hseSrv.getRandomNumReq.randomNumLength = Size;
        pHseSrvDescriptor->hseSrv.getRandomNumReq.pRandomNum      = RetVal;
        return (uint8_t *)RetVal;
    }
    return NULL;
}
