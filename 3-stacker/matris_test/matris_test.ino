/*
  MATRİS TESTİ (sıralı bağlantı için)
  1. Bölüm: 8 satır tek tek boydan boya yanar
  2. Bölüm: 8 sütun tek tek boydan boya yanar
  Seri Monitör (9600) o an hangi hattın yandığını yazar.
  Bir çizgi hiç yanmıyorsa: o an yazan hattın kablosu/direnci temas etmiyor.
*/

const bool SATIR_ANOT = true;   // Hiç LED yanmazsa false yap

const byte SATIR[8] = {A3, 12, 9, A0, 2, 8, 3, 6};     // satır 1..8
const byte SUTUN[8] = {13, 4, 5, A2, 7, A1, 11, 10};   // sütun 1..8

// Hangi hat hangi delikte? (hata ararken bakmak için)
const char* SATIR_DELIK[8] = {"j12", "j7", "a12", "j9", "a5", "a11", "a6", "a9"};
const char* SUTUN_DELIK[8] = {"j8", "a7", "a8", "j11", "a10", "j10", "j6", "j5"};

void hepsiniKapat() {
  for (byte i = 0; i < 8; i++) {
    digitalWrite(SATIR[i], SATIR_ANOT ? LOW : HIGH);
    digitalWrite(SUTUN[i], SATIR_ANOT ? HIGH : LOW);
  }
}

// Aynı anda tek LED yakar (güvenli)
void ledYak(byte r, byte c) {
  hepsiniKapat();
  digitalWrite(SATIR[r], SATIR_ANOT ? HIGH : LOW);
  digitalWrite(SUTUN[c], SATIR_ANOT ? LOW : HIGH);
  delayMicroseconds(1000);
}

void setup() {
  Serial.begin(9600);
  for (byte i = 0; i < 8; i++) { pinMode(SATIR[i], OUTPUT); pinMode(SUTUN[i], OUTPUT); }
  hepsiniKapat();
}

void loop() {
  for (byte r = 0; r < 8; r++) {
    Serial.print("Satir "); Serial.print(r + 1);
    Serial.print("  (delik "); Serial.print(SATIR_DELIK[r]); Serial.println(")");
    unsigned long t = millis();
    while (millis() - t < 1000) for (byte c = 0; c < 8; c++) ledYak(r, c);
  }
  for (byte c = 0; c < 8; c++) {
    Serial.print("Sutun "); Serial.print(c + 1);
    Serial.print("  (delik "); Serial.print(SUTUN_DELIK[c]); Serial.println(", direncli)");
    unsigned long t = millis();
    while (millis() - t < 1000) for (byte r = 0; r < 8; r++) ledYak(r, c);
  }
  hepsiniKapat();
  Serial.println("--- Tur bitti ---");
  delay(1500);
}
