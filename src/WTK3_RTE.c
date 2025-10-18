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

typedef struct {
    uint32_t CSRr;
    uint32_t RVR;
    uint32_t CVR;
    uint32_t CALIB;
} S32_SysTick_Type, *S32_SysTick_MemMapPtr;

#define S32_SysTick_BASE                         (0xE000E010u)
#define S32_SysTick                              ((S32_SysTick_Type *)S32_SysTick_BASE)
#define S32_SysTick_CSR_ENABLE_MASK              0x1u
#define S32_SysTick_CSR_ENABLE_SHIFT             0u
#define S32_SysTick_CSR_ENABLE(x)                (((uint32_t)(((uint32_t)(x))<<S32_SysTick_CSR_ENABLE_SHIFT))&S32_SysTick_CSR_ENABLE_MASK)
#define S32_SysTick_CSR_TICKINT_MASK             0x2u
#define S32_SysTick_CSR_TICKINT_SHIFT            1u
#define S32_SysTick_CSR_TICKINT(x)               (((uint32_t)(((uint32_t)(x))<<S32_SysTick_CSR_TICKINT_SHIFT))&S32_SysTick_CSR_TICKINT_MASK)
#define S32_SysTick_CSR_CLKSOURCE_MASK           0x4u
#define S32_SysTick_CSR_CLKSOURCE_SHIFT          2u
#define S32_SysTick_CSR_CLKSOURCE(x)             (((uint32_t)(((uint32_t)(x))<<S32_SysTick_CSR_CLKSOURCE_SHIFT))&S32_SysTick_CSR_CLKSOURCE_MASK)
#define S32_SysTick_RVR_RELOAD_MASK              0xFFFFFFu
#define S32_SysTick_RVR_RELOAD_SHIFT             0u
#define S32_SysTick_RVR_RELOAD(x)                (((uint32_t)(((uint32_t)(x))<<S32_SysTick_RVR_RELOAD_SHIFT))&S32_SysTick_RVR_RELOAD_MASK)
#define S32_SysTick_CVR_CURRENT_MASK             0xFFFFFFu
#define S32_SysTick_CVR_CURRENT_SHIFT            0u
#define S32_SysTick_CVR_CURRENT(x)               (((uint32_t)(((uint32_t)(x))<<S32_SysTick_CVR_CURRENT_SHIFT))&S32_SysTick_CVR_CURRENT_MASK)

typedef struct
{
    uint32_t counterId;
    uint32_t counterFrequency;
} OsIf_ConfigType;

extern const OsIf_ConfigType *const OsIf_apxPredefinedConfig[];

typedef void (*IntCtrl_Ip_IrqHandlerType)(void);
void IntCtrl_Ip_InstallHandler(int32_t eIrqNumber,
                               const IntCtrl_Ip_IrqHandlerType pfNewHandler,
                               IntCtrl_Ip_IrqHandlerType* const pfOldHandler);
#define SysTick_IRQn (-1)

static volatile uint32_t __attribute__((section(".dtcm_data"))) gCurrentTick;
static IntCtrl_Ip_IrqHandlerType __attribute__((section(".dtcm_data"))) pSysTick = 0;

void __attribute__((section(".itcm_text"), optimize("O1"))) WTK3_System_Timer_IncCounter(void) {
    ++gCurrentTick;
    if (pSysTick) {
        pSysTick();
    }
}

uint32_t __attribute__((section(".itcm_text"), optimize("O1"))) WTK3_System_Timer_GetCounter(void) {
    return gCurrentTick;
}

void WTK3_System_Timer_Init(void) {
    S32_SysTick->CSRr = S32_SysTick_CSR_ENABLE(0u);
    S32_SysTick->RVR = S32_SysTick_RVR_RELOAD(OsIf_apxPredefinedConfig[0]->counterFrequency / 1000);
    S32_SysTick->CVR = S32_SysTick_CVR_CURRENT(0U);
    S32_SysTick->CSRr = S32_SysTick_CSR_ENABLE(1u) | S32_SysTick_CSR_TICKINT(1u) | S32_SysTick_CSR_CLKSOURCE(1u);
    IntCtrl_Ip_InstallHandler(SysTick_IRQn, WTK3_System_Timer_IncCounter, &pSysTick);
    gCurrentTick = 0;
}
