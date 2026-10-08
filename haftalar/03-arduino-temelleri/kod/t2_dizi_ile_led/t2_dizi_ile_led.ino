/*
  ================================================================
   T2  -  DİZİ İLE İSTEDİĞİN LED'İ SEÇ
  ================================================================
   Öğreneceklerin:  dizi (liste), const, for, kendi fonksiyonunu yazmak
   (Arduino Temelleri PDF: bölüm 7, 9 ve 10)

   Matrisin bacakları içeride karışık bağlıdır. Hangi satırın hangi
   pine gittiğini bu iki liste tutar:
       SATIR[0] = A3  ->  1. satır (en üst)
       SUTUN[0] = 13  ->  1. sütun (en sol)
   Dikkat: Burada satır 0 EN ÜSTTEDİR (matrisin kendi numarası).

   Aynı anda sadece BİR LED yakıyoruz. Bu yüzden devre her zaman güvende.

   GÖREVLER
   9. sınıf
   1) Nokta köşeleri ters yönde dolaşsın.
   2) for döngüsüyle nokta sol üstten sağ alta çapraz yürüsün.
      İpucu: ledYak(i, i);
   3) Dört köşe yerine ekranın ortasındaki dört LED'i dolaş.
   10. sınıf
   4) İç içe for ile nokta bütün ekranı satır satır gezsin.
   5) Yılan gibi gezsin: tek satırlarda soldan sağa, çift satırlarda
      sağdan sola.  İpucu: if (satir % 2 == 0) ...
  ================================================================
*/

const int SATIR[8] = {A3, 12, 9, A0, 2, 8, 3, 6};    // satır 1..8
const int SUTUN[8] = {13, 4, 5, A2, 7, A1, 11, 10};  // sütun 1..8

// Bütün LED'leri söndür: satırlar LOW, sütunlar HIGH
void hepsiniSondur() {
  for (int i = 0; i < 8; i++) {
    digitalWrite(SATIR[i], LOW);
    digitalWrite(SUTUN[i], HIGH);
  }
}

// Önce her şeyi söndür, sonra sadece istenen LED'i yak
void ledYak(int satir, int sutun) {
  hepsiniSondur();
  digitalWrite(SATIR[satir], HIGH);
  digitalWrite(SUTUN[sutun], LOW);
}

void setup() {
  for (int i = 0; i < 8; i++) {      // 16 pinin hepsi çıkış
    pinMode(SATIR[i], OUTPUT);
    pinMode(SUTUN[i], OUTPUT);
  }
  hepsiniSondur();
}

void loop() {
  ledYak(0, 0);  delay(300);   // sol üst
  ledYak(0, 7);  delay(300);   // sağ üst
  ledYak(7, 7);  delay(300);   // sağ alt
  ledYak(7, 0);  delay(300);   // sol alt
}
