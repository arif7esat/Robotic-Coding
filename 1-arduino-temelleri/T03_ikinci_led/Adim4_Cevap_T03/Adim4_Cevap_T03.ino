/*
  ================================================================
   T03  -  İKİNCİ LED  ·  GÖREV CEVAPLARI
  ================================================================
   Kullanım: GOREV sayısını 1-3 arasında değiştir ve yükle.
   Devre:    T03 devresi. Kabloya dokunma.

   SORULARIN CEVAPLARI
   Görev 1 - İki LED birlikte yanınca A3 pininden ikisinin akımı
     birlikte çıkar: ~2 x 13 mA = ~26 mA. Pinin sınırı 40 mA; güvenli.
   Görev 2 - Kodda tek değişiklik: bekleme = 100. Sırayla yer değiştirme
     zaten T03'ün kendi davranışı.
   Görev 3 - for döngüsünü henüz bilmiyoruz; bu yüzden aynı satırlar
     tekrar ediyor. T05'te bunu kısaltacağız.
  ================================================================
*/

const int GOREV = 1;     // <-- 1, 2 ya da 3

const int SATIR_1 = A3;
const int SUTUN_1 = 13;  // sol LED
const int SUTUN_2 = 4;   // sağ LED

int bekleme = 400;

void setup() {
  pinMode(SATIR_1, OUTPUT);
  pinMode(SUTUN_1, OUTPUT);
  pinMode(SUTUN_2, OUTPUT);
  digitalWrite(SUTUN_1, HIGH);
  digitalWrite(SUTUN_2, HIGH);
  digitalWrite(SATIR_1, HIGH);
  if (GOREV == 2) bekleme = 100;
  if (GOREV == 3) bekleme = 80;
}

void loop() {
  if (GOREV == 1) {              // birlikte yan, birlikte sön
    digitalWrite(SUTUN_1, LOW);
    digitalWrite(SUTUN_2, LOW);
    delay(bekleme);
    digitalWrite(SUTUN_1, HIGH);
    digitalWrite(SUTUN_2, HIGH);
    delay(bekleme);
  }
  if (GOREV == 2) {              // sırayla, 100 ms
    digitalWrite(SUTUN_1, LOW);
    delay(bekleme);
    digitalWrite(SUTUN_1, HIGH);
    digitalWrite(SUTUN_2, LOW);
    delay(bekleme);
    digitalWrite(SUTUN_2, HIGH);
  }
  if (GOREV == 3) {              // polis lambası
    digitalWrite(SUTUN_1, LOW);  delay(bekleme);   // sol: 1
    digitalWrite(SUTUN_1, HIGH); delay(bekleme);
    digitalWrite(SUTUN_1, LOW);  delay(bekleme);   // sol: 2
    digitalWrite(SUTUN_1, HIGH); delay(bekleme);

    digitalWrite(SUTUN_2, LOW);  delay(bekleme);   // sağ: 1
    digitalWrite(SUTUN_2, HIGH); delay(bekleme);
    digitalWrite(SUTUN_2, LOW);  delay(bekleme);   // sağ: 2
    digitalWrite(SUTUN_2, HIGH); delay(bekleme);
  }
}
