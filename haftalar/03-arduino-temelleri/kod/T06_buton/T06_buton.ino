/*
  ================================================================
   T06  -  BUTON
  ================================================================
   Yeni kavramlar:  digitalRead, INPUT_PULLUP, if / else
   Devre:           T05 + GND hattı + buton (A4)

   Şimdiye kadar Arduino sadece konuşuyordu (OUTPUT). Şimdi dinliyor:
   A4 pini giriş (INPUT_PULLUP). Arduino bu pini içeriden 5 V'a çeker.
       buton bırakık  ->  digitalRead(A4) = HIGH
       buton basılı   ->  A4 doğrudan GND'ye bağlanır  ->  LOW

   KISA DEVRE UYARISI
   Butonun bir ucu GND'de. Bu pini asla OUTPUT + HIGH yapma: butona
   basınca 5 V dirençsiz GND'ye bağlanır, pin yanar. PDF'te anlatılıyor.

   GÖREVLER
   9. sınıf
   1) Ters çalışsın: basılıyken sağdaki, bırakıkken soldaki LED yansın.
   2) Butona basılıyken koşan ışık (T05) çalışsın, bırakınca dursun.
   10. sınıf
   3) Her BASIŞTA ışık bir sonraki LED'e geçsin.
      İpucu: int onceki = HIGH;  ve  if (durum == LOW && onceki == HIGH)
  ================================================================
*/

const int SATIR_1 = A3;
const int SUTUN[3] = {13, 4, 5};
const int BUTON = A4;

void setup() {
  pinMode(SATIR_1, OUTPUT);
  for (int i = 0; i < 3; i++) {
    pinMode(SUTUN[i], OUTPUT);
    digitalWrite(SUTUN[i], HIGH);
  }
  digitalWrite(SATIR_1, HIGH);
  pinMode(BUTON, INPUT_PULLUP);     // giriş, içeriden 5 V'a çekili
}

void loop() {
  if (digitalRead(BUTON) == LOW) {  // basılı
    digitalWrite(SUTUN[0], LOW);    // sol yanar
    digitalWrite(SUTUN[2], HIGH);   // sağ söner
  } else {                          // bırakık
    digitalWrite(SUTUN[0], HIGH);
    digitalWrite(SUTUN[2], LOW);
  }
}
