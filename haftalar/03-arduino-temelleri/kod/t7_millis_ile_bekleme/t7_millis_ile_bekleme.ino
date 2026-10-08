/*
  ================================================================
   T7  -  AYNI ANDA İKİ İŞ: delay mi, millis mi?
  ================================================================
   Öğreneceklerin:  millis, unsigned long, bool, delay'in sorunu
   (Arduino Temelleri PDF: bölüm 6)

   İki LED aynı satırda (satır 1):
       LED A (sütun 1, pin 13)  ->  kendi kendine yarım saniyede bir yanıp söner
       LED B (sütun 8, pin 10)  ->  butona basılıyken yanar

   DENEY: Aşağıdaki KULLAN_DELAY değerini önce true yap ve yükle.
   Butona bas: LED B geç tepki veriyor, çünkü delay sırasında Arduino
   butona bakamıyor. Sonra false yap ve tekrar dene: anında tepki!

   GÖREVLER
   9. sınıf
   1) Deneyi yap: true ve false arasındaki farkı arkadaşına anlat.
   2) LED A saniyede bir yanıp sönsün.
   10. sınıf
   3) Üçüncü bir LED (sütun 4, pin A2) farklı bir hızda, 300 ms'de bir
      yanıp sönsün. Kendi "sonDegisim" değişkeni olmalı.
   4) Butona basılıyken LED A'nın hızı iki katına çıksın.
  ================================================================
*/

const bool KULLAN_DELAY = false;   // true: eski yöntem, false: millis

const int SATIR_1 = A3;
const int LED_A   = 13;    // sütun 1
const int LED_B   = 10;    // sütun 8
const int BUTON   = A4;

unsigned long sonDegisim = 0;   // LED A en son ne zaman değişti?
bool ledAYanik = false;

void setup() {
  pinMode(SATIR_1, OUTPUT);
  pinMode(LED_A, OUTPUT);
  pinMode(LED_B, OUTPUT);
  pinMode(BUTON, INPUT_PULLUP);
  digitalWrite(SATIR_1, HIGH);   // satır açık; LED'leri sütunlarla kontrol ediyoruz
  digitalWrite(LED_A, HIGH);     // sütun HIGH = sönük
  digitalWrite(LED_B, HIGH);
}

void loop() {
  // ---- LED A: yanıp sönme ----
  if (KULLAN_DELAY) {
    digitalWrite(LED_A, LOW);  delay(500);    // bu 1 saniye boyunca
    digitalWrite(LED_A, HIGH); delay(500);    // buton okunmuyor!
  } else {
    if (millis() - sonDegisim >= 500) {       // 500 ms geçti mi?
      sonDegisim = millis();
      ledAYanik = !ledAYanik;                 // durumu tersine çevir
      if (ledAYanik) digitalWrite(LED_A, LOW);
      else           digitalWrite(LED_A, HIGH);
    }
  }

  // ---- LED B: buton ----
  if (digitalRead(BUTON) == LOW) digitalWrite(LED_B, LOW);    // yan
  else                           digitalWrite(LED_B, HIGH);   // sön
}
