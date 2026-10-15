/*
  ================================================================
   T08  -  NEFES ALAN LED  ·  GÖREV CEVAPLARI
  ================================================================
   Kullanım: GOREV sayısını 1-3 arasında değiştir ve yükle.
   Devre:    T08 devresi. Kabloya dokunma.

   SORULARIN CEVAPLARI
   Görev 1 - delay(6) yerine delay(3). Bir nefes 2 x 256 adım:
     6 ms ile ~3 saniye, 3 ms ile ~1,5 saniye.
   Görev 2 - Sütun 1 (pin 13) ~1,5 saniye tam yanar, ~1,5 saniye tam
     söner; arada kısılma yok. 13, kartta ~ işareti olmayan bir pin:
     PWM yapamaz. analogWrite böyle bir pinde digitalWrite gibi davranır:
         değer 128'den küçük -> LOW,   128 ve üstü -> HIGH
     Karttaki L LED'i de 13'e bağlı; o da ters sırayla yanıp söner.
   Görev 3 - parlaklik sınırların dışına çıkarsa (256, -1) analogWrite
     yanlış değer alır; bu yüzden 0 ile 255 arasında tutuyoruz.
  ================================================================
*/

const int GOREV = 1;     // <-- 1, 2 ya da 3

const int SATIR_1 = A3;
const int SUTUN_1 = 13;    // PWM DEĞİL
const int SUTUN_3 = 5;     // PWM pini (~5)
const int BUTON = A4;

int parlaklik = 0;         // Görev 3

void setup() {
  pinMode(SATIR_1, OUTPUT);
  pinMode(SUTUN_1, OUTPUT);
  pinMode(SUTUN_3, OUTPUT);
  digitalWrite(SUTUN_1, HIGH);   // ikisi de sönük başlasın
  digitalWrite(SUTUN_3, HIGH);
  digitalWrite(SATIR_1, HIGH);
  pinMode(BUTON, INPUT_PULLUP);
}

void loop() {
  if (GOREV == 1) {                                          // iki kat hızlı
    for (int p = 0; p <= 255; p++) { analogWrite(SUTUN_3, 255 - p); delay(3); }
    for (int p = 255; p >= 0; p--) { analogWrite(SUTUN_3, 255 - p); delay(3); }
  }

  if (GOREV == 2) {                                          // PWM olmayan pin
    for (int p = 0; p <= 255; p++) { analogWrite(SUTUN_1, 255 - p); delay(6); }
    for (int p = 255; p >= 0; p--) { analogWrite(SUTUN_1, 255 - p); delay(6); }
  }

  if (GOREV == 3) {                                          // butonla parlaklık
    if (digitalRead(BUTON) == LOW) {
      parlaklik = parlaklik + 5;                             // basılı: hızlı artar
    } else {
      parlaklik = parlaklik - 1;                             // bırakık: yavaş azalır
    }
    if (parlaklik > 255) parlaklik = 255;
    if (parlaklik < 0)   parlaklik = 0;
    analogWrite(SUTUN_3, 255 - parlaklik);
    delay(10);
  }
}
