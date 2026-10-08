/*
  ================================================================
   T03  -  İKİNCİ LED
  ================================================================
   Yeni kavramlar:  iki çıkışı ayrı ayrı yönetmek, sırayla yakmak
   Devre:           T02 + sütun 2 hattı (a7 -> direnç -> D4)

   İki LED de satır 1'de. Bu yüzden artık satırı hep HIGH tutuyoruz ve
   LED'leri SÜTUN pinleriyle yönetiyoruz:
       sütun pini LOW   ->  LED yanar  (katot 0 V)
       sütun pini HIGH  ->  LED söner  (iki uç da 5 V, akım yok)

   Dikkat: iki LED aynı anda yanarsa satır pininden iki LED'in akımı
   birlikte çıkar (~2 x 13 mA). PDF'teki "Bugünün devre bilgisi" bölümü.

   GÖREVLER
   9. sınıf
   1) İki LED birlikte yansın, birlikte sönsün.
   2) Biri yanarken diğeri sönük olsun, sırayla yer değiştirsinler,
      ama daha hızlı: 100 ms.
   10. sınıf
   3) Polis lambası: sol LED iki kez hızlıca yanıp sönsün,
      sonra sağ LED iki kez.
  ================================================================
*/

const int SATIR_1 = A3;   // iki LED'in de anodu
const int SUTUN_1 = 13;   // sol LED'in katodu
const int SUTUN_2 = 4;    // sağ LED'in katodu

int bekleme = 400;

void setup() {
  pinMode(SATIR_1, OUTPUT);
  pinMode(SUTUN_1, OUTPUT);
  pinMode(SUTUN_2, OUTPUT);
  digitalWrite(SUTUN_1, HIGH);   // ikisi de sönük başlasın
  digitalWrite(SUTUN_2, HIGH);
  digitalWrite(SATIR_1, HIGH);   // satır hep açık
}

void loop() {
  digitalWrite(SUTUN_1, LOW);    // sol yanar
  delay(bekleme);
  digitalWrite(SUTUN_1, HIGH);   // sol söner

  digitalWrite(SUTUN_2, LOW);    // sağ yanar
  delay(bekleme);
  digitalWrite(SUTUN_2, HIGH);   // sağ söner
}
