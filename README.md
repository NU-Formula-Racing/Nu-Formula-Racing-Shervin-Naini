Strain-Gauge & Airspeed Printed Circuit Board Firmware:

Hello! Thanks for stopping by, below are some of the skills I learned and applied this year for Northwestern Formula.

1. Strain Gauge Integration & Signal Conditioning
Developed the firmware logic to interface with high-resolution ADCs to monitor chassis and suspension loading in real-time.

Precision Sampling: Implemented I^2C communication with the onboard ADCs, utilizing hardware interrupts to ensure consistent sampling rates!!

Calibration Routine: Integrated a zero-offset calibration function triggered during pre-run sequences to account for ambient thermal drift.

2. Pitot Tube & Airspeed Processing
Engineered the driver for the differential pressure sensor used in the vehicle's Pitot-static system.

Dynamic Pressure Calculation: Implemented the Bernoulli-based conversion logic to translate raw voltage/pressure differentials into knots and m/s.

Altitude Compensation: Integrated ambient temperature and atmospheric pressure variables to maintain airspeed accuracy across varying track conditions.

3. CAN Bus Architecture
Data Packaging: Designed the CAN frame structure to broadcast strain and airspeed telemetry across the vehicle network.

Priority Management: Optimized message IDs to ensure critical aerodynamic and structural data maintain high bus priority during high-bandwidth operation.

Logging: Synchronized sensor timestamps with the central logger to allow for post-run correlation between vehicle speed and suspension travel.

Technical Stack
Languages: C, C++ (Embedded)

Protocols: CAN, I2C

Hardware: Microcontrollers (ESP32), Differential Pressure Sensors, 

Hardware Skills: PCB Design (Altium Designer)


