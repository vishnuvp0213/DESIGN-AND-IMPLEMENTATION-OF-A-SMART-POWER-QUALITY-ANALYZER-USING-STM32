# Smart Power Analyzer with Harmonic Detection and Power Factor Correction

## Overview
This project presents a smart power monitoring system capable of measuring electrical parameters, detecting harmonics, and improving power factor in real time. The system is developed using an STM32 microcontroller and performs signal processing using FFT to analyze harmonic distortion in the power supply.

The system measures voltage and current signals from the load and calculates parameters such as RMS voltage, RMS current, active power, apparent power, power factor, and total harmonic distortion (THD). The measured values are displayed on an OLED display and can also be transmitted for remote monitoring using an ESP8266 module.

The project also includes a power factor correction mechanism that automatically switches capacitor banks when a low power factor condition is detected.

---
<img width="638" height="879" alt="Image" src="https://github.com/user-attachments/assets/6d2247f7-2e07-4eb9-a0a8-678569b69417" />

## Features
- Real-time measurement of voltage and current
- Calculation of electrical parameters:
  - RMS Voltage
  - RMS Current
  - Active Power
  - Apparent Power
  - Power Factor
- Harmonic analysis using FFT
- THD calculation for voltage and current
- OLED display for real-time monitoring
- IoT monitoring using ESP8266
- Automatic power factor correction using capacitor banks
- Harmonic detection with visual LED indication

---

## Hardware Components
- STM32 Microcontroller
- ACS712 Current Sensor
- Voltage sensing circuit
- ESP8266 WiFi Module
- 0.96 inch OLED Display (I2C)
- Relay module
- Capacitor banks
- Inductor ballast
- Incandescent bulb
- Passive harmonic filters
  - C-Type filter
  - Second-order high-pass filter
- Indicator LEDs
- Push buttons
- Power supply module

---

## System Working
1. Voltage and current signals are sensed from the load.
2. The STM32 microcontroller samples the signals using ADC.
3. RMS values and power parameters are calculated.
4. FFT is applied to determine harmonic components.
5. THD is calculated for voltage and current.
6. Results are displayed on the OLED display.
7. Data is transmitted through ESP8266 for IoT monitoring.
8. If the power factor drops below the threshold, the controller activates the relay to connect capacitor banks.

---

## Experimental Validation

### Load Used
A laptop charger was used as a nonlinear load for testing harmonic distortion and power factor behavior.

### Parameter Comparison

| Parameter | Power Analyzer | Proposed System |
|----------|---------------|----------------|
| Voltage THD | 1.6% | 1.7% |
| Current THD | 174.3% | 119.2% |
| Power Factor | 0.45 | 0.48 |

The measured values from the proposed system closely match the readings from the commercial power analyzer.

---

## Power Factor Correction Test
An RL load was created by connecting an incandescent bulb in series with an inductor ballast.

Before correction:
- Power factor ≈ 0.519

After capacitor bank switching:
- Power factor ≈ 0.830

The slight deviation from the expected value (~0.9) is due to sensor accuracy and measurement limitations.






## Calibration Procedure

To obtain accurate voltage and current measurements, sensor calibration must be performed before running the main program. The calibration codes are provided in the **calibration** folder of this repository.

Repository Structure

calibration/
- acs712_midpoint_calibration.ino
- acs712_irms_calculation.ino
- zmpt_voltage_calibration.ino

main_code/
- stm32_power_analyzer.ino
- esp8266_iot_monitoring.ino


Current Sensor Calibration (ACS712)

Two calibration programs are provided to correctly measure current using the ACS712 sensor.

Step 1 – Find ADC Midpoint

Upload the code:

acs712_midpoint_calibration.ino

Purpose:
This code determines the ADC midpoint value of the ACS712 sensor. The midpoint represents the sensor output when no current is flowing through the sensor.

Procedure:
1. Connect the ACS712 sensor to the STM32.
2. Ensure no load current is flowing through the sensor.
3. Upload the midpoint calibration code.
4. Open the Serial Monitor.
5. Note the midpoint ADC value printed in the Serial Monitor.

This midpoint value will be used as the current offset in the next step.


Step 2 – Calculate RMS Current

Upload the code:

acs712_irms_calculation.ino

Purpose:
This code calculates the RMS current using the midpoint value obtained in Step 1.

Procedure:
1. Insert the midpoint value obtained from Step 1 into the code.
2. Upload the program to the STM32.
3. Connect a load to the sensor.
4. Observe the current value printed in the Serial Monitor.
5. Compare it with a multimeter or clamp meter and adjust the sensitivity value if necessary.


Voltage Sensor Calibration (ZMPT101B)

Voltage calibration is performed using the following code:

zmpt_voltage_calibration.ino

Purpose:
This code allows adjustment of the voltage calibration constant to match the actual supply voltage.

Procedure:
1. Upload the voltage calibration code to the STM32.
2. Measure the actual AC voltage using a multimeter.
3. Observe the voltage value printed in the Serial Monitor.
4. Adjust the voltage calibration constant in the code until the measured value matches the multimeter reading.


Running the Main System

After completing the calibration process, upload the main project codes.

STM32 Main Code:
main_code/stm32_power_analyzer.ino

ESP8266 IoT Communication Code:
main_code/esp8266_iot_monitoring.ino

Once uploaded, the system will perform real-time monitoring including voltage and current measurement, power parameter calculation, harmonic analysis using FFT, THD calculation, OLED display monitoring, and IoT data transmission through ESP8266.




Team Members
• Keerthana C (NSS22EE07)
• Nandana Narayanan (PKD22EE038)
• T. B. Vishnu Prasad (NSS22EE124)
• V. Anand (NSS22EE128)

Department of Electrical and Electronics Engineering
Dr. A. P. J. Abdul Kalam Technological University
Palakkad, India
