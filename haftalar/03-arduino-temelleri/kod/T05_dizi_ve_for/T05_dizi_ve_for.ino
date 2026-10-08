/*
  ================================================================
   T05  -  DİZİ VE FOR
  ================================================================
   Yeni kavramlar:  dizi [ ], for döngüsü
   Devre:           T04 ile aynı. Kabloya dokunma.

   T04'teki koşan ışığın aynısı, ama 12 satır yerine 3 satır.
       Dizi  : aynı türden sayıları tek bir isimde sıralar.
               SUTUN[0] = 13,  SUTUN[1] = 4,  SUTUN[2] = 5
               Sayma 0'dan başlar!
       for   : bir işi belli sayıda tekrar eder.
               for (int i = 0; i < 3; i++)  ->  i önce 0, sonra 1, sonra 2

   GÖREVLER
   9. sınıf
   1) Işık sağdan sola koşsun. (İpucu: i 2'den başlasın, i-- ile azalsın.)
   2) Dizideki sırayı {5, 13, 4} yap. Ne değişti? loop'a dokundun mu?
   10. sınıf
   3) Işık gidip gelsin: biri ileri, biri geri iki for döngüsü kullan.
  ================================================================
*/

const int SATIR_1 = A3;
const int SUTUN[3] = {13, 4, 5};   // soldan sağa üç LED'in katodu

int bekleme = 200;

void setup() {
  pinMode(SATIR_1, OUTPUT);
  for (int i = 0; i < 3; i++) {
    pinMode(SUTUN[i], OUTPUT);
    digitalWrite(SUTUN[i], HIGH);  // hepsi sönük başlasın
  }
  digitalWrite(SATIR_1, HIGH);
}

void loop() {
  for (int i = 0; i < 3; i++) {
    digitalWrite(SUTUN[i], LOW);   // i. LED yanar
    delay(bekleme);
    digitalWrite(SUTUN[i], HIGH);  // i. LED söner
  }
}
