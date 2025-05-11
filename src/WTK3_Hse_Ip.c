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

#define HSE_IP_H
typedef uint16_t hseStatus_t;

#include "libwtk3.h"

extern hseStatus_t Hse_Ip_GetHseStatus(uint8_t u8MuInstance);


Hse_Status Hse_GetStatus(uint8_t u8MuInstance) {
	Hse_Status retval;
	retval.status = Hse_Ip_GetHseStatus(u8MuInstance);
	return retval;
}
