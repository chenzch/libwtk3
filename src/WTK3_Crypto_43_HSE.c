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
static pCrypto_Task gCryptoTask = NULL;

void Crypto_Task_Init(uint32_t TaskCount, pCrypto_Task pTasks) {
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
        pCrypto_Task pTask = &gCryptoTask[Id];
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
    return 0x01U;
}
