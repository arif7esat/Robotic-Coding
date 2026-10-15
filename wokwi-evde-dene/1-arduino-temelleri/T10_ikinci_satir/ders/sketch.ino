/*
  ================================================================
   T10  -  İKİNCİ SATIR: HAYALET LED VE GÖZ YANILMASI
  ================================================================
   Yeni kavramlar:  kendi fonksiyonunu yazmak (parametreli void),
                    hayalet LED, göz yanılması
   Devre:           T09 + satır 2 kablosu (j7 -> D12)

   Artık 2 satır x 3 sütun = 6 LED'e ulaşabiliyoruz.
   Hedef iki LED: sol üst (satır 1, sütun 1) ve sağ alt (satır 2, sütun 3).

   HAYALET_DENEYI = true  : ikisini birden yakmaya çalışır. İki satır
                            açık, iki sütun açık -> 4 kesişim -> 4 LED!
   HAYALET_DENEYI = false : LED'leri sırayla yakar. Her an tek yol açık.
                            bekleme küçülünce göz ikisini birlikte görür.

   GÖREVLER
   9. sınıf
   1) bekleme'yi 500, 100, 20, 5 yap. Titreme hangi değerde kayboldu?
   2) HAYALET_DENEYI = true yap. Hangi LED'ler yandı? Neden 4 tane?
   10. sınıf
   3) 6 LED ile "T" harfi çiz: üst satırın üçü + alt satırın ortası.
      Hayalet olmasın! (İpucu: ledYak ile tek tek, bekleme 2 ms.)
  ================================================================
*/

const int SATIR[2] = {A3, 12};     // satır 1, satır 2 (anotlar)
const int SUTUN[3] = {13, 4, 5};   // sütun 1, 2, 3 (katotlar)

const bool HAYALET_DENEYI = false;
int bekleme = 500;

void hepsiniSondur() {
  for (int s = 0; s < 2; s++) digitalWrite(SATIR[s], LOW);
  for (int k = 0; k < 3; k++) digitalWrite(SUTUN[k], HIGH);
}

void ledYak(int s, int k) {        // s: satır sırası, k: sütun sırası
  hepsiniSondur();
  digitalWrite(SATIR[s], HIGH);
  digitalWrite(SUTUN[k], LOW);
}

void setup() {
  for (int s = 0; s < 2; s++) pinMode(SATIR[s], OUTPUT);
  for (int k = 0; k < 3; k++) pinMode(SUTUN[k], OUTPUT);
  hepsiniSondur();
}

void loop() {
  if (HAYALET_DENEYI) {
    digitalWrite(SATIR[0], HIGH);   // iki satır birden
    digitalWrite(SATIR[1], HIGH);
    digitalWrite(SUTUN[0], LOW);    // iki sütun birden
    digitalWrite(SUTUN[2], LOW);
  } else {
    ledYak(0, 0);                   // sol üst
    delay(bekleme);
    ledYak(1, 2);                   // sağ alt
    delay(bekleme);
  }
}
