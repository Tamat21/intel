#pragma once

/*++

Copyright (c) 2025 Manus AI

Module Name:

    Trace.h

Abstract:

    Заголовочный файл для трассировки и отладки драйвера Intel i219-v с игровыми оптимизациями.

Environment:

    Kernel-mode Driver Framework

--*/

// Включаем базовые заголовки
#include <ntddk.h>
#include <wdf.h>

// Определение GUID для трассировки
// {5E0D9C94-3A19-4D1F-A3B3-6C0FAFC7CF3F}
#define WPP_CONTROL_GUIDS \
    WPP_DEFINE_CONTROL_GUID( \
        I219vTraceGuid, (5E0D9C94,3A19,4D1F,A3B3,6C0FAFC7CF3F), \
        WPP_DEFINE_BIT(TRACE_DRIVER)     /* bit  0 = 0x00000001 */ \
        WPP_DEFINE_BIT(TRACE_DEVICE)     /* bit  1 = 0x00000002 */ \
        WPP_DEFINE_BIT(TRACE_ADAPTER)    /* bit  2 = 0x00000004 */ \
        WPP_DEFINE_BIT(TRACE_QUEUE)      /* bit  3 = 0x00000008 */ \
        WPP_DEFINE_BIT(TRACE_HARDWARE)   /* bit  4 = 0x00000010 */ \
        WPP_DEFINE_BIT(TRACE_GAMING)     /* bit  5 = 0x00000020 */ \
        WPP_DEFINE_BIT(TRACE_PERFORMANCE)/* bit  6 = 0x00000040 */ \
        )

// Определение флагов трассировки
#define TRACE_DRIVER      0x00000001
#define TRACE_DEVICE      0x00000002
#define TRACE_ADAPTER     0x00000004
#define TRACE_QUEUE       0x00000008
#define TRACE_HARDWARE    0x00000010
#define TRACE_GAMING      0x00000020
#define TRACE_PERFORMANCE 0x00000040

// Определение уровней трассировки
#define TRACE_LEVEL_FATAL        0
#define TRACE_LEVEL_ERROR        1
#define TRACE_LEVEL_WARNING      2
#define TRACE_LEVEL_INFORMATION  3
#define TRACE_LEVEL_VERBOSE      4

// Макросы для трассировки
#define TraceEvents(level, flags, ...) \
    WPP_LEVEL_FLAGS_LOGGER(flags, level) WPP_LEVEL_FLAGS_ENABLED(flags, level) ? \
    WPP_LEVEL_FLAGS_LOGGER(flags, level)(WPP_LEVEL_FLAGS_ARGS(flags, level) __VA_ARGS__) : 0

// Включаем поддержку WPP
// Вторая (пустая) строка "#define WPP_CONTROL_GUIDS" была удалена, так как WPP_CONTROL_GUIDS определяется выше.
#include <WppRecorder.h>

// Определение макросов для записи в журнал событий
#define EventWriteDriverStart() \
    TraceEvents(TRACE_LEVEL_INFORMATION, TRACE_DRIVER, "Driver started")

#define EventWriteDriverStop() \
    TraceEvents(TRACE_LEVEL_INFORMATION, TRACE_DRIVER, "Driver stopped")

#define EventWriteDeviceAdd() \
    TraceEvents(TRACE_LEVEL_INFORMATION, TRACE_DEVICE, "Device added")

#define EventWriteDeviceRemove() \
    TraceEvents(TRACE_LEVEL_INFORMATION, TRACE_DEVICE, "Device removed")

#define EventWriteAdapterStart() \
    TraceEvents(TRACE_LEVEL_INFORMATION, TRACE_ADAPTER, "Adapter started")

#define EventWriteAdapterStop() \
    TraceEvents(TRACE_LEVEL_INFORMATION, TRACE_ADAPTER, "Adapter stopped")

#define EventWriteQueueCreate() \
    TraceEvents(TRACE_LEVEL_INFORMATION, TRACE_QUEUE, "Queue created")

#define EventWriteQueueDestroy() \
    TraceEvents(TRACE_LEVEL_INFORMATION, TRACE_QUEUE, "Queue destroyed")

#define EventWriteHardwareInitialize() \
    TraceEvents(TRACE_LEVEL_INFORMATION, TRACE_HARDWARE, "Hardware initialized")

#define EventWriteHardwareShutdown() \
    TraceEvents(TRACE_LEVEL_INFORMATION, TRACE_HARDWARE, "Hardware shutdown")

#define EventWriteGamingProfileChange(profile) \
    TraceEvents(TRACE_LEVEL_INFORMATION, TRACE_GAMING, "Gaming profile changed to %d", profile)

#define EventWritePerformanceStats(sent, received) \
    TraceEvents(TRACE_LEVEL_INFORMATION, TRACE_PERFORMANCE, "Performance stats: sent=%llu, received=%llu", sent, received)
