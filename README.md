# DESIGN-AND-IMPLEMENTATION-OF-A-SMART-POWER-QUALITY-ANALYZER-USING-STM32
Smart Power Analyzer with Harmonic Detection and Power Factor Correction
Overview

This project presents a smart power monitoring system capable of measuring electrical parameters, detecting harmonics, and improving power factor in real time. The system is developed using an STM32 microcontroller and performs signal processing using FFT to analyze harmonic distortion in the power supply.

The system measures voltage and current signals from the load and calculates parameters such as RMS voltage, RMS current, active power, apparent power, power factor, and total harmonic distortion (THD). The measured values are displayed on an OLED display and can also be transmitted for remote monitoring using an ESP8266 module.

The project also includes a power factor correction mechanism that automatically switches capacitor banks when a low power factor condition is detected.

Features

Real-time measurement of voltage and current

Calculation of electrical parameters:

RMS Voltage

RMS Current

Active Power

Apparent Power

Power Factor

Harmonic analysis using FFT

THD calculation for voltage and current

OLED display for real-time monitoring

IoT monitoring using ESP8266

Automatic power factor correction using capacitor banks

Harmonic detection with visual LED indication

Hardware Components

STM32 Microcontroller

ACS712 Current Sensor

Voltage sensing circuit

ESP8266 WiFi Module

0.96 inch OLED Display (I2C)

Relay module

Capacitor banks

Inductor ballast

Incandescent bulb

Passive harmonic filters

C-Type filter

Second-order high-pass filter

Indicator LEDs

Push buttons

Power supply module

System Working

Voltage and current signals are sensed from the load.

The STM32 microcontroller samples the signals using ADC.

RMS values and power parameters are calculated.

FFT is applied to determine harmonic components.

THD is calculated for voltage and current.

Results are displayed on the OLED display.

Data is transmitted through ESP8266 for IoT monitoring.

If the power factor drops below the threshold, the controller activates the relay to connect capacitor banks.

Experimental Validation
Load Used

A laptop charger was used as a nonlinear load for testing harmonic distortion and power factor behavior.

Parameter Comparison
Parameter	Power Analyzer	Proposed System
Voltage THD	1.6%	1.7%
Current THD	174.3%	119.2%
Power Factor	0.45	0.48

The measured values from the proposed system closely match the readings from the commercial power analyzer.

Power Factor Correction Test

An RL load was created by connecting an incandescent bulb in series with an inductor ballast.

Before correction:
Power factor ≈ 0.519

After capacitor bank switching:
Power factor ≈ 0.830

The slight deviation from the expected value (~0.9) is due to sensor accuracy and measurement limitations.
