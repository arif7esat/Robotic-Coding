# Başlarken

Arduino IDE'yi kurmak, kodu indirip karta yüklemek için bu sayfayı takip et. 10 dakikada hazır olursun.

---

## 1. Arduino IDE'yi kur

1. [arduino.cc/en/software](https://www.arduino.cc/en/software) adresine git.
2. İşletim sistemine göre indir (Windows / macOS / Linux).
3. Kur ve aç.

> Sette **CH340** çipli bir Arduino UNO varsa (arkasında "SMD" ya da "CH340" yazıyorsa) sürücü yüklemen gerekebilir. [CH340 sürücüsü](http://www.wch-ic.com/downloads/CH341SER_ZIP.html) buradan indirilir.

---

## 2. Kodu indir

1. Reponun ana sayfasında yeşil **Code** butonuna tıkla → **Download ZIP**.
2. ZIP dosyasını aç.
3. Çalışmak istediğin haftanın `kod/` klasöründeki `.ino` dosyasını çift tıkla. Arduino IDE açılacak.

> **Önemli:** Arduino IDE, `.ino` dosyasının kendi adıyla aynı klasörde durmasını ister. ZIP'ten çıkan yapı buna zaten uygun; dosyaları klasörden çıkarma.

---

## 3. Kartı bağla ve portu seç

1. Arduino'yu USB kablosuyla bilgisayara bağla.
2. Arduino IDE'de **Araçlar → Kart → Arduino UNO** seç.
3. **Araçlar → Port** → listeden Arduino'nun bağlı olduğu portu seç.
   - Windows: `COM3`, `COM4` gibi bir isim.
   - macOS: `/dev/cu.usbserial-...` ya da `/dev/cu.wchusbserial-...`.
   - Port listesi boşsa: USB kablosunu değiştir veya CH340 sürücüsünü kontrol et.

---

## 4. Kodu yükle

1. Sol üstteki **→** (yükle) butonuna bas.
2. Altındaki mesaj kutusunda "Yükleme tamamlandı" yazarsa her şey yolunda.
3. Hata alıyorsan → [Sorun giderme](SORUN-GIDERME.md).

---

## 5. Breadboard nasıl çalışır?

Breadboard lehim olmadan parçaları birbirine bağladığımız delikli tahtadır. Görünmeyen metal şeritleri bilmeden kablolama tutmaz.

- **Sayılar** (1–60) sütunları, **harfler** (a–j) satırları gösterir.
- Aynı sütundaki 5 delik birbirine bağlıdır: `a5-b5-c5-d5-e5` tek şerit, `f5-g5-h5-i5-j5` ayrı bir şerit.
- Ortadaki **kanal** iki yarıyı ayırır: `e5` ile `f5` bağlı **değildir**.
- Kenardaki uzun **+** ve **−** hatları boydan boya bağlıdır — güç ve GND için kullanılır.

Daha detaylı görsel: [Breadboard iç yapısı](kaynaklar/breadboard-ic-yapisi-2.png)

---

## 6. Setteki parçalar

| Parça | Adet | Görevi |
|---|:---:|---|
| Arduino UNO | 1 | Beyni. Kodu çalıştırır, pinlerinden 5 V / 0 V verir. |
| Breadboard | 1 | Lehimsiz bağlantı tahtası. |
| 1088BS 8×8 LED matris | 1 | 64 kırmızı LED, 16 bacak. Ekranımız. |
| 220 Ω direnç | 8+ | LED akımını sınırlar. Halkalar: kırmızı-kırmızı-kahverengi. |
| Tact buton | 1+ | Oyun kontrolü, başlatma. |
| Pasif buzzer | 1 | Ses efektleri ve melodiler. Altında yeşil devre kartı görünür. |
| Erkek-erkek jumper | 30 | Bağlantı kabloları. |

Setin tam içeriği ve daha fazla parça için [Direnç.net](https://www.direnc.net/) sitesine bakabilirsin.

---

## Ek kaynaklar

- [Arduino UNO CH340 Öğretim Rehberi (PDF)](kaynaklar/Arduino_UNO_SMD_CH340_Ogretim_Rehberi.pdf)
- [Breadboard iç yapısı görseli](kaynaklar/breadboard-ic-yapisi.png)
- [Veri tipleri ve aralıkları tablosu](kaynaklar/veri-tipleri-ve-araliklari.png)

---

← [Ana sayfa](README.md)
