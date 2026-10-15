/*
  ================================================================
   T11  -  TAM MATRİS  ·  GÖREV CEVAPLARI
  ================================================================
   Kullanım: GOREV sayısını 1-3 arasında değiştir ve yükle.
   Devre:    T11 devresi (tam matris). Kabloya dokunma.

   SORULARIN CEVAPLARI
   Görev 1 - Dıştaki for artık sütun (k), içteki satır (s). İç döngü
     önce bir SÜTUNU yukarıdan aşağı bitirir, sonra dış döngü sağa geçer.
     ledYak(s, k) satırına dokunmadık; sadece döngülerin sırası değişti.
   Görev 2 - Bütün 64 LED'i yine geziyoruz ama ledYak ve delay sadece
     kenardakilerde çalışıyor. Ortadakiler beklemeden atlanıyor.
     ||  "veya" demek: dört koşuldan biri doğruysa LED kenardadır.
   Görev 3 - Evet, tek for yeter. Köşegende satır ve sütun hep eşit
     (s = k). İki ayrı sayıya ihtiyaç yok: ledYak(i, i).
     İç içe for 64 adım atar; köşegen için 8 adım yeterli.
  ================================================================
*/

const int GOREV = 1;     // <-- 1, 2 ya da 3

const int SATIR[8] = {A3, 12, 9, A0, 2, 8, 3, 6};
const int SUTUN[8] = {13, 4, 5, A2, 7, A1, 11, 10};

int bekleme = 60;

void hepsiniSondur() {
  for (int i = 0; i < 8; i++) {
    digitalWrite(SATIR[i], LOW);
    digitalWrite(SUTUN[i], HIGH);
  }
}

void ledYak(int s, int k) {
  hepsiniSondur();
  digitalWrite(SATIR[s], HIGH);
  digitalWrite(SUTUN[k], LOW);
}

void setup() {
  for (int i = 0; i < 8; i++) {
    pinMode(SATIR[i], OUTPUT);
    pinMode(SUTUN[i], OUTPUT);
  }
  hepsiniSondur();
}

void loop() {
  if (GOREV == 1) {                              // sütun sütun
    for (int k = 0; k < 8; k++) {
      for (int s = 0; s < 8; s++) {
        ledYak(s, k);
        delay(bekleme);
      }
    }
  }

  if (GOREV == 2) {                              // sadece çerçeve
    for (int s = 0; s < 8; s++) {
      for (int k = 0; k < 8; k++) {
        if (s == 0 || s == 7 || k == 0 || k == 7) {
          ledYak(s, k);
          delay(bekleme);
        }
      }
    }
  }

  if (GOREV == 3) {                              // köşegen
    for (int i = 0; i < 8; i++) {
      ledYak(i, i);
      delay(150);
    }
  }
}
