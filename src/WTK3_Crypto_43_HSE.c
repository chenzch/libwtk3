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
#include "Crypto_43_HSE.h"
#include "libwtk3.h"

static uint32_t     gTaskCount  = 0;
static Crypto_Task *gCryptoTask = NULL;

void Crypto_Task_Init(uint32_t TaskCount, Crypto_Task *pTasks) {
    gTaskCount = TaskCount;
    gCryptoTask = pTasks;
    for (Crypto_Task_ID index = 0; index < TaskCount; ++index) {
        Crypto_Task_Release(index);
    }
}

Crypto_Task_ID Crypto_Task_GetFreeSlot(void) {
    Crypto_Task_ID index = 0;
    for (; index < gTaskCount; index++) {
        if (!gCryptoTask[index].isUsed) {
            gCryptoTask[index].isUsed = true;
            break;
        }
    }
    return index;
}

void Crypto_Task_Release(Crypto_Task_ID Id) {
    if (Id < gTaskCount) {
        Crypto_Task *pTask = &gCryptoTask[Id];
        pTask->isUsed = false;

        Crypto_PrimitiveInfoType *pPrimitiveInfo = &pTask->PrimitiveInfo;
        Crypto_JobPrimitiveInfoType *pJobPrimitiveInfo = &pTask->JobPrimitiveInfo;
        Crypto_JobType *pJob = &pTask->Job;

        pPrimitiveInfo->service = (Crypto_ServiceInfoType)-1U;
        pPrimitiveInfo->algorithm.family = CRYPTO_ALGOFAM_NOT_SET;
        pPrimitiveInfo->algorithm.secondaryFamily = CRYPTO_ALGOFAM_NOT_SET;
        pPrimitiveInfo->algorithm.keyLength = 0;
        pPrimitiveInfo->algorithm.mode = CRYPTO_ALGOMODE_NOT_SET;

        pJobPrimitiveInfo->callbackId = 0;
        pJobPrimitiveInfo->primitiveInfo = pPrimitiveInfo;
        pJobPrimitiveInfo->cryIfKeyId = 0;
        pJobPrimitiveInfo->processingType = CRYPTO_PROCESSING_SYNC;

        pJob->jobId = Id + 1;
        pJob->jobState = CRYPTO_JOBSTATE_IDLE;
        pJob->jobPrimitiveInputOutput.inputPtr = NULL;
        pJob->jobPrimitiveInputOutput.inputLength = 0;
        pJob->jobPrimitiveInputOutput.secondaryInputPtr = NULL;
        pJob->jobPrimitiveInputOutput.secondaryInputLength = 0;
        pJob->jobPrimitiveInputOutput.tertiaryInputPtr = NULL;
        pJob->jobPrimitiveInputOutput.tertiaryInputLength = 0;
        pJob->jobPrimitiveInputOutput.outputPtr = NULL;
        pJob->jobPrimitiveInputOutput.outputLengthPtr = NULL;
        pJob->jobPrimitiveInputOutput.secondaryOutputPtr = NULL;
        pJob->jobPrimitiveInputOutput.secondaryOutputLengthPtr = NULL;
        pJob->jobPrimitiveInputOutput.verifyPtr = NULL;
        pJob->jobPrimitiveInputOutput.mode = CRYPTO_OPERATIONMODE_SINGLECALL;
        pJob->jobPrimitiveInputOutput.cryIfKeyId = 0;
        pJob->jobPrimitiveInputOutput.targetCryIfKeyId = 0;
        pJob->jobPrimitiveInfo = pJobPrimitiveInfo;
        pJob->jobRedirectionInfoRef = NULL;
        pJob->cryptoKeyId = 0;
        pJob->targetCryptoKeyId = 0;
        pJob->jobPriority = 0;
    }
}

Std_ReturnType Crypto_Task_SyncRequest(uint32_t ObjectId, Crypto_Task_ID Id) {
    if ((Id < gTaskCount) && (gCryptoTask[Id].isUsed)) {
        gCryptoTask[Id].Job.jobPrimitiveInfo->processingType = CRYPTO_PROCESSING_SYNC;
        return Crypto_43_HSE_ProcessJob(ObjectId, &gCryptoTask[Id].Job);
    }
    return E_NOT_OK;
}

Std_ReturnType Crypto_Task_AsyncRequest(uint32_t ObjectId, Crypto_Task_ID Id) {
    if ((Id < gTaskCount) && (gCryptoTask[Id].isUsed)) {
        gCryptoTask[Id].Job.jobPrimitiveInfo->processingType = CRYPTO_PROCESSING_ASYNC;
        return Crypto_43_HSE_ProcessJob(ObjectId, &gCryptoTask[Id].Job);
    }
    return E_NOT_OK;
}

Crypto_JobStateType Crypto_Task_GetResponse(Crypto_Task_ID Id) {
    if ((Id < gTaskCount) && (gCryptoTask[Id].isUsed)) {
        Crypto_43_HSE_MainFunction();
        return gCryptoTask[Id].Job.jobState;
    }
    return CRYPTO_JOBSTATE_IDLE; // Return idle state if the task is not used or invalid ID
}


    // /* bSingleCallOnly, bCheckTargetKeyId, u8InputModeMask, u8SecondaryInputModeMask, u8TertiaryInputModeMask, u8OutputModeMask, u8SecondaryOutputModeMask, u8VerifyPtrModeMask */
    // {  (boolean)FALSE,   (boolean)FALSE,     CRYPTO_U_U8,            0x0U,                    0x0U,              CRYPTO_F_U8,              0x0U,                   0x0U         },  /* CRYPTO_HASH                  Idx = 0x00 */
    // {  (boolean)FALSE,   (boolean)FALSE,     CRYPTO_U_U8,            0x0U,                    0x0U,              CRYPTO_F_U8,              0x0U,                   0x0U         },  /* CRYPTO_MACGENERATE           Idx = 0x01 */
    // {  (boolean)FALSE,   (boolean)FALSE,     CRYPTO_U_U8,         CRYPTO_F_U8,                0x0U,                 0x0U,                  0x0U,                CRYPTO_F_U8     },  /* CRYPTO_MACVERIFY             Idx = 0x02 */
    // {  (boolean)FALSE,   (boolean)FALSE,     CRYPTO_U_U8,            0x0U,                    0x0U,              CRYPTO_UF_U8,             0x0U,                   0x0U         },  /* CRYPTO_ENCRYPT               Idx = 0x03 */
    // {  (boolean)FALSE,   (boolean)FALSE,     CRYPTO_U_U8,            0x0U,                    0x0U,              CRYPTO_UF_U8,             0x0U,                   0x0U         },  /* CRYPTO_DECRYPT               Idx = 0x04 */
    // {  (boolean)FALSE,   (boolean)FALSE,     CRYPTO_U_U8,         CRYPTO_F_U8,                0x0U,              CRYPTO_UF_U8,          CRYPTO_F_U8,               0x0U         },  /* CRYPTO_AEADENCRYPT           Idx = 0x05 */
    // {  (boolean)FALSE,   (boolean)FALSE,     CRYPTO_U_U8,         CRYPTO_F_U8,             CRYPTO_F_U8,          CRYPTO_UF_U8,             0x0U,                CRYPTO_F_U8     },  /* CRYPTO_AEADDECRYPT           Idx = 0x06 */
    // {  (boolean)FALSE,   (boolean)FALSE,     CRYPTO_U_U8,            0x0U,                    0x0U,              CRYPTO_F_U8,              0x0U,                   0x0U         },  /* CRYPTO_SIGNATUREGENERATE     Idx = 0x07 */
    // {  (boolean)FALSE,   (boolean)FALSE,     CRYPTO_U_U8,         CRYPTO_F_U8,                0x0U,                 0x0U,                  0x0U,                CRYPTO_F_U8     },  /* CRYPTO_SIGNATUREVERIFY       Idx = 0x08 */
    // {  (boolean)TRUE,    (boolean)FALSE,        0x0U,                0x0U,                    0x0U,                 0x0U,                  0x0U,                   0x0U         },  /* CRYPTO_KEYGENERATE           Idx = 0x0D */
    // {  (boolean)TRUE,    (boolean)TRUE,         0x0U,                0x0U,                    0x0U,                 0x0U,                  0x0U,                   0x0U         },  /* CRYPTO_KEYDERIVE             Idx = 0x0E */
    // {  (boolean)TRUE,    (boolean)FALSE,        0x0U,             CRYPTO_F_U8,                0x0U,                 0x0U,                  0x0U,                   0x0U         },  /* CRYPTO_KEYEXCHANGECALCPUBVAL Idx = 0x0F */
    // {  (boolean)TRUE,    (boolean)FALSE,     CRYPTO_F_U8,            0x0U,                    0x0U,                 0x0U,                  0x0U,                   0x0U         },  /* CRYPTO_KEYEXCHANGECALCSECRET Idx = 0x10 */
    // {  (boolean)TRUE,    (boolean)FALSE,        0x0U,                0x0U,                    0x0U,                 0x0U,                  0x0U,                   0x0U         },  /* CRYPTO_KEYSETVALID           Idx = 0x13 */
    // {  (boolean)TRUE,    (boolean)FALSE,        0x0U,                0x0U,                    0x0U,                 0x0U,                  0x0U,                   0x0U         }   /* CRYPTO_KEYSETINVALID         Idx = 0x14 */

// CRYPTO_RANDOMSEED CRYPTO_43_HSE_RET_NOT_SUPPORTED

// CRYPTO_RANDOMGENERATE
// /* bSingleCallOnly, bCheckTargetKeyId, u8InputModeMask, u8SecondaryInputModeMask, u8TertiaryInputModeMask, u8OutputModeMask, u8SecondaryOutputModeMask, u8VerifyPtrModeMask */
// {  (boolean)TRUE,    (boolean)FALSE,        0x0U,                0x0U,                    0x0U,              CRYPTO_F_U8,              0x0U,                   0x0U         },  /* CRYPTO_RANDOMGENERATE        Idx = 0x0B */
void Crypto_Task_GetRandomBuffer(Crypto_Task_ID Id, uint8_t Level, uint8_t *pBuffer, uint32_t *pSize) {
    if ((Id < gTaskCount) && (gCryptoTask[Id].isUsed)) {
        Crypto_Task *pTask = &gCryptoTask[Id];

        Crypto_PrimitiveInfoType *pPrimitiveInfo = &pTask->PrimitiveInfo;
        Crypto_JobType *pJob = &pTask->Job;

        pPrimitiveInfo->service = CRYPTO_RANDOMGENERATE;
        switch (Level)
        {
        case HSE_RNG_CLASS_DRG4: // Level 1
            pPrimitiveInfo->algorithm.mode = CRYPTO_43_HSE_ALGOMODE_CUSTOM_DRBG_PR;
            /* code */
            break;
        case HSE_RNG_CLASS_PTG3: // Level 2
            pPrimitiveInfo->algorithm.mode = CRYPTO_43_HSE_ALGOMODE_CUSTOM_DRBG_RS;
            break;
        case HSE_RNG_CLASS_DRG3: // Level 0
            /* no break */
        default: // Level 0
            pPrimitiveInfo->algorithm.mode = CRYPTO_ALGOMODE_CTRDRBG;
            break;
        }

        pJob->jobPrimitiveInputOutput.outputPtr = pBuffer;
        pJob->jobPrimitiveInputOutput.outputLengthPtr = pSize;
    }
}
