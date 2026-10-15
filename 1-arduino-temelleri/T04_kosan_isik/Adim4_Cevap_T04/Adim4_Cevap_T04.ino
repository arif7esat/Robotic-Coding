/*
  ================================================================
   T04  -  KOŞAN IŞIK  ·  GÖREV CEVAPLARI
  ================================================================
   Kullanım: GOREV sayısını 1-3 arasında değiştir ve yükle.
   Devre:    T04 devresi. Kabloya dokunma.

   SORULARIN CEVAPLARI
   Görev 2 - Gidip gelmek: 1 - 2 - 3 - 2 ve loop başa döner. Son adımda
     1'i tekrar yakmıyoruz; loop zaten 1'den başlıyor, yoksa 1 iki kez
     üst üste yanar ve ışık uçta "takılmış" gibi görünür.
   Görev 3 - Üç LED'in akımı aynı satır pininden (A3) çıkar:
     3 x ~13 mA = ~39 mA. Arduino pininin sınırı 40 mA.
     Dördüncü LED: 4 x 13 = ~52 mA > 40 mA. Pin aşırı ısınır, zamanla
     bozulur. Kural: bir satırda aynı anda EN FAZLA 3 LED.
  ================================================================
*/

const int GOREV = 1;     // <-- 1, 2 ya da 3

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
  if (GOREV == 1) {              // sağdan sola: 3 - 2 - 1
    digitalWrite(SUTUN_3, LOW);  delay(bekleme);  digitalWrite(SUTUN_3, HIGH);
    digitalWrite(SUTUN_2, LOW);  delay(bekleme);  digitalWrite(SUTUN_2, HIGH);
    digitalWrite(SUTUN_1, LOW);  delay(bekleme);  digitalWrite(SUTUN_1, HIGH);
  }
  if (GOREV == 2) {              // gidip gelme: 1 - 2 - 3 - 2
    digitalWrite(SUTUN_1, LOW);  delay(bekleme);  digitalWrite(SUTUN_1, HIGH);
    digitalWrite(SUTUN_2, LOW);  delay(bekleme);  digitalWrite(SUTUN_2, HIGH);
    digitalWrite(SUTUN_3, LOW);  delay(bekleme);  digitalWrite(SUTUN_3, HIGH);
    digitalWrite(SUTUN_2, LOW);  delay(bekleme);  digitalWrite(SUTUN_2, HIGH);
  }
  if (GOREV == 3) {              // üçü birlikte: A3'ten ~39 mA
    digitalWrite(SUTUN_1, LOW);
    digitalWrite(SUTUN_2, LOW);
    digitalWrite(SUTUN_3, LOW);
    delay(500);
    digitalWrite(SUTUN_1, HIGH);
    digitalWrite(SUTUN_2, HIGH);
    digitalWrite(SUTUN_3, HIGH);
    delay(500);
  }
}
