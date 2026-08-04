# Strain-Gauge & Airspeed PCB Firmware
Firmware for Northwestern Formula Racing’s strain-gauge and airspeed sensing boards — real-time chassis/suspension load monitoring and Pitot-static airspeed over CAN.
## Overview
This project covers embedded firmware for printed circuit boards that:
- Read high-resolution strain-gauge ADCs for chassis and suspension loading
- Drive a differential pressure (Pitot) sensor for vehicle airspeed
- Broadcast calibrated telemetry on the vehicle CAN bus for logging and analysis
Built for Northwestern Formula Racing (FSAE).
## Features
### Strain Gauge Integration & Signal Conditioning
- Firmware interface to high-resolution ADCs for real-time chassis and suspension load monitoring
- I²C communication with onboard ADCs, using hardware interrupts for consistent sampling rates
- Zero-offset calibration routine for pre-run sequences to correct ambient thermal drift
### Pitot Tube & Airspeed Processing
- Driver for the differential pressure sensor in the Pitot-static system
- Bernoulli-based conversion from raw pressure differentials to knots and m/s
- Altitude compensation using ambient temperature and atmospheric pressure for track conditions
### CAN Bus Architecture
- CAN frame design for broadcasting strain and airspeed telemetry on the vehicle network
- Message ID prioritization so critical aero/structural data stays high-priority under load
- Timestamp sync with the central logger for post-run correlation (e.g. speed vs. suspension travel)
## Technical Stack
| Area | Tools / Tech |
|------|----------------|
| Languages | C, C++ (embedded) |
| Protocols | CAN, I²C |
| Hardware | ESP32, differential pressure sensors, strain-gauge ADCs |
| Design | PCB design in Altium Designer |
## Skills Applied
- Embedded firmware (C/C++)
- ADC sampling & interrupt-driven I²C
- Sensor calibration & signal conditioning
- Aerodynamic airspeed computation
- CAN messaging & vehicle telemetry
- Altium PCB design
