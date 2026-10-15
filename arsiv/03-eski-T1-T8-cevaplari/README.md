# Eski T1–T8 serisinin cevapları

> **Bu cevaplar güncel derslerle uyuşmaz.** Arduino Temelleri serisi T01–T12 olarak yeniden yazıldı; buradaki dosyalar kaldırılan eski T1–T8 serisinin görevlerine aittir. Güncel dersler → [1-arduino-temelleri/](../../1-arduino-temelleri/)
>
> Eski serinin ders kodları ve PDF'leri git geçmişinde duruyor (`e360bb1` öncesi).

## Nasıl kullanılır?

Her dosyanın en üstündeki satırı değiştirip yükle:

```cpp
const int GOREV = 1;     // <-- görev numarası
```

Kod gerektirmeyen soruların cevapları dosyanın başındaki **SORULARIN CEVAPLARI** bölümünde yazılı.

## Ek kablo gereken görevler

| Görev | Eklenecek hat |
|---|---|
| T1 · görev 2 | Satır 8: a9 → D6 · Sütun 8: j5 → j41, direnç i41–i45, j45 → D10 |
| T1 · görev 4 | Sütun 2: a7 → b29, direnç d29–d33, b33 → D4 |
| T6 · görev 4 | Buton: d47 d49 g47 g49 · b47 → A4 · h49 → − · Arduino GND → − |
| T6 · görev 5 | Sütun 7: j6 → j35, direnç i35–i39, j39 → D11 |
| T7 · görev 3 | Sütun 4: j11 → j17, direnç i17–i21, j21 → A2 |
| T8 · görev 4 | Bütün matris (T2 devresi) |
