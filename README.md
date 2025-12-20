# DOST-BULSU FUTURE-LAB IoT Trainer Board
## Project Description
FUTURE-LAB (Fault-Tolerant and User-Friendly Trainer Board for Upcoming Research and Engineering Education Lab Kit Integrating Emerging Technologies) is a DOST CRADLE funded research and development project. It is an integrated electronics laboratory trainer board engineered for both academic training and professional development. This board simulates a wide range of hands-on learning, prototype development, and experimentation with emerging technologies in engineering education and research, incorporating critical fault-tolerance mechanisms. It is ideal for learning how to design resilient and reliable smart systems.

Its primary purpose is to:
* Serve as a modular, fault-tolerant platform for exploring embedded systems, IoT, AI, and smart technologies.
* Equip students, educators, and researchers with a user-friendly training environment for real-world applications and interdisciplinary learning.
* Provide a versatile and scalable system that supports classroom instruction, capstone projects, R&D, and technology deployment.
* Demonstrate innovation in areas such as smart agriculture, smart cities, environmental sensing, wireless communication, and edge computing.

| ![1.png](https://github.com/TronixLab/DOST-BULSU-FUTURE-LAB-IoT-Trainer-Board/blob/main/media/1.png) | 
|:--:| 
| *FUTURE-LAB IoT Trainer Board* |

### Board Components
**1. Core Development Board**
FUTURE-LAB is built around the LILYGO TTGO LoRa32, a compact yet powerful development board based on the ESP32 microcontroller, which integrates key wireless communication features and embedded peripherals for rapid Internet of Things (IoT) prototyping and education.
| ![2.png](https://github.com/TronixLab/DOST-BULSU-FUTURE-LAB-IoT-Trainer-Board/blob/main/media/2.png?raw=true) | 
|:--:| 
| *LILYGO TTGO LoRa32 V2.1_6.1 Wi-Fi + Bluetooth LoRa Board* |

**2. Board Peripherals**
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
Key Features:

