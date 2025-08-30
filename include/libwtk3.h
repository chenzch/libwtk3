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
#define FOREACH(index, array) for ((index) = 0; (index) < ARRAY_SIZE(array); ++(index))
#endif

#if !defined(BIT)
#define BIT(n) (1U << (n))
#endif

static inline void NopDelay(uint32_t count) {
    register uint32_t Count = count;
    while (Count--) {
        __asm("nop");
    }
}

static inline void Breakpoint(void) {
    __asm("bkpt");
}

typedef union {
    uint32_t value;
    struct {
        bool     FWPresent : 1;
        bool     MUIfReady : 1;
        bool     CodeFlashErased : 1;
        bool     DataFlashErased : 1;
        bool     FirmwareErased : 1;
        bool     RecoveryMode : 1;
        uint8_t  reserved3 : 1;
        bool     SBAF_Random : 1;
        uint32_t reserved2 : 8;
        bool     WriteLockUTEST : 1;
        bool     WriteLock0 : 1;
        bool     WriteLock1 : 1;
        bool     WriteLock2 : 1;
        bool     WriteLock3 : 1;
        bool     WriteLock4 : 1;
        uint32_t reserved1 : 2;
        bool     ReadLockUTEST : 1;
        bool     ReadLock0 : 1;
        bool     ReadLock1 : 1;
        bool     ReadLock2 : 1;
        bool     ReadLock3 : 1;
        bool     ReadLock4 : 1;
        uint32_t reserved0 : 2;
    } B;
} HSE_CONFIG_GPR3;

#define HSE_UTESTWrite  BIT(16)
#define HSE_Block0Write BIT(17)
#define HSE_Block1Write BIT(18)
#define HSE_Block2Write BIT(19)
#define HSE_Block3Write BIT(20)
#define HSE_Block4Write BIT(21)
#define HSE_UTESTRead   BIT(24)
#define HSE_Block0Read  BIT(25)
#define HSE_Block1Read  BIT(26)
#define HSE_Block2Read  BIT(27)
#define HSE_Block3Read  BIT(28)
#define HSE_Block4Read  BIT(29)

#define HSE_CONFIG_GPR3_READ_MASK  (0x3F000000)
#define HSE_CONFIG_GPR3_WRITE_MASK (0x003F0000)
#define HseConfigGPR3              (*(HSE_CONFIG_GPR3 *)0x4039C028UL)

#define sBafVersion (*(uint64_t *)0x4039C020UL)

static inline void JumpToApplication(uint32_t BaseAddress) {
    uint32_t         *pIntVector = (uint32_t *)BaseAddress;
    uint32_t          userSP     = pIntVector[0];
    register uint32_t userEntry  = pIntVector[1];
    uint32_t         *pVTOR      = (uint32_t *)0xE000ED08UL;

    __asm("cpsid i \t\n");

    *pVTOR = BaseAddress;

    /* Set up stack pointer */
    __asm("msr msp, %[inputSP] \t\n"
          "msr psp, %[inputSP] \t\n"
          :
          : [inputSP] "r"(userSP));

    /* Jump to application PC (r1) */
    __asm("mov pc, %[inputEntry] \t\n" : : [inputEntry] "r"(userEntry));
}

// Clock_Ip.h included
#if defined(CLOCK_IP_H)
static inline Clock_Ip_StatusType Clock_Ip_Init_Check_Rtc(Clock_Ip_ClockConfigType const *Config) {
    if (0 == (IP_MC_ME->PRTN1_COFB1_STAT & MC_ME_PRTN1_COFB1_STAT_BLOCK34_MASK)) {
        IP_MC_ME->PRTN1_COFB1_CLKEN |= MC_ME_PRTN1_COFB1_CLKEN_REQ34_MASK;
        IP_MC_ME->PRTN1_PCONF |= MC_ME_PRTN1_PCONF_PCE_MASK;
        IP_MC_ME->PRTN1_PUPD |= MC_ME_PRTN1_PUPD_PCUD_MASK;
        IP_MC_ME->CTL_KEY = 0x5AF0U;
        IP_MC_ME->CTL_KEY = 0xA50FU;
    }
    return Clock_Ip_Init(Config);
}

#define Clock_Ip_Init(Config) Clock_Ip_Init_Check_Rtc(Config)
#endif

#if defined(CPU_S32K310) || defined(CPU_S32K311) || defined(CPU_S32K312) ||                        \
    defined(CPU_S32K314) || defined(CPU_S32K341) || defined(CPU_S32K342) ||                        \
    defined(CPU_S32K344) || defined(CPU_S32K348)
#define WTK3_GetCoreID() ((uint8_t)0)
#elif defined(CPU_S32K322) || defined(CPU_S32K324) || defined(CPU_S32K328) ||                      \
    defined(CPU_S32K336) || defined(CPU_S32K338) || defined(CPU_S32K374) ||                        \
    defined(CPU_S32K376) || defined(CPU_S32K394) || defined(CPU_S32K396) || defined(CPU_S32K388)
#define WTK3_GetCoreID() ((uint8_t)(IP_MSCM->CPXNUM & MSCM_CPXNUM_CPN_MASK))
#elif defined(CPU_S32K356) || defined(CPU_S32K358)
#define WTK3_GetCoreID() ((uint8_t)((IP_MSCM->CPXNUM & MSCM_CPXNUM_CPN_MASK) >> 1))
#else
#error "No platform is selected. At least one platform should be selected."
#endif

// Siul2_Dio_Ip.h included
#if defined(SIUL2_DIO_IP_H)
#define SIUL2_DIO_PIN(Port, Pin)                                                                   \
    (((Pin) < 16) ? PT##Port##_L_HALF : PT##Port##_H_HALF), ((Pin) & 0x0F)
#define SIUL2_DIO_NAMED_PIN(NAME) NAME##_PORT, NAME##_PIN
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

#if defined(DEBUGPIN)

#define DEBUGPINOUT ((&IP_SIUL2->GPDO3)[DEBUGPIN ^ 3])

void Siul2_Port_SetDebugPin(volatile uint8_t *PinReg);
void Siul2_Port_DebugOut(uint8_t Data);

#define LogInit()                                                                                  \
    do {                                                                                           \
        Siul2_Port_SetDebugPin(&DEBUGPINOUT);                                                      \
        IP_SIUL2->MSCR[(DEBUGPIN)] |= SIUL2_MSCR_OBE_MASK;                                         \
    } while (0)

#define LogChar(DATA) Siul2_Port_DebugOut(DATA)
#define LogString(DATA)                                                                            \
    do {                                                                                           \
        for (uint32_t index = 0; (index < ARRAY_SIZE(DATA)); ++index) {                            \
            register uint8_t Data = (DATA)[index];                                                 \
            if (Data) {                                                                            \
                Siul2_Port_DebugOut(Data);                                                         \
            } else {                                                                               \
                break;                                                                             \
            }                                                                                      \
        }                                                                                          \
    } while (0)

#else

#define LogInit()                                                                                  \
    do {                                                                                           \
    } while (0)

#define LogChar   LogInit
#define LogString LogInit

#endif

#endif

// Flexio_Mcl_Ip.h included
#if defined(FLEXIO_MCL_IP_H)
#define Flexio_Pins_Input           (IP_FLEXIO->PIN)
#define Flexio_Pins_Output          (IP_FLEXIO->PINOUTD)
#define Flexio_Pins_Status          (IP_FLEXIO->PINSTAT)
#define Flexio_Pins_OutputEnable    (IP_FLEXIO->PINOUTE)
#define Flexio_Pins_OutputDisable   (IP_FLEXIO->PINOUTDIS)
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
        Flexio_Shifter_Control(Config->ShifterID) |=
            FLEXIO_SHIFTCTL_PINCFG(FLEXIO_PIN_CONFIG_OUTPUT);
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
    TIMER_DECREMENT_FLEXIO              = FLEXIO_TIMER_DECREMENT_CLK_SHIFT_TMR,
    TIMER_DECREMENT_TRG_SHIFT_TMR       = FLEXIO_TIMER_DECREMENT_TRG_SHIFT_TMR,
    TIMER_DECREMENT_PIN_SHIFT_PIN       = FLEXIO_TIMER_DECREMENT_PIN_SHIFT_PIN,
    TIMER_DECREMENT_TRG_SHIFT_TRG       = FLEXIO_TIMER_DECREMENT_TRG_SHIFT_TRG,
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

    bool SetOutput = false;

    if (Config->TimerID >= FLEXIO_TIMCTL_COUNT) {
        return; // Invalid TimerID
    }

    if (Config->UseNextPinForInput && (Config->PinNumber & 0x01U)) {
        // Pin number must be even if UseNextPinForInput is true
        return;
    }

    Flexio_Mcl_Ip_PinConfigType PinConfig = Config->PinOutType;

    if (FLEXIO_PIN_CONFIG_OUTPUT == PinConfig) {
        // Handle error: pin configuration is disabled
        PinConfig = FLEXIO_PIN_CONFIG_BIDIR_OUTPUT;
        SetOutput = true;
    }

    Flexio_Timer_Control(Config->TimerID) =
        FLEXIO_TIMCTL_TIMOD(Config->TimerMode) | FLEXIO_TIMCTL_ONETIM(Config->OneShot) |
        FLEXIO_TIMCTL_PININS(Config->UseNextPinForInput) |
        FLEXIO_TIMCTL_PINPOL(Config->PinPolarity) | FLEXIO_TIMCTL_PINSEL(Config->PinNumber) |
        FLEXIO_TIMCTL_PINCFG(PinConfig) | FLEXIO_TIMCTL_TRGPOL(Config->TriggerPolarity) |
        FLEXIO_TIMCTL_TRGSRC(Config->TriggerSourceType) |
        FLEXIO_TIMCTL_TRGSEL(Config->TriggerSource);
    Flexio_Timer_Config(Config->TimerID) =
        FLEXIO_TIMCFG_TSTART(Config->TimerStartBit) | FLEXIO_TIMCFG_TSTOP(Config->TimerStop) |
        FLEXIO_TIMCFG_TIMENA(Config->TimerEnable) | FLEXIO_TIMCFG_TIMDIS(Config->TimerDisable) |
        FLEXIO_TIMCFG_TIMRST(Config->TimerReset) | FLEXIO_TIMCFG_TIMDEC(Config->TimerDecrement) |
        FLEXIO_TIMCFG_TIMOUT(Config->TimerOutput);
    if (SetOutput) {
        Flexio_Timer_Control(Config->TimerID) |= FLEXIO_TIMCTL_PINCFG(FLEXIO_PIN_CONFIG_OUTPUT);
    }
    if (CompareValue <= 0xFFFFU) {
        Flexio_Timer_Compare(Config->TimerID) = CompareValue;
    }
}

static inline void Flexio_Timer_SetMode(uint8_t TimerID, Flexio_Mcl_Ip_TimerModeType Mode) {
    Flexio_Timer_Control(TimerID) =
        ((Flexio_Timer_Control(TimerID)) & (~FLEXIO_TIMCTL_TIMOD_MASK)) | FLEXIO_TIMCTL_TIMOD(Mode);
}

#endif

// C40_Ip.h included
#if defined(C40_IP_H)
#define C40_WaitForDone()                                                                          \
    do {                                                                                           \
        register volatile uint32_t *pMCRS = &IP_FLASH->MCRS;                                       \
        IP_FLASH->MCR |= FLASH_MCR_EHV_MASK;                                                       \
        while (0 == ((*pMCRS) & FLASH_MCRS_DONE_MASK))                                             \
            ;                                                                                      \
    } while (0)

typedef void (*C40_WaitForDone_Ptr)(void);

#define C40_WaitForDone_Bin                                                                        \
    {0x10, 0xB4, 0x08, 0x4C, 0x23, 0x68, 0x43, 0xF0, 0x01, 0x03, 0x23, 0x60, 0x04, 0x34,           \
     0x00, 0xBF, 0x23, 0x68, 0x03, 0xF4, 0x00, 0x43, 0x00, 0x2B, 0xFA, 0xD0, 0x00, 0xBF,           \
     0x00, 0xBF, 0x5D, 0xF8, 0x04, 0x4B, 0x70, 0x47, 0x00, 0xC0, 0x2E, 0x40}

#endif

// Dma_Ip.h included
#if defined(DMA_IP_DRIVER_H_)

static inline uint32_t Dma_Config_Address(Dma_Ip_LogicChannelTransferListType *pLocList,
                                          uint32_t SourceAddress, uint32_t DestinationAddress) {
    uint32_t LocCount = 0;

    if (((uint32_t)-1U) != SourceAddress) {
        LocCount++;
        pLocList->Param = DMA_IP_CH_SET_SOURCE_ADDRESS;
        pLocList->Value = SourceAddress;
        pLocList++;
    }

    if (((uint32_t)-1U) != DestinationAddress) {
        LocCount++;
        pLocList->Param = DMA_IP_CH_SET_DESTINATION_ADDRESS;
        pLocList->Value = DestinationAddress;
        pLocList++;
    }

    return LocCount;
}

static inline uint32_t Dma_Config_LoopCount(Dma_Ip_LogicChannelTransferListType *pLocList,
                                            uint32_t MinorLoopSize, uint32_t MajorLoopCount) {
    uint32_t LocCount = 0;

    if (MinorLoopSize > 0U) {
        LocCount++;
        pLocList->Param = DMA_IP_CH_SET_MINORLOOP_SIZE;
        pLocList->Value = MinorLoopSize;
        pLocList++;
    }

    if (MajorLoopCount > 0U) {
        LocCount++;
        pLocList->Param = DMA_IP_CH_SET_MAJORLOOP_COUNT;
        pLocList->Value = MajorLoopCount;
        pLocList++;
    }

    return LocCount;
}

static inline uint32_t Dma_Config_TransferSize(Dma_Ip_LogicChannelTransferListType *pLocList,
                                               uint32_t TransferSize, uint32_t MinorLoopSize) {
    uint32_t LocCount = 0;

    if (TransferSize > 0U) {
        LocCount++;
        pLocList->Param = DMA_IP_CH_SET_SOURCE_TRANSFER_SIZE;
        pLocList->Value = TransferSize;
        pLocList++;
    }

    if (MinorLoopSize > 0U) {
        LocCount++;
        pLocList->Param = DMA_IP_CH_SET_DESTINATION_TRANSFER_SIZE;
        pLocList->Value = TransferSize;
        pLocList++;
    }

    return LocCount;
}

static inline uint32_t Dma_Config_SourceOffset(Dma_Ip_LogicChannelTransferListType *pLocList,
                                               int32_t Offset, int32_t LastAdj, uint32_t EleSize,
                                               uint32_t Modulo) {

    pLocList->Param = DMA_IP_CH_SET_SOURCE_SIGNED_OFFSET;
    pLocList->Value = Offset;
    pLocList++;

    pLocList->Param = DMA_IP_CH_SET_SOURCE_SIGNED_LAST_ADDR_ADJ;
    pLocList->Value = LastAdj;
    pLocList++;

    pLocList->Param = DMA_IP_CH_SET_SOURCE_TRANSFER_SIZE;
    pLocList->Value = EleSize;
    pLocList++;

    pLocList->Param = DMA_IP_CH_SET_SOURCE_MODULO;
    pLocList->Value = Modulo;
    pLocList++;

    return 4;
}

static inline uint32_t Dma_Config_DestinationOffset(Dma_Ip_LogicChannelTransferListType *pLocList,
                                                    int32_t Offset, int32_t LastAdj,
                                                    uint32_t EleSize, uint32_t Modulo) {

    pLocList->Param = DMA_IP_CH_SET_DESTINATION_SIGNED_OFFSET;
    pLocList->Value = Offset;
    pLocList++;

    pLocList->Param = DMA_IP_CH_SET_DESTINATION_SIGNED_LAST_ADDR_ADJ;
    pLocList->Value = LastAdj;
    pLocList++;

    pLocList->Param = DMA_IP_CH_SET_DESTINATION_TRANSFER_SIZE;
    pLocList->Value = EleSize;
    pLocList++;

    pLocList->Param = DMA_IP_CH_SET_DESTINATION_MODULO;
    pLocList->Value = Modulo;
    pLocList++;

    return 4;
}

static inline uint32_t Dma_Control_EnMajorInterrupt(Dma_Ip_LogicChannelTransferListType *pLocList,
                                                    bool                                 enable) {
    pLocList->Param = DMA_IP_CH_SET_CONTROL_EN_MAJOR_INTERRUPT;
    pLocList->Value = enable ? 1U : 0U;
    return 1;
}

static inline uint32_t Dma_Control_DisableAutoRequest(Dma_Ip_LogicChannelTransferListType *pLocList,
                                                      bool disable) {
    pLocList->Param = DMA_IP_CH_SET_CONTROL_DIS_AUTO_REQUEST;
    pLocList->Value = disable ? 1U : 0U;
    return 1;
}

#define Dma_Start(Channel) Dma_Ip_SetLogicChannelCommand(Channel, DMA_IP_CH_SET_SOFTWARE_REQUEST)

#define Dma_WaitDone(Channel)                                                                      \
    do {                                                                                           \
        Dma_Ip_LogicChannelStatusType t_GetChannelStatus;                                          \
        do {                                                                                       \
            Dma_Ip_GetLogicChannelStatus(Channel, &t_GetChannelStatus);                            \
        } while (!t_GetChannelStatus.Done);                                                        \
    } while (0)

#endif

#if defined(GMAC_IP_H)
/* Code from Eth_43_GMAC_Ipw_SelectPhyInterface */
static inline Gmac_Ip_StatusType Gmac_Ip_Init_With_Phy(uint8                      Instance,
                                                       const Gmac_CtrlConfigType *Config) {
#define ETH_IPW_IP_EMAC (0U)
#define ETH_IPW_IP_GMAC (1U)

    Gmac_Ip_MiiModeType ModeSelect = Config->Gmac_pCtrlConfig->MiiMode;
#if (ETH_IPW_IP_EMAC == GMAC_IP_FEATURE_ORIGIN)
    if (GMAC_MII_MODE == ModeSelect) {
        IP_DCM_GPR->DCMRWF1 = (IP_DCM_GPR->DCMRWF1 & ~DCM_GPR_DCMRWF1_MAC_CONF_SEL_MASK) |
                              DCM_GPR_DCMRWF1_MAC_CONF_SEL(0U);
    } else if (GMAC_RMII_MODE == ModeSelect) {
#if defined(S32K396) || defined(S32K394) || defined(S32K376) || defined(S32K374)
        IP_DCM_GPR->DCMRWF1 = (IP_DCM_GPR->DCMRWF1 & ~DCM_GPR_DCMRWF1_MAC_CONF_SEL_MASK) |
                              DCM_GPR_DCMRWF1_MAC_CONF_SEL(1U);
#else
        IP_DCM_GPR->DCMRWF1 = (IP_DCM_GPR->DCMRWF1 & ~DCM_GPR_DCMRWF1_MAC_CONF_SEL_MASK) |
                              DCM_GPR_DCMRWF1_MAC_CONF_SEL(2U);
#endif
    }
#endif
#if (ETH_IPW_IP_GMAC == GMAC_IP_FEATURE_ORIGIN)
    if (GMAC_MII_MODE == ModeSelect) {
        IP_DCM_GPR->DCMRWF1 = (IP_DCM_GPR->DCMRWF1 & ~DCM_GPR_DCMRWF1_MAC_CONF_SEL_MASK) |
                              DCM_GPR_DCMRWF1_MAC_CONF_SEL(0U);
    } else if (GMAC_RMII_MODE == ModeSelect) {
        IP_DCM_GPR->DCMRWF1 = (IP_DCM_GPR->DCMRWF1 & ~DCM_GPR_DCMRWF1_MAC_CONF_SEL_MASK) |
                              DCM_GPR_DCMRWF1_MAC_CONF_SEL(2U);
    }
#if FEATURE_GMAC_RGMII_EN
    else {
#if defined(S32K388)
        /* Enables the MAC_TX_RMII_CLK loopback and select RGMII mode. */
        IP_DCM_GPR->DCMRWF1 = (IP_DCM_GPR->DCMRWF1 & ~DCM_GPR_DCMRWF1_MAC_CONF_SEL_MASK) |
                              DCM_GPR_DCMRWF1_MAC_CONF_SEL(1U) |
                              DCM_GPR_DCMRWF1_MAC_TX_RMII_CLK_LPBCK_EN(1U);
#else
        /* TODO: replace setting bit 31 with macro when header file S32K358_DCM_GPR.h is updated following new version of RM. */
        IP_DCM_GPR->DCMRWF1 = (IP_DCM_GPR->DCMRWF1 & ~DCM_GPR_DCMRWF1_MAC_CONF_SEL_MASK) |
                              DCM_GPR_DCMRWF1_MAC_CONF_SEL(1U) | ((uint32)1U << 31U);
#endif
    }
#endif
#endif
    return Gmac_Ip_Init(Instance, Config);
}

#define Gmac_Ip_Init(Instance, Config) Gmac_Ip_Init_With_Phy(Instance, Config)
#endif

#if defined(CRYPTO_43_HSE_H)

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

extern hseStatus_t Hse_Ip_GetHseStatus(uint8_t u8MuInstance);

typedef struct {
    bool                        isUsed;
    Crypto_PrimitiveInfoType    PrimitiveInfo;
    Crypto_JobPrimitiveInfoType JobPrimitiveInfo;
    Crypto_JobType              Job;
} Crypto_Task;

typedef uint8_t Crypto_Task_ID;

#define Crypto_Format Crypto_43_HSE_Exts_FormatKeyCatalogs

void Crypto_Task_Init(uint32_t TaskCount, Crypto_Task *pTasks);

Crypto_Task_ID Crypto_Task_GetFreeSlot(void);

void Crypto_Task_Release(Crypto_Task_ID Id);

Std_ReturnType Crypto_Task_SyncRequest(uint32_t ObjectId, Crypto_Task_ID Id);

Std_ReturnType Crypto_Task_AsyncRequest(uint32_t ObjectId, Crypto_Task_ID Id);

Crypto_JobStateType Crypto_Task_GetResponse(Crypto_Task_ID Id);

void Crypto_Task_GetRandomBuffer(Crypto_Task_ID Id, uint8_t Level, uint8_t *pBuffer,
                                 uint32_t *pSize);

void Crypto_Task_KeySetValid(Crypto_Task_ID Id, uint32_t KeyElement);

void Crypto_Task_KeySetInvalid(Crypto_Task_ID Id, uint32_t KeyElement);

#elif defined(HSE_IP_H)

// Hse_Ip.h included
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

#define HSE_SRV_RSP_BUSY ((hseSrvResponse_t)0x0UL)

typedef struct {
    union {
        hseAttrCapabilities_t Hse_AttrCapabilities;
        hseAttrMUConfig_t     Hse_MuConfig;
        hseAttrFwVersion_t    Hse_FwVersion;
    } Data;
    hseSrvDescriptor_t SrvDescriptor;
} HSE_Context;

typedef struct {
    bool             isUsed;
    Hse_Ip_ReqType   SrvRequest;
    hseSrvResponse_t SrvResponse;
} HSE_Task;

typedef uint8_t Hse_Task_ID;

#define Hse_WaitForDone()                                                                          \
    while ((IP_MC_ME->PRTN0_CORE2_STAT & MC_ME_PRTN0_CORE2_STAT_WFI_MASK) == 0)

void Hse_Task_Init(uint32_t TaskCount, HSE_Task *pHSE_Task, HSE_Context *pHSEContext);

Hse_Task_ID Hse_Task_GetFreeSlot(void);

void Hse_Task_Release(Hse_Task_ID Id);

hseSrvResponse_t Hse_Task_MasterRequest(Hse_Task_ID Id, uint8_t u8MuInstance, uint32_t u32Timeout);

hseSrvResponse_t Hse_Task_SyncRequest(Hse_Task_ID Id, uint8_t u8MuInstance, uint32_t u32Timeout);

hseSrvResponse_t Hse_Task_AsyncRequest(Hse_Task_ID Id, uint8_t u8MuInstance, bool useInterrupt);

hseSrvResponse_t Hse_Task_GetResponse(Hse_Task_ID Id, uint8_t u8MuInstance);

hseAttrMUConfig_t *Hse_GetMuConfig(Hse_Task_ID Id);

hseAttrCapabilities_t *Hse_GetCapabilities(Hse_Task_ID Id);

hseAttrFwVersion_t *Hse_GetFwVersion(Hse_Task_ID Id);

bool Hse_GetRandomBuffer(Hse_Task_ID Id, uint8_t Level, uint8_t *pBuffer, uint32_t Size);

void Hse_ActivatePassiveBlock(Hse_Task_ID Id);

#endif

#if defined(WKPU_IP_H)
#define WKPU_SRC_INNER(X) (X)
#define WKPU_SRC_OUTER(X) ((X) + 4)
#endif

typedef struct {
    uint16_t CrystalFrequency : 16;
    uint16_t Reserved : 4;
    uint16_t EOCV : 8;
    uint16_t GMSEL : 4;
    uint32_t MagicNumber;
} FXOSCConfig_Type;

typedef struct {
    uint32_t Value;
    uint32_t Key;
} DCFRecord_Type;

typedef struct {
    uint64_t         HSE_UsageFlag;     /* Offset : 0x00 */
    uint64_t         Reserved1[7];      /* Offset : 0x08 */
    uint64_t         ChipID;            /* Offset : 0x40 */
    uint64_t         Reserved2;         /* Offset : 0x48 */
    FXOSCConfig_Type FXOSC_Config;      /* Offset : 0x50 */
    uint64_t         Partial_ABSwap;    /* Offset : 0x58 */
    uint64_t         JDCClkDisable;     /* Offset : 0x60 */
    uint64_t         Reserved3[3];      /* Offset : 0x68 */
    uint8_t          DebugPassword[16]; /* Offset : 0x80 */
    uint64_t         Reserved4[46];     /* Offset : 0x90 */
    uint64_t
        DebugAuthFlag; /* Offset : 0x200 This flag indicates whether changing the secure debug authentication mode from Password to challenge Response (CR) */
    uint64_t
        IVT_XRDC_GMAC; /* Offset : 0x208 This flag indicates whether enabling the IVT AUTH feature */
    uint64_t       LCSlots[6][2];        /* Offset : 0x210 */
    uint64_t       Reserved5[32];        /* Offset : 0x270 */
    uint8_t        HSEDebugPassword[16]; /* Offset : 0x370 */
    uint64_t       Reserved6[112];       /* Offset : 0x380 */
    uint64_t       DCF_Start;            /* Offset : 0x700 */
    DCFRecord_Type DCF_Records[671];     /* Offset : 0x708 */
} UTEST_Type, *UTEST_MemMapPtr;

/** Peripheral UTEST base pointer */
#define IP_UTEST_BASE (0x1B000000u)
/** Peripheral UTEST base pointer */
#define IP_UTEST ((UTEST_Type *)IP_UTEST_BASE)

#define HSE_UNUSED_FLAG     (0xFFFFFFFFFFFFFFFFULL)
#define PARTIAL_ABSWAP_FLAG (0xDABADABADABADABAULL)
#define DCF_START_FLAG      (0x0000000005AA55AFULL)
#define LC_SLOT_ERASED      (0xFFFFFFFFFFFFFFFFULL)
#define LC_SLOT_ACTIVE      (0x55AA50AF55AA50AFULL)

#define LC_SLOT_MCU_PRODUCTION       (0x0U)
#define LC_SLOT_CUSTOMER_DELIVERY    (0x1U)
#define LC_SLOT_OEM_PRODUCTION       (0x2U)
#define LC_SLOT_IN_FIELD             (0x3U)
#define LC_SLOT_PRE_FAILURE_ANALYSIS (0x4U)
#define LC_SLOT_FAILURE_ANALYSIS     (0x5U)
#define LC_SLOT_VALID                (0x0U)
#define LC_SLOT_INVALID              (0x1U)

#define DCF_KEY_UTEST_MISC                                                                         \
    (0x00100004UL) /* If CoreClock > 160MHz HSE_CLK_MODE_AND_GSKT_CTRL should be set. HSE Reference Manual */
#define DCF_KEY_RESET_PAD_DEDICATED (0x00100008UL)
#define DCF_KEY_DEST_RST_ESC        (0x0010000CUL)
#define DCF_KEY_SDI0                (0x00100010UL)
#define DCF_KEY_SDI1                (0x00100014UL)
#define DCF_KEY_SDI2                (0x00100018UL)
#define DCF_KEY_SDI3                (0x0010001CUL)
#define DCF_KEY_SDI4                (0x00100020UL)
#define DCF_KEY_SDI5                (0x00100024UL)
#define DCF_KEY_SDI6                (0x00100028UL)
#define DCF_KEY_SDI7                (0x0010002CUL)
#define DCF_KEY_SDI8                (0x00100030UL)
#define DCF_KEY_SDI9                (0x00100034UL)
#define DCF_KEY_SDI10               (0x00100038UL)
#define DCF_KEY_SDI11               (0x0010003CUL)
#define DCF_KEY_SDI12               (0x00100040UL)
#define DCF_KEY_SDI13               (0x00100044UL)
#define DCF_KEY_SDI14               (0x00100048UL)
#define DCF_KEY_SDI15               (0x0010004CUL)
#define DCF_KEY_INSTANCEID          (0x00100050UL)

static inline uint8_t *UTEST_GetDebugPassword(void) {
    if (IP_UTEST->HSE_UsageFlag == HSE_UNUSED_FLAG) {
        return &IP_UTEST->DebugPassword[0];
    } else {
        return &IP_UTEST->HSEDebugPassword[0];
    }
}

static inline uint8_t UTEST_GetCurrentLifeCycle(void) {
    for (uint8_t index = LC_SLOT_MCU_PRODUCTION; index <= LC_SLOT_FAILURE_ANALYSIS; ++index) {
        if (IP_UTEST->LCSlots[index][LC_SLOT_VALID] == LC_SLOT_ACTIVE) {
            return index;
        }
    }
    return LC_SLOT_IN_FIELD; // Default to IN_FIELD if no active slot found
}

static inline DCFRecord_Type *UTEST_GetFreeDCFRecord(void) {
    for (uint32_t index = 0; index < ARRAY_SIZE(IP_UTEST->DCF_Records); index++) {
        if ((IP_UTEST->DCF_Records[index].Key == 0xFFFFFFFFUL) &&
            (IP_UTEST->DCF_Records[index].Value == 0xFFFFFFFFUL)) {
            return &IP_UTEST->DCF_Records[index];
        }
    }
    return NULL;
}

typedef struct {
    uint32_t  Header;                   /* IVT_HEADER_MAGIC */
    uint32_t  BootConfig;               /* Boot Configuration Word */
    uint32_t  Reserved08;               /* Reserved */
    uint32_t *CM7_0_StartAddress;       /* Start address of application on CM7_0 core */
    uint32_t  Reserved10;               /* Reserved */
    uint32_t *CM7_1_StartAddress;       /* Start address of application on CM7_1 core */
    uint32_t  Reserved18;               /* Reserved */
    uint32_t *CM7_2_StartAddress;       /* Start address of application on CM7_2 core */
    uint32_t *XRDCConfig_StartAddress;  /* Address of XRDC configuration data */
    uint32_t *LCConfig;                 /* Address of LC configuration */
    uint32_t *CM7_3_StartAddress;       /* Start address of application on CM7_3 core */
    uint32_t *HseFwHeader_StartAddress; /* Start address of HSE-FW image FW_IMG */
    uint32_t *AppBL_StartAddress;       /* Start address of application bootloader */
    uint32_t  Reserved34[3];            /* Reserved */
    uint32_t *AppCore_StartAddress; /* Start address of Application Core for Secure Recovery Mode */
    uint32_t  AppCore_Length;       /* Length of Application Core for Secure Recovery Mode */
    uint8_t   Reserved[156];        /* Reserved */
    uint8_t   RandomVector[12];     /* Vector Value used in calc of GMAC */
    uint8_t   GMAC[16];             /* GMAC */
} IVT_Type, *IVT_MemMapPtr;

#define IVT_HEADER_MAGIC         (0x5AA55AA5UL) /* Magic number for IVT header */
#define IVT_EMPTY_PTR            (0xFFFFFFFFUL) /* Empty pointer value in IVT */
#define LC_CONFIG_OEM_PRODUCTION (0xDADADADAUL) /* LC configuration for OEM production */
#define LC_CONFIG_IN_FIELD       (0xBABABABAUL) /* LC configuration for in-field */

#define IVT_BCW_CM7_0_ENABLE            (0x00000001UL)
#define IVT_BCW_CM7_1_ENABLE            (0x00000002UL)
#define IVT_BCW_CM7_2_ENABLE            (0x00000004UL)
#define IVT_BCW_CM7_3_ENABLE            (0x00000100UL)
#define IVT_BCW_SECURE_BOOT_ENABLE      (0x00000008UL)
#define IVT_BCW_PLL_ENABLE              (0x00000010UL)
#define IVT_BCW_SWT0_ENABLE             (0x00000020UL)
#define IVT_BCW_DISABLE_SECURE_RECOVERY (0x00000040UL)
#define IVT_BCW_RESET_RECOVERY          (0x00000080UL)
#define IVT_BCW_FW_USAGE_FLAG_PROGRAM   (0x00000200UL)
#define IVT_BCW_HSE_BACKUP_DISABLE      (0x00000400UL)

#if defined(__cplusplus)
}
#endif

#endif // LIBWTK3_H
