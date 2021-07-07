# TM1637 Display driver for STM32

 *	WebSite:    https://www.github.com/NimaLTD
 *	Instagram:  https://www.instagram.com/github.NimaLTD
 *	LinkedIn:   https://www.linkedin.com/in/NimaLTD
 *	Youtube:    https://www.youtube.com/channel/UCUhY7qY1klJm1d2kulr9ckw

How to use this Library:
* Put all files into your project.
* Set your Configuration in `tm1637_config.h`.
* Select 2 pins on cubemx as gpio open drain.
* Create a strcuture `tm1637_t your_struct`.
* Call `tm1637_init()`.

example:

```
#include "tm1637.h"
tm1637_t disp;

const uint8_t seg_LOAD[4] =  {0x38, 0x5c, 0x77, 0x5e}; // display LOAD
.
.
.
int main()
{
  .
  .
  .
  tm1637_init(&disp, CLK1_GPIO_Port, CLK1_Pin, DIO1_GPIO_Port, DIO1_Pin);
  tm1637_write_segment(&disp, seg_LOAD, 4, 0);
  HAL_Delay(1000);
  tm1637_write_float(&disp, -1.23, 2, 0);
  HAL_Delay(1000);
  tm1637_write_int(&disp, 56, 0);
}

```
