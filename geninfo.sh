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

if FindModule "MCU"; then
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

if FindModule "Crypto_43_HSE"; then
    echo "#include \"Crypto_43_HSE.h\""
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

if FindModule "MCU"; then
    echo "// MCU initialization"
else
    Init_Parameter="NULL_PTR"
    if FileExist "generate/include/Clock_Ip_*fg.h"; then
        Init_Parameter=$(grep '^extern const Clock_Ip_ClockConfigType .*\[\];' generate/include/Clock_Ip_*fg.h | tr '[];' '   ' | awk '{ print $4 }');
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
    echo "#include \"Port.h\""
else
    if FindModule "Siul2_Port"; then
        for numval in $(grep '^#define NUM_OF_CONFIGURED_PINS_' board/Siul2_Port_Ip_Cfg.h | awk '{ print $2 }'); do
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

if FindModule "Dio"; then
    echo "#include \"Dio.h\""
else
    if FindModule "Siul2_Dio"; then
        echo
    fi
fi

if FindModule "Crypto_43_HSE"; then
    echo "#include \"Crypto_43_HSE.h\""
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
    echo "#include \"Platform.h\""
else
    if FindModule "IntCtrl_Ip"; then
        Init_Parameter="NULL_PTR"
        if FileExist "generate/include/IntCtrl_Ip_*fg.h"; then
            Init_Parameter=$(grep '^extern const IntCtrl_Ip_CtrlConfigType .*;' generate/include/IntCtrl_Ip_*fg.h | tr ';' ' ' | awk '{ print $4 }');
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
echo "}"
