# 🎮 Arduino Atölyesi

Kitaptaki "LED yak, LED söndür" alıştırmalarıyla yetinmiyoruz. Tek bir LED'den başlayıp adım adım AVM'deki oyun makinesine kadar gidiyoruz: kendin kurup kendin oynayabileceğin projeler.

Derste kaçırdın mı? Evde yeniden kurmak mı istiyorsun? Aşağıdaki yol haritasında kaldığın yeri bul. Her bölümde devre şeması, yükleyeceğin kod ve sık karşılaşılan sorunlar var.

---

## 🧭 Yol haritası

Bölümleri **sırayla** takip et. Devre 1. bölümde adım adım kurulur, sonra hiç sökülmez: 2. ve 3. bölümde sadece kod değişir.

| Bölüm | Ne yapıyoruz? | Ders sayısı | Seviye |
|:---:|---|:---:|:---:|
| **1** | [**Arduino Temelleri**](1-arduino-temelleri/): tek LED'den tam 8×8 ekrana. `pinMode`, `digitalWrite`, buton, buzzer, PWM, `millis` | T01 → T12 | ★☆☆ |
| **2** | [**Matris ile Kodlama**](2-matris-ile-kodlama/): hazır `matris.h` ile değişken, döngü, dizi, fonksiyon. Emoji, zar, ilk oyun | P1 → P8 | ★★☆ |
| **3** | [**Stacker**](3-stacker/): kule dikme oyunu. Hepsini birleştiren final projesi | 1 oyun | ★★★ |

> İlk kez mi buradasın? → [Başlarken](rehber/BASLARKEN.md): Arduino IDE'yi kur, kodu indir, karta yükle.
>
> Bir şey çalışmıyor mu? → [Sorun giderme](rehber/SORUN-GIDERME.md)
>
> Bir kelimeyi bilmiyor musun? → [Sözlük](rehber/SOZLUK.md)

---

## 📁 Klasör yapısı

```
1-arduino-temelleri/        ← 1. bölüm
   T01_tek_led/                ← her ders tek klasör, içinde 4 adım:
      Adim1_Dokuman_T01.pdf       devreyi kur + kodun mantığı
      Adim2_Kod_T01/              yükleyeceğin kod
      Adim3_Gorev_T01.pdf         görevlerin
      Adim4_Cevap_Dokuman_T01.pdf görev çözümlerinin mantığı
      Adim4_Cevap_T01/            görevlerin cevap kodu
   T02_degisken/
   ...
2-matris-ile-kodlama/       ← 2. bölüm
   p1_ilk_isik/                ← ders
   p1_ilk_isik_cevap/          ← hemen altında: o dersin görev cevapları
   ...
3-stacker/                  ← 3. bölüm: oyun kodları + kitapçık PDF'leri
rehber/                     ← Başlarken, Sorun giderme, Sözlük, Arduino rehberleri
arsiv/                      ← eski denemeler (derste kullanılmıyor)
```

**Kural basit:** Bölüm klasörüne gir → dersin klasörüne gir → **Adım 1, 2, 3, 4** sırayla. Her bölümün README'si o bölümdeki derslerin tablosunu, devre PDF'lerini ve cevaplarını tek sayfada gösterir.

---

## Kodu nasıl indiririm?

**Bilgisayardan:**
1. Bu sayfanın üstündeki yeşil **Code** butonuna tıkla → **Download ZIP**.
2. ZIP'i aç. Bölümün klasörüne, sonra dersin klasörüne gir; `.ino` dosyasını çift tıkla. Arduino IDE açılır.

**Telefondan (sadece görmek için):**
1. Yüklemek istediğin `.ino` dosyasına git.
2. **Raw** butonuna bas → kodun tamamını göreceksin. Kopyalayıp bilgisayara yapıştırabilirsin.

> **Bu kodları değiştirmekten korkma.** Değiştirir, bozarsın, geri alırsın. Her şeyi yeniden indirmek iki tık. Öğrenmenin en iyi yolu denemek.

---

## Ne kullanıyoruz?

[Direnç.net Arduino Süper Başlangıç Seti](https://www.direnc.net/) ile çalışıyoruz: Arduino UNO, breadboard, 8×8 LED matris (1088BS), dirençler, buton, pasif buzzer, jumper kablolar ve daha fazlası.

---

## Lisans

Kodlar [MIT lisansı](LICENSE) ile paylaşılmaktadır: kullanabilir, değiştirebilir, dağıtabilirsiniz.

Belgeler (PDF kitapçıklar, montaj kartları, görseller) [CC BY 4.0](https://creativecommons.org/licenses/by/4.0/deed.tr) ile lisanslıdır: kaynak göstererek paylaşabilirsiniz.
