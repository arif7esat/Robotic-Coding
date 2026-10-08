# Cevaplar — Görev Çözümleri (Öğretmen için)

02 ve 03 haftalarındaki her `.ino` dosyasının başındaki **9. sınıf** ve **10. sınıf** görevlerinin çözümleri.

## Nasıl kullanılır?

Her proje için **tek bir cevap dosyası** var. Dosyanın en üstündeki satırı değiştirip yükle:

```cpp
const int GOREV = 1;     // <-- görev numarası
```

- Kod gerektirmeyen sorular ("Ne oldu? Neden?") dosyanın başındaki **SORULARIN CEVAPLARI** bölümünde yazılı.
- 02 haftasının cevap klasörlerinde `matris.h` de var; klasörü bütün olarak kopyala.
- Hepsi Arduino UNO için derlenip kontrol edildi.

## Ek kablo gereken görevler (03 haftası)

03 haftasının devreleri her proje için en küçük haliyle kuruluyor. Bazı görevler o devrede olmayan bir hatta ihtiyaç duyar; delik numaraları cevap dosyasının başında da yazıyor.

| Görev | Eklenecek hat |
|---|---|
| T1 · görev 2 | Satır 8: a9 → D6 · Sütun 8: j5 → j41, direnç i41–i45, j45 → D10 |
| T1 · görev 4 | Sütun 2: a7 → b29, direnç d29–d33, b33 → D4 |
| T6 · görev 4 | Buton: d47 d49 g47 g49 · b47 → A4 · h49 → − · Arduino GND → − |
| T6 · görev 5 | Sütun 7: j6 → j35, direnç i35–i39, j39 → D11 |
| T7 · görev 3 | Sütun 4: j11 → j17, direnç i17–i21, j21 → A2 |
| T8 · görev 4 | Bütün matris (T2 devresi) |

02 haftasında P5 · görev 2 ses çıkardığı için buzzer gerekir (P6 devresi).

## Klasörler

| Hafta | Cevap dosyaları |
|---|---|
| [02-matris-ile-kodlama](02-matris-ile-kodlama) | p1_cevaplar … p8_cevaplar |
| [03-arduino-temelleri](03-arduino-temelleri) | t1_cevaplar … t8_cevaplar |

> Öğrencilere vermeden önce: görevlerin amacı denemek ve yanılmak. Cevabı göstermek yerine önce ipucu (dosyalardaki "İpucu" satırları) vermek daha öğretici.
