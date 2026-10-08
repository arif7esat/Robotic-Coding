/*
  ================================================================
   T1  -  TEK LED  (yardımcı dosya yok, her şey açıkta)
  ================================================================
   Öğreneceklerin:  pinMode, digitalWrite, HIGH / LOW, delay
   (Arduino Temelleri PDF: bölüm 2, 3 ve 4)

   Matristeki her LED bir SATIR teli ile bir SÜTUN telinin kesiştiği
   yerdedir. Bir LED'in yanması için:
       satır pini  HIGH  (LED'in + ucu, 5 V)
       sütun pini  LOW   (LED'in - ucu, 0 V, 220 ohm direnç üzerinden)

   Bu projede sol üst köşedeki LED'i kullanıyoruz:
       satır 1  ->  A3 pini
       sütun 1  ->  13 pini

   Sadece iki pini OUTPUT yapıyoruz. Diğer pinlere dokunmadığımız
   için onlar "INPUT" kalır, yani elektrik vermez; diğer LED'ler yanmaz.

   GÖREVLER
   9. sınıf
   1) LED daha hızlı yanıp sönsün.
   2) Sağ alt köşedeki LED'i yak: satır 8 -> pin 6, sütun 8 -> pin 10.
   3) Satırı hep HIGH bırak, bu sefer SÜTUN pinini HIGH / LOW yap.
      LED hangisinde yanıyor? Neden tersi?
   10. sınıf
   4) Aynı satırdaki iki LED sırayla yansın (sütun 1 ve sütun 2 = pin 4).
   5) Karttaki küçük "L" LED'i de 13 numaralı pine bağlıdır.
      Matristeki LED yanarken L LED'i neden sönüyor? Açıkla.
  ================================================================
*/

void setup() {
  pinMode(A3, OUTPUT);      // satır 1 artık çıkış
  pinMode(13, OUTPUT);      // sütun 1 artık çıkış
  digitalWrite(13, LOW);    // sütun LOW: LED'in eksi ucu 0 V'a bağlandı
}

void loop() {
  digitalWrite(A3, HIGH);   // satır HIGH: akım akar, LED yanar
  delay(500);
  digitalWrite(A3, LOW);    // iki uç da 0 V: akım yok, LED söner
  delay(500);
}
