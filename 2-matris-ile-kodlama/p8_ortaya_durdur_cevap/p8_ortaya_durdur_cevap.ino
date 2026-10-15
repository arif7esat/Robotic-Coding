/*
  ================================================================
   P8  -  ORTAYA DURDUR  ·  GÖREV CEVAPLARI
  ================================================================
   Kullanım: GOREV sayısını 1-6 arasında değiştir ve yükle.
   Seri Monitör (görev 4): 9600.

   SORULARIN CEVAPLARI
   Görev 1 - Hedefi kaydırırken İKİ yeri birlikte değiştirmek gerekir:
     hedefin çizildiği yer ve isabet kontrolü. Bu çözümde ikisi de
     "hedef" değişkenini kullandığı için tek yerden değişiyor. Ders: aynı
     sayıyı iki yere yazma, bir değişkene koy.
   Görev 3 - 2 LED genişliğinde blok sol ucu x'te durur, x+1'i de kaplar.
     Sağ duvar artık x == 6 (x+1 = 7). İsabet: blok tam hedefin üstünde,
     yani x == hedef.
  ================================================================
*/
#include "matris.h"

const int GOREV = 1;     // <-- 1 ... 6

const char* MUTLU[8] = {"..####..", ".#....#.", "#.#..#.#", "#......#",
                        "#.#..#.#", "#..##..#", ".#....#.", "..####.."};
const char* UZGUN[8] = {"..####..", ".#....#.", "#.#..#.#", "#......#",
                        "#..##..#", "#.#..#.#", ".#....#.", "..####.."};
const char* OYUN_BITTI[8] = {"#......#", ".#....#.", "..#..#..", "...##...",
                             "...##...", "..#..#..", ".#....#.", "#......#"};

int x = 0, yon = 1, skor = 0;
int hedef = 3;               // hedef sütunları: hedef ve hedef+1
int baslangicHiz = 200;
int hizAdimi = 20;
int hiz = 200;
int genislik = 1;            // görev 3: 2
int can = 3;                 // görev 6

void hedefCiz() {
  ledYak(hedef, 0);  ledYak(hedef + 1, 0);
  ledYak(hedef, 7);  ledYak(hedef + 1, 7);
}

bool isabetMi() {
  if (genislik == 2) return x == hedef;
  return x == hedef || x == hedef + 1;
}

void skoruGoster() {                      // görev 4: skor kadar LED
  ekraniTemizle();
  for (int i = 0; i < skor && i < 64; i++) ledYak(i % 8, i / 8);
  delay(2000);
}

void setup() {
  matrisBaslat();
  Serial.begin(9600);
  if (GOREV == 1) hedef = 1;                         // hedef sola
  if (GOREV == 2) { baslangicHiz = 300; hizAdimi = 10; }
  if (GOREV == 3) genislik = 2;
  hiz = baslangicHiz;
}

void loop() {
  ekraniTemizle();
  hedefCiz();
  ledYak(x, 3);
  if (genislik == 2) ledYak(x + 1, 3);

  if (bekleBasildiMi(hiz)) {
    if (isabetMi()) {                                // İSABET
      resimCiz(MUTLU);
      bip(1047, 150);
      skor = skor + 1;
      hiz = hiz - hizAdimi;
      if (hiz < 40) hiz = 40;
      if (GOREV == 4) { Serial.print("Skor: "); Serial.println(skor); }
      if (GOREV == 5) {                              // hedef rastgele yere taşınır
        randomSeed(micros());
        hedef = random(1, 6);                        // 1..5 (hedef+1 en fazla 6)
      }
    } else {                                         // KAÇIRDIN
      resimCiz(UZGUN);
      bip(200, 400);
      if (GOREV == 4) skoruGoster();
      if (GOREV == 6) {
        can = can - 1;
        Serial.print("Kalan can: "); Serial.println(can);
        if (can == 0) {
          resimCiz(OYUN_BITTI);
          bip(150, 800);
          delay(2000);
          can = 3;
          skor = 0;
          hiz = baslangicHiz;
        }
      } else {
        skor = 0;
        hiz = baslangicHiz;
      }
    }
    delay(1000);
    x = 0;
    yon = 1;
  } else {
    x = x + yon;
    int sagDuvar = 8 - genislik;                     // 1 LED: 7, 2 LED: 6
    if (x == 0 || x == sagDuvar) {
      yon = -yon;
    }
  }
}
