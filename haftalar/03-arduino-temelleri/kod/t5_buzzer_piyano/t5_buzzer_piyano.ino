/*
  ================================================================
   T5  -  IŞIKLI PİYANO
  ================================================================
   Öğreneceklerin:  tone, dizi, for, buton + ses + ışık birlikte
   (Arduino Temelleri PDF: bölüm 7, 9 ve 11)

   Butona basınca Do'dan üst Do'ya 8 nota çalar. Her nota çalarken
   en alt satırda o notanın sütunundaki LED yanar:
       sütun 1 = Do ... sütun 8 = üst Do
   Frekans büyüdükçe ses incelir.

   GÖREVLER
   9. sınıf
   1) Notaları ters sırayla (incelden kalına) çal.
   2) Daha hızlı çal: tone süresini ve delay'i küçült.
   3) Butona her basışta sadece TEK nota çalsın, sıradaki notaya geçsin.
   10. sınıf
   4) Kendi kısa melodini yaz: ayrı bir dizide hangi notanın çalınacağını,
      başka bir dizide ne kadar süreceğini tut.
   5) Basılı tuttukça notalar yükselsin, bırakınca dursun.
  ================================================================
*/

const int SATIR[8] = {A3, 12, 9, A0, 2, 8, 3, 6};
const int SUTUN[8] = {13, 4, 5, A2, 7, A1, 11, 10};
const int BUTON  = A4;
const int BUZZER = A5;

//                  Do   Re   Mi   Fa   Sol  La   Si   Do
int notalar[8] = {262, 294, 330, 349, 392, 440, 494, 523};

void setup() {
  for (int i = 0; i < 8; i++) {
    pinMode(SATIR[i], OUTPUT);
    pinMode(SUTUN[i], OUTPUT);
    digitalWrite(SATIR[i], LOW);
    digitalWrite(SUTUN[i], HIGH);
  }
  pinMode(BUTON, INPUT_PULLUP);
  pinMode(BUZZER, OUTPUT);
  digitalWrite(SATIR[7], HIGH);        // en alt satır hazır bekliyor
}

void loop() {
  if (digitalRead(BUTON) == LOW) {
    for (int i = 0; i < 8; i++) {
      digitalWrite(SUTUN[i], LOW);     // bu notanın LED'i yansın
      tone(BUZZER, notalar[i], 200);   // notayı çal
      delay(250);                      // nota bitsin, biraz boşluk kalsın
      digitalWrite(SUTUN[i], HIGH);    // LED sönsün
    }
  }
}
