# TM1637 7-Segment Display Driver

## Author & License

- **Author:** Nima Askari  
- **Version:** 2.0.0  
- **License:** See the [`LICENSE`](./LICENSE) file in the root folder.  

## Social & Contact  

[![GitHub](https://img.shields.io/badge/GitHub-000?logo=github&logoColor=white)](https://www.github.com/nimaltd)  
[![LinkedIn](https://img.shields.io/badge/LinkedIn-0077B5?logo=linkedin&logoColor=white)](https://www.linkedin.com/in/nimaltd)  
[![YouTube](https://img.shields.io/badge/YouTube-FF0000?logo=youtube&logoColor=white)](https://www.youtube.com/@nimaltd)  
[![Instagram](https://img.shields.io/badge/Instagram-E4405F?logo=instagram&logoColor=white)](https://instagram.com/github.nimaltd)  

© 2025 Nima Askari - NimaLTD. All rights reserved.  

---

## TM1637 7-Segment Display Driver Help  

### Pin Connections  

| Display Segment | TM1637 Pin |
|----------------|-----------|
| A             | SEG1      |
| B             | SEG2      |
| C             | SEG3      |
| D             | SEG4      |
| E             | SEG5      |
| F             | SEG6      |
| G             | SEG7      |
| . (Dot)       | SEG8      |

---

## STM32CubeMX Configuration  

Set **CLK (Clock)** and **DIO (Data I/O)** pins as:  
- **Mode:** Output Open Drain  
- **Select:** High-level initialization  

---

## Usage  

### 1. Declare a Display Instance  
Create an instance for each display:  

```c
tm1637_t seg = 
{
    .seg_cnt = 4,
    .gpio_clk = GPIOA,
    .gpio_dat = GPIOA,
    .pin_clk = GPIO_PIN_1,
    .pin_data = GPIO_PIN_2,
};
