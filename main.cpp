//sfml grafik kütüphanesi ve standart kütüphaneleri dahil etme
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <string> // Skor ve canları pencere başlığına metin olarak yazdırmak için ekledik
#include <cstdlib> // Power-up düşme şansı (rand) için ekledik
#include "OyunFonksiyonlari.hpp" //header dosyası


int main() {
    std::cout << "1. Adim: Program basladi..." << std::endl;
    
    // Pencere oluşturmayı deniyoruz(pencere boyutunu, adını belirleme)
    // Başlangıçta seviye, skor ve can bilgisini pencere başlığında gösteriyoruz
    sf::RenderWindow window(sf::VideoMode(800, 600), "Arkanoid - Seviye: 1  Skor: 0  Can: 3");
    
    std::cout << "2. Adim: Pencere basariyla olusturuldu!" << std::endl;
    
    window.setFramerateLimit(60);

    //raket tanımladım(boyutunu, rengini ve başlangıç konumunu belirleme)
    sf::RectangleShape paddle(sf::Vector2f(120.f, 20.f));
    paddle.setFillColor(sf::Color::Cyan);
    paddle.setPosition(340.0f, 550.0f);
            
    //oyunun farklı bilgisayarlarda aynı hızda çalışmasını sf::clock kullanarak sağlıyoruz
    sf::Clock clock;
    float paddleSpeed = 600.0f;

    // top ayarları
    sf::CircleShape ball(10.0f); //sfmlden hazır aldığım top çizme kalıbı , buyukluğu 10
    ball.setFillColor(sf::Color::White); //topun  rengi
    ball.setPosition(400.0f, 300.0f);//ektranın boyutuna göre ortada durması
    sf::Vector2f ballVelocity(300.0f, -300.0f);  //topun yönü
        
    // oyunun durumunu takip etmek için basit değişkenler (Skor ve can takibi için)
    int skor = 0;
    int can = 3;
    int seviye = 1;
    bool oyunBitti = false;
    bool seviyeGecisEkrani = false; //seviye-1 bitince enter basılmasını bekleyen kontrol değişkeni
    
    // Düşen güç arttırıcı kutularını hafızada tutacak vektörümüz
    std::vector<PowerUp> powerUps;

    //blokları tutacak olan vektörümüzü tanımlıyoruz ve dosyadan haritayı okuyup blokları ekrana dizen fonksiyonla ekrana diziyoruzz
    std::vector<Tugla> blocks;
    seviyeYukle("seviye1.txt", blocks); // Döngü başlamadan önce dosyayı bir kez okuyup blokları hafızaya alır

    //döngü, pencere açık olduğu sürece kontrolleri çizimleri yapaıcak
    while (window.isOpen()) {

        //kapatma tuşu gibi olayları kontrol etme 
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
    
        // geçen süreyi hesaplama ve girdilere göre raketi hareket ettirme kısmı
        sf::Time dt = clock.restart();
            
        if (!oyunBitti) {

            // seviye geçiş ekranı kontrolü
            if (seviyeGecisEkrani) {
                window.setTitle("TEBRIKLER! SEVIYE GECILDI! - Bir sonraki seviye için ENTER'a basin");
                ballVelocity = sf::Vector2f(0.0f, 0.0f);
                ball.setPosition(400.0f, 300.0f);

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
                    seviye = 2;
                    seviyeYukle("seviye2.txt", blocks); // yeni seviye yüklenicek

                    // topu, raketi ve aktif power-up'ları seviye-2 için sıfırlama
                    ball.setPosition(400.0f, 300.0f);
                    paddle.setSize(sf::Vector2f(120.f, 20.f)); // Raket boyutunu normale döndür
                    paddle.setPosition(340.0f, 550.0f);
                    powerUps.clear(); // Eski seviyeden kalan kutuları temizle

                    ballVelocity = sf::Vector2f(320.0f, -320.0f); // topun hızını biraz artırarak yeni seviyeye başlıyoruz

                    seviyeGecisEkrani = false; // seviye geçiş ekranını kapat

                    clock.restart();
                    continue; // "contunie" yazım hatası düzeltildi.
                }
            } 
            else {
                // Normal oyun döngüsü: raket hareketi, top hareketi, çarpışmalar ve skor güncelleme
                raketHareketi(paddle, paddleSpeed, dt);
                
                // Topun düşme kontrolünü yapıyoruz
                bool topDustu = topHareketiVeDuvarSekmesi(ball, ballVelocity, dt);

                if (topDustu) {
                    can--;
                    if (can <= 0) {
                        oyunBitti = true;
                        ballVelocity = sf::Vector2f(0.0f, 0.0f); // Topu durduruyoruz
                        window.setTitle("OYUN BITTI! Caniniz Kalmadi. Toplam Skor: " + std::to_string(skor));
                    } else {
                        // Can gitirse topu, raketi ve güçlendiricileri merkeze sıfırla
                        ball.setPosition(400.0f, 300.0f);
                        paddle.setSize(sf::Vector2f(120.f, 20.f)); // Özellikleri sıfırla
                        paddle.setPosition(340.0f, 550.0f);
                        powerUps.clear(); // Ekrandaki kutuları temizle

                        ballVelocity = sf::Vector2f(300.0f, -300.0f);
                    }
                }
            
                topRaketCarpmasi(ball, ballVelocity, paddle);
                
                // Blok çarpışmasından önceki blok sayısını tutuyoruz (Kutu düşürme kontrolü için)
                size_t eskiBlokSayisi = blocks.size();

                // Blok çarpışmasını ve skor artışını yönetiyoruz
                topBlokCarpismasi(ball, ballVelocity, blocks, skor);
                
                // Eğer bir blok kırıldıysa %40 şansla içerisinden güç arttırıcı kutu düşürüyoruz
                if (blocks.size() < eskiBlokSayisi) {
                    if (rand() % 10 < 4) { // %40 olasılık
                        PowerUp p;
                        p.shape.setSize(sf::Vector2f(25.f, 15.f)); // Kutunun boyutu
                        p.shape.setPosition(ball.getPosition().x, ball.getPosition().y - 10.f); // Kırılma noktasından başlasın
                        p.tip = (rand() % 2) + 1; // 1 veya 2 rastgele seçilsin

                        // Tipine göre kutunun rengini belirliyoruz
                        if (p.tip == 1) {
                            p.shape.setFillColor(sf::Color::Yellow); // Sarı kutu raket genişletir
                        } else {
                            p.shape.setFillColor(sf::Color::Red); // Kırmızı kutu topu hızlandırır
                        }
                        powerUps.push_back(p);
                    }
                }

                // Düşen güç arttırıcı kutuların hareket ve raketle çarpışma kontrollerini yapıyoruz
                for (size_t i = 0; i < powerUps.size(); ) {
                    if (!powerUps[i].aktif) {
                        powerUps.erase(powerUps.begin() + i);
                        continue;
                    }

                    // Kutuyu sabit bir hızla aşağı doğru hareket ettiriyoruz
                    powerUps[i].shape.move(0.0f, 200.0f * dt.asSeconds());

                    // Raket düşen kutuyu yakaladı mı kontrol ediyoruz
                    if (powerUps[i].shape.getGlobalBounds().intersects(paddle.getGlobalBounds())) {
                        if (powerUps[i].tip == 1) {
                            // Güç Arttırıcı 1: Raket Genişletme (Genişliği 180f yapıyoruz)
                            paddle.setSize(sf::Vector2f(180.f, 20.f));
                        } 
                        else if (powerUps[i].tip == 2) {
                            // Güç Arttırıcı 2: Topu yavaşlatma (%30)
                            ballVelocity.x *= 0.70f;
                            ballVelocity.y *= 0.70f;
                        }
                        powerUps[i].aktif = false; // Yakalanan kutuyu iptal et
                    }
                    // Eğer kutu raketten kaçıp ekranın altına düşerse listeden silinsin
                    else if (powerUps[i].shape.getPosition().y > 600.f) {
                        powerUps[i].aktif = false;
                    }

                    i++;
                }
            
                // Hata veren font kütüphanesi yerine, skoru pencerenin üstündeki başlığa canlı yazdırıyoruz
                if (!oyunBitti) {
                    std::string yeniBaslik = "Arkanoid - Seviye: " + std::to_string(seviye) + 
                                             "   Skor: " + std::to_string(skor) + 
                                             "   Can: " + std::to_string(can);
                    window.setTitle(yeniBaslik);
                }
            
                //  Blok Bitme Durumları ---
                if (blocks.empty() && seviye == 1) {
                    seviyeGecisEkrani = true; // Seviye 1 bittiyse geçiş moduna al
                }
                else if (blocks.empty() && seviye == 2) {
                    // Seviye 2 de bittiyse oyunu tamamen bitir
                    window.setTitle("TEBRIKLER! OYUNU TAMAMEN KAZANDINIZ! TOPLAM SKOR: " + std::to_string(skor));
                    oyunBitti = true; 

                    ballVelocity = sf::Vector2f(0.0f, 0.0f); // Topu durduruyoruz
                }
            }
        }
            
        // ekran temizleme, raketi çizme ve ekrana yansıtma kısmı
        window.clear(sf::Color::Black);
        
        window.draw(paddle);
        window.draw(ball);
        
        //listede kalan tuğlaları tek tek çizme
        for (const auto& block : blocks) {
            window.draw(block.shape);
        }
        
        // Aktif olan güç arttırıcı kutuları ekrana çiziyoruz
        for (const auto& p : powerUps) {
            window.draw(p.shape);
        }
            
        window.display();
    }

    std::cout << "3. Adim: Program kapaniyor." << std::endl;
    return 0;
}