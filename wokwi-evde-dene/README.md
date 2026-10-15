# 🖥️ Evde dene: Wokwi simülasyonları

Kiti eve götüremiyor musun? Dersin devresi ve kodu tarayıcıda hazır. **Hesap açmana gerek yok.**

**Her derste iki bağlantı var:**

| Bağlantı | Ne açılır? | Ne zaman kullanırım? |
|---|---|---|
| 🟢 **Ders kodu** | O dersin devresi + derste yüklediğimiz kod (`Adim2_Kod`) | Dersi tekrar etmek, **görevleri kendin denemek** için. Kodu değiştir, ▶ ile çalıştır. |
| 🟣 **Görev çözümü** | Aynı devre + görevlerin cevap kodu (`Adim4_Cevap`) | Görevi **denedikten sonra** kendi çözümünü karşılaştırmak için. En üstteki `const int GOREV = 1;` satırında sayıyı **1, 2 ya da 3** yap, ▶'ya bas. |

**Nasıl kullanılır?**
1. Bağlantıyı aç, sağ üstteki yeşil **▶** tuşuna bas. İlk çalıştırmada derleme **10–20 saniye** sürebilir, bekle.
2. Kodu soldaki pencerede değiştir, ▶ ile yeniden çalıştır. Buton olan derslerde butona fareyle tıkla.
3. **Bir şeyi bozdun mu? Sayfayı yenile.** Devre ve kod ilk haline döner; değişikliklerin başkasını etkilemez.

**Ekranda ne görüyorum?** Matrisin "kutusunu açtık": 64 LED tek tek görünüyor. **Kırmızı yatay teller = satır = LED'in A + (anot) bacağı**, **mavi dikey teller = sütun = LED'in K − (katot) bacağı**. Her derste sadece o derste kurduğumuz kablolar bağlı; bağlı olmayan LED'ler yanmaz. Breadboard delikleri (j8, a7…) simülasyonda yok; montajı sınıfta yapıyoruz.

## 1. Bölüm · Arduino Temelleri

| Ders | 🟢 Ders kodu: derste yüklediğin kod | 🟣 Görev çözümü: görevlerin cevap kodu | Devre dosyaları |
|---|:---:|:---:|:---:|
| **T01** · Tek LED | [▶ Aç](https://wokwi.com/projects/477911568675575809) | [▶ Aç](https://wokwi.com/projects/477912466272732161) | [klasör](../1-arduino-temelleri/T01_tek_led/) |
| **T02** · Değişkenle hız | [▶ Aç](https://wokwi.com/projects/477911947229486081) | [▶ Aç](https://wokwi.com/projects/477912480863673345) | [klasör](../1-arduino-temelleri/T02_degisken/) |
| **T03** · İkinci LED | [▶ Aç](https://wokwi.com/projects/477911977989474305) | [▶ Aç](https://wokwi.com/projects/477912500554888193) | [klasör](../1-arduino-temelleri/T03_ikinci_led/) |
| **T04** · Koşan ışık | [▶ Aç](https://wokwi.com/projects/477912005408700417) | [▶ Aç](https://wokwi.com/projects/477912518320916481) | [klasör](../1-arduino-temelleri/T04_kosan_isik/) |
| **T05** · Dizi ve for | [▶ Aç](https://wokwi.com/projects/477912032382283777) | [▶ Aç](https://wokwi.com/projects/477912536072273921) | [klasör](../1-arduino-temelleri/T05_dizi_ve_for/) |
| **T06** · Buton | [▶ Aç](https://wokwi.com/projects/477912057764125697) | [▶ Aç](https://wokwi.com/projects/477912554994888705) | [klasör](../1-arduino-temelleri/T06_buton/) |
| **T07** · Buzzer | [▶ Aç](https://wokwi.com/projects/477912077893657601) | [▶ Aç](https://wokwi.com/projects/477912806888144897) | [klasör](../1-arduino-temelleri/T07_buzzer/) |
| **T08** · Nefes alan LED | [▶ Aç](https://wokwi.com/projects/477912099218556929) | [▶ Aç](https://wokwi.com/projects/477912840252806145) | [klasör](../1-arduino-temelleri/T08_nefes_alan_led/) |
| **T09** · delay mi, millis mi? | [▶ Aç](https://wokwi.com/projects/477912113402648577) | [▶ Aç](https://wokwi.com/projects/477912873728619521) | [klasör](../1-arduino-temelleri/T09_delay_mi_millis_mi/) |
| **T10** · İkinci satır | [▶ Aç](https://wokwi.com/projects/477912132410192897) | [▶ Aç](https://wokwi.com/projects/477912906927595521) | [klasör](../1-arduino-temelleri/T10_ikinci_satir/) |
| **T11** · Tam matris | [▶ Aç](https://wokwi.com/projects/477912146730600449) | [▶ Aç](https://wokwi.com/projects/477912945708143617) | [klasör](../1-arduino-temelleri/T11_tam_matris/) |
| **T12** · Kendi ekranını sür | [▶ Aç](https://wokwi.com/projects/477912175490952193) | [▶ Aç](https://wokwi.com/projects/477912988664126465) | [klasör](../1-arduino-temelleri/T12_kendi_ekranin/) |

> *Devre dosyaları* sütunundaki klasörlerde her dersin `ders/` ve `gorev-cozumu/` devreleri (`diagram.json` + `sketch.ino`) durur. Bağlantılar bir gün açılmazsa bu dosyalarla aynı devre Wokwi'de yeniden kurulabilir.

← [Ana sayfa](../README.md)
