/*
  ================================================================
   T04  -  KOŞAN IŞIK (3 LED)
  ================================================================
   Yeni kavramlar:  aynı işi tekrar eden kod (ve bunun zahmeti)
   Devre:           T03 + sütun 3 hattı (a8 -> direnç -> D5)

   Üç LED soldan sağa sırayla yanar: ışık koşuyormuş gibi görünür.
   Kodun loop kısmına bak: aynı üç satır üç kez tekrar ediyor.
   LED sayısı 8 olsaydı 24 satır yazacaktık. T05'te bunu kısaltacağız.

   GÜVENLİK KURALI
   Bir satırda aynı anda EN FAZLA 3 LED yanabilir. Hepsinin akımı
   aynı satır pininden çıkar: 3 x 13 mA ~ 39 mA, pinin sınırı 40 mA.

   GÖREVLER
   9. sınıf
   1) Işık ters yönde, sağdan sola koşsun.
   2) Işık gidip gelsin: 1 - 2 - 3 - 2 - 1 ...
   10. sınıf
   3) Üç LED birlikte yanıp sönsün. A3 pininden kaç mA çıkıyor?
      Dördüncü bir LED eklemek neden yasak?
  ================================================================
*/

const int SATIR_1 = A3;
const int SUTUN_1 = 13;
const int SUTUN_2 = 4;
const int SUTUN_3 = 5;

int bekleme = 200;

void setup() {
  pinMode(SATIR_1, OUTPUT);
  pinMode(SUTUN_1, OUTPUT);
  pinMode(SUTUN_2, OUTPUT);
  pinMode(SUTUN_3, OUTPUT);
  digitalWrite(SUTUN_1, HIGH);
  digitalWrite(SUTUN_2, HIGH);
  digitalWrite(SUTUN_3, HIGH);
  digitalWrite(SATIR_1, HIGH);
}

void loop() {
  digitalWrite(SUTUN_1, LOW);    // 1. LED
  delay(bekleme);
  digitalWrite(SUTUN_1, HIGH);

  digitalWrite(SUTUN_2, LOW);    // 2. LED
  delay(bekleme);
  digitalWrite(SUTUN_2, HIGH);

  digitalWrite(SUTUN_3, LOW);    // 3. LED
  delay(bekleme);
  digitalWrite(SUTUN_3, HIGH);
}
