# 💡 TM1637 7-Segment Display Driver for STM32  

A lightweight and efficient **TM1637 display driver** written in **C** for STM32 (HAL-based).  

This library provides an easy way to interface STM32 MCUs with the **TM1637** 7-segment LED display driver — commonly used in digital clocks, voltmeters, and similar projects.  
It supports **1–6 digits**, **brightness control**, and **formatted string display**.

---

## ✨ Features  

- 🔹 Supports **1 to 6 digits** (configurable)
- 🔹 Adjustable **brightness levels (0–8)**
- 🔹 Displays **numbers, characters, and strings**
- 🔹 Supports **formatted printing (`printf`)**
- 🔹 Full **STM32 HAL** compatibility
- 🔹 Simple and portable API design
- 🔹 Example and video tutorial included

---

## ⚙️ Installation  

You can install in two ways:  

### 1. Copy files directly  
Add these files to your STM32 project:  
- `tm1637.h`  
- `tm1637.c`  
- `tm1637_config.h`  

### 2. STM32Cube Pack Installer (Recommended)  
Available in the official pack repo:  
👉 [STM32-PACK](https://github.com/nimaltd/STM32-PACK)

---

## 🛠 CubeMX Setup  

1. **CLK (Clock) Pin** – Configure as **Output Open-Drain**  
2. **DIO (Data I/O) Pin** – Configure as **Output Open-Drain**  
3. No timer or interrupt configuration is needed  

---

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

## 🚀 Quick Start  

### Adjust delay
To ensure latency in 'tm1637_config.h', set it to a large value and then adjust it for faster response.

```c
TM1637_DELAY     10
```


### Define and Initialize a Display  

```c
#include "tm1637.h"

tm1637_t seg = 
{
    .seg_cnt  = 4,             // Number of digits
    .gpio_clk = GPIOA,         // CLK pin port
    .gpio_dat = GPIOA,         // DIO pin port
    .pin_clk  = GPIO_PIN_1,    // CLK pin number
    .pin_data = GPIO_PIN_2,    // DIO pin number
};

tm1637_init(&seg);
tm1637_str(&seg, "1234");
```

---

## 🧰 API Overview  

| Function | Description |
|----------|-------------|
| `tm1637_init()` | Initializes the TM1637 display driver |
| `tm1637_brightness()` | Sets brightness level (0–8) |
| `tm1637_seg()` | Configures number of active 7-segment digits |
| `tm1637_raw()` | Displays raw segment data buffer |
| `tm1637_str()` | Displays a string on the display |
| `tm1637_printf()` | Displays formatted text using `printf` style |
| `tm1637_clear()` | Clears all digits (turns off all segments) |

---

## 🎥 Example & Demo Video ( Previous Version ) 

<div align="center">
  <a href="https://www.youtube.com/watch?v=Fom88WRaH4o">
    <img src="https://img.youtube.com/vi/Fom88WRaH4o/0.jpg" alt="TM1637 Video" width="480">
  </a>
</div>

---

## 💖 Support  

If you find this project useful, please ⭐ the repo and consider supporting me:  

- [![GitHub](https://img.shields.io/badge/GitHub-Follow-black?style=for-the-badge&logo=github)](https://github.com/NimaLTD)  
- [![YouTube](https://img.shields.io/badge/YouTube-Subscribe-red?style=for-the-badge&logo=youtube)](https://youtube.com/@nimaltd)  
- [![Instagram](https://img.shields.io/badge/Instagram-Follow-blue?style=for-the-badge&logo=instagram)](https://instagram.com/github.nimaltd)  
- [![LinkedIn](https://img.shields.io/badge/LinkedIn-Connect-blue?style=for-the-badge&logo=linkedin)](https://linkedin.com/in/nimaltd)  
- [![Email](https://img.shields.io/badge/Email-Contact-red?style=for-the-badge&logo=gmail)](mailto:nima.askari@gmail.com)  
- [![Ko-fi](https://img.shields.io/badge/Ko--fi-Support-orange?style=for-the-badge&logo=ko-fi)](https://ko-fi.com/nimaltd)

---

## 📜 License  

Licensed under the terms in the [LICENSE](./LICENSE.TXT).
