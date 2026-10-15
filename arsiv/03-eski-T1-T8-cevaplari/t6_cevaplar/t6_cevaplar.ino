/*
  ================================================================
   T6  -  NEFES ALAN LED  ·  GÖREV CEVAPLARI
  ================================================================
   Kullanım: GOREV sayısını 1-5 arasında değiştir ve yükle.

   DEVRE EKLERİ (T6 devresinde olmayan parçalar)
   Görev 4: buton eklenmeli (T4 ile aynı)
            buton bacakları d47 d49 g47 g49 · b47 → A4 (yeşil) ·
            h49 → üst − hattı · Arduino GND → üst − hattı
   Görev 5: sütun 7 eklenmeli
            sütun 7 : j6 → j35 (turuncu), direnç i35–i39, j39 → D11 (sarı)

   SORULARIN CEVAPLARI
   Görev 2 - "255 - parlaklik" silinince (GOREV = 2) LED ters nefes alır:
     kod "parla" derken söner, "sön" derken parlar. Çünkü PWM sinyali
     LED'in eksi ucuna (sütuna) gidiyor; pin LOW iken LED yanar.
     analogWrite(5, 0) = tam parlak, analogWrite(5, 255) = sönük.
   Görev 3 - Parlaklık 128'in altına inmesin: döngü 0 yerine 128'den
     başlar ve 128'de durur. LED hiç sönmez, yarı parlakla tam parlak
     arasında gidip gelir.
  ================================================================
*/

const int GOREV = 1;     // <-- 1 ... 5

const int LED_SATIR = A3;   // satır 1
const int LED_SUTUN = 5;    // sütun 3 (PWM)
const int LED2_SUTUN = 11;  // görev 5: sütun 7 (PWM)
const int BUTON = A4;       // görev 4

int parlaklik = 0;          // görev 4

void setup() {
  pinMode(LED_SATIR, OUTPUT);
  pinMode(LED_SUTUN, OUTPUT);
  digitalWrite(LED_SATIR, HIGH);
  if (GOREV == 4) pinMode(BUTON, INPUT_PULLUP);
  if (GOREV == 5) pinMode(LED2_SUTUN, OUTPUT);
}

void loop() {
  if (GOREV == 1) {                                  // daha hızlı nefes
    for (int p = 0; p <= 255; p = p + 15) { analogWrite(LED_SUTUN, 255 - p); delay(15); }
    for (int p = 255; p >= 0; p = p - 15) { analogWrite(LED_SUTUN, 255 - p); delay(15); }
  }
  if (GOREV == 2) {                                  // ters mantık deneyi
    for (int p = 0; p <= 255; p = p + 5) { analogWrite(LED_SUTUN, p); delay(20); }
    for (int p = 255; p >= 0; p = p - 5) { analogWrite(LED_SUTUN, p); delay(20); }
  }
  if (GOREV == 3) {                                  // en az yarı parlak
    for (int p = 128; p <= 255; p = p + 3) { analogWrite(LED_SUTUN, 255 - p); delay(20); }
    for (int p = 255; p >= 128; p = p - 3) { analogWrite(LED_SUTUN, 255 - p); delay(20); }
  }
  if (GOREV == 4) {                                  // butonla parlaklık
    if (digitalRead(BUTON) == LOW) parlaklik = parlaklik + 5;   // basılı: art
    else                           parlaklik = parlaklik - 2;   // bırakık: yavaşça azal
    if (parlaklik > 255) parlaklik = 255;
    if (parlaklik < 0)   parlaklik = 0;
    analogWrite(LED_SUTUN, 255 - parlaklik);
    delay(20);
  }
  if (GOREV == 5) {                                  // iki LED ters fazda
    for (int p = 0; p <= 255; p = p + 5) {
      analogWrite(LED_SUTUN, 255 - p);               // biri parlar
      analogWrite(LED2_SUTUN, p);                    // diğeri söner
      delay(20);
    }
    for (int p = 255; p >= 0; p = p - 5) {
      analogWrite(LED_SUTUN, 255 - p);
      analogWrite(LED2_SUTUN, p);
      delay(20);
    }
  }
}
