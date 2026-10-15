/*
  ================================================================
   PROJE 6  -  TIKLAMA SAYACI
  ================================================================
   Öğreneceklerin:
   - Sayaç değişkeni: her basışta 1 artan sayı
   - Bölme (/) ve kalan (%) ile sayıyı ekrandaki yere çevirmek
       sayac = 13  ->  x = 13 % 8 = 5,   y = 13 / 8 = 1
   - Seri Monitör: Arduino'nun bilgisayara yazı yazması
     (Araçlar > Seri Port Ekranı, 9600 baud)

   GÖREVLER
   9. sınıf
   1) Seri Monitörü aç ve tıklama sayısını izle.
   2) Her 8 tıklamada (bir satır dolunca) farklı bir ses çalsın.
      İpucu: if (sayac % 8 == 0) { ... }
   3) Ekran 64 yerine 32 tıklamada dolsun ve sıfırlansın.
   10. sınıf
   4) 10 SANİYE OYUNU: 10 saniyede kaç kere basabilirsin?
      İpucu: unsigned long baslangic = millis();
             millis() - baslangic > 10000  ise süre bitti.
   5) Ekran yukarıdan aşağı dolsun.  İpucu: y = 7 - sayac / 8;
  ================================================================
*/
#include "matris.h"

int sayac = 0;

void setup() {
  matrisBaslat();
  Serial.begin(9600);
  Serial.println("Butona bas!");
}

void loop() {
  if (butonaBasildi()) {
    int x = sayac % 8;      // sütun: 0,1,2...7 sonra yine 0
    int y = sayac / 8;      // satır: her 8 tıklamada bir yukarı
    ledYak(x, y);
    bip(1000, 30);

    sayac = sayac + 1;
    Serial.print("Tiklama: ");
    Serial.println(sayac);

    if (sayac == 64) {      // ekran doldu!
      for (int i = 0; i < 3; i++) {
        ekraniTemizle();
        delay(150);
        ekraniDoldur();
        bip(1500, 150);
      }
      ekraniTemizle();
      sayac = 0;
      Serial.println("Ekran doldu, bastan!");
    }
  }
}
