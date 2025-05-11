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

// Hse_Ip.h included
#if defined(HSE_IP_H)

#define MU_ADMIN_CHANNEL_U8 ((uint8)0U)
typedef union
{
    hseStatus_t status;
    struct
    {
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

Hse_Status Hse_GetStatus(uint8_t u8MuInstance);

#endif

#if defined(__cplusplus)
}
#endif

#endif // LIBWTK3_H
