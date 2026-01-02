# DOST-BULSU FUTURE-LAB IoT Trainer Board
## Project Description
FUTURE-LAB (Fault-Tolerant and User-Friendly Trainer Board for Upcoming Research and Engineering Education Lab Kit Integrating Emerging Technologies) is a DOST CRADLE funded research and development project. It is an integrated electronics laboratory trainer board engineered for both academic training and professional development. This board simulates a wide range of hands-on learning, prototype development, and experimentation with emerging technologies in engineering education and research, incorporating critical fault-tolerance mechanisms. It is ideal for learning how to design resilient and reliable smart systems.

Its primary purpose is to:
* Serve as a modular, fault-tolerant platform for exploring embedded systems, IoT, AI, and smart technologies.
* Equip students, educators, and researchers with a user-friendly training environment for real-world applications and interdisciplinary learning.
* Provide a versatile and scalable system that supports classroom instruction, capstone projects, R&D, and technology deployment.
* Demonstrate innovation in areas such as smart agriculture, smart cities, environmental sensing, wireless communication, and edge computing.

| ![1.png]([https://github.com/TronixLab/DOST-BULSU-FUTURE-LAB-IoT-Trainer-Board/blob/main/media/1.png](https://github.com/TronixLab/DOST-BULSU-FUTURE-LAB-IoT-Trainer-Board/blob/main/media/FUTURE-LAB%20BOARD.png)) | 
|:--:| 
| *FUTURE-LAB IoT Trainer Board* |

### Board Components
**I. Core Development Board**

FUTURE-LAB is built around the LILYGO TTGO LoRa32, a compact yet powerful development board based on the ESP32 microcontroller, which integrates key wireless communication features and embedded peripherals for rapid Internet of Things (IoT) prototyping and education.
| ![2.png](https://github.com/TronixLab/DOST-BULSU-FUTURE-LAB-IoT-Trainer-Board/blob/main/media/2.png?raw=true) | 
|:--:| 
| *LILYGO TTGO LoRa32 V2.1_6.1 Wi-Fi + Bluetooth LoRa Board* |

**II. Board Peripherals**

The trainer board expands the capabilities of the core module through dedicated, accessible subsystems.
| ![2.png](https://github.com/TronixLab/DOST-BULSU-FUTURE-LAB-IoT-Trainer-Board/blob/main/media/4.png?raw=true) | 
|:--:| 
| *FUTURE-LAB Trainer Board Peripherals Section* |

1. **Power Supply Section**: Stable power regulation and distribution with onboard protection. It is designed with both flexibility and safety in mind, incorporating e-Fuse technology to intelligently manage multiple power sources.
Key Features:
* Dual Power Source Support: Accepts input either from a regulated laboratory bench power supply or a standard AC/DC wall adapter.
* e-Fuse Protection Technology: Acts as a smart gatekeeper for power delivery, offering Reverse polarity protection, Overvoltage and undervoltage lockout, Short-circuit current limiting, Thermal shutdown, and fault detection.
2. **General-Purpose Input/Output (GPIO) Section**: Breakout pins for digital I/O, ready for jumper wire or module connections with onboard protection.
Key Features:
* ESD Protection Circuitry: Each GPIO line is integrated with electrostatic discharge (ESD) protection, shielding the ESP32 microcontroller from voltage spikes caused by electrostatic discharge, signal incompatibility between 3.3V logic of the MCU and 5V peripherals, and overvoltage conditions from miswiring.
* Flexible Connectivity: Clearly labeled pin headers for digital I/O and support standard interfaces such as UART, I2C, SPI, and PWM signals.
3. **LED Indicator Section**: Multiple programmable sets of visual output modules for learning, debugging, and developing control logic through intuitive lighting systems.
* **LED Array**: A series of discrete LEDs connected to GPIOs for binary output, status indication, or logic testing.
* **Traffic Light**: Pre-built Red-Orange-Green LEDs for simulating traffic control systems and automation sequences.
* **RGB LED**: A standard common-cathode RGB LED that allows color mixing through PWM control.
* **Addressable RGB LED (WS2812)**: A single-wire, daisy-chainable LED supporting full-color 24-bit control via NeoPixel or similar libraries.
* **7-Segment Display**: A 1-digit numeric display for outputting numbers and limited characters.
* **7-Segment Display Decoder**: Integrated BCD to 7-segment decoder/driver IC (CD4511) for simplifying digit display control with binary-coded input.
4. **Digital Input Section**: Button or switch interfaces to simulate and test control inputs.
Designed to simulate various real-world input conditions and allow users to interact with embedded systems directly. This section includes configurable buttons, switches, a rotary selector, a matrix keypad, and capacitive touch pads—all interfaced to microcontroller I/O pins.
* **Configurable Push Button (w/ LED)**: Pull-up/down selectable, real-time LED state indicator
* **Push Button Only (w/ LED)**: Simplified input with onboard LED state feedback
* **Rotary Encoder with Swtich**: User interfaces, combining continuous rotation (for volume, menus, brightness) with a push-button (for selection, power)
* **4×4 Matrix Keypad**: 16 keys (0–9, A–D, *, #); ideal for password entry, menu selection
* **Touch Pads (Capacitive)**: Touch-sensitive inputs for modern, buttonless interfaces
5. **Analog Input Sensors**: Potentiometers, voltage dividers, and external analog signal interfaces. This section helps users explore how physical changes—like movement, resistance, voltage, or temperature—are converted into voltage levels that can be read by a microcontroller’s ADC (Analog-to-Digital Converter).
* **Potentiometers**: Adjustable voltage sources to simulate analog sensor output (e.g., temperature, position).
* **Joystick Controller**: Dual-axis analog joystick (X and Y potentiometers); used to simulate multi-variable control or navigation input.
* **LDR Light Sensor**: Photoresistor paired with a fixed resistor in a voltage divider; provides variable voltage based on ambient light.
* **Analog Temperature Sensor**: TMP36 - a low-voltage, analog temperature sensor from Analog Devices that outputs a voltage proportional to Celsius temperature
* **Soil Moisture Sensor Interface**: External 3-pin analog soil moisture sensor, measures soil moisture through capacitance via voltage output.
* **Voltage Divider Circuit**: A pair of resistors connected in series forms a voltage divider that proportionally scales down the input voltage. The divided voltage is tapped between the two resistors and sent to the ADC pin for measurement.
6. **Sensor Modules**: Pre-mounted and external sensor support for monitoring environmental and physical parameters.
* **MAX30102** Pulse Oximeter & Heart Rate Sensor: Measures heart rate and SpO₂ (blood oxygen saturation) using optical photoplethysmography (PPG).
* **HC-SR04** Ultrasonic Distance Sensor: Measures object distance by calculating time-of-flight of ultrasonic pulses.
* IR Proximity Sensor: Detects nearby objects or obstacles using reflected infrared light.
* **BMP280** Barometric Sensor: Measures atmospheric pressure and temperature; useful for altitude and weather monitoring.
* **AGS10** TVOC Air Quality Sensor: Detects total volatile organic compounds (TVOCs); used for indoor air quality analysis.
* **DHT22** Digital Temperature and Humidity Sensor: Provides calibrated temperature and relative humidity readings with high accuracy.
* **AM312** PIR Motion Sensor: Detects human presence or motion using passive infrared radiation sensing.
7. **Actuator Section**: Transistor/MOSFET drivers for controlling actuators, relays, or motors.
* **Electromechanical Relay Switch**: Switches AC/DC loads using isolated digital control. Used for on/off control of lamps, solenoids, and appliances.
* **Solid State Relay Switch (SSR)**: Silent, fast-switching alternative to mechanical relays. Suitable for switching AC devices with zero-crossing detection.
* **H-Bridge Dual Motor Driver (L293D)**: Controls two DC motors bidirectionally using four digital signals. Supports speed control via PWM.
* **PWM Driver Circuit**: Uses transistor or MOSFET switching to modulate power for fans, LEDs, or other variable devices.
* **Passive & Active Speakers**: Demonstrate audio signal output and PWM sound synthesis. Active speaker accepts line-level signal; passive uses PWM.
* **Stepper Motor Driver (ULN2003)**: Drives unipolar stepper motors like the 28BYJ-48 using micro stepping control sequences.
* **Servo Motor (SG90)**: Standard 3-pin RC servo for angular position control (0°–180°) via PWM signal.
8. **Display Section**: Support for character or graphical Liquid Crystal Display (LCD) 16x2 screen via I²C or parallel interface.
* **16x2 LCD**: a standard 16×2 LCD based on the HD44780 controller, widely used in embedded systems for displaying text. It supports both 4-bit and 8-bit parallel interfaces, and is also compatible with I²C backpack modules for reduced pin usage.
9. **Communications Section**: Extended UART/I²C headers for integrating external modules, NB-IoT Module, RS-485 Modbus interface, and IR controller communication.
* **RS-485 to UART Converter (Bidirectional)**: Enables long-distance, differential serial communication over twisted pair. Supports Modbus RTU and other RS-485 protocols via UART bridging.
* **Waveshare SIM7600G-H 4G LTE Module**: Waveshare SIM7600G-H 4G LTE Module
* **I²C Bus (Inter-Integrated Circuit)**: Two-wire serial bus (SDA/SCL) used for communicating with multiple onboard and external digital sensors and displays. Pull-up resistors included for signal integrity.
* **Infrared (IR) Controller Receiver**: Demodulates IR signals from common remote controls (e.g., NEC protocol). Useful for testing user interface inputs and IR-based automation.
