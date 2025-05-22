#pragma once

/*++

Copyright (c) 2025 Manus AI

Module Name:

    i219v_gaming.h

Abstract:

    Заголовочный файл для игровых оптимизаций драйвера Intel i219-v.
    Содержит определения функций и структур для оптимизации сетевой производительности в играх.

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
#include "i219v_hw.h"

EXTERN_C_START

// Определения для игровых профилей
typedef enum _I219V_GAMING_PROFILE {
    I219V_GAMING_PROFILE_DISABLED = 0,
    I219V_GAMING_PROFILE_BALANCED = 1,
    I219V_GAMING_PROFILE_COMPETITIVE = 2,
    I219V_GAMING_PROFILE_STREAMING = 3,
    I219V_GAMING_PROFILE_CUSTOM = 4
} I219V_GAMING_PROFILE, *PI219V_GAMING_PROFILE;

// Определения для приоритетов трафика
typedef enum _I219V_TRAFFIC_PRIORITY {
    I219V_TRAFFIC_PRIORITY_LOWEST = 0,
    I219V_TRAFFIC_PRIORITY_LOW = 1,
    I219V_TRAFFIC_PRIORITY_MEDIUM = 2,
    I219V_TRAFFIC_PRIORITY_HIGH = 3,
    I219V_TRAFFIC_PRIORITY_HIGHEST = 4
} I219V_TRAFFIC_PRIORITY, *PI219V_TRAFFIC_PRIORITY;

// Структура NET_PACKET определяется в заголовках NetAdapterCx (включенных через netadaptercx.h).
// Не следует переопределять или определять ее здесь.
// typedef struct _NET_PACKET NET_PACKET, *PNET_PACKET;

// Функции для работы с игровыми профилями
NTSTATUS
I219vSetGamingProfile(
    _In_ PI219V_DEVICE_CONTEXT DeviceContext,
    _In_ UINT32 Profile
    );

NTSTATUS
I219vEnableTrafficPrioritization(
    _In_ PI219V_DEVICE_CONTEXT DeviceContext,
    _In_ BOOLEAN Enable
    );

NTSTATUS
I219vEnableLatencyReduction(
    _In_ PI219V_DEVICE_CONTEXT DeviceContext,
    _In_ BOOLEAN Enable
    );

NTSTATUS
I219vEnableBandwidthControl(
    _In_ PI219V_DEVICE_CONTEXT DeviceContext,
    _In_ BOOLEAN Enable
    );

NTSTATUS
I219vEnableSmartPowerManagement(
    _In_ PI219V_DEVICE_CONTEXT DeviceContext,
    _In_ BOOLEAN Enable
    );

NTSTATUS
I219vSetInterruptModerationRate(
    _In_ PI219V_DEVICE_CONTEXT DeviceContext,
    _In_ UINT32 Rate
    );

NTSTATUS
I219vSetBufferSizes(
    _In_ PI219V_DEVICE_CONTEXT DeviceContext,
    _In_ UINT32 ReceiveSize,
    _In_ UINT32 TransmitSize
    );

NTSTATUS
I219vSetPacketPriority(
    _In_ PI219V_DEVICE_CONTEXT DeviceContext,
    _In_ PNET_PACKET Packet,
    _In_ I219V_TRAFFIC_PRIORITY Priority
    );

NTSTATUS
I219vGetPerformanceStats(
    _In_ PI219V_DEVICE_CONTEXT DeviceContext,
    _Out_ PI219V_GAMING_PERFORMANCE_STATS PerformanceStats
    );

// Функции для анализа трафика
VOID
I219vGetGamingProfile(
    _Out_ PI219V_GAMING_PROFILE GamingProfile,
    _In_ BOOLEAN DefaultIfDisabled
    );

VOID
I219vGetCompetitiveProfile(
    _Out_ PI219V_GAMING_PROFILE GamingProfile,
    _In_ BOOLEAN DefaultIfDisabled
    );

VOID
I219vGetStreamingProfile(
    _Out_ PI219V_GAMING_PROFILE GamingProfile,
    _In_ BOOLEAN DefaultIfDisabled
    );

// Функции для определения типа трафика
BOOLEAN
I219vIsGamingTraffic(
    _In_ PNET_PACKET Packet
    );

BOOLEAN
I219vIsVoiceTraffic(
    _In_ PNET_PACKET Packet
    );

BOOLEAN
I219vIsStreamingTraffic(
    _In_ PNET_PACKET Packet
    );

// Функции для оптимизации TCP/UDP
NTSTATUS
I219vOptimizeTCP(
    _In_ PI219V_DEVICE_CONTEXT DeviceContext,
    _In_ BOOLEAN Enable
    );

NTSTATUS
I219vOptimizeUDP(
    _In_ PI219V_DEVICE_CONTEXT DeviceContext,
    _In_ BOOLEAN Enable
    );

NTSTATUS
I219vSetNagleAlgorithm(
    _In_ PI219V_DEVICE_CONTEXT DeviceContext,
    _In_ BOOLEAN Enable
    );

EXTERN_C_END
