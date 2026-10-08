/*
  ================================================================
   T8  -  GÖZ YANILMASI: matris aslında nasıl resim çizer?
  ================================================================
   Öğreneceklerin:  çoklama (multiplexing), görme sürekliliği
   (Kodların Mantığı PDF: bölüm 1 ve 5)

   Hedef: (satır 1, sütun 3) ve (satır 2, sütun 5) AYNI ANDA yansın.

   ADIM 1 - HAYALET DENEYİ: HAYALET_DENEYI = true yap ve yükle.
            İki satırı ve iki sütunu aynı anda açıyoruz. Kaç LED yandı?
            İstemediğimiz 2 "hayalet" LED de yanar!

   ADIM 2 - ÇÖZÜM: HAYALET_DENEYI = false yap. Şimdi iki LED'i SIRAYLA
            yakıyoruz. bekleme = 500 ile başla: LED'ler sırayla yanar.
            Sonra bekleme değerini 100, 20, 5, 1 yap ve her seferinde
            yükle. Bir noktadan sonra gözün ikisini AYNI ANDA yanıyor sanır!
            Sinema ve bütün LED ekranlar bu hileyle çalışır.

   GÖREVLER
   9. sınıf
   1) Titremenin tamamen kaybolduğu bekleme değerini bul ve not et.
   2) Üçüncü bir LED ekleyerek bir üçgen çiz.
   10. sınıf
   3) 4 LED ile bir kare çiz (her LED farklı satır ya da sütunda).
   4) Gülen bir yüz çiz: her satırı sırayla aç, o satırdaki LED'lerin
      sütunlarını LOW yap. Kural: bir satırda en fazla 3 LED!
      (matris.h tam olarak bunu senin yerine yapıyordu.)
  ================================================================
*/

const bool HAYALET_DENEYI = false;
int bekleme = 500;          // 500 -> 100 -> 20 -> 5 -> 1 dene!

const int SATIR[8] = {A3, 12, 9, A0, 2, 8, 3, 6};
const int SUTUN[8] = {13, 4, 5, A2, 7, A1, 11, 10};

void hepsiniSondur() {
  for (int i = 0; i < 8; i++) {
    digitalWrite(SATIR[i], LOW);
    digitalWrite(SUTUN[i], HIGH);
  }
}

void ledYak(int satir, int sutun) {
  hepsiniSondur();
  digitalWrite(SATIR[satir], HIGH);
  digitalWrite(SUTUN[sutun], LOW);
}

void setup() {
  for (int i = 0; i < 8; i++) {
    pinMode(SATIR[i], OUTPUT);
    pinMode(SUTUN[i], OUTPUT);
  }
  hepsiniSondur();
}

void loop() {
  if (HAYALET_DENEYI) {
    // Satır 1 ve 2 açık, sütun 3 ve 5 açık -> 4 kesişim yanar
    hepsiniSondur();
    digitalWrite(SATIR[0], HIGH);
    digitalWrite(SATIR[1], HIGH);
    digitalWrite(SUTUN[2], LOW);
    digitalWrite(SUTUN[4], LOW);
  } else {
    ledYak(0, 2);          // 1. an: sadece satır 1, sütun 3
    delay(bekleme);
    ledYak(1, 4);          // 2. an: sadece satır 2, sütun 5
    delay(bekleme);
  }
}
