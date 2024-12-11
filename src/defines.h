/*
	SlimeVR Code is placed under the MIT license
	Copyright (c) 2021 Eiren Rain

	Permission is hereby granted, free of charge, to any person obtaining a copy
	of this software and associated documentation files (the "Software"), to deal
	in the Software without restriction, including without limitation the rights
	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
	copies of the Software, and to permit persons to whom the Software is
	furnished to do so, subject to the following conditions:

	The above copyright notice and this permission notice shall be included in
	all copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
	THE SOFTWARE.
*/
// ================================================
// See docs for configuration options and examples:
// https://docs.slimevr.dev/firmware/configuring-project.html#2-configuring-definesh
// ================================================

// Set parameters of IMU and board used
#define IMU IMU_BNO085
#define SECOND_IMU IMU
#define IMU_ROTATION DEG_270
#define SECOND_IMU_ROTATION DEG_270

#define BOARD BOARD_XIAO_ESP32C3
#define PRIMARY_IMU_OPTIONAL false
#define SECONDARY_IMU_OPTIONAL true

#define MAX_IMU_COUNT 2

// Axis mapping example
/*
#include "sensors/axisremap.h"
#define BMI160_QMC_REMAP AXIS_REMAP_BUILD(AXIS_REMAP_USE_Y, AXIS_REMAP_USE_XN,
AXIS_REMAP_USE_Z, \ AXIS_REMAP_USE_YN, AXIS_REMAP_USE_X, AXIS_REMAP_USE_Z)

IMU_DESC_ENTRY(IMU_BMP160, PRIMARY_IMU_ADDRESS_ONE, IMU_ROTATION, PIN_IMU_SCL,
PIN_IMU_SDA, PRIMARY_IMU_OPTIONAL, BMI160_QMC_REMAP) \
*/

#ifndef IMU_DESC_LIST
#define IMU_DESC_LIST              \
	IMU_DESC_ENTRY(                \
		IMU,                       \
		PRIMARY_IMU_ADDRESS_ONE,   \
		IMU_ROTATION,              \
		PIN_IMU_SCL,               \
		PIN_IMU_SDA,               \
		PRIMARY_IMU_OPTIONAL,      \
		PIN_IMU_INT                \
	)                              \
	IMU_DESC_ENTRY(                \
		SECOND_IMU,                \
		SECONDARY_IMU_ADDRESS_TWO, \
		SECOND_IMU_ROTATION,       \
		PIN_IMU_SCL,               \
		PIN_IMU_SDA,               \
		SECONDARY_IMU_OPTIONAL,    \
		PIN_IMU_INT_2              \
	)
#endif

// Battery monitoring options (comment to disable):
//   BAT_EXTERNAL for ADC pin,
//   BAT_INTERNAL for internal - can detect only low battery,
//   BAT_MCP3021 for external ADC connected over I2C
#define BATTERY_MONITOR BAT_INTERNAL

// BAT_EXTERNAL definition override
// D1 Mini boards with ESP8266 have internal resistors. For these boards you only have
// to adjust BATTERY_SHIELD_RESISTANCE. For other boards you can now adjust the other
// resistor values. The diagram looks like this:
//   (Battery)--- [BATTERY_SHIELD_RESISTANCE] ---(INPUT_BOARD)---  [BATTERY_SHIELD_R2]
//   ---(ESP32_INPUT)--- [BATTERY_SHIELD_R1] --- (GND)
// #define BATTERY_SHIELD_RESISTANCE 180 //130k BatteryShield, 180k SlimeVR or fill in
// external resistor value in kOhm #define BATTERY_SHIELD_R1 100 // Board voltage
// divider resistor Ain to GND in kOhm #define BATTERY_SHIELD_R2 220 // Board voltage
// divider resistor Ain to INPUT_BOARD in kOhm

// LED configuration:
// Configuration Priority 1 = Highest:
// 1. LED_PIN
// 2. LED_BUILTIN
//
//   LED_PIN
//     - Number or Symbol (D1,..) of the Output
//     - To turn off the LED, set LED_PIN to LED_OFF
//   LED_INVERTED
//     - false for output 3.3V on high
//     - true for pull down to GND on high

// Board-specific configurations
#if BOARD == BOARD_SLIMEVR
#define PIN_IMU_SDA 14
#define PIN_IMU_SCL 12
#define PIN_IMU_INT 16
#define PIN_IMU_INT_2 13
#define PIN_BATTERY_LEVEL 17
#define LED_PIN 2
#define LED_INVERTED true
#ifndef BATTERY_SHIELD_RESISTANCE
#define BATTERY_SHIELD_RESISTANCE 0
#endif
#ifndef BATTERY_SHIELD_R1
#define BATTERY_SHIELD_R1 10
#endif
#ifndef BATTERY_SHIELD_R2
#define BATTERY_SHIELD_R2 40.2
#endif
#elif BOARD == BOARD_XIAO_ESP32C3
  #define PIN_IMU_SDA 6 // D4
  #define PIN_IMU_SCL 7 // D5
  #define PIN_IMU_INT 5 // D3
  #define PIN_IMU_INT_2 10 // D10
  #define LED_PIN 4 // D2 Note: There is no LED_BUILTIN available for the XIAO ESP32C3.
  #define LED_INVERTED false
  #define PIN_BATTERY_LEVEL 2 // D0 / A0
  #ifndef BATTERY_SHIELD_RESISTANCE
    #define BATTERY_SHIELD_RESISTANCE 0
  #endif
  #ifndef BATTERY_SHIELD_R1
    #define BATTERY_SHIELD_R1 100
  #endif
  #ifndef BATTERY_SHIELD_R2
    #define BATTERY_SHIELD_R2 100
  #endif
#endif
