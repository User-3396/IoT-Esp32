# Esp32 - Intelligent Elevator

## Estructure

| File | Description |
| - | - |
| `main.cpp` | General management of the Hall system |
| `Hall.cpp` | Hall class features and methods |
| `mqttClient` | MQTT and Wifi connectivity features and methods |

### Topics

- IoT
- MQTT 
- ESP32
- Elevator: Hall functionalities

<!-- ![](https://img.shields.io/badge/MQTT-black?style=for-the-badge&logo=mqtt&logoColor=green&logoSize=auto)
![](https://img.shields.io/badge/Espressif-black?style=for-the-badge&logo=espressif&logoColor=green&logoSize=auto) -->

## Esp32 (models)

| DevKitC v4 (based in wokwi.com) | DOIT DevKit v1 - ESP-Wroom-32D |
| - | - |

<img
    allign="center"
    title="ESP32 DevKitC v4"
    style="height: 200px; border: solid 2px rgb(255,185,0);" 
    src="https://docs.espressif.com/projects/esp-dev-kits/en/latest/esp32/_images/esp32_devkitC_v4_pinlayout.png"
/>
<img 
    allign="center"
    title="ESP32 DOIT DevKit v1"
    style="height: 200px; border: solid 2px rgb(255,185,0);"
    src="lib/ESP32 - Wroom - 32D.png"
/>

## Configuration for use in the Arduino IDE:

* Download the folder `Main` from `/src` and open on IDE, because the software works if the main.cpp file is inside a folder named "Main";
* It may be necessary to change the extension of the main file (`main.cpp`) to `.ino`;
* It may be necessary for each file  (`.ino`, `.cpp` e `.h`) to be listed on the first line:
    ```ino
    #include <Arduino.h>
    ```
* install the library __PubSubClient__

<!-- ### Ecrã - Pinout

| Display | DOIT DevKit v1 | DevKitC v4 |
| - | - | - |
| Vcc | `3V3` | `3V3` |
| GND | `GND` | `GND` |
| SCK | `D18` `GPIO 18` `SCK` | - |
| SDA | `D23` `GPIO 23` `MOSI` | `23` `GPIO 23` `WIRE_MOSI` |
| DC | qualquer digital livre |
| RST/RES | qualquer digital livre |
| BKL/BL/LED | `5v` `3V3` | `5V` |-->

<!-- ## Linguagens e Tecnologias -->

---
---
# Refferences

https://www.circuitstate.com/pinouts/doit-esp32-devkit-v1-wifi-development-board-pinout-diagram-and-reference/#Pull-Up_amp;_Pull-Down

In cooperation with an external repository: https://github.com/0Chaves/CabineElevador_eps32

