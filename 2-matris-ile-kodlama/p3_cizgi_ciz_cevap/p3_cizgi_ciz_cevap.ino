/*
  ================================================================
   P3  -  ÇİZGİ ÇİZ  ·  GÖREV CEVAPLARI
  ================================================================
   Kullanım: GOREV sayısını 1-6 arasında değiştir ve yükle.

   SORULARIN CEVAPLARI
   Görev 4 - Satranç tahtası: Çift satırda x 0'dan, tek satırda 1'den
     başlar. "y % 2" çift sayıda 0, tek sayıda 1 verdiği için başlangıç
     değeri olarak doğrudan kullanılabilir.
   Görev 5 - Tersten söndürmede neden int? byte negatif olamaz: 0'dan sonra
     1 azalınca 255 olur, "y >= 0" hep doğru kalır ve döngü hiç bitmez.
  ================================================================
*/
#include "matris.h"

const int GOREV = 1;     // <-- 1 ... 6

void setup() {
  matrisBaslat();
}

void loop() {
  if (GOREV == 1) {                       // sol sütun aşağıdan yukarı
    for (int y = 0; y < 8; y++) { ledYak(0, y); delay(100); }
  }
  if (GOREV == 2) {                       // diğer çapraz: sol üstten sağ alta
    for (int i = 0; i < 8; i++) { ledYak(i, 7 - i); delay(100); }
  }
  if (GOREV == 3) {                       // çerçeve
    for (int i = 0; i < 8; i++) {
      ledYak(i, 0);  ledYak(i, 7);        // alt ve üst kenar
      ledYak(0, i);  ledYak(7, i);        // sol ve sağ kenar
      delay(80);
    }
  }
  if (GOREV == 4) {                       // satranç tahtası
    for (int y = 0; y < 8; y++) {
      for (int x = y % 2; x < 8; x = x + 2) {
        ledYak(x, y);
        delay(20);
      }
    }
  }
  if (GOREV == 5) {                       // doldur, sonra tersten söndür
    for (int y = 0; y < 8; y++)
      for (int x = 0; x < 8; x++) { ledYak(x, y); delay(15); }
    delay(300);
    for (int y = 7; y >= 0; y--)
      for (int x = 7; x >= 0; x--) { ledSondur(x, y); delay(15); }
  }
  if (GOREV == 6) {                       // ortadan dışa büyüyen kareler
    for (int k = 0; k < 4; k++) {
      int alt = 3 - k, ust = 4 + k;       // karenin kenarları
      for (int i = alt; i <= ust; i++) {
        ledYak(i, alt);  ledYak(i, ust);
        ledYak(alt, i);  ledYak(ust, i);
      }
      delay(300);
    }
  }
  delay(500);
  ekraniTemizle();
  delay(300);
}
