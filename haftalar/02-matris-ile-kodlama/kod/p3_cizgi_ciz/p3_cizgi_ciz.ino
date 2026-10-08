/*
  ================================================================
   PROJE 3  -  ÇİZGİ ÇİZ  (for döngüsü)
  ================================================================
   Öğreneceklerin:
   - for döngüsü: aynı işi istediğin kadar tekrarlamak
       for (int x = 0; x < 8; x++) { ... }
       "x 0'dan başla, 8'den küçük olduğu sürece devam et, her turda 1 artır"
   - İç içe döngü ile bütün ekranı gezmek

   GÖREVLER
   9. sınıf
   1) En sol sütunu aşağıdan yukarı doldur.
   2) Diğer çaprazı çiz (sol üstten sağ alta).  İpucu: ledYak(i, 7 - i);
   3) Ekranın çevresine bir çerçeve çiz (4 tane for döngüsü).
   10. sınıf
   4) x++ yerine x = x + 2 kullanarak satranç tahtası yap.
      (Tek satırlarda 0'dan, çift satırlarda 1'den başla.)
   5) Ekran dolduktan sonra LED'leri tersten tek tek söndür.
   6) Ortadan dışa doğru büyüyen kareler çiz.
  ================================================================
*/
#include "matris.h"

void setup() {
  matrisBaslat();
}

void loop() {
  // 1) Alt satırı soldan sağa doldur
  for (int x = 0; x < 8; x++) {
    ledYak(x, 0);
    delay(100);
  }
  delay(500);
  ekraniTemizle();

  // 2) Çapraz çizgi: (0,0), (1,1), (2,2) ... (7,7)
  for (int i = 0; i < 8; i++) {
    ledYak(i, i);
    delay(100);
  }
  delay(500);
  ekraniTemizle();

  // 3) İç içe döngü: bütün ekranı satır satır doldur
  for (int y = 0; y < 8; y++) {
    for (int x = 0; x < 8; x++) {
      ledYak(x, y);
      delay(20);
    }
  }
  delay(500);
  ekraniTemizle();
  delay(500);
}
