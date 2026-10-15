/*
  ================================================================
   T01  -  TEK LED  ·  GÖREV CEVAPLARI
  ================================================================
   Kullanım: GOREV sayısını 1-3 arasında değiştir ve yükle.
   Devre:    T01 devresi. Kabloya dokunma.

   SORULARIN CEVAPLARI
   Görev 3 - LED, 13 LOW iken yanar, 13 HIGH iken söner: T01'in tersi.
     13 numaralı pin LED'in eksi (katot) ucudur. Akım ancak artı uç
     (A3, 5 V) eksi uçtan yüksekteyse akar:
         A3 5 V, 13 0 V  ->  fark 5 V  ->  LED yanar
         A3 5 V, 13 5 V  ->  fark yok  ->  LED söner
     Bonus gözlem: Karttaki küçük "L" LED'i de 13. pine bağlıdır ama
     GND'ye doğru bağlıdır, yani 13 HIGH iken yanar. Görev 3'te matris
     LED'i ile L LED'i sırayla yanar: biri yanarken öteki söner.
  ================================================================
*/

const int GOREV = 1;     // <-- 1, 2 ya da 3

void setup() {
  pinMode(A3, OUTPUT);
  pinMode(13, OUTPUT);
  if (GOREV == 3) {
    digitalWrite(A3, HIGH);   // satır hep açık
  } else {
    digitalWrite(13, LOW);    // sütun hep 0 V
  }
}

void loop() {
  if (GOREV == 1) {           // daha hızlı: 500 yerine 150
    digitalWrite(A3, HIGH);
    delay(150);
    digitalWrite(A3, LOW);
    delay(150);
  }
  if (GOREV == 2) {           // kısa yanık, uzun sönük
    digitalWrite(A3, HIGH);
    delay(100);
    digitalWrite(A3, LOW);
    delay(900);
  }
  if (GOREV == 3) {           // bu sefer sütun pini değişiyor
    digitalWrite(13, LOW);    // katot 0 V: LED yanar (L LED'i söner)
    delay(5000);
    digitalWrite(13, HIGH);   // katot 5 V: LED söner (L LED'i yanar)
    delay(5000);
  }
}
