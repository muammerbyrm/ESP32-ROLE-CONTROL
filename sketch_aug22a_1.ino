#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "ESP32_ROLE";
const char* password = "12345678";

WebServer server(80);

#define ROLE1 16
#define ROLE2 17
#define ROLE3 18
#define ROLE4 19

// Röle butona basılınca kaç ms açık kalsın (buton taklidi)
const int PULSE_MS = 500;

void pulseRelay(int pin) {
  digitalWrite(pin, LOW);   // röleyi tetikle (aktif-LOW modül varsayımı)
  delay(PULSE_MS);
  digitalWrite(pin, HIGH);  // bırak
}

void sendPage() {

  String html =
  "<!DOCTYPE html><html>"
  "<head>"
  "<meta name='viewport' content='width=device-width, initial-scale=1'>"
  "<title>ESP32 Kontrol</title>"
  "<style>"
    "*{box-sizing:border-box;margin:0;padding:0}"
    "body{"
      "font-family:'Segoe UI',Arial,sans-serif;"
      "background:linear-gradient(135deg,#1e1e2f,#2d2d44);"
      "min-height:100vh;"
      "display:flex;flex-direction:column;align-items:center;"
      "padding:32px 16px;color:#f0f0f5;"
    "}"
    "h1{font-size:1.6rem;font-weight:600;margin-bottom:24px;letter-spacing:0.5px}"
    ".grid{"
      "display:grid;grid-template-columns:1fr 1fr;gap:16px;"
      "width:100%;max-width:420px;"
    "}"
    ".card{"
      "background:rgba(255,255,255,0.06);"
      "border:1px solid rgba(255,255,255,0.1);"
      "border-radius:16px;padding:20px 12px;"
      "text-align:center;"
      "backdrop-filter:blur(6px);"
    "}"
    ".card h3{font-size:0.95rem;font-weight:500;opacity:0.8;margin-bottom:14px}"
    "button{"
      "width:100%;padding:16px 0;border:none;border-radius:12px;"
      "background:linear-gradient(135deg,#6c5ce7,#8e6ff0);"
      "color:#fff;font-size:1rem;font-weight:600;"
      "cursor:pointer;transition:transform 0.1s ease,box-shadow 0.15s ease;"
      "box-shadow:0 4px 12px rgba(108,92,231,0.35);"
    "}"
    "button:active{transform:scale(0.95);box-shadow:0 2px 6px rgba(108,92,231,0.35)}"
    ".status{margin-top:24px;font-size:0.8rem;opacity:0.5}"
  "</style>"
  "</head>"
  "<body>"
  "<h1>ESP32 Röle Kontrol</h1>"
  "<div class='grid'>"
    "<div class='card'><h3>Röle 1</h3><button onclick=\"trig('r1')\">TETİKLE</button></div>"
    "<div class='card'><h3>Röle 2</h3><button onclick=\"trig('r2')\">TETİKLE</button></div>"
    "<div class='card'><h3>Röle 3</h3><button onclick=\"trig('r3')\">TETİKLE</button></div>"
    "<div class='card'><h3>Röle 4</h3><button onclick=\"trig('r4')\">TETİKLE</button></div>"
  "</div>"
  "<div class='status' id='status'>Hazır</div>"
  "<script>"
    "function trig(id){"
      "document.getElementById('status').innerText = id + ' tetiklendi...';"
      "fetch('/'+id).then(()=>{"
        "document.getElementById('status').innerText = id + ' OK';"
      "}).catch(()=>{"
        "document.getElementById('status').innerText = 'Bağlantı hatası';"
      "});"
    "}"
  "</script>"
  "</body></html>";

  server.send(200, "text/html", html);
}

void setup() {

  Serial.begin(115200);

  pinMode(ROLE1, OUTPUT);
  pinMode(ROLE2, OUTPUT);
  pinMode(ROLE3, OUTPUT);
  pinMode(ROLE4, OUTPUT);

  digitalWrite(ROLE1, HIGH);
  digitalWrite(ROLE2, HIGH);
  digitalWrite(ROLE3, HIGH);
  digitalWrite(ROLE4, HIGH);

  WiFi.mode(WIFI_AP);
  bool apOk = WiFi.softAP(ssid, password);

  Serial.println(apOk ? "WiFi Basladi" : "WiFi Baslamadi!");
  Serial.println(WiFi.softAPIP());

  server.on("/", sendPage);

  server.on("/r1", [](){
    pulseRelay(ROLE1);
    server.send(200, "text/plain", "OK");
  });

  server.on("/r2", [](){
    pulseRelay(ROLE2);
    server.send(200, "text/plain", "OK");
  });

  server.on("/r3", [](){
    pulseRelay(ROLE3);
    server.send(200, "text/plain", "OK");
  });

  server.on("/r4", [](){
    pulseRelay(ROLE4);
    server.send(200, "text/plain", "OK");
  });

  server.begin();
}

void loop() {
  server.handleClient();
}
