# Stacker Denemeleri (Arşiv)

> ⚠️ **Bu dosyalar eski pin düzeniyle çalışır** (`{2,3,4,5,6,7,8,9}` / `{10,11,12,13,A0,A1,A2,A3}`).
> Güncel devreyle uyumlu kodlar → [haftalar/01-stacker/kod/](../../haftalar/01-stacker/kod/)

Stacker'ın ilk fikirden son hâline kadar geçtiği yolun kayıtları. Her dosya bir deneme aşaması:

| Klasör | Ne olduğu |
|---|---|
| `stacker/` | İlk sürüm. Tek seviye, can sistemi yok, test modu dahil. |
| `stacker_ogrenci/` | Öğrenci sürümünün eski pin düzenli hâli. |
| `stacker_pro/` | Pro sürüm, 9 seviye detaylı, eski pinler. 540 satır. |
| `stacker_pro_new/` | Pro sürümün ara geçiş hâli, eski pinli. |
| `diff_stacker1/` | Pro sürüme can değişim animasyonu eklenen deneme. |
| `diff_stacker2/` | Pro sürüme yüz animasyonları (mutlu, üzgün, ağlayan) eklenen deneme. |
| `Dot_Matris_Control/` | Matris testi, eski pinler, delik isimleri yok (sonradan eklendi). |

### Neden eski?

İlk denemelerde matris bacaklarını sırayla D2..D9 ve D10..A3 pinlerine bağladık. Sonra breadboard üzerinde kabloların çapraz geçmesini engellemek için farklı bir pin düzenine geçtik (`{A3, 12, 9, A0, 2, 8, 3, 6}`). Bu düzen kablolamayı çok kolaylaştırdı ama kodda pin listelerinin tamamen değişmesi gerekti.
