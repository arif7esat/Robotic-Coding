# Bölüm 1 — Arduino Temelleri (Matrisle, Yardımcısız)

> 🧭 **Buradasın:** **1. Temeller** → 2. Matris ile Kodlama → 3. Stacker

**Tek bir LED'den tam ekrana: 12 derste, her derste tek bir yeni adım.**

Bu bölümde hiçbir yardımcı dosya yok. Öğrenci `pinMode`, `digitalWrite`, `digitalRead`, `analogWrite`, `tone`, `millis` komutlarını çıplak haliyle yazar ve her komutun etkisini doğrudan LED'lerde görür.

Devre **dersten derse büyür ve hiç sökülmez.** T01'de dört kablo (GND dahil) ve bir dirençle başlar; her derste ya tek bir parça eklenir ya da kabloya hiç dokunulmaz. T11'in sonunda devre, **[3-stacker](../3-stacker/) bölümündeki devrenin birebir aynısı** olur. 2. ve 3. bölüm boyunca bu devre hiç sökülmez.

📄 Konu anlatımı: [Arduino Temelleri (PDF)](Arduino_Temelleri.pdf)

---

## Matrisin tek kuralı

| | Satır pini (anot, +) | Sütun pini (katot, −) |
|---|---|---|
| LED **yanar** | `HIGH` | `LOW` |
| LED **söner** | `LOW` | `HIGH` |

> ⚠️ **Güvenlik kuralı (T04):** Bir **satırda** aynı anda en fazla **3 LED**. Satır pininde direnç yok; her LED ~13 mA çeker ve hepsi aynı pinden çıkar (40 mA bir pinin mutlak sınırı: hiç aşılmamalı). Bu bölümün bütün kodları bu kurala uyuyor.

---

## Bir ders nasıl işlenir? (her ders aynı 4 adım)

Her ders klasöründe 4 adımın 5 dosyası vardır; dosya sırası derste izlenecek sıradır:

```
T01_tek_led/
   Adim1_Dokuman_T01.pdf     ← devre kurulumu + kodun mantığı
   Adim2_Kod_T01/            ← herkesin yükleyeceği kod
   Adim3_Gorev_T01.pdf       ← öğrenciye verilen görev sayfası
   Adim4_Cevap_Dokuman_T01.pdf ← görev çözümlerinin mantığı + devreye etkisi
   Adim4_Cevap_T01/          ← görevlerin cevap kodu
```

| Sınıfta | Ne yapıyorsun? | Hangi dosya? |
|:---:|---|---|
| **1** | Devreyi kurdur. Montaj resimlerini projeksiyonda adım adım göster. | `Adim1_Dokuman` → baştaki *devre ve montaj* bölümü |
| **2** | Herkes kodu yüklesin. **Herkesin LED'i yanıyor mu?** Yanmayanlara kontrol listesi / T00 testi. | `Adim2_Kod` |
| **3** | Kodu birlikte oku: parça parça, "bu satır ne yapıyor?" diye sor. | `Adim1_Dokuman` → sondaki **Kodun mantığı** sayfaları (A · B · C) |
| **4** | Görev sayfasını göster / dağıt. Öğrenci kodu *Farklı Kaydet* ile kendi adıyla kaydedip görevlere başlar. | `Adim3_Gorev` (tek sayfa) |
| **5** | Görev bitince çözümü anlat: her görev için **ne değişti → kodun mantığı → devrede ne oluyor → dikkat**. | `Adim4_Cevap_Dokuman` (görev başına önce/sonra kodu, pin tabloları, yanan LED resimleri) |
| **6** | Çözümü karta yükleyip göster. | `Adim4_Cevap`: en üstteki `GOREV = 1` sayısını 1, 2 ya da 3 yap, yükle. |

> **Kablo kuralı:** Devre dersten derse büyür, **hiç sökülmez.** Her görev o dersin devresiyle yapılır; hiçbir görev ek kablo istemez. T11'in sonunda devre [3-stacker](../3-stacker/) devresinin aynısıdır ve 2. ve 3. bölüm boyunca öyle kalır.
>
> **Hızlı ilerlerken:** Devre eklemesi olmayan derslerde (T02, T05, T08, T09, T12) montaj resimlerini atla, ama 1. adımdaki **Bugünün devre bilgisi** bölümünü oku (Ohm hesabı, PWM, millis gibi konular orada). Sonra kodu yükle ve *Kodun mantığı*'na geç.
>
> **Cevap kodlarındaki `GOREV` seçici öğretmen içindir:** `if` T06'da öğretiliyor; öğrenciler kendi çözümlerini ayrı yazar.

---

## Dersler

| # | Ders | Koddaki yeni kavram | Devreye eklenen | 1 | 2 | 3 | 4 | Konu PDF bölümü | Evde dene |
|:---:|---|---|---|:---:|:---:|:---:|:---:|:---:|:---:|
| T00 | [Devre testi](T00_devre_testi/T00_devre_testi.ino) *(isteğe bağlı)* | LED yönü doğru mu? | T01 devresi | | [💻 Kod](T00_devre_testi/T00_devre_testi.ino) | | | | |
| **T01** | [Tek LED](T01_tek_led/) | `setup`, `loop`, `pinMode`, `digitalWrite`, `delay` | satır 1 + sütun 1 | [📐 Doküman](T01_tek_led/Adim1_Dokuman_T01.pdf) | [💻 Kod](T01_tek_led/Adim2_Kod_T01/Adim2_Kod_T01.ino) | [📝 Görev](T01_tek_led/Adim3_Gorev_T01.pdf) | [📘 Çözüm](T01_tek_led/Adim4_Cevap_Dokuman_T01.pdf) · [✅ Kod](T01_tek_led/Adim4_Cevap_T01/Adim4_Cevap_T01.ino) | 2–4 | [🖥️ Wokwi](https://wokwi.com/projects/477911568675575809) |
| **T02** | [Değişkenle hız](T02_degisken/) | `int`, `const`, anlamlı isimler | — | [📐 Doküman](T02_degisken/Adim1_Dokuman_T02.pdf) | [💻 Kod](T02_degisken/Adim2_Kod_T02/Adim2_Kod_T02.ino) | [📝 Görev](T02_degisken/Adim3_Gorev_T02.pdf) | [📘 Çözüm](T02_degisken/Adim4_Cevap_Dokuman_T02.pdf) · [✅ Kod](T02_degisken/Adim4_Cevap_T02/Adim4_Cevap_T02.ino) | 7 | [🖥️ Wokwi](https://wokwi.com/projects/477911947229486081) |
| **T03** | [İkinci LED](T03_ikinci_led/) | iki çıkış, sırayla yakmak | sütun 2 | [📐 Doküman](T03_ikinci_led/Adim1_Dokuman_T03.pdf) | [💻 Kod](T03_ikinci_led/Adim2_Kod_T03/Adim2_Kod_T03.ino) | [📝 Görev](T03_ikinci_led/Adim3_Gorev_T03.pdf) | [📘 Çözüm](T03_ikinci_led/Adim4_Cevap_Dokuman_T03.pdf) · [✅ Kod](T03_ikinci_led/Adim4_Cevap_T03/Adim4_Cevap_T03.ino) | 4 | [🖥️ Wokwi](https://wokwi.com/projects/477911977989474305) |
| **T04** | [Koşan ışık](T04_kosan_isik/) | tekrar eden kod, 3 LED kuralı | sütun 3 | [📐 Doküman](T04_kosan_isik/Adim1_Dokuman_T04.pdf) | [💻 Kod](T04_kosan_isik/Adim2_Kod_T04/Adim2_Kod_T04.ino) | [📝 Görev](T04_kosan_isik/Adim3_Gorev_T04.pdf) | [📘 Çözüm](T04_kosan_isik/Adim4_Cevap_Dokuman_T04.pdf) · [✅ Kod](T04_kosan_isik/Adim4_Cevap_T04/Adim4_Cevap_T04.ino) | 3 | [🖥️ Wokwi](https://wokwi.com/projects/477912005408700417) |
| **T05** | [Dizi ve for](T05_dizi_ve_for/) | dizi `[ ]`, `for` | — | [📐 Doküman](T05_dizi_ve_for/Adim1_Dokuman_T05.pdf) | [💻 Kod](T05_dizi_ve_for/Adim2_Kod_T05/Adim2_Kod_T05.ino) | [📝 Görev](T05_dizi_ve_for/Adim3_Gorev_T05.pdf) | [📘 Çözüm](T05_dizi_ve_for/Adim4_Cevap_Dokuman_T05.pdf) · [✅ Kod](T05_dizi_ve_for/Adim4_Cevap_T05/Adim4_Cevap_T05.ino) | 7, 9 | [🖥️ Wokwi](https://wokwi.com/projects/477912032382283777) |
| **T06** | [Buton](T06_buton/) | `digitalRead`, `INPUT_PULLUP`, `if / else` | buton (GND hattı T01'den beri takılı) | [📐 Doküman](T06_buton/Adim1_Dokuman_T06.pdf) | [💻 Kod](T06_buton/Adim2_Kod_T06/Adim2_Kod_T06.ino) | [📝 Görev](T06_buton/Adim3_Gorev_T06.pdf) | [📘 Çözüm](T06_buton/Adim4_Cevap_Dokuman_T06.pdf) · [✅ Kod](T06_buton/Adim4_Cevap_T06/Adim4_Cevap_T06.ino) | 4, 9 | [🖥️ Wokwi](https://wokwi.com/projects/477912057764125697) |
| **T07** | [Buzzer](T07_buzzer/) | `tone`, `noTone`, frekans | buzzer | [📐 Doküman](T07_buzzer/Adim1_Dokuman_T07.pdf) | [💻 Kod](T07_buzzer/Adim2_Kod_T07/Adim2_Kod_T07.ino) | [📝 Görev](T07_buzzer/Adim3_Gorev_T07.pdf) | [📘 Çözüm](T07_buzzer/Adim4_Cevap_Dokuman_T07.pdf) · [✅ Kod](T07_buzzer/Adim4_Cevap_T07/Adim4_Cevap_T07.ino) | 11 | [🖥️ Wokwi](https://wokwi.com/projects/477912077893657601) |
| **T08** | [Nefes alan LED](T08_nefes_alan_led/) | `analogWrite`, PWM | — | [📐 Doküman](T08_nefes_alan_led/Adim1_Dokuman_T08.pdf) | [💻 Kod](T08_nefes_alan_led/Adim2_Kod_T08/Adim2_Kod_T08.ino) | [📝 Görev](T08_nefes_alan_led/Adim3_Gorev_T08.pdf) | [📘 Çözüm](T08_nefes_alan_led/Adim4_Cevap_Dokuman_T08.pdf) · [✅ Kod](T08_nefes_alan_led/Adim4_Cevap_T08/Adim4_Cevap_T08.ino) | 5 | [🖥️ Wokwi](https://wokwi.com/projects/477912099218556929) |
| **T09** | [delay mi, millis mi?](T09_delay_mi_millis_mi/) | `millis`, `unsigned long`, `bool` | — | [📐 Doküman](T09_delay_mi_millis_mi/Adim1_Dokuman_T09.pdf) | [💻 Kod](T09_delay_mi_millis_mi/Adim2_Kod_T09/Adim2_Kod_T09.ino) | [📝 Görev](T09_delay_mi_millis_mi/Adim3_Gorev_T09.pdf) | [📘 Çözüm](T09_delay_mi_millis_mi/Adim4_Cevap_Dokuman_T09.pdf) · [✅ Kod](T09_delay_mi_millis_mi/Adim4_Cevap_T09/Adim4_Cevap_T09.ino) | 6 | [🖥️ Wokwi](https://wokwi.com/projects/477912113402648577) |
| **T10** | [İkinci satır](T10_ikinci_satir/) | kendi fonksiyonun, hayalet LED | satır 2 | [📐 Doküman](T10_ikinci_satir/Adim1_Dokuman_T10.pdf) | [💻 Kod](T10_ikinci_satir/Adim2_Kod_T10/Adim2_Kod_T10.ino) | [📝 Görev](T10_ikinci_satir/Adim3_Gorev_T10.pdf) | [📘 Çözüm](T10_ikinci_satir/Adim4_Cevap_Dokuman_T10.pdf) · [✅ Kod](T10_ikinci_satir/Adim4_Cevap_T10/Adim4_Cevap_T10.ino) | 10 | [🖥️ Wokwi](https://wokwi.com/projects/477912132410192897) |
| **T11** | [Tam matris](T11_tam_matris/) | iç içe `for`, iki boyut | kalan 6 satır + 5 sütun | [📐 Doküman](T11_tam_matris/Adim1_Dokuman_T11.pdf) | [💻 Kod](T11_tam_matris/Adim2_Kod_T11/Adim2_Kod_T11.ino) | [📝 Görev](T11_tam_matris/Adim3_Gorev_T11.pdf) | [📘 Çözüm](T11_tam_matris/Adim4_Cevap_Dokuman_T11.pdf) · [✅ Kod](T11_tam_matris/Adim4_Cevap_T11/Adim4_Cevap_T11.ino) | 9 | [🖥️ Wokwi](https://wokwi.com/projects/477912146730600449) |
| **T12** | [Kendi ekranını sür](T12_kendi_ekranin/) | resim verisi, tarama | — | [📐 Doküman](T12_kendi_ekranin/Adim1_Dokuman_T12.pdf) | [💻 Kod](T12_kendi_ekranin/Adim2_Kod_T12/Adim2_Kod_T12.ino) | [📝 Görev](T12_kendi_ekranin/Adim3_Gorev_T12.pdf) | [📘 Çözüm](T12_kendi_ekranin/Adim4_Cevap_Dokuman_T12.pdf) · [✅ Kod](T12_kendi_ekranin/Adim4_Cevap_T12/Adim4_Cevap_T12.ino) | 10 | [🖥️ Wokwi](https://wokwi.com/projects/477912175490952193) |

🖥️ **Evde dene (Wokwi):** Kiti eve götüremeyen öğrenci, dersin devresini ve kodunu tarayıcıda çalıştırır; hesap gerekmez. ▶ tuşuna basınca derleme 10–20 saniye sürebilir. Simülasyonda matrisin "kutusu açık": 64 LED, kırmızı yatay teller = satır = anot (A +), mavi dikey teller = sütun = katot (K −). Öğrencinin değişiklikleri yalnızca kendi ekranında kalır; **bozarsan sayfayı yenile**, devre ilk haline döner. Devre dosyaları her dersin `Wokwi/` klasöründe.

📄 *Konu PDF bölümü* sütunu: [Arduino Temelleri (PDF)](Arduino_Temelleri.pdf) içinde o dersin konusunun anlatıldığı bölüm numaraları (ör. 7 = "Değişkenler ve tipler").

**T12 sonraki bölüme köprüdür:** öğrencinin burada kendi yazdığı tarama kodunu (satır satır, 3'erli parçalarla), 2. bölümdeki `matris.h` arka planda yapar. Böylece öğrenci 2. bölümde `ledYak(x, y)` gibi kısa komutlarla çalışırken perdenin arkasında ne olduğunu zaten bilir.

---

## Adım 1 dokümanında neler var?

- **Devre ve montaj** (baştaki sayfalar): mantıksal şema, *bugünün devre bilgisi* (anot/katot, Ohm, akım toplanması, pin sınırı, kısa devre…), tasarım gerekçeleri, breadboard yerleşimi, resimli adım adım montaj (önceki derslerden kalanlar soluk, yeni parça parlak), akımın yolu, kontrol listesi ve hata tablosu. Mavi **"Kelimenin hikâyesi"** kutuları bir terimin kökenini ~1 dakikada anlatır.
- **Kodun mantığı** (son sayfalar): varsa önceki sayfalar için **düzeltme notu** · **A.** kod parça parça, yanında açıklama ve adım adım tablolar · **B.** bu derste öğrenilen komutlar · **C.** sınıfa sorulacak kontrol soruları ve cevapları · T01'de ayrıca **D.** kafaya takılan sorular.

> Devre ve montaj sayfalarının başlığında yazan **"Hafta 03"** bu bölümün eski adıdır. O sayfalarda geçen `T01_tek_led.ino` gibi dosya adlarının yeni karşılığı `Adim2_Kod_T01.ino`'dur. Eski sayfalardaki birkaç hatanın (T01, T10, T12) doğrusu, aynı PDF'in *Kodun mantığı* kısmının başındaki kırmızı **düzeltme notunda** yazıyor.

---

## Sık karşılaşılan sorunlar

| Belirti | Muhtemel sebep | Çözüm |
|---|---|---|
| LED hiç yanmıyor | Satır ve sütun pini karıştı | Satır `HIGH`, sütun `LOW` olmalı |
| LED çok sönük | `pinMode(..., OUTPUT)` unutuldu | `setup()` içine ekle |
| Matris LED'i hiç yanmıyor (T01) | LED yönü ters ya da kablo yanlış delikte | [T00 devre testini](T00_devre_testi/T00_devre_testi.ino) yükle, Seri Monitör'ü aç |
| Başka LED'ler de yanıyor (T10 sonrası) | Önceki LED söndürülmeden yenisi yakıldı | Önce `hepsiniSondur()` çağır |
| T08'de LED ters davranıyor | LED sütun pininde, mantık ters | `255 - parlaklik` kullan |
| Buton rastgele okunuyor | `INPUT` kullanıldı | `INPUT_PULLUP` yap |

Genel sorunlar için → [Sorun giderme](../rehber/SORUN-GIDERME.md)

---

**Sonraki bölüm →** [2. Matris ile Kodlama](../2-matris-ile-kodlama/)

← [Ana sayfa](../README.md) · [Başlarken](../rehber/BASLARKEN.md) · [Sorun giderme](../rehber/SORUN-GIDERME.md) · [Sözlük](../rehber/SOZLUK.md)
