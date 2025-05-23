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
#if !defined(LIBWTK3_H)
#define LIBWTK3_H (1)

#if defined(__cplusplus)
extern "C" {
#endif

#define MAX_HSE_TASK_NUM (4)

// Hse_Ip.h included
#if defined(HSE_IP_H)

typedef union {
    hseStatus_t status;
    struct {
        bool reserved : 1;              // bit 0
        bool SHESecureBoot : 1;         // bit 1
        bool SHESecureBootInit : 1;     // bit 2
        bool SHESecureBootFinished : 1; // bit 3
        bool SHESecureBootOK : 1;       // bit 4
        bool RNGInitOK : 1;             // bit 5
        bool HostDebuggerActive : 1;    // bit 6
        bool HSEDebuggerActive : 1;     // bit 7
        bool InitOK : 1;                // bit 8
        bool InstallOK : 1;             // bit 9
        bool BootOK : 1;                // bit 10
        bool CustSuperUser : 1;         // bit 11
        bool OEMSuperUser : 1;          // bit 12
#ifdef HSE_SPT_FLASHLESS_DEV
        bool PublishSysImage : 1; // bit 13
        bool PrimarySysImage : 1; // bit 14
        bool BackupSysImage : 1;  // bit 15
#else
        bool FWUpdateInProgress : 1;           // bit 13
        bool PublishNVMKeystoreRAMToFlash : 1; // bit 14
#endif
    } B;
} Hse_Status;

typedef union {
    hseAttrCapabilities_t Capabilities;
    struct {
        bool RANDOM : 1;            // bit 0
        bool SHE : 1;               // bit 1
        bool AES : 1;               // bit 2
        bool XTS_AES : 1;           // bit 3
        bool AEAD_GCM : 1;          // bit 4
        bool AEAD_CCM : 1;          // bit 5
        bool RESERVED1 : 1;         // bit 6
        bool SHA1 : 1;              // bit 7
        bool SHA2 : 1;              // bit 8
        bool SHA3 : 1;              // bit 9
        bool MP : 1;                // bit 10
        bool CMAC : 1;              // bit 11
        bool HMAC : 1;              // bit 12
        bool GMAC : 1;              // bit 13
        bool XCBC_MAC : 1;          // bit 14
        bool RSAES_NO_PADDING : 1;  // bit 15
        bool RSAES_OAEP : 1;        // bit 16
        bool RSAES_PKCS1_V15 : 1;   // bit 17
        bool RSASSA_PSS : 1;        // bit 18
        bool RSASSA_PKCS1_V15 : 1;  // bit 19
        bool ECDH : 1;              // bit 20
        bool ECDSA : 1;             // bit 21
        bool EDDSA : 1;             // bit 22
        bool MONTDH : 1;            // bit 23
        bool CLASSIC_DH : 1;        // bit 24
        bool KDF_SP800_56C : 1;     // bit 25
        bool KDF_SP800_108 : 1;     // bit 26
        bool KDF_ANS_X963 : 1;      // bit 27
        bool KDF_ISO18033_KDF1 : 1; // bit 28
        bool KDF_ISO18033_KDF2 : 1; // bit 29
        bool PBKDF2 : 1;            // bit 30
        bool KDF_TLS12_PRF : 1;     // bit 31
        bool HKDF : 1;              // bit 32
        bool KDF_IKEV2 : 1;         // bit 33

    } B;
} Hse_Capabilities;

typedef uint8_t Hse_Task_ID;

void Hse_Task_Init(void);

Hse_Task_ID Hse_Task_GetFreeSlot(void);

void Hse_Task_Release(Hse_Task_ID Id);

hseSrvResponse_t Hse_Task_MasterRequest(Hse_Task_ID Id, uint8_t u8MuInstance, uint32_t u32Timeout);

hseSrvResponse_t Hse_Task_SyncRequest(Hse_Task_ID Id, uint8_t u8MuInstance, uint32_t u32Timeout);

hseAttrMUConfig_t *Hse_GetMuConfig(Hse_Task_ID Id);

hseAttrCapabilities_t *Hse_GetCapabilities(Hse_Task_ID Id);

hseAttrFwVersion_t *Hse_GetFwVersion(Hse_Task_ID Id);

bool Hse_GetRandomBuffer(Hse_Task_ID Id, uint8_t Level, uint8_t *pBuffer, uint32_t Size);

#endif

// #if defined(CRYPTO_43_HSE_H)

// #define Crypto_Format Crypto_43_HSE_Exts_FormatKeyCatalogs

// typedef uint8_t Hse_Task_ID;

// void Hse_Task_Init(void);

// Hse_Task_ID Hse_Task_GetFreeSlot(void);

// void Hse_Task_Release(Hse_Task_ID Id);

// // Std_ReturnType Hse_Task_SyncRequest(uint32_t ObjectId, Hse_Task_ID Id);

// uint8_t *Hse_GetSHA256Buffer(Hse_Task_ID Id, uint8_t *pInputData, uint32_t Size);

// #endif

#if defined(__cplusplus)
}
#endif

#endif // LIBWTK3_H
