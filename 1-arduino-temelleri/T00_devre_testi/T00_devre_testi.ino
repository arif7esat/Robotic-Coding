/*
  T00 - DEVRE TESTİ (T01 devresi: satır 1 -> A3, sütun 1 -> direnç -> 13)
  Seri Monitör: 9600

  Sırayla iki durum dener, her biri 1 saniye:
    DURUM 1: A3 HIGH, 13 LOW   -> normal yön (satır anot)
    DURUM 2: A3 LOW,  13 HIGH  -> ters yön  (karttaki L LED'i de yanar)

  Gözlem:
    - Matris LED'i L LED'i SÖNÜKKEN yanıyor  -> devre doğru, T01 çalışmalı
    - Matris LED'i L LED'i ile BİRLİKTE yanıyor -> LED yönü ters
      (matris ortak katot ya da satır/sütun kabloları yer değiştirmiş)
    - Matris LED'i hiç yanmıyor -> kablo deliği yanlış ya da matris
      180° ters takılı (j12 ve j8 o zaman ikisi de satır bacağı olur)
*/

void setup() {
  pinMode(A3, OUTPUT);
  pinMode(13, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  digitalWrite(A3, HIGH); digitalWrite(13, LOW);
  Serial.println("DURUM 1: A3 HIGH, 13 LOW  (normal)");
  delay(1000);
  digitalWrite(A3, LOW); digitalWrite(13, HIGH);
  Serial.println("DURUM 2: A3 LOW, 13 HIGH  (ters)");
  delay(1000);
}
