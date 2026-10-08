/*
  ================================================================
   T5  -  IŞIKLI PİYANO  ·  GÖREV CEVAPLARI
  ================================================================
   Kullanım: GOREV sayısını 1-5 arasında değiştir ve yükle.
   Devre: T5 devresi, ek gerekmez.

   SORULARIN CEVAPLARI
   Görev 3 - Her basışta tek nota için "yeni basış" yakalanmalı; buton
     basılı tutulunca notalar tekrar tekrar çalmamalı. Bunun için önceki
     buton durumu hatırlanır (T4 görev 3 ile aynı fikir).
   Görev 4 - Melodi iki dizide tutulur: hangi nota (frekans) ve ne kadar
     sürecek (ms). Örnek melodi bu dosya için yazıldı; öğrenci kendi
     notalarını yazabilir. 0 frekans "sus" demektir.
   Görev 5 - Basılı tuttukça: her turda butona bakılır; basılıysa sıradaki
     nota çalar, bırakılınca sıra başa döner.
  ================================================================
*/

const int GOREV = 1;     // <-- 1 ... 5

const int SATIR[8] = {A3, 12, 9, A0, 2, 8, 3, 6};
const int SUTUN[8] = {13, 4, 5, A2, 7, A1, 11, 10};
const int BUTON  = A4;
const int BUZZER = A5;

int notalar[8] = {262, 294, 330, 349, 392, 440, 494, 523};

// Görev 4: kendi melodimiz (indeks: 0 = Do ... 7 = üst Do, -1 = sus)
int melodi[12] = {0, 2, 4, 4, -1, 4, 5, 4, 2, 0, -1, 0};
int sure[12]   = {250, 250, 400, 250, 150, 250, 250, 250, 250, 400, 150, 600};

int sira = 0;          // görev 3 ve 5
int onceki = HIGH;     // görev 3

void notaCal(int i, int ms) {           // i: 0..7
  digitalWrite(SUTUN[i], LOW);           // notanın LED'i
  tone(BUZZER, notalar[i], ms);
  delay(ms + 50);
  digitalWrite(SUTUN[i], HIGH);
}

void setup() {
  for (int i = 0; i < 8; i++) {
    pinMode(SATIR[i], OUTPUT);
    pinMode(SUTUN[i], OUTPUT);
    digitalWrite(SATIR[i], LOW);
    digitalWrite(SUTUN[i], HIGH);
  }
  pinMode(BUTON, INPUT_PULLUP);
  pinMode(BUZZER, OUTPUT);
  digitalWrite(SATIR[7], HIGH);          // en alt satır
}

void loop() {
  int durum = digitalRead(BUTON);

  if (GOREV == 1 && durum == LOW) {      // ters sırayla
    for (int i = 7; i >= 0; i--) notaCal(i, 200);
  }
  if (GOREV == 2 && durum == LOW) {      // daha hızlı
    for (int i = 0; i < 8; i++) notaCal(i, 80);
  }
  if (GOREV == 3) {                      // her basışta tek nota
    if (durum == LOW && onceki == HIGH) {
      notaCal(sira, 250);
      sira = sira + 1;
      if (sira == 8) sira = 0;
    }
    onceki = durum;
  }
  if (GOREV == 4 && durum == LOW) {      // kendi melodin
    for (int k = 0; k < 12; k++) {
      if (melodi[k] < 0) delay(sure[k]);           // sus
      else               notaCal(melodi[k], sure[k]);
    }
  }
  if (GOREV == 5) {                      // basılı tuttukça yüksel
    if (durum == LOW) {
      notaCal(sira, 200);
      if (sira < 7) sira = sira + 1;     // en tizde kalır
    } else {
      sira = 0;
    }
  }
}
