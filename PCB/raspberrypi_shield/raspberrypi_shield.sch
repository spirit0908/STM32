EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Connector_Generic:Conn_02x20_Odd_Even J12
U 1 1 5F948853
P 9550 1900
F 0 "J12" H 9600 3017 50  0000 C CNN
F 1 "Conn_02x20_Odd_Even" H 9600 2926 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_2x20_P2.54mm_Vertical" H 9550 1900 50  0001 C CNN
F 3 "~" H 9550 1900 50  0001 C CNN
	1    9550 1900
	1    0    0    -1  
$EndComp
Text Label 9050 1000 0    50   ~ 0
3.3v
Wire Wire Line
	9000 1100 9350 1100
Text Label 9050 1100 0    50   ~ 0
GPIO02
Text Label 9050 1200 0    50   ~ 0
GPIO03
Text Label 9050 1300 0    50   ~ 0
GPIO04
Wire Wire Line
	9000 1400 9350 1400
Text Label 9050 1400 0    50   ~ 0
GND
Wire Wire Line
	9000 1500 9350 1500
Text Label 9050 1500 0    50   ~ 0
GPIO17
Wire Wire Line
	9000 1600 9350 1600
Text Label 9050 1600 0    50   ~ 0
GPIO27
Wire Wire Line
	9000 1700 9350 1700
Text Label 9050 1700 0    50   ~ 0
GPIO22
Wire Wire Line
	9000 1800 9350 1800
Text Label 9050 1800 0    50   ~ 0
3.3v
Text Label 9050 1900 0    50   ~ 0
GPIO10
Text Label 9050 2000 0    50   ~ 0
GPIO09
Text Label 9050 2100 0    50   ~ 0
GPIO11
Wire Wire Line
	9000 2200 9350 2200
Text Label 9050 2200 0    50   ~ 0
GND
Wire Wire Line
	9000 2300 9350 2300
Text Label 9050 2300 0    50   ~ 0
ID_SD
Wire Wire Line
	9000 2400 9350 2400
Text Label 9050 2400 0    50   ~ 0
GPIO05
Wire Wire Line
	9000 2500 9350 2500
Text Label 9050 2500 0    50   ~ 0
GPIO06
Wire Wire Line
	9000 2600 9350 2600
Text Label 9050 2600 0    50   ~ 0
GPIO13
Wire Wire Line
	9000 2700 9350 2700
Text Label 9050 2700 0    50   ~ 0
GPIO19
Wire Wire Line
	9000 2800 9350 2800
Text Label 9050 2800 0    50   ~ 0
GPIO26
Wire Wire Line
	9000 2900 9350 2900
Text Label 9050 2900 0    50   ~ 0
GND
Text Label 10050 1000 0    50   ~ 0
5v
Wire Wire Line
	9850 1100 10200 1100
Text Label 10050 1100 0    50   ~ 0
5v
Wire Wire Line
	9850 1200 10200 1200
Text Label 10050 1200 0    50   ~ 0
GND
Text Label 10050 1300 0    50   ~ 0
GPIO14
Text Label 10050 1400 0    50   ~ 0
GPIO15
Wire Wire Line
	9850 1500 10200 1500
Text Label 10050 1500 0    50   ~ 0
GPIO18
Wire Wire Line
	9850 1600 10200 1600
Text Label 10050 1600 0    50   ~ 0
GND
Wire Wire Line
	9850 1700 10200 1700
Text Label 10050 1700 0    50   ~ 0
GPIO23
Wire Wire Line
	9850 1800 10200 1800
Text Label 10050 1800 0    50   ~ 0
GPIO24
Wire Wire Line
	9850 1900 10200 1900
Text Label 10050 1900 0    50   ~ 0
GND
Text Label 10050 2000 0    50   ~ 0
GPIO25
Text Label 10050 2100 0    50   ~ 0
GPIO08
Wire Wire Line
	9850 2200 10200 2200
Text Label 10050 2200 0    50   ~ 0
GPIO07
Wire Wire Line
	9850 2300 10200 2300
Text Label 10050 2300 0    50   ~ 0
ID_SC
Wire Wire Line
	9850 2400 10200 2400
Text Label 10050 2400 0    50   ~ 0
GND
Wire Wire Line
	9850 2500 10200 2500
Text Label 10050 2500 0    50   ~ 0
GPIO12
Wire Wire Line
	9850 2600 10200 2600
Text Label 10050 2600 0    50   ~ 0
GND
Wire Wire Line
	9850 2700 10200 2700
Text Label 10050 2700 0    50   ~ 0
GPIO16
Wire Wire Line
	9850 2800 10200 2800
Text Label 10050 2800 0    50   ~ 0
GPIO20
Wire Wire Line
	9850 2900 10200 2900
Text Label 10050 2900 0    50   ~ 0
GPIO21
$Comp
L Interface_CAN_LIN:MCP2515-xSO U1
U 1 1 5F95DC24
P 2650 1800
F 0 "U1" H 2650 2781 50  0000 C CNN
F 1 "MCP2515-xSO" H 2650 2690 50  0000 C CNN
F 2 "Package_SO:SOIC-18W_7.5x11.6mm_P1.27mm" H 2650 900 50  0001 C CIN
F 3 "http://ww1.microchip.com/downloads/en/DeviceDoc/21801e.pdf" H 2750 1000 50  0001 C CNN
	1    2650 1800
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x07 J11
U 1 1 5F96020F
P 7400 1700
F 0 "J11" H 7480 1742 50  0000 L CNN
F 1 "Conn_01x07" H 7480 1651 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x07_P2.54mm_Vertical" H 7400 1700 50  0001 C CNN
F 3 "~" H 7400 1700 50  0001 C CNN
	1    7400 1700
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x02 J6
U 1 1 5F961277
P 5650 1700
F 0 "J6" H 5730 1692 50  0000 L CNN
F 1 "Conn_01x02" H 5730 1601 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 5650 1700 50  0001 C CNN
F 3 "~" H 5650 1700 50  0001 C CNN
	1    5650 1700
	1    0    0    -1  
$EndComp
Text Label 5250 1700 0    50   ~ 0
CANH
Text Label 5250 1800 0    50   ~ 0
CANL
$Comp
L power:+3.3V #PWR0101
U 1 1 5F96650A
P 7100 1350
F 0 "#PWR0101" H 7100 1200 50  0001 C CNN
F 1 "+3.3V" H 7115 1523 50  0000 C CNN
F 2 "" H 7100 1350 50  0001 C CNN
F 3 "" H 7100 1350 50  0001 C CNN
	1    7100 1350
	1    0    0    -1  
$EndComp
Wire Wire Line
	7100 1350 7100 1400
Wire Wire Line
	7100 1400 7200 1400
$Comp
L power:GND #PWR0102
U 1 1 5F9681E0
P 7100 2050
F 0 "#PWR0102" H 7100 1800 50  0001 C CNN
F 1 "GND" H 7105 1877 50  0000 C CNN
F 2 "" H 7100 2050 50  0001 C CNN
F 3 "" H 7100 2050 50  0001 C CNN
	1    7100 2050
	1    0    0    -1  
$EndComp
Wire Wire Line
	7100 2050 7100 2000
Wire Wire Line
	7100 2000 7200 2000
$Comp
L power:GND #PWR0103
U 1 1 5F96BA6E
P 2650 2650
F 0 "#PWR0103" H 2650 2400 50  0001 C CNN
F 1 "GND" H 2655 2477 50  0000 C CNN
F 2 "" H 2650 2650 50  0001 C CNN
F 3 "" H 2650 2650 50  0001 C CNN
	1    2650 2650
	1    0    0    -1  
$EndComp
Wire Wire Line
	2650 2650 2650 2600
$Comp
L power:+3.3V #PWR0104
U 1 1 5F96F114
P 2650 750
F 0 "#PWR0104" H 2650 600 50  0001 C CNN
F 1 "+3.3V" H 2665 923 50  0000 C CNN
F 2 "" H 2650 750 50  0001 C CNN
F 3 "" H 2650 750 50  0001 C CNN
	1    2650 750 
	1    0    0    -1  
$EndComp
Wire Wire Line
	6850 1500 7200 1500
Text Label 6900 1500 0    50   ~ 0
CS
Wire Wire Line
	6850 1600 7200 1600
Text Label 6900 1600 0    50   ~ 0
SO
Wire Wire Line
	6850 1700 7200 1700
Text Label 6900 1700 0    50   ~ 0
SI
Wire Wire Line
	6850 1800 7200 1800
Text Label 6900 1800 0    50   ~ 0
SCK
Wire Wire Line
	6850 1900 7200 1900
Text Label 6900 1900 0    50   ~ 0
INT
Wire Wire Line
	1700 1400 2050 1400
Text Label 1750 1400 0    50   ~ 0
CS
Wire Wire Line
	1700 1300 2050 1300
Text Label 1750 1300 0    50   ~ 0
SO
Wire Wire Line
	1700 1200 2050 1200
Text Label 1750 1200 0    50   ~ 0
SI
Wire Wire Line
	1700 1500 2050 1500
Text Label 1750 1500 0    50   ~ 0
SCK
Text Label 3300 1800 0    50   ~ 0
INT
$Comp
L power:+3.3V #PWR0105
U 1 1 5F991454
P 3650 2350
F 0 "#PWR0105" H 3650 2200 50  0001 C CNN
F 1 "+3.3V" H 3665 2523 50  0000 C CNN
F 2 "" H 3650 2350 50  0001 C CNN
F 3 "" H 3650 2350 50  0001 C CNN
	1    3650 2350
	1    0    0    -1  
$EndComp
$Comp
L Device:R R5
U 1 1 5F993096
P 3450 2400
F 0 "R5" V 3243 2400 50  0000 C CNN
F 1 "10k" V 3334 2400 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P5.08mm_Horizontal" V 3380 2400 50  0001 C CNN
F 3 "~" H 3450 2400 50  0001 C CNN
	1    3450 2400
	0    1    1    0   
$EndComp
Wire Wire Line
	3250 2400 3300 2400
$Comp
L Device:C C3
U 1 1 5F99CAE4
P 1350 1850
F 0 "C3" V 1602 1850 50  0000 C CNN
F 1 "22" V 1511 1850 50  0000 C CNN
F 2 "Capacitor_THT:C_Disc_D3.0mm_W1.6mm_P2.50mm" H 1388 1700 50  0001 C CNN
F 3 "~" H 1350 1850 50  0001 C CNN
	1    1350 1850
	0    -1   -1   0   
$EndComp
$Comp
L Device:C C4
U 1 1 5F99D529
P 1350 2250
F 0 "C4" V 1602 2250 50  0000 C CNN
F 1 "22" V 1511 2250 50  0000 C CNN
F 2 "Capacitor_THT:C_Disc_D3.0mm_W1.6mm_P2.50mm" H 1388 2100 50  0001 C CNN
F 3 "~" H 1350 2250 50  0001 C CNN
	1    1350 2250
	0    -1   -1   0   
$EndComp
$Comp
L Device:Crystal Y1
U 1 1 5F9A0726
P 1600 2050
F 0 "Y1" V 1646 1919 50  0000 R CNN
F 1 "8M" V 1555 1919 50  0000 R CNN
F 2 "Resistor_THT:R_Axial_DIN0411_L9.9mm_D3.6mm_P7.62mm_Vertical" H 1600 2050 50  0001 C CNN
F 3 "~" H 1600 2050 50  0001 C CNN
	1    1600 2050
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR0106
U 1 1 5F9B58B6
P 1200 2350
F 0 "#PWR0106" H 1200 2100 50  0001 C CNN
F 1 "GND" H 1205 2177 50  0000 C CNN
F 2 "" H 1200 2350 50  0001 C CNN
F 3 "" H 1200 2350 50  0001 C CNN
	1    1200 2350
	1    0    0    -1  
$EndComp
Wire Wire Line
	1800 2100 1800 2250
Wire Wire Line
	1800 2250 1600 2250
Wire Wire Line
	1800 2000 1800 1850
Wire Wire Line
	1800 1850 1600 1850
Wire Wire Line
	1800 2000 2050 2000
Wire Wire Line
	1800 2100 2050 2100
Wire Wire Line
	1600 1900 1600 1850
Connection ~ 1600 1850
Wire Wire Line
	1600 1850 1500 1850
Wire Wire Line
	1600 2200 1600 2250
Connection ~ 1600 2250
Wire Wire Line
	1600 2250 1500 2250
Text GLabel 1700 1200 0    50   Input ~ 0
SI
Text GLabel 1700 1300 0    50   Output ~ 0
SO
Text GLabel 1700 1400 0    50   Input ~ 0
CS
Text GLabel 1700 1500 0    50   Input ~ 0
SCK
Text GLabel 6850 1800 0    50   Output ~ 0
SCK
Text GLabel 6850 1700 0    50   Output ~ 0
SI
Text GLabel 6850 1600 0    50   Input ~ 0
SO
Text GLabel 6850 1500 0    50   Output ~ 0
CS
Text GLabel 6850 1900 0    50   Input ~ 0
INT
Text GLabel 3450 1800 2    50   Output ~ 0
INT
$Comp
L Device:C C1
U 1 1 5F9D0FB7
P 750 1150
F 0 "C1" H 635 1104 50  0000 R CNN
F 1 "10u" H 635 1195 50  0000 R CNN
F 2 "Capacitor_THT:C_Disc_D3.0mm_W1.6mm_P2.50mm" H 788 1000 50  0001 C CNN
F 3 "~" H 750 1150 50  0001 C CNN
	1    750  1150
	-1   0    0    1   
$EndComp
$Comp
L Device:C C2
U 1 1 5F9D3E84
P 1150 1150
F 0 "C2" H 1035 1104 50  0000 R CNN
F 1 "104" H 1035 1195 50  0000 R CNN
F 2 "Capacitor_THT:C_Disc_D3.0mm_W1.6mm_P2.50mm" H 1188 1000 50  0001 C CNN
F 3 "~" H 1150 1150 50  0001 C CNN
	1    1150 1150
	-1   0    0    1   
$EndComp
$Comp
L Device:R R6
U 1 1 5F9E21D5
P 5050 1550
F 0 "R6" V 4843 1550 50  0000 C CNN
F 1 "10k" V 4934 1550 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P5.08mm_Horizontal" V 4980 1550 50  0001 C CNN
F 3 "~" H 5050 1550 50  0001 C CNN
	1    5050 1550
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x02 J5
U 1 1 5F9E664B
P 5050 1200
F 0 "J5" V 5014 1012 50  0000 R CNN
F 1 "Conn_01x02" V 4923 1012 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 5050 1200 50  0001 C CNN
F 3 "~" H 5050 1200 50  0001 C CNN
	1    5050 1200
	0    -1   -1   0   
$EndComp
Wire Wire Line
	5150 1400 5150 1800
Wire Wire Line
	5150 1800 5450 1800
Connection ~ 5050 1700
Wire Wire Line
	5050 1700 5450 1700
Connection ~ 5150 1800
Wire Wire Line
	4800 1650 4950 1650
Wire Wire Line
	4950 1650 4950 1700
Wire Wire Line
	4950 1800 4950 1850
Wire Wire Line
	4950 1850 4800 1850
Wire Wire Line
	1200 1850 1200 2250
Connection ~ 1200 2250
Wire Wire Line
	1200 2250 1200 2350
Wire Wire Line
	3800 1300 3800 1550
Wire Wire Line
	3700 1200 3700 1650
Wire Wire Line
	3700 1650 3800 1650
Wire Wire Line
	3650 2350 3650 2400
Wire Wire Line
	3650 2400 3600 2400
Wire Wire Line
	4950 1700 5050 1700
Wire Wire Line
	4950 1800 5150 1800
Wire Wire Line
	3250 1800 3450 1800
$Comp
L power:GND #PWR0107
U 1 1 5FAF8BFA
P 1150 1400
F 0 "#PWR0107" H 1150 1150 50  0001 C CNN
F 1 "GND" H 1155 1227 50  0000 C CNN
F 2 "" H 1150 1400 50  0001 C CNN
F 3 "" H 1150 1400 50  0001 C CNN
	1    1150 1400
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR0108
U 1 1 5FAFD57C
P 1150 900
F 0 "#PWR0108" H 1150 750 50  0001 C CNN
F 1 "+3.3V" H 1165 1073 50  0000 C CNN
F 2 "" H 1150 900 50  0001 C CNN
F 3 "" H 1150 900 50  0001 C CNN
	1    1150 900 
	1    0    0    -1  
$EndComp
Wire Wire Line
	1150 1400 1150 1300
Wire Wire Line
	750  1300 1150 1300
Connection ~ 1150 1300
Wire Wire Line
	750  1000 1150 1000
Wire Wire Line
	1150 900  1150 1000
Connection ~ 1150 1000
Wire Wire Line
	3250 1200 3700 1200
Wire Wire Line
	3250 1300 3800 1300
$Comp
L Connector_Generic:Conn_01x04 J13
U 1 1 5FB3E7D1
P 10300 4100
F 0 "J13" H 10380 4092 50  0000 L CNN
F 1 "Conn_01x04" H 10380 4001 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x04_P2.54mm_Vertical" H 10300 4100 50  0001 C CNN
F 3 "~" H 10300 4100 50  0001 C CNN
	1    10300 4100
	1    0    0    -1  
$EndComp
$Comp
L Sensor:DHT11 U7
U 1 1 5FB3F640
P 8900 4100
F 0 "U7" H 8656 4146 50  0000 R CNN
F 1 "DHT11" H 8656 4055 50  0000 R CNN
F 2 "Sensor:Aosong_DHT11_5.5x12.0_P2.54mm" H 8900 3700 50  0001 C CNN
F 3 "http://akizukidenshi.com/download/ds/aosong/DHT11.pdf" H 9050 4350 50  0001 C CNN
	1    8900 4100
	1    0    0    -1  
$EndComp
Wire Wire Line
	9750 4000 10100 4000
Text Label 9800 4000 0    50   ~ 0
VDD
Text Label 9800 4100 0    50   ~ 0
DATA
Wire Wire Line
	9750 4300 10100 4300
Text Label 9800 4300 0    50   ~ 0
GND
$Comp
L power:GND #PWR0109
U 1 1 5FB5F737
P 8900 4450
F 0 "#PWR0109" H 8900 4200 50  0001 C CNN
F 1 "GND" H 8905 4277 50  0000 C CNN
F 2 "" H 8900 4450 50  0001 C CNN
F 3 "" H 8900 4450 50  0001 C CNN
	1    8900 4450
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR0110
U 1 1 5FB66239
P 8900 3750
F 0 "#PWR0110" H 8900 3600 50  0001 C CNN
F 1 "+3.3V" H 8915 3923 50  0000 C CNN
F 2 "" H 8900 3750 50  0001 C CNN
F 3 "" H 8900 3750 50  0001 C CNN
	1    8900 3750
	1    0    0    -1  
$EndComp
Wire Wire Line
	8900 3750 8900 3800
Wire Wire Line
	8900 4400 8900 4450
Wire Wire Line
	8900 4450 9750 4450
Wire Wire Line
	9750 4450 9750 4300
Connection ~ 8900 4450
Wire Wire Line
	9750 3800 9750 4000
Wire Wire Line
	9200 4100 9500 4100
Wire Wire Line
	8900 3800 9500 3800
Connection ~ 8900 3800
$Comp
L Device:R R11
U 1 1 5FBA53A9
P 9500 3950
F 0 "R11" V 9293 3950 50  0000 C CNN
F 1 "10k" V 9384 3950 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P5.08mm_Horizontal" V 9430 3950 50  0001 C CNN
F 3 "~" H 9500 3950 50  0001 C CNN
	1    9500 3950
	1    0    0    -1  
$EndComp
Connection ~ 9500 3800
Wire Wire Line
	9500 3800 9750 3800
Connection ~ 9500 4100
Wire Wire Line
	9500 4100 10100 4100
Wire Wire Line
	4300 2200 4300 2150
$Comp
L power:GND #PWR0111
U 1 1 5F96A9C3
P 4300 2200
F 0 "#PWR0111" H 4300 1950 50  0001 C CNN
F 1 "GND" H 4305 2027 50  0000 C CNN
F 2 "" H 4300 2200 50  0001 C CNN
F 3 "" H 4300 2200 50  0001 C CNN
	1    4300 2200
	1    0    0    -1  
$EndComp
$Comp
L Interface_CAN_LIN:MCP2551-I-P U2
U 1 1 5F95F1DA
P 4300 1750
F 0 "U2" H 4300 2331 50  0000 C CNN
F 1 "MCP2551-I-P" H 4300 2240 50  0000 C CNN
F 2 "Package_SO:HTSOP-8-1EP_3.9x4.9mm_P1.27mm_EP2.4x3.2mm_ThermalVias" H 4300 1250 50  0001 C CIN
F 3 "http://ww1.microchip.com/downloads/en/devicedoc/21667d.pdf" H 4300 1750 50  0001 C CNN
	1    4300 1750
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0112
U 1 1 5FC3C511
P 10300 950
F 0 "#PWR0112" H 10300 800 50  0001 C CNN
F 1 "+5V" H 10315 1123 50  0000 C CNN
F 2 "" H 10300 950 50  0001 C CNN
F 3 "" H 10300 950 50  0001 C CNN
	1    10300 950 
	1    0    0    -1  
$EndComp
Wire Wire Line
	10300 950  10300 1000
Wire Wire Line
	9850 1000 10300 1000
$Comp
L power:GND #PWR0113
U 1 1 5FC4D4B2
P 9000 2900
F 0 "#PWR0113" H 9000 2650 50  0001 C CNN
F 1 "GND" H 9005 2727 50  0000 C CNN
F 2 "" H 9000 2900 50  0001 C CNN
F 3 "" H 9000 2900 50  0001 C CNN
	1    9000 2900
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR0114
U 1 1 5FC56A6C
P 8900 950
F 0 "#PWR0114" H 8900 800 50  0001 C CNN
F 1 "+3.3V" H 8915 1123 50  0000 C CNN
F 2 "" H 8900 950 50  0001 C CNN
F 3 "" H 8900 950 50  0001 C CNN
	1    8900 950 
	1    0    0    -1  
$EndComp
Wire Wire Line
	8900 1000 8900 950 
Wire Wire Line
	8900 1000 9350 1000
Text Label 10700 2100 2    50   ~ 0
CS
Text Label 8700 2000 0    50   ~ 0
SO
Text Label 8700 1900 0    50   ~ 0
SI
Text Label 8700 2100 0    50   ~ 0
SCK
Text Label 10650 2000 2    50   ~ 0
INT
Text GLabel 8650 2100 0    50   Output ~ 0
SCK
Text GLabel 8650 1900 0    50   Output ~ 0
SI
Text GLabel 8650 2000 0    50   Input ~ 0
SO
Text GLabel 10750 2100 2    50   Output ~ 0
CS
Text GLabel 10700 2000 2    50   Input ~ 0
INT
$Comp
L power:+5V #PWR0115
U 1 1 5FC7EFD7
P 4300 1100
F 0 "#PWR0115" H 4300 950 50  0001 C CNN
F 1 "+5V" H 4315 1273 50  0000 C CNN
F 2 "" H 4300 1100 50  0001 C CNN
F 3 "" H 4300 1100 50  0001 C CNN
	1    4300 1100
	1    0    0    -1  
$EndComp
Wire Wire Line
	4300 1100 4300 1350
Wire Wire Line
	9850 2100 10750 2100
Wire Wire Line
	8650 2000 9350 2000
Wire Wire Line
	8650 1900 9350 1900
Wire Wire Line
	8650 2100 9350 2100
Wire Wire Line
	9850 2000 10700 2000
$Comp
L Isolator:4N25 U3
U 1 1 5FDB4383
P 6700 3700
F 0 "U3" H 6700 4025 50  0000 C CNN
F 1 "4N25" H 6700 3934 50  0000 C CNN
F 2 "Package_DIP:DIP-6_W7.62mm" H 6500 3500 50  0001 L CIN
F 3 "https://www.vishay.com/docs/83725/4n25.pdf" H 6700 3700 50  0001 L CNN
	1    6700 3700
	1    0    0    -1  
$EndComp
$Comp
L Isolator:4N25 U4
U 1 1 5FDC2D98
P 6700 4250
F 0 "U4" H 6700 4575 50  0000 C CNN
F 1 "4N25" H 6700 4484 50  0000 C CNN
F 2 "Package_DIP:DIP-6_W7.62mm" H 6500 4050 50  0001 L CIN
F 3 "https://www.vishay.com/docs/83725/4n25.pdf" H 6700 4250 50  0001 L CNN
	1    6700 4250
	1    0    0    -1  
$EndComp
$Comp
L Isolator:4N25 U5
U 1 1 5FDCACA6
P 6700 4800
F 0 "U5" H 6700 5125 50  0000 C CNN
F 1 "4N25" H 6700 5034 50  0000 C CNN
F 2 "Package_DIP:DIP-6_W7.62mm" H 6500 4600 50  0001 L CIN
F 3 "https://www.vishay.com/docs/83725/4n25.pdf" H 6700 4800 50  0001 L CNN
	1    6700 4800
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR0116
U 1 1 5FE358BC
P 7500 3650
F 0 "#PWR0116" H 7500 3500 50  0001 C CNN
F 1 "+3.3V" H 7515 3823 50  0000 C CNN
F 2 "" H 7500 3650 50  0001 C CNN
F 3 "" H 7500 3650 50  0001 C CNN
	1    7500 3650
	1    0    0    -1  
$EndComp
$Comp
L Device:R R7
U 1 1 5FE358C2
P 7300 3700
F 0 "R7" H 7230 3654 50  0000 R CNN
F 1 "10k" H 7230 3745 50  0000 R CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P5.08mm_Horizontal" V 7230 3700 50  0001 C CNN
F 3 "~" H 7300 3700 50  0001 C CNN
	1    7300 3700
	0    1    1    0   
$EndComp
Wire Wire Line
	7000 3800 7050 3800
Wire Wire Line
	7500 3650 7500 3700
Wire Wire Line
	7500 3700 7450 3700
$Comp
L power:GND #PWR0117
U 1 1 5FEC0746
P 7050 4350
F 0 "#PWR0117" H 7050 4100 50  0001 C CNN
F 1 "GND" H 7055 4177 50  0000 C CNN
F 2 "" H 7050 4350 50  0001 C CNN
F 3 "" H 7050 4350 50  0001 C CNN
	1    7050 4350
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR0118
U 1 1 5FEC074C
P 7500 4200
F 0 "#PWR0118" H 7500 4050 50  0001 C CNN
F 1 "+3.3V" H 7515 4373 50  0000 C CNN
F 2 "" H 7500 4200 50  0001 C CNN
F 3 "" H 7500 4200 50  0001 C CNN
	1    7500 4200
	1    0    0    -1  
$EndComp
$Comp
L Device:R R8
U 1 1 5FEC0752
P 7300 4250
F 0 "R8" H 7230 4204 50  0000 R CNN
F 1 "10k" H 7230 4295 50  0000 R CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P5.08mm_Horizontal" V 7230 4250 50  0001 C CNN
F 3 "~" H 7300 4250 50  0001 C CNN
	1    7300 4250
	0    1    1    0   
$EndComp
Wire Wire Line
	7000 4250 7150 4250
Wire Wire Line
	7000 4350 7050 4350
Wire Wire Line
	7500 4200 7500 4250
Wire Wire Line
	7500 4250 7450 4250
$Comp
L power:GND #PWR0119
U 1 1 5FEC896A
P 7050 4900
F 0 "#PWR0119" H 7050 4650 50  0001 C CNN
F 1 "GND" H 7055 4727 50  0000 C CNN
F 2 "" H 7050 4900 50  0001 C CNN
F 3 "" H 7050 4900 50  0001 C CNN
	1    7050 4900
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR0120
U 1 1 5FEC8970
P 7500 4750
F 0 "#PWR0120" H 7500 4600 50  0001 C CNN
F 1 "+3.3V" H 7515 4923 50  0000 C CNN
F 2 "" H 7500 4750 50  0001 C CNN
F 3 "" H 7500 4750 50  0001 C CNN
	1    7500 4750
	1    0    0    -1  
$EndComp
$Comp
L Device:R R9
U 1 1 5FEC8976
P 7300 4800
F 0 "R9" H 7230 4754 50  0000 R CNN
F 1 "10k" H 7230 4845 50  0000 R CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P5.08mm_Horizontal" V 7230 4800 50  0001 C CNN
F 3 "~" H 7300 4800 50  0001 C CNN
	1    7300 4800
	0    1    1    0   
$EndComp
Wire Wire Line
	7000 4800 7150 4800
Wire Wire Line
	7000 4900 7050 4900
Wire Wire Line
	7500 4750 7500 4800
Wire Wire Line
	7500 4800 7450 4800
Text GLabel 7350 3800 2    50   Input ~ 0
Input1
Text GLabel 7350 4350 2    50   Input ~ 0
Input2
Text GLabel 7350 4900 2    50   Input ~ 0
Input3
Wire Wire Line
	7350 4350 7150 4350
Wire Wire Line
	7150 4350 7150 4250
Connection ~ 7150 4250
Wire Wire Line
	7350 4900 7150 4900
Wire Wire Line
	7150 4900 7150 4800
Connection ~ 7150 4800
Wire Wire Line
	7000 3700 7150 3700
Wire Wire Line
	7350 3800 7150 3800
Wire Wire Line
	7150 3800 7150 3700
Connection ~ 7150 3700
$Comp
L power:GND #PWR0121
U 1 1 5FDFF557
P 7050 3800
F 0 "#PWR0121" H 7050 3550 50  0001 C CNN
F 1 "GND" H 7055 3627 50  0000 C CNN
F 2 "" H 7050 3800 50  0001 C CNN
F 3 "" H 7050 3800 50  0001 C CNN
	1    7050 3800
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x02 J7
U 1 1 5FF426C9
P 6100 3750
F 0 "J7" H 6018 3425 50  0000 C CNN
F 1 "Conn_01x02" H 6018 3516 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 6100 3750 50  0001 C CNN
F 3 "~" H 6100 3750 50  0001 C CNN
	1    6100 3750
	-1   0    0    1   
$EndComp
$Comp
L Connector_Generic:Conn_01x02 J8
U 1 1 5FF4D238
P 6100 4300
F 0 "J8" H 6018 3975 50  0000 C CNN
F 1 "Conn_01x02" H 6018 4066 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 6100 4300 50  0001 C CNN
F 3 "~" H 6100 4300 50  0001 C CNN
	1    6100 4300
	-1   0    0    1   
$EndComp
Wire Wire Line
	6300 3650 6300 3600
Wire Wire Line
	6300 3600 6400 3600
Wire Wire Line
	6400 3800 6300 3800
Wire Wire Line
	6300 3800 6300 3750
Wire Wire Line
	6300 4200 6300 4150
Wire Wire Line
	6300 4150 6400 4150
Wire Wire Line
	6400 4350 6300 4350
Wire Wire Line
	6300 4350 6300 4300
$Comp
L Connector_Generic:Conn_01x02 J9
U 1 1 5FF561C7
P 6100 4850
F 0 "J9" H 6018 4525 50  0000 C CNN
F 1 "Conn_01x02" H 6018 4616 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 6100 4850 50  0001 C CNN
F 3 "~" H 6100 4850 50  0001 C CNN
	1    6100 4850
	-1   0    0    1   
$EndComp
Wire Wire Line
	6300 4750 6300 4700
Wire Wire Line
	6300 4700 6400 4700
Wire Wire Line
	6400 4900 6300 4900
Wire Wire Line
	6300 4900 6300 4850
$Comp
L Isolator:4N25 U6
U 1 1 60025085
P 6700 5350
F 0 "U6" H 6700 5675 50  0000 C CNN
F 1 "4N25" H 6700 5584 50  0000 C CNN
F 2 "Package_DIP:DIP-6_W7.62mm" H 6500 5150 50  0001 L CIN
F 3 "https://www.vishay.com/docs/83725/4n25.pdf" H 6700 5350 50  0001 L CNN
	1    6700 5350
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0122
U 1 1 6002508B
P 7050 5450
F 0 "#PWR0122" H 7050 5200 50  0001 C CNN
F 1 "GND" H 7055 5277 50  0000 C CNN
F 2 "" H 7050 5450 50  0001 C CNN
F 3 "" H 7050 5450 50  0001 C CNN
	1    7050 5450
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR0123
U 1 1 60025091
P 7500 5300
F 0 "#PWR0123" H 7500 5150 50  0001 C CNN
F 1 "+3.3V" H 7515 5473 50  0000 C CNN
F 2 "" H 7500 5300 50  0001 C CNN
F 3 "" H 7500 5300 50  0001 C CNN
	1    7500 5300
	1    0    0    -1  
$EndComp
$Comp
L Device:R R10
U 1 1 60025097
P 7300 5350
F 0 "R10" H 7230 5304 50  0000 R CNN
F 1 "10k" H 7230 5395 50  0000 R CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P5.08mm_Horizontal" V 7230 5350 50  0001 C CNN
F 3 "~" H 7300 5350 50  0001 C CNN
	1    7300 5350
	0    1    1    0   
$EndComp
Wire Wire Line
	7000 5350 7150 5350
Wire Wire Line
	7000 5450 7050 5450
Wire Wire Line
	7500 5300 7500 5350
Wire Wire Line
	7500 5350 7450 5350
Text GLabel 7350 5450 2    50   Input ~ 0
Input4
Wire Wire Line
	7350 5450 7150 5450
Wire Wire Line
	7150 5450 7150 5350
Connection ~ 7150 5350
$Comp
L Connector_Generic:Conn_01x02 J10
U 1 1 600250A5
P 6100 5400
F 0 "J10" H 6018 5075 50  0000 C CNN
F 1 "Conn_01x02" H 6018 5166 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 6100 5400 50  0001 C CNN
F 3 "~" H 6100 5400 50  0001 C CNN
	1    6100 5400
	-1   0    0    1   
$EndComp
Wire Wire Line
	6300 5300 6300 5250
Wire Wire Line
	6300 5250 6400 5250
Wire Wire Line
	6400 5450 6300 5450
Wire Wire Line
	6300 5450 6300 5400
$Comp
L Relay:SANYOU_SRD_Form_C K1
U 1 1 600972DD
P 2450 4200
F 0 "K1" H 2880 4246 50  0000 L CNN
F 1 "SANYOU_SRD_Form_C" H 2880 4155 50  0000 L CNN
F 2 "Relay_THT:Relay_SPDT_SANYOU_SRD_Series_Form_C" H 2900 4150 50  0001 L CNN
F 3 "http://www.sanyourelay.ca/public/products/pdf/SRD.pdf" H 2450 4200 50  0001 C CNN
	1    2450 4200
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x03 J1
U 1 1 600972E3
P 4250 4200
F 0 "J1" H 4330 4242 50  0000 L CNN
F 1 "Conn_01x03" H 4330 4151 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x03_P2.54mm_Vertical" H 4250 4200 50  0001 C CNN
F 3 "~" H 4250 4200 50  0001 C CNN
	1    4250 4200
	1    0    0    -1  
$EndComp
Wire Wire Line
	3850 4100 4050 4100
Text Label 3900 4100 0    50   ~ 0
NC_1
Text Label 3900 4200 0    50   ~ 0
COM_1
Text Label 3900 4300 0    50   ~ 0
NO_1
Wire Wire Line
	2650 4500 3700 4500
Wire Wire Line
	3700 4500 3700 4200
Wire Wire Line
	3700 4200 4050 4200
Wire Wire Line
	3850 4100 3850 3750
Wire Wire Line
	3850 3750 2550 3750
Wire Wire Line
	2550 3750 2550 3900
Wire Wire Line
	2750 3900 3750 3900
Wire Wire Line
	3750 3900 3750 4300
Wire Wire Line
	3750 4300 4050 4300
$Comp
L Device:D D1
U 1 1 600972F6
P 1800 4200
F 0 "D1" V 1754 4280 50  0000 L CNN
F 1 "D" V 1845 4280 50  0000 L CNN
F 2 "Diode_THT:D_A-405_P7.62mm_Horizontal" H 1800 4200 50  0001 C CNN
F 3 "~" H 1800 4200 50  0001 C CNN
	1    1800 4200
	0    1    1    0   
$EndComp
$Comp
L power:+5V #PWR0124
U 1 1 600972FC
P 2250 3900
F 0 "#PWR0124" H 2250 3750 50  0001 C CNN
F 1 "+5V" H 2265 4073 50  0000 C CNN
F 2 "" H 2250 3900 50  0001 C CNN
F 3 "" H 2250 3900 50  0001 C CNN
	1    2250 3900
	1    0    0    -1  
$EndComp
$Comp
L Transistor_BJT:2N2219 Q1
U 1 1 60097302
P 1350 4250
F 0 "Q1" H 1540 4296 50  0000 L CNN
F 1 "2N2219" H 1540 4205 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-39-3" H 1550 4175 50  0001 L CIN
F 3 "http://www.onsemi.com/pub_link/Collateral/2N2219-D.PDF" H 1350 4250 50  0001 L CNN
	1    1350 4250
	0    1    1    0   
$EndComp
$Comp
L Device:R R1
U 1 1 60097308
P 1150 4050
F 0 "R1" V 943 4050 50  0000 C CNN
F 1 "10k" V 1034 4050 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P5.08mm_Horizontal" V 1080 4050 50  0001 C CNN
F 3 "~" H 1150 4050 50  0001 C CNN
	1    1150 4050
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR0125
U 1 1 6009730E
P 1050 4400
F 0 "#PWR0125" H 1050 4150 50  0001 C CNN
F 1 "GND" H 1055 4227 50  0000 C CNN
F 2 "" H 1050 4400 50  0001 C CNN
F 3 "" H 1050 4400 50  0001 C CNN
	1    1050 4400
	1    0    0    -1  
$EndComp
Wire Wire Line
	1300 4050 1350 4050
Wire Wire Line
	2250 4500 2250 4550
Wire Wire Line
	2250 4550 1800 4550
Wire Wire Line
	1800 4550 1800 4350
Wire Wire Line
	1800 4050 1800 3900
Wire Wire Line
	1800 3900 2250 3900
Text GLabel 1000 4050 0    50   Input ~ 0
Relay1
Wire Wire Line
	1550 4350 1800 4350
Connection ~ 1800 4350
Wire Wire Line
	1150 4350 1050 4350
Wire Wire Line
	1050 4350 1050 4400
Connection ~ 2250 3900
$Comp
L Relay:SANYOU_SRD_Form_C K2
U 1 1 601DB785
P 2450 5100
F 0 "K2" H 2880 5146 50  0000 L CNN
F 1 "SANYOU_SRD_Form_C" H 2880 5055 50  0000 L CNN
F 2 "Relay_THT:Relay_SPDT_SANYOU_SRD_Series_Form_C" H 2900 5050 50  0001 L CNN
F 3 "http://www.sanyourelay.ca/public/products/pdf/SRD.pdf" H 2450 5100 50  0001 C CNN
	1    2450 5100
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x03 J2
U 1 1 601DB78B
P 4250 5100
F 0 "J2" H 4330 5142 50  0000 L CNN
F 1 "Conn_01x03" H 4330 5051 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x03_P2.54mm_Vertical" H 4250 5100 50  0001 C CNN
F 3 "~" H 4250 5100 50  0001 C CNN
	1    4250 5100
	1    0    0    -1  
$EndComp
Wire Wire Line
	3850 5000 4050 5000
Text Label 3900 5000 0    50   ~ 0
NC_2
Text Label 3900 5100 0    50   ~ 0
COM_2
Text Label 3900 5200 0    50   ~ 0
NO_2
Wire Wire Line
	2650 5400 3700 5400
Wire Wire Line
	3700 5400 3700 5100
Wire Wire Line
	3700 5100 4050 5100
Wire Wire Line
	3850 5000 3850 4650
Wire Wire Line
	3850 4650 2550 4650
Wire Wire Line
	2550 4650 2550 4800
Wire Wire Line
	2750 4800 3750 4800
Wire Wire Line
	3750 4800 3750 5200
Wire Wire Line
	3750 5200 4050 5200
$Comp
L Device:D D2
U 1 1 601DB79E
P 1800 5100
F 0 "D2" V 1754 5180 50  0000 L CNN
F 1 "D" V 1845 5180 50  0000 L CNN
F 2 "Diode_THT:D_A-405_P7.62mm_Horizontal" H 1800 5100 50  0001 C CNN
F 3 "~" H 1800 5100 50  0001 C CNN
	1    1800 5100
	0    1    1    0   
$EndComp
$Comp
L power:+5V #PWR0126
U 1 1 601DB7A4
P 2250 4800
F 0 "#PWR0126" H 2250 4650 50  0001 C CNN
F 1 "+5V" H 2265 4973 50  0000 C CNN
F 2 "" H 2250 4800 50  0001 C CNN
F 3 "" H 2250 4800 50  0001 C CNN
	1    2250 4800
	1    0    0    -1  
$EndComp
$Comp
L Transistor_BJT:2N2219 Q2
U 1 1 601DB7AA
P 1350 5150
F 0 "Q2" H 1540 5196 50  0000 L CNN
F 1 "2N2219" H 1540 5105 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-39-3" H 1550 5075 50  0001 L CIN
F 3 "http://www.onsemi.com/pub_link/Collateral/2N2219-D.PDF" H 1350 5150 50  0001 L CNN
	1    1350 5150
	0    1    1    0   
$EndComp
$Comp
L Device:R R2
U 1 1 601DB7B0
P 1150 4950
F 0 "R2" V 943 4950 50  0000 C CNN
F 1 "10k" V 1034 4950 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P5.08mm_Horizontal" V 1080 4950 50  0001 C CNN
F 3 "~" H 1150 4950 50  0001 C CNN
	1    1150 4950
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR0127
U 1 1 601DB7B6
P 1050 5300
F 0 "#PWR0127" H 1050 5050 50  0001 C CNN
F 1 "GND" H 1055 5127 50  0000 C CNN
F 2 "" H 1050 5300 50  0001 C CNN
F 3 "" H 1050 5300 50  0001 C CNN
	1    1050 5300
	1    0    0    -1  
$EndComp
Wire Wire Line
	1300 4950 1350 4950
Wire Wire Line
	2250 5400 2250 5450
Wire Wire Line
	2250 5450 1800 5450
Wire Wire Line
	1800 5450 1800 5250
Wire Wire Line
	1800 4950 1800 4800
Wire Wire Line
	1800 4800 2250 4800
Text GLabel 1000 4950 0    50   Input ~ 0
Relay1
Wire Wire Line
	1550 5250 1800 5250
Connection ~ 1800 5250
Wire Wire Line
	1150 5250 1050 5250
Wire Wire Line
	1050 5250 1050 5300
Connection ~ 2250 4800
$Comp
L Relay:SANYOU_SRD_Form_C K3
U 1 1 601ECC77
P 2450 6000
F 0 "K3" H 2880 6046 50  0000 L CNN
F 1 "SANYOU_SRD_Form_C" H 2880 5955 50  0000 L CNN
F 2 "Relay_THT:Relay_SPDT_SANYOU_SRD_Series_Form_C" H 2900 5950 50  0001 L CNN
F 3 "http://www.sanyourelay.ca/public/products/pdf/SRD.pdf" H 2450 6000 50  0001 C CNN
	1    2450 6000
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x03 J3
U 1 1 601ECC7D
P 4250 6000
F 0 "J3" H 4330 6042 50  0000 L CNN
F 1 "Conn_01x03" H 4330 5951 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x03_P2.54mm_Vertical" H 4250 6000 50  0001 C CNN
F 3 "~" H 4250 6000 50  0001 C CNN
	1    4250 6000
	1    0    0    -1  
$EndComp
Wire Wire Line
	3850 5900 4050 5900
Text Label 3900 5900 0    50   ~ 0
NC_3
Text Label 3900 6000 0    50   ~ 0
COM_3
Text Label 3900 6100 0    50   ~ 0
NO_3
Wire Wire Line
	2650 6300 3700 6300
Wire Wire Line
	3700 6300 3700 6000
Wire Wire Line
	3700 6000 4050 6000
Wire Wire Line
	3850 5900 3850 5550
Wire Wire Line
	3850 5550 2550 5550
Wire Wire Line
	2550 5550 2550 5700
Wire Wire Line
	2750 5700 3750 5700
Wire Wire Line
	3750 5700 3750 6100
Wire Wire Line
	3750 6100 4050 6100
$Comp
L Device:D D3
U 1 1 601ECC90
P 1800 6000
F 0 "D3" V 1754 6080 50  0000 L CNN
F 1 "D" V 1845 6080 50  0000 L CNN
F 2 "Diode_THT:D_A-405_P7.62mm_Horizontal" H 1800 6000 50  0001 C CNN
F 3 "~" H 1800 6000 50  0001 C CNN
	1    1800 6000
	0    1    1    0   
$EndComp
$Comp
L power:+5V #PWR0128
U 1 1 601ECC96
P 2250 5700
F 0 "#PWR0128" H 2250 5550 50  0001 C CNN
F 1 "+5V" H 2265 5873 50  0000 C CNN
F 2 "" H 2250 5700 50  0001 C CNN
F 3 "" H 2250 5700 50  0001 C CNN
	1    2250 5700
	1    0    0    -1  
$EndComp
$Comp
L Transistor_BJT:2N2219 Q3
U 1 1 601ECC9C
P 1350 6050
F 0 "Q3" H 1540 6096 50  0000 L CNN
F 1 "2N2219" H 1540 6005 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-39-3" H 1550 5975 50  0001 L CIN
F 3 "http://www.onsemi.com/pub_link/Collateral/2N2219-D.PDF" H 1350 6050 50  0001 L CNN
	1    1350 6050
	0    1    1    0   
$EndComp
$Comp
L Device:R R3
U 1 1 601ECCA2
P 1150 5850
F 0 "R3" V 943 5850 50  0000 C CNN
F 1 "10k" V 1034 5850 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P5.08mm_Horizontal" V 1080 5850 50  0001 C CNN
F 3 "~" H 1150 5850 50  0001 C CNN
	1    1150 5850
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR0129
U 1 1 601ECCA8
P 1050 6200
F 0 "#PWR0129" H 1050 5950 50  0001 C CNN
F 1 "GND" H 1055 6027 50  0000 C CNN
F 2 "" H 1050 6200 50  0001 C CNN
F 3 "" H 1050 6200 50  0001 C CNN
	1    1050 6200
	1    0    0    -1  
$EndComp
Wire Wire Line
	1300 5850 1350 5850
Wire Wire Line
	2250 6300 2250 6350
Wire Wire Line
	2250 6350 1800 6350
Wire Wire Line
	1800 6350 1800 6150
Wire Wire Line
	1800 5850 1800 5700
Wire Wire Line
	1800 5700 2250 5700
Text GLabel 1000 5850 0    50   Input ~ 0
Relay1
Wire Wire Line
	1550 6150 1800 6150
Connection ~ 1800 6150
Wire Wire Line
	1150 6150 1050 6150
Wire Wire Line
	1050 6150 1050 6200
Connection ~ 2250 5700
$Comp
L Relay:SANYOU_SRD_Form_C K4
U 1 1 601FCAA0
P 2450 6950
F 0 "K4" H 2880 6996 50  0000 L CNN
F 1 "SANYOU_SRD_Form_C" H 2880 6905 50  0000 L CNN
F 2 "Relay_THT:Relay_SPDT_SANYOU_SRD_Series_Form_C" H 2900 6900 50  0001 L CNN
F 3 "http://www.sanyourelay.ca/public/products/pdf/SRD.pdf" H 2450 6950 50  0001 C CNN
	1    2450 6950
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x03 J4
U 1 1 601FCAA6
P 4250 6950
F 0 "J4" H 4330 6992 50  0000 L CNN
F 1 "Conn_01x03" H 4330 6901 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x03_P2.54mm_Vertical" H 4250 6950 50  0001 C CNN
F 3 "~" H 4250 6950 50  0001 C CNN
	1    4250 6950
	1    0    0    -1  
$EndComp
Wire Wire Line
	3850 6850 4050 6850
Text Label 3900 6850 0    50   ~ 0
NC
Text Label 3900 6950 0    50   ~ 0
COM
Text Label 3900 7050 0    50   ~ 0
NO
Wire Wire Line
	2650 7250 3700 7250
Wire Wire Line
	3700 7250 3700 6950
Wire Wire Line
	3700 6950 4050 6950
Wire Wire Line
	3850 6850 3850 6500
Wire Wire Line
	3850 6500 2550 6500
Wire Wire Line
	2550 6500 2550 6650
Wire Wire Line
	2750 6650 3750 6650
Wire Wire Line
	3750 6650 3750 7050
Wire Wire Line
	3750 7050 4050 7050
$Comp
L Device:D D4
U 1 1 601FCAB9
P 1800 6950
F 0 "D4" V 1754 7030 50  0000 L CNN
F 1 "D" V 1845 7030 50  0000 L CNN
F 2 "Diode_THT:D_A-405_P7.62mm_Horizontal" H 1800 6950 50  0001 C CNN
F 3 "~" H 1800 6950 50  0001 C CNN
	1    1800 6950
	0    1    1    0   
$EndComp
$Comp
L power:+5V #PWR0130
U 1 1 601FCABF
P 2250 6650
F 0 "#PWR0130" H 2250 6500 50  0001 C CNN
F 1 "+5V" H 2265 6823 50  0000 C CNN
F 2 "" H 2250 6650 50  0001 C CNN
F 3 "" H 2250 6650 50  0001 C CNN
	1    2250 6650
	1    0    0    -1  
$EndComp
$Comp
L Transistor_BJT:2N2219 Q4
U 1 1 601FCAC5
P 1350 7000
F 0 "Q4" H 1540 7046 50  0000 L CNN
F 1 "2N2219" H 1540 6955 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-39-3" H 1550 6925 50  0001 L CIN
F 3 "http://www.onsemi.com/pub_link/Collateral/2N2219-D.PDF" H 1350 7000 50  0001 L CNN
	1    1350 7000
	0    1    1    0   
$EndComp
$Comp
L Device:R R4
U 1 1 601FCACB
P 1150 6800
F 0 "R4" V 943 6800 50  0000 C CNN
F 1 "10k" V 1034 6800 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P5.08mm_Horizontal" V 1080 6800 50  0001 C CNN
F 3 "~" H 1150 6800 50  0001 C CNN
	1    1150 6800
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR0131
U 1 1 601FCAD1
P 1050 7150
F 0 "#PWR0131" H 1050 6900 50  0001 C CNN
F 1 "GND" H 1055 6977 50  0000 C CNN
F 2 "" H 1050 7150 50  0001 C CNN
F 3 "" H 1050 7150 50  0001 C CNN
	1    1050 7150
	1    0    0    -1  
$EndComp
Wire Wire Line
	1300 6800 1350 6800
Wire Wire Line
	2250 7250 2250 7300
Wire Wire Line
	2250 7300 1800 7300
Wire Wire Line
	1800 7300 1800 7100
Wire Wire Line
	1800 6800 1800 6650
Wire Wire Line
	1800 6650 2250 6650
Text GLabel 1000 6800 0    50   Input ~ 0
Relay1
Wire Wire Line
	1550 7100 1800 7100
Connection ~ 1800 7100
Wire Wire Line
	1150 7100 1050 7100
Wire Wire Line
	1050 7100 1050 7150
Connection ~ 2250 6650
$Comp
L Connector_Generic:Conn_01x04 J14
U 1 1 602972B5
P 10300 5300
F 0 "J14" H 10380 5292 50  0000 L CNN
F 1 "Conn_01x04" H 10380 5201 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x04_P2.54mm_Vertical" H 10300 5300 50  0001 C CNN
F 3 "~" H 10300 5300 50  0001 C CNN
	1    10300 5300
	1    0    0    -1  
$EndComp
Wire Wire Line
	9750 5200 10100 5200
Wire Wire Line
	9750 5500 10100 5500
Wire Wire Line
	9750 5400 10100 5400
Text Label 9850 5300 0    50   ~ 0
VCC
Text Label 9850 5200 0    50   ~ 0
GND
Text Label 9850 5500 0    50   ~ 0
SCL
Text Label 9850 5400 0    50   ~ 0
SDA
$Comp
L power:+3.3V #PWR0132
U 1 1 60344351
P 9450 5200
F 0 "#PWR0132" H 9450 5050 50  0001 C CNN
F 1 "+3.3V" H 9465 5373 50  0000 C CNN
F 2 "" H 9450 5200 50  0001 C CNN
F 3 "" H 9450 5200 50  0001 C CNN
	1    9450 5200
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0133
U 1 1 60355B3F
P 9750 5200
F 0 "#PWR0133" H 9750 4950 50  0001 C CNN
F 1 "GND" H 9755 5027 50  0000 C CNN
F 2 "" H 9750 5200 50  0001 C CNN
F 3 "" H 9750 5200 50  0001 C CNN
	1    9750 5200
	0    1    1    0   
$EndComp
Wire Wire Line
	9450 5200 9450 5300
Wire Wire Line
	9450 5300 10100 5300
Text GLabel 9750 5400 0    50   Input ~ 0
SDA
Text GLabel 9750 5500 0    50   Input ~ 0
SCL
Text GLabel 10450 1400 2    50   Input ~ 0
SDA
Text GLabel 10450 1300 2    50   Input ~ 0
SCL
Wire Wire Line
	9850 1300 10450 1300
Wire Wire Line
	9850 1400 10450 1400
Wire Wire Line
	2650 750  2650 1000
Text GLabel 10650 3100 2    50   Input ~ 0
Input1
Text GLabel 10650 3200 2    50   Input ~ 0
Input2
Text GLabel 10650 3300 2    50   Input ~ 0
Input3
Text GLabel 10650 3400 2    50   Input ~ 0
Input3
$Comp
L Connector_Generic:Conn_01x04 J15
U 1 1 605817A4
P 5650 850
F 0 "J15" H 5730 842 50  0000 L CNN
F 1 "Conn_01x04" H 5730 751 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x04_P2.54mm_Vertical" H 5650 850 50  0001 C CNN
F 3 "~" H 5650 850 50  0001 C CNN
	1    5650 850 
	1    0    0    -1  
$EndComp
Text Label 5250 850  0    50   ~ 0
CANH
Text Label 5250 950  0    50   ~ 0
CANL
Wire Wire Line
	5150 950  5450 950 
Wire Wire Line
	5150 850  5450 850 
$Comp
L power:GND #PWR?
U 1 1 5F9792A8
P 5550 3400
F 0 "#PWR?" H 5550 3150 50  0001 C CNN
F 1 "GND" H 5555 3227 50  0000 C CNN
F 2 "" H 5550 3400 50  0001 C CNN
F 3 "" H 5550 3400 50  0001 C CNN
	1    5550 3400
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 5F9CAEDF
P 5550 3250
F 0 "R?" H 5620 3296 50  0000 L CNN
F 1 "R" H 5620 3205 50  0000 L CNN
F 2 "" V 5480 3250 50  0001 C CNN
F 3 "~" H 5550 3250 50  0001 C CNN
	1    5550 3250
	1    0    0    -1  
$EndComp
Text GLabel 5400 2700 0    50   Input ~ 0
LED1
Text GLabel 8800 1200 0    50   Input ~ 0
PB1
Wire Wire Line
	8800 1200 9350 1200
Wire Wire Line
	5400 2700 5550 2700
$Comp
L Switch:SW_Push SW?
U 1 1 5FA93F97
P 4900 2900
F 0 "SW?" V 4854 3048 50  0000 L CNN
F 1 "SW_Push" V 4945 3048 50  0000 L CNN
F 2 "" H 4900 3100 50  0001 C CNN
F 3 "~" H 4900 3100 50  0001 C CNN
	1    4900 2900
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5FA93F9D
P 4900 3400
F 0 "#PWR?" H 4900 3150 50  0001 C CNN
F 1 "GND" H 4905 3227 50  0000 C CNN
F 2 "" H 4900 3400 50  0001 C CNN
F 3 "" H 4900 3400 50  0001 C CNN
	1    4900 3400
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 5FA93FA3
P 4900 3250
F 0 "R?" H 4970 3296 50  0000 L CNN
F 1 "R" H 4970 3205 50  0000 L CNN
F 2 "" V 4830 3250 50  0001 C CNN
F 3 "~" H 4900 3250 50  0001 C CNN
	1    4900 3250
	1    0    0    -1  
$EndComp
Text GLabel 4750 2700 0    50   Input ~ 0
PB1
Wire Wire Line
	4750 2700 4900 2700
$Comp
L Device:LED D?
U 1 1 5FACB7B3
P 5550 2950
F 0 "D?" V 5589 2832 50  0000 R CNN
F 1 "LED" V 5498 2832 50  0000 R CNN
F 2 "" H 5550 2950 50  0001 C CNN
F 3 "~" H 5550 2950 50  0001 C CNN
	1    5550 2950
	0    -1   -1   0   
$EndComp
Wire Wire Line
	5550 2700 5550 2800
Text GLabel 8800 1300 0    50   Input ~ 0
LED1
Wire Wire Line
	8800 1300 9350 1300
$EndSCHEMATC
