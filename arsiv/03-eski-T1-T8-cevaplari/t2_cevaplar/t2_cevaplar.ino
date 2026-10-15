/*
  ================================================================
   T2  -  DİZİ İLE LED SEÇ  ·  GÖREV CEVAPLARI
  ================================================================
   Kullanım: GOREV sayısını 1-5 arasında değiştir ve yükle.
   Devre: T2 devresi (16 hat), ek gerekmez.
   Hatırlatma: Burada satır 0 EN ÜSTTE, sütun 0 EN SOLDA.

   SORULARIN CEVAPLARI
   Görev 5 - Yılan: çift satırlarda (0, 2, 4, 6) soldan sağa, tek satırlarda
     sağdan sola gidilir. "satir % 2 == 0" satırın çift olup olmadığını
     söyler. Sağdan sola gitmek için sütun = 7 - s yazılır.
  ================================================================
*/

const int GOREV = 1;     // <-- 1 ... 5

const int SATIR[8] = {A3, 12, 9, A0, 2, 8, 3, 6};
const int SUTUN[8] = {13, 4, 5, A2, 7, A1, 11, 10};

void hepsiniSondur() {
  for (int i = 0; i < 8; i++) {
    digitalWrite(SATIR[i], LOW);
    digitalWrite(SUTUN[i], HIGH);
  }
}

void ledYak(int satir, int sutun) {
  hepsiniSondur();
  digitalWrite(SATIR[satir], HIGH);
  digitalWrite(SUTUN[sutun], LOW);
}

void setup() {
  for (int i = 0; i < 8; i++) {
    pinMode(SATIR[i], OUTPUT);
    pinMode(SUTUN[i], OUTPUT);
  }
  hepsiniSondur();
}

void loop() {
  if (GOREV == 1) {                          // köşeler ters yönde
    ledYak(0, 0);  delay(300);   // sol üst
    ledYak(7, 0);  delay(300);   // sol alt
    ledYak(7, 7);  delay(300);   // sağ alt
    ledYak(0, 7);  delay(300);   // sağ üst
  }
  if (GOREV == 2) {                          // çapraz yürüyüş
    for (int i = 0; i < 8; i++) { ledYak(i, i); delay(150); }
  }
  if (GOREV == 3) {                          // ortadaki dört LED
    ledYak(3, 3);  delay(300);
    ledYak(3, 4);  delay(300);
    ledYak(4, 4);  delay(300);
    ledYak(4, 3);  delay(300);
  }
  if (GOREV == 4) {                          // bütün ekran satır satır
    for (int satir = 0; satir < 8; satir++) {
      for (int sutun = 0; sutun < 8; sutun++) {
        ledYak(satir, sutun);
        delay(60);
      }
    }
  }
  if (GOREV == 5) {                          // yılan gibi
    for (int satir = 0; satir < 8; satir++) {
      for (int s = 0; s < 8; s++) {
        int sutun = s;
        if (satir % 2 == 1) sutun = 7 - s;   // tek satırda sağdan sola
        ledYak(satir, sutun);
        delay(60);
      }
    }
  }
}
