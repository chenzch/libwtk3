/**
*   @file    hse_interface.h
*
*   @brief   HSE service descriptor definition.
*   @details This file contains the HSE service descriptor definition.
*
*/
/*==================================================================================================
*
*   Copyright 2019 - 2023 NXP.
*
*   This software is owned or controlled by NXP and may only be used strictly in accordance with
*   the applicable license terms. By expressly accepting such terms or by downloading, installing,
*   activating and/or otherwise using the software, you are agreeing that you have read, and that
*   you agree to comply with and are bound by, such license terms. If you do not agree to
*   be bound by the applicable license terms, then you may not retain, install, activate or
*   otherwise use the software.
==================================================================================================*/

#ifndef HSE_INTERFACE_H
#define HSE_INTERFACE_H

#ifdef __cplusplus
extern "C"{
#endif

/* GNU Compiler &  DIAB Compiler */
#if (defined (__GNUC__) && defined (__DCC__))
    #pragma clang diagnostic push
    #pragma clang diagnostic ignored "-Wpragma-pack"
#endif

/*==================================================================================================
*                                        INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/

#if defined(CUSTOM_STDINT_H)
    /* Define at compile time the header file containing the definition for custom types from stdint */
    #include CUSTOM_STDINT_H
#else
    /* Default - include stdint.h */
    #include <stdint.h>
    #include <stdbool.h>
#endif

/* Standard typedefs used by header files, based on ISO C standard */
typedef volatile int8_t vint8_t;
typedef volatile uint8_t vuint8_t;

typedef volatile int16_t vint16_t;
typedef volatile uint16_t vuint16_t;

typedef volatile int32_t vint32_t;
typedef volatile uint32_t vuint32_t;

typedef volatile int64_t vint64_t;
typedef volatile uint64_t vuint64_t;

typedef uint8_t bool_t;

#ifndef TRUE
    /**
    * @brief Boolean true value
    */
    #define TRUE true
#endif
#ifndef FALSE
    /**
    * @brief Boolean false value
    */
    #define FALSE false
#endif

#ifndef NULL
    #define NULL ((void *)0)
#endif
/** @} */


/* ***********************************************
* Define all supported HSE platform
**************************************************/
#define HSE_S32G2XX          1U     /**< @brief  S32G2xx platform. */
#define HSE_S32S2XX          2U     /**< @brief  S32S2xx platform. */
#define HSE_S32K2TV          3U     /**< @brief  S32K2TV platform. */
#define HSE_S32R45X          4U     /**< @brief  S32R45X platform. */
#define HSE_S32K3X4          5U     /**< @brief  S32K3X4 platform. */
#define HSE_S32R41X          6U     /**< @brief  S32R41X platform. */
#define HSE_SAF85XX          7U     /**< @brief  SAF85XX platform. */
#define HSE_S32K3X1          12U    /**< @brief  S32K3X1 platform. */
#define HSE_S32K3X2          13U    /**< @brief  S32K3X2 platform. */
#define HSE_S32K358          14U    /**< @brief  S32K3X8 platform renamed to S32K358 platform. */
#define HSE_S32K3X6          15U    /**< @brief  S32K3X6 platform. */
#define HSE_S32K388          16U    /**< @brief  S32K388 platform. */

#define HSE_S32G3XX          20U    /**< @brief  S32G3XX platform. */
#define HSE_S32ZE            30U    /**< @brief  S32ZE   platforms. */
#define HSE_S32Z1XX          31U    /**< @brief  S32Z1XX platform */

/*==================================================================================================
*                                      DEFINES AND MACROS
==================================================================================================*/

/* ***********************************************
* Define HSE FW type
**************************************************/
#define HSE_STANDARD_FW 0
#define HSE_FULLMEM_TYPE 0
#define HSE_ABSWAP_TYPE 1

/* ***********************************************
* Define current configuration
**************************************************/
#define HSE_FWTYPE         HSE_STANDARD_FW         /**< @brief  HSE FW Type. */
#define HSE_SWAPTYPE       HSE_FULLMEM_TYPE        /**< @brief  HSE SWAP Type. */

/**
 * HSE_PLATFORM
 * HSE_S32K3X4 - S32K344, S32K324, S32K314
 * HSE_S32K3X1 - S32K311, S32K310
 * HSE_S32K3X2 - S32K312, S32K342, S32K322, S32K341
 * HSE_S32K358 - S32K358, S32K348, S32K338, S32K328, S32K336, S32K356
 * HSE_S32K3X6 - S32K396, S32K376, S32K394, S32K374
 * HSE_S32K388 - S32K388
 */
#if defined(CPU_S32K344) || defined(CPU_S32K324) || defined(CPU_S32K314)
    #define HSE_PLATFORM       HSE_S32K3X4              /**< @brief  HSE Platform. */
#elif defined(CPU_S32K311) || defined(CPU_S32K310)
    #define HSE_PLATFORM       HSE_S32K3X1              /**< @brief  HSE Platform. */
#elif defined(CPU_S32K312) || defined(CPU_S32K342) || defined(CPU_S32K322) || defined(CPU_S32K341)
    #define HSE_PLATFORM       HSE_S32K3X2              /**< @brief  HSE Platform. */
#elif defined(CPU_S32K358) || defined(CPU_S32K348) || defined(CPU_S32K338) || defined(CPU_S32K328) || defined(CPU_S32K336) || defined(CPU_S32K356)
    #define HSE_PLATFORM       HSE_S32K358              /**< @brief  HSE Platform. */
#elif defined(CPU_S32K396) || defined(CPU_S32K376) || defined(CPU_S32K394) || defined(CPU_S32K374) || defined(CPU_S32K366) || defined(CPU_S32K364)
    #define HSE_PLATFORM       HSE_S32K3X6              /**< @brief  HSE Platform. */
#elif defined(CPU_S32K388)
    #define HSE_PLATFORM       HSE_S32K388              /**< @brief  HSE Platform. */
#else
    #error "No platform is selected. At least one platform should be selected."
#endif

#define HSE_FW_VERSION { \
    HSE_SWAPTYPE,     /* reserved */ \
    HSE_PLATFORM,     /* socTypeId */ \
    0U,     /* fwTypeId */ \
    2U,     /* majorVersion */ \
    55U,     /* minorVersion */ \
    0U      /* patchVersion */ \
}

/*==================================================================================================
*                                      DEFINES AND MACROS
==================================================================================================*/
/* ENABLE SPECIFIC FEATURES HERE */
#if (HSE_PLATFORM == HSE_S32G2XX)
    #define HSE_H
    #define HSE_SPT_64BIT_ADDR                  /**< @brief HSE supports 64-bit address. */
    #define HSE_SPT_PHYSICAL_TAMPER_CONFIG      /**< @brief HSE supports the physical tamper configuration. */
    #define HSE_SPT_TEMP_SENS_VIO_CONFIG        /**< @brief HSE supports the temperature sensor configuration. */
    #define HSE_SPT_CMU                         /**< @brief Support for CMU tamper (clock integrity verification) */
    #define HSE_NUM_OF_OTFAD_INSTANCES    (1U)  /**< @brief The supported number of OTFAD Instances */
#elif (HSE_PLATFORM == HSE_S32G3XX)
    #define HSE_H
    #define HSE_SPT_64BIT_ADDR                  /**< @brief HSE supports 64-bit address. */
    #define HSE_SPT_HW_SHA3                     /**< @brief HSE supports SHA3 accelerated in HW. */
    #define HSE_SPT_PHYSICAL_TAMPER_CONFIG      /**< @brief HSE supports the physical tamper configuration. */
    #define HSE_SPT_TEMP_SENS_VIO_CONFIG        /**< @brief HSE supports the temperature sensor configuration. */
    #define HSE_SPT_CMU                         /**< @brief Support for CMU tamper (clock integrity verification) */
    #define HSE_NUM_OF_OTFAD_INSTANCES    (1U)  /**< @brief The supported number of OTFAD Instances */
#elif (HSE_PLATFORM == HSE_S32R45X)
    #define HSE_H
    #define HSE_SPT_64BIT_ADDR                  /**< @brief HSE supports 64-bit address. */
    #define HSE_SPT_TEMP_SENS_VIO_CONFIG        /**< @brief HSE supports the temperature sensor configuration. */
    #define HSE_SPT_CMU                         /**< @brief Support for CMU tamper (clock integrity verification) */
    #define HSE_NUM_OF_OTFAD_INSTANCES    (1U)  /**< @brief The supported number of OTFAD Instances */
#elif (HSE_PLATFORM == HSE_S32S2XX)
    #define HSE_H

#elif (HSE_PLATFORM == HSE_S32ZE)
    #define HSE_H
    #define HSE_SPT_HW_SHA3                          /**< @brief HSE supports SHA3 accelerated in HW. */
    #define HSE_NUM_OF_MU_INSTANCES       (8U)       /**< @brief The maxim number of MU interfaces */
    #define HSE_NUM_OF_OTFAD_INSTANCES    (2U)       /**< @brief The supported number of OTFAD Instances */
    #define HSE_SPT_MSC_KEYSTORE                     /**< @brief Support "Managed Security Component" (MSC) keystore (e.g. ACE key store)*/
    #define HSE_SPT_TRIM_PASSWORD_PROVISION          /**< @brief Support trim password provision */

    #define HSE_SPT_IEE_DDR_FLASH                    /**< @brief Support In Line Decryption of LPDDR4 Flash */

    #ifdef HSE_SPT_IEE_DDR_FLASH
    #define HSE_NUM_OF_IEE_DDR_ENTRIES    (7U)       /**< @brief The supported number of IEE_DDR entries/contexts */
    #endif /* HSE_SPT_IEE_DDR_FLASH */
    #define HSE_SPT_TEMP_SENS_VIO_CONFIG             /**< @brief HSE supports the temperature sensor configuration. */
    #define HSE_SPT_CMU                              /**< @brief Support for CMU tamper (clock integrity verification) */

#elif (HSE_PLATFORM == HSE_S32Z1XX)
    #define HSE_H
    #define HSE_SPT_HW_SHA3                          /**< @brief HSE supports SHA3 accelerated in HW. */
    #define HSE_NUM_OF_MU_INSTANCES       (8U)       /**< @brief The maxim number of MU interfaces */
    #define HSE_NUM_OF_OTFAD_INSTANCES    (2U)       /**< @brief The supported number of OTFAD Instances */
    #define HSE_SPT_MSC_KEYSTORE                     /**< @brief Support "Managed Security Component" (MSC) keystore (e.g. ACE key store)*/
    #define HSE_SPT_TRIM_PASSWORD_PROVISION          /**< @brief Support trim password provision */
    #define HSE_SPT_TEMP_SENS_VIO_CONFIG             /**< @brief HSE supports the temperature sensor configuration. */
    #define HSE_SPT_CMU                              /**< @brief Support for CMU tamper (clock integrity verification) */

#elif (HSE_PLATFORM == HSE_S32R41X)
    #define HSE_M
    #define HSE_SPT_HW_SHA3                     /**< @brief HSE supports SHA3 accelerated in HW. */
    #define HSE_NUM_OF_OTFAD_INSTANCES    (1U)  /**< @brief The supported number of OTFAD Instances */
    #define HSE_SPT_TMU_REG_CONFIG              /**< @brief Support TMU registers configuration  */
    #define HSE_SPT_CMU                         /**< @brief Support for CMU tamper (clock integrity verification) */
    #define HSE_SPT_TMU_CMU                     /**< @brief Support CMU tamper for external TMU on CMU1 (clock integrity verification) */
#elif (HSE_PLATFORM == HSE_SAF85XX)
    #define HSE_M
    #define HSE_NUM_OF_OTFAD_INSTANCES    (1U)              /**< @brief The supported number of OTFAD Instances */
    #define HSE_SPT_HW_SHA3                                 /**< @brief HSE supports SHA3 accelerated in HW. */
    #define HSE_SPT_NXP_RFE_SW                              /**< @brief HSE supports proprietary SW loading to RFE. */
    /**< \defdisable{#define, HSE_SPT_TMU_REG_CONFIG} */    /**< @brief Support TMU registers configuration. */
    /**< \defdisable{#define, HSE_SPT_CMU} */               /**< @brief Support CMU tamper for HSE on CMU0 (clock integrity verification) */
    /**< \defdisable{#define, HSE_TMU_SPT_CMU} */           /**< @brief Support CMU tamper for external TMU on CMU1 (clock integrity verification) */
#elif ((HSE_PLATFORM == HSE_S32K3X1)||(HSE_PLATFORM == HSE_S32K3X2)||(HSE_PLATFORM == HSE_S32K3X4)||(HSE_PLATFORM == HSE_S32K3X6)||(HSE_PLATFORM == HSE_S32K358)||(HSE_PLATFORM == HSE_S32K388))
    #define HSE_B
    #define HSE_SPT_CMU                         /**< @brief Support CMU tamper for HSE on CMU0 (clock integrity verification) */
#else
    #error "No platform is selected. At least one platform should be selected."
#endif


#if defined(HSE_H)
    #error "hse_h_config.h not exist"
#elif defined(HSE_M)
    #error "hse_m_config.h not exist"
#elif defined(HSE_B)
/*==================================================================================================
*                                      DEFINES AND MACROS
==================================================================================================*/

    /**< \defdisable{#define,HSE_SPT_FLASHLESS_DEV}*/   /**< @brief  The service is flashless (external flash). */
    #define HSE_SPT_INTERNAL_FLASH_DEV                  /**< @brief  Device has internal flash. */
    /*-------------------------------------------------------*/
    #define HSE_SPT_RANDOM          /**< @brief Support for Random Number Generation. */
    /*-------------------------------------------------------*/
    #define HSE_SPT_SHE             /**< @brief Support for SHE specification.
                                                @note AES and CMAC features must be enabled. */
    /*-------------------------------------------------------*/
    #define HSE_SPT_AES             /**< @brief Support for AES_(128, 192, 256)_(ECB, CBC, CFB, OFB, CTR). AES-CBC is supported on all platforms by default. */

    #ifdef HSE_SPT_AES
    #define HSE_SPT_CIPHER_BLOCK_MODE_CFB       /**< @brief  AES-CFB cipher mode supported */
    #define HSE_SPT_CIPHER_BLOCK_MODE_CTR       /**< @brief  AES-CTR cipher mode supported */
    #define HSE_SPT_CIPHER_BLOCK_MODE_ECB       /**< @brief  AES-ECB cipher mode supported */
    #define HSE_SPT_CIPHER_BLOCK_MODE_OFB       /**< @brief  AES-OFB cipher mode supported */
    #endif /*HSE_SPT_AES*/

    /**< \defdisable{#define,HSE_SPT_XTS_AES}*/   /**< @brief Support for XTS AES  */
    #define HSE_SPT_AEAD_GCM                      /**< @brief Support for AEAD AES GCM as defined  in FIPS PUB 197, NIST SP 800-38D, RFC-5288 and RFC-4106. */
    #define HSE_SPT_AEAD_CCM                      /**< @brief Support for AEAD AES CCM as defined  in FIPS PUB 197, NIST SP 800-38C, RFC-6655 and RFC-4309. */
    /**< \defdisable{#define,HSE_SPT_AUTHENC}*/   /**< @brief Support for Dual Purpose Crypto Service (Authenticated encryption) */
    /**< \defdisable{#define,HSE_SPT_CRC32}*/     /**< @brief Support CRC computation */

    /*-------------------------------------------------------*/
    #define HSE_SPT_HASH                      /**< @brief Hash support */
#ifdef HSE_SPT_HASH
    #define HSE_SPT_SHA1                      /**< @brief Support for SHA-1 as defined  in FIPS PUB 180-4. */
    #define HSE_SPT_SHA2_224                  /**< @brief Support for SHA2_224 in FIPS PUB 180-4. */
    #define HSE_SPT_SHA2_256                  /**< @brief Support for SHA2_256 in FIPS PUB 180-4. */
    #define HSE_SPT_SHA2_384                  /**< @brief Support for SHA2_384 in FIPS PUB 180-4. Scatter gather feature is not supported. */
    #define HSE_SPT_SHA2_512                  /**< @brief Support for SHA2_512 in FIPS PUB 180-4. Scatter gather feature is not supported. */
    #define HSE_SPT_SHA2_512_224              /**< @brief Support for SHA2_512_224 in FIPS PUB 180-4. Scatter gather feature is not supported. */
    #define HSE_SPT_SHA2_512_256              /**< @brief Support for SHA2_512_256 in FIPS PUB 180-4. Scatter gather feature is not supported. */
    #define HSE_SPT_SHA3                     /**< @brief Support for SHA3_(224, 256, 384, 512) as defined  in FIPS PUB 202. */
    #define HSE_SPT_MIYAGUCHI_PRENEEL         /**< @brief Miyaguchi-Preneel compression function (SHE spec support)*/
#endif /* ifdef HSE_SPT_HASH */

    /*-------------------------------------------------------*/
    #define HSE_SPT_MAC                       /**< @brief MAC support */
#ifdef HSE_SPT_MAC
    #define HSE_SPT_FAST_CMAC                     /**< @brief Support for AES fast CMAC (optimized) */
    #define HSE_SPT_CMAC                          /**< @brief Support for AES CMAC as defined  in NIST SP 800-38B. */
    #define HSE_SPT_HMAC                          /**< @brief Support for HMAC_SHA1 and HMAC_SHA2_(224, 256, 384, 512) as defined in FIPS PUB 198-1 and SP 800-107. */
    #define HSE_SPT_GMAC                          /**< @brief Support for AES GMAC as defined  in NIST SP 800-38D. */
    /**< \defdisable{#define,HSE_SPT_XCBC_MAC}*/  /**< @brief Support for AES XCBC_MAC_96 as defined  in RFC-3566. */
#endif /* ifdef HSE_SPT_MAC */

    /*-------------------------------------------------------*/
    /**< \defdisable{#define,HSE_SPT_SIPHASH}*/   /**< @brief Support for SipHash */

    /*-------------------------------------------------------*/
    #define HSE_SPT_RSA                 /**< @brief RSA support */
#ifdef HSE_SPT_RSA
    #define HSE_SPT_RSAES_NO_PADDING    /**< @brief  RSA modular exponentiation operations( RSAEP and RSADP). */
    #define HSE_SPT_RSAES_OAEP          /**< @brief Support for RSAES_OAEP as defined by RFC-8017. */
    #define HSE_SPT_RSAES_PKCS1_V15     /**< @brief Support for RSAES_PKCS1_V15 as defined  by PKCS#1 v2.2. */
    #define HSE_SPT_RSASSA_PSS          /**< @brief Support for RSASSA_PSS as defined  by FIPS 186-4. */
    #define HSE_SPT_RSASSA_PKCS1_V15    /**< @brief Support RSASSA_PKCS1_V15 as defined by PKCS#1 v2.2. */
#endif /* ifdef HSE_SPT_RSA */

    /*-------------------------------------------------------*/
    #define HSE_SPT_ECC                                   /**< @brief Support for ECC */
    /**< \defdisable{#define HSE_SPT_CLASSIC_DH}*/                            /**< @brief Support for generate key pair, DH share secret computation as defined in FIPS 186-4 */
#ifdef HSE_SPT_ECC
    #define HSE_SPT_ECDH                                  /**< @brief ECDH support */
    #define HSE_SPT_ECDSA                                 /**< @brief ECDSA support */
    #define HSE_SPT_EDDSA                                 /**< @brief Twisted Edwards EDDSA (e.g. ED25519) support */
    #define HSE_SPT_MONTDH                                /**< @brief Montgomery DH (e.g X25519 curve) support */
    #define HSE_SPT_ECC_USER_CURVES                       /**< @brief Support to set ECC curve (not supported by default)*/
    #define HSE_SPT_EC_SEC_SECP256R1                      /**< @brief Support Ecc p256v1 */
    #define HSE_SPT_EC_SEC_SECP384R1                      /**< @brief Support Ecc SECP p384r1 */
    #define HSE_SPT_EC_SEC_SECP521R1                      /**< @brief Support Ecc SECP p521r1 */
    #define HSE_SPT_EC_BRAINPOOL_BRAINPOOLP256R1          /**< @brief Support Ecc BrainPool p256r1 */
    #define HSE_SPT_EC_BRAINPOOL_BRAINPOOLP320R1          /**< @brief Support Ecc BrainPool p320r1 */
    #define HSE_SPT_EC_BRAINPOOL_BRAINPOOLP384R1          /**< @brief Support Ecc BrainPool p384r1 */
    #define HSE_SPT_EC_BRAINPOOL_BRAINPOOLP512R1          /**< @brief Support Ecc BrainPool p521r1 */
    #define HSE_SPT_EC_25519_ED25519                      /**< @brief Twisted Edwards ED25519 curve support (used with EdDSA )*/
    /**< \defdisable{#define,HSE_SPT_EC_448_ED448} */     /**< @brief Twisted Edwards ED448 curve support (used with EdDSA )*/
    #define HSE_SPT_EC_25519_CURVE25519                   /**< @brief Montgomery X25519 curve support (used with MONTDH) */
    /**< \defdisable{#define,HSE_SPT_EC_448_CURVE448}*/   /**< @brief Montgomery X448 curve support (used with MONTDH) */
    /**< \defdisable{#define HSE_SPT_BURMESTER_DESMEDT}*/                     /**< @brief Burmester-Desmedt Protocol support */
#endif /*ifdef HSE_SPT_ECC */

    /*-------------------------------------------------------*/
    #define HSE_SPT_KEY_GEN             /**< @brief Key Generate support */
#ifdef HSE_SPT_KEY_GEN
    #define HSE_SPT_SYM_RND_KEY_GEN     /**< @brief Support for symmetric random key generation. */

    #ifdef HSE_SPT_ECC
    #define HSE_SPT_ECC_KEY_PAIR_GEN    /**< @brief Support for ECC key-pair generation. */
    #endif /* HSE_SPT_ECC */

    #ifdef HSE_SPT_RSA
    #define HSE_SPT_RSA_KEY_PAIR_GEN                                /**< @brief Support for RSA key-pair generation. */
    #define HSE_SPT_TLS12_RSA_PRE_MASTER_SECRET_GEN                 /**< @brief Support for RSA key exchange. */
    #endif /* HSE_SPT_RSA */

    #ifdef HSE_SPT_CLASSIC_DH
    #define HSE_SPT_CLASSIC_DH_KEY_PAIR_GEN                         /**< @brief Support for Classic DH key-pair generation. */
    #endif /* HSE_SPT_CLASSIC_DH */
#endif

    /*-------------------------------------------------------*/
    #define HSE_SPT_KEY_DERIVE              /**< @brief KDF support */
#ifdef HSE_SPT_KEY_DERIVE
    #define HSE_SPT_KDF_NXP_GENERIC         /**< @brief NXP Generic KDF. */
    #define HSE_SPT_KDF_SP800_56C_ONESTEP   /**< @brief Support for KDF One-step as defined  by SP800-56C rev1. HMAC and XCBC_MAC options as PRF algorithm are not supported */
    #define HSE_SPT_KDF_SP800_56C_TWOSTEP   /**< @brief Support for KDF Two-step as defined  by SP800-56C rev1. HMAC and XCBC_MAC options as PRF algorithm are not supported */
    #define HSE_SPT_KDF_SP800_108           /**< @brief Support for KDF(Counter, Feedback, Pipeline) as defined  by SP800-108. Only counter mode is supported. HMAC and XCBC_MAC options as PRF algorithm are not supported */
    #define HSE_SPT_KDF_ANS_X963            /**< @brief Support for KDF as defined  by ANS X9.63. HMAC and XCBC_MAC options as PRF algorithm are not supported */
    #define HSE_SPT_KDF_ISO18033_KDF1       /**< @brief Support for KDF1 as defined by ISO18033. HMAC and XCBC_MAC options as PRF algorithm are not supported */
    #define HSE_SPT_KDF_ISO18033_KDF2       /**< @brief Support for KDF2 as defined by ISO18033. HMAC and XCBC_MAC options as PRF algorithm are not supported */
    #define HSE_SPT_PBKDF2                  /**< @brief Support for PBKDF2 as defined as defined by PKCS#5 v2.1 and RFC-8018. Support of HMAC is provided with Hash algos SHA-1, SHA-224, and SHA-256. */
    #define HSE_SPT_KDF_TLS12_PRF           /**< @brief KDF Support for TLS 1.2 as defined by RFC-5246. Support of HMAC is provided with Hash algos SHA-1, SHA-224, and SHA-256. */
    #define HSE_SPT_HKDF                    /**< @brief Support for HMAC-based Extract-and-Expand KDF as defined by RFC-5869. Support of HMAC is provided with Hash algos SHA-1, SHA-224, and SHA-256. */
    /**< \defdisable{#define,HSE_SPT_KDF_IKEV2}*/              /**< @brief KDF Support for IKEv2 as defined  by RFC-4306. */
#endif /* ifdef HSE_SPT_KEY_DERIVE */

    /*-------------------------------------------------------*/
    #define HSE_SPT_NXP_ROM_KEYS                /**< @brief Support NXP ROM keys. */
#ifdef HSE_SPT_NXP_ROM_KEYS
    #define HSE_SPT_NXP_ROM_RSA_PUB_KEYS        /**< @brief Support NXP RSA ROM public keys. */
    #define HSE_SPT_NXP_ROM_ECC_PUB_KEYS        /**< @brief Support NXP ECC ROM public keys. */
#endif

    #define HSE_SPT_FORMAT_KEY_CATALOGS     /**< @brief Support Format Key Catalogs service */
    /**< \defdisable{#define HSE_SPT_EXTEND_KEY_CATALOG}*/      /**< @brief Support Format Key Catalogs Extend service */
    #define HSE_SPT_GET_KEY_INFO            /**< @brief Support Get Key Info Service. */
    #define HSE_SPT_KEY_VERIFY              /**< @brief Support Key Verify Service. */
    #define HSE_SPT_IMPORT_KEY              /**< @brief Support Import Key Service. */
    #define HSE_SPT_EXPORT_KEY              /**< @brief Support Export Key Service. */
    #define HSE_SPT_KEY_MGMT_POLICIES       /**< @brief Support Key Management configurable policies. */

    /*-------------------------------------------------------*/
    #define HSE_SPT_PUBLISH_NVM_KEYSTORE_RAM_TO_FLASH                /**< @brief Support Publishing the keystore from RAM to data flash */

    /*-------------------------------------------------------*/
    #define HSE_SPT_MONOTONIC_COUNTERS            /**< @brief Monotonic Counter support */
#ifdef HSE_SPT_MONOTONIC_COUNTERS
    #define HSE_NUM_OF_MONOTONIC_COUNTERS            (16U) /**< @brief   The supported number of monotonic counters */
    #define HSE_NVM_SPT_MONOTONIC_CNT_NO_OF_SECTORS  (1U)  /**< @brief The supported number of passive sectors used by monotonic counters */
#endif
    #define HSE_SPT_NXP_KEY_STORE_NO_OF_SECTORS      (1U)    /**< @brief The supported number of active sectors used by NXP key store */
    #define HSE_SECTOR_SIZE                          (8192U) /**< @brief The size of Flash Sector in S32K3xx Devices */
    /*-------------------------------------------------------*/
    #define HSE_SPT_BOOTDATASIGN                   /**< @brief Boot Data Sign Support  */
#ifdef HSE_SPT_BOOTDATASIGN
    #define HSE_SPT_BSB                            /**< @brief Basic Secure Booting(ASB) Support  */
#endif

    /*-------------------------------------------------------*/
    #ifdef HSE_SPT_MONOTONIC_COUNTERS
    /**< \defdisable{#define HSE_SPT_CMAC_WITH_COUNTER}*/            /**< @brief Support for CMAC with counter */
    #endif /* HSE_SPT_MONOTONIC_COUNTERS */

    /*-------------------------------------------------------*/

    #define HSE_SPT_SMR_CR                           /**< @brief Advance Secure Booting(ASB) Secure memory regions verification (SMR) & Core Reset(CR) Table Support */
#ifdef HSE_SPT_SMR_CR
    #define HSE_NUM_OF_SMR_ENTRIES          (8U)                  /**< @brief   The supported number of SMR entries*/
    #if (HSE_PLATFORM == HSE_S32K388)
    #define HSE_NUM_OF_CORE_RESET_ENTRIES   (4U)                  /**< @brief   The supported number of CORE RESET entries*/
    #else
    #define HSE_NUM_OF_CORE_RESET_ENTRIES   (3U)                  /**< @brief   The supported number of CORE RESET entries*/
    #endif /* (HSE_PLATFORM == HSE_S32K388) */
    #define HSE_SPT_SMR_DECRYPT                                   /**< @brief   Support encrypted SMRs. */
#endif
    /*-------------------------------------------------------*/
    #define HSE_SPT_STREAM_CTX_IMPORT_EXPORT      /**< @brief Support Import/Export of streaming context for symmetric operations */


    #define HSE_SPT_MU_CONFIG                     /**< @brief Support MU configuration */

    #define HSE_SPT_CUST_SEC_POLICY               /**< @brief Support of Customer Security Policy */
    #define HSE_SPT_OEM_SEC_POLICY                /**< @brief Support of Oem Security Policy */

    #define HSE_SPT_PHYSICAL_TAMPER_CONFIG                          /**< @brief Support of active tamper */
    #define HSE_NUM_OF_PHYSICAL_TAMPER_INSTANCES         (1U)       /**< @brief  Number of Physical Tamper Instances */


    /**< \defdisable{#define,HSE_SPT_SELF_TEST}*/  /**< @brief Support self test */

    #define HSE_SPT_MEM_REGION_PROTECT             /**< @brief Support memory region protection */
#ifdef HSE_SPT_MEM_REGION_PROTECT
    #define HSE_MAX_NUM_OF_MEM_REGIONS     (6U)    /**< @brief Maximum number of memory regions configurable through #HSE_SPT_MEM_REGION_PROTECT service */
#endif /* HSE_SPT_MEM_REGION_PROTECT */

    #define HSE_SPT_OTA_FIRMWARE_UPDATE            /**< @brief Support OTA Firmware Update */
    #define HSE_SPT_OTA_SBAF_UPDATE                /**< @brief Support SBAF update */
    #define HSE_SPT_FW_BACKUP_ENABLE               /**< @brief Support BACKUP Feature. */
    #define HSE_SPT_FW_INTEGRITY_CHECK             /**< @brief Support HSE flash memory integrity check. */
    #define HSE_SPT_ERASE_FW                       /**< @brief Erase Active HSE FW, Backup (if present) and SYS-IMG from internal secure flash memory in CUST_DEL lifecycle */

    #define HSE_SPT_SGT_OPTION                     /**< @brief Enable support for Scatter Gatter Table */
#ifdef HSE_SPT_SGT_OPTION
    #define HSE_MAX_NUM_OF_SGT_ENTRIES  (8U)        /**< @brief Maximum number for SGT entries */
#endif
    /**< \defdisable{#define HSE_SPT_APP_SPECIFIC_DATA_ATTR}*/          /**< @brief Enable support for "Application Specific Data" attribute. */
    /*-------------------------------------------------------*/
    #define HSE_NUM_OF_MU_INSTANCES       (2U)      /**< @brief  The maxim number of MU interfaces */
    #define HSE_NUM_OF_CHANNELS_PER_MU    (4U)      /**< @brief  The maxim number of channels per MU interface  */
    #define HSE_STREAM_COUNT              (2U)      /**< @brief  HSE stream count per interface */

#ifdef HSE_SPT_ECC_USER_CURVES
    #define HSE_NUM_OF_USER_ECC_CURVES    (1U)      /**< @brief The number of ECC curves the user can load into the HSE */
#endif

    #define HSE_TOTAL_NUM_OF_KEY_GROUPS   (32U)     /**< @brief  The total number of catalog configuration entries for both NVM and RAM catalogs.*/
    #define HSE_MAX_RAM_STORE_SIZE        (6144U)   /**< @brief  RAM key store size (in bytes) */
    #define HSE_MAX_NVM_STORE_SIZE        (7768U + ((HSE_SPT_NXP_KEY_STORE_NO_OF_SECTORS - 1U) * HSE_SECTOR_SIZE))   /**< @brief  NVM key store size (in bytes) */

    #define HSE_AES_KEY_BITS_LENS         {128U, 192U, 256U}   /**< @brief  AES key bit length (set to zero to disable a AES key size)*/

    #define HSE_MAX_SHARED_SECRET_BITS_LEN (4096U)             /**< @brief  Max shared secret bit length */

#ifdef HSE_SPT_HMAC
    #define HSE_MIN_HMAC_KEY_BITS_LEN     (128U)               /**< @brief  Min HMAC key bit length  */
    #define HSE_MAX_HMAC_KEY_BITS_LEN     (1024U)              /**< @brief  Max HMAC key bit length  */
#endif

#ifdef HSE_SPT_ECC
    #define HSE_MIN_ECC_KEY_BITS_LEN      (192U)               /**< @brief  Min ECC key bit length  */
    #define HSE_MAX_ECC_KEY_BITS_LEN      (521U)               /**< @brief  Max ECC key bit length */
#endif

#ifdef HSE_SPT_RSA
    #define HSE_MIN_RSA_KEY_BITS_LEN      (1024U)              /**< @brief  Min RSA key bit length */
    #define HSE_MAX_RSA_KEY_BITS_LEN      (4096U)              /**< @brief  Max RSA key bit length  */
    #define HSE_MAX_RSA_PUB_EXP_SIZE      (8U)                 /**< @brief  Max RSA public exponent size (in bytes) */
#endif

#ifdef HSE_SPT_CLASSIC_DH
    #define HSE_MIN_CLASSIC_DH_BITS_LEN    (1024U)              /**< @brief  Min Classic DH key bit length  */
    #define HSE_MAX_CLASSIC_DH_BITS_LEN    (4096U)              /**< @brief  Max Classic DH key bit length*/
#endif

#ifdef HSE_SPT_FAST_CMAC
    #define HSE_DEFAULT_MIN_FAST_CMAC_TAG_BITLEN   (64U)         /**< @brief  FAST CMAC default min bit length*/
#endif

#ifdef HSE_SPT_SIPHASH
    #define HSE_SIPHASH_KEY_BIT_LENS          (128U)             /**< @brief  SipHash key bit length*/
#endif

#if defined(HSE_SPT_ECDSA) || defined(HSE_SPT_EDDSA) || defined(HSE_SPT_RSASSA_PSS) || defined(HSE_SPT_RSASSA_PKCS1_V15)
    #define HSE_SPT_SIGN
#endif

#if defined(HSE_SPT_AEAD_GCM) || defined(HSE_SPT_AEAD_CCM)
    #define HSE_SPT_AEAD
#endif

#if defined(HSE_SPT_ECDH) || defined(HSE_SPT_CLASSIC_DH) || defined(HSE_SPT_MONTDH)
    #define HSE_SPT_COMPUTE_DH
#endif

#if (defined(HSE_SPT_SHA2_224) || defined(HSE_SPT_SHA2_256) || defined(HSE_SPT_SHA2_384) || \
     defined(HSE_SPT_SHA2_512) || defined(HSE_SPT_SHA2_512_224) || defined(HSE_SPT_SHA2_512_256))
    #define HSE_SPT_SHA2
#endif
/**< @} */

#else
    #error "No HSE HW variant is selected. At least one HSE HW variant should be selected."
#endif

/** @} */

/*==================================================================================================
*                                      DEFINES AND MACROS
==================================================================================================*/
/** @brief HSE Service versions */
#define HSE_SRV_VER_0                     (0x00000000UL)
#define HSE_SRV_VER_1                     (0x01000000UL)

/** @brief Define min. */
#if !defined(MIN)
#define MIN(a, b)                         (((a) < (b))?(a):(b))
#endif

/** @brief Define max. */
#if !defined(MAX)
#define MAX(a, b)                         (((a) > (b))?(a):(b))
#endif

/** @brief Compute the number of elements of an array */
#ifndef  NUM_OF_ELEMS
#define  NUM_OF_ELEMS(x) (sizeof(x)/sizeof((x)[0]))
#endif

/** @brief Compute the size of a string initialized with quotation marks */
#ifndef SIZE_OF_STRING
#define SIZE_OF_STRING(string)            (sizeof(string) - 1U)
#endif

/** @brief Translate bits to bytes */
#ifndef HSE_BITS_TO_BYTES
#define HSE_BITS_TO_BYTES(bitLen)         ((((bitLen) + 7UL) >> 3UL))
#endif

/** @brief Translate bits to bytes (uint16_t) */
#ifndef HSE_BITS_TO_BYTES_UINT16
#define HSE_BITS_TO_BYTES_UINT16(bitLen)  ((uint16_t)HSE_BITS_TO_BYTES(bitLen))
#endif

/** @brief Translate bytes to bits */
#ifndef HSE_BYTES_TO_BITS
#define HSE_BYTES_TO_BITS(byteLen)        ((byteLen) << 3UL)
#endif

/** @brief Host address size */
#ifndef HSE_SPT_64BIT_ADDR
    #define HOST_ADDR                     uint32_t
#else
    #define HOST_ADDR                     uint64_t
#endif

/** @brief NULL host address */
#ifndef NULL_HOST_ADDR
#define NULL_HOST_ADDR                    ((HOST_ADDR)0UL)
#endif

/** @brief Pointer to Host address  */
#ifndef HSE_PTR_TO_HOST_ADDR
    #define HSE_PTR_TO_HOST_ADDR(ptr)     ((HOST_ADDR)(uintptr_t)(ptr))
#endif

typedef uint8_t hseDigestLen_t;
#define HSE_SHA1_DIGEST_LEN               ((hseDigestLen_t)20U)  /**<  @brief SHA1 digest length in bytes */
#define HSE_SHA224_DIGEST_LEN             ((hseDigestLen_t)28U)  /**<  @brief SHA224 digest length in bytes*/
#define HSE_SHA256_DIGEST_LEN             ((hseDigestLen_t)32U)  /**<  @brief SHA256 digest length in bytes*/
#define HSE_SHA384_DIGEST_LEN             ((hseDigestLen_t)48U)  /**<  @brief SHA384 digest length in bytes*/
#define HSE_SHA512_DIGEST_LEN             ((hseDigestLen_t)64U)  /**<  @brief SHA512 digest length in bytes*/
#define HSE_MAX_DIGEST_LEN                ((hseDigestLen_t)64U)  /**<  @brief Max digest buffer in bytes */

typedef uint8_t hseBlockLen_t;

#define HSE_AES_BLOCK_LEN                 ((hseBlockLen_t)16U)   /**<  @brief AES block length in bytes  */

/** @brief  The capabilities indices for each enabled algorithm */
typedef uint8_t hseAlgoCapIdx_t;
#define HSE_CAP_IDX_RANDOM                ((hseAlgoCapIdx_t)0U)
#define HSE_CAP_IDX_SHE                   ((hseAlgoCapIdx_t)1U)
#define HSE_CAP_IDX_AES                   ((hseAlgoCapIdx_t)2U)
#define HSE_CAP_IDX_XTS_AES               ((hseAlgoCapIdx_t)3U)
#define HSE_CAP_IDX_AEAD_GCM              ((hseAlgoCapIdx_t)4U)
#define HSE_CAP_IDX_AEAD_CCM              ((hseAlgoCapIdx_t)5U)
#define HSE_CAP_IDX_RESERVED1             ((hseAlgoCapIdx_t)6U)        /* Reserved (MD5 obsolete)*/
#define HSE_CAP_IDX_SHA1                  ((hseAlgoCapIdx_t)7U)
#define HSE_CAP_IDX_SHA2                  ((hseAlgoCapIdx_t)8U)
#define HSE_CAP_IDX_SHA3                  ((hseAlgoCapIdx_t)9U)
#define HSE_CAP_IDX_MP                    ((hseAlgoCapIdx_t)10U)
#define HSE_CAP_IDX_CMAC                  ((hseAlgoCapIdx_t)11U)
#define HSE_CAP_IDX_HMAC                  ((hseAlgoCapIdx_t)12U)
#define HSE_CAP_IDX_GMAC                  ((hseAlgoCapIdx_t)13U)
#define HSE_CAP_IDX_XCBC_MAC              ((hseAlgoCapIdx_t)14U)
#define HSE_CAP_IDX_RSAES_NO_PADDING      ((hseAlgoCapIdx_t)15U)
#define HSE_CAP_IDX_RSAES_OAEP            ((hseAlgoCapIdx_t)16U)
#define HSE_CAP_IDX_RSAES_PKCS1_V15       ((hseAlgoCapIdx_t)17U)
#define HSE_CAP_IDX_RSASSA_PSS            ((hseAlgoCapIdx_t)18U)
#define HSE_CAP_IDX_RSASSA_PKCS1_V15      ((hseAlgoCapIdx_t)19U)
#define HSE_CAP_IDX_ECDH                  ((hseAlgoCapIdx_t)20U)
#define HSE_CAP_IDX_ECDSA                 ((hseAlgoCapIdx_t)21U)
#define HSE_CAP_IDX_EDDSA                 ((hseAlgoCapIdx_t)22U)
#define HSE_CAP_IDX_MONTDH                ((hseAlgoCapIdx_t)23U)
#define HSE_CAP_IDX_CLASSIC_DH            ((hseAlgoCapIdx_t)24U)
#define HSE_CAP_IDX_KDF_SP800_56C         ((hseAlgoCapIdx_t)25U)
#define HSE_CAP_IDX_KDF_SP800_108         ((hseAlgoCapIdx_t)26U)
#define HSE_CAP_IDX_KDF_ANS_X963          ((hseAlgoCapIdx_t)27U)
#define HSE_CAP_IDX_KDF_ISO18033_KDF1     ((hseAlgoCapIdx_t)28U)
#define HSE_CAP_IDX_KDF_ISO18033_KDF2     ((hseAlgoCapIdx_t)29U)
#define HSE_CAP_IDX_PBKDF2                ((hseAlgoCapIdx_t)30U)
#define HSE_CAP_IDX_KDF_TLS12_PRF         ((hseAlgoCapIdx_t)31U)
#define HSE_CAP_IDX_HKDF                  ((hseAlgoCapIdx_t)32U)
#define HSE_CAP_IDX_KDF_IKEV2             ((hseAlgoCapIdx_t)33U)

#if (   defined ( __ghs__ ) ||  /* GHS compiler */  \
        defined ( __CC_ARM ) || /* Arm Compiler 4/5  */  \
        defined (__ARMCC_VERSION)||/* Arm Compiler 6 (armclang) */\
        defined ( __GNUC__ ) || /* GNU Compiler*/  \
        defined ( __ICCARM__ ) /* IAR Compiler*/ )
    #pragma pack(push, 4)
    #undef PRAGMA_PACK_ERROR
#elif defined( __DCC__ ) /* DIAB compiler */
    #pragma pack(4,4,0)
    #undef PRAGMA_PACK_ERROR
#else
    #error "Unknown compiler. Define pragma pack for the compiler."
#endif

/** @brief Absolute maximum HSE service descriptor size.
 *         This is determined by the HSE-HOST shared memory size, the number of MUs and the number of channels per MU.*/
#define HSE_MAX_DESCR_SIZE                  (256U)

/*==================================================================================================
*                                      DEFINES AND MACROS
==================================================================================================*/
/** @brief    HSE Message Unite (MU) masks */
typedef uint8_t hseMuMask_t;
#define HSE_MU0_MASK                 ((hseMuMask_t)1U << 0U) /**< @brief MU Instance 0 */
#define HSE_MU1_MASK                 ((hseMuMask_t)1U << 1U) /**< @brief MU Instance 1 */
#if HSE_NUM_OF_MU_INSTANCES > 2
#define HSE_MU2_MASK                 ((hseMuMask_t)1U << 2U) /**< @brief MU Instance 2 */
#define HSE_MU3_MASK                 ((hseMuMask_t)1U << 3U) /**< @brief MU Instance 3 */
#if HSE_NUM_OF_MU_INSTANCES > 4
#define HSE_MU4_MASK                 ((hseMuMask_t)1U << 4U) /**< @brief MU Instance 2 */
#define HSE_MU5_MASK                 ((hseMuMask_t)1U << 5U) /**< @brief MU Instance 3 */
#define HSE_MU6_MASK                 ((hseMuMask_t)1U << 6U) /**< @brief MU Instance 2 */
#define HSE_MU7_MASK                 ((hseMuMask_t)1U << 7U) /**< @brief MU Instance 3 */
#endif
#endif


/** @brief    Mask for all MU Instances */
#if HSE_NUM_OF_MU_INSTANCES == 2
#define HSE_ALL_MU_MASK              (HSE_MU0_MASK | HSE_MU1_MASK)
#elif HSE_NUM_OF_MU_INSTANCES == 4
#define HSE_ALL_MU_MASK              (HSE_MU0_MASK | HSE_MU1_MASK | HSE_MU2_MASK | HSE_MU3_MASK)
#else
#define HSE_ALL_MU_MASK              (HSE_MU0_MASK | HSE_MU1_MASK | HSE_MU2_MASK | HSE_MU3_MASK | \
                                      HSE_MU4_MASK | HSE_MU5_MASK | HSE_MU6_MASK | HSE_MU7_MASK )
#endif

/** @brief   HSE Scatter-Gather Option .
 *  @details Specifies if the input or output data is provided a scatter list (see hseScatterList_t).
 *           @note The remaining bit are ignored when SGT option is used.*/
typedef uint8_t hseSGTOption_t;
#define HSE_SGT_OPTION_NONE      ((hseSGTOption_t)0U)       /**< @brief Scatter list is not used.*/
#define HSE_SGT_OPTION_INPUT     ((hseSGTOption_t)1U << 0U) /**< @brief Input pointer is provided a scatter list.*/
#define HSE_SGT_OPTION_OUTPUT    ((hseSGTOption_t)1U << 1U) /**< @brief Output pointer is provided a scatter list.*/
/** @brief    Mask for input/output scatter-gatther option */
#define HSE_SGT_OPTION_INPUT_OUTPUT_MASK (HSE_SGT_OPTION_INPUT | HSE_SGT_OPTION_OUTPUT)

/** @brief   Scatter-gather Final chunk BIT.
 *           This bit is set in the "length" field of the chunk (see hseScatterList_t).*/
#define HSE_SGT_FINAL_CHUNK_BIT_MASK (0x40000000UL)

/** @brief    HSE access modes.*/
typedef uint8_t hseAccessMode_t;
#define HSE_ACCESS_MODE_ONE_PASS     ((hseAccessMode_t)0U)      /**< @brief ONE-PASS access mode */
#define HSE_ACCESS_MODE_START        ((hseAccessMode_t)1U)      /**< @brief START access mode  */
#define HSE_ACCESS_MODE_UPDATE       ((hseAccessMode_t)2U)      /**< @brief UPDATE access mode  */
#define HSE_ACCESS_MODE_FINISH       ((hseAccessMode_t)3U)      /**< @brief FINISH access mode  */

/** @brief   HASH algorithm types.*/
typedef uint8_t hseHashAlgo_t;
#define HSE_HASH_ALGO_NULL           ((hseHashAlgo_t)0U)         /**< @brief None */
#define HSE_HASH_RESERVED1           ((hseHashAlgo_t)1U)         /**< @brief Reserved (MD5 obsolete) */
#define HSE_HASH_ALGO_SHA_1          ((hseHashAlgo_t)2U)         /**< @brief SHA1 hash */
#define HSE_HASH_ALGO_SHA2_224       ((hseHashAlgo_t)3U)         /**< @brief SHA2_224 hash */
#define HSE_HASH_ALGO_SHA2_256       ((hseHashAlgo_t)4U)         /**< @brief SHA2_256 hash */
#define HSE_HASH_ALGO_SHA2_384       ((hseHashAlgo_t)5U)         /**< @brief SHA2_384 hash */
#define HSE_HASH_ALGO_SHA2_512       ((hseHashAlgo_t)6U)         /**< @brief SHA2_512 hash */
#define HSE_HASH_ALGO_SHA2_512_224   ((hseHashAlgo_t)7U)         /**< @brief SHA2_512_224 hash */
#define HSE_HASH_ALGO_SHA2_512_256   ((hseHashAlgo_t)8U)         /**< @brief SHA2_512_256 hash */
#define HSE_HASH_ALGO_SHA3_224       ((hseHashAlgo_t)9U)         /**< @brief SHA3_224 hash */
#define HSE_HASH_ALGO_SHA3_256       ((hseHashAlgo_t)10U)        /**< @brief SHA3_256 hash */
#define HSE_HASH_ALGO_SHA3_384       ((hseHashAlgo_t)11U)        /**< @brief SHA3_384 hash */
#define HSE_HASH_ALGO_SHA3_512       ((hseHashAlgo_t)12U)        /**< @brief SHA3_512 hash */
#define HSE_HASH_ALGO_MP             ((hseHashAlgo_t)13U)        /**< @brief Miyaguchi-Preneel compression using AES-ECB with 128-bit key size (SHE spec support). */


/** @brief    Symmetric Cipher Algorithms .*/
typedef uint8_t hseCipherAlgo_t;
#define HSE_CIPHER_ALGO_NULL         ((hseCipherAlgo_t)0x00U)     /**< @brief NULL cipher */
#define HSE_CIPHER_ALGO_AES          ((hseCipherAlgo_t)0x10U)     /**< @brief AES cipher */


/** @brief    Symmetric Cipher Block Modes */
typedef uint8_t hseCipherBlockMode_t;
#define HSE_CIPHER_BLOCK_MODE_NULL   ((hseCipherBlockMode_t)0U)   /**< @brief NULL cipher */
#define HSE_CIPHER_BLOCK_MODE_CTR    ((hseCipherBlockMode_t)1U)   /**< @brief CTR mode (AES) */
#define HSE_CIPHER_BLOCK_MODE_CBC    ((hseCipherBlockMode_t)2U)   /**< @brief CBC mode (AES) */
#define HSE_CIPHER_BLOCK_MODE_ECB    ((hseCipherBlockMode_t)3U)   /**< @brief ECB mode (AES) */
#define HSE_CIPHER_BLOCK_MODE_CFB    ((hseCipherBlockMode_t)4U)   /**< @brief CFB mode (AES) */
#define HSE_CIPHER_BLOCK_MODE_OFB    ((hseCipherBlockMode_t)5U)   /**< @brief OFB mode (AES) */


/** @brief   HSE cipher direction: encryption/decryption */
typedef uint8_t hseCipherDir_t;
#define HSE_CIPHER_DIR_DECRYPT       ((hseCipherDir_t)0U)         /**< @brief Decrypt */
#define HSE_CIPHER_DIR_ENCRYPT       ((hseCipherDir_t)1U)         /**< @brief Encrypt */


/** @brief   HSE Authenticated cipher/encryption mode (only AES supported). */
typedef uint8_t hseAuthCipherMode_t;
#define HSE_AUTH_CIPHER_MODE_CCM     ((hseAuthCipherMode_t)0x11U)  /**< @brief CCM mode */
#define HSE_AUTH_CIPHER_MODE_GCM     ((hseAuthCipherMode_t)0x12U)  /**< @brief GCM mode */


/** @brief   HSE authentication direction: generate/verify.*/
typedef uint8_t hseAuthDir_t;
#define HSE_AUTH_DIR_VERIFY          ((hseAuthDir_t)0U)            /**< @brief Verify authentication tag */
#define HSE_AUTH_DIR_GENERATE        ((hseAuthDir_t)1U)            /**< @brief Generate authentication tag */


/** @brief   HSE MAC algorithm.*/
typedef uint8_t hseMacAlgo_t;
#define HSE_MAC_ALGO_CMAC            ((hseMacAlgo_t)0x11U)         /**< @brief CMAC (AES)*/
#define HSE_MAC_ALGO_GMAC            ((hseMacAlgo_t)0x12U)         /**< @brief GMAC (AES)*/
#define HSE_MAC_ALGO_XCBC_MAC        ((hseMacAlgo_t)0x13U)         /**< @brief XCBC MAC (AES128) */
#define HSE_MAC_ALGO_HMAC            ((hseMacAlgo_t)0x20U)         /**< @brief HMAC */

/** @brief   Signature scheme enumeration.*/
typedef uint8_t hseSignSchemeEnum_t;
#define HSE_SIGN_ECDSA                ((hseSignSchemeEnum_t)0x80U) /**< @brief ECDSA signature scheme */
#define HSE_SIGN_EDDSA                ((hseSignSchemeEnum_t)0x81U) /**< @brief EdDSA signature scheme */
#define HSE_SIGN_RSASSA_PKCS1_V15     ((hseSignSchemeEnum_t)0x93U) /**< @brief RSASSA_PKCS1_V15 signature scheme */
#define HSE_SIGN_RSASSA_PSS           ((hseSignSchemeEnum_t)0x94U) /**< @brief RSASSA_PSS signature scheme */


/** @brief   RSA algorithm types.*/
typedef uint8_t hseRsaAlgo_t;
#define HSE_RSA_ALGO_NO_PADDING        ((hseRsaAlgo_t)0x90U)        /**< @brief The input will be treated as an unsigned integer and perform a modular exponentiation of the input  */
#define HSE_RSA_ALGO_RSAES_OAEP        ((hseRsaAlgo_t)0x91U)        /**< @brief RSAES OAEP cipher */
#define HSE_RSA_ALGO_RSAES_PKCS1_V15   ((hseRsaAlgo_t)0x92U)        /**< @brief ECDSA RSAES_PKCS1_V15 cipher */

#ifdef HSE_SPT_FLASHLESS_DEV /* HSE_H/M device */
/** @brief   The application core IDs (that can be started).
             Only the IDs for the table below must be provided for a specific platform; otherwise an error will be reported.

    Core assignment table:

    | CoreID | S32G2XX | S32R45| S32R41      | SAF85XX     |S32G3XX  | S32ZE             |
    |-------:|:-------:|:-----:|:-----------:|:-----------:|:-------:|:-----------------:|
    |   0    | M7_0    | M7_0  | M7_0        | M7_0        | M7_0    | M33 (SMU)         |
    |   1    | M7_1    | M7_1  | M7_1        | M7_1(RFE)   | M7_1    | LLCE_0(CE M33_0)* |
    |   2    | M7_2    | M7_2  | A53_0       | A53_0       | M7_2    | LLCE_1(CE M33_1)* |
    |   3    | A53_0   | A53_0 | BBE32EP DSP | BBE32EP DSP | M7_3    | CEVA_SPF2*        |
    |   4    | A53_1   | A53_1 |             |             | A53_0   | R52_0             |
    |   5    | A53_2   | A53_2 |             |             | A53_1   | R52_1             |
    |   6    | A53_3   | A53_3 |             |             | A53_2   | R52_2             |
    |   7    | LLCE_0* |       |             |             | A53_3   | R52_3             |
    |   8    | LLCE_1* |       |             |             | A53_4   | R52_4             |
    |   9    | LLCE_2* |       |             |             | A53_5   | R52_5             |
    |  10    | LLCE_3* |       |             |             | A53_6   | R52_6             |
    |  11    |         |       |             |             | A53_7   | R52_7             |
    |  12    |         |       |             |             | LLCE_0* |                   |
    |  13    |         |       |             |             | LLCE_1* |                   |
    |  14    |         |       |             |             | LLCE_2* |                   |
    |  15    |         |       |             |             | LLCE_3* |                   |
@note: The cores marked with "*" are currently not supported to be loaded by the HSE FW
*/
#else /* HSE_B device */
/** @brief   The application core IDs (that can be started).
             Only the IDs for the table below must be provided for a specific platform; otherwise an error will be reported.

    Core assignment table:

    | CoreID | S32K311 | S32K312| S32K342 | S32K344 | S32K396 | S32K358  | S32K388 |
    |-------:|:-------:|:------:|:-------:|:-------:|:-------:|:--------:|:-------:|
    |   0    | M7_0    | M7_0   | M7_0    | M7_0    | M7_0    | M7_0     | M7_0    |
    |   1    |         |        | M7_1    | M7_1    | M7_1    | M7_1     | M7_1    |
    |   2    |         |        |         |         | M7_2    | M7_2     | M7_2    |
    |   3    |         |        |         |         |         |          | M7_3    |
*/
#endif /* HSE_SPT_FLASHLESS_DEV */

typedef uint8_t hseAppCore_t;
#define HSE_APP_CORE0        ((hseAppCore_t)0U)    /**< @brief Core0 */
#define HSE_APP_CORE1        ((hseAppCore_t)1U)    /**< @brief Core1 */
#define HSE_APP_CORE2        ((hseAppCore_t)2U)    /**< @brief Core2 */
#define HSE_APP_CORE3        ((hseAppCore_t)3U)    /**< @brief Core3 */
#define HSE_APP_CORE4        ((hseAppCore_t)4U)    /**< @brief Core4 */
#define HSE_APP_CORE5        ((hseAppCore_t)5U)    /**< @brief Core5 */
#define HSE_APP_CORE6        ((hseAppCore_t)6U)    /**< @brief Core6 */
#define HSE_APP_CORE7        ((hseAppCore_t)7U)    /**< @brief Core7 */
#define HSE_APP_CORE8        ((hseAppCore_t)8U)    /**< @brief Core8 */
#define HSE_APP_CORE9        ((hseAppCore_t)9U)    /**< @brief Core9 */
#define HSE_APP_CORE10       ((hseAppCore_t)10U)   /**< @brief Core10 */
#define HSE_APP_CORE11       ((hseAppCore_t)11U)   /**< @brief Core11 */
#define HSE_APP_CORE12       ((hseAppCore_t)12U)   /**< @brief Core12 */
#define HSE_APP_CORE13       ((hseAppCore_t)13U)   /**< @brief Core13 */
#define HSE_APP_CORE14       ((hseAppCore_t)14U)   /**< @brief Core14 */
#define HSE_APP_CORE15       ((hseAppCore_t)15U)   /**< @brief Core15 */

/*==================================================================================================
                                 STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/

/** @brief    HSE Service IDs.*/
typedef uint32_t hseSrvId_t;

/** @brief Stream ID type.
  * @details The stream ID identifies the stream to be used in streaming operations. */
typedef uint8_t hseStreamId_t;

/** @brief Key Handle type.
  * @details The keyHandle identifies the key catalog(byte2), group index in catalog(byte1) and key slot index (byte0) */
typedef uint32_t hseKeyHandle_t;

/** @brief   HSE key group index.
 *  @details A group represents a set of keys of the same type.
 *           Each group is identified by its index within the catalog where it is declared*/
typedef uint8_t hseKeyGroupIdx_t;

/** @brief   HSE key slot index.
 *  @details A key slot represent a memory container for a single key.
 *           A group contains several key slots as defined during the key configuration */
typedef uint8_t hseKeySlotIdx_t;

/**
 * @brief   HSE service metadata.
 * @details Each service has a metadata (e.g. priority) */
typedef struct
{
    uint8_t             reserved[4]; /**< @brief For future use. */
} hseSrvMetaData_t;


/** @brief  No scheme (or parameters) are defined. */
typedef uint32_t hseNoScheme_t;


/** @brief RSAES OAEP Scheme.
 *  @details  Includes parameters needed for RSAES OAEP encryption/ decryption. */
typedef struct
{
    /** @brief   INPUT: The Hash algorithm for RSA OAEP padding. */
    hseHashAlgo_t   hashAlgo;
    uint8_t         reserved[3];
    /** @brief   INPUT: Optional OAEP label length (it can be 0). Must be less than 128. */
    uint32_t        labelLength;
    /** @brief   INPUT: Optional OAEP label (it can be NULL if label length is 0). Must be less than 128 bytes long. */
    HOST_ADDR       pLabel;
}hseRsaOAEPScheme_t;


/** @brief ECDSA signature scheme.
 *  @details  Includes parameters needed for ECDSA signature generate/verify. */
typedef struct
{
    /** @brief   INPUT: The hash algorithm used to hash the input before applying the ECDSA operation.
     *           Must not be #HSE_HASH_ALGO_NULL. */
    hseHashAlgo_t   hashAlgo;

    uint8_t         reserved[3];
}hseEcdsaScheme_t;


/** @brief EDDSA signature scheme.
 *  @details  Includes parameters needed for EDDSA signature generate/verify. */
typedef struct
{
    /** @brief   INPUT: Whether to pre-hash the input, and perform a HashEddsa signature. */
    bool_t          bHashEddsa;

    /** @brief   INPUT: The length of the EDDSA context. Length of zero means no context. */
    uint8_t         contextLength;

    uint8_t         reserved[2];

    /** @brief   INPUT: The EDDSA context. Ignored if contextLength is zero.
     *           Must remain unchanged until the signing operation is finished (especially in streaming),
     *           or the signature will be incorrect */
    HOST_ADDR       pContext;
}hseEddsaSignScheme_t;


/** @brief RSASSA_PSS signature scheme.
 *  @details  Includes parameters needed for RSASSA_PSS signature generate/verify. */
typedef struct
{
    /** @brief   INPUT: The hash algorithm used to hash the input before applying the RSA operation.
     *           Must not be #HSE_HASH_ALGO_NULL. */
    hseHashAlgo_t   hashAlgo;

    uint8_t         reserved[3];

    /** @brief   INPUT: The length of the salt in bytes. It must fulfill one of the following conditions:
     *                    - 0 <= saltLength <= 62 if the key length is 128 bytes and SHA-512 is used as hash algorithm;
     *                    - 0 <= saltLength <= hashLength otherwise, where hashLength denotes the output length of the chosen hash algorithm.

     */
    uint32_t        saltLength;
}hseRsaPssSignScheme_t;


/** @brief RSASSA_PKCS1_V15 signature scheme.
 *  @details  Includes parameters needed for RSASSA_PKCS1_V15 signature generate/verify. */
typedef struct
{
    /** @brief   INPUT: The hash algorithm
     *           Must not be HSE_HASH_ALGO_NULL. */
    hseHashAlgo_t   hashAlgo;

    uint8_t         reserved[3];
}hseRsaPkcs1v15Scheme_t;


/** @brief The HSE signature scheme.
 *  @details  Includes parameters needed for signature generate/verify. */
typedef struct
{
    /** @brief   INPUT: Signature scheme.*/
    hseSignSchemeEnum_t        signSch;
    uint8_t                    reserved[3];
    /** @brief   INPUT: Additional information for selected Signature scheme. */
    union
    {
        /** @brief   INPUT: ECDSA signature scheme. */
        hseEcdsaScheme_t       ecdsa;
        /** @brief   INPUT: EDDSA signature scheme. */
        hseEddsaSignScheme_t   eddsa;
        /** @brief   INPUT: RSA PSS signature scheme. */
        hseRsaPssSignScheme_t  rsaPss;
        /** @brief   INPUT: RSASSA_PKCS1_V15 signature scheme. */
        hseRsaPkcs1v15Scheme_t rsaPkcs1v15;
    }sch;
}hseSignScheme_t;


/** @brief HSE symmetric cipher scheme.
 *  @details Includes parameters needed for a symmetric cipher.
 */
typedef struct
{
    /** @brief   INPUT: Select an symmetric cipher. */
    hseCipherAlgo_t         cipherAlgo;
    /** @brief   INPUT: Specifies the cipher block mode. */
    hseCipherBlockMode_t    cipherBlockMode;
    uint8_t                 reserved[2];
    /** @brief   INPUT: Initialization Vector length(at least 16 bytes). */
    uint32_t                ivLength;
    /** @brief   INPUT: Initialization Vector/Nonce. */
    HOST_ADDR               pIV;
} hseSymCipherScheme_t;

typedef struct
{
    /** @brief   INPUT: Specifies the authenticated cipher mode. */
    hseAuthCipherMode_t     authCipherMode;
    uint8_t                 reserved[1];
    /** @brief   INPUT: Specifies the tag length. */
    uint16_t                tagLength;
    /** @brief   INPUT: Tag pointer. */
    HOST_ADDR                pTag;
    /** @brief   INPUT: Initialization Vector length(at least 12 bytes). */
    uint32_t                ivLength;
    /** @brief   INPUT: Initialization Vector/Nonce. */
    HOST_ADDR               pIV;
    /** @brief   INPUT: The length of Additional Data (in bytes). Can be zero. */
    uint32_t                aadLength;
    /** @brief   INPUT: The AAD Header data. Ignored if aadLength is zero. */
    HOST_ADDR               pAAD;
} hseAeadScheme_t;


/**
* @brief          RSA cipher scheme.
* @details        Performs the RSA encryption/decryption).
*/
typedef struct
{
    /** @brief   INPUT: RSA algorithm. */
    hseRsaAlgo_t             rsaAlgo;
    uint8_t                  reserved[3];
    /** @brief   INPUT: Scheme for selected RSA algorithm. */
    union
    {
        /** @brief   INPUT: RSA-OAEP scheme. */
        hseRsaOAEPScheme_t   rsaOAEP;
        /** @brief   INPUT: No scheme for RSA-PKCS1V15. */
        hseNoScheme_t        rsaPkcs1v15;
    }sch;
}hseRsaCipherScheme_t;


/** @brief HSE Cipher scheme.
 *  @details Includes parameters needed for symmetric cipher/RSA encryption and decryption.
 */
typedef union
{
    /** @brief   INPUT: Symmetric cipher scheme. */
    hseSymCipherScheme_t      symCipher;
    /** @brief   INPUT: Authenticated encryption scheme (AEAD-GCM/CCM). */
    hseAeadScheme_t           aeadCipher;
    /** @brief   INPUT: RSA cipher scheme. */
    hseRsaCipherScheme_t      rsaCipher;
}hseCipherScheme_t;

/** @brief CMAC scheme.
 *  @details  Includes parameters needed for CMAC tag generation/verification. */
typedef struct
{
    /** @brief   INPUT: Select a cipher algorithm for CMAC. */
    hseCipherAlgo_t    cipherAlgo;
    uint8_t            reserved[3];
} hseCmacScheme_t;


/** @brief HMAC scheme.
 *  @details  Includes parameters needed for HMAC tag generation/verification. */
typedef struct
{
    /** @brief   INPUT: Specifies the hash algorithm for HMAC. SHA3 and Miyaguchi-Preneel are not supported for HMAC */
    hseHashAlgo_t      hashAlgo;
    uint8_t            reserved[3];
} hseHmacScheme_t;

/** @brief GMAC scheme (AES only).
 *  @details  Includes parameters needed for GMAC tag generation/verification. */
typedef struct
{
    /** @brief   INPUT: Initialization Vector length. Zero is not allowed. Recommended 12 bytes or greater. */
    uint32_t           ivLength;

    /** @brief   INPUT: Initialization Vector/Nonce. */
    HOST_ADDR          pIV;
} hseGmacScheme_t;

/** @brief HSE MAC scheme.
 *  @details Includes parameters needed for MAC computation.
 */
typedef struct
{
    /** @brief   INPUT: Select an MAC algorithm. */
    hseMacAlgo_t      macAlgo;
    uint8_t           reserved[3];
    /** @brief   INPUT: The scheme (or parameters) for the selected mac algorithm. */
    union
    {
        /** @brief   INPUT: CMAC scheme (AES). */
        hseCmacScheme_t        cmac;
        /** @brief   INPUT: HMAC scheme. */
        hseHmacScheme_t        hmac;
        /** @brief   INPUT: GMAC scheme. Supports only AES. */
        hseGmacScheme_t        gmac;
        /** @brief   INPUT: No scheme parameters; supports only AES128. */
        hseNoScheme_t          xCbcmac;
    }sch;
} hseMacScheme_t;

/** @brief HSE authentication scheme.
 *  @details Includes parameters needed for authentication.
 */
typedef union
{
    /** @brief   INPUT: MAC scheme. */
    hseMacScheme_t    macScheme;
    /** @brief   INPUT: Signature scheme. */
    hseSignScheme_t   sigScheme;
} hseAuthScheme_t;

/** @brief   HSE Scatter List .
 *  @details The input and output data can be provided as a scatter list.
             A scatter list is used when the input/output is not a continuous buffer (the buffer is spread across multiple memory locations).
             The input and output pointers are specified as a list of entries as below. */
#ifdef HSE_SPT_SGT_OPTION
typedef struct
{
    uint32_t       length;         /**< @brief The length of the chunk. Maximum size must be less than 2^30.
                                        The final chunk from scatter list must have bit30 set to 1 (e.g. length = chunk_len | #HSE_SGT_FINAL_CHUNK_BIT_MASK) */
    HOST_ADDR      pPtr;           /**< @brief  Pointer to the chunk. */
}hseScatterList_t;
#endif /* HSE_SPT_SGT_OPTION */
/** @} */

/*==================================================================================================
*                                      DEFINES AND MACROS
==================================================================================================*/
/**  @brief   HSE attribute IDs.
 *   @details   The following attribute types are defined:
 *            - RO-ATTR - Read-Only attribute
 *            - OTP-ATTR - One Time Programmable; can be written only once (set FUSE/UTEST area)
 *            - OTP-ADVANCE-ATTR - One Time Programmable attribute that can only be advanced (e.g. LifeCycle)
 *            - NVM-RW-ATTR - System NVM attributes; can be read or written
 *            - SET-ONCE-ATTR- Once the attribute is set, it can not be changed until next reset (e.g. can be set once at initialization time)
 *
 * @note
 * - For HSE_H/M devices, if the NVM-RW attributes were updated, the SYS-IMAGE must be published and stored in external flash.
 * - For HSE_H/M devices, in order to program fuses (OTP-ATTR and OTP-ADVANCE-ATTR) during development and potentially in the field, the application must supply power to the VDD_EFUSE pin of the device.
 *   This allows the programming operation to take place. If theVDD_EFUSE is not powered and the application tries to write a fuse, the HSE returns an error
 *   (HSE_SRV_RSP_FUSE_VDD_GND). The VDD_EFUSE state is checked before the fuse write by reading the NCSPD_STAT register of the on-chip PMC module.
 *   The application must provide read access (xRDC restriction) to HSE in order to be able to read the NCSPD_STAT register.
 *   For more details, refer to HSE FW Reference Manual.
 * - To set/update the OTP or NVM attributes (except SET-ONCE-ATTR and OTP-ADVANCE-ATTR), the host needs SuperUser rights.
 * - After setting the HSE_SECURE_LIFECYCLE_ATTR_ID attribute, a destructive reset is needed.
*/
typedef uint16_t hseAttrId_t;

    /*----------------- Common (HSE_H/M/B) attributes ---------------------*/

    #define HSE_NONE_ATTR_ID                         ((hseAttrId_t)0U)
    /* RO-ATTR */
    #define HSE_FW_VERSION_ATTR_ID                   ((hseAttrId_t)1U)    /**< @brief RO-ATTR; HSE FW version (see #hseAttrFwVersion_t) */
    #define HSE_CAPABILITIES_ATTR_ID                 ((hseAttrId_t)2U)    /**< @brief RO-ATTR; HSE capabilities (see #hseAttrCapabilities_t) */
    #if defined(HSE_SPT_SMR_CR) || defined(HSE_SPT_BSB)
    #define HSE_SMR_CORE_BOOT_STATUS_ATTR_ID         ((hseAttrId_t)3U)    /**< @brief RO-ATTR;  SMR verification & Core-boot status (see #hseAttrSmrCoreStatus_t) */
    #endif  /* defined(HSE_SPT_SMR_CR) || defined(HSE_SPT_BSB) */
    #define HSE_FW_BUILD_INFO_ATTR_ID                ((hseAttrId_t)4U)    /**< @brief RO-ATTR; HSE FW Build information (see #hseFwBuildInfo_t) */

    /* OTP-ATTR & OTP-ADVANCE-ATTR*/
    #define HSE_DEBUG_AUTH_MODE_ATTR_ID              ((hseAttrId_t)10U)   /**< @brief OTP-ATTR; Debug Authorization mode (see #hseAttrDebugAuthMode_t) */
    #define HSE_APP_DEBUG_KEY_ATTR_ID                ((hseAttrId_t)11U)   /**< @brief OTP-ATTR; Application Debug Key / Password (see #hseAttrApplDebugKey_t and #hseAttrSecureApplDebugKey_t) */
    #define HSE_SECURE_LIFECYCLE_ATTR_ID             ((hseAttrId_t)12U)   /**< @brief OTP-ADVANCE-ATTR; Secure Life-cycle (see #hseAttrSecureLifecycle_t) */
    #define HSE_ENABLE_BOOT_AUTH_ATTR_ID             ((hseAttrId_t)13U)   /**< @brief OTP-ATTR; IVT/ DCD Authentication bit for HSE H and IVT Authentication bit for HSE M (see #hseAttrConfigBootAuth_t)  */

    #ifdef HSE_SPT_CUST_SEC_POLICY
    #define HSE_EXTEND_CUST_SECURITY_POLICY_ATTR_ID  ((hseAttrId_t)14U)   /**< @brief OTP-ATTR & NVM-RW-ATTR; HSE security policies extension in CUST_DEL lifecycle for user with CUST SU rights (see #hseAttrExtendCustSecurityPolicy_t). \
                                                                                    Note that this attribute also enables the ADKPm in OTP (ADKP diversified with UID), along with the START_AS_USER setting for CUST_DEL lifecycle. */
    #endif /* HSE_SPT_CUST_SEC_POLICY */

    /* NVM-RW-ATTR */
    #define HSE_MU_CONFIG_ATTR_ID                    ((hseAttrId_t)20U)   /**< @brief NVM-RW-ATTR; MU configuration (see #hseAttrMUConfig_t) */

    #ifdef HSE_SPT_OEM_SEC_POLICY
    #define HSE_EXTEND_OEM_SECURITY_POLICY_ATTR_ID   ((hseAttrId_t)21U)   /**< @brief NVM-RW-ATTR; HSE security policies extension in OEM_PROD lifecycle for user with OEM SU rights  (see #hseAttrExtendOemSecurityPolicy_t) */
    #endif /* HSE_SPT_OEM_SEC_POLICY */

    #ifdef HSE_SPT_FAST_CMAC
    #define HSE_FAST_CMAC_MIN_TAG_BIT_LEN_ATTR_ID    ((hseAttrId_t)22U)   /**< @brief NVM-RW-ATTR; The minimum tag bit length that can be used for Fast CMAC verify/generate (see #hseAttrFastCmacMinTagBitLen_t) */
    #endif /* HSE_SPT_FAST_CMAC */

    #define HSE_CORE_RESET_RELEASE_ATTR_ID           ((hseAttrId_t)23U)   /**< @brief NVM-RW-ATTR; Specifies Core Reset table parsing strategy (see #hseAttrCoreResetRelease_t) */

    #ifdef HSE_SPT_KEY_MGMT_POLICIES
    #define HSE_RAM_PUB_KEY_IMPORT_POLICY_ATTR_ID    ((hseAttrId_t)24U)   /**< @brief NVM-RW-ATTR; Specifies RAM public keys import policy in advanced LCs (see #hseAttrRamPubKeyImportPolicy_t) */
    #endif /* HSE_SPT_KEY_MGMT_POLICIES */

    #ifdef HSE_SPT_RESET_SOC_ON_TAMPER_ATTR
    #define HSE_RESET_SOC_ON_TAMPER_ATTR_ID          ((hseAttrId_t)25U)   /**< @brief NVM-RW-ATTR; Reset Soc on tamper detection (see #hseResetSocOnTamper_t) */
    #endif /* HSE_SPT_RESET_SOC_ON_TAMPER_ATTR */

    /*----------------- END  Common (HSE_H/M/B) attributes --------------------*/

#ifdef HSE_SPT_FLASHLESS_DEV

    #define HSE_OTP_ROLLBACK_PROTECTION_POLICY_ATTR_ID ((hseAttrId_t)26U) /**< @brief NVM-RW-ATTR; Disable or enable (default) the OTP rollback protection for FW Blue Image and SYS-IMG (see #hseOtpRollbackProtectionPolicy_t) */
#endif /* HSE_SPT_FLASHLESS_DEV */

    #ifdef HSE_SPT_APP_SPECIFIC_DATA_ATTR
    #define HSE_APP_SPECIFIC_DATA_ATTR_ID               ((hseAttrId_t)27U)    /**< @brief NVM-RW-ATTR; Set an application-specific data of maximum #HSE_APP_SPECIFIC_DATA_MAX_BUFFER_SIZE bytes (see #hseAppSpecificData_t) */

    #define HSE_DISABLE_APP_SPECIFIC_DATA_WRITE_ATTR_ID ((hseAttrId_t)28U)    /**< @brief SET-ONLY-ONCE-ATTR; Disable the write of APP_SPECIFIC_DATA attribute (see #hseDisableAppSpecificDataWrite_t) */
    #endif /* HSE_SPT_APP_SPECIFIC_DATA_ATTR */

    /* SET-ONCE-ATTR*/
    #ifdef HSE_SPT_PHYSICAL_TAMPER_CONFIG
    #define HSE_PHYSICAL_TAMPER_ATTR_ID              ((hseAttrId_t)30U)   /**< @brief SET-ONLY-ONCE-ATTR; Enables the physical tamper violation in HSE.
                                                                                Once the violation is enabled in HSE, it can not be cleared
                                                                                until next reset. There are two tamper related functions available on PADs: Input (TAMPER_IN), Output (TAMPER_OUT).
                                                                                To support protection against physical tampering, connect TAMPER_OUT to
                                                                                TAMPER_IN. Any physical tamper that breaks this connectivity sets off an alarm at
                                                                                HSE (if enabled using this attribute). User can optionally lock those pads
                                                                                configuration for further modification using virtual wrapper (refer to #hseAttrPhysicalTamper_t).
                                                                                The configuration status is provided by reading the HSE_GPR_STATUS_ADDRESS register (refer to #hseTamperConfigStatus_t). */
    #endif /* HSE_SPT_PHYSICAL_TAMPER_CONFIG */

    #ifdef HSE_SPT_MEM_REGION_PROTECT
    #define HSE_MEM_REGIONS_PROTECT_ATTR_ID          ((hseAttrId_t)31U)   /**< @brief SET-ONLY-ONCE-ATTR; Configures memory regions accessible through each MU (refer to #hseAttrAllMuMemRegions_t) */
    #endif /* HSE_SPT_MEM_REGION_PROTECT */

    /*------------------------ HSE_H/M specific attributes ------------------------*/
#if defined(HSE_SPT_FLASHLESS_DEV)

    /* RO-ATTR */
    #define HSE_FW_SIZE_ATTR_ID                      ((hseAttrId_t)100U)  /**< @brief RO-ATTR; HSE Firmware Size (see #hseAttrHseFwSize_t) */
    #define HSE_AVAIL_ANTI_ROLLBACK_COUNTER_ATTR_ID  ((hseAttrId_t)101U)  /**< @brief RO-ATTR; The anti-rollback counter updates left (see #hseAvailAntiRollbackCounter_t) */
    #define HSE_FW_PARTITION_ATTR_ID                 ((hseAttrId_t)102U)  /**< @brief RO-ATTR; The partition (primary or backup) used by BootRom to load the HSE Firmware (see #hseAttrFwPartition_t) */

    #ifdef HSE_SPT_OTFAD
    #define HSE_OTFAD_CTX_STATUS_ATTR_ID             ((hseAttrId_t)103U)  /**< @brief RO-ATTR; Otfad contexts status (see #hseOtfadContextStatus_t). */
    #endif /* HSE_SPT_OTFAD */

    #ifdef HSE_SPT_SMR_SECURE_LOGGING
    #define HSE_SLOG_STATUS_ATTR_ID                  ((hseAttrId_t)104U)  /**< @brief RO-ATTR; Get the secure logging status (see #hseSlogStatus_t) */
    #endif /* HSE_SPT_SMR_SECURE_LOGGING */

    /* OTP-ATTR */
    #define HSE_APP_DEBUG_DIS_ATTR_ID                ((hseAttrId_t)200U)  /**< @brief OTP-ATTR; Disable Application Debug (see #hseAttrDisableAppDebug_t) */

    /* NVM-RW-ATTR */
    #ifdef HSE_SPT_SMR_SECURE_LOGGING
    #define HSE_SLOG_SMR_CONFIG_ATTR_ID              ((hseAttrId_t)301U)   /**< @brief NVM-RW-ATTR; To configure the SMR(s) linked with the secure logging (see #hseAttrSlogSmrCfg_t) */
    #endif /* HSE_SPT_SMR_SECURE_LOGGING */

    /* SET-ONCE-ATTR*/
    #ifdef HSE_SPT_TEMP_SENS_VIO_CONFIG
    #define HSE_TEMP_SENSOR_VIO_CONFIG_ATTR_ID       ((hseAttrId_t)400U)  /**< @brief SET-ONLY-ONCE-ATTR; Enable the temperature sensor violation in HSE (see #hseTempSensVioConfig_t) */
    #endif /* HSE_SPT_TEMP_SENS_VIO_CONFIG */

#endif /* HSE_SPT_FLASHLESS_DEV */
    /*------------------------ END HSE_H/M specific attributes ---------------------*/

    /*------------------------ HSE_B specific attributes ---------------------------*/
#ifdef HSE_B

    /* SET-ONCE-ATTR*/
    #define HSE_FIRC_DIVIDER_CONFIG_ATTR_ID          ((hseAttrId_t)600U)  /**< @brief RAM-RW; FIRC Divider Configuration by HSE Firmware from HSE_GPR (see #hseFircDivConfig_t) */
    /* Secure Recovery */
    #define HSE_SECURE_RECOVERY_CONFIG_ATTR_ID       ((hseAttrId_t)601U)  /**< @brief OTP-ATTR; Secure Recovery Configuration by HSE Firmware (see #hseAttrConfigSecureRecovery_t) */
    /* Flash Optimization Config Attr */
    #if defined(HSE_SPT_PUBLISH_NVM_KEYSTORE_RAM_TO_FLASH)
    #define HSE_ENABLE_PUBLISH_KEY_STORE_RAM_TO_FLASH_ATTR_ID    ((hseAttrId_t)602U)  /**< @brief RAM-RW; Allow to publish the NVM keystore from secure NVM keystore into the data flash (see #hsePublishNvmKeystoreRamtToFlash_t) */
    #endif /* HSE_SPT_PUBLISH_NVM_KEYSTORE_RAM_TO_FLASH */

#endif /* HSE_B */
    /*------------------------ END HSE_B specific attributes ---------------------*/


/** @brief    Activate or not a specific configuration.
 * @details   Tells whether the HSE activate or not a specific configuration.
 */
typedef uint32_t hseAttrCfg_t;
#define HSE_CFG_NO       ((hseAttrCfg_t)(0x0UL))                    /**< @brief NO, deactivate the configuration */
#define HSE_CFG_YES      ((hseAttrCfg_t)(0xB7A5C365UL))             /**< @brief YES, activate the configuration */

/*==================================================================================================
*                                             ENUMS
==================================================================================================*/

/*==================================================================================================
                                 STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/

/*==================================================================================================
                                 HSE SET/GET ATTRIBUTE SERVICES
==================================================================================================*/

/** @brief Set HSE attribute service.
 *         @note SuperUser rights (for NVM Configuration) are needed to perform this service.
 */
typedef struct
{
    /** @brief   INPUT: Specifies the HSE attribute ID.*/
    hseAttrId_t   attrId;
    uint8_t       reserved[2];
    /** @brief   INPUT: Specifies the attribute length (in bytes). The size of the memory location
     *                   must be equal to the length of attribute structure */
    uint32_t      attrLen;
    /** @brief   INPUT: The address of the attribute.
     *                  The attribute must have the format of the corresponding attributes structure (see attributes definition)
     *                  @note
     *                  The comment for each attribute ID provides the name for the attribute data structure.
     *                  E.g:The #HSE_MU_CONFIG_ATTR_ID definition includes the following comment: "NVM-RW-ATTR; MU configuration (see #hseAttrMUConfig_t)". */
    HOST_ADDR     pAttr;
} hseSetAttrSrv_t;

/** @brief Get HSE attribute service. */
typedef struct
{
    /** @brief   INPUT: Specifies the HSE attribute ID.*/
    hseAttrId_t   attrId;
    uint8_t       reserved[2];
    /** @brief   INPUT: Specifies the attribute length (in bytes).The size of the memory location
     *                  must be bigger than or equal to the length of attribute structure */
    uint32_t      attrLen;
    /** @brief   OUTPUT: The address where the attribute will be stored.
     *                   The attribute must be stored in the format of the corresponding attribute Id (see the attributes definition).
     *                  @note
     *                  The comment for each attribute ID provides the name for the attribute data structure.
     *                   E.g: The #HSE_FW_VERSION_ATTR_ID definition includes the following comment: "RO-ATTR; HSE FW version (see #hseAttrFwVersion_t)". */
    HOST_ADDR     pAttr;
} hseGetAttrSrv_t;

/*==================================================================================================
                                 ATTRIBUTE DEFINITION
==================================================================================================*/

/*==================================================================================================
                                 HSE FW version
==================================================================================================*/
/**
* @brief          HSE FW version attribute (HSE_H/M/B attribute).
*                 This is a READ-ONLY global attribute.
*/
typedef struct
{
    uint8_t     reserved;       /**< @brief  For HSE_B, it is used for OTA Config: 0 = Full Mem Config; 1 = AB Swap Config.
                                             For other SOC type: Reserved, expected to be 0 */
    uint8_t     socTypeId;      /**< @brief  Identifies the SoC Type ID; same as HSE_PLATFORM from hse_target.h */
    uint16_t    fwTypeId;       /**< @brief  Identifies the FW type:
                                              - 0 - Standard FW targeting all customers
                                              - 1 - Premium  FW targeting all customers
                                              - 2-7 - Reserved
                                              - 8 >= Custom1, Custom2... etc */
    uint8_t     majorVersion;   /**< @brief  Major revision
                                              - 0 - Pre-stabilization releases
                                              - 1 - at first stable interface release, and increased later if breaking changes were introduced */
    uint8_t     minorVersion;   /**< @brief  Minor revision, bumped on new compatible changes added; <br>
                                             reset to 0 on majorVersion bump, if majorVersion > 0 */
    uint16_t    patchVersion;   /**< @brief  Hotfix release (patch version, bug fix releases).<br>
                                             After majorVersion > 0, reset to 0 on majorVersion or minorVersion bump. */
} hseAttrFwVersion_t;


/*==================================================================================================
                                 HSE capabilities
==================================================================================================*/
/** @brief    HSE capabilities bits definition.
 * @details   Provides information about the capabilities of HSE security blocks (list of what algorithms are supported).
 *            Each bit specifies an supported algorithm. The index for each bit in the attribute is defined by #hseAlgoCapIdx_t.
*/
typedef uint64_t hseAttrCapabilities_t;
/** @brief    Provided the bit (used in hseAttrCapabilities_t) based on the algorithm capability index (see #hseAlgoCapIdx_t) */
#define HSE_ALGO_CAP_MASK(capIdx)  (1ULL << (capIdx))

/*==================================================================================================
                                 HSE FW build info
==================================================================================================*/
/**
* @brief          HSE FW build information attribute.
*                 This is a READ-ONLY global attribute.
*/
typedef struct
{
    uint64_t    buildUniqueIdentifier;          /**< @brief  Build unique identifier (8 bytes of SHA1 of the HEAD ) */
    uint32_t    buildDate;                      /**< @brief  Build date in hexadecimal (hex(YYYYMMDD)) */
    uint32_t    buildTime;                      /**< @brief  Build time in hexadecimal (hex(HHMMSS)) */
} hseFwBuildInfo_t;

/*==================================================================================================
                                 SMR verification & Core-boot status
==================================================================================================*/
/** @brief    The SMR and Core Boot status.
 * @details   Provides the following infomation:
 *            - SMR entry installation status corresponding to the entries present in SMR table (refer to #smrEntryInstallStatus)
 *            - SMR verification status corresponding to the entries present in SMR table (refer to #smrStatus[])
 *            - Provides Core Boot status (refer to #coreBootStatus[])
 *            - In case Basic Secure Boot (BSB) is performed, it provides the Core Boot status and the location of loaded application (primary/backup, refer to #coreBootStatus[])
 */
#if defined(HSE_SPT_SMR_CR) || defined(HSE_SPT_BSB)
typedef struct
{
    uint32_t smrStatus[2U];         /**< @brief  0-31 bit will represent 32 SMR table entries (applicable when SMR is present/enabled).
                                                - smrStatus[0].bit : 0 - SMR Not verified
                                                - smrStatus[0].bit : 1 - SMR verified
                                                - smrStatus[1].bit : 0 - SMR verification fail
                                                - smrStatus[1].bit : 1 - SMR verification pass */
    uint32_t coreBootStatus[2U];   /**< @brief   0-31 bit will represent CORE-ID (0-31):
                                                - coreBootStatus[0].bit : 1 - Core booted
                                                - coreBootStatus[0].bit : 0 - Core Not booted
                                                - coreBootStatus[1].bit : 1 - Core booted with pass/primary reset address
                                                - coreBootStatus[1].bit : 0 - Core booted with alternate/backup reset address */
    uint32_t smrEntryInstallStatus;/**< @brief   0-31 bit will represent 32 SMR table entries (applicable when SMR is present/enabled).
                                                - bit : 0 - SMR entry not installed
                                                - bit : 1 - SMR entry installed */
} hseAttrSmrCoreStatus_t;
#endif /*defined(HSE_SPT_SMR_CR) || defined(HSE_SPT_BSB) */

#ifdef HSE_SPT_SMR_SECURE_LOGGING
/** @brief    The secure logging SMR(s) configuration
 * @details   This service configures the on-demand or periodic SMR(s) that must be verified for secure logging.
 *             Additionally, it enables the use of fuse or RAM for secure logging.
 * @note
 *   - The Application must have SU rights to configure this attribute.
 *   - The attribute can be read at any time without any restriction.
 *   - HSE logs the SMR failures and recoveries in a 8-bit secure logging status.
 *     Maximum 4 failures and 3 recoveries can be logged (7 bits in total, from 0 to 6; last bit is not used).
 *     For details, refer to #hseSlogStatus_t.
 *   - By default, HSE logs the secure logging status in RAM. Using this service, the application
 *     can enable the logging in fuses. The application must understand the criticality of the secure logging in fuses.
 *   - A failure is logged if one of the following conditions is met:
 *     1. At start-up, when BOOT_SEQ == 1 and the secure boot (SMR or BSB) fails
 *     2. If any of the on-demand/runtime SMR specified in smrPeriodicOnDemand flags failed.
 */
typedef struct
{
    uint32_t     slogSmrPeriodicOnDemand;           /**< @brief The on-demand or periodic SMR(s) that must be verified for secure logging. */
    hseAttrCfg_t enableFuseUsage;                   /**< @brief #HSE_CFG_NO -  the fuse bits are not used. The secure logging status is stored in internal RAM (is not persistent).<br>
                                                                #HSE_CFG_YES - the fuse bits are used. The secure logging status is persistent in fuse. */
    uint8_t      reserved[8];
} hseAttrSlogSmrCfg_t;

/** @brief   The secure logging status
 * @details  It provides the SMR failures and recoveries in fuse (or RAM if enableFuseUsage == HSE_CFG_NO).
 *           The secure logging is configured using #hseAttrSlogSmrCfg_t attribute.
 *           By default, the secure logging is using the RAM (it is not persistent in fuses)
 *           The secure logging status is stored in 8 bits as follows:
 *           - Even bits signals a failure: sLog[bit#i (even)] == 1 means the secure boot failed (logging number i/2)
 *           - Odd bits signals a recovery: sLog[bit#i + 1]    == 1 means the secure boot failure number i/2 was recovered
 *           - bit #7 is not used
 *           @note
 *           - Example of logging the secure boot failures and recoveries in fuse (bit #7 not used)
 * |  Bit position   |  b7 |  b6 |  b5 |  b4 |  b3 |  b2 |  b1 |  b0 |                        Remark                            |
 * |----------------:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---------------------------------------------------------|
 * | hseSlogStatus   |  X  |  0  |  0  |  0  |  0  |  0  |  0  |  0  | No secure boot failure logged                            |
 * | hseSlogStatus   |  X  |  0  |  0  |  0  |  0  |  0  |  0  |  1  | One secure boot failure logged                           |
 * | hseSlogStatus   |  X  |  0  |  0  |  0  |  0  |  0  |  1  |  1  | One secure boot failure logged but recovered             |
 * | hseSlogStatus   |  X  |  1  |  1  |  1  |  1  |  1  |  1  |  1  | Four secure boot failure logged, no further log possible |
 */
typedef uint8_t hseSlogStatus_t;

#endif /* HSE_SPT_SMR_SECURE_LOGGING */

/*==================================================================================================
                                 Core Release Strategy
==================================================================================================*/
/** @brief    The Core Reset release from reset method.
 * @details   Specifies the startup method for releasing the application core from reset. */
typedef uint32_t hseAttrCoreResetRelease_t;
#define HSE_CR_RELEASE_ALL_AT_ONCE        ((hseAttrCoreResetRelease_t)0xA5556933UL)  /**< @brief Cores are released all-at-once after the pre-boot verification phase is over */
#define HSE_CR_RELEASE_ONE_BY_ONE         ((hseAttrCoreResetRelease_t)0xA5557555UL)  /**< @brief Cores are released from reset one-by-one after their respective pre-boot phase has finalized successfully
                                                                                                 (i.e. the SMR entries linked to the core via CR table have been loaded and verified). <br>
                                                                                                 The cores are released in ascending order of their indicies in the Core Reset table. <br>
                                                                                                 Flashless devices (e.g. HSE_H/M) limitations:
                                                                                                  - Only the first Core Reset entry can be booted from SD/MMC.
                                                                                                  - The system clocks and QSPI configurations shall not be changed by the core(s) booted until #HSE_STATUS_BOOT_OK status is set. */

/*==================================================================================================
                                 Debug Authorization Mode bit
==================================================================================================*/
/** @brief    Debug Authorization Mode bit (HSE_H/M/B attribute).
 * @details   Tells whether the Application debug authorization will be password based or challenge-response based.
*/
typedef uint8_t hseAttrDebugAuthMode_t;
#define HSE_DEBUG_AUTH_MODE_PW          ((hseAttrDebugAuthMode_t)0x0U)            /**< @brief Password based application debug authorization mode.
                                                                                     - Read: Application debug authorization will be password based.
                                                                                     - Write: Does not affect application debug authorization mode at all. */
#define HSE_DEBUG_AUTH_MODE_CR          ((hseAttrDebugAuthMode_t)0x1U)            /**< @brief Challenge-Response based application debug authorization mode.
                                                                                     - Read: Application debug authorization will be challenge-response based.
                                                                                     - Write: Enables challenge-response application debug authorization mode.
                                                                                              Once this mode is enabled, it cannot be disabled.
                                                                                              Operation allowed in CUST_DEL, OEM_PROD and IN_FIELD LCs only. */


/*==================================================================================================
                                 Application Debug Key/ Password definition-
==================================================================================================*/
/** @brief    Application Debug Key/ Password definition (HSE_H/M/B attribute).
 * @details   It is an 128-bit Application Debug Key/ Password to be set by the host in CUST_DEL LifeCycle.
 *            - Read: Not allowed if ADKP has not been written yet. After it has been written, first 16 bytes of SHA2_224(ADKP) can be requested via get ADKP attribute service.
 *            - Write: ADKP can be updated only once. The operation allowed only in CUST_DEL LifeCycle.
 *
 * @note      Provided ADKP, if containing all 0x00 bytes or all 0xFF bytes will be rejected by HSE Firmware with the response #HSE_SRV_RSP_INVALID_PARAM.
 */
typedef uint8_t hseAttrApplDebugKey_t[16];

/** @brief    Secure Application Debug Key/ Password definition (HSE_H/M/B attribute).
 * @details   It is the key handle referencing a key already installed in HSE. It must be an AES 128-bits key from RAM or NVM key catalogs.
 *            - Read: Allowed only as the hash over the ADKP (see Read from #hseAttrApplDebugKey_t).
 *            - Write:
 *                  - ADKP can be updated only once. The operation allowed only in CUST_DEL LifeCycle.
 *                  - The key referenced must be installed in HSE a priori. After the key is written successfully in the fuse as ADK/P, it will be erased from the RAM/NVM key catalog.
 */
typedef hseKeyHandle_t hseAttrSecureApplDebugKey_t;


/*==================================================================================================
                                 HSE Secure Lifecycle
==================================================================================================*/
/** @brief    HSE secure lifecycle definition.
 * @details   Represents HSE secure lifecycle. The lifecycle can be advanced only in forward direction.
 *            Warnings:
 *            - The lifecycle is read/scanned by hardware during the reset phase. Hence, a reset is recommended
 *            after each LC write-advance operation.
 *            - The lifecycle can be advanced to OEM_PROD/IN_FIELD only if the #HSE_APP_DEBUG_KEY_ATTR_ID attribute was set before.
 */
typedef uint8_t hseAttrSecureLifecycle_t;
#define HSE_LC_CUST_DEL                 ((hseAttrSecureLifecycle_t)0x4U)    /**< @brief Customer Delivery Lifecycle.
                                                                                - Read: The current LC is CUST_DEL.
                                                                                - Write: Advancement to this LC is not allowed (through HSE Firmware). */
#define HSE_LC_OEM_PROD                 ((hseAttrSecureLifecycle_t)0x8U)    /**< @brief OEM Production Lifecycle.
                                                                                - Read: The current LC is OEM_PROD.
                                                                                - Write: Advancement to this LC is allowed only once (from CUST_DEL LC).
                                                                                         The key catalogs MUST be configured before advancing to this lifecycle. */
#define HSE_LC_IN_FIELD                 ((hseAttrSecureLifecycle_t)0x10U)    /**< @brief In-Field Lifecycle.
                                                                                - Read: The current LC is IN_FIELD.
                                                                                - Write: Advancement to this LC is allowed only once (from CUST_DEL, OEM_PROD LCs).
                                                                                         The key catalogs MUST be configured before advancing to this lifecycle. */
#define HSE_LC_PRE_FA                   ((hseAttrSecureLifecycle_t)0x14U)    /**< @brief Pre-Failure Analysis Lifecycle.
                                                                                - Read: The current LC is Pre-FA.
                                                                                - Write: Advancement from/to this LC is NOT allowed (through HSE Firmware).*/
#define HSE_LC_SIMULATED_OEM_PROD       ((hseAttrSecureLifecycle_t)0xA6U)   /**< @brief Simulated OEM_PROD to avoid writing in FUSE/UTEST. A system reset will revert LC to FUSE/UTEST value.
                                                                                - Read: The current LC is OEM_PROD.
                                                                                - Write: Advancement to this LC is allowed only once (from CUST_DEL LC).
                                                                                         The key catalogs MUST be configured before advancing to this lifecycle. */
#define HSE_LC_SIMULATED_IN_FIELD       ((hseAttrSecureLifecycle_t)0xA7U)   /**< @brief Simulated IN_FIELD to avoid writing in FUSE/UTEST. A system reset will revert LC to FUSE/UTEST value.
                                                                                - Read: The current LC is IN_FIELD.
                                                                                - Write: Advancement to this LC is allowed only once (from CUST_DEL, SIMULATED_OEM_PROD LCs).
                                                                                         The key catalogs MUST be configured before advancing to this lifecycle. */


/*==================================================================================================
                                 IVT Boot Authentication configuration
==================================================================================================*/
/** @brief    Boot Authentication bit.
 * @details   Value used by Boot ROM to check whether the IVT data needs be authenticated.
*/
typedef uint8_t hseAttrConfigBootAuth_t;
#define HSE_IVT_NO_AUTH             ((hseAttrConfigBootAuth_t)0x0U)            /**< @brief
                                                                                    For HSE_H/M, the IVT/DCD/ST is not authenticated by BootROM:
                                                                                     - Read: IVT/DCD/ST is not authenticated by BootROM.
                                                                                     - Write: Does not affect IVT/ DCD authentication value at all.

                                                                                    For HSE_B, the IVT configuration is not authenticated by Secure BAF:
                                                                                     - Read: IVT is not authenticated by Secure BAF.
                                                                                     - Write: Does not affect IVT configuration authentication value at all.
                                                                               */
#define HSE_IVT_AUTH                ((hseAttrConfigBootAuth_t)0x1U)            /**< @brief
                                                                                    For HSE_H/M, the IVT/DCD/ST to be authenticated by BootROM:
                                                                                    - Read: IVT/DCD/ST is authenticated by BootROM.
                                                                                    - Write: Sets IVT/DCD/ST authentication value.
                                                                                    Once this value is set, it cannot be cleared back.
                                                                                    Operation allowed in CUST_DEL, OEM_PROD & IN_FIELD LCs only.

                                                                                    For HSE_B, the IVT to be authenticated by Secure BAF:
                                                                                     - Read: IVT will be authenticated by Secure BAF.
                                                                                     - Write: Sets IVT authentication value.
                                                                                    Once this value is set, it cannot be cleared back.
                                                                                    Operation allowed in CUST_DEL, OEM_PROD & IN_FIELD LCs only.
                                                                               */


/*==================================================================================================
                                 MU Configuration and XRDC configuration
==================================================================================================*/
/** @brief    MU configuration byte (HSE_H/M/B attribute).
 * @details   Tells whether the HSE enables the receive interrupt on the configured MU interface.
*/
typedef uint8_t hseMUConfig_t;
#define HSE_MU_ACTIVATED       ((hseMUConfig_t)(0xA5U))                   /**< @brief HSE enables the receive interrupt on the MU interface. */
#define HSE_MU_DEACTIVATED     ((hseMUConfig_t)(0x5AU))                   /**< @brief HSE disables the receive interrupt on the MU interface. */

/** @brief    MU Configuration and XRDC configuration definition for a MU interface.
 * @details   Configures a MU interface and XRDC configuration for the HOST Interface Memory.
 *            @note
 *                  If the device does have (or use) any Host Interface memory, the xrdcDomainId and
 *                  sharedMemChunkSize can be set zero.
 */
typedef struct
{
    hseMUConfig_t muConfig;                 /**< @brief    This value specifies MU interface state.
                                                           - #HSE_MU_ACTIVATED:      MU interface activated
                                                           - #HSE_MU_DEACTIVATED:    MU interface deactivated
                                                           @note It is not allowed to deactivate the MU0 interface */

    uint8_t xrdcDomainId;                   /**< @brief    Domain Id to access the Host Interface memory chunk reserved for
                                                           the MU interface. Must have a value between interval [0, 7].
                                                           The xrdcDomainId field is not taken into account when the
                                                           #sharedMemChunkSize field is equal to 0. */
    uint16_t sharedMemChunkSize;            /**< @brief    Specifies what chunk of host interface memory to reserve for
                                                           the specific MU interface.
                                                           For a value of 0 there is no memory reserved for the MU interface.
                                                           If the #sharedMemChunkSize field is equal to 0 for all MU interfaces,
                                                           the XRDC is disabled and there are no restrictions on the host
                                                           interface memory. */
    uint8_t reserved[60];
} hseAttrMUInstanceConfig_t;

/** @brief    MU Configurations and XRDC configuration definition.
 * @details   Configures the MU interfaces and XRDC configurations for the HOST Interface Memory.
 *
 */
typedef struct
{
    hseAttrMUInstanceConfig_t muInstances[HSE_NUM_OF_MU_INSTANCES];   /**< @brief   Contains the configurations for all MU interfaces */
} hseAttrMUConfig_t;


/*==================================================================================================
                                 HSE Memory region
==================================================================================================*/
#ifdef HSE_SPT_MEM_REGION_PROTECT

/** @brief Access types for #HSE_SPT_MEM_REGION_PROTECT service regions */
typedef uint32_t hseMemRegAccess_t;
#define HSE_MEM_REG_ACCESS_MASK_IN     ((hseMemRegAccess_t)(0x00003C96UL))
#define HSE_MEM_REG_ACCESS_MASK_OUT    ((hseMemRegAccess_t)(0x5A690000UL))
#define HSE_MEM_REG_ACCESS_MASK_INOUT  ((hseMemRegAccess_t)(HSE_MEM_REG_ACCESS_MASK_IN | HSE_MEM_REG_ACCESS_MASK_OUT))

/**
* @brief        HSE Memory region
* @details      Defines base address and length of a region
*/
typedef struct
{
    /** @brief     INPUT: Access type on which the region applies */
    hseMemRegAccess_t accessType;

    /** @brief     INPUT: Length of memory region */
    uint32_t          length;

    /** @brief     INPUT: Start address of memory region */
    HOST_ADDR         pBaseAddr;
} hseAttrMemRegion_t;

/**
* @brief        HSE Memory region attribute for a single MU.
* @details      Defines the number of regions and their start address
*               and sizes for a single MU
*/
typedef struct
{
    /** @brief     INPUT: Specify the number of memory regions for one MU.
     *             @note
     *             Set to zero if not used
     */
    uint8_t            numofMemRegions;

    uint8_t            reserved[3];

    /** @brief     INPUT: Specifies the memory regions for one MU */
    hseAttrMemRegion_t memRegionList[HSE_MAX_NUM_OF_MEM_REGIONS];
} hseAttrMuMemRegions_t;

/**
* @brief        HSE Memory regions protection attribute for all HSE MUs.
* @details      HSE Memory regions protection is a service used to prevent memory accesses
*               between disallowed bus masters through HSE MUs.
*               HSE uses these regions to validate the input/output parameters
*               for each service received on the corresponding MU.
*               @note
*                 - The attribute is not persistent and can only be set once. <br>
*                   A reset is necessary for this configuration to be settable again.
*                 - Input and output data linked via pointers in the service descriptor (these are typically pointers to
*                   SRAM or DRAM) can be isolated between hosts using the
*                   HSE_MEM_REGIONS_PROTECT_ATTR_ID attribute. The host can communicate to HSE the
*                   memory ranges that are associated with each MU instance. If provided, the HSE dismisses the data
*                   that falls outside the ranges for a particular MU instance.
*
*/
typedef struct
{
    /** @brief     INPUT: Array with memory regions for all MUs */
    hseAttrMuMemRegions_t muMemRegions[HSE_NUM_OF_MU_INSTANCES];
} hseAttrAllMuMemRegions_t;

#endif /* HSE_SPT_MEM_REGION_PROTECT */

/*==================================================================================================
                                HSE key management policies
==================================================================================================*/
#ifdef HSE_SPT_KEY_MGMT_POLICIES

/** @brief    HSE key management policy regarding RAM public keys import.
 *  @details  Determines whether public keys can be imported without authentication in advanced LCs. <br>
 *            Default value is HSE_KM_POLICY_DEFAULT, i.e. HSE does not allow public key import in RAM, when having User rights, if they are not an authenticated key container. <br>
 *            Otherwise, if set to HSE_KM_POLICY_ALLOW_RAM_PUB_KEY_IMPORT, RAM public keys are allowed to be imported without authentication, regardless of the access rights. <br>
 *            SU access rights with configuration privileges are required to update this attribute value.
*/
typedef uint32_t hseAttrRamPubKeyImportPolicy_t;
#define HSE_KM_POLICY_DEFAULT                   ((hseAttrRamPubKeyImportPolicy_t)(0x4E8BD124UL))
#define HSE_KM_POLICY_ALLOW_RAM_PUB_KEY_IMPORT  ((hseAttrRamPubKeyImportPolicy_t)(0xB1742EDBUL))

#endif /* HSE_SPT_KEY_MGMT_POLICIES */

/*==================================================================================================
                                 HSE extend CUST security policies
==================================================================================================*/
#ifdef HSE_SPT_CUST_SEC_POLICY

/** @brief    HSE extend CUST security policies attribute definition.
 * @details   Determines whether certain security policies are extended in HSE Firmware or not; applies only for CUST_DEL LC.
 *            - Read: Tells which extended security policies are set or not.
 *            - Write:
 *                   - If a given policy is not set to be TRUE, there is no change on security policy extension.
 *                   - If a given policy is set to be TRUE, security policy is extended on successful operation.
 *                   - Write operation is allowed only for users with CUST SU rights in CUST_DEL LC.
 */
typedef struct
{
    bool_t  enableADKm;      /**< @brief Application Debug Key/Password (attribute) diversified with UID before
                                        being written in fuse. The supplied 128-bit value for ADK/P attribute
                                        will be interpreted as ADKPm (customer's master key/ password). If needed,
                                        this policy must be set before setting ADK/P attribute. <br>
                                        If set, the following logic must be used at customer's end for debug-authorization:
                                         - hUID = SHA2_256(UID)
                                         - hADKPm = SHA2_256(ADKPm)
                                         - ADKP {for debugger} = AES256-ECB(hUID(16 bytes..0 to 15)), key = hADKPm;  {ADKPm = customer's master key/ password}.
                                         The hash of ADKPm (set using ADKP attribute) will be used as the key in the derivation of the application password.
                                         An error will be returned if the value of this attribute is given as 0 from host interface.
                                         @note For HSE_H/M, the UID is read by HSE from system fuses. The application must provide read access (xRDC restriction) to HSE in order to be able to read the UID.*/
    bool_t  startAsUser;     /**< @brief Host starts with User rights in LC = CUST_DEL.
                                        @note Setting this attribute will take effect only after publishing the SYS Image and issuing a reset. */
    uint8_t reserved[2];     /**< @brief HSE reserved */
} hseAttrExtendCustSecurityPolicy_t;

#endif /* HSE_SPT_CUST_SEC_POLICY */

/*==================================================================================================
                                 HSE extend OEM security policies
==================================================================================================*/
#ifdef HSE_SPT_OEM_SEC_POLICY

/** @brief    HSE extend OEM security policies attribute definition.
 * @details   Determines whether certain security policies are extended in HSE Firmware or not in OEM_PROD LC.
 *            - Read: Tells which extended security policies are set or not.
 *            - Write:
 *                   - If a given policy is not set to be TRUE, there is no change on security policy extension.
 *                   - If a given policy is set to be TRUE, security policy is extended on successful operation.
 *                   - Write operation is allowed only for users with OEM SU rights in OEM_PROD LC.
 */
typedef struct
{
    bool_t startAsUser;     /**< @brief Host starts with User rights in LC = OEM_PROD.
                                        @note Setting this attribute will take effect only after publishing the SYS Image and issuing a reset. */
    uint8_t reserved[3];    /**< @brief HSE reserved */
} hseAttrExtendOemSecurityPolicy_t;

#endif /* HSE_SPT_OEM_SEC_POLICY */


/*==================================================================================================
                                 Minimal tag bit length for Fast CMAC
==================================================================================================*/
#ifdef HSE_SPT_FAST_CMAC

/** @brief  Minimal tag bit length for Fast CMAC service.
 *  @details By default, the minimal tag bit length that can be used for the Fast CMAC service (see hseFastCMACSrv_t) is 64 bits.
 *           This attribute can be set to be able to use the Fast CMAC service with the tag bit length less than 64 bits.
 *           The value to be set must be provided in bits. */
typedef uint8_t hseAttrFastCmacMinTagBitLen_t;

#endif /* HSE_SPT_FAST_CMAC */


/*==================================================================================================
                                 External Tamper Configuration
==================================================================================================*/
#ifdef HSE_SPT_PHYSICAL_TAMPER_CONFIG

/** @brief    Activate or Deactivate a tamper
 * @details   Tells whether tamper needs to be activated or deactivated.
*/
typedef uint8_t hseTamperConfig_t;
#define HSE_TAMPER_CONFIG_DEACTIVATE        ((hseTamperConfig_t)(0U))            /**< @brief HSE Tamper Deactivate */
#define HSE_TAMPER_CONFIG_ACTIVATE          ((hseTamperConfig_t)(1U))            /**< @brief HSE Tamper Activate */

/** @brief    Tamper Polarity
 * @details   Specifies the polarity to activate the tamper. This configuration is applicable only
 * for passive tamper configuration. User must set the default state of the tamper input pin accordingly on the board.
 * For example: If the tamper polarity is set "ACTIVE_HIGH" then the default state on the tamper input pin must be "ACTIVE LOW".
*/
typedef uint8_t hseTamperPolarity_t;
#define HSE_TAMPER_POL_ACTIVE_LOW           ((hseTamperPolarity_t)(0U))           /**< @brief HSE Tamper Active low polarity*/
#define HSE_TAMPER_POL_ACTIVE_HIGH          ((hseTamperPolarity_t)(1U))           /**< @brief HSE Tamper Active high polarity*/

/** @brief     Filter Duration
  * @details   This macro describes the maximum filter duration that is possible for the physical tamper.
  *            The clock frequency used in the glitch filter is 32 KHz.
  */
#define HSE_FILTER_DURATION_MAX             ((uint32_t)128U)

/** @brief    Tamper routing configuration
 * @details   This configuration defines the type of tamper (i.e. active or passive).
 *  - In case of active tamper, the clock is derived on GPIO pad which should be routed back to
 * the input tamper pin on the ECU. User must configure the alternate functionality of
 * GPIO pin to tamper output so that the clock can be routed on that pin.
 *  - In case of passive tamper, HSE senses the change in polarity of the input pin. In this case, there is
 * no need to configure the active tamper pin. Only external tamper pin should be configured.
 *  - User is recommended to refer the SIUL chapter in SOC reference manual to configure the
 * correct GPIO pin.
 * For some SOC types, only one active tamper can be
 * supported. Please refer to #HSE_NUM_OF_PHYSICAL_TAMPER_INSTANCES to see how many active tamper are supported.
 * @note #HSE_TAMPER_ACTIVE_TWO is not valid for devices - S32G2, S32K3xx
 * */
typedef uint8_t hseOutputPinConfig_t;
#define HSE_TAMPER_PASSIVE                  ((hseOutputPinConfig_t)(0U))
#define HSE_TAMPER_ACTIVE_ONE               ((hseOutputPinConfig_t)(1U))
#define HSE_TAMPER_ACTIVE_TWO               ((hseOutputPinConfig_t)(2U))

/** @brief    Tamper clock that needs to be driven on the tamper output pad
 * @details   Tamper clock that needs to be driven on the tamper output pad.
 *  Please note that the alternate functionality of GPIO pin must be configured
 *  (for the tamper functionality) so that below the mentioned clock can be
 *  driven on that pad. Not applicable for passive tamper configuration
*/
typedef uint8_t hseTamperOutputClock_t;
#define HSE_TAMPER_ACTIVE_CLOCK_16HZ        ((hseTamperOutputClock_t)(0U))
#define HSE_TAMPER_ACTIVE_CLOCK_8HZ         ((hseTamperOutputClock_t)(1U))
#define HSE_TAMPER_ACTIVE_CLOCK_4HZ         ((hseTamperOutputClock_t)(2U))
#define HSE_TAMPER_ACTIVE_CLOCK_2HZ         ((hseTamperOutputClock_t)(3U))

/** @brief    Enables the tamper violation in HSE subsystem for all physical tampers supported by the SOC.
 * @details   This service only enables the  tamper violation in HSE subsystem for all physical tampers supported by the SOC.
 * Once violation is active it cannot be disabled until next reset. <br>
 * Physical tamper feature can be configured in following two ways:
 * 1. Active Tamper Configuration
 * 2. Passive tamper configuration
 *  @note User must configure the GPIO pins for tamper functionality before calling this service; otherwise,
 *        a false violation can be triggered by HSE. User is also recommended to protect the tamper GPIO configuration
 *        using register protection, virtual wrapper and XRDC configuration against further modification by any application running on host side.
 */
typedef struct
{
    hseTamperConfig_t   tamperConfig;               /**< @brief This field indicates the tamper configuration to be enable or not. */

    hseOutputPinConfig_t tamperOutputConfig;        /**< @brief This parameter tells which type (Active or Passive) of input is connected to external tamper input.
                                                            If it is an active input, up to 2 tamper options can be selected as input source for external
                                                            tamper input. Based on the value of this parameter, the clock will be driven on this pad by HSE */

    uint8_t filterDuration;                         /**< @brief Configures the length of the digital glitch filter for the external tamper
                                                            pin between 128 and 32640 SIRC clock cycles. Any assertion on external tamper that is
                                                            equal to or less than the value of the digital glitch filter is ignored.
                                                            The length of the glitches filtered out is:
                                                            -  128 + ((FilterDuration - 1) x 256), where FilterDuration = 1, ... , 128. <br>
                                                            If the FilterDuration value is 0, then the glitch filter will not be enabled.
                                                            Filter Duration is a must requirement for Active Tamper and optional for Passive Tamper. */

    hseTamperPolarity_t tamperPolarity;             /**< @brief This field indicates the polarity of the tamper to be be configured.
                                                            It can be "Active LOW" or "Active HIGH".  This parameter is
                                                            considered only when the tamper source in tamperOutputConfig is selected as passive */

    hseTamperOutputClock_t tamperActiveClock;       /**< @brief Determines the clock to be driven on the output pad of the tamper. This parameter is
                                                            considered only when the tamper source in tamperOutputConfig is selected as active */

    uint8_t reserved[3];                            /**< @brief HSE reserved */
} hseAttrPhysicalTamper_t;

/** @brief    Physical Tamper Configurations.
 * @details   Configures all available physical tamper instances.
 */
typedef struct
{
    hseAttrPhysicalTamper_t tamperInstances[HSE_NUM_OF_PHYSICAL_TAMPER_INSTANCES];   /**< @brief Contains the configuration for all the physical temper interfaces */
} hseAttrPhysicalTamperConfig_t;

#endif /* HSE_SPT_PHYSICAL_TAMPER_CONFIG */

/*==================================================================================================
                                 HSE_APP_SPECIFIC_DATA Attribute
==================================================================================================*/
#ifdef HSE_SPT_APP_SPECIFIC_DATA_ATTR

/** @brief   Application-Specific Data stored in SYS-IMG (persistent memory)
*   @details It can be used to store persistent application data.
*
*   @note
*   - The attribute can be read at any time without any restriction. If the attribute is not set previously,
*     a read request will fail.
*   - If one of the following conditions is met the attribute cannot be set:
*     1. If writing was disabled previously (see #hseDisableAppSpecificDataWrite_t)
*     2. At start-up, when BOOT_SEQ == 1 and the secure boot (SMR or BSB) fails
*     3. If any of the on-demand/runtime SMR specified in smrPeriodicOnDemand flags failed.
*     @note
*     This attribute can be set only having SU rights.
*/
typedef struct
{
    /** @brief     The data to be stored in SYS-IMG.
     *             Note: All bytes must be specified; if some bytes are not used, those can be set zero. */
    uint8_t  specificData[252U];

    /**< @brief    The on-demand or periodic SMR(s) that can be used to restrict
     *             the writing of the attribute; if any of the smrPeriodicOnDemand SMR verification fails, the attribute can not be written.
     *             Note: Set this field to zero if the on-demand or periodic SMR are not used. */
    uint32_t smrPeriodicOnDemand;
}hseAppSpecificData_t;

/** @brief   Disable the writing of Application-Specific Data attribute
*   @details The write of Application-Specific Data attribute can be disabled
*            by setting this attribute as #HSE_CFG_YES.
* @note
*            - When BOOT_SEQ ==1, if the secure boot at start-up and the on-demand or periodic SMR
*              check (configured using #hseAppSpecificData_t service) fails, this attribute is automatically
*              set to #HSE_CFG_YES (application specific data can not be written).
*            - At start-up, the default value of the attribute is #HSE_CFG_NO.
*              The attribute can only be modified from #HSE_CFG_NO to #HSE_CFG_YES,
*              using the set attribute service. The attribute can be set only once,
*              meaning that once the attribute is set to #HSE_CFG_YES, it cannot be
*              set back to #HSE_CFG_NO in the current power cycle.
*/
typedef hseAttrCfg_t hseDisableAppSpecificDataWrite_t;

#endif /* HSE_SPT_APP_SPECIFIC_DATA_ATTR */

/*==================================================================================================
                                 HSE_H/M specific attributes
==================================================================================================*/
#if defined(HSE_SPT_FLASHLESS_DEV)
/*==================================================================================================
                                 HSE-Firmware Size
==================================================================================================*/
/** @brief    HSE-Firmware Size.
 * @details   Size of HSE-Firmware in bytes.
 */
typedef uint32_t hseAttrHseFwSize_t;


/*==================================================================================================
                                 Anti-rollback counter updates left
==================================================================================================*/
/** @brief    Anti-rollback counter updates left.
 * @details   There are available 158 anti-rollback counter updates (fuses) for the key store and HSE firmware.
 *            After 158 updates, the key store and HSE firmware are not protected against rollbacks.
 */
typedef uint32_t hseAvailAntiRollbackCounter_t;


/*==================================================================================================
                                 HSE-Firmware used partition on load
==================================================================================================*/
/** @brief    HSE-Firmware used partition on load.
 * @details   Specified the partition (primary or backup) used by BootRom to load the HSE Firmware.
 */
typedef uint8_t hseAttrFwPartition_t;
#define HSE_FW_PARTITION_PRIMARY        ((hseAttrFwPartition_t)0x1U)           /**< @brief HSE firmware was loaded from primary partition */
#define HSE_FW_PARTITION_BACKUP         ((hseAttrFwPartition_t)0x2U)           /**< @brief HSE firmware was loaded from back-up partition */


/*==================================================================================================
                                 Application debug disable
==================================================================================================*/
/** @brief    Application debug disable.
 * @details   Tells if the Application debug is disabled or not for OEM_PROD and/or IN_FIELD life-cycles.
*/
typedef uint8_t hseAttrDisableAppDebug_t;
#define HSE_APP_DEBUG_DIS_NONE          ((hseAttrDisableAppDebug_t)0x0U)       /**< @brief Application Debug not disabled.
                                                                                    - Read: Application Debug is not disabled for OEM_PROD/ IN_FIELD LC.
                                                                                    Application debug can be opened in OEM_PROD/ IN_FIELD LC using the debug
                                                                                    authorization mechanism.
                                                                                    - Write: Does not disable the application debug. */
#define HSE_APP_DEBUG_DIS_OEM           ((hseAttrDisableAppDebug_t)0x1U)       /**< @brief Application Debug disabled for OEM_PROD LC.
                                                                                    - Read: Application Debug is disabled for OEM_PROD LC.
                                                                                    Application debug can never be opened in OEM_PROD LC.
                                                                                    - Write: Disables application debug for OEM_PROD LC only.
                                                                                    Operation allowed in CUST_DEL, OEM_PROD & IN_FIELD LCs only. */
#define HSE_APP_DEBUG_DIS_FLD           ((hseAttrDisableAppDebug_t)0x2U)       /**< @brief Application Debug disabled for IN_FIELD LC.
                                                                                    - Read: Application Debug is disabled for IN_FIELD LC.
                                                                                    Application debug can never be opened in IN_FIELD LC.
                                                                                    - Write: Disables application debug for IN_FIELD LC only.
                                                                                    Operation allowed in CUST_DEL, OEM_PROD & IN_FIELD LCs only. */
#define HSE_APP_DEBUG_DIS_OEM_FLD       ((hseAttrDisableAppDebug_t)0x3U)       /**< @brief Application Debug disabled for both OEM_PROD & IN_FIELD LCs.
                                                                                    - Read: Application Debug is disabled for both OEM_PROD & IN_FIELD LCs.
                                                                                    Application debug can never be opened in OEM_PROD & IN_FIELD LCs.
                                                                                     -Write: Disables application debug for both OEM_PROD & IN_FIELD LCs.
                                                                                    Operation allowed in CUST_DEL, OEM_PROD & IN_FIELD LCs only. */


/*==================================================================================================
                                 Temperature Sensor violation configuration
==================================================================================================*/
#ifdef HSE_SPT_TEMP_SENS_VIO_CONFIG
/** @brief    Temperature Sensor violation configuration byte.
 * @details   Once the violation is enabled in HSE, it can not be cleared
 *            until next reset. User must configure the Temperature Monitoring Unit (TMU)
 *            before giving the attribute. It can also be configured via DCD configuration.
 *            The HSE Firmware signals an Fatal error (see hseError_t bits) if this tamper is detected.
 *            User is recommended to protect the TMU Registers (see REG_PROT on Soc) after the configuration.
 *            The tamper configuration status is available by reading the HSE_GPR_STATUS_ADDRESS register (refer to #hseTamperConfigStatus_t).
 *            Four TMU Monitors are mapped to HSE: Average High Critical Temperature TMU Monitor,
 *            Average Low Critical Temperature TMU Monitor, Rising Rate Critical Temperature TMU Monitor,
 *            Falling Rate Critical Temperature TMU Monitor.
 *
*/
typedef uint8_t hseTempSensVioConfig_t;
#define HSE_TEMP_SENS_VIO_ACTIVATED       ((hseTempSensVioConfig_t)(0xA5U))  /**< @brief HSE enables the temperature sensor violation in SNVS. */
#define HSE_TEMP_SENS_VIO_DEACTIVATED     ((hseTempSensVioConfig_t)(0x5AU))  /**< @brief HSE disables the temperature sensor violation in SNVS.  */
#endif /* HSE_SPT_TEMP_SENS_VIO_CONFIG */


/*==================================================================================================
                                 OTFAD context status
==================================================================================================*/
#ifdef HSE_SPT_OTFAD
/** @brief   OTFAD context status.
 *  @details After installation of the otfad context, the OTFAD region may be activated or deactivated.
 *           The OTFAD region may be deactivated because the #HSE_OTFAD_CTX_ACTIVE_ON_BOOT flag is not set during
 *           installation or due to a configuration error. */
typedef uint8_t hseOtfadContextStatus_t;
#define HSE_OTFAD_CTX_NOT_INSTALLED       ((hseOtfadContextStatus_t)(0x00U))    /**< @brief OTFAD context not installed. */
#define HSE_OTFAD_CTX_INSTALLED           ((hseOtfadContextStatus_t)(0xCAU))    /**< @brief OTFAD context installed but not configured. */
#define HSE_OTFAD_CTX_ACTIVE              ((hseOtfadContextStatus_t)(0xACU))    /**< @brief OTFAD context configured and active. */
#define HSE_OTFAD_CTX_INACTIVE            ((hseOtfadContextStatus_t)(0xDEU))    /**< @brief OTFAD context configured but not active. */

/** @brief   OTFAD context status.
 *  @details The OTFAD context status for all OTFAD entries. */
typedef struct
{
    hseOtfadContextStatus_t OtfadCtxStatus[HSE_NUM_OF_OTFAD_INSTANCES][HSE_NUM_OF_OTFAD_ENTRIES];   /**< @brief Contains the status for all OTFAD region. */
    #ifdef HSE_SPT_IEE_DDR_FLASH
    hseOtfadContextStatus_t ieeDdrCtxStatus[HSE_NUM_OF_IEE_DDR_ENTRIES];                            /**< @brief Contains the status for all IEE_DDR region. */
    uint8_t                 reserved;
    #endif /* HSE_SPT_IEE_DDR_FLASH */
} hseOtfadCtxStatus_t;
#endif /* HSE_SPT_OTFAD */


/*==================================================================================================
                                OTP Rollback Protection Policy
==================================================================================================*/
/** @brief   Disable the OTP rollback protection when updating the FW Blue Image and/or SYS-IMG.
 *  @details After updating the new FW Blue Image or SYS-IMG (NVM keystore) in external flash, a system reset is needed to update the anti-rollback
 *           counter in OTP area (fuses). To be able to update the fuse counter, the VDD_EFUSE must be always powered or
 *           can be powered at start-up by HSE FW (if the VDD_EFUSE configuration word from IVT is supported; refer to the HSE Firmware Reference Manual).
 *           @note
 *           - Anti-rollback protection on FW-IMG is provided only when it is re-encrypted with a device specific key
 *            (only when the so called FW Blue Image is used).
 *           - SuperUser rights are needed to configure this attribute. */
typedef struct
{
    /** @brief This field controls the rollback protection for FW Blue Image  and/or SYS-IMG update:
     *         - HSE_CFG_NO (default configuration): the OTP rollback protection is enabled.
     *           At boot time, HSE updates the OTP counter (the VDD_EFUSE must be powered).
     *         - HSE_CFG_YES: disable the OTP rollback protection. */
    hseAttrCfg_t disableOtpRollbackProtect;
    /** @brief Prevents the firmware from running if it was loading from a Pink FW Image.
     *         This configuration is ignored for non-secure boot.
     *         - HSE_CFG_NO (default configuration): allow HSE to run if the firmware was loading from a Pink or Blue FW Image.
     *         - HSE_CFG_YES: disallow HSE to run if firmware was loading from a Pink FW Image.
     *           Only the FW Blue Image can be used after setting this field to HSE_CFG_YES.
     *         @note
     *         - Only the Blue FW image provides the rollback protection.
     *         - For secure-boot use case, if disableOtpRollbackProtect == HSE_CFG_YES and the firmware was loaded from PINK FW image ,
     *           HSE performs a function reset; otherwise, it will continue its execution.
     *         - For non-secure boot, this configuration is ignored. */
    hseAttrCfg_t disallowRunningFromPinkFWImage;
} hseOtpRollbackProtectionPolicy_t;

#endif /* HSE_SPT_FLASHLESS_DEV */



/*==================================================================================================
                                 HSE_B specific attributes
==================================================================================================*/
#ifdef HSE_B
/*==================================================================================================
                                 FIRC Divider Configuration
==================================================================================================*/
/** @brief  FIRC Divider Configuration by HSE Firmware from HSE GPR.*/
typedef uint8_t hseFircDivConfig_t;
#define HSE_FIRC_NO_CONFIG                ((hseFircDivConfig_t)0U)       /**< @brief No Configuration. */
#define HSE_FIRC_DIV_BY_1_CONFIG          ((hseFircDivConfig_t)1U)       /**< @brief HSE enables the FIRC divider by 1. */
#define HSE_FIRC_DIV_BY_2_CONFIG          ((hseFircDivConfig_t)2U)       /**< @brief HSE enables the FIRC divider by 2. */
#define HSE_FIRC_DIV_BY_16_CONFIG         ((hseFircDivConfig_t)16U)      /**< @brief HSE enables the FIRC divider by 16. */


/*==================================================================================================
                                 HSE_B Configure Secure Recovery
==================================================================================================*/
/** @brief    Secure Recovery bit.
 * @details   This setting is used by SecureBAF/HSE Firmware to check whether the firmware enters in the Secure Recovery state or not.
*/
typedef uint8_t hseAttrConfigSecureRecovery_t;
#define HSE_SECURE_RECOVERY_DISABLE             ((hseAttrConfigSecureRecovery_t)0x0U)            /**< @brief
                                                                                                  * - Secure Recovery is disabled by HSE Firmware.
                                                                                                  * - Write: It does not affect the value at all.
                                                                                                  */

#define HSE_SECURE_RECOVERY_ENABLE              ((hseAttrConfigSecureRecovery_t)0x1U)            /**< @brief
                                                                                                  * - Secure Recovery is enabled by HSE Firmware.
                                                                                                  * - Write: It enables the Secure Recovery mode.
                                                                                                  */


/*==================================================================================================
                                 HSE_B Publish NVM Keystore RAM to FLASH
==================================================================================================*/
#if defined(HSE_SPT_PUBLISH_NVM_KEYSTORE_RAM_TO_FLASH)

/** @brief HSE Publish NVM Keystore RAM to Flash
* @details This service can be used to reduce the number of write operations in the data flash, and increase the performance when the key store is updated.
* At start-up, the HSE FW loads the NVM key from data flash into the secure RAM (NVM keys are mirrored in RAM).
* After loading, the NVM keys are used only from RAM memory. At key update/erase, both the mirrored RAM area and the data flash for the keys are updated.
*
* - By default, the attribute is set to #HSE_CFG_NO; this means that during key import (or load key) service,
* HSE updates the NVM keys to both the mirrored RAM area and the data flash.
* - By setting this attribute to #HSE_CFG_YES, the HSE FW will update the NVM keys only in the mirror RAM memory.
* To perform the flash write operation, the application must call the #HSE_SRV_ID_PUBLISH_NVM_KEYSTORE_RAM_TO_FLASH service.
*
* @note
* This attribute is available in Cust-Del and Oem-Prod LC only.
*/
typedef hseAttrCfg_t hsePublishNvmKeystoreRamtToFlash_t;

#endif /* defined(HSE_SPT_PUBLISH_NVM_KEYSTORE_RAM_TO_FLASH) */

#endif /* HSE_B */


/*==================================================================================================
                                 RESET_SOC_ON_TAMPER Attribute
==================================================================================================*/
#ifdef HSE_SPT_RESET_SOC_ON_TAMPER_ATTR

/** @brief   HSE Reset Soc on tamper detection.
 *  @details By default HSE does not reset the Soc on tamper detection (this attribute is configured as #HSE_CFG_NO),
 *           Instead it signals an HSE error (see #hseError_t) and enter shutdown mode.
 *           To reset the Soc, the host application must set this attribute to #HSE_CFG_YES and publish SYS-IMG.
 *           On next boot, HSE configures the attribute.
 *  @note
 *  The Application must have SU rights to configure this attribute.*/
typedef hseAttrCfg_t hseResetSocOnTamper_t;

#endif /* HSE_SPT_RESET_SOC_ON_TAMPER_ATTR */

/** @} */

/*==================================================================================================
                                 STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/
/** @brief HSE Cancel service.
 *  @details This service cancels a HSE one-pass and streaming service that was sent on a specific channel.
 *
 * @note
 *      - The requests with the service ID that starts with 0x00A5XXXX can not be canceled.
 *      - Cancel requests cannot be canceled (by a subsequent request);
 */
typedef struct
{
    /** @brief   INPUT: The channel Index of MU interface [0..#HSE_NUM_OF_CHANNELS_PER_MU). <br>
     *                  The muChannelIdx and the MU channel on which the service is sent, must belong to
     *                  the same MU Interface. Otherwise an #HSE_SRV_RSP_INVALID_PARAM error will be reported. */
    uint8_t  muChannelIdx;
    uint8_t  reserved[3];
} hseCancelSrv_t;

#ifdef HSE_SPT_STREAM_CTX_IMPORT_EXPORT

/** @brief   The maximum size of the streaming context. */
#define MAX_STREAMING_CONTEXT_SIZE      (372UL)

/** @brief   Streaming Context Operation: Import/Export. */
typedef uint8_t hseStreamContextOp_t;
#define HSE_IMPORT_STREAMING_CONTEXT    ((hseStreamContextOp_t)1U)    /**< @brief Import streaming context */
#define HSE_EXPORT_STREAMING_CONTEXT    ((hseStreamContextOp_t)2U)    /**< @brief Export streaming context */

/** @brief   HSE Import/Export Streaming Context service.
 *  @details This service allows import/export of a streaming context used in an on-going streaming operation (e.g. Hash, MAC, Cipher, AEAD, etc). <br>
 *           The streaming context will be imported/exported as a blob (encrypted with a device specific key).
 */
typedef struct
{
    /** @brief   INPUT: Specifies the operation to be performed with the streaming context: Import/Export. */
    hseStreamContextOp_t    operation;
    /** @brief   INPUT: Specifies the stream to be exported or overwritten if imported. Note that each interface supports
     *                  up to #HSE_STREAM_COUNT streams per interface. */
    hseStreamId_t           streamId;
    uint8_t                 reserved[2];
    /** @brief   OUTPUT/INPUT: The output buffer where the streaming context will be copied (export) or
     *                         the input buffer from which HSE will copy the streaming context (import).
     *                         Length of the buffer should be at least #MAX_STREAMING_CONTEXT_SIZE bytes.
     *                         A streaming context can be imported or exported on the same MU instance on which the streaming START step was called
     *                         (e.g. the steaming context is allocated when the START step is called)."*/
    HOST_ADDR               pStreamContext;
} hseImportExportStreamCtxSrv_t;

#endif /* HSE_SPT_STREAM_CTX_IMPORT_EXPORT */

/**
 * @brief    Prepare the security subsytem (BootROM + HSE) for Stand-By.
 * @details  This service is used for updating the internal state of HSE before system goes in Stand-By mode.
 *           Applicable only for flashless devices (HSE_H/M variants).
 *           This service can be called only once per running state, otherwise HSE will return #HSE_SRV_RSP_NOT_ALLOWED.
 */
#if defined(HSE_SPT_FLASHLESS_DEV)
typedef struct
{
    uint8_t          reserved[4U];
} hsePrepareForStandBySrv_t;
#endif /* HSE_SPT_FLASHLESS_DEV */

#ifdef HSE_SPT_INTERNAL_FLASH_DEV
/**
 * @brief    Erase SYS-IMG in Data Flash.
 * @details  This service is used for erasing SYS-IMG in HSE Data Flash.
 *           The service is available for flash based devices only (HSE_B variant).
 *           Can be performed only in CUST_DEL life cycle, otherwise #HSE_SRV_RSP_NOT_ALLOWED error will be reported.
 */
typedef struct
{
    uint8_t          reserved[4];
} hseEraseNvmDataSrv_t;
#endif /* HSE_SPT_INTERNAL_FLASH_DEV */

#ifdef HSE_SPT_ERASE_FW
/**
 * @brief    Erase HSE Firmware from the device.
 * @details  This service is used for erasing the HSE Firmware.
 *           This service also erases the SYS-IMG and backup (if present) in the secure flash from the device.
 *           The service is available for flash based devices only (HSE_B variant).
 *           Can be performed only in CUST_DEL life cycle, otherwise #HSE_SRV_RSP_NOT_ALLOWED error will be reported.
 */
typedef struct
{
    uint8_t          reserved[4];
} hseEraseFwSrv_t;
#endif /* HSE_SPT_ERASE_FW */

#ifdef HSE_SPT_TRIM_PASSWORD_PROVISION
/** @brief A 32 bytes array that represents the trim password value. */
typedef uint8_t hseTrimPassword_t[32];

/**
 * @brief    Provide a password to enable read access of certain system fusemap.
 * @details  If the trim password is valid the HSE shall enable the read for system fuses that can not be read by default by customer.
 *           The customer shall contact NXP to receive the trim password.
 *           After reset, the read for system fuses should be enabled again by providing the same trim password.
 */
typedef struct
{
    /** @brief   INPUT: Specifies the trim password address. The trim password has a length of 32 bytes. */
    HOST_ADDR   pTrimPw;
} hseTrimPasswordProvision_t;
#endif /* HSE_SPT_TRIM_PASSWORD_PROVISION */
/** @} */

/*==================================================================================================
*                                      DEFINES AND MACROS
==================================================================================================*/

/** @brief HSE RNG classes.
 *
    @note  Additional entropy (personalization string) is not needed to be provide by user.
           The entropy generated by the TRNG already ensures this with high probability. */
typedef uint8_t hseRngClass_t;

/** @brief DRG.3 class uses the RNG engine with prediction resistance disabled.
 *         This is the most efficient class in terms of performance. */
#define HSE_RNG_CLASS_DRG3 ((hseRngClass_t)0U)
/** @brief DRG.4 (AIS-20/SP800-90A) class uses the RNG engine with  prediction resistance enabled.
 *         Using the prediction resistance will impact the performance, as every
 *         call to Get Random invokes reseed internally. */
#define HSE_RNG_CLASS_DRG4 ((hseRngClass_t)1U)
/** @brief PTG.3 (AIS 31/SP800-90B) class uses the RNG engine with prediction resistance enabled
 *         and will reseed for each 16 bytes of data.
 *         This is the most costly class in terms of performance. */
#define HSE_RNG_CLASS_PTG3 ((hseRngClass_t)2U)

/*==================================================================================================
*                                             ENUMS
==================================================================================================*/

/*==================================================================================================
                                 STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/
/** @brief Get random number service.
 *  @note When the HSE_STATUS_RNG_INIT_OK status flag is cleared (failed), the call of any service
 *        that requires a random number (e.g. Get Random Number, ECDSA signature generate etc.)
 *        triggers a RNG re-initialization before requesting the random number.
 *        If the RNG re-initialization is executed successfully, the HSE_STATUS_RNG_INIT_OK status flag is set to 1.
 * */
typedef struct
{
    /** @brief   INPUT: The RNG class. */
    hseRngClass_t           rngClass;
    uint8_t                 reserved[3];
    /** @brief   INPUT: Length of the generated random number in bytes. The maximum value for one request is 512 bytes. */
    uint32_t                randomNumLength;
    /** @brief   OUTPUT: The address where the random number will be stored. */
    HOST_ADDR               pRandomNum;
} hseGetRandomNumSrv_t;

/** @} */

/*==================================================================================================
                                 STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/

/**
* @brief          MAC service.
* @details        MAC algorithms are symmetric key cryptographic techniques to provide
*                 message authentication codes (MACs), also known as tags.
*                 These can be used to verify both the integrity and authenticity of a message.

*                 This service can be accessible in one-pass or streaming (SUF) mode.
*                 In case of streaming mode, three steps (calls) will be used: START, UPDATE, FINISH.
*                 START and FINISH are mandatory; UPDATE is optional.
*                 Not all fields are used by each access mode.
*
*  The table below summarizes which fields are used by each access mode.
*  Unused fields are ignored by the HSE.
*
* |Field \ Mode      | One-pass  | Start | Update  | Finish  |
* |-----------------:|:---------:|:-----:|:-------:|:-------:|
* | accessMode       |     *     |   *   |    *    |    *    |
* | streamId         |     *     |   *   |    *    |    *    |
* | authDir          |     *     |   *   |         |         |
* | sgtOption        |     *     |   *   |    *    |    *    |
* | macScheme        |     *     |   *   |         |         |
* | keyHandle        |     *     |   *   |         |         |
* | inputLength      |     *     |   *   |    *    |    *    |
* | pInput           |     *     |   *   |    *    |    *    |
* | pTagLength       |     *     |       |         |    *    |
* | pTag             |     *     |       |         |    *    |
*/
typedef struct
{
    /** @brief   INPUT: Specifies the access mode: ONE-PASS, START, UPDATE, FINISH. <br>
     *           STREAMING USAGE: Used in all steps.*/
    hseAccessMode_t accessMode;

    /** @brief   INPUT: Specifies the stream to use for START, UPDATE, FINISH access modes. Each interface supports
     *           a limited number of streams per interface, up to #HSE_STREAM_COUNT. <br>
     *           STREAMING USAGE: Used in all steps.*/
    hseStreamId_t   streamId;

    /** @brief   INPUT: Specifies the direction: generate/verify. <br>
     *           STREAMING USAGE: Used in START.*/
    hseAuthDir_t    authDir;

    /** @brief  INPUT: Specify if pInput is provided as hseScatterList_t list (the host address points to a hseScatterList_t list).
     *                 Ignored if SGT is not supported.
     *                 @note
     *                 - For HSE_B devices, the SGT for the HMAC scheme is not available for the following hash algorithms (the parameter is ignored):
     *                      - SHA2_384/512 (not available in HW)
     *                 - ONLY HSE_SGT_OPTION_INPUT can be used.
     *                 - If scatter option is selected (set), the length (e.g. #inputLength) shall specified the entire message length
     *                 (sum of all hseScatterList_t lengths).
     *                 - The number for SGT entries shall be less then #HSE_MAX_NUM_OF_SGT_ENTRIES.<br>
     *           STREAMING USAGE: Used in all steps.*/
    hseSGTOption_t   sgtOption;

    /** @brief   INPUT: Specifies the MAC scheme. <br>
     *           STREAMING USAGE: Used in START.*/
    hseMacScheme_t  macScheme;

    /** @brief   INPUT: The key to be used for the operation.
     *           STREAMING USAGE: Used in START.*/
    hseKeyHandle_t  keyHandle;

    /** @brief   INPUT: Length of the input message. Can be zero. <br>
     *           STREAMING USAGE: Used in all steps.
     *            - START: Must be a multiple of block length (for HMAC-hash or AES), or zero. Cannot be zero for HMAC.
     *            - UPDATE: Must be a multiple of block length (for HMAC-hash or AES). Cannot be zero.
     *                  Refrain from issuing the service request, instead of passing zero.
     *            - FINISH: Can be any value (For CMAC & XCBC-MAC, zero length is invalid).
     *
     *           Algorithm block lengths (for STREAMING USAGE):
     *            - CMAC, GMAC, XCBC-MAC: 16
     *            - HMAC, depends on underlying hash:
     *                - SHA1, SHA2_224, SHA2_256: 64
     *                - SHA2_512_224, SHA2_512_256, SHA2_384, SHA2_512: 128
     *                - SHA3: not supported for HMAC
     *                - Miyaguchi-Preneel: not supported for HMAC */
    uint32_t        inputLength;

    /** @brief   INPUT: The input message.
     *           @note The input message for GMAC is the AAD (as specified by AEAD-GCM).
     *
     *           STREAMING USAGE: Used in all steps, but ignored when #inputLength is zero */
    HOST_ADDR       pInput;

    /** @brief   INPUT/OUTPUT: Holds the address to a memory location (an uint32_t variable) in which the tag length in bytes is stored.
     *                         - GENERATE:
     *                           - On calling service (input), this parameter shall contain the size of the buffer provided by #pTag.
     *                           - For GMAC, valid tag lengths are 8, 12, 13, 14, 15 and 16. Tag-lengths greater than 16 will be truncated to 16.
     *                           - For HMAC, valid tag lengths are [8, hash-length]. Tag-lengths greater than hash-length will be truncated to hash-length.
     *                           - For CMAC & XCBC-MAC, valid tag lengths are [8, cipher-block-length]. Tag-lengths greater than cipher-block-length will be
     *                             truncated to cipher-block-length.
     *                           - When the request has finished (output), the actual length of the returned value shall be stored.
     *                         - VERIFY:
     *                           - On calling service (input), this parameter shall contain the tag-length to be verified.
     *                           - For GMAC, valid tag lengths are 8, 12, 13, 14, 15 and 16.
     *                           - For HMAC, valid tag lengths are [8, hash-length].
     *                           - For CMAC & XCBC-MAC, valid tag lengths are [8, cipher block-length].
     *
     *           STREAMING USAGE: Used in FINISH. */
    HOST_ADDR     pTagLength;

    /** @brief   OUTPUT/INPUT: The output tag for "generate"; the input tag for "verify". <br>
     *           STREAMING USAGE: Used in FINISH.*/
    HOST_ADDR     pTag;
} hseMacSrv_t;

/**
 * @brief          Fast CMAC service.
 * @details        CMAC algorithms are symmetric key cryptographic techniques to provide
 *                 message authentication codes (MACs), also known as tags.
 *                 These can be used to verify both the integrity and authenticity of a message.
 *
 *                 This FAST CMAC version can provide improved performance for CAN frames and compared
 *                 to the other MAC implementation is using bits representation for #pInput and #pTag.
 *                 @note Bits are represented from left to right at byte level.
 */
typedef struct
{
    /** @brief   INPUT: The key to be used for the operation. */
    hseKeyHandle_t keyHandle;

    /** @brief   INPUT: The input message. */
    HOST_ADDR      pInput;

    /** @brief   INPUT: Length of the input message.(in bits) */
    uint32_t       inputBitLength;

    /** @brief   INPUT: Specifies the direction: generate/verify. */
    hseAuthDir_t   authDir;

    /** @brief   INPUT/OUTPUT: Holds tag length in bits.
     *           - GENERATE:
     *             - On calling service (input), this parameter shall contain the size of the buffer provided by #pTag.
     *             - Recommended tag lengths are [32, 128]. Tag-lengths greater than 128 will be truncated to 128.
     *           - VERIFY:
     *             - On calling service (input), this parameter shall contain the tag-length to be verified.
     *             - Recommended tag lengths are [32, 128].
     *             - The #HSE_FAST_CMAC_MIN_TAG_BIT_LEN_ATTR_ID attribute can be used to overwrite
     *               the lower recommended tag bit length limit (minimum is 1).
     */
    uint8_t        tagBitLength;

    uint8_t        reserved[2];

    /** @brief   OUTPUT/INPUT: The output tag for "generate"; the input tag for "verify". */
    HOST_ADDR      pTag;

} hseFastCMACSrv_t;

/** @} */

/*==================================================================================================
                                 STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/

/**
* @brief          Symmetric Cipher service.
* @details        To perform encryption/decryption with a block cipher in ECB or CBC mode, the length of the input must
*                 be an exact multiple of the block size. For all AES variants it is 16 bytes (128 bits). If the input plaintext
*                 is not an exact multiple of block size, it must be padded by application (by adding a padding string).
*                 For other modes, such as counter mode (CTR) or OFB or CFB, padding is not required.
*                 In these cases, the ciphertext is always the same length as the plaintext.
*                 If the plaintext is always an exact multiple of the block length, padding can be avoided.
*
*                 This service can be accessible in one-pass or streaming (SUF) mode.
*                 In case of streaming mode, three steps (calls) will be used: START, UPDATE, FINISH.
*                 START and FINISH are mandatory; UPDATE is optional.
*                 Not all fields are used by each access mode.
*
*  The table below summarizes which fields are used by each access mode.
*  Unused fields are ignored by the HSE.
*
* |Field \ Mode      | One-pass  | Start | Update  | Finish  |
* |-----------------:|:---------:|:-----:|:-------:|:-------:|
* | accessMode       |     *     |   *   |    *    |    *    |
* | streamId         |           |   *   |    *    |    *    |
* | cipherAlgo       |     *     |   *   |         |         |
* | cipherBlockMode  |     *     |   *   |         |         |
* | cipherDir        |     *     |   *   |         |         |
* | sgtOption        |     *     |   *   |    *    |     *   |
* | keyHandle        |     *     |   *   |         |         |
* | pIV              |     *     |   *   |         |         |
* | inputLength      |     *     |   *   |    *    |    *    |
* | pInput           |     *     |   *   |    *    |    *    |
* | pOutput          |     *     |   *   |    *    |    *    |
*/
typedef struct
{
    /** @brief   INPUT: Specifies the access mode: ONE-PASS, START, UPDATE, FINISH. <br>
     *           STREAMING USAGE: Used in all steps.*/
    hseAccessMode_t  accessMode;

    /** @brief   INPUT: Specifies the stream to use for START, UPDATE, FINISH access modes. Each interface supports
    *           a limited number of streams per interface, up to #HSE_STREAM_COUNT. <br>
    *           STREAMING USAGE: Used in all steps.*/
    hseStreamId_t    streamId;

    /** @brief   INPUT: Specifies the cipher algorithm . <br>
     *           STREAMING USAGE: Used in START.*/
    hseCipherAlgo_t  cipherAlgo;

    /** @brief   INPUT: Specifies the cipher mode. <br>
     *           STREAMING USAGE: Used in START.*/
    hseCipherBlockMode_t  cipherBlockMode;

    /** @brief   INPUT: Specifies the cipher direction: encryption/decryption. <br>
     *           STREAMING USAGE: Used in START.*/
    hseCipherDir_t   cipherDir;

    /** @brief  INPUT: Specify if pInput/pOutput are provided as hseScatterList_t list (the host address points to a hseScatterList_t list).
     *                 Ignored if SGT is not supported.
     *                 @note
     *                 - If scatter option is selected (set), the length (e.g. #inputLength) shall specified the entire message length
     *                   (sum of all hseScatterList_t lengths).
     *                 - The number for SGT entries shall be less then #HSE_MAX_NUM_OF_SGT_ENTRIES. <br>
     *           STREAMING USAGE: Used in all steps.*/
    hseSGTOption_t   sgtOption;

    uint8_t          reserved[2];

    /** @brief   INPUT: The key to be used for the operation. <br>
     *           STREAMING USAGE: Used in START step. */
    hseKeyHandle_t   keyHandle;

    /** @brief   INPUT: Initialization Vector/Nonce. Ignored for NULL & ECB cipher block modes. <br>
     *                  IV length is 16 bytes. (AES cipher block size). <br>
     *           STREAMING USAGE: Used in START.*/
    HOST_ADDR        pIV;

    /** @brief   INPUT: The plaintext and ciphertext length. For ECB, CBC & CFB cipher block modes,
     *                  must be a multiple of block length. Cannot be zero. <br>
     *           STREAMING USAGE: MANDATORY for all steps.<br>
     *            - START: Must be a multiple of block length. Can be zero.
     *            - UPDATE: Must be a multiple of block length. Cannot be zero. Refrain from issuing the service request, instead of passing zero.
     *            - FINISH: For ECB, CBC & CFB cipher block modes, must be a multiple of block length. Cannot be zero.
     *                     For remaining cipher block modes, can be any value except zero.
     *
     *           AES block lengths: 16 */
    uint32_t         inputLength;

    /** @brief   INPUT: The plaintext for encryption or the ciphertext for decryption. <br>
     *           STREAMING USAGE: Used in START, UPDATE and FINISH. Ignored in START if #inputLength is zero. */
    HOST_ADDR        pInput;

    /** @brief   OUTPUT: The plaintext for decryption or ciphertext for encryption. <br>
     *           STREAMING USAGE: Used in START, UPDATE and FINISH. Ignored in START if #inputLength is zero. */
    HOST_ADDR        pOutput;

} hseSymCipherSrv_t;


#ifdef HSE_SPT_XTS_AES
/**
* @brief       XTS AES Cipher service.
* @details     To perform XTS AES encryption/decryption.
*              @note
*              ONLY AES128 and AES256 keys shall be used.
*/
typedef struct
{
    /** @brief   INPUT: Specifies the cipher direction: encryption/decryption. */
    hseCipherDir_t   cipherDir;
    uint8_t          reserved0[3];
    /** @brief   INPUT: The key to be used for the operation.
     *           @note The cipher key must have the encryption or decryption usage flags set, depending on
     *                 the desired operations. */
    hseKeyHandle_t   cipherKeyHandle;
    /** @brief   INPUT: The XTS Tweak key.
     *           @note The XTS Tweak key must always and only have the #HSE_KF_USAGE_XTS_TWEAK flag set, as it is used internally to
     *                 encrypt the tweak value during both the encryption and the decryption operations.*/
    hseKeyHandle_t   tweakKeyHandle;
    /** @brief   INPUT: The sector number. */
    uint64_t         sectorNumber;
    /** @brief   INPUT: Sector size. Must be a multiple of 16 bytes. */
    uint16_t         sectorSize;
    /** @brief  INPUT: Specify if pInput/pOutput are provided as hseScatterList_t list (the host address points to a hseScatterList_t list).
     *                 @note
     *                 - If scatter option is selected (set), the length (e.g. #inputLength) shall specified the entire message length
     *                   (sum of all hseScatterList_t lengths).
     *                 - The number for SGT entries shall be less than #HSE_MAX_NUM_OF_SGT_ENTRIES. <br>*/
    hseSGTOption_t   sgtOption;
    uint8_t          reserved1;
    /** @brief   INPUT: The plaintext and ciphertext length. Must be above or equal to 16. */
    uint32_t         inputLength;
    /** @brief   INPUT: The plaintext for encryption or the ciphertext for decryption. */
    HOST_ADDR        pInput;
    /** @brief   OUTPUT: The plaintext for decryption or ciphertext for encryption. */
    HOST_ADDR        pOutput;
} hseXtsAesCipherSrv_t;
#endif /* HSE_SPT_XTS_AES*/


/*==================================================================================================
*                                      DEFINES AND MACROS
==================================================================================================*/
/** @brief   HSE key catalog type.
 *  @details A key catalog is a memory container that holds groups of keys.
 *           The catalog defines the type of storage (volatile / non-volatile) and the visibility to the application (host) */
typedef uint8_t hseKeyCatalogId_t;
#define HSE_KEY_CATALOG_ID_ROM        ((hseKeyCatalogId_t)0U)    /**< @brief ROM key catalog (NXP keys) */
#define HSE_KEY_CATALOG_ID_NVM        ((hseKeyCatalogId_t)1U)    /**< @brief NVM key catalog */
#define HSE_KEY_CATALOG_ID_RAM        ((hseKeyCatalogId_t)2U)    /**< @brief RAM key catalog */

/** @brief All keys used in cryptographic operations are referenced by a unique key handle.
 *         The key handle is a 32-bit integer: the key catalog(byte2), group index in catalog (byte1) and key slot index (byte0).
 *         It can be retrieved  based on the catalog ID, the group index and its slot index within the group.
 *         The group index is between 0 and (n-1), where n is the maximum number of groups defined in the catalog
 *         The slot index is between 0 and (p-1), where p is the maximum number of keys defined in the group */
#define GET_KEY_HANDLE(catalogId, groupIdx, slotIdx) \
                      ((((hseKeyHandle_t)((hseKeyCatalogId_t)(catalogId))) << 16U) | \
                       (((hseKeyHandle_t)((hseKeyGroupIdx_t)(groupIdx))) << 8U) | \
                       (((hseKeyHandle_t)((hseKeySlotIdx_t)(slotIdx)))))

#define GET_CATALOG_ID(keyHandle)     ((hseKeyCatalogId_t)((keyHandle) >> 16U)) /**< @brief Get key catalog Id. */
#define GET_GROUP_IDX(keyHandle)      ((hseKeyGroupIdx_t)((keyHandle) >> 8U))   /**< @brief Get key group index. */
#define GET_SLOT_IDX(keyHandle)       ((hseKeySlotIdx_t)(keyHandle))            /**< @brief Get key slot index. */

#define HSE_INVALID_KEY_HANDLE        ((hseKeyHandle_t)0xFFFFFFFFUL)   /**< @brief HSE invalid key . */
#define HSE_INVALID_GROUP_IDX         ((hseKeyGroupIdx_t)0xFFU)        /**< @brief HSE invalid key group index. */
#define HSE_INVALID_SLOT_IDX          ((hseKeySlotIdx_t)0xFFU)         /**< @brief HSE invalid key slot index. */


/** @brief HSE Key Group owner */
typedef uint8_t hseKeyGroupOwner_t;

/** @brief The key are owned by ANY owner. This applies only for RAM key groups.
 *         The RAM keys can be installed/updated by any owner (CUST or OEM) having SuperUser or User rights. */
#define HSE_KEY_OWNER_ANY             ((hseKeyGroupOwner_t)0U)

/** @brief The key are owned by OWNER_CUST. This applies only for NVM key groups. <br>
 *         The CUST keys can be installed/updated as follow:
 *          - using CUST SuperUser rights (if Life Cycle = CUST_DEL or if the host was granted with CUST SuperUser rights).
 *          - using User rights (Life Cycle = IN_FIELD) */
#define HSE_KEY_OWNER_CUST            ((hseKeyGroupOwner_t)1U)

/** @brief The key groups owned by OWNER_OEM. This applies only for NVM key groups. <br>
 *         The OEM keys can be installed/updated as follow:
 *          - using OEM SuperUser rights (if Life Cycle = OEM_PROD or if the host was granted with OEM SuperUser rights).
 *          - using User rights (Life Cycle = IN_FIELD) */
#define HSE_KEY_OWNER_OEM             ((hseKeyGroupOwner_t)2U)

/** @brief HSE Key type.
  *       Specifies the Key type. It provides information about the interpretation of key data. */
typedef uint8_t hseKeyType_t;
#define HSE_KEY_TYPE_SHE              ((hseKeyType_t)0x11U)            /**< @brief Symmetric AES128 key used with SHE specification commands.
                                                                                 It can be used with any AES block ciphering mode and AES MACs (same as any AES128 key). */
#define HSE_KEY_TYPE_AES              ((hseKeyType_t)0x12U)            /**< @brief Symmetric AES key or AES OTFAD key */
#define HSE_KEY_TYPE_HMAC             ((hseKeyType_t)0x20U)            /**< @brief Symmetric HMAC key */
#define HSE_KEY_TYPE_SHARED_SECRET    ((hseKeyType_t)0x30U)            /**< @brief Shared secret used by DH key exchange protocols */
#define HSE_KEY_TYPE_SIPHASH          ((hseKeyType_t)0x40U)            /**< @brief Symmetric SipHash key */
#define HSE_KEY_TYPE_ECC_PAIR         ((hseKeyType_t)0x87U)            /**< @brief ECC key pair (private and public) */
#define HSE_KEY_TYPE_ECC_PUB          ((hseKeyType_t)0x88U)            /**< @brief ECC Public key */
#define HSE_KEY_TYPE_ECC_PUB_EXT      ((hseKeyType_t)0x89U)            /**< @brief ECC public keys, where the key value is stored in the application area (e.g. certificate) */
#define HSE_KEY_TYPE_RSA_PAIR         ((hseKeyType_t)0x97U)            /**< @brief RSA key pair (private and public key) */
#define HSE_KEY_TYPE_RSA_PUB          ((hseKeyType_t)0x98U)            /**< @brief RSA Public key */
#define HSE_KEY_TYPE_RSA_PUB_EXT      ((hseKeyType_t)0x99U)            /**< @brief RSA public keys, where the key value is stored in the application area (e.g. certificate) */
#define HSE_KEY_TYPE_DH_PAIR          ((hseKeyType_t)0xA7U)            /**< @brief DH key pair */
#define HSE_KEY_TYPE_DH_PUB           ((hseKeyType_t)0xA8U)            /**< @brief DH public key */


/** @brief    The key flags specifies the operations or restrictions that can be apply to a key. */
typedef uint16_t hseKeyFlags_t;
#define HSE_KF_USAGE_ENCRYPT          ((hseKeyFlags_t)1U << 0U)     /**< @brief Key is used to encrypt data (including keys if HSE_KF_USAGE_KEY_PROVISION is set). */
#define HSE_KF_USAGE_DECRYPT          ((hseKeyFlags_t)1U << 1U)     /**< @brief Key is used to decrypt data (including keys if HSE_KF_USAGE_KEY_PROVISION is set). */
#define HSE_KF_USAGE_SIGN             ((hseKeyFlags_t)1U << 2U)     /**< @brief Key is used to generate digital signatures or MACs of any data
                                                                     *          (including keys if HSE_KF_USAGE_KEY_PROVISION is set).*/
#define HSE_KF_USAGE_VERIFY           ((hseKeyFlags_t)1U << 3U)     /**< @brief Key is used to verify digital signatures or MACs of any data
                                                                     *          (including keys if HSE_KF_USAGE_KEY_PROVISION is set).*/
#define HSE_KF_USAGE_EXCHANGE         ((hseKeyFlags_t)1U << 4U)     /**< @brief Key is used for key exchange protocol (e.g. DH).*/
#define HSE_KF_USAGE_DERIVE           ((hseKeyFlags_t)1U << 5U)     /**< @brief Key may be use as a base key for deriving other keys. */
#define HSE_KF_USAGE_KEY_PROVISION    ((hseKeyFlags_t)1U << 6U)     /**< @brief Key used for key provisioning operation. The provision keys can only be NVM keys.
                                                                     *          This bit (if it is set) along with the encrypt/decrypt/sign/verify flags
                                                                     *           specifies which operations can be performed on a key using this key (provisioning key). */
#define HSE_KF_USAGE_AUTHORIZATION    ((hseKeyFlags_t)1U << 7U)     /**< @brief Key can be used for system authorization. Can be set only for NVM keys.
                                                                     *          This key should have the verify flag set, but the sign flag NOT set. */
#define HSE_KF_USAGE_SMR_DECRYPT      ((hseKeyFlags_t)1U << 8U)     /**< @brief The key is used for SMR decryption. If this bit is set during key installation, the HSE will set the HSE_KF_USAGE_DECRYPT flag to zero. */
#define HSE_KF_ACCESS_WRITE_PROT      ((hseKeyFlags_t)1U << 9U)     /**< @brief The key is write protected and cannot change anymore. For RAM keys, this flag is forced to zero. */
#define HSE_KF_ACCESS_DEBUG_PROT      ((hseKeyFlags_t)1U << 10U)    /**< @brief The key is disabled when a debugger is attached. For RAM keys, this flag is forced to zero. */
#define HSE_KF_ACCESS_EXPORTABLE      ((hseKeyFlags_t)1U << 11U)    /**< @brief The key can be exported or not in any format. Ignored when used in combination with
                                                                    *          HSE_KF_USAGE_KEY_PROVISION or HSE_KF_USAGE_AUTHORIZATION (provision/authorization keys are NOT exportable). */
#define HSE_KF_USAGE_XTS_TWEAK        ((hseKeyFlags_t)1U << 12U)    /**< @brief This is used as a tweak key in xts aes encryption; no other flag shall be set */
#define HSE_KF_USAGE_OTFAD_DECRYPT    ((hseKeyFlags_t)1U << 13U)    /**< @brief The key is used just in OTFAD decryption; no other flag shall be set*/

/** @brief    The Key Usage flags mask. */
#define HSE_KF_USAGE_MASK   \
       (HSE_KF_USAGE_ENCRYPT | HSE_KF_USAGE_DECRYPT | HSE_KF_USAGE_SIGN | HSE_KF_USAGE_VERIFY | HSE_KF_USAGE_EXCHANGE | \
        HSE_KF_USAGE_DERIVE | HSE_KF_USAGE_KEY_PROVISION | HSE_KF_USAGE_AUTHORIZATION | HSE_KF_USAGE_SMR_DECRYPT |      \
        HSE_KF_USAGE_XTS_TWEAK | HSE_KF_USAGE_OTFAD_DECRYPT)

/** @brief    The Key Access flags mask. */
#define HSE_KF_ACCESS_MASK  (HSE_KF_ACCESS_WRITE_PROT | HSE_KF_ACCESS_DEBUG_PROT | HSE_KF_ACCESS_EXPORTABLE)

/** @brief    The maximum value of key counter. Note that 0xFFFFFFFF is reserved for RAM keys. */
#define HSE_KF_MAX_KEY_COUNTER_VALUE    ((uint32_t)0xFFFFFFFFUL - 1UL)

/**  HSE ROM key handles.
  *  The ROM key catalog references keys that are provisioned by NXP and can be used by the host.
  *
  *  @note
  *       - The ROM keys have the following access restriction flags set:
  *      \code
  *
  *             (#HSE_KF_ACCESS_WRITE_PROT | #HSE_KF_ACCESS_DEBUG_PROT)
  *
  *      \endcode
  */

/** @brief  This key can be used for data encryption/decryption, having the following usage restrictions:
 *  @note
 *        - This key is a device-specific secret
 *        - This key can be used to encrypt/decrypt application data with a device-specific key
 * \code
 *
 * (#HSE_KF_USAGE_ENCRYPT | #HSE_KF_USAGE_DECRYPT)
 *
 * \endcode */
#define HSE_ROM_KEY_AES256_KEY0       ((hseKeyHandle_t)0x00000000UL)

/** @brief This key can be used for key derivation and key provisioning, having the following usage restrictions:
 *  @note
 *       - This key is a shared secret owned by NXP
 *       - It can be used during key provision to import an application key encrypted with an NXP secret
 *       - This NXP key can be used to encrypt a customer key using an email service provided by NXP. In this way, the customer key can be injected in HSE
 *         sub-system in a secure manner. Contact NXP support team for more details.
 *       - The service is used in pair with another RSA key. The email service provides a signature which is verified using the RSA key.
 * \code
 *
 * (#HSE_KF_USAGE_DERIVE | #HSE_KF_USAGE_VERIFY | #HSE_KF_USAGE_ENCRYPT | #HSE_KF_USAGE_DECRYPT | #HSE_KF_USAGE_KEY_PROVISION)
 *
 * \endcode */
#define HSE_ROM_KEY_AES256_KEY1       ((hseKeyHandle_t)0x00000001UL)

#if defined(HSE_SPT_NXP_RFE_SW)
/** @brief This key can be used for the decryption of NXP RFE image, having the following usage restrictions:
 * \code
 *
 * (#HSE_KF_USAGE_SMR_DECRYPT | #HSE_KF_USAGE_VERIFY)
 *
 * \endcode */
#define HSE_ROM_KEY_AES256_KEY2       ((hseKeyHandle_t)0x00000002UL)
#endif /* HSE_SPT_NXP_RFE_SW */

/** @brief This key can be used for RSA encrypt and signature verify, having the following usage restrictions:
 *  @note
 *       - This key is a public RSA key owned by NXP; the corresponding private key is owned by NXP.
 *       - It can be used during key provision to import an application key signed.
 *       - This NXP key can be used to verify a signature on a customer key which is signed using an email service provided by NXP. In this way, the customer key can be injected in HSE
 *         sub-system in a secure manner. Contact NXP support team for more details.
 *       - The service is used in pair with another ROM key i.e HSE_ROM_KEY_AES256_KEY1.
 * \code
 *
 * (#HSE_KF_USAGE_ENCRYPT | #HSE_KF_USAGE_VERIFY | #HSE_KF_USAGE_KEY_PROVISION)
 *
 * \endcode */
#define HSE_ROM_KEY_RSA3072_PUB_KEY0  ((hseKeyHandle_t)0x00000100UL)

#if defined(HSE_SPT_NXP_RFE_SW)
/** @brief This key can be used for RSA signature verification of NXP RFE image, having the following usage restrictions:
 * \code
 *
 * (#HSE_KF_USAGE_VERIFY)
 *
 * \endcode */
#define HSE_ROM_KEY_RSA2048_PUB_KEY1  ((hseKeyHandle_t)0x00000101UL)
#endif /* HSE_SPT_NXP_RFE_SW */

/** @brief This key can be used for key provisioning having the following usage restrictions:
 *  @note
 *       - This key is a public ECC key owned by NXP; the corresponding private key owned by NXP.
 *       - It can be used during key provision to import an application key signed using an NXP ECC public key.
 *       - This NXP key can be used to sign a customer key using an email service provided by NXP. In this way, the customer key can be injected in HSE
 *         sub-system in a secure manner. Contact NXP for more details.
 * \code
 *
 * (#HSE_KF_USAGE_VERIFY | #HSE_KF_USAGE_KEY_PROVISION)
 *
 * \endcode */
#define HSE_ROM_KEY_ECC256_PUB_KEY0   ((hseKeyHandle_t)0x00000200UL)

/** @brief   The SMR flags.
 *  @details A set of flags that define which secure memory region (SMR),
 *           shall be verified before the key can be used.
 *           For RAM keys, the SMR flags are forced to zero (not used). */
typedef uint32_t hseSmrFlags_t;
#define HSE_KF_SMR_0                  ((hseSmrFlags_t)1UL << 0UL)
#define HSE_KF_SMR_1                  ((hseSmrFlags_t)1UL << 1UL)
#define HSE_KF_SMR_2                  ((hseSmrFlags_t)1UL << 2UL)
#define HSE_KF_SMR_3                  ((hseSmrFlags_t)1UL << 3UL)
#define HSE_KF_SMR_4                  ((hseSmrFlags_t)1UL << 4UL)
#define HSE_KF_SMR_5                  ((hseSmrFlags_t)1UL << 5UL)
#define HSE_KF_SMR_6                  ((hseSmrFlags_t)1UL << 6UL)
#define HSE_KF_SMR_7                  ((hseSmrFlags_t)1UL << 7UL)
#define HSE_KF_SMR_8                  ((hseSmrFlags_t)1UL << 8UL)
#define HSE_KF_SMR_9                  ((hseSmrFlags_t)1UL << 9UL)
#define HSE_KF_SMR_10                 ((hseSmrFlags_t)1UL << 10UL)
#define HSE_KF_SMR_11                 ((hseSmrFlags_t)1UL << 11UL)
#define HSE_KF_SMR_12                 ((hseSmrFlags_t)1UL << 12UL)
#define HSE_KF_SMR_13                 ((hseSmrFlags_t)1UL << 13UL)
#define HSE_KF_SMR_14                 ((hseSmrFlags_t)1UL << 14UL)
#define HSE_KF_SMR_15                 ((hseSmrFlags_t)1UL << 15UL)
#define HSE_KF_SMR_16                 ((hseSmrFlags_t)1UL << 16UL)
#define HSE_KF_SMR_17                 ((hseSmrFlags_t)1UL << 17UL)
#define HSE_KF_SMR_18                 ((hseSmrFlags_t)1UL << 18UL)
#define HSE_KF_SMR_19                 ((hseSmrFlags_t)1UL << 19UL)
#define HSE_KF_SMR_20                 ((hseSmrFlags_t)1UL << 20UL)
#define HSE_KF_SMR_21                 ((hseSmrFlags_t)1UL << 21UL)
#define HSE_KF_SMR_22                 ((hseSmrFlags_t)1UL << 22UL)
#define HSE_KF_SMR_23                 ((hseSmrFlags_t)1UL << 23UL)
#define HSE_KF_SMR_24                 ((hseSmrFlags_t)1UL << 24UL)
#define HSE_KF_SMR_25                 ((hseSmrFlags_t)1UL << 25UL)
#define HSE_KF_SMR_26                 ((hseSmrFlags_t)1UL << 26UL)
#define HSE_KF_SMR_27                 ((hseSmrFlags_t)1UL << 27UL)
#define HSE_KF_SMR_28                 ((hseSmrFlags_t)1UL << 28UL)
#define HSE_KF_SMR_29                 ((hseSmrFlags_t)1UL << 29UL)
#define HSE_KF_SMR_30                 ((hseSmrFlags_t)1UL << 30UL)
#define HSE_KF_SMR_31                 ((hseSmrFlags_t)1UL << 31UL)

/** @brief The ECC curve IDs*/
typedef uint8_t hseEccCurveId_t;
#define HSE_EC_CURVE_NONE                 ((hseEccCurveId_t)0U)
#define HSE_EC_SEC_SECP256R1              ((hseEccCurveId_t)1U)
#define HSE_EC_SEC_SECP384R1              ((hseEccCurveId_t)2U)
#define HSE_EC_SEC_SECP521R1              ((hseEccCurveId_t)3U)
#define HSE_EC_BRAINPOOL_BRAINPOOLP256R1  ((hseEccCurveId_t)4U)
#define HSE_EC_BRAINPOOL_BRAINPOOLP320R1  ((hseEccCurveId_t)5U)
#define HSE_EC_BRAINPOOL_BRAINPOOLP384R1  ((hseEccCurveId_t)6U)
#define HSE_EC_BRAINPOOL_BRAINPOOLP512R1  ((hseEccCurveId_t)7U)
#define HSE_EC_25519_ED25519              ((hseEccCurveId_t)9U)
#define HSE_EC_25519_CURVE25519           ((hseEccCurveId_t)10U)
#define HSE_EC_448_ED448                  ((hseEccCurveId_t)11U)
#define HSE_EC_448_CURVE448               ((hseEccCurveId_t)12U)
 /* The curve IDs that can be set at init time */
#define HSE_EC_USER_CURVE1                ((hseEccCurveId_t)101U)
#define HSE_EC_USER_CURVE2                ((hseEccCurveId_t)102U)
#define HSE_EC_USER_CURVE3                ((hseEccCurveId_t)103U)

/** @brief    Some default key bits values.
 *  @details  The below values are only only a few possible values.
 *            Note that HSE supports key bit length different than those defined below (eg. TU Darmstadt curves 1 to 38). */
typedef uint16_t hseKeyBits_t;
#define HSE_KEY_BITS_INVALID          ((hseKeyBits_t)0xFFFFU)
#define HSE_KEY_BITS_ZERO             ((hseKeyBits_t)0U)
#define HSE_KEY64_BITS                ((hseKeyBits_t)64U)
#define HSE_KEY128_BITS               ((hseKeyBits_t)128U)
#define HSE_KEY160_BITS               ((hseKeyBits_t)160U)
#define HSE_KEY192_BITS               ((hseKeyBits_t)192U)
#define HSE_KEY224_BITS               ((hseKeyBits_t)224U)
#define HSE_KEY240_BITS               ((hseKeyBits_t)240U)
#define HSE_KEY256_BITS               ((hseKeyBits_t)256U)
#define HSE_KEY320_BITS               ((hseKeyBits_t)320U)
#define HSE_KEY384_BITS               ((hseKeyBits_t)384U)
#define HSE_KEY512_BITS               ((hseKeyBits_t)512U)
#define HSE_KEY521_BITS               ((hseKeyBits_t)521U)
#define HSE_KEY638_BITS               ((hseKeyBits_t)638U)
#define HSE_KEY1024_BITS              ((hseKeyBits_t)1024U)
#define HSE_KEY2048_BITS              ((hseKeyBits_t)2048U)
#define HSE_KEY3072_BITS              ((hseKeyBits_t)3072U)
#define HSE_KEY4096_BITS              ((hseKeyBits_t)4096U)

/** @brief    Cipher modes flags for AES keys
 *  @details  The values below are representing the cipher mode flags that an AES key can take. */
typedef uint8_t hseAesBlockModeMask_t;
#define HSE_KU_AES_BLOCK_MODE_ANY     ((hseAesBlockModeMask_t)0U)                                   /**< @brief Any block mode below */
#define HSE_KU_AES_BLOCK_MODE_XTS     ((hseAesBlockModeMask_t)(1U << 0U))                           /**< @brief XTS mode (AES) */
#define HSE_KU_AES_BLOCK_MODE_CTR     ((hseAesBlockModeMask_t)(1U << HSE_CIPHER_BLOCK_MODE_CTR))    /**< @brief CTR mode (AES) */
#define HSE_KU_AES_BLOCK_MODE_CBC     ((hseAesBlockModeMask_t)(1U << HSE_CIPHER_BLOCK_MODE_CBC))    /**< @brief CBC mode (AES) */
#define HSE_KU_AES_BLOCK_MODE_ECB     ((hseAesBlockModeMask_t)(1U << HSE_CIPHER_BLOCK_MODE_ECB))    /**< @brief ECB mode (AES) */
#define HSE_KU_AES_BLOCK_MODE_CFB     ((hseAesBlockModeMask_t)(1U << HSE_CIPHER_BLOCK_MODE_CFB))    /**< @brief CFB mode (AES) */
#define HSE_KU_AES_BLOCK_MODE_OFB     ((hseAesBlockModeMask_t)(1U << HSE_CIPHER_BLOCK_MODE_OFB))    /**< @brief OFB mode (AES) */
#define HSE_KU_AES_BLOCK_MODE_CCM     ((hseAesBlockModeMask_t)(1U << 6U))                           /**< @brief CCM mode (AES) */
#define HSE_KU_AES_BLOCK_MODE_GCM     ((hseAesBlockModeMask_t)(1U << 7U))                           /**< @brief GCM mode (AES) */

/*==================================================================================================
*                                             ENUMS
==================================================================================================*/

/*==================================================================================================
                                 STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/

/** @brief    The entry of the Key Catalog Configuration
 *  @details  The size of a key slot is computed internally based on keytype and maxKeyBitLen.
 *            @note A key group (catalog entry) contains keys that have the same key type and the keybitLen <= maxKeyBitLen.
 *  */
typedef struct
{
    hseMuMask_t        muMask;          /**< @brief Specifies the MU Instance(s) for the key group. A key group can belong to one ore more MUs. */
    hseKeyGroupOwner_t groupOwner;      /**< @brief Specifies the key group owner. */
    hseKeyType_t       keyType;         /**< @brief The key type (see #hseKeyType_t). */
    uint8_t            numOfKeySlots;   /**< @brief The number of key slots. */
    uint16_t           maxKeyBitLen;    /**< @brief The maximum length of the key (in bits). All stored keys have keyBitLen <= maxKeyBitLen. */
    uint8_t            hseReserved[2];  /**< @brief HSE reserved */
} hseKeyGroupCfgEntry_t;


/** @brief   Key properties
 *  @details Each cryptographic key material will be based on key properties (info) and key data */
typedef struct
{
    hseKeyFlags_t keyFlags;         /**< @brief The key flags (see #hseKeyFlags_t) */

    /** @brief The length of key in bits.
     * - For RSA, bit length of modulus n
     * - For ECC, the bit length of the base point order.
     * - Any other key, the bit length of the key. */
    uint16_t      keyBitLen;

    /** @brief The key counter used to prevent the rollback attacks on the key. <br>
     *         For NVM keys, the key counter must be between 0 and #HSE_KF_MAX_KEY_COUNTER_VALUE
     *         For RAM keys, the key counter is forced to 0xFFFFFFFF (not used).
     *         @note
     *         The key counter for SHE keys follows the SHE specification (e.g. key counter is 28bits;
     *         for SHE RAM keys, the key counter is forced to zero). */
    uint32_t      keyCounter;

    /** @brief A set of flags that define which secure memory region (SMR),
     *         indexed from 0 to 31, should be verified before the
     *         key can be used. Set to zero means not used. <br>
     *         For RAM keys, the SMR flags are forced to zero (not used).
     *         Keys linked with SMR(s) that are not yet present in the system
     *         will be available until these SMR(s) are successfully installed. */
    hseSmrFlags_t smrFlags;
    hseKeyType_t  keyType;                   /**< @brief The key type (see #hseKeyType_t). */

    union
    {
        hseEccCurveId_t         eccCurveId;          /**< @brief The ECC curve Id used with this key. This is used only for ECC key type */
        uint8_t                 pubExponentSize;     /**< @brief The size (in bytes) of the RSA public exponent (e); it should be less than 16 bytes. */
        hseAesBlockModeMask_t   aesBlockModeMask;    /**< @brief The cipher mode usage for an AES key. This is used only for AES key type
                                                                 If aesBlockModeMask == 0, any AES block mode can be used */
    }specific;
    uint8_t          hseReserved[2U];
} hseKeyInfo_t;

/** @} */

/*==================================================================================================
*                                      DEFINES AND MACROS
==================================================================================================*/
/** @brief    Options to erase keys.
 *  @details  The erase key options are used only if the provided key handle is set to #HSE_INVALID_KEY_HANDLE. */
typedef uint8_t hseEraseKeyOptions_t;
#define HSE_ERASE_NOT_USED                   (0U)  /**< @brief Erase key options not used. */
#define HSE_ERASE_ALL_RAM_KEYS_ON_MU_IF      (1U)  /**< @brief Erase all RAM keys assigned to MU Interface on which the erase service is sent. */
#define HSE_ERASE_ALL_NVM_SYM_KEYS_ON_MU_IF  (2U)  /**< @brief Erase all NVM symmetric keys assigned to MU Interface on which the erase service is sent
                                                               (needs CUST/OEM SuperUser rights). */
#define HSE_ERASE_ALL_NVM_ASYM_KEYS_ON_MU_IF (3U)  /**< @brief Erase all NVM asymmetric keys assigned to MU Interface on which the erase service is sent
                                                               (needs CUST/OEM SuperUser rights). */
#define HSE_ERASE_ALL_NVM_KEYS_ON_MU_IF      (4U)  /**< @brief Erase all NVM KEYS assigned to MU Interface on which the erase service is sent
                                                                (needs CUST/OEM SuperUser rights). */
#define HSE_ERASE_KEYGROUP_ON_MU_IF          (5U)  /**< @brief Erase all keys assigned to the key group referenced in the key handle.
                                                               The MU Interface on which the erase service is sent to must be part of the group mask.
                                                               CUST/OEM SuperUser rights with KM privileges are needed to perform this operation.
                                                               In case the key group as an owner (CUST/OEM) the SU rights must be provided for this owner. */

/*==================================================================================================
*                                             ENUMS
==================================================================================================*/

/*==================================================================================================
                                 STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/

/*-------------------------------SERVICES DEFINITION----------------------------------------------*/
/** @brief HSE Load ECC curve.
 *  @details This service can be used to set the domain parameters
 *           for a Weierstrass ECC curve that is not supported by default. Twisted Edwards or
 *           Montgomery curve parameters cannot be loaded by this service.
 *  @note
 *        1. Loading a curve into the HSE modifies the SYS-IMAGE, making it necessary to publish it
 *           and store it in external flash on HSE_H/M devices.
 *        2. The host needs super-user rights to update the NVM configuration, in order to use this service.
 */
#ifdef HSE_SPT_ECC_USER_CURVES
typedef struct
{
    /** @brief   INPUT: The ECC curve ID. Must be a user allocated curve ID (i.e. HSE_ECC_CURVEx). */
    hseEccCurveId_t eccCurveId;
    uint8_t         reserved[3];

    /** @brief   INPUT: The bit length of the prime p. */
    hseKeyBits_t pBitLen;

    /** @brief   INPUT: The bit length of the order n. */
    hseKeyBits_t nBitLen;

    /** @brief   INPUT: Elliptic curve parameter a. Must be represented as
     * a big endian number, in the form of a byte array of length #HSE_BITS_TO_BYTES(#pBitLen), e.g. 256 bit curves
     * need 32 byte arrays, 521 bit curves need 66 byte arrays */
    HOST_ADDR    pA;

    /** @brief   INPUT: Elliptic curve parameter b. Must be represented as
     * a big endian number, in the form of a byte array of length #HSE_BITS_TO_BYTES(#pBitLen), e.g. 256 bit curves
     * need 32 byte arrays, 521 bit curves need 66 byte arrays */
    HOST_ADDR    pB;

    /** @brief   INPUT: Elliptic curve prime p. Must be represented as
     * a big endian number, in the form of a byte array of length #HSE_BITS_TO_BYTES(#pBitLen), e.g. 256 bit curves
     * need 32 byte arrays, 521 bit curves need 66 byte arrays. */
    HOST_ADDR    pP;

    /** @brief   INPUT: Elliptic curve order n. Must be represented as
     * a big endian number, in the form of a byte array of length #HSE_BITS_TO_BYTES(#nBitLen), e.g. 256 bit curves
     * need 32 byte arrays, 521 bit curves need 66 byte arrays. */
    HOST_ADDR    pN;

    /** @brief   INPUT: Elliptic curve generator point. The x and y coordinates of the generator,
     * represented as big endian numbers, each in the form of a byte array of length #HSE_BITS_TO_BYTES(#pBitLen),
     * then concatenated. The HSE expects an array of size 2 * #HSE_BITS_TO_BYTES(#pBitLen). */
    HOST_ADDR    pG;
} hseLoadEccCurveSrv_t;
#endif /* HSE_SPT_ECC_USER_CURVES */

/** @brief HSE "Format Key Catalogs" service.
 *  @details Used to configure the NVM or RAM key catalogs.
 *           The catalogs format should be define according to the total number of groups (#HSE_TOTAL_NUM_OF_KEY_GROUPS).
 *           and the maximum available memory for NVM or RAM keys handled by the HSE Firmware (see #HSE_MAX_NVM_STORE_SIZE and #HSE_MAX_RAM_STORE_SIZE).
 *           If the catalog definition does not fit within the available memory, an error occurs and the key format fails.
 *           Each catalog should terminate with a zero filled entry.
 *
 *      The key catalogs (NVM and RAM) can only be formatted (or re-formatted)  only if one of the following conditions is met:
 *      - if the application has CUST_DEL SuperUser rights (see hseSysAuthorizationReqSrv_t).
 *      - if #HSE_STATUS_INSTALL_OK is cleared (there is no SYS-IMG installed). In this case, after formatting the key catalogs,
 *        the application will be granted with CUST and OEM SU rights (ANY).
 *      @note
 *            - Each catalog entry represent a key group of the same key type.
 *            - Each group is identified by its index within the catalog.
 *            - Each group has an owner (see #hseKeyGroupOwner_t). NVM keys can be owned by CUST or OEM; RAM key owner is always #HSE_KEY_OWNER_ANY.
 *            - Note that a key group can contain keys that have keybitLen <= maxKeyBitLen.
 *              For example, the group of key type #HSE_KEY_TYPE_AES of 256bits can contain AES128, AES192 and AES256 keys.
 *              If there are not enough slots for an AES128 key in an AES128 group, the key can be store in an AES256 slot.
 *            - At least one group should be defined for each catalog (NVM or RAM).
 *            - #HSE_KEY_TYPE_SHARED_SECRET key group can only be used for RAM key catalog.
 *            - #HSE_KEY_TYPE_RSA_PAIR key group can only be used for NVM key catalog.
 *            - A key group can belong to one or more MUs.
 *            - Both NVM and RAM catalogs shall be set in the same manner.
 *
 *   Example of NVM key catalog configuration.
 *   \code
 *    {
 *      {  HSE_MU0_MASK, HSE_KEY_OWNER_CUST, HSE_KEY_TYPE_AES,            20U,        HSE_KEY128_BITS },
 *      {  HSE_MU0_MASK, HSE_KEY_OWNER_CUST, HSE_KEY_TYPE_ECC_PAIR,       2U,         HSE_KEY256_BITS },
 *      {  HSE_MU1_MASK, HSE_KEY_OWNER_OEM,  HSE_KEY_TYPE_AES,            20U,        HSE_KEY256_BITS },
 *      {  HSE_MU1_MASK, HSE_KEY_OWNER_OEM,  HSE_KEY_TYPE_HMAC,           10U,        HSE_KEY512_BITS },
 *      {  HSE_MU1_MASK, HSE_KEY_OWNER_OEM,  HSE_KEY_TYPE_ECC_PAIR,       2U,         HSE_KEY256_BITS },
 *      {  HSE_MU1_MASK, HSE_KEY_OWNER_OEM,  HSE_KEY_TYPE_ECC_PUB,        6U,         HSE_KEY256_BITS },
 *      {  HSE_MU1_MASK, HSE_KEY_OWNER_OEM,  HSE_KEY_TYPE_ECC_PUB_EXT,    10U,        HSE_KEY256_BITS },
 *      {  0U,           0U,                 0U,                          0U,         0U  }
 *    }
 *    \endcode
 *
 *    SHE Key catalog configuration (see below configuration):
 *    - NVM SHE keys shall be mapped on key group 0 in NVM key Catalog . Otherwise an error will be reported.
 *    - In addition to the SHE keys KEY_1 to KEY_10 (key ID 0x4 to 0x0D), the HSE firmware allows the application
 *      to provision extra NVM SHE keys. These extended NVM SHE key groups must map to the key groups 1 to 4 in the NVM key catalogs,
 *      and shall contain 10 keys.
 *    - Maximum 5 NVM SHE groups are allowed.
 *    - RAM SHE key shall also be mapped on key group 0 in RAM key Catalog.
 *    - The owner for SHE key group shall be set to #HSE_KEY_OWNER_ANY.
 *    - Any other non-SHE key group can be added after SHE key groups in NVM/RAM Key Catalogs.
 *
 *   NVM SHE Key Catalog Configuration:
 *   - row0: MASTER_ECU_KEY, BOOT_MAC_KEY, KEY_1 to KEY_10
 *   - row1: KEY_11 to KEY_20
 *   - row2: KEY_21 to KEY_30
 *   - row3: KEY_31 to KEY_40
 *   - row4: KEY_41 to KEY_50
 *   \code
 *    {
 *      { HSE_MU0_MASK, HSE_KEY_OWNER_ANY,  HSE_KEY_TYPE_SHE,  12U  ,     HSE_KEY128_BITS },
 *      { HSE_MU0_MASK, HSE_KEY_OWNER_ANY,  HSE_KEY_TYPE_SHE,  10U  ,     HSE_KEY128_BITS },
 *      { HSE_MU0_MASK, HSE_KEY_OWNER_ANY,  HSE_KEY_TYPE_SHE,  10U  ,     HSE_KEY128_BITS },
 *      { HSE_MU0_MASK, HSE_KEY_OWNER_ANY,  HSE_KEY_TYPE_SHE,  10U  ,     HSE_KEY128_BITS },
 *      { HSE_MU0_MASK, HSE_KEY_OWNER_ANY,  HSE_KEY_TYPE_SHE,  10U  ,     HSE_KEY128_BITS },
 *      { 0U,           0U,                 0U,                0U   ,     0U  }
 *    }
 *   \endcode
 *
 *   RAM SHE Key Catalog Configuration
 *   \code
 *    {
 *      { HSE_MU0_MASK, HSE_KEY_OWNER_ANY, HSE_KEY_TYPE_SHE,          1U   ,     HSE_KEY128_BITS },
 *      { 0U,           0U,                0U              ,          0U   ,     0U  }
 *    }
 *    \endcode
 */
#ifdef HSE_SPT_FORMAT_KEY_CATALOGS
typedef struct
{
    /** @brief   INPUT: Points to "NVM Key Catalog" table  (table entries of type #hseKeyGroupCfgEntry_t). */
    HOST_ADDR           pNvmKeyCatalogCfg;
    /** @brief   INPUT: Points to "RAM Key Catalog" table  (table entries of type #hseKeyGroupCfgEntry_t). */
    HOST_ADDR           pRamKeyCatalogCfg;
} hseFormatKeyCatalogsSrv_t;
#endif /* HSE_SPT_FORMAT_KEY_CATALOGS */

/** @brief   HSE "Extend Key Catalog" service.
 *  @details Used to update the NVM or RAM key catalogs without reformatting and erasing the contents.
 *           The new key groups added via this services will be appended to the end of the groups already part of the targeted key catalog configuration.
 *           As a precondition, the key catalogs must be formatted before calling this service.
 *           SuperUser access rights with KM privileges are needed in order to execute this service (see #hseSysAuthorizationReqSrv_t service).
 */
#ifdef HSE_SPT_EXTEND_KEY_CATALOG
typedef struct
{
    /** @brief   INPUT: The ID of the key catalog for which the group entry is appended. Can be only NVM or RAM. */
    hseKeyCatalogId_t   keyCatalogId;
    /** @brief   INPUT: The number of key catalog entries that are appended to the targeted catalog. */
    uint8_t             numOfKeyGroupEntries;
    /** @brief   Reserved bytes */
    uint8_t             reserved[2U];
    /** @brief   INPUT: Points to the key catalog group entry/entries which are appended (see #hseKeyGroupCfgEntry_t). */
    HOST_ADDR           pKeyGroupEntries;
} hseExtendKeyCatalogSrv_t;
#endif /* HSE_SPT_EXTEND_KEY_CATALOG */

/** @brief   HSE Erase key.
 *  @details This service can be used to erase RAM or NVM keys.
 *  The erase service depends on HSE access right (see #hseSysRights_t):
 *  1. SuperUser rights (CUST or OEM):
 *       - NVM CUST keys can be erased only if the CUST SuperUser rights were granted (see #hseSysAuthorizationReqSrv_t service)
 *       - NVM OEM keys can be erased only if the OEM SuperUser rights were granted (see #hseSysAuthorizationReqSrv_t service)
 *       - RAM keys can be erased
 *  2. User rights:
 *       - NVM keys can NOT be erased.
 *       - RAM keys can be erased.
 *
 * @note
 * - The MU mask of the key group(s) must match the MU interface on which the erase request was sent.
 * - For NVM key erase, the MU interface on which the host was authorized as SupperUser must match the MU interface
 *   on which erase service request has been sent.
 * - SHE keys cannot be erased individually (as single slot or as single NVM group). When #HSE_ERASE_ALL_NVM_SYM_KEYS_ON_MU_IF or #HSE_ERASE_ALL_NVM_KEYS_ON_MU_IF options are used, the SHE keys would be erased
 *   only if system authorization was performed beforehand using MASTER_ECU key. Otherwise, the operation will be successful erasing other key types, but not SHE keys.
 */
typedef struct
{
    /** @brief   INPUT: The key handle.
     *                  It is used if the erase option is #HSE_ERASE_NOT_USED, specifying the one key to be erased or
     *                  if the erase option is #HSE_ERASE_KEYGROUP_ON_MU_IF, specifying the key catalog and group to be erased. <br>
     *                  Otherwise, it must be set to #HSE_INVALID_KEY_HANDLE when used with the other erase options
     *                  (#HSE_ERASE_ALL_RAM_KEYS_ON_MU_IF, #HSE_ERASE_ALL_NVM_SYM_KEYS_ON_MU_IF, #HSE_ERASE_ALL_NVM_ASYM_KEYS_ON_MU_IF, #HSE_ERASE_ALL_NVM_KEYS_ON_MU_IF).
     *                  @note A single write-protected NVM key cannot be deleted.
     *                        Write-protected NVM keys can be deleted when multiple keys are erased
     *                        (using #HSE_ERASE_ALL_NVM_SYM_KEYS_ON_MU_IF, #HSE_ERASE_ALL_NVM_ASYM_KEYS_ON_MU_IF, #HSE_ERASE_ALL_NVM_KEYS_ON_MU_IF or
     *                        #HSE_ERASE_KEYGROUP_ON_MU_IF options).
     */
    hseKeyHandle_t        keyHandle;
    /** @brief   INPUT: The Erase key options (see #hseEraseKeyOptions_t) */
    hseEraseKeyOptions_t  eraseKeyOptions;
    uint8_t               reserved[3];
} hseEraseKeySrv_t;

/** @brief   HSE Get Key Info service.
 *  @details Return the key information (or properties) using the "key handle" as input parameter.
 */
#ifdef HSE_SPT_GET_KEY_INFO
typedef struct
{
    /** @brief   INPUT: The key handle. */
    hseKeyHandle_t   keyHandle;
    /** @brief   OUTPUT: Address where to store hseKeyInfo_t (Specifies usage flags, restriction access, key bit length etc ). */
    HOST_ADDR        pKeyInfo;
} hseGetKeyInfoSrv_t;
#endif /* HSE_SPT_GET_KEY_INFO */


#ifdef HSE_SPT_KEY_VERIFY
/** @brief   The algorithm used for key verification .*/
typedef uint8_t hseKeyVerAlgo_t;
#define HSE_KEY_VER_SHA256          ((hseKeyVerAlgo_t)HSE_HASH_ALGO_SHA2_256)   /**< @brief SHA256 */
#define HSE_KEY_VER_SHA384          ((hseKeyVerAlgo_t)HSE_HASH_ALGO_SHA2_384)   /**< @brief SHA384 */
#define HSE_KEY_VER_SHA512          ((hseKeyVerAlgo_t)HSE_HASH_ALGO_SHA2_512)   /**< @brief SHA512 */
#define HSE_KEY_VER_CMAC            ((hseKeyVerAlgo_t)HSE_MAC_ALGO_CMAC)        /**< @brief CMAC (AES) */

/** @brief   HSE Key Verify service.
 *  @details This service is used to verify a CMAC, SHA256, SHA384 or SHA512 over
 *           a key stored inside HSE. The CMAC, SHA256 or SHA384 are provided by the application.
 */
typedef struct
{
    /** @brief   INPUT: The key handle of the key that needs to be verified.
     *                  The key must be a symmetric key.
    */
    hseKeyHandle_t   keyHandle;
    /** @brief   INPUT: The key handle used for CMAC operation.
     *                  For HSE_KEY_VER_SHA256, HSE_KEY_VER_SHA384 and HSE_KEY_VER_SHA512 selected algorithms, this parameter is ignored. */
    hseKeyHandle_t   cmackeyHandle;
    /** @brief   INPUT: Key verification algorithm. It can be #HSE_KEY_VER_CMAC, #HSE_KEY_VER_SHA256, #HSE_KEY_VER_SHA384 or #HSE_KEY_VER_SHA512(see #hseKeyVerAlgo_t)  */
    hseKeyVerAlgo_t  keyVerAlgo;
    /** @brief   INPUT: The provided tag length. It can be:
     *                  - a CMAC tag; the length must be between 8 - 16 bytes
     *                  - a SHA256 hash; the length must be between 8 - 32 bytes
     *                  - a SHA384 hash; the length must be between 8 - 48 bytes
     *                  - a SHA512 hash; the length must be between 8 - 64 bytes
     */
    uint8_t          tagLen;
    /** @brief   Reserved bytes */
    uint8_t          reserved[2U];
    /** @brief   INPUT: Address where tag is stored (CMAC tag, SHA256, SHA384 or SHA512 hash) */
    HOST_ADDR        pTag;
} hseKeyVerifySrv_t;
#endif /* HSE_SPT_KEY_VERIFY */

/** @} */

/** @brief   HSE Service response.
*  @details  The Service response is provided by MUB_RRx register after the service execution. */
typedef uint32_t  hseSrvResponse_t;
#define HSE_SRV_RSP_OK                          ((hseSrvResponse_t)0x55A5AA33UL)  /**< @brief HSE service successfully executed with no error. */
#define HSE_SRV_RSP_VERIFY_FAILED               ((hseSrvResponse_t)0x55A5A164UL)  /**< @brief HSE signals that a verification request fails (e.g. MAC and Signature verification). */
#define HSE_SRV_RSP_INVALID_ADDR                ((hseSrvResponse_t)0x55A5A26AUL)  /**< @brief The address parameters are invalid. */
#define HSE_SRV_RSP_INVALID_PARAM               ((hseSrvResponse_t)0x55A5A399UL)  /**< @brief The HSE request parameters are invalid. */
#define HSE_SRV_RSP_NOT_SUPPORTED               ((hseSrvResponse_t)0xAA55A11EUL)  /**< @brief The operation or feature not supported. */
#define HSE_SRV_RSP_NOT_ALLOWED                 ((hseSrvResponse_t)0xAA55A21CUL)  /**< @brief The operation is not allowed because of some restrictions (in attributes, life-cycle dependent operations, key-management, etc.). */
#define HSE_SRV_RSP_NOT_ENOUGH_SPACE            ((hseSrvResponse_t)0xAA55A371UL)  /**< @brief There is no enough space to perform service (e.g. format key store) */
#define HSE_SRV_RSP_READ_FAILURE                ((hseSrvResponse_t)0xAA55A427UL)  /**< @brief The service request failed because read access was denied. For HSE_B, it can be returned if Host Flash Programming/Erase operaton was in progress at the time of giving the command. */
#define HSE_SRV_RSP_WRITE_FAILURE               ((hseSrvResponse_t)0xAA55A517UL)  /**< @brief The service request failed because write access was denied */
#define HSE_SRV_RSP_STREAMING_MODE_FAILURE      ((hseSrvResponse_t)0xAA55A6B1UL)  /**< @brief The service request that uses streaming mode failed (e.g. UPDATES and FINISH steps do not use the same HSE interface ID and channel ID as START step). */
#define HSE_SRV_RSP_KEY_NOT_AVAILABLE           ((hseSrvResponse_t)0xA5AA51B2UL)  /**< @brief This error code is returned if a key is locked due to failed boot measurement or an active debugger. */
#define HSE_SRV_RSP_KEY_INVALID                 ((hseSrvResponse_t)0xA5AA52B4UL)  /**< @brief The key usage flags (provided using the key handle) don't allow to perform the requested crypto operation (the key flags don't match the crypto operation;
                                                                                              e.g. the key is configured to be used for decryption, and the host requested an encryption). In SHE, the key ID provided is either invalid or non-usable
                                                                                              due to some flag restrictions. */
#define HSE_SRV_RSP_KEY_EMPTY                   ((hseSrvResponse_t)0xA5AA5317UL)  /**< @brief Specified key slot is empty. */
#define HSE_SRV_RSP_KEY_WRITE_PROTECTED         ((hseSrvResponse_t)0xA5AA5436UL)  /**< @brief Key slot to be loaded is protected with WRITE PROTECTION restriction flag. */
#define HSE_SRV_RSP_KEY_UPDATE_ERROR            ((hseSrvResponse_t)0xA5AA5563UL)  /**< @brief Used only in the context of SHE specification: specified key slot cannot be updated due to errors in verification of the parameters. */
#define HSE_SRV_RSP_MEMORY_FAILURE              ((hseSrvResponse_t)0x33D6D136UL)  /**< @brief Detect physical errors, flipped bits etc., during memory read or write operations. */
#define HSE_SRV_RSP_CANCEL_FAILURE              ((hseSrvResponse_t)0x33D6D261UL)  /**< @brief The service can not be canceled. */
#define HSE_SRV_RSP_CANCELED                    ((hseSrvResponse_t)0x33D6D396UL)  /**< @brief The service has been canceled. */
#define HSE_SRV_RSP_GENERAL_ERROR               ((hseSrvResponse_t)0x33D6D4F1UL)  /**< @brief This error code is returned if an error not covered by the error codes above is detected inside HSE. */
#define HSE_SRV_RSP_COUNTER_OVERFLOW            ((hseSrvResponse_t)0x33D6D533UL)  /**< @brief The monotonic counter overflows. */
#define HSE_SRV_RSP_SHE_NO_SECURE_BOOT          ((hseSrvResponse_t)0x33D6D623UL)  /**< @brief HSE did not perform SHE based secure Boot. */
#define HSE_SRV_RSP_SHE_BOOT_SEQUENCE_ERROR     ((hseSrvResponse_t)0x33D7D83AUL)  /**< @brief Received SHE_BOOT_OK or SHE_BOOT_FAILURE more then one time. */

#ifdef HSE_SPT_IPSEC
#define HSE_SRV_RSP_IPSEC_INVALID_DATA          ((hseSrvResponse_t)0xDD333133UL)  /**< @brief Invalid (malformed) IP packet */
#define HSE_SRV_RSP_IPSEC_REPLAY_DETECTED       ((hseSrvResponse_t)0xDD3332DDUL)  /**< @brief Valid packet but replay detected */
#define HSE_SRV_RSP_IPSEC_REPLAY_LATE           ((hseSrvResponse_t)0xDD3333A5UL)  /**< @brief Valid packet but frame late in sequence */
#define HSE_SRV_RSP_IPSEC_SEQNUM_OVERFLOW       ((hseSrvResponse_t)0xDD33343DUL)  /**< @brief Sequence number overflow */
#define HSE_SRV_RSP_IPSEC_CE_DROP               ((hseSrvResponse_t)0xDD33A15AUL)  /**< @brief Decap CE DROP (ECN issue) error */
#define HSE_SRV_RSP_IPSEC_TTL_EXCEEDED          ((hseSrvResponse_t)0xDD33A2D3UL)  /**< @brief Packet decrypted but TTL exceeded */
#define HSE_SRV_RSP_IPSEC_VALID_DUMMY_PAYLOAD   ((hseSrvResponse_t)0xDD33A3D5UL)  /**< @brief Valid Dummy Payload (type 59) */
#define HSE_SRV_RSP_IPSEC_HEADER_LEN_OVERFLOW   ((hseSrvResponse_t)0xDD33A4D9UL)  /**< @brief Operation successful, but IPsec additions cause overflow of IP header length field */
#define HSE_SRV_RSP_IPSEC_PADDING_CHECK_FAIL    ((hseSrvResponse_t)0xDD33A53AUL)  /**< @brief IPsec padding check error found */
#endif

#define HSE_SRV_RSP_FUSE_WRITE_FAILURE          ((hseSrvResponse_t)0xBB4456E7UL)  /**< @brief This error code is returned, if fuse write operation fail. */
#define HSE_SRV_RSP_FUSE_VDD_GND                ((hseSrvResponse_t)0xBB4457F3UL)  /**< @brief This error code is returned, if EFUSE_VDD connected to ground during fuse write operation. */

#define HSE_SRV_RSP_SBAF_UPDATE_REQUIRED        ((hseSrvResponse_t)0xCC66FEADUL)  /**< @brief This error code is returned, if operation is dependent on Secure BAF version, which on the device happens to be old. */


/** @} */

/*==================================================================================================
*                                      HSE errors
==================================================================================================*/

/**  @addtogroup hse_interface_errors HSE Errors
 *   @ingroup    class_interface
 *   @{
 */

/** @page     errors HSE Errors Details
 *  @details  These error events are reported when some kind of intrusion/violation is detected in the system.
 *            The most significant 16 bits are reserved for NXP internal errors and less significant 16 bits indicate the source of violation as defined below.
 *
 *            @note
 *            - If the MU General Purpose Interrupt is enabled on the host-side, any bit set to "1" (on MUB_GSR register) triggers an interrupt.
 *            - The host must read the MUB_GSR register and write back the register value to clear the bits (W1C - write one to clear).
 *            - The bits[0..7] (listed below) are fatal errors that trigger an HSE shutdown (HSE enters in the secure failure state, all MU are disabled).
 *            - The bits[8..15] (listed below) are warning events (something failed, but it is not fatal).
 */
typedef uint32_t hseError_t;
/*LIST OF HSE FATAL ERRORS. Any fatal error triggers an HSE shutdown. */
#define HSE_ERR_GENERAL                    ((hseError_t)1UL << 0U)  /**< @brief Internal fatal error detected by HSE. The HSE system shutdowns. */

/* LiST OF HSE WARNING EVENTS. In this case, the HSE is still running (it doesn't shutdown). */
#define HSE_WA_SMR_PERIODIC_CHECK_FAILED    ((hseError_t)1UL << 8U) /**< @brief The verification of periodic check SMR (hseSmrEntry_t#checkPeriod !=0) failed. The application can read
                                                                                 #HSE_SMR_CORE_BOOT_STATUS_ATTR_ID attribute to see what SMR failed. */

#ifdef HSE_SPT_INTERNAL_FLASH_DEV /* HSE_B device specific warning bits */
#define HSE_WA_DATA_FLASH_INTEGRITY_FAIL    ((hseError_t)1UL << 9U) /**< @brief HSE Data flash memory integrity check failed. */
#endif /* HSE_SPT_INTERNAL_FLASH_DEV */

#define HSE_WA_RNG_NOT_INIT                 ((hseError_t)1UL << 10U) /**< @brief RNG is not initialized. Services depending on the RNG may be delayed as HSE attempts RNG re-initialization. */

#ifdef HSE_SPT_FLASHLESS_DEV /* HSE_H/M */
#define HSE_WA_PUBLISH_COUNTER_TBL          ((hseError_t)1UL << 11U) /**< @brief The application shall publish and store the monotonic counter table. */
#endif /*HSE_SPT_FLASHLESS_DEV*/

/**@}*/

/*==================================================================================================
*                                      Host Events To HSE
==================================================================================================*/
/**  @addtogroup hse_interface_host_events Host Events To HSE
 *   @ingroup class_interface
 *   @{
 */

#ifdef HSE_SPT_FLASHLESS_DEV /* HSE_H/M */
/** @page     host_events Host Events To HSE Details
 *  @brief    These events are sent by Host to notify HSE of actions that needs synchronization between the two.
 *            In order to signal HSE of these events, the host must write its value to MUB_GCR.
 *  @note     This is applicable only for MU0 instance.*/
typedef uint32_t hseHostEvent_t;

/** @brief This event is sent by the host to notify HSE after it configures the external peripherals at init-time.
 *  @note     This host event is applicable only at start-up:
 *           - When BOOT_SEQ == 0, until the HSE sets HSE_STATUS_INIT_OK
 *           - Or, when BOOT_SEQ == 1 and the POST_BOOT SMRs are used, after HSE sets #HSE_STATUS_BOOT_OK, until #HSE_STATUS_INIT_OK is set.
 *           - In the above cases,for HSE_B/H/M (except SAF85XX), if the #HSE_HOST_PERIPH_CONFIG_DONE is not received within 5 seconds (computed at maximum frequency), the HSE execution continues.
 *           - Or, for SAF85XX if the #HSE_HOST_PERIPH_CONFIG_DONE is not received within 240 milliseconds (computed at maximum frequency), the HSE execution continues.
 **/
#define HSE_HOST_PERIPH_CONFIG_DONE ((hseHostEvent_t)1UL << 0U)

#ifdef HSE_M
/** @brief This event is sent by the host to notify HSE to trigger TMU BIST selftest.
 *  @note     This host event is applicable only once and the #HSE_STATUS_INIT_OK bit must be set. <br>
 *            For S32R41X, the host must read the TRITSR[3-4]/TRATSR[3-4] register for the results. <br>
 *            For SAF85XX, the host must read the HSE-GPR register for the results <br>
 *                         #HSE_TMU_BIST_MODE_TEST_BJT_CORE_SEQ1, <br>
 *                         #HSE_TMU_BIST_MODE_TEST_BJT_CORE_SEQ2, <br>
 *                         #HSE_TMU_BIST_MODE_TEST_ADC_OUTPUT     <br>
 **/
#define HSE_TMU_BIST_SELFTEST       ((hseHostEvent_t)1UL << 1U)
#endif /* HSE_M */

#endif /* HSE_SPT_FLASHLESS_DEV */

/**@}*/

/*==================================================================================================
*                                      HSE Status
==================================================================================================*/

/**  @addtogroup hse_interface_status HSE Status
 *   @ingroup    class_interface
 *   @{
 */

/** @page   status HSE Status Details
 *  @details HSE status can be read by the HOST and represents the most significant 16 bits
 *           in MUB.FSR register. The least significant 16 bits in MUB.FSR register identifies
 *           the status of each channel:
 *             - 0b - channel idle and it can accept service requests
 *             - 1b - channel busy */
typedef uint16_t hseStatus_t;
/** @details This bit is set when the SHE based secure boot process has been started by HSE firmware.
 *           This bit is only set when SMR0 entry has been installed by the user and its authentication key is set as SHE based BOOT_MAC_KEY */
#define HSE_SHE_STATUS_SECURE_BOOT                          ((hseStatus_t)1U << 1U)

/** @details This bit is set when BOOT_MAC personalization has been completed by HSE firmware.
 *           It means that the BOOT_MAC slot was empty and SHE-based secure boot is performed the the first time.
 *           In that case, if BOOT_MAC_KEY is present, then HSE firmware calculates the BOOT_MAC of the SMR
 *           image present in the SMR0 (using the BOOT_MAC_KEY) and store it as part of sys image. */
#define HSE_SHE_STATUS_SECURE_BOOT_INIT                     ((hseStatus_t)1U << 2U)

/** @details This bit is set when the HSE firmware has completed the secure boot
 *           process with a failure status. (the image verification failed). */
#define HSE_SHE_STATUS_SECURE_BOOT_FINISHED                 ((hseStatus_t)1U << 3U)

/** @details This bit is set when the HSE firmware has successfully completed the secure boot
 *           process (the image verification was successful). */
#define HSE_SHE_STATUS_SECURE_BOOT_OK                       ((hseStatus_t)1U << 4U)

/** @brief This bit is set when HSE FW has successfully initiliazed the RNG. */
#define HSE_STATUS_RNG_INIT_OK                              ((hseStatus_t)1U << 5U)

/** @brief This bit is set when debugger on HOST side is active as well as enabled */
#define HSE_STATUS_HOST_DEBUGGER_ACTIVE                     ((hseStatus_t)1U << 6U)

/** @brief This bit is set when debugger on HSE side is active as well as enabled */
#define HSE_STATUS_HSE_DEBUGGER_ACTIVE                      ((hseStatus_t)1U << 7U)

/** @details This bit is set when the HSE initialization has been successfully completed (HSE service requests can be sent over MUs).
 *           If this bit is cleared, the host can NOT perform any service request (MUs are disabled). */
#define HSE_STATUS_INIT_OK                                  ((hseStatus_t)1U << 8U)

/** @details This flag signals the application that needs to format the key catalogs (NVM and RAM).
 *           - When it is clear, the application shall format the key catalogs;
 *           - When it is set, the HSE installation phase has been successfully completed.
 *             (e.g HSE is in normal state and the application can install the NVM key, configure the SMR entries etc).
 *             @note This step is MANDATORY.*/
#define HSE_STATUS_INSTALL_OK                                ((hseStatus_t)1U << 9U)

/** @details This bit is set when the HSE booting phase has been successfully completed.
 *           This bit is cleared if the HSE booting phase is still in execution or failed.
 *           @note
 *           - HSE set this bit only when the secure boot is configured (BOOT_SEQ = 1).
 *           - This bit represents the status of booting phase which includes the PRE_BOOT SMR verification (without POST_BOOT SMRs) and cores un-gating.
 *           - The HSE FW signals the end of the POST_BOOT phase along with additional peripherals initialization via #HSE_STATUS_INIT_OK flag. */
#define HSE_STATUS_BOOT_OK                                  ((hseStatus_t)1U << 10U)

/** @details After reset, if the Life Cycle = CUST_DEL, this bit is set (SuperUser rights are granted). <br>
*          During run-time:
*            - it is set if the authorization request for CUST SuperUser rights are granted using an CUST authorization key.
*            - it is cleared for USER rights.
*             @note  If CUST START_AS_USER policy attribute is set (TRUE), the device will always start having User rights. */
#define HSE_STATUS_CUST_SUPER_USER                          ((hseStatus_t)1U << 11U)

/** @details After reset: if the Life Cycle = OEM_PROD, this bit is set (SuperUser rights are granted). <br>
*             During run-time:
*            - it is set if the authorization request for OEM SuperUser rights are granted using an OEM authorization key.
*            - it is cleared for USER rights.
*             @note If OEM START_AS_USER policy attribute is set (TRUE), the device will always start having User rights. */
#define HSE_STATUS_OEM_SUPER_USER                           ((hseStatus_t)1U << 12U)


#ifdef HSE_SPT_FLASHLESS_DEV /* HSE_H/M device specific status bits */

/** @details This flag signals the application to publish the SYS-IMAGE.
 *            - When this flags is set, the host must trigger a PUBLISH_SYS_IMG request.
 *              @note This flag is set whenever the HSE SYS-IMAGE has been updated in the HSE internal RAM (e.g. after a key update, SMR update, etc.).
 *            - Once SYS-IMG is published to application RAM, this bit is cleared.*/
#define HSE_STATUS_PUBLISH_SYS_IMAGE                        ((hseStatus_t)1U << 13U)

/** @details This flag signals the application whether HSE FW has loaded or not the SYS-IMAGE from primary address.
 *           - If this flag is set, the primary SYS-IMAGE has been loaded.
 *           - If this flag is cleared, the primary SYS-IMAGE has NOT been loaded. This means that HSE either
 *             loaded the SYS-IMAGE from backup address (see #HSE_STATUS_BACKUP_SYS_IMAGE flag) or both primary and backup loads failed. */
#define HSE_STATUS_PRIMARY_SYS_IMAGE                        ((hseStatus_t)1U << 14U)

/** @details This flag signals the application whether HSE FW has loaded or not the SYS-IMAGE from backup address.
 *           - If this flag is set, the backup SYS-IMAGE has been loaded.
 *           - If this flag is cleared, the backup SYS-IMAGE has NOT been loaded. This means that HSE either
 *             loaded the SYS-IMAGE from primary address (see #HSE_STATUS_PRIMARY_SYS_IMAGE flag) or both primary and backup loads failed. */
#define HSE_STATUS_BACKUP_SYS_IMAGE                         ((hseStatus_t)1U << 15U)


#else /* HSE_B device specific status bits */

/** @details This bit is set when the HSE FW update is in progress.
 *           This bit is cleared after HSE FW update completion. */
#define HSE_STATUS_FW_UPDATE_IN_PROGRESS                    ((hseStatus_t)1U << 13U)

/** @details This flag signals the application to publish the NVM KEYSTORE to Secure flash Region.
 *            - This feature can be enabled via #HSE_ENABLE_PUBLISH_KEY_STORE_RAM_TO_FLASH_ATTR_ID attribute.
 *            - When this flags is set, the host must trigger a PUBLISH_KEYSTORE request via #HSE_SRV_ID_PUBLISH_NVM_KEYSTORE_RAM_TO_FLASH.
 *              @note This flag is set whenever the HSE NVM KEYSTORE has been updated in the HSE internal RAM indicating that it is not safe to reset the device.
 *            - Once NVM KEYSTORE via #HSE_SRV_ID_PUBLISH_NVM_KEYSTORE_RAM_TO_FLASH, it is written on secure region in data flash and this bit is cleared.
 *            - If this bit is set, the application must call the #HSE_SRV_ID_PUBLISH_NVM_KEYSTORE_RAM_TO_FLASH service before issuing the Firmware Update.
 *              Otherwise, the HSE_SRV_RSP_NOT_ALLOWED response status will be returned.
 */
#define HSE_STATUS_PUBLISH_NVM_KEYSTORE_RAM_TO_FLASH        ((hseStatus_t)1U << 14U)

#endif /* HSE_SPT_FLASHLESS_DEV */



/** @} */


#ifdef HSE_SPT_MSC_KEYSTORE
/*==================================================================================================
                                 STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/

/** @brief The restriction flags for the Key Handle Translation Table (KHTT) entry.*/
typedef uint8_t hseKHTTRestrictFlags_t;
/** @brief The restriction used when more MSC keys are pushed at once:
 *         - If it is set 0, HSE loads the MSC key when the #hsePushMscKeySrv_t service is called with hseKeyHandle = HSE_INVALID_KEY_HANDLE.
 *         - If it is set 1, HSE does not load the MSC key when the #hsePushMscKeySrv_t service is called with hseKeyHandle = HSE_INVALID_KEY_HANDLE. */
#define HSE_KHTT_RESTRICT_PUSH_MANY             ((hseKHTTRestrictFlags_t)1U)

/** @brief The Key Handle Translation Table (KHTT) entry.
 *         Each KHTT entry contains the correspondence between HSE Key Handles and MSC key slots (e.g. ACE key slots).
 *         @note
 *         - The "Managed Security Component"(MSC) term is used bellow for any HW accelerator on host-side that uses keys managed by HSE FW.
 *         - Each MSC key inherit the properties of its corresponding key in HSE.
 *         - If keyInfo.keyFlags is set to any of the HSE_KF_USAGE_VERIFY and HSE_KF_USAGE_SIGN flags, the key can only be used with CMAC operation.
 *           The rest of the key flags are ignored.
 *         - If the DID input received over ACE buses is not matching the DID flags configured for the entry, the key can not be used.
 *         - MSC key store must be statically partitioned per host (e.g. each host has its own key slots)
 * */
typedef struct
{
    /** @brief   INPUT: The key handle used with HSE keystore.
     *           @note
     *           The key bit length of HSE key can only be 128 or 256 bits (e.g. the 256 bit key group cannot get a key of 128 bit size). */
    hseKeyHandle_t      hseKeyHandle;
    /** @brief   INPUT: The MSC key slot index. The MSC/ACE subsystem accesses a key selecting a key slot in the range 0 to 127.
     *           @note
     *           - The MSC keystore (e.g. ACE keystore) contains 128 X key slots of 16 bytes and the associated key properties.
     *             Without considering the key properties, it can be seen as an array of 128 elements, the size of each element
     *             being 16 bytes (e.g keystore[128][16]).
     *           - An AES128 key occupies only one key slot. An AES256 key occupies two key slots. In this case,
     *             the next key slot following an AES256 key must be placed at N+2 (e.g keystore[N+2]), where N is the AES256 key slot index.
     *           - The maximum number of MSC keys is 128 x 128-bit keys or 64 x 256-bit keys or any combination in between. */
    uint8_t             mscKeySlotIdx;
    /** @brief   INPUT: MSC Instance (e.g. the instance of the HW accelerator on the host side).
     *           @note
     *           On S32ZE, field is ignored; there is only one MSC instance (e.g. ACE HW accelerator). */
    uint8_t             mscInstance;
    /** @brief   INPUT: 16 bits for Domain ID (DID) filtering. The didFlags is compared against "1<<bus DID value".
     *           @note
     *           On the buses the DID value is 4 bits only. The DID comparison works in this way:
     *           If bus DID = 4, it means bit 4 in didFlags must be set to be able to use the key. */
    uint16_t            aceDidFlags;
    /** @brief   INPUT: Restriction flags (see #hseKHTTRestrictFlags_t) */
    hseKHTTRestrictFlags_t restrictFlags;
    uint8_t             reserved[3];
} hseKHTTEntry_t;


/** @brief Configure the Key Handle Translation Table (KHTT) service.
 *         This service sends the Key Handle Translation Table (KHTT) which is statically defined by the application at configuration time.
 *         @note
 *         - The "Managed Security Component"(MSC) term is used below for any HW accelerator on host-side that uses keys managed by HSE FW.
 *         - Before configuring the MSC keys, the application shall enable the MSC clock (e.g ACE clock must be enabled by the application).
 *         - The Key Handle Translation Table (KHTT) is a table stored in SYS-IMG with correspondences between HSE KeyHandles and MSC key slots.
 *         - Using KHTT table, the HSE keys are mirrored by HSE subsystem in the MSC key store (e.g. ACE key store).
 *           This means that any key import/erase is automatically performed on both key stores (HSE and MSC keystores).
 *         - The KHTT table maps each HSE keyHandle to MSC mscKeySlotIdx. The key handles can be NVM or RAM keys.
 *           Only the NVM keys are stored in SYS-IMG (the RAM keys are not persistent).
 *         - The MSC keys can be loaded (at initialization) from SYS-IMG in MSC key store calling the
 *           #hsePushMscKeySrv_t service with the hseKeyHandle parameter equal with HSE_INVALID_KEY_HANDLE.
 *           The same service can be used to push only one HSE key slot to one MSC key slot, providing the corresponding hseKeyHandle.
 */
typedef struct
{
    /** @brief   INPUT: Number of KHTT entries. It shall be maximum 200 entries. */
    uint16_t            numOfKHTTEntries;
    uint8_t             reserved[2];
/** @brief   INPUT: Pointer to the Key Handle Translation Table(KHTT) that contains #numOfKHTTEntries entries of type #hseKHTTEntry_t. */
    HOST_ADDR           pKHTT;
}hseConfigKHTTSrv_t;

/** @brief Push one or more MSC keys.
 *         This service requests HSE to push one or more HSE keys in the corresponding MSC slots.
 *         The HSE key handle must be found in the Key Handle Translation Table (KHTT) (see #hseConfigKHTTSrv_t).
 * */
typedef struct
{
    /** @brief   INPUT: The HSE key handle to be pushed to MSC key slot.
     *                  If hseKeyHandle == HSE_INVALID_KEY_HANDLE, HSE pushes all key slots (not empty)
     *                  from KHTT table that do not have the #HSE_KHTT_RESTRICT_PUSH_MANY flag set.
     *         @note
     *         - This option can be used to load (at initialization time) the NVM HSE keys
     *           whose handles are found in the KHTT and have the #HSE_KHTT_RESTRICT_PUSH_MANY flag set.
     *         - If hseKeyHandle != HSE_INVALID_KEY_HANDLE, HSE pushes a single key which must be in the KHTT table.
     *         - The pushed key(s) must not be empty
     */
    hseKeyHandle_t      hseKeyHandle;
}hsePushMscKeySrv_t;

/** @} */
#endif

#ifdef HSE_SPT_CMAC_WITH_COUNTER
/*==================================================================================================
 *                               STRUCTURES AND OTHER TYPEDEFS
 * ==================================================================================================*/

/**
 * @brief          CMAC With Counter service.
 * @details        This service calculates/verifies the CMAC of a given input message concatenated with a selected secure counter.
 *                 @note
 *                 - The secure counter must be configured before (refer to #hseConfigSecCounterSrv_t)
 *                 - Bits are represented from left to right at byte level.
 *                 - In the description below, the following notation is used:
 *                     - SC - 64bit secure counter
 *                     - RP - The Rollover Protection bits of the secure counter (refer to #hseConfigSecCounterSrv_t)
 *                     - VC - The Volatile Counter bits of the secure counter (refer to #hseConfigSecCounterSrv_t)
 *                     - SC_counterIdx is the secure counter identified by the counterIdx (counter index)
 *                     - VC_counterIdx is the volatile part of the secure counter (volatile counter) identified by the counterIdx
 *                     - RP_counterIdx is the Rollover Protection value of the secure counter identified by the counterIdx (the volatile counter bits are all zeros)
 *                     - "||" means concatenation
 *                     - VCI is the Volatile Counter provide as input parameter by the service (#pVolatileCounter parameter)
 *                     - RPO is the Rollover Protection Offset (#RPOffset parameter for CMAC verify) added to Rollover Protection value to adjust the RP bits.
 *                     - ISC - the implied value of the SC computed by HSE concatenating the optionally adjusted RP bits with the VCI bits
 *                       (refer to CMAC verify sequence below)
 *
 *                 For CMAC generate, the HSE firmware performs the following sequence: <br>
 *                     \code
 *                     SC_counterIdx = SC_counterIdx + 1
 *                     TAG = CMAC_GENERATE(KeyHandle, input || SC_counterIdx)
 *                     VC_counterIdx = SC_counterIdx - RP_counterIdx
 *                     if(VC_counterIdx == 0) then update RP_counterIdx in NVM
 *                     return  TAG, VC_counterIdx & RSP_STATUS_OK
 *                     \endcode
 *
 *                 For CMAC verify, the HSE firmware performs the following sequence: <br>
 *                      \code
 *                      if(VCI > VC_counterIdx) then ISC = (RP_counterIdx + RPO) || VCI
 *                      if(VCI <= VC_counterIdx) then ISC = (RP_counterIdx + 1 + RPO) || VCI
 *                      if(CMAC_VERIFY(KEY_HANDLE, input || ISC)) then
 *                      {
 *                           SC_counterIdx = ISC
 *                           if((RPO != 0) or (VCI <= VC_counterIdx)) then update RP_counterIdx in NVM
 *                           rsp_status = HSE_SRV_RSP_OK
 *                      }
 *                      else
 *                      {
 *                           rsp_status =  HSE_SRV_RSP_VERIFY_FAILED
 *                      }
 *                      return rsp_status
 *                      \endcode
 */
typedef struct
{
    /** @brief   INPUT: Specifies the direction: generate/verify. */
    hseAuthDir_t   authDir;

    uint8_t        reserved1[3U];

    /** @brief   INPUT: The key to be used for the operation. */
    hseKeyHandle_t keyHandle;

    /** @brief   INPUT: The counter Index of the secure counter */
    uint32_t       counterIdx;

    /** @brief   INPUT: The Rollover protection offset used to adjust the Rollover protection bits of the secure counter in the CMAC verify operation.
     *                  It is ignored for CMAC generate.
     *                  If the CMAC verification fails, the application can try with a different RPOffset. */
    uint8_t        RPOffset;

    /** @brief  INPUT: Specify if pInput is provided as hseScatterList_t list (the host address points to a hseScatterList_t list).
     *                 Ignored if SGT is not supported.
     *                 @note
     *                 - ONLY HSE_SGT_OPTION_INPUT can be used.
     *                 - If scatter option is selected (set), the length (e.g. inputBitLength) shall specified the entire message length
     *                 (sum of all hseScatterList_t lengths in bits).
     *                 - If scatter option is selected, the number of input SGT entries shall be 2. */
    hseSGTOption_t   sgtOption;

    uint8_t        reserved2[2U];

    /** @brief   INPUT: Length of the input message.(in bits) */
    uint32_t       inputBitLength;

    /** @brief   INPUT: The input message. */
    HOST_ADDR      pInput;

    /** @brief   INPUT: Holds tag length in bits.
     *           - CMAC GENERATE:
     *             - On calling service (input), this parameter shall contain the length of the buffer (in bits) provided by #pTag.
     *             - Recommended tag lengths are [32, 128]. Tag-lengths greater than 128 are truncated to 128.
     *           - CMAC VERIFY:
     *             - On calling service (input), this parameter shall contain the bit-length to be verified.
     *             - Recommended tag lengths are [32, 128].
     *             - The #HSE_FAST_CMAC_MIN_TAG_BIT_LEN_ATTR_ID attribute can be used to overwrite
     *               the lower recommended tag bit length limit (minimum is 1). */
    uint8_t        tagBitLength;

    uint8_t        reserved3[3U];

    /** @brief   OUTPUT/INPUT: The output tag for "generate"; the input tag for "verify". */
    HOST_ADDR      pTag;

    /** @brief   OUTPUT/INPUT: The address of the volatile counter.
     *                         HSE reads/writes #HSE_BITS_TO_BYTES(64-RPBitSize) bytes at pVolatileCounter address:
     *           - CMAC GENERATE: Specifies the address where to provide the Volatile Counter (Output parameter).
     *           - CMAC VERIFY: Input parameter that specifies the Volatile Counter to be used for the CMAC verify operation. */
    HOST_ADDR      pVolatileCounter;
}hseCmacWithCounterSrv_t;

/*==================================================================================================
 *                               GLOBAL VARIABLE DECLARATIONS
 * ==================================================================================================*/

/*==================================================================================================
 *                                   FUNCTION PROTOTYPES
 * ==================================================================================================*/


/** @} */
#endif

#ifdef HSE_SPT_IMPORT_KEY
/*==================================================================================================
                                 STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/
/** @brief HSE ECC key format
 *  @details Additional info for Ecc key format for import and export
 *    For Weierstrass curve public keys:
 *    - the raw format is the X coordinate concatenated with the Y coordinate ( X || Y ), in big endian
 *    - the uncompressed  format is a byte of 0x04, concatenated with the X coordinate and Y coordinates ( 0x04 || X || Y )
 *    - the compressed format is a byte of 0x02 or 0x03, depending on the (lsb) of Y, concatenated with the X coordinate
 *          - ( 0x02 || X ) if the lsb of Y is 0
 *          - ( 0x03 || X ) if the lsb of Y is 1
 *    For Twisted Edwards curve public keys:
 *    - the raw format is the standard compressed format (point Y with the the sign bit of X), but in big endian
 *    For Montgomery curve public keys:
 *    - the raw format is the X coordinate, in big endian
 */
typedef uint8_t hseEccKeyFormat_t;
#define HSE_KEY_FORMAT_ECC_PUB_RAW                       ((hseEccKeyFormat_t)0U) /**< @brief Raw ECC public key: X || Y */
#define HSE_KEY_FORMAT_ECC_PUB_UNCOMPRESSED              ((hseEccKeyFormat_t)1U) /**< @brief Standard ECC uncompressed public key: 0x04 || X || Y */
#define HSE_KEY_FORMAT_ECC_PUB_COMPRESSED                ((hseEccKeyFormat_t)2U) /**< @brief Standard ECC compressed public key: 0x02/0x03 || X */

/** @brief HSE key format.
 *  @details Includes additional information about the format of the key. Currently only used for ECC keys.
 */
typedef union
{
    /** @brief   INPUT: ECC key format. */
    hseEccKeyFormat_t eccKeyFormat;
    uint8_t reserved[4];
} hseKeyFormat_t;


/** @brief   HSE Import Key Service.
 *  @details This service can be used to import a key in an empty slot or to update an existing key.
 *  1. Common key restrictions (which apply for both SuperUser and User rights):
 *     - Key flags (of key properties) are always applied.
 *     - The NVM provisioning keys can be installed/updated without authentication only having SuperUser rights;
 *       they can also be updated having User rights using the pre-installed provision keys.
 *     - The RAM provision keys can be imported only authenticated and can be used only to import RAM keys.
 *     - A key can be authenticated signing the key container (e.g. X.509 certificate or any container).
 *       The HOST shall provide a pointer to that key container, pointer(s) to key value(s) within the key container and
 *       pointer(s) to the tag/signature(s) (computed over the key container).
 *     - To import an encrypted/authenticated NVM key, the provided provision key(s) must have the same group owner as the imported NVM key.
 *     - To import an encrypted/authenticated NVM symmetric key using AEAD, the pointer to key info must be in the additional data
 *     - The key properties (keyInfo) along with the public key values are always imported in plain format.
 *  2. SuperUser key restrictions:
 *     - NVM keys:
 *         - In empty slots, an encrypted key can be imported only authenticated, and a plain key can be imported
 *           with/without authentication (public keys must be imported in plain).
 *         - In non-empty slots, NVM keys can be imported(overwritten) in plain/encrypted, only authenticated.
 *     - RAM keys:
 *         - An encrypted key can be imported only authenticated. A plain key can be imported with/without authentication.
 *           Exception: RAM provision keys can be imported only authenticated.
 *  3. User key restrictions:
 *     - NVM keys:
 *         - NVM secrets (symmetric keys and key pairs) can be imported only encrypted and authenticated.
 *           For key pair, private value must be encrypted and public value(s) unencrypted.
 *           NVM secrets imported from a signed key container MUST include the key properties (keyInfo) in the container
 *           (the provided key counter must be bigger than the previous one).
 *         - NVM public keys can be imported in plain, only authenticated.
 *           NVM public key imported from a signed key container can/cannot include the keyInfo in the container.
 *     - RAM keys:
 *         - An encrypted key can be imported only authenticated. A plain key can be imported with/without authentication.
 *         - key pairs can be imported only authenticated; private value encrypted and public value(s) unencrypted
 *         - public keys can be imported in plain, only authenticated.
 *  @note
 *     - The key catalogs must have been formatted prior to provisioning the keys.
 *     - When AEAD is used to import a key, the container cannot be used.
 *     - The key types *_PUB_EXT are stored in plain in the application NVM. For these key types, HSE stores only the key
 *       properties and the pointers to the public key values, as well as an authentication tag calculated over the key container:
 *       the authentication tag is verified by the HSE firmware whenever the related key is used by the host.
 *     - For HSE_H/M devices, the SYS-IMAGE does not have to be written to application NVM after each key import operation; the SYS-IMAGE update
 *       process can be done at the end of the configuration process.
 **/
typedef struct
{
    /** @brief   INPUT: Specifies the slot where to add or updated a key.
     *                  Note that the keyHandle identifies the key catalog, key group index and key slot index */
    hseKeyHandle_t      targetKeyHandle;
    /** @brief   INPUT: Specifies usage flags, restriction access, key length in bits, etc for the key (see hseKeyInfo_t).
     *                  @note
     *                        - Only keys that are not write protected can be updated with this service.
     *                        - NVM keys are secured against replay attacks by including a counter value stored within HSE.
     *                          The anti-replay attack counter included in the key info header should be greater than
     *                          the counter of the HSE key that will be updated (in case of key update).
     *                          This mean that keyInfo MUST be included in the signed key container (when the Life Cycle is IN_FIELD).
     *                        - For RAM keys the key counter is ignored (keyInfo may not be in the key container). */
    HOST_ADDR           pKeyInfo;
    /** @brief   INPUT: Pointer to key values.
     *           A RSA private key should always be imported together with the public key.
     *           An ECC private key can be imported standalone if the public key (pKey[0]) is NULL and
     *           the public key length (keyLen[0]) is zero. The public key will be computed internally from
     *           the private key.
     *           - pKey[0]:
     *              - RSA public modulus n (big-endian).
     *              - ECC depends on the key format
     *                  - Weierstrass curve keys:
     *                      - raw format: X || Y, in big endian; keyLen[0] must be 2 * #HSE_BITS_TO_BYTES(keyBitLength)
     *                      - uncompressed format: 0x04 || X || Y, in big endian; keyLen[0] must be 1 + 2 * #HSE_BITS_TO_BYTES(keyBitLength)
     *                      - compressed format: 0x02 / x03 || X,  in big endian; keyLen[0] must be 1 + #HSE_BITS_TO_BYTES(keyBitLength)
     *                  - Twisted Edwards curve keys:
     *                      - raw format: point Y with the sign bit of X, in big endian; keyLen[0] must be #HSE_BITS_TO_BYTES(keyBitLength)
     *                  - Montgomery curve keys:
     *                      - raw format: the X coordinate, in big endian; keyLen[0] must be #HSE_BITS_TO_BYTES(keyBitLength)
     *              - Classic DH prime modulus p
     *           - pKey[1]:
     *              - RSA public exponent e (big-endian).
     *              - Classic DH public key
     *           - pKey[2]:
     *              - RSA private exponent d (big-endian).
     *              - ECC/ED25519 private scalar (big-endian).
     *              - The symmetric key (e.g AES, HMAC).
     *              - Classic DH private key
     */
    HOST_ADDR       pKey[3];
    /** @brief   INPUT: The length in bytes for the above key values in the same order. <br>
     *                  Note that keyInfo.keyBitLen specifies the key length in bits.*/
    uint16_t        keyLen[3];
    uint8_t         reserved[2];
    /** @brief   INPUT: Cipher parameters are used only if the cipherKeyHandle is not #HSE_INVALID_KEY_HANDLE.
     *                  @note
     *                  - For AES-block cipher, if the keyBitLen is not multiple of AES block size (128bits), the key value have to be padded with zeros.
     *                  - For RSAES NO PADDING, the keyBitLen of the imported key must be less than or equal to #HSE_BITS_TO_BYTES(cipherKey_keyBitLen), and the key is considered a big-endian integer.
     *                  - For RSAES-PKCS1-v1_5, the keyBitLen of the imported key shall not be greater than #HSE_BITS_TO_BYTES(cipherKey_keyBitLen) -11 bytes.
     *                  - For RSAES-OAEP, the keyBitLen of the imported key shall not be greater than #HSE_BITS_TO_BYTES(cipherKey_keyBitLen) - 2 * hashLen - 2 bytes.
    */
    struct
    {
        /** @brief   INPUT: Decryption key handle.
         *                  The cipherKeyHandle can only be a provisioning key (#HSE_KF_USAGE_KEY_PROVISION and #HSE_KF_USAGE_DECRYPT flags are set). <br>
         *                  Note that the key handle identifies the cipher scheme below.
         *                  In case of symmetric cipher scheme and authenticated encryption scheme(AEAD) the differentiation is made using the first byte of cipherScheme.
         *                  Must be set to #HSE_INVALID_KEY_HANDLE if not used. */
        hseKeyHandle_t    cipherKeyHandle;
        /** @brief Symmetric, asymmetric  and AEAD cipher scheme.
                   @note
                   - Only the private keys are encrypted. */
        hseCipherScheme_t cipherScheme;
    }cipher;

    /** @brief   INPUT: The keyContainer parameters should be used if the key comes in a signed key container: pointers to key values
     *                  within the key container should be provided. The signature/tag is assumed to be done over the key container.
     *           @note
     *              - For NVM keys having User rights, the keyInfo MUST be included in the key container.
     *              - If the HOST is authorized (SU rights), the *_PUB_EXT key type can be imported from an unauthenticated key container (providing the key container without the signature). */
    struct
    {
        /** @brief   INPUT: The container length.
         *           @note  The container includes only the signed block (without the signature). */
        uint16_t          keyContainerLen;
        uint8_t           reserved[2];
        /** @brief   INPUT: Address of the key container; includes the key value(s) and other information used to authenticate the key.
         *                  (e.g. TBSCertificate for a X.509 certificate). */
        HOST_ADDR         pKeyContainer;
        /** @brief   INPUT: Authentication key handle (#HSE_KF_USAGE_KEY_PROVISION and #HSE_KF_USAGE_VERIFY flags are set).
         *                  Must be set to #HSE_INVALID_KEY_HANDLE if not used. An encrypted key can be imported only authenticated.*/
        hseKeyHandle_t    authKeyHandle;
        /** @brief   INPUT: Authentication scheme. <br>
         *                  Note that the key handle identifies the authentication scheme below.
         *           @note  For the GMAC scheme, the minimum IV length is 12 bytes.*/
        hseAuthScheme_t   authScheme;
        /** @brief   INPUT: Byte length(s) of the authentication tag(s).
         *                   @note
         *                   - For MAC and RSA signature, only authLen[0] is used.
         *                   - Both lengths are used for (R,S) (ECC or ED25519).
         *                   - The MAC tag size must be minimum 16 bytes.
         *                   - RSA signature size must be #HSE_BITS_TO_BYTES(keyBitLength);
         *                   - R or S size for ECDSA/EdDSA signature must be #HSE_BITS_TO_BYTES(keyBitLength) */
        uint16_t          authLen[2];
        /** @brief   INPUT: Address(es) to authentication tag.
         *                   @note
         *                   - For MAC and RSA signature,  only pAuth[0] is used.
         *                   - Both pointers are used for (R,S) (ECC or ED25519). */
        HOST_ADDR         pAuth[2];
    }keyContainer;
    /** @brief   INPUT: Additional information about the format of the key. Key type specific. */
    hseKeyFormat_t     keyFormat;
} hseImportKeySrv_t;


/** @brief   HSE Export Key Service.
 *  @details The key values and the key properties (optional) can be exported to the host via a key export service.
 *
 *  1. Common key restrictions (which apply for both SuperUser and User rights):
 *     - Key flags (of key properties) are always applied; this service can only be used if the key is exportable.
 *     - Provision/Authorization keys are NOT exportable (#HSE_KF_ACCESS_EXPORTABLE flag is ignored).
 *     - NVM keys can not be exported using RAM provision keys.
 *     - NVM/RAM symmetric keys can be exported only encrypted with/without authentication.
 *     - NVM/RAM public keys (from key pair or public key slots) can be exported in plain; keys may/may not be authenticated.
 *     - The private part of a key pair can NOT be exported (the private part is never disclosed to the host).
 *     - _PUB_EXT can NOT be exported.
 *     - To export an encrypted/authenticated NVM key, the provided provision key must have the same group owner as the exported NVM key (not applicable for RAM keys).
 *     - When AEAD is used to export a key, the container cannot be used.
 */
typedef struct
{
    /** @brief   INPUT: The key handle to be exported.  <br>
     *                  Note that the keyHandle identifies the key catalog, key group index and key slot index */
    hseKeyHandle_t      targetKeyHandle;
    /** @brief   OUTPUT: Export the key information (see hseKeyInfo_t).
     *                   @note
     *                   - For symmetric keys exported in an authenticated key container, key information MUST be part of the key container;
     *                   - For symmetric keys exported authenticated with AEAD, key information MUST be part of AAD (see hseAeadScheme_t);
     *                   - For public keys this parameter is optional. It can be NULL. */
    HOST_ADDR           pKeyInfo;
    /** @brief   OUTPUT: Addresses where to fill to key values.
     *           - pKey[0]:
     *              - RSA public modulus n.
     *              - ECC depends on the key format
     *                  - Weierstrass curve keys:
     *                      - raw format: X || Y, in big endian; the HSE will output 2 * #HSE_BITS_TO_BYTES(keyBitLength) bytes
     *                      - uncompressed format: 0x04 || X || Y, in big endian; the HSE will output 1 + 2 * #HSE_BITS_TO_BYTES(keyBitLength) bytes
     *                      - compressed format: 0x02 / x03 || X,  in big endian; the HSE will output 1 + #HSE_BITS_TO_BYTES(keyBitLength) bytes
     *                  - Twisted Edwards curve keys:
     *                      - raw format: point Y with the sign bit of X, in big endian; the HSE will output #HSE_BITS_TO_BYTES(keyBitLength) bytes
     *                  - Montgomery curve keys:
     *                      - raw format: the X coordinate, in big endian; the HSE will output #HSE_BITS_TO_BYTES(keyBitLength) bytes
     *              - Classic DH prime modulus p
     *           - pKey[1]:
     *              - RSA public exponent e.
     *              - Classic DH public key
     *           - pKey[2]:
     *              - The symmetric key (e.g AES, HMAC).
     *              - Classic DH private key
     */
    HOST_ADDR          pKey[3];
    /** @brief   INPUT/OUTPUT: Addressed of uint16_t values of the length (in bytes) for the above buffers (INPUT).
     *                         As output, it provides the lengths of the encrypted or unencrypted (only for public) keys. <br>
     *                         Note that the length in bits of the key is specified by hseKeyInfo_t.
     */
    HOST_ADDR          pKeyLen[3];

    /** @brief   INPUT: Cipher parameters.
     *                  @note
     *                  - Only the private keys are encrypted and the encrypted value length is specified by the corresponding private key length (in bytes).
     *                  - For AES-block cipher, if the keyBitLen of the exported is not multiple of AES block size (128bits), the key value will be padded with zeros.
     *                  - For RSAES NO PADDING, the keyBitLen of the exported key must be less than or equal to #HSE_BITS_TO_BYTES(cipherKey_keyBitLen), and the key is considered a big-endian integer.
     *                  - For RSAES-PKCS1-v1_5, the keyBitLen of the exported key shall not be greater than #HSE_BITS_TO_BYTES(cipherKey_keyBitLen) -11 bytes.
     *                  - For RSAES-OAEP, the keyBitLen of the exported key shall not be greater than #HSE_BITS_TO_BYTES(cipherKey_keyBitLen) - 2 * hashLen - 2 bytes.
     * */
    struct
    {
        /** @brief   INPUT: Encryption key handle.
         *                  The cipherKeyHandle can only be a provisioning key (#HSE_KF_USAGE_KEY_PROVISION and #HSE_KF_USAGE_ENCRYPT flags are set). <br>
         *                  Note that the key handle will identifies the cipher scheme below.
         *                  Must be set to #HSE_INVALID_KEY_HANDLE if not used. */
        hseKeyHandle_t    cipherKeyHandle;
        /** @brief Symmetric, asymmetric  and AEAD cipher scheme.
                   @note
                   - Only the private keys are encrypted.*/
        hseCipherScheme_t cipherScheme;
    }cipher;

    /** @brief   INPUT: The keyContainer parameters should be used when the key have to be exported in a key container that will be authenticated:
     *                  pointers to where key values will be exported should be provided within the key container. Optionally,
     *                  the pKeyInfo may point inside the key container. The signature/tag is done over the key container. */
    struct
    {
        /** @brief   INPUT: The container length.
         *           @note  The key container length is the size of the byte block to be signed (without the signature). */
        uint16_t          keyContainerLen;
        uint8_t           reserved[2];
        /** @brief   INPUT: Address of the key container; includes the key value(s) and other information used to authenticate the key.
         *                  (e.g. TBSCertificate for a X.509 certificate). */
        HOST_ADDR         pKeyContainer;
        /** @brief   INPUT: Authentication key handle (#HSE_KF_USAGE_KEY_PROVISION and #HSE_KF_USAGE_SIGN flags are set). <br>
         *                  Note that the key handle identifies the authentication scheme below.
         *                  Must be set to HSE_INVALID_KEY_HANDLE if not used. */
        hseKeyHandle_t    authKeyHandle;
        /** @brief   INPUT: Authentication scheme.
         *           @note  For the GMAC scheme, the minimum IV length is 12 bytes. */
        hseAuthScheme_t   authScheme;
        /** @brief   OUTPUT: Address(es) for the length(s) (uin16_t values) of the authentication tag.
         *                   @note
         *                   - For MAC and RSA signature,  only pAuthLen[0] is used.
         *                   - Both lengths are used for (R,S) (ECC or ED25519). */
        HOST_ADDR         pAuthLen[2];
        /** @brief   OUTPUT: Address of authentication tag.
         *                   @note
         *                   - For MAC and RSA signature,  only pAuth[0] is used.
         *                   - Both pointers are used for (R,S) (ECC or ED25519). */
        HOST_ADDR         pAuth[2];
    }keyContainer;
    /** @brief   INPUT: Additional information about the format of the key. Key type specific. */
    hseKeyFormat_t     keyFormat;
} hseExportKeySrv_t;

/** @} */
#endif

/*==================================================================================================
*                                      DEFINES AND MACROS
==================================================================================================*/

/** @brief HSE System Access rights.
 *   @details
 *    After reset (default access rights):
 *    | Life Cycle | NVM CUST keys   | NVM OEM keys  | RAM keys  | NVM config|
 *    |-----------:|:---------------:|:-------------:|:---------:|:---------:|
 *    |CUST_DEL    |      SU/U*      |       U       |   SU/U*   |   SU/U*   |
 *    |OEM_PROD    |        U        |     SU/U*     |   SU/U*   |   SU/U*   |
 *    |IN_FIELD    |        U        |       U       |     U     |     U     |
 *
 *   After reset, the SYS rights are synchronized with Life cycle (LC) and CUST/OEM START_AS_USER policy attributes (see CUST/OEM policy attributes).
 *      - if LC = CUST_DEL:
 *           - if CUST_START_AS_USER policy = FALSE, CUST SuperUser rights are granted (CUST NVM Keys / NVM configuration updates)
 *           - otherwise User rights are granted (U* in the above table)
 *      - if LC = OEM_DEL:
 *           - if OEM_START_AS_USER policy = FALSE, OEM SuperUser rights are granted (OEM NVM Keys / NVM configuration updates)
 *           - otherwise User rights are granted (U* in the above table)
 *      - if LC = IN_FIELD, User rights are granted.
 */
typedef uint8_t hseSysRights_t;
/** @brief SuperUser rights: can install/update CUST/OEM NVM keys or RAM keys using less restrictions. <br>
           CUST/OEM SuperUser restrictions are specific to CUST_DEL/OEM_PROD Life cycle. */
#define HSE_RIGHTS_SUPER_USER           ((hseSysRights_t)1U)
/** @brief User rights: can install/update NVM/RAM keys using high restrictions. <br>
           User restrictions are specific to IN_FILED life cycle. */
#define HSE_RIGHTS_USER                 ((hseSysRights_t)2U)

/** @brief   HSE System Authorization options.
 *  @details Specifies the services for which the system authorization is performed.
 */
typedef uint8_t hseSysAuthOption_t;
/** @brief Request SuperUser rights for Key Management services (e.g. import/export/erase/key generate/key derive). <br>
 *         If SuperUser rights are granted, Key Management services can be performed using less restrictions. */
#define HSE_SYS_AUTH_KEY_MGMT            ((hseSysAuthOption_t)(1U << 0U))
/** @brief Request SuperUser rights to update/install the HSE NVM tables/attributes which are stored in SYS-IMAGE(HSE_H/M)/internal flash(HSE_B) (e.g. SMR, CR, OTFAD, NVM attributes). <br>
 *         If SuperUser rights are granted, updates of NVM configuration will be permitted. */
#define HSE_SYS_AUTH_NVM_CONFIG          ((hseSysAuthOption_t)(1U << 1U))
/** @brief Request SuperUser rights for both Key Management services and NVM configuration updates. */
#define HSE_SYS_AUTH_ALL                 ((HSE_SYS_AUTH_KEY_MGMT) | (HSE_SYS_AUTH_NVM_CONFIG))

/** @brief Challenge length: Length of the challenge (in bytes) returned by a successful authorization request. */
#define HSE_SYS_AUTH_CHALLENGE_LENGTH    (32UL)

/*==================================================================================================
*                                             ENUMS
==================================================================================================*/

/*==================================================================================================
                                 STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/


/**
 * @brief     HSE SYS Authorization Request service.
 * @details
 *    During run-time (IN_FIELD Life cycle), the User rights can be temporarily elevated to SuperUser(CUST/OEM) using HSE Authorization Request/Response.
 *    - CUST SuperUser rights are granted using an authorization key owned by CUST.
 *    - OEM SuperUser rights are granted using an authorization key owned by OEM.
 *    - The User rights (non privilege rights) can be requested without authorization.
 *      In this case, HSE_SYS_Authorization_Resp shall not be used.
 *
 * @note
 *    - After reset, the default access rights are used (see #hseSysRights_t).
 *    - If no authorization key is installed during CUST_DEL or OEM_PROD life cycle, the keys can be updated only having USER rights.
 *    - HSE FW can perform only one SYS Authorization Request at a time. A second request will overwrite the first request.
 *    - An authorization key is a NVM key that can only be used for verify.
 *    - If authorization succeeds, it will be opened on the MU Interface on which the request was performed,
 *      and the services that needs authorization  (e.g. key import/generate/derive/export) must be performed on the same MU Interface.
 *    - The system authorization procedure can be used to emulate the SHE CMD_DEBUG using the MASTER_ECU_KEY key (as per SHE specification).
 *      In this case, if SU access rights are requested for Key Management services (see #hseSysAuthOption_t),
 *      the authorization using MASTER_ECU_KEY cannot be performed if any SHE key has the WRITE_PROTECTED flag set. <br>
 *      Access rights requested only for NVM Configuration services (see #hseSysAuthOption_t) are not bound to this condition.
 *      Note that SHE keys can be erased only if the authorization was performed with the MASTER_ECU_KEY (refer to #hseEraseKeySrv_t).
 */
typedef struct
{
    /** @brief   INPUT: Authorization option: Key management/NVM configuration/Both. */
    hseSysAuthOption_t  sysAuthOption;
    /** @brief   INPUT: Requested system rights: SuperUser (CUST/OEM) or User rights. */
    hseSysRights_t      sysRights;
    uint8_t             reserved[2];
    /** @brief   INPUT: The owner key handle:
     *           -  if sysRights = HSE_RIGHTS_SUPER_USER, it shall be a CUST or OEM key used for only for signature verification.
     *           -  if sysRights = HSE_RIGHTS_USER, the key handle is not used. */
    hseKeyHandle_t      ownerKeyHandle;
    /** @brief   INPUT: Authentication scheme. ONLY RSA, ECDSA, EDDSA and CMAC schemes are supported. <br>
     *                  If sysRights = HSE_RIGHTS_USER, authScheme is not used.
     *                  @note
     *                      - EDDSA scheme with user provided context (eddsa.contextLength != 0) is NOT supported. */
    hseAuthScheme_t     authScheme;
    /** @brief   OUTPUT: The output challenge that needs to be signed by the HOST.
     *                   In case SHE MASTER_ECU_KEY is used, the returned challenge is HSE_SYS_AUTH_CHALLENGE_LENGTH - 1 byte long and
     *                   is formed from 16 random bytes concatenated with SHE UID: (RANDOM(16 bytes) || SHE_UID(15 bytes)). <br>
     *                   Otherwise, for any other key type, the challenge size is HSE_SYS_AUTH_CHALLENGE_LENGTH bytes.
     *                   If sysRights = HSE_RIGHTS_USER, pChallenge is not used.
     *                   @note For HSE_H/M, the UID is read by HSE from system fuses. The application must provide read-only access (xRDC restriction) to HSE to read the UID.
     *  */
    HOST_ADDR           pChallenge;
} hseSysAuthorizationReqSrv_t;


/**
 * @brief           HSE SYS Authorization Response service.
 * @details         Provides the signature for the requested challenge (using hseSysAuthorizationReqSrv_t service).
 * @note
 *      - In case SHE MASTER_ECU key is used, the HSE will return the HSE_SRV_RSP_VERIFY_FAILED status
 *        as the equivalent of ERC_NO_DEBUGGING status as specified by the SHE spec (returned when the tag over the challenge is not correct).
 */
typedef struct
{
    /** @brief   INPUT: Byte length(s) of the authentication tag(s).
     *                   @note
     *                   - For RSA signature and CMAC only authLen[0] is used.
     *                   - Both lengths are used for (R,S) (ECC).
     *                   - The MAC tag size must be minimum 16 bytes.
     *                   - RSA signature size must be #HSE_BYTES_TO_BITS(keyBitLength);
     *                   - R or S size for ECDSA/EDDSA signature must be #HSE_BYTES_TO_BITS(keyBitLength)*/
    uint16_t          authLen[2];
    /** @brief   INPUT: Address(es) to authentication tag.
     *                   @note
     *                   - For RSA signature and CMAC only pAuth[0] is used.
     *                   - Both pointers are used for (R,S) (ECC).
     *                   - If SHE MASTER_ECU_KEY is used, the CMAC must be computed over the challenge (31 bytes) using a derived key (as per SHE specification). */
    HOST_ADDR         pAuth[2];
} hseSysAuthorizationRespSrv_t;

/** @} */


#ifdef HSE_SPT_BOOTDATASIGN

/*==================================================================================================
                                 STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/

/** @brief The Application Image header that keeps information about the Basic Secure Booting (BSB)
 *        (e.g. header information, source and destination addresses, app code length, tag location).
 *
 *   @note
 *   If both SMR and BSB are configured, HSE executes the secure boot using SMR only. If the
 *   SYS-IMG is not loaded because it is corrupted (the SMRs are not present), HSE executes the secure boot
 *   using BSB. In this case, the App BSB can be seen as a recovery image (to recover the SYS-IMG).
 *   Note that the App image can be booted without loading the SYS-IMG.
 */
#ifdef HSE_SPT_BSB
typedef struct
{
    uint8_t                 hdrTag;                  /**< @brief App header tag shall be 0xD5. */
    uint8_t                 reserved1[2];            /**< @brief Reserved field has no impact. Set to all zeroes.*/
    uint8_t                 hdrVersion;              /**< @brief App header version shall be 0x60. */
    uint32_t                pAppDestAddres;          /**< @brief The destination address where the application is copied.
                                                                 @note For HSE_B, it is NULL (the code is executed from flash) */
    uint32_t                pAppStartEntry;          /**< @brief The address of the first instruction to be executed.*/
    uint32_t                codeLength;              /**< @brief Length of application image. */
    hseAppCore_t            coreId;                  /**< @brief The application core ID that is un-gated.
                                                                 @note Valid for HSE_B devices only. For HSE_H/M core id defined in IVT*/
    uint8_t                 reserved2[47];           /**< @brief Reserved field has no impact. Set to all zeroes. */
} hseAppHeader_t;
#endif /* HSE_SPT_BSB */

/** @brief HSE Boot Data Image GMAC generation.
 *  @details This service is used to generate the GMAC tag along with the random IV (for new device revisions; see notes below) for different Boot Data images. <br>
 *           For HSE_H/M, the following Boot Data Images can be signed:
 *              - IVT, DCD, SELF-TEST and Application Image (also referred below as App BSB Image).
 *              - LPDDR4 Flash image for S32Z/E (HSE_H) devices.
 *           For HSE_B, the following Boot Data Images can be signed:
 *              - IVT and Application Image (also referred below as App BSB Image).
 *                The computed random IV and GMAC tag must be placed/copied at the end of the image.
 *                The 12 bytes of random IV and 16 bytes of GMAC are generated by HSE Firmware.
 *                The random IV is also part of GMAC calculation (for images format, refer to HSE FW Reference Manual). <br>
 *    @note
 *    - SuperUser rights (for NVM Configuration) are needed to perform this service.
 *    - For new device revisions (see table below), the service provides in the pOutTagAddr a random IV (12byte) followed by the GMAC tag (16 bytes).
 *      The IV and GMAC tag must be placed at the end of the image (with one exception for LPDDR4 FLash image; see below).
 *      Note that the GMAC tag generation is also done over the random IV.
 *      The GMAC tag and random IV offsets in the image are specified in the HSE Firmware Reference Manual.
 *    - For older device revisions (the part revision is smaller than the revision specified in the table below),
 *      a static IV is used that is not placed in the image. For the static IV value, refer to HSE Firmware Reference Manual.
 *    - The application can check the device revision information reading the MAJOR_MASK and MINOR_MASK
 *      fields of SIUL2_4 for S32ZE or SIUL2_0 for the others devices
 *    - S32K3XX devices support only random IV
 *
 *    | Device  | New part revision|
 *    |:-------:|:----------------:|
 *    | S32G2   | rev2.1 or higher |
 *    | S32G3   | rev1.1 or higher |
 *    | S32ZE   | rev1.1 or higher |
 *    | S32R45  | rev2.1 or higher |
 *    | S32R41  | rev1.1 or higher |
 *    | SAF85XX | rev2.0 or higher |
 *    | S32K3XX | new rev only     |
 *
 */
#ifdef HSE_SPT_BOOTDATASIGN
typedef struct
{
    /** @brief  INPUT:  The address of the Boot Data Image. The Boot Data Image can be:
     *                  - For HSE_H/M, IVT or DCD or SELF-TEST or App BSB or LPDDR4(for S32Z/E devices) image; the address may be a QSPI-FLASH (external flash) or system RAM address. <br>
     *                  - For HSE_B, the IVT or App BSB image; the address can be a flash or
     *                    system RAM address. <br>
     *
     *                  The length of the pInImage is not provided. HSE uses the information
     *                  from the provided pInImage to compute the image length. <br>
     *                  The length of each image is computed in the below manner:
     *                  1. For HSE_H/M new device revisions: <br>
     *                      - the IVT Image length must be 256 bytes (IVT Image header (4bytes) + IVT Image data (224 bytes) + Random IV (12bytes) + GMAC(16 bytes))
     *                      - For S32Z/E devices (HSE_H), DCD/SELF-TEST Image length must be maximum 32768 bytes (DCD/ST Image header(4 bytes) + maximum DCD/ST Image data (32764 byte))
     *                      - For other devices,DCD/SELF-TEST Image length must be maximum 8192 bytes (DCD/ST Image header(4 bytes) + maximum DCD/ST Image data (8188 byte))
     *                      - For S32Z/E devices (HSE_H), the maximum length of the LPDDR4 Flash image must be smaller or equal to (7MB + 336bytes)(Image header(336 bytes) + code length(maximum 7MB))
     *                      - pInImage can point to the App BSB Image that contains the App header and App code:
     *                          - App image header shall be specified as hseAppHeader_t. It has a fixed size of 64 bytes.
     *                          - App image code shall follow the App image header and has a variable length specified by "codelength" parameter.
     *                          - The computed GMAC tag for App BSB Image includes both App header, App code and Random IV.
     *
     *                     For old device revision (static IV):
     *                     -  For IVT, the IV bytes are reserved (set to zero)
     *                     -  For DCD/SELF-TEST and APP BSB, the IV bytes are not included at all.
     *                     -  For S32Z/E devices, the image does not include any IV in the image header.
     *                     -  For S32Z/E devices (HSE_H), DCD/SELF-TEST Image length must be maximum 8192 bytes (DCD/ST Image header(4 bytes) + maximum DCD/ST Image data (8188 byte))
     *
     *                  2. For HSE_B:
     *                      - The IVT image length must be 256 bytes (IVT Image header (4bytes) + IVT Image data (224 bytes) + IV (12 bytes) + GMAC(16 bytes)).
     *                        The computed GMAC tag is over IVT Image header and data (228 bytes) and IV (12 bytes).
     *                      - pInImage can point to the App BSB Image that contains the App header and App code:
     *                          - App image header shall be specified as hseAppHeader_t. It has a fixed size of 64 bytes.
     *                          - App image code shall follow the App image header and has a variable length specified by "codelength" parameter.
     *                          - The computed GMAC tag for App BSB Image includes App header, App code and IV (12 bytes)
     **/
    HOST_ADDR              pInImage;
    /** @brief  INPUT:  The length in bytes of the IV + GMAC tag.
     *                  This length must be equal to or greater than
     *                  1. For HSE_H/M:<br>
     *                     - new device revisions (random IV): 28 bytes
     *                     - old device revisions (static IV): 16 bytes<br>
     *                  2. For HSE_B, 28 bytes*/
    uint32_t               inTagLength;
    /** @brief  OUTPUT: 1. For HSE_H/M, the output address:
     *                      - new device revisions: random IV (12 bytes) followed by the GMAC tag (16 bytes)
     *                      - old device revisions: GMAC tag (16 bytes)
     *                  2. For HSE_B: The address where the random IV (12 bytes), followed by
     *                                the GMAC tag (16 bytes) are generated. It must be a system RAM address.<br>
     *
     *                  @note
     *                  The computed output data shall be copied at the end of boot data image. <br>
     *                  Exception: For S32Z/E devices (HSE_H), computed random IV shall be copied to LPDDR4 image header (at 0x144 offset) and
     *                  the computed GMAC tag shall be copied at the end of boot data image.
     */
    HOST_ADDR              pOutTagAddr;
}hseBootDataImageSignSrv_t;

/** @brief HSE Boot Data Image GMAC verification.
 *  @details This service can be used to verify the GMAC tag generated using the hseBootDataImageSignSrv_t service.
 */
typedef struct
{
    /** @brief   INPUT: The address of the HSE Boot Data Image (for more details about the HSE Boot Data Images refer to pInImage parameter from hseBootDataImageSignSrv_t service).
     *                  @note
     *                  - HSE uses the Boot Data Image information (provided by #pInImage) to compute the length of the image and to verify the authentication TAG. */
    HOST_ADDR            pInImage;
}hseBootDataImageVerifySrv_t;
#endif /* HSE_SPT_BOOTDATASIGN */

/** @} */
#endif

#ifdef HSE_SPT_IPSEC
/*==================================================================================================
*                                      DEFINES AND MACROS
==================================================================================================*/

/** @brief IPSEC security association ID type.
  * @details The IPSEC security association ID identifies an internal IPSEC context used to
  * hold the state of any established IPSEC security association, managed by the HSE IPSEC acceleration service. */
typedef uint32_t hseIpsecSaId_t;

/** @brief    HSE IPSEC suite IDs.*/
typedef uint16_t hseIpsecSuite_t;
#define HSE_IPSEC_SUITE_NULL_NULL                   ((hseIpsecSuite_t)0x0b00U)
#define HSE_IPSEC_SUITE_NULL_RESERVED1              ((hseIpsecSuite_t)0x0b01U)
#define HSE_IPSEC_SUITE_NULL_HMAC_SHA1_96           ((hseIpsecSuite_t)0x0b02U)
#define HSE_IPSEC_SUITE_NULL_AES_XCBC_MAC_96        ((hseIpsecSuite_t)0x0b05U)
#define HSE_IPSEC_SUITE_NULL_RESERVED2              ((hseIpsecSuite_t)0x0b06U)
#define HSE_IPSEC_SUITE_NULL_HMAC_SHA1_160          ((hseIpsecSuite_t)0x0b07U)
#define HSE_IPSEC_SUITE_NULL_AES_CMAC_96            ((hseIpsecSuite_t)0x0b08U)
#define HSE_IPSEC_SUITE_NULL_HMAC_SHA2_256_128      ((hseIpsecSuite_t)0x0b0cU)
#define HSE_IPSEC_SUITE_NULL_HMAC_SHA2_384_192      ((hseIpsecSuite_t)0x0b0dU)
#define HSE_IPSEC_SUITE_NULL_HMAC_SHA2_512_256      ((hseIpsecSuite_t)0x0b0eU)
#define HSE_IPSEC_SUITE_NULL_HMAC_SHA2_224_96       ((hseIpsecSuite_t)0x0bf2U)
#define HSE_IPSEC_SUITE_NULL_HMAC_SHA2_224_112      ((hseIpsecSuite_t)0x0bf4U)
#define HSE_IPSEC_SUITE_NULL_HMAC_SHA2_224_224      ((hseIpsecSuite_t)0x0bf8U)
#define HSE_IPSEC_SUITE_AES_CBC_NULL                ((hseIpsecSuite_t)0x0c00U)
#define HSE_IPSEC_SUITE_AES_CBC_RESERVED1           ((hseIpsecSuite_t)0x0c01U)
#define HSE_IPSEC_SUITE_AES_CBC_HMAC_SHA1_96        ((hseIpsecSuite_t)0x0c02U)
#define HSE_IPSEC_SUITE_AES_CBC_AES_XCBC_MAC_96     ((hseIpsecSuite_t)0x0c05U)
#define HSE_IPSEC_SUITE_AES_CBC_RESERVED2           ((hseIpsecSuite_t)0x0c06U)
#define HSE_IPSEC_SUITE_AES_CBC_HMAC_SHA1_160       ((hseIpsecSuite_t)0x0c07U)
#define HSE_IPSEC_SUITE_AES_CBC_AES_CMAC_96         ((hseIpsecSuite_t)0x0c08U)
#define HSE_IPSEC_SUITE_AES_CBC_HMAC_SHA2_256_128   ((hseIpsecSuite_t)0x0c0cU)
#define HSE_IPSEC_SUITE_AES_CBC_HMAC_SHA2_384_192   ((hseIpsecSuite_t)0x0c0dU)
#define HSE_IPSEC_SUITE_AES_CBC_HMAC_SHA2_512_256   ((hseIpsecSuite_t)0x0c0eU)
#define HSE_IPSEC_SUITE_AES_CBC_HMAC_SHA2_224_96    ((hseIpsecSuite_t)0x0cf2U)
#define HSE_IPSEC_SUITE_AES_CBC_HMAC_SHA2_224_112   ((hseIpsecSuite_t)0x0cf4U)
#define HSE_IPSEC_SUITE_AES_CBC_HMAC_SHA2_224_224   ((hseIpsecSuite_t)0x0cf8U)
#define HSE_IPSEC_SUITE_AES_CTR_NULL                ((hseIpsecSuite_t)0x0d00U)
#define HSE_IPSEC_SUITE_AES_CTR_RESERVED1           ((hseIpsecSuite_t)0x0d01U)
#define HSE_IPSEC_SUITE_AES_CTR_HMAC_SHA1_96        ((hseIpsecSuite_t)0x0d02U)
#define HSE_IPSEC_SUITE_AES_CTR_AES_XCBC_MAC_96     ((hseIpsecSuite_t)0x0d05U)
#define HSE_IPSEC_SUITE_AES_CTR_RESERVED2           ((hseIpsecSuite_t)0x0d06U)
#define HSE_IPSEC_SUITE_AES_CTR_HMAC_SHA1_160       ((hseIpsecSuite_t)0x0d07U)
#define HSE_IPSEC_SUITE_AES_CTR_AES_CMAC_96         ((hseIpsecSuite_t)0x0d08U)
#define HSE_IPSEC_SUITE_AES_CTR_HMAC_SHA2_256_128   ((hseIpsecSuite_t)0x0d0cU)
#define HSE_IPSEC_SUITE_AES_CTR_HMAC_SHA2_384_192   ((hseIpsecSuite_t)0x0d0dU)
#define HSE_IPSEC_SUITE_AES_CTR_HMAC_SHA2_512_256   ((hseIpsecSuite_t)0x0d0eU)
#define HSE_IPSEC_SUITE_AES_CTR_HMAC_SHA2_224_96    ((hseIpsecSuite_t)0x0df2U)
#define HSE_IPSEC_SUITE_AES_CTR_HMAC_SHA2_224_112   ((hseIpsecSuite_t)0x0df4U)
#define HSE_IPSEC_SUITE_AES_CTR_HMAC_SHA2_224_224   ((hseIpsecSuite_t)0x0df8U)
#define HSE_IPSEC_SUITE_AES_CCM_8                   ((hseIpsecSuite_t)0x0e00U)
#define HSE_IPSEC_SUITE_AES_CCM_12                  ((hseIpsecSuite_t)0x0f00U)
#define HSE_IPSEC_SUITE_AES_CCM_16                  ((hseIpsecSuite_t)0x1000U)
#define HSE_IPSEC_SUITE_AES_GCM_8                   ((hseIpsecSuite_t)0x1200U)
#define HSE_IPSEC_SUITE_AES_GCM_12                  ((hseIpsecSuite_t)0x1300U)
#define HSE_IPSEC_SUITE_AES_GCM_16                  ((hseIpsecSuite_t)0x1400U)
#define HSE_IPSEC_SUITE_AES_NULL_GMAC               ((hseIpsecSuite_t)0x1500U)


/** @brief    HSE IPSEC security association type: transport/tunnel,
 *            encapsulation/decapsulation */
typedef uint8_t hseIpsecType_t;
#define HSE_IPSEC_TYPE_TRANSPORT_ENCAP              ((hseIpsecType_t)0U)
#define HSE_IPSEC_TYPE_TRANSPORT_DECAP              ((hseIpsecType_t)1U)
#define HSE_IPSEC_TYPE_TUNNEL_ENCAP                 ((hseIpsecType_t)2U)
#define HSE_IPSEC_TYPE_TUNNEL_DECAP                 ((hseIpsecType_t)3U)

/** @brief    HSE IPSEC init option flags. Set the flag to enable the option.
 *            The options are set for the entire security association. */
typedef uint32_t hseIpsecOptionFlags_t;

/** @brief    Create an IPv6 SA. Without this flag and IPv4 SA will be created */
#define HSE_IPSEC_OPTION_IPV6                       ((hseIpsecOptionFlags_t)1U << 1U)

/** @brief    Use extended sequence numbers
 *  @note: This option is not supported.*/
#define HSE_IPSEC_OPTION_EXTENDED_SEQNUM            ((hseIpsecOptionFlags_t)1U << 2U)

/** @brief    Use fully random IVs. Otherwise the IVs are chained from frame to frame */
#define HSE_IPSEC_OPTION_IV_SRC_RANDOM              ((hseIpsecOptionFlags_t)1U << 3U)

/** @brief    Decrement TTL on decapsulation */
#define HSE_IPSEC_OPTION_TTL_DECREMENT              ((hseIpsecOptionFlags_t)1U << 4U)

/** @brief    Rollover sequence numbers */
#define HSE_IPSEC_OPTION_SEQNUM_ROLLOVER            ((hseIpsecOptionFlags_t)1U << 5U)

/** @brief    Copy the DF bit*/
#define HSE_IPSEC_OPTION_DF_COPY                    ((hseIpsecOptionFlags_t)1U << 6U)

/** @brief    Copy the Diffserv bits */
#define HSE_IPSEC_OPTION_DIFFSERV_COPY              ((hseIpsecOptionFlags_t)1U << 7U)

/** @brief    Update the IP header checksum */
#define HSE_IPSEC_OPTION_CKSM_UPDATE                ((hseIpsecOptionFlags_t)1U << 8U)

/** @details    Set the IP header source, if any: context, frame or external.
 *            Use only one of the following 4 flags:
 *             - #HSE_IPSEC_OPTION_IP_HDR_SRC_NONE
 *             - #HSE_IPSEC_OPTION_IP_HDR_SRC_CONTEXT
 *             - #HSE_IPSEC_OPTION_IP_HDR_SRC_FRAME
 *             - #HSE_IPSEC_OPTION_IP_HDR_SRC_EXTERNAL
 *
 *            #HSE_IPSEC_OPTION_IP_HDR_SRC_NONE and #HSE_IPSEC_OPTION_IP_HDR_SRC_EXTERNAL
 *            are only valid for tunnel mode
 */
#define HSE_IPSEC_OPTION_IP_HDR_SRC_NONE            ((hseIpsecOptionFlags_t)0U << 9U)
#define HSE_IPSEC_OPTION_IP_HDR_SRC_CONTEXT         ((hseIpsecOptionFlags_t)1U << 9U)
#define HSE_IPSEC_OPTION_IP_HDR_SRC_FRAME           ((hseIpsecOptionFlags_t)2U << 9U)
#define HSE_IPSEC_OPTION_IP_HDR_SRC_EXTERNAL        ((hseIpsecOptionFlags_t)3U << 9U)

/** @brief    Output only the PDU. Otherwise all the input fields will be copied to the output frame */
#define HSE_IPSEC_OPTION_OUTPUT_PDU_ONLY            ((hseIpsecOptionFlags_t)1U << 11U)

/** @brief    Adjust the frame length */
#define HSE_IPSEC_OPTION_OUTPUT_FRAME_LEN_ADJUST    ((hseIpsecOptionFlags_t)1U << 12U)

/** @brief    Override the DF bit */
#define HSE_IPSEC_OPTION_DF_OVERRIDE                ((hseIpsecOptionFlags_t)1U << 13U)

/** @brief    The value to override the DF bit with, if #HSE_IPSEC_OPTION_DF_OVERRIDE is set */
#define HSE_IPSEC_OPTION_DF_OVERRIDE_VALUE_0        ((hseIpsecOptionFlags_t)0U << 14U)
#define HSE_IPSEC_OPTION_DF_OVERRIDE_VALUE_1        ((hseIpsecOptionFlags_t)1U << 14U)

/** @brief    Enable NAT */
#define HSE_IPSEC_OPTION_NAT                        ((hseIpsecOptionFlags_t)1U << 15U)

/** @brief    Update the UDP checksum, if NAT is on (#HSE_IPSEC_OPTION_NAT is set)*/
#define HSE_IPSEC_OPTION_UDP_CHECKSUM               ((hseIpsecOptionFlags_t)1U << 16U)

/** @brief    Update the ether type */
#define HSE_IPSEC_OPTION_ETHER_TYPE_UPDATE          ((hseIpsecOptionFlags_t)1U << 17U)

/*==================================================================================================
*                                             ENUMS
==================================================================================================*/

/*==================================================================================================
                                 STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/

/**
* @brief          HSE IPSEC acceleration initialization service.
* @details
*/
typedef struct
{
    /** @brief   INPUT: Specifies the context to use to store the IPSEC state of this SA.*/
    hseIpsecSaId_t              saId;

    /** @brief   INPUT: Security parameter index of this SA.*/
    uint32_t                    spi;

    /** @brief   INPUT: Initial sequence number.*/
    uint32_t                    seqNum;

    /** @brief   INPUT: Key handle for encryption/decryption.*/
    hseKeyHandle_t              cipherKeyHandle;

    /** @brief   INPUT: Key handle for tag generation/verification.*/
    hseKeyHandle_t              authKeyHandle;

    /** @brief   INPUT: IPSEC cipher suite used.*/
    hseIpsecSuite_t             ipsecSuite;

    /** @brief   INPUT: The IANA type of the next header.*/
    uint8_t                     nextHeader;

    /** @brief   INPUT: Offset of the next header.*/
    uint8_t                     nextHeaderOffset;

    /** @brief   INPUT: Offset of the outer IP header.*/
    uint8_t                     actualOuterIpHeaderOffset;

    uint8_t                     reserved1;

    /** @brief   INPUT: IP header length.*/
    uint16_t                    ipHeaderLen;

    /** @brief   INPUT: Pointer to the IP header for the output frame.*/
    HOST_ADDR                   pIpHeader;

    /** @brief   INPUT: Extended sequence number.*/
    uint32_t                    esn;

    /** @brief   INPUT: Pointer to the initialization vector.*/
    HOST_ADDR                   pIv;

    /** @details   INPUT: Salt used, where applicable, formated as a uint32_t
     *                  Salts less then 4 bytes must be placed in the least significant bytes
     *                  of the salt field */
    uint32_t                    salt;

    /** @brief   INPUT: CTR/CCM initial count.*/
    uint32_t                    initialCount;

    /** @brief   INPUT: CTR nonce.*/
    uint32_t                    nonce;

    /** @brief   INPUT: IPSEC type - Transport/Tunnel, Encap/Decap.*/
    hseIpsecType_t              ipsecType;

    /** @brief   INPUT: Anti-replay window size. 0 - disables anti-replay protection.
     *                  Any other number is rounded up to the next power of two. Numbers
     *                  higher than 128 are rounded down to 128.*/
    uint8_t                     antiReplayWindowSize;

    uint8_t                    reserved2[2];
    /** @brief   INPUT: IPSEC type - Transport/Tunnel, Encap/Decap.*/
    hseIpsecOptionFlags_t       ipsecOptionFlags;
} hseIpsecInitSrv_t;

/**
* @brief          HSE IPSEC acceleration frame processing service.
*/
typedef struct
{
    /** @brief   INPUT: Specifies the context to use to store the IPSEC state of this SA.*/
    hseIpsecSaId_t              saId;

    /** @brief   INPUT: Input frame length.*/
    uint16_t                    inputFrameLength;

    /** @brief   INPUT: Whether to override SA params set at init, for this frame only.*/
    bool_t                      bOverrideInitParams;

    /** @brief  INPUT: Specify if #pInputFrame/#pOutputFrame are provided as hseScatterList_t list (the host address points to a hseScatterList_t list).
     *                 Ignored if SGT is not supported.
     *                 @note
     *                 - If scatter option is selected (set), the length (e.g. #inputFrameLength) shall specified the entire message length
     *                 (sum of all hseScatterList_t lengths).
     *                 - The number for SGT entries shall be less then #HSE_MAX_NUM_OF_SGT_ENTRIES. */
    hseSGTOption_t              sgtOption;

    /** @brief   INPUT: The location of the input frame.*/
    HOST_ADDR                   pInputFrame;

    /** @brief   INPUT: The capacity of the output frame.*/
    uint16_t                    maxOutputFrameLength;
    uint8_t                     reserved1[2];
    /** @brief   OUTPUT: The location of the output frame.*/
    HOST_ADDR                   pOutputFrame;

    /** @brief   INPUT: The override parameter values.
     *  @note
     * - Not all parameters are relevant for all IPSEC types. The relevant params for each IPSEC type are:
     *       - HSE_IPSEC_TRANSPORT_ENCAP:  nextHeader, nextHeaderOffset, ipHeaderLen, bOverrideEcn, ecn
     *       - HSE_IPSEC_TRANSPORT_DECAP:  nextHeaderOffset, ipHeaderLen, bOverrideEcn, ecn
     *       - HSE_IPSEC_TUNNEL_ENCAP:     pIpHeader, nextHeader, ipHeaderLen, ipHeaderSource
     *       - HSE_IPSEC_TUNNEL_DECAP:     pIpHeader, ipHeaderLen, ipHeaderSource
     *  - Not relevant parameters are ignored.
     *  - Overriding is all or nothing. With the exception of ecn (which has a specific flag),
     *    if overriding is enabled, and a parameter is relevant to the IPSEC type, it will be overridden
     *    with the value found here. */
    struct
    {
        /** @brief   INPUT: Override value for the IANA type of the next header.*/
        uint8_t                     nextHeader;

        /** @brief   INPUT: Override value for offset of the next header.*/
        uint8_t                     nextHeaderOffset;

        /** @brief   INPUT: Override value for the offset of the outer IP header.*/
        uint8_t                     actualOuterIpHeaderOffset;

        uint8_t                     reserved2[2];

        /** @brief   INPUT: Override value for IP header length.*/
        uint8_t                     ipHeaderLen;

        /** @brief   INPUT: Whether to override ECN.*/
        bool_t                      bOverrideEcn;

        /** @brief   INPUT: Override value for ECN (0 - 3).*/
        uint8_t                     ecn;

        /** @brief   INPUT: Override value for the IP header source.
         *  Only #HSE_IPSEC_OPTION_IP_HDR_SRC_CONTEXT and #HSE_IPSEC_OPTION_IP_HDR_SRC_FRAME are allowed here */
        hseIpsecOptionFlags_t    ipHeaderSource;

    } overrideParams;
} hseIpsecProcessSrv_t;

/**
* @brief          Get the current sequence number of the indicated SA.
* @note           Service is only allowed on outgoing SAs (type is either HSE_IPSEC_TYPE_TRANSPORT_ENCAP
*                 or HSE_IPSEC_TYPE_TUNNEL_ENCAP). It does not make sense for incoming SAs, as IP packets
*                 can arrive out of order.
*/
typedef struct
{
    /** @brief   INPUT: Specifies the context to use to store the IPSEC state of this SA.*/
    hseIpsecSaId_t              saId;

    /** @brief   INPUT: Whether we are managing the extended sequence number. 0 - regular SN, 1 - ESN
     *  @note The extended sequence number is not supported.
    */
    bool_t                      bExtendedSeqNum;

    uint8_t                     reserved[3];

    /** @brief   OUTPUT: Where to write the sequence number.*/
    HOST_ADDR                   pSeqNum;
} hseIpsecGetSeqNumSrv_t;

/**
* @brief          Set the current sequence number of the indicated SA.
* @note           Service is only allowed on outgoing SAs (type is either HSE_IPSEC_TYPE_TRANSPORT_ENCAP
*                 or HSE_IPSEC_TYPE_TUNNEL_ENCAP). It does not make sense for incoming SAs, as IP packets
*                 can arrive out of order.
*/
typedef struct
{
    /** @brief   INPUT: Specifies the context to use to store the IPSEC state of this SA.*/
    hseIpsecSaId_t              saId;

    /** @brief   INPUT: Whether we are managing the extended sequence number. 0 - regular SN, 1 - ESN
     *  @note The extended sequence number is not supported.
     */
    bool_t                      bExtendedSeqNum;

    uint8_t                     reserved[3];

    /** @brief   INPUT: The sequence number to set. */
    uint32_t                    seqNum;
} hseIpsecSetSeqNumSrv_t;

/** @} */
#endif

#ifdef HSE_SPT_SELF_TEST
/*==================================================================================================
*                                      DEFINES AND MACROS
==================================================================================================*/
/**<@brief Self-test capabilities mask. */
typedef uint64_t hseSelfTestMask_t;
#define HSE_ST_FW_INTEGRITY         ((hseSelfTestMask_t)(1ULL << 0U))     /**<@brief Verify HSE Firmware Integrity */
#if defined(HSE_SPT_RANDOM)
#define HSE_ST_RNG_ENGINE           ((hseSelfTestMask_t)(1ULL << 1U))     /**<@brief Random Number Generator */
#endif /* defined(HSE_SPT_RANDOM) */
#if defined(HSE_SPT_AES)
#define HSE_ST_AES_ENGINE           ((hseSelfTestMask_t)(1ULL << 2U))     /**<@brief Advanced Encryption Standard Hardware Accelerator */
#endif /* defined(HSE_SPT_AES) */
#if defined(HSE_SPT_HASH)
#define HSE_ST_HASH_ENGINE          ((hseSelfTestMask_t)(1ULL << 3U))     /**<@brief Hash Generator */
#endif /* defined(HSE_SPT_HASH) */
#if defined(HSE_SPT_CRC32)
#define HSE_ST_CRC_ENGINE           ((hseSelfTestMask_t)(1ULL << 4U))     /**<@brief Cyclic-Redundancy Check Hardware Accelerator */
#endif /* defined(HSE_SPT_CRC32) */
#if defined(HSE_SPT_RSA)
#define HSE_ST_RSA_ENGINE           ((hseSelfTestMask_t)(1ULL << 5U))     /**<@brief Rivest-Shamir-Adleman Hardware Accelerator */
#endif /* defined(HSE_SPT_RSA) */
#if defined(HSE_SPT_ECC)
#define HSE_ST_ECC_ENGINE           ((hseSelfTestMask_t)(1ULL << 6U))     /**<@brief Elliptic Curve Cryptography Hardware Accelerator */
#endif /* defined(HSE_SPT_ECC) */
#if defined(HSE_SPT_HMAC)
#define HSE_ST_HMAC_ENGINE          ((hseSelfTestMask_t)(1ULL << 7U))     /**<@brief Hash-Based Message Authentication Code Hardware Accelerator */
#endif /* defined(HSE_SPT_HMAC) */
/*==================================================================================================
*                                             ENUMS
==================================================================================================*/

/*==================================================================================================
                                 STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/
/** @brief Self Test service.
 *  @details Performs a self-test on a specific security block or a full self-test.
 *  @note - During the self-test operation, the HSE firmware cannot be interrupted by another request
 *         (until the operation is completed).
 *        - The requested self-tests must be supported; otherwise, the self-test service returns the
 *          #HSE_SRV_RSP_NOT_ALLOWED status (no requested self-tests will be executed).
 *        - If one of the check fails, the HSE firmware returns #HSE_SRV_RSP_GENERAL_ERROR and goes to
 *          shutdown (a fatal error occurred). In this case, the application must perform a system reset.
 *        - The #HSE_ST_FW_INTEGRITY flag checks the integrity of HSE FW and runtime SYS-IMG (if present) inside HSE.
 *        - At first request for #HSE_ST_FW_INTEGRITY the hash over HSE FW will be computed,
 *          verification being done in the subsequent requests. */
typedef struct
{
    /** @brief   INPUT:  Select bits to run a specific self-test.
     *                   (note that the selected bits should map the supported self-tests).
     *                   All bits zero means that a full self-test will be performed. */
    hseSelfTestMask_t    selfTest;
    /** @brief   OUTPUT: The address where the self-tests results bit mask is returned (points to a #hseSelfTestMask_t type).
     *                   If one of the requested self-tests failed, HSE returns #HSE_SRV_RSP_GENERAL_ERROR
     *                   and the corresponding bit for the failing test is set to one.
     *                   If all the self-tests passed, HSE returns #HSE_SRV_RSP_OK and this field can be ignored. */
    HOST_ADDR            pTestResultsBitMask;
} hseSelfTestSrv_t;

/** @} */
#endif

#ifdef HSE_SPT_MONOTONIC_COUNTERS
/*==================================================================================================
*                                      DEFINES AND MACROS
==================================================================================================*/

#if defined(HSE_SPT_FLASHLESS_DEV)
/** @brief  The size of the NVM container for the Monotonic Counter table (in bytes).*/
#define HSE_NVM_CONTAINER_CNT_TBL_SIZE   ((HSE_NUM_OF_MONOTONIC_COUNTERS * sizeof(uint64_t)) + 48U)

/** @brief  Publish or load the NVM container for the Monotonic Counter table. */
typedef uint8_t hseNvmCntTblAction_t;
#define HSE_NVM_CNT_TBL_ACTION_PUBLISH   ((hseNvmCntTblAction_t)0x01U)     /**< @brief  Publish the Nvm Container for the Monotonic Counter table. */
#define HSE_NVM_CNT_TBL_ACTION_LOAD      ((hseNvmCntTblAction_t)0x02U)     /**< @brief  Load the Nvm Container for the Monotonic Counter table. */
#endif /* HSE_SPT_FLASHLESS_DEV */

/*==================================================================================================
*                                             ENUMS
==================================================================================================*/

/*==================================================================================================
                                 STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/

/**
 * @brief Increment a monotonic counter service with a specific value.
 * @details
 *         - For HSE_H/M, the counters are volatile. Host application has to publish/load
 *           the monotonic counter table using hsePublishLoadCntTblSrv_t service.
 *         - For HSE_B, the host application shall use the hseConfigSecCounterSrv_t service
 *           to initialize and configure the secure counters.
 *         - If the counter is saturated, an error is reported. */
typedef struct
{
    /** @brief   INPUT: The counter Index. */
    uint32_t                counterIndex;
    /** @brief   INPUT: The value to be added. */
    uint32_t                value;
}hseIncrementCounterSrv_t;

/** @brief Read a monotonic counter service. */
typedef struct
{
    /** @brief   INPUT: The counter Index. */
    uint32_t                counterIndex;
    /** @brief   OUTPUT: The address where the counter value is returned (a uint64_t value). */
    HOST_ADDR               pCounterVal;
} hseReadCounterSrv_t;


#if defined(HSE_SPT_FLASHLESS_DEV)
/**
 * @brief    Publish or load the monotonic counter table.
 * @details   This is supported only for HSE_H/M devices and should be used to publish/load
 *            the monotonic counter table in NVM
 * */
typedef struct
{
    /** @brief  INPUT:   Publish/load the NVM container for the Monotonic Counter table. */
    hseNvmCntTblAction_t    action;
    uint8_t                 reserved[3];
    /** @brief  OUTPUT:  The address of the NVM container for the Monotonic Counter table.
     *                   The size of the NVM container is #HSE_NVM_CONTAINER_CNT_TBL_SIZE. */
    HOST_ADDR               pNvmContainerCntTbl;
} hsePublishLoadCntTblSrv_t;
#endif /* HSE_SPT_FLASHLESS_DEV */


/**
 * @brief   Initialize and configure a secure counter.
 * @details HSE supports 16 X 64 bits secure counters, each counter having associated a CounterIndex from 0 to 15.
 *          By default, all the counters are disabled.  <br>
 *          The secure counter (SC) consists of 2 separate bitfields: Rollover Protection (RP) + Volatile Counter (VC).
 *          HSE stores the secure counter in data flash each time the Rollover Protection (RP) is updated.  <br>
 *          The purpose of this service is to enable the secure counter and configure the Rollover Protection bitfield size.
 *          The objective is to reduce the rate at which NVM programming operations occur.  <br>
 *          If the secure counter is already configured and this service is called, HSE re-configures the counter
 *          with the new Rollover Protection (RP) and reset it to 0.
 *         @note
 *         - SuperUser rights are needed to configure/enable the monotonic counters.
 *         - For HSE_B (devices with internal flash)
 *              - WARNING: The HSE erases a flash sector after 511 Rollover Protection updates in data flash.  <br>
 *              The number of data flash erases is limited to 100.000. The application shall configure each secure counter
 *              depending on the SC update rate and the number of enabled counters.
 *              - The secure counter configuration is stored in data flash each time hseConfigSecCounterSrv_t is called.
 *              - If RPBitSize = 64bits, the HSE stores the SC in flash each time is updated.
 *         - For HSE_H/M (flashless devices)
 *              - The RPBitSize is configured for all the enabled secure counters. If the RP of a counter is updated, a warning event is trigger
 *                called #HSE_WA_PUBLISH_COUNTER_TBL through MUB_GSR register. The application shall clear the warning bit (W1C) and
 *                use the #hsePublishLoadCntTblSrv_t service to publish and store the counter table in the external flash.
 *                Note that the counter table must be loaded at initialization time by the application (anti-rollback protection is not supported).
 *
 *         Example:
 *         Let's consider the RPBitSize = 40bits and SC = 0x0000000000000001.  <br>
 *         This means Rollover Protection (40bits) + Volatile Counter (24bits).  <br>
 *         The secure counter (SC) will be stored in flash if the incremental value is >= 0xFFFFFF. Otherwise, the counter will be updated but not stored.  <br>
 *         SC = 0x0000000000000001+0xFFFFFF = 0x0000000001000000 (RP was changed)
 */
typedef struct
{
    /** @brief   INPUT: - For HSE_B, specifies the counter Index.
     *                  - For HSE_H/M, specifies the number of counters to be enabled (max 16). E.g. if it is set to 5,
     *                    the counters with the index from 0 to 4 are enabled. */
    uint32_t                counterIndex;
    /** @brief   INPUT: The Rollover Protection bit size (refer to service comments). It shall be >= 32 bits and <= 64 bits. */
    uint8_t                 RPBitSize;
    uint8_t                 reserved[3];
} hseConfigSecCounterSrv_t;

/** @} */

#endif

#ifdef HSE_SPT_OTA_FIRMWARE_UPDATE

/*==================================================================================================
                                 STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/

#if defined(HSE_SPT_FLASHLESS_DEV)
/**
 * @brief   HSE_H/M Firmware Update Service.
 * @details This service is used to re-encrypt the current running HSE FW image or
 *          the HSE firmware delivered by NXP (pink image) with a device-specific key. <br>
 *          The re-encrypted image (blue image) is published back on system RAM.
 *          The re-encryption operation can be performed in place by overwriting the pink image
 *          (the application can use the same pink image buffer for the output).
 *          @note
 *          -  The HSE firmware boot can be protected against rollback attack only if it boots a blue image. This protection
 *             at boot does not exist if IVT is pointing to a pink image. It is possible to enforce a boot to blue image via HSE
 *             system attributes (refer to hseOtpRollbackProtectionPolicy_t attribute). As long as the HSE SYS-IMG is
 *             available, it can prevent the HSE executing a pink image, hence bypassing the rollback protection. The HSE
 *             always ensure that the rollback counter value in the blue image is above or equal to the rollback counter infuse
 *          -  If the OTP rollback protection is not disabled (refer to #hseOtpRollbackProtectionPolicy_t attribute),
 *             to be able to update fuse counter, the VDD_EFUSE supply must be powered at start-up before fuses
 *             are written (refer to HSE FW Reference Manual). The anti-rollback counter is incremented in fuses at start-up.
 *             After writing the updated current/blue FW image in the external flash, a reset is needed.
 *             The VDD_EFUSE state is checked before the fuse write by reading the NCSPD_STAT register of the on-chip PMC module.
 *             The application shall provide read-only access (xRDC restriction) to HSE to read the NCSPD_STAT register.
 *             The rollback counter is NOT updated in fuses when LC == CUST_DEL and BOOT_SEQ == 0.
 *             If the rollback counter is saturated, the HSE firmware can still be updated, but without rollback protection.
 *
 */
typedef struct
{
    /** @brief  INPUT:    The length in bytes of the new NXP Firmware file.
     *                    It represents the length of new NXP Firmware file to be re-encrypted with a device-specific key.
     *                    - If "#inFwFileLength == 0", then the pInFwFile parameter is ignored and an encrypted version of the currently running HSE FW image
     *                    will be generated with a device-specific key (generate the blue firmware image of the currently running HSE FW image).
     *                    - If "#inFwFileLength != 0", then #inFwFileLength must be equal with the new NXP firmware image (pink image) size.*/
    uint32_t                inFwFileLength;

    /** @brief  INPUT:    The address of new version of HSE Firmware file to be re-encrypted with a device specific key (#inFwFileLength != 0). */
    HOST_ADDR               pInFwFile;

    /** @brief  INPUT:    The address where the length (an uint32_t value) of the buffer will be provided.
     *                    - If "#inFwFileLength == 0", then the buffer length must be equal to at least the size obtained by getting the attribute #HSE_FW_SIZE_ATTR_ID.
     *                    - If "#inFwFileLength != 0", then the buffer length must be equal to or greater than #inFwFileLength.
     *                    - If the size of the buffer is less than the expected size of HSE_H/M FW file an error will be returned.
     *          OUTPUT:   The HSE FW will return the total length of the image which have been published.
    */
    HOST_ADDR               pFwBufferLength;

    /** @brief  INPUT:    It is the address of the buffer where the encrypted version of HSE_H/M FW file (with a device specific key) will be stored.*/
    HOST_ADDR               pOutFwBuffer;
} hseFirmwareUpdateSrv_t;
#endif /* HSE_SPT_FLASHLESS_DEV */


#if defined(HSE_B)
/**
 * @brief   HSE_B Firmware Update Service.
 * @details This service is used to update the HSE firmware into the HSE internal flash memory.
 *
 *  The table below summarizes which fields are used by each access mode.
 *  Unused fields are ignored by the HSE.
 *
 *  |Field / Mode       | One-pass  | Start | Update  | Finish  |
 *  |----------------- :|:---------:|:-----:|:-------:|:-------:|
 *  | accessMode        |     *     |   *   |    *    |    *    |
 *  | streamLength      |           |   *   |    *    |    *    |
 *  | pInFwFile         |     *     |   *   |    *    |    *    |
 */
typedef struct
{
    /** @brief  INPUT:   Specifies the access mode: ONE-PASS, START, UPDATE, FINISH.*/
    hseAccessMode_t          accessMode;
    uint8_t                  reserved[3];

    /** @brief  INPUT:   The length in bytes of a chunk. It is used only for STREAMING mode. It must be at least 64 bytes or multiple of 64 bytes;
     *                   otherwise, an HSE error is returned.
     *                   - START mode:  must be multiple of 64bytes.
     *                   - UPDATE mode: must be multiple of 64bytes.
     *                   - FINISH mode: can be any value.*/
    uint32_t                 streamLength;

    /** @brief  INPUT:   ONE-PASS  USAGE: The address of new version of HSE Firmware file to be updated into the HSE internal flash memory.<br>
     *                   STREAMING USAGE: The address of chunk to be updated into the HSE internal flash memory. */
    HOST_ADDR                pInFwFile;
}hseFirmwareUpdateSrv_t;
#endif /* defined(HSE_B) */

/** @} */
#endif

#ifdef HSE_SPT_OTA_SBAF_UPDATE

/*==================================================================================================
                                 STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/

#if defined(HSE_B)
#if defined(HSE_SPT_OTA_SBAF_UPDATE)
/**
 * @brief   SBAF Update Service.
 * @details This service is used to update the SBAF firmware into the HSE internal flash memory.\
 *          Sbaf update supports both One-pass and streaming mode, We recommend to use One-pass\
 *          mode for sbaf update.
 *
 *  The table below summarizes which fields are used by each access mode.
 *  Unused fields are ignored by the HSE.
 *
 *  |Field / Mode       | One-pass  | Start | Update  | Finish  |
 *  |----------------- :|:---------:|:-----:|:-------:|:-------:|
 *  | accessMode        |     *     |   *   |    *    |    *    |
 *  | streamLength      |           |   *   |    *    |    *    |
 *  | pInFwFile         |     *     |   *   |    *    |    *    |
 *
 * @note  After successful SBAF update, application should issue a reset to the device.
 */
typedef struct
{
/** @brief  INPUT:   Specifies the access mode: ONE-PASS, START, UPDATE, FINISH. <br> */
hseAccessMode_t          accessMode;
uint8_t                  reserved[3];
/** @brief  INPUT:   The length in bytes of a chunk. It is used only for STREAMING mode. It must be at least 64bytes or multiple of 64bytes,
 *                   otherwise an HSE error is returned.
 *                   - START mode:  must be multiple of 64bytes.
 *                   - UPDATE mode: must be multiple of 64bytes.
 *                   - FINISH mode: can be any value.*/
uint32_t                 streamLength;
/** @brief  INPUT:   ONE-PASS  USAGE:The address of new version of SBAF Firmware file to be updated into the HSE internal flash memory.<br>
 *                   STREAMING USAGE: The address of chunk to be updated into the HSE internal flash memory. */
HOST_ADDR                pInFwFile;
}hseSbafUpdateSrv_t;
#endif /* HSE_SPT_OTA_SBAF_UPDATE */
#endif /* defined(HSE_B) */
/*==================================================================================================
                                 GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/

/*==================================================================================================
                                     FUNCTION PROTOTYPES
==================================================================================================*/


/** @} */
#endif

#if defined(HSE_SPT_KEY_GEN) || defined(HSE_SPT_COMPUTE_DH)

/*==================================================================================================
*                                             ENUMS
==================================================================================================*/
/** @brief HSE Key Generate schemes. */
typedef uint8_t hseKeyGenScheme_t;
#ifdef HSE_SPT_SYM_RND_KEY_GEN
#define HSE_KEY_GEN_SYM_RANDOM_KEY                   1U /**< @brief Generate a random symmetric key (e.g AES, HMAC). */
#endif /* HSE_SPT_SYM_RND_KEY_GEN */

#ifdef HSE_SPT_RSA_KEY_PAIR_GEN
#define HSE_KEY_GEN_RSA_KEY_PAIR                     2U /**< @brief Generate a RSA key pair. */
#endif /* HSE_SPT_RSA_KEY_PAIR_GEN */

#ifdef HSE_SPT_ECC_KEY_PAIR_GEN
#define HSE_KEY_GEN_ECC_KEY_PAIR                     3U /**< @brief Generate a ECC key pair. */
#endif /* HSE_SPT_ECC_KEY_PAIR_GEN */

#ifdef HSE_SPT_CLASSIC_DH_KEY_PAIR_GEN
#define HSE_KEY_GEN_CLASSIC_DH_KEY_PAIR              4U /**< @brief Generate a Classic-DH key pair. */
#endif /* HSE_SPT_CLASSIC_DH_KEY_PAIR_GEN */

#ifdef HSE_SPT_TLS12_RSA_PRE_MASTER_SECRET_GEN
#define HSE_TLS12_RSA_PRE_MASTER_SECRET_GEN          5U /**< @brief Generate the pre-master secret for TLS 1.2 RSA key exchange. */
#endif /* HSE_SPT_TLS12_RSA_PRE_MASTER_SECRET_GEN */

/*==================================================================================================
                                 STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/
#ifdef HSE_SPT_RSA_KEY_PAIR_GEN
/** @brief RSA key generate scheme.
 *  @details It generates a RSA key pair.
 *           Note that the public modulus can be exported to HOST via this service or using the export key service. */
typedef struct
{
    /** @brief   INPUT: The length of public exponent "e". Should not be more than 16 bytes */
    uint32_t             pubExpLength;
    /** @brief   INPUT: The public exponent "e". */
    HOST_ADDR            pPubExp;
    /** @brief   OUTPUT: The  public modulus n. It can be NULL (the modulus is not provided using this service).
     *                   The size of this memory area must be at least the byte length of the public modulus. */
    HOST_ADDR            pModulus;
} hseKeyGenRsaScheme_t;
#endif /* HSE_SPT_RSA_KEY_PAIR_GEN */


#ifdef HSE_SPT_ECC_KEY_PAIR_GEN
/** @brief   ECC Key Generate scheme.
 *  @details It generates a ECC key pair.
 *           @note
 *           - the curve ID is specified by the keyInfo.specific.eccCurveId parameter.
 *           - Note that the public key can be exported to HOST via this service or using the export key service.*/
typedef struct
{
    /** @brief   OUTPUT: Where to store the public key. If the public key is not needed at this point, pass a NULL pointer. <br>
     *                   The x and y coordinate of the public key will be passed concatenated one after another, as big-endian
     *                   strings. The size of the buffer must be double the byte length of the prime n. */
    HOST_ADDR            pPubKey;
} hseKeyGenEccScheme_t;
#endif /* HSE_SPT_ECC_KEY_PAIR_GEN */


#ifdef HSE_SPT_CLASSIC_DH_KEY_PAIR_GEN
/** @brief    DH Key Pair Generation service.
 *  @details  It computes: y = g^x mod p
 *            where:
 *            - g is the public base
 *            - p is the public modulus
 *            - x is the private key
 *            - y is the public key
 *  */
typedef struct
{
    /** @brief   INPUT: The length of public base "g". */
    uint32_t            baseGLength;
    /** @brief   INPUT: The base g as big-endian integer. */
    HOST_ADDR           pBaseG;
    /** @brief   INPUT: The length of modulus "p". */
    uint32_t            modulusLength;
    /** @brief   INPUT: The modulus p as big-endian integer. */
    HOST_ADDR           pModulus;
    /** @brief   OUTPUT: The public Key. It can be NULL (the public key is not provided using this service). <br>
     *                   The size of this memory area must be at least the byte length of the public modulus p. */
    HOST_ADDR           pPubKey;
} hseKeyGenClassicDhScheme_t;
#endif /* HSE_SPT_CLASSIC_DH_KEY_PAIR_GEN */

#ifdef HSE_SPT_TLS12_RSA_PRE_MASTER_SECRET_GEN

/** @brief   Generate the pre-master secret for TLS 1.2 RSA key exchange.
 *  @details It computes the pre-master secret for TLS 1.2 RSA key exchange as specified by rfc5246(TLS 1.2):
 *           - The hseKeyGenerateSrv_t#targetKeyHandle must be a #HSE_KEY_TYPE_SHARED_SECRET key slot.
 *           - The hseKeyGenerateSrv_t#keyInfo must have the following key flags set: #HSE_KF_USAGE_DERIVE, #HSE_KF_ACCESS_EXPORTABLE.
 *           - The rfc5246 specification is used:
 *                  - keyInfo#keyBitLen must be 384bits (48bytes)
 *                  - The pre-master secret is computed as ProtocolVersion (2bytes) concatenated with 46 byte random number. The ProtocolVersion = {3,3} for TLS 1.2.
 *           - To encrypt the generated pre-master secret, the #hseExportKeySrv_t service with (the proper RSA scheme) must be used.
 *             The encrypted pre-master secret is sent to the peer node.
 *           - To decrypt an encrypted pre-master secret, the #hseImportKeySrv_t service (with the proper RSA scheme) must be used. The destination key slot
 *             can be a #HSE_KEY_TYPE_SHARED_SECRET (with #HSE_KF_USAGE_DERIVE key flag set) that further can be used to derive the TLS 1.2 key_block.
 *           - To generate the master secret the #hseKdfTLS12PrfScheme_t service must be used.
 *
 *          @note
 *          - This service can also be used to perform the RSA_PSK key exchange as specified by rfc4279. In the same manner as explained above,
 *            it can be used to generate the input needed for RSA encryption (see EncryptedPreMasterSecret).
 *            The EncryptedPreMasterSecret can be generated using the #hseExportKeySrv_t service (on the client side),
 *            and imported using the the #hseImportKeySrv_t service (on the server side).
 *            In this case, to generate the master secret the #hseKdfTLS12PrfScheme_t
 *            service must be executed using the tlsPskUsage = #HSE_TLS_KEY_EXCHANGE_RSA_PSK option.
 */
typedef struct
{
    /** @brief   INPUT: The TLS or DTLS version.
     *                   E.g. for TLS1.2 must be {3, 3}; for DTLS1.2 must be { 254, 253 }
     *                   @note
     *                   HSE does not check the provided values;it just concatenates the protocol version with 46 byte random number.
     * */
    uint8_t        protocolVersion[2U];
    /** @brief   Reserved for future use. */
    uint8_t        reserved[2U];
} hseKeyGenTls12RsaPreMaster_t;
#endif /*HSE_SPT_TLS12_RSA_PRE_MASTER_SECRET_GEN*/

/*-------------------------------SERVICES DEFINITION----------------------------------------------*/

#ifdef HSE_SPT_KEY_GEN
/** @brief HSE Key generate service.
 *  @details It can be used to generate a key pair (e.g. public and private RSA, ECC, classic DH)
 *           or a random symmetric key.
 *  @note
 *  - Key flags (of key properties) are always applied.
 *  - The keys can be generated as follow:
 *  1. SuperUser key restrictions:
 *      - NVM keys can only be generated in empty slots (an erase shall be performed in advance)
 *      - RAM keys can always be generated (RAM keys can be overwritten)
 *  2. User key restrictions:
 *      - NVM keys can NOT be generated.
 *      - RAM keys can always be generated (RAM keys can be overwritten)
 *  */
typedef struct
{
    /** @brief   INPUT: The target key handle (where to store the new key). */
    hseKeyHandle_t      targetKeyHandle;
    /** @brief   INPUT:  Specifies usage flags, restriction access, key bit length etc for the key.
     *                   @note
     *                   - For random symmetric key, the key length in bits should be specified by keyBitLen.
     *                   - For RSA, keyBitLen specifies the bit length of the public modulus which shall be generated.
     *                   - For ECC, the keyInfo should specify the ECC curve ID and the length of the base point order.
     *                   - For RSA TLS 1.2 pre-master secret, see the #hseKeyGenTls12RsaPreMaster_t notes.
     *                   - For classic DH, the keyBitLen specifies the bit length of the public modulus.*/
    hseKeyInfo_t        keyInfo;
    /** @brief   INPUT: Specifies the key generation scheme (e.g random sym key, rsa key pair, ecc key pair,
     *                                                       RSA TLS 1.2 pre-master secret, classic-DH key pair). */
    hseKeyGenScheme_t   keyGenScheme;
    uint8_t             reserved[3];
    /** @brief   INPUT: The selected scheme parameters. */
    union
    {
    #ifdef HSE_SPT_SYM_RND_KEY_GEN
        /** @brief   INPUT: No scheme (parameter) is used for random symmetric key. */
        hseNoScheme_t              symKey;
    #endif /* HSE_SPT_SYM_RND_KEY_GEN */
    #ifdef HSE_SPT_RSA_KEY_PAIR_GEN
        /** @brief   INPUT: The scheme used to generate a RSA key pair. */
        hseKeyGenRsaScheme_t       rsaKey;
    #endif /* HSE_SPT_RSA_KEY_PAIR_GEN */
    #ifdef HSE_SPT_ECC_KEY_PAIR_GEN
        /** @brief   INPUT: The scheme used to generate a ECC key pair. */
        hseKeyGenEccScheme_t       eccKey;
    #endif /* HSE_SPT_ECC_KEY_PAIR_GEN */
    #ifdef HSE_SPT_TLS12_RSA_PRE_MASTER_SECRET_GEN
        /** @brief   INPUT: The scheme used to generate the Rsa pre-master secret. */
        hseKeyGenTls12RsaPreMaster_t rsaPreMaster;
    #endif /* HSE_SPT_TLS12_RSA_PRE_MASTER_SECRET_GEN */
    #ifdef HSE_SPT_CLASSIC_DH_KEY_PAIR_GEN
        /** @brief   INPUT: The scheme used to generate a Classic-DH key pair. */
        hseKeyGenClassicDhScheme_t classicDhKey;
    #endif /* HSE_SPT_CLASSIC_DH_KEY_PAIR_GEN */
    }sch;
} hseKeyGenerateSrv_t;
#endif /* HSE_SPT_KEY_GEN */



#ifdef HSE_SPT_COMPUTE_DH
/** @brief DH Compute Shared Secret service.
 *  @details Computes the Diffie-Hellman share secret for ECC or classic DH (e.g. the key exchange protocol). <br>
 *           The share secret can only be computed in a shared secret slot, and can not be exported.
 *  */
typedef struct
{
    /** @brief   INPUT: The target key handle (where to store the shared secret).
     *                  It must specify a #HSE_KEY_TYPE_SHARED_SECRET key slot. */
    hseKeyHandle_t      targetKeyHandle;
    /** @brief   INPUT: The private key. */
    hseKeyHandle_t      privKeyHandle;
    /** @brief   INPUT: The peer public key. Must be previously imported into the HSE. <br>
     *                  Note that the peer public key can also be imported as a *_PUB_EXT key type (external public key stored on the application NVM) */
    hseKeyHandle_t      peerPubKeyHandle;
} hseDHComputeSharedSecretSrv_t;
#endif /* HSE_SPT_COMPUTE_DH */

#ifdef HSE_SPT_BURMESTER_DESMEDT
/** @brief HSE Burmester-Desmedt steps.
 */
typedef uint8_t hseBDStep_t;
#define HSE_BD_STEP_COMPUTE_SECOND_PUBLIC_KEY     0U /**< @brief Burmester-Desmedt second public key computation step, as described by the service. */
#define HSE_BD_STEP_COMPUTE_SHARED_SECRET         1U /**< @brief Burmester-Desmedt shared secret generation step, as described by the service. */

/** @brief   The ECC variant Burmester-Desmedt Protocol service to compute a share secret.
 *  @details The Burmester-Desmedt Protocol protocol is an extention to the Diffie-Hellman key-agreement protocol.
 *           It allows to establish a shared secret key for a number of participants organized in a "ring".
 *
 *        @note
 *        The following notation is used below:
 *        - The key generation process involves n participants (from 0 to n-1). Participants X_i organize a "ring", so that X_n = X_0.
 *        - All used public keys must be RAM keys.
 *        - i is the index of the current node doing the calculation
 *        - a_i is the private key of the participant with index i
 *        - G is the generator on the elliptic curve
 *        - Z_i is the first public key of the participant with index i
 *        - X_i is the second public key of the participant with index i, computed on the step 2 below.
 *        - K is the shared secret (the coordinates x and y stored in a #HSE_KEY_TYPE_SHARED_SECRET slot)
 *
 *        The Burmester-Desmedt protocol consists of 3 steps:
 *        - STEP 1: Generate of an initial ECC key pair.
 *                  - Z_i = a_i * G
 *                  This step can be performed using #hseKeyGenerateSrv_t service (#HSE_KEY_GEN_ECC_KEY_PAIR scheme) and export the public key.
 *        - STEP 2: Upon receipt of the first public keys from the neighbor participants from the ring (Z_i+1 and Z_i-1), HSE computes the second public keys (X_i):
 *                  - X_i = a_i * (Z_i+1 - Z_i-1)
 *                  E.g. for n=5 participants (from 0 to n-1), the participant i=0 shall compute:
 *                  - X_0 = a_0 * (Z_1 - Z_4)
 *        - STEP 3: Upon receipt of the second public keys of all other participants (X_j, j!=i), the X_i participant shall calculate the shared secret:
 *                  - K = n*a_i*Z_i-1 + for(j=0..n-2){SUM((n-1-j) * X_i+j)}
 *                  E.g. for n=5 participants (from 0 to n-1), the participant i=0 shall compute:
 *                  - K = 5*a_0*Z_4 + 4*X_0 +3*X1 + 2*X_2 + 1*X_3
 *
 *        To perform the Burmester-Desmedt calculation the HSE requires a set of n+1 consecutive ECC public key slots in a single group to store the temporary keys
 *        involved in the calculation. Each key slot must be capable of storing a public key on the curve the negotiation is carried out. There are no specific
 *        requirements other than the capability to hold the temporary keys.
 *        The set of keys is conceptually partitioned as follows:
 *
 *            +-------+-------+-----+-------+-----+-------+-------+
 *            | Z_i-1 | Z_i+1 | X_i | X_i+1 | ... | X_i-3 | X_i-2 |
 *            *-------+-------+-----+-------+-----+-------+-------+
 *
 *        The slots in the set will be indexed here relative to the first slot in the set, regardless of whether the first slot of the set is the first slot
 *        in the key group or not.
 *
 *          - Slot 0 will hold the first public key of the current node's predecessor in the Burmester-Desmedt ring.
 *          - Slot 1 will hold the public key of the current node's successor in the ring.
 *          - Slot 2 will hold the current node's second public key.
 *          - Slots 3 and on will hold the second public keys of the current node's successors in the ring, up to, but excluding, the predecessor.
 *
 *        For example, for node 3 in a BD negotiation with 5 participants (0 - 4), the key set will hold the following keys:
 *
 *            +-----+-----+-----+-----+-----+-----+
 *            | Z_2 | Z_4 | X_3 | X_4 | X_0 | X_1 |
 *            *-----+-----+-----+-----+-----+-----+
 *
 *        To perform the full BD calculation, the user should do the following:
 *
 *          - Generate an ephemeral ECC key pair on the curve the negotiation will be carried out. The is done using the #hseKeyGenerateSrv_t service.
 *              The slot will be referenced by #deviceKeyHandle
 *          - Export the public key from the slot above, using the #hseExportKeySrv_t service. This is the first public key, and should be distributed to
 *              the other nodes in the negotiation. Actual distribution is out of scope of the HSE.
 *          - Import the first public key of the predecessor in the ring, into slot 0 of the key set earmarked for the BD calculation.
 *              Use the #hseImportKeySrv_t service for this. The target key handle will be pubKeyHandle
 *          - Import the first public key of the successor in the ring, into slot 1 of the key group earmarked for the BD calculation.
 *              Use the #hseImportKeySrv_t service for this. The target key handle will be pubKeyHandle + 1
 *          - Compute the second public key of the current node, using the hseBurmesterDesmedtSrv_t service in step HSE_BD_STEP_COMPUTE_SECOND_PUBLIC_KEY.
 *              After the computation, the second public key will be stored in slot 2 of the BD key group.
 *          - Export the node's second public key, via the export service, from target key handle pubKeyHandle + 2,
 *              and distribute it to the other nodes
 *          - Import the the other needed second public keys into slots 3 and up of the BD key group.
 *          - Compute the BD shared secret, using the hseBurmesterDesmedtSrv_t service in step HSE_BD_STEP_COMPUTE_SHARED_SECRET.
 *              The BD shared secret is an ECC public key, so the target slot must be able to hold a key of twice the curve size, in bits
 *              ( e.g. for a BD negotiation on a 256 bit ECC curve, the shared secret key slot must be at least 512 bits wide)
 * */
typedef struct
{
    /** @brief   INPUT: The current step of the BD calculation. Can be either HSE_BD_STEP_COMPUTE_SECOND_PUBLIC_KEY or HSE_BD_STEP_COMPUTE_SHARED_SECRET.
     */
    hseBDStep_t         bdStep;

    /** @brief   INPUT: The number of participants in the Burmester-Desmedt negotiation. Ignored in the #HSE_BD_STEP_COMPUTE_SECOND_PUBLIC_KEY step.
     */
    uint8_t             numParticipants;

    uint8_t             reserved0[2];

    /** @brief   INPUT: The key slot containing the ephemeral Burmester-Desmedt device ECC key pair. Must refer to a key slot of type HSE_KEY_TYPE_ECC_PAIR.
     */
    hseKeyHandle_t      deviceKeyHandle;

    /** @brief   INPUT: The key handle of slot 0 of the key set used for the BD calculation. Must hold at least (*numParticipants* + 1) public ECC keys, i.e.
     *                  *pubKeyHandle* + *numParticipants* must be also a valid key handle.
     *                  - In step HSE_BD_STEP_COMPUTE_SECOND_PUBLIC_KEY it must hold the first public keys of the neighbors in slots 0 and 1, and the second
     *                    public key of the current device will be written in slot 2.
     *                  - In step HSE_BD_STEP_COMPUTE_SHARED_SECRET it must hold the first public key of the predecessor in slot 0, the device's second public key in slot 2,
     *                    and the successor's second public keys in slots 3 and on, up to, but excluding, the predecessor's second public key.
     */
    hseKeyHandle_t      pubKeyHandle;

    /** @brief   INPUT: The target key slot where the BD shared secret will be stored. Must be at least twice the size of the ECC curve
     *                  used for the BD negotiation. Ignored in the #HSE_BD_STEP_COMPUTE_SECOND_PUBLIC_KEY step.
     */
    hseKeyHandle_t      sharedSecretKeyHandle;
} hseBurmesterDesmedtSrv_t;

#endif /* HSE_SPT_BURMESTER_DESMEDT */

/** @} */

#endif

#ifdef HSE_SPT_KEY_DERIVE
/*==================================================================================================
*                                      DEFINES AND MACROS
==================================================================================================*/

/** @brief  HSE Key derivation algorithms.*/
typedef uint8_t hseKdfAlgo_t;
#define HSE_KDF_ALGO_NXP_GENERIC         ((hseKdfAlgo_t)1U)  /**< @brief NXP Generic KDF. */
#define HSE_KDF_ALGO_EXTRACT_STEP        ((hseKdfAlgo_t)2U)  /**< @brief Generic Extraction Step for Two-step KDFs.*/

#ifdef HSE_SPT_KDF_SP800_56C_ONESTEP
#define HSE_KDF_ALGO_SP800_56C_ONE_STEP  ((hseKdfAlgo_t)3U)  /**< @brief One-step KDF as defined by SP800-56C rev1. */
#endif /* HSE_SPT_KDF_SP800_56C_ONESTEP */

#ifdef HSE_SPT_KDF_SP800_56C_TWOSTEP
#define HSE_KDF_ALGO_SP800_56C_TWO_STEP  ((hseKdfAlgo_t)4U)  /**< @brief Two-step KDF as defined by SP800-56C rev1. */
#endif /* HSE_SPT_KDF_SP800_56C_TWOSTEP */

#ifdef HSE_SPT_KDF_SP800_108
#define HSE_KDF_ALGO_SP800_108           ((hseKdfAlgo_t)5U)  /**< @brief KDF(Counter, Feedback, Pipeline) as defined  by SP800-108. */
#endif /* HSE_SPT_KDF_SP800_108 */

#ifdef HSE_SPT_PBKDF2
#define HSE_KDF_ALGO_PBKDF2HMAC          ((hseKdfAlgo_t)6U)  /**< @brief PBKDF2HMAC as defined  by PKCS#5 v2.1 and RFC-8018. */
#endif /* HSE_SPT_PBKDF2 */

#ifdef HSE_SPT_HKDF
#define HSE_KDF_ALGO_HKDF_EXPAND         ((hseKdfAlgo_t)7U)  /**< @brief HKDF Expand KDFs as defined  by RFC-5869. */
#endif /* HSE_SPT_HKDF */

#ifdef HSE_SPT_KDF_ANS_X963
#define HSE_KDF_ALGO_ANS_X963            ((hseKdfAlgo_t)8U)  /**< @brief KDF as defined  by ANS X9.63. */
#endif /* HSE_SPT_KDF_ANS_X963 */

#ifdef HSE_SPT_KDF_ISO18033_KDF1
#define HSE_KDF_ALGO_ISO18033_KDF1       ((hseKdfAlgo_t)9U)  /**< @brief KDF1 as defined  by ISO18033. */
#endif /* HSE_SPT_KDF_ISO18033_KDF1 */

#ifdef HSE_SPT_KDF_ISO18033_KDF2
#define HSE_KDF_ALGO_ISO18033_KDF2       ((hseKdfAlgo_t)10U) /**< @brief KDF2 as defined  by ISO18033. */
#endif /* HSE_SPT_KDF_ISO18033_KDF2 */

#ifdef HSE_SPT_KDF_TLS12_PRF
#define HSE_KDF_ALGO_TLS12PRF            ((hseKdfAlgo_t)11U) /**< @brief TLS 1.2 PRF as defined  by RFC-5246. */
#endif /* HSE_SPT_KDF_TLS12_PRF */

#ifdef HSE_SPT_KDF_IKEV2
#define HSE_KDF_ALGO_IKEV2               ((hseKdfAlgo_t)12U) /**< @brief KDF IKEv2 as defined  by RFC-4306. */
#endif /* HSE_SPT_KDF_IKEV2 */

/** @brief  Hash algorithm available for KDF.*/
typedef uint8_t hseKdfHashAlgo_t;
#define HSE_KDF_SHA2_224           ((hseKdfHashAlgo_t)HSE_HASH_ALGO_SHA2_224)
#define HSE_KDF_SHA2_256           ((hseKdfHashAlgo_t)HSE_HASH_ALGO_SHA2_256)
#define HSE_KDF_SHA2_384           ((hseKdfHashAlgo_t)HSE_HASH_ALGO_SHA2_384)
#define HSE_KDF_SHA2_512           ((hseKdfHashAlgo_t)HSE_HASH_ALGO_SHA2_512)
#define HSE_KDF_SHA2_512_224       ((hseKdfHashAlgo_t)HSE_HASH_ALGO_SHA2_512_224)
#define HSE_KDF_SHA2_512_256       ((hseKdfHashAlgo_t)HSE_HASH_ALGO_SHA2_512_256)

/** @brief  HSE KDF "Pseudo-Random Function" (PRF).*/
typedef uint8_t hseKdfPrf_t;
#define HSE_KDF_PRF_HASH           ((hseKdfPrf_t)1U) /**< @brief SHA2 families. */
#define HSE_KDF_PRF_HMAC           ((hseKdfPrf_t)2U) /**< @brief HMAC-SHA2 families. */
#define HSE_KDF_PRF_CMAC           ((hseKdfPrf_t)3U) /**< @brief CMAC. */
#define HSE_KDF_PRF_XCBC_MAC       ((hseKdfPrf_t)4U) /**< @brief XCBC_MAC (used only for IKEV2 KDF). */

/** @brief  HSE PRF algorithm.*/
typedef hseKdfHashAlgo_t           hseHashPrfAlgo_t;   /**< @brief Algorithm for hash PRF (e.g SHA256) */
typedef hseKdfHashAlgo_t           hseHmacPrfAlgo_t;   /**< @brief Algorithm for hmac PRF (e.g SHA256) */
typedef uint8_t                    hseNoPrfAlgo_t;     /**< @brief No PRF algorithm */

/** @brief  SP800-108 KDF modes (only Counter mode supported).*/
typedef uint8_t hseKdfSP800_108Mode_t;
#define HSE_KDF_SP800_108_COUNTER      ((hseKdfSP800_108Mode_t)1U) /**< @brief SP800 108 Counter step */

/** @brief  SP800-108 KDF counter length (only 1, 2 and 4 bytes supported).*/
typedef uint8_t hseKdfSP800_108CounterLen_t;
#define HSE_KDF_SP800_108_COUNTER_LEN_DEFAULT ((hseKdfSP800_108CounterLen_t)0U) /**< @brief SP800 108 default counter length (4 bytes) */
#define HSE_KDF_SP800_108_COUNTER_LEN_1       ((hseKdfSP800_108CounterLen_t)1U) /**< @brief SP800 108 1 byte counter length */
#define HSE_KDF_SP800_108_COUNTER_LEN_2       ((hseKdfSP800_108CounterLen_t)2U) /**< @brief SP800 108 2 bytes counter length */

/** @brief  HSE IKEv2 exchange of messages steps.*/
typedef uint8_t hseIkev2Steps_t;
#define HSE_IKEV2_STEP_INIT_SA          ((hseIkev2Steps_t)1U)   /**< @brief IKE_SA_INIT step - Initial Keying Material for the IKE SA */
#define HSE_IKEV2_STEP_CHILD_SA         ((hseIkev2Steps_t)2U)   /**< @brief CHILD_SA step - Generating Keying Material for Child SAs */
#define HSE_IKEV2_STEP_REKEY_SA         ((hseIkev2Steps_t)3U)   /**< @brief REKEY step - Rekeying IKE SAs Using a CREATE_CHILD_SA Exchange */

/** @brief  TLS PSK usage.*/
typedef uint8_t hseTlsPskUsage_t;
#define HSE_TLS_PSK_NOT_USED            ((hseTlsPskUsage_t)0U)  /**< @brief TLS PSK is not used */
#define HSE_TLS_KEY_EXCHANGE_PSK        ((hseTlsPskUsage_t)1U)  /**< @brief Key Exchange PSK (refer to rfc4279) */
#define HSE_TLS_KEY_EXCHANGE_ECDHE_PSK  ((hseTlsPskUsage_t)2U)  /**< @brief Key Exchange ECDHE_PSK (refer to rfc5489) */
#define HSE_TLS_KEY_EXCHANGE_RSA_PSK    ((hseTlsPskUsage_t)3U)  /**< @brief Key Exchange RSA_PSK (refer to rfc4279) */
#define HSE_TLS_KEY_EXCHANGE_DHE_PSK    ((hseTlsPskUsage_t)4U)  /**< @brief Key Exchange DHE_PSK (refer to rfc4279) */

/*==================================================================================================
*                                             ENUMS
==================================================================================================*/

/*==================================================================================================
                                 STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/
/** @brief The KDF salt definition.
 *  @details  The salt is  used as the MAC key during the execution of the randomness-extraction step (first step).
 *            The salt can be a secret (providing the key handle) or a non-secret (e.g. value computed from
 *            nonces exchanged as part of a key-establishment protocol).
 */
typedef struct
{
    /** @brief INPUT: The salt key handle (when the salt is provided as a secret).
     *                If (#saltKeyHandle == #HSE_INVALID_KEY_HANDLE), the salt shall be specified by saltLength
     *                and pSalt parameters.
     *                If the #saltKeyHandle is valid, the salt length is the key size in bytes and should match
     *                the the input block size.*/
    hseKeyHandle_t       saltKeyHandle;
    /** @brief INPUT: Length of the salt in bytes. Used only if #saltKeyHandle == #HSE_INVALID_KEY_HANDLE.
     *                The length of salt are determined by the PRF algorithm:
     *                - For HMAC-hash PRF, the #saltLength should be equal with the input block size (e.g 64/128 bytes). <br>
     *                  If #saltLength is shorter, it will be padded with zeros.
     *                  The #saltLength greater than input block size will be firstly hashed using HASH PRF and
     *                  then use the resultant byte string.
     *                - CMAC requires keys that are N bits long (for N = 128, 192, or 256). In this case,
     *                  the salt should be 16, 24, or 32 bytes, depending upon the AES variant. <br>
     *                  Note that the #saltLength can also be zero. In this case, the salt is an all-zero byte array
     *                  whose length is equal to input block size (for hash or CMAC).
     */
    uint32_t             saltLength;
    /** @brief INPUT: The salt. Used only if #saltKeyHandle == #HSE_INVALID_KEY_HANDLE. <br>
               If #pSalt is not passed (#pSalt is NULL), default_salt will be used
               (the default_salt is all-zero byte array of length determined by input block). */
    HOST_ADDR            pSalt;
} hseKdfSalt_t;

/** @brief KDF Extraction step
 *  @details The extraction step is a Pseudo-Random Function (PRF) that takes as inputs a shared secret (#secretKeyHandle)
 *           and the salt which can be a secret (a key) or non-secret (a generated random number). <br>
 *           From these inputs, the PRF generates a pseudo-random key (PRK). The PRK can be used for the Expansion phase.
 *           The size of the PRK is equal with the size of the PRF output.
 *
 *   The following PRFs can be performed:
 *          - PRK = HMAC-hash(salt, secret);
 *          - PRK = CMAC(salt, secret);
 */
typedef struct
{
    /** @brief INPUT: The shared secret to be used for the operation. */
    hseKeyHandle_t       secretKeyHandle;
    /** @brief INPUT: The target key handle (where to store the new key). It should point to a #HSE_KEY_TYPE_SHARED_SECRET slot.
     *                The application can use the generated PRK for the Expand phase (using the same key handle) or
     *                it can extract the key(s) (in different slots) using the hseKeyDeriveCopyKeySrv_t service.
     *                The size of the PRK is equal with the size of the PRF output (e.g. for hmac-sha256, the key bit length is 256 bits) */
    hseKeyHandle_t       targetKeyHandle;
    /** @brief INPUT: Selected the PRF to be used. <br>
     *                Supported options: #HSE_KDF_PRF_HMAC, #HSE_KDF_PRF_CMAC */
    hseKdfPrf_t          kdfPrf;
    /** @brief INPUT: Selects the algorithm for the PRF */
    union
    {
        hseHmacPrfAlgo_t       hmacHash;     /**< @brief The hash algorithm used for HMAC. */
        hseNoPrfAlgo_t         cmac;         /**< @brief Dummy byte. */
    }prfAlgo;
    uint8_t               reserved[2];
    /** @brief INPUT: The salt which is used as key.
     *                The saltLength should be equal with the input block size (e.g 16/64/128 bytes). See hseKdfSalt_t comments.
     */
    hseKdfSalt_t         salt;
} hseKdfExtractStepScheme_t;

/** @brief KDF Common parameters
 *  @details Common parameters for expansion step used for different KDFs (SP800_56CTwoStep, HKDF-Expand, prf+ from IKEV2 etc).
 *           The expansion inputs are the output from the extractor (pseudo-random key from #hseKdfExtractStepScheme_t)
 *           and the public context information (#pInfo).
*/
typedef struct
{
    /** @brief INPUT: The source key to be used for the operation.
     *                For the expansion step, the source key handle should be a pseudorandom key (PRK) or a shared secret.
     *                (usually, the output from the extraction step; see hseKdfExtractStepScheme_t). */
    hseKeyHandle_t       srcKeyHandle;
    /** @brief INPUT: The target key handle (where to store the new key).It should point to a #HSE_KEY_TYPE_SHARED_SECRET slot.
     *                The user can extract the key(s) (in different slots) from the derived key material
     *                using the hseKeyDeriveCopyKeySrv_t service. */
    hseKeyHandle_t       targetKeyHandle;
    /** @brief   INPUT: The key material length to be derived (it must be >= 16 bytes and <= slot size).*/
    uint16_t             keyMatLen;
    /** @brief INPUT: The PRFs used for KDF. <br>
    *                 Supported options: #HSE_KDF_PRF_HASH, #HSE_KDF_PRF_HMAC, #HSE_KDF_PRF_CMAC */
    hseKdfPrf_t          kdfPrf;
    /** @brief INPUT: Selects the algorithm for the PRF */
    union
    {
        hseHashPrfAlgo_t       hash;         /**< @brief The KDF hash algorithm . */
        hseHmacPrfAlgo_t       hmacHash;     /**< @brief The hash algorithm used for HMAC. */
        hseNoPrfAlgo_t         cmac;         /**< @brief Dummy byte. */
    }prfAlgo;
    uint32_t             infoLength;         /**< @brief INPUT: Length of the pInfo. It must be <= 256 bytes. */
    HOST_ADDR            pInfo;              /**< @brief INPUT: The Info. */
} hseKdfCommonParams_t;

/*------------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/
/** @brief KDF NXP generic scheme.
 *  @details Used for deriving a cryptographic key from a source key and seed as described below:
 *  \code
        {
            K[0]= NULL;
            key_mat[0]= NULL;
            iter = key_mat_len/prfOut_size;
            if(0 != (key_mat_len%prfOut_size))
            {
               iter = iter+1;
            }
            for(i = 1; i <= iter;i++)
            {
                 step1: K[i] = Prf(srcKey, K[i-1] || seed)
                 step2: key_mat[i]= key_mat[i-1] || K[i]
            }
            key_mat = truncate(key_mat_len, key_mat[iter]).
        }
    \endcode
   @note
   - If the key_mat_len >= 32 bytes, the last 8 bytes from the key material
     can be exported to the HOST.
   - For SHA PRF:
       - if srcKeyAfterSeed = FALSE, step1 is K[i] = SHA(srcKey || K[i-1] || seed)
       - if srcKeyAfterSeed = TRUE , step1 is K[i] = SHA(K[i-1] || seed || srcKey)
*/
typedef struct
{
    /** @brief INPUT: KDF common parameters. Only HASH PRF is supported.
     *       - hseKdfCommonParams_t#kdfPrf = #HSE_KDF_PRF_HASH
     *       - hseKdfCommonParams_t#pInfo = Seed.
     *       - hseKdfCommonParams_t#infoLength = Seed length (must be <= 256 bytes). Zero means the Seed is not used.*/
    hseKdfCommonParams_t    kdfCommon;
     /** @brief INPUT: Concatenate the source key after the seed. */
    bool_t                  srcKeyAfterSeed;
    uint8_t                 reserved;
    /** @brief INPUT: Output data length to be exported to the host.
    *                It should be <= 8 bytes and can be used only if hseKdfCommonParams_t#keyMatLen >= 32 bytes. */
    uint16_t                outputLength;
    /** @brief OUTPUT: Export outputLength bytes to host (only if the hseKdfCommonParams_t#keyMatLen >= 32 bytes). It can be NULL.*/
    HOST_ADDR pOutput;
} hseKdfNxpGenericScheme_t;

/*------------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/
#ifdef HSE_SPT_KDF_SP800_56C_ONESTEP
/** @brief SP800 56C One Step Key derivation
 *  @details Perform One step KDF specified in SP800-56C rev1.
 *   @note Length of the counter is always 32bits.
 */
typedef struct
{
    /** @brief INPUT: KDF common parameters. Only HASH and HMAC are supported.
     *       - kdfCommon#kdfPrf = #HSE_KDF_PRF_HASH or #HSE_KDF_PRF_HMAC.
     *       - kdfCommon#pInfo = Fixed Info specified according to SP800_56C OneStep.*/
    hseKdfCommonParams_t  kdfCommon;
    /** @brief INPUT: The salt.
     *        The salt is used only if HMAC PRF is selected (it's used as key).
     *        The saltLength should be equal with the input block size (e.g 64/128 bytes).
     *        If saltLength is shorter, it will be padded with zeros; if saltLength is longer, it will be hashed. */
    hseKdfSalt_t             salt;
} hseKdfSP800_56COneStepScheme_t;
#endif /* HSE_SPT_KDF_SP800_56C_ONESTEP */

/*------------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/
#ifdef HSE_SPT_KDF_SP800_108
/** @brief SP800 108 Key derivation.
 *  @details The KDF(Counter mode) as defined  by SP800-108.
 *  @note The key material length ([L]_2) from SP800 108 is represented on 32 bits. The iteration counter ([i]_2) can have
 *        8, 16 or 32 bits.
 *  */
typedef struct
{
    /** @brief INPUT: KDF common parameters. Only HMAC and CMAC are supported.
     *       - .kdfCommon.kdfPrf = #HSE_KDF_PRF_HMAC or #HSE_KDF_PRF_CMAC.
     *       - .kdfCommon.pInfo = the context-specific data according to SP800_108: "Label||0x00||Context||[L]_2".
     *  @note Source key should be a valid symmetric key of length that respects the constraints defined for kdf salt (see hseKdfSalt_t).*/
    hseKdfCommonParams_t   kdfCommon;
    /** @brief INPUT: Selects the SP800_108 mode: Counter (e.g. Feedback, Pipeline not suppoted)*/
    hseKdfSP800_108Mode_t  mode;
    /** @brief INPUT: Selects the length in bytes of the counter ([i]_2). The length of the counter can be 1, 2 or 4 bytes.
     *  @note Any other value will be treated as the default value (4 bytes) */
    hseKdfSP800_108CounterLen_t counterByteLength;
    uint8_t                reserved[14];
} hseKdfSP800_108Scheme_t;
#endif /* HSE_SPT_KDF_SP800_108 */

/*------------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/
#ifdef HSE_SPT_KDF_SP800_56C_TWOSTEP
/** @brief SP800 56C Two-step Key derivation
 *  @details Perform Two step KDF specified in SP800-56C. <br>
 *           SP800_56C Two Step includes SP800 108 parameters for Expansion Step, and additional the salt for Extraction Step.
 *  @note
 *  - OtherInput define by SP800 56C contains the salt, the key material length (L) and FixedInfo,
 *          which are provided as parameters by the service.
 *  - Counter length ['r'] supported is 32 bits. */
typedef struct
{
    /** @brief INPUT: KDF common parameters. Only HMAC and CMAC are supported.
     *                - .expand.kdfCommon.kdfPrf = #HSE_KDF_PRF_HMAC or #HSE_KDF_PRF_CMAC.
     *                - .expand.kdfCommon.pInfo = FixedInfo which follows SP800-56C. */
    hseKdfSP800_108Scheme_t   expand;
    /** @brief INPUT: The salt used for Extraction Step. */
    hseKdfSalt_t              salt;
} hseKdfSP800_56CTwoStepScheme_t;
#endif /* HSE_SPT_KDF_SP800_56C_TWOSTEP */

/*------------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/
#ifdef HSE_SPT_PBKDF2
/** @brief Password Based Key Derivation Function 2.
 *  @details Used for deriving a cryptographic key from a password */
typedef struct
{
    /** @brief INPUT: The source key to be used for the operation (shared secret). */
    hseKeyHandle_t       srcKeyHandle;
    /** @brief INPUT: The target key handle (where to store the new key).It should point to a #HSE_KEY_TYPE_SHARED_SECRET slot.
     *                The user can extract the key(s) (in different slots) from the derived key material
     *                using the hseKeyDeriveCopyKeySrv_t service. */
    hseKeyHandle_t       targetKeyHandle;
    /** @brief   INPUT: The key material length to be derived (it must be <= slot size). */
    uint16_t             keyMatLen;
    hseHmacPrfAlgo_t     hmacHash;        /**< @brief INPUT: The hash algorithm for HMAC PRF. \
                                               @note HSE_M devices do not support SHA2_384/512 hash algorithms for PBKDF2.*/
    uint8_t              reserved;
    /** @brief  INPUT: The number of iterations to be performed.
     *                 Should take a value higher than 100. */
    uint32_t             iterations;
    uint32_t             saltLength;      /**< @brief INPUT: Length of the salt. It must be < 8192 bytes. */
    HOST_ADDR            pSalt;           /**< @brief INPUT: A salt; 16 bytes or longer (randomly generated) */
} hsePBKDF2Scheme_t;
#endif /* HSE_SPT_PBKDF2 */

/*------------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/
#ifdef HSE_SPT_HKDF
/** @brief HKDF-Expand KDF Function.
 *  @details  It is suitable for deriving keys of a fixed size used for other cryptographic operations.
 *            @note
 *            For TLS1.3, the HKDF-Extract function (first step) can be performed using #hseKdfExtractStepScheme_t.
 *  */
typedef struct
{
    /** @brief INPUT: KDF common parameters. Only HMAC is supported.
     *       - .kdfCommon.kdfPrf = #HSE_KDF_PRF_HMAC
     *       - .kdfCommon.pInfo = Application specific context. Can be NULL.
     *        */
    hseKdfCommonParams_t   kdfCommon;
    /** @brief OUTPUT: The TLS1.3 IV output.
     *                 HSE exports the HKDF expansion output only if the kdfCommon.pInfo starts with the following
     *                 concatenation: kdfCommon.keyMatLen(2 bytes big-endian) | "tls13 iv" (string of 8 bytes). <br>
     *                 The length of pIvOutput is the kdfCommon.keyMatLen. <br>
     *                 In this case kdfCommon.targetKeyHandle is not used.
     **/
    HOST_ADDR                  pIvOutput;
} hseHKDF_ExpandScheme_t;
#endif /* HSE_SPT_HKDF */

/*------------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/
#ifdef HSE_SPT_KDF_ANS_X963
/** @brief ANS X9.63 KDF as specified by SEC1-v2.
 *  @details One-step KDF performed in the context of an ANS X9.63 key agreement scheme. <br>
 *  ANS X9.63 KDF supports:
 *  - .kdfPrf = #HSE_KDF_PRF_HASH (ANS X9.63 supports only hash PRF).
 *  - .pInfo points to SharedInfo (optional, as defined by ANS X9.63).
 *   */
typedef hseKdfCommonParams_t hseKdfANSX963Scheme_t;
#endif /* HSE_SPT_KDF_ANS_X963 */

/*------------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/
#ifdef HSE_SPT_KDF_ISO18033_KDF1
/** @brief KDF1 as specified by ISO18033.
 *  @details One-step KDF performed as specified by ISO18033. <br>
 *  ISO18033 KDF1 supports:
 *  - .kdfPrf = #HSE_KDF_PRF_HASH (ISO18033 supports only hash PRF).
 *  - .pInfo = NULL.
 *  - .infoLength = 0UL  <br>
 *   */
typedef hseKdfCommonParams_t hseKdfISO18033_KDF1Scheme_t;
#endif /* HSE_SPT_KDF_ISO18033_KDF1 */

/*------------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/
#ifdef HSE_SPT_KDF_ISO18033_KDF2
/** @brief KDF2 as specified by ISO18033.
 *  @details One-step KDF performed as specified by ISO18033. <br>
 *  ISO18033 KDF2 supports:
 *  - .kdfPrf = #HSE_KDF_PRF_HASH (ISO18033 supports only hash PRF).
 *  - .pInfo = NULL.
 *  - .infoLength = 0UL
 *   */
typedef hseKdfCommonParams_t hseKdfISO18033_KDF2Scheme_t;
#endif /* HSE_SPT_KDF_ISO18033_KDF2*/

/*------------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/
#ifdef HSE_SPT_KDF_TLS12_PRF
/** @brief TLS 1.2 PRF as specified by RFC 5246.
 *  @details The PRF needed in TLS1.2 protocol to derive the master secret, the key block and the verify data.
 */
typedef struct
{
    /** @brief INPUT: The label length in bytes (without '\0' termination).
     *        Only the following labels are valid in case of TLS 1.2 PRF.
     *             - master secret label    -  "master secret"
     *             - extended master secret -  "extended master secret" (refer to rfc7627)
     *             - key expansion label    -  "key expansion"
     *             - client finished label  -  "client finished"
     *             - server finished label  -  "server finished"
     *         @note
     *             - The above arrays do not contain the string termination character.
     *             - The above label lengths are the only valid label lengths that must be provided by the Host Application (refer to RFC 5246).
     */
    uint16_t         labelLength;
    uint8_t          reserved1[2U];

    /** @brief INPUT: The label of the TLS1.2 PRF operations.
     *                - If pLabel = "master secret" or "extended master secret", HSE computes the master secret; the hseKdfTLS12PrfScheme_t#keyMatLength must be 48 bytes.
     *                - If pLabel = "key expansion", HSE computes the key_block; the hseKdfTLS12PrfScheme_t#keyMatLength must be >= 32 bytes.
     *                  HSE also outputs the client and server IVs (see #pOutput).
     *                - if pLabel = "client finished" or  "server finished", HSE computes the verify_data (see #pOutput).
     *                @note
     *                - The pre-master shared secret (#HSE_KEY_TYPE_SHARED_SECRET key slot) is deleted after master secret computation (see rfc5246).
     */
    HOST_ADDR        pLabel;

    /** @brief INPUT: Selects TLS-PSK algorithm usage.
     *                Used only for master secret computation (label = "master secret"). Ignored for other labels.
     *                @note
     *                - #HSE_TLS_PSK_NOT_USED           - pre-shared key not used
     *                - #HSE_TLS_KEY_EXCHANGE_PSK       - pre-master secret is computed as:
     *                  If the PSK is N octets long, concatenate a uint16 with the value N, N zero octets,
     *                  a second uint16 with the value N, and the PSK itself (refer to rfc4279)
     *                - #HSE_TLS_KEY_EXCHANGE_ECDHE_PSK - pre-master secret is computed as:
     *                  Let Z be the octet string of ECDH shared secret. The pre-master is the concatenation of a
     *                  uint16 containing the length of Z (in octets), Z itself, a uint16 containing the length of
     *                  the PSK (in octets), and the PSK itself (refer to rfc5489)
     *                - #HSE_TLS_KEY_EXCHANGE_RSA_PSK   - pre-master secret is computed as:
     *                  concatenate a uint16 with the value 48, the 2-byte version number and the 46-byte random value,
     *                  a uint16 containing the length of the PSK (in octets), and the PSK itself
     *                  (the pre-master secret is thus 52 octets longer than the PSK); refer to rfc4279.
     *                - #HSE_TLS_KEY_EXCHANGE_DHE_PSK - let Z be the value produced by classic DH computation. The pre-master secret is computed: concatenate
     *                  a uint16 containing the length of Z (in octets), Z itself, a uint16 containing the length of the PSK (in octets), and the PSK itself.
     */
    hseTlsPskUsage_t tlsPskUsage;
    uint8_t          reserved2[3U];

    /** @brief INPUT: Pre-shared key handle. It can be any symmetric NVM key that has the #HSE_KF_USAGE_DERIVE flag set.
     *  Used only for master secret computation and #tlsPskUsage != #HSE_TLS_PSK_NOT_USED.*/
    hseKeyHandle_t   pskKeyHandle;

    /** @brief INPUT: The source key handle (it must point to a #HSE_KEY_TYPE_SHARED_SECRET slot). <br>
     *                - For label = "master secret":
     *                    - if #tlsPskUsage = #HSE_TLS_PSK_NOT_USED, it must be the pre-master secret (e.g DH shared secret).
     *                    - if #tlsPskUsage = #HSE_TLS_KEY_EXCHANGE_PSK, it is ignored (key handle is provided by #pskKeyHandle).
     *                    - if #tlsPskUsage = #HSE_TLS_KEY_EXCHANGE_ECDHE_PSK, it is the DH shared secret.
     *                    - if #tlsPskUsage = #HSE_TLS_KEY_EXCHANGE_RSA_PSK, the shared secret slot contains:
     *                                ProtocolVersion (2bytes) concatenated with 46 byte random number.
     *                - For key_block or verify_data, it must be the master secret. */
    hseKeyHandle_t   srcKeyHandle;
    /** @brief INPUT: The hash algorithm for HMAC PRF. */
    hseHmacPrfAlgo_t hmacHash;
    uint8_t          reserved3[1U];
    /** @brief INPUT: The seed length. It must be <= 256 bytes.*/
    uint16_t         seedLength;

    /** @brief INPUT: The seed for TLS 1.2 PRF. In TLS, this is usually a combination of user and random data. <br>
     *                This is the concatenation of Server and Client Hello random data.
     *                - For master secret, it is concatenation of Server Random Data || Client Random Data.
     *                - For extended master secret, it is the session_hash (refer to rfc7627).
     *                - For Key Expansion, it is concatenation of Client Random Data || Server Random Data. <br>
     *                Refer to RFC 5246 for more details.
     */
    HOST_ADDR        pSeed;

    /** @brief INPUT: The target key handle (where to store the new key). It shall point to a
     *               #HSE_KEY_TYPE_SHARED_SECRET slot (this means #HSE_KF_USAGE_DERIVE flag is set by default). <br>
     *               It can be:
     *               - the derived master secret
     *               - the derived key_block.
     *                     The user can extract the key(s) using the hseKeyDeriveCopyKeySrv_t service. <br>
     *                     The key_block is partitioned as follows:
     *                     - client_write_MAC_key[]
     *                     - server_write_MAC_key[]
     *                     - client_write_key[]
     *                     - server_write_key[]
     *                     - client_write_IV[]; exported in pOutput below if #pLabel = "key expansion"
     *                     - server_write_IV[]; exported in pOutput below if #pLabel = "key expansion"
     *               - not used for verify_data (#pLabel = "client finished" or #pLabel = "server finished")
     *
     */
    hseKeyHandle_t   targetKeyHandle;

    /** @brief INPUT: The key material length (in bytes).
     *                -  If pLabel = "master secret" or "extended master secret", the #keyMatLength must be 48 bytes.
     *                -  If pLabel = "key expansion" (key_block), the #keyMatLength must be >= 32 bytes.
     *                   It must be the total length for Client and Server keys without the IVs (only the MAC and encryption keys).
     *                -  Not used for verify_data (if the #pLabel = "client finished" or #pLabel = "server finished")
     */
    uint16_t         keyMatLength;

    /** @brief INPUT:   The length for output data (#pOutput) which can be:
     *                  - For pLabel= "key expansion", the total length for client and server Initialization Vectors from key_block.
     *                    Can be 0. If it is provided, it must be <= 32 bytes (2*block size).
     *                  - For #pLabel = "client finished" or "server finished", the verify_data length. Must be 12 bytes.
     */
    uint16_t         outputLength;

    /** @brief OUTPUT: The output data which can be:
     *                 - For #pLabel = "key expansion", concatenated client and server IVs of totalIvLength (client_write_IV[] || server_write_IV[]). Can be NULL.
     *                 - For #pLabel = "client finished" or "server finished", verify_data sent in the Finished message.
     */
    HOST_ADDR        pOutput;
} hseKdfTLS12PrfScheme_t;
#endif /* HSE_SPT_KDF_TLS12_PRF */

/*------------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/
#ifdef HSE_SPT_KDF_IKEV2
/** @brief IKEv2 KDF as specified by RFC 5996.
 *  @details Two-step KDF that derives the needed keys in the Internet Key Exchange Protocol Version 2. <br>
 *           RFC5996 specifies the following Security Association (SA) steps:
 *           - INIT_SA step computes:
 *               - SKEYSEED = prf(Ni | Nr, g^ir)
 *               - KEYMAT= prf+ (SKEYSEED, Ni | Nr | SPIi | SPIr )
 *           - CHILD_SA step (it can use a new Shared Secret (g^ir) from the ephemeral DH of CREATE_CHILD_SA exchange). <br>
 *               For new g^ir, it computes: KEYMAT = prf+(SK_d, g^ir (new) | Ni | Nr ). <br>
 *               Otherwise, it is computes: KEYMAT = prf+(SK_d, Ni | Nr).
 *           - REKEY_SA step computes:
 *                 - SKEYSEED = prf(SK_d (old), g^ir (new) | Ni | Nr)
 *                 - KEYMAT= prf+ (SKEYSEED, Ni | Nr | SPIi | SPIr ) from the new exchange
 *
 *    @note
 *    - KEYMAT contains 7 keys: {SK_d | SK_ai | SK_ar | SK_ei | SK_er | SK_pi | SK_pr }.
 *      The host shall extract the keys in different slots using the hseKeyDeriveCopyKeySrv_t service.
 *    - If the negotiated PRF is AES-XCBC-PRF-128 or AES-CMAC-PRF-128,
 *      only the first 64 bits of Ni and the first 64 bits of Nr are used in
 *      calculating SKEYSEED, but all the bits are used for input to the prf+ function.
 */
typedef struct
{
    /** @brief INPUT: The Security Association (SA) step: #HSE_IKEV2_STEP_INIT_SA, #HSE_IKEV2_STEP_CHILD_SA, #HSE_IKEV2_STEP_REKEY_SA */
    hseIkev2Steps_t   step;
    uint8_t           reserved[3];
    /** @brief INPUT: The key handle for g^ir from ephemeral DH.
     *                - For #HSE_IKEV2_STEP_CHILD_SA, if no new g_ir is computed it shall be set to #HSE_INVALID_KEY_HANDLE. */
    hseKeyHandle_t    g_ir_keyHandle;
    /** @brief INPUT: The key handle of SK_d use within #HSE_IKEV2_STEP_CHILD_SA or #HSE_IKEV2_STEP_REKEY_SA steps; otherwise not used.*/
    hseKeyHandle_t    sk_d_keyHandle;
    /** @brief INPUT: The target key handle (where to store the new key). It shall point to a
     *                #HSE_KEY_TYPE_SHARED_SECRET slot, and the user can extract the keys in different slots using the
     *                hseKeyDeriveCopyKeySrv_t service. <br>
     *                The keys are partitioned in the slot as follows:
     *                {SK_d | SK_ai | SK_ar | SK_ei | SK_er | SK_pi | SK_pr }. */
    hseKeyHandle_t    targetKeyHandle;
    /** @brief  INPUT: The key material length to be derived (it must be <= slot size). It should include the total length for
     *                 all generated 7 keys.
     *          @note The lengths of SK_d, SK_pi, and SK_pr MUST be the preferred key length of the PRF agreed.*/
    uint16_t          keyMatLen;
    /** @brief INPUT: The PRFs used for KDF. <br>
    *                 Supported options: #HSE_KDF_PRF_HMAC, #HSE_KDF_PRF_CMAC, #HSE_KDF_PRF_XCBC_MAC. */
    hseKdfPrf_t       kdfPrf;
    /** @brief INPUT: Selects the algorithm for the PRF */
    union
    {
        hseHmacPrfAlgo_t       hmacHash;     /**< @brief The hash algorithm used for HMAC. */
        hseNoPrfAlgo_t         cmac;         /**< @brief No PRF algorithm. */
        hseNoPrfAlgo_t         xCbcmac;      /**< @brief No PRF algorithm. */
    }prfAlgo;

    /** @brief INPUT: Number of bytes from input to be processed. It must be between 16 and 528 bytes. */
    uint32_t           inputLength;
    /** @brief INPUT: Input data for each IKEv2 step:
     *                - #HSE_IKEV2_STEP_INIT_SA step: concatenation of Ni | Nr | SPIi | SPIr
     *                - #HSE_IKEV2_STEP_CHILD_SA step: concatenation of Ni | Nr
     *                - #HSE_IKEV2_STEP_REKEY_SA step: concatenation of Ni | Nr | SPIi | SPIr from the new exchange. */
    HOST_ADDR          pInput;
    /** @brief INPUT: Length of Ni | Nr concatenation. <br>
     *                Used only for #HSE_IKEV2_STEP_INIT_SA and #HSE_IKEV2_STEP_REKEY_SA. */
    uint32_t           totalNonceLength;
} hseKdfIKEV2Scheme_t;
#endif /* HSE_SPT_KDF_IKEV2 */

/*------------------------------------------------------------------------------------------------*/
/*-------------------------------SERVICES DEFINITION----------------------------------------------*/

#ifdef HSE_SPT_KEY_DERIVE

/** @brief HSE Key Derive service.

 *  @details The key derive service (KDF) derives one or more secret keys from a secret value.
 *
 *  @note
 *        - The key material can be derived only in #HSE_KEY_TYPE_SHARED_SECRET slots (specified as targetKeyHandle),
 *          which can not be exported outside HSE.
 */
typedef struct
{
    /** @brief INPUT: The key derivation algorithm. */
    hseKdfAlgo_t         kdfAlgo;
    uint8_t              reserved[3];
    /** @brief INPUT: The selected key derivation algorithm. */
    union
    {
        /** @brief INPUT: NXP generic KDF scheme. */
        hseKdfNxpGenericScheme_t         nxpGeneric;
        /** @brief Generic Extraction Step for Two-step KDFs. */
        hseKdfExtractStepScheme_t        extractStep;
    #ifdef HSE_SPT_KDF_SP800_56C_ONESTEP
        /** @brief INPUT: One-Step SP800_56C KDF scheme. */
        hseKdfSP800_56COneStepScheme_t   SP800_56COneStep;
    #endif
    #ifdef HSE_SPT_KDF_SP800_56C_TWOSTEP
        /** @brief INPUT: Two-Step SP800_56C KDF scheme. */
        hseKdfSP800_56CTwoStepScheme_t   SP800_56CTwoStep;
    #endif
    #ifdef HSE_SPT_KDF_SP800_108
        /** @brief INPUT: SP800 108 KDF scheme. */
        hseKdfSP800_108Scheme_t          SP800_108;
    #endif
    #ifdef HSE_SPT_PBKDF2
        /** @brief INPUT: PBKDF2 scheme. */
        hsePBKDF2Scheme_t                PBKDF2;
    #endif
    #ifdef HSE_SPT_HKDF
        /** @brief INPUT: HKDF-Expand scheme. */
        hseHKDF_ExpandScheme_t           HKDF_Expand;
    #endif
    #ifdef HSE_SPT_KDF_ANS_X963
        /** @brief INPUT: ANS_X963 KDF scheme. */
        hseKdfANSX963Scheme_t            ANS_X963;
    #endif
    #ifdef HSE_SPT_KDF_ISO18033_KDF1
        /** @brief INPUT: ISO18033 KDF1 scheme. */
        hseKdfISO18033_KDF1Scheme_t      ISO18033_KDF1;
    #endif
    #ifdef HSE_SPT_KDF_ISO18033_KDF2
        /** @brief INPUT: ISO18033 KDF2 scheme. */
        hseKdfISO18033_KDF2Scheme_t      ISO18033_KDF2;
    #endif
    #ifdef HSE_SPT_KDF_TLS12_PRF
        /** @brief INPUT: TLS 1.2 PRF. */
        hseKdfTLS12PrfScheme_t           TLS12Prf;
    #endif
    #ifdef HSE_SPT_KDF_IKEV2
        /** @brief INPUT: IKEv2 KDF scheme. */
        hseKdfIKEV2Scheme_t              IKEv2;
    #endif
    }sch;
} hseKeyDeriveSrv_t;

/** @brief HSE Key Derive - Copy Key service.
 *  @details This service can be used to extract keys (or a key) from the derived key material placed
 *           in a temporary shared secret slot (#HSE_KEY_TYPE_SHARED_SECRET).
 *
 *  The key(s) can be copied in NVM/RAM slots as follow:
 *  1. SuperUser key restrictions:
 *        - keys can be copied in NVM key store from the derived key material only in empty slots (an erase shall be performed in advance if needed).
 *        - keys can be copied in RAM key store from the derived key material (RAM keys can be overwritten).
 *  2. User key restrictions:
 *        - keys can NOT be copied in NVM key store from the derived key material.
 *        - keys can be copied in RAM key store from the derived key material (RAM keys can be overwritten).
 */
typedef struct
{
    /** @brief   INPUT: The key handle to be used to extract a key value.
     *                  The key handle should point to a #HSE_KEY_TYPE_SHARED_SECRET key type. */
    hseKeyHandle_t      keyHandle;
    /** @brief   INPUT: Start offset from where to copy the key. The offset can be zero or a multiple of 4 bytes. */
    uint16_t            startOffset;
    uint8_t             reserved[2];
    /** @brief   INPUT: The target key handle (where to store the new key). */
    hseKeyHandle_t      targetKeyHandle;
    /** @brief   INPUT: Specifies usage flags, restriction access, key bit length etc for the key.
     *                  Note that the length of the copied key is considered to be hseKeyInfo_t#keyBitLen.
     *                  The minimum key length that can be copied is 16 bytes. */
    hseKeyInfo_t        keyInfo;
} hseKeyDeriveCopyKeySrv_t;

#endif /* HSE_SPT_KEY_DERIVE */

/** @} */
#endif

#ifdef HSE_SPT_SHE

/*==================================================================================================
                                 STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/


/** @brief SHE load key service.
 *  @details Load a SHE key into the HSE according to the SHE memory update protocol.
 *  @note The SHE keys can be used for any supported AES operations (e.g. AES with all block modes, AEAD etc.)
 *        given the proper flags are set. One exception is BOOT_MAC_KEY, which can only be used with CMAC verify operation. */
typedef struct
{
    /** @brief   Group Index for the SHE NVM catalog, ranging from 0 to 4. This parameter also decides the KDF
     *           input constants "CENC" & "CMAC" to be used in memory update protocol operation.
     *  @details
     *           - For (1 <= keyID <= 3), this parameter is ignored and taken as zero to decide "CENC" and "CMAC".
     *           - For (keyID = 14) and (4 <= authID <= 13), this parameter is used to select auth-user-key (authID) group
     *             and to decide "CENC" & "CMAC".
     *           - For (keyID = 14) and (authID = 0), this parameter is ignored & taken as zero to decide "CENC" & "CMAC".
     *           - For (4 <= keyID <= 13) and (4 <= authID <= 13), given that keyID = authID, this parameter
     *             is used to select both user-key (keyID) group & auth-user-key (authID) group and to decide
     *             "CENC" & "CMAC".
     *           - For (4 <= keyID <= 13) and (authID = 1), this parameter is used to select user-key (keyID) group
     *             and to decide "CENC" & "CMAC". */
    hseKeyGroupIdx_t sheGroupIndex;
    uint8_t          reserved[3];
    /** @brief   INPUT: Pointer to M1 */
    HOST_ADDR      pM1;
    /** @brief   INPUT: Pointer to M2 */
    HOST_ADDR      pM2;
    /** @brief   INPUT: Pointer to M3 */
    HOST_ADDR      pM3;
    /** @brief   OUTPUT: Pointer to M4 */
    HOST_ADDR      pM4;
    /** @brief   OUTPUT: Pointer to M5 */
    HOST_ADDR      pM5;
} hseSheLoadKeySrv_t;


/** @brief SHE load plain key service.
 *  @details Load a SHE RAM key from plain text */
typedef struct
{
    /** @brief   INPUT: Pointer to the unencrypted key */
    HOST_ADDR  pKey;
} hseSheLoadPlainKeySrv_t;


/** @brief SHE export RAM key service.
 *  @details Export a SHE RAM key in the format used for re-loading with SHE Load key. This export can
 *           happen only if RAM key was loaded using SHE RAM plain key service. */
typedef struct
{
    /** @brief   OUTPUT: Pointer to M1 */
    HOST_ADDR  pM1;
    /** @brief   OUTPUT: Pointer to M2 */
    HOST_ADDR  pM2;
    /** @brief   OUTPUT: Pointer to M3 */
    HOST_ADDR  pM3;
    /** @brief   OUTPUT: Pointer to M4 */
    HOST_ADDR  pM4;
    /** @brief   OUTPUT: Pointer to M5 */
    HOST_ADDR  pM5;
} hseSheExportRamKeySrv_t;

/** @brief SHE get ID service.
 *  @details Returns the Identity (UID) and the value of the status register protected by a
 *           MAC over a challenge and the data.
 *           If MASTER_ECU_KEY is empty, the returned MAC has to be set to zero.
 *
 *  @note For HSE_H/M, the UID is read by HSE from system fuses. The application must provide read-only access (xRDC restriction) to HSE to read the UID.*/
typedef struct
{
    /** @brief   INPUT: Pointer to 128-bit Challenge */
    HOST_ADDR  pChallenge;
    /** @brief   OUTPUT: Pointer to 120-bit UID */
    HOST_ADDR  pId;
    /** @brief   OUTPUT: Pointer to 8-bit Status Register (SREG).
     *                   Refer to HSE Status for status related information (boot, debug, etc.) */
    HOST_ADDR  pSreg;
    /** @brief   OUTPUT: Pointer to 128-bit CMAC(CHALLENGE | ID | SREG) using MASTER_ECU_KEY as key. */
    HOST_ADDR  pMac;
} hseSheGetIdSrv_t;

/** @} */
#endif

#ifdef HSE_SPT_HASH

/*==================================================================================================
                                 STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/


/**
* @brief          HASH service.
* @details        The HASH service is used to map data of arbitrary size to data of fixed size.
*                 The values returned by a hash function are called hash values, hash codes, digests, or simply hashes.
*
*                 The HASH service can be accessible in one-pass or streaming (SUF) mode.
*                 In case of streaming mode, three steps (calls) will be used: START, UPDATE, FINISH.
*                 START and FINISH are mandatory; UPDATE is optional.
*                 Not all fields are used by each access mode.
*
*  The table below summarizes which fields are used by each access mode.
*  Unused fields are ignored by the HSE.
*
*  |Field \ Mode      | One-pass  | Start | Update  | Finish  |
*  |-----------------:|:---------:|:-----:|:-------:|:-------:|
*  | accessMode       |     *     |   *   |    *    |    *    |
*  | streamId         |           |   *   |    *    |    *    |
*  | hashAlgo         |     *     |   *   |         |         |
*  | sgtOption        |     *     |   *   |    *    |    *    |
*  | inputLength      |     *     |   *   |    *    |    *    |
*  | pInput           |     *     |   *   |    *    |    *    |
*  | pHashLength      |     *     |       |         |    *    |
*  | pHash            |     *     |       |         |    *    |
*/
typedef struct
{
    /** @brief   INPUT: Specifies the access mode: ONE-PASS, START, UPDATE, FINISH.
     *           @note
     *           - Miyaguchi-Preneel does not support streaming. For MP this parameter is ignored
     *           and considered default ONE-PASS.
     *           STREAMING USAGE: Used in all steps. */
    hseAccessMode_t  accessMode;

    /** @brief   INPUT: Specifies the stream to use for START, UPDATE, FINISH access modes. Each interface supports
     *           a limited number of streams per interface, up to #HSE_STREAM_COUNT.
     *           @note
     *           - Miyaguchi-Preneel does not support streaming. For MP this parameter is ignored.
     *           STREAMING USAGE: Used in all steps. */
    hseStreamId_t    streamId;

    /** @brief   INPUT: Specifies the hash algorithm. <br>
     *           STREAMING USAGE: Used in START. */
    hseHashAlgo_t    hashAlgo;

    /** @brief  INPUT: Specify if pInput is provided as hseScatterList_t list (the host address points to a hseScatterList_t list).
     *                 Ignored if SGT is not supported.
     *                 @note
     *                 - SGT is not available for the following hash algorithms and the parameter is ignored:
     *                      - Miyaguchi-Preneel
     *                      - SHA3 (unless the targeted platform has #HSE_SPT_HW_SHA3 defined)
     *                      - SHA2_384/512 for HSE_B devices (not available in hardware)
     *                 - ONLY HSE_SGT_OPTION_INPUT can be used. #HSE_SGT_OPTION_OUTPUT will be ignored if used, as output is always considered a buffer.
     *                 - If scatter option is selected (set), the length (e.g. #inputLength) shall specified the entire message length (sum of all hseScatterList_t lengths).
     *                 - The number for SGT entries shall be less then #HSE_MAX_NUM_OF_SGT_ENTRIES.<br>
     *           STREAMING USAGE: Used in all steps.*/
    hseSGTOption_t   sgtOption;

    /** @brief   INPUT: Length of the input message. Can be zero (except Miyaguchi-Preneel). <br>
     *                  For Miyaguchi-Preneel, inputLength must be multiple of 16 bytes and not equal to zero. <br>
     *           STREAMING USAGE: Used in all steps.
     *            - START: Must be a multiple of block length, or zero.
     *            - UPDATE: Must be a multiple of block length. Cannot be zero. Refrain from issuing the service request, instead of passing zero.
     *            - FINISH: Can be any value.
     *
     *           Algorithm block lengths:
     *            - Miyaguchi-Preneel: not supported in streaming mode
     *            - SHA1, SHA2_224, SHA2_256: 64
     *            - SHA2_384, SHA2_512, SHA2_512_224, SHA2_512_256: 128
     *            - SHA3-224: 144
     *            - SHA3-256: 136
     *            - SHA3-384: 104
     *            - SHA3-512: 72
     *            - SHA3: If the targeted platform does NOT have #HSE_SPT_HW_SHA3 defined, there is no limitation (input can be any size) */
    uint32_t         inputLength;
    /** @brief   INPUT: Address of the input message. <br>
     *                  For Miyaguchi-Preneel, according to SHE specification, the input shall be (K | C | padding). <br>
     *                  Ignored if inputLength is zero.<br>
     *           STREAMING USAGE: Used in all steps (except if inputLength is zero). */
    HOST_ADDR        pInput;

    /** @brief   INPUT/OUTPUT: Pointer to a uint32_t location in which the hash length in bytes is stored.
                               On calling this service, this parameter shall contain the size of the buffer provided by host.
                               When the request has finished, the actual length of the returned value shall be stored. If the buffer
                               is smaller than the size of the hash, the hash will be truncated (not applicable for Miyaguchi Preneel). <br>
                               For Miyaguchi-Preneel, if the buffer is smaller than the size of the hash (16 bytes), parameter will be
                               considered invalid. If the buffer is larger, #pHashLength is adjusted to the size of the hash.
                               A hash buffer length (i.e. a #pHashLength) of zero makes no sense, and is considered invalid.<br>
     *           STREAMING USAGE: MANDATORY for FINISH */
    HOST_ADDR        pHashLength;

    /** @brief   OUTPUT: The address of the output buffer where the resulting hash will be stored. <br>
     *           STREAMING USAGE: MANDATORY for FINISH. */
    HOST_ADDR        pHash;
} hseHashSrv_t;

/** @} */
#endif

#ifdef HSE_SPT_SIPHASH

/*==================================================================================================
 *                                      DEFINES AND MACROS
 * ==================================================================================================*/

/** @brief   HSE SipHash algorithm.*/
typedef uint8_t hseSipHashVariant_t;
#define HSE_SIPHASH_VARIANT_64       ((hseSipHashVariant_t)0x2U)  /**< @brief 64 bit SipHash - the classic. Perform a SipHash_2_4 calculation. */
#define HSE_SIPHASH_VARIANT_128      ((hseSipHashVariant_t)0x4U)  /**< @brief 128 bit SipHash */

/*==================================================================================================
 *                                             ENUMS
 * ==================================================================================================*/

/*==================================================================================================
 *                               STRUCTURES AND OTHER TYPEDEFS
 * ==================================================================================================*/

/**
 * @brief          SipHash service.
 * @details        SipHash is a method to provide message authentication codes (MACs), also known as tags.
 *                 These can be used to verify both the integrity and authenticity of a message.
 *                 SipHash is optimized for fast processing speeds when used to authenticate small
 *                 messages.
 *
 *                 This service is only accessible in one-pass.
 */
typedef struct
{
    /** @brief   INPUT: Specifies the direction: generate/verify. */
    hseAuthDir_t        authDir;

    /** @brief   INPUT: Specifies the SipHash variant: 64 or 128 bits. This is also the tag length in bits.
     *              The classic SipHash_2_4 is selected by picking #HSE_SIPHASH_VARIANT_64.
     *              @note At present we do not support a variable number of SipRounds */
    hseSipHashVariant_t sipHashVariant;

    /** @brief   INPUT: The length of the input message. Can be zero. */
    uint16_t            inputLength;

    /** @brief   INPUT: The key to be used for the operation. Must be a slot of type #HSE_KEY_TYPE_SIPHASH,
     *              of the appropriate size for the variant.<br>
     *              Key sizes for each SipHash variant are:
     *                  - #HSE_SIPHASH_VARIANT_64:  128 bits (16 bytes)
     *                  - #HSE_SIPHASH_VARIANT_128: 128 bits (16 bytes) */
    hseKeyHandle_t      keyHandle;

    /** @brief   INPUT: The input message.*/
    HOST_ADDR           pInput;

    /** @brief   INPUT: The tag length in bytes is stored. Zero length is invalid.
     *                  - GENERATE:
     *                    - On calling service, this parameter shall contain the size of the buffer provided by pTag.
     *                    - If a truncated tag is desired, provide a shorter tag length.
     *                    - Requested tag lengths greater than the algorithm variant output will be truncated to algorithm output
     *                      (e.g. SipHash64 tag lengths greater than 8 will be truncated to 8)
     *                  - VERIFY:
     *                    - On calling service, this parameter shall contain the tag length to be verified.
     *                    - Tag lengths less than the variant output assume a truncated tag.
     *                    - Tag lengths greater than the variant output are invalid.
     *                      (e.g. SipHash64 tag lengths greater than 8 are invalid). */
    uint8_t             tagLength;

    uint8_t             reserved[3];

    /** @brief   OUTPUT/INPUT: The output tag for "generate"; the input tag for "verify". */
    HOST_ADDR           pTag;
} hseSipHashSrv_t;

/** @} */
#endif

#ifdef HSE_SPT_AEAD

/*==================================================================================================
                                 STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/

/**
* @brief          AEAD  service.
* @details        Authenticated Encryption with Associated Data (AEAD, also known as Authenticated Encryption)
*                 is a block cipher mode of operation which also allows integrity checks (e.g. AES-GCM).
*                 Additional authenticated data (AAD) is optional additional input header which is authenticated,
*                 but not encrypted. Both confidentiality and message authentication is provided on the input plaintext.
*
*                 This service can be accessible in one-pass or streaming (SUF) mode.
*                 In case of streaming mode, three steps (calls) will be used: START, UPDATE, FINISH.
*                 START and FINISH are mandatory; UPDATE is optional.
*                 Not all fields are used by each access mode.
*
*  @note
*           1. Streaming mode is not supported for CCM.
*           2. The key usage flags used with AEAD operations:
*              - #HSE_KF_USAGE_ENCRYPT specifies that the key can be used for encryption and tag computation
*                (note that the #HSE_KF_USAGE_SIGN flag is not used).
*              - #HSE_KF_USAGE_DECRYPT specifies that the key can be used for decryption and tag verification
*                (note that #HSE_KF_USAGE_VERIFY flag is not used).
*
*  The table below summarizes which fields are used by each access mode.
*  Unused fields are ignored by the HSE.
*
* |Field \ Mode      | One-pass  | Start | Update  | Finish  |
* |-----------------:|:---------:|:-----:|:-------:|:-------:|
* | accessMode       |     *     |   *   |    *    |    *    |
* | streamId         |           |   *   |    *    |    *    |
* | authCipherMode   |     *     |   *   |         |         |
* | cipherDir        |     *     |   *   |         |         |
* | keyHandle        |     *     |   *   |         |         |
* | ivLength         |     *     |   *   |         |         |
* | pIV              |     *     |   *   |         |         |
* | aadLength        |     *     |   *   |         |         |
* | pAAD             |     *     |   *   |         |         |
* | sgtOption        |     *     |   *   |    *    |    *    |
* | inputLength      |     *     |       |    *    |    *    |
* | pInput           |     *     |       |    *    |    *    |
* | tagLength        |     *     |       |         |    *    |
* | pTag             |     *     |       |         |    *    |
* | pOutput          |     *     |       |    *    |    *    |
*/
typedef struct
{
    /** @brief   INPUT: Specifies the access mode: ONE-PASS, START, UPDATE, FINISH. <br>
     *           STREAMING USAGE: Used in all steps. */
    hseAccessMode_t     accessMode;

    /** @brief   INPUT: Specifies the stream to use for START, UPDATE, FINISH access modes. Each interface supports
     *           a limited number of streams per interface, up to #HSE_STREAM_COUNT. <br>
     *           STREAMING USAGE: Used in all steps. */
    hseStreamId_t       streamId;

    /** @brief   INPUT: Specifies the authenticated cipher mode. <br>
     *           STREAMING USAGE: Used in all steps. */
    hseAuthCipherMode_t authCipherMode;

    /** @brief   INPUT: Specifies the cipher direction: encryption/decryption. <br>
     *           STREAMING USAGE: Used in all steps. */
    hseCipherDir_t      cipherDir;

    /** @brief   INPUT: The key to be used for the operation. <br>
     *           STREAMING USAGE: Used in START step. */
    hseKeyHandle_t      keyHandle;

    /** @brief   INPUT: The length of the IV/Nonce (in bytes).
     *                  - CCM valid IV sizes 7, 8, 9, 10, 11, 12, 13 bytes
     *                  - GCM: 1<= ivLength <= 2^32-1. Recommended 12 bytes or greater.
     *
     *           STREAMING USAGE: Used in START. */
    uint32_t            ivLength;

    /** @brief   INPUT: Initialization Vector/Nonce. <br>
     *           STREAMING USAGE: Used in START.
     *           @note
     *           In GCM operations, it is recommended to use IV values of exactly 12 bytes. For any IV size different
     *           from 12 bytes, the authentication tag generated by the GCM encryption operation might not be correct.
     *           In GCM decryption operations, the authentication check might fail. */
    HOST_ADDR           pIV;

    /** @brief   INPUT: The length of AAD Header data (in bytes). Can be zero.
     *                  - CCM: Restricted to lengths less than or equal to (2^16 - 2^8) bytes.
     *
     *           STREAMING USAGE: Used in START. Any AAD is ignored in UPDATE or FINISH, and must be passed to the HSE in START. */
    uint32_t            aadLength;

    /** @brief   INPUT: The AAD Header data. Ignored if aadLength is zero. <br>
     *           STREAMING USAGE: Used in START. Any AAD is ignored in UPDATE or FINISH, and must be passed to the HSE in START. */
    HOST_ADDR           pAAD;

    /** @brief  INPUT: Specify if pInput/pOutput are provided as hseScatterList_t list (the host address points to a hseScatterList_t list).
     *                 Ignored if SGT is not supported.
     *                 @note
     *                 - If scatter option is selected (set), the length (e.g. inputLength) shall specified the entire message length
     *                 (sum of all hseScatterList_t lengths).
     *                 - The number for SGT entries shall be less then #HSE_MAX_NUM_OF_SGT_ENTRIES.
     *
     *           STREAMING USAGE: Used in all steps. */
    hseSGTOption_t      sgtOption;
    uint8_t             reserved[3];

    /** @brief   INPUT: The length of the plaintext and ciphertext (in bytes).
     *                  Can be zero (compute/verify the tag without input message). <br>
     *           STREAMING USAGE:
     *            - START:  The input length is ignored.
     *            - UPDATE: Must be a multiple of block length. Cannot be zero. Refrain from issuing the service request
     *                      instead of passing zero.
     *            - FINISH: All lengths are allowed. */
    uint32_t            inputLength;

    /** @brief   INPUT: The plaintext for "authenticated encryption" or
     *                  the ciphertext for "authenticated decryption". <br>
     *           STREAMING USAGE: Used in UPDATE and FINISH step. Ignored for START step or if inputLength is zero. */
    HOST_ADDR           pInput;

    /** @brief   INPUT: The length of tag (in bytes).
     *                  - CCM valid Tag sizes 4, 6, 8, 10, 12, 14, 16 bytes
     *                  - GCM valid Tag sizes 4, 8, 12, 13, 14, 15, 16 bytes
     *           STREAMING USAGE: Used in FINISH step. */
    uint32_t            tagLength;

    /** @brief   OUTPUT/INPUT: The output tag for "authenticated encryption" or
     *                         the input tag for "authenticated decryption". <br>
     *           STREAMING USAGE: Used in FINISH step. */
    HOST_ADDR           pTag;

    /** @brief   OUTPUT: The ciphertext for "authenticated encryption" or
     *                   the plaintext for "authenticated decryption". <br>
     *           STREAMING USAGE: Used in UPDATE and FINISH step. */
    HOST_ADDR           pOutput;
} hseAeadSrv_t;

/** @} */
#endif

#ifdef HSE_SPT_SIGN
/*==================================================================================================
                                 STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/

/**
* @brief          Digital Signature service.
* @details        Uses the input parameters to perform the signature calculation and stores the signature
*                 in the memory location pointed by the output parameter.
*
*                 This service can be accessible in one-pass or streaming (SUF) mode.
*                 In case of streaming mode, three steps (calls) will be used: START, UPDATE, FINISH.
*                 START and FINISH are mandatory; UPDATE is optional.
*                 Not all fields are used by each access mode.
*
*  The table below summarizes which fields are used by each access mode.
*  Unused fields are ignored by the HSE.
*
* |Field \ Mode      | One-pass  | Start | Update  | Finish  |
* |-----------------:|:---------:|:-----:|:-------:|:-------:|
* | accessMode       |     *     |   *   |    *    |    *    |
* | streamId         |           |   *   |    *    |    *    |
* | signScheme       |     *     |   *   |         |         |
* | authDir          |     *     |   *   |         |         |
* | keyHandle        |     *     |   *   |         |         |
* | sgtOption        |     *     |   *   |    *    |    *    |
* | inputLength      |     *     |   *   |    *    |    *    |
* | pInput           |     *     |   *   |    *    |    *    |
* | pSignatureLength |     *     |       |         |    *    |
* | pSignature       |     *     |       |         |    *    |
*/
typedef struct
{
    /** @brief   INPUT: Specifies the access mode: ONE-PASS, START, UPDATE, FINISH. <br>
     *           STREAMING USAGE: Used in all steps.*/
    hseAccessMode_t accessMode;

    /** @brief   INPUT: Specifies the stream to use for START, UPDATE, FINISH access modes. Each interface supports
     *           a limited number of streams per interface, up to #HSE_STREAM_COUNT. <br>
     *           STREAMING USAGE: Used in all steps.*/
    hseStreamId_t   streamId;

    /** @brief   INPUT: Specifies the direction: generate/verify. <br>
     *           STREAMING USAGE: Used in START.*/
    hseAuthDir_t    authDir;

    /** @brief   INPUT: Specifies that the input is already hashed with the algorithm in specified in the sign scheme.
     *                  Not valid for any signing scheme that does not perform prehashing (i.e. PureEDDSA)
     *           @note The hashing algorithm must still be provided as it is included in the signature for various schemes (e.g. RSA)
     *           STREAMING USAGE: Not supported in streaming mode.*/
    bool_t          bInputIsHashed;


    /** @brief   INPUT: Scheme for selected Signature algo. <br>
     *           STREAMING USAGE: Used in START.*/
    hseSignScheme_t signScheme;

    /** @brief   INPUT: The key to be used for the operation. <br>
     *           STREAMING USAGE: Used in START.*/
    hseKeyHandle_t  keyHandle;

    /** @brief  INPUT: Specify if pInput is provided as hseScatterList_t list (the host address points to a hseScatterList_t list).
     *                 Ignored if SGT is not supported.
     *                 @note
     *                 - ONLY HSE_SGT_OPTION_INPUT can be used (the rest of the bits are ignored)
     *                 - Scatter option is supported only for RSA and ECDSA. For EDDSA, it is not supported.
     *                 - Scatter option is not supported for SHA3 hashes (unless the targeted platform has #HSE_SPT_HW_SHA3 defined).
     *                 - Scatter option is not supported for pre-hashed inputs
     *                 - If scatter option is selected (set), the length (e.g. #inputLength) shall specified the entire message length
     *                 (sum of all hseScatterList_t lengths).
     *                 - The number for SGT entries shall be less then #HSE_MAX_NUM_OF_SGT_ENTRIES. <br>
     *          STREAMING USAGE: Used in all steps.*/
    hseSGTOption_t  sgtOption;

    uint8_t         reserved[3U];

    /** @brief   INPUT: The length of the message.
     *                  For RSA schemes, this must be the length of the original (not pre-hashed) input. <br>
     *           STREAMING USAGE: Used in all steps.
     *            - START: Must be a multiple of block length of the hash, or zero.
     *            - UPDATE: Must be a multiple of block length of the hash. Cannot be zero. Refrain from issuing the service request, instead of passing zero.
     *            - FINISH: Can be any value.
     *
     *           Algorithm block lengths:
     *            - SHA1, SHA2_224, SHA2_256: 64
     *            - SHA2_512_224, SHA2_512_256, SHA2_384, SHA2_512: 128
     *            - SHA3-224: 144
     *            - SHA3-256: 136
     *            - SHA3-384: 104
     *            - SHA3-512: 72
     *            - SHA3: If the targeted platform does NOT have #HSE_SPT_HW_SHA3 defined, there is no limitation (input can be any size)
     *           @note EDDSA does not support streaming */
    uint32_t        inputLength;

    /** @brief   INPUT: The address of the message to be signed/verify.
     *                  For RSA schemes, this is the actual (not pre-hashed) input. <br>
     *           STREAMING USAGE: Used in all steps.*/
    HOST_ADDR       pInput;

    /** @brief   INPUT/OUTPUT: An array of two addresses of two uint32_t values containing signature lengths. It is input/output for "generate" and input for "verify".
     *                         On calling "generate" service, these parameter shall contain the size of the signature buffers provided by the application.
                               When the request has finished, the actual lengths of the signature components. <br>
     *           STREAMING USAGE: Used in FINISH. */
    HOST_ADDR       pSignatureLength[2];

    /** @brief   OUTPUT: Where the signature components must be stored.  It is output for "generate" and input for "verify".
     *                   - RSA has a single signature component, at index 0, and the size of buffer must be at least the byteLength(public modulus n)
     *                   - ECDSA and EDDSA signature format as (r,s), with r at index 0, and s at index 1.
     *                     The buffer size for each component must be at least the length of the used curve in bytes (e.g. 32 bytes for a 256 bit curve).<br>
     *           STREAMING USAGE: Used in FINISH. */
    HOST_ADDR       pSignature[2];
} hseSignSrv_t;

/*==================================================================================================
                                 GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/

/*==================================================================================================
                                     FUNCTION PROTOTYPES
==================================================================================================*/


/** @} */

#endif

#ifdef HSE_SPT_RSA
/*==================================================================================================
                                 STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/
/**
* @brief          RSA Cipher service.
* @details        Performs the RSA Cipher (Encryption/Decryption) (RSAEP) operation.
*/
typedef struct
{
    /** @brief   INPUT: The RSA cipher scheme. */
    hseRsaCipherScheme_t    rsaScheme;
    /** @brief   INPUT: Specifies the cipher direction: encryption/decryption.*/
    hseCipherDir_t          cipherDir;
    uint8_t                 reserved[3];
    /** @brief   INPUT: The key to be used for the operation. */
    hseKeyHandle_t          keyHandle;
    /** @brief   INPUT: The input length (plaintext or ciphertext):
     *                 - The length of the ciphertext should be #HSE_BITS_TO_BYTES(keyBitLen) .
     *                 - The length of the plaintext (in bytes):
     *                      - For RSAES NO PADDING, the Input Length must be less than or equal to #HSE_BITS_TO_BYTES(keyBitLen), and
     *                        #pInput is considered a big-endian integer.
     *                      - For RSAES-PKCS1-v1_5, the Input Length shall not be greater than #HSE_BITS_TO_BYTES(keyBitLen) -11 bytes.
     *                      - For RSAES-OAEP, Input Length shall not be greater than #HSE_BITS_TO_BYTES(keyBitLen) - 2 * hashLen - 2 bytes. */
    uint32_t                inputLength;
    /** @brief   INPUT: The plaintext for encryption or the ciphertext for decryption. */
    HOST_ADDR               pInput;
    /** @brief   INPUT/OUTPUT: Holds the address to a location (an uint32_t variable) in which the output length in bytes is stored.  <br>
                               On calling this service, this parameter shall contain the size of the buffer
                               provided by the application.
                               When the request has finished, the actual length of the returned value shall be stored.*/
    HOST_ADDR               pOutputLength;
    /** @brief   OUTPUT: The address of the Output. The plaintext for decryption or ciphertext for encryption.
     *                   The size of output must be at least the #HSE_BITS_TO_BYTES(keyBitLen) */
    HOST_ADDR               pOutput;
} hseRsaCipherSrv_t;

/** @} */
#endif

#ifdef HSE_SPT_AUTHENC

/*==================================================================================================
                                 STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/


/**
* @brief          HSE Authenticated Encryption
* @details        This service allows to perform in parallel the Encrypt-then-MAC operation using NULL/AES cipher
*                 and MAC algorithms.
*                 HSE Authenticated Encryption uses two keys:
*                 one for encryption/decryption and another for MAC generate/verify.<br>
*                 The authenticated encryption service (hseAuthEncSrv_t) supports the following combinations:
*                   - AES_(ECB, CBC, CTR, CFB, OFB) and HMAC_ (SHA1, SHA2_224, SHA2_256, SHA2_384, SHA2_512);
*                     CMAC/GMAC/XCBC_MAC are not supported with AES encryption.
*                   - NULL cipher with all MAC algorithms (CMAC, GMAC, XCBC_MAC, HMAC_(SHA1, all SHA2))
*/
typedef struct
{
    /** @brief   INPUT: Specifies the cipher algorithm. Can be either #HSE_CIPHER_ALGO_NULL or #HSE_CIPHER_ALGO_AES.
     */
    hseCipherAlgo_t      cipherAlgo;
    /** @brief   INPUT: Specifies the block cipher mode. All cipher block modes are supported. Ignored if HSE_CIPHER_ALGO_NULL is used.
     */
    hseCipherBlockMode_t cipherBlockMode;
    /** @brief   INPUT: Specifies the cipher direction: encryption/decryption or MAC generate/verify.
     */
    hseCipherDir_t       cipherDir;
    /** @brief  INPUT: Specify if pInput/pOutput are provided as hseScatterList_t list (the host address points to a hseScatterList_t list).
     *                 Ignored if SGT is not supported.
     *                 @note
     *                 - If scatter option is selected (set), the length (e.g. inputLength) shall specified the entire message length
     *                 (sum of all hseScatterList_t lengths).
     *                 - The number for SGT entries shall be less then #HSE_MAX_NUM_OF_SGT_ENTRIES.
     * */
    hseSGTOption_t      sgtOption;
    /** @brief   INPUT: The key to be used for the cipher operation.<br>
     *                  This parameter is ignored if #HSE_CIPHER_ALGO_NULL is used.
     */
    hseKeyHandle_t       cipherKeyHandle;
    /** @brief   INPUT: Specifies the authentication scheme. All MAC schemes are supported.
     *                  @note The IV from GMAC is ignored (the IV from this structure is used).
     */
    hseMacScheme_t       macScheme;
    /** @brief   INPUT: The key to be used for the MAC operation.
                        @note HMAC key size shall be less than hash block size (e.g. 64bytes for SHA2_256).
    */
    hseKeyHandle_t       authKeyHandle;
    /** @brief   INPUT: The length of the plaintext and ciphertext (in bytes).*/
    uint32_t             inputLength;
    /** @brief   INPUT: The plaintext for "authenticated encryption"; the ciphertext for "authenticated decryption".
    */
    HOST_ADDR            pInput;
    /** @brief   INPUT: The length of the IV/Nonce (in bytes)used for AES cipher. Not used for ECB mode.
     */
    uint32_t             ivLength;
    /** @brief   INPUT: Initialization Vector/Nonce used for AES cipher. Not used for ECB mode.
     *                  @note The IV is also used for GMAC authentication scheme when processed.
     */
    HOST_ADDR            pIV;
    /** @brief   INPUT: Length of Additional Authenticated Data (AAD). Optional (can be 0)
     */
    uint32_t             aadLength;
    /** @brief   INPUT: Pointer to Additional Authenticated Data (AAD) buffer. Optional (can be NULL)
     */
    HOST_ADDR            pAAD;
    /** @brief   OUTPUT: The ciphertext for "authenticated encryption" or the plaintext for "authenticated decryption".
     */
    HOST_ADDR            pOutput;
    /** @brief   INPUT/OUTPUT: Holds the address to a memory location (an uint32_t variable) in which the tag length in bytes is stored.
     *                          GENERATE:
     *                           - On calling service (input), this parameter shall contain the size of the buffer provided by pTag.
     *                           - For GMAC, valid tag lengths are 4, 8, 12, 13, 14, 15 and 16. Tag-lengths greater than 16 will be truncated
     *                             to 16.
     *                           - For HMAC, valid tag lengths are [1, hash-length]. Tag-lengths greater than hash-length will be truncated
     *                             to hash-length.
     *                           - For CMAC & XCBC-MAC, valid tag lengths are [4, cipher-block-length]. Tag-lengths greater than
     *                             cipher-block-length will be truncated to cipher-block-length.
     *                           - When the request has finished (output), the actual length of the returned value shall be stored. <br>
     *                          VERIFY:
     *                           - On calling service (input), this parameter shall contain the tag-length to be verified.
     *                           - For GMAC, valid tag lengths are 4, 8, 12, 13, 14, 15 and 16.
     *                           - For HMAC, valid tag lengths are [1, hash-length].
     *                           - For CMAC & XCBC-MAC, valid tag lengths are [4, cipher block-length].
     */
    HOST_ADDR            pTagLength;
    /** @brief   OUTPUT/INPUT: The output tag for "authenticated encryption" or
     *                         the input tag for "authenticated decryption". <br>
     *                         Ignored if tagLength is zero.
     */
    HOST_ADDR            pTag;
} hseAuthEncSrv_t;

/** @} */
#endif

#ifdef HSE_SPT_SMR_CR
/*==================================================================================================
*                                      DEFINES AND MACROS
==================================================================================================*/

/** @brief Decryption of SMR is not used. */
#define HSE_SMR_DECRYPT_KEY_HANDLE_NOT_USED  (0UL)
/** @brief SMR version is not used (value to ignore hseSmrEntryInstallSrv_t#versionOffset field). */
#define HSE_SMR_VERSION_NOT_USED             (0UL)

/** @brief CORE sanctions to be applied if the verification of at least one SMR entry fails
           on both Primary and Backup SMR maps as defined in CR entry (hseCrEntry_t#preBootSmrMap and hseCrEntry_t#altPreBootSmrMap) */
typedef uint16_t hseCrSanction_t;
#define HSE_CR_SANCTION_DIS_INDIV_KEYS       ((hseCrSanction_t)0x7433U)    /**< @brief Disable individual keys; if at least one SMR entry specified by the key smrFlags (see hseKeyInfo_t) is not verified, the key can not be used. */
#define HSE_CR_SANCTION_KEEP_CORE_IN_RESET   ((hseCrSanction_t)0x7455U)    /**< @brief The HSE keeps in reset the core (if the verification of at least one SMR entry fails) */
#define HSE_CR_SANCTION_RESET_SOC            ((hseCrSanction_t)0x8B17U)    /**< @brief The HSE reset the SoC. */
#define HSE_CR_SANCTION_DIS_ALL_KEYS         ((hseCrSanction_t)0x8B1EU)    /**< @brief Disable all keys */


/** @brief The start option for a Core Reset Entry */
typedef uint16_t hseCrStartOption_t;
#define HSE_CR_AUTO_START                    ((hseCrStartOption_t)0x35A5U) /**< @brief The Core is released from reset automatically at startup (if the coresponding SMR(s) are loaded and verified). */
#define HSE_CR_ON_DEMAND                     ((hseCrStartOption_t)0x5567U) /**< @brief The Core is not released from reset automatically; this can be triggered by another Application Core using hseCrOnDemandBootSrv_t service. */


/** @brief Specifies the boot interface (where the SMR needs to be copied from).
      @note
      - For HSE_H/M, the SMR source memory can be:
            - QSPI Flash
            - SD card
            - MMC
            - LPDDR4 Flash (used only for S32ZE devices)
            - for different SMR(s), any combination of the above memory interfaces, except MMC and SD (e.g. QSPI/LPDDR4 Flash and SD, QSPI/LPDDR4 Flash and MMC).
      - For HSE_B, the source memory flags (QSPI/SD/MMC/LPDDR4) are not used.
*/
typedef uint8_t hseSmrConfig_t;
#define HSE_SMR_CFG_FLAG_QSPI_FLASH          ((hseSmrConfig_t)0x0U)        /**< @brief Identifies the Interface (where the SMR needs to be copied from)*/
#define HSE_SMR_CFG_FLAG_SD_FLASH            ((hseSmrConfig_t)0x2U)        /**< @brief Identifies the Interface (where the SMR needs to be copied from)*/
#define HSE_SMR_CFG_FLAG_MMC_FLASH           ((hseSmrConfig_t)0x3U)        /**< @brief Identifies the Interface (where the SMR needs to be copied from)*/

#define HSE_SMR_CFG_FLAG_INSTALL_AUTH        ((hseSmrConfig_t)(1U << 2U))  /**< @brief If it is set, the authentication scheme and tag provided during installation phase (installation TAG) are used also during the verification phase.
                                                                                   If it is cleared, during installation HSE will compute and store an internal hash digest (SHA2-256)
                                                                                   During verification phase, HSE will use this internal digest.
                                                                                   @note
                                                                                   - If the #HSE_SMR_CFG_FLAG_INSTALL_AUTH flag is cleared and SHE-boot is used (SMR #0 with BOOT_MAC_KEY), HSE FW will return #HSE_SRV_RSP_NOT_ALLOWED on SMR#0 installation request. */
#define HSE_SMR_CFG_FLAG_AUTH_AAD            ((hseSmrConfig_t)(1U << 3U))  /**< @brief If this bit is set, the authentication is computed over [AAD || Plain] image.
                                                                                    @note
                                                                                    - The SMR has to be configured with AEAD-GCM decryption (i.e. AAD and GMAC tag are provided as part of decryption parameters). */

/** @brief Options for customizing SMR run-time verification. */
typedef uint16_t hseSmrVerificationOptions_t;
#define HSE_SMR_VERIFICATION_OPTION_NONE           ((hseSmrVerificationOptions_t)0UL)            /** @brief Default verification of the SMR at run-time. */
#define HSE_SMR_VERIFICATION_OPTION_NO_LOAD        ((hseSmrVerificationOptions_t)(3UL << 0U))    /** @brief SMR is verified from the external flash (using pSmrSrc address) even if pSmrDest is specified or if already loaded. Can be used only if SMR is in a memory mapped external flash (e.g. QSPI/LPDDR4 and not SD/eMMC). Additionally the SMR cannot be encrypted. */
#define HSE_SMR_VERIFICATION_OPTION_RELOAD         ((hseSmrVerificationOptions_t)(3UL << 2U))    /** @brief SMR is loaded from the external flash and verified even if it is already loaded. Can be used only if SMR is in a memory mapped external flash (e.g. QSPI/LPDDR4 and not SD/eMMC). */
#if defined(HSE_SPT_INTERNAL_FLASH_DEV)
#define HSE_SMR_VERIFICATION_OPTION_PASSIVE_MEM    ((hseSmrVerificationOptions_t)(3UL << 4U))    /** @brief Only for HSE_B with A/B Swap Configuration. Verifies the SMR from the passive block, applying address translation. */
#endif /* HSE_SPT_INTERNAL_FLASH_DEV */

/*==================================================================================================
*                                             ENUMS
==================================================================================================*/

/*==================================================================================================
                                 STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/

#ifdef HSE_SPT_SMR_DECRYPT
/** @brief   Defines the parameters to decrypt an encrypted SMR.
 *  @details The parameters below are used in the SMR entry only with an encrypted SMR.
 *           @note The following algorithms can be used:
 *           - If pGmacTag == NULL, the SMR must be encrypted using AES-CTR
 *           - If pGmacTag != NULL, the SMR must be encrypted using AEAD-GCM with AAD = NULL (pGmacTag shall point to the GMAC Tag).
 */
typedef struct
{
    hseKeyHandle_t          decryptKeyHandle;   /**< @brief   The key handle referencing the decryption key.
                                                              - If #decryptKeyHandle == #HSE_SMR_DECRYPT_KEY_HANDLE_NOT_USED, the SMR is not encrypted; all the fields below are ignored.
                                                              - If #decryptKeyHandle != #HSE_SMR_DECRYPT_KEY_HANDLE_NOT_USED, the #decryptKeyHandle specifies the key used to decrypt the SMR.
                                                              @note
                                                                - The used algorithm is always AEAD-GCM, where GMAC and AAD are optional.
                                                                - If the GMAC tag is provided (is not NULL), the same key is also used to verify the tag. */
    uint32_t                pGmacTag;           /**< @brief   The Tag used for GCM. If it set NULL, AES-CTR (instead of GCM) is used for decryption.
                                                              - If #pGmacTag == NULL, an internal hash is computed at installation over the encrypted SMR. This internal hash is used at verification phase.
                                                              - If #pGmacTag != NULL, the external stored GMAC tag (in flash) is used to verify the encrypted SMR.
                                                                The length considered in this case is 16 bytes. */
    uint8_t                 aadLength;          /**< @brief   Optional - the length in bytes of the Authenticated Additional Data (AAD). <br>
                                                              - If not used, the length can be zero; <br>
                                                              - If used, the length can be either 64 or 128 bytes.
                                                              - If used, #pGmacTag must also be provided. */
    uint8_t                 reserved[3U];       /**< @brief   Reserved - alignment. */
    uint32_t                pAAD;               /**< @brief   Optional - the AAD used for AEAD. <br>
                                                              - Ignored if aadLength is zero; <br>
                                                              - If provided, the AAD is NOT stored by HSE internally; pAAD address must point to an external flash location that HSE will use during verification. */
} hseSmrDecrypt_t;
#endif /* HSE_SPT_SMR_DECRYPT */


/** @brief   Define the parameters of a Secure Memory Region (SMR) entry in a SMR table.
 *  @details The SMR entry is installed and verified in two phases:
 *           1. "Installation Phase" (using hseSmrEntryInstallSrv_t service).
 *                - The parameters related to SMR authetication and encryption, namely #authScheme, #authKeyHandle and if the SMR is encrypted, hseSmrDecrypt_t#decryptKeyHandle and hseSmrDecrypt_t#pGmacTag
 *                  will be used by HSE at installation time from the hseSmrEntry_t structure referenced in the hseSmrEntryInstallSrv_t#pSmrEntry.
 *                - This phase happens at run-time and as a consequence any data provided to HSE must be memory-mapped (QSPI/LPDDR4/RAM). In case an SMR lying in SD/eMMC is installed, a copy of the data that is not stored
 *                  by the HSE internally must be done available in RAM (e.g. SMR source, signature, AAD, GMAC tag, etc.). At installation time HSE will use the matching pointer fields from the hseSmrEntryInstallSrv_t structure to access the data.
 *           2. "Verification Phase" that can be configured to be performed in two modes:
 *                - Verify with the Original/Installation Authentication TAG over the plaintext (#HSE_SMR_CFG_FLAG_INSTALL_AUTH flag is set); the #pInstAuthTag parameter must be provided and must point to original signature.
 *                - Verify using an internal computed hash (#HSE_SMR_CFG_FLAG_INSTALL_AUTH flag is cleared); #pInstAuthTag is not used in this case.
 *                - In the same manner, if the SMR is encrypted, HSE can use the provided hseSmrDecrypt_t#pGmacTag (original) or an internally computed hash to verify the encrypted SMR before decryption.
 */
typedef struct
{
    uint32_t            pSmrSrc;            /**< @brief Source address where the SMR needs to be loaded from. This address must be absolute address. */
    uint32_t            smrSize;            /**< @brief The size in bytes of the SMR to be loaded/verified. */
    HOST_ADDR           pSmrDest;           /**< @brief Destination address of SMR (where to copy the SMR after authentication).
                                                        @note
                                                        - For HSE_B, if this parameter is specified (i.e. pSmrDest != NULL), pSmrDest and (pSmrDest + smrSize) must be aligned to 16 bytes. */
    hseSmrConfig_t      configFlags;        /**< @brief Configuration flags of SMR entry (see #hseSmrConfig_t). */
    uint8_t             reserved0[3U];      /**< @brief Reserved for alignment. */
    uint32_t            checkPeriod;        /**< @brief If #checkPeriod != 0, HSE verify the SMR entry periodically (in background).
                                                        Specifies the verification period in x100 milliseconds when HSE is running at maximum frequency.
                                                        Otherwise, the period is multiplied by the factor max_freq/actual_freq (e.g. 10ms at 400MHz, 20ms at 200MHz, etc).
                                                        @note
                                                        - The value 0xFFFFFFFFUL invalid; the checkPeriod max value must be [MAX_UNSIGNED32_INT - 1].
                                                        - If the checkPeriod is non zero, the #pSmrDest must be non zero and the #configFlags must be zero.
                                                        - The SMR periodic verification will start on next boot after PRE and POST boot verification.
                                                        - If the periodic SMR verification is used, the HSE firmware always uses the internal hash for verification. */
    hseKeyHandle_t      authKeyHandle;      /**< @brief The key handle used to check the authenticity of the plaintext SMR.
                                                        @note
                                                        - If the #HSE_SMR_CFG_FLAG_INSTALL_AUTH flag is cleared, the authKeyHandle is used only in the Installation Phase.
                                                        - The key flags must be configured as follow: #HSE_KF_USAGE_VERIFY must be set, #HSE_KF_USAGE_SIGN flag must NOT be set.*/
    hseAuthScheme_t     authScheme;         /**< @brief The authentication scheme used to verify the SMR either during the Installation Phase or Verification phase.
                                                        - If the #HSE_SMR_CFG_FLAG_INSTALL_AUTH flag is set (see #hseSmrConfig_t), the same authentication scheme (installation TAG) can be used to
                                                        verify the authenticity of SMR during verification phase too;
                                                        - Otherwise an internal authentication scheme is used.
                                                        @note
                                                        - The authKeyHandle must match the authentication scheme (e.g. a RSA key must be used for RSA signature).
                                                        - Pure EDDSA scheme (eddsa.bHashEddsa != TRUE) is not supported for streaming installation.
                                                        - Pure EDDSA scheme (eddsa.bHashEddsa != TRUE) is not supported with encrypted SMR.
                                                        - EDDSA scheme Context (if used) can be maximum 16 bytes. */
    uint32_t            pInstAuthTag[2];    /**< @brief Optional - The location in external flash of the initial proof of authenticity over SMR.
                                                        - If the #HSE_SMR_CFG_FLAG_INSTALL_AUTH flag is set, it specifies the address(es) where the SMR original authentication TAG to be verified is located.
                                                        - If the #HSE_SMR_CFG_FLAG_INSTALL_AUTH flag is cleared, this field is not used (an internal authentication scheme is used).
                                                        @note
                                                        - The SMR authentication proof is always computed over the plain SMR.
                                                        - For MAC and RSA signature, only pInstAuthTag[0] is used.
                                                        - Both addresses are used for ECDSA and EDDSA signatures (specified by (r,s), with r at index 0, and s at index 1). */
    #if defined(HSE_SPT_SMR_DECRYPT)
    hseSmrDecrypt_t     smrDecrypt;         /**< @brief Specifies the parameters for SMR decryption */
    #endif

    uint32_t versionOffset;                 /**< @brief Optional - The offset in SMR where the image version can be found.
                                                        May be used to provide the SMR version which offers anti-rollback protection for the image against attacks during update.
                                                        @note
                                                        - Ignored if set to #HSE_SMR_VERSION_NOT_USED (i.e. 0).
                                                        - If used, it must be a valid offset within the SMR in the range [4, hseSmrEntry_t#smrSize - 4].
                                                        - Once used when installing an SMR, all subsequent updates of that SMR must have a version GREATER than the previous one.
                                                        - During SMR update the version offset can be modified only having SU rights. The version value must still be GREATER than the previous one.
                                                        - The version offset must be aligned to 4 bytes.
                                                        - Not used for SHE based secure boot (must be set to #HSE_SMR_VERSION_NOT_USED in this case). */
} hseSmrEntry_t;

/** @brief   Define the parameters of a Core Reset entry in CR table.
 *  @details The CR table contains the configurations for each Application Core that HSE will use to perform the advanced secure boot.
 *  @note
 *    - SU right are needed to install/update a Core reset entry.
 *    - Updating an existing CR entry is conditioned by having all preBoot and postBoot SMR(s) linked with the previous entry verified successfully (applicable only in OEM_PROD/IN_FIELD LCs).
 *    - The core release strategy is defined by the #HSE_CORE_RESET_RELEASE_ATTR_ID attribute ("ALL-AT-ONCE" or "ONE-BY-ONE")
 *    - For devices with SD/eMMC support (e.g. HSE_H), the SMR having the source address in SD/eMMC can be used only if the following conditions are met:
 *        - The release core strategy is either set to "ALL-AT-ONCE" or "ONE-BY-ONE", the SMR in SD/eMMC is linked only to the first entry in the CR table (see #hseAttrCoreResetRelease_t).
 *        - The #startOption is #HSE_CR_AUTO_START.
 *        - SMR type: either SMR is linked via #preBootSmrMap or #altPreBootSmrMap to the CR entry (i.e. will be loaded and verified in PRE-BOOT phase).
 *        - SMR type: or     SMR is linked via #postBootSmrMap when #preBootSmrMap & #altPreBootSmrMap are zero (i.e. will be used for parallel secure boot - loaded in PRE-BOOT phase and verified POST-BOOT).
 */
typedef struct
{
    hseAppCore_t        coreId;             /**< @brief Identifies the core Id to be started (see hseAppCore_t for core mapping). */
    uint8_t             reserved0[1U];
    hseCrSanction_t     crSanction;         /**< @brief The sanction applied if one of the SMR(s) linked to the CR entry failed the verification.
                                                    @note
                                                    - If at least one SMR from each PRE-BOOT bitfield (i.e. #preBootSmrMap and #altPreBootSmrMap) failed verification, the sanction will be applied prior to releasing the core from reset.
                                                    - If on SMR specified by #postBootSmrMap failed, the sanction will be applied after the core is released from reset. In this case, the #HSE_CR_SANCTION_KEEP_CORE_IN_RESET option has no effect.
                                                    - #HSE_CR_SANCTION_DIS_INDIV_KEYS option has no effect on the behavior of the core itself, but will take effect on the key usage at run-time (see SMR flags from hseKeyInfo_t). */
    uint32_t            preBootSmrMap;      /**< @brief The PRE-BOOT SMR(s) which need to be verified before releasing the core from #pPassReset address. <br>
                                                        It's a 32 bits value, each bit specifies the particular SMR entry index from 0-31. HSE loads and verifies each PRE-BOOT SMR entry specified by this bitfield. */
    uint32_t            pPassReset;         /**< @brief The primary address of the first instruction after a regular reset. The core starts the execution from this address if all #preBootSmrMap SMR(s) have been successfully verified.
                                                        @note
                                                            - The #pPassReset must be within a SMR specified by #preBootSmrMap.
                                                            - If #preBootSmrMap == 0, #pPassReset must be within a SMR specified by #postBootSmrMap.
                                                              In this case, the HSE will attempt a "parallel secure boot" for this core (see #postBootSmrMap description below). */
    uint32_t            altPreBootSmrMap;   /**< @brief The ALT-PRE-BOOT SMR(s) which need to be verified before releasing the core from #pAltReset address. <br>
                                                        It's a 32 bits value, each bit specifying the particular SMR entry index from 0-31. HSE verifies each SMR entry specified by this bitfield. <br>
                                                        The #altPreBootSmrMap SMR(s) are verified ONLY if one of the SMR(s) specified by #preBootSmrMap failed.
                                                        @note
                                                            - Once #altPreBootSmrMap SMR(s) are loaded and the verification process is triggered, the #preBootSmrMap SMR(s) will be considered overwritten/not loaded (see hseSmrVerifySrv_t).
                                                            - If #preBootSmrMap == 0, #altPreBootSmrMap must be also 0 (cannot be used). */
    uint32_t            pAltReset;          /**< @brief The alternative address of the first instruction after a regular reset. The core starts the execution if all #altPreBootSmrMap SMR(s) have been successfully verified.
                                                        @note
                                                            - HSE will try to boot the core from the alternate address only if the #preBootSmrMap SMR(s) verification failed.
                                                            - The #pAltReset must be within a SMR specified by #altPreBootSmrMap.
                                                            - If #altPreBootSmrMap == 0, #pAltReset field is ignored (can not used).
                                                            - If the conditions to boot from #pAltReset are not met (#altPreBootSmrMap == 0, #pAltReset == NULL or one of the #altPreBootSmrMap SMR(s) fails)
                                                              HSE will apply the sanctions as specified in #crSanction field. */
    uint32_t            postBootSmrMap;     /**< @brief The POST-BOOT SMR(s) which need to be loaded after verifying the #preBootSmrMap SMR(s) (if any). <br>
                                                        It's a 32 bits value, each bit specifying the particular SMR entry index from 0-31. HSE verifies each SMR entry specified by this bitfield.
                                                        @note
                                                            - If #preBootSmrMap == 0 (no PRE-BOOT SMR is specified), the SMR(s) specified by #postBootSmrMap will be loaded before the core is un-gated from #pPassReset address.
                                                              In this case, only the verification is done after the core is released from reset (POST-BOOT). This is referenced as "parallel secure boot".
                                                              It can be used only if the POST-BOOT SMRs are in memory mapped locations (e.g. QuadSPI Flash, and not in SD/eMMC).*/
    hseCrStartOption_t  startOption;        /**< @brief Specifies if the Application Core is automaticaly released from reset or not. */
    uint8_t             reserved1[6U];
} hseCrEntry_t;

/*-------------------------------SERVICES DEFINITION----------------------------------------------*/

/** @brief HSE Secure Memory Region Installation service (update or add new entry).
*  @details  This service installs a SMR entry which needs to be verify during boot or runtime phase.
*            The installation can be done in one-pass or streaming mode.
*            The streaming mode is useful when the SMR content to be install is not entirely available in the system memory when the installation starts (OTA use case).
*            The table below summarizes the fields needed to be provided for each access mode.
*            Unused fields are ignored by the HSE.
*            SMR(s) can be installed only in sequence, one at a time. This service does not use a stream ID as HSE uses internal contexts when processing in streaming mode.
*
* |Field \ Mode      | One-pass  | Start | Update  | Finish  |
* |-----------------:|:---------:|:-----:|:-------:|:-------:|
* | accessMode       |     *     |   *   |    *    |    *    |
* | entryIndex       |     *     |   *   |         |         |
* | pSmrEntry        |     *     |   *   |         |         |
* | pSmrData         |     *     |   *   |    *    |    *    |
* | smrDataLength    |     *     |   *   |    *    |    *    |
* | pAuthTag         |     *     |       |         |    *    |
* | authTagLength    |     *     |       |         |    *    |
* | cipher.pIV       |     *     |   *   |         |         |
* | cipher.pGmacTag  |     *     |       |         |    *    |
*
* @note
*    - The provisioning of the original authentication tag shall be optional when LC == CUST_DEL.
*      This allows to implement SHE use-case: autonomous bootstrap.
*    - In User mode, the SMR can be updated only changing the hseSmrEntry_t#pSmrSrc, hseSmrEntry_t#smrSize and hseSmrEntry_t#pInstAuthTag.
*      Any other configuration fields (such as keyHandle, configFlags, verifMethod, etc.) of a SMR entry can only be updated if the host has SuperUser rights (for NVM Configuration).
*    - POST_BOOT and periodic SMR(s) source addresses cannot be in SD/MMC or external flash memory.
*    - The keys linked with a SMR entry (through smrFlags in hseKeyInfo_t) will become unavailable after successful installation of the SMR entry.
*      The SMR must be verified (automatically at boot-time, periodically or via verify request at run-time) before the key can be used again.
*    - If a periodic SMR is updated during runtime using this service, the periodic checks for this SMR entry are disabled till the next reset.
*
* @note (SHE boot): <br>
*    The SMR #0 is the only SMR that can be associated to the SHE AES key BOOT_MAC_KEY as the
*    SMR authentication key. In this case, the reference authentication tag is the CMAC value referred to as BOOT_MAC.
*    The BOOT_MAC value can be initialized and updated via the SHE key update protocol. <br>
*    In addition, when LC is set to CUST_DEL, BOOT_MAC can be automatically calculated as described below:
*        - On the first SMR #0 installation using BOOT_MAC_KEY, if BOOT_MAC is empty (i.e. not initialized) and if
*          BOOT_MAC_KEY has been provisioned, the reference authentication tag is calculated by the HSE and saved
*          in the BOOT_MAC slot. This specific installation process satisfies the SHE requirement referred to as
*          "autonomous bootstrap configuration".
*        - When installing SMR #0 using the BOOT_MAC_KEY while the BOOT_MAC is already initialized, the
*          BOOT_MAC value must be updated via the SHE key update protocol prior to issuing the SMR installation service.
*        - In all cases, the arrays #pAuthTag and #authTagLength are always discarded and should be set
*          respectively to NULL and 0.
*        - If SMR #0 installation using the keyHandle for SHE(BOOT_MAC_KEY), #HSE_SMR_CFG_FLAG_INSTALL_AUTH = 0 is not allowed.
*
* @note NXP RFE SMR entries: <br>
*    On platforms having #HSE_SPT_NXP_RFE_SW feature enabled HSE FW provides the functionality of installing NXP owned SMR entries on application cores.
*    These are images encrypted and authenticated by NXP and have dedicated handling on installation.
*    To install such an image one must:
*        - Declare the ownership of the SW targeted for the application core to NXP - by setting the OTP attribute #HSE_RFE_CORE_SW_MODE_ATTR_ID.
*        - Program the image(s) to the external flash to a chosen location, e.g. ExternalFlashAddr.
*        - Provide the encryption and authentication key handles of the ROM keys targeted for this use case (#HSE_ROM_KEY_AES256_KEY2 and #HSE_ROM_KEY_RSA2048_PUB_KEY1).
*        - Provide the installation address of the image (can be the same of that from the external flash - ExternalFlashAddr - as long as it is in QSPI/LPDDR4 or a different chosen location - InstallationAddr).
*        - Provide a chosen index for the installed SMR - Ind.
*   Example of NXP SMR installation:
*   \code
*   smrEntry.pSmrSrc                            = ExternalFlashAddr;
*   smrEntry.authKeyHandle                      = HSE_ROM_KEY_RSA2048_PUB_KEY1;
*   smrEntry.smrDecrypt.decryptKeyHandle        = HSE_ROM_KEY_AES256_KEY2;
*
*   hseDescriptor.srvId                         = HSE_SRV_ID_SMR_ENTRY_INSTALL;
*   hseDescriptor.smrEntryInstallReq.accessMode = HSE_ACCESS_MODE_ONE_PASS;
*   hseDescriptor.smrEntryInstallReq.entryIndex = Ind;
*   hseDescriptor.smrEntryInstallReq.pSmrEntry  = HSE_PTR_TO_HOST_ADDR(&smrEntry);
*   hseDescriptor.smrEntryInstallReq.pSmrData   = InstallationAddr;
*
*   SendDescToHse(&hseDescriptor);
*   \endcode
*   Constraints and additional notes:
*        - #HSE_RFE_CORE_SW_MODE_ATTR_ID attribute must be set to NXP before being allowed to install NXP SMR entries.
*        - Only #HSE_ACCESS_MODE_ONE_PASS access mode can be used.
*        - All parameters not specified in the above example are ignored.
*/
typedef struct
{
    /** @brief INPUT: Specifies the access mode: ONE-PASS, START, UPDATE, FINISH.
     *         @note
     *         - Streaming is not supported for Pure EDDSA scheme (eddsa.bHashEddsa != TRUE).
     *         STREAMING USAGE: Used in all steps.*/
    hseAccessMode_t     accessMode;

    /** @brief INPUT: Identifies the index of SMR entry (in the SMR table) which has to be installed/updated.
     *         Refer to #HSE_NUM_OF_SMR_ENTRIES
     *         STREAMING USAGE: Used in START.*/
    uint8_t             entryIndex;
    uint8_t             reserved[2U];

    /** @brief INPUT: Address of SMR entry structure containing the configuration properties to be installed (refer to hseSmrEntry_t). */
    HOST_ADDR           pSmrEntry;

    /** @brief INPUT: The address where SMR data to be installed is located.
     *         STREAMING USAGE: Used in all steps, but ignored if smrDataLength is zero.
     *         @note
     *         - If SMR#0 is used for SHE-boot and the BOOT_MAC slot is empty then the BOOT_MAC is be calculated by HSE FW at the time of SMR installation.
     *         - For HSE_H/M devices, if the SMR is flashed in SD/eMMC, the application need to copy SMR data in System RAM (and pSmrData must point to that System RAM address) */
    HOST_ADDR           pSmrData;

    /** @brief INPUT: The length of the SMR data. In case of streaming mode, the total size of SMR is computed by summing the length of SMR chunks provided during Update/Finish
     *         STREAMING USAGE: Used in all steps.
     *          - START: Must be a multiple of 64/128 bytes, or zero. Cannot be zero for HMAC.
     *          - UPDATE: Must be a multiple of 64/128 bytes. Cannot be zero.
     *                    Refrain from issuing the service request, instead of passing zero.
     *          - FINISH: Can be any value (For CMAC & XCBC-MAC, zero length is invalid).
     *
     *          @note
     *          - Depending on the algorithm used, the length must be:
     *              - Multiple of 64 bytes:
     *                  - CMAC, GMAC, XCBC-MAC;
     *                  - HMAC, RSA, ECDSA with underlying hash: SHA1, SHA2_224, SHA2_256;
     *              - Multiple of 128 bytes:
     *                  - HMAC, RSA, ECDSA with underlying hash: SHA2_384, SHA2_512, SHA2_512_224, SHA2_512_256;
     *          - Miyaguchi-Preneel not supported as hash algorithm;
     *          - HMAC: SHA3 not supported as hash algorithm.
     *          - Pure EDDSA scheme (eddsa.bHashEddsa != TRUE): not supported in streaming mode. */
    uint32_t            smrDataLength;

    /** @brief INPUT: The address where SMR Original authentication tag to be verify is located.
     *                @note
     *                   - The SMR authentication proof is always computed over the plain SMR.
     *                   - For MAC and RSA signature, only pAuthTag[0] is used.
     *                   - Both pointers are used for ECDSA and EDDSA signatures (specified as (r,s), with r at index 0, and s at index 1).
     *                   - ignored if SMR#0 is SHE-boot.
     *           STREAMING USAGE: Used in FINISH. */
    HOST_ADDR           pAuthTag[2];

    /** @brief INPUT: The length of the SMR authentication proof (tag/signature).
     *                @note
     *                   - For MAC and RSA signature, only authTagLength[0] is used.
     *                   - Both pointers are used for ECDSA and EDDSA signatures (specified the length of (r,s), with r at index 0, and s at index 1).
     *                   - Ignored if SMR#0 is used for SHE-boot.
     *                   - The MAC tag size must be minimum 16 bytes.
     *                   - RSA signature size must be #HSE_BYTES_TO_BITS(keyBitLength);
     *                   - R or S size for ECDSA/EDDSA signature must be #HSE_BYTES_TO_BITS(keyBitLength)
     *           STREAMING USAGE: Used in FINISH. */
    uint16_t            authTagLength[2];

    #if defined(HSE_SPT_SMR_DECRYPT)
    /** @brief INPUT: Optional - Cipher parameters used for installing encrypted SMR(s).
     *                @note
     *                  - These parameters are use only if hseSmrDecrypt_t#decryptKeyHandle != #HSE_SMR_DECRYPT_KEY_HANDLE_NOT_USED (see hseSmrDecrypt_t).
     *                  - The pointers that are specified in this structure shall be provided from a memory-mapped location (QSPI/LPDDR4/RAM).
     *                  - In case an SMR lying in SD/eMMC external flash is installed, a copy of GMAC tag (if used) shall be done in RAM and provided via the fields below. <br>
     *                    The pointers provided via hseSmrEntryInstallSrv_t#pSmrEntry shall point to the location in external flash that will be used by HSE at boot-time.
     */
    struct
    {
        /** @brief INPUT: Initialization Vector/Nonce. The length of the IV is 16 bytes. Will be stored by HSE internally.
         *         STREAMING USAGE: Used in START.*/
        HOST_ADDR               pIV;
        /** @brief INPUT: Optional - tag used for AEAD. The length considered for the GMAC tag is 16 bytes (if used - see hseSmrDecrypt_t).
         *                @note
         *                  - Used only if hseSmrDecrypt_t#pGmacTag != NULL.
         *                  - Must point to the same data as hseSmrDecrypt_t#pGmacTag, however the memory location may differ (QSPI/LPDDR4/RAM vs QSPI/LPDDR4/SD/eMMC).
         *         STREAMING USAGE: Used in FINISH.*/
        HOST_ADDR               pGmacTag;
        /** @brief INPUT: Optional - the AAD used for AEAD. The length considered for the AAD is specified via pSmrEntry->smrDecrypt.aadLength (see #hseSmrDecrypt_t).
         *                @note
         *                  - Used only if length is not zero.
         *                  - Must point to the same data as pSmrEntry->smrDecrypt.pAAD, however the memory location may differ (QSPI/LPDDR4/RAM vs QSPI/LPDDR4/SD/eMMC).
         *         STREAMING USAGE: Used in START.*/
        HOST_ADDR               pAAD;
    } cipher;
    #endif /* defined(HSE_SPT_SMR_DECRYPT) */
} hseSmrEntryInstallSrv_t;

/** @brief HSE Secure Memory Region verification service.
 *  @details This service starts the on-demand verification of a secure memory region by specifying the index in the SMR table.
 */
typedef struct
{
    /** @brief INPUT: Specifies the entry in the SMR table to be verified (max #HSE_NUM_OF_SMR_ENTRIES).
     *                This service loads and verifies on-demand an SMR entry (in SRAM).
     *                   @note (HSE_H/M)
     *                     - The SMR(s) used in CORE RESET table can be verified on-demand only if they were loaded before in SRAM or the BOOT_SEQ = 0.
     *                       Otherwise, an error will be reported (NOT ALLOWED).
     *                     - The SMR(s) that are not part of the CORE RESET table configuration can be loaded and verified at run time.
     *                       Note that on the second call of this service, the HSE will only performed the verification in SRAM.
     *                       Using this service, the SMR(s) can not be loaded and verified from SD/MMC memory. */
    uint8_t entryIndex;

    /** @brief RFU. Set to 0 for compatibility with future updates. */
    uint8_t reserved;

    /** @brief INPUT: Options for customizing the on-demand SMR verification (see #hseSmrVerificationOptions_t). Values not defined or not applicable are ignored. */
    hseSmrVerificationOptions_t options;
} hseSmrVerifySrv_t;

/** @brief   SMR entry erase service.
 *  @details This service erases one SMR entry from the internal HSE memory.
 *  @note
 *          - SuperUser (SU) access rights with privileges over HSE_SYS_AUTH_NVM_CONFIG data are required to perform this service.
 */
typedef struct
{
    /** @brief INPUT: Identifies the index in the SMR table for the entry to be erased. */
    uint8_t              smrEntryInd;
    uint8_t              reserved[3];
} hseSmrEntryEraseSrv_t;

/** @brief   Core Reset entry install (update or add new entry)
 *  @details This service updates an existing or add a new entry in the Core Reset table.
 *  @note
 *          - SMR entries that are linked with the installed CR entry (via preBoot/altPreBoot/postBoot SMR maps) must be installed in HSE prior to the CR installation.
 *          - SuperUser rights (for NVM Configuration) are needed to perform this service.
 *          - Updating an existing CR entry is conditioned by having all preBoot and postBoot SMR(s) linked with the previous entry verified successfully (applicable only in OEM_PROD/IN_FIELD LCs).
 *
 *  @note NXP RFE CR entry: <br>
 *      On platforms having #HSE_SPT_NXP_RFE_SW feature enabled HSE FW provides the functionality of installing NXP owned CR entry for application cores (e.g. RFE - CORE1 on SAF85XX platform).
 *      This CR entry are linked with the NXP SMR entries and have a dedicated handling on installation.
 *      To install such an entry one must:
 *          - Install the corresponding NXP SMR images.
 *          - Link the NXP SMR entries to the CR entry to be installed.
 *          - Provide a chosen index for the installed CR - CrInd.
 *   Example of RFE CR installation when owned by NXP:
 *   \code
 *   crEntry.coreId                                 = HSE_APP_CORE1;
 *   crEntry.preBootSmrMap                          = ((1UL << ITCM_PRIMARY_IND) | (1UL << DTCM_PRIMARY_IND));
 *   crEntry.altPreBootSmrMap                       = ((1UL << ITCM_BACKUP_IND)  | (1UL << DTCM_BACKUP_IND));
 *
 *   hseDescriptor.srvId                            = HSE_SRV_ID_CORE_RESET_ENTRY_INSTALL;
 *   hseDescriptor.crEntryInstallReq.crEntryIndex   = CrInd;
 *   hseDescriptor.crEntryInstallReq.pCrEntry       = HSE_PTR_TO_HOST_ADDR(&crEntry);
 *
 *   SendDescToHse(&hseDescriptor);
 *   \endcode
 *   Constraints and additional notes:
 *          - The referenced NXP SMR must be installed prior to CR entry installation.
 *          - Only NXP SMR are allowed to be linked with the RFE core when #HSE_RFE_CORE_SW_MODE_ATTR_ID is set to NXP.
 *          - All parameters not specified in the above example are ignored.
 */
typedef struct
{
    /** @brief INPUT: Identifies the index in the Core Reset table which has to be added/updated
               Refer to #HSE_NUM_OF_CORE_RESET_ENTRIES. */
    uint8_t              crEntryIndex;
    uint8_t              reserved[3];
    /** @brief INPUT: Address of Core Reset entry structure (refer to #hseCrEntry_t). */
    HOST_ADDR            pCrEntry;
} hseCrEntryInstallSrv_t;

/** @brief   On-demand boot of a Core Reset entry.
 *  @details This service triggers the loading, verification and reset release of a core that is not automatically started (at boot time).
 *  @note
 *          - This service can be called only once and only for the Core Reset entries that have the startOption option set to #HSE_CR_ON_DEMAND.
 *          - Using this service, the SMR(s) can not be loaded and verified from SD/MMC memory.
 */
typedef struct
{
    /** @brief INPUT: Identifies the index in the Core Reset table which has to be released from reset after loading and verification.
               Refer to #HSE_NUM_OF_CORE_RESET_ENTRIES. */
    uint8_t              crEntryIndex;
    uint8_t              reserved[3];
} hseCrOnDemandBootSrv_t;

/** @brief   Core Reset entry erase service.
 *  @details This service erases one Core Reset entry from the internal HSE memory.
 *  @note
 *          - SuperUser (SU) access rights with privileges over HSE_SYS_AUTH_NVM_CONFIG data are required to perform this service.
 */
typedef struct
{
    /** @brief INPUT: Identifies the index in the Core Reset table for the entry to be erased. */
    uint8_t              crEntryInd;
    uint8_t              reserved[3];
} hseCrEntryEraseSrv_t;

/** @} */
#endif

#ifdef HSE_SPT_FLASHLESS_DEV /* HSE_H/M device */
/*==================================================================================================
*                                      DEFINES AND MACROS
==================================================================================================*/
/** @brief  Publish SYS-IMAGE options. */
typedef uint8_t hsePublishOptions_t;
#define HSE_PUBLISH_RESERVED                 ((hsePublishOptions_t)1U << 0U)  /**< @brief Unsupported publish method */
#define HSE_PUBLISH_ALL_DATA_SETS            ((hsePublishOptions_t)1U << 1U)  /**< @brief Publish all data sets. */

/*==================================================================================================
*                                             ENUMS
==================================================================================================*/

/*==================================================================================================
                                 STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/

/** @brief   HSE Publish SYS-IMAGE (only for HSE_H/M devices).
 *  @details Publish the SYS-IMAGE to be stored on an external RAM memory (controlled by application).
 *           The host application uses this service to request the SYS-IMAGE.
 *           The SYS-IMAGE is built from three Data Sets:
 *           - a Main Header (one flash page is allocated)
 *           - SMR/CR/OTFAD/NVM/IEE_DDR(if supported) attributes Data set; max size is max(8KB, flashPageSize).
 *           - NVM Key Store Data Set; max size is 32KB. <br>
 *           The last two data sets are protected against reply attacks using a version counter stored in fuses.
 *           The SYS-IMAGE size depends on the flash page size configured in the IVT (if set zero in IVT, HSE used 4KB as the default flash page size);
 *           it can be calculated as "flashPageSize + max(8KB, flashPageSize) + 32KB" (e.g for 4KB flash sector size, the SYS-IMAGE size is 44KB).
 *           The application can request to publish only all data sets at the same time. <br>
 *
 *      @note
 *           - The rollback protection for SYS-IMG can be disabled using #HSE_OTP_ROLLBACK_PROTECTION_POLICY_ATTR_ID attribute
 *           - If the OTP rollback protection is not disabled (refer to #HSE_OTP_ROLLBACK_PROTECTION_POLICY_ATTR_ID attribute),
 *             to be able to update fuse counter, the VDD_EFUSE supply must be powered before fuses
 *             are written (refer to HSE FW Reference Manual).
 *           - If the OTP rollback protection is not disabled
 *              - if the host requests to publish the Data Sets, and none of the Data Sets wasn't updated,
 *                the anti-rollback counter will not be updated in fuses. If one of the Data Sets is updated,
 *                the counter is incremented (fuse counter+1) in image header. The counter will be updated also in fuses
 *                (when sys-image is loaded during start-up).
 *              - During a power cycle, the value of the anti-rollback counter is incremented with a maximum value of 1.
 *                (multiple update-publish requests in one power cycle will not burn more than one fuse).
 *                The VDD_EFUSE state is checked before the fuse write by reading the NCSPD_STAT register of the on-chip PMC module.
 *                The application shall provide read-only access (xRDC restriction) to HSE to read the NCSPD_STAT register.
 *           - For S32ZE, the SYS-IMG size is 48KB.
 *           - Depending on the size of the DataSet, not the entire flash page(s) is used. An empty space is reserved at the end of
 *             the DataSet (end of the last flash page of the DataSet) for further extention of the DataSet. These reserved empty
 *             spaces are not authenticated during SYS-IMG loading (e.g only relevant data is authenticated and encrypted).
 */
typedef struct
{
    /** @brief   INPUT: Publish SYS-IMAGE options:
                - #HSE_PUBLISH_RESERVED - unsupported publish method.
                - #HSE_PUBLISH_ALL_DATA_SETS - publish all Data Sets.*/
    hsePublishOptions_t    publishOptions;
    uint8_t                reserved[3];
    /** @brief   OUTPUT: The address where to store the Data Set offset (a uint32_t value). <br>
     *                   This offset specifies where the provided output buffer needs to be stored in the external flash SYS-IMAGE
     *                   (e.g. the buffer of size #pBuffLength shall be copied in the external flash starting from address specified
     *                   by "SYS_IMAGE_BASE_ADDR + PublishOffset").
     *                   Since the only supported publish method is for all data sets at the same time, the offset is always set to zero. */
    HOST_ADDR              pPublishOffset;
    /** @brief   INPUT/OUTPUT: As input, it specifies the length (a uint32_t value) of the output buffer provided by the application. <br>
     *                         This needs to be at least greater or equal to the size returned by get the SYS_IMG size request (see hseGetSysImageSizeSrv_t).
     *                         The uint32_t value pointed by #pBuffLength will be overwritten by HSE with the number of bytes that were written into the pBuff buffer. */
    HOST_ADDR              pBuffLength;
    /** @brief   OUTPUT: The address of the output buffer. */
    HOST_ADDR              pBuff;
} hsePublishSysImageSrv_t;

/** @brief   HSE Get SYS_IMAGE size (only for HSE_H/M devices).
 *  @details Return the total length of SYS_IMAGE in bytes.
 */
typedef struct
{
    /** @brief   OUTPUT: The address where to store the size of the SYS_IMAGE (a uint32_t value). */
    HOST_ADDR              pSysImageSize;
} hseGetSysImageSizeSrv_t;

/** @brief   HSE Verify SYS_IMAGE (only for HSE_H/M devices).
 *  @details This service can be used to verify the SYS_IMAGE integrity after it is written in external flash.
 */
typedef struct
{
    /** @brief   INPUT: The address where SYS_IMAGE is stored. Must point to the start of the entire SYS_IMAGE. Cannot be in SD/eMMC external flash. */
    HOST_ADDR              pSysImageAddr;
} hseVerifySysImageSrv_t;

/** @} */
#endif

#ifdef HSE_SPT_OTFAD
/*==================================================================================================
*                                      DEFINES AND MACROS
==================================================================================================*/
/** @brief   OTFAD instance type. */
typedef uint8_t hseOtfadInstance_t;
#define HSE_OTFAD_INSTANCE_0     (0U)   /**< @brief OTFAD Instance 0. */

#if HSE_NUM_OF_OTFAD_INSTANCES > (1U)
#define HSE_OTFAD_INSTANCE_1     (1U)   /**< @brief OTFAD Instance 1. */
#endif

#ifdef HSE_SPT_IEE_DDR_FLASH
#define HSE_IEE_DDR_INSTANCE_2   (2U)   /**< @brief The instance used for IEE_DDR for flash decrypt */
#endif /* HSE_SPT_IEE_DDR_FLASH */

/*==================================================================================================
*                                             ENUMS
==================================================================================================*/

/*==================================================================================================
                                 STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/
/** @brief   OTFAD/IEE_DDR context activation flag. */
typedef uint16_t hseOtfadActivateFlag_t;
#define HSE_OTFAD_CTX_ACTIVE_ON_BOOT      ((hseOtfadActivateFlag_t)0xAB65U)    /**< @brief Activate context on boot. */
#define HSE_OTFAD_CTX_INACTIVE_ON_BOOT    ((hseOtfadActivateFlag_t)0x375AU)    /**< @brief Inactive context on boot. */

/** @brief Define the parameters of OTFAD/IEE_DDR context entry
 *
 * @note
 *  - The OTFAD/IEE_DDR configuration is part of SYS-IMG. Once configured, the host must publish and save the SYS_IMG to Flash.
 *  - The OTFAD/IEE_DDR cannot be used for IVT, DCD/ST-DCD, FW_IMG/FW_IMG* and SYS-IMG images: these images must be
 *    stored unencrypted in external Flash.
*/
typedef struct
{
    hseKeyHandle_t           keyHandle;            /**< @brief  The key handle of the OTFAD key (AES 128bit), the OTFAD key handle must always and only have #HSE_KF_USAGE_OTFAD_DECRYPT flag set. */
    uint8_t                  iv[4];                /**< @brief  - OTFAD Instance[0, 1]: Byte array defining the user's part of the initial vector (counter) used by the AES-CTR mode algorithm.
                                                                                        To avoid possible attack scenarios, diversification of the IV for each updated version of
                                                                                        application code is highly recommended. <br>
                                                                - IEE_DDR Instance[2]: Fixed upper 32-bits of the Counter value when using PRINCE-CTR mode. Counter mode uses a 64-bit counter value.
                                                                                       It is composed of two halves, an upper fixed value stored as a 32-bit integer,
                                                                                       and a lower half formed from the ((address - startAddress) >> 3) (e.g offset in the defined memory region)
                                                                                       at which Ciphertext data is stored in memory. This counter value increments for each 8-byte block of encrypted data.
                                                                                       @note The lower half of the counter always starts at 0 for a block of encrypted data that starts from startAddress. */
    uint32_t                 startAddress;         /**< @brief  - OTFAD Instance[0, 1]: The start address of the memory region. Must be aligned on a 1KB boundary. <br>
                                                                - IEE_DDR Instance[2]: The start address of the memory region. Must be aligned on a 1MB boundary. */
    uint32_t                 endAddress;           /**< @brief  - OTFAD Instance[0, 1]: The end address of the memory region. Must be aligned on a 1KB boundary. <br>
                                                                - IEE_DDR Instance[2]: The end address of the memory region. Must be aligned on a 1MB boundary.  */
    hseSmrFlags_t            smrFlags;             /**< @brief   - When BOOT_SEQ == 1 (Secure boot), it specifies the SMR entries (bit field) that should be verified before the activation of the OTFAD/IEE_DDR entry.
                                                                 - When BOOT_SEQ == 0 (Un-secure boot), if there is any SMR linked with OTFAD/IEE_DDR entry,
                                                                   the application should trigger the verification at run-time (activate the OTFAD/IEE_DDR context using the service structure hseActivateOtfadContextSrv_t);
                                                                   in this case, the SMR must NOT be in the QSPI flash region configured using OTFAD/IEE_DDR.*/
    hseOtfadActivateFlag_t   activateOnBoot;       /**< @brief  If #activateOnBoot == #HSE_OTFAD_CTX_ACTIVE_ON_BOOT, the configured OTFAD/IEE_DDR context will automatically activate while booting.
                                                                otherwise, the hseOtfadActivateContextSrv_t service must be called to activate the OTFAD/IEE_DDR context. */
    uint8_t                  reserved[2];
} hseOtfadContext_t;

/*-------------------------------SERVICES DEFINITION----------------------------------------------*/

/** @brief HSE OTFAD/IEE_DDR Install Context service (update or add new entry).
 *  @details This service installs an existing OTFAD/IEE_DDR context or add a new one.
 *  @note SuperUser rights (for NVM Configuration) are needed to perform this service.
 */
typedef struct
{
    /** @brief INPUT: Identifies the index of OTFAD configuration table which has to be installed/updated.
                      I can be defined up to #HSE_NUM_OF_OTFAD_ENTRIES contexts (per OTFAD instance) and up to #HSE_NUM_OF_IEE_DDR_ENTRIES for IEE_DDR instance (if supported) */
    uint8_t              otfadIdx ;
    /** @brief INPUT: Identifies the OTFAD or IEE_DDR instance (refer to #hseOtfadInstance_t). it shall be between 0 and #HSE_NUM_OF_OTFAD_INSTANCES.
     *                @note
     *                - S32ZE devices have more than one OTFAD instances.
     *                - If IEE_DDR for flash decrypt is supported (see #HSE_SPT_IEE_DDR_FLASH), the last instance (see #HSE_IEE_DDR_INSTANCE_2)
     *                  is used to configure the IEE DDR. This instance contains #HSE_NUM_OF_IEE_DDR_ENTRIES contexts.*/
    hseOtfadInstance_t   otfadInstance;
    uint8_t              reserved[2];
    /** @brief INPUT: Address to hseOtfadContext_t that contains the configuration properties of OTFAD/IEE_DDR context */
    HOST_ADDR            pOtfadCtxEntry;
} hseInstallOtfadContextSrv_t;

/** @brief HSE Activate Otfad Context service
 *  @details This service is used to configure the hardware using an already installed OTFAD/IEE_DDR entry.
 *           The SMR flag used in the OTFAD/IEE_DDR entry must be verified before calling this service.
 *           @note
 *           - For S32ZE, IEE regions can be activated only once, per run-time session after installation.
 *             If an IEE region is updated during run-time, the activation of the updated IEE entry will be possible,
 *             only after the next reset.
 */
typedef struct
{
    /** @brief INPUT: Identifies the entry in the OTFAD/IEE_DDR configuration table.
     *                @note
     *                - The OTFAD instance contains #HSE_NUM_OF_OTFAD_ENTRIES (otfadIdx < HSE_NUM_OF_OTFAD_ENTRIES)
     *                - The IEE_DDR instance contains #HSE_NUM_OF_IEE_DDR_ENTRIES (otfadIdx < HSE_NUM_OF_IEE_DDR_ENTRIES)
     */
    uint8_t             otfadIdx;
    /** @brief INPUT: Identifies the OTFAD or IEE_DDR instance (refer to #hseOtfadInstance_t). it shall be between 0 and #HSE_NUM_OF_OTFAD_INSTANCES.
     *                @note
     *                - S32ZE devices have more than one OTFAD instances.
     *                - if IEE_DDR for flash decrypt is supported (see #HSE_SPT_IEE_DDR_FLASH), the last instance (see #HSE_IEE_DDR_INSTANCE_2)
     *                  is used to configure the IEE_DDR. .*/
    hseOtfadInstance_t   otfadInstance;
    uint8_t              reserved[2];
} hseActivateOtfadContextSrv_t;

 /** @brief HSE Get OTFAD/IEE_DDR Context Info service
 *   @details This service is used to extract the context parameters previously set in the OTFAD/IEE_DDR table.
 */
typedef struct
{
    /** @brief INPUT: Identifies the entry in the OTFAD/IEE_DDR configuration table whose parameters need to be extracted.
     *                @note
     *                - The OTFAD instance contains #HSE_NUM_OF_OTFAD_ENTRIES (otfadIdx < HSE_NUM_OF_OTFAD_ENTRIES)
     *                - The IEE_DDR instance contains #HSE_NUM_OF_IEE_DDR_ENTRIES (otfadIdx < HSE_NUM_OF_IEE_DDR_ENTRIES)
     */
    uint8_t             otfadIdx;
    /** @brief INPUT: Identifies the OTFAD or IEE_DDR instance (refer to #hseOtfadInstance_t). it shall be between 0 and #HSE_NUM_OF_OTFAD_INSTANCES.
     *                @note
     *                - S32ZE devices have more than one OTFAD instances.
     *                - if IEE DDR for flash decrypt is supported (see #HSE_SPT_IEE_DDR_FLASH), the last instance (see #HSE_IEE_DDR_INSTANCE_2)
     *                  is used to configure the IEE DDR. */
    hseOtfadInstance_t   otfadInstance;
    uint8_t              reserved[2];
    /** @brief OUTPUT: Address where the configuration parameters of the selected OTFAD context need to be stored.
                       It's up to the user to allocate memory of sizeof(hseOtfadContext_t) in the application memory space. */
    HOST_ADDR           pOtfadContext;
} hseGetOtfadContextSrv_t;

/** @} */
#endif

#ifdef HSE_SPT_CRC32
/*==================================================================================================
*                                      DEFINES AND MACROS
==================================================================================================*/
/** @brief  HSE CRC32 supported standards algorithms .*/
typedef uint32_t hseCrc32Mode_t;
#define HSE_CRC32_MODE_IEEE_802                 ((hseCrc32Mode_t)0x00000010U)   /**< @brief CRC32_IEEE_802 standard. */
#define HSE_CRC32_MODE_IETF_3385                ((hseCrc32Mode_t)0x00000020U)   /**< @brief CRC32_IETF_3385 standard. */

/** @brief  HSE CRC32 additional flags for CRC32 computation .*/
#define HSE_CRC32_MODE_DONT_INPUT_SWAP          ((hseCrc32Mode_t)0x00000100U)   /**< @brief The input is not bit-swapped within each byte (the difference between with- and without- this flag is equivalent
                                                                                  *         to bitswap within each byte of the input). */
#define HSE_CRC32_MODE_DONT_OUTPUT_SWAP         ((hseCrc32Mode_t)0x00000200U)   /**< @brief The output is not bit-swapped within each byte (the difference between with- and without- this flag is equivalent
                                                                                  *         to bitswap within each byte of the output). */
#define HSE_CRC32_MODE_DONT_OUTPUT_COMP         ((hseCrc32Mode_t)0x00000400U)   /**< @brief The output is not complimented (xored with all-ones) (the difference between with- and without- this flag is equivalent
                                                                                  *         to xor of the output with all-ones).*/
#define HSE_CRC32_MODE_INITIAL_VALUE_ZERO       ((hseCrc32Mode_t)0x00000800U)   /**< @brief The initial crc value is 0 instead of all-ones. */
/*==================================================================================================
*                                             ENUMS
==================================================================================================*/

/*==================================================================================================
                                 STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/

/**
* @brief        CRC service.
* @details      CRC32 is an error-detecting code commonly used in network protocols(such as IPsec).
                Can be used as an separate service. <br>
*               This service support two standards:
*                   - #HSE_CRC32_MODE_IEEE_802; Polynomial: 0x04c11db7 (names IEEE 802.3 or CRC-32)
*                   - #HSE_CRC32_MODE_IETF_3385; Polynomial: 0x1edc6f41 (names iSCSI, CRC-32C or CRC-32/4)

*               With additional flags depending on the format of input/output/desired CRC variant:
*                   - #HSE_CRC32_MODE_DONT_INPUT_SWAP
*                   - #HSE_CRC32_MODE_DONT_OUTPUT_SWAP
*                   - #HSE_CRC32_MODE_DONT_OUTPUT_COMP
*                   - #HSE_CRC32_MODE_INITIAL_VALUE_ZERO
*/
typedef struct
{
    /** @brief     INPUT: Specify te operation mode for CRC32 computation. <br>
     *                    Supported operation:
     *                    - #HSE_CRC32_MODE_IEEE_802
     *                    - #HSE_CRC32_MODE_IETF_3385
     *                    Additional flags that can be used depending on the format of input/output/desired CRC variant. <br>
     *                    In general, the CRC variant may be simply OR-ed with the desired flags e.g.:
     *                    crcOperation = #HSE_CRC32_MODE_IEEE_802 | #HSE_CRC32_MODE_DONT_INPUT_SWAP | #HSE_CRC32_MODE_DONT_OUTPUT_SWAP; */
    uint32_t       crcOpMode;

    /** @brief     INPUT: Specify if the pInput are provided as hseScatterList_t list (the host address points to a hseScatterList_t list).
     *                    Ignored if SGT is not supported.
     *                    @note
     *                    - ONLY HSE_SGT_OPTION_INPUT can be used (the rest of the bits are ignored)
     *                    - If scatter option is selected (set), the length (e.g. inputLength) shall
     *                      specified the entire message length (sum of all hseScatterList_t lengths).
     *                    - The number for SGT entries shall be less then #HSE_MAX_NUM_OF_SGT_ENTRIES. */
    hseSGTOption_t sgtOption;
    uint8_t        reserved[3];

    /** @brief     INPUT: Length of the input data(in bytes). */
    uint32_t       inputLength;

    /** @brief     INPUT: The input data that is used to calculate CRC32. */
    HOST_ADDR      pInput;

    /** @brief     OUTPUT: The address where output CRC32 (an uint32_t value) will be stored */
    HOST_ADDR      pOutput;

} hseCrc32Srv_t;

/** @} */
#endif

#ifdef HSE_SPT_TMU_REG_CONFIG

/*==================================================================================================
*                                      DEFINES AND MACROS
==================================================================================================*/
/** @brief  HSE TMU register operations. The operations are equivalent with the below macros:
 *  \code
 *      #define REG_WRITE32(address, value)       ((*(volatile uint32 *)(address)) = (value))
 *      #define REG_BIT_SET32(address, mask)      ((*(volatile uint32 *)(address)) |= (mask))
 *      #define REG_BIT_CLEAR32(address, mask)    ((*(volatile uint32 *)(address)) &= (~(mask)))
 *      #define REG_RMW32(address, mask, value)   (REG_WRITE32((address), ((REG_READ32(address) & ((uint32_t) ~ (mask))) | ((value) & (mask)))))
 *  \endcode
 */
typedef uint16_t hseTmuRegOp_t;
#define HSE_TMU_REG_WRITE32            ((hseTmuRegOp_t)3U << 0U)   /**< @brief Register write (32 bits) */
#define HSE_TMU_REG_BIT_SET32          ((hseTmuRegOp_t)3U << 2U)   /**< @brief Bits setting (32 bits) */
#define HSE_TMU_REG_BIT_CLEAR32        ((hseTmuRegOp_t)3U << 4U)   /**< @brief Bits clearing (32 bits) */
#define HSE_TMU_REG_RMW32              ((hseTmuRegOp_t)3U << 6U)   /**< @brief Clear bits and set with new value (Read-Modify-Write 32 bits) */
/*==================================================================================================
*                                             ENUMS
==================================================================================================*/

/*==================================================================================================
                                 STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/

/**
* @brief        TMU Register Configuration service.
* @details      The TMU service performs different operations on TMU registers (see #hseTmuRegOp_t).
*               The registers from the table below can be modified.
*
*  @note
*  Temperature calculation formula:
*  - SAF85XX: -42C <---> +152C
*      - for Temp < 0,  Lower Threshold  =  Temp_DegC * 64 + 2^16
*      - for Temp > 0,  Higher Threshold =  Temp_DegC * 64 <br>
*  Lower  Threshold : -42C * 64 + 2^16    = F580h <br>
*  Higher Threshold : 152C * 64           = 2600h
*
*  - S32R41: -45C <---> +155C <br>
*  Lower  Threshold : -45C + 273Kelvin    = E4h <br>
*  Higher Threshold : 155C + 273Kelvin    = 1ACh
*
*  |Register Name     | Reg Addr   |                                    Remark                                                                                              |
*  |-----------------:|:----------:|:--------------------------------------------------------------------------------------------------------------------------------------:|
*  | TMR              | 0x4008C000 |   Allowed OP: HSE_TMU_REG_WRITE32; <br> Changeable bits: bit[25,24] (the rest of the bit are ignored)                                  |
*  | TSR              | 0x4008C004 |   NA                                                                                                                                   |
*  | TIER             | 0x4008C020 |   Allowed OP: HSE_TMU_REG_WRITE32; <br> Changeable bits: bit[31,30], [28,27], [25,24] (the rest of the bit are ignored)                |
*  | TIDR             | 0x4008C024 |   NA                                                                                                                                   |
*  | TIISCR           | 0x4008C030 |   NA                                                                                                                                   |
*  | TIASCR           | 0x4008C034 |   NA                                                                                                                                   |
*  | TMHTCR           | 0x4008C040 |   NA                                                                                                                                   |
*  | TMLTCR           | 0x4008C044 |   NA                                                                                                                                   |
*  | TMRTRCR          | 0x4008C048 |   NA                                                                                                                                   |
*  | TMFTRCR          | 0x4008C04C |   NA                                                                                                                                   |
*  | TMHTITR          | 0x4008C050 |   NA                                                                                                                                   |
*  | TMHTATR          | 0x4008C054 |   NA                                                                                                                                   |
*  | TMHTACTR         | 0x4008C058 |  Allowed OP: HSE_TMU_REG_WRITE32; <br> SAF85XX: Min: F580h(-42C), Max: 2600h(152C), bit[0,15]; <br> S32R41: Min: E4h  (-45C), Max: 1ACh (155C), bit[0,8]; <br> (the rest of the bit are ignored)   |
*  | TMLTITR          | 0x4008C060 |   NA                                                                                                                                   |
*  | TMLTATR          | 0x4008C064 |   NA                                                                                                                                   |
*  | TMLTACTR         | 0x4008C068 |  Allowed OP: HSE_TMU_REG_WRITE32; <br> SAF85XX: Min: F580h(-42C), Max: 2600h(152C), bit[0,15]; <br> S32R41: Min: E4h  (-45C), Max: 1ACh (155C), bit[0,8]; <br> (the rest of the bit are ignored)   |
*  | TMRTRCTR         | 0x4008C070 |  Allowed OP: HSE_TMU_REG_WRITE32                                                                                                       |
*  | TMFTRCTR         | 0x4008C074 |  Allowed OP: HSE_TMU_REG_WRITE32                                                                                                       |
*  | TMCFG0R          | 0x4008C400 |  Only Valid for SAF85XX; <br> Allowed OP : HSE_TMU_REG_WRITE32; <br> Changeable bits: bit[0,1] (the rest of the bit are ignored)       |
*  | TTCFGR           | 0x4008C080 |  Only Valid for HSE_S32R41X; <br> Allowed OP : HSE_TMU_REG_WRITE32; <br> Changeable bits: [0,3] (the rest of the bit are ignored)
*/
typedef struct
{
    /** @brief     INPUT: Specify the Tmu register operations (see #hseTmuRegOp_t). */
    hseTmuRegOp_t  hseTmuRegOp;
    uint8_t        reserved[2U];
    /** @brief     INPUT: The TMU register address . */
    uint32_t       regAddr;
    /** @brief     INPUT: The mask use for the operation. This parameter is ignored for #HSE_TMU_REG_WRITE32 operation.*/
    uint32_t       mask;
    /** @brief     INPUT: The value use for the operation. This parameter is ignored for #HSE_TMU_REG_BIT_SET32 and #HSE_TMU_REG_BIT_CLEAR32 operations.*/
    uint32_t       value;
} hseTmuRegConfigSrv_t;

/** @} */
#endif

/*==================================================================================================
*                                     HSE Service IDs
==================================================================================================*/

/*  HSE Service IDs of type hseSrvId_t. It's a concatenation of 4 bytes:
    "Service Version | Cancellable | Class | ID" (refer to hseSrvDescriptor_t) */
/*-------- Service class 0x00: administrative services -------------*/
    #define HSE_SRV_ID_SET_ATTR                 ((hseSrvId_t)(HSE_SRV_VER_0 | 0x00000001UL))  /**< @brief Set HSE attribute. Data structure used: #hseSetAttrSrv_t. */
    #define HSE_SRV_ID_GET_ATTR                 ((hseSrvId_t)(HSE_SRV_VER_0 | 0x00A50002UL))  /**< @brief Get HSE attribute. Data structure used: #hseGetAttrSrv_t. */

#ifdef HSE_SPT_SELF_TEST
    #define HSE_SRV_ID_SELF_TEST                ((hseSrvId_t)(HSE_SRV_VER_0 | 0x00000003UL))  /**< @brief Self-test. Data structure used: #hseSelfTestSrv_t. */
#endif /* HSE_SPT_SELF_TEST */

    #define HSE_SRV_ID_CANCEL                   ((hseSrvId_t)(HSE_SRV_VER_0 | 0x00A50004UL))  /**< @brief Cancel a one-pass or streaming service on a specific channel. Data structure used: #hseCancelSrv_t. */
    #define HSE_SRV_ID_FIRMWARE_UPDATE          ((hseSrvId_t)(HSE_SRV_VER_0 | 0x00000005UL))  /**< @brief HSE firmware update. Data structure used: #hseFirmwareUpdateSrv_t. */
    #define HSE_SRV_ID_SYS_AUTH_REQ             ((hseSrvId_t)(HSE_SRV_VER_0 | 0x00000006UL))  /**< @brief Perform a SYS Authorization request. Data structure used: #hseSysAuthorizationReqSrv_t. */
    #define HSE_SRV_ID_SYS_AUTH_RESP            ((hseSrvId_t)(HSE_SRV_VER_0 | 0x00000007UL))  /**< @brief Send the SYS Authorization response. Data structure used: #hseSysAuthorizationRespSrv_t. */
    #define HSE_SRV_ID_BOOT_DATA_IMAGE_SIGN     ((hseSrvId_t)(HSE_SRV_VER_0 | 0x00000008UL))  /**< @brief Boot Data image sign (e.g. for HSE_H/M, IVT/DCD/ST/LPDDR4(S32Z/E devices)/AppBSB image; for HSE_B, IVT/AppBSB image). Data structure used: #hseBootDataImageSignSrv_t. */
    #define HSE_SRV_ID_BOOT_DATA_IMAGE_VERIFY   ((hseSrvId_t)(HSE_SRV_VER_0 | 0x00000009UL))  /**< @brief Boot Data images verify (e.g. for HSE_H/M, IVT/DCD/ST/LPDDR4(S32Z/E devices)/AppBSB image; for HSE_B, IVT/AppBSB image). Data structure used: #hseBootDataImageVerifySrv_t. */

#ifdef HSE_SPT_STREAM_CTX_IMPORT_EXPORT
    #define HSE_SRV_ID_IMPORT_EXPORT_STREAM_CTX ((hseSrvId_t)(HSE_SRV_VER_0 | 0x00A5000AUL))  /**< @brief Import/Export Streaming Context. Data structure used: #hseImportExportStreamCtxSrv_t. */
#endif /* HSE_SPT_STREAM_CTX_IMPORT_EXPORT */

#ifdef HSE_SPT_FLASHLESS_DEV /* HSE_H/M device */
    #define HSE_SRV_ID_PUBLISH_SYS_IMAGE        ((hseSrvId_t)(HSE_SRV_VER_0 | 0x00000011UL))  /**< @brief Publish the NVM SYS-IMAGE. Data structure used: #hsePublishSysImageSrv_t. */
    #define HSE_SRV_ID_GET_SYS_IMAGE_SIZE       ((hseSrvId_t)(HSE_SRV_VER_0 | 0x00000012UL))  /**< @brief Get the SYS-IMAGE size. Data structure used: #hseGetSysImageSizeSrv_t. */
    #define HSE_SRV_ID_VERIFY_SYS_IMAGE         ((hseSrvId_t)(HSE_SRV_VER_0 | 0x00000018UL))  /**< @brief Verify SYS-IMAGE. Data structure used: #hseVerifySysImageSrv_t. */

    #ifdef HSE_SPT_MONOTONIC_COUNTERS
    #define HSE_SRV_ID_PUBLISH_LOAD_CNT_TBL     ((hseSrvId_t)(HSE_SRV_VER_0 | 0x00000013UL))  /**< @brief Request to publish/load the NVM container for the Monotonic Counter table (only for HSE_H/M). Data structure used: #hsePublishLoadCntTblSrv_t. */
    #endif /* HSE_SRV_ID_PUBLISH_LOAD_CNT_TBL*/

    #ifdef HSE_SPT_OTFAD
    #define HSE_SRV_ID_INSTALL_OTFAD_CTX        ((hseSrvId_t)(HSE_SRV_VER_0 | 0x00000014UL))  /**< @brief Install an On-The-Fly AES Decryption (OTFAD) context (only for HSE_H/M). Data structure used: #hseInstallOtfadContextSrv_t. */
    #define HSE_SRV_ID_ACTIVATE_OTFAD_CTX       ((hseSrvId_t)(HSE_SRV_VER_0 | 0x00000015UL))  /**< @brief Activate on-demand OTFAD context (only for HSE_H/M). Data structure used: #hseActivateOtfadContextSrv_t. */
    #define HSE_SRV_ID_GET_OTFAD_CTX            ((hseSrvId_t)(HSE_SRV_VER_0 | 0x00000016UL))  /**< @brief Get OTFAD context information (only for HSE_H/M). Data structure used: #hseGetOtfadContextSrv_t. */
    #endif /* HSE_SPT_OTFAD */

    #define HSE_SRV_ID_PREPARE_FOR_STANDBY      ((hseSrvId_t)(HSE_SRV_VER_0 | 0x00A50017UL))  /**< @brief Prepare HSE before system goes to Stand-By mode (only for HSE_H/M). Data structure used: #hsePrepareForStandBySrv_t. */

#ifdef HSE_SPT_TRIM_PASSWORD_PROVISION
    #define HSE_SRV_ID_TRIM_PASSWORD_PROVISION    ((hseSrvId_t)(HSE_SRV_VER_0 | 0x00000020UL))  /**< @brief Provide a trim password to allow the read for fuses that can't be read (by default) by the customer. Data structure used: #hseTrimPasswordProvision_t. */
#endif

    #ifdef HSE_SPT_MSC_KEYSTORE
    #define HSE_SRV_ID_CONFIG_KHTT              ((hseSrvId_t)(HSE_SRV_VER_0 | 0x00000019UL))  /**< @brief Configure the Key Handle Translation Table (KHTT). Data structure used: #hseConfigKHTTSrv_t. */
    #define HSE_SRV_ID_PUSH_MSC_KEYS            ((hseSrvId_t)(HSE_SRV_VER_0 | 0x00000021UL))  /**< @brief Push one or more HSE keys in ACE key store. Data structure used: #hsePushMscKeySrv_t. */
    #endif /* HSE_SPT_MSC_KEYSTORE */
#endif /* HSE_SPT_FLASHLESS_DEV */

#ifdef HSE_SPT_INTERNAL_FLASH_DEV /* HSE_B device */
    #define HSE_SRV_ID_ERASE_HSE_NVM_DATA       ((hseSrvId_t)(HSE_SRV_VER_0 | 0x00000050UL))  /**< @brief Erase HSE Data Flash (only for HSE_B). This service is only allowed in CUST_DEL LC. Data structure used: #hseEraseNvmDataSrv_t. */

    #ifdef HSE_SPT_ERASE_FW
    #define HSE_SRV_ID_ERASE_FW                 ((hseSrvId_t)(HSE_SRV_VER_0 | 0x00000057UL))  /**< @brief Erase Sys-Img, Backup FW as well Current running HSE FW from code flash. Data Structure used: #hseEraseFwSrv_t */
    #endif /* HSE_SPT_ERASE_FW */

    #define HSE_SRV_ID_ACTIVATE_PASSIVE_BLOCK   ((hseSrvId_t)(HSE_SRV_VER_0 | 0x00000051UL))  /**< @brief Application request to switch passive flash block area (only for HSE_B). No data structure used. */

    #ifdef HSE_SPT_OTA_SBAF_UPDATE
    #define HSE_SRV_ID_SBAF_UPDATE              ((hseSrvId_t)(HSE_SRV_VER_0 | 0x00000053UL))  /**< @brief SBAF firmware update request. Data structure used: #hseSbafUpdateSrv_t. */
    #endif /* HSE_SPT_OTA_SBAF_UPDATE */

    #ifdef HSE_SPT_FW_INTEGRITY_CHECK
    #define HSE_SRV_ID_FW_INTEGRITY_CHECK       ((hseSrvId_t)(HSE_SRV_VER_0 | 0x00000054UL))  /**< @brief Application request to checks the integrity of HSE FW and SYS-IMG inside HSE (only for HSE_B). No data structure used. */
    #endif /* HSE_SPT_FW_INTEGRITY_CHECK */

    #ifdef HSE_SPT_PUBLISH_NVM_KEYSTORE_RAM_TO_FLASH
    #define HSE_SRV_ID_PUBLISH_NVM_KEYSTORE_RAM_TO_FLASH       ((hseSrvId_t)(HSE_SRV_VER_0 | 0x00000055UL))  /**< @brief Application requests the firmware to write the NVM keys from RAM mirrored keystore into the data flash. This service has no parameters. */
    #endif /* HSE_SPT_PUBLISH_NVM_KEYSTORE_RAM_TO_FLASH */

#endif /* HSE_SPT_INTERNAL_FLASH_DEV */

#ifdef HSE_SPT_MONOTONIC_COUNTERS
    #define HSE_SRV_ID_CONFIG_COUNTER           ((hseSrvId_t)(HSE_SRV_VER_0 | 0x00000052UL))  /**< @brief Configure the secure counter (only for HSE_B). This service requires SuperUser rights. Data structure used: #hseConfigSecCounterSrv_t. */
#endif /* HSE_SPT_MONOTONIC_COUNTERS */


#ifdef HSE_SPT_TMU_REG_CONFIG
    #define HSE_SRV_ID_TMU_REG_CONFIG           ((hseSrvId_t)(HSE_SRV_VER_0 | 0x00000056UL))  /**< @brief TMU register configuration. Data structure used: #hseTmuRegConfigSrv_t */
#endif /* HSE_SPT_TMU_REG_CONFIG */

/*-------- Service class 0x01: key management services -------------*/
#ifdef HSE_SPT_ECC_USER_CURVES
    #define HSE_SRV_ID_LOAD_ECC_CURVE           ((hseSrvId_t)(HSE_SRV_VER_0 | 0x00000100UL))  /**< @brief Load the parameters for a Weierstrass ECC curve. Data structure used: #hseLoadEccCurveSrv_t. */
#endif /* HSE_SPT_ECC_USER_CURVES*/

#ifdef HSE_SPT_FORMAT_KEY_CATALOGS
    #define HSE_SRV_ID_FORMAT_KEY_CATALOGS      ((hseSrvId_t)(HSE_SRV_VER_0 | 0x00000101UL))  /**< @brief Format key catalogs (NVM or RAM). Data structure used: #hseFormatKeyCatalogsSrv_t. */
#endif /* HSE_SPT_FORMAT_KEY_CATALOGS*/

    #define HSE_SRV_ID_ERASE_KEY                ((hseSrvId_t)(HSE_SRV_VER_0 | 0x00000102UL))  /**< @brief Erase NVM/RAM key(s). Data structure used: #hseEraseKeySrv_t. */

#ifdef HSE_SPT_GET_KEY_INFO
    #define HSE_SRV_ID_GET_KEY_INFO             ((hseSrvId_t)(HSE_SRV_VER_0 | 0x00A50103UL))  /**< @brief Get key information header. Data structure used: #hseGetKeyInfoSrv_t. */
#endif /* HSE_SPT_GET_KEY_INFO */

#ifdef HSE_SPT_IMPORT_KEY
    #define HSE_SRV_ID_IMPORT_KEY               ((hseSrvId_t)(HSE_SRV_VER_0 | 0x00000104UL))  /**< @brief Import a key. Data structure used: #hseImportKeySrv_t. */
#endif /* HSE_SPT_IMPORT_KEY */

#ifdef HSE_SPT_EXPORT_KEY
    #define HSE_SRV_ID_EXPORT_KEY               ((hseSrvId_t)(HSE_SRV_VER_0 | 0x00000105UL))  /**< @brief Export a key. Data structure used: #hseExportKeySrv_t. */
#endif /* HSE_SPT_EXPORT_KEY */

#ifdef HSE_SPT_KEY_GEN
    #define HSE_SRV_ID_KEY_GENERATE             ((hseSrvId_t)(HSE_SRV_VER_0 | 0x00000106UL))  /**< @brief Key Generation (e.g. rsa key pair, ecc key pair etc.). Data structure used: #hseKeyGenerateSrv_t. */
#endif /* HSE_SPT_KEY_GEN */

#ifdef HSE_SPT_COMPUTE_DH
    #define HSE_SRV_ID_DH_COMPUTE_SHARED_SECRET ((hseSrvId_t)(HSE_SRV_VER_0 | 0x00000107UL))  /**< @brief ECC Diffie-Hellman Compute Key (shared secret). Data structure used: #hseDHComputeSharedSecretSrv_t. */
#endif /* HSE_SPT_COMPUTE_DH */

#ifdef HSE_SPT_KEY_DERIVE
    #define HSE_SRV_ID_KEY_DERIVE               ((hseSrvId_t)(HSE_SRV_VER_0 | 0x00000108UL))  /**< @brief Perform a key derivation function. Data structure used: #hseKeyDeriveSrv_t. */
    #define HSE_SRV_ID_KEY_DERIVE_COPY          ((hseSrvId_t)(HSE_SRV_VER_0 | 0x00000109UL))  /**< @brief Copy a key from the derived key material. Data structure used: #hseKeyDeriveCopyKeySrv_t. */
#endif /* HSE_SPT_KEY_DERIVE */

#ifdef HSE_SPT_BURMESTER_DESMEDT
    #define HSE_SRV_ID_BURMESTER_DESMEDT        ((hseSrvId_t)(HSE_SRV_VER_0 | 0x0000010AUL))  /**< @brief ECC Burmester-Desmedt Protocol calculation. Data structure used: #hseBurmesterDesmedtSrv_t. */
#endif /* HSE_SPT_BD_COMPUTE_SHARE_SECRET */

#ifdef HSE_SPT_KEY_VERIFY
    #define HSE_SRV_ID_KEY_VERIFY               ((hseSrvId_t)(HSE_SRV_VER_0 | 0x0000010BUL))  /**< @brief Perform a verification for CMAC and SHA256/384/512. Data structure used: #hseKeyVerifySrv_t. */
#endif /* HSE_SRV_ID_KEY_VERIFY */

#ifdef HSE_SPT_EXTEND_KEY_CATALOG
    #define HSE_SRV_ID_EXTEND_KEY_CATALOG       ((hseSrvId_t)(HSE_SRV_VER_0 | 0x0000010CUL))  /**< @brief Update the NVM or RAM key catalogs format. Data structure used: #hseExtendKeyCatalogSrv_t. */
#endif /* HSE_SPT_EXTEND_KEY_CATALOG */

/*-------- Service class 0xA1: SHE specification commands -------------*/
#ifdef HSE_SPT_SHE
    #define HSE_SRV_ID_SHE_LOAD_KEY             ((hseSrvId_t)(HSE_SRV_VER_0 | 0x0000A101UL))  /**< @brief Load a SHE key using the SHE memory update protocol. Data structure used: #hseSheLoadKeySrv_t. */
    #define HSE_SRV_ID_SHE_LOAD_PLAIN_KEY       ((hseSrvId_t)(HSE_SRV_VER_0 | 0x0000A102UL))  /**< @brief Load the SHE RAM key as plain text. Data structure used: #hseSheLoadPlainKeySrv_t. */
    #define HSE_SRV_ID_SHE_EXPORT_RAM_KEY       ((hseSrvId_t)(HSE_SRV_VER_0 | 0x0000A103UL))  /**< @brief Export the SHE RAM key. Data structure used: #hseSheExportRamKeySrv_t. */
    #define HSE_SRV_ID_SHE_GET_ID               ((hseSrvId_t)(HSE_SRV_VER_0 | 0x0000A104UL))  /**< @brief Get UID as per SHE specification. Data structure used: #hseSheGetIdSrv_t. */
    #define HSE_SRV_ID_SHE_BOOT_OK              ((hseSrvId_t)(HSE_SRV_VER_0 | 0x0000A105UL))  /**< @brief BOOT_OK as per SHE specification. No data structure used. */
    #define HSE_SRV_ID_SHE_BOOT_FAILURE         ((hseSrvId_t)(HSE_SRV_VER_0 | 0x0000A106UL))  /**< @brief BOOT_FAILURE as per SHE specification. No data structure used. */
#endif /* HSE_SPT_SHE*/

/*-------- Service class 0x02: cryptographic functions -------------*/
#ifdef HSE_SPT_HASH
    #define HSE_SRV_ID_HASH                     ((hseSrvId_t)(HSE_SRV_VER_0 | 0x00A50200UL))  /**< @brief HASH service ID. Data structure used: #hseHashSrv_t. */
#endif /*HSE_SPT_HASH*/

    #define HSE_SRV_ID_MAC                      ((hseSrvId_t)(HSE_SRV_VER_0 | 0x00A50201UL))  /**< @brief MAC generate/verify. Data structure used: #hseMacSrv_t. */

#ifdef HSE_SPT_FAST_CMAC
    #define HSE_SRV_ID_FAST_CMAC                ((hseSrvId_t)(HSE_SRV_VER_0 | 0x00A50202UL))  /**< @brief CMAC fast generate/verify. Data structure used: #hseFastCMACSrv_t. */
#endif  /* HSE_SPT_FAST_CMAC */

    #define HSE_SRV_ID_SYM_CIPHER               ((hseSrvId_t)(HSE_SRV_VER_0 | 0x00A50203UL))  /**< @brief Symmetric encryption/decryption. Data structure used: #hseSymCipherSrv_t. */

#ifdef HSE_SPT_AEAD
    #define HSE_SRV_ID_AEAD                     ((hseSrvId_t)(HSE_SRV_VER_0 | 0x00A50204UL))  /**< @brief AEAD  encryption/decryption. Data structure used: #hseAeadSrv_t. */
#endif /*HSE_SPT_AEAD*/

#ifdef HSE_SPT_XTS_AES
    #define HSE_SRV_ID_XTS_AES_CIPHER           ((hseSrvId_t)(HSE_SRV_VER_0 | 0x00A50205UL))  /**< @brief XTS AES encryption/decryption. Data structure used: #hseXtsAesCipherSrv_t. */
#endif /* HSE_SPT_XTS_AES */

#ifdef HSE_SPT_SIGN
    #define HSE_SRV_ID_SIGN                     ((hseSrvId_t)(HSE_SRV_VER_0 | 0x00000206UL))  /**< @brief Digital Signature. Data structure used: #hseSignSrv_t. */
#endif /* HSE_SPT_SIGN */

#ifdef HSE_SPT_RSA
    #define HSE_SRV_ID_RSA_CIPHER               ((hseSrvId_t)(HSE_SRV_VER_0 | 0x00000207UL))  /**< @brief RSA Cipher ID. Data structure used: #hseRsaCipherSrv_t. */
#endif /* HSE_SPT_RSA */

#ifdef HSE_SPT_AUTHENC
    #define HSE_SRV_ID_AUTHENC                  ((hseSrvId_t)(HSE_SRV_VER_0 | 0x00A50208UL))  /**< @brief AuthEnc ID. Data structure used: #hseAuthEncSrv_t. */
#endif /* HSE_SPT_AUTHENC */

#ifdef HSE_SPT_CRC32
    #define HSE_SRV_ID_CRC32                    ((hseSrvId_t)(HSE_SRV_VER_0 | 0x00A50209UL))  /**< @brief CRC32 ID. Data structure used: #hseCrc32Srv_t. */
#endif /* HSE_SPT_CRC32 */

#ifdef HSE_SPT_SIPHASH
    #define HSE_SRV_ID_SIPHASH                  ((hseSrvId_t)(HSE_SRV_VER_0 | 0x0000020AUL))  /**< @brief SipHash service ID. Data structure used: #hseSipHashSrv_t. */
#endif  /* HSE_SPT_SIPHASH*/

#ifdef HSE_SPT_CMAC_WITH_COUNTER
    #define HSE_SRV_ID_CMAC_WITH_COUNTER        ((hseSrvId_t)(HSE_SRV_VER_0 | 0x00A5020BUL))  /**< @brief CMAC with counter service ID. Data structure used: #hseCmacWithCounterSrv_t. */
#endif  /*HSE_SPT_CMAC_WITH_COUNTER*/

/*-------- Service class 0x03: random number generation ------------*/
#ifdef HSE_SPT_RANDOM
    #define HSE_SRV_ID_GET_RANDOM_NUM           ((hseSrvId_t)(HSE_SRV_VER_0 | 0x00000300UL))  /**< @brief Get random number. Data structure used: #hseGetRandomNumSrv_t */
#endif /* HSE_SPT_RANDOM */

/*-------- Service class 0x04: monotonic counter management --------*/
#ifdef HSE_SPT_MONOTONIC_COUNTERS
    #define HSE_SRV_ID_INCREMENT_COUNTER        ((hseSrvId_t)(HSE_SRV_VER_0 | 0x00A50400UL))  /**< @brief Increment a monotonic counter. Data structure used: #hseIncrementCounterSrv_t. */
    #define HSE_SRV_ID_READ_COUNTER             ((hseSrvId_t)(HSE_SRV_VER_0 | 0x00A50401UL))  /**< @brief Read a monotonic counter. Data structure used: #hseReadCounterSrv_t. */
#endif /* HSE_SPT_MONOTONIC_COUNTERS*/

/*-------- Service class 0x05: secure memory regions management ----*/
#ifdef HSE_SPT_SMR_CR
    #define HSE_SRV_ID_SMR_ENTRY_INSTALL        ((hseSrvId_t)(HSE_SRV_VER_0 | 0x00000501UL))  /**< @brief Install a Secure memory region (SMR) table entry. Data structure used: #hseSmrEntryInstallSrv_t. */
    #define HSE_SRV_ID_SMR_VERIFY               ((hseSrvId_t)(HSE_SRV_VER_0 | 0x00000502UL))  /**< @brief Verify a Secure memory region (SMR) table entry. Data structure used: #hseSmrVerifySrv_t. */
    #define HSE_SRV_ID_CORE_RESET_ENTRY_INSTALL ((hseSrvId_t)(HSE_SRV_VER_0 | 0x00000503UL))  /**< @brief Install a Core Reset (CR) table entry. Data structure used: #hseCrEntryInstallSrv_t. */
    #define HSE_SRV_ID_ON_DEMAND_CORE_RESET     ((hseSrvId_t)(HSE_SRV_VER_0 | 0x00000504UL))  /**< @brief On demand release a core  from reset after loading and verification. Data structure used: #hseCrOnDemandBootSrv_t. */
    #define HSE_SRV_ID_SMR_ENTRY_ERASE          ((hseSrvId_t)(HSE_SRV_VER_0 | 0x00000505UL))  /**< @brief Erase a Secure memory region (SMR) table entry. Data structure used: #hseSmrEntryEraseSrv_t. */
    #define HSE_SRV_ID_CORE_RESET_ENTRY_ERASE   ((hseSrvId_t)(HSE_SRV_VER_0 | 0x00000506UL))  /**< @brief Erase a Core Reset (CR) table entry. Data structure used: #hseCrEntryEraseSrv_t. */
#endif /*HSE_SPT_SMR_CR */

/*----------- Service class 0x06: IPSEC protocol acceleration ------*/
#ifdef HSE_SPT_IPSEC
    #define HSE_SRV_ID_IPSEC_INIT               ((hseSrvId_t)(HSE_SRV_VER_0 | 0x00A50600UL))  /**< @brief Initialize an IPSEC SA. Data structure used: #hseIpsecInitSrv_t. */
    #define HSE_SRV_ID_IPSEC_PROCESS            ((hseSrvId_t)(HSE_SRV_VER_0 | 0x00A50601UL))  /**< @brief Process an IPSEC frame. Data structure used: #hseIpsecProcessSrv_t. */
    #define HSE_SRV_ID_IPSEC_GET_SEQ_NUM        ((hseSrvId_t)(HSE_SRV_VER_0 | 0x00A50602UL))  /**< @brief Get the expected sequence number of an SA. Data structure used: #hseIpsecGetSeqNumSrv_t. */
    #define HSE_SRV_ID_IPSEC_SET_SEQ_NUM        ((hseSrvId_t)(HSE_SRV_VER_0 | 0x00A50603UL))  /**< @brief Set an SA's expected sequence number. Data structure used: #hseIpsecSetSeqNumSrv_t. */
#endif /* HSE_SPT_IPSEC */
/**@}*/

/*==================================================================================================
*                                             ENUMS
==================================================================================================*/

/*==================================================================================================
                                 STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/
/**   @addtogroup hse_interface_descriptor HSE Service Descriptor
 *    @ingroup    class_interface
 *    @{
 */
/** @page          descriptor HSE service descriptor details
 *  @details       Each service is identified by a unique ID (called service ID). Each service ID identifies a service from the hseSrvDescriptor_t#hseSrv union.
 *                 The service ID contains 4 bytes that specify the following:
 *                  - byte[0]: service index (0..255)
 *                  - byte[1]: service class index (0..255)(see more details below)
 *                  - byte[2]: 0x00 - service can be canceled; 0xA5 - service can not be canceled
 *                  - byte[3]: service version (0..255)
 *
 * The following service classes are defined:
 *  - Administrative services (e.g set/get an HSE attribute, self-test, cancel service etc.)
 *  - Key management services (e.g key generation, Diffie-Hellman shared secret computation, import/export key etc.)
 *  - Crypto services (e.g. HASH, MAC generate/verify, encryption/decryption, signature generate/verify)
 *  - Random number
 *  - Monotonic counters
 *  - Secure boot and memory checking services (Secure Memory Regions (SMR) and Core reset(CR) services)
 *  - Network Crypto services (IPsec ).
 *
 * @note
 *  - The services guarded by HSE_SPT_FLASHLESS_DEV macro are available only for HSE_H/M (flashless devices).
 *  - The services guarded by HSE_SPT_INTERNAL_FLASH_DEV macro are available only for HSE_B (devices with internal flash).
 */
typedef struct
{
    /** @brief The service ID of the HSE message */
    hseSrvId_t        srvId;
    /** @brief The service metadata (e.g. priority)*/
    hseSrvMetaData_t  srvMetaData;
    /** @brief The service ID will identify a service in the following union */
    union
    {
        /*-------- HSE administrative services --------*/
            hseSetAttrSrv_t                 setAttrReq;             /**< @brief Request to set a HSE attribute (note that some attributes are read only) */
            hseGetAttrSrv_t                 getAttrReq;             /**< @brief Request to get a HSE attribute */
        #ifdef HSE_SPT_SELF_TEST
            hseSelfTestSrv_t                selfTestReq;            /**< @brief Request to execute a HSE self test procedure */
        #endif
            hseCancelSrv_t                  cancelSrvReq;           /**< @brief Request to cancel a one-pass or streaming service on a specific channel */
        #ifdef HSE_SPT_OTA_FIRMWARE_UPDATE
            hseFirmwareUpdateSrv_t          firmwareUpdateReq;      /**< @brief Request to HSE firmware update. */
        #endif
        /*--------System authorization services--------*/
            hseSysAuthorizationReqSrv_t     sysAuthorizationReq;    /**< @brief Perform an SYS Authorization Request */
            hseSysAuthorizationRespSrv_t    sysAuthorizationResp;   /**< @brief Send the SYS Authorization Response */
        #ifdef HSE_SPT_BOOTDATASIGN
            hseBootDataImageSignSrv_t       bootDataImageSignReq;   /**< @brief Request to generate the Signature  for Boot Data images (e.g. for HSE_H/M, IVT/DCD/ST/LPDDR4(ZSE devices)/AppBSB image; for HSE_B, IVT/XRDC/AppBSB image) */
            hseBootDataImageVerifySrv_t     bootDataImageSigVerifyReq;/**< @brief Request to verify the Signature for Boot Data images (e.g. for HSE_H/M, IVT/DCD/ST/LPDDR4(ZSE devices)/AppBSB image; for HSE_B, IVT/XRDC/AppBSB image) */
        #endif
        #ifdef HSE_SPT_STREAM_CTX_IMPORT_EXPORT
            hseImportExportStreamCtxSrv_t   importExportStreamCtx;  /**< @brief Request to import/export a streaming context. */
        #endif
        #ifdef HSE_SPT_FLASHLESS_DEV /* HSE_H/M device */
            hsePublishSysImageSrv_t         publishSysImageReq;     /**< @brief Request to Publish a NVM SYS-IMAGE (only for HSE_H/M). */
            hseGetSysImageSizeSrv_t         getSysImageSizeReq;     /**< @brief Request to get SYS-IMAGE size (only for HSE_H/M). */
            hseVerifySysImageSrv_t          verifySysImageReq;      /**< @brief Request to Verify SYS-IMAGE after it is stored in external flash (only for HSE_H/M). */
            #ifdef HSE_SPT_MONOTONIC_COUNTERS
            hsePublishLoadCntTblSrv_t       publishLoadCntTblReq;   /**< @brief Request to publish/load the NVM container for the  Monotonic Counter table (only for HSE_H/M). */
            #endif/*HSE_SPT_MONOTONIC_COUNTERS*/
            #ifdef HSE_SPT_OTFAD
            hseInstallOtfadContextSrv_t     installOtfadReq;        /**< @brief Request to install an OTFAD context (only for HSE_H/M). */
            hseActivateOtfadContextSrv_t    activateOtfadReq;       /**< @brief Request to activate on-demand an already installed OTFAD context (only for HSE_H/M). */
            hseGetOtfadContextSrv_t         getOtfadCtxReq;         /**< @brief Request to get OTFAD context information (only for HSE_H/M). */
            #endif /* end HSE_SPT_OTFAD */
            hsePrepareForStandBySrv_t       prepareForStandByReq;   /**< @brief Request HSE to prepare for Stand-By mode (only for HSE_H/M). */
            #ifdef HSE_SPT_MSC_KEYSTORE
            hseConfigKHTTSrv_t              configKHTT;            /**< @brief Configure the Key Handle Translation Table (KHTT). */
            hsePushMscKeySrv_t              pushMscKey;            /**< @brief Push one or more HSE keys in ACE key store */
            #endif /* HSE_SPT_MSC_KEYSTORE*/
        #endif /* end HSE_SPT_FLASHLESS_DEV */

        #ifdef HSE_SPT_INTERNAL_FLASH_DEV /* HSE_B device */
            hseEraseNvmDataSrv_t            eraseNvmDataReq;        /**< @brief Request to reset HSE data flash. Only allowed in CUST_DEL LC */

            #ifdef HSE_SPT_OTA_SBAF_UPDATE
            hseSbafUpdateSrv_t              sbafUpdateReq;         /**< @brief Request to SBAF firmware update. */
            #endif /* HSE_SPT_OTA_SBAF_UPDATE */

            #ifdef HSE_SPT_ERASE_FW
            hseEraseFwSrv_t            eraseFwReq;                /**< @brief Request to erase sys-img, backup, current firmware. Only allowed in CUST_DEL LC */
            #endif /* HSE_SPT_ERASE_FW */

        #endif /* HSE_SPT_INTERNAL_FLASH_DEV */

        #ifdef HSE_SPT_TMU_REG_CONFIG
            hseTmuRegConfigSrv_t            tmuRegConfigReq;       /**< @brief TMU register configuration */
        #endif /* HSE_SPT_TMU_REG_CONFIG */

        #ifdef HSE_SPT_TRIM_PASSWORD_PROVISION
            hseTrimPasswordProvision_t        trimPasswordReq;       /**< @brief Request to verify trim password to enable read access for certain system fuses (e.g trim values, MIDR etc). */
        #endif  /* HSE_SPT_TRIM_PASSWORD_PROVISION */

        /*--------HSE key management services--------*/
        #ifdef HSE_SPT_ECC_USER_CURVES
            hseLoadEccCurveSrv_t            loadEccCurveReq;       /**< @brief Request to load an ECC curve */
        #endif
        #ifdef HSE_SPT_FORMAT_KEY_CATALOGS
            hseFormatKeyCatalogsSrv_t       formatKeyCatalogsReq;   /**< @brief Format the key catalogs */
        #endif
            hseEraseKeySrv_t                eraseKeyReq;            /**< @brief Request to erase NVM/RAM key(s). */
        #ifdef HSE_SPT_GET_KEY_INFO
            hseGetKeyInfoSrv_t              getKeyInfoReq;          /**< @brief Request to get key information (flags) */
        #endif
        #ifdef HSE_SPT_IMPORT_KEY
            hseImportKeySrv_t               importKeyReq;           /**< @brief Request to import a key. */
        #endif
        #ifdef HSE_SPT_EXPORT_KEY
            hseExportKeySrv_t               exportKeyReq;           /**< @brief Request to export a key. */
        #endif
        #ifdef HSE_SPT_KEY_VERIFY
            hseKeyVerifySrv_t               verifyKeyReq;           /**< @brief Request to verify a key. */
        #endif
        #ifdef HSE_SPT_KEY_GEN
            hseKeyGenerateSrv_t             keyGenReq;              /**< @brief Request to generate a key (e.g. sym random key, rsa key pair etc.) . */
        #endif
        #ifdef HSE_SPT_COMPUTE_DH
            hseDHComputeSharedSecretSrv_t   dhComputeSecretReq;     /**< @brief Request a ECC Diffie-Hellman Compute shared secret. */
        #endif
        #ifdef HSE_SPT_BURMESTER_DESMEDT
            hseBurmesterDesmedtSrv_t        burmesterDesmedtReq;    /**< @brief Request to perform a Burmester-Desmedt computation. */
        #endif
        #ifdef HSE_SPT_KEY_DERIVE
            hseKeyDeriveSrv_t               keyDeriveReq;           /**< @brief Request key derivation function. */
            hseKeyDeriveCopyKeySrv_t        keyDeriveCopyKeyReq;    /**< @brief Request to copy a key from the derived key material. */
        #endif
        #ifdef HSE_SPT_EXTEND_KEY_CATALOG
            hseExtendKeyCatalogSrv_t        extendKeyCatalogReq;    /**< @brief Request to extend the NVM or RAM key catalog format. */
        #endif
        #ifdef HSE_SPT_SHE
            hseSheLoadKeySrv_t              sheLoadKeyReq;          /**< @brief Request to load a SHE key using memory update protocol (as per SHE specification) */
            hseSheLoadPlainKeySrv_t         sheLoadPlainKeyReq;     /**< @brief Request to load the SHE RAM key from plain text (as per SHE specification) */
            hseSheExportRamKeySrv_t         sheExportRamKeyReq;     /**< @brief Request to export the SHE RAM key (as per SHE specification) */
            hseSheGetIdSrv_t                sheGetIdReq;            /**< @brief Request to get UID (as per SHE specification) */
        #endif

        /*--------HSE crypto services--------*/
        #ifdef HSE_SPT_HASH
            hseHashSrv_t                    hashReq;                /**< @brief Request a HASH */
        #endif
            hseMacSrv_t                     macReq;                 /**< @brief Request to generate/verify a MAC */
        #ifdef HSE_SPT_FAST_CMAC
            hseFastCMACSrv_t                fastCmacReq;            /**< @brief Request to FAST generate/verify a CMAC */
        #endif
        #ifdef HSE_SPT_CMAC_WITH_COUNTER
            hseCmacWithCounterSrv_t         cmacWithCounterReq;     /**< @brief Request to generate/verify a CMAC with counter */
        #endif
            hseSymCipherSrv_t               symCipherReq;           /**< @brief Request a Symmetric Cipher operation */
        #ifdef HSE_SPT_AEAD
            hseAeadSrv_t                    aeadReq;                /**< @brief Request an AEAD operation */
        #endif
        #ifdef HSE_SPT_XTS_AES
            hseXtsAesCipherSrv_t            xtsAesCipherReq;        /**< @brief Request a XTS AES Cipher operation */
        #endif
        #ifdef HSE_SPT_SIGN
            hseSignSrv_t                    signReq;                /**< @brief Request a Digital Signature Generation/Verification */
        #endif
        #ifdef HSE_SPT_RSA
            hseRsaCipherSrv_t               rsaCipherReq;           /**< @brief Request a RSA Cipher (Encryption/Decryption) operation */
        #endif
        #ifdef HSE_SPT_AUTHENC
            hseAuthEncSrv_t                 authEncReq;             /**< @brief Request an AuthEncryption operation (encrypt/decrypt + authenticate) */
        #endif
        #ifdef HSE_SPT_CRC32
            hseCrc32Srv_t                   crc32Req;                /**< @brief Request to initialize an CRC computation */
        #endif
        #ifdef HSE_SPT_SIPHASH
            hseSipHashSrv_t                 sipHashReq;             /**< @brief Request to generate/verify a SipHash */
        #endif
         /*--------HSE random number--------*/
        #ifdef HSE_SPT_RANDOM
            hseGetRandomNumSrv_t            getRandomNumReq;        /**< @brief Request to random number generation */
        #endif
        /*--------HSE monotonic counters--------*/
        #ifdef HSE_SPT_MONOTONIC_COUNTERS
            hseIncrementCounterSrv_t        incCounterReq;          /**< @brief Request to increment a monotonic counter */
            hseReadCounterSrv_t             readCounterReq;         /**< @brief Request to read a monotonic counter */
            hseConfigSecCounterSrv_t        configSecCounter;       /**< @brief Request to configure a secure counter */
        #endif
        /*--------Secure Memory Regions (SMR) management--------*/
        #ifdef HSE_SPT_SMR_CR
            hseSmrEntryInstallSrv_t         smrEntryInstallReq;     /**< @brief Request to install a Secure Memory Region (SMR) table entry. */
            hseSmrVerifySrv_t               smrVerifyReq;           /**< @brief Request to verify a Secure Memory Region (SMR) table entry. */
            hseSmrEntryEraseSrv_t           smrEntryEraseReq;       /**< @brief Request to erase a Secure Memory Region (SMR) table entry */
            hseCrEntryInstallSrv_t          crEntryInstallReq;      /**< @brief Request to install a Core Reset (CR) table entry. */
            hseCrOnDemandBootSrv_t          crOnDemandBootReq;      /**< @brief Request to release a Core Reset (CR) table entry. */
            hseCrEntryEraseSrv_t            crEntryEraseReq;        /**< @brief Request to erase a Core Reset (CR) table entry. */
        #endif
        /*--------IPSEC protocol acceleration--------*/
        #ifdef HSE_SPT_IPSEC
            hseIpsecInitSrv_t               ipsecInitReq;           /**< @brief Request to initialize an IPSEC SA. */
            hseIpsecProcessSrv_t            ipsecProcessReq;        /**< @brief Request to process an IPSEC frame. */
            hseIpsecGetSeqNumSrv_t          ipsecGetSeqNumReq;      /**< @brief Request to get the expected sequence number of an SA. */
            hseIpsecSetSeqNumSrv_t          ipsecSetSeqNumReq;      /**< @brief Request to set an SA's expected sequence number. */
        #endif
        /*-------- HSE CUSTOM SERVICE --------*/
        #if HSE_FWTYPE >= 8U
            HSE_CUSTOM_SERVICES
        #endif

    } hseSrv;
} hseSrvDescriptor_t;

/*==================================================================================================
                                 GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/

/*==================================================================================================
                                     FUNCTION PROTOTYPES
==================================================================================================*/

#if (   defined ( __ghs__ ) ||  /* GHS compiler */  \
        defined ( __CC_ARM ) || /* Arm Compiler 4/5  */  \
        defined (__ARMCC_VERSION)||/* Arm Compiler 6 (armclang) */\
        defined ( __GNUC__ ) || /* GNU Compiler*/  \
        defined ( __ICCARM__ ) /* IAR Compiler*/ )
    #pragma pack(pop)
    #undef PRAGMA_PACK_ERROR
#elif defined( __DCC__ ) /* DIAB compiler */
    #pragma pack()
    #undef PRAGMA_PACK_ERROR
#else
    #error "Unknown compiler. Define pragma pack for the compiler."
#endif

/* GNU Compiler &  DIAB Compiler */
#if (defined (__GNUC__) && defined (__DCC__))
        #pragma clang diagnostic pop
#endif

#ifdef __cplusplus
}
#endif

#endif /* HSE_INTERFACE_H */

/** @} */
