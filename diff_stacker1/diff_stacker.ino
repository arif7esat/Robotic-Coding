/*
  ============================================================
   STACKER PRO - Seviyeli, canlı arcade kule oyunu
   Donanım: Arduino UNO + 1088BS 8x8 matris + 8 adet 220 ohm
            + 1 buton + 1 buzzer
   Pinler : satırlar D2-D9, sütunlar D10-D13 A0-A3,
            buton A4, buzzer A5
  ============================================================
   NASIL OYNANIR?
   - Butona bas: oyun başlar. 3 canla başlarsın.
   - En alttaki satırda bir blok sağa sola kayar, butonla durdur.
   - Alttaki bloğun üstüne gelmeyen parçalar kesilir, blok daralır.
   - 8 katı tamamlarsan seviye atlarsın ve +1 can kazanırsın (en fazla 5).
   - Blok tamamen boşa düşerse 1 can gider, seviye baştan başlar.
   - Can biterse oyun biter. 9 seviyenin hepsini geçen ŞAMPİYON olur!

   SEVİYELERİN ÖZELLİKLERİ
   1-2 : Isınma, sadece hız artar
   3   : RÜZGAR   -> blok bazen aniden yön değiştirir
   4   : HAYALET  -> blok arada bir görünmez olur
   5   : Dar blokla başlarsın
   6   : RÜZGAR + hızlı daralma
   7   : HAYALET + dar blok
   8   : RÜZGAR + HAYALET
   9   : RÜZGAR + HAYALET + ZİKZAK (hız düzensiz değişir) -> FİNAL
  ============================================================
*/

#include <EEPROM.h>

// ================== AYARLAR ==================
const bool TEST_MODU  = false;  // true: açılışta LED'leri tek tek yakar
const bool SATIR_ANOT = true;   // 1088BS için true. Hiç LED yanmıyorsa false yap
const bool KULE_TERS  = false;  // Kule yukarıdan aşağı büyüyorsa true yap
const bool AYNA       = false;  // Sağ-sol ters görünüyorsa true yap

// ================== PİNLER ==================
// Matris satır bacakları (R1..R8) -> fiziksel bacak: 9,14,8,12,1,7,2,5
const byte satirPin[8] = {2, 3, 4, 5, 6, 7, 8, 9};
// Matris sütun bacakları (C1..C8) -> fiziksel bacak: 13,3,4,10,6,11,15,16
// (Her birinin önünde 220 ohm direnç var!)
const byte sutunPin[8] = {10, 11, 12, 13, A0, A1, A2, A3};
const byte BUTON  = A4;  // Butonun diğer ucu GND'ye
const byte BUZZER = A5;  // Buzzer'ın eksi ucu GND'ye

// ================== OYUN AYARLARI ==================
const byte BASLANGIC_CAN = 3;
const byte MAKS_CAN      = 5;
const byte SON_SEVIYE    = 9;

// Özel zorluklar (birleştirilebilir: RUZGAR | HAYALET)
#define RUZGAR  1   // blok bazen aniden yön değiştirir
#define HAYALET 2   // blok arada bir görünmez olur
#define ZIKZAK  4   // her adımın süresi düzensiz

struct Seviye {
  unsigned int hizBas;  // ilk kattaki adım süresi (ms) - büyük = yavaş
  unsigned int hizSon;  // son kattaki adım süresi (ms)
  byte genislik;        // başlangıç blok genişliği
  byte adim;            // kaç katta bir en fazla genişlik 1 azalır
  byte ozel;            // özel zorluklar
};

const Seviye SEVIYELER[SON_SEVIYE] = {
  //  hizBas hizSon gen adim ozel
  {   240,   150,   3,  4,   0                          },  // 1
  {   210,   120,   3,  3,   0                          },  // 2
  {   190,   105,   3,  3,   RUZGAR                     },  // 3
  {   175,    95,   3,  3,   HAYALET                    },  // 4
  {   160,    90,   2,  4,   0                          },  // 5
  {   150,    85,   3,  2,   RUZGAR                     },  // 6
  {   140,    80,   2,  4,   HAYALET                    },  // 7
  {   130,    75,   2,  3,   RUZGAR | HAYALET           },  // 8
  {   115,    65,   2,  3,   RUZGAR | HAYALET | ZIKZAK  }   // 9 FİNAL
};

// ================== DEĞİŞKENLER ==================
byte oyunEkran[8];   // Ekranda ne görünecek? (satır başına 8 bit)
byte kat[8];         // Kilitlenmiş bloklar
byte aktifKat;       // Şu an hangi kattayız (0 = en alt)
byte genislik;       // Hareket eden bloğun genişliği
int  konum;          // Bloğun en sol hücresi
int  yon;            // +1 sağa, -1 sola
unsigned long sonAdim;
unsigned int  adimSuresi;
unsigned int  beklemeSuresi;

byte seviye;         // 1..9
byte can;            // 0..5
unsigned long puan;

enum Durum { BEKLEME, OYUN, BITTI };
Durum durum = BEKLEME;

// =========================================================
//  EKRAN: Matrisi satır satır tarar. Göz hepsini aynı anda
//  yanıyor sanar (göz kalıcılığı).
//  KURAL: Bir satırda en fazla 3 LED yakılır (pin akımı sınırı).
// =========================================================
byte taranan = 0;
unsigned long sonTarama = 0;

void satirYaz(byte r, bool aktif) {
  digitalWrite(satirPin[r], (aktif == SATIR_ANOT) ? HIGH : LOW);
}

void sutunYaz(byte c, bool yan) {
  digitalWrite(sutunPin[c], (yan != SATIR_ANOT) ? HIGH : LOW);
}

void hepsiniSondur() {
  for (byte c = 0; c < 8; c++) sutunYaz(c, false);
  for (byte r = 0; r < 8; r++) satirYaz(r, false);
}

// GÜVENLİ MOD: Kalp gibi bir satırda 3'ten fazla LED yanan resimler için.
// Her satır 3'erli gruplara bölünüp ayrı ayrı yakılır (8 satır x 3 grup).
// Boş gruplar atlanır, böylece resim daha parlak görünür.
bool guvenliMod = false;

void guvenliModAyarla(bool acik) {
  guvenliMod = acik;
  taranan = 0;
}

void guvenliTara() {
  if (micros() - sonTarama < 500) return;
  sonTarama = micros();
  hepsiniSondur();
  const byte bas[3] = {0, 3, 6}, son[3] = {3, 6, 8};
  for (byte deneme = 0; deneme < 24; deneme++) {   // sıradaki dolu grubu bul
    byte r = taranan / 3, grp = taranan % 3;
    taranan = (taranan + 1) % 24;
    byte g = KULE_TERS ? r : 7 - r;
    byte veri = oyunEkran[g];
    bool dolu = false;
    for (byte c = bas[grp]; c < son[grp]; c++) if (bitRead(veri, AYNA ? 7 - c : c)) dolu = true;
    if (!dolu) continue;
    satirYaz(r, true);
    for (byte c = bas[grp]; c < son[grp]; c++) sutunYaz(c, bitRead(veri, AYNA ? 7 - c : c));
    return;
  }
}

void ekranTara() {
  if (guvenliMod) { guvenliTara(); return; }
  if (micros() - sonTarama < 1500) return;  // her satır ~1.5 ms yanar
  sonTarama = micros();

  hepsiniSondur();  // gölgelenmeyi önler

  byte g = KULE_TERS ? taranan : 7 - taranan;  // matris satırı -> oyun satırı
  byte satirVerisi = oyunEkran[g];

  satirYaz(taranan, true);
  for (byte c = 0; c < 8; c++) {
    byte x = AYNA ? 7 - c : c;
    sutunYaz(c, bitRead(satirVerisi, x));
  }
  taranan = (taranan + 1) % 8;
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
//  TÜM EKRANI YAK (güvenli yöntem)
//  Her satırı 3'erli gruplar halinde çok hızlı tarar:
//  8 satır x 3 grup = 24 adım. Göz 64 LED'i birden yanık görür.
// =========================================================
void tumunuYak(unsigned long ms) {
  const byte gruplar[3][2] = {{0, 3}, {3, 6}, {6, 8}};
  unsigned long baslangic = millis();
  while (millis() - baslangic < ms) {
    for (byte r = 0; r < 8; r++) {
      for (byte g = 0; g < 3; g++) {
        hepsiniSondur();
        satirYaz(r, true);
        for (byte c = gruplar[g][0]; c < gruplar[g][1]; c++) sutunYaz(c, true);
        delayMicroseconds(400);
      }
    }
  }
  hepsiniSondur();
}

// =========================================================
//  RAKAM VE CAN GÖSTERİMİ (her satırda en fazla 3 LED)
// =========================================================
const byte RAKAM[10][5] = {      // 3x5 piksel rakamlar, üstten alta
  {0b111, 0b101, 0b101, 0b101, 0b111},  // 0
  {0b010, 0b011, 0b010, 0b010, 0b111},  // 1
  {0b111, 0b100, 0b111, 0b001, 0b111},  // 2
  {0b111, 0b100, 0b111, 0b100, 0b111},  // 3
  {0b101, 0b101, 0b111, 0b100, 0b100},  // 4
  {0b111, 0b001, 0b111, 0b100, 0b111},  // 5
  {0b111, 0b001, 0b111, 0b101, 0b111},  // 6
  {0b111, 0b100, 0b100, 0b100, 0b100},  // 7
  {0b111, 0b101, 0b111, 0b101, 0b111},  // 8
  {0b111, 0b101, 0b111, 0b100, 0b111}   // 9
};

void rakamCiz(byte d) {
  ekraniTemizle();
  for (byte i = 0; i < 5; i++) oyunEkran[6 - i] = RAKAM[d][i] << 3;  // ortada
}

// Seviye ekranı: solda "L", sağda seviye numarası  ->  L3
// (bir satırda 3'ten fazla LED yanabilir, güvenli modda gösterilir)
void seviyeEkraniCiz(byte d) {
  ekraniTemizle();
  for (byte i = 0; i < 5; i++) oyunEkran[6 - i] = (RAKAM[d][i] << 4) | 0b0001;  // L'nin dikey çizgisi
  oyunEkran[2] |= 0b0011;                                                         // L'nin tabanı
}

// Can ekranı: solda küçük kalp, sağda can sayısı  ->  ♥3
void canEkraniCiz(byte n) {
  ekraniTemizle();
  for (byte i = 0; i < 5; i++) oyunEkran[6 - i] = RAKAM[n][i] << 4;
  oyunEkran[5] |= 0b101;   // küçük kalp: üst
  oyunEkran[4] |= 0b111;   //             orta
  oyunEkran[3] |= 0b010;   //             uç
}

// =========================================================
//  KALPLER (can gösterimi) - güvenli modda çizilir
// =========================================================
const byte KALP_BUYUK[8] = {      // alttan üste: oyunEkran[0]..[7]
  0b00000000,
  0b00011000,
  0b00111100,
  0b01111110,
  0b11111111,
  0b11111111,
  0b11111111,
  0b01100110
};
const byte KALP_KIRIK[8] = {      // ortasından zikzak çatlak geçen kalp
  0b00000000,
  0b00010000,
  0b00101100,
  0b01110110,
  0b11101111,
  0b11110111,
  0b11101111,
  0b01100110
};
const byte KALP_KUCUK[8] = {
  0b00000000,
  0b00000000,
  0b00011000,
  0b00111100,
  0b00100100,
  0b00000000,
  0b00000000,
  0b00000000
};

void resimCiz(const byte* resim) {
  for (byte i = 0; i < 8; i++) oyunEkran[i] = resim[i];
}

// Kalp "can" kadar atar (her atışta bip), sonra can sayısı rakamla görünür
void canGoster(byte n) {
  guvenliModAyarla(true);
  for (byte i = 0; i < n; i++) {
    resimCiz(KALP_BUYUK); tone(BUZZER, 880, 60); bekle(220);
    resimCiz(KALP_KUCUK);                        bekle(160);
  }
  resimCiz(KALP_BUYUK); bekle(400);
  canEkraniCiz(n); bekle(1000);
  guvenliModAyarla(false);
}

// Can değişimi: kayıpta kalp kırılır, kazançta kalp parlayarak atar
void canDegisimi(byte eski, byte yeni) {
  guvenliModAyarla(true);
  if (yeni < eski) {
    resimCiz(KALP_BUYUK); bekle(400);
    tone(BUZZER, 150, 300);
    for (byte i = 0; i < 3; i++) {
      resimCiz(KALP_KIRIK); bekle(250);
      ekraniTemizle();      bekle(120);
    }
    resimCiz(KALP_KIRIK); bekle(500);
  } else {
    for (byte i = 0; i < 4; i++) {
      resimCiz(KALP_BUYUK); tone(BUZZER, 660 + i * 220, 80); bekle(150);
      resimCiz(KALP_KUCUK);                                  bekle(100);
    }
    resimCiz(KALP_BUYUK); bekle(500);
  }
  for (byte i = 0; i < 3; i++) {   // ♥eski -> ♥yeni yanıp söner
    canEkraniCiz(eski); bekle(200);
    canEkraniCiz(yeni); bekle(200);
  }
  bekle(500);
  guvenliModAyarla(false);
}

// Can zaten en fazladayken seviye geçilirse: kalp parlar ama sayı değişmez
void canDolu() {
  guvenliModAyarla(true);
  for (byte i = 0; i < 3; i++) {
    resimCiz(KALP_BUYUK); tone(BUZZER, 1319, 60); bekle(150);
    ekraniTemizle();                               bekle(100);
  }
  canEkraniCiz(MAKS_CAN); bekle(800);
  guvenliModAyarla(false);
}

// =========================================================
//  BUTON: Sadece "basıldığı an" bir kez true döner
// =========================================================
bool butonOnceki = HIGH;

// Animasyonlardan sonra çağrılır: o sırada basılı tutulan buton
// yeni bir "basış" sayılmasın
void butonSifirla() { butonOnceki = digitalRead(BUTON); }

bool butonBasildi() {
  bool& onceki = butonOnceki;
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
const Seviye& sv() { return SEVIYELER[seviye - 1]; }

byte blokMaske() {
  return ((1 << genislik) - 1) << konum;  // örn. genislik 3, konum 2 -> 00011100
}

byte bitSay(byte b) {
  byte n = 0;
  while (b) { n += b & 1; b >>= 1; }
  return n;
}

// Bu katta izin verilen en fazla genişlik
byte maksGenislik(byte k) {
  int g = sv().genislik - k / sv().adim;
  return g < 1 ? 1 : g;
}

void ciz() {
  ekraniTemizle();
  for (byte g = 0; g < aktifKat; g++) oyunEkran[g] = kat[g];
  bool gorunur = true;
  if (sv().ozel & HAYALET) gorunur = (millis() % 1000) < 600;  // %40 görünmez
  if (gorunur) oyunEkran[aktifKat] = blokMaske();
}

// =========================================================
//  SESLER
// =========================================================
void melodi(const int* nota, const int* sure, byte adet) {
  for (byte i = 0; i < adet; i++) {
    if (nota[i]) tone(BUZZER, nota[i], sure[i]);
    bekle(sure[i] + 30);
  }
}

// =========================================================
//  OYUN AKIŞI
// =========================================================
void canKaybet();
void seviyeTamam();
void oyunBitti();
void sampiyon();

void yeniKatHazirla() {
  if (random(2) == 0) { konum = 0; yon = 1; }
  else                { konum = 8 - genislik; yon = -1; }
  adimSuresi = sv().hizBas - (long)(sv().hizBas - sv().hizSon) * aktifKat / 7;
  beklemeSuresi = adimSuresi;
  sonAdim = millis();
}

// Seviye ekranı: seviye numarası + canlar
void seviyeTanit() {
  ekraniTemizle(); bekle(300);
  guvenliModAyarla(true);
  seviyeEkraniCiz(seviye);
  const int n[] = {523, 659, 784};
  const int s[] = {100, 100, 200};
  melodi(n, s, 3);
  bekle(900);
  guvenliModAyarla(false);

  canGoster(can);

  ekraniTemizle(); bekle(300);
}

void seviyeyiBaslat() {
  for (byte i = 0; i < 8; i++) kat[i] = 0;
  aktifKat = 0;
  genislik = maksGenislik(0);
  seviyeTanit();
  yeniKatHazirla();
  butonSifirla();
  durum = OYUN;
}

void oyunuBaslat() {
  seviye = 1;
  can = BASLANGIC_CAN;
  puan = 0;
  Serial.println("=== YENI OYUN ===");

  // 3-2-1 geri sayım
  ekraniTemizle();
  for (byte i = 3; i > 0; i--) {
    rakamCiz(i);
    tone(BUZZER, 880, 120);
    bekle(500);
  }
  tone(BUZZER, 1760, 250);
  seviyeyiBaslat();
}

void blokuHareketEttir() {
  if (millis() - sonAdim < beklemeSuresi) return;
  sonAdim = millis();

  // RÜZGAR: %10 ihtimalle blok aniden yön değiştirir
  if ((sv().ozel & RUZGAR) && random(100) < 10) yon = -yon;

  int yeni = konum + yon;
  if (yeni < 0 || yeni + genislik > 8) {  // kenara çarptı, geri dön
    yon = -yon;
    yeni = konum + yon;
  }
  konum = yeni;

  // ZİKZAK: bir sonraki adımın süresi %60-%140 arası rastgele
  if (sv().ozel & ZIKZAK) beklemeSuresi = (long)adimSuresi * random(60, 141) / 100;
  else                    beklemeSuresi = adimSuresi;
}

void blokuKilitle() {
  byte blok  = blokMaske();
  byte sonuc = (aktifKat == 0) ? blok : (blok & kat[aktifKat - 1]);
  byte dusen = blok & ~sonuc;  // alttakiyle örtüşmeyen parçalar

  if (sonuc == 0) {  // hiç örtüşme yok -> can gider
    canKaybet();
    return;
  }

  if (dusen) {  // kesilen parçaları yakıp söndür
    tone(BUZZER, 220, 150);
    for (byte i = 0; i < 3; i++) {
      oyunEkran[aktifKat] = sonuc | dusen; bekle(80);
      oyunEkran[aktifKat] = sonuc;         bekle(80);
    }
  } else {      // tam isabet: yükselen ses + bonus puan
    tone(BUZZER, 600 + aktifKat * 120, 70);
    puan += 5 * seviye;
  }

  kat[aktifKat] = sonuc;
  puan += bitSay(sonuc) * seviye;
  aktifKat++;

  if (aktifKat == 8) {
    seviyeTamam();
    return;
  }

  genislik = min(bitSay(sonuc), maksGenislik(aktifKat));
  yeniKatHazirla();
}

void canKaybet() {
  // Kuleyi yakıp söndür + üzgün ses
  tone(BUZZER, 330, 200); bekle(230);
  tone(BUZZER, 262, 200); bekle(230);
  tone(BUZZER, 196, 400);
  for (byte i = 0; i < 3; i++) {
    ekraniTemizle();                                     bekle(150);
    for (byte g = 0; g < aktifKat; g++) oyunEkran[g] = kat[g];
    bekle(150);
  }

  canDegisimi(can, can - 1);
  can--;
  Serial.print("Can kaybedildi! Kalan can: ");
  Serial.println(can);

  if (can == 0) oyunBitti();
  else          seviyeyiBaslat();  // aynı seviye baştan
}

void seviyeTamam() {
  Serial.print("Seviye "); Serial.print(seviye);
  Serial.print(" tamam! Puan: "); Serial.println(puan);

  const int n[] = {523, 659, 784, 1047};
  const int s[] = {100, 100, 100, 300};
  melodi(n, s, 4);
  for (byte i = 0; i < 3; i++) {  // kule yanıp söner
    ekraniTemizle();                            bekle(120);
    for (byte g = 0; g < 8; g++) oyunEkran[g] = kat[g];
    bekle(120);
  }

  puan += 50 * seviye;  // seviye bonusu

  if (can < MAKS_CAN) {  // +1 can
    canDegisimi(can, can + 1);
    can++;
  } else {
    canDolu();
  }

  if (seviye == SON_SEVIYE) {
    sampiyon();
    return;
  }
  seviye++;
  seviyeyiBaslat();
}

void rekorKontrol(byte ulasilan) {
  byte rekor = EEPROM.read(0);
  if (rekor > SON_SEVIYE) rekor = 0;  // ilk kullanımda boş hafıza
  Serial.print("Ulasilan seviye: "); Serial.print(ulasilan);
  Serial.print("  |  Puan: "); Serial.print(puan);
  Serial.print("  |  Rekor seviye: "); Serial.println(max(rekor, ulasilan));

  if (ulasilan > rekor) {  // yeni rekor: kalıcı hafızaya yaz
    EEPROM.write(0, ulasilan);
    Serial.println("*** YENI REKOR! ***");
    for (byte i = 0; i < 3; i++) {
      tone(BUZZER, 1319, 80); bekle(100);
      tone(BUZZER, 1568, 80); bekle(100);
    }
  }
}

void oyunBitti() {
  const int n[] = {392, 330, 262, 196};
  const int s[] = {200, 200, 200, 500};
  melodi(n, s, 4);
  // Ulaşılan seviyeyi göster (yanıp söner)
  guvenliModAyarla(true);
  for (byte i = 0; i < 4; i++) {
    seviyeEkraniCiz(seviye); bekle(350);
    ekraniTemizle();         bekle(200);
  }
  rekorKontrol(seviye);
  seviyeEkraniCiz(seviye);   // BITTI ekranında güvenli modda kalır
  butonSifirla();
  durum = BITTI;
}

void sampiyon() {
  Serial.println("*** SAMPIYON! Tum seviyeler tamamlandi! ***");
  const int n[] = {523, 659, 784, 1047, 784, 1047, 1319};
  const int s[] = {120, 120, 120, 250, 120, 250, 600};
  melodi(n, s, 7);

  for (byte i = 0; i < 3; i++) {  // tüm ekran flaşları
    tone(BUZZER, 1047 + i * 262, 120);
    tumunuYak(250);
    bekle(150);
  }
  for (byte tur = 0; tur < 3; tur++) {  // havai fişek
    for (byte g = 0; g < 8; g++) {
      ekraniTemizle();
      oyunEkran[g] = 0b10000001 | (1 << (3 + (g % 2)));
      bekle(60);
    }
  }
  rekorKontrol(SON_SEVIYE);
  guvenliModAyarla(true);
  seviyeEkraniCiz(9);
  butonSifirla();
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

// Açılış gösterisi: tüm ekran 3 kez yanıp söner
void acilisGosterisi() {
  for (byte i = 0; i < 3; i++) {
    tone(BUZZER, 523 + i * 262, 150);
    tumunuYak(300);
    delay(200);
  }
}

// TEST MODU: LED'leri sırayla yakar (sol alttan başlar, sağa, sonra yukarı)
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
  Serial.println("STACKER PRO hazir. Baslamak icin butona bas!");

  if (TEST_MODU) testModu();
  acilisGosterisi();
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
      if (butonBasildi()) { guvenliModAyarla(false); durum = BEKLEME; }
      break;
  }
}
