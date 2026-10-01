# Sorun Giderme

Bir şey çalışmıyor mu? Önce buradaki listeyi kontrol et. Çoğu sorunun çözümü 30 saniye sürer.

---

## Kod yüklenmiyor

| Belirti | Muhtemel sebep | Çözüm |
|---|---|---|
| "Port bulunamadı" | USB kablosu bağlı değil veya sürücü eksik | Kabloyu değiştir. CH340 sürücüsünü kur ([indirme linki](http://www.wch-ic.com/downloads/CH341SER_ZIP.html)). |
| "Kart yanıt vermiyor" | Yanlış kart seçili | **Araçlar → Kart → Arduino UNO** olmalı. |
| "avrdude: stk500 not in sync" | Port yanlış ya da başka bir program portu kullanıyor | Seri Monitör'ü kapat. Doğru portu seç. |
| Yükleme sırasında hata | `.ino` dosyası klasör adıyla aynı isimde değil | Dosya `stacker_ogrenci/stacker_ogrenci.ino` gibi olmalı. Dosyayı klasörden çıkarma. |

---

## Hiçbir LED yanmıyor

1. **Matris ters mi?** "1088BS" yazısı sana (a tarafına) bakmalı.
2. **Kodda `SATIR_ANOT` değerini kontrol et.** `true` dene, olmazsa `false` dene.
3. **GND kablosu takılı mı?** Arduino GND pini, breadboard'un − hattına bağlı olmalı.
4. **Kabloları kontrol et.** Sıkıca oturmayan kablo temas etmez.

---

## Bir çizgi / sıra yanmıyor

1. `matris_test.ino`'yu yükle.
2. **Seri Monitör'ü aç** (9600 baud).
3. Yanmayan çizgi sırasında hangi delik yazıyorsa o kabloyu veya direnci kontrol et.
4. Kabloyu bastır ya da çıkarıp yeniden tak.

---

## Görüntü karışık veya ters

| Belirti | Çözüm |
|---|---|
| Kule yandan ya da ters yönden büyüyor | Kodda `donusDerecesi`'ni değiştir: `0`, `90`, `180`, `270` |
| Sağ-sol ters görünüyor | Kodda `AYNA` değerini `true` yap |
| Her şey rastgele yanıyor | Kabloları montaj tablosuyla tek tek karşılaştır |

---

## Buton çalışmıyor

1. **GND bağlı mı?** Butonun bir ucu A4'e, diğer ucu GND'ye (− hattına) bağlı olmalı.
2. **− hattı ortadan bölünmüş olabilir.** GND kablosunu, butonun bağlı olduğu yarıya tak.
3. **A4 yuvası sıkı mı?** Kablo temas etmiyorsa bastır veya aynı pini paylaşan **SDA** yuvasını dene.

---

## Buzzer çalışmıyor veya cızırdıyor

| Belirti | Çözüm |
|---|---|
| Ses yok | GND bağlantısını kontrol et. Buzzer'ın uzun bacağı A5'e, kısa bacağı GND'ye. |
| Cızırtılı, bozuk ses | **Aktif** buzzer takılmış olabilir. Altında yeşil devre kartı görünen **pasif** buzzer'ı kullan. |

---

## Seri Monitör açılmıyor

1. **Araçlar → Seri Monitör** (ya da `Ctrl+Shift+M` / `Cmd+Shift+M`).
2. Sağ alt köşede baud hızı **9600** olmalı.
3. Port seçili değilse: **Araçlar → Port** → doğru portu seç.

---

## Arduino IDE ".ino dosyası klasörde değil" diyor

Arduino IDE, `.ino` dosyasının kendi adıyla aynı klasörde olmasını ister. Örneğin:
```
stacker_ogrenci/
  └── stacker_ogrenci.ino    ✅ doğru

stacker_ogrenci.ino           ❌ yanlış (klasörsüz)
```

ZIP'i indirip açtığında yapı zaten doğrudur. Dosyayı klasörden çıkarma.

---

Hâlâ çözülmedi mi? Derste sor ya da [bir issue aç](https://github.com/arif7esat/Robotic-Coding/issues).

← [Ana sayfa](README.md)
