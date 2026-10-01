/*
  ============================================================
   STACKER - 8x8 LED matris ile arcade kule oyunu
   Donanım: Arduino UNO + 1088BS 8x8 matris + 8 adet 220 ohm
            + 1 buton + 1 buzzer
  ============================================================
   NASIL OYNANIR?
   - Butona bas: oyun başlar.
   - En alttaki satırda bir blok sağa sola kayar.
   - Butona bas: blok olduğu yerde durur.
   - Alttaki bloğun üstüne gelmeyen parçalar kesilir, blok daralır.
   - Her katta blok hızlanır. 8. kata ulaşan kazanır!
  ============================================================
*/

// ================== AYARLAR ==================
// İlk çalıştırmada TEST_MODU'nu true yap, bağlantıyı kontrol et.
const bool TEST_MODU  = true;   // İlk yüklemede true: LED'leri tek tek yakar. Çalışınca false yap.
const bool SATIR_ANOT = true;   // 1088BS için true. Hiç LED yanmıyorsa false yap.
const bool KULE_TERS  = false;  // Kule yukarıdan aşağı büyüyorsa true yap
const bool AYNA       = false;  // Sağ-sol ters görünüyorsa true yap
const bool HILE_MODU  = false;  // "AVM modu": son katta blok bazen bir adım kayar

// ================== PİNLER ==================
// Matris satır bacakları (R1..R8) -> fiziksel bacak: 9,14,8,12,1,7,2,5
const byte satirPin[8] = {2, 3, 4, 5, 6, 7, 8, 9};
// Matris sütun bacakları (C1..C8) -> fiziksel bacak: 13,3,4,10,6,11,15,16
// (Her birinin önünde 220 ohm direnç var!)
const byte sutunPin[8] = {10, 11, 12, 13, A0, A1, A2, A3};
const byte BUTON  = A4;  // Butonun diğer ucu GND'ye
const byte BUZZER = A5;  // Buzzer'ın eksi ucu GND'ye

// ================== OYUN AYARLARI ==================
// Her kattaki adım süresi (ms). Küçüldükçe blok hızlanır.
const unsigned int HIZ[8] = {220, 195, 170, 150, 130, 110, 95, 80};
// Her katta izin verilen en fazla blok genişliği (oyunu zorlaştırır)
const byte MAKS_GENISLIK[8] = {3, 3, 3, 2, 2, 2, 1, 1};

// ================== DEĞİŞKENLER ==================
byte oyunEkran[8];   // Ekranda ne görünecek? (satır başına 8 bit)
byte kat[8];         // Kilitlenmiş bloklar
byte aktifKat;       // Şu an hangi kattayız (0 = en alt)
byte genislik;       // Hareket eden bloğun genişliği
int  konum;          // Bloğun en sol hücresi
int  yon;            // +1 sağa, -1 sola
unsigned long sonAdim;
unsigned int adimSuresi;
byte rekor = 0;

enum Durum { BEKLEME, OYUN, BITTI };
Durum durum = BEKLEME;

// =========================================================
//  EKRAN: Matrisi satır satır tarar. Göz hepsini aynı anda
//  yanıyor sanar (göz kalıcılığı).
// =========================================================
byte taranan = 0;
unsigned long sonTarama = 0;

void satirYaz(byte r, bool aktif) {
  digitalWrite(satirPin[r], (aktif == SATIR_ANOT) ? HIGH : LOW);
}

void sutunYaz(byte c, bool yan) {
  digitalWrite(sutunPin[c], (yan != SATIR_ANOT) ? HIGH : LOW);
}

void ekranTara() {
  if (micros() - sonTarama < 1500) return;  // her satır ~1.5 ms yanar
  sonTarama = micros();

  // Önce her şeyi söndür (gölgelenmeyi önler)
  for (byte c = 0; c < 8; c++) sutunYaz(c, false);
  for (byte r = 0; r < 8; r++) satirYaz(r, false);

  // Matris satırını oyun satırına çevir
  byte g = KULE_TERS ? taranan : 7 - taranan;
  byte satirVerisi = oyunEkran[g];

  satirYaz(taranan, true);
  for (byte c = 0; c < 8; c++) {
    byte x = AYNA ? 7 - c : c;
    sutunYaz(c, bitRead(satirVerisi, x));
  }

  taranan = (taranan + 1) % 8;
}

// =========================================================
//  TÜM EKRANI YAK (güvenli yöntem)
//  Bir satırda 8 LED birden yanarsa pinden ~90 mA çekilir (sınır 40 mA).
//  Bu yüzden her satırı 3'erli gruplar halinde çok hızlı tararız:
//  8 satır x 3 grup = 24 adım. Göz bunu "64 LED aynı anda yanıyor" diye görür.
// =========================================================
void tumunuYak(unsigned long ms) {
  const byte gruplar[3][2] = {{0, 3}, {3, 6}, {6, 8}};  // sütun 0-2, 3-5, 6-7
  unsigned long baslangic = millis();
  while (millis() - baslangic < ms) {
    for (byte r = 0; r < 8; r++) {
      for (byte g = 0; g < 3; g++) {
        for (byte c = 0; c < 8; c++) sutunYaz(c, false);
        for (byte i = 0; i < 8; i++) satirYaz(i, false);
        satirYaz(r, true);
        for (byte c = gruplar[g][0]; c < gruplar[g][1]; c++) sutunYaz(c, true);
        delayMicroseconds(400);
      }
    }
  }
  for (byte c = 0; c < 8; c++) sutunYaz(c, false);
  for (byte i = 0; i < 8; i++) satirYaz(i, false);
}

// Açılış gösterisi: tüm ekran 3 kez yanıp söner, her seferinde bip
void acilisGosterisi() {
  for (byte i = 0; i < 3; i++) {
    tone(BUZZER, 523 + i * 262, 150);
    tumunuYak(300);
    delay(200);
  }
}

// Beklerken ekranı taramaya devam et (delay yerine bunu kullan!)
void bekle(unsigned long ms) {
  unsigned long baslangic = millis();
  while (millis() - baslangic < ms) ekranTara();
}

void ekraniTemizle() {
  for (byte i = 0; i < 8; i++) oyunEkran[i] = 0;
}

// =========================================================
//  BUTON: Sadece "basıldığı an" bir kez true döner
// =========================================================
bool butonBasildi() {
  static bool onceki = HIGH;
  static unsigned long sonDegisim = 0;
  bool simdi = digitalRead(BUTON);
  if (simdi != onceki && millis() - sonDegisim > 30) {  // 30 ms parazit filtresi
    sonDegisim = millis();
    onceki = simdi;
    if (simdi == LOW) return true;
  }
  return false;
}

// =========================================================
//  YARDIMCILAR
// =========================================================
byte blokMaske() {
  return ((1 << genislik) - 1) << konum;  // örn. genislik 3, konum 2 -> 00011100
}

byte bitSay(byte b) {
  byte n = 0;
  while (b) { n += b & 1; b >>= 1; }
  return n;
}

void ciz() {
  ekraniTemizle();
  for (byte g = 0; g < aktifKat; g++) oyunEkran[g] = kat[g];
  oyunEkran[aktifKat] = blokMaske();
}

// =========================================================
//  OYUN AKIŞI
// =========================================================
void yeniKatHazirla() {
  // Blok rastgele soldan ya da sağdan başlasın
  if (random(2) == 0) { konum = 0; yon = 1; }
  else                { konum = 8 - genislik; yon = -1; }
  adimSuresi = HIZ[aktifKat];
  sonAdim = millis();
}

void oyunuBaslat() {
  for (byte i = 0; i < 8; i++) kat[i] = 0;
  aktifKat = 0;
  genislik = MAKS_GENISLIK[0];

  // 3-2-1 geri sayım
  ekraniTemizle();
  for (int i = 3; i > 0; i--) {
    tone(BUZZER, 880, 120);
    bekle(500);
  }
  tone(BUZZER, 1760, 250);

  yeniKatHazirla();
  durum = OYUN;
}

void blokuHareketEttir() {
  if (millis() - sonAdim < adimSuresi) return;
  sonAdim = millis();
  int yeni = konum + yon;
  if (yeni < 0 || yeni + genislik > 8) {  // kenara çarptı, geri dön
    yon = -yon;
    yeni = konum + yon;
  }
  konum = yeni;
}

void blokuKilitle() {
  // --- AVM MODU: gerçek ödül makineleri gibi son katta "şans" ayarı ---
  if (HILE_MODU && aktifKat == 7 && random(100) < 70) {
    konum = (konum > 0) ? konum - 1 : konum + 1;  // blok "kayıyor"
  }

  byte blok  = blokMaske();
  byte sonuc = (aktifKat == 0) ? blok : (blok & kat[aktifKat - 1]);
  byte dusen = blok & ~sonuc;  // alttakiyle örtüşmeyen parçalar

  if (sonuc == 0) {  // hiç örtüşme yok
    oyunBitti();
    return;
  }

  // Kesilen parçaları yakıp söndür
  if (dusen) {
    tone(BUZZER, 220, 150);
    for (byte i = 0; i < 3; i++) {
      oyunEkran[aktifKat] = sonuc | dusen; bekle(80);
      oyunEkran[aktifKat] = sonuc;         bekle(80);
    }
  } else {
    tone(BUZZER, 600 + aktifKat * 120, 70);  // tam isabet: yükselen ses
  }

  kat[aktifKat] = sonuc;
  aktifKat++;

  if (aktifKat == 8) {
    kazandin();
    return;
  }

  genislik = min(bitSay(sonuc), MAKS_GENISLIK[aktifKat]);
  yeniKatHazirla();
}

void oyunBitti() {
  if (aktifKat > rekor) rekor = aktifKat;
  Serial.print("Oyun bitti! Ulasilan kat: ");
  Serial.print(aktifKat);
  Serial.print("  |  Rekor: ");
  Serial.println(rekor);

  // Kuleyi yakıp söndür + üzgün ses
  tone(BUZZER, 330, 250); bekle(280);
  tone(BUZZER, 262, 250); bekle(280);
  tone(BUZZER, 196, 500);
  for (byte i = 0; i < 4; i++) {
    ekraniTemizle();                                bekle(200);
    for (byte g = 0; g < aktifKat; g++) oyunEkran[g] = kat[g];
    bekle(200);
  }
  durum = BITTI;
}

void kazandin() {
  rekor = 8;
  Serial.println("KAZANDIN! Kule tamamlandi!");

  // Zafer melodisi
  const int nota[] = {523, 659, 784, 1047, 784, 1047};
  const int sure[] = {120, 120, 120, 250, 120, 400};
  for (byte i = 0; i < 6; i++) {
    tone(BUZZER, nota[i], sure[i]);
    bekle(sure[i] + 30);
  }

  // Kule yanıp söner
  for (byte i = 0; i < 5; i++) {
    ekraniTemizle();                            bekle(150);
    for (byte g = 0; g < 8; g++) oyunEkran[g] = kat[g];
    bekle(150);
  }

  // Havai fişek: aşağıdan yukarı çıkan ışıklar (her satırda en fazla 3 LED!)
  for (byte tur = 0; tur < 3; tur++) {
    for (byte g = 0; g < 8; g++) {
      ekraniTemizle();
      oyunEkran[g] = 0b10000001 | (1 << (3 + (g % 2)));
      bekle(60);
    }
  }
  durum = BITTI;
}

// Bekleme ekranı: altta bir blok gidip gelir
void beklemeAnimasyonu() {
  static unsigned long t = 0;
  static int x = 0, d = 1;
  if (millis() - t < 150) return;
  t = millis();
  ekraniTemizle();
  oyunEkran[0] = 0b11 << x;
  x += d;
  if (x < 0 || x > 6) { d = -d; x += 2 * d; }
}

// =========================================================
//  TEST MODU: LED'leri sırayla yakar.
//  Doğru bağlantıda: sol alttan başlar, sağa gider, sonra bir üst satır.
// =========================================================
void testModu() {
  for (byte g = 0; g < 8; g++) {
    for (byte x = 0; x < 8; x++) {
      ekraniTemizle();
      bitSet(oyunEkran[g], x);
      bekle(150);
    }
  }
  ekraniTemizle();
}

// =========================================================
void setup() {
  for (byte i = 0; i < 8; i++) {
    pinMode(satirPin[i], OUTPUT);
    pinMode(sutunPin[i], OUTPUT);
  }
  pinMode(BUTON, INPUT_PULLUP);
  pinMode(BUZZER, OUTPUT);
  Serial.begin(9600);
  Serial.println("STACKER hazir. Baslamak icin butona bas!");

  if (TEST_MODU) testModu();
  acilisGosterisi();   // açılışta tüm ekran yanıp söner
}

void loop() {
  ekranTara();  // Ekran her zaman taranmalı!

  switch (durum) {
    case BEKLEME:
      beklemeAnimasyonu();
      if (butonBasildi()) {
        randomSeed(micros());  // basılma anı rastgele -> her oyun farklı
        oyunuBaslat();
      }
      break;

    case OYUN:
      blokuHareketEttir();
      ciz();
      if (butonBasildi()) blokuKilitle();
      break;

    case BITTI:
      if (butonBasildi()) durum = BEKLEME;
      break;
  }
}
