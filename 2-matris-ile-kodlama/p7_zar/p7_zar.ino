/*
  ================================================================
   PROJE 7  -  ELEKTRONİK ZAR
  ================================================================
   Öğreneceklerin:
   - Kendi komutunu (fonksiyonunu) yazmak:  void buyukNokta(...)
   - random(1, 7): 1 ile 6 arasında rastgele sayı (7 dahil değil!)
   - if / else if zinciri

   GÖREVLER
   9. sınıf
   1) Zar daha uzun süre dönsün.
   2) 6 gelince kısa bir zafer melodisi çalsın.
   3) Sonucu Seri Monitöre de yazdır.
   10. sınıf
   4) zarCiz() içindeki uzun if zincirini kısalt.
      İpucu: 1, 3 ve 5'te orta nokta var; 2'den büyük her sayıda
      iki çapraz köşe var; 4'ten büyüklerde diğer iki köşe var...
   5) İKİ OYUNCU: sırayla atsınlar, toplam puanları Seri Monitörde
      görünsün. 20 puana ilk ulaşan kazansın.
   6) Hileli zar: 6 gelme ihtimali diğerlerinden fazla olsun.
      İpucu: random(1, 10) ile 7, 8, 9 gelirse 6 say.
  ================================================================
*/
#include "matris.h"

// Noktaların yerleri (her nokta 2x2 LED)
int SOL = 0;   int ORTA = 3;   int SAG = 6;
int ALT = 0;                   int UST = 6;

// (x, y) köşesinden başlayan 2x2'lik kalın nokta çizer
void buyukNokta(int x, int y) {
  ledYak(x, y);
  ledYak(x + 1, y);
  ledYak(x, y + 1);
  ledYak(x + 1, y + 1);
}

// Zarın 1-6 yüzünü çizer
void zarCiz(int sayi) {
  ekraniTemizle();
  if (sayi == 1) {
    buyukNokta(ORTA, ORTA);
  } else if (sayi == 2) {
    buyukNokta(SOL, UST);   buyukNokta(SAG, ALT);
  } else if (sayi == 3) {
    buyukNokta(SOL, UST);   buyukNokta(ORTA, ORTA);   buyukNokta(SAG, ALT);
  } else if (sayi == 4) {
    buyukNokta(SOL, UST);   buyukNokta(SAG, UST);
    buyukNokta(SOL, ALT);   buyukNokta(SAG, ALT);
  } else if (sayi == 5) {
    buyukNokta(SOL, UST);   buyukNokta(SAG, UST);
    buyukNokta(ORTA, ORTA);
    buyukNokta(SOL, ALT);   buyukNokta(SAG, ALT);
  } else if (sayi == 6) {
    buyukNokta(SOL, UST);   buyukNokta(SAG, UST);
    buyukNokta(SOL, ORTA);  buyukNokta(SAG, ORTA);
    buyukNokta(SOL, ALT);   buyukNokta(SAG, ALT);
  }
}

void setup() {
  matrisBaslat();
  zarCiz(6);
}

void loop() {
  if (butonaBasildi()) {
    randomSeed(micros());   // butona bastığın an = gerçekten rastgele başlangıç

    // Zar dönüyor: gittikçe yavaşlayan 10 rastgele yüz
    for (int i = 0; i < 10; i++) {
      zarCiz(random(1, 7));
      bip(400 + i * 50, 30);
      delay(50 + i * 20);
    }

    int sonuc = random(1, 7);
    zarCiz(sonuc);
    bip(1200, 200);
  }
}
