#pragma once

/*++

Copyright (c) 2025 Manus AI

Module Name:

    DeviceContext.h

Abstract:

    Определение структуры контекста устройства для драйвера Intel i219-v с игровыми оптимизациями.

Environment:

    Kernel-mode Driver Framework

--*/

// Включаем базовые заголовки
#include <ntddk.h>
#include <wdf.h>
#include <netadaptercx.h>

// Определения для статистики игровой производительности
typedef struct _I219V_GAMING_PERFORMANCE_STATS {
    UINT64 TotalPacketsSent;
    UINT64 TotalPacketsReceived;
    UINT64 HighPriorityPacketsSent;
    UINT64 HighPriorityPacketsReceived;
    UINT64 LowLatencyPacketsSent;
    UINT64 LowLatencyPacketsReceived;
} I219V_GAMING_PERFORMANCE_STATS, *PI219V_GAMING_PERFORMANCE_STATS;

// Структура контекста устройства
typedef struct _I219V_DEVICE_CONTEXT {
    // Базовые поля
    WDFDEVICE WdfDevice;
    NETADAPTER NetAdapter;
    WDFINTERRUPT WdfInterrupt;
    
    // Ресурсы устройства
    PVOID RegisterBase;
    ULONG RegisterSize;
    PVOID MemoryBase;
    ULONG MemorySize;
    
    // Настройки адаптера
    UINT32 LinkSpeed;
    BOOLEAN FullDuplex;
    BOOLEAN LinkUp;
    
    // Игровые оптимизации
    UINT32 GamingProfile;
    BOOLEAN TrafficPrioritizationEnabled;
    BOOLEAN LatencyReductionEnabled;
    BOOLEAN BandwidthControlEnabled;
    BOOLEAN SmartPowerManagementEnabled;
    UINT32 InterruptModerationRate;
    UINT32 ReceiveBufferSize;
    UINT32 TransmitBufferSize;
    BOOLEAN GameDetectionEnabled;
    BOOLEAN TCPOptimizationEnabled;
    BOOLEAN UDPOptimizationEnabled;
    BOOLEAN NagleAlgorithmEnabled;
    
    // Статистика трафика
    UINT64 GameTrafficCount;
    UINT64 VoiceTrafficCount;
    UINT64 StreamingTrafficCount;
    UINT64 BackgroundTrafficCount;
    
    // Статистика производительности
    I219V_GAMING_PERFORMANCE_STATS GamingPerformanceStats;
    
    // Дополнительные поля для расширенных функций
    PVOID ExtendedContext;
} I219V_DEVICE_CONTEXT, *PI219V_DEVICE_CONTEXT;
