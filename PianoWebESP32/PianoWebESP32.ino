#include <WiFi.h>
#include <WebServer.h>

// ===== Configuracao do Wi-Fi =====
// Troque pelos dados da sua rede antes de gravar no ESP32.
const char* ssid = "NOME_DA_SUA_REDE";
const char* password = "SENHA_DA_SUA_REDE";

// ===== Configuracao do buzzer =====
// Ligue o terminal positivo do buzzer neste pino e o negativo no GND.
const int BUZZER_PIN = 25;

WebServer server(80);

struct Note {
  const char* name;
  const char* key;
  int frequency;
};

// Frequencias aproximadas da escala de Do maior na oitava 4.
Note notes[] = {
  {"Do", "A", 262},
  {"Re", "S", 294},
  {"Mi", "D", 330},
  {"Fa", "F", 349},
  {"Sol", "G", 392},
  {"La", "H", 440},
  {"Si", "J", 494},
  {"Do agudo", "K", 523}
};

const int NOTE_COUNT = sizeof(notes) / sizeof(notes[0]);

// ===== HTML =====
const char HTML_PAGE[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="pt-BR">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Piano Web ESP32</title>
  <style>
    %CSS%
  </style>
</head>
<body>
  <main class="app">
    <h1>Piano Web ESP32</h1>

    <section class="status">
      <span>Nota tocada:</span>
      <strong id="current-note">Nenhuma</strong>
    </section>

    <section class="piano" aria-label="Teclas do piano">
      <button class="key" data-note="0" data-label="Do">Do<small>A</small></button>
      <button class="key" data-note="1" data-label="Re">Re<small>S</small></button>
      <button class="key" data-note="2" data-label="Mi">Mi<small>D</small></button>
      <button class="key" data-note="3" data-label="Fa">Fa<small>F</small></button>
      <button class="key" data-note="4" data-label="Sol">Sol<small>G</small></button>
      <button class="key" data-note="5" data-label="La">La<small>H</small></button>
      <button class="key" data-note="6" data-label="Si">Si<small>J</small></button>
      <button class="key" data-note="7" data-label="Do agudo">Do+<small>K</small></button>
    </section>

    <button id="stop-button" class="stop-button" type="button">Parar som</button>
  </main>

  <script>
    %JS%
  </script>
</body>
</html>
)rawliteral";

// ===== CSS =====
const char CSS_CODE[] PROGMEM = R"rawliteral(
* {
  box-sizing: border-box;
}

body {
  margin: 0;
  min-height: 100vh;
  display: flex;
  align-items: center;
  justify-content: center;
  font-family: Arial, Helvetica, sans-serif;
  background: #20242c;
  color: #f5f5f5;
  padding: 24px;
}

.app {
  width: min(920px, 100%);
  text-align: center;
}

h1 {
  margin: 0 0 18px;
  font-size: clamp(28px, 5vw, 44px);
  font-weight: 700;
}

.status {
  display: inline-flex;
  gap: 10px;
  align-items: center;
  justify-content: center;
  margin-bottom: 22px;
  padding: 10px 16px;
  border-radius: 8px;
  background: #303744;
}

.status strong {
  color: #ffd166;
}

.piano {
  display: grid;
  grid-template-columns: repeat(8, minmax(56px, 1fr));
  gap: 6px;
  padding: 12px;
  background: #11151b;
  border-radius: 8px;
  box-shadow: 0 16px 36px rgba(0, 0, 0, 0.35);
}

.key {
  min-height: 220px;
  border: 0;
  border-radius: 0 0 8px 8px;
  background: linear-gradient(#ffffff, #dfe4ea);
  color: #1d252f;
  font-size: clamp(15px, 2.4vw, 22px);
  font-weight: 700;
  cursor: pointer;
  display: flex;
  flex-direction: column;
  align-items: center;
  justify-content: flex-end;
  gap: 8px;
  padding: 18px 6px;
  box-shadow: inset 0 -8px 0 rgba(0, 0, 0, 0.08);
  transition: transform 0.08s ease, background 0.08s ease;
}

.key small {
  color: #69717c;
  font-size: 13px;
}

.key:active,
.key.active {
  transform: translateY(5px);
  background: linear-gradient(#ffd166, #f4b942);
}

.stop-button {
  margin-top: 20px;
  min-height: 44px;
  padding: 0 22px;
  border: 0;
  border-radius: 8px;
  background: #ef476f;
  color: #ffffff;
  font-size: 16px;
  font-weight: 700;
  cursor: pointer;
}

.stop-button:active {
  transform: translateY(2px);
}

@media (max-width: 640px) {
  body {
    padding: 14px;
  }

  .piano {
    grid-template-columns: repeat(4, 1fr);
  }

  .key {
    min-height: 150px;
  }
}
)rawliteral";

// ===== JavaScript =====
const char JS_CODE[] PROGMEM = R"rawliteral(
const keys = document.querySelectorAll(".key");
const currentNote = document.getElementById("current-note");
const stopButton = document.getElementById("stop-button");
const keyboardMap = {
  a: 0,
  s: 1,
  d: 2,
  f: 3,
  g: 4,
  h: 5,
  j: 6,
  k: 7
};

async function playNote(noteIndex) {
  const key = document.querySelector(`[data-note="${noteIndex}"]`);
  if (!key) return;

  keys.forEach(item => item.classList.remove("active"));
  key.classList.add("active");
  currentNote.textContent = key.dataset.label;

  try {
    await fetch(`/play?note=${noteIndex}`);
  } catch (error) {
    currentNote.textContent = "Erro de conexao";
  }
}

async function stopSound() {
  keys.forEach(item => item.classList.remove("active"));
  currentNote.textContent = "Nenhuma";

  try {
    await fetch("/stop");
  } catch (error) {
    currentNote.textContent = "Erro de conexao";
  }
}

keys.forEach(key => {
  key.addEventListener("click", () => playNote(key.dataset.note));
});

stopButton.addEventListener("click", stopSound);

document.addEventListener("keydown", event => {
  const noteIndex = keyboardMap[event.key.toLowerCase()];
  if (noteIndex !== undefined && !event.repeat) {
    playNote(noteIndex);
  }
});

document.addEventListener("keyup", event => {
  if (keyboardMap[event.key.toLowerCase()] !== undefined) {
    stopSound();
  }
});
)rawliteral";

String buildPage() {
  String page = FPSTR(HTML_PAGE);
  page.replace("%CSS%", FPSTR(CSS_CODE));
  page.replace("%JS%", FPSTR(JS_CODE));
  return page;
}

void stopTone() {
  noTone(BUZZER_PIN);
}

void playTone(int frequency) {
  tone(BUZZER_PIN, frequency);
}

void handleRoot() {
  server.send(200, "text/html", buildPage());
}

void handlePlay() {
  if (!server.hasArg("note")) {
    server.send(400, "text/plain", "Parametro note ausente");
    return;
  }

  int noteIndex = server.arg("note").toInt();
  if (noteIndex < 0 || noteIndex >= NOTE_COUNT) {
    server.send(400, "text/plain", "Nota invalida");
    return;
  }

  playTone(notes[noteIndex].frequency);
  server.send(200, "text/plain", notes[noteIndex].name);
}

void handleStop() {
  stopTone();
  server.send(200, "text/plain", "Som parado");
}

void setup() {
  Serial.begin(115200);

  // Prepara o pino do buzzer. A funcao tone() usa PWM internamente no ESP32.
  pinMode(BUZZER_PIN, OUTPUT);
  stopTone();

  // Conecta o ESP32 ao roteador Wi-Fi.
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  Serial.print("Conectando ao Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.print("Conectado. Acesse: http://");
  Serial.println(WiFi.localIP());

  // Rotas HTTP servidas pelo ESP32.
  server.on("/", handleRoot);
  server.on("/play", handlePlay);
  server.on("/stop", handleStop);
  server.begin();
}

void loop() {
  // Mantem o servidor web respondendo as requisicoes do navegador.
  server.handleClient();
}
