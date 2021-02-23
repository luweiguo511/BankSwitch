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

# Quickly Add an Accelerometer with SPI
## Overview
For IOT (Internet of Things) solution, it often uses accelerometer sensor like IMU (Inertial Measurement Unit). The [EFR32BG22 Thunderboard](https://www.silabs.com/development-tools/thunderboard/thunderboard-bg22-kit) (kit SLTB010A) has an onboard 6-axis [ICM-20648](https://invensense.tdk.com/products/motion-tracking/6-axis/icm-20648/) sensor from vendor TDK InvenSense. 

This lab shows how to add this accelerometer sensor quickly. 

**Topic Covered**
- Accelerometer (Inertial Measurement Unit) sensor
- Software component
- EFR connect app. 

## Getting Started
Review the following materials before starting this lab. Ensure that you have the correct hardware and software prepared to successfully complete the lab.

### Hardware Requirements
Silicon Labs BG22 Thunderboard Kit: [SLTB010A](https://www.silabs.com/development-tools/thunderboard/thunderboard-bg22-kit)

Which included:
-	[EFR32BG22C224F512IM40](https://www.silabs.com/wireless/bluetooth/efr32bg22-series-2-socs) Soc
-	6-axis IMU (Inertial Measurement Unit): TDK InvenSense [ICM-20648](https://invensense.tdk.com/products/motion-tracking/6-axis/icm-20648/) with SPI interface
### Software Requirements
- [Simplicity Studio v5](https://www.silabs.com/products/development-tools/software/simplicity-studio)
- Gecko SDK v3.1 (GSDK) or above with the Bluetooth Stack (v3.1.1) installed
- EFR Connect Mobile App
   -	If you have problem to access Google Play in china mainland, try link [here](https://github.com/SiliconLabs/EFRConnect-android)
   -	If you have problem to access Apple store or don’t have an account, try link [here](https://github.com/SiliconLabs/EFRConnect-ios)

### Install Tools
Download and install [Simplicity Studio v5](https://www.silabs.com/products/development-tools/software/simplicity-studio) if it is not already installed. Be sure to update to have GSDK 3.1.x and Bluetooth Stack installed.



### Connect your Hardware
Attach the BG Thunderboard kit to the PC with Simplicity Studio installed by using a USB cable (not a charging cable). Connecting between the PC host USB port to the J-link USB port (micro) on the kit.

<img src="https://docs.silabs.com/resources/bluetooth/lab-manuals/getting-started-with-bluetooth-in-simplicity-studio-v5/images/1.3connectyourhardware.png" title="Silicon Labs Gecko and Wireless Gecko MCUs" alt="EFM32 32-bit Microcontrollers" width="250"/>

## Hardware Introduction
Refer to [this page](https://www.silabs.com/documents/public/schematic-files/BRD4184A-A01-schematic.pdf) for detailed hardware information (Schematic for BG22 Thunderboard in pdf format).




### Connection between IMU sensor and EFR32BG22


Pins used to connect between the EFR32BG22 and IMU:
- SPI interface:
  -  SPI_MOSI (PC00)
  -  SPI_MISO (PC01)
  -  SPI_SCLK (PC02)
  -  SPI_CS (PB02)
- IMU_ENABLE (PB04)
- IMU_INT (PB03)


## Lab
### Creating the Project (based on SOC empty)
1. If the BG22 Thunderboard has not been plugged into PC using the USB cable (micro type), do so now. The kit and debug information (board and target) should be displayed in the Launcher->Debug Adapters window. Picture here!!!
2. In the "Debug Adapters window", click on the device (board).
3. Information about the target hardware and software will appear in Launcher -> Overview tab (together with the Adapter FW and Secure FW version). If this does not appear, click on the Launcher button in the top right corner.
4. Select the "Preferred SDK" to the latest version. For this lab, the latest version of "Gecko SDK Suite" v3.1.1 is used.
5. Click on "Create New Project" in the upper right hand corner. A "New Project Wizard" window should appear.
6. For this lab, the Bluetooth -> SoC Empty project will be used as the starter project. Scroll and select Bluetooth -> SoC Empty. 
Note: to filter the projects, click on Bluetooth for the "Technology Type" and empty for "keywords".
7. Click Next to move on.
8. Rename the project under "Project name". For this lab, name the project soc_spi_acc.
9. Select (check) "Copy contents" under "With Project files" to copy the project files into your project. This makes version control easier to manage and future updates to the Simplicity Studio libraries will not impact the copied files in this project.
10. Check "Use default location" (workspace).
11. Click Finish to generate the project.
12. The IDE perspective launchered automatically.
13. You could see gatt_configuration.btconf, soc_spi_acc.slcp and readme showed up.

#### Recap of this step:
In fact, the SOC Empty project will install some software components. You could check what has installed via checking the "Installed Components" under "Software Components", you will see component like below were installed:
- Advanced Configurator -> Bluetooth GATT Configurator
- Bluethooth -> OTA -> AppLoader,
- Platform -> services->Sleep Timer
- etc.



### Installing the imu sensor components
14. Open (click) the soc_spi_acc.sclp file. The Overview will show information about the target hardware and software.
Note: Target and SDK Selection, Ensure the Board should be thunderboard EFR32BG22.
15. Select the Software Components tab at the top.
16. Scroll down to the "Platform" section. Notice how there are many components available that you can install for your application with ease.
17. Install the following components using the Install button as shown in the image. The process is repeated for all components needed to add.
- Services -> IO stream ->IO Stream: USART (dependent).
- Platform -> Board Driver -> IMU - Inertial Measurement Unit
- Bluetooth -> GATT -> Inertial Measurement Unit GATT Service.
- Bluetooth -> Sensor -> Inertial Measurement Unit Sensor.

#### Recap of this step (explanation):
##### Motion Sensor
After you add/install the motion sensor component, you will see somes files was added.

##### Inertial Measurement Unit GATT Service.
After you add/install the Inertial Measurement Unit GATT Service, you will see somes other files was added.
In file sl_event_handler, you could see the API was added into the routine sl_internal_app_process_action.
void sl_internal_app_process_action(void)
{
  sl_gatt_service_imu_step();
}
If you open the config->btconf->gatt_configuration.btcon gatt configure file, you could see the Acceleration and Orientation was added.

### Adding the Project Source Files
Copy app.c source file to the top level of the project. The source files (automatically added included) and code details are found at the Code Explanation section of this doc. App.c will overwrite the existing file to add the new application. The source files can be dragged and dropped into Simplicity Studio or placed in this file path.
C:\Users\user_acount\SimplicityStudio\v5_workshop\soc_spi_acc
Where user_acount is the default workspace and SS installation path.
You can also edit the app.c file manually if you prefer to this way.
#### Recap of this step (explanation):
```
static void sensor_init(void)
{
  sl_sensor_imu_init();
  sl_sensor_imu_enable(true);
}
sl_status_t sl_gatt_service_imu_get(int16_t ovec[3], int16_t avec[3])
{
  return sl_sensor_imu_get(ovec, avec);
}
Some change was made in the app.c file. 
    // -------------------------------
    // This event indicates that a new connection was opened.
    case sl_bt_evt_connection_opened_id:
      sensor_init();
      break;
    // -------------------------------
    // This event indicates that a connection was closed.
    case sl_bt_evt_connection_closed_id:
      // Restart advertising after client has disconnected.
      sc = sl_bt_advertiser_start(
        advertising_set_handle,
        advertiser_general_discoverable,
        advertiser_connectable_scannable);
      sl_app_assert(sc == SL_STATUS_OK,
                    "[E: 0x%04x] Failed to start advertising\n",
                    (int)sc);
        sl_sensor_imu_deinit();      
      break;      
```
### Build and Flash the Project
Build the project by clicking on the hammer icon in the top left corner of the Simplicity Studio IDE perspective.
Right-click on the hex file and select Flash to Device... to make the Flash Programmer window appear. 
Note: if a Device Selection window appears, select the correct device.
Click Program to flash the device.

## Usage
### Connecting with EFR Connect App
With the EFR Connect App, connect to the device and view the sensor data that is sent from the EFR32BG22 device (via notification).
Click the notify button, you should see the sensor data get updated regularly.
You could move the orientation of the Thunderboard to see this change.

## Code Explanation
The following sections explain critical lines of code pertinent to this lab. The code can be found in different files (driver).
### Accelerometer (icm20648) Driver
#### sl_icm20648_config.h
This is a header file generated automatically by the Simplicity Studio pintool/software component. You may need to change the pin map based on your hardware.
Use the software components->Platform->Board drivers->ICM20648->Configure to change this.
picture here:

#### sl_icm20648.c
C:\SiliconLabs\SimplicityStudio\v5\developer\sdks\gecko_sdk_suite\v3.1\hardware\driver\icm20648\src
This is the driver file for ICM20648 prepared by Silabs. If you use sensor from aother vendor, you may need to consider to implement the similar driver for it.
Please consider to contact with the vendor of the sensor you use to get help on how implementing the driver.




#### sl_imu_fuse.c/ sl_imu.c/ sl_sensor_imu.c
These are re-pack of the API provided in sl_icm20648.c. The high level code (app.c) call API like sl_sensor_imu_init, sl_sensor_imu_get and others provided in these files to initialize and enable/disable the imu sensor. These files are in folder like below:
C:\SiliconLabs\SimplicityStudio\v5\developer\sdks\gecko_sdk_suite\v3.1\hardware\driver\imu\src
C:\SiliconLabs\SimplicityStudio\v5\developer\sdks\gecko_sdk_suite\v3.1\app\bluetooth\common\sensor_imu


### Application (app.c)

The SoC-Empty project generates a default app.c source file with a skeleton Bluetooth event handler. The app.c file provided for this lab adds code to handle the BLE connection and notifications.
#### Connection Opened
The imu sensor is initialized and enabled when event sl_bt_evt_connection_opened_id received. The imu sampling does not start sampling until a connection has been made and the user has enabled GATT notifications acceleration (or orientation) characteristics. 
```
static void sensor_init(void)
{
  sl_sensor_imu_init();
  sl_sensor_imu_enable(true);
}
    // -------------------------------
    // This event indicates that a new connection was opened.
    case sl_bt_evt_connection_opened_id:
      sensor_init();
      break;
      
```

#### Connection Closed
When the connection is closed, the sl_bt_evt_connection_closed_id event is triggered, to save power when no devices are connected the sensor was disabled via sensor_deinit() function.

    ```cpp
    // -------------------------------
    // This event indicates that a connection was closed.
    case sl_bt_evt_connection_closed_id:
      // Restart advertising after client has disconnected.
      sc = sl_bt_advertiser_start(
        advertising_set_handle,
        advertiser_general_discoverable,
        advertiser_connectable_scannable);
      sl_app_assert(sc == SL_STATUS_OK,
                    "[E: 0x%04x] Failed to start advertising\n",
                    (int)sc);
      break;

    ```
### BLE notification
Once the user has enabled GATT notifications to the characteristic, the sl_bt_evt_gatt_server_characteristic_status_id event is triggered. In this event, the device will periodically update the characteristic value until the device disconnects. 

#### sl_event_handler.c
C:\Users\delu\SimplicityStudio\v5_workspace\soc_thunderboard_brd4184b\autogen


    ```cpp
    void sl_internal_app_process_action(void)
    {
      sl_sensor_sound_step();
    }
    ```
#### sl_gatt_service_imu.c
C:\SiliconLabs\SimplicityStudio\v5\developer\sdks\gecko_sdk_suite\v3.1\app\bluetooth\common\gatt_service_imu
```
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
```

## Porting consideration
### Other Drivers
BG22 Thunderboard also integrated other sensors:
- Silabs Relative humidity & temperature sensor: I2C [Si7021](https://www.silabs.com/sensors/humidity/si7006-13-20-21-34)
- Silabs UV and ambient light sensor: I2C [Si1133](https://www.silabs.com/sensors/optical/si1133)
- Silabs Hall effect sensor: I2C [Si7210](https://www.silabs.com/sensors/magnetic/si7210)

Note: The SOC Empty project don't have the bootloader, be sure to program the bootloader to the device first. In some cases, the bootloader may be missing from the device if it has been completely erased. If that happens:
-  options:
    -  open the Flash Programmer and program the bootloader found here:
C:\SiliconLabs\SimplicityStudio_v5\developer\sdks\gecko_sdk_suite\v3.1\platform\bootloader\sample-apps\bootloader-storage-internal-single-512k\efr32mg22c224f512im40-brd4182a\bootloader-storage-internal-single-512k.s37
    -  flash the demo example first, then flash the applicatin got here.


Note: The SOC Empty project don't have the bootloader, be sure to program the bootloader to the device first.

## Reference
[Peripheral examples](https://github.com/SiliconLabs/peripheral_examples)

[GSDK document](https://docs.silabs.com/gecko-platform/latest/)

[SS v5 user guide](https://docs.silabs.com/simplicity-studio-5-users-guide/latest/ss-5-users-guide-overview/)



