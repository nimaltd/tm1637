
/*
 * @file        TM1637
 * @author      Nima Askari
 * @version     2.0.0
 * @license     See the LICENSE file in the root folder.
 *
 * @github      https://www.github.com/nimaltd
 * @linkedin    https://www.linkedin.com/in/nimaltd
 * @youtube     https://www.youtube.com/@nimaltd
 * @instagram   https://instagram.com/github.nimaltd
 *
 * Copyright (C) 2025 Nima Askari - NimaLTD. All rights reserved.
 *
 */

/*
 *  TM1637 7-Segment Display Driver Help
 *
 *  Pin Connections:
 *  Display Segment | TM1637 Pin
 *  ----------------|-----------
 *          A       |   SEG1
 *          B       |   SEG2
 *          C       |   SEG3
 *          D       |   SEG4
 *          E       |   SEG5
 *          F       |   SEG6
 *          G       |   SEG7
 *          .       |   SEG8
 *
 *  STM32CubeMX Configuration:
 *  Set CLK (Clock) and DIO (Data I/O) pins as:
 *  - Mode: Output Open Drain
 *  - Select High level initialization
 *
 *  Usage:
 *  1. Declare a display instance:
 *    one instance per display
 *    tm1637_t seg =
 *    {
 *      .seg_cnt = 4,
 *      .gpio_clk = GPIOA,
 *      .gpio_dat = GPIOA,
 *      .pin_clk = GPIO_PIN_1,
 *      .pin_data = GPIO_PIN_2,
 *    };
 *
 *  2. Initialize with GPIO settings:
 *    tm1637_init(&display);
 *
 *  3. Use display functions.
 *
 *  Notes:
 *  - Always initialize with tm1637_init() before other functions
 *  - Ensure proper pull-up resistors on both CLK and DIO lines
 *  - Maximum 6-digit 7-segment displays are supported
 */

#ifndef _TM1637_H_
#define _TM1637_H_

#ifdef __cplusplus
extern "C" {
#endif

/*************************************************************************************************/
/** Includes **/
/*************************************************************************************************/

#include <stdarg.h>
#include <stdio.h>
#include <stdbool.h>
#include "main.h"

/*************************************************************************************************/
/** Macros and Definitions **/
/*************************************************************************************************/

typedef enum
{
  TM1637_ERR_NONE                   = 0,  /* No error */
  TM1637_ERR_ERROR,                       /* Acknowledge error */

} tm1637_err_t;

/*************************************************************************************************/
/** Strucs and Enums **/
/*************************************************************************************************/

typedef struct
{
  GPIO_TypeDef        *gpio_clk;
  GPIO_TypeDef        *gpio_dat;
  uint16_t            pin_clk;
  uint16_t            pin_dat;
  uint8_t             seg_cnt;

} tm1637_t;

/*************************************************************************************************/
/** Function Declarations **/
/*************************************************************************************************/

tm1637_err_t  tm1637_init(tm1637_t *handle);
tm1637_err_t  tm1637_brightness(tm1637_t *handle, uint8_t brightness_0_8);
void          tm1637_seg(tm1637_t *handle, uint8_t seg_1_6);
tm1637_err_t  tm1637_disp_raw(tm1637_t *handle, const uint8_t *data);
tm1637_err_t  tm1637_disp_str(tm1637_t *handle, const char *str);
tm1637_err_t  tm1637_disp_printf(tm1637_t *handle, const char *format, ...);
tm1637_err_t  tm1637_disp_clear(tm1637_t *handle);

/*************************************************************************************************/
/** End of File **/
/*************************************************************************************************/

#ifdef __cplusplus
}
#endif
#endif /* _TM1637_H_ */
