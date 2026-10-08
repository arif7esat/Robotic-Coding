/*
  ================================================================
   T01  -  TEK LED
  ================================================================
   Yeni kavramlar:  setup / loop, pinMode, digitalWrite, HIGH / LOW, delay
   Devre:           1 satır kablosu + 1 sütun hattı (kablo, direnç, kablo)
                    Ayrıntı: T01_Devre_ve_Montaj.pdf

   Matristeki her LED bir SATIR teli ile bir SÜTUN telinin kesiştiği
   yerdedir. LED'in iki ucu var:
       anot  (+)  ->  satır 1  ->  A3 pini
       katot (-)  ->  sütun 1  ->  220 ohm direnç  ->  13 pini

   LED'in yanması için akım anottan girip katottan çıkmalı:
       A3  HIGH (5 V)   ve   13  LOW (0 V)

   GÖREVLER
   9. sınıf
   1) LED daha hızlı yanıp sönsün.
   2) LED kısa yansın, uzun sönsün: 100 ms yanık, 900 ms sönük.
   10. sınıf
   3) A3'ü hep HIGH bırak; bu sefer 13 numaralı pini HIGH / LOW yap.
      LED hangisinde yanıyor? Neden tersi oldu?
  ================================================================
*/

void setup() {
  pinMode(A3, OUTPUT);      // satır 1 artık çıkış
  pinMode(13, OUTPUT);      // sütun 1 artık çıkış
  digitalWrite(13, LOW);    // katot 0 V'a bağlandı
}

void loop() {
  digitalWrite(A3, HIGH);   // anot 5 V: akım akar, LED yanar
  delay(500);               // yarım saniye bekle
  digitalWrite(A3, LOW);    // iki uç da 0 V: akım yok, LED söner
  delay(500);
}
