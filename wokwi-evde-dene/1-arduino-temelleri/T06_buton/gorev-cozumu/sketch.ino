/*
  ================================================================
   T06  -  BUTON  ·  GÖREV CEVAPLARI
  ================================================================
   Kullanım: GOREV sayısını 1-3 arasında değiştir ve yükle.
   Devre:    T06 devresi. Kabloya dokunma.

   SORULARIN CEVAPLARI
   Görev 2 - Buton, koşan ışığın bir turu bittiğinde okunur. Turun
     ortasında bırakırsan ışık o turu bitirip öyle durur.
   Görev 3 - "Basılı mı?" değil, "az önce mi basıldı?" sorusu:
     şimdiki durum LOW ve bir önceki tur HIGH ise basış yeni olmuştur.
     onceki olmadan yazılırsa, basılı tuttuğun sürece ışık çok hızlı
     (delay(20) ile saniyede ~50 adım) ilerler ve rastgele bir LED'de kalır.
     delay(20): butonun metal yaprakları basınca birkaç ms sıçrar (bounce, "ark");
     bu kısa bekleme o titreşimi tek basış olarak saydırır.
  ================================================================
*/

const int GOREV = 1;     // <-- 1, 2 ya da 3

const int SATIR_1 = A3;
const int SUTUN[3] = {13, 4, 5};
const int BUTON = A4;

int onceki = HIGH;       // Görev 3: butonun bir önceki turdaki durumu
int sira = 0;            // Görev 3: şu an yanan LED (0, 1, 2)

void setup() {
  pinMode(SATIR_1, OUTPUT);
  for (int i = 0; i < 3; i++) {
    pinMode(SUTUN[i], OUTPUT);
    digitalWrite(SUTUN[i], HIGH);
  }
  digitalWrite(SATIR_1, HIGH);
  pinMode(BUTON, INPUT_PULLUP);
  if (GOREV == 3) digitalWrite(SUTUN[sira], LOW);   // ilk LED yanık başlar
}

void loop() {
  if (GOREV == 1) {                          // ters çalışma
    if (digitalRead(BUTON) == LOW) {         // basılı: sağ yanar
      digitalWrite(SUTUN[0], HIGH);
      digitalWrite(SUTUN[2], LOW);
    } else {                                 // bırakık: sol yanar
      digitalWrite(SUTUN[0], LOW);
      digitalWrite(SUTUN[2], HIGH);
    }
  }

  if (GOREV == 2) {                          // basılıyken koşan ışık
    if (digitalRead(BUTON) == LOW) {
      for (int i = 0; i < 3; i++) {
        digitalWrite(SUTUN[i], LOW);
        delay(200);
        digitalWrite(SUTUN[i], HIGH);
      }
    }
  }

  if (GOREV == 3) {                          // her basışta bir sonraki LED
    int durum = digitalRead(BUTON);
    if (durum == LOW && onceki == HIGH) {    // yeni basıldı
      digitalWrite(SUTUN[sira], HIGH);       // eskisi söner
      sira = sira + 1;
      if (sira == 3) sira = 0;               // sondan başa dön
      digitalWrite(SUTUN[sira], LOW);        // yenisi yanar
    }
    onceki = durum;
    delay(20);
  }
}
