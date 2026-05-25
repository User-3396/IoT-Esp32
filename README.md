# Esp32 - Intelligent Elevator (Under development...)

### **Hall implementation**

### Topics

- IoT
- MQTT 
- ESP32
- Elevator: Hall functionalities

![](https://img.shields.io/badge/MQTT-black?style=for-the-badge&logo=mqtt&logoColor=green&logoSize=auto)
![](https://img.shields.io/badge/Espressif-black?style=for-the-badge&logo=espressif&logoColor=green&logoSize=auto)

## Esp32

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

## Digital display (_GMT130-v1.0_)

<img 
    allign="center"  
    style="width: 300px; border: solid 2px rgb(0, 255, 255);"
    src="https://abacasstorageaccnt.blob.core.windows.net/cirkit/589453c0-de81-4c0b-ba42-8bb299b8a8d3.png"
/>


## Configuração

```cpp
    char* codigo ="cpp";
```

---
---

### Ecrã - Pinagem

| Display | DOIT DevKit v1 | DevKitC v4 |
| - | - | - |
| Vcc | `3V3` | `3V3` |
| GND | `GND` | `GND` |
| SCK | `D18` `GPIO 18` `SCK` | - |
| SDA | `D23` `GPIO 23` `MOSI` | `23` `GPIO 23` `WIRE_MOSI` |
| DC | qualquer digital livre |
| RST/RES | qualquer digital livre |
| BKL/BL/LED | `5v` `3V3` | `5V` |

<!-- ## Linguagens e Tecnologias -->

---
---
# Refferences

https://www.circuitstate.com/pinouts/doit-esp32-devkit-v1-wifi-development-board-pinout-diagram-and-reference/#Pull-Up_amp;_Pull-Down

In cooperation with an external repository: https://github.com/0Chaves/CabineElevador_eps32

