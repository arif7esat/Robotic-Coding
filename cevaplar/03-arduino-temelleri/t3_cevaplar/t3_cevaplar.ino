/*
  ================================================================
   T3  -  SÜTUN VE AKIM  ·  GÖREV CEVAPLARI
  ================================================================
   Kullanım: GOREV sayısını 1-5 arasında değiştir ve yükle.
   Devre: T3 devresi (16 hat), ek gerekmez. Seri Monitör (görev 4): 9600.

   SORULARIN CEVAPLARI
   Görev 2 - Kod gerekmez (GOREV = 2 orijinal animasyonu oynatır).
     Parlaklık ilk birkaç LED'de belirgin düşer: 1 LED ~13 mA, 2 LED her
     biri ~6,5 mA, 3 LED ~4,3 mA. Göz parlaklık farkını oransal algıladığı
     için en büyük düşüş 1'den 2'ye geçerken fark edilir. Kesin "kaçıncı LED"
     cevabı yok; öğrencinin gözlemi doğrudur, önemli olan nedenini söylemesi:
     8 LED tek bir 220 Ω direnci paylaşıyor.
   Görev 4 - 13.0 / sayi yazılmalı. 13 / sayi yazılırsa iki tam sayı
     bölünür ve küsurat atılır: 13 / 3 = 4 olur (4,33 değil).
  ================================================================
*/

const int GOREV = 1;     // <-- 1 ... 5

const int SATIR[8] = {A3, 12, 9, A0, 2, 8, 3, 6};
const int SUTUN[8] = {13, 4, 5, A2, 7, A1, 11, 10};
const int ORTADAN[8] = {3, 4, 2, 5, 1, 6, 0, 7};   // görev 5: sütun sırası

void hepsiniSondur() {
  for (int i = 0; i < 8; i++) {
    digitalWrite(SATIR[i], LOW);
    digitalWrite(SUTUN[i], HIGH);
  }
}

void setup() {
  for (int i = 0; i < 8; i++) {
    pinMode(SATIR[i], OUTPUT);
    pinMode(SUTUN[i], OUTPUT);
  }
  hepsiniSondur();
  Serial.begin(9600);
}

void loop() {
  for (int k = 0; k < 8; k++) {
    int s = k;
    if (GOREV == 5) s = ORTADAN[k];         // ortadan dışa
    hepsiniSondur();
    digitalWrite(SUTUN[s], LOW);            // sadece bu sütun açık (güvenli)

    for (int i = 0; i < 8; i++) {
      int r = i;
      if (GOREV == 1) r = 7 - i;            // aşağıdan yukarı
      digitalWrite(SATIR[r], HIGH);

      if (GOREV == 4) {
        int yanan = i + 1;
        Serial.print("yanan LED: ");
        Serial.print(yanan);
        Serial.print(", LED basina ~");
        Serial.print(13.0 / yanan, 1);      // 1 basamak ondalık
        Serial.println(" mA");
      }

      if (GOREV == 3) delay(50);            // daha hızlı
      else            delay(150);
    }
    if (GOREV == 3) delay(150);
    else            delay(400);
  }
}
