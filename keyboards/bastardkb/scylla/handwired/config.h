// Copyright 2022 Mike Engel (@mike-engel)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "config_common.h"

#undef DIODE_DIRECTION

/* Handedness. */
#define MASTER_LEFT

/* serial.c configuration (for split keyboard). */
/* https://docs.qmk.fm/#/feature_split_keyboard */
#define USE_SERIAL
#define SOFT_SERIAL_PIN D0 /* D1 also available */
