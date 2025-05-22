#pragma once

/*++

Copyright (c) 2025 Manus AI

Module Name:

    i219v_hw.h

Abstract:

    Заголовочный файл для работы с аппаратной частью Intel i219-v.
    Содержит определения регистров, битовых масок и функций для взаимодействия с оборудованием.

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

// Определения для регистров устройства
#define I219V_REG_CTRL        0x0000  // Device Control Register
#define I219V_REG_STATUS      0x0008  // Device Status Register
#define I219V_REG_EECD        0x0010  // EEPROM/Flash Control/Data Register
#define I219V_REG_EERD        0x0014  // EEPROM Read Register
#define I219V_REG_CTRL_EXT    0x0018  // Extended Device Control Register
#define I219V_REG_MDIC        0x0020  // MDI Control Register
#define I219V_REG_FCAL        0x0028  // Flow Control Address Low
#define I219V_REG_FCAH        0x002C  // Flow Control Address High
#define I219V_REG_FCT         0x0030  // Flow Control Type
#define I219V_REG_KUMCTRLSTA  0x0034  // MAC-PHY Interface
#define I219V_REG_RXCSUM      0x005C  // Receive Checksum Control
#define I219V_REG_TXCW        0x0178  // Transmit Configuration Word
#define I219V_REG_RXCW        0x0180  // Receive Configuration Word
#define I219V_REG_TCTL        0x0400  // Transmit Control Register
#define I219V_REG_TIPG        0x0410  // Transmit Inter Packet Gap
#define I219V_REG_LEDCTL      0x0E00  // LED Control
#define I219V_REG_PBA         0x1000  // Packet Buffer Allocation
#define I219V_REG_ICR         0x1500  // Interrupt Cause Read
#define I219V_REG_ITR         0x1504  // Interrupt Throttling Rate
#define I219V_REG_ICS         0x1508  // Interrupt Cause Set
#define I219V_REG_IMS         0x150C  // Interrupt Mask Set/Read
#define I219V_REG_IMC         0x1510  // Interrupt Mask Clear
#define I219V_REG_IAM         0x1514  // Interrupt Acknowledge Auto Mask
#define I219V_REG_RCTL        0x0100  // Receive Control Register
#define I219V_REG_FCRTL       0x2160  // Flow Control Receive Threshold Low
#define I219V_REG_FCRTH       0x2168  // Flow Control Receive Threshold High
#define I219V_REG_RDBAL       0x2800  // Receive Descriptor Base Address Low
#define I219V_REG_RDBAH       0x2804  // Receive Descriptor Base Address High
#define I219V_REG_RDLEN       0x2808  // Receive Descriptor Length
#define I219V_REG_RDH         0x2810  // Receive Descriptor Head
#define I219V_REG_RDT         0x2818  // Receive Descriptor Tail
#define I219V_REG_RXDCTL      0x2828  // Receive Descriptor Control
#define I219V_REG_TDBAL       0x3800  // Transmit Descriptor Base Address Low
#define I219V_REG_TDBAH       0x3804  // Transmit Descriptor Base Address High
#define I219V_REG_TDLEN       0x3808  // Transmit Descriptor Length
#define I219V_REG_TDH         0x3810  // Transmit Descriptor Head
#define I219V_REG_TDT         0x3818  // Transmit Descriptor Tail
#define I219V_REG_TXDCTL      0x3828  // Transmit Descriptor Control
#define I219V_REG_CRCERRS     0x4000  // CRC Error Count
#define I219V_REG_ALGNERRC    0x4004  // Alignment Error Count
#define I219V_REG_RXERRC      0x400C  // RX Error Count
#define I219V_REG_MPC         0x4010  // Missed Packets Count
#define I219V_REG_GPRC        0x4074  // Good Packets Received Count
#define I219V_REG_GPTC        0x4080  // Good Packets Transmitted Count
#define I219V_REG_STATCTL     0x4014  // Statistics Control Register

// Битовые маски для регистров
#define I219V_CTRL_FD         0x00000001  // Full Duplex
#define I219V_CTRL_LRST       0x00000008  // Link Reset
#define I219V_CTRL_ASDE       0x00000020  // Auto-Speed Detection Enable
#define I219V_CTRL_SLU        0x00000040  // Set Link Up
#define I219V_CTRL_SPEED_MASK 0x00000300  // Speed selection mask
#define I219V_CTRL_SPEED_10   0x00000000  // 10Mbps
#define I219V_CTRL_SPEED_100  0x00000100  // 100Mbps
#define I219V_CTRL_SPEED_1000 0x00000200  // 1000Mbps
#define I219V_CTRL_FRCSPD     0x00000800  // Force Speed
#define I219V_CTRL_FRCDPX     0x00001000  // Force Duplex
#define I219V_CTRL_RST        0x04000000  // Device Reset
#define I219V_CTRL_RFCE       0x08000000  // Receive Flow Control Enable
#define I219V_CTRL_TFCE       0x10000000  // Transmit Flow Control Enable

#define I219V_STATUS_FD       0x00000001  // Full Duplex
#define I219V_STATUS_LU       0x00000002  // Link Up
#define I219V_STATUS_SPEED    0x000000C0  // Speed indication
#define I219V_STATUS_SPEED_10 0x00000000  // 10Mbps
#define I219V_STATUS_SPEED_100 0x00000040 // 100Mbps
#define I219V_STATUS_SPEED_1000 0x00000080 // 1000Mbps

#define I219V_RCTL_EN         0x00000002  // Receiver Enable
#define I219V_RCTL_SBP        0x00000004  // Store Bad Packets
#define I219V_RCTL_UPE        0x00000008  // Unicast Promiscuous Enable
#define I219V_RCTL_MPE        0x00000010  // Multicast Promiscuous Enable
#define I219V_RCTL_LBM_MASK   0x000000C0  // Loopback Mode
#define I219V_RCTL_LBM_NONE   0x00000000  // No Loopback
#define I219V_RCTL_LBM_PHY    0x000000C0  // PHY or external SerDes loopback
#define I219V_RCTL_RDMTS_MASK 0x00000300  // Receive Descriptor Minimum Threshold Size
#define I219V_RCTL_RDMTS_HALF 0x00000000  // Threshold is 1/2 of RDLEN
#define I219V_RCTL_RDMTS_QUAT 0x00000100  // Threshold is 1/4 of RDLEN
#define I219V_RCTL_RDMTS_EIGTH 0x00000200 // Threshold is 1/8 of RDLEN
#define I219V_RCTL_BAM        0x00008000  // Broadcast Accept Mode
#define I219V_RCTL_SECRC      0x04000000  // Strip Ethernet CRC

#define I219V_TCTL_EN         0x00000002  // Transmit Enable
#define I219V_TCTL_PSP        0x00000008  // Pad Short Packets
#define I219V_TCTL_CT         0x00000ff0  // Collision Threshold
#define I219V_TCTL_COLD       0x003ff000  // Collision Distance
#define I219V_TCTL_SWXOFF     0x00400000  // Software XOFF Transmission
#define I219V_TCTL_RTLC       0x01000000  // Re-transmit on Late Collision

// Функции для работы с регистрами
UINT32
I219vReadRegister(
    _In_ PI219V_DEVICE_CONTEXT DeviceContext,
    _In_ UINT32 Register
    );

VOID
I219vWriteRegister(
    _In_ PI219V_DEVICE_CONTEXT DeviceContext,
    _In_ UINT32 Register,
    _In_ UINT32 Value
    );

// Функции для работы с PHY
UINT16
I219vReadPhy(
    _In_ PI219V_DEVICE_CONTEXT DeviceContext,
    _In_ UINT32 PhyRegister
    );

VOID
I219vWritePhy(
    _In_ PI219V_DEVICE_CONTEXT DeviceContext,
    _In_ UINT32 PhyRegister,
    _In_ UINT16 Value
    );

// Функции для инициализации и управления оборудованием
NTSTATUS
I219vInitializeHardware(
    _In_ PI219V_DEVICE_CONTEXT DeviceContext
    );

NTSTATUS
I219vResetHardware(
    _In_ PI219V_DEVICE_CONTEXT DeviceContext
    );

NTSTATUS
I219vSetLinkSpeed(
    _In_ PI219V_DEVICE_CONTEXT DeviceContext,
    _In_ UINT32 Speed,
    _In_ BOOLEAN FullDuplex
    );

NTSTATUS
I219vGetLinkStatus(
    _In_ PI219V_DEVICE_CONTEXT DeviceContext,
    _Out_ BOOLEAN* LinkUp,
    _Out_ UINT32* Speed,
    _Out_ BOOLEAN* FullDuplex
    );

NTSTATUS
I219vSetupReceiveResources(
    _In_ PI219V_DEVICE_CONTEXT DeviceContext
    );

NTSTATUS
I219vSetupTransmitResources(
    _In_ PI219V_DEVICE_CONTEXT DeviceContext
    );

NTSTATUS
I219vEnableInterrupts(
    _In_ PI219V_DEVICE_CONTEXT DeviceContext
    );

NTSTATUS
I219vDisableInterrupts(
    _In_ PI219V_DEVICE_CONTEXT DeviceContext
    );

EXTERN_C_END
