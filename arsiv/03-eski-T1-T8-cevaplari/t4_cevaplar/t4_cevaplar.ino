/*
  ================================================================
   T4  -  BUTONU OKU  ·  GÖREV CEVAPLARI
  ================================================================
   Kullanım: GOREV sayısını 1-4 arasında değiştir ve yükle.
   Devre: T4 devresi, ek gerekmez. Seri Monitör: 9600.

   SORULARIN CEVAPLARI
   Görev 2 - INPUT deneyi (GOREV = 2): Buton bırakıkken pin hiçbir yere
     bağlı değildir, "havada" kalır. Seri Monitörde 0 ve 1 rastgele karışır;
     ele, kabloya dokununca ya da yaklaşınca değişir, çünkü pin çevredeki
     elektrik gürültüsünü okur. INPUT_PULLUP içerideki direnci açar ve pini
     5 V'a "çeker": bırakıkken hep 1 okunur. Deneyden sonra INPUT_PULLUP'a
     geri dön.
   Görev 3 - Kenar algılama: "şu an basılı VE bir önceki turda basılı
     değildi" ise yeni bir basıştır. 30 ms bekleme, buton metalinin
     sekmesini (debounce) atlatır.
  ================================================================
*/

const int GOREV = 1;     // <-- 1 ... 4

const int BUTON = A4;
const int LED_SATIR = A3;
const int LED_SUTUN = 13;

int onceki = HIGH;        // görev 3 ve 4
bool ledYanik = false;    // görev 3
int sayac = 0;            // görev 4

void setup() {
  if (GOREV == 2) pinMode(BUTON, INPUT);          // deney
  else            pinMode(BUTON, INPUT_PULLUP);
  pinMode(LED_SATIR, OUTPUT);
  pinMode(LED_SUTUN, OUTPUT);
  digitalWrite(LED_SUTUN, LOW);
  Serial.begin(9600);
}

void loop() {
  int durum = digitalRead(BUTON);

  if (GOREV == 1) {                               // ters: basınca sön
    if (durum == LOW) digitalWrite(LED_SATIR, LOW);
    else              digitalWrite(LED_SATIR, HIGH);
  }
  if (GOREV == 2) {                               // havadaki pini izle
    Serial.println(durum);
    delay(50);
  }
  if (GOREV == 3 || GOREV == 4) {
    if (durum == LOW && onceki == HIGH) {         // YENİ basış
      if (GOREV == 3) {
        ledYanik = !ledYanik;
        digitalWrite(LED_SATIR, ledYanik ? HIGH : LOW);
      } else {
        sayac = sayac + 1;
        Serial.print("Basis sayisi: ");
        Serial.println(sayac);
      }
      delay(30);                                  // sekmeyi atlat
    }
    onceki = durum;
  }
}
