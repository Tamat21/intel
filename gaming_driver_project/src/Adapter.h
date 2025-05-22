#pragma once

/*++

Copyright (c) 2025 Manus AI

Module Name:

    Adapter.h

Abstract:

    Заголовочный файл для работы с сетевым адаптером Intel i219-v.
    Содержит определения функций для инициализации и управления адаптером.

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

// Функции для работы с адаптером
NTSTATUS
I219vAdapterCreate(
    _In_ WDFDEVICE Device,
    _In_ PI219V_DEVICE_CONTEXT DeviceContext
    );

VOID
I219vEvtAdapterSetCapabilities(
    _In_ NETADAPTER Adapter
    );

VOID
I219vEvtAdapterStart(
    _In_ NETADAPTER Adapter
    );

VOID
I219vEvtAdapterStop(
    _In_ NETADAPTER Adapter
    );

VOID
I219vEvtAdapterPause(
    _In_ NETADAPTER Adapter
    );

VOID
I219vEvtAdapterRestart(
    _In_ NETADAPTER Adapter
    );

NTSTATUS
I219vEvtAdapterCreateTxQueue(
    _In_ NETADAPTER Adapter,
    _In_ PNETTXQUEUE_INIT TxQueueInit
    );

NTSTATUS
I219vEvtAdapterCreateRxQueue(
    _In_ NETADAPTER Adapter,
    _In_ PNETRXQUEUE_INIT RxQueueInit
    );

EXTERN_C_END
