# Hafta 03 — Arduino Temelleri (Matrisle, Yardımcısız)

**Tek bir LED'den tam ekrana: 12 derste, her derste tek bir yeni adım.**

Bu haftada hiçbir yardımcı dosya yok. Öğrenci `pinMode`, `digitalWrite`, `digitalRead`, `analogWrite`, `tone`, `millis` komutlarını çıplak haliyle yazar ve her komutun etkisini doğrudan LED'lerde görür.

Devre **dersten derse büyür ve hiç sökülmez.** T01'de iki kablo ve bir dirençle başlar; her derste ya tek bir parça eklenir ya da kabloya hiç dokunulmaz. T11'in sonunda devre, **01-stacker haftasındaki devrenin birebir aynısı** olur.

📄 Konu anlatımı: [Arduino Temelleri (PDF)](../../kaynaklar/Arduino_Temelleri.pdf)

---

## Matrisin tek kuralı

| | Satır pini (anot, +) | Sütun pini (katot, −) |
|---|---|---|
| LED **yanar** | `HIGH` | `LOW` |
| LED **söner** | `LOW` | `HIGH` |

> ⚠️ **Güvenlik kuralı (T04):** Bir **satırda** aynı anda en fazla **3 LED**. Satır pininde direnç yok; her LED ~13 mA çeker ve hepsi aynı pinden çıkar (pin sınırı 40 mA). Bu haftanın bütün kodları bu kurala uyuyor.

---

## Dersler

| # | Ders | Koddaki yeni kavram | Devreye eklenen | Devre bilgisi | Konu (PDF) | Devre ve montaj |
|:---:|---|---|---|---|:---:|:---:|
| T01 | [Tek LED](kod/T01_tek_led/T01_tek_led.ino) | `setup`, `loop`, `pinMode`, `digitalWrite`, `delay` | satır 1 + sütun 1 (1 direnç) | anot / katot | 2–4 | [📐 PDF](kod/T01_tek_led/T01_Devre_ve_Montaj.pdf) |
| T02 | [Değişkenle hız](kod/T02_degisken/T02_degisken.ino) | `int`, `const`, anlamlı isimler | — | Ohm yasası: 220 Ω nereden çıktı? | 7 | [📐 PDF](kod/T02_degisken/T02_Devre_ve_Montaj.pdf) |
| T03 | [İkinci LED](kod/T03_ikinci_led/T03_ikinci_led.ino) | iki çıkış, sırayla yakmak | sütun 2 hattı | yollar ayrılınca akım toplanır | 4 | [📐 PDF](kod/T03_ikinci_led/T03_Devre_ve_Montaj.pdf) |
| T04 | [Koşan ışık](kod/T04_kosan_isik/T04_kosan_isik.ino) | tekrar eden kod | sütun 3 hattı | pin sınırı: satırda en fazla 3 LED | 3 | [📐 PDF](kod/T04_kosan_isik/T04_Devre_ve_Montaj.pdf) |
| T05 | [Dizi ve for](kod/T05_dizi_ve_for/T05_dizi_ve_for.ino) | dizi `[ ]`, `for` | — | kullanılmayan pin neden LED yakmaz? | 7, 9 | [📐 PDF](kod/T05_dizi_ve_for/T05_Devre_ve_Montaj.pdf) |
| T06 | [Buton](kod/T06_buton/T06_buton.ino) | `digitalRead`, `INPUT_PULLUP`, `if / else` | GND hattı + buton | **kısa devre** | 4, 9 | [📐 PDF](kod/T06_buton/T06_Devre_ve_Montaj.pdf) |
| T07 | [Buzzer](kod/T07_buzzer/T07_buzzer.ino) | `tone`, `noTone`, frekans | pasif buzzer | ses bir titreşimdir | 11 | [📐 PDF](kod/T07_buzzer/T07_Devre_ve_Montaj.pdf) |
| T08 | [Nefes alan LED](kod/T08_nefes_alan_led/T08_nefes_alan_led.ino) | `analogWrite`, PWM | — | PWM: çok hızlı aç-kapa | 5 | [📐 PDF](kod/T08_nefes_alan_led/T08_Devre_ve_Montaj.pdf) |
| T09 | [delay mi, millis mi?](kod/T09_delay_mi_millis_mi/T09_delay_mi_millis_mi.ino) | `millis`, `unsigned long`, `bool` | — | Arduino'nun saati (16 MHz) | 6 | [📐 PDF](kod/T09_delay_mi_millis_mi/T09_Devre_ve_Montaj.pdf) |
| T10 | [İkinci satır](kod/T10_ikinci_satir/T10_ikinci_satir.ino) | kendi fonksiyonun, parametre | satır 2 kablosu | hayalet LED, göz yanılması | 10 | [📐 PDF](kod/T10_ikinci_satir/T10_Devre_ve_Montaj.pdf) |
| T11 | [Tam matris](kod/T11_tam_matris/T11_tam_matris.ino) | iç içe `for`, iki boyut | kalan 6 satır + 5 sütun | sütun boyunca güvenli, satır boyunca değil | 9 | [📐 PDF](kod/T11_tam_matris/T11_Devre_ve_Montaj.pdf) |
| T12 | [Kendi ekranını sür](kod/T12_kendi_ekranin/T12_kendi_ekranin.ino) | resmi veri olarak saklamak, tarama | — | tarama hızı ve parlaklık | 10 | [📐 PDF](kod/T12_kendi_ekranin/T12_Devre_ve_Montaj.pdf) |

**T12 köprü derstir:** 02. haftadaki `matris.h`'nin arka planda yaptığı iş (satır satır, 3'erli parçalarla tarama) artık öğrencinin kendi yazdığı koddur.

---

## Her ders klasöründe

- **`.ino` kodu:** başında dersin anlatımı ve **9. sınıf** (2 görev) ile **10. sınıf** (1 görev) görevleri.
- **Devre ve montaj PDF'i:**
  - mantıksal devre şeması,
  - **bugünün devre bilgisi** (anot/katot, Ohm, akım toplanması, pin sınırı, kısa devre…),
  - tasarım gerekçeleri,
  - breadboard yerleşimi ve bağlantı tablosu (bu derste eklenenler işaretli),
  - resimli adım adım montaj (önceki derslerden kalanlar soluk, yeni parça parlak),
  - akımın yolu, kontrol listesi ve hata tablosu.

**Breadboard çizimleri 01-stacker montaj kartıyla aynı dilde:**

- Kırmızı satır kabloları dümdüz Arduino'ya gider.
- Dirençli sütun hatları iç içe dikdörtgenler çizer: en soldaki bacak en dıştaki şeride çıkar.
- Hiçbir kablo bir diğerinin üstünden geçmez.
- Oklar akımın yönünü gösterir.

**Mavi "Kelimenin hikâyesi" kutuları** bir terimin kökenini ve o kökenden çıkan mantığı ~1 dakikada anlatır: anot/katot, direnç/ohm, paralel, algoritma, kısa devre, GND, pull-up, PWM, bit/bayt, matris, piksel ve diğerleri.

Görev çözümleri: [cevaplar/03-arduino-temelleri](../../cevaplar/03-arduino-temelleri)

---

## Sık karşılaşılan sorunlar

| Belirti | Muhtemel sebep | Çözüm |
|---|---|---|
| LED hiç yanmıyor | Satır ve sütun pini karıştı | Satır `HIGH`, sütun `LOW` olmalı |
| LED çok sönük | `pinMode(..., OUTPUT)` unutuldu | `setup()` içine ekle |
| Başka LED'ler de yanıyor (T10 sonrası) | Önceki LED söndürülmeden yenisi yakıldı | Önce `hepsiniSondur()` çağır |
| T08'de LED ters davranıyor | LED sütun pininde, mantık ters | `255 - parlaklik` kullan |
| Buton rastgele okunuyor | `INPUT` kullanıldı | `INPUT_PULLUP` yap |

Genel sorunlar için → [Sorun giderme](../../SORUN-GIDERME.md)

---

← [Ana sayfa](../../README.md) · [Başlarken](../../BASLARKEN.md) · [Sorun giderme](../../SORUN-GIDERME.md) · [Sözlük](../../SOZLUK.md)
