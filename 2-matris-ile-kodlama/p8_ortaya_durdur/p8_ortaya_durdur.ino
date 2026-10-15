/*
  ================================================================
   PROJE 8  -  ORTAYA DURDUR  (ilk oyunun!)
  ================================================================
   Kayan noktayı butonla tam ortada (işaretli iki sütunda) durdur.
   Başarırsan nokta hızlanır, kaçırırsan baştan başlarsın.
   Stacker oyununun kalbi tam olarak bu fikir!

   Öğreneceklerin:
   - Şimdiye kadar öğrendiğin her şeyi birleştirmek
   - "veya" bağlacı:   x == 3 || x == 4
   - Duvara çarpınca yön değiştirmek:  yon = -yon;
   - bekleBasildiMi(ms): beklerken butonu da dinlemek

   GÖREVLER
   9. sınıf
   1) Hedefi sola kaydır (hedefCiz ve isabet kontrolünü birlikte değiştir!).
   2) Başlangıç hızını ve her isabette ne kadar hızlanacağını değiştir.
   3) Kayan nokta yerine 2 LED genişliğinde bir blok kaysın.
   10. sınıf
   4) Skoru Seri Monitöre yazdır; oyun bitince skor kadar LED yansın.
   5) Her isabetten sonra hedef rastgele bir yere taşınsın.
      İpucu: int hedef = random(1, 6);  hedef ve hedef+1 sütunları
   6) 3 can ekle: can bitince "oyun bitti" resmi çıksın.
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

int x = 0;          // kayan noktanın yeri
int yon = 1;        // 1 = sağa,  -1 = sola
int hiz = 200;      // bir adım kaç milisaniye (küçük = hızlı)
int skor = 0;

// Hedef sütunları (3 ve 4) üstte ve altta işaretle
void hedefCiz() {
  ledYak(3, 0);  ledYak(4, 0);
  ledYak(3, 7);  ledYak(4, 7);
}

void setup() {
  matrisBaslat();
}

void loop() {
  ekraniTemizle();
  hedefCiz();
  ledYak(x, 3);                      // kayan nokta ortadaki satırda

  if (bekleBasildiMi(hiz)) {         // beklerken butona basıldı mı?
    if (x == 3 || x == 4) {          // İSABET!
      resimCiz(MUTLU);
      bip(1047, 150);
      skor = skor + 1;
      hiz = hiz - 20;                // bir sonraki tur daha hızlı
      if (hiz < 40) {
        hiz = 40;
      }
    } else {                         // KAÇIRDIN
      resimCiz(UZGUN);
      bip(200, 400);
      skor = 0;
      hiz = 200;                     // baştan başla
    }
    delay(1000);
    x = 0;
    yon = 1;
  } else {                           // basılmadı: noktayı ilerlet
    x = x + yon;
    if (x == 0 || x == 7) {          // duvara çarptı: geri dön
      yon = -yon;
    }
  }
}
