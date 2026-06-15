## Grupo 03 - Lucio

<div align="center" 
style="
    padding:0px;
    margin:0px;
    background-color:rgb(30,30,30); 
    color:rgb(255,185,0);
    border: 2px solid rgb(60,60,60);
    border-radius: 10px;
"> 

Descrição geral da implementação. 
</div>

### Estrutura Modular: 

<div style="
    padding:5px;
    margin:0px;
    background-color:rgb(30,30,30); 
    border: 2px solid rgb(60,60,60);
    border-radius: 10px;
">

- Main/main.cpp
- Sensor.cpp
- MQTTClient.cpp
</div>

### Classes: 
`Sensor` `MQTTClient`

### Conexão MQTT:

<div style="
    padding:5px;
    margin:0px;
    background-color:rgb(30,30,30); 
    border: 2px solid rgb(60,60,60);
    border-radius: 10px;
">

- MQTTClient.cpp

    - `MQTTClient::begin()`
    Função de inicialização que configura a conexão com wifi e se inscreve nos tópicos;
    - `MQTTClient::loop()`
    Função que roda o ciclo mqtt de mensagens e checa a conexão wifi;
    - `MQTTClient::publish()`
    Função que publica as mensagens;

- Mensagens:

    - __Publicação/Envio__: 

    ```cpp
    '{"stationId":"corredor-001","type": "SE","luminosidade": 47}'
    '{"stationId":"corredor-001","type":"SE","emergencia": 0}'
    ```

    - __Escuta__:

    ```cpp
    '{"stationId":"EIF001","latitude":-28.47410011,"longitude": -49.02539825,"type":"SE","emergencia": 1}'
    ```
</div>

### Funcionalidades no Sensor:

- Inicialização da classe de conexão MQTT `client`

```cpp
void Sensor::start (const char* clientID, const uint8_t* pins ,const uint8_t* modes, int size){
    client.begin("corredor-001");
    // (...)
}
```
- configuração dos pinos do LDR:

```cpp
pinMode(pins[0], modes[0]);
pinMode(pins[1], modes[1]);
_LDR_PIN =pins[0];
_RELE_PIN =pins[1];
```

- chamada da função de atualização do ciclo MQTT:

```cpp
void Sensor::update (){
    client.loop();
```

- 

<br>

<div align="center" 
style="
    padding:0px;
    margin:0px;
    background-color:rgb(30,30,30); 
    color:rgb(255,185,0);
    border: 2px solid rgb(60,60,60);
    border-radius: 10px;
">

### Tópicos utilizados para publicação e escuta. 
</div>

- __Escuta__: 
    - `rpiot/grupo03/corredor/esp32/emergencia`

- __Publicação__:
    - `rpiot/grupo03/corredor/esp32/luminosidade`
    - `rpiot/grupo03/corredor/esp32/emergencia`

<br>

<div align="center" 
style="
    padding:0px;
    margin:0px;
    background-color:rgb(30,30,30); 
    color:rgb(255,185,0);
    border: 2px solid rgb(60,60,60);
    border-radius: 10px;
">

### Prints do monitor serial. 
</div>

<br>

<div align="center" 
style="
    padding:0px;
    margin:0px;
    background-color:rgb(30,30,30); 
    color:rgb(255,185,0);
    border: 2px solid rgb(60,60,60);
    border-radius: 10px;
">

### Json/print do dashboard. 
</div>

<br>

<div align="center" 
style="
    padding:0px;
    margin:0px;
    background-color:rgb(30,30,30); 
    color:rgb(255,185,0);
    border: 2px solid rgb(60,60,60);
    border-radius: 10px;
">

### Esquema de ligação dos sensores e atuadores (Wokwi). 
</div>


https://dillinger.io/

