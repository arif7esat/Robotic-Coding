/*
  ================================================================
   S01  -  IŞIK THEREMİNİ
  ================================================================
   Elini ışık sensörünün (LDR) üstünde gezdir:
   ışık azaldıkça ses kalınlaşır, ışık arttıkça incelir.

   Devre: LDR      -> 5V ile A0 arasında
          10k      -> A0 ile GND arasında
          Buzzer   -> + bacak A5, - bacak GND (PASİF buzzer)
  ================================================================
*/

const int LDR_PIN = A0;   // ışığı okuduğumuz pin
const int BUZZER  = A5;   // pasif buzzer

void setup() {
  Serial.begin(9600);     // öğretmen bilgisayarında ışık değerini izlemek için
}

void loop() {
  int isik = analogRead(LDR_PIN);            // 0 (karanlık) ... 1023 (çok aydınlık)
  int ses  = map(isik, 0, 1023, 100, 2000);  // ışık sayısını ses frekansına (Hz) çevir
  tone(BUZZER, ses);                         // buzzer saniyede "ses" kez titrer
  Serial.println(isik);                      // Seri Monitör'de ışık değeri
  delay(10);
}
