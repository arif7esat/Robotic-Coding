/*
  ================================================================
   T1  -  TEK LED  ·  GÖREV CEVAPLARI
  ================================================================
   Kullanım: GOREV sayısını 1-4 arasında değiştir ve yükle.

   DEVRE EKLERİ (T1 devresinde olmayan hatlar)
   Görev 2: satır 8 ve sütun 8 eklenmeli
            satır 8 : a9 → D6 (kırmızı, dirençsiz)
            sütun 8 : j5 → j41 (turuncu), direnç i41–i45, j45 → D10 (sarı)
   Görev 4: sütun 2 eklenmeli
            sütun 2 : a7 → b29 (turuncu), direnç d29–d33, b33 → D4 (sarı)

   SORULARIN CEVAPLARI
   Görev 3 - Satır hep HIGH, sütun yanıp sönüyor. LED sütun LOW iken yanar,
     HIGH iken söner: tersi! Çünkü sütun LED'in eksi (katot) ucudur. Akım
     ancak artı uç eksi uçtan yüksek gerilimdeyse akar: satır 5 V, sütun
     0 V olunca yanar; ikisi de 5 V olunca fark kalmaz, söner.
   Görev 5 - Karttaki L LED'i 13. pin ile GND arasına bağlıdır; yanması için
     13. pin HIGH olmalı. Matristeki LED'in yanması için ise 13. pin (sütun 1)
     LOW olmalı. T1'de 13. pin hep LOW tutulduğu için L LED'i hep söner.
     Aynı pin aynı anda hem HIGH hem LOW olamaz; ikisi asla birlikte yanmaz.
  ================================================================
*/

const int GOREV = 1;     // <-- 1, 2, 3 ya da 4

void setup() {
  pinMode(A3, OUTPUT);   // satır 1
  pinMode(13, OUTPUT);   // sütun 1
  if (GOREV == 1) {
    digitalWrite(13, LOW);
  }
  if (GOREV == 2) {      // sağ alt LED: satır 8 (D6) + sütun 8 (D10)
    pinMode(6, OUTPUT);
    pinMode(10, OUTPUT);
    digitalWrite(10, LOW);
  }
  if (GOREV == 3) {      // satır hep açık, sütun yanıp sönecek
    digitalWrite(A3, HIGH);
  }
  if (GOREV == 4) {      // aynı satırda iki LED: sütun 1 (13) ve sütun 2 (4)
    pinMode(4, OUTPUT);
    digitalWrite(A3, HIGH);
  }
}

void loop() {
  if (GOREV == 1) {                    // iki kat hızlı
    digitalWrite(A3, HIGH); delay(250);
    digitalWrite(A3, LOW);  delay(250);
  }
  if (GOREV == 2) {                    // sağ alt köşe yanıp söner
    digitalWrite(6, HIGH); delay(500);
    digitalWrite(6, LOW);  delay(500);
  }
  if (GOREV == 3) {                    // sütunu değiştir: LOW = yanar
    digitalWrite(13, LOW);  delay(500);
    digitalWrite(13, HIGH); delay(500);
  }
  if (GOREV == 4) {                    // sırayla: biri yanarken diğeri sönük
    digitalWrite(13, LOW);  digitalWrite(4, HIGH);  delay(300);
    digitalWrite(13, HIGH); digitalWrite(4, LOW);   delay(300);
  }
}
