/*
  ================================================================
   PROJE 5  -  BUTONLU YÜZ
  ================================================================
   Öğreneceklerin:
   - Arduino'nun dışarıdan bilgi okuması (giriş): buton
   - if / else: "eğer böyleyse bunu yap, değilse şunu yap"

   GÖREVLER
   9. sınıf
   1) Tersini yap: butona basınca üzgün, bırakınca mutlu olsun.
   2) Butona basılıyken buzzer da ötsün.
   3) Üzgün yüz yerine kendi çizdiğin bir resmi koy.
   10. sınıf
   4) Butona basılı tutmak yerine her BASIŞTA yüz değişsin
      (bir mutlu, bir üzgün).
      İpucu: bool mutluMu = true;   butonaBasildi()   mutluMu = !mutluMu;
   5) Üç resim olsun, her basışta sıradakine geçsin.
      İpucu: int sira = 0;  ve  if (sira == 3) sira = 0;
  ================================================================
*/
#include "matris.h"

const char* MUTLU[8] = {
  "..####..",
  ".#....#.",
  "#.#..#.#",
  "#......#",
  "#.#..#.#",
  "#..##..#",
  ".#....#.",
  "..####.."
};

const char* UZGUN[8] = {
  "..####..",
  ".#....#.",
  "#.#..#.#",
  "#......#",
  "#..##..#",
  "#.#..#.#",
  ".#....#.",
  "..####.."
};

void setup() {
  matrisBaslat();
}

void loop() {
  if (butonaBasiliMi()) {     // buton basılıysa
    resimCiz(MUTLU);
  } else {                    // değilse
    resimCiz(UZGUN);
  }
}
