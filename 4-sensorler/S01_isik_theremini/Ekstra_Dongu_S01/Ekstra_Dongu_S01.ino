/*
  ================================================================
   S01  -  IŞIK THEREMİNİ  ·  DÖNGÜ SÜRÜMÜ (for / while)
  ================================================================
   Açılışta 3 kısa bip (devre hazır), sonra karanlık sürdükçe alarm.
   Devre: ders devresinin aynısı (LDR, 10k, pasif buzzer).
  ================================================================
*/

const int LDR_PIN = A0;
const int BUZZER  = A5;
const int ESIK    = 400;          // sınıfına göre ayarla

void setup() {
  for (int i = 0; i < 3; i++) {   // 3 kez tekrarla: devre hazır sinyali
    tone(BUZZER, 1000);
    delay(100);
    noTone(BUZZER);
    delay(100);
  }
}

void loop() {
  while (analogRead(LDR_PIN) < ESIK) {   // karanlık sürdükçe
    tone(BUZZER, 800);                   // alarm çalmaya devam et
  }
  noTone(BUZZER);                        // aydınlık: sus
}
