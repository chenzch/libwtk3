#!/bin/bash

MexFile="$1"

BaseRoot="$(dirname "$MexFile")"

FindModule() {
    local pattern="<instance name=\\\"$1\\\""
    grep -q "$pattern" "$MexFile"
}

FileExist() {
    local file_pattern="$1"
    local matching_files=($(ls $file_pattern 2>/dev/null))
    [ ${#matching_files[@]} -gt 0 ]
}

FindProcessor() {
    local pattern="processor=\"$processor\""
    grep "<processor>" "$MexFile" | tr '<>' '  ' | awk '{ print $2}'
}

PrintMPUInfo() {
    for file in $BaseRoot/generate/src/Mpu_M7_Ip_*fg.c; do
        if [ -f "$file" ]; then
            start_line=$(grep -n "const Mpu_M7_Ip_RegionConfigType" "$file" | cut -d: -f1)
            start_line=$((start_line + 1))
            end_line=$(sed -n "${start_line},\$p" "$file" | grep -n "};" | head -n 1 | cut -d: -f1)
            end_line=$((end_line + start_line - 1))
            extracted_content=$(sed -n "${start_line},${end_line}p" "$file")
            cleaned_content=$(echo "$extracted_content" | sed 's|/\*.*\*/||g')

            buffer=()
            line_count=0

            if [ "$start_line" -gt 1 ]; then
                echo "    /* MPU Region Configuration in $file */"
                echo "    /*        ID,  StartAddr,  EndAddress,Size, MemoryType              , AccessRights            , Outer Cache Policy                  , Inner Cache Policy                  , SubRegion , Shareable */"
                echo "$cleaned_content" | while IFS= read -r line; do
                    line="${line#"${line%%[![:space:]]*}"}"
                    line="${line//UL,/}"
                    line="${line//U,/}"
                    if [[ "$line" =~ ^[{}] ]]; then
                        continue
                    fi

                    buffer+=("$line")
                    line_count=$((line_count + 1))

                    if [ $line_count -eq 9 ]; then
                        num1=$(echo "${buffer[0]}" | sed 's/[^0-9]*//g')
                        printf "    /* Region %2d, " "$num1"

                        num2=$(echo "${buffer[1]}" | sed 's/[^0-9]*//g')
                        printf "0x%08X - " "$num2"

                        num3=$(echo "${buffer[2]}" | sed 's/[^0-9]*//g')

                        size=$((num3 - num2 + 1))
                        sizenum=0
                        num3_calc=1
                        for i in {0..31}; do
                            num3_calc=$((num3_calc * 2))
                            if (( (2 << i) >= size )); then
                                sizenum=$i
                                break
                            fi
                        done

                        num3_calc=$((num3_calc - 1))

                        if ((sizenum == 0)); then
                            printf "0x%08X, Err, " "$num3"
                        else
                            printf "0x%08X, " "$num3_calc"
                            printf " %-2d, " "$sizenum"
                        fi

                        for i in {3..6}; do
                            buffer[$i]=$(echo "${buffer[$i]}" | sed 's/MPU_M7_//;s/,.*$//')
                        done
                        printf "%-24s, " "${buffer[3]}"
                        printf "%-24s, " "${buffer[4]}"
                        if [[ "${buffer[3]}" == "MEM_NORMAL_CACHEABLE" ]]; then
                            printf "%-36s, " "${buffer[5]}"
                            printf "%-36s, " "${buffer[6]}"
                        else
                            printf "%-36s, %-36s, "
                        fi

                        num8=$(echo "${buffer[7]}" | sed 's/[^0-9]*//g')
                        printf "0b%08d, " "$(echo "obase=2; $num8" | bc | awk '{printf "%08d", $0}')"

                        if [[ "${buffer[8]}" =~ FALSE ]]; then
                            printf "FALSE    "
                        else
                            printf "TRUE     "
                        fi

                        printf " */\n"

                        buffer=()
                        line_count=0
                    fi
                done
            fi
        fi
    done
}

# Header file processing
echo "// Header files"
if FindModule "BaseNXP"; then
    echo "#include \"Mcal.h\""
    echo "#include \"OsIf.h\""
fi

if FindModule "Mcu"; then
    echo "#include \"Mcu.h\""
else
    echo "#include \"Clock_Ip.h\""
fi

if FindModule "Port"; then
    echo "#include \"Port.h\""
else
    if FindModule "Siul2_Port"; then
        echo "#include \"Siul2_Port_Ip.h\""
        echo "#include \"Tspc_Port_Ip.h\""
    fi
fi

if FindModule "IPV_Mpu_M7_Ip"; then
    echo "#include \"Mpu_M7_Ip.h\""
fi

if FindModule "Dio"; then
    echo "#include \"Dio.h\""
else
    if FindModule "Siul2_Dio"; then
        echo "#include \"Siul2_Dio_Ip.h\""
    fi
fi

if FindModule "Siul2_Icu"; then
    echo "#include \"Siul2_Icu_Ip.h\""
fi

if FindModule "POWER"; then
    echo "#include \"Power_Ip.h\""
fi

if FindModule "Dma_Ip"; then
    echo "#include \"Dma_Ip.h\""
fi

if FindModule "Rm"; then
    echo "#include \"CDD_Rm.h\""
fi

if FindModule "Flexio_Mcl_Ip"; then
    echo "#include \"Flexio_Mcl_Ip.h\""
fi

if FindModule "Lpuart_Uart"; then
    echo "#include \"Lpuart_Uart_Ip.h\""
fi

if FindModule "C40_Ip"; then
    echo "#include \"C40_Ip.h\""
fi

if FindModule "Cache_Ip"; then
    echo "#include \"Cache_Ip.h\""
fi

if FindModule "Wkpu"; then
    echo "#include \"Wkpu_Ip.h\""
fi

if FindModule "Lpi2c"; then
    echo "#include \"Lpi2c_Ip.h\""
    echo "#include \"Lpi2c_Ip_Irq.h\""
fi

if FindModule "Gmac"; then
    echo "#include \"Gmac_Ip.h\""
fi

if FindModule "Crypto_43_HSE"; then
    echo "#include \"Crypto_43_HSE.h\""
    echo "#include \"Crypto_43_HSE_Util.h\""
    echo "#include \"Hse_Ip_Cfg.h\""
else
    if FindModule "Hse"; then
        echo "#include \"Hse_Ip.h\""
    fi
fi

if FindModule "Platform"; then
    echo "#include \"Platform.h\""
else
    if FindModule "IntCtrl_Ip"; then
        echo "#include \"IntCtrl_Ip.h\""
    fi
fi

echo "#include \"libwtk3.h\""
echo
echo "#if !defined(NDEBUG)"
echo "#include \"Devassert.h\""
echo "#endif /* #if !defined(NDEBUG) */"
echo


if FindModule "Crypto_43_HSE"; then
    if FileExist "$BaseRoot/generate/include/Crypto_43_HSE_*fg.h"; then
        for ObjectId in $(grep -h '^#define CryptoConf_CryptoDriverObject_.*' $BaseRoot/generate/include/Crypto_43_HSE_*fg.h | awk '{ print $2 }'); do
            echo "#define ObjectId_${ObjectId/CryptoConf_CryptoDriverObject_/} $ObjectId"
        done
        for KeyElement in $(grep -h '^#define CryptoConf_CryptoKeyElement_.*' $BaseRoot/generate/include/Crypto_43_HSE_*fg.h | awk '{ print $2 }'); do
            echo "#define KeyElement_${KeyElement/CryptoConf_CryptoKeyElement_/} $KeyElement"
        done
    fi
else
    if FindModule "Hse"; then
        echo "#define HSE_MAX_TASK_COUNT 4

#define CRYPTO_43_HSE_START_SEC_VAR_CLEARED_UNSPECIFIED_NO_CACHEABLE
#include \"Crypto_43_HSE_MemMap.h\"

static HSE_Context gHSEContext[HSE_MAX_TASK_COUNT];

#define CRYPTO_43_HSE_STOP_SEC_VAR_CLEARED_UNSPECIFIED_NO_CACHEABLE
#include \"Crypto_43_HSE_MemMap.h\""
    fi
fi

if FindModule "Platform"; then
    if FindModule "Crypto_43_HSE"; then
        echo "ISR(Mu_Ip_Mu0_OredRx_Isr);

#if (HSE_IP_NUM_OF_MU_INSTANCES > 1U)
ISR(Mu_Ip_Mu1_OredRx_Isr);
#endif /* (HSE_IP_NUM_OF_MU_INSTANCES > 1U) */
"
    fi
else
    if FindModule "IntCtrl_Ip"; then
        if FindModule "Siul2_Icu"; then
            echo "#if ((defined SIUL2_ICU_IRQ_CH_0_ISR_USED) || (defined SIUL2_ICU_IRQ_CH_1_ISR_USED) || \\
     (defined SIUL2_ICU_IRQ_CH_2_ISR_USED) || (defined SIUL2_ICU_IRQ_CH_3_ISR_USED) || \\
     (defined SIUL2_ICU_IRQ_CH_4_ISR_USED) || (defined SIUL2_ICU_IRQ_CH_5_ISR_USED) || \\
     (defined SIUL2_ICU_IRQ_CH_6_ISR_USED) || (defined SIUL2_ICU_IRQ_CH_7_ISR_USED))
ISR(SIUL2_EXT_IRQ_0_7_ISR);
#endif

#if ((defined SIUL2_ICU_IRQ_CH_8_ISR_USED) || (defined SIUL2_ICU_IRQ_CH_9_ISR_USED) || \\
     (defined SIUL2_ICU_IRQ_CH_10_ISR_USED) || (defined SIUL2_ICU_IRQ_CH_11_ISR_USED) || \\
     (defined SIUL2_ICU_IRQ_CH_12_ISR_USED) || (defined SIUL2_ICU_IRQ_CH_13_ISR_USED) || \\
     (defined SIUL2_ICU_IRQ_CH_14_ISR_USED) || (defined SIUL2_ICU_IRQ_CH_15_ISR_USED))
ISR(SIUL2_EXT_IRQ_8_15_ISR);
#endif

#if ((defined SIUL2_ICU_IRQ_CH_16_ISR_USED) || (defined SIUL2_ICU_IRQ_CH_17_ISR_USED) || \\
     (defined SIUL2_ICU_IRQ_CH_18_ISR_USED) || (defined SIUL2_ICU_IRQ_CH_19_ISR_USED) || \\
     (defined SIUL2_ICU_IRQ_CH_20_ISR_USED) || (defined SIUL2_ICU_IRQ_CH_21_ISR_USED) || \\
     (defined SIUL2_ICU_IRQ_CH_22_ISR_USED) || (defined SIUL2_ICU_IRQ_CH_23_ISR_USED))
ISR(SIUL2_EXT_IRQ_16_23_ISR);
#endif

#if ((defined SIUL2_ICU_IRQ_CH_24_ISR_USED) || (defined SIUL2_ICU_IRQ_CH_25_ISR_USED) || \\
     (defined SIUL2_ICU_IRQ_CH_26_ISR_USED) || (defined SIUL2_ICU_IRQ_CH_27_ISR_USED) || \\
     (defined SIUL2_ICU_IRQ_CH_28_ISR_USED) || (defined SIUL2_ICU_IRQ_CH_29_ISR_USED) || \\
     (defined SIUL2_ICU_IRQ_CH_30_ISR_USED) || (defined SIUL2_ICU_IRQ_CH_31_ISR_USED))
ISR(SIUL2_EXT_IRQ_24_31_ISR);
#endif"
        fi
    fi
fi


echo
echo "// Initialization"
echo "void wtk3_init(void) {"
# Initialization processing
if FindModule "BaseNXP"; then
    echo "    OsIf_SuspendAllInterrupts();"
    echo "    OsIf_Init(NULL_PTR);"
fi

if FindModule "Crypto_43_HSE"; then
    echo
else
    if FindModule "Hse"; then
        echo "    {
        Hse_Status status;
        do {
            status.status = Hse_Ip_GetHseStatus(0);
#if !defined(NDEBUG)
            DevAssert(status.B.InitOK);
            DevAssert(status.B.RNGInitOK);
#endif /* #if !defined(NDEBUG) */
        } while(!(status.B.InitOK && status.B.RNGInitOK));
    }"
    fi
fi

if FindModule "Mcu"; then
    McuConfig="NULL_PTR"
    if FileExist "$BaseRoot/generate/include/Mcu_*fg.h"; then
        McuConfig=$(grep -h '^extern const Mcu_ConfigType .*;' $BaseRoot/generate/include/Mcu_*fg.h | tr ';' ' ' | awk '{ print $4 }');
        McuConfig="&$McuConfig"
    fi
    ClockConfig="0"
    if FileExist "$BaseRoot/generate/include/Mcu_*fg.h"; then
        ClockConfig=$(grep -h '#define .* ((Mcu_ClockType)0U)' $BaseRoot/generate/include/Mcu_*fg.h | awk '{ print $2 }' | head -n 1);
        ClockConfig="$ClockConfig"
    fi
    ModeConfig="0"
    if FileExist "$BaseRoot/generate/include/Mcu_*fg.h"; then
        ModeConfig=$(grep -h '#define .* ((Mcu_ModeType)0U)' $BaseRoot/generate/include/Mcu_*fg.h | awk '{ print $2 }' | head -n 1);
        ModeConfig="$ModeConfig"
    fi
    echo "    /* Initialize the Mcu driver */
#if (MCU_PRECOMPILE_SUPPORT == STD_ON)
    Mcu_Init(NULL_PTR);
#else
    Mcu_Init($McuConfig);
#endif /* (MCU_PRECOMPILE_SUPPORT == STD_ON) */

    /* Initialize the clock tree and apply PLL as system clock */
#if (MCU_INIT_CLOCK == STD_ON)
    Mcu_InitClock($ClockConfig);
#endif /* (MCU_INIT_CLOCK == STD_ON) */

    /* Apply a mode configuration */
    Mcu_SetMode($ModeConfig);
"
else
    Init_Parameter="NULL_PTR"
    if FileExist "$BaseRoot/generate/include/Clock_Ip_*fg.h"; then
        Init_Parameter=$(grep -h '^extern const Clock_Ip_ClockConfigType .*\[\];' $BaseRoot/generate/include/Clock_Ip_*fg.h | tr '[];' '   ' | awk '{ print $4 }');
        Init_Parameter="&$Init_Parameter[0]"
    fi
    echo "    {
        Clock_Ip_StatusType status = Clock_Ip_Init($Init_Parameter);
#if !defined(NDEBUG)
        DevAssert((Clock_Ip_StatusType)CLOCK_IP_SUCCESS == status);
#endif /* #if !defined(NDEBUG) */
    }"
fi

if FindModule "Port"; then
    PortConfig="NULL_PTR"
    #if FileExist "$BaseRoot/generate/include/Port_*fg.h"; then
    #    PortConfig=$(grep -h '^extern const Port_ConfigType .*;' $BaseRoot/generate/include/Port_*fg.h | tr ';' ' ' | awk '{ print $4 }');
    #    PortConfig="&$PortConfig"
    #fi
    echo "#if (STD_ON == PORT_PRECOMPILE_SUPPORT)
    Port_Init(NULL_PTR);
#else
    Port_Init($PortConfig);
#endif /* (STD_ON == PORT_PRECOMPILE_SUPPORT) */
"
    if grep -q '{ (uint16)4, PORT_SIUL2_0_U8 },' $BaseRoot/generate/src/Port_*fg.c; then
        echo "    // Check unused PTA4 PIN 4 (SWD_DIO)"
    fi
    if grep -q '{ (uint16)68, PORT_SIUL2_0_U8 },' $BaseRoot/generate/src/Port_*fg.c; then
        echo "    // Check unused PTC4 PIN 68 (SWD_CLK)"
    fi
    if grep -q '{ (uint16)5, PORT_SIUL2_0_U8 },' $BaseRoot/generate/src/Port_*fg.c; then
        echo "    // Check unused PTA5 PIN 5 (RESET_b)"
    fi
else
    if FindModule "Siul2_Port"; then
        declare -a usedpin
        MaxPin=0
        case $(FindProcessor) in
            S32K310|S32K311)
                usedpin=(4 5 10 18 19 20 21 22 23 24 25 26 27 28 29 30 31 38 39 \
	                     50 51 52 53 54 55 56 57 58 59 60 61 62 63 82 83 84 85  \
                         86 87 88 89 90 91 92 93 94 95 114 115 116 117 118 119  \
                         120 121 122 123 124 125 126 127 132 133 142)
                MaxPin=145
                ;;
            S32K312)
                usedpin=(4 5 10 22 23 38 39 63 68 69 86 115 121)
                MaxPin=155
                ;;
            S32K322)
                usedpin=(4 5 10 38 39 62 63 68 69 86 114 115 121 147 148)
                MaxPin=155
                ;;
            S32K341)
                usedpin=(4 5 10 22 23 38 39 62 63 68 69 86 114 115 121 147 148)
                MaxPin=155
                ;;
            S32K314|S32K324|S32K344)
                usedpin=(4 5 10 38 39 68 69)
                MaxPin=220
                ;;
            S32K328|S32K338|S32K348|S32K358)
                usedpin=(4 5 10 38 39 68 69)
                MaxPin=237
                ;;
            S32K388)
                usedpin=(4 5 10 38 39 68 69 141)
                MaxPin=237
                ;;
            *)
                echo "Error: Invalid processor argument."
                exit 1
                ;;
        esac

        declare -A usedpin_map
        for pin in "${usedpin[@]}"; do
            usedpin_map["$pin"]=1
        done

        while IFS= read -r line; do
            if [[ $line =~ ^([A-Z])([0-9]+) ]]; then
                letter="${BASH_REMATCH[1]}"
                digit="${BASH_REMATCH[2]}"
                number=$(( ( $(printf "%d" "'$letter") - $(printf "%d" "'A") ) * 32 + digit ))
                usedpin_map["$number"]=1
            fi
        done < <(grep "<pin peripheral=.*pin_signal" "$MexFile" | sed 's/.*pin_signal=\"PT//' | tr '>"' '  ')

        declare -a unusedPins
        for i in $(seq 0 $((MaxPin - 1))); do
            if [[ -z ${usedpin_map["$i"]} ]]; then
            unusedPins+=("$i")
            fi
        done

        echo "    {
        static const uint8_t unusedPins[] = {"
        count=0
        for pin in "${unusedPins[@]}"; do
            if [ $((count % 16)) -eq 0 ]; then
                printf "            "
            fi
            printf "%s, " "$pin"
            ((count++))
            if [ $((count % 16)) -eq 0 ]; then
                printf "\n"
            fi
        done

        if [ $((count % 16)) -ne 0 ]; then
            printf "\n"
        fi

        echo "        };
        Siul2_Port_DisableUnusedPins(ARRAY_SIZE(unusedPins), &unusedPins[0]);
    }"
        for numval in $(grep -h '^#define NUM_OF_CONFIGURED_PINS_' $BaseRoot/board/Siul2_Port_Ip_Cfg.h | awk '{ print $2 }'); do
            Array_Name=$(grep "\[$numval\]" $BaseRoot/board/Siul2_Port_Ip_Cfg.h | tr '[' ' ' | awk ' { print $4 }')
            echo "    {
        Siul2_Port_Ip_PortStatusType status = Siul2_Port_Ip_Init($numval, &$Array_Name[0]);
#if !defined(NDEBUG)
        DevAssert((Siul2_Port_Ip_PortStatusType)SIUL2_PORT_SUCCESS == status);
#endif /* #if !defined(NDEBUG) */
    }"
        done
    fi
fi

if FindModule "IPV_Mpu_M7_Ip"; then
    MpuConfig="NULL_PTR"
    if FileExist $BaseRoot/generate/include/Mpu_M7_Ip_*fg.h; then
        MpuConfig=$(grep -h '^extern const Mpu_M7_Ip_ConfigType .*;' $BaseRoot/generate/include/Mpu_M7_Ip_*fg.h | tr ';' ' ' | awk '{ print $4 }');
        MpuConfig="&$MpuConfig"
    fi
    echo "    Mpu_M7_Ip_Init($MpuConfig);"

    PrintMPUInfo
fi

if FindModule "Siul2_Icu"; then
    IcuConfig="NULL_PTR"
    if FileExist "$BaseRoot/generate/include/Siul2_Icu_Ip_*fg.h"; then
        IcuConfig=$(grep -h 'extern const Siul2_Icu_Ip_ConfigType .*;' $BaseRoot/generate/include/Siul2_Icu_Ip_*fg.h | tr ';' ' ' | awk '{ print $4 }');
        IcuConfig="&$IcuConfig"
    fi
    echo "    {
        Siul2_Icu_Ip_StatusType status = Siul2_Icu_Ip_Init(0, $IcuConfig);
#if !defined(NDEBUG)
        DevAssert((Siul2_Icu_Ip_StatusType)SIUL2_ICU_IP_SUCCESS == status);
#endif /* #if !defined(NDEBUG) */"
    for file in $BaseRoot/generate/src/Siul2_Icu_Ip_*fg.c; do
        if [ -f "$file" ]; then
            ChannelName=$(grep -A 1 "Siul2 HW Module and Channel used by the Icu channel" "$file" | grep -v "Siul2 HW Module and Channel used by the Icu channel" | grep -oE '[0-9]+')
            echo "        Siul2_Icu_Ip_EnableInterrupt(0, $ChannelName);
        Siul2_Icu_Ip_EnableNotification(0, $ChannelName);"
        fi
    done
    echo "    }"
fi

if FindModule "POWER"; then
    Power_Parameter="NULL_PTR"
    if FileExist "$BaseRoot/generate/include/Power_Ip_*fg.h"; then
        Power_Parameter=$(grep -h '^extern const Power_Ip_HwIPsConfigType .*;' $BaseRoot/generate/include/Power_Ip_*fg.h | tr ';' ' ' | awk '{ print $4 }');
        Power_Parameter="&$Power_Parameter"
    fi
    Mode_Parameter="NULL_PTR"
    if FileExist "$BaseRoot/generate/include/Power_Ip_*fg.h"; then
        Mode_Parameter=$(grep -h '^extern const Power_Ip_ModeConfigType .*\[\];' $BaseRoot/generate/include/Power_Ip_*fg.h | tr '[];' '   ' | awk '{ print $4 }');
        Mode_Parameter="&$Mode_Parameter[0]"
    fi
    Reset_Parameter="NULL_PTR"
    if FileExist "$BaseRoot/generate/include/Power_Ip_*fg.h"; then
        Reset_Parameter=$(grep -h '^extern const Power_Ip_HwIPsConfigType .*;' $BaseRoot/generate/include/Power_Ip_*fg.h | tr '[];' '   ' | awk '{ print $4 }');
        Reset_Parameter="&$Reset_Parameter"
    fi
    echo "    Power_Ip_Init($Power_Parameter);"
    echo "    // Power_Ip_SetMode($Mode_Parameter);"
    echo "    switch (Power_Ip_GetResetReason()) {
    case MCU_POWER_ON_RESET:           /**< @brief Power on reset event. RGM_DES[F_DR0]. */
    case MCU_FCCU_FTR_RESET:           /**< @brief FCCU failure to react. RGM_DES[F_DR3]. */
    case MCU_STCU_URF_RESET:           /**< @brief STCU unrecoverable fault. RGM_DES[F_DR4]. */
    case MCU_MC_RGM_FRE_RESET:         /**< @brief Functional reset escalation. RGM_DES[F_DR6]. */
    case MCU_FXOSC_FAIL_RESET:         /**< @brief FXOSC failure. RGM_DES[F_DR8]. */
    case MCU_PLL_LOL_RESET:            /**< @brief PLL_LOL and related PLL loss of lock. RGM_DES[F_DR9]. */
    case MCU_CORE_CLK_FAIL_RESET:      /**< @brief CORE_CLK_FAIL and related Core clock failure. RGM_DES[F_DR10]. */
    case MCU_AIPS_PLAT_CLK_FAIL_RESET: /**< @brief AIPS_PLAT_CLK failure. RGM_DES[F_DR12]. */
    case MCU_HSE_CLK_FAIL_RESET:       /**< @brief HSE_CLK failure. RGM_DES[F_DR14]. */
    case MCU_SYS_DIV_FAIL_RESET:       /**< @brief System clock dividers alignment failure. RGM_DES[F_DR15]. */
    case MCU_CM7_CORE_CLK_FAIL_RESET:  /**< @brief CM7_CORE_CLK Failure. RGM_DES[F_DR16]. */
    case MCU_HSE_TMPR_RST_RESET:       /**< @brief HSE_B tamper detect reset. RGM_DES[F_DR17]. */
    case MCU_HSE_SNVS_RST_RESET:       /**< @brief HSE_B SNVS tamper detection. RGM_DES[F_DR18]. */
    case MCU_SW_DEST_RESET:            /**< @brief Software destructive reset. RGM_DES[F_DR29]. */
    case MCU_DEBUG_DEST_RESET:         /**< @brief Debug destructive reset. RGM_DES[F_DR30]. */
    case MCU_F_EXR_RESET:              /**< @brief Software destructive reset. RGM_FES[F_FR0]. */
    case MCU_FCCU_RST_RESET:           /**< @brief FCCU Reset Reaction. RGM_FES[F_FR3]. */
    case MCU_ST_DONE_RESET:            /**< @brief Self-Test Done. RGM_FES[F_FR4]. */
    case MCU_SWT0_RST_RESET:           /**< @brief SWT0 Timeout. RGM_FES[F_FR6]. */
    case MCU_SWT1_RST_RESET:           /**< @brief SWT1 Timeout. RGM_FES[F_FR7]. */
    case MCU_SWT2_RST_RESET:           /**< @brief SWT2 Timeout. RGM_FES[F_FR8]. */
    case MCU_JTAG_RST_RESET:           /**< @brief JTAG reset. RGM_FES[F_FR9]. */
    case MCU_SWT3_RST_RESET:           /**< @brief SWT3 Timeout. RGM_FES[F_FR10].*/
    case MCU_PLL_AUX_RESET:            /**< @brief PLL_AUX_CLK failure. RGM_FES[F_FR12].*/
    case MCU_HSE_SWT_RST_RESET:        /**< @brief HSE_B SWT timeout. RGM_FES[F_FR16]. */
    case MCU_HSE_BOOT_RST_RESET:       /**< @brief HSE_B boot reset. RGM_FES[F_FR20]. */
    case MCU_SW_FUNC_RESET:            /**< @brief Software functional reset. RGM_FES[F_FR29]. */
    case MCU_DEBUG_FUNC_RESET:         /**< @brief Debug functional reset. RGM_FES[F_FR30]. */
    case MCU_WAKEUP_REASON:            /**< @brief Wake-up event detected. */
    case MCU_NO_RESET_REASON:          /**< @brief No reset reason found */
    case MCU_MULTIPLE_RESET_REASON:    /**< @brief More than one reset events are logged except "Power on event" */
    case MCU_RESET_UNDEFINED:          /**< @brief Undefined reset source. */
    default:
        break;
	}
#if (POWER_IP_PERFORM_RESET_API == STD_ON)
    Power_Ip_PerformReset($Reset_Parameter);
#endif /* (POWER_IP_PERFORM_RESET_API == STD_ON) */"
fi

if FindModule "Dma_Ip"; then
    Dma_Parameter="NULL_PTR"
    if FileExist "$BaseRoot/generate/include/Dma_Ip_*fg.h"; then
        Dma_Parameter=$(grep -h '^extern const Dma_Ip_InitType .*;' $BaseRoot/generate/include/Dma_Ip_*fg.h | tr ';' ' ' | awk '{ print $4 }');
        Dma_Parameter="&$Dma_Parameter"
    fi
    echo "    {
        Dma_Ip_ReturnType status = Dma_Ip_Init($Dma_Parameter);
#if !defined(NDEBUG)
        DevAssert((Dma_Ip_ReturnType)DMA_IP_STATUS_SUCCESS == status);
#endif /* #if !defined(NDEBUG) */
    }"
fi

if FindModule "Rm"; then
    Rm_Parameter="NULL_PTR"
    if FileExist "$BaseRoot/generate/include/CDD_Rm_*fg.h"; then
        Rm_Parameter=$(grep -h 'extern const Rm_ConfigType .*;' $BaseRoot/generate/include/CDD_Rm_*fg.h | tr ';' ' ' | awk '{ print $4 }');
        Rm_Parameter="&$Rm_Parameter"
    fi
    echo "    Rm_Init($Rm_Parameter);"
fi

if FindModule "Flexio_Mcl_Ip"; then
    Flexio_Parameter="NULL_PTR"
    if FileExist "$BaseRoot/generate/include/Flexio_Mcl_Ip_*fg.h"; then
        Flexio_Parameter=$(grep -h '^extern const Flexio_Ip_InstanceConfigType .*;' $BaseRoot/generate/include/Flexio_Mcl_Ip_*fg.h | tr ';' ' ' | awk '{ print $4 }');
        Flexio_Parameter="&$Flexio_Parameter"
    fi
    echo "    {
        Flexio_Ip_CommonStatusType status = Flexio_Mcl_Ip_InitDevice($Flexio_Parameter);
#if !defined(NDEBUG)
        DevAssert((Flexio_Ip_CommonStatusType)FLEXIO_IP_COMMON_STATUS_SUCCESS == status);
#endif /* #if !defined(NDEBUG) */
    }"
fi

if FindModule "Lpuart_Uart"; then
    for instance in $(grep -h '^extern const Lpuart_Uart_Ip_UserConfigType .*;' $BaseRoot/generate/include/Lpuart_Uart_Ip_*fg.h | tr ';' ' ' | awk '{ print $4 }'); do
        echo "    Lpuart_Uart_Ip_Init(${instance/Lpuart_Uart_Ip_xHwConfigPB_/}, &$instance);"
    done
fi

if FindModule "C40_Ip"; then
    C40_Parameter="NULL_PTR"
    if FileExist "$BaseRoot/generate/include/C40_Ip_*fg.h"; then
        C40_Parameter=$(grep -h 'extern const C40_Ip_ConfigType .*;' $BaseRoot/generate/include/C40_Ip_*fg.h | tr ';' ' ' | awk '{ print $4 }');
        C40_Parameter="&$C40_Parameter"
    fi
    echo "    {
        C40_Ip_StatusType status = C40_Ip_Init($C40_Parameter);
#if !defined(NDEBUG)
        DevAssert((C40_Ip_StatusType)C40_IP_STATUS_SUCCESS == status);
#endif /* #if !defined(NDEBUG) */
    }"
fi

if FindModule "Cache_Ip"; then
    echo "    // Cache_Ip_Enable(CACHE_IP_CORE, CACHE_IP_INSTRUCTION);"
    echo "    // Cache_Ip_Enable(CACHE_IP_CORE, CACHE_IP_DATA);"
fi

if FindModule "Wkpu"; then
    WkpuConfig="NULL_PTR"
    if FileExist "$BaseRoot/generate/include/Wkpu_Ip_*fg.h"; then
        WkpuConfig=$(grep -h 'extern const Wkpu_Ip_IrqConfigType .*;' $BaseRoot/generate/include/Wkpu_Ip_*fg.h | tr ';' ' ' | awk '{ print $4 }');
        WkpuConfig="&$WkpuConfig"
    fi
    echo "    {
        Wkpu_Ip_StatusType status = Wkpu_Ip_Init(0, $WkpuConfig);
#if !defined(NDEBUG)
        DevAssert((Wkpu_Ip_StatusType)WKPU_IP_SUCCESS == status);
#endif /* #if !defined(NDEBUG) */"
    for file in $BaseRoot/generate/src/Wkpu_Ip_*fg.c; do
        if [ -f "$file" ]; then
            ChannelName=$(grep -A 1 "Wkpu HW Channel used by the Icu channel" "$file" | grep -v "Wkpu HW Channel used by the Icu channel" | grep -oE '[0-9]+')
            if [ "$ChannelName" -ge 4 ]; then
                ChannelString="WKPU_SRC_OUTER($((ChannelName - 4)))"
            else
                ChannelString="WKPU_SRC_INNER($ChannelName)"
            fi
            echo "        Wkpu_Ip_GetInputState(0, $ChannelString);
        Wkpu_Ip_EnableInterrupt(0, $ChannelString);
        Wkpu_Ip_EnableNotification($ChannelString);"
        fi
    done
    echo "    }"

fi

if FindModule "Lpi2c"; then
    echo "    {
        static LPI2C_Type * const Lpi2c_Ip_pxBase[LPI2C_INSTANCE_COUNT] = IP_LPI2C_BASE_PTRS;
        Lpi2c_Ip_StatusType status = (Lpi2c_Ip_StatusType)LPI2C_IP_SUCCESS_STATUS;"
    for MasterChannel in $(grep -h '^extern const Lpi2c_Ip_MasterConfigType .*;' $BaseRoot/generate/include/Lpi2c_Ip_*fg.h | tr ';' ' ' | awk '{ print $4 }'); do
        echo "        status = Lpi2c_Ip_MasterInit(LPI2C_CHANNEL_${MasterChannel/I2c_Lpi2cMasterChannel/}, &$MasterChannel);"
        echo "        Lpi2c_Ip_pxBase[LPI2C_CHANNEL_${MasterChannel/I2c_Lpi2cMasterChannel/}]->MCR |= LPI2C_MCR_DBGEN_MASK;"
        echo "#if !defined(NDEBUG)
        DevAssert((Lpi2c_Ip_StatusType)LPI2C_IP_SUCCESS_STATUS == status);
#endif /* #if !defined(NDEBUG) */"
    done
    for SlaveChannel in $(grep -h '^extern const Lpi2c_Ip_SlaveConfigType .*;' $BaseRoot/generate/include/Lpi2c_Ip_*fg.h | tr ';' ' ' | awk '{ print $4 }'); do
        echo "        status = Lpi2c_Ip_SlaveInit(LPI2C_CHANNEL_${SlaveChannel/I2c_Lpi2cSlaveChannel/}, &$SlaveChannel);"
        echo "        Lpi2c_Ip_pxBase[LPI2C_CHANNEL_${SlaveChannel/I2c_Lpi2cSlaveChannel/}]->MCR |= LPI2C_MCR_DBGEN_MASK;"
        echo "#if !defined(NDEBUG)
        DevAssert((Lpi2c_Ip_StatusType)LPI2C_IP_SUCCESS_STATUS == status);
#endif /* #if !defined(NDEBUG) */"
    done
    echo "    }"
fi

if FindModule "Gmac"; then
    if FileExist "$BaseRoot/generate/include/Gmac_Ip_*fg.h"; then
        GmacConfig=$(grep -h 'extern const Gmac_CtrlConfigType Gmac_0.*;' $BaseRoot/generate/include/Gmac_Ip_*fg.h | tr ';' ' ' | awk '{ print $4 }');
        if [ -n "$GmacConfig" ]; then
            GmacConfig="&$GmacConfig"
            echo "    {
        Gmac_Ip_StatusType status = Gmac_Ip_Init(INST_GMAC_0, $GmacConfig);
#if !defined(NDEBUG)
        DevAssert((Gmac_Ip_StatusType)GMAC_STATUS_SUCCESS == status);
#endif /* #if !defined(NDEBUG) */
    }"
        fi
        GmacConfig=$(grep -h 'extern const Gmac_CtrlConfigType Gmac_1.*;' $BaseRoot/generate/include/Gmac_Ip_*fg.h | tr ';' ' ' | awk '{ print $4 }');
        if [ -n "$GmacConfig" ]; then
            GmacConfig="&$GmacConfig"
            echo "    {
        Gmac_Ip_StatusType status = Gmac_Ip_Init(INST_GMAC_1, $GmacConfig);
#if !defined(NDEBUG)
        DevAssert((Gmac_Ip_StatusType)GMAC_STATUS_SUCCESS == status);
#endif /* #if !defined(NDEBUG) */
    }"
        fi
    fi
fi

if FindModule "Crypto_43_HSE"; then
    echo "    /* Initialize Crypto driver */
    Crypto_43_HSE_Init(NULL_PTR);
#define HSE_MAX_TASK_COUNT 4
    static Crypto_Task Tasks[HSE_MAX_TASK_COUNT];
    Crypto_Task_Init(HSE_MAX_TASK_COUNT, &Tasks[0]);"
else
    if FindModule "Hse"; then
        echo "    {
        static Hse_Ip_ReqType Hse_Ip_Request[HSE_IP_NUM_OF_MU_INSTANCES][HSE_IP_NUM_OF_CHANNELS_PER_MU];
        static Hse_Ip_MuStateType HseIp_MuState[HSE_IP_NUM_OF_MU_INSTANCES];
        for (uint32_t InstID = 0; InstID < HSE_IP_NUM_OF_MU_INSTANCES; ++InstID) {
            Hse_Ip_StatusType status = Hse_Ip_Init(InstID, &HseIp_MuState[InstID]);
#if !defined(NDEBUG)
            DevAssert((Hse_Ip_StatusType)HSE_IP_STATUS_SUCCESS == status);
#endif /* #if !defined(NDEBUG) */
        }
        {
            static HSE_Task gTasks[HSE_MAX_TASK_COUNT];
            Hse_Task_Init(HSE_MAX_TASK_COUNT, &gTasks[0], &gHSEContext[0]);
        }
    }"
    fi
fi

# Processing Interrupts
if FindModule "Platform"; then
    echo "    Platform_Init(NULL_PTR);"
    # for i in $(grep "ISR(.*)" $BaseRoot/RTD/src/* | sed 's/ //g' | tr '()' '  ' | awk '{ print $2 }' | sort -u); do
    #     echo
    #     echo "    // Platform_InstallIrqHandler(IRQn_Type, $i, NULL_PTR); // Parameter 3 is output of current ISR"
    #     echo "    // Platform_SetIrqPriority(IRQn_Type, 0); // 0 highest -> 15 lowest"
    #     echo "    // Platform_SetIrq(IRQn_Type, TRUE);"
    # done
    PrintMPUInfo
    if FindModule "Crypto_43_HSE"; then
        echo "    Platform_InstallIrqHandler(HSE_MU0_RX_IRQn, Mu_Ip_Mu0_OredRx_Isr, NULL_PTR); // Parameter 3 is output of current ISR
    Platform_SetIrqPriority(HSE_MU0_RX_IRQn, 0); // 0 highest -> 15 lowest
    Platform_SetIrq(HSE_MU0_RX_IRQn, TRUE);

#if (HSE_IP_NUM_OF_MU_INSTANCES > 1U)
    Platform_InstallIrqHandler(HSE_MU1_RX_IRQn, Mu_Ip_Mu1_OredRx_Isr, NULL_PTR); // Parameter 3 is output of current ISR
    Platform_SetIrqPriority(HSE_MU1_RX_IRQn, 0); // 0 highest -> 15 lowest
    Platform_SetIrq(HSE_MU1_RX_IRQn, TRUE);
#endif /* (HSE_IP_NUM_OF_MU_INSTANCES > 1U) */"
    fi

else
    if FindModule "IntCtrl_Ip"; then
        Init_Parameter="NULL_PTR"
        if FileExist "$BaseRoot/generate/include/IntCtrl_Ip_*fg.h"; then
            Init_Parameter=$(grep -h '^extern const IntCtrl_Ip_CtrlConfigType .*;' $BaseRoot/generate/include/IntCtrl_Ip_*fg.h | tr ';' ' ' | awk '{ print $4 }');
            Init_Parameter="&$Init_Parameter"
        fi
        echo "    {
        IntCtrl_Ip_StatusType status = IntCtrl_Ip_Init($Init_Parameter);
#if !defined(NDEBUG)
        DevAssert((IntCtrl_Ip_StatusType)INTCTRL_IP_STATUS_SUCCESS == status);
#endif /* #if !defined(NDEBUG) */"
        # for i in $(grep "ISR(.*)" $BaseRoot/RTD/src/* | sed 's/ //g' | tr '()' '  ' | awk '{ print $2 }' | sort -u); do
        #     echo
        #     echo "        // IntCtrl_Ip_InstallHandler(IRQn_Type, $i, NULL_PTR); // Parameter 3 is output of current ISR"
        #     echo "        // IntCtrl_Ip_SetPriority(IRQn_Type, 0); // 0 highest -> 15 lowest"
        #     echo "        // IntCtrl_Ip_EnableIrq(IRQn_Type);"
        # done
        if FindModule "Siul2_Icu"; then
            echo "#if ((defined SIUL2_ICU_IRQ_CH_0_ISR_USED) || (defined SIUL2_ICU_IRQ_CH_1_ISR_USED) || \\
     (defined SIUL2_ICU_IRQ_CH_2_ISR_USED) || (defined SIUL2_ICU_IRQ_CH_3_ISR_USED) || \\
     (defined SIUL2_ICU_IRQ_CH_4_ISR_USED) || (defined SIUL2_ICU_IRQ_CH_5_ISR_USED) || \\
     (defined SIUL2_ICU_IRQ_CH_6_ISR_USED) || (defined SIUL2_ICU_IRQ_CH_7_ISR_USED))
        IntCtrl_Ip_InstallHandler(SIUL_0_IRQn, SIUL2_EXT_IRQ_0_7_ISR, NULL_PTR); // Parameter 3 is output of current ISR
        IntCtrl_Ip_SetPriority(SIUL_0_IRQn, 0); // 0 highest -> 15 lowest
        IntCtrl_Ip_EnableIrq(SIUL_0_IRQn);
#endif

#if ((defined SIUL2_ICU_IRQ_CH_8_ISR_USED) || (defined SIUL2_ICU_IRQ_CH_9_ISR_USED) || \\
     (defined SIUL2_ICU_IRQ_CH_10_ISR_USED) || (defined SIUL2_ICU_IRQ_CH_11_ISR_USED) || \\
     (defined SIUL2_ICU_IRQ_CH_12_ISR_USED) || (defined SIUL2_ICU_IRQ_CH_13_ISR_USED) || \\
     (defined SIUL2_ICU_IRQ_CH_14_ISR_USED) || (defined SIUL2_ICU_IRQ_CH_15_ISR_USED))
        IntCtrl_Ip_InstallHandler(SIUL_1_IRQn, SIUL2_EXT_IRQ_8_15_ISR, NULL_PTR); // Parameter 3 is output of current ISR
        IntCtrl_Ip_SetPriority(SIUL_1_IRQn, 0); // 0 highest -> 15 lowest
        IntCtrl_Ip_EnableIrq(SIUL_1_IRQn);
#endif

#if ((defined SIUL2_ICU_IRQ_CH_16_ISR_USED) || (defined SIUL2_ICU_IRQ_CH_17_ISR_USED) || \\
     (defined SIUL2_ICU_IRQ_CH_18_ISR_USED) || (defined SIUL2_ICU_IRQ_CH_19_ISR_USED) || \\
     (defined SIUL2_ICU_IRQ_CH_20_ISR_USED) || (defined SIUL2_ICU_IRQ_CH_21_ISR_USED) || \\
     (defined SIUL2_ICU_IRQ_CH_22_ISR_USED) || (defined SIUL2_ICU_IRQ_CH_23_ISR_USED))
        IntCtrl_Ip_InstallHandler(SIUL_2_IRQn, SIUL2_EXT_IRQ_16_23_ISR, NULL_PTR); // Parameter 3 is output of current ISR
        IntCtrl_Ip_SetPriority(SIUL_2_IRQn, 0); // 0 highest -> 15 lowest
        IntCtrl_Ip_EnableIrq(SIUL_2_IRQn);
#endif

#if ((defined SIUL2_ICU_IRQ_CH_24_ISR_USED) || (defined SIUL2_ICU_IRQ_CH_25_ISR_USED) || \\
     (defined SIUL2_ICU_IRQ_CH_26_ISR_USED) || (defined SIUL2_ICU_IRQ_CH_27_ISR_USED) || \\
     (defined SIUL2_ICU_IRQ_CH_28_ISR_USED) || (defined SIUL2_ICU_IRQ_CH_29_ISR_USED) || \\
     (defined SIUL2_ICU_IRQ_CH_30_ISR_USED) || (defined SIUL2_ICU_IRQ_CH_31_ISR_USED))
        IntCtrl_Ip_InstallHandler(SIUL_3_IRQn, SIUL2_EXT_IRQ_24_31_ISR, NULL_PTR); // Parameter 3 is output of current ISR
        IntCtrl_Ip_SetPriority(SIUL_3_IRQn, 0); // 0 highest -> 15 lowest
        IntCtrl_Ip_EnableIrq(SIUL_3_IRQn);
#endif"
        fi
        echo "
    }"
    fi
fi

# Finishing processing
if FindModule "BaseNXP"; then
    echo "    OsIf_ResumeAllInterrupts();"
fi

if FindModule "Dio"; then
    for port in $(grep -h '^#define DioConf_DioChannel_DioChannel_' $BaseRoot/generate/include/Dio_*fg.h | awk '{ print $2 }'); do
        echo "    Dio_WriteChannel($port, STD_HIGH);"
    done
else
    if FindModule "Siul2_Dio"; then
        for NamedPin in $(grep -h '^#define .*_PIN ' $BaseRoot/board/Siul2_Port_Ip_Cfg.h | tr '_' ' ' | awk '{ print $2 }'); do
            echo "    Siul2_Dio_Ip_WritePin(SIUL2_DIO_NAMED_PIN($NamedPin), 1);"
        done
    fi
fi

if FindModule "Port"; then
    echo
else
    if FindModule "Siul2_Port"; then
        echo "#if defined(DEBUGPIN)
    LogInit();
    LogChar(0x55);
#endif"
    fi
fi

echo "}"
