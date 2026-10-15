/*
  ================================================================
   T02  -  DEĞİŞKENLE HIZ
  ================================================================
   Yeni kavramlar:  değişken (int), sabit (const), anlamlı isimler
   Devre:           T01 ile aynı. Kabloya dokunma.

   T01'de A3, 13 ve 500 sayıları kodun içine dağılmıştı. Hızı değiştirmek
   için iki yeri ayrı ayrı düzeltmek gerekiyordu. Şimdi her sayıya bir
   isim veriyoruz:
       const int  ->  hiç değişmeyecek sayı (pin numarası)
       int        ->  değişebilecek sayı (bekleme süresi)

   Hızı değiştirmek için artık tek bir satırı düzeltmen yeter.

   GÖREVLER
   9. sınıf
   1) bekleme'yi 150 yap. Kaç satırı değiştirdin?
   2) Yanık ve sönük süreleri ayrı olsun: iki değişken kullan,
      yanikSure = 100 ve sonukSure = 900.
   10. sınıf
   3) loop'un sonuna  bekleme = bekleme - 50;  ekle ve izle.
      LED hızlanıyor; bir süre sonra neden takılıp kalıyor?
  ================================================================
*/

const int SATIR_1 = A3;   // LED'in anodu (+)
const int SUTUN_1 = 13;   // LED'in katodu (-), 220 ohm direnç üzerinden

int bekleme = 500;        // milisaniye

void setup() {
  pinMode(SATIR_1, OUTPUT);
  pinMode(SUTUN_1, OUTPUT);
  digitalWrite(SUTUN_1, LOW);
}

void loop() {
  digitalWrite(SATIR_1, HIGH);
  delay(bekleme);
  digitalWrite(SATIR_1, LOW);
  delay(bekleme);
}
