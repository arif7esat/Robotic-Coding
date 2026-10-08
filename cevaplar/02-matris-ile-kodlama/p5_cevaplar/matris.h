/*
  ================================================================
   matris.h  -  YARDIMCI DOSYA  (BU DOSYAYA DOKUNMANA GEREK YOK!)
  ================================================================
   Bu dosya 8x8 matrisi arka planda sürekli yeniler.
   Sayesinde sen sadece aşağıdaki kolay komutları kullanırsın
   ve delay() ile rahatça bekleyebilirsin.

   KOORDİNAT:  x = sütun  (0 = en sol,  7 = en sağ)
               y = satır  (0 = en alt,  7 = en üst)

   KOMUTLAR
   matrisBaslat();            -> setup() içinde ilk satır bu olmalı
   matrisBaslat(90);          -> ekran yan duruyorsa 90, 180 veya 270 dene
   ledYak(x, y);              -> o noktadaki LED'i yakar
   ledSondur(x, y);           -> o noktadaki LED'i söndürür
   ledYanikMi(x, y)           -> LED yanıyorsa true verir
   ekraniTemizle();           -> bütün LED'leri söndürür
   ekraniDoldur();            -> bütün LED'leri yakar
   resimCiz(RESIM);           -> '#' ve '.' ile çizilmiş resmi gösterir
   butonaBasiliMi()           -> buton şu an basılıysa true verir
   butonaBasildi()            -> butona YENİ basıldıysa true verir (bir kez)
   bekleBasildiMi(ms)         -> ms kadar bekler, bu sırada butona basılırsa
                                 hemen true verir
   bip(frekans, sure);        -> buzzer'dan ses çıkarır (sure: milisaniye)

   Bağlantı: 01-stacker haftasındaki devrenin aynısı.
             Buton -> A4 ve GND,  Buzzer -> A5 ve GND
  ================================================================
*/
#pragma once
#include <Arduino.h>

const byte BUTON  = A4;
const byte BUZZER = A5;

// ---------------------------------------------------------------
//  Aşağısı öğretmen için: matrisin arka plan yenileme kodu
// ---------------------------------------------------------------
const bool SATIR_ANOT = true;   // 1088BS için true. Hiç LED yanmazsa false yap.

const byte _SATIR[8] = {A3, 12, 9, A0, 2, 8, 3, 6};    // satır 1..8 (direnç yok)
const byte _SUTUN[8] = {13, 4, 5, A2, 7, A1, 11, 10};  // sütun 1..8 (220 ohm ile)
const byte _PARCA[3] = {0x07, 0x38, 0xC0};             // sütunlar 3'erli: 0-2, 3-5, 6-7

byte _ekran[8];                  // _ekran[y] içindeki x. bit = (x, y) LED'i
volatile byte _fiziksel[8];      // kesmenin okuduğu: [satır pini] bit = sütun pini
byte _donusAdimi = 0;
bool _ayna = false;

volatile byte _parca = 0;        // 0..23  (8 satır x 3 parça)
byte _yanikSatir = 255;
byte _yanikMaske = 0;

// Ekrandaki (x, y) -> matrisin (satır pini, sütun pini)
void _cevir(byte x, byte y, byte &satir, byte &sutun) {
  if (_ayna) x = 7 - x;
  for (byte k = 0; k < _donusAdimi; k++) {
    byte eski = x;
    x = y;
    y = 7 - eski;
  }
  sutun = x;
  satir = 7 - y;
}

void _fizikseliHesapla(const byte ekran[8], byte hedef[8]) {
  for (byte r = 0; r < 8; r++) hedef[r] = 0;
  for (byte y = 0; y < 8; y++) {
    for (byte x = 0; x < 8; x++) {
      if (ekran[y] & (1 << x)) {
        byte r, c;
        _cevir(x, y, r, c);
        hedef[r] |= (1 << c);
      }
    }
  }
}

// Yeni ekranı tek seferde değiştir (titreme olmasın)
void _ekranaYaz(const byte yeni[8]) {
  byte f[8];
  _fizikseliHesapla(yeni, f);
  noInterrupts();
  for (byte i = 0; i < 8; i++) { _ekran[i] = yeni[i]; _fiziksel[i] = f[i]; }
  interrupts();
}

// Her 400 mikrosaniyede bir çalışır. Aynı anda en fazla 1 satırın
// 3 LED'i yanar (Arduino pini 40 mA'den fazla vermesin diye).
ISR(TIMER1_COMPA_vect) {
  if (_yanikSatir != 255) {
    digitalWrite(_SATIR[_yanikSatir], SATIR_ANOT ? LOW : HIGH);
    for (byte c = 0; c < 8; c++)
      if (_yanikMaske & (1 << c)) digitalWrite(_SUTUN[c], SATIR_ANOT ? HIGH : LOW);
    _yanikSatir = 255;
  }
  for (byte i = 0; i < 24; i++) {          // sıradaki dolu parçayı bul
    _parca = (_parca + 1) % 24;
    byte r = _parca / 3;
    byte maske = _fiziksel[r] & _PARCA[_parca % 3];
    if (maske) {
      for (byte c = 0; c < 8; c++)
        if (maske & (1 << c)) digitalWrite(_SUTUN[c], SATIR_ANOT ? LOW : HIGH);
      digitalWrite(_SATIR[r], SATIR_ANOT ? HIGH : LOW);
      _yanikSatir = r;
      _yanikMaske = maske;
      return;
    }
  }
}

// ---------------------------------------------------------------
//  ÖĞRENCİ KOMUTLARI
// ---------------------------------------------------------------
void matrisBaslat(int derece = 0, bool ayna = false) {
  for (byte i = 0; i < 8; i++) {
    pinMode(_SATIR[i], OUTPUT);
    pinMode(_SUTUN[i], OUTPUT);
    digitalWrite(_SATIR[i], SATIR_ANOT ? LOW : HIGH);
    digitalWrite(_SUTUN[i], SATIR_ANOT ? HIGH : LOW);
  }
  pinMode(BUTON, INPUT_PULLUP);
  pinMode(BUZZER, OUTPUT);

  derece = derece % 360;
  if (derece < 0) derece += 360;
  _donusAdimi = ((derece + 45) / 90) % 4;
  _ayna = ayna;

  // Timer1: 16 MHz / 64 = 250 kHz, 100 adımda bir kesme = 400 us
  noInterrupts();
  TCCR1A = 0;
  TCCR1B = (1 << WGM12) | (1 << CS11) | (1 << CS10);
  TCNT1  = 0;
  OCR1A  = 99;
  TIMSK1 |= (1 << OCIE1A);
  interrupts();
}

void _ledAyarla(int x, int y, bool yansin) {
  if (x < 0 || x > 7 || y < 0 || y > 7) return;   // ekran dışı: yok say
  byte yeni[8];
  for (byte i = 0; i < 8; i++) yeni[i] = _ekran[i];
  if (yansin) yeni[y] |=  (1 << x);
  else        yeni[y] &= ~(1 << x);
  _ekranaYaz(yeni);
}

void ledYak(int x, int y)    { _ledAyarla(x, y, true);  }
void ledSondur(int x, int y) { _ledAyarla(x, y, false); }

bool ledYanikMi(int x, int y) {
  if (x < 0 || x > 7 || y < 0 || y > 7) return false;
  return _ekran[y] & (1 << x);
}

void ekraniTemizle() {
  byte yeni[8] = {0, 0, 0, 0, 0, 0, 0, 0};
  _ekranaYaz(yeni);
}

void ekraniDoldur() {
  byte yeni[8] = {255, 255, 255, 255, 255, 255, 255, 255};
  _ekranaYaz(yeni);
}

// Resmin ilk yazısı matrisin EN ÜST satırıdır.
void resimCiz(const char* resim[8]) {
  byte yeni[8] = {0, 0, 0, 0, 0, 0, 0, 0};
  for (byte i = 0; i < 8; i++) {
    for (byte x = 0; x < 8 && resim[i][x] != '\0'; x++) {
      if (resim[i][x] == '#') yeni[7 - i] |= (1 << x);
    }
  }
  _ekranaYaz(yeni);
}

bool butonaBasiliMi() {
  return digitalRead(BUTON) == LOW;
}

bool _butonOnceki = false;
unsigned long _sonBasis = 0;

bool butonaBasildi() {
  bool simdi = butonaBasiliMi();
  bool yeni = (simdi && !_butonOnceki && millis() - _sonBasis > 50);
  if (yeni) _sonBasis = millis();
  _butonOnceki = simdi;
  return yeni;
}

bool bekleBasildiMi(unsigned long ms) {
  unsigned long baslangic = millis();
  while (millis() - baslangic < ms) {
    if (butonaBasildi()) return true;
    delay(1);
  }
  return false;
}

void bip(int frekans, int sure) {
  tone(BUZZER, frekans, sure);
  delay(sure);
}
