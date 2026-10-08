/*
  ================================================================
   T3  -  SÜTUN DOLDUR VE AKIMI GÖZLEMLE
  ================================================================
   Öğreneceklerin:  iç içe for, akım paylaşımı, devreyi korumak
   (Arduino Temelleri PDF: bölüm 3 ve 9)

   Bir sütunun LED'lerini tek tek ekliyoruz. DİKKATLİ BAK:
   LED sayısı arttıkça hepsi SÖNÜKLEŞİR. Neden?
   Bir sütundaki 8 LED aynı 220 ohm direnci paylaşır. Direnç toplam
   akımı ~13 mA ile sınırlar; 1 LED yanarsa hepsi onun, 8 LED yanarsa
   her birine ~1,6 mA düşer. Toplam akım sabit kalır, yani bu güvenli.

   !!! TERSİNİ ASLA YAPMA !!!
   Satır pinlerinde direnç yoktur. Bir SATIRIN 8 LED'ini aynı anda
   yakarsan o tek satır pininden ~100 mA akım çekilir. Arduino pininin
   sınırı 40 mA'dir; pin zamanla bozulur.
   Kural: SÜTUN boyunca yakmak güvenli, SATIR boyunca yakmak değil.

   GÖREVLER
   9. sınıf
   1) Sütun aşağıdan yukarı dolsun.  İpucu: for (int r = 7; r >= 0; r--)
   2) Kaçıncı LED'de parlaklığın gözle görülür şekilde düştüğünü not et.
   3) delay değerlerini değiştirerek animasyonu hızlandır.
   10. sınıf
   4) Seri Monitöre "yanan LED: 3, LED başına ~4.3 mA" gibi yazdır.
      İpucu: 13.0 / yananSayisi  (13.0 yazmazsan sonuç tam sayı olur)
   5) Sütunları soldan sağa değil, ortadan dışa doğru doldur.
  ================================================================
*/

const int SATIR[8] = {A3, 12, 9, A0, 2, 8, 3, 6};
const int SUTUN[8] = {13, 4, 5, A2, 7, A1, 11, 10};

void hepsiniSondur() {
  for (int i = 0; i < 8; i++) {
    digitalWrite(SATIR[i], LOW);
    digitalWrite(SUTUN[i], HIGH);
  }
}

void setup() {
  for (int i = 0; i < 8; i++) {
    pinMode(SATIR[i], OUTPUT);
    pinMode(SUTUN[i], OUTPUT);
  }
  hepsiniSondur();
}

void loop() {
  for (int s = 0; s < 8; s++) {          // her sütun için
    hepsiniSondur();
    digitalWrite(SUTUN[s], LOW);         // sadece bu sütun açık
    for (int r = 0; r < 8; r++) {        // satırları tek tek ekle
      digitalWrite(SATIR[r], HIGH);
      delay(150);
    }
    delay(400);
  }
}
