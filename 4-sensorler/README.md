# 4. Bölüm · Sensörler

Matris devresi bitti. Bu bölümde her ders **sıfırdan, boş bir breadboard'a** kurulan **küçük** bir devreyle başlar:
birkaç parça, birkaç kablo, ~10 dakikada kurulum. Sonra hemen koda geçeriz.

Yeni fikir: Arduino artık sadece "yan / sön" demiyor, **dış dünyayı ölçüyor**.

## Ders akışı (1. bölümle aynı)

| Adım | Dosya | Ne için? |
|:---:|---|---|
| 1 | `Adim1_Dokuman_SXX.pdf` | Parçaları seç → pinleri bul → adım adım montaj → kontrol listesi → devrenin ve kodun mantığı |
| 2 | `Adim2_Kod_SXX/` | Derste yüklenen kod |
| 3 | `Adim3_Gorev_SXX.pdf` | Öğrenci görevleri (devreye dokunmadan, sadece kod) |
| 4 | `Adim4_Cevap_Dokuman_SXX.pdf` + `Adim4_Cevap_SXX/` | Cevapların anlatımı + cevap kodu (`GOREV = 1, 2, 3`) |

## Dersler

| Ders | Konu | Parçalar | 1 Doküman | 2 Kod | 3 Görev | 4 Cevap |
|---|---|---|:---:|:---:|:---:|:---:|
| **S01** · Işık Theremini | `analogRead`, `map`, `tone` · gerilim bölücü | LDR, 10 kΩ, pasif buzzer, 5 kablo | [PDF](S01_isik_theremini/Adim1_Dokuman_S01.pdf) | [kod](S01_isik_theremini/Adim2_Kod_S01/Adim2_Kod_S01.ino) | [PDF](S01_isik_theremini/Adim3_Gorev_S01.pdf) | [PDF](S01_isik_theremini/Adim4_Cevap_Dokuman_S01.pdf) · [kod](S01_isik_theremini/Adim4_Cevap_S01/Adim4_Cevap_S01.ino) |

### S01 ek kodları (aynı devre)

| Dosya | Ne yapar? |
|---|---|
| [Ekstra_Karar_S01](S01_isik_theremini/Ekstra_Karar_S01/Ekstra_Karar_S01.ino) | Gece alarmı: `if` / `else` ile karanlıkta öter, aydınlıkta susar |
| [Ekstra_Dongu_S01](S01_isik_theremini/Ekstra_Dongu_S01/Ekstra_Dongu_S01.ino) | Açılışta `for` ile 3 bip, sonra `while` ile karanlık sürdükçe alarm |
| [Ekstra_Pro_S01](S01_isik_theremini/Ekstra_Pro_S01/Ekstra_Pro_S01.ino) | Profesyonel sürüm: kalibrasyon, yumuşatma, `millis` |

## Kod yapbozu (akıllı tahta)

[**Kod Atölyesi'ni aç**](https://raw.githack.com/arif7esat/Robotic-Coding/main/kod-atolyesi/index.html): öğrenciler tahtada kod parçalarını parmakla sürükleyip boşluklara yerleştirir. Doğru parça yeşil, yanlış parça kırmızı yanıp söner.

| Seviye | Konu | Kod |
|---|---|---|
| Temel 1 | İskelet: `setup`, `loop`, `{ }`, `;` | ders kodu |
| Temel 2 | Değişkenler: `const`, `int`, `=` | ders kodu |
| Temel 3 | Fonksiyonlar: parantez içine ne girer? | ders kodu |
| Temel 4 | Karar: `if` / `else` | Ekstra_Karar_S01 |
| Temel 5 | Döngü: `for` / `while` | Ekstra_Dongu_S01 |
| Profesyonel | Kalibrasyon, yumuşatma, `millis` | Ekstra_Pro_S01 |

İnternet olmadan da çalışır: `kod-atolyesi/index.html` dosyasını USB bellekle tahtaya kopyalayıp çift tıklamak yeter.
