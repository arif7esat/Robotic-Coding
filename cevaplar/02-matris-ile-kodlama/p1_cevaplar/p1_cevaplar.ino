/*
  ================================================================
   P1  -  İLK IŞIK  ·  GÖREV CEVAPLARI
  ================================================================
   Kullanım: Aşağıdaki GOREV sayısını 1-5 arasında değiştir ve yükle.
   Devre: 02 haftasının tam matris devresi (P1 devre PDF'i).

   SORULARIN CEVAPLARI
   Görev 2 - "Tam orta" neden yok?  Matris 8×8. 8 çift sayı olduğu için
     tam ortada tek bir LED yoktur; orta 4 LED'dir: (3,3) (4,3) (3,4) (4,4).
     Çözümde bu 4 LED birlikte yanıp söner.
   Görev 4 - Baş harf: Örnek olarak "A" harfi çizildi. Önce kareli
     kâğıda çizip her kareyi bir ledYak satırına çevirmek en kolay yol.
  ================================================================
*/
#include "matris.h"

const int GOREV = 1;     // <-- 1, 2, 3, 4 ya da 5

void ortaDortlu(bool yansin) {
  if (yansin) { ledYak(3, 3); ledYak(4, 3); ledYak(3, 4); ledYak(4, 4); }
  else        { ledSondur(3, 3); ledSondur(4, 3); ledSondur(3, 4); ledSondur(4, 4); }
}

void harfA() {
  ledYak(3, 7); ledYak(4, 7);                 // tepe
  ledYak(2, 6); ledYak(5, 6);
  for (int y = 0; y <= 5; y++) {              // iki yan bacak
    ledYak(1, y);
    ledYak(6, y);
  }
  for (int x = 2; x <= 5; x++) ledYak(x, 3);  // ortadaki çizgi
}

void setup() {
  matrisBaslat();
  if (GOREV <= 3) {            // görev 1-3: köşeler
    ledYak(0, 0);
    ledYak(7, 7);
  }
  if (GOREV == 1) {            // görev 1: diğer iki köşe
    ledYak(0, 7);              // sol üst
    ledYak(7, 0);              // sağ alt
  }
  if (GOREV == 4) {
    harfA();
  }
}

void loop() {
  if (GOREV == 1) {            // orijinal yanıp sönme
    ledYak(3, 4);    delay(500);
    ledSondur(3, 4); delay(500);
  }
  if (GOREV == 2) {            // ortadaki 4 LED
    ortaDortlu(true);  delay(500);
    ortaDortlu(false); delay(500);
  }
  if (GOREV == 3) {            // iki kat hızlı: 500 yerine 250
    ledYak(3, 4);    delay(250);
    ledSondur(3, 4); delay(250);
  }
  if (GOREV == 5) {            // polis çakarı
    ledYak(0, 4);  ledSondur(7, 4);
    delay(300);
    ledSondur(0, 4);  ledYak(7, 4);
    delay(300);
  }
}
