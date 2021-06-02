EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "STM32 proto prog"
Date "2021-04-02"
Rev "0.1"
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L can_uart_converter-rescue:MCP2551-I-P-Interface_CAN_LIN-stm_proto_board-rescue U2
U 1 1 5B6EF31C
P 9100 1650
F 0 "U2" H 9100 2228 50  0000 C CNN
F 1 "MCP2551-I-P" H 9100 2137 50  0000 C CNN
F 2 "Package_DIP:DIP-8_W7.62mm" H 9100 1150 50  0001 C CIN
F 3 "http://ww1.microchip.com/downloads/en/devicedoc/21667d.pdf" H 9100 1650 50  0001 C CNN
	1    9100 1650
	1    0    0    -1  
$EndComp
$Comp
L can_uart_converter-rescue:Conn_01x04-Connector_Generic-stm_proto_board-rescue J2
U 1 1 5B6EF715
P 10300 1550
F 0 "J2" H 10380 1542 50  0000 L CNN
F 1 "Conn_01x04" H 10380 1451 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x04_P2.54mm_Horizontal" H 10300 1550 50  0001 C CNN
F 3 "~" H 10300 1550 50  0001 C CNN
	1    10300 1550
	1    0    0    -1  
$EndComp
$Comp
L can_uart_converter-rescue:+3.3V-power-stm_proto_board-rescue #PWR0105
U 1 1 5B6EE504
P 9100 1050
F 0 "#PWR0105" H 9100 900 50  0001 C CNN
F 1 "+3.3V" H 9115 1223 50  0000 C CNN
F 2 "" H 9100 1050 50  0001 C CNN
F 3 "" H 9100 1050 50  0001 C CNN
	1    9100 1050
	1    0    0    -1  
$EndComp
Wire Wire Line
	9100 1250 9100 1050
$Comp
L can_uart_converter-rescue:GND-power-stm_proto_board-rescue #PWR0106
U 1 1 5B6EE5EC
P 9100 2200
F 0 "#PWR0106" H 9100 1950 50  0001 C CNN
F 1 "GND" H 9105 2027 50  0000 C CNN
F 2 "" H 9100 2200 50  0001 C CNN
F 3 "" H 9100 2200 50  0001 C CNN
	1    9100 2200
	1    0    0    -1  
$EndComp
Wire Wire Line
	9100 2050 9100 2200
Wire Wire Line
	10100 1550 9600 1550
Wire Wire Line
	9600 1750 9750 1750
Wire Wire Line
	9750 1750 9750 1650
Wire Wire Line
	9750 1650 10100 1650
Text Label 9850 1450 0    50   ~ 0
Valt1
Wire Wire Line
	9850 1450 10100 1450
Text Label 9850 1750 0    50   ~ 0
Valt2
Wire Wire Line
	9850 1750 10100 1750
Text GLabel 8450 1450 0    50   Input ~ 0
CAN_TX
Text GLabel 8450 1550 0    50   Input ~ 0
CAN_RX
Text GLabel 8450 1850 0    50   Input ~ 0
CAN_EN
Wire Wire Line
	8600 1450 8450 1450
Wire Wire Line
	8600 1550 8450 1550
Wire Wire Line
	8450 1850 8600 1850
Text Notes 10300 4350 0    50   ~ 0
Serial DBG Link
Wire Notes Line
	11000 2500 11000 800 
Wire Notes Line
	11000 800  7900 800 
Text Notes 10550 2450 0    50   ~ 0
CAN Link
Text GLabel 6150 4450 2    50   Output ~ 0
USART2_TX
Wire Wire Line
	6150 4450 6050 4450
Wire Wire Line
	4450 4550 4300 4550
Text GLabel 4100 1600 0    50   BiDi ~ 0
SDA
Text GLabel 4100 1700 0    50   Input ~ 0
SCL
Wire Wire Line
	4200 1600 4100 1600
Wire Wire Line
	4100 1700 4200 1700
Text GLabel 4300 4550 0    50   BiDi ~ 0
SDA
Text GLabel 4300 4450 0    50   Output ~ 0
SCL
Text Notes 4450 1900 0    50   ~ 0
PN532 - I2C
Wire Notes Line
	5000 1050 5000 1950
Wire Notes Line
	5000 1950 3550 1950
Wire Notes Line
	3550 1950 3550 1050
Wire Notes Line
	3550 1050 5000 1050
$Comp
L can_uart_converter-rescue:+3V3-power-stm_proto_board-rescue #PWR0126
U 1 1 5BE0BBD6
P 6000 1350
F 0 "#PWR0126" H 6000 1200 50  0001 C CNN
F 1 "+3V3" H 6015 1523 50  0000 C CNN
F 2 "" H 6000 1350 50  0001 C CNN
F 3 "" H 6000 1350 50  0001 C CNN
	1    6000 1350
	1    0    0    -1  
$EndComp
Wire Wire Line
	6150 1350 6000 1350
Wire Notes Line
	5500 1050 6950 1050
$Comp
L can_uart_converter-rescue:MAX3232_convertor-perso-stm_proto_board-rescue U3
U 1 1 5B6FB7F9
P 8650 3450
F 0 "U3" H 8575 3815 50  0000 C CNN
F 1 "MAX3232_convertor" H 8575 3724 50  0000 C CNN
F 2 "" H 8650 3000 50  0001 C CNN
F 3 "" H 8650 3000 50  0001 C CNN
	1    8650 3450
	-1   0    0    1   
$EndComp
Wire Wire Line
	9450 3900 9700 3900
Wire Wire Line
	9250 3350 9800 3350
Wire Wire Line
	9250 3550 9550 3550
Wire Wire Line
	4300 4450 4450 4450
$Comp
L can_uart_converter-rescue:Conn_01x02-Connector_Generic-stm_proto_board-rescue J5
U 1 1 5FABC2C9
P 4400 1350
F 0 "J5" H 4480 1342 50  0000 L CNN
F 1 "Conn_01x02" H 4480 1251 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 4400 1350 50  0001 C CNN
F 3 "~" H 4400 1350 50  0001 C CNN
	1    4400 1350
	1    0    0    -1  
$EndComp
$Comp
L can_uart_converter-rescue:Conn_01x02-Connector_Generic-stm_proto_board-rescue J17
U 1 1 5FAE99A1
P 4400 1600
F 0 "J17" H 4480 1592 50  0000 L CNN
F 1 "Conn_01x02" H 4480 1501 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 4400 1600 50  0001 C CNN
F 3 "~" H 4400 1600 50  0001 C CNN
	1    4400 1600
	1    0    0    -1  
$EndComp
$Comp
L can_uart_converter-rescue:+3V3-power-stm_proto_board-rescue #PWR0115
U 1 1 5B81E324
P 4050 1350
F 0 "#PWR0115" H 4050 1200 50  0001 C CNN
F 1 "+3V3" H 4065 1523 50  0000 C CNN
F 2 "" H 4050 1350 50  0001 C CNN
F 3 "" H 4050 1350 50  0001 C CNN
	1    4050 1350
	1    0    0    -1  
$EndComp
Wire Wire Line
	4200 1350 4050 1350
Text GLabel 4050 1450 0    50   Input ~ 0
GND_SCL
Wire Wire Line
	4050 1450 4200 1450
Wire Wire Line
	6050 1450 6150 1450
Text GLabel 6050 1450 0    50   Input ~ 0
GND_SCL
Wire Wire Line
	6050 2950 6050 3150
$Comp
L can_uart_converter-rescue:GND-power-stm_proto_board-rescue #PWR0102
U 1 1 5B6EFA7C
P 6050 2950
F 0 "#PWR0102" H 6050 2700 50  0001 C CNN
F 1 "GND" H 6055 2777 50  0000 C CNN
F 2 "" H 6050 2950 50  0001 C CNN
F 3 "" H 6050 2950 50  0001 C CNN
	1    6050 2950
	-1   0    0    1   
$EndComp
Wire Wire Line
	7350 3350 8150 3350
Wire Wire Line
	7950 3250 8150 3250
$Comp
L can_uart_converter-rescue:GND-power-stm_proto_board-rescue #PWR0134
U 1 1 6002FF33
P 7950 3250
F 0 "#PWR0134" H 7950 3000 50  0001 C CNN
F 1 "GND" H 7955 3077 50  0000 C CNN
F 2 "" H 7950 3250 50  0001 C CNN
F 3 "" H 7950 3250 50  0001 C CNN
	1    7950 3250
	0    1    1    0   
$EndComp
$Comp
L can_uart_converter-rescue:+3.3V-power-stm_proto_board-rescue #PWR0133
U 1 1 5FFBC37C
P 7350 3350
F 0 "#PWR0133" H 7350 3200 50  0001 C CNN
F 1 "+3.3V" H 7365 3523 50  0000 C CNN
F 2 "" H 7350 3350 50  0001 C CNN
F 3 "" H 7350 3350 50  0001 C CNN
	1    7350 3350
	1    0    0    -1  
$EndComp
Wire Wire Line
	8150 3550 7950 3550
Wire Wire Line
	7950 3450 8150 3450
Text GLabel 7950 3550 0    50   Input ~ 0
USART2_TX
Wire Wire Line
	7350 3800 7350 4000
Text GLabel 7950 3450 0    50   Input ~ 0
USART2_RX
$Comp
L can_uart_converter-rescue:Conn_01x04-Connector_Generic-stm_proto_board-rescue J12
U 1 1 5FC3FC3F
P 8150 4000
F 0 "J12" H 8230 3992 50  0000 L CNN
F 1 "Conn_01x04" H 8230 3901 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x04_P2.54mm_Vertical" H 8150 4000 50  0001 C CNN
F 3 "~" H 8150 4000 50  0001 C CNN
	1    8150 4000
	1    0    0    -1  
$EndComp
Text GLabel 7800 4200 0    50   Input ~ 0
USART2_TX
Text GLabel 7800 4100 0    50   Input ~ 0
USART2_RX
$Comp
L can_uart_converter-rescue:GND-power-stm_proto_board-rescue #PWR0104
U 1 1 5B6EE2CE
P 7800 3900
F 0 "#PWR0104" H 7800 3650 50  0001 C CNN
F 1 "GND" H 7805 3727 50  0000 C CNN
F 2 "" H 7800 3900 50  0001 C CNN
F 3 "" H 7800 3900 50  0001 C CNN
	1    7800 3900
	0    1    1    0   
$EndComp
$Comp
L can_uart_converter-rescue:+3.3V-power-stm_proto_board-rescue #PWR0103
U 1 1 5B6EE29F
P 7350 3800
F 0 "#PWR0103" H 7350 3650 50  0001 C CNN
F 1 "+3.3V" H 7365 3973 50  0000 C CNN
F 2 "" H 7350 3800 50  0001 C CNN
F 3 "" H 7350 3800 50  0001 C CNN
	1    7350 3800
	1    0    0    -1  
$EndComp
Wire Notes Line
	5500 1950 5500 1050
Wire Notes Line
	6950 1950 5500 1950
Wire Notes Line
	6950 1050 6950 1950
Text Notes 6150 1900 0    50   ~ 0
Temperature sensor
Wire Wire Line
	6050 1650 6150 1650
Wire Wire Line
	6150 1550 6050 1550
Text GLabel 6050 1650 0    50   Input ~ 0
SCL
Text GLabel 6050 1550 0    50   BiDi ~ 0
SDA
$Comp
L can_uart_converter-rescue:Conn_01x04-Connector_Generic-stm_proto_board-rescue J11
U 1 1 5BE0BBCF
P 6350 1450
F 0 "J11" H 6430 1442 50  0000 L CNN
F 1 "Conn_01x04" H 6430 1351 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x04_P2.54mm_Vertical" H 6350 1450 50  0001 C CNN
F 3 "~" H 6350 1450 50  0001 C CNN
	1    6350 1450
	1    0    0    -1  
$EndComp
Text GLabel 4300 3550 0    50   Output ~ 0
CAN_EN
Wire Wire Line
	4450 3950 4300 3950
Wire Wire Line
	4300 3850 4450 3850
Text GLabel 4300 3950 0    50   Output ~ 0
CAN_TX
Text GLabel 4300 3850 0    50   Input ~ 0
CAN_RX
Wire Wire Line
	6050 4350 6150 4350
Text GLabel 6150 4350 2    50   Input ~ 0
USART2_RX
Wire Notes Line
	7900 800  7900 2500
Wire Notes Line
	7900 2500 11000 2500
Text Label 9850 1650 0    50   ~ 0
CANL
Text Label 9850 1550 0    50   ~ 0
CANH
Text GLabel 4300 3650 0    50   Output ~ 0
ibutton_data
Text GLabel 4300 3750 0    50   Output ~ 0
ibutton_led+
Wire Wire Line
	9450 4000 9800 4000
Wire Wire Line
	9450 4200 9550 4200
$Comp
L can_uart_converter-rescue:Conn_01x04-Connector_Generic-stm_proto_board-rescue J13
U 1 1 5FC5BFA5
P 9250 4100
F 0 "J13" H 9330 4092 50  0000 L CNN
F 1 "Conn_01x04" H 9330 4001 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x04_P2.54mm_Vertical" H 9250 4100 50  0001 C CNN
F 3 "~" H 9250 4100 50  0001 C CNN
	1    9250 4100
	-1   0    0    1   
$EndComp
Wire Wire Line
	7350 4000 7950 4000
Wire Wire Line
	7800 4200 7950 4200
Wire Wire Line
	7800 4100 7950 4100
Wire Wire Line
	7800 3900 7950 3900
Text Label 9300 3350 0    50   ~ 0
RS232_RX
Text Label 9250 3550 0    50   ~ 0
RS232_GND
Text Label 9850 4100 0    50   ~ 0
GND_232
$Comp
L can_uart_converter-rescue:Conn_01x04-Connector_Generic-stm_proto_board-rescue J?
U 1 1 5FB3717B
P 10400 3900
AR Path="/60043CA2/5FB3717B" Ref="J?"  Part="1" 
AR Path="/5FB3717B" Ref="J3"  Part="1" 
F 0 "J3" H 10480 3892 50  0000 L CNN
F 1 "Conn_01x04" H 10480 3801 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x04_P2.54mm_Vertical" H 10400 3900 50  0001 C CNN
F 3 "~" H 10400 3900 50  0001 C CNN
	1    10400 3900
	1    0    0    -1  
$EndComp
Text Label 9850 3900 0    50   ~ 0
RS232_TX
Connection ~ 9700 3900
Connection ~ 9800 3800
Wire Wire Line
	9800 3800 9800 4000
Wire Wire Line
	9550 3550 9550 4200
Wire Wire Line
	9700 3250 9700 3900
Wire Wire Line
	9800 3350 9800 3800
Text Label 9850 3800 0    50   ~ 0
RS232_RX
Wire Wire Line
	9800 3800 10200 3800
Wire Wire Line
	9700 3900 10200 3900
Wire Wire Line
	9450 4100 10200 4100
Text Label 9300 3250 0    50   ~ 0
RS232_TX
Wire Wire Line
	8650 5500 8850 5500
$Comp
L can_uart_converter-rescue:+3.3V-power-stm_proto_board-rescue #PWR0118
U 1 1 5FDDA0F7
P 8650 5500
F 0 "#PWR0118" H 8650 5350 50  0001 C CNN
F 1 "+3.3V" H 8665 5673 50  0000 C CNN
F 2 "" H 8650 5500 50  0001 C CNN
F 3 "" H 8650 5500 50  0001 C CNN
	1    8650 5500
	1    0    0    -1  
$EndComp
Wire Wire Line
	9300 5700 9400 5700
Wire Wire Line
	9300 5900 9300 5700
$Comp
L can_uart_converter-rescue:R-Device-stm_proto_board-rescue R15
U 1 1 5FD3DA1B
P 9150 5900
F 0 "R15" V 8943 5900 50  0000 C CNN
F 1 "330" V 9034 5900 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P7.62mm_Horizontal" V 9080 5900 50  0001 C CNN
F 3 "~" H 9150 5900 50  0001 C CNN
	1    9150 5900
	0    1    1    0   
$EndComp
Connection ~ 9400 5900
Wire Wire Line
	9400 5800 9400 5900
Wire Notes Line
	8400 6150 10750 6150
Wire Notes Line
	8400 5250 10750 5250
Wire Notes Line
	8400 5250 8400 6150
Wire Notes Line
	10750 5250 10750 6150
Wire Wire Line
	9150 5500 9300 5500
Wire Wire Line
	9300 5600 9250 5600
Connection ~ 9300 5600
Wire Wire Line
	9300 5500 9300 5600
$Comp
L can_uart_converter-rescue:R-Device-stm_proto_board-rescue R14
U 1 1 5FB24111
P 9000 5500
F 0 "R14" V 8793 5500 50  0000 C CNN
F 1 "330" V 8884 5500 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P7.62mm_Horizontal" V 8930 5500 50  0001 C CNN
F 3 "~" H 9000 5500 50  0001 C CNN
	1    9000 5500
	0    1    1    0   
$EndComp
Text Notes 10150 6100 0    50   ~ 0
ibutton reader
$Comp
L can_uart_converter-rescue:GND-power-stm_proto_board-rescue #PWR0117
U 1 1 5FBB0AC2
P 9400 5900
F 0 "#PWR0117" H 9400 5650 50  0001 C CNN
F 1 "GND" H 9405 5727 50  0000 C CNN
F 2 "" H 9400 5900 50  0001 C CNN
F 3 "" H 9400 5900 50  0001 C CNN
	1    9400 5900
	1    0    0    -1  
$EndComp
Text Notes 10250 5900 0    50   ~ 0
Wires color:\n1. red\n2. white\n3. black\n4. green
Wire Wire Line
	9400 5600 9300 5600
Text GLabel 9250 5600 0    50   Input ~ 0
ibutton_data
Text GLabel 9000 5900 0    50   Input ~ 0
ibutton_led+
$Comp
L can_uart_converter-rescue:Conn_01x04-Connector_Generic-stm_proto_board-rescue J20
U 1 1 5FB0F0D0
P 9600 5700
F 0 "J20" H 9680 5692 50  0000 L CNN
F 1 "Conn_01x04" H 9680 5601 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x04_P2.54mm_Vertical" H 9600 5700 50  0001 C CNN
F 3 "~" H 9600 5700 50  0001 C CNN
	1    9600 5700
	1    0    0    -1  
$EndComp
NoConn ~ 10200 4000
NoConn ~ 6050 3250
NoConn ~ 6050 3450
NoConn ~ 6050 5050
NoConn ~ 9250 3450
NoConn ~ 6450 -350
Wire Wire Line
	9250 3250 9700 3250
$Comp
L can_uart_converter-rescue:+5V-power-stm_proto_board-rescue #PWR0119
U 1 1 5B8AAD24
P 3700 4850
F 0 "#PWR0119" H 3700 4700 50  0001 C CNN
F 1 "+5V" H 3715 5023 50  0000 C CNN
F 2 "" H 3700 4850 50  0001 C CNN
F 3 "" H 3700 4850 50  0001 C CNN
	1    3700 4850
	1    0    0    -1  
$EndComp
Wire Wire Line
	3700 4850 4450 4850
$Comp
L can_uart_converter-rescue:+3.3V-power-stm_proto_board-rescue #PWR?
U 1 1 606A91F3
P 6300 3350
F 0 "#PWR?" H 6300 3200 50  0001 C CNN
F 1 "+3.3V" H 6315 3523 50  0000 C CNN
F 2 "" H 6300 3350 50  0001 C CNN
F 3 "" H 6300 3350 50  0001 C CNN
	1    6300 3350
	1    0    0    -1  
$EndComp
Wire Wire Line
	6050 3350 6300 3350
Wire Notes Line
	11000 3000 11000 4400
Wire Notes Line
	7150 4400 11000 4400
Wire Notes Line
	7150 3000 11000 3000
Wire Notes Line
	7150 3000 7150 4400
Wire Wire Line
	4300 3550 4450 3550
Wire Wire Line
	4300 3650 4450 3650
Wire Wire Line
	4300 3750 4450 3750
$Comp
L can_uart_converter-rescue:YAAJ_BluePill_Part_Like-YAAJ_BluePill_Part_Like U1
U 1 1 5F8EE832
P 5250 4050
F 0 "U1" H 5250 5215 50  0000 C CNN
F 1 "YAAJ_BluePill_Part_Like" H 5250 5124 50  0000 C CNN
F 2 "Footprints:YAAJ_BluePill_1" H 5950 3050 50  0001 C CNN
F 3 "" H 5950 3050 50  0001 C CNN
	1    5250 4050
	1    0    0    -1  
$EndComp
$EndSCHEMATC
