/*
  ================================================================
   T11  -  TAM MATRİS
  ================================================================
   Yeni kavramlar:  iki boyut (satır + sütun), iç içe for
   Devre:           T10 + kalan 6 satır + kalan 5 sütun hattı
                    (Bitince Stacker devresinin aynısı olur.)

   16 kablo ile 64 LED'e ulaşıyoruz. Bir LED'in adresi iki sayıdır:
   satır ve sütun. İki for iç içe:
       dış döngü  s : 0 ... 7   (satırlar, yukarıdan aşağı)
       iç döngü   k : 0 ... 7   (sütunlar, soldan sağa)
   İç döngü bir satırı baştan sona bitirmeden dış döngü ilerlemez.
   Nokta ekranı kitap okur gibi satır satır gezer.

   GÖREVLER
   9. sınıf
   1) Nokta ekranı sütun sütun gezsin (yukarıdan aşağı, sonra sağa).
      İpucu: iki for satırının yerini değiştir.
   2) Sadece çerçeve: nokta yalnızca kenardaki LED'lerde dursun.
      İpucu: if (s == 0 || s == 7 || k == 0 || k == 7)
   10. sınıf
   3) Nokta sadece köşegende gezsin: (0,0), (1,1) ... (7,7).
      Tek bir for yeter mi? Neden?
  ================================================================
*/

const int SATIR[8] = {A3, 12, 9, A0, 2, 8, 3, 6};     // satır 1 ... 8
const int SUTUN[8] = {13, 4, 5, A2, 7, A1, 11, 10};   // sütun 1 ... 8

int bekleme = 60;

void hepsiniSondur() {
  for (int i = 0; i < 8; i++) {
    digitalWrite(SATIR[i], LOW);
    digitalWrite(SUTUN[i], HIGH);
  }
}

void ledYak(int s, int k) {
  hepsiniSondur();
  digitalWrite(SATIR[s], HIGH);
  digitalWrite(SUTUN[k], LOW);
}

void setup() {
  for (int i = 0; i < 8; i++) {
    pinMode(SATIR[i], OUTPUT);
    pinMode(SUTUN[i], OUTPUT);
  }
  hepsiniSondur();
}

void loop() {
  for (int s = 0; s < 8; s++) {        // her satır için
    for (int k = 0; k < 8; k++) {      //   o satırın her sütunu için
      ledYak(s, k);
      delay(bekleme);
    }
  }
}
