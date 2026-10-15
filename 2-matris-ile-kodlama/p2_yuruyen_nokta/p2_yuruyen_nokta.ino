/*
  ================================================================
   PROJE 2  -  YÜRÜYEN NOKTA
  ================================================================
   Öğreneceklerin:
   - Değişken: bir sayıyı aklında tutan kutu   (int x = 0;)
   - Değişkeni değiştirmek:                    x = x + 1;
   - Karar vermek:                             if (...) { ... }

   GÖREVLER
   9. sınıf
   1) Nokta en üst satırda yürüsün.
   2) "bekleme" değişkenini değiştirerek noktayı hızlandır.
   3) ekraniTemizle(); satırının başına // koy. Ne oldu? Neden?
   4) Nokta yatay değil, aşağıdan yukarı yürüsün.
   10. sınıf
   5) Nokta sağ duvara çarpınca geri dönsün, sol duvara çarpınca
      yine dönsün.  İpucu: int yon = 1;  ve  x = x + yon;
   6) Her turda nokta bir satır yukarı çıksın, en üste gelince
      tekrar en alttan başlasın.
  ================================================================
*/
#include "matris.h"

int x = 0;            // noktanın yeri
int bekleme = 150;    // bir adım kaç milisaniye sürsün

void setup() {
  matrisBaslat();
}

void loop() {
  ekraniTemizle();    // önceki noktayı sil
  ledYak(x, 3);       // noktayı yeni yerinde yak
  delay(bekleme);

  x = x + 1;          // bir adım sağa

  if (x > 7) {        // ekrandan çıktıysa
    x = 0;            // en sola geri dön
  }
}
