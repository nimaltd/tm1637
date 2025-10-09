
/*
 * @file        tm1637.c
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

/*************************************************************************************************/
/** Includes **/
/*************************************************************************************************/

#include "tm1637.h"
#include "tm1637_config.h"

/*************************************************************************************************/
/** Macros and Definitions **/
/*************************************************************************************************/

#define TM1637_COMM1      0x40
#define TM1637_COMM2      0xC0
#define TM1637_COMM3_OFF  0x80
#define TM1637_COMM3_ON   0x88
#define TM1637_SEG_MAX    6

/*************************************************************************************************/
/** Private Function prototype **/
/*************************************************************************************************/

/* Delay for generating pulse */
static void         tm1637_delay(void);

/* Generate Start Signal */
static void         tm1637_start(tm1637_t *handle);

/* Generate Stop Signal */
static void         tm1637_stop(tm1637_t *handle);

/* Write data to chip */
static tm1637_err_t tm1637_write(tm1637_t *handle, uint8_t data);

/*************************************************************************************************/
/** Function Implementations **/
/*************************************************************************************************/

/*************************************************************************************************/
/**
 * @brief Initializes the TM1637 display driver.
 * @param[in] handle Pointer to the TM1637 handle structure.
 * @return tm1637_err_t Error code indicating success or failure.
 */
tm1637_err_t tm1637_init(tm1637_t *handle)
{
  tm1637_err_t err;
  assert_param(handle != NULL);
  assert_param(IS_GPIO_PIN(pin_clk));
  assert_param(IS_GPIO_PIN(pin_dat));
  assert_param(handle->gpio_dat != NULL);
  assert_param(handle->gpio_clk != NULL);

  /* Set All pins to high */
  handle->gpio_clk->BSRR = handle->pin_clk;
  handle->gpio_dat->BSRR = handle->pin_dat;

  /* Send TM1637_COMM1 */
  tm1637_start(handle);
  err = tm1637_write(handle, TM1637_COMM1);
  tm1637_stop(handle);
  return err;
}

/*************************************************************************************************/
/**
 * @brief Sets the brightness level of the TM1637 display.
 * @param[in] handle Pointer to the TM1637 handle structure.
 * @param[in] brightness_0_8 Brightness level (0-8), where 0 turns off the display.
 * @return tm1637_err_t Error code indicating success or failure.
 */
tm1637_err_t tm1637_brightness(tm1637_t *handle, uint8_t brightness_0_8)
{
  tm1637_err_t err;
  assert_param(handle != NULL);

  /* Map brightness */
  uint8_t tmp = brightness_0_8 > 8 ? 8 : brightness_0_8;
  tmp = (brightness_0_8 == 0) ? TM1637_COMM3_OFF : TM1637_COMM3_ON;
  if (brightness_0_8 > 0)
  {
    brightness_0_8--;
  }

  /* Send Brightness */
  tm1637_start(handle);
  err = tm1637_write(handle, tmp | brightness_0_8);
  tm1637_stop(handle);
  return err;
}

/*************************************************************************************************/
/**
 * @brief Sets the number of 7-segment digits to be used on the TM1637 display.
 * @param[in] handle Pointer to the TM1637 handle structure.
 * @param[in] seg_1_6 Number of segments (1-6). Values greater than 6 are capped at 6, and 0 is set to 1.
 */
void tm1637_seg(tm1637_t *handle, uint8_t seg_1_6)
{
  assert_param(handle != NULL);

  /* Set segment value */
  handle->seg_cnt = (seg_1_6 > 6) ? 6 : seg_1_6;
  handle->seg_cnt = (handle->seg_cnt == 0) ? 1 : handle->seg_cnt;
}

/*************************************************************************************************/
/**
 * @brief Displays raw segment data on the TM1637 display.
 * @param[in] handle Pointer to the TM1637 handle structure.
 * @param[in] data Pointer to an array containing raw segment data.
 *
 * @return tm1637_err_t Error code indicating success or failure.
 */
tm1637_err_t tm1637_raw(tm1637_t *handle, const uint8_t *data)
{
  tm1637_err_t err;
  assert_param(handle != NULL);

  /* Send TM1637_COMM2 */
  tm1637_start(handle);
  err = tm1637_write(handle, TM1637_COMM2);
  if (err != TM1637_ERR_NONE)
  {
    return TM1637_ERR_ERROR;
  }

  /* Send all data */
  for (uint8_t i = 0; i < handle->seg_cnt; i++)
  {
    err = tm1637_write(handle, data[i]);
    if (err != TM1637_ERR_NONE)
    {
      break;
    }
  }
  tm1637_stop(handle);
  return err;
}

/*************************************************************************************************/
/**
 * @brief Displays a string on the TM1637 7-segment display.
 * @param[in] handle Pointer to the TM1637 handle structure.
 * @param[in] str Pointer to a null-terminated string to display.
 *               Supports numbers (0-9), letters (if enabled), '-' and '.' for decimal points.
 * @return tm1637_err_t Error code indicating success or failure.
 */
tm1637_err_t tm1637_str(tm1637_t *handle, const char *str)
{
  uint8_t buff[TM1637_SEG_MAX + 1] = {0};
  char *str_tmp = (char*)str;
  assert_param(handle != NULL);

  for (int i = 0; i < handle->seg_cnt; i++)
  {
    switch (*str_tmp)
    {
    case '0':
      buff[i] = 0x3f;
      break;
    case '1':
      buff[i] = 0x06;
      break;
    case '2':
      buff[i] = 0x5b;
      break;
    case '3':
      buff[i] = 0x4f;
      break;
    case '4':
      buff[i] = 0x66;
      break;
    case '5':
      buff[i] = 0x6d;
      break;
    case '6':
      buff[i] = 0x7d;
      break;
    case '7':
      buff[i] = 0x07;
      break;
    case '8':
      buff[i] = 0x7f;
      break;
    case '9':
      buff[i] = 0x6f;
      break;
    case '-':
      buff[i] = 0x40;
      break;
#if (TM1637_ENABLE_ALFABET == 1)
    case 'A':
    case 'a':
      buff[i] = 0x77;
      break;
    case 'B':
    case 'b':
      buff[i] = 0x7C;
      break;
    case 'C':
    case 'c':
      buff[i] = 0x58;
      break;
    case 'D':
    case 'd':
      buff[i] = 0x5E;
      break;
    case 'E':
    case 'e':
      buff[i] = 0x79;
      break;
    case 'F':
    case 'f':
      buff[i] = 0x71;
      break;
    case 'G':
    case 'g':
      buff[i] = 0x6f;
      break;
    case 'H':
    case 'h':
      buff[i] = 0x76;
      break;
    case 'I':
    case 'i':
      buff[i] = 0x06;
      break;
    case 'J':
    case 'j':
      buff[i] = 0x0E;
      break;
    case 'L':
    case 'l':
      buff[i] = 0x38;
      break;
    case 'N':
    case 'n':
      buff[i] = 0x54;
      break;
    case 'O':
    case 'o':
      buff[i] = 0x5C;
      break;
    case 'P':
    case 'p':
      buff[i] = 0x73;
      break;
    case 'Q':
    case 'q':
      buff[i] = 0x67;
      break;
    case 'R':
    case 'r':
      buff[i] = 0x50;
      break;
    case 'S':
    case 's':
      buff[i] = 0x6D;
      break;
    case 'T':
    case 't':
      buff[i] = 0x78;
      break;
    case 'U':
    case 'u':
      buff[i] = 0x1C;
      break;
    case 'Y':
    case 'y':
      buff[i] = 0x6E;
      break;
#endif
    default:
      buff[i] = 0;
      break;
    }
    if (*(str_tmp + 1) == '.')
    {
      buff[i] |= 0x80;
      str_tmp++;
    }
    str_tmp++;
  }

  /* Write to tm1637 */
  return tm1637_raw(handle, buff);
}

/*************************************************************************************************/
/**
 * @brief Displays a formatted string on the TM1637 7-segment display.
 * @param[in] handle Pointer to the TM1637 handle structure.
 * @param[in] format Format string (printf-style) to display.
 * @param[in] ... Additional arguments for the formatted string.
 * @return tm1637_err_t Error code indicating success or failure.
 */
tm1637_err_t  tm1637_printf(tm1637_t *handle, const char *format, ...)
{
  char buff[TM1637_SEG_MAX + 1] = {0};
  assert_param(handle != NULL);

  va_list args;
  va_start(args, format);
  int chars_written = vsnprintf(buff, sizeof(buff), format, args);
  va_end(args);
  if (chars_written < 0)
  {
    return TM1637_ERR_ERROR;
  }
  return tm1637_str(handle, buff);
}

/*************************************************************************************************/
/**
 * @brief Clears the TM1637 display by setting all segments to off.
 * @param[in] handle Pointer to the TM1637 handle structure.
 * @return tm1637_err_t Error code indicating success or failure.
 */
tm1637_err_t tm1637_clear(tm1637_t *handle)
{
  const uint8_t buff[TM1637_SEG_MAX] = {0};
  assert_param(handle != NULL);

  /* Write all 0 */
  return tm1637_raw(handle, buff);
}

/*************************************************************************************************/
/** Private Function Implementations **/
/*************************************************************************************************/

/*************************************************************************************************/
/**
 * @brief Provides a delay for the TM1637 display operations.
 *        This function uses a simple loop to generate a delay for controlling the timing
 *        of the TM1637 display operations.
 */
static void tm1637_delay(void)
{
  for (uint32_t i = 0; i < TM1637_DELAY; i++)
  {
    __NOP();
  }
}

/*************************************************************************************************/
/**
 * @brief Generates a start condition for the TM1637 communication.
 *        This function generates a start condition by toggling the clock and data lines.
 *        The start condition is necessary to begin communication with the TM1637 display.
 * @param[in] handle Pointer to the TM1637 handle structure.
 */
static void tm1637_start(tm1637_t *handle)
{
  assert_param(handle != NULL);

  /* Raise CLK/DAT high */
  handle->gpio_clk->BSRR = handle->pin_clk;
  handle->gpio_dat->BSRR = handle->pin_dat;
  tm1637_delay();

  /* Pull DAT low to start */
  handle->gpio_dat->BSRR = handle->pin_dat << 16;
  tm1637_delay();
}

/*************************************************************************************************/
/**
 * @brief Generates a stop condition for the TM1637 communication.
 *        This function generates a stop condition by toggling the data and clock lines.
 *        The stop condition signals the end of communication with the TM1637 display.
 * @param[in] handle Pointer to the TM1637 handle structure.
 */
static void tm1637_stop(tm1637_t *handle)
{
  assert_param(handle != NULL);

  /* Pull DAT low */
  handle->gpio_dat->BSRR = handle->pin_dat << 16;
  tm1637_delay();

  /* Raise CLK high */
  handle->gpio_clk->BSRR = handle->pin_clk;
  tm1637_delay();

  /* Release DAT high (STOP) */
  handle->gpio_dat->BSRR = handle->pin_dat;
  tm1637_delay();
}

/*************************************************************************************************/
/**
 * @brief Writes a byte of data to the TM1637 display.
 *        This function sends a single byte of data to the TM1637 display, bit by bit,
 *        through the data and clock lines. It also handles the acknowledgment signal
 *        from the TM1637 after sending the data.
 * @param[in] handle Pointer to the TM1637 handle structure.
 * @param[in] data The byte of data to send to the display.
 * @return tm1637_err_t Error code indicating success or failure.
 */
static tm1637_err_t tm1637_write(tm1637_t *handle, uint8_t data)
{
  uint8_t tmp = data;
  assert_param(handle != NULL);

  /* Send each bit (LSB first) */
  for (int i = 0; i < 8; i++)
  {
    handle->gpio_clk->BSRR = handle->pin_clk << 16;
    tm1637_delay();
    handle->gpio_dat->BSRR = (tmp & 0x01) ? handle->pin_dat : (handle->pin_dat << 16);
    tm1637_delay();
    handle->gpio_clk->BSRR = handle->pin_clk;
    tm1637_delay();
    tmp >>= 1;
  }
  handle->gpio_clk->BSRR = handle->pin_clk << 16;
  handle->gpio_dat->BSRR = handle->pin_dat;
  tm1637_delay();

  /* Generate clock pulse for ACK phase */
  handle->gpio_clk->BSRR = handle->pin_clk;
  tm1637_delay();
  tm1637_delay();

  /* Read ACK bit from TM1637 — data line is released and clock is toggled to sample response */
  tmp = (handle->gpio_dat->IDR & handle->pin_dat) ? 1 : 0;
  handle->gpio_dat->BSRR = (tmp == 0) ? (handle->pin_dat << 16) : handle->pin_dat;
  tm1637_delay();
  handle->gpio_clk->BSRR = handle->pin_clk << 16;
  tm1637_delay();
  return (tm1637_err_t)tmp;
}

/*************************************************************************************************/
/** End of File **/
/*************************************************************************************************/
