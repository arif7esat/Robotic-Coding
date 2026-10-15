/*
  ================================================================
   T7  -  delay mi, millis mi?  ·  GÖREV CEVAPLARI
  ================================================================
   Kullanım: GOREV sayısını 1-4 arasında değiştir ve yükle.

   DEVRE EKİ (T7 devresinde olmayan hat)
   Görev 3: sütun 4 eklenmeli
            sütun 4 : j11 → j17 (turuncu), direnç i17–i21, j21 → A2 (sarı)
   Not: Görev 3'te satır 1'de aynı anda en fazla 3 LED yanar (~3 × 13 mA).
   Bu, pinin mutlak sınırı olan 40 mA'e yakındır; daha fazla LED ekleme.

   SORULARIN CEVAPLARI
   Görev 1 - Deney (GOREV = 1, KULLAN_DELAY = true): LED B butona geç tepki
     verir, bazen hiç vermez. delay(500) boyunca Arduino başka hiçbir şey
     yapamaz; buton ancak saniyede bir kez okunur. millis ile Arduino hiç
     beklemez, sadece "zaman doldu mu?" diye bakar; buton binlerce kez okunur
     ve tepki anında gelir.
   Görev 4 - Bekleme süresi bir değişkende tutulur ve butona göre 500 ya da
     250 seçilir. millis karşılaştırması bu değişkenle yapılır.
  ================================================================
*/

const int GOREV = 1;     // <-- 1 ... 4
const bool KULLAN_DELAY = true;    // sadece görev 1 için: true / false dene

const int SATIR_1 = A3;
const int LED_A   = 13;    // sütun 1
const int LED_B   = 10;    // sütun 8
const int LED_C   = A2;    // görev 3: sütun 4
const int BUTON   = A4;

unsigned long sonDegisim = 0;
bool ledAYanik = false;
unsigned long sonDegisimC = 0;     // görev 3
bool ledCYanik = false;

void setup() {
  pinMode(SATIR_1, OUTPUT);
  pinMode(LED_A, OUTPUT);
  pinMode(LED_B, OUTPUT);
  pinMode(BUTON, INPUT_PULLUP);
  digitalWrite(SATIR_1, HIGH);
  digitalWrite(LED_A, HIGH);
  digitalWrite(LED_B, HIGH);
  if (GOREV == 3) { pinMode(LED_C, OUTPUT); digitalWrite(LED_C, HIGH); }
}

void loop() {
  bool basili = (digitalRead(BUTON) == LOW);

  if (GOREV == 1 && KULLAN_DELAY) {               // eski yöntem
    digitalWrite(LED_A, LOW);  delay(500);
    digitalWrite(LED_A, HIGH); delay(500);
  } else {
    unsigned long aralik = 500;
    if (GOREV == 2) aralik = 1000;                // saniyede bir
    if (GOREV == 4 && basili) aralik = 250;       // basılıyken iki kat hız
    if (millis() - sonDegisim >= aralik) {
      sonDegisim = millis();
      ledAYanik = !ledAYanik;
      digitalWrite(LED_A, ledAYanik ? LOW : HIGH);
    }
  }

  if (GOREV == 3 && millis() - sonDegisimC >= 300) {   // üçüncü LED, 300 ms
    sonDegisimC = millis();
    ledCYanik = !ledCYanik;
    digitalWrite(LED_C, ledCYanik ? LOW : HIGH);
  }

  if (basili) digitalWrite(LED_B, LOW);
  else        digitalWrite(LED_B, HIGH);
}
