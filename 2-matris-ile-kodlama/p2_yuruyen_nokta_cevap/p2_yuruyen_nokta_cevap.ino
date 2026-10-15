/*
  ================================================================
   P2  -  YÜRÜYEN NOKTA  ·  GÖREV CEVAPLARI
  ================================================================
   Kullanım: GOREV sayısını 1-6 arasında değiştir ve yükle.

   SORULARIN CEVAPLARI
   Görev 3 - ekraniTemizle() silinince ne oldu?
     Nokta arkasında iz bırakır, satır soldan sağa dolar. İlk turdan sonra
     satır hep dolu kalır; nokta hâlâ yürür ama yandığı yer zaten yanık
     olduğu için hareket görünmez. Neden: Program bir LED'i kendi kendine
     söndürmez; "söndür" demezsen yanık kalır. Bilgisayar sadece ona
     söyleneni yapar.
  ================================================================
*/
#include "matris.h"

const int GOREV = 1;     // <-- 1 ... 6

int x = 0;
int y = 0;               // görev 6
int yon = 1;             // görev 5: 1 = sağa, -1 = sola
int bekleme = 150;

void setup() {
  matrisBaslat();
  if (GOREV == 2) bekleme = 50;    // görev 2: daha hızlı
}

void loop() {
  if (GOREV != 3) ekraniTemizle(); // görev 3: temizleme yok, iz kalır

  if (GOREV == 1)      ledYak(x, 7);        // en üst satır
  else if (GOREV == 4) ledYak(3, x);        // aşağıdan yukarı (x artık yükseklik)
  else if (GOREV == 6) ledYak(x, y);        // her turda bir satır yukarı
  else                 ledYak(x, 3);        // görev 2, 3, 5

  delay(bekleme);

  if (GOREV == 5) {                          // duvardan sekme
    x = x + yon;
    if (x == 7 || x == 0) {
      yon = -yon;
    }
  } else {
    x = x + 1;
    if (x > 7) {
      x = 0;
      if (GOREV == 6) {
        y = y + 1;
        if (y > 7) y = 0;
      }
    }
  }
}
