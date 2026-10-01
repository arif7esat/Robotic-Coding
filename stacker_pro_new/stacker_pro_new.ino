/*
  ================================================================
   STACKER  -  PRO SÜRÜM (verimli tasarım)
  ================================================================
   Donanım : Arduino UNO, 1088BS 8x8 matris, 8 x 220 ohm, buton, buzzer
   Pinler  : satırlar D2..D9, sütunlar D10..D13 + A0..A3 (220 ohm ile)
             buton A4 (GND'ye), buzzer A5 (GND'ye)

   ÖĞRENCİ SÜRÜMÜNDEN FARKLARI
   1) Ekran 64 bool yerine 8 byte: her satır tek bir byte, her bit bir LED.
      Bloklar "bit maskesi": çakışma kontrolü tek bir AND (&) işlemi.
   2) Döndürme/aynalama her karede değil, ekran değiştiğinde BİR KEZ yapılır.
   3) Resimler, rakamlar ve seviye tablosu flash hafızada (PROGMEM),
      2 KB'lık RAM'i harcamaz.
  ================================================================
*/
#include <EEPROM.h>
#include <avr/pgmspace.h>

// ---------------- PİNLER ----------------
const byte SATIR[8] = {2, 3, 4, 5, 6, 7, 8, 9};
const byte SUTUN[8] = {10, 11, 12, 13, A0, A1, A2, A3};
const byte BUTON  = A4;
const byte BUZZER = A5;

// ---------------- AYARLAR ----------------
const bool SATIR_ANOT   = true;   // 1088BS: true. Hiç LED yanmazsa false
const int  DONUS_DERECE = 180;      // taban kenarı: 0, 90, 180, 270 (her sayı olur: 450 -> 90)
const bool AYNA         = false;  // "L3" ayna gibi görünüyorsa true
const byte BASLANGIC_CAN = 3, MAKS_CAN = 5, SEVIYE_SAYISI = 9;

// Dereceyi derleme anında 0..3 adıma çevir (mod 360, en yakın 90'ın katı)
constexpr int  DERECE_360 = ((DONUS_DERECE % 360) + 360) % 360;
constexpr byte DONUS      = ((DERECE_360 + 45) / 90) % 4;

// ---------------- SEVİYELER (flash'ta) ----------------
enum : byte { NORMAL = 0, RUZGAR = 1, HAYALET = 2 };
struct Seviye { int hizBas, hizSon; byte genislik, ozel; };

const Seviye SEVIYELER[SEVIYE_SAYISI] PROGMEM = {
  {240, 150, 3, NORMAL},  {210, 120, 3, NORMAL},  {190, 105, 3, RUZGAR},
  {175,  95, 3, HAYALET}, {160,  90, 2, NORMAL},  {150,  85, 3, RUZGAR},
  {140,  80, 2, HAYALET}, {130,  75, 2, RUZGAR | HAYALET},
  {110,  60, 2, RUZGAR | HAYALET}
};

// ---------------- RESİMLER (flash'ta, ilk byte = EN ALT satır, bit0 = sol) ----------------
const byte KALP[8]    PROGMEM = {0x00, 0x18, 0x3C, 0x7E, 0xFF, 0xFF, 0xFF, 0x66};
const byte KIRIK[8]   PROGMEM = {0x00, 0x10, 0x2C, 0x76, 0xEF, 0xF7, 0xEF, 0x66};
const byte MUTLU[8]   PROGMEM = {0x3C, 0x42, 0x99, 0xA5, 0x81, 0xA5, 0x42, 0x3C};
const byte UZGUN[8]   PROGMEM = {0x3C, 0x42, 0xA5, 0x99, 0x81, 0xA5, 0x42, 0x3C};
const byte AGLAYAN[8] PROGMEM = {0x3C, 0x42, 0xA5, 0x99, 0xA1, 0xA5, 0x42, 0x3C};

// 3x5 rakamlar: her rakam 5 satır (üstten alta), her satır 3 bit (bit0 = sol)
const byte RAKAM[10][5] PROGMEM = {
  {7,5,5,5,7}, {2,3,2,2,7}, {7,4,7,1,7}, {7,4,7,4,7}, {5,5,7,4,4},
  {7,1,7,4,7}, {7,1,7,5,7}, {7,4,4,4,4}, {7,5,7,5,7}, {7,5,7,4,7}
};

// ---------------- EKRAN ----------------
byte ekran[8];        // mantıksal görüntü: ekran[0] = en alt satır, bit0 = en sol
byte fiziksel[8];     // matrise giden görüntü: fiziksel[r] = r. satır pini, bit c = c. sütun pini

void temizle()                  { memset(ekran, 0, 8); }
void resim(const byte* pResim)  { memcpy_P(ekran, pResim, 8); }

void rakam(byte d, byte x) {
  for (byte i = 0; i < 5; i++) ekran[6 - i] |= pgm_read_byte(&RAKAM[d][i]) << x;
}
void seviyeEkrani(byte s) { temizle(); for (byte y = 2; y <= 6; y++) ekran[y] = 1; ekran[2] = 0b11; rakam(s, 4); }
void canEkrani(byte n)    { temizle(); ekran[5] = 0b101; ekran[4] = 0b111; ekran[3] = 0b010; rakam(n, 4); }

// Mantıksal görüntüyü bir kez fiziksel yöne çevirir (aynalama + döndürme)
void fizikseleCevir() {
  memset(fiziksel, 0, 8);
  for (byte y = 0; y < 8; y++) {
    for (byte x = 0; x < 8; x++) {
      if (!bitRead(ekran[y], x)) continue;
      byte px = AYNA ? 7 - x : x, py = y;
      for (byte k = 0; k < DONUS; k++) { byte t = px; px = py; py = 7 - t; }   // 90° döndür
      fiziksel[7 - py] |= 1 << px;                                             // satır pini 0 = üst
    }
  }
}

void hepsiniKapat() {
  for (byte i = 0; i < 8; i++) {
    digitalWrite(SATIR[i], !SATIR_ANOT);
    digitalWrite(SUTUN[i],  SATIR_ANOT);
  }
}

// Bir kare çiz: aynı anda tek satırın en fazla 3 LED'i yanar (pin akımı < 40 mA)
void kareCiz() {
  for (byte r = 0; r < 8; r++) {
    for (byte bas = 0; bas < 8; bas += 3) {
      byte parca = (fiziksel[r] >> bas) & 0b111;
      if (!parca) continue;
      digitalWrite(SATIR[r], SATIR_ANOT);
      for (byte i = 0; i < 3 && bas + i < 8; i++)
        if (bitRead(parca, i)) digitalWrite(SUTUN[bas + i], !SATIR_ANOT);
      delayMicroseconds(300);
      hepsiniKapat();
    }
  }
}

// ---------------- BUTON VE ZAMAN ----------------
bool butonBasildi() {                       // sadece yeni basışta true
  static bool onceki = HIGH;
  static unsigned long son = 0;
  bool simdi = digitalRead(BUTON);
  bool basildi = onceki == HIGH && simdi == LOW && millis() - son > 50;
  if (basildi) son = millis();
  onceki = simdi;
  return basildi;
}

// Ekranı ms kadar göster. kesilebilir = true ise butona basılınca hemen true döner.
bool goster(unsigned long ms, bool kesilebilir = false) {
  fizikseleCevir();                          // ekran bu süre boyunca değişmez: bir kez çevir
  unsigned long bas = millis();
  while (millis() - bas < ms) {
    kareCiz();
    if (butonBasildi() && kesilebilir) return true;
  }
  return false;
}

void bip(int f, int ms) { tone(BUZZER, f, ms); goster(ms + 30); }

// ---------------- ANİMASYONLAR ----------------
void kalpAt(byte n) {
  for (byte i = 0; i < n; i++) { resim(KALP); tone(BUZZER, 880, 60); goster(220); temizle(); goster(140); }
  canEkrani(n); goster(1000);
}

void canDegisti(byte eski, byte yeni) {     // ♥eski <-> ♥yeni yanıp söner
  for (byte i = 0; i < 3; i++) { canEkrani(eski); goster(200); canEkrani(yeni); goster(200); }
  goster(400);
}

void uzgunYuz() {
  resim(MUTLU); bip(784, 120); goster(600);
  resim(UZGUN); bip(392, 200); bip(330, 200); bip(262, 400);
  for (byte i = 0; i < 2; i++) { resim(AGLAYAN); goster(300); resim(UZGUN); goster(250); }
}

void kalpKirildi(byte eski, byte yeni) {
  resim(KALP); goster(300);
  tone(BUZZER, 150, 300);
  for (byte i = 0; i < 3; i++) { resim(KIRIK); goster(250); temizle(); goster(120); }
  canDegisti(eski, yeni);
}

void canKazanildi(byte eski, byte yeni) {
  for (byte i = 0; i < 4; i++) { resim(KALP); bip(660 + i * 220, 80); temizle(); goster(80); }
  canDegisti(eski, yeni);
}

void flas(byte kez) {
  for (byte i = 0; i < kez; i++) {
    memset(ekran, 0xFF, 8); bip(523 + i * 262, 150); goster(150);
    temizle(); goster(200);
  }
}

// ---------------- BİR SEVİYE: 8 kat biterse true, blok düşerse false ----------------
bool seviyeOyna(byte s) {
  Seviye sv;
  memcpy_P(&sv, &SEVIYELER[s - 1], sizeof sv);
  byte genislik = sv.genislik;
  byte alttaki  = 0xFF;                               // zemin: her yer dolu
  temizle();

  for (byte kat = 0; kat < 8; kat++) {
    int  hiz   = map(kat, 0, 7, sv.hizBas, sv.hizSon);
    int  konum = random(2) ? 0 : 8 - genislik;
    int  yon   = konum ? -1 : 1;
    byte blok;

    while (true) {                                    // blok kayar
      blok = ((1 << genislik) - 1) << konum;
      bool gorunur = !(sv.ozel & HAYALET) || millis() % 1000 <= 600;
      ekran[kat] = gorunur ? blok : 0;
      if (goster(hiz, true)) break;                   // basıldı
      if ((sv.ozel & RUZGAR) && random(10) == 0) yon = -yon;
      if (konum + yon < 0 || konum + yon + genislik > 8) yon = -yon;
      konum += yon;
    }

    byte kalan = blok & alttaki;                      // çakışan kısım
    if (!kalan) return false;

    if (kalan == blok) tone(BUZZER, 600 + kat * 120, 70);
    else {
      tone(BUZZER, 220, 150);
      for (byte i = 0; i < 3; i++) { ekran[kat] = blok; goster(80); ekran[kat] = kalan; goster(80); }
    }
    ekran[kat] = alttaki = kalan;
    genislik = __builtin_popcount(kalan);             // kalan LED sayısı
  }
  return true;
}

// ---------------- ANA PROGRAM ----------------
void setup() {
  for (byte i = 0; i < 8; i++) { pinMode(SATIR[i], OUTPUT); pinMode(SUTUN[i], OUTPUT); }
  pinMode(BUTON, INPUT_PULLUP);
  pinMode(BUZZER, OUTPUT);
  hepsiniKapat();
  flas(3);
}

void loop() {
  // 1) Bekleme
  for (int x = 0, d = 1; ; x += d) {
    temizle(); ekran[0] = 0b11 << x;
    if (goster(150, true)) break;
    if (x + d < 0 || x + d > 6) d = -d;
  }
  randomSeed(micros());

  // 2) Oyun
  byte seviye = 1, can = BASLANGIC_CAN;
  while (can > 0 && seviye <= SEVIYE_SAYISI) {
    seviyeEkrani(seviye); bip(523, 100); bip(659, 100); bip(784, 200); goster(800);
    kalpAt(can);
    if (seviyeOyna(seviye)) {
      bip(523, 100); bip(659, 100); bip(784, 100); bip(1047, 300);
      if (can < MAKS_CAN) { canKazanildi(can, can + 1); can++; }
      seviye++;
    } else {
      uzgunYuz();
      kalpKirildi(can, can - 1);
      can--;
    }
  }

  // 3) Sonuç ve rekor
  byte ulasilan = min(seviye, SEVIYE_SAYISI);
  if (can) flas(5);                                   // şampiyon
  byte rekor = EEPROM.read(0);
  if (rekor > SEVIYE_SAYISI) rekor = 0;
  if (ulasilan > rekor) {
    EEPROM.update(0, ulasilan);
    for (byte i = 0; i < 3; i++) { bip(1319, 80); bip(1568, 80); }
  }
  seviyeEkrani(ulasilan);
  while (!goster(100, true)) {}
}
