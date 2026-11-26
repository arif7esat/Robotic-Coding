/*
  ================================================================
   S01  -  IŞIK THEREMİNİ  ·  KARAR SÜRÜMÜ (if / else)
  ================================================================
   Gece alarmı: LDR'yi kapatınca öter, açınca susar.
   Devre: ders devresinin aynısı (LDR, 10k, pasif buzzer).
   ESIK'i sınıfına göre ayarla: Seri Monitör'de el açıkken ve
   LDR kapalıyken gördüğün iki sayının ortası.
  ================================================================
*/

const int LDR_PIN = A0;
const int BUZZER  = A5;
const int ESIK    = 400;          // sınıfına göre ayarla

void setup() {
  Serial.begin(9600);
}

void loop() {
  int isik = analogRead(LDR_PIN);
  Serial.println(isik);

  if (isik < ESIK) {              // karanlık mı?
    tone(BUZZER, 1000);           // evet: alarm
  } else {
    noTone(BUZZER);               // hayır: sessiz
  }
  delay(10);
}
