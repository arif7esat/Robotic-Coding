/*
  ================================================================
   P6  -  TIKLAMA SAYACI  ·  GÖREV CEVAPLARI
  ================================================================
   Kullanım: GOREV sayısını 1-5 arasında değiştir ve yükle.
   Seri Monitör: Araçlar > Seri Port Ekranı, sağ altta 9600.

   SORULARIN CEVAPLARI
   Görev 1 - Kod gerekmez: Seri Monitörü açınca her basışta
     "Tiklama: 1, 2, 3..." yazar. Hız 9600 değilse anlamsız karakterler
     görünür.
   Görev 4 - İlk basış oyunu başlatır ve zamanı not eder. Her döngüde
     "millis() - baslangic > 10000" kontrol edilir; 10 saniye dolunca
     skor Seri Monitöre yazılır. Sonraki basış yeni oyunu başlatır.
   Görev 5 - y = 7 - sayac / 8: sayaç 0-7 iken y = 7 (en üst), 8-15 iken
     y = 6 ... Böylece ekran yukarıdan aşağı dolar.
  ================================================================
*/
#include "matris.h"

const int GOREV = 1;     // <-- 1 ... 5

int sayac = 0;
unsigned long baslangic = 0;   // görev 4
bool oyunVar = false;          // görev 4

void ekranDoldu() {
  for (int i = 0; i < 3; i++) {
    ekraniTemizle(); delay(150);
    ekraniDoldur();  bip(1500, 150);
  }
  ekraniTemizle();
  sayac = 0;
  Serial.println("Ekran doldu, bastan!");
}

void setup() {
  matrisBaslat();
  Serial.begin(9600);
  Serial.println("Butona bas!");
}

void loop() {
  if (GOREV == 4) {                       // 10 saniye oyunu
    if (butonaBasildi()) {
      if (!oyunVar) {                     // ilk basış oyunu başlatır
        oyunVar = true;
        baslangic = millis();
        sayac = 0;
        ekraniTemizle();
        Serial.println("Basla! 10 saniye...");
      }
      if (sayac < 64) ledYak(sayac % 8, sayac / 8);
      sayac = sayac + 1;
      bip(1000, 20);
    }
    if (oyunVar && millis() - baslangic > 10000) {
      oyunVar = false;
      Serial.print("Sure doldu! Skor: ");
      Serial.println(sayac);
      bip(300, 500);
    }
    return;                               // görev 4 burada biter
  }

  if (butonaBasildi()) {
    int x = sayac % 8;
    int y = sayac / 8;
    if (GOREV == 5) y = 7 - sayac / 8;    // yukarıdan aşağı
    ledYak(x, y);
    bip(1000, 30);

    sayac = sayac + 1;
    Serial.print("Tiklama: ");
    Serial.println(sayac);

    if (GOREV == 2 && sayac % 8 == 0) {   // satır dolunca farklı ses
      bip(2000, 150);
    }

    int sinir = 64;
    if (GOREV == 3) sinir = 32;           // 32'de dolsun
    if (sayac == sinir) {
      ekranDoldu();
    }
  }
}
