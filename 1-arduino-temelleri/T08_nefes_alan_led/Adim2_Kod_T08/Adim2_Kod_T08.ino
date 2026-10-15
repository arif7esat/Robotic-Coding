/*
  ================================================================
   T08  -  NEFES ALAN LED (PWM)
  ================================================================
   Yeni kavramlar:  analogWrite, PWM, 0-255 arası değer
   Devre:           T07 ile aynı. Kabloya dokunma.

   digitalWrite sadece iki şey bilir: açık ya da kapalı.
   analogWrite(pin, değer) pini saniyede ~1000 kez açıp kapatır:
       0   -> hep LOW       255 -> hep HIGH       128 -> yarı yarıya
   Bu sadece kartta ~ işareti olan pinlerde çalışır: 3, 5, 6, 9, 10, 11.
   Bizim 3 LED'den sadece sütun 3 (pin 5) böyle bir pine bağlı.

   TERS MANTIK
   Pin 5 LED'in katoduna (-) bağlı: pin LOW iken LED yanar. Bu yüzden
   parlaklığı "255 - parlaklik" olarak gönderiyoruz.

   GÖREVLER
   9. sınıf
   1) LED iki kat hızlı nefes alsın.
   2) SUTUN_3 yerine 13 yaz (sütun 1). LED ne yapıyor? Neden kısılmıyor?
   10. sınıf
   3) Butonla parlaklık: basılıyken parlaklık artsın, bırakınca
      yavaşça azalsın. (İpucu: parlaklığı 0 ile 255 arasında tut.)
  ================================================================
*/

const int SATIR_1 = A3;
const int SUTUN_3 = 5;     // PWM pini (~5)

void setup() {
  pinMode(SATIR_1, OUTPUT);
  pinMode(SUTUN_3, OUTPUT);
  digitalWrite(SATIR_1, HIGH);
}

void loop() {
  for (int parlaklik = 0; parlaklik <= 255; parlaklik++) {   // parla
    analogWrite(SUTUN_3, 255 - parlaklik);
    delay(6);
  }
  for (int parlaklik = 255; parlaklik >= 0; parlaklik--) {   // sön
    analogWrite(SUTUN_3, 255 - parlaklik);
    delay(6);
  }
}
