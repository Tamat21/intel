#pragma once

/*++

Copyright (c) 2025 Manus AI

Module Name:

    Driver.h

Abstract:

    Заголовочный файл для драйвера Intel i219-v с игровыми оптимизациями.
    Содержит определения типов, структур и функций драйвера.

Environment:

    Kernel-mode Driver Framework

--*/

// Стандартные заголовки WDK
#include <ntddk.h>
#include <wdf.h>
#include <netadaptercx.h>

// Заголовки проекта
#include "Trace.h"
#include "DeviceContext.h"

EXTERN_C_START

// Определения для аннотаций SAL
#ifndef _In_
#define _In_
#endif

#ifndef _Out_
#define _Out_
#endif

#ifndef _Inout_
#define _Inout_
#endif

// Определения для базовых типов, если они не определены
// Лучше использовать стандартные типы из WDK (например, BOOLEAN, UINT32, NTSTATUS)
// #ifndef VOID
// typedef void VOID;
// #endif
//
// #ifndef BOOLEAN
// typedef unsigned char BOOLEAN;
// #endif
//
// #ifndef UINT16
// typedef unsigned short UINT16;
// #endif
//
// #ifndef UINT32
// typedef unsigned int UINT32;
// #endif
//
// #ifndef TRUE
// #define TRUE 1
// #endif
//
// #ifndef FALSE
// #define FALSE 0
// #endif
//
// #ifndef STATUS_SUCCESS
// #define STATUS_SUCCESS ((NTSTATUS)0x00000000L) // Стандартное определение NTSTATUS
// #endif

// Определения для типов WDF должны поступать из заголовков WDF/NetAdapterCx.
// Их переопределение здесь некорректно и может привести к ошибкам компиляции.
// #ifndef WDFDRIVER
// typedef PVOID WDFDRIVER;
// #endif
//
// #ifndef WDFDEVICE
// typedef PVOID WDFDEVICE;
// #endif
//
// #ifndef NETADAPTER
// typedef PVOID NETADAPTER;
// #endif
//
// #ifndef NETPACKETQUEUE
// typedef PVOID NETPACKETQUEUE;
// #endif
//
// #ifndef PNETPACKETQUEUE
// typedef NETPACKETQUEUE* PNETPACKETQUEUE;
// #endif

// Определения для типов обработчиков событий
typedef EVT_WDF_DRIVER_DEVICE_ADD EvtDriverDeviceAdd;
typedef EVT_WDF_DRIVER_UNLOAD EvtDriverUnload;
typedef EVT_WDF_DEVICE_PREPARE_HARDWARE EvtDevicePrepareHardware;
typedef EVT_WDF_DEVICE_RELEASE_HARDWARE EvtDeviceReleaseHardware;
typedef EVT_WDF_DEVICE_D0_ENTRY EvtDeviceD0Entry;
typedef EVT_WDF_DEVICE_D0_EXIT EvtDeviceD0Exit;
typedef EVT_NET_ADAPTER_CREATE_TXQUEUE EvtAdapterCreateTxQueue;
typedef EVT_NET_ADAPTER_CREATE_RXQUEUE EvtAdapterCreateRxQueue;
typedef EVT_NET_ADAPTER_SET_CAPABILITIES EvtAdapterSetCapabilities;
typedef EVT_NET_ADAPTER_START EvtAdapterStart;
typedef EVT_NET_ADAPTER_STOP EvtAdapterStop;
typedef EVT_NET_ADAPTER_PAUSE EvtAdapterPause;
typedef EVT_NET_ADAPTER_RESTART EvtAdapterRestart;

// Функции драйвера
DRIVER_INITIALIZE DriverEntry;
EVT_WDF_DRIVER_UNLOAD I219vEvtDriverUnload;
EVT_WDF_DRIVER_DEVICE_ADD I219vEvtDriverDeviceAdd;

// Получение контекста устройства
WDF_DECLARE_CONTEXT_TYPE_WITH_NAME(I219V_DEVICE_CONTEXT, I219vGetDeviceContext);

// Определения для регистров устройства
#define I219V_REG_TXCW        0x0178
#define I219V_REG_RXCW        0x0180
#define I219V_REG_TXDCTL      0x3828
#define I219V_REG_RXDCTL      0x2828

// Определения для приоритетов трафика
#define I219V_TRAFFIC_PRIORITY_LOWEST   0
#define I219V_TRAFFIC_PRIORITY_LOW      1
#define I219V_TRAFFIC_PRIORITY_MEDIUM   2
#define I219V_TRAFFIC_PRIORITY_HIGH     3
#define I219V_TRAFFIC_PRIORITY_HIGHEST  4

// Определения для игровых профилей
#define I219V_GAMING_PROFILE_DISABLED    0
#define I219V_GAMING_PROFILE_BALANCED    1
#define I219V_GAMING_PROFILE_COMPETITIVE 2
#define I219V_GAMING_PROFILE_STREAMING   3
#define I219V_GAMING_PROFILE_CUSTOM      4

EXTERN_C_END
