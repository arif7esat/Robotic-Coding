/*
  ================================================================
   T10  -  İKİNCİ SATIR  ·  GÖREV CEVAPLARI
  ================================================================
   Kullanım: GOREV sayısını 1-3 arasında değiştir ve yükle.
   Devre:    T10 devresi. Kabloya dokunma.

   SORULARIN CEVAPLARI
   Görev 1 - (Öğretmen için otomatik deneme: T11'de öğreteceğimiz iç içe
     for'u kullanır. Öğrenci bekleme'yi elle değiştirerek aynı sonucu bulur.)
     Bu cevap kodu 500, 100, 20, 5 değerlerini 3'er saniye sırayla
     dener; Seri Monitör (9600) hangisinde olduğunu yazar.
       500 / 100 : LED'ler açıkça sırayla yanıyor.
       20        : ikisi birlikte yanıyor gibi ama hafif titreme var
                   (bir tur 40 ms, saniyede 25 tur).
       5         : titreme yok (bir tur 10 ms, saniyede 100 tur).
     Göz saniyede ~50 kareden hızlısını ayırt edemez: göz yanılması.
   Görev 2 - Yanan LED'ler: satır1-sütun1, satır1-sütun3, satır2-sütun1,
     satır2-sütun3. Açık her satır, açık her sütunla bir yol oluşturur:
     2 satır x 2 sütun = 4 kesişim = 4 LED. İstediğimiz 2, istemediğimiz
     2 tane "hayalet" LED. Çözüm: aynı anda tek bir yol aç, hızlı değiştir.
   Görev 3 - Dört LED'i tek tek, 2'şer ms yakıyoruz. Her an sadece bir
     LED açık; hayalet olamaz. Göz dördünü birlikte "T" olarak görür.
  ================================================================
*/

const int GOREV = 1;     // <-- 1, 2 ya da 3

const int SATIR[2] = {A3, 12};
const int SUTUN[3] = {13, 4, 5};

void hepsiniSondur() {
  for (int s = 0; s < 2; s++) digitalWrite(SATIR[s], LOW);
  for (int k = 0; k < 3; k++) digitalWrite(SUTUN[k], HIGH);
}

void ledYak(int s, int k) {
  hepsiniSondur();
  digitalWrite(SATIR[s], HIGH);
  digitalWrite(SUTUN[k], LOW);
}

void setup() {
  for (int s = 0; s < 2; s++) pinMode(SATIR[s], OUTPUT);
  for (int k = 0; k < 3; k++) pinMode(SUTUN[k], OUTPUT);
  hepsiniSondur();
  Serial.begin(9600);
}

void loop() {
  if (GOREV == 1) {                          // titreme deneyi
    const int DEGERLER[4] = {500, 100, 20, 5};
    for (int d = 0; d < 4; d++) {
      int bekleme = DEGERLER[d];
      Serial.print("bekleme = ");
      Serial.println(bekleme);
      for (int t = 0; t < 3000; t = t + 2 * bekleme) {   // ~3 saniye
        ledYak(0, 0);
        delay(bekleme);
        ledYak(1, 2);
        delay(bekleme);
      }
    }
  }

  if (GOREV == 2) {                          // hayalet deneyi
    digitalWrite(SATIR[0], HIGH);
    digitalWrite(SATIR[1], HIGH);
    digitalWrite(SUTUN[0], LOW);
    digitalWrite(SUTUN[2], LOW);
  }

  if (GOREV == 3) {                          // "T" harfi
    ledYak(0, 0); delay(2);                  // üst sol
    ledYak(0, 1); delay(2);                  // üst orta
    ledYak(0, 2); delay(2);                  // üst sağ
    ledYak(1, 1); delay(2);                  // alt orta
  }
}
