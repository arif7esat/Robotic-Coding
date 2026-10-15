Perşembe Arduino dersi · 1088BS 8×8 matris · Arduino UNO

# Stacker montaj kartı

Breadboard yatay, **1 numara solda**. Senden uzaktan yakına: − + | j i h g f | e d c b a | − +. Matrisin her bacağına, aynı sütundaki **a** (sana yakın) ya da **j** (uzak) deliğinden bağlanılır.

## Breadboard şeması

Matrisin "1088BS" yazısı sana (a tarafına) bakar. Sol baştaki bacak b5'e girer. Dirençler matrisin sağında yatay durur. Soldaki delikten çıkan turuncu kablo en uzaktaki dirence gider, böylece kablolar birbirinin üstünden geçmez. Sette olan 30 erkek-erkek kablonun 29'u kullanılır, dişi-erkek kablo gerekmez.

**Akımın yolu:** Arduino satır pini (HIGH) → kırmızı kablo → matris satırı → LED → matris sütunu → turuncu kablo → direnç → sarı kablo → Arduino sütun pini (LOW)

**Kırmızı** · satır kablosu\
Arduino → matris. 8 adet, dirençsiz.

**Turuncu** · sütun kablosu\
Matris → direnç. 8 adet.

**Direnç** · 220 Ω\
Kırmızı-kırmızı-kahverengi halkalı.

**Sarı** · dönüş kablosu\
Direnç → Arduino. 8 adet.

**Siyah** · GND\
Arduino GND, buton, buzzer. 3 adet.

**Yeşil** · buton → A4

**Mavi** · buzzer → A5

Her rengin açık ve koyu tonu var: yan yana kablolar farklı tonda çizildi, karışmasın diye. Turuncu kabloların üstündeki küçük etiket, kablonun hangi delikten geldiğini gösterir. Sette her renkten yeterli kablo olmayabilir. Renkler şemayı okumak için; gerçekte aynı gruptaki kabloları mümkün olduğunca aynı renkte tutman yeterli.

## Tek kural: soldan sağa sırayla

Alt sıra · a5 → a12**D2 · D3 · D4 · D5 · D6 · D7 · D8 · D9**

Üst sıra · j5 → j12**D10 · D11 · D12 · D13 · A0 · A1 · A2 · A3**

Direnç takılan 8 delik**a7 · a8 · a10 · j5 · j6 · j8 · j10 · j11**

| Delik | Yol | Arduino |
| --- | --- | --- |

| Delik | Yol | Arduino |
| --- | --- | --- |

3 kişilik grup · herkes aynı anda çalışır

## Rol kartları

Rol 1

### Matrisçi

- Matrisi tak: yazı sana baksın, bacaklar b5–b12 ve i5–i12.
- Düz kablolar: a5→D2, a6→D3, a9→D6, a11→D8, a12→D9
- j7→D12, j9→A0, j12→A3
- Arduino GND → en üstteki − hattı

9 kablo

Rol 2

### Üst dirençler

- Her satır: delikten kablo j sırasına → direnç i sırasında → Arduino kablosu j sırasından
- j5 → j41 · i41–i45 · j45 → D10
- j6 → j35 · i35–i39 · j39 → D11
- j8 → j29 · i29–i33 · j33 → D13
- j10 → j23 · i23–i27 · j27 → A1
- j11 → j17 · i17–i21 · j21 → A2

5 direnç · 10 kablo · soldaki delik en uzağa gider

Rol 3

### Alt dirençler + buton + buzzer

- a7 → b29 · d29–d33 · b33 → D4
- a8 → b23 · d23–d27 · b27 → D5
- a10 → b17 · d17–d21 · b21 → D7
- Buton bacakları d47 d49 g47 g49. b47 → A4, h49 → −
- Pasif buzzer: uzun bacak h54, kısa h57. j54 → A5, j57 → −

3 direnç · 10 kablo

## Güç vermeden önce

1. 16 delikte (a5–a12, j5–j12) birer bağlantı var.
2. 8 direncin iki bacağı da farklı sütunda (örneğin i17 ve i21), bacaklar birbirine değmiyor.
3. Kablo uçları tam oturmuş, hafifçe çekince çıkmıyor.
4. GND, h49 ve j57 en üstteki − hattında.

## Test

1. matris_test.ino yüklenir: önce 8 yatay, sonra 8 dikey çizgi yanmalı.
2. Bir çizgi yanmıyorsa Seri Monitör (9600) o anki hattın deliğini yazar: o kabloyu bastır.
3. Hiçbir şey yanmıyorsa kodda SATIR_ANOT değeri değiştirilir.
4. Hepsi yanıyorsa oyun kodu yüklenir.