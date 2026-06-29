# Piano Web com ESP32

Projeto Arduino/ESP32 de um piano simples controlado por pagina web. O ESP32 conecta ao Wi-Fi, hospeda uma interface web com teclas virtuais e toca notas musicais em um buzzer piezoeletrico.

## Recursos

- ESP32 como servidor web
- Buzzer piezoeletrico em pino digital/PWM
- Teclas virtuais: Do, Re, Mi, Fa, Sol, La, Si e Do agudo
- Controle pelo mouse/toque na tela
- Controle pelo teclado do computador: A, S, D, F, G, H, J, K
- Indicador da nota tocada
- Botao para parar o som
- HTML, CSS e JavaScript separados em blocos dentro do arquivo `.ino`

## Esquema de ligacao

```text
Buzzer positivo (+)  -> GPIO 25 do ESP32
Buzzer negativo (-)  -> GND do ESP32
```

Se quiser usar outro pino, altere esta linha no codigo:

```cpp
const int BUZZER_PIN = 25;
```

## Configuracao do Wi-Fi

No arquivo `PianoWebESP32/PianoWebESP32.ino`, altere:

```cpp
const char* ssid = "NOME_DA_SUA_REDE";
const char* password = "SENHA_DA_SUA_REDE";
```

## Como executar

1. Abra `PianoWebESP32/PianoWebESP32.ino` na Arduino IDE.
2. Selecione sua placa ESP32 em `Ferramentas > Placa`.
3. Grave o codigo no ESP32.
4. Abra o Monitor Serial em `115200` baud.
5. Aguarde o IP aparecer, por exemplo:

```text
Conectado. Acesse: http://192.168.1.50
```

6. Abra esse endereco em um navegador conectado a mesma rede Wi-Fi.
7. Toque nas teclas virtuais ou use as teclas A, S, D, F, G, H, J, K.

## Bibliotecas usadas

As bibliotecas usadas ja fazem parte do suporte ESP32 para Arduino IDE:

- `WiFi.h`
- `WebServer.h`
