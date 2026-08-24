# ESP32 Röle Kontrol

ESP32 üzerinde çalışan, WiFi erişim noktası (Access Point) açarak tarayıcı üzerinden 4 kanallı röleyi buton gibi tetikleyen bir kontrol sistemi.

## Özellikler

- ESP32 kendi WiFi ağını yayınlar (harici router gerekmez)
- Modern, koyu temalı, mobil uyumlu web arayüzü
- Her röle **buton taklidi** yapar: tetiklendiğinde kısa süre (varsayılan 500ms) açılır ve otomatik kapanır — garaj kapısı, kapı zili, geçici anahtarlama gibi kullanımlar için uygundur
- 4 bağımsız röle kanalı, sayfa yenilenmeden (fetch/AJAX) tetikleme

## Donanım

- ESP32 geliştirme kartı
- 4 kanallı röle modülü (aktif-LOW)
- 5V harici güç adaptörü (ESP32 ve röle modülünü birlikte besleyecek, min. 1-2A)

### Bağlantılar

| ESP32 GPIO | Röle Kanalı |
|---|---|
| 16 | IN1 |
| 17 | IN2 |
| 18 | IN3 |
| 19 | IN4 |

Röle modülünün VCC ve GND'si ile ESP32'nin 5V/VIN ve GND'si, ortak bir 5V adaptörden paralel beslenmelidir. Tüm GND hatları ortak olmalıdır.

## Kurulum

1. Arduino IDE'de `WiFi.h` ve `WebServer.h` kütüphanelerinin (ESP32 board paketiyle birlikte gelir) kurulu olduğundan emin ol.
2. `sketch_aug22a.ino` dosyasını aç.
3. Gerekirse `ssid`, `password` ve `PULSE_MS` (tetikleme süresi) değerlerini kendine göre düzenle.
4. Kartı seç (Tools > Board > ESP32) ve yükle.

## Kullanım

1. ESP32 açıldıktan sonra `ESP32_ROLE` adlı WiFi ağına bağlan (şifre: `12345678`).
2. Tarayıcıdan `192.168.4.1` adresine git.
3. İlgili röle kartındaki **TETİKLE** butonuna bas.

## Lisans

Bu proje kişisel/eğitim amaçlı kullanım için serbesttir.
