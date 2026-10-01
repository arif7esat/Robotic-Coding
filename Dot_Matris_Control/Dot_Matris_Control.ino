// MATRİS TESTİ - 1088BS
// 1. Bölüm: Satırlar tek tek, her satır boydan boya yanar (1'den 8'e)
// 2. Bölüm: Sütunlar tek tek, her sütun boydan boya yanar (1'den 8'e)
// Seri Monitör (9600) hangi satır/sütunun yandığını yazar.

const bool SATIR_ANOT = true;   // Hiç LED yanmazsa false yap

const byte satirPin[8] = {2, 3, 4, 5, 6, 7, 8, 9};
const byte sutunPin[8] = {10, 11, 12, 13, A0, A1, A2, A3};

void hepsiSondur() {
  for (byte i = 0; i < 8; i++) {
    digitalWrite(satirPin[i], SATIR_ANOT ? LOW : HIGH);  // satır pasif
    digitalWrite(sutunPin[i], SATIR_ANOT ? HIGH : LOW);  // sütun pasif
  }
}

// Tek bir LED'i çok kısa yak (aynı anda sadece 1 LED yanar = güvenli)
void ledYak(byte r, byte c) {
  hepsiSondur();
  digitalWrite(satirPin[r], SATIR_ANOT ? HIGH : LOW);
  digitalWrite(sutunPin[c], SATIR_ANOT ? LOW : HIGH);
  delayMicroseconds(1000);
}

void setup() {
  Serial.begin(9600);
  for (byte i = 0; i < 8; i++) {
    pinMode(satirPin[i], OUTPUT);
    pinMode(sutunPin[i], OUTPUT);
  }
  hepsiSondur();
}

void loop() {
  // 1. Bölüm: Satırlar
  for (byte r = 0; r < 8; r++) {
    Serial.print("Satir "); Serial.println(r + 1);
    unsigned long t = millis();
    while (millis() - t < 1000)            // her satır 1 saniye
      for (byte c = 0; c < 8; c++) ledYak(r, c);
  }
  // 2. Bölüm: Sütunlar
  for (byte c = 0; c < 8; c++) {
    Serial.print("Sutun "); Serial.println(c + 1);
    unsigned long t = millis();
    while (millis() - t < 1000)            // her sütun 1 saniye
      for (byte r = 0; r < 8; r++) ledYak(r, c);
  }
  hepsiSondur();
  Serial.println("--- Tur bitti ---");
  delay(1500);
}