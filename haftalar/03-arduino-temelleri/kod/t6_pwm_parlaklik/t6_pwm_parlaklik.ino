/*
  ================================================================
   T6  -  NEFES ALAN LED (PWM)
  ================================================================
   Öğreneceklerin:  analogWrite, PWM, adımlı for döngüsü
   (Arduino Temelleri PDF: bölüm 5)

   LED: satır 1 (A3) ve sütun 3 (pin 5). Pin 5 "~" işaretli bir PWM
   pinidir, yani analogWrite ile 0-255 arası değer alabilir.

   TERS MANTIK: LED'in eksi ucu sütun pinine bağlı. Sütun LOW (0)
   olunca LED yanar. Bu yüzden
       analogWrite(5, 0)    ->  LED TAM PARLAK
       analogWrite(5, 255)  ->  LED SÖNÜK
   Kodda "255 - parlaklik" yazarak bunu düzeltiyoruz.

   GÖREVLER
   9. sınıf
   1) LED daha hızlı / daha yavaş nefes alsın.
   2) "255 - parlaklik" yerine sadece "parlaklik" yaz. Ne değişti? Neden?
   3) LED tamamen sönmesin, en az yarı parlak kalsın.
   10. sınıf
   4) Butona basılıyken parlaklık artsın, bırakınca yavaşça azalsın.
   5) Sütun 7 (pin 11) de PWM pinidir. İkinci LED'i ilkinin tersine
      nefes aldır: biri parlarken diğeri sönsün.
  ================================================================
*/

const int LED_SATIR = A3;   // satır 1
const int LED_SUTUN = 5;    // sütun 3 (PWM pini)

void setup() {
  pinMode(LED_SATIR, OUTPUT);
  pinMode(LED_SUTUN, OUTPUT);
  digitalWrite(LED_SATIR, HIGH);       // satır hep açık, ışığı sütun ayarlıyor
}

void loop() {
  for (int parlaklik = 0; parlaklik <= 255; parlaklik = parlaklik + 5) {
    analogWrite(LED_SUTUN, 255 - parlaklik);   // yavaşça parla
    delay(20);
  }
  for (int parlaklik = 255; parlaklik >= 0; parlaklik = parlaklik - 5) {
    analogWrite(LED_SUTUN, 255 - parlaklik);   // yavaşça sön
    delay(20);
  }
}
