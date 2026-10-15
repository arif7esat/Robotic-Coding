/*
  ================================================================
   T02  -  DEĞİŞKENLE HIZ  ·  GÖREV CEVAPLARI
  ================================================================
   Kullanım: GOREV sayısını 1-3 arasında değiştir ve yükle.
   Devre:    T01 devresi. Kabloya dokunma.

   SORULARIN CEVAPLARI
   Görev 1 - Tek satır: int bekleme = 150;  T01'de iki delay satırını
     ayrı ayrı düzeltmek gerekiyordu. Değişkenin faydası bu.
   Görev 3 - Seri Monitör'ü aç (9600). bekleme her turda 50 azalır:
     500, 450, ... 50, 0, -50. delay() negatif sayı bilmez; -50'yi dev
     bir pozitif sayı olarak okur (4 294 967 246 ms, yaklaşık 50 gün).
     LED tam o anda yanık (HIGH'tan hemen sonraki delay) ve 50 gün
     yanık kalır: "takıldı" gibi görünür. Seri Monitör'de son satır -50.
     Düzeltme: bekleme 50'nin altına inince yeniden 500 yap
       if (bekleme < 50) bekleme = 500;
  ================================================================
*/

const int GOREV = 1;     // <-- 1, 2 ya da 3

const int SATIR_1 = A3;
const int SUTUN_1 = 13;

int bekleme = 150;       // Görev 1: tek satır değişti
int yanikSure = 100;     // Görev 2
int sonukSure = 900;     // Görev 2

void setup() {
  pinMode(SATIR_1, OUTPUT);
  pinMode(SUTUN_1, OUTPUT);
  digitalWrite(SUTUN_1, LOW);
  if (GOREV == 3) {
    bekleme = 500;
    Serial.begin(9600);
  }
}

void loop() {
  if (GOREV == 1) {
    digitalWrite(SATIR_1, HIGH);
    delay(bekleme);
    digitalWrite(SATIR_1, LOW);
    delay(bekleme);
  }
  if (GOREV == 2) {
    digitalWrite(SATIR_1, HIGH);
    delay(yanikSure);
    digitalWrite(SATIR_1, LOW);
    delay(sonukSure);
  }
  if (GOREV == 3) {
    Serial.println(bekleme);       // bekleme'nin değerini izle
    digitalWrite(SATIR_1, HIGH);
    delay(bekleme);
    digitalWrite(SATIR_1, LOW);
    delay(bekleme);
    bekleme = bekleme - 50;
  }
}
