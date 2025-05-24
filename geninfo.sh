#!/bin/bash

MexFile="$1"

FindModule() {
    local pattern="<instance name=\\\"$1\\\""
    grep -q "$pattern" "$MexFile"
}

FileExist() {
    local file_pattern="$1"
    local matching_files=($(ls $file_pattern 2>/dev/null))
    [ ${#matching_files[@]} -gt 0 ]
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

if FindModule "Dio"; then
    echo "#include \"Dio.h\""
else
    if FindModule "Siul2_Dio"; then
        echo "#include \"Siul2_Dio_Ip.h\""
    fi
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

if FindModule "Lpuart_Uart"; then
    echo "#include \"Lpuart_Uart_Ip.h\""
fi

if FindModule "Crypto_43_HSE"; then
    echo "#include \"Crypto_43_HSE.h\""
    echo "#include \"Crypto_43_HSE_Util.h\""
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
echo "#define DEBUG_ASSERT"
echo
echo "#if defined(DEBUG_ASSERT)"
echo "#include \"Devassert.h\""
echo "#endif /* #if defined(DEBUG_ASSERT) */"
echo
echo "// Initialization"
echo "static void wtk3_init(void) {"
# Initialization processing
if FindModule "BaseNXP"; then
    echo "    OsIf_SuspendAllInterrupts();"
    echo "    OsIf_Init(NULL_PTR);"
fi

if FindModule "Mcu"; then
    McuConfig="NULL_PTR"
    if FileExist "generate/include/Mcu_*fg.h"; then
        McuConfig=$(grep -h '^extern const Mcu_ConfigType .*;' generate/include/Mcu_*fg.h | tr ';' ' ' | awk '{ print $4 }');
        McuConfig="&$McuConfig"
    fi
    ClockConfig="0"
    if FileExist "generate/include/Mcu_*fg.h"; then
        ClockConfig=$(grep -h '#define .* ((Mcu_ClockType)0U)' generate/include/Mcu_*fg.h | awk '{ print $2 }' | head -n 1);
        ClockConfig="$ClockConfig"
    fi
    ModeConfig="0"
    if FileExist "generate/include/Mcu_*fg.h"; then
        ModeConfig=$(grep -h '#define .* ((Mcu_ModeType)0U)' generate/include/Mcu_*fg.h | awk '{ print $2 }' | head -n 1);
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
    if FileExist "generate/include/Clock_Ip_*fg.h"; then
        Init_Parameter=$(grep -h '^extern const Clock_Ip_ClockConfigType .*\[\];' generate/include/Clock_Ip_*fg.h | tr '[];' '   ' | awk '{ print $4 }');
        Init_Parameter="&$Init_Parameter[0]"
    fi
    echo "    {
        Clock_Ip_StatusType status = Clock_Ip_Init($Init_Parameter);
#if defined(DEBUG_ASSERT)
        DevAssert((Clock_Ip_StatusType)CLOCK_IP_SUCCESS == status);
#endif /* #if defined(DEBUG_ASSERT) */
    }"
fi

if FindModule "Port"; then
    PortConfig="NULL_PTR"
    #if FileExist "generate/include/Port_*fg.h"; then
    #    PortConfig=$(grep -h '^extern const Port_ConfigType .*;' generate/include/Port_*fg.h | tr ';' ' ' | awk '{ print $4 }');
    #    PortConfig="&$PortConfig"
    #fi
    echo "#if (STD_ON == PORT_PRECOMPILE_SUPPORT)
    Port_Init(NULL_PTR);
#else
    Port_Init($PortConfig);
#endif /* (STD_ON == PORT_PRECOMPILE_SUPPORT) */
"
    if grep -q '{ (uint16)4, PORT_SIUL2_0_U8 },' generate/src/Port_*fg.c; then
        echo "    // Check unused PTA4 PIN 4 (SWD_DIO)"
    fi
    if grep -q '{ (uint16)68, PORT_SIUL2_0_U8 },' generate/src/Port_*fg.c; then
        echo "    // Check unused PTC4 PIN 68 (SWD_CLK)"
    fi
    if grep -q '{ (uint16)5, PORT_SIUL2_0_U8 },' generate/src/Port_*fg.c; then
        echo "    // Check unused PTA5 PIN 5 (RESET_b)"
    fi
else
    if FindModule "Siul2_Port"; then
        for numval in $(grep -h '^#define NUM_OF_CONFIGURED_PINS_' board/Siul2_Port_Ip_Cfg.h | awk '{ print $2 }'); do
            Array_Name=$(grep "\[$numval\]" board/Siul2_Port_Ip_Cfg.h | tr '[' ' ' | awk ' { print $4 }')
            echo "    {
        Siul2_Port_Ip_PortStatusType status = Siul2_Port_Ip_Init($numval, &$Array_Name[0]);
#if defined(DEBUG_ASSERT)
        DevAssert((Siul2_Port_Ip_PortStatusType)SIUL2_PORT_SUCCESS == status);
#endif /* #if defined(DEBUG_ASSERT) */
    }"
        done
    fi
fi

if FindModule "POWER"; then
    Power_Parameter="NULL_PTR"
    if FileExist "generate/include/Power_Ip_*fg.h"; then
        Power_Parameter=$(grep -h '^extern const Power_Ip_HwIPsConfigType .*;' generate/include/Power_Ip_*fg.h | tr ';' ' ' | awk '{ print $4 }');
        Power_Parameter="&$Power_Parameter"
    fi
    Mode_Parameter="NULL_PTR"
    if FileExist "generate/include/Power_Ip_*fg.h"; then
        Mode_Parameter=$(grep -h '^extern const Power_Ip_ModeConfigType .*\[\];' generate/include/Power_Ip_*fg.h | tr '[];' '   ' | awk '{ print $4 }');
        Mode_Parameter="&$Mode_Parameter[0]"
    fi
    echo "    Power_Ip_Init($Power_Parameter);"
    echo "    Power_Ip_SetMode($Mode_Parameter);"
fi

if FindModule "Dma_Ip"; then
    Dma_Parameter="NULL_PTR"
    if FileExist "generate/include/Dma_Ip_*fg.h"; then
        Dma_Parameter=$(grep -h '^extern const Dma_Ip_InitType .*;' generate/include/Dma_Ip_*fg.h | tr ';' ' ' | awk '{ print $4 }');
        Dma_Parameter="&$Dma_Parameter"
    fi
    echo "    {
        Dma_Ip_ReturnType status = Dma_Ip_Init($Dma_Parameter);
#if defined(DEBUG_ASSERT)
        DevAssert((Dma_Ip_ReturnType)DMA_IP_STATUS_SUCCESS == status);
#endif /* #if defined(DEBUG_ASSERT) */
    }"
fi

if FindModule "Rm"; then
    Rm_Parameter="NULL_PTR"
    if FileExist "generate/include/CDD_Rm_*fg.h"; then
        Rm_Parameter=$(grep -h 'extern const Rm_ConfigType .*;' generate/include/CDD_Rm_*fg.h | tr ';' ' ' | awk '{ print $4 }');
        Rm_Parameter="&$Rm_Parameter"
    fi
    echo "    Rm_Init($Rm_Parameter);"
fi

if FindModule "Lpuart_Uart"; then
    for instance in $(grep -h '^extern const Lpuart_Uart_Ip_UserConfigType .*;' generate/include/Lpuart_Uart_Ip_*fg.h | tr ';' ' ' | awk '{ print $4 }'); do
        echo "    Lpuart_Uart_Ip_Init(${instance/Lpuart_Uart_Ip_xHwConfigPB_/}, &$instance);"
    done
fi

if FindModule "Crypto_43_HSE"; then
    echo "    /* Initialize Crypto driver */
    Crypto_43_HSE_Init(NULL_PTR);"
else
    if FindModule "Hse"; then
        echo "    {
        Hse_Status status;
        do {
            status.status = Hse_Ip_GetHseStatus(0);
#if defined(DEBUG_ASSERT)
            DevAssert(status.B.InitOK);
            DevAssert(status.B.RNGInitOK);
#endif /* #if defined(DEBUG_ASSERT) */
        } while(!(status.B.InitOK && status.B.RNGInitOK));

        static Hse_Ip_MuStateType HseIp_MuState[HSE_IP_NUM_OF_MU_INSTANCES];
        for (uint32_t InstID = 0; InstID < HSE_IP_NUM_OF_MU_INSTANCES; InstID++) {
            Hse_Ip_StatusType status = Hse_Ip_Init(InstID, &HseIp_MuState[InstID]);
#if defined(DEBUG_ASSERT)
            DevAssert((Hse_Ip_StatusType)HSE_IP_STATUS_SUCCESS == status);
#endif /* #if defined(DEBUG_ASSERT) */
        }
        Hse_Task_Init();
    }"
    fi
fi

# Processing Interrupts
if FindModule "Platform"; then
    echo "    Platform_Init(NULL_PTR);"
    for i in $(grep "ISR(.*);" RTD/src/* | sed 's/ //g' | tr '()' '  ' | awk '{ print $2 }'); do
        echo
        echo "    // Platform_InstallIrqHandler(IRQn_Type, $i, NULL_PTR); // Parameter 3 is output of current ISR"
        echo "    // Platform_SetIrqPriority(IRQn_Type, 0); // 0 highest -> 15 lowest"
        echo "    // Platform_SetIrq(IRQn_Type, TRUE);"
    done
else
    if FindModule "IntCtrl_Ip"; then
        Init_Parameter="NULL_PTR"
        if FileExist "generate/include/IntCtrl_Ip_*fg.h"; then
            Init_Parameter=$(grep -h '^extern const IntCtrl_Ip_CtrlConfigType .*;' generate/include/IntCtrl_Ip_*fg.h | tr ';' ' ' | awk '{ print $4 }');
            Init_Parameter="&$Init_Parameter"
        fi
        echo "    {
        IntCtrl_Ip_StatusType status = IntCtrl_Ip_Init($Init_Parameter);
#if defined(DEBUG_ASSERT)
        DevAssert((IntCtrl_Ip_StatusType)INTCTRL_IP_STATUS_SUCCESS == status);
#endif /* #if defined(DEBUG_ASSERT) */"
        for i in $(grep "ISR(.*);" RTD/src/* | sed 's/ //g' | tr '()' '  ' | awk '{ print $2 }'); do
            echo
            echo "        // IntCtrl_Ip_InstallHandler(IRQn_Type, $i, NULL_PTR); // Parameter 3 is output of current ISR"
            echo "        // IntCtrl_Ip_SetPriority(IRQn_Type, 0); // 0 highest -> 15 lowest"
            echo "        // IntCtrl_Ip_EnableIrq(IRQn_Type);"
        done
        echo "
    }"
    fi
fi

# Finishing processing
if FindModule "BaseNXP"; then
    echo "    OsIf_ResumeAllInterrupts();"
fi

if FindModule "Dio"; then
    for port in $(grep -h '^#define DioConf_DioChannel_DioChannel_' generate/include/Dio_*fg.h | awk '{ print $2 }'); do
        echo "    Dio_WriteChannel($port, STD_HIGH);"
    done
else
    if FindModule "Siul2_Dio"; then
        echo "    Siul2_Dio_Ip_WritePin(SIUL2_DIO_PIN(A, 16), 1);"
    fi
fi

echo "}"
