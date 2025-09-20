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
#if !defined(WTK3_RTE_H)
#define WTK3_RTE_H (1)

#if defined(__cplusplus)
extern "C" {
#endif

typedef union {
    uint64_t rawValue;
    struct {
        uint32_t value : 32;
        uint32_t countReload : 8;
        uint32_t count : 8;
        uint32_t initialized : 1;
        uint32_t updated : 1;
    } Item;
} WT_RTE_Item, *WT_RTE_ItemPtr;

static inline WT_RTE_Item WT_RTE_Read(WT_RTE_ItemPtr pItem) {
    register WT_RTE_Item Value      = *pItem;
    const WT_RTE_Item    updateMask = {.Item = {.updated = 1}};
    if (Value.Item.count > 0) {
        --Value.Item.count;
    }
    pItem->rawValue = Value.rawValue & ~updateMask.rawValue;
    return Value;
}

static inline void WT_RTE_Write(WT_RTE_ItemPtr pItem, uint32_t value) {
    register uint8_t ReloadValue = pItem->Item.countReload;
    WT_RTE_Item      newValue    = {.Item = {.value       = value,
                                             .countReload = ReloadValue,
                                             .count       = ReloadValue,
                                             .initialized = 1,
                                             .updated     = 1}};
    pItem->rawValue              = newValue.rawValue;
}

#define WT_RTE_GetValue(Item)      ((Item).Item.value)
#define WT_RTE_IsUpdated(Item)     ((Item).Item.updated)
#define WT_RTE_IsInitialized(Item) ((Item).Item.initialized)
#define WT_RTE_IsTimeout(Item)                                                                     \
    (((Item).Item.countReload != 0) && ((Item).Item.count == 0) && ((Item).Item.updated == 0))
#define WT_RTE_InitializedValue(Value, Count)                                                      \
    ((uint64_t)(Value) | ((uint64_t)((Count) * 0x0101) << 32ULL))


typedef struct {
    uint32_t TaskState;
    uint32_t NextTick;
    uint32_t TickInterval;
    bool (*TaskInit)(void);
    void (*TaskRun)(void);
    bool (*TaskEnd)(void);
} WT_RTE_Task, *WT_RTE_TaskPtr;

#define WT_RTE_TASK_STATE_INVALID (-1U)
#define WT_RTE_TASK_STATE_IDLE    (0U)
#define WT_RTE_TASK_STATE_RUN     (1U)

#define WT_RTE_Task_INIT(Interval, FuncInit, FuncRun, FuncEnd) {WT_RTE_TASK_STATE_IDLE, 0, (Interval), (FuncInit), (FuncRun), (FuncEnd)}
#define WT_RTE_Task_End() {WT_RTE_TASK_STATE_INVALID, 0, 0, NULL, NULL, NULL}

void WTK3_System_Timer_Init(void);
uint32_t WTK3_System_Timer_GetCounter(void);

static inline bool WTK3_RTE_Task_Init(WT_RTE_TaskPtr pTask) {
    bool Result = true;
    uint32_t currentTick = WTK3_System_Timer_GetCounter();

    if (pTask) {
        while (pTask->TaskState != WT_RTE_TASK_STATE_INVALID) {
            if (pTask->TaskState == WT_RTE_TASK_STATE_IDLE) {
                if (pTask->TaskInit && !pTask->TaskInit()) {
					Result = false;
                } else {
                    pTask->TaskState = WT_RTE_TASK_STATE_RUN;
                    pTask->NextTick = currentTick + pTask->TickInterval;
                }
            }
            ++pTask;
        }
    }
    return Result;
}

static inline void WTK3_RTE_Task_Run(WT_RTE_TaskPtr pTask) {
    if (pTask) {
        uint32_t currentTick = WTK3_System_Timer_GetCounter();
        while (pTask->TaskState != WT_RTE_TASK_STATE_INVALID) {
            if (pTask->TaskState == WT_RTE_TASK_STATE_RUN) {
                if (pTask->TaskRun) {
                    if (((int32_t)(currentTick - pTask->NextTick)) >= 0) {
                        pTask->TaskRun();
                        if (pTask->TickInterval) {
                            pTask->NextTick += pTask->TickInterval;
                        } else {
                            pTask->NextTick = currentTick;
                        }
                    }
                }
            }
            ++pTask;
        }
    }
}

#if defined(__cplusplus)
}
#endif

#endif // WTK3_RTE_H
