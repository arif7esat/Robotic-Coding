# Sözlük

Derslerde geçen teknik terimlerin kısa açıklamaları. Bir kelimeyi bilmiyorsan buraya bak.

---

| Terim | Açıklama |
|---|---|
| **Anot** | LED'in artı (+) ucu, uzun bacak. Akım anottan girer. |
| **Ark (bounce)** | Butona basıldığında metal yayın birkaç milisaniye titreşmesi. Kodda 50 ms filtre ile engellenir. |
| **Breadboard** | Lehim olmadan parçaları birbirine bağladığımız delikli tahta. İçindeki metal şeritler delikleri gruplar halinde birleştirir. |
| **Dijital pin** | Arduino'nun HIGH (5 V) veya LOW (0 V) yapılabilen çıkışları. D0–D13. |
| **EEPROM** | Elektrik kesilince silinmeyen küçük kalıcı hafıza. Rekor skorunu burada saklıyoruz. |
| **Frekans (Hz)** | Saniyedeki titreşim sayısı. Sesin inceliğini/kalınlığını belirler. 440 Hz = La notası. |
| **GND (Ground)** | Toprak, 0 V. Devrenin dönüş yolu. Her devrede en az bir GND bağlantısı olmalı. |
| **Göz kalıcılığı** | Gözün ışığı kısa bir süre "hatırlaması". Taramanın çalışma sebebi: LED saniyede 100 kez yanıp sönerse sürekli yanıyor sanırız. |
| **HIGH / LOW** | Pinin 5 V (HIGH) veya 0 V (LOW) olması. `digitalWrite(pin, HIGH)` ile kontrol edilir. |
| **INPUT_PULLUP** | Pinin içeriden 5 V'a çekilmesi; buton basılınca LOW okunur. Dış direnç gerekmez. |
| **Katot** | LED'in eksi (−) ucu, kısa bacak. Akım katottan çıkar. |
| **Kısa devre** | Akımın bir yükten (direnç, LED) geçmeden doğrudan dönmesi. Parçalara zarar verebilir. |
| **mA (miliamper)** | Akımın birimi. 1000 mA = 1 A. Arduino'nun bir pini en fazla 40 mA verebilir. |
| **Modüler aritmetik (%)** | Bölmeden kalan. `450 % 360 = 90`. Kodda yön hesaplamada kullanılır. |
| **Ohm yasası** | Akım = Gerilim / Direnç (`I = V / R`). Direnç değeri seçmenin temel formülü. |
| **Ortak anot** | Bir satırdaki LED'lerin anotlarının tek bacakta birleşmesi. 1088BS matris ortak anottur. |
| **PROGMEM** | Verileri RAM yerine flash (program) hafızasında tutan Arduino komutu. 2 KB RAM'i korur. |
| **Tarama (multiplexing)** | Ekranı satır satır çok hızlı yakarak bütün resmi göstermek. 16 kabloyla 64 LED kontrol etmenin yolu. |

---

← [Ana sayfa](README.md)
