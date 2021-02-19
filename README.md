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

# Getting Started #
Review the following material before starting the Bluetooth 5 labs. Ensure that you have the correct hardware and software to successfully complete the labs.

## Hardware Requirements ##
Silicon Labs Thunderboard BG22 Kit: SLTB010A
EFR32BG22 Soc
## Software Requirements ##
Simplicity Studio v5
Gecko SDK v3.0 with the Bluetooth stack installed
EFRConnect Mobile App
## Install Tools ##
Download and install Simplicity Studio 5 if it is not already installed.

## Connect your Hardware ##



# Lab #
## Creating the Project ##
1. If the BG22 TB has not been plugged in to PC using the USB cable (A-Micro), do so now. The kit and debug (board and target) information should be displayed in the Launcher->Debug Adapters window. Picture here!!!
2. In the Debug Adapters window, click on the device (board).
3. Information about the target hardware and software will appear in overview. If this does not appear, click on the Launcher button in the top right corner.
4. Select the Preferred SDK to the latest version. For this lab, the latest version of Gecko SDK (v3.1.1) is used.
5. Click on Create New Project in the upper right hand corner. A "New Project Wizard" window should appear.
6. For this lab, the Bluetooth - SoC Empty project will be used as the starter project. Scroll and select Bluetooth - SoC Empty. 
Note: to filter the projects, click on Bluetooth for the Technology Type. and empty for keywords.
7. Click Next to move on.
8. Rename the project. For this lab, name the project soc_spi_acc.
9. Select Copy contents to copy the project files into your project. This makes version control easier to manage and future updates to the Simplicity Studio libraries will not impact the copied files in this project.
10. check use default location (workspace)
11. Click Finish to generate the project.
12. the IDE perspective launchered automatically.
13. you could see gatt_configuration.btconf, soc_spi_acc.slcp and readme.
14. 

summary:
file included.
Check Installed Components, you will see:
Adanced Configurator
Bluethooth -> OTA -> AppLoader,
Stack, a lot.
Platform, 
services->NVM3
services->Device Initialization->Device Init, Clocks/DPLL/DC-DC, etc. 
services->Sleep Timer
bbb
## Installing the imu sensor components ##
14. Open (click) the soc_spi_acc.sclp file. The file will show information about the target hardware and software (in overview->project details).
15. Select the Software Components tab at the top.
16. Scroll down to the "Platform" section. Notice how there are many components available that you can install for your application with ease.
17. The list of EMLIB source files is available under "Peripherals". Install the following components using the Install button as shown in the image. The process is repeated for all 4 components.
- Platfrom-Board Driver->ICM20648 -> Motion Sensor
- Bluetooth->GATT->Inertial Measurement Unit GATT Service.
- LETIMER
- PRS
explaination:
### Platfrom-Board Driver->ICM20648 -> Motion Sensor ###
for the motion sensor component, you will see the file was added.
the file was generated automatically.
You can configure the pin now with the configure button.
### Bluetooth->GATT->Inertial Measurement Unit GATT Service. ###


# Adding a Custom BLE GATT Service and Characteristic #
The average data that the IADC sampled can be retrieved wirelessly through BLE. To make the data visible, a custom GATT service and characteristic are used.

Open the GATT configurator, which is located in _./config/btconf/gatt_configuration.btconf_. The GATT configurator GUI has been updated and is very different compared to SSv4.
For this lab, the Device name will be modified to "LE Voltage Monitor" located under the Generic Access characteristics. The Value length will have to be updated to 18.
Click on the left-most icon in the top left corner of the GATT configurator and select New Service.
Click on the new custom service and rename the service to "Voltage Monitor".
Add an ID to the custom service to give a meaningful ID reference to the service. For this lab, "voltage_monitor" is used for the ID.

Click on the left-most icon in the top left corner of the GATT configurator and select New Characteristic.
Click on the new custom characteristic. For this lab, rename the characteristic to be "Average Voltage Data".
Add an ID to the custom characteristic. For this lab, "avg_voltage_data" is used for the ID. This ID field will create a meaningful name for the GATT characteristic variable to use in code development. This variable can be found in gatt_db.h and the variable will be prefixed with gattdb.
Select USER for the Value settings. This will require the user to allocate their own resources for the GATT characteristic. For more information, see KBA.
Select Notify under Properties. The EFR32 device will notify connected devices of any GATT characteristic value changes.

# Adding the Project Source Files #
Copy le_voltage_monitor.c, le_voltage_monitor.h, and app.c source files to the top level of the project. The source files and code details are found at the Code Explanation section of this doc. App.c will overwrite the existing file to add the new application. The source files can be dragged and dropped into Simplicity Studio or placed in this file path:
# Build and Flash the Project #
Build the project by clicking on the hammer icon in the top left corner of the Simplicity Studio IDE.
Right-click on the hex file and select Flash to Device... to make the Flash Programmer window appear. Note: if a Device Selection window appears, select the correct device.
Click Program to flash the device.

# Usage #
Connecting with EFR Connect App


## Documentation ##

# Code Explanation #
## Creating the Project ##
## Documentation ##


# Source #
## sl_icm20648.c ##
C:\SiliconLabs\SimplicityStudio\v5\developer\sdks\gecko_sdk_suite\v3.1\hardware\driver\icm20648\src
- aa
- mm
## sl_icm20648_config.h ##
-- bbbb



## sl_imu_fuse.c ##
C:\SiliconLabs\SimplicityStudio\v5\developer\sdks\gecko_sdk_suite\v3.1\hardware\driver\imu\src
 ******************************************************************************/
void sl_imu_update(void)
{
  sl_imu_fuse_update(&fuseObj);
}

## sl_imu.c ##
C:\SiliconLabs\SimplicityStudio\v5\developer\sdks\gecko_sdk_suite\v3.1\hardware\driver\imu\src
void sl_imu_update(void)
{
  sl_imu_fuse_update(&fuseObj);
}


## sl_sensor_imu.c ##
C:\SiliconLabs\SimplicityStudio\v5\developer\sdks\gecko_sdk_suite\v3.1\app\bluetooth\common\sensor_imu
sl_status_t sl_sensor_imu_get(int16_t ovec[3], int16_t avec[3])

## app.c ##
static void sensor_init(void)
{

#if defined(SL_CATALOG_GATT_SERVICE_IMU_PRESENT) && defined(SL_CATALOG_SENSOR_IMU_PRESENT)
sl_status_t sl_gatt_service_imu_get(int16_t ovec[3], int16_t avec[3])
{
  return sl_sensor_imu_get(ovec, avec);
}

# BLE notification #
## sl_event_handler.c ##
C:\Users\delu\SimplicityStudio\v5_workspace\soc_thunderboard_brd4184b\autogen
void sl_internal_app_process_action(void)
{
  sl_gatt_service_aio_step();
  sl_gatt_service_imu_step();
  sl_sensor_sound_step();
}
## sl_gatt_service_imu.c ##
C:\SiliconLabs\SimplicityStudio\v5\developer\sdks\gecko_sdk_suite\v3.1\app\bluetooth\common\gatt_service_imu

void sl_gatt_service_imu_step(void)
{
  if (imu_state) {
    if (SL_STATUS_OK == sl_gatt_service_imu_get(imu_ovec, imu_avec)) {
      if (imu_acceleration_notification) {
        imu_acceleration_notify();
      }
      if (imu_orientation_notification) {
        imu_orientation_notify();
      }
    }
  }
}
aa
## sl_bt_api.h ##
C:\SiliconLabs\SimplicityStudio\v5\developer\sdks\gecko_sdk_suite\v3.1\protocol\bluetooth\inc
 ******************************************************************************/
sl_status_t sl_bt_gatt_server_send_notification(uint8_t connection,
                                                uint16_t characteristic,
                                                size_t value_len,
                                                const uint8_t* value);


## gatt_db.c ##

# Porting consideration #
## other driver ##
sensor with i2c
driver levels
Your own driver.

Note: Bootloader.
# Reference #
## peripheral examples ##
## platform application ##
## platform hardware driver ##


