/*
  ================================================================
   P5  -  BUTONLU YÜZ  ·  GÖREV CEVAPLARI
  ================================================================
   Kullanım: GOREV sayısını 1-5 arasında değiştir ve yükle.
   Devre: tam matris + buton. Görev 2 ses çıkardığı için buzzer da
   bağlı olmalı (P6 devre PDF'i: buton + buzzer).

   SORULARIN CEVAPLARI
   Görev 2 - Neden bip() değil tone()? bip() her seferinde sesin bitmesini
     bekler; buton basılıyken loop binlerce kez döner ve ses kesik kesik
     çıkar. tone(BUZZER, 1000) sesi başlatır ve kesintisiz çalar,
     noTone(BUZZER) durdurur.
   Görev 4 - Burada yeni kavram "durum" (state): Program hangi yüzü
     gösterdiğini mutluMu değişkeninde hatırlıyor. butonaBasildi() her
     basışta sadece bir kez true verdiği için yüz bir kez değişir.
  ================================================================
*/
#include "matris.h"

const int GOREV = 1;     // <-- 1 ... 5

const char* MUTLU[8] = {"..####..", ".#....#.", "#.#..#.#", "#......#",
                        "#.#..#.#", "#..##..#", ".#....#.", "..####.."};
const char* UZGUN[8] = {"..####..", ".#....#.", "#.#..#.#", "#......#",
                        "#..##..#", "#.#..#.#", ".#....#.", "..####.."};
const char* KALP[8]  = {".##..##.", "########", "########", "########",
                        ".######.", "..####..", "...##...", "........"};
const char* EV[8]    = {"...##...", "..####..", ".######.", "########",
                        ".#....#.", ".#.##.#.", ".#.##.#.", ".######."};

bool mutluMu = true;     // görev 4
int sira = 0;            // görev 5

void setup() {
  matrisBaslat();
}

void loop() {
  if (GOREV == 1) {                    // tersi
    if (butonaBasiliMi()) resimCiz(UZGUN);
    else                  resimCiz(MUTLU);
  }
  if (GOREV == 2) {                    // basılıyken ses
    if (butonaBasiliMi()) { resimCiz(MUTLU); tone(BUZZER, 1000); }
    else                  { resimCiz(UZGUN); noTone(BUZZER); }
  }
  if (GOREV == 3) {                    // üzgün yerine kendi resmi
    if (butonaBasiliMi()) resimCiz(MUTLU);
    else                  resimCiz(EV);
  }
  if (GOREV == 4) {                    // her basışta değiştir
    if (butonaBasildi()) {
      mutluMu = !mutluMu;
    }
    if (mutluMu) resimCiz(MUTLU);
    else         resimCiz(UZGUN);
  }
  if (GOREV == 5) {                    // üç resim sırayla
    if (butonaBasildi()) {
      sira = sira + 1;
      if (sira == 3) sira = 0;
    }
    if (sira == 0)      resimCiz(MUTLU);
    else if (sira == 1) resimCiz(UZGUN);
    else                resimCiz(KALP);
  }
}
