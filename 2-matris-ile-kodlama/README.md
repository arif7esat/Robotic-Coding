# Bölüm 2 — Matris ile Kodlama

> 🧭 **Buradasın:** 1. Temeller → **2. Matris ile Kodlama** → 3. Stacker

**Stacker'ı yapmadan önce: 8x8 matrisle adım adım kodlamanın temellerini öğreniyoruz.**

Devre, **1. bölümün sonunda (T11) kurduğun devrenin aynısı**; bu aynı zamanda [3-stacker](../3-stacker/) devresi (matris + buton A4 + buzzer A5). Kablolara dokunmadan sadece kod değişir.

---

## Nasıl çalışıyor?

Her proje klasöründe şu dosyalar var:

| Dosya | Ne işe yarar? |
|---|---|
| `pX_....ino` | Öğrencinin kodu. Kısa ve okunur. |
| `matris.h` | Yardımcı dosya. Matrisi arka planda sürekli yeniler. **Dokunulmaz.** |
| `PX_Devre_ve_Montaj.pdf` | O projenin devresi ve resimli montajı. |

Her projenin hemen altında aynı adla biten bir **`_cevap`** klasörü durur (ör. `p1_ilk_isik` → `p1_ilk_isik_cevap`). İçinde o projenin görev çözümleri var.

`.ino` dosyasını Arduino IDE'de açınca `matris.h` yan sekmede kendiliğinden görünür. Bu sayede öğrenciler 1. bölümün T12 dersinde elle yazdıkları çoklama (multiplexing) koduyla uğraşmadan `ledYak(3, 4);` yazıp `delay()` ile rahatça bekleyebilir.

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

| # | Proje | Yeni öğrenilen kavram | Devre ve montaj | Cevaplar |
|:---:|---|---|:---:|:---:|
| 1 | [İlk Işık](p1_ilk_isik/p1_ilk_isik.ino) | `setup`/`loop`, komut çağırmak, koordinat, `delay` | [📐 PDF](p1_ilk_isik/P1_Devre_ve_Montaj.pdf) | [✅ Cevap](p1_ilk_isik_cevap/p1_ilk_isik_cevap.ino) |
| 2 | [Yürüyen Nokta](p2_yuruyen_nokta/p2_yuruyen_nokta.ino) | Değişken, `x = x + 1`, `if` | [📐 PDF](p2_yuruyen_nokta/P2_Devre_ve_Montaj.pdf) | [✅ Cevap](p2_yuruyen_nokta_cevap/p2_yuruyen_nokta_cevap.ino) |
| 3 | [Çizgi Çiz](p3_cizgi_ciz/p3_cizgi_ciz.ino) | `for` döngüsü, iç içe döngü | [📐 PDF](p3_cizgi_ciz/P3_Devre_ve_Montaj.pdf) | [✅ Cevap](p3_cizgi_ciz_cevap/p3_cizgi_ciz_cevap.ino) |
| 4 | [Emoji ve Animasyon](p4_emoji_animasyon/p4_emoji_animasyon.ino) | Dizi (resim), animasyon kareleri | [📐 PDF](p4_emoji_animasyon/P4_Devre_ve_Montaj.pdf) | [✅ Cevap](p4_emoji_animasyon_cevap/p4_emoji_animasyon_cevap.ino) |
| 5 | [Butonlu Yüz](p5_butonlu_yuz/p5_butonlu_yuz.ino) | Giriş (buton), `if / else` | [📐 PDF](p5_butonlu_yuz/P5_Devre_ve_Montaj.pdf) | [✅ Cevap](p5_butonlu_yuz_cevap/p5_butonlu_yuz_cevap.ino) |
| 6 | [Tıklama Sayacı](p6_tiklama_sayaci/p6_tiklama_sayaci.ino) | Sayaç, `/` ve `%`, Seri Monitör | [📐 PDF](p6_tiklama_sayaci/P6_Devre_ve_Montaj.pdf) | [✅ Cevap](p6_tiklama_sayaci_cevap/p6_tiklama_sayaci_cevap.ino) |
| 7 | [Elektronik Zar](p7_zar/p7_zar.ino) | Kendi fonksiyonunu yazmak, `random`, `else if` | [📐 PDF](p7_zar/P7_Devre_ve_Montaj.pdf) | [✅ Cevap](p7_zar_cevap/p7_zar_cevap.ino) |
| 8 | [Ortaya Durdur](p8_ortaya_durdur/p8_ortaya_durdur.ino) | Hepsini birleştiren ilk oyun → Stacker'a köprü | [📐 PDF](p8_ortaya_durdur/P8_Devre_ve_Montaj.pdf) | [✅ Cevap](p8_ortaya_durdur_cevap/p8_ortaya_durdur_cevap.ino) |

> 🔌 **1. bölümü bitirdiysen hiçbir şeyi sökme:** devren zaten tam (matris + buton + buzzer). Aşağıdaki P PDF'lerinin montaj kısmını atla; o PDF'ler bu bölüme sıfırdan başlayanlar için.
>
> ⚠️ **ledYak farkı:** `matris.h`'te `ledYak(x, y)` sırası **(sütun, satır)** ve (0, 0) **sol alt** köşedir. 1. bölümdeki (T10–T12) kendi `ledYak(s, k)`'mizde önce satır gelir ve (0, 0) sol üsttür.

Her proje klasöründe, **sadece o projenin kullandığı parçalarla** (matris her zaman tam; buton ve buzzer sadece kullanılan projelerde) ayrı bir devre PDF'i var: şema, tasarım gerekçeleri, breadboard yerleşimi, resimli adım adım montaj, akımın yolu, kontrol listesi ve mavi "Kelimenin hikâyesi" kutuları.

Her `.ino` dosyasının başında **9. sınıf** ve **10. sınıf** için ayrı görevler var. 9. sınıf görevleri çoğunlukla bir sayıyı/satırı değiştirmek; 10. sınıf görevleri yeni kod yazmayı gerektirir.

---

## Cevaplar nasıl kullanılır? (öğretmen için)

Her `_cevap` klasöründe **tek bir cevap dosyası** var. En üstteki satırı değiştirip yükle:

```cpp
const int GOREV = 1;     // <-- görev numarası
```

- Kod gerektirmeyen soruların ("Ne oldu? Neden?") cevapları dosyanın başındaki **SORULARIN CEVAPLARI** bölümünde yazılı.
- Cevap klasörlerinde de `matris.h` var; klasörü bütün olarak kopyala.
- Hepsi Arduino UNO için derlenip kontrol edildi.

> Öğrencilere vermeden önce: görevlerin amacı denemek ve yanılmak. Cevabı göstermek yerine önce ipucu (dosyalardaki "İpucu" satırları) vermek daha öğretici.

---

## Sık karşılaşılan sorunlar

| Belirti | Muhtemel sebep | Çözüm |
|---|---|---|
| `matris.h: No such file` | `.ino` dosyası tek başına kopyalanmış | Klasörü `matris.h` ile birlikte kopyala |
| `'ledYak' was not declared` | `#include "matris.h"` satırı silinmiş | En üste geri ekle |
| Hiç LED yanmıyor | `matrisBaslat();` unutulmuş | `setup()` içine ilk satır olarak ekle |
| Resim yan duruyor | Matris breadboard'a farklı yönde takılı | `matrisBaslat(90);` dene |
| Kod değişti ama ekran aynı | Yükleme yapılmadı | Yükle (→) butonuna bas |

Genel sorunlar için → [Sorun giderme](../rehber/SORUN-GIDERME.md)

---

## İleri okuma

- 📄 [Kodların mantığı — öğretmen için detaylı açıklama (PDF)](Matris_ile_Kodlama_Kod_Mantigi.pdf)

> PDF başlıklarında yazan **"Hafta 02"** bu bölümün eski adıdır.

---

**← Önceki bölüm** [1. Arduino Temelleri](../1-arduino-temelleri/) · **Sonraki bölüm →** [3. Stacker](../3-stacker/)

← [Ana sayfa](../README.md) · [Başlarken](../rehber/BASLARKEN.md) · [Sorun giderme](../rehber/SORUN-GIDERME.md) · [Sözlük](../rehber/SOZLUK.md)
