# **Controlled Ice Cream Truck**  :car:

## Overview
Mobile platform remote controlled via applictaion using Bluetooth/Uart.

## Description
Controllerd Ice Cream is an university project made by Olga Detko and Małgorzata Marczyk - student's at Electric Department 
of Poznan University of Technology. 
Remote control the car is possible thanks to the application RoboRemoFree on Android and via Bluetooth connection (USART). 
There are 4 button responible for direction and 1 using for evoke special sound. 
The power supply of STM32 board and engine is from powerbank. 

## Tools
- STM32F4 Discovery board
- 2x engine HG7881
- Bluetooth 2.1 XM-15B
- RGB diode
- DAC converter
- car platform
- RoboRemoFree app on Android

## How to run 
Fetch our project, and run it using System Workbenc for STM32. 
Upload program to STM32F4 Discovery and connect all needed pins:


Engines - Discovery:
- A-IA (right engine) -> PE9
- A-IB (right engine) -> PE7
- B-IA (right engine) -> PE3
- B-IB (right engine) -> PE1
- VCC (right engine) -> 5V
- GND (right engine) -> GND
- A-IA (left engine) -> PE10
- A-IB (left engine) -> PE8
- B-IA (left engine) -> PE2
- B-IB (left engine) -> PE0
- VCC (left engine) -> 5V
- GND (left engine) -> GND


Bluetooth - Discovery:
- VCC -> VDD
- GND -> GND
- TXD -> PC11
- RXD -> PC10

RGB Diod (1)- Discovery:
- B -> PD12
- GND -> GND

RGB Diod (2)- Discovery:
- B -> PD13
- GND -> GND

DAC Converter - Discovery:
- VCC ->VDD
- GND -> GND
- ACD2 -> PA1
- AIN -> PA4
- +5V -> VDD/5V

## Attributions 
We've been using codes and documentations provided by each device's manufacturer. For example:
- https://abc-rc.pl/modul-podwojnego-sterownika-l9110
- https://botland.com.pl/moduly-bluetooth/6642-modul-bluetooth-21-xm-15b-33v5v.html
- http://www.st.com/content/ccc/resource/technical/document/user_manual/59/2d/ab/ad/f8/29/49/d6/DM00023896.pdf/files/DM00023896.pdf/jcr:content/translations/en.DM00023896.pdf

## How to compile:
Let your compiler do the work, there is nothing more to it.

## License
[MIT](https://github.com/OlgaDetko/Controlled-Ice-Cream-Truck/blob/master/LICENSE.md/LICENSE.md) license

## Credits 
- Olga Detko
- Małgorzata Marczyk

*The project was conducted during the Microprocessor Lab course held by the Institute of Control and Information Engineering, Poznan University of Technology.
Supervisor: Marek Kraft/Michał Fularz/Tomasz Mańkowski/Adam Bondyra*





