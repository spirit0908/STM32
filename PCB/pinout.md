# Pinout

Pin |  Name  | Port/Pin | Analog |   Special function    |   PWM   |    Board    |  Function
----|--------|----------|--------|-----------------------|---------|-------------|----------
 1  | +3.3V  |          |        |                       |         |             |
 2  |  GND   |          |        |                       |         |             |
 3  |  +5V   |          |        |                       |         |             |
 4  |  PB9   |   PB_9   |   D14  | CAN1 TD / I2C1 SDA    |         |             |
 5  |  PB8   |   PB_8   |   D15  | CAN1 RD / I2C1 SCL    |         |             |
 6  |  PB7   |   PB_7   |        | Serial1 RX / I2C1 SDA |         |             |
 7  |  PB6   |   PB_6   |   D10  | Serial1 TX / I2C1 SCL |         |             |
 8  |  PB5   |   PB_5   |   D4   |   SPI1 MOSI           | PWM3/2  |   CAN_RS    | Digital Output
 9  |  PB4   |   PB_4   |   D5   |   SPI1 MISO           | PWM3/1  |             |
10  |  PB3   |   PB_3   |   D3   |   SPI1 SCK            | PWM2/2  |   LCD_CLK   | Digital Output
11  |  PA15  |   PA_15  |        | SPI1 NSS              | PWM2/1  |           l |
12  |  PA12  |   PA_12  | USB DP |   CAN1 TD             |         |   CAN_TX    | CAN
13  |  PA11  |   PA_11  | USB DM |   CAN1 RD             | PWM1/4  |   CAN_RX    | CAN
14  |  PA10  |   PA_10  |   D2   |   Serial1 TX          | PWM1/3  |             |
15  |  PA9   |   PA_9   |   D8   |   Serial1 RX          | PWM1/2  |             |
16  |  PA8   |   PA_8   |   D7   |                       | PWM1/1  |             |
17  |  PB15  |   PB_15  |        | SPI2 MOSI             | PWM1/2N |   LCD_DIN   | Digital Input
18  |  PB14  |   PB_14  |        | SPI2 MISO             | PWM1/2N |   LCD_DC    |
19  |  PB13  |   PB_13  |        | SPI2 SCK              | PWM1/1N |   LCD_CE    | Digital Output
20  |  PB12  |   PB_12  |        | SPI2 NSS              |         |   LCD_RST   | Digital Output
21  |  VSS   |     -    |   -    |           -           |    -    |      -      |      -
22  |  VSS   |     -    |   -    |           -           |    -    |      -      |      -
23  | +3.3V  |     -    |   -    |           -           |    -    |      -      |      -
24  |  RESET |     -    |   -    |           -           |    -    |      -      |      -
25  |  PB11  |     -    |   -    | Serial3 RX/I2C2 SDA   |         | Teleinfo_EDF|   serial3
26  |  PB10  |   PB_10  |   D6   |   Serial3 TX/I2C2 SCL |         |    ND       |
27  |  PB1   |   PB_1   |        |                       |         | Analog In   |
28  |  PB0   |   PB_0   |   A3   |           Analog In   | PWM3/3  | LED_STRIP_R |   PWM3
29  |  PA7   |   PA_7   |   D11  | SPI1 MOSI / Analog In | PWM3/2  | LED_STRIP_G |   PWM3
30  |  PA6   |   PA_6   |   D12  | SPI1 MISO / Analog In | PWM3/1  | LED_STRIP_B |   PWM3
31  |  PA5   |   PA_5   |   D13  | SPI1 SCK  / Analog In |         |             |
32  |  PA4   |   PA_4   |   A2   | SPI1 NSS  / Analog In |         |             |
33  |  PA3   |   PA_3   |   D0   | Serial2 RX/ Analog In | PWM2/4  |Serial DBG RX|   serial2
34  |  PA2   |   PA_2   |   D1   | Serial2 TX/ Analog In | PWM2/3  |Serial DBG TX|   serial2
35  |  PA1   |   PA_1   |   A1   |           Analog In   | PWM2/2  |  PB_RIGHT   |   digital input
36  |  PA0   |   PA_0   |   A0   |           Analog In   |         |  PB_UP      |   digital input
37  |  PC15  |   PC_15  |        |                       |         |  PB_LEFT    |   digital input
38  |  PC14  |   PC_14  |        |                       |         |  PB_DOWN    |   digital input
39  |  PC13  |   PC_13  |   C13  |                       |         |    LED      |   Digital Output
40  |  VBAT  |          |        |                       |         |             |
