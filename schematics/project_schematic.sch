EESchema Schematic File Version 2
LIBS:power
LIBS:device
LIBS:switches
LIBS:relays
LIBS:motors
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:avr_atmega162
LIBS:project_schematic-cache
EELAYER 25 0
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
L LM7805_TO220 U?
U 1 1 5B86E5CE
P 1650 950
F 0 "U?" H 1500 1075 50  0000 C CNN
F 1 "LM7805_TO220" H 1650 1075 50  0000 L CNN
F 2 "TO_SOT_Packages_THT:TO-220_Vertical" H 1650 1175 50  0001 C CIN
F 3 "" H 1650 900 50  0001 C CNN
	1    1650 950 
	1    0    0    -1  
$EndComp
$Comp
L CP C_in
U 1 1 5B86E8C8
P 1250 1100
F 0 "C_in" H 1275 1200 50  0000 L CNN
F 1 "1uF" H 950 1000 50  0000 L CNN
F 2 "" H 1288 950 50  0001 C CNN
F 3 "" H 1250 1100 50  0001 C CNN
	1    1250 1100
	1    0    0    -1  
$EndComp
$Comp
L CP C_out
U 1 1 5B86EA19
P 2050 1100
F 0 "C_out" H 2075 1200 50  0000 L CNN
F 1 "0,1uF" H 2100 1000 50  0000 L CNN
F 2 "" H 2088 950 50  0001 C CNN
F 3 "" H 2050 1100 50  0001 C CNN
	1    2050 1100
	1    0    0    -1  
$EndComp
$Comp
L AVR_atmega162 U?
U 1 1 5B878E1F
P 6550 4050
F 0 "U?" H 7150 5150 79  0000 C CNN
F 1 "AVR_atmega162" V 6450 4300 79  0000 C CNN
F 2 "" H 6450 3150 79  0001 C CNN
F 3 "" H 6450 3150 79  0001 C CNN
	1    6550 4050
	0    1    1    0   
$EndComp
$Comp
L CP C?
U 1 1 5B87909F
P 7600 5300
F 0 "C?" H 7625 5400 50  0000 L CNN
F 1 "CP" H 7625 5200 50  0000 L CNN
F 2 "" H 7638 5150 50  0001 C CNN
F 3 "" H 7600 5300 50  0001 C CNN
	1    7600 5300
	0    -1   -1   0   
$EndComp
Connection ~ 1250 950 
Wire Wire Line
	1950 950  2550 950 
Wire Wire Line
	7350 5300 7450 5300
Connection ~ 7350 5300
Wire Wire Line
	5450 1100 5450 2600
Wire Wire Line
	6550 1900 6550 2600
$Comp
L R_Small R
U 1 1 5B879841
P 6550 1800
F 0 "R" H 6580 1820 50  0000 L CNN
F 1 "330R" H 6580 1760 50  0000 L CNN
F 2 "" H 6550 1800 50  0001 C CNN
F 3 "" H 6550 1800 50  0001 C CNN
	1    6550 1800
	1    0    0    -1  
$EndComp
$Comp
L C_Small C
U 1 1 5B8798AD
P 7000 1800
F 0 "C" H 7010 1870 50  0000 L CNN
F 1 "0,1uF" H 7010 1720 50  0000 L CNN
F 2 "" H 7000 1800 50  0001 C CNN
F 3 "" H 7000 1800 50  0001 C CNN
	1    7000 1800
	1    0    0    -1  
$EndComp
Wire Wire Line
	6550 2000 7000 2000
Wire Wire Line
	7000 2000 7000 1900
Connection ~ 6550 2000
Wire Wire Line
	7000 1700 7000 1100
Connection ~ 7000 1100
$Comp
L SW_Push SW?
U 1 1 5B879980
P 6550 1500
F 0 "SW?" H 6600 1600 50  0000 L CNN
F 1 "SW_Push" H 6550 1440 50  0000 C CNN
F 2 "" H 6550 1700 50  0001 C CNN
F 3 "" H 6550 1700 50  0001 C CNN
	1    6550 1500
	0    1    1    0   
$EndComp
Wire Wire Line
	6550 1300 6550 1100
Connection ~ 6550 1100
Wire Wire Line
	5550 1450 5550 2600
Wire Wire Line
	5650 1950 5650 2600
$Comp
L Crystal 4.9152Mhz
U 1 1 5B87AC0A
P 5700 1700
F 0 "4.9152Mhz" V 5500 1700 50  0000 C CNN
F 1 "Crystal" H 5700 1550 50  0000 C CNN
F 2 "" H 5700 1700 50  0001 C CNN
F 3 "" H 5700 1700 50  0001 C CNN
	1    5700 1700
	1    0    0    -1  
$EndComp
Wire Wire Line
	5650 1950 5850 1950
Wire Wire Line
	5850 1950 5850 1450
$Comp
L CP1_Small C
U 1 1 5B87B1B0
P 5550 1350
F 0 "C" H 5560 1420 50  0000 L CNN
F 1 "22pF" H 5560 1270 50  0000 L CNN
F 2 "" H 5550 1350 50  0001 C CNN
F 3 "" H 5550 1350 50  0001 C CNN
	1    5550 1350
	-1   0    0    1   
$EndComp
$Comp
L CP1_Small C?
U 1 1 5B87B274
P 5850 1350
F 0 "C?" H 5860 1420 50  0000 L CNN
F 1 "22pF" H 5860 1270 50  0000 L CNN
F 2 "" H 5850 1350 50  0001 C CNN
F 3 "" H 5850 1350 50  0001 C CNN
	1    5850 1350
	-1   0    0    1   
$EndComp
Wire Wire Line
	5550 1250 5550 1100
Connection ~ 5550 1100
Wire Wire Line
	5850 1250 5850 1100
Connection ~ 5850 1100
Connection ~ 1650 1250
$Comp
L GND #PWR?
U 1 1 5B88370B
P 1650 1250
F 0 "#PWR?" H 1650 1000 50  0001 C CNN
F 1 "GND" H 1650 1100 50  0000 C CNN
F 2 "" H 1650 1250 50  0001 C CNN
F 3 "" H 1650 1250 50  0001 C CNN
	1    1650 1250
	1    0    0    -1  
$EndComp
Wire Wire Line
	1250 1250 2050 1250
Wire Wire Line
	1350 950  900  950 
Wire Wire Line
	900  950  900  800 
$Comp
L VCC #PWR?
U 1 1 5B88365E
P 900 800
F 0 "#PWR?" H 900 650 50  0001 C CNN
F 1 "VCC" H 900 950 50  0000 C CNN
F 2 "" H 900 800 50  0001 C CNN
F 3 "" H 900 800 50  0001 C CNN
	1    900  800 
	1    0    0    -1  
$EndComp
Text Label 2550 950  0    60   ~ 0
5V
Wire Wire Line
	7000 1100 5100 1100
$Comp
L GND #PWR?
U 1 1 5B883D7D
P 5100 1100
F 0 "#PWR?" H 5100 850 50  0001 C CNN
F 1 "GND" H 5100 950 50  0000 C CNN
F 2 "" H 5100 1100 50  0001 C CNN
F 3 "" H 5100 1100 50  0001 C CNN
	1    5100 1100
	1    0    0    -1  
$EndComp
Wire Wire Line
	7750 5300 7850 5300
$Comp
L GND #PWR?
U 1 1 5B8841BB
P 7850 5300
F 0 "#PWR?" H 7850 5050 50  0001 C CNN
F 1 "GND" H 7850 5150 50  0000 C CNN
F 2 "" H 7850 5300 50  0001 C CNN
F 3 "" H 7850 5300 50  0001 C CNN
	1    7850 5300
	1    0    0    -1  
$EndComp
$Comp
L AVR-JTAG-10 CON?
U 1 1 5B88494F
P 6050 6000
F 0 "CON?" H 5880 6330 50  0000 C CNN
F 1 "AVR-JTAG-10" H 5710 5670 50  0000 L BNN
F 2 "AVR-JTAG-10" V 5480 6020 50  0001 C CNN
F 3 "" H 6050 6000 50  0001 C CNN
	1    6050 6000
	0    -1   1    0   
$EndComp
Wire Wire Line
	7350 5200 7350 5550
Text Notes 2550 1050 0    60   ~ 0
to pin 40 - VCC on AtMega
Wire Wire Line
	5850 5200 5850 5800
Wire Wire Line
	5950 5450 5950 5800
Wire Wire Line
	5950 5450 6050 5450
Wire Wire Line
	6050 5450 6050 5200
Wire Wire Line
	6250 5800 6250 5450
Wire Wire Line
	6250 5450 6150 5450
Wire Wire Line
	6150 5450 6150 5200
$Comp
L GND #PWR?
U 1 1 5B885CB3
P 5950 6800
F 0 "#PWR?" H 5950 6550 50  0001 C CNN
F 1 "GND" H 5950 6650 50  0000 C CNN
F 2 "" H 5950 6800 50  0001 C CNN
F 3 "" H 5950 6800 50  0001 C CNN
	1    5950 6800
	1    0    0    -1  
$EndComp
Wire Wire Line
	6050 5800 6050 5500
Wire Wire Line
	6050 5500 6000 5500
Wire Wire Line
	6000 5500 6000 5400
Wire Wire Line
	6000 5400 5950 5400
Wire Wire Line
	5950 5400 5950 5200
Wire Wire Line
	5950 6050 5950 6500
$Comp
L C_Small 0.1uF??
U 1 1 5B8863A3
P 5950 6600
F 0 "0.1uF??" H 5960 6670 50  0000 L CNN
F 1 "C" H 5960 6520 50  0000 L CNN
F 2 "" H 5950 6600 50  0001 C CNN
F 3 "" H 5950 6600 50  0001 C CNN
	1    5950 6600
	1    0    0    -1  
$EndComp
Wire Wire Line
	5850 6050 5850 6800
Wire Wire Line
	5850 6800 6250 6800
Wire Wire Line
	6250 6800 6250 6050
Wire Wire Line
	5950 6700 5950 6800
Connection ~ 5950 6800
Wire Wire Line
	5950 6450 5550 6450
Connection ~ 5950 6450
$Comp
L MAX233 RS-232?
U 1 1 5B887F08
P 3200 3900
F 0 "RS-232?" H 3500 3450 60  0000 C CNN
F 1 "MAX233" H 3050 3450 60  0000 C CNN
F 2 "" H 2250 4800 60  0001 C CNN
F 3 "" H 2250 4800 60  0001 C CNN
	1    3200 3900
	0    1    1    0   
$EndComp
Connection ~ 5450 1100
Wire Wire Line
	6350 2600 6350 2350
Wire Wire Line
	6350 2350 3450 2350
Wire Wire Line
	3450 1900 3450 3300
Wire Wire Line
	6450 2450 6450 2600
Wire Wire Line
	3550 2450 6450 2450
Connection ~ 3450 2350
Connection ~ 3650 2450
Wire Wire Line
	3550 4550 3550 4750
Wire Wire Line
	3550 4750 3050 4750
Wire Wire Line
	3050 4750 3050 4550
Wire Wire Line
	3450 4550 3450 4850
Wire Wire Line
	3450 4850 2550 4850
Wire Wire Line
	2550 4850 2550 3200
Wire Wire Line
	2550 3200 2950 3200
Wire Wire Line
	2950 3200 2950 3300
Wire Wire Line
	2950 4550 2950 4650
Wire Wire Line
	2950 4650 3350 4650
Wire Wire Line
	3350 4650 3350 4550
Wire Wire Line
	3250 2350 3250 3300
Wire Wire Line
	3250 2550 3150 2550
Connection ~ 3250 2550
$Comp
L CP1_Small C?
U 1 1 5B88C7DE
P 3050 2550
F 0 "C?" H 3060 2620 50  0000 L CNN
F 1 "1uF" H 3060 2470 50  0000 L CNN
F 2 "" H 3050 2550 50  0001 C CNN
F 3 "" H 3050 2550 50  0001 C CNN
	1    3050 2550
	0    1    1    0   
$EndComp
Wire Wire Line
	2550 2550 2950 2550
$Comp
L GND #PWR?
U 1 1 5B88CD96
P 2550 2850
F 0 "#PWR?" H 2550 2600 50  0001 C CNN
F 1 "GND" H 2550 2700 50  0000 C CNN
F 2 "" H 2550 2850 50  0001 C CNN
F 3 "" H 2550 2850 50  0001 C CNN
	1    2550 2850
	1    0    0    -1  
$EndComp
Wire Wire Line
	2550 2550 2550 2850
Wire Wire Line
	3350 3300 3350 2750
Wire Wire Line
	3350 2750 2550 2750
Connection ~ 2550 2750
Wire Wire Line
	3050 3300 3050 2750
Connection ~ 3050 2750
$Comp
L +5V #PWR?
U 1 1 5B88D4B3
P 3250 2350
F 0 "#PWR?" H 3250 2200 50  0001 C CNN
F 1 "+5V" H 3250 2490 50  0000 C CNN
F 2 "" H 3250 2350 50  0001 C CNN
F 3 "" H 3250 2350 50  0001 C CNN
	1    3250 2350
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR?
U 1 1 5B88D57B
P 5550 6450
F 0 "#PWR?" H 5550 6300 50  0001 C CNN
F 1 "+5V" H 5550 6590 50  0000 C CNN
F 2 "" H 5550 6450 50  0001 C CNN
F 3 "" H 5550 6450 50  0001 C CNN
	1    5550 6450
	0    -1   -1   0   
$EndComp
$Comp
L +5V #PWR?
U 1 1 5B88D607
P 7350 5550
F 0 "#PWR?" H 7350 5400 50  0001 C CNN
F 1 "+5V" H 7350 5690 50  0000 C CNN
F 2 "" H 7350 5550 50  0001 C CNN
F 3 "" H 7350 5550 50  0001 C CNN
	1    7350 5550
	1    0    0    1   
$EndComp
Text Notes 7450 7250 0    60   ~ 0
1
Text Notes 7400 7500 0    60   ~ 0
Lab exercise 1
Connection ~ 3550 2450
$Comp
L DB9_Female J?
U 1 1 5B890D48
P 3450 1600
F 0 "J?" H 3450 2150 50  0000 C CNN
F 1 "DB9_Female" H 3450 1025 50  0000 C CNN
F 2 "" H 3450 1600 50  0001 C CNN
F 3 "" H 3450 1600 50  0001 C CNN
	1    3450 1600
	0    -1   -1   0   
$EndComp
Wire Wire Line
	3550 3300 3550 2050
Wire Wire Line
	3550 2050 3250 2050
Wire Wire Line
	3250 2050 3250 1900
$EndSCHEMATC
