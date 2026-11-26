/*
  ================================================================
   S01  -  IŞIK THEREMİNİ  ·  GÖREV CEVAPLARI
  ================================================================
   Kullanım: GOREV sayısını 1-3 arasında değiştir ve yükle.
   Devre:    Ders devresinin aynısı. Kabloya dokunma.

   Görev 1 - Ters theremin: map'in son iki sayısı yer değiştirdi.
             Karanlık = ince ses, aydınlık = kalın ses.
   Görev 2 - Gece alarmı: ışık ESIK'in altına düşünce öter,
             yoksa susar. ESIK'i sınıfına göre ayarla:
             Seri Monitör'de elin açıkken ve LDR'yi kapatınca
             gördüğün iki sayının ortasını yaz.
   Görev 3 - Notalı theremin: ışık 5 parçaya bölünür, her parça
             bir nota. 1023 / 205 = 4, yani sira hiçbir zaman 5 olmaz.
  ================================================================
*/

const int GOREV = 1;      // <-- 1, 2 ya da 3

const int LDR_PIN = A0;
const int BUZZER  = A5;

const int ESIK = 400;                            // Görev 2: sınıfına göre ayarla
const int NOTA[5] = {262, 294, 330, 349, 392};   // Görev 3: Do Re Mi Fa Sol

void setup() {
  Serial.begin(9600);
}

void loop() {
  int isik = analogRead(LDR_PIN);
  Serial.println(isik);

  if (GOREV == 1) {
    int ses = map(isik, 0, 1023, 2000, 100);    // 100 ile 2000 yer değiştirdi
    tone(BUZZER, ses);
  }

  if (GOREV == 2) {
    if (isik < ESIK) {
      tone(BUZZER, 1000);                       // karanlık: alarm
    } else {
      noTone(BUZZER);                           // aydınlık: sessiz
    }
  }

  if (GOREV == 3) {
    int sira = isik / 205;                      // 0, 1, 2, 3 ya da 4
    tone(BUZZER, NOTA[sira]);
  }

  delay(10);
}
