# Hafta 03 — Arduino Temelleri (Matrisle, Yardımcısız)

**Aynı matris devresinde, `matris.h` olmadan: her komutun etkisini doğrudan LED'lerde görüyoruz.**

Devre **01-stacker haftasındaki devrenin aynısı**. Bu haftanın farkı: hiçbir yardımcı dosya yok. Öğrenci `pinMode`, `digitalWrite`, `digitalRead`, `analogWrite`, `tone`, `millis` komutlarını çıplak haliyle yazıyor.

📄 Konu anlatımı: [Arduino Temelleri (PDF)](../../kaynaklar/Arduino_Temelleri.pdf)

---

## Matrisin tek kuralı

| | Satır pini | Sütun pini |
|---|---|---|
| LED **yanar** | `HIGH` | `LOW` |
| LED **söner** | `LOW` | `HIGH` |

```cpp
const int SATIR[8] = {A3, 12, 9, A0, 2, 8, 3, 6};    // satır 1..8 (üstten alta)
const int SUTUN[8] = {13, 4, 5, A2, 7, A1, 11, 10};  // sütun 1..8 (soldan sağa)
```

> ⚠️ **Güvenlik kuralı:** Bir **satırın** birden çok LED'ini aynı anda yakma. Satır pinlerinde direnç yok; 8 LED birden ~100 mA çeker ve pini bozar. Bir **sütunu** boydan boya yakmak ise güvenli, çünkü sütundaki direnç akımı sınırlar (T3'te bunu gözle görüyoruz). Bu haftanın bütün kodları bu kurala uyuyor.

---

## Projeler

| # | Proje | Komutlar / kavram | Konu (PDF) | Devre ve montaj |
|:---:|---|---|:---:|:---:|
| T1 | [Tek LED](kod/t1_tek_led/t1_tek_led.ino) | `pinMode`, `digitalWrite`, `delay` | 2–4 | [📐 PDF](kod/t1_tek_led/T1_Devre_ve_Montaj.pdf) |
| T2 | [Dizi ile LED seç](kod/t2_dizi_ile_led/t2_dizi_ile_led.ino) | dizi, `const`, `for`, kendi fonksiyonun | 7, 9, 10 | [📐 PDF](kod/t2_dizi_ile_led/T2_Devre_ve_Montaj.pdf) |
| T3 | [Sütun ve akım](kod/t3_sutun_ve_akim/t3_sutun_ve_akim.ino) | iç içe `for`, akım paylaşımı, güvenlik | 3, 9 | [📐 PDF](kod/t3_sutun_ve_akim/T3_Devre_ve_Montaj.pdf) |
| T4 | [Butonu oku](kod/t4_buton_oku/t4_buton_oku.ino) | `digitalRead`, `INPUT_PULLUP`, `Serial` | 4, 11 | [📐 PDF](kod/t4_buton_oku/T4_Devre_ve_Montaj.pdf) |
| T5 | [Işıklı piyano](kod/t5_buzzer_piyano/t5_buzzer_piyano.ino) | `tone`, dizi, ses + ışık | 7, 11 | [📐 PDF](kod/t5_buzzer_piyano/T5_Devre_ve_Montaj.pdf) |
| T6 | [Nefes alan LED](kod/t6_pwm_parlaklik/t6_pwm_parlaklik.ino) | `analogWrite`, PWM, ters mantık | 5 | [📐 PDF](kod/t6_pwm_parlaklik/T6_Devre_ve_Montaj.pdf) |
| T7 | [delay mi, millis mi?](kod/t7_millis_ile_bekleme/t7_millis_ile_bekleme.ino) | `millis`, `unsigned long`, `bool` | 6 | [📐 PDF](kod/t7_millis_ile_bekleme/T7_Devre_ve_Montaj.pdf) |
| T8 | [Göz yanılması](kod/t8_goz_yanilmasi/t8_goz_yanilmasi.ino) | çoklama, görme sürekliliği | — | [📐 PDF](kod/t8_goz_yanilmasi/T8_Devre_ve_Montaj.pdf) |

Her proje klasöründe, **sadece o kodun kullandığı parçalarla** kurulan ayrı bir devre PDF'i var: mantıksal şema, tasarım gerekçeleri, breadboard yerleşimi, resimli adım adım montaj, akımın yolu, kontrol listesi ve hata tablosu.

Her dosyanın başında **9. sınıf** ve **10. sınıf** görevleri var. T4, T7 ve T8'de öğrencinin tek bir değeri değiştirip farkı gözlemlediği **deneyler** var.

**T8 köprü projedir:** Öğrenci matrisin aslında satır satır, çok hızlı yanıp söndüğünü kendi gözüyle keşfeder. 02. haftadaki `matris.h`'nin arka planda yaptığı iş tam olarak budur.

---

## Sık karşılaşılan sorunlar

| Belirti | Muhtemel sebep | Çözüm |
|---|---|---|
| LED hiç yanmıyor | Satır ve sütun pini karıştı | Satır `HIGH`, sütun `LOW` olmalı |
| LED çok sönük | `pinMode(..., OUTPUT)` unutuldu | `setup()` içine ekle |
| Başka LED'ler de yanıyor | Önceki LED söndürülmeden yenisi yakıldı | Önce `hepsiniSondur()` çağır |
| T6'da LED ters davranıyor | LED sütun pininde, mantık ters | `255 - parlaklik` kullan |
| Buton rastgele okunuyor | `INPUT` kullanıldı | `INPUT_PULLUP` yap |

Genel sorunlar için → [Sorun giderme](../../SORUN-GIDERME.md)

---

← [Ana sayfa](../../README.md) · [Başlarken](../../BASLARKEN.md) · [Sorun giderme](../../SORUN-GIDERME.md) · [Sözlük](../../SOZLUK.md)
