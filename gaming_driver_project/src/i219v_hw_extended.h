#pragma once

/*++

Copyright (c) 2025 Manus AI

Module Name:

    i219v_hw_extended.h

Abstract:

    Расширенный заголовочный файл для работы с аппаратной частью Intel i219-v.
    Содержит дополнительные определения регистров и функций для оптимизации производительности.

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

// Расширенные определения для регистров устройства
#define I219V_REG_EEER        0x0D00  // Energy Efficient Ethernet Register
#define I219V_REG_ERT         0x2008  // Early Receive Threshold
#define I219V_REG_RXPBS       0x2404  // Receive Packet Buffer Size
#define I219V_REG_TXPBS       0x3404  // Transmit Packet Buffer Size
#define I219V_REG_TDFPC       0x3430  // Transmit Data FIFO Packet Count
#define I219V_REG_RFCTL       0x5008  // Receive Filter Control Register
#define I219V_REG_MANC        0x5820  // Management Control Register
#define I219V_REG_FACTPS      0x5B30  // Function Active and Power State to MNG
#define I219V_REG_GSCL_1      0x5B00  // Gigabit Serial Control 1
#define I219V_REG_GSCL_2      0x5B04  // Gigabit Serial Control 2
#define I219V_REG_GSCL_3      0x5B08  // Gigabit Serial Control 3
#define I219V_REG_GSCL_4      0x5B0C  // Gigabit Serial Control 4
#define I219V_REG_GSCN_0      0x5B10  // Gigabit Serial Control 0
#define I219V_REG_GSCN_1      0x5B14  // Gigabit Serial Control 1
#define I219V_REG_GSCN_2      0x5B18  // Gigabit Serial Control 2
#define I219V_REG_GSCN_3      0x5B1C  // Gigabit Serial Control 3
#define I219V_REG_PSRCTL      0x2170  // Packet Split Receive Control
#define I219V_REG_WUC         0x5800  // Wake Up Control
#define I219V_REG_WUFC        0x5808  // Wake Up Filter Control
#define I219V_REG_WUS         0x5810  // Wake Up Status
#define I219V_REG_IPAV        0x5838  // IP Address Valid
#define I219V_REG_FFLT        0x5F00  // Flexible Filter Length Table
#define I219V_REG_FFMT        0x5F08  // Flexible Filter Mask Table
#define I219V_REG_FTFT        0x5F10  // Flexible TCO Filter Table

// Битовые маски для расширенных регистров
#define I219V_EEER_EEE_EN     0x00000001  // Energy Efficient Ethernet Enable
#define I219V_EEER_TX_LPI_EN  0x00000002  // Transmit Low Power Idle Enable
#define I219V_EEER_RX_LPI_EN  0x00000004  // Receive Low Power Idle Enable
#define I219V_EEER_LPI_FC     0x00000008  // LPI Flow Control Enable

#define I219V_MANC_SMBUS_EN   0x00000001  // SMBus Enable
#define I219V_MANC_ASF_EN     0x00000002  // ASF Enable
#define I219V_MANC_ARP_EN     0x00000004  // ARP Response Enable
#define I219V_MANC_RCV_TCO_EN 0x00000008  // Receive TCO Packets Enable
#define I219V_MANC_BLK_PHY_RST_ON_IDE 0x00000010 // Block PHY resets on IDE
#define I219V_MANC_EN_MAC_ADDR_FILTER 0x00000020 // Enable MAC address filtering
#define I219V_MANC_EN_MNG2HOST 0x00000040 // Enable MNG packets to host memory

#define I219V_WUC_APME        0x00000001  // APM Enable
#define I219V_WUC_PME_EN      0x00000002  // PME Enable
#define I219V_WUC_PME_STATUS  0x00000004  // PME Status
#define I219V_WUC_APMPME      0x00000008  // Assert PME on APM Wakeup

// Расширенные функции для оптимизации производительности
NTSTATUS
I219vEnableEEE(
    _In_ PI219V_DEVICE_CONTEXT DeviceContext,
    _In_ BOOLEAN Enable
    );

NTSTATUS
I219vSetPacketBufferSizes(
    _In_ PI219V_DEVICE_CONTEXT DeviceContext,
    _In_ UINT32 ReceiveSize,
    _In_ UINT32 TransmitSize
    );

NTSTATUS
I219vOptimizeInterrupts(
    _In_ PI219V_DEVICE_CONTEXT DeviceContext,
    _In_ UINT32 InterruptModerationRate
    );

NTSTATUS
I219vOptimizeReceiveFilters(
    _In_ PI219V_DEVICE_CONTEXT DeviceContext,
    _In_ BOOLEAN EnableGameFilters
    );

NTSTATUS
I219vOptimizeTransmitDescriptors(
    _In_ PI219V_DEVICE_CONTEXT DeviceContext,
    _In_ BOOLEAN LowLatencyMode
    );

NTSTATUS
I219vOptimizeReceiveDescriptors(
    _In_ PI219V_DEVICE_CONTEXT DeviceContext,
    _In_ BOOLEAN LowLatencyMode
    );

NTSTATUS
I219vSetPowerProfile(
    _In_ PI219V_DEVICE_CONTEXT DeviceContext,
    _In_ BOOLEAN HighPerformance
    );

NTSTATUS
I219vConfigureWakeOnLAN(
    _In_ PI219V_DEVICE_CONTEXT DeviceContext,
    _In_ BOOLEAN Enable
    );

EXTERN_C_END
