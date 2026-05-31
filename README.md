# SFML Arkanoid (Breakout) Oyunu

Bu proje, Kocaeli Üniversitesi Yazılım Mühendisliği Bölümü Programlama II dersi için geliştirilmiş nesne yönelimli bir Arkanoid klonudur.

## Geliştirilen Özellikler
- **Dinamik Harita Yükleme:** Oyun haritaları ve tuğla canları dışarıdan `seviye1.txt` ve `seviye2.txt` dosyalarından dinamik olarak okunur.
- **Modüler Mimari:** Proje `main.cpp`, `OyunFonksiyonlari.cpp` ve `OyunFonksiyonlari.hpp` şeklinde yapılandırılarak nesne yönelimli programlama (OOP) mantığına uygun geliştirilmiştir.
- **Oyuncu Dostu Power-Up Sistemi:** Kırılan bloklardan %40 şansla güçlendirici kutular düşer. 
  - **Sarı Kutu:** Raketin boyutunu genişleterek topu yakalamayı kolaylaştırır.
  - **Kırmızı Kutu:** Topun hızını %30 yavaşlatarak oyuncuya zaman ve kontrol avantajı sağlar.
- **Çok Seviyeli Yapı (Seviye Geçiş Ekranı):** Seviye 1 başarıyla tamamlandığında oyun duraklatılır ve kullanıcı pencere başlığındaki yönergeyle Enter'a basarak daha zorlu olan Seviye 2'ye geçer.

## Çalıştırma Talimatları
Proje CMake yapısıyla kurulmuştur. `build` klasörü içerisinde şu komutlarla derleyip çalıştırabilirsiniz:
```bash
cmake --build .
.\Arkanoid.exe


## GitHub Repository
Projenin kaynak kodlarına ve commit geçmişine aşağıdaki bağlantıdan ulaşabilirsiniz:
https://github.com/eliflklc1012-cell/Arkanoid-Game