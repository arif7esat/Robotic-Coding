/*
  ================================================================
   PROJE 4  -  EMOJİ VE ANİMASYON
  ================================================================
   Öğreneceklerin:
   - Resmi kodun içine çizmek:  '#' = yanan LED,  '.' = sönük LED
   - Dizi (liste): 8 satırlık resim tek bir isimde durur
   - Animasyon: resimleri sırayla göstermek (çizgi film gibi)

   GÖREVLER
   9. sınıf
   1) BENIM_RESMIM'i doldur (kendi emojini çiz) ve loop() içinde göster.
   2) Kalbi daha hızlı attır.
   3) Kalp her attığında farklı bir ses çıksın.
   10. sınıf
   4) Göz kırpan yüz yap: gözü açık ve gözü kapalı iki resim çiz.
   5) En az 4 kareli kendi animasyonunu yap
      (yürüyen adam, yağmur, dönen çizgi...).
   6) "hiz" adında bir değişken ekle; animasyon her turda biraz
      daha hızlansın.
  ================================================================
*/
#include "matris.h"

const char* KALP[8] = {
  ".##..##.",
  "########",
  "########",
  "########",
  ".######.",
  "..####..",
  "...##...",
  "........"
};

const char* KUCUK_KALP[8] = {
  "........",
  "........",
  ".##..##.",
  ".######.",
  "..####..",
  "...##...",
  "........",
  "........"
};

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

const char* BENIM_RESMIM[8] = {     // <-- burayı sen çiz
  "........",
  "........",
  "........",
  "........",
  "........",
  "........",
  "........",
  "........"
};

void setup() {
  matrisBaslat();

  resimCiz(MUTLU);      // açılışta gülen yüz
  delay(1500);
}

void loop() {
  // Kalp atışı: büyük - küçük - büyük - küçük ...
  resimCiz(KALP);
  bip(880, 60);
  delay(300);

  resimCiz(KUCUK_KALP);
  delay(400);
}
