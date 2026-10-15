/*
  ================================================================
   T8  -  GÖZ YANILMASI  ·  GÖREV CEVAPLARI
  ================================================================
   Kullanım: GOREV sayısını 1-4 arasında değiştir ve yükle.

   DEVRE EKİ
   Görev 1-3: T8 devresi yeterli (satır 1-2, sütun 3 ve 5).
   Görev 4  : bütün matris gerekli (T2 devresi: 16 hat, 8 direnç).

   SORULARIN CEVAPLARI
   Görev 1 - Titremenin kaybolduğu değer kişiden kişiye biraz değişir;
     çoğu kişi için bekleme 10 ms ve altında titreme görünmez. Neden: iki
     LED sırayla yandığı için bir tur 2 × bekleme sürer. 10 ms beklemede
     her LED saniyede 50 kez yanar; göz bunu sürekli ışık sanar. GOREV = 1
     bekleme değerini 500'den 1'e kadar kendisi küçültür ve Seri Monitöre
     (9600) yazar: titremenin bittiği anı not et.
   Görev 2 - Üçgen için yeni kablo gerekmez: iki satır ve iki sütun 4
     kesişim verir. Bunlardan herhangi 3'ü bir dik üçgen oluşturur.
   Görev 3 - Kare: 4 kesişimin hepsi. Hepsi sırayla tek tek yakıldığı için
     hayalet oluşmaz.
   Görev 4 - Gülen yüz: her satır sırayla açılır, o satırın LED'leri en
     fazla 3'erli gruplar halinde yakılır (bir satırda 4 LED olduğu için
     iki parça). matris.h tam olarak bunu yapıyordu.
  ================================================================
*/

const int GOREV = 1;     // <-- 1 ... 4

const int SATIR[8] = {A3, 12, 9, A0, 2, 8, 3, 6};
const int SUTUN[8] = {13, 4, 5, A2, 7, A1, 11, 10};

const char* YUZ[8] = {"..####..", ".#....#.", "#.#..#.#", "#......#",
                      "#.#..#.#", "#..##..#", ".#....#.", "..####.."};

void hepsiniSondur() {
  for (int i = 0; i < 8; i++) {
    digitalWrite(SATIR[i], LOW);
    digitalWrite(SUTUN[i], HIGH);
  }
}

void ledYak(int satir, int sutun) {
  hepsiniSondur();
  digitalWrite(SATIR[satir], HIGH);
  digitalWrite(SUTUN[sutun], LOW);
}

int bekleme = 500;                 // görev 1

void setup() {
  for (int i = 0; i < 8; i++) {
    pinMode(SATIR[i], OUTPUT);
    pinMode(SUTUN[i], OUTPUT);
  }
  hepsiniSondur();
  Serial.begin(9600);
}

void loop() {
  if (GOREV == 1) {                // bekleme kendiliğinden küçülür
    unsigned long bas = millis();
    while (millis() - bas < 3000) {          // her değeri 3 saniye göster
      ledYak(0, 2); delay(bekleme);
      ledYak(1, 4); delay(bekleme);
    }
    Serial.print("bekleme = ");
    Serial.print(bekleme);
    Serial.println(" ms");
    if (bekleme > 50) bekleme = bekleme / 2;  // 500, 250, 125, 62
    else if (bekleme > 1) bekleme = bekleme - 5 > 1 ? bekleme - 5 : 1;
    else bekleme = 500;                        // başa dön
  }
  if (GOREV == 2) {                // üçgen: 3 kesişim
    ledYak(0, 2); delay(2);
    ledYak(1, 2); delay(2);
    ledYak(1, 4); delay(2);
  }
  if (GOREV == 3) {                // kare: 4 kesişim
    ledYak(0, 2); delay(2);
    ledYak(0, 4); delay(2);
    ledYak(1, 4); delay(2);
    ledYak(1, 2); delay(2);
  }
  if (GOREV == 4) {                // gülen yüz, satır satır, en fazla 3 LED
    for (int r = 0; r < 8; r++) {
      for (int bas = 0; bas < 8; bas = bas + 3) {
        hepsiniSondur();
        digitalWrite(SATIR[r], HIGH);
        for (int c = bas; c < bas + 3 && c < 8; c++) {
          if (YUZ[r][c] == '#') digitalWrite(SUTUN[c], LOW);
        }
        delayMicroseconds(400);
      }
    }
    hepsiniSondur();
  }
}
