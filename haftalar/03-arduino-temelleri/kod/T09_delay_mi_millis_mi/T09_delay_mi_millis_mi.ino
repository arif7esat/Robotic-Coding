/*
  ================================================================
   T09  -  delay MI, millis MI?
  ================================================================
   Yeni kavramlar:  millis, unsigned long, bool
   Devre:           T08 ile aynı. Kabloya dokunma.

   delay(500) çalışırken Arduino yarım saniye boyunca hiçbir şey
   yapamaz; butona bassan bile duymaz.
   millis() ise "Arduino açılalı kaç milisaniye geçti?" sorusunun
   cevabıdır. Beklemek yerine saate bakarız:
       "Son değişimden beri 500 ms geçti mi? Geçtiyse LED'i değiştir."
   Böylece loop saniyede binlerce kez döner ve buton hep duyulur.

   Bu kodda iki iş aynı anda yürür:
       sol LED  : kendi kendine yarım saniyede bir yanıp söner
       sağ LED  : butona basılıyken anında yanar

   GÖREVLER
   9. sınıf
   1) DENEY: loop'un en başına  delay(1000);  ekle. Butona bas.
      Sağ LED neden geç tepki veriyor?  (Deneyden sonra sil.)
   2) Sol LED saniyede bir yanıp sönsün.
   10. sınıf
   3) Orta LED de 300 ms'de bir, kendi ritmiyle yanıp sönsün.
      İpucu: ikinci bir sonDegisim ve ikinci bir yanik değişkeni.
  ================================================================
*/

const int SATIR_1 = A3;
const int SUTUN[3] = {13, 4, 5};
const int BUTON = A4;

unsigned long sonDegisim = 0;   // sol LED en son ne zaman değişti (ms)
bool yanik = false;             // sol LED şu an yanık mı?

void setup() {
  pinMode(SATIR_1, OUTPUT);
  for (int i = 0; i < 3; i++) {
    pinMode(SUTUN[i], OUTPUT);
    digitalWrite(SUTUN[i], HIGH);
  }
  digitalWrite(SATIR_1, HIGH);
  pinMode(BUTON, INPUT_PULLUP);
}

void loop() {
  // 1. iş: sol LED, beklemeden yanıp söner
  if (millis() - sonDegisim >= 500) {
    sonDegisim = millis();
    yanik = !yanik;                       // yanıksa sönük, sönükse yanık
    if (yanik) digitalWrite(SUTUN[0], LOW);
    else       digitalWrite(SUTUN[0], HIGH);
  }

  // 2. iş: sağ LED butonu dinler
  if (digitalRead(BUTON) == LOW) digitalWrite(SUTUN[2], LOW);
  else                           digitalWrite(SUTUN[2], HIGH);
}
