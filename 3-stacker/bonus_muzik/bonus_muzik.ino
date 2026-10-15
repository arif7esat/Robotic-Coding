// HAVALI MÜZİK: Tetris + Dağ Kralının Salonunda (hızlanan)
// Butona bas: sıradaki parça çalar.

const byte BUTON  = A4;
const byte BUZZER = A5;

// Nota frekansları (Hz)
#define B3  247
#define C4  262
#define Cd4 277   // Do diyez
#define D4  294
#define E4  330
#define F4  349
#define Fd4 370   // Fa diyez
#define G4  392
#define A4n 440
#define B4  494
#define C5  523
#define D5  587
#define E5  659
#define F5  698
#define G5  784
#define A5n 880
#define SUS 0

// ---------- TETRIS (Korobeiniki) ----------
const int tetris[] = {
  E5,B4,C5,D5,C5,B4,  A4n,A4n,C5,E5,D5,C5,  B4,C5,D5,E5,  C5,A4n,A4n,A4n,B4,C5,
  D5,F5,A5n,G5,F5,    E5,C5,E5,D5,C5,       B4,B4,C5,D5,E5, C5,A4n,A4n,SUS
};
const float tetrisS[] = {   // 1 = dörtlük, 0.5 = sekizlik, 1.5 = noktalı dörtlük
  1,0.5,0.5,1,0.5,0.5,  1,0.5,0.5,1,0.5,0.5,  1.5,0.5,1,1,  1,1,0.5,1,0.5,0.5,
  1.5,0.5,1,0.5,0.5,    1.5,0.5,1,0.5,0.5,    1,0.5,0.5,1,1,  1,1,1,1
};

// ---------- DAĞ KRALININ SALONUNDA (Grieg) ----------
const int dag[] = {
  B3,Cd4,D4,E4,Fd4,D4,Fd4,  F4,Cd4,F4,  E4,C4,E4,
  B3,Cd4,D4,E4,Fd4,D4,Fd4,B4,  A4n,Fd4,D4,Fd4,A4n
};
const float dagS[] = {
  0.5,0.5,0.5,0.5,0.5,0.5,1,  0.5,0.5,1,  0.5,0.5,1,
  0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,  0.5,0.5,0.5,0.5,2
};

// Parçayı çal: tempo = 1 vuruşun süresi (ms), carpan = 2 ise bir oktav tiz
void parcaCal(const int* n, const float* s, int adet, int tempo, byte carpan) {
  for (int i = 0; i < adet; i++) {
    int sure = s[i] * tempo;
    if (n[i] != SUS) tone(BUZZER, n[i] * carpan, sure * 0.85);
    delay(sure);
  }
  noTone(BUZZER);
}

void setup() {
  pinMode(BUTON, INPUT_PULLUP);
  pinMode(BUZZER, OUTPUT);
  tone(BUZZER, 1000, 100);   // hazır sinyali
}

void loop() {
  static byte parca = 0;
  if (digitalRead(BUTON) == LOW) {
    if (parca == 0) {
      // Tetris: iki tur, ikincisi biraz daha hızlı
      parcaCal(tetris, tetrisS, sizeof(tetris) / sizeof(int), 280, 1);
      parcaCal(tetris, tetrisS, sizeof(tetris) / sizeof(int), 220, 1);
    } else {
      // Dağ Kralı: 6 tur, her turda hızlanır, son 3 tur bir oktav tiz
      int tempo = 300;
      for (byte tur = 0; tur < 6; tur++) {
        parcaCal(dag, dagS, sizeof(dag) / sizeof(int), tempo, tur < 3 ? 1 : 2);
        tempo = tempo * 0.8;   // her tur %20 hızlan
      }
      tone(BUZZER, 1976, 600); // final
      delay(700);
    }
    parca = (parca + 1) % 2;
    delay(300);
  }
}