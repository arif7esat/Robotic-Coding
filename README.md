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

## 🖥️ Evde dene: Wokwi simülasyonları

Kiti eve götüremiyor musun? Dersin devresi ve kodu tarayıcıda hazır. **Hesap açmana gerek yok.**

**Her derste iki bağlantı var:**

| Bağlantı | Ne açılır? | Ne zaman kullanırım? |
|---|---|---|
| 🟢 **Ders kodu** | O dersin devresi + derste yüklediğimiz kod (`Adim2_Kod`) | Dersi tekrar etmek, **görevleri kendin denemek** için. Kodu değiştir, ▶ ile çalıştır. |
| 🟣 **Görev çözümü** | Aynı devre + görevlerin cevap kodu (`Adim4_Cevap`) | Görevi **denedikten sonra** kendi çözümünü karşılaştırmak için. En üstteki `const int GOREV = 1;` satırında sayıyı **1, 2 ya da 3** yap, ▶'ya bas. |

**Nasıl kullanılır?**
1. Bağlantıyı aç, sağ üstteki yeşil **▶** tuşuna bas. İlk çalıştırmada derleme **10–20 saniye** sürebilir, bekle.
2. Kodu soldaki pencerede değiştir, ▶ ile yeniden çalıştır. Buton olan derslerde butona fareyle tıkla.
3. **Bir şeyi bozdun mu? Sayfayı yenile.** Devre ve kod ilk haline döner; değişikliklerin başkasını etkilemez.

**Ekranda ne görüyorum?** Matrisin "kutusunu açtık": 64 LED tek tek görünüyor. **Kırmızı yatay teller = satır = LED'in A + (anot) bacağı**, **mavi dikey teller = sütun = LED'in K − (katot) bacağı**. Her derste sadece o derste kurduğumuz kablolar bağlı; bağlı olmayan LED'ler yanmaz. Breadboard delikleri (j8, a7…) simülasyonda yok; montajı sınıfta yapıyoruz.

### 1. Bölüm · Arduino Temelleri

| Ders | 🟢 Ders kodu: derste yüklediğin kod | 🟣 Görev çözümü: görevlerin cevap kodu | Devre dosyaları |
|---|:---:|:---:|:---:|
| **T01** · Tek LED | [▶ Aç](https://wokwi.com/projects/477911568675575809) | [▶ Aç](https://wokwi.com/projects/477912466272732161) | [klasör](wokwi-evde-dene/1-arduino-temelleri/T01_tek_led/) |
| **T02** · Değişkenle hız | [▶ Aç](https://wokwi.com/projects/477911947229486081) | [▶ Aç](https://wokwi.com/projects/477912480863673345) | [klasör](wokwi-evde-dene/1-arduino-temelleri/T02_degisken/) |
| **T03** · İkinci LED | [▶ Aç](https://wokwi.com/projects/477911977989474305) | [▶ Aç](https://wokwi.com/projects/477912500554888193) | [klasör](wokwi-evde-dene/1-arduino-temelleri/T03_ikinci_led/) |
| **T04** · Koşan ışık | [▶ Aç](https://wokwi.com/projects/477912005408700417) | [▶ Aç](https://wokwi.com/projects/477912518320916481) | [klasör](wokwi-evde-dene/1-arduino-temelleri/T04_kosan_isik/) |
| **T05** · Dizi ve for | [▶ Aç](https://wokwi.com/projects/477912032382283777) | [▶ Aç](https://wokwi.com/projects/477912536072273921) | [klasör](wokwi-evde-dene/1-arduino-temelleri/T05_dizi_ve_for/) |
| **T06** · Buton | [▶ Aç](https://wokwi.com/projects/477912057764125697) | [▶ Aç](https://wokwi.com/projects/477912554994888705) | [klasör](wokwi-evde-dene/1-arduino-temelleri/T06_buton/) |
| **T07** · Buzzer | [▶ Aç](https://wokwi.com/projects/477912077893657601) | [▶ Aç](https://wokwi.com/projects/477912806888144897) | [klasör](wokwi-evde-dene/1-arduino-temelleri/T07_buzzer/) |
| **T08** · Nefes alan LED | [▶ Aç](https://wokwi.com/projects/477912099218556929) | [▶ Aç](https://wokwi.com/projects/477912840252806145) | [klasör](wokwi-evde-dene/1-arduino-temelleri/T08_nefes_alan_led/) |
| **T09** · delay mi, millis mi? | [▶ Aç](https://wokwi.com/projects/477912113402648577) | [▶ Aç](https://wokwi.com/projects/477912873728619521) | [klasör](wokwi-evde-dene/1-arduino-temelleri/T09_delay_mi_millis_mi/) |
| **T10** · İkinci satır | [▶ Aç](https://wokwi.com/projects/477912132410192897) | [▶ Aç](https://wokwi.com/projects/477912906927595521) | [klasör](wokwi-evde-dene/1-arduino-temelleri/T10_ikinci_satir/) |
| **T11** · Tam matris | [▶ Aç](https://wokwi.com/projects/477912146730600449) | [▶ Aç](https://wokwi.com/projects/477912945708143617) | [klasör](wokwi-evde-dene/1-arduino-temelleri/T11_tam_matris/) |
| **T12** · Kendi ekranını sür | [▶ Aç](https://wokwi.com/projects/477912175490952193) | [▶ Aç](https://wokwi.com/projects/477912988664126465) | [klasör](wokwi-evde-dene/1-arduino-temelleri/T12_kendi_ekranin/) |

Ayrıntılar ve devre dosyaları → [wokwi-evde-dene/](wokwi-evde-dene/)

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
wokwi-evde-dene/            ← tarayıcıda simülasyon: her dersin devresi (ders + görev çözümü)
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
