
/*
 * @file        tm1637.h
 * @brief       tm1637 7seg driver
 * @author      Nima Askari
 * @version     3.0.0
 * @license     See the LICENSE file in the root folder.
 *
 * @note        All my libraries are dual-licensed.
 *              Please review the licensing terms before using them.
 *              For any inquiries, feel free to contact me.
 *
 * @github      https://www.github.com/nimaltd
 * @linkedin    https://www.linkedin.com/in/nimaltd
 * @youtube     https://www.youtube.com/@nimaltd
 * @instagram   https://instagram.com/github.nimaltd
 *
 * Copyright (C) 2025 Nima Askari - NimaLTD. All rights reserved.
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
/** Typedef/Struct/Enum **/
/*************************************************************************************************/

/*************************************************************************************************/
/* Error values returned by OneWire operations */
typedef enum
{
  TM1637_ERR_NONE     = 0,  /* No error */
  TM1637_ERR_ERROR,         /* Acknowledge error */

} tm1637_err_t;

/*************************************************************************************************/
/* Main driver handle containing config */
typedef struct
{
  GPIO_TypeDef        *gpio_clk;
  GPIO_TypeDef        *gpio_dat;
  uint16_t            pin_clk;
  uint16_t            pin_dat;
  uint8_t             seg_cnt;

} tm1637_t;

/*************************************************************************************************/
/** API Functions **/
/*************************************************************************************************/

/* Initializes the TM1637 display driver */
tm1637_err_t  tm1637_init(tm1637_t *handle);

/* Sets the brightness level of the TM1637 display */
tm1637_err_t  tm1637_brightness(tm1637_t *handle, uint8_t brightness_0_8);

/* Sets the number of 7-segment digits to be used on the TM1637 display */
void          tm1637_seg(tm1637_t *handle, uint8_t seg_1_6);

/* Displays raw segment data on the TM1637 display */
tm1637_err_t  tm1637_raw(tm1637_t *handle, const uint8_t *data);

/* Displays raw segment data on the TM1637 display */
tm1637_err_t  tm1637_str(tm1637_t *handle, const char *str);

/* Displays a formatted string on the TM1637 7-segment display */
tm1637_err_t  tm1637_printf(tm1637_t *handle, const char *format, ...);

/* Clears the TM1637 display by setting all segments to off */
tm1637_err_t  tm1637_clear(tm1637_t *handle);

/*************************************************************************************************/
/** End of File **/
/*************************************************************************************************/

#ifdef __cplusplus
}
#endif
#endif /* _TM1637_H_ */
