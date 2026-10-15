/*
  ================================================================
   PROJE 1  -  İLK IŞIK
  ================================================================
   Öğreneceklerin:
   - setup() bir kez, loop() sonsuza kadar tekrar çalışır
   - Komut (fonksiyon) çağırmak:  ledYak(x, y);
   - Koordinat ve delay() ile beklemek

   KOORDİNAT:     y
                  7  . . . . . . . .
                  6  . . . . . . . .
                  5  . . . . . . . .
                  4  . . . . . . . .
                  3  . . . . . . . .
                  2  . . . . . . . .
                  1  . . . . . . . .
                  0  . . . . . . . .
                     0 1 2 3 4 5 6 7   x

   GÖREVLER
   9. sınıf
   1) Diğer iki köşeyi de yak (sol üst ve sağ alt).
   2) Yanıp sönen LED'i ekranın tam ortasına taşı.
   3) Yanıp sönmeyi iki kat hızlandır.
   10. sınıf
   4) Adının baş harfini ledYak komutlarıyla nokta nokta çiz.
   5) İki LED "polis çakarı" gibi sırayla yansın:
      biri yanarken diğeri sönük olsun.
  ================================================================
*/
#include "matris.h"

void setup() {
  matrisBaslat();      // matrisi hazırla (her projede ilk satır bu)

  ledYak(0, 0);        // sol alt köşe
  ledYak(7, 7);        // sağ üst köşe
}

void loop() {
  ledYak(3, 4);        // (3, 4) noktasındaki LED'i yak
  delay(500);          // 500 milisaniye = yarım saniye bekle
  ledSondur(3, 4);     // söndür
  delay(500);
}
