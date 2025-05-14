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
#ifndef HSE_IP_H
#define HSE_IP_H

#ifdef __cplusplus
extern "C" {
#endif

typedef uint16_t hseStatus_t;

typedef enum {
    HSE_IP_REQTYPE_SYNC =
        0UL, /*!< Synchronous - the service request function does not return until the HSE completes
                                     the request, or the timeout expires */
    HSE_IP_REQTYPE_ASYNC_IRQ, /*!< Asynchronous using interrupts - the service request function returns right after
                                     sending the request to HSE; an interrupt is triggered when HSE completes the request
                                     (application can be notified through the channel callback) */
    HSE_IP_REQTYPE_ASYNC_POLL /*!< Asynchronous polling - the service request function returns right after sending the
                                     request to HSE; application must poll the driver by calling Hse_Ip_MainFunction */
} Hse_Ip_ReqTypeType;

typedef void (*Hse_Ip_pfResponseCallbackType)(uint8_t u8MuInstance, uint8_t u8MuChannel,
                                              hseSrvResponse_t HseResponse, void *pCallbackParam);

typedef struct {
    Hse_Ip_ReqTypeType            eReqType;   /*!< Selects the request type (SYNC/ASYNC) */
    Hse_Ip_pfResponseCallbackType pfCallback; /*!< The callback for asynchronous request */
    void *pCallbackParam; /*!< Parameter used to call the asynchronous callback(can be NULL) */
    uint32_t
        u32Timeout; /*!< Timeout for the synchronous requests (in us or ticks depending on selected counter) */
} Hse_Ip_ReqType;

hseSrvResponse_t Hse_Ip_ServiceRequest(uint8_t u8MuInstance, uint8_t u8MuChannel,
                                       Hse_Ip_ReqType *pRequest, hseSrvDescriptor_t *pHseSrvDesc);

#define HSE_IP_INVALID_MU_CHANNEL_U8 ((uint8_t)0xFFU)
uint8_t Hse_Ip_GetFreeChannel(uint8_t u8MuInstance);

#ifdef __cplusplus
}
#endif

#endif /* HSE_IP_H */
