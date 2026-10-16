# Piano Web ESP32

[Português](#português) · [English](#english)

## Português

Projeto acadêmico desenvolvido com Arduino e ESP32: um piano simples controlado pelo navegador, com reprodução de notas em um buzzer piezoelétrico.

O circuito foi **montado e testado fisicamente**. O estudo conecta uma interface web a um dispositivo físico, explorando comunicação por Wi-Fi e controle de som.

### Funcionamento

O ESP32 conecta-se à rede Wi-Fi e hospeda uma página com teclas virtuais. Ao interagir com a interface, o usuário envia comandos ao dispositivo, que reproduz a nota no buzzer.

- Oito notas: Dó, Ré, Mi, Fá, Sol, Lá, Si e Dó agudo.
- Controle por clique, toque ou teclado: `A S D F G H J K`.
- Indicador da nota atual e botão para parar o som.
- Interface HTML, CSS e JavaScript incorporada ao sketch Arduino.

### Hardware

- Placa ESP32.
- Buzzer piezoelétrico.
- Fios para conexão.
- Cabo USB compatível com a placa.

```text
Buzzer positivo (+) → GPIO 25 do ESP32
Buzzer negativo (-) → GND do ESP32
```

O pino pode ser ajustado em `BUZZER_PIN` no sketch.

### Como executar

1. Abra `PianoWebESP32/PianoWebESP32.ino` na Arduino IDE com suporte à sua placa ESP32 instalado.
2. Configure `ssid` e `password` com os dados da sua rede Wi-Fi.
3. Selecione a placa e a porta correspondentes e envie o sketch ao ESP32.
4. Abra o Monitor Serial em **115200 baud**.
5. Acesse o endereço IP informado usando um navegador na mesma rede.
6. Use as teclas virtuais ou `A S D F G H J K` para tocar.

As bibliotecas `WiFi.h` e `WebServer.h` fazem parte do suporte ESP32 para Arduino. Mantenha as credenciais da sua rede fora das versões publicadas do código.

### Tecnologias e limites

ESP32 · Arduino/C++ · Wi-Fi · HTML · CSS · JavaScript

O projeto é uma demonstração acadêmica de controle web de hardware. O buzzer reproduz tons simples, e o acesso à interface depende da conectividade com o ESP32 na rede local.

---

## English

An academic project built with Arduino and ESP32: a simple browser-controlled piano that plays notes through a piezo buzzer.

The circuit was **physically assembled and tested**. The study connects a web interface to a physical device, exploring Wi-Fi communication and sound control.

### How it works

The ESP32 joins a Wi-Fi network and hosts a page with virtual keys. Interacting with the interface sends commands to the device, which plays the selected note on the buzzer.

- Eight notes: C, D, E, F, G, A, B, and high C.
- Mouse, touch, or keyboard controls: `A S D F G H J K`.
- Current-note indicator and a stop button.
- HTML, CSS, and JavaScript interface embedded in the Arduino sketch.

### Hardware

- ESP32 board.
- Piezo buzzer.
- Connecting wires.
- A USB cable compatible with the board.

```text
Buzzer positive (+) → ESP32 GPIO 25
Buzzer negative (-) → ESP32 GND
```

The pin can be changed through `BUZZER_PIN` in the sketch.

### Setup

1. Open `PianoWebESP32/PianoWebESP32.ino` in Arduino IDE with support for your ESP32 board installed.
2. Set `ssid` and `password` to your Wi-Fi network credentials.
3. Select the correct board and port, then upload the sketch.
4. Open the Serial Monitor at **115200 baud**.
5. Open the reported IP address in a browser on the same network.
6. Play using the virtual keys or `A S D F G H J K`.

The `WiFi.h` and `WebServer.h` libraries are included in Arduino's ESP32 support. Keep your network credentials out of published versions of the code.

### Technologies and limitations

ESP32 · Arduino/C++ · Wi-Fi · HTML · CSS · JavaScript

This project is an academic demonstration of web-controlled hardware. The buzzer produces simple tones, and accessing the interface requires connectivity to the ESP32 on the local network.
