# 🎮 Arduino Atölyesi

Her hafta bir proje. Kitaptaki "LED yak, LED söndür" alıştırmaları değil; AVM'deki oyun makinesinden radara kadar gerçek hayattan, kendin kurup kendin oynayabileceğin projeler.

Derste kaçırdın mı? Evde yeniden kurmak mı istiyorsun? Aşağıdan haftanı seç. Her sayfada devre şeması, kablo tablosu, yükleyeceğin kod ve sık karşılaşılan sorunlar var.

| Hafta | Proje | Ne öğrendik? | Seviye |
|:---:|---|---|:---:|
| 01 | [Stacker — kule dikme oyunu](haftalar/01-stacker/) | LED matris, tarama, Ohm yasası, buton, ses, EEPROM | ★★☆ |
| 02 | *Yakında* | | |

> İlk kez mi buradasın? → [Başlarken](BASLARKEN.md): Arduino IDE'yi kur, kodu indir, karta yükle.
>
> Bir şey çalışmıyor mu? → [Sorun giderme](SORUN-GIDERME.md)
>
> Bir kelimeyi bilmiyor musun? → [Sözlük](SOZLUK.md)

---

## Kodu nasıl indiririm?

**Bilgisayardan:**
1. Bu sayfanın üstündeki yeşil **Code** butonuna tıkla → **Download ZIP**.
2. ZIP'i aç. İstediğin haftanın `kod/` klasöründen `.ino` dosyasını çift tıkla — Arduino IDE açılır.

**Telefondan (sadece görmek için):**
1. Yüklemek istediğin `.ino` dosyasına git.
2. **Raw** butonuna bas → kodun tamamını göreceksin. Kopyalayıp bilgisayara yapıştırabilirsin.

> **Bu kodları değiştirmekten korkma.** Değiştirir, bozarsın, geri alırsın. Her şeyi yeniden indirmek iki tık. Öğrenmenin en iyi yolu denemek.

---

## Ne kullanıyoruz?

[Direnç.net Arduino Süper Başlangıç Seti](https://www.direnc.net/) ile çalışıyoruz: Arduino UNO, breadboard, 8×8 LED matris (1088BS), dirençler, buton, pasif buzzer, jumper kablolar ve daha fazlası.

---

## Klasör yapısı

```
haftalar/         ← Her haftanın kodları, şemaları ve belgeleri
  01-stacker/     ← 1. hafta: Stacker
  _sablon/        ← Yeni hafta şablonu (öğretmenler için)
kaynaklar/        ← Arduino rehberi, breadboard görseli, veri tipleri
arsiv/            ← Eski denemeler ve geliştirme sürecinin kayıtları
```

---

## Lisans

Kodlar [MIT lisansı](LICENSE) ile paylaşılmaktadır — kullanabilir, değiştirebilir, dağıtabilirsiniz.

Belgeler (PDF kitapçıklar, montaj kartları, görseller) [CC BY 4.0](https://creativecommons.org/licenses/by/4.0/deed.tr) ile lisanslıdır — kaynak göstererek paylaşabilirsiniz.
