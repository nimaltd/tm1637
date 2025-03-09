# TM1637 7-Segment Display Driver

## Author & License

- **Author:** Nima Askari  
- **Version:** 2.0.0  
- **License:** See the [`LICENSE`](LICENSE.TXT) file in the root folder.  

---

### Connect with Me, Support Me  

- [![YouTube](https://img.shields.io/badge/YouTube-Subscribe-red?style=for-the-badge&logo=youtube)](https://youtube.com/@nimaltd)  
- [![Instagram](https://img.shields.io/badge/Instagram-Follow-blue?style=for-the-badge&logo=instagram)](https://instagram.com/github.nimaltd)  
- [![LinkedIn](https://img.shields.io/badge/LinkedIn-Connect-blue?style=for-the-badge&logo=linkedin)](https://linkedin.com/in/nimaltd)  
- [![Email](https://img.shields.io/badge/Email-Contact-red?style=for-the-badge&logo=gmail)](mailto:nima.askari@gmail.com)  
- [![Ko-fi](https://img.shields.io/badge/Ko--fi-Support-orange?style=for-the-badge&logo=ko-fi)](https://ko-fi.com/nimaltd)  

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
.
.
.
tm1637_init(&seg);
tm1637_disp_str(&seg, "1234");
```
