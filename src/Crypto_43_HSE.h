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
#ifndef CRYPTO_43_HSE_H
#define CRYPTO_43_HSE_H

#define E_NOT_OK 0x01U

typedef uint8_t Std_ReturnType;

typedef enum
{
    CRYPTO_HASH                  = 0x00U,  /* Hash Service */
    CRYPTO_MACGENERATE           = 0x01U,  /* MacGenerate Service */
    CRYPTO_MACVERIFY             = 0x02U,  /* MacVerify Service */
    CRYPTO_ENCRYPT               = 0x03U,  /* Encrypt Service */
    CRYPTO_DECRYPT               = 0x04U,  /* Decrypt Service */
    CRYPTO_AEADENCRYPT           = 0x05U,  /* AEADEncrypt Service */
    CRYPTO_AEADDECRYPT           = 0x06U,  /* AEADDecrypt Service */
    CRYPTO_SIGNATUREGENERATE     = 0x07U,  /* SignatureGenerate Service */
    CRYPTO_SIGNATUREVERIFY       = 0x08U,  /* SignatureVerify Service */
    CRYPTO_RANDOMGENERATE        = 0x0BU,  /* RandomGenerate Service */
    CRYPTO_RANDOMSEED            = 0x0CU,  /* RandomSeed Service */
    CRYPTO_KEYGENERATE           = 0x0DU,  /* KeyGenerate Service */
    CRYPTO_KEYDERIVE             = 0x0EU,  /* KeyDerive Service */
    CRYPTO_KEYEXCHANGECALCPUBVAL = 0x0FU,  /* KeyExchangeCalcpubVal Service */
    CRYPTO_KEYEXCHANGECALCSECRET = 0x10U,  /* KeyExchangeCalcSecret Service */
    CRYPTO_KEYSETVALID           = 0x13U,  /* KeySetValid Service */
    CRYPTO_KEYSETINVALID         = 0x14U   /* KeySetInvalid Service */
} Crypto_ServiceInfoType;

typedef enum
{
    CRYPTO_ALGOFAM_NOT_SET                      = 0x00U, /* Algorithm family is not set */
    CRYPTO_ALGOFAM_SHA1                         = 0x01U, /* SHA1 hash */
    CRYPTO_ALGOFAM_SHA2_224                     = 0x02U, /* SHA2-224 hash */
    CRYPTO_ALGOFAM_SHA2_256                     = 0x03U, /* SHA2-256 hash */
    CRYPTO_ALGOFAM_SHA2_384                     = 0x04U, /* SHA2-384 hash */
    CRYPTO_ALGOFAM_SHA2_512                     = 0x05U, /* SHA2-512 hash */
    CRYPTO_ALGOFAM_SHA2_512_224                 = 0x06U, /* SHA2-512/224 hash */
    CRYPTO_ALGOFAM_SHA2_512_256                 = 0x07U, /* SHA2-512/256 hash */
    CRYPTO_ALGOFAM_SHA3_224                     = 0x08U, /* SHA3-224 hash */
    CRYPTO_ALGOFAM_SHA3_256                     = 0x09U, /* SHA3-256 hash */
    CRYPTO_ALGOFAM_SHA3_384                     = 0x0AU, /* SHA3-384 hash */
    CRYPTO_ALGOFAM_SHA3_512                     = 0x0BU, /* SHA3-512 hash */
    CRYPTO_ALGOFAM_SHAKE128                     = 0x0CU, /* SHAKE128 hash */
    CRYPTO_ALGOFAM_SHAKE256                     = 0x0DU, /* SHAKE256 hash */
    CRYPTO_ALGOFAM_RIPEMD160                    = 0x0EU, /* RIPEMD hash */
    CRYPTO_ALGOFAM_BLAKE_1_256                  = 0x0FU, /* BLAKE-1-256 hash */
    CRYPTO_ALGOFAM_BLAKE_1_512                  = 0x10U, /* BLAKE-1-512 hash */
    CRYPTO_ALGOFAM_BLAKE_2s_256                 = 0x11U, /* BLAKE-2s-256 hash */
    CRYPTO_ALGOFAM_BLAKE_2s_512                 = 0x12U, /* BLAKE-2s-512 hash */
    CRYPTO_ALGOFAM_3DES                         = 0x13U, /* 3DES cipher */
    CRYPTO_ALGOFAM_AES                          = 0x14U, /* AES cipher */
    CRYPTO_ALGOFAM_CHACHA                       = 0x15U, /* ChaCha cipher */
    CRYPTO_ALGOFAM_RSA                          = 0x16U, /* RSA cipher */
    CRYPTO_ALGOFAM_ED25519                      = 0x17U, /* ED22519 elliptic curve */
    CRYPTO_ALGOFAM_BRAINPOOL                    = 0x18U, /* Brainpool elliptic curve */
    CRYPTO_ALGOFAM_ECCNIST                      = 0x19U, /* NIST ECC elliptic curves */
    CRYPTO_ALGOFAM_RNG                          = 0x1BU, /* Random Number Generator */
    CRYPTO_ALGOFAM_SIPHASH                      = 0x1CU, /* SipHash */
    CRYPTO_ALGOFAM_ECCANSI                      = 0x1EU, /* Elliptic curve according to ANSI X9.62 */
    CRYPTO_ALGOFAM_ECCSEC                       = 0x1FU, /* Elliptic curve according to SECG */
    CRYPTO_ALGOFAM_DRBG                         = 0x20U, /* Random number generator according to NIST SP800-90A */
    CRYPTO_ALGOFAM_FIPS186                      = 0x21U, /* Random number generator according to FIPS 186. */
    CRYPTO_ALGOFAM_PADDING_PKCS7                = 0x22U, /* Cipher padding according to PKCS.7 */
    CRYPTO_ALGOFAM_PADDING_ONEWITHZEROS         = 0x23U, /* Cipher padding mode. Fill/verify data with 0, but first bit after the data is 1. Eg. "DATA" & 0x80 & 0x00... */
    CRYPTO_ALGOFAM_PBKDF2                       = 0x24U, /* Password-Based Key Derivation Function 2 */
    CRYPTO_ALGOFAM_KDFX963                      = 0x25U, /* ANSI X9.63 Public Key Cryptography */
    CRYPTO_ALGOFAM_DH                           = 0x26U, /* Diffie-Hellman */
    CRYPTO_ALGOFAM_SM2                          = 0x27U, /* SM2 elliptic curve algorithm */
    CRYPTO_ALGOFAM_EEA3                         = 0x28U, /* Stream cipher based on [x01] */
    CRYPTO_ALGOFAM_SM3                          = 0x29U, /* Chinese hash algorithm based on [x02] */
    CRYPTO_ALGOFAM_EIA3                         = 0x2AU, /* Authentication algorithm [x01] */
    CRYPTO_ALGOFAM_HKDF                         = 0x2BU, /* HMAC-based extract-and-expand key derivation function */
    CRYPTO_ALGOFAM_ECDSA                        = 0x2CU, /* Elliptic-curve Digital Signatures */
    CRYPTO_ALGOFAM_POLY1305                     = 0x2DU, /* MAC calculation algorithm */
    CRYPTO_ALGOFAM_X25519                       = 0x2EU, /* Elliptic curve X25519 for ECDH */
    CRYPTO_ALGOFAM_ECDH                         = 0x2FU, /* Elliptic-curve Diffie Hellman */
    CRYPTO_ALGOFAM_CUSTOM                       = 0xFFU  /* Custom algorithm family */
} Crypto_AlgorithmFamilyType;

typedef enum
{
    CRYPTO_ALGOMODE_NOT_SET           = 0x00U,  /* Algorithm key is not set */
    CRYPTO_ALGOMODE_ECB               = 0x01U,  /* Blockmode: Electronic Code Book */
    CRYPTO_ALGOMODE_CBC               = 0x02U,  /* Blockmode: Cipher Block Chaining */
    CRYPTO_ALGOMODE_CFB               = 0x03U,  /* Blockmode: Cipher Feedback Mode */
    CRYPTO_ALGOMODE_OFB               = 0x04U,  /* Blockmode: Output Feedback Mode */
    CRYPTO_ALGOMODE_CTR               = 0x05U,  /* Blockmode: Counter Modex */
    CRYPTO_ALGOMODE_GCM               = 0x06U,  /* Blockmode: Galois/Counter Mode */
    CRYPTO_ALGOMODE_XTS               = 0x07U,  /* XEX Tweakable Block Cipher with Ciphertext Stealing */
    CRYPTO_ALGOMODE_RSAES_OAEP        = 0x08U,  /* RSA Optimal Asymmetric Encryption Padding */
    CRYPTO_ALGOMODE_RSAES_PKCS1_v1_5  = 0x09U,  /* RSA encryption/decryption with PKCS#1 v1.5 padding */
    CRYPTO_ALGOMODE_RSASSA_PSS        = 0x0AU,  /* RSA Probabilistic Signature Scheme */
    CRYPTO_ALGOMODE_RSASSA_PKCS1_v1_5 = 0x0BU,  /* RSA signature with PKCS#1 v1.5 */
    CRYPTO_ALGOMODE_8ROUNDS           = 0x0CU,  /* 8 rounds (e.g. ChaCha8) */
    CRYPTO_ALGOMODE_12ROUNDS          = 0x0DU,  /* 12 rounds (e.g. ChaCha12) */
    CRYPTO_ALGOMODE_20ROUNDS          = 0x0EU,  /* 20 rounds (e.g. ChaCha20) */
    CRYPTO_ALGOMODE_HMAC              = 0x0FU,  /* Hashed-based MAC */
    CRYPTO_ALGOMODE_CMAC              = 0x10U,  /* Cipher-based MAC */
    CRYPTO_ALGOMODE_GMAC              = 0x11U,  /* Galois MAC */
    CRYPTO_ALGOMODE_CTRDRBG           = 0x12U,  /* Counter-based Deterministic Random Bit Generator */
    CRYPTO_ALGOMODE_SIPHASH_2_4       = 0x13U,  /* Siphash-2-4 */
    CRYPTO_ALGOMODE_SIPHASH_4_8       = 0x14U,  /* Siphash-4-8 */
    CRYPTO_ALGOMODE_PXXXR1            = 0x15U,  /* ANSI R1 Curve */
    CRYPTO_ALGOMODE_CUSTOM            = 0xffU   /* Custom algorithm mode */
} Crypto_AlgorithmModeType;

typedef struct
{
    Crypto_AlgorithmFamilyType family;          /* The family of the algorithm */
    Crypto_AlgorithmFamilyType secondaryFamily; /* The secondary family of the algorithm  */
    uint32_t                   keyLength;       /* The key length in bits to be used with that algorithm */
    Crypto_AlgorithmModeType   mode;            /* The operation mode to be used with that algorithm */
} Crypto_AlgorithmInfoType;

typedef struct
{
    Crypto_ServiceInfoType   service;   /* Contains the enum of the used service, e.g. Encrypt */
    Crypto_AlgorithmInfoType algorithm; /* Contains the information of the used algorithm */
} Crypto_PrimitiveInfoType;

typedef enum
{
    CRYPTO_PROCESSING_ASYNC = 0x00U, /* Asynchronous job processing */
    CRYPTO_PROCESSING_SYNC  = 0x01U  /* Synchronous  job processing */
} Crypto_ProcessingType;

typedef struct
{
    uint32_t                  callbackId;     /* Identifier of the callback function, to be called, if the configured service finished. */
    Crypto_PrimitiveInfoType* primitiveInfo;  /* Pointer to a structure containing further configuration of the crypto primitives */
    uint32_t                  cryIfKeyId;     /* Identifier of the CryIf key. */
    Crypto_ProcessingType     processingType; /* Determines the synchronous or asynchronous behavior. */
} Crypto_JobPrimitiveInfoType;

typedef enum
{
    CRYPTO_JOBSTATE_IDLE   = 0x00U, /* Job is in the state "idle". This state is reached after Csm_Init() or when the "Finish" state is finished. */
    CRYPTO_JOBSTATE_ACTIVE = 0x01U  /* Job is in the state "active". There was already some input or there are intermediate results. This state is reached, when the "update" or "start" operation  finishes. */
} Crypto_JobStateType;

typedef enum
{
    CRYPTO_E_VER_OK     = 0x00U, /* The result of the verification is "true", i.e. the two compared elements are identical. This return code shall be given as value "0" */
    CRYPTO_E_VER_NOT_OK = 0x01U  /* The result of the verification is "false", i.e. the two compared elements are not identical. This return code shall be given as value "1". */
} Crypto_VerifyResultType;

typedef enum
{
    CRYPTO_OPERATIONMODE_START           = 0x01U, /* Operation Mode is "Start". The job's state shall be reset, i.e. previous input data and intermediate results shall be deleted. */
    CRYPTO_OPERATIONMODE_UPDATE          = 0x02U, /* Operation Mode is "Update". Used to calculate intermediate results. */
    CRYPTO_OPERATIONMODE_STREAMSTART     = 0x03U, /* Operation Mode is "Stream Start". Mixture of "Start" and "Update". Used for streaming. */
    CRYPTO_OPERATIONMODE_FINISH          = 0x04U, /* Operation Mode is "Finish". The calculations shall be finalized */
    CRYPTO_OPERATIONMODE_SINGLECALL      = 0x07U, /* Operation Mode is "Single Call". Mixture of "Start", "Update" and "Finish". */
    CRYPTO_OPERATIONMODE_SAVE_CONTEXT    = 0x08U, /* Operation mode is "Save workspace context". Context data shall be provided by the crypto driver to the application. */
    CRYPTO_OPERATIONMODE_RESTORE_CONTEXT = 0x10U  /* Operation mode is "Restore workspace context". Application provides the context data that was previously stored and the crypto driver shall restore the internal workspace. */
} Crypto_OperationModeType;

typedef struct
{
    const uint8_t*           inputPtr;                  /* Pointer to the input data. */
    uint32_t                 inputLength;               /* Contains the input length in bytes. */
    const uint8_t*           secondaryInputPtr;         /* Pointer to the secondary input data (for MacVerify, SignatureVerify). */
    uint32_t                 secondaryInputLength;      /* Contains the secondary input length in bytes. */
    const uint8_t*           tertiaryInputPtr;          /* Pointer to the tertiary input data (for MacVerify, SignatureVerify). */
    uint32_t                 tertiaryInputLength;       /* Contains the tertiary input length in bytes. */
    uint8_t*                 outputPtr;                 /* Pointer to the output data. */
    uint32_t*                outputLengthPtr;           /* Holds a pointer to a memory location containing the output length in bytes. */
    uint8_t*                 secondaryOutputPtr;        /* Pointer to the secondary output data. */
    uint32_t*                secondaryOutputLengthPtr;  /* Holds a pointer to a memory location containing the secondary output length in bytes. */
    Crypto_VerifyResultType* verifyPtr;                 /* Output pointer to a memory location holding a Crypto_VerifyResultType */
    Crypto_OperationModeType mode;                      /* Indicator of the mode(s)/operation(s) to be performed */
    uint32_t                 cryIfKeyId;                /* Holds the CryIf key id for key operation services. */
    uint32_t                 targetCryIfKeyId;          /* Holds the target CryIf key id for key operation services. */
} Crypto_JobPrimitiveInputOutputType;

typedef struct
{
    uint8_t  redirectionConfig;           /* Bit structure which indicates which buffer shall be redirected to a key element. Values from Crypto_InputOutputRedirectionConfigType can be used and combined with unary OR operation. */
    uint32_t inputKeyId;                  /* Identifier of the key which shall be used as input */
    uint32_t inputKeyElementId;           /* Identifier of the key element which shall be used as input */
    uint32_t secondaryInputKeyId;         /* Identifier of the key which shall be used as secondary input */
    uint32_t secondaryInputKeyElementId;  /* Identifier of the key element which shall be used as secondary input */
    uint32_t tertiaryInputKeyId;          /* Identifier of the key which shall be used as tertiary input */
    uint32_t tertiaryInputKeyElementId;   /* Identifier of the key element which shall be used as tertiary input */
    uint32_t outputKeyId;                 /* Identifier of the key which shall be used as output */
    uint32_t outputKeyElementId;          /* Identifier of the key element which shall be used as output */
    uint32_t secondaryOutputKeyId;        /* Identifier of the key which shall be used as secondary output */
    uint32_t secondaryOutputKeyElementId; /* Identifier of the key element which shall be used as secondary output */
} Crypto_JobRedirectionInfoType;

typedef struct
{
    uint32_t                           jobId;                   /* Identifier for the job structure */
    Crypto_JobStateType                jobState;                /* Determines the current job state */
    Crypto_JobPrimitiveInputOutputType jobPrimitiveInputOutput; /* Structure containing input and output information depending on the job and the crypto primitive */
    Crypto_JobPrimitiveInfoType*       jobPrimitiveInfo;        /* Pointer to a structure containing further information, which depends on the job and the crypto primitive */
    Crypto_JobRedirectionInfoType*     jobRedirectionInfoRef;   /* Pointer to a structure containing further information on the usage of keys as input and output for jobs. */
    uint32_t                           cryptoKeyId;             /* Identifier of the Crypto Driver key. The identifier shall be written by the Crypto Interface. */
    uint32_t                           targetCryptoKeyId;       /* Target identifier of the Crypto Driver key. The identifier shall be written by the Crypto Interface. */
    uint32_t                           jobPriority;             /* Specifies the importance of the job (the higher, the more important). */
} Crypto_JobType;

Std_ReturnType Crypto_43_HSE_ProcessJob(uint32_t objectId, Crypto_JobType* job);

void Crypto_43_HSE_MainFunction (void);

#define CRYPTO_43_HSE_ALGOMODE_CUSTOM_DRBG_PR ((uint8_t)130)  /* Deterministic Random Bit Generator with prediction resistance */
#define CRYPTO_43_HSE_ALGOMODE_CUSTOM_DRBG_RS ((uint8_t)131)  /* Deterministic Random Bit Generator with prediction resistance and reseed for each 16 bytes of data */

#endif
