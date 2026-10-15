/*
  ================================================================
   T09  -  delay MI, millis MI?  ·  GÖREV CEVAPLARI
  ================================================================
   Kullanım: GOREV sayısını 1-3 arasında değiştir ve yükle.
   Devre:    T09 devresi. Kabloya dokunma.

   SORULARIN CEVAPLARI
   Görev 1 - delay(1000) yüzünden loop artık saniyede yalnızca BİR kez
     döner. Buton da turda bir kez okunur: bastığın an Arduino uyuyorsa
     tepki 1 saniyeye kadar gecikir. Kısa bir basışı hiç görmeyebilir.
     Sol LED de artık 500 ms'de değil, her turda (~1 s) değişir.
     Ders: delay sırasında Arduino başka hiçbir şey yapamaz.
   Görev 2 - 500 yerine 1000. Dikkat: 500'de LED zaten "saniyede bir"
     yanıp sönüyordu (500 yanık + 500 sönük). 1000 ile 1 s yanık,
     1 s sönük olur. Sınıfta "saniyede bir" ne demek, tartışın.
   Görev 3 - Her LED'in kendi saati (sonDegisim) ve kendi durumu (yanik)
     olur. İki saat birbirini beklemez; iki ritim aynı anda yürür.
  ================================================================
*/

const int GOREV = 1;     // <-- 1, 2 ya da 3

const int SATIR_1 = A3;
const int SUTUN[3] = {13, 4, 5};
const int BUTON = A4;

unsigned long sonDegisim = 0;     // sol LED'in saati
bool yanik = false;
unsigned long sonDegisim2 = 0;    // Görev 3: orta LED'in saati
bool yanik2 = false;

unsigned long aralik = 500;       // sol LED kaç ms'de bir değişsin

void setup() {
  pinMode(SATIR_1, OUTPUT);
  for (int i = 0; i < 3; i++) {
    pinMode(SUTUN[i], OUTPUT);
    digitalWrite(SUTUN[i], HIGH);
  }
  digitalWrite(SATIR_1, HIGH);
  pinMode(BUTON, INPUT_PULLUP);
  if (GOREV == 2) aralik = 1000;
}

void loop() {
  if (GOREV == 1) delay(1000);    // DENEY: Arduino'yu uyutuyoruz

  // sol LED: kendi ritmi
  if (millis() - sonDegisim >= aralik) {
    sonDegisim = millis();
    yanik = !yanik;
    if (yanik) digitalWrite(SUTUN[0], LOW);
    else       digitalWrite(SUTUN[0], HIGH);
  }

  // orta LED: ikinci ritim (sadece Görev 3)
  if (GOREV == 3 && millis() - sonDegisim2 >= 300) {
    sonDegisim2 = millis();
    yanik2 = !yanik2;
    if (yanik2) digitalWrite(SUTUN[1], LOW);
    else        digitalWrite(SUTUN[1], HIGH);
  }

  // sağ LED: buton
  if (digitalRead(BUTON) == LOW) digitalWrite(SUTUN[2], LOW);
  else                           digitalWrite(SUTUN[2], HIGH);
}
