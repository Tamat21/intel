#pragma once

/*++

Copyright (c) 2025 Manus AI

Module Name:

    Queue.h

Abstract:

    Заголовочный файл для работы с очередями пакетов Intel i219-v.
    Содержит определения функций для управления очередями приема и передачи.

Environment:

    Kernel-mode Driver Framework

--*/

// Включаем базовые заголовки
#include <ntddk.h>
#include <wdf.h>
#include <netadaptercx.h>

// Включаем заголовки проекта
#include "Driver.h"
#include "DeviceContext.h"

EXTERN_C_START

// Структуры для контекста очередей
typedef struct _I219V_TXQUEUE_CONTEXT {
    PI219V_DEVICE_CONTEXT DeviceContext;
    NETPACKETQUEUE NetTxQueue;
    WDFSPINLOCK Lock;
    UINT32 QueueId;
    BOOLEAN LowLatencyMode;
} I219V_TXQUEUE_CONTEXT, *PI219V_TXQUEUE_CONTEXT;

typedef struct _I219V_RXQUEUE_CONTEXT {
    PI219V_DEVICE_CONTEXT DeviceContext;
    NETPACKETQUEUE NetRxQueue;
    WDFSPINLOCK Lock;
    UINT32 QueueId;
    BOOLEAN LowLatencyMode;
} I219V_RXQUEUE_CONTEXT, *PI219V_RXQUEUE_CONTEXT;

// Функции для работы с очередями передачи
NTSTATUS
I219vTxQueueInitialize(
    _In_ NETPACKETQUEUE TxQueue,
    _In_ PI219V_DEVICE_CONTEXT DeviceContext
    );

VOID
I219vEvtTxQueueStart(
    _In_ NETPACKETQUEUE TxQueue
    );

VOID
I219vEvtTxQueueStop(
    _In_ NETPACKETQUEUE TxQueue
    );

VOID
I219vEvtTxQueueAdvance(
    _In_ NETPACKETQUEUE TxQueue
    );

VOID
I219vEvtTxQueueCancel(
    _In_ NETPACKETQUEUE TxQueue
    );

VOID
I219vEvtTxQueueSetNotificationEnabled(
    _In_ NETPACKETQUEUE TxQueue,
    _In_ BOOLEAN NotificationEnabled
    );

// Функции для работы с очередями приема
NTSTATUS
I219vRxQueueInitialize(
    _In_ NETPACKETQUEUE RxQueue,
    _In_ PI219V_DEVICE_CONTEXT DeviceContext
    );

VOID
I219vEvtRxQueueStart(
    _In_ NETPACKETQUEUE RxQueue
    );

VOID
I219vEvtRxQueueStop(
    _In_ NETPACKETQUEUE RxQueue
    );

VOID
I219vEvtRxQueueAdvance(
    _In_ NETPACKETQUEUE RxQueue
    );

VOID
I219vEvtRxQueueCancel(
    _In_ NETPACKETQUEUE RxQueue
    );

VOID
I219vEvtRxQueueSetNotificationEnabled(
    _In_ NETPACKETQUEUE RxQueue,
    _In_ BOOLEAN NotificationEnabled
    );

// Функции для оптимизации очередей
NTSTATUS
I219vSetQueueLowLatencyMode(
    _In_ PI219V_TXQUEUE_CONTEXT TxQueueContext,
    _In_ BOOLEAN Enable
    );

NTSTATUS
I219vSetQueuePriority(
    _In_ PI219V_TXQUEUE_CONTEXT TxQueueContext,
    _In_ UINT32 Priority
    );

EXTERN_C_END
