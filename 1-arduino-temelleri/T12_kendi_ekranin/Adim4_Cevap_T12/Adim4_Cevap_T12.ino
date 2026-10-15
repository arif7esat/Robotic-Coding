/*
  ================================================================
   T12  -  KENDİ EKRANINI SÜR  ·  GÖREV CEVAPLARI
  ================================================================
   Kullanım: GOREV sayısını 1-3 arasında değiştir ve yükle.
   Devre:    T11 devresi (tam matris + buton A4). Kabloya dokunma.

   SORULARIN CEVAPLARI
   Görev 1 - Örnek: kalp. Her satır tam 8 karakter olmalı; eksik ya da
     fazla karakter resmi kaydırır.
   Görev 2 - Bir resim 8 satır x 3 parça = 24 adımda çizilir.
       300 us  ->  24 x (0,3 ms + komutlar) = ~7-9 ms -> saniyede 100+ resim: sabit
       5000 us ->  24 x 5 ms   = 120 ms  ->  saniyede ~8 resim: titrer
     Göz yanılması bozulur; satırların ve parçaların sırayla yandığını
     görürsün. Tarama, ekranın gerçekte böyle çalıştığını ele verir.
   Görev 3 - ciz() ve parcaYak() artık hangi resmi çizeceğini parametre
     olarak alır (resmi okuyan parcaYak; sadece ciz değişirse buton işe yaramaz).
     Aynı fonksiyon iki resim için de çalışır; loop sadece seçim yapar.
  ================================================================
*/

const int GOREV = 1;     // <-- 1, 2 ya da 3

const int SATIR[8] = {A3, 12, 9, A0, 2, 8, 3, 6};
const int SUTUN[8] = {13, 4, 5, A2, 7, A1, 11, 10};
const int BUTON = A4;

const char* RESIM[8] = {   // gülen yüz (T12'nin kendi resmi)
  "..####..",
  ".#....#.",
  "#.#..#.#",
  "#......#",
  "#.#..#.#",
  "#..##..#",
  ".#....#.",
  "..####.."
};

const char* KALP[8] = {    // Görev 1
  "........",
  ".##..##.",
  "#..##..#",
  "#......#",
  ".#....#.",
  "..#..#..",
  "...##...",
  "........"
};

const char* RESIM2[8] = {  // Görev 3: üzgün yüz
  "..####..",
  ".#....#.",
  "#.#..#.#",
  "#......#",
  "#..##..#",
  "#.#..#.#",
  ".#....#.",
  "..####.."
};

int parcaBekleme = 300;    // mikrosaniye

void hepsiniSondur() {
  for (int i = 0; i < 8; i++) {
    digitalWrite(SATIR[i], LOW);
    digitalWrite(SUTUN[i], HIGH);
  }
}

// resim'in s. satırında, bas. sütundan başlayan 3'lü parçayı yakar
void parcaYak(const char* resim[], int s, int bas) {
  hepsiniSondur();
  digitalWrite(SATIR[s], HIGH);
  for (int k = bas; k < bas + 3 && k < 8; k++) {
    if (resim[s][k] == '#') digitalWrite(SUTUN[k], LOW);
  }
}

void ciz(const char* resim[]) {
  for (int s = 0; s < 8; s++) {
    for (int bas = 0; bas < 8; bas += 3) {
      parcaYak(resim, s, bas);
      delayMicroseconds(parcaBekleme);
    }
  }
  hepsiniSondur();
}

void setup() {
  for (int i = 0; i < 8; i++) {
    pinMode(SATIR[i], OUTPUT);
    pinMode(SUTUN[i], OUTPUT);
  }
  hepsiniSondur();
  pinMode(BUTON, INPUT_PULLUP);
  if (GOREV == 2) parcaBekleme = 5000;
}

void loop() {
  if (GOREV == 1) ciz(KALP);
  if (GOREV == 2) ciz(RESIM);                    // yavaş tarama
  if (GOREV == 3) {
    if (digitalRead(BUTON) == LOW) ciz(RESIM2);  // basılı: üzgün
    else                           ciz(RESIM);   // bırakık: gülen
  }
}
