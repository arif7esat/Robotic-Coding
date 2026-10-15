/*
  ================================================================
   P4  -  EMOJİ VE ANİMASYON  ·  GÖREV CEVAPLARI
  ================================================================
   Kullanım: GOREV sayısını 1-6 arasında değiştir ve yükle.
   Devre: tam matris + buzzer (P4 devre PDF'i).

   SORULARIN CEVAPLARI
   Görev 1 - Örnek resim olarak bir ev çizildi. Öğrencinin kendi çizimi
     elbette farklı olacak; tek kural her satırın 8 karakter olması.
   Görev 4 - Gerçekçi göz kırpma için göz uzun süre açık (2 sn),
     kısa süre kapalı (0,15 sn) kalır. Kapalı gözde göz noktaları silinir.
  ================================================================
*/
#include "matris.h"

const int GOREV = 1;     // <-- 1 ... 6

const char* KALP[8] = {".##..##.", "########", "########", "########",
                       ".######.", "..####..", "...##...", "........"};
const char* KUCUK_KALP[8] = {"........", "........", ".##..##.", ".######.",
                             "..####..", "...##...", "........", "........"};
const char* BENIM_RESMIM[8] = {      // görev 1: örnek resim (ev)
  "...##...",
  "..####..",
  ".######.",
  "########",
  ".#....#.",
  ".#.##.#.",
  ".#.##.#.",
  ".######."
};
const char* GOZ_ACIK[8] = {"..####..", ".#....#.", "#.#..#.#", "#......#",
                           "#.#..#.#", "#..##..#", ".#....#.", "..####.."};
const char* GOZ_KAPALI[8] = {"..####..", ".#....#.", "#......#", "#......#",
                             "#.#..#.#", "#..##..#", ".#....#.", "..####.."};
// görev 5: dönen çizgi, 4 kare:  |  /  -  \ .
const char* CIZGI_1[8] = {"...#....", "...#....", "...#....", "...#....",
                          "...#....", "...#....", "...#....", "...#...."};
const char* CIZGI_2[8] = {".......#", "......#.", ".....#..", "....#...",
                          "...#....", "..#.....", ".#......", "#......."};
const char* CIZGI_3[8] = {"........", "........", "........", "########",
                          "........", "........", "........", "........"};
const char* CIZGI_4[8] = {"#.......", ".#......", "..#.....", "...#....",
                          "....#...", ".....#..", "......#.", ".......#"};

int nota = 500;          // görev 3
int hiz = 400;           // görev 6

void setup() {
  matrisBaslat();
}

void loop() {
  if (GOREV == 1) {
    resimCiz(BENIM_RESMIM);
    delay(1000);
  }
  if (GOREV == 2) {                    // daha hızlı kalp
    resimCiz(KALP);  bip(880, 60);  delay(120);
    resimCiz(KUCUK_KALP);           delay(180);
  }
  if (GOREV == 3) {                    // her atışta farklı ses
    resimCiz(KALP);  bip(nota, 60);  delay(300);
    resimCiz(KUCUK_KALP);            delay(400);
    nota = nota + 100;
    if (nota > 1500) nota = 500;
  }
  if (GOREV == 4) {                    // göz kırpan yüz
    resimCiz(GOZ_ACIK);   delay(2000);
    resimCiz(GOZ_KAPALI); delay(150);
  }
  if (GOREV == 5) {                    // 4 kareli animasyon
    resimCiz(CIZGI_1); delay(150);
    resimCiz(CIZGI_2); delay(150);
    resimCiz(CIZGI_3); delay(150);
    resimCiz(CIZGI_4); delay(150);
  }
  if (GOREV == 6) {                    // her turda hızlanan kalp
    resimCiz(KALP);  bip(880, 60);  delay(hiz);
    resimCiz(KUCUK_KALP);           delay(hiz);
    hiz = hiz - 20;
    if (hiz < 80) hiz = 400;           // çok hızlanınca baştan
  }
}
