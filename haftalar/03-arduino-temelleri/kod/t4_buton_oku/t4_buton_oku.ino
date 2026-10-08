/*
  ================================================================
   T4  -  BUTONU OKU
  ================================================================
   Öğreneceklerin:  digitalRead, INPUT_PULLUP, if / else, Serial
   (Arduino Temelleri PDF: bölüm 4, 9 ve 11)

   Buton A4 ile GND arasında. INPUT_PULLUP modunda Arduino pini
   içeriden 5 V'a çeker:
       buton bırakık  ->  digitalRead = HIGH (1)
       buton basılı   ->  digitalRead = LOW  (0)   (ters mantık!)

   Seri Monitörü aç (Araçlar > Seri Port Ekranı, 9600) ve butona
   basarken sayıların nasıl değiştiğini izle.

   GÖREVLER
   9. sınıf
   1) Ters çalışsın: basınca sönsün, bırakınca yansın.
   2) DENEY: INPUT_PULLUP yerine INPUT yaz. Butona basmadan elini
      kablolara yaklaştır ve Seri Monitörü izle. Ne görüyorsun?
      (Sonra geri INPUT_PULLUP yapmayı unutma.)
   10. sınıf
   3) Her BASIŞTA LED durum değiştirsin (bir yanık, bir sönük).
      İpucu: int onceki = HIGH;  ve  if (durum == LOW && onceki == HIGH)
   4) Butona kaç kez basıldığını Seri Monitöre yazdır.
  ================================================================
*/

const int BUTON = A4;
const int LED_SATIR = A3;   // satır 1
const int LED_SUTUN = 13;   // sütun 1

void setup() {
  pinMode(BUTON, INPUT_PULLUP);
  pinMode(LED_SATIR, OUTPUT);
  pinMode(LED_SUTUN, OUTPUT);
  digitalWrite(LED_SUTUN, LOW);
  Serial.begin(9600);
}

void loop() {
  int durum = digitalRead(BUTON);   // 1 (bırakık) ya da 0 (basılı)
  Serial.println(durum);

  if (durum == LOW) {               // basılı
    digitalWrite(LED_SATIR, HIGH);
  } else {                          // bırakık
    digitalWrite(LED_SATIR, LOW);
  }
  delay(50);                        // Seri Monitör çok hızlı akmasın
}
