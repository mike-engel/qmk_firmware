// Copyright 2024 Mike Engel (@mike-engel)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

// Not available in keyboard.json
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 1000U

#define SERIAL_USART_FULL_DUPLEX // Enable full duplex operation mode.
#define SERIAL_USART_PIN_SWAP
#define SERIAL_USART_TX_PIN GP2 // USART TX pin
#define SERIAL_USART_RX_PIN GP3 // USART RX pin
