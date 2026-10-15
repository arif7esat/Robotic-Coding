/*
  ================================================================
   T05  -  DİZİ VE FOR  ·  GÖREV CEVAPLARI
  ================================================================
   Kullanım: GOREV sayısını 1-3 arasında değiştir ve yükle.
   Devre:    T04 devresi. Kabloya dokunma.

   SORULARIN CEVAPLARI
   Görev 1 - for (int i = 2; i >= 0; i--)  ->  i önce 2, sonra 1, sonra 0.
     Koşul "i >= 0" olmalı; "i > 0" yazılırsa 0. LED (en soldaki) hiç yanmaz.
   Görev 2 - Dizi {5, 13, 4} olunca sıra: sağ, sol, orta. Işık zıplıyor.
     loop'a HİÇ dokunmadık. Dizi "hangi sırayla" bilgisini, for ise
     "nasıl" bilgisini taşır. Sırayı değiştirmek için sadece veriyi
     değiştirmek yetti.
   Görev 3 - İleri: 0, 1, 2. Geri: 1. Sonra loop yine 0'dan başlar.
     Geri döngü 2 ve 0'ı atlar; yoksa uçtaki LED'ler iki kez yanar.
  ================================================================
*/

const int GOREV = 1;     // <-- 1, 2 ya da 3

const int SATIR_1 = A3;
const int SUTUN_A[3] = {13, 4, 5};   // Görev 1 ve 3: normal sıra
const int SUTUN_B[3] = {5, 13, 4};   // Görev 2: karışık sıra

int bekleme = 200;

void setup() {
  pinMode(SATIR_1, OUTPUT);
  for (int i = 0; i < 3; i++) {
    pinMode(SUTUN_A[i], OUTPUT);
    digitalWrite(SUTUN_A[i], HIGH);
  }
  digitalWrite(SATIR_1, HIGH);
}

void loop() {
  if (GOREV == 1) {                          // sağdan sola
    for (int i = 2; i >= 0; i--) {
      digitalWrite(SUTUN_A[i], LOW);
      delay(bekleme);
      digitalWrite(SUTUN_A[i], HIGH);
    }
  }
  if (GOREV == 2) {                          // loop aynı, dizi farklı
    for (int i = 0; i < 3; i++) {
      digitalWrite(SUTUN_B[i], LOW);
      delay(bekleme);
      digitalWrite(SUTUN_B[i], HIGH);
    }
  }
  if (GOREV == 3) {                          // gidip gelme
    for (int i = 0; i < 3; i++) {            // ileri: 0, 1, 2
      digitalWrite(SUTUN_A[i], LOW);
      delay(bekleme);
      digitalWrite(SUTUN_A[i], HIGH);
    }
    for (int i = 1; i > 0; i--) {            // geri: sadece 1
      digitalWrite(SUTUN_A[i], LOW);
      delay(bekleme);
      digitalWrite(SUTUN_A[i], HIGH);
    }
  }
}
