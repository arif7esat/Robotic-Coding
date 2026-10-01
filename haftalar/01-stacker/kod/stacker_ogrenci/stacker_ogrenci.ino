/*
  ================================================================
   STACKER  -  ÖĞRENCİ SÜRÜMÜ
  ================================================================
   Malzemeler : Arduino UNO, 1088BS 8x8 LED matris, 8 adet 220 ohm
                direnç, 1 buton, 1 buzzer
   Bağlantı   : (Matris bacakları breadboard'da a5-a12 ve j5-j12 deliklerine bağlı)
                Alt sıra  a5 -> a12  soldan sağa:  D2, D3, D4, D5, D6, D7, D8, D9
                Üst sıra  j5 -> j12  soldan sağa:  D10, D11, D12, D13, A0, A1, A2, A3
                a7, a8, a10, j5, j6, j8, j10, j11 deliklerinde kablo yerine
                220 ohm direnç var (direncin ucuna dişi-erkek kablo takılır)
                Buton  -> A4 ve GND
                Buzzer -> A5 ve GND

   NASIL OYNANIR?
   - Kayan bloğu butonla durdur, alttaki bloğun üstüne oturt.
   - Taşan kısımlar kesilir, blok daralır. 8 kat = seviye tamam!
   - 3 canla başlarsın. Seviye geçince +1 can (en fazla 5).
   - Blok boşa düşerse 1 can gider, seviye baştan başlar.
   - 9 seviyeyi geçen ŞAMPİYON olur.
  ================================================================
*/

#include <EEPROM.h>   // rekoru kalıcı hafızaya yazmak için


// ================================================================
//  1) PİNLER
// ================================================================
// Matrisin içindeki satır ve sütunlar bacaklara karışık dağılmıştır.
// Kabloları SIRAYLA taktık, karışıklığı bu iki liste çözüyor:
int satirPinleri[8] = {A3, 12, 9, A0, 2, 8, 3, 6};     // satır 1..8 (direnç yok)
int sutunPinleri[8] = {13, 4, 5, A2, 7, A1, 11, 10};   // sütun 1..8 (220 ohm ile)
int butonPini  = A4;
int buzzerPini = A5;


// ================================================================
//  2) AYARLAR  (sadece burayı değiştirmen yeterli)
// ================================================================
const bool SATIR_ANOT = true;   // 1088BS için true. Hiç LED yanmazsa false yap.

// Oyunun tabanı matrisin hangi kenarı olsun? Derece yaz: 0, 90, 180, 270
// Başka sayı da yazabilirsin: 360 -> 0, 450 -> 90, -90 -> 270, 100 -> 90
int  donusDerecesi = 0;
bool ayna = false;              // Harfler ayna gibi ters görünüyorsa true yap

int baslangicCani = 3;
int enFazlaCan    = 5;


// ================================================================
//  3) SEVİYELER  (9 seviye)
//  Hız = bloğun bir adım ilerlemesi için geçen süre (milisaniye).
//  Küçük sayı = hızlı blok.
// ================================================================
int  seviyeHizBas[9]   = {240, 210, 190, 175, 160, 150, 140, 130, 110};  // ilk kattaki hız
int  seviyeHizSon[9]   = {150, 120, 105,  95,  90,  85,  80,  75,  60};  // son kattaki hız
int  seviyeGenislik[9] = {  3,   3,   3,   3,   2,   3,   2,   2,   2};  // blok kaç LED
bool seviyeRuzgar[9]   = {false, false, true,  false, false, true,  false, true, true};
bool seviyeHayalet[9]  = {false, false, false, true,  false, false, true,  true, true};
// RÜZGAR : blok bazen aniden yön değiştirir
// HAYALET: blok arada bir görünmez olur


// ================================================================
//  4) RESİMLER
//  '#' = yanan LED, '.' = sönük LED. Matriste aynen böyle görünür!
// ================================================================
const char* KALP[8] = {
  ".##..##.",
  "########",
  "########",
  "########",
  ".######.",
  "..####..",
  "...##...",
  "........"
};

const char* KIRIK_KALP[8] = {
  ".##..##.",
  "####.###",
  "###.####",
  "####.###",
  ".##.###.",
  "..##.#..",
  "....#...",
  "........"
};

const char* MUTLU[8] = {
  "..####..",
  ".#....#.",
  "#.#..#.#",
  "#......#",
  "#.#..#.#",
  "#..##..#",
  ".#....#.",
  "..####.."
};

const char* UZGUN[8] = {
  "..####..",
  ".#....#.",
  "#.#..#.#",
  "#......#",
  "#..##..#",
  "#.#..#.#",
  ".#....#.",
  "..####.."
};

const char* AGLAYAN[8] = {
  "..####..",
  ".#....#.",
  "#.#..#.#",
  "#....#.#",   // gözyaşı
  "#..##..#",
  "#.#..#.#",
  ".#....#.",
  "..####.."
};

// Rakamlar: 3 sütun genişliğinde, 5 satır yüksekliğinde
const char* RAKAMLAR[10][5] = {
  {"###", "#.#", "#.#", "#.#", "###"},   // 0
  {".#.", "##.", ".#.", ".#.", "###"},   // 1
  {"###", "..#", "###", "#..", "###"},   // 2
  {"###", "..#", "###", "..#", "###"},   // 3
  {"#.#", "#.#", "###", "..#", "..#"},   // 4
  {"###", "#..", "###", "..#", "###"},   // 5
  {"###", "#..", "###", "#.#", "###"},   // 6
  {"###", "..#", "..#", "..#", "..#"},   // 7
  {"###", "#.#", "###", "#.#", "###"},   // 8
  {"###", "#.#", "###", "..#", "###"}    // 9
};


// ================================================================
//  5) EKRAN HAFIZASI
//  ekran[satir][sutun] = true ise o LED yanar.
//  satir 0 = EN ALT satır, sutun 0 = EN SOL sütun.
// ================================================================
bool ekran[8][8];
int  donusAdimi = 0;   // 0, 1, 2, 3  (her adım 90 derece)

void ekraniTemizle() {
  for (int y = 0; y < 8; y++) {
    for (int x = 0; x < 8; x++) {
      ekran[y][x] = false;
    }
  }
}

void resimCiz(const char* resim[8]) {
  ekraniTemizle();
  for (int i = 0; i < 8; i++) {          // i = resmin satırı (0 = en üst)
    for (int x = 0; x < 8; x++) {
      if (resim[i][x] == '#') {
        ekran[7 - i][x] = true;          // en üst satır = ekran[7]
      }
    }
  }
}

void rakamCiz(int rakam, int solSutun) {
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 3; j++) {
      if (RAKAMLAR[rakam][i][j] == '#') {
        ekran[6 - i][solSutun + j] = true;
      }
    }
  }
}

void seviyeEkraniCiz(int seviye) {       // matriste "L3" yazar
  ekraniTemizle();
  for (int y = 2; y <= 6; y++) ekran[y][0] = true;   // L'nin dik çizgisi
  ekran[2][1] = true;                                // L'nin tabanı
  rakamCiz(seviye, 4);
}

void canEkraniCiz(int can) {             // matriste "♥3" yazar
  ekraniTemizle();
  ekran[5][0] = true;  ekran[5][2] = true;                       // küçük kalp
  ekran[4][0] = true;  ekran[4][1] = true;  ekran[4][2] = true;
  ekran[3][1] = true;
  rakamCiz(can, 4);
}

void blokCiz(int satir, int sol, int genislik) {
  for (int x = 0; x < 8; x++) {
    ekran[satir][x] = (x >= sol && x < sol + genislik);
  }
}


// ================================================================
//  6) MATRİSİ YAKMAK
//  Arduino'nun bir pini en fazla 40 mA verebilir. Bu yüzden aynı anda
//  sadece BİR satırın EN FAZLA 3 LED'ini yakarız. Bu parçaları çok hızlı
//  sırayla yakınca göz bütün resmi aynı anda yanıyor sanır.
// ================================================================
void hepsiniKapat() {
  for (int i = 0; i < 8; i++) {
    digitalWrite(satirPinleri[i], SATIR_ANOT ? LOW : HIGH);
    digitalWrite(sutunPinleri[i], SATIR_ANOT ? HIGH : LOW);
  }
}

// Matrisin (satır pini, sütun pini) noktasındaki LED yanmalı mı?
// Döndürme ve aynalama burada yapılır.
bool ledYanmali(int satirNo, int sutunNo) {
  int x = sutunNo;
  int y = 7 - satirNo;
  for (int k = 0; k < donusAdimi; k++) {   // her adımda 90 derece geri döndür
    int eski = y;
    y = x;
    x = 7 - eski;
  }
  if (ayna) x = 7 - x;
  return ekran[y][x];
}

void ekraniBirKezCiz() {
  for (int satirNo = 0; satirNo < 8; satirNo++) {
    for (int bas = 0; bas < 8; bas += 3) {           // sütunlar 3'erli: 0-2, 3-5, 6-7
      int son = min(bas + 3, 8);

      bool parcadaLedVar = false;
      for (int s = bas; s < son; s++) {
        if (ledYanmali(satirNo, s)) parcadaLedVar = true;
      }
      if (!parcadaLedVar) continue;                  // boş parçayı atla

      digitalWrite(satirPinleri[satirNo], SATIR_ANOT ? HIGH : LOW);
      for (int s = bas; s < son; s++) {
        if (ledYanmali(satirNo, s)) {
          digitalWrite(sutunPinleri[s], SATIR_ANOT ? LOW : HIGH);
        }
      }
      delayMicroseconds(300);
      hepsiniKapat();
    }
  }
}


// ================================================================
//  7) BUTON VE BEKLEME
// ================================================================
bool butonOnceki = HIGH;
unsigned long sonBasis = 0;

// Butona YENİ basıldıysa true verir (basılı tutmak tekrar sayılmaz)
bool butonaBasildi() {
  bool simdi = digitalRead(butonPini);
  bool basildi = (butonOnceki == HIGH && simdi == LOW && millis() - sonBasis > 50);
  if (basildi) sonBasis = millis();
  butonOnceki = simdi;
  return basildi;
}

// Ekranı "sure" milisaniye boyunca göster (butonu dinlemez)
void goster(unsigned long sure) {
  unsigned long baslangic = millis();
  while (millis() - baslangic < sure) {
    ekraniBirKezCiz();
    butonaBasildi();          // bu sırada basılanlar sonra sayılmasın
  }
}

// Ekranı göster, butona basılırsa hemen dur ve true ver
bool gosterVeyaBasis(unsigned long sure) {
  unsigned long baslangic = millis();
  while (millis() - baslangic < sure) {
    ekraniBirKezCiz();
    if (butonaBasildi()) return true;
  }
  return false;
}

void bip(int frekans, int sure) {
  tone(buzzerPini, frekans, sure);
  goster(sure + 30);
}


// ================================================================
//  8) ANİMASYONLAR
// ================================================================
void kalpAt(int can) {                   // kalp "can" kadar atar
  for (int i = 0; i < can; i++) {
    resimCiz(KALP);
    tone(buzzerPini, 880, 60);
    goster(220);
    ekraniTemizle();
    goster(140);
  }
  canEkraniCiz(can);
  goster(1000);
}

void uzgunYuz() {                        // mutlu -> üzgün -> ağlayan
  resimCiz(MUTLU);
  bip(784, 120);
  goster(600);
  resimCiz(UZGUN);
  bip(392, 200);
  bip(330, 200);
  bip(262, 400);
  for (int i = 0; i < 2; i++) {
    resimCiz(AGLAYAN);  goster(300);
    resimCiz(UZGUN);    goster(250);
  }
}

void kalpKirildi(int eskiCan, int yeniCan) {
  resimCiz(KALP);
  goster(300);
  tone(buzzerPini, 150, 300);
  for (int i = 0; i < 3; i++) {
    resimCiz(KIRIK_KALP);  goster(250);
    ekraniTemizle();       goster(120);
  }
  for (int i = 0; i < 3; i++) {
    canEkraniCiz(eskiCan);  goster(200);
    canEkraniCiz(yeniCan);  goster(200);
  }
  goster(400);
}

void canKazanildi(int eskiCan, int yeniCan) {
  for (int i = 0; i < 4; i++) {
    resimCiz(KALP);
    bip(660 + i * 220, 80);
    ekraniTemizle();
    goster(80);
  }
  for (int i = 0; i < 3; i++) {
    canEkraniCiz(eskiCan);  goster(200);
    canEkraniCiz(yeniCan);  goster(200);
  }
  goster(400);
}

void tumEkranFlas(int kac) {
  for (int i = 0; i < kac; i++) {
    for (int y = 0; y < 8; y++) {
      for (int x = 0; x < 8; x++) ekran[y][x] = true;
    }
    bip(523 + i * 262, 150);
    goster(150);
    ekraniTemizle();
    goster(200);
  }
}


// ================================================================
//  9) BİR SEVİYEYİ OYNA
//  8 katı bitirirse true, blok boşa düşerse false verir.
// ================================================================
bool seviyeOyna(int seviye) {
  int i = seviye - 1;                    // diziler 0'dan başlar
  int genislik = seviyeGenislik[i];
  int altSol = 0;                        // alttaki bloğun sol ucu
  int altSag = 7;                        // alttaki bloğun sağ ucu (ilk katta zemin)
  ekraniTemizle();

  for (int kat = 0; kat < 8; kat++) {
    int hiz = map(kat, 0, 7, seviyeHizBas[i], seviyeHizSon[i]);   // her katta hızlanır

    // Blok rastgele soldan ya da sağdan başlasın
    int sol, yon;
    if (random(2) == 0) { sol = 0;            yon = 1;  }
    else                { sol = 8 - genislik; yon = -1; }

    // --- Blok kayar, butona basılana kadar ---
    while (true) {
      bool gorunur = true;
      if (seviyeHayalet[i] && millis() % 1000 > 600) gorunur = false;

      if (gorunur) blokCiz(kat, sol, genislik);
      else         blokCiz(kat, 0, 0);          // satırı boşalt

      if (gosterVeyaBasis(hiz)) break;          // butona basıldı -> dur

      if (seviyeRuzgar[i] && random(10) == 0) yon = -yon;              // rüzgar
      if (sol + yon < 0 || sol + yon + genislik > 8) yon = -yon;      // kenara çarptı
      sol = sol + yon;
    }

    // --- Blok durdu: alttakiyle çakışan kısım kalır ---
    int sag     = sol + genislik - 1;
    int yeniSol = max(sol, altSol);
    int yeniSag = min(sag, altSag);

    if (yeniSol > yeniSag) return false;         // hiç çakışmıyor: boşa düştü!

    if (yeniSol == sol && yeniSag == sag) {
      tone(buzzerPini, 600 + kat * 120, 70);     // tam isabet!
    } else {
      tone(buzzerPini, 220, 150);                // taşan kısım kesiliyor
      for (int t = 0; t < 3; t++) {
        blokCiz(kat, sol, genislik);                    goster(80);
        blokCiz(kat, yeniSol, yeniSag - yeniSol + 1);   goster(80);
      }
    }

    blokCiz(kat, yeniSol, yeniSag - yeniSol + 1);
    altSol   = yeniSol;
    altSag   = yeniSag;
    genislik = yeniSag - yeniSol + 1;
  }
  return true;                                   // 8 kat tamam!
}


// ================================================================
//  10) ANA PROGRAM
// ================================================================
void setup() {
  for (int i = 0; i < 8; i++) {
    pinMode(satirPinleri[i], OUTPUT);
    pinMode(sutunPinleri[i], OUTPUT);
  }
  pinMode(butonPini, INPUT_PULLUP);
  pinMode(buzzerPini, OUTPUT);
  hepsiniKapat();

  // Dereceyi 0, 1, 2, 3 adımına çevir
  int derece = donusDerecesi % 360;      // 450 -> 90
  if (derece < 0) derece = derece + 360; // -90 -> 270
  donusAdimi = ((derece + 45) / 90) % 4; // en yakın 90'ın katı: 100 -> 90

  tumEkranFlas(3);
}

void loop() {
  // ---- 1) BEKLEME: altta küçük bir blok gidip gelir ----
  int x = 0, yon = 1;
  while (true) {
    ekraniTemizle();
    blokCiz(0, x, 2);
    if (gosterVeyaBasis(150)) break;     // butona basıldı -> oyun başlasın
    x = x + yon;
    if (x == 0 || x == 6) yon = -yon;
  }
  randomSeed(micros());

  // ---- 2) OYUN ----
  int seviye = 1;
  int can = baslangicCani;

  while (can > 0 && seviye <= 9) {
    seviyeEkraniCiz(seviye);
    bip(523, 100);  bip(659, 100);  bip(784, 200);
    goster(800);
    kalpAt(can);

    if (seviyeOyna(seviye)) {            // seviye tamam!
      bip(523, 100);  bip(659, 100);  bip(784, 100);  bip(1047, 300);
      if (can < enFazlaCan) {
        canKazanildi(can, can + 1);
        can = can + 1;
      }
      seviye = seviye + 1;
    } else {                             // blok düştü
      uzgunYuz();
      kalpKirildi(can, can - 1);
      can = can - 1;
    }
  }

  // ---- 3) SONUÇ ----
  int ulasilan = min(seviye, 9);
  if (can > 0) tumEkranFlas(5);          // 9 seviye bitti: ŞAMPİYON!

  int rekor = EEPROM.read(0);
  if (rekor > 9) rekor = 0;              // hafıza ilk kez kullanılıyorsa
  if (ulasilan > rekor) {                // yeni rekor!
    EEPROM.write(0, ulasilan);
    for (int i = 0; i < 3; i++) { bip(1319, 80); bip(1568, 80); }
  }

  seviyeEkraniCiz(ulasilan);
  while (!gosterVeyaBasis(100)) { }      // butona basılana kadar sonucu göster
}
