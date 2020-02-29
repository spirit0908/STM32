EESchema Schematic File Version 4
EELAYER 26 0
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
L pspice:DIODE D1
U 1 1 5B9BEDA7
P 4900 2050
F 0 "D1" H 4900 2315 50  0000 C CNN
F 1 "DIODE" H 4900 2224 50  0000 C CNN
F 2 "" H 4900 2050 50  0001 C CNN
F 3 "" H 4900 2050 50  0001 C CNN
	1    4900 2050
	0    -1   -1   0   
$EndComp
$Comp
L Connector:Screw_Terminal_01x03 J1
U 1 1 5B9BF13A
P 7000 2050
F 0 "J1" H 7080 2092 50  0000 L CNN
F 1 "Screw_Terminal_01x03" H 7080 2001 50  0000 L CNN
F 2 "" H 7000 2050 50  0001 C CNN
F 3 "~" H 7000 2050 50  0001 C CNN
	1    7000 2050
	1    0    0    -1  
$EndComp
$Comp
L Transistor_Array:ULN2803A U2
U 1 1 5B9BFE8D
P 4700 6400
F 0 "U2" H 4700 6967 50  0000 C CNN
F 1 "ULN2803A" H 4700 6876 50  0000 C CNN
F 2 "" H 4750 5750 50  0001 L CNN
F 3 "http://www.ti.com/lit/ds/symlink/uln2803a.pdf" H 4800 6200 50  0001 C CNN
	1    4700 6400
	1    0    0    -1  
$EndComp
Wire Wire Line
	5750 2350 6400 2350
Wire Wire Line
	6400 2350 6400 2050
Wire Wire Line
	6400 2050 6800 2050
Wire Wire Line
	6800 1950 6700 1950
Wire Wire Line
	6700 1950 6700 1650
Wire Wire Line
	6700 1650 5650 1650
Wire Wire Line
	6600 2150 6800 2150
$Comp
L power:+5V #PWR0101
U 1 1 5B9C039A
P 4900 1600
F 0 "#PWR0101" H 4900 1450 50  0001 C CNN
F 1 "+5V" H 4915 1773 50  0000 C CNN
F 2 "" H 4900 1600 50  0001 C CNN
F 3 "" H 4900 1600 50  0001 C CNN
	1    4900 1600
	1    0    0    -1  
$EndComp
$Comp
L Isolator:PC817 U1
U 1 1 5B9C0F1B
P 3800 2150
F 0 "U1" H 3800 2475 50  0000 C CNN
F 1 "PC817" H 3800 2384 50  0000 C CNN
F 2 "Package_DIP:DIP-4_W7.62mm" H 3600 1950 50  0001 L CIN
F 3 "http://www.soselectronic.cz/a_info/resource/d/pc817.pdf" H 3800 2150 50  0001 L CNN
	1    3800 2150
	1    0    0    -1  
$EndComp
Wire Wire Line
	5350 1750 5350 1700
Wire Wire Line
	5350 1700 4900 1700
Wire Wire Line
	4900 1700 4900 1850
Wire Wire Line
	4900 2250 4900 2400
Wire Wire Line
	4900 2400 5350 2400
Wire Wire Line
	5350 2400 5350 2350
$Comp
L power:GND #PWR0102
U 1 1 5B9C1C7B
P 4900 2800
F 0 "#PWR0102" H 4900 2550 50  0001 C CNN
F 1 "GND" H 4905 2627 50  0000 C CNN
F 2 "" H 4900 2800 50  0001 C CNN
F 3 "" H 4900 2800 50  0001 C CNN
	1    4900 2800
	1    0    0    -1  
$EndComp
Wire Wire Line
	4900 1600 4900 1700
Connection ~ 4900 1700
Wire Wire Line
	4100 2250 4250 2250
Wire Wire Line
	5850 1750 6600 1750
Wire Wire Line
	6600 1750 6600 2150
Wire Wire Line
	5650 1650 5650 1750
$Comp
L power:GND #PWR0103
U 1 1 5B9C4659
P 3500 2300
F 0 "#PWR0103" H 3500 2050 50  0001 C CNN
F 1 "GND" H 3505 2127 50  0000 C CNN
F 2 "" H 3500 2300 50  0001 C CNN
F 3 "" H 3500 2300 50  0001 C CNN
	1    3500 2300
	1    0    0    -1  
$EndComp
Wire Wire Line
	3500 2250 3500 2300
$Comp
L Device:R R1
U 1 1 5B9C4E44
P 3200 2050
F 0 "R1" V 2993 2050 50  0000 C CNN
F 1 "R" V 3084 2050 50  0000 C CNN
F 2 "" V 3130 2050 50  0001 C CNN
F 3 "~" H 3200 2050 50  0001 C CNN
	1    3200 2050
	0    1    1    0   
$EndComp
Wire Wire Line
	3500 2050 3350 2050
$Comp
L Transistor_BJT:BC141 Q1
U 1 1 5B9C5AA9
P 4800 2600
F 0 "Q1" H 4991 2646 50  0000 L CNN
F 1 "BC141" H 4991 2555 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-39-3" H 5000 2525 50  0001 L CIN
F 3 "http://www.farnell.com/datasheets/296634.pdf" H 4800 2600 50  0001 L CNN
	1    4800 2600
	1    0    0    -1  
$EndComp
Connection ~ 4900 2400
$Comp
L Device:R R2
U 1 1 5B9C645A
P 4450 2600
F 0 "R2" V 4243 2600 50  0000 C CNN
F 1 "R" V 4334 2600 50  0000 C CNN
F 2 "" V 4380 2600 50  0001 C CNN
F 3 "~" H 4450 2600 50  0001 C CNN
	1    4450 2600
	0    1    1    0   
$EndComp
Wire Wire Line
	4250 2250 4250 2600
Wire Wire Line
	4250 2600 4300 2600
Wire Wire Line
	4350 2050 4350 1700
Wire Wire Line
	4350 1700 4900 1700
Wire Wire Line
	4100 2050 4350 2050
$Comp
L Relay:SILxx-1Cxx-51x K1
U 1 1 5B9C7E88
P 5550 2050
F 0 "K1" H 5980 2096 50  0000 L CNN
F 1 "SILxx-1Cxx-51x" H 5980 2005 50  0000 L CNN
F 2 "Relay_THT:Relay_SPDT_StandexMeder_SIL_Form1C" H 6000 2000 50  0001 L CNN
F 3 "https://standexelectronics.com/wp-content/uploads/datasheet_reed_relay_SIL.pdf" H 5550 2050 50  0001 C CNN
	1    5550 2050
	1    0    0    -1  
$EndComp
$EndSCHEMATC
