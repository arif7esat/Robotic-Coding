/*
  ================================================================
   T12  -  KENDİ EKRANINI SÜR
  ================================================================
   Yeni kavramlar:  resmi veri olarak saklamak, satır satır tarama
   Devre:           T11 ile aynı. Kabloya dokunma.

   RESIM dizisinin her satırı ekranın bir satırıdır:
       '#' = LED yanık,  '.' = LED sönük
   Ekran satır satır, çok hızlı taranır: her an sadece BİR satır açık.
   Göz bunu tek bir resim olarak görür (T10'daki göz yanılması).

   GÜVENLİK: Bir satırda en fazla 3 LED aynı anda yanmalı (T04).
   Bu yüzden her satır 3'erli parçalar halinde yakılır:
       sütun 1-3, sonra 4-6, sonra 7-8.
   02. haftadaki matris.h dosyası tam olarak bunu yapıyordu.

   GÖREVLER
   9. sınıf
   1) RESIM'i değiştir: kendi resmini çiz (kalp, ok, harf...).
   2) delayMicroseconds(300) değerini 5000 yap. Ne görüyorsun? Neden?
   10. sınıf
   3) İkinci bir resim ekle (RESIM2). Butona basılıyken o görünsün.
      İpucu: ciz fonksiyonuna hangi resmi çizeceğini parametre olarak ver.
  ================================================================
*/

const int SATIR[8] = {A3, 12, 9, A0, 2, 8, 3, 6};
const int SUTUN[8] = {13, 4, 5, A2, 7, A1, 11, 10};

const char* RESIM[8] = {
  "..####..",
  ".#....#.",
  "#.#..#.#",
  "#......#",
  "#.#..#.#",
  "#..##..#",
  ".#....#.",
  "..####.."
};

void hepsiniSondur() {
  for (int i = 0; i < 8; i++) {
    digitalWrite(SATIR[i], LOW);
    digitalWrite(SUTUN[i], HIGH);
  }
}

// s. satırın, bas. sütundan başlayan 3'lü parçasını yakar
void parcaYak(int s, int bas) {
  hepsiniSondur();
  digitalWrite(SATIR[s], HIGH);
  for (int k = bas; k < bas + 3 && k < 8; k++) {
    if (RESIM[s][k] == '#') digitalWrite(SUTUN[k], LOW);
  }
}

void ciz() {
  for (int s = 0; s < 8; s++) {              // 8 satır
    for (int bas = 0; bas < 8; bas += 3) {   // parçalar: 0, 3, 6
      parcaYak(s, bas);
      delayMicroseconds(300);
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
}

void loop() {
  ciz();
}
