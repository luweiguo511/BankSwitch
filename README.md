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
## Overview ##
For IOT (Internet of Things) solution, it often uses accelerometer sensor like IMU (Inertial Measurement Unit). The EFR32BG22 Thunderboard (kit SLTB010A) has an onboard 6-axis ICM20648 sensor from vendor TDK InvenSense. 

https://www.silabs.com/development-tools/thunderboard/thunderboard-bg22-kit

https://invensense.tdk.com/products/motion-tracking/6-axis/icm-20648/

This lab shows how to add an Accelerometer sensor (like IMU) quickly. 

#### Topic Covered ####
- Accelerometer (Inertial Measurement Unit) sensor
- Software component
- EFR connect app. 

## Getting Started ##
Review the following material before starting this lab. Ensure that you have the correct hardware and software prepared to successfully complete the lab.

### Hardware Requirements ###
Silicon Labs BG22 Thunderboard Kit: SLTB010A

Which included:
-	EFR32BG22C224F512IM40 Soc
-	6-axis IMU (Inertial Measurement Unit): TDK InvenSense ICM-20648 with SPI interface
### Software Requirements ###
- Simplicity Studio v5
- Gecko SDK v3.1 (GSDK) or obove with the Bluetooth Stack (v3.1.1) installed
- EFRConnect Mobile App
-	•	If you have problem to access Google Play in china mainland, try link here
-	•	If you have problem to access Apple store or don’t have an account, try link here.

### Install Tools ###
Download and install Simplicity Studio v5 if it is not already installed. Be sure to update to have GSDK 3.1.x and Bluetooth Stack installed.

https://www.silabs.com/products/development-tools/software/simplicity-studio

### Connect your Hardware ###
Attach the BG Thunderboard kit to the PC with Simplicity Studio installed by using a USB cable (not a charging cable) and connecting between the PC host USB port to the J-link USB port (micro) on the kit.
picture here.

## Hardware introduction ##
Refer to this page for detailed hardware information (Schematic for BG22 Thunderboard in pdf format):

https://www.silabs.com/documents/public/schematic-files/BRD4184A-A01-schematic.pdf


### Connection between IMU sensor and EFR32BG22 ###
picture uploaded here:

Pins used to connect between the EFR32BG22 and IMU:
- SPI interface:
- 	•	SPI_MOSI (PC00)
- 	•	SPI_MISO (PC01)
- 	•	SPI_SCLK (PC02)
- 	•	SPI_CS (PB02)
- IMU_ENABLE (PB04)
- IMU_INT (PB03)


## Lab ##
### Creating the Project (based on SOC empty) ###
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

#### Recap of this step: ####
In fact the SOC Empty project will install some software compnents. You could check the "Installed Components" under "Software Components", you will see component like below were installed:
- Adanced Configurator -> Bluetooth GATT Configurator
- Bluethooth -> OTA -> AppLoader,
- Platform -> services->Sleep Timer
- etc.



### Installing the imu sensor components ###
14. Open (click) the soc_spi_acc.sclp file. The Overview will show information about the target hardware and software.
15. Select the Software Components tab at the top.
16. Scroll down to the "Platform" section. Notice how there are many components available that you can install for your application with ease.
17. Install the following components using the Install button as shown in the image. The process is repeated for all components needed to add.
- IO stream (dependent).
- Platfrom-Board Driver -> ICM20648 -> Motion Sensor
- Bluetooth -> GATT -> Inertial Measurement Unit GATT Service.
- Bluetooth -> Sensor -> Inertial Measurement Unit GATT Service.
- Bluetooth -> Sensor -> Inertial Measurement Unit GATT Service.

#### Recap of this step (explaination): ####
##### Platfrom-Board Driver -> ICM20648 -> Motion Sensor #####
for the motion sensor component, you will see the file was added.
the file was generated automatically.
You can configure the pin now with the configure button.
##### Bluetooth -> GATT -> Inertial Measurement Unit GATT Service. #####


### Adding a Custom BLE GATT Service and Characteristic ###
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

void sl_internal_app_process_action(void)
{
  sl_gatt_service_imu_step();
}

### Adding the Project Source Files ###
Copy app.c source file to the top level of the project. The source files (autommatically added included) and code details are found at the Code Explanation section of this doc. App.c will overwrite the existing file to add the new application. The source files can be dragged and dropped into Simplicity Studio or placed in this file path:

#### Recap of this step (explaination): ####

### Build and Flash the Project ###
Build the project by clicking on the hammer icon in the top left corner of the Simplicity Studio IDE perspectibe.
Right-click on the hex file and select Flash to Device... to make the Flash Programmer window appear. 
Note: if a Device Selection window appears, select the correct device.
Click Program to flash the device.

## Usage ##
### Connecting with EFR Connect App ###
With the EFR Connect App, connect to the device and view the sensor data that is sent from the EFR32BG22 device (via notification).
Click the notify button, you should see the sensor data get updated regularly.
You could move the oritention of the Thunderboard to see this change.

### Recap ###

## Code Explanation ##
The following sections explain critical lines of code pertinent to this lab. The code can be found in different files (driver).
### Accelerometer (icm20648) Driver ###
#### sl_icm20648_config.h ####
This is a header file generated automatically bu the Simplicity Studio pintool/software component. You may need to change the pin map based on your hardware.
Use the software components->Platform->Board drivers->ICM20648->Configure to change this.
picture here:

#### sl_icm20648.c ####
C:\SiliconLabs\SimplicityStudio\v5\developer\sdks\gecko_sdk_suite\v3.1\hardware\driver\icm20648\src
This is the driver file for ICM20648 prepared by Silabs. If you use sensor from other vendor, you may need to consider to implement the similar driver for it.
Please consider to contact with the vendor of the sensor you use to get help on how to implement the driver.




#### sl_imu_fuse.c ####
C:\SiliconLabs\SimplicityStudio\v5\developer\sdks\gecko_sdk_suite\v3.1\hardware\driver\imu\src

void sl_imu_fuse_update(sl_imu_sensor_fusion_t *f)
{
  uint8_t imu_state = sl_imu_get_state();
  if ( imu_state != IMU_STATE_READY ) {
    return;
  }

  /* Get accelerometer data and update Fuse filter */
  sl_imu_get_acceleration_raw_data(f->aVector);
  sl_imu_fuse_accelerometer_update_filter(f, f->aVector);

  /* Get gyro data and update fuse */
  sl_imu_get_gyro_raw_data(f->gVector);
  f->gVector[0] = -f->gVector[0];
  f->gVector[1] = -f->gVector[1];
  sl_imu_fuse_gyro_update(f, f->gVector);

  /* Perform fusion to compensate for gyro drift */
  sl_imu_fuse_gyro_calculate_correction_vector(f, true, false, 0);
}

#### sl_imu.c ####
C:\SiliconLabs\SimplicityStudio\v5\developer\sdks\gecko_sdk_suite\v3.1\hardware\driver\imu\src

void sl_imu_update(void)
{
  sl_imu_fuse_update(&fuseObj);
}
void sl_imu_get_orientation(int16_t ovec[3])
{
  ovec[0] = (int16_t) (100.0f * IMU_RAD_TO_DEG_FACTOR * fuseObj.orientation[0]);
  ovec[1] = (int16_t) (100.0f * IMU_RAD_TO_DEG_FACTOR * fuseObj.orientation[1]);
  ovec[2] = (int16_t) (100.0f * IMU_RAD_TO_DEG_FACTOR * fuseObj.orientation[2]);
}

#### sl_sensor_imu.c ####
C:\SiliconLabs\SimplicityStudio\v5\developer\sdks\gecko_sdk_suite\v3.1\app\bluetooth\common\sensor_imu

sl_status_t sl_sensor_imu_get(int16_t ovec[3], int16_t avec[3])
{
  sl_status_t sc = SL_STATUS_NOT_READY;
  if (sl_imu_is_data_ready()) {
    sl_imu_update();
    sl_imu_get_orientation(ovec);
    sl_imu_get_acceleration(avec);
    sc = SL_STATUS_OK;
  }
  return sc;
}


### Application (app.c) ###

The SoC-Empty project generates a default app.c source file with a skeleton Bluetooth event handler. The app.c file provided for this lab adds code to handle the BLE connection and notifications.
#### Connection Opened ####
The imu sensor is initialized in app_init() in line 35 of app.c. The voltage monitor IADC does not start sampling until a connection has been made and the user has enabled GATT notifications to the Average Volage Data characteristic.
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
      

#### Notifications Enabled ####
#if defined(SL_CATALOG_GATT_SERVICE_IMU_PRESENT) && defined(SL_CATALOG_SENSOR_IMU_PRESENT)
sl_status_t sl_gatt_service_imu_get(int16_t ovec[3], int16_t avec[3])
{
  return sl_sensor_imu_get(ovec, avec);
}

#### Connection Closed ####
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


### BLE notification ###
#### sl_event_handler.c ####
C:\Users\delu\SimplicityStudio\v5_workspace\soc_thunderboard_brd4184b\autogen
void sl_internal_app_process_action(void)
{
  sl_sensor_sound_step();
}
#### sl_gatt_service_imu.c ####
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


## Porting consideration ##
### other driver ###
BG22 Thunderboard also integrated other sensors:
- Silabs Relative humidity & temperature sensor: I2C Si7021
- Silabs UV and ambient light sensor: I2C Si1133
- Silabs Hall effect sensor: I2C Si7210

sensor with i2c
driver levels
Your own driver.

Note: The SOC Empty project don't have the bootloader, be sure to program the bootloader to the device first.

## Reference ##
### Peripheral examples ###

https://github.com/SiliconLabs/peripheral_examples

### GSDK document ###

https://docs.silabs.com/gecko-platform/latest/

### SS v5 user guide ###
https://docs.silabs.com/simplicity-studio-5-users-guide/latest/ss-5-users-guide-overview/



