<table border="0">
  <tr>
    <td align="left" valign="middle">
    <h1>EFM32 and EFR32<br/>Platform Examples</h1>
  </td>
  <td align="left" valign="middle">
    <a href="https://www.silabs.com/mcu/32-bit">
      <img src="http://pages.silabs.com/rs/634-SLU-379/images/WGX-transparent.png"  title="Silicon Labs Gecko and Wireless Gecko MCUs" alt="EFM32 32-bit Microcontrollers" width="250"/>
    </a>
  </td>
  </tr>
</table>

# Quickly Add an Accelerometer with SPI #

Our energy-friendly EFM32 and EFR32 microcontrollers (MCUs) are ideal for ultra-low power applications. Based on ARM® Cortex® -M0+, Cortex-M3, and Cortex-M4 cores, our 32-bit MCUs extend battery life for those "hard-to-reach", power-sensitive consumer and industrial applications. Engineered for low power and intelligent design, our MCUs can scale power consumption while still performing real-time embedded tasks.

## Overview ##

### Topic Covered ###
- imu (Inertia Motion Sensor) sensor
- Software component
- Pintool
- Simplicity Studio v5

## Component dependency ##

- peripheral_examples
  - Examples that demonstrate the peripherals of Silicon Labs Series 0, Series 1, and Series 2 devices.
- platform_applications
  - Platform examples made for EFM and EFR devices.

## Low level driver ##

- EFM32ZG
- EFM32HG
- 

## Code generation ##

- EFM32PG1
- EFR32MG1
- 

## Peripheral Reflex System ##

- EFR32MG21
- EFR32BG21

## Getting Started ##
Review the following material before starting the Bluetooth 5 labs. Ensure that you have the correct hardware and software to successfully complete the labs.

# Hardware Requirements #
Silicon Labs Thunderboard BG22 Kit: SLTB010A
EFR32BG22 Soc
# Software Requirements #
Simplicity Studio v5
Gecko SDK v3.0 with the Bluetooth stack installed
EFRConnect Mobile App
# Install Tools #
Download and install Simplicity Studio 5 if it is not already installed.

# Connect your Hardware #



# Lab #
## Creating the Project ##
1. If the BG22 WSTK has not been plugged in using the USB cable, do so now. The kit and debug information should be displayed in the Debug Adapters window.
2. In the Debug Adapters window, click on the device.
3. Information about the target hardware and software will appear. If this does not appear, click on the Launcher button in the top right corner.
4. Select the Preferred SDK to the latest version. For this lab, the latest version of Gecko SDK (v3.1.0) is used.
5. Click on Create New Project in the upper right hand corner. A "New Project Wizard" window should appear.

## Documentation ##

# Code Explanation #
## Creating the Project ##
## Documentation ##


# Source #
## sl_icm20648.c ##
- aa
- mm
## sl_icm20648_config.h ##
--bbbb

# Porting consideration #
## other driver ##
sensor with i2c
driver levels
Your own driver.

# Reference #
## peripheral examples ##
## platform application ##
## platform hardware driver ##
