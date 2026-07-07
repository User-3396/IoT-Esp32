# Iluminação de Emergência para Ambientes Críticos 

## __Objetivo__: 
O __sensor LDR__ monitora a luz ambiente. Em caso de uma queda súbita e acentuada de luz (simulando uma falha de energia), o __relé__ é acionado para ligar um sistema de iluminação secundário (__LED__). O acionamento do relé deve ser feito via mensagem recebida do MQTT, e não diretamente pelo sketch. 

## __Gráficos Grafana (tipo: dados)__
- Stat: iluminação 
- Stat: LED 

## __Tópicos MQTT__

<details><summary>detalhes</summary>

- __Gravar__: 
    - _rpiot/__grupoXX__/corredor/esp32/luminosidade_ 

        Exemplo mensagem: 
        _'{"stationId":"EIF001","latitude":-28.47410011,"longitude": -49.02539825,"type":"SE","luminosidade":47}'_

    - _rpiot/<grupo99>/corredor/esp32/emergencia_
        
        Exemplo mensagem: 
        _'{"stationId":"EIF001","latitude":-28.47410011,"longitude": -49.02539825,"type":"SE","emergencia": 1}'_

- __Ler__: 
    - _rpiot/<grupo99>/corredor/esp32/emergencia_
        - Se 1 aciona relé, se 0 desliga.
</details>

## __Lista de Componentes__: 
<details><summary>detalhes</summary>

- ESP32 DevKit V1 
- Módulo Sensor de Luz LDR 
- Módulo Relé 
- Protoboard e Jumpers 
- LED alto brilho 
- Resistor 220 Ohms 
</details>

## Esquema de Ligação: 
- __Sensor LDR -> ESP32__: 
    - VCC -> 3.3V 
    - GND -> GND 
    - A0 -> GPIO02

- __Módulo Relé -> ESP32__: 
    - VCC -> VIN (5V) 
    - GND -> GND 
    - IN -> GPIO04 
    
- __Módulo Relé -> LED__: 
    - COM -> 5V 
    - NC -> Anodo (+) 

