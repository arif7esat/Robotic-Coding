/*
  ================================================================
   P7  -  ELEKTRONİK ZAR  ·  GÖREV CEVAPLARI
  ================================================================
   Kullanım: GOREV sayısını 1-6 arasında değiştir ve yükle.
   Seri Monitör (görev 3 ve 5): 9600.

   SORULARIN CEVAPLARI
   Görev 4 - Kısa zarCiz: 1, 3, 5'te orta nokta var (tek sayılar:
     sayi % 2 == 1). 2'den büyük her sayıda bir çapraz çift, 4'ten
     büyüklerde diğer çapraz çift, 6'da yanlardaki iki nokta var.
   Görev 6 - Hileli zar: random(1, 10) 1-9 verir; 7, 8, 9 da 6 sayılır.
     6 gelme ihtimali 1/6 (~%17) yerine 4/9 (~%44) olur. Olasılık
     konusunu konuşmak için iyi bir fırsat: 100 atış yapıp say.
  ================================================================
*/
#include "matris.h"

const int GOREV = 1;     // <-- 1 ... 6

int SOL = 0;   int ORTA = 3;   int SAG = 6;
int ALT = 0;                   int UST = 6;

int oyuncu = 1;          // görev 5
int puan1 = 0;
int puan2 = 0;

void buyukNokta(int x, int y) {
  ledYak(x, y); ledYak(x + 1, y); ledYak(x, y + 1); ledYak(x + 1, y + 1);
}

// Görev 4: kısaltılmış zarCiz (diğer görevler de bunu kullanıyor)
void zarCiz(int sayi) {
  ekraniTemizle();
  if (sayi % 2 == 1) buyukNokta(ORTA, ORTA);                       // 1, 3, 5
  if (sayi >= 2) { buyukNokta(SOL, UST); buyukNokta(SAG, ALT); }   // 2-6
  if (sayi >= 4) { buyukNokta(SAG, UST); buyukNokta(SOL, ALT); }   // 4-6
  if (sayi == 6) { buyukNokta(SOL, ORTA); buyukNokta(SAG, ORTA); } // 6
}

int zarSec() {
  if (GOREV == 6) {                     // hileli zar
    int s = random(1, 10);              // 1 ... 9
    if (s > 6) s = 6;
    return s;
  }
  return random(1, 7);                  // 1 ... 6
}

void setup() {
  matrisBaslat();
  Serial.begin(9600);
  zarCiz(6);
}

void loop() {
  if (!butonaBasildi()) return;
  randomSeed(micros());

  int donus = 10;
  if (GOREV == 1) donus = 20;           // daha uzun dönsün
  for (int i = 0; i < donus; i++) {
    zarCiz(random(1, 7));
    bip(400 + i * 50, 30);
    delay(50 + i * 20);
  }

  int sonuc = zarSec();
  zarCiz(sonuc);
  bip(1200, 200);

  if (GOREV == 2 && sonuc == 6) {       // 6 gelince melodi
    bip(523, 100); bip(659, 100); bip(784, 300);
  }
  if (GOREV == 3) {
    Serial.print("Zar: ");
    Serial.println(sonuc);
  }
  if (GOREV == 5) {                     // iki oyuncu
    if (oyuncu == 1) puan1 = puan1 + sonuc;
    else             puan2 = puan2 + sonuc;
    Serial.print("Oyuncu ");  Serial.print(oyuncu);
    Serial.print(" atti: ");  Serial.print(sonuc);
    Serial.print("  |  Puanlar  1: "); Serial.print(puan1);
    Serial.print("  2: ");             Serial.println(puan2);
    if (puan1 >= 20 || puan2 >= 20) {
      Serial.print("KAZANAN: Oyuncu ");
      Serial.println(puan1 >= 20 ? 1 : 2);
      puan1 = 0; puan2 = 0;
      Serial.println("--- Yeni oyun ---");
    }
    oyuncu = 3 - oyuncu;                // 1 -> 2, 2 -> 1
  }
}
