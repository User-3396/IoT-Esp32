# Esp32 - Intelligent Elevator (Under development...)

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

* Baixar a pasta `Main` de `/src` e abrir na IDE, pois o software funciona se o arquivo main.cpp estiver dentro de uma pasta nomeada de "Main";
* Pode ser necessário mudar a extensão do arquivo principal (`main.cpp`) para `.ino`;
* Pode ser necessário que cada arquivo (`.ino`, `.cpp` e `.h`) precise constar na primeira linha: 
* instalar bibliotecas como __PubSubClient__
    ```ino
    #include <Arduino.h>
    ```

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

