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

#if !defined(ARRAY_SIZE)
#define ARRAY_SIZE(a) (sizeof(a) / sizeof((a)[0]))
#endif

#if !defined(FOREACH)
#define FOREACH(index, array) for (uint32_t(index) = 0; (index) < ARRAY_SIZE(a); ++(index))
#endif

#if !defined(BIT)
#define BIT(n) (1U << (n))
#endif

// Siul2_Dio_Ip.h included
#if defined(SIUL2_DIO_IP_H)
#define SIUL2_DIO_PIN(Port, Pin)                                                                   \
    (((Pin) < 16) ? PT##Port##_L_HALF : PT##Port##_H_HALF), ((Pin) & 0x0F)
#endif

// Siul2_Port_Ip.h included
#if defined(SIUL2_PORT_IP_H)
static inline void Siul2_Port_DisableUnusedPins(uint32_t       NumberOfUnusedPins,
                                                const uint8_t *UnusedPins) {
    for (uint32_t i = 0; i < NumberOfUnusedPins; ++i) {
        uint8_t                 pin = *(UnusedPins++);
        Siul2_Port_Ip_PortType *BaseValue =
            (Siul2_Port_Ip_PortType *)(SIUL2_MSCR_BASE + (pin & ~0xFU));
        uint16_t PinValue = pin & 0xF;
        if ((pin & (~1U)) == 24) {
            Siul2_Port_Ip_SetPinDirection(BaseValue, PinValue, SIUL2_PORT_IN);
            Siul2_Port_Ip_SetPullSel(BaseValue, PinValue, PORT_INTERNAL_PULL_DOWN_ENABLED);
        } else {
            Siul2_Port_Ip_SetPinDirection(BaseValue, PinValue, SIUL2_PORT_OUT);
            Siul2_Port_Ip_SetOutputBuffer(BaseValue, PinValue, 1, PORT_MUX_AS_GPIO);
        }
    }
}
#endif

// Flexio_Mcl_Ip.h included
#if defined(FLEXIO_MCL_IP_H)
#define Flexio_Pins_Input  (IP_FLEXIO->PIN)
#define Flexio_Pins_Output (IP_FLEXIO->PINOUTD)
#define Flexio_Pins_Status (IP_FLEXIO->PINSTAT
#define Flexio_Pins_OutputEnable (IP_FLEXIO->PINOUTE)
#define Flexio_Pins_OutputDisable (IP_FLEXIO->PINOUTDIS)
#define Flexio_Pins_ClearOutput     (IP_FLEXIO->PINOUTCLR)
#define Flexio_Pins_SetOutput       (IP_FLEXIO->PINOUTSET)
#define Flexio_Pins_ToggleOutput    (IP_FLEXIO->PINOUTTOG)
#define Flexio_Pins_InterruptEnable (IP_FLEXIO->PINIEN)
#define Flexio_Pins_RaiseInterrupt  (IP_FLEXIO->PINREN)
#define Flexio_Pins_FallInterrupt   (IP_FLEXIO->PINFEN)

#define Flexio_Shifter_Control(n)           (IP_FLEXIO->SHIFTCTL[(n)])
#define Flexio_Shifter_Config(n)            (IP_FLEXIO->SHIFTCFG[(n)])
#define Flexio_Shifter_Status               (IP_FLEXIO->SHIFTSTAT)
#define Flexio_Shifter_ErrorStatus          (IP_FLEXIO->SHIFTERR)
#define Flexio_Shifter_InterruptEnable      (IP_FLEXIO->SHIFTSIEN)
#define Flexio_Shifter_ErrorInterruptEnable (IP_FLEXIO->SHIFTEIEN)
#define Flexio_Shifter_DMAStatusEnable      (IP_FLEXIO->SHIFTSDEN)
#define Flexio_Shifter_State                (IP_FLEXIO->SHIFTSTAT)
/**
 * D[31:0]
 */
#define Flexio_Shifter_Buffer(n) (IP_FLEXIO->SHIFTBUF[(n)])
/**
 * D[0:31]
 */
#define Flexio_Shifter_BitSwapBuffer(n) (IP_FLEXIO->SHIFTBUFBIS[(n)])
/**
 * D[15:0], D[31:16]
 */
#define Flexio_Shifter_HalfWordSwapBuffer(n) (IP_FLEXIO->SHIFTBUFHWS[(n)])
/**
 * D[7:0], D[15:8], D[23:16], D[31:24]
 */
#define Flexio_Shifter_ByteSwapBuffer(n) (IP_FLEXIO->SHIFTBUFBYS[(n)])
/**
 * D[24:31], D[16:23], D[8:15], D[0:7]
 */
#define Flexio_Shifter_BitByteSwapBuffer(n) (IP_FLEXIO->SHIFTBUFBBS[(n)])
/**
 * D[23:16], D[31:24], D[7:0], D[15:8]
 */
#define Flexio_Shifter_HalfWordByteSwapBuffer(n) (IP_FLEXIO->SHIFTBUFHBS[(n)])
/**
 * D[27:24], D[31:28], D[19:16], D[23:20], D[11:8], D[15:12], D[3:0], D[7:4]
 */
#define Flexio_Shifter_NibbleByteSwapBuffer(n) (IP_FLEXIO->SHIFTBUFNBS[(n)])
/**
 * D[3:0], D[7:4], D[11:8], D[15:12], D[19:16], D[23:20], D[27:24], D[31:28]
 */
#define Flexio_Shifter_NibbleSwapBuffer(n) (IP_FLEXIO->SHIFTBUFNIS[(n)])
/**
 * D[31], D[29], D[27], D[25], D[23], D[21], D[19], D[17], D[15], D[13], D[11], D[9], D[7], D[5], D[3], D[1],
 * D[30], D[28], D[26], D[24], D[22], D[20], D[18], D[16], D[14], D[12], D[10], D[8], D[6], D[4], D[2], D[0]
 */
#define Flexio_Shifter_OddEvenSwapBuffer(n) (IP_FLEXIO->SHIFTBUFOES[(n)])
/**
 * D[30], D[28], D[26], D[24], D[22], D[20], D[18], D[16], D[14], D[12], D[10], D[8], D[6], D[4], D[2], D[0],
 * D[31], D[29], D[27], D[25], D[23], D[21], D[19], D[17], D[15], D[13], D[11], D[9], D[7], D[5], D[3], D[1]
 */
#define Flexio_Shifter_EvenOddSwapBuffer(n) (IP_FLEXIO->SHIFTBUFEOS[(n)])

#define Flexio_Timer_Control(n)      (IP_FLEXIO->TIMCTL[(n)])
#define Flexio_Timer_Config(n)       (IP_FLEXIO->TIMCFG[(n)])
#define Flexio_Timer_Compare(n)      (IP_FLEXIO->TIMCMP[(n)])
#define Flexio_Timer_Status          (IP_FLEXIO->TIMSTAT)
#define Flexio_Timer_InterruptEnable (IP_FLEXIO->TIMIEN)
#define Flexio_Timer_DMAStatusEnable (IP_FLEXIO->TIMERSDEN)

#define Flexio_Trigger_Status          (IP_FLEXIO->TRIGSTAT)
#define Flexio_Trigger_InterruptEnable (IP_FLEXIO->TRIGIEN)

typedef enum {
    SHIFTER_MODE_DISABLED         = 0U,
    SHIFTER_MODE_RECEIVE          = 1U,
    SHIFTER_MODE_TRANSMIT         = 2U,
    SHIFTER_MODE_MATCH_STORE      = 4U,
    SHIFTER_MODE_MATCH_CONTINUOUS = 5U,
    SHIFTER_MODE_STATE            = 6U,
    SHIFTER_MODE_LOGIC            = 7U,
} Flexio_Shifter_ModeType;

typedef enum {
    SHIFTER_STORE_PRESHIFT  = 0U, // Store preshift register state
    SHIFTER_STORE_POSTSHIFT = 1U, // Store postshift register state
} Flexio_Shifter_StoreType;

typedef struct {
    uint8_t                 ShifterID;
    Flexio_Shifter_ModeType ShifterMode;

    uint8_t                         TimerInputID;
    Flexio_Mcl_Ip_TimerPolarityType TimerPolarity;

    uint8_t                       PinNumber;
    Flexio_Mcl_Ip_PinConfigType   PinOutType;
    Flexio_Mcl_Ip_PinPolarityType PinPolarity;

    uint16_t ParallelWidth; // 1-32 bits -> 0-31
    bool     Mode24bit;     // 24-bit mode or 32-bit mode

    Flexio_Shifter_StoreType LastStore; // Store preshift or postshift register state

    Flexio_Mcl_Ip_ShifterSourceType InputSource; // Input from pin or another shifter

    Flexio_Mcl_Ip_ShifterStopType  StopBit;  // Stop bit type
    Flexio_Mcl_Ip_ShifterStartType StartBit; // Start bit type

} Flexio_Shifter_Config_t;

static inline void Flexio_Shifter_Init(const Flexio_Shifter_Config_t *Config) {

    bool SetOutput = false;

    if (Config->ShifterID >= FLEXIO_SHIFTCTL_COUNT) {
        // Handle error: invalid shifter ID
        return;
    }

    Flexio_Mcl_Ip_PinConfigType PinConfig = Config->PinOutType;

    if (FLEXIO_PIN_CONFIG_OUTPUT == PinConfig) {
        // Handle error: pin configuration is disabled
        PinConfig = FLEXIO_PIN_CONFIG_BIDIR_OUTPUT;
        SetOutput = true;
    }

    Flexio_Shifter_Control(Config->ShifterID) =
        FLEXIO_SHIFTCTL_SMOD(Config->ShifterMode) | FLEXIO_SHIFTCTL_PINPOL(Config->PinPolarity) |
        FLEXIO_SHIFTCTL_PINSEL(Config->PinNumber) | FLEXIO_SHIFTCTL_PINCFG(PinConfig) |
        FLEXIO_SHIFTCTL_TIMPOL(Config->TimerPolarity) |
        FLEXIO_SHIFTCTL_TIMSEL(Config->TimerInputID);
    Flexio_Shifter_Config(Config->ShifterID) =
        FLEXIO_SHIFTCFG_SSTOP(Config->StopBit) | FLEXIO_SHIFTCFG_SSTART(Config->StartBit) |
        FLEXIO_SHIFTCFG_INSRC(Config->InputSource) | FLEXIO_SHIFTCFG_LATST(Config->LastStore) |
        FLEXIO_SHIFTCFG_SSIZE(Config->Mode24bit) | FLEXIO_SHIFTCFG_PWIDTH(Config->ParallelWidth);

    if (SetOutput) {
        Flexio_Shifter_Control(Config->ShifterID) |= FLEXIO_SHIFTCTL_PINCFG(FLEXIO_PIN_CONFIG_OUTPUT);
    }
}

#define TIMER_TRIGGER_EXTERNAL_0          (0U)             // External trigger 0
#define TIMER_TRIGGER_EXTERNAL_1          (1U)             // External trigger 1
#define TIMER_TRIGGER_EXTERNAL_2          (2U)             // External trigger 2
#define TIMER_TRIGGER_EXTERNAL_3          (3U)             // External trigger 3
#define TIMER_TRIGGER_INTERNAL_PIN(n)     ((n) << 1)       // Internal trigger
#define TIMER_TRIGGER_INTERNAL_SHIFTER(n) (((n) << 2) | 1) // Internal shifter flag
#define TIMER_TRIGGER_INTERNAL_TIMER(n)   (((n) << 2) | 3) // Internal timer trigger

typedef enum {
    TIMER_DECREMENT_CLK_SHIFT_TMR =
        0x00U, /*!< Decrement counter on FlexIO clock, Shift clock equals Timer output. */
    TIMER_DECREMENT_TRG_SHIFT_TMR =
        0x01U, /*!< Decrement counter on Trigger input (both edges), Shift clock equals Timer output. */
    TIMER_DECREMENT_PIN_SHIFT_PIN =
        0x02U, /*!< Decrement counter on Pin input (both edges), Shift clock equals Pin input. */
    TIMER_DECREMENT_TRG_SHIFT_TRG =
        0x03U, /*!< Decrement counter on Trigger input (both edges), Shift clock equals Trigger input. */
    TIMER_DECREMENT_FLEXIO_DIV_16       = 0x04U,
    TIMER_DECREMENT_FLEXIO_DIV_256      = 0x05U,
    TIMER_DECREMENT_PIN_IN_RISING_EDGE  = 0x06U,
    TIMER_DECREMENT_TRIGGER_RISING_EDGE = 0x07U,
} Flexio_Timer_TriggerDecrementType;

typedef struct {
    uint8_t TimerID;

    Flexio_Mcl_Ip_TriggerSourceType   TriggerSourceType; // Trigger source
    uint16_t                          TriggerSource;     // Trigger source value
    Flexio_Mcl_Ip_TriggerPolarityType TriggerPolarity;   // Trigger active low

    uint8_t                       PinNumber;
    Flexio_Mcl_Ip_PinConfigType   PinOutType;
    Flexio_Mcl_Ip_PinPolarityType PinPolarity;
    bool                          UseNextPinForInput; // Use next pin for input

    bool OneShot; // One-shot mode

    Flexio_Mcl_Ip_TimerModeType TimerMode; // Timer mode

    Flexio_Mcl_Ip_TimerOutputType TimerOutput; // Timer output type

    Flexio_Timer_TriggerDecrementType TimerDecrement; // Timer decrement type
    Flexio_Mcl_Ip_TimerResetType      TimerReset;     // Timer reset type
    Flexio_Mcl_Ip_TimerDisableType    TimerDisable;   // Timer disable type
    Flexio_Mcl_Ip_TimerEnableType     TimerEnable;    // Timer enable type
    Flexio_Mcl_Ip_TimerStopType       TimerStop;      // Timer stop type
    Flexio_Mcl_Ip_TimerStartType      TimerStartBit;  // Start bit

} Flexio_Timer_Config_t;

static inline void Flexio_Timer_Init(const Flexio_Timer_Config_t *Config, uint32_t CompareValue) {

    if (Config->TimerID >= FLEXIO_TIMCTL_COUNT) {
        return; // Invalid TimerID
    }

    if (Config->UseNextPinForInput && (Config->PinNumber & 0x01U)) {
        // Pin number must be even if UseNextPinForInput is true
        return;
    }

    Flexio_Timer_Control(Config->TimerID) =
        FLEXIO_TIMCTL_TIMOD(Config->TimerMode) | FLEXIO_TIMCTL_ONETIM(Config->OneShot) |
        FLEXIO_TIMCTL_PININS(Config->UseNextPinForInput) |
        FLEXIO_TIMCTL_PINPOL(Config->PinPolarity) | FLEXIO_TIMCTL_PINSEL(Config->PinNumber) |
        FLEXIO_TIMCTL_PINCFG(Config->PinOutType) | FLEXIO_TIMCTL_TRGPOL(Config->TriggerPolarity) |
        FLEXIO_TIMCTL_TRGSRC(Config->TriggerSourceType) |
        FLEXIO_TIMCTL_TRGSEL(Config->TriggerSource);
    Flexio_Timer_Config(Config->TimerID) =
        FLEXIO_TIMCFG_TSTART(Config->TimerStartBit) | FLEXIO_TIMCFG_TSTOP(Config->TimerStop) |
        FLEXIO_TIMCFG_TIMENA(Config->TimerEnable) | FLEXIO_TIMCFG_TIMDIS(Config->TimerDisable) |
        FLEXIO_TIMCFG_TIMRST(Config->TimerReset) | FLEXIO_TIMCFG_TIMDEC(Config->TimerDecrement) |
        FLEXIO_TIMCFG_TIMOUT(Config->TimerOutput);
    Flexio_Timer_Compare(Config->TimerID) = CompareValue;
}

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
