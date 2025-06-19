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

static volatile uint8_t *pDebugPin;

void Siul2_Port_SetDebugPin(volatile uint8_t *PinReg) {
    pDebugPin  = PinReg;
    *pDebugPin = 1; // Set pin to high
}

void Siul2_Port_DebugOut(uint8_t Data) {
    register volatile uint8_t *pOut   = pDebugPin;
    register uint32_t          signal = (0x300 | (Data)) << 1;
    for (register uint32_t index = 0; index < 11; ++index, signal >>= 1) {
        *pOut = (signal & 1);
        __asm("nop");__asm("nop");__asm("nop");__asm("nop");
    }
}
