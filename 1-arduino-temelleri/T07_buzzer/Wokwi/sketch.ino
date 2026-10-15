/*
  ================================================================
   T07  -  BUZZER
  ================================================================
   Yeni kavramlar:  tone, noTone, frekans (Hz)
   Devre:           T06 + pasif buzzer (A5)

   Butona basınca üç LED sırayla yanar ve her biri kendi notasını çalar:
   Do (262 Hz), Mi (330 Hz), Sol (392 Hz).
   tone(pin, frekans) pini saniyede "frekans" kez açıp kapatır;
   buzzer'ın zarı bu hızda titrer ve ses çıkar.

   GÖREVLER
   9. sınıf
   1) Notalar ters sırayla çalsın: Sol, Mi, Do.
   2) Notaları La (440), Si (494), üst Do (523) yap. Ses nasıl değişti?
   10. sınıf
   3) Butona basılı tuttukça ses yavaşça incelsin: bir frekans değişkeni
      her turda 10 artsın, buton bırakılınca 200'e dönsün.
  ================================================================
*/

const int SATIR_1 = A3;
const int SUTUN[3] = {13, 4, 5};
const int BUTON = A4;
const int BUZZER = A5;

const int NOTA[3] = {262, 330, 392};   // Do, Mi, Sol

void setup() {
  pinMode(SATIR_1, OUTPUT);
  for (int i = 0; i < 3; i++) {
    pinMode(SUTUN[i], OUTPUT);
    digitalWrite(SUTUN[i], HIGH);
  }
  digitalWrite(SATIR_1, HIGH);
  pinMode(BUTON, INPUT_PULLUP);
  pinMode(BUZZER, OUTPUT);
}

void loop() {
  if (digitalRead(BUTON) == LOW) {
    for (int i = 0; i < 3; i++) {
      digitalWrite(SUTUN[i], LOW);     // notanın LED'i yanar
      tone(BUZZER, NOTA[i]);           // nota başlar
      delay(300);
      noTone(BUZZER);                  // nota biter
      digitalWrite(SUTUN[i], HIGH);
      delay(50);
    }
  }
}
