/*
  ================================================================
   T07  -  BUZZER  ·  GÖREV CEVAPLARI
  ================================================================
   Kullanım: GOREV sayısını 1-3 arasında değiştir ve yükle.
   Devre:    T07 devresi. Kabloya dokunma.

   SORULARIN CEVAPLARI
   Görev 2 - Ses inceldi. Frekans = buzzer'ın zarının saniyedeki
     titreşim sayısı. Daha çok titreşim -> daha ince (tiz) ses.
     Üst Do (523) alttaki Do'nun (262) neredeyse tam 2 katı: bir oktav
     yukarısı, frekansın iki katı demektir.
   Görev 3 - frekans her turda 10 artar; tur ~20 ms sürdüğü için ses
     saniyede ~500 Hz incelir. 4000 Hz'de durduruyoruz; daha yukarısı
     kulağı rahatsız eder. Bırakınca frekans yeniden 200 olur.
  ================================================================
*/

const int GOREV = 1;     // <-- 1, 2 ya da 3

const int SATIR_1 = A3;
const int SUTUN[3] = {13, 4, 5};
const int BUTON = A4;
const int BUZZER = A5;

const int NOTA[3]  = {262, 330, 392};   // Do, Mi, Sol
const int NOTA2[3] = {440, 494, 523};   // Görev 2: La, Si, üst Do

int frekans = 200;                      // Görev 3

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
  if (GOREV == 1) {                       // ters sıra: Sol, Mi, Do
    if (digitalRead(BUTON) == LOW) {
      for (int i = 2; i >= 0; i--) {
        digitalWrite(SUTUN[i], LOW);
        tone(BUZZER, NOTA[i]);
        delay(300);
        noTone(BUZZER);
        digitalWrite(SUTUN[i], HIGH);
        delay(50);
      }
    }
  }

  if (GOREV == 2) {                       // La, Si, üst Do
    if (digitalRead(BUTON) == LOW) {
      for (int i = 0; i < 3; i++) {
        digitalWrite(SUTUN[i], LOW);
        tone(BUZZER, NOTA2[i]);
        delay(300);
        noTone(BUZZER);
        digitalWrite(SUTUN[i], HIGH);
        delay(50);
      }
    }
  }

  if (GOREV == 3) {                       // basılı tuttukça incelen ses
    if (digitalRead(BUTON) == LOW) {
      tone(BUZZER, frekans);
      frekans = frekans + 10;
      if (frekans > 4000) frekans = 4000;
    } else {
      noTone(BUZZER);
      frekans = 200;
    }
    delay(20);
  }
}
