# Hafta 02 — Matris ile Kodlama

**Stacker'ı yapmadan önce: 8x8 matrisle adım adım kodlamanın temellerini öğreniyoruz.**

Devre **01-stacker haftasındaki devrenin aynısı** (matris + buton A4 + buzzer A5). Kablolara dokunmadan sadece kod değişir.

---

## Nasıl çalışıyor?

Her proje klasöründe iki dosya var:

| Dosya | Ne işe yarar? |
|---|---|
| `pX_....ino` | Öğrencinin kodu. Kısa ve okunur. |
| `matris.h` | Yardımcı dosya. Matrisi arka planda sürekli yeniler. **Dokunulmaz.** |

`.ino` dosyasını Arduino IDE'de açınca `matris.h` yan sekmede kendiliğinden görünür. Bu sayede öğrenciler çoklama (multiplexing) ile uğraşmadan `ledYak(3, 4);` yazıp `delay()` ile rahatça bekleyebilir.

> Ekran yan veya ters görünüyorsa: `matrisBaslat();` yerine `matrisBaslat(90);` (veya 180, 270) yaz.
> Ayna gibi ters görünüyorsa: `matrisBaslat(0, true);`

---

## Komut kartı

Koordinat: **x = sütun** (0 en sol → 7 en sağ), **y = satır** (0 en alt → 7 en üst)

| Komut | Ne yapar? |
|---|---|
| `matrisBaslat();` | Matrisi hazırlar. `setup()` içinde ilk satır. |
| `ledYak(x, y);` | O noktadaki LED'i yakar |
| `ledSondur(x, y);` | O noktadaki LED'i söndürür |
| `ledYanikMi(x, y)` | LED yanıyorsa `true` |
| `ekraniTemizle();` | Hepsini söndürür |
| `ekraniDoldur();` | Hepsini yakar |
| `resimCiz(RESIM);` | `#` ve `.` ile çizilmiş resmi gösterir |
| `butonaBasiliMi()` | Buton şu an basılıysa `true` |
| `butonaBasildi()` | Butona **yeni** basıldıysa `true` (bir kez) |
| `bekleBasildiMi(ms)` | `ms` kadar bekler; bu sırada basılırsa hemen `true` |
| `bip(frekans, sure);` | Buzzer'dan ses |

---

## Projeler (kolaydan zora)

| # | Proje | Yeni öğrenilen kavram |
|:---:|---|---|
| 1 | [İlk Işık](kod/p1_ilk_isik/p1_ilk_isik.ino) | `setup`/`loop`, komut çağırmak, koordinat, `delay` |
| 2 | [Yürüyen Nokta](kod/p2_yuruyen_nokta/p2_yuruyen_nokta.ino) | Değişken, `x = x + 1`, `if` |
| 3 | [Çizgi Çiz](kod/p3_cizgi_ciz/p3_cizgi_ciz.ino) | `for` döngüsü, iç içe döngü |
| 4 | [Emoji ve Animasyon](kod/p4_emoji_animasyon/p4_emoji_animasyon.ino) | Dizi (resim), animasyon kareleri |
| 5 | [Butonlu Yüz](kod/p5_butonlu_yuz/p5_butonlu_yuz.ino) | Giriş (buton), `if / else` |
| 6 | [Tıklama Sayacı](kod/p6_tiklama_sayaci/p6_tiklama_sayaci.ino) | Sayaç, `/` ve `%`, Seri Monitör |
| 7 | [Elektronik Zar](kod/p7_zar/p7_zar.ino) | Kendi fonksiyonunu yazmak, `random`, `else if` |
| 8 | [Ortaya Durdur](kod/p8_ortaya_durdur/p8_ortaya_durdur.ino) | Hepsini birleştiren ilk oyun → Stacker'a köprü |

Her `.ino` dosyasının başında **9. sınıf** ve **10. sınıf** için ayrı görevler var. 9. sınıf görevleri çoğunlukla bir sayıyı/satırı değiştirmek; 10. sınıf görevleri yeni kod yazmayı gerektirir.

---

## Sık karşılaşılan sorunlar

| Belirti | Muhtemel sebep | Çözüm |
|---|---|---|
| `matris.h: No such file` | `.ino` dosyası tek başına kopyalanmış | Klasörü `matris.h` ile birlikte kopyala |
| `'ledYak' was not declared` | `#include "matris.h"` satırı silinmiş | En üste geri ekle |
| Hiç LED yanmıyor | `matrisBaslat();` unutulmuş | `setup()` içine ilk satır olarak ekle |
| Resim yan duruyor | Matris breadboard'a farklı yönde takılı | `matrisBaslat(90);` dene |
| Kod değişti ama ekran aynı | Yükleme yapılmadı | Yükle (→) butonuna bas |

Genel sorunlar için → [Sorun giderme](../../SORUN-GIDERME.md)

---

## İleri okuma

- 📄 [Kodların mantığı — öğretmen için detaylı açıklama (PDF)](belgeler/Matris_ile_Kodlama_Kod_Mantigi.pdf)

---

← [Ana sayfa](../../README.md) · [Başlarken](../../BASLARKEN.md) · [Sorun giderme](../../SORUN-GIDERME.md) · [Sözlük](../../SOZLUK.md)
