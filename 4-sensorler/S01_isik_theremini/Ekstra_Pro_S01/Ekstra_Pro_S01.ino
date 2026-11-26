/*
  ================================================================
   S01  -  IŞIK THEREMİNİ  ·  PROFESYONEL SÜRÜM
  ================================================================
   Devre: ders devresinin aynısı (LDR, 10k, pasif buzzer).

   Temel sürümden farkı:
   1. Kalibrasyon: ilk 3 saniyede sınıfın ışık aralığını öğrenir.
      Kodu yükleyince (ya da RESET'e basınca) 3 saniye boyunca
      elini LDR'nin üstünde gezdir.
   2. Yumuşatma: ölçüm titremesini azaltır, ses daha temiz kayar.
   3. delay yok: millis ile 15 ms'de bir güncellenir.
  ================================================================
*/

const int LDR_PIN = A0;
const int BUZZER  = A5;

const int FREKANS_MIN = 150;                  // en kalın ses (Hz)
const int FREKANS_MAX = 1800;                 // en ince ses (Hz)
const unsigned long KALIBRASYON_MS = 3000;    // ilk 3 saniye: ölçüm aralığını öğren
const unsigned long GUNCELLEME_MS  = 15;      // sesi 15 ms'de bir güncelle

int isikMin = 1023;
int isikMax = 0;
float yumusak = 0;                            // titremesi azaltılmış ışık değeri
unsigned long sonGuncelleme = 0;

void setup() {
  Serial.begin(9600);
  // Kalibrasyon: bu 3 saniyede elini LDR'nin üstünde gezdir
  unsigned long baslangic = millis();
  while (millis() - baslangic < KALIBRASYON_MS) {
    int okuma = analogRead(LDR_PIN);
    isikMin = min(isikMin, okuma);
    isikMax = max(isikMax, okuma);
  }
  if (isikMax - isikMin < 50) {               // el gezdirilmediyse tüm aralığı kullan
    isikMin = 0;
    isikMax = 1023;
  }
  yumusak = analogRead(LDR_PIN);
}

void loop() {
  if (millis() - sonGuncelleme >= GUNCELLEME_MS) {   // delay yok: Arduino hiç beklemez
    sonGuncelleme = millis();
    int okuma = analogRead(LDR_PIN);
    yumusak = 0.8 * yumusak + 0.2 * okuma;    // yeni ölçümün sadece %20'si: ani sıçrama yok
    int isik = constrain((int)yumusak, isikMin, isikMax);
    int frekans = map(isik, isikMin, isikMax, FREKANS_MIN, FREKANS_MAX);
    tone(BUZZER, frekans);
    Serial.println(isik);
  }
}
