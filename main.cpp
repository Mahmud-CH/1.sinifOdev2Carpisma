/****************************************************************************
**  					SAKARYA ÜNİVERSİTESİ
**  	 BİLGİSAYAR VE BİLİŞİM BİLİMLERİ FAKÜLTESİ
**  			 BİLGİSAYAR MÜHENDİSLİĞİ BÖLÜMÜ
**  				 PROGRAMLAMAYA GİRİŞİ DERSİ
**	
**				ÖDEV NUMARASI….....: 2.Odev
**				ÖĞRENCİ ADI SOYADI.: MAHMUD CH
****************************************************************************/


#include <iostream>
#include <cmath> // sqrt(), pow(),hypot(), atan2(), sin() ve cos() icin
using namespace std;

// carpisma sonucunu sayisaldan sozele cevirir
string carpismaBoolToString(const bool carpisma);


//--------------------------N2B-------------------------------


// 2 boyutlu nokta sinifi
class N2B
{
  public:
    double x {};
    double y {};

  N2B() : x{ 0 }, y{ 0 } {}
  N2B(double xy) : x{ xy }, y{ xy } {}
  N2B(double x, double y) : x{ x }, y{ y } {}

    N2B operator+(N2B digerNokta)
    {
      N2B toplam;
      toplam.x = this->x + digerNokta.x;
      toplam.y = this->y + digerNokta.y;

      return toplam;
    };

};


//-------------------------Geo2D------------------------------


class Geo2D
{
  public:
    // herseyin merkezi oldugu icin merkezi burda koydum
    N2B merkez;

  Geo2D() {}
  // merkezi farkli siniftan degerini olusturmak icin
  Geo2D(N2B merkez) : merkez{ merkez } {}

};

class Kare : public Geo2D
{
  public:
    double kenar {};

  // constructur
  Kare(N2B merkez, double kenar) : Geo2D(merkez), kenar{ kenar } {}

};

class Dikdortgen : public Geo2D
{
  public:
  // taban ve kenar dan herhangi bir dikdortgen olusturabiliriz
    double kenar{};
    double taban{};

  Dikdortgen(N2B merkez, double kenar, double taban) : Geo2D(merkez), kenar{ kenar }, taban{ taban } {}

};

class Cember : public Geo2D
{
  public:
    double yaricap{};

  Cember(N2B merkez, double yaricap) : Geo2D(merkez), yaricap{ yaricap } {}

};


//--------------------------N3B------------------------------


// 3 boyutlu nokta sinifi
class N3B : public N2B
{
  public:
    double z {};

  N3B() : N2B(), z{ 0 } {};
  N3B(double x, double y, double z) : N2B(x,y), z{ z } {};

  N3B operator+(N3B digerNokta)
  {
    N3B toplam;
    toplam.x = this->x + digerNokta.x;
    toplam.y = this->y + digerNokta.y;
    toplam.z = this->z + digerNokta.z;

    return toplam;
  }

};


//-------------------------Geo3D------------------------------


class Geo3D
{
  public:
    // herseyin merkezi oldugu icin merkezi burda koydum
    N3B merkez;
    // double yaricap {};
    // koymadim cunku sonrada 3 poyutlu kup hesaplamak
    // istiyorsak o yaricap bize sikinti yaratir 

  Geo3D() {}
  // merkezi farkli siniftan degerini olusturmak icin
  Geo3D(N3B merkez) : merkez{merkez} {}
};

class Kure : public Geo3D
{
  public:
    double yaricap {};
  Kure(N3B merkez, double yaricap) : Geo3D(merkez), yaricap{ yaricap } {}

};

class Silindir : public Geo3D
{
  public:
    double yaricap {};
    double yukseklik {};

  Silindir(N3B merkez, double yaricap, double yukseklik) : Geo3D(merkez), yaricap{ yaricap }, yukseklik{ yukseklik } {}
};


//-----------------------Carpisma-----------------------------


// carpisma formuleri interneten buldum
// anlamak icin kafam patladi
class Carpisma
{
  public:
  
    //------------------Geo2DCarpisma-------------------------
  
    static bool dikdortgenCarpisma(const Dikdortgen birinci, const Dikdortgen ikinci)
    {

      // Burda karmasik gorunmesin diye esittir kullandim (copy-initialization)
      bool xCarpisma = (birinci.merkez.x + birinci.taban/2) >= (ikinci.merkez.x - ikinci.taban/2) &&
                       (birinci.merkez.x - birinci.taban/2) <= (ikinci.merkez.x + ikinci.taban/2);

      bool yCarpisma = (birinci.merkez.y + birinci.kenar/2) >= (ikinci.merkez.y - ikinci.kenar/2) &&
                       (birinci.merkez.y - birinci.kenar/2) <= (ikinci.merkez.y + ikinci.kenar/2);

      bool carpisma { (xCarpisma && yCarpisma) };

      return carpisma;
    }

    static bool kareCarpisma(const Kare birinci, const Kare ikinci)
    {
      Dikdortgen bir(birinci.merkez, birinci.kenar, birinci.kenar);
      Dikdortgen iki(ikinci.merkez, ikinci.kenar, ikinci.kenar);

      bool carpisma { dikdortgenCarpisma(bir, iki) };

      return carpisma;
    }

    static bool dikdortgenCemberCarpisma(const Dikdortgen dikdortgen, const Cember cember)
    {

      double minX { dikdortgen.merkez.x - dikdortgen.kenar/2 };
      double maxX { dikdortgen.merkez.x + dikdortgen.kenar/2 };

      double minY { dikdortgen.merkez.y - dikdortgen.taban/2 };
      double maxY { dikdortgen.merkez.y + dikdortgen.taban/2 };

      // the reason we take the width for the x axis is
      // because the height would only contain one x variable
      // while for the width it can contain multiple
      // like the min of a width could start at (0,1) and end at (10,1)
      // here the x axis changes while the y axis stays the same
      double xEnYakin { max(maxY, min(maxX, cember.merkez.x)) };
      double yEnYakin { max(minY, min(maxY, cember.merkez.y)) };

      double xUzaklik { cember.merkez.x - xEnYakin };
      double yUzaklik { cember.merkez.y - yEnYakin };

      // xUzaklik ile yUzaklik uzunlugu bulmak icin
      // pisagor uygulariz
      double uzaklik { hypot(xUzaklik, yUzaklik) };

      bool carpisma { cember.yaricap >= uzaklik };

      return carpisma;
    }

    static bool cemberCarpisma(const Cember birinci, const Cember ikinci)
    {
      // karesini alacagmiz icin negatif olmasi farketmiyor
      double xEkseni { birinci.merkez.x - ikinci.merkez.x };
      double yEkseni { birinci.merkez.y - ikinci.merkez.y };

      double toplamCap { birinci.yaricap + ikinci.yaricap };

      // uzunluk bulmak icin pisagor uygulariz
      double uzunluk { hypot(xEkseni, yEkseni) };

      bool carpisma { (uzunluk <= toplamCap) };

      return carpisma;
    }

    //------------------Geo3DCarpisma-------------------------

    static bool kureCarpisma(const Kure birinci, const Kure ikinci)
    {
      double xEkseni { birinci.merkez.x - ikinci.merkez.x };
      double yEkseni { birinci.merkez.y - ikinci.merkez.y };
      double zEkseni { birinci.merkez.z - ikinci.merkez.z };

      double toplamCap { birinci.yaricap + ikinci.yaricap };

      // uzunluk bulmak icin pisagor uygulariz
      double uzunluk { sqrt(pow(xEkseni, 2) + pow(yEkseni, 2) + pow(zEkseni, 2)) };

      // double uzunluk { hypot(xEkseni, yEkseni, zEkseni) };
      // bunu kulanabilirdik ama c++17 gerektigi icin sansima denemek istemiyorum

      bool carpisma { (uzunluk <= toplamCap) };

      return carpisma;
    }

    static bool silindirCarpisma(const Silindir birinci, const Silindir ikinci)
    {
      double birinciUst { birinci.merkez.z - birinci.yukseklik/2 };
      double birinciAlt { birinci.merkez.z + birinci.yukseklik/2 };

      double ikinciUst { ikinci.merkez.z - ikinci.yukseklik/2 };
      double ikinciAlt { ikinci.merkez.z + ikinci.yukseklik/2 };

      bool zCarpisma { (birinciAlt >= ikinciUst) && (ikinciAlt >= birinciUst) };

      N2B birinciCemberKordinat(birinci.merkez.x, birinci.merkez.y);
      N2B ikinciCemberKordinat (ikinci.merkez.x, ikinci.merkez.y);

      Cember birinciCember(birinciCemberKordinat, birinci.yaricap);
      Cember ikinciCember (ikinciCemberKordinat, ikinci.yaricap);

      bool xyCarpisma { cemberCarpisma(birinciCember, ikinciCember) };

      // burda ikisi ayni midir diye bakiyor ikisi true ise true ikisi false ise false
      bool carpisma { (zCarpisma && xyCarpisma) };
      
      return carpisma;
    }

};


//-------------------koordinatDonusturcu----------------------


// formuleri interneten buldum
class KoordinatDonustur
{
  public:
    struct K2BPolar { double yaricap, teta; };
    struct K3BSilindir { double yaricap, kutupsalAci, zKordinat; };

    static K2BPolar K2BToK2BPolar(const N2B kartezyen)
    {
      K2BPolar polar;

      polar.yaricap = hypot(kartezyen.x, kartezyen.y);
      polar.teta    = atan2(kartezyen.y, kartezyen.x);
      // atan2 = arctan

      return polar;
    }

    static N2B K2BPolarToK2B(const K2BPolar polar)
    {
      N2B kartezyen;

      kartezyen.x = polar.yaricap * cos(polar.teta);
      kartezyen.y = polar.yaricap * sin(polar.teta);

      return kartezyen;
    }

    static K3BSilindir K3BToK3BSilindir(const N3B kartezyen)
    {
      K3BSilindir silindir;

      silindir.yaricap     = hypot(kartezyen.x, kartezyen.y);
      silindir.kutupsalAci = atan2(kartezyen.y, kartezyen.x);
      silindir.zKordinat   = kartezyen.z;

      return silindir;
    }

    static N3B K3BSilindirToK3B(const K3BSilindir silindir)
    {
      N3B kartezyen;

      kartezyen.x = silindir.yaricap * cos(silindir.kutupsalAci);
      kartezyen.y = silindir.yaricap * sin(silindir.kutupsalAci);
      kartezyen.z = silindir.zKordinat;

      return kartezyen;
    }

};


//-------------------------main-------------------------------


int main()
{
  bool carpisma;


  cout << "--------------------Kordinat-Test---------------------------\n\n\n";


  N2B n2BTestNokta1(2, 3);
  N2B n2BTestNokta2(1, 5);
  cout << "Iki tane (" << n2BTestNokta1.x << ", " << n2BTestNokta1.y << "), ";
  cout << "(" << n2BTestNokta2.x << ", " << n2BTestNokta2.y << ") ";
  cout << "iki boyutlu nokta olusturuldu.\n";

  N2B n2BTestToplam { n2BTestNokta1 + n2BTestNokta2 };
  cout << "\nIki Noktanin toplami: (" << n2BTestToplam.x << ", " << n2BTestToplam.y << ")\n";

  N3B n3BTestNokta1(5, 1, 8);
  N3B n3BTestNokta2(2, 3, 5);
  cout << "\n\nIki tane (" << n3BTestNokta1.x << ", " << n3BTestNokta1.y << ", " << n3BTestNokta1.z << "), ";
  cout << "(" << n3BTestNokta2.x << ", " << n3BTestNokta2.y << ", " << n3BTestNokta2.z << ") ";
  cout << "uc boyutlu nokta olusturuldu.\n";

  N3B n3BTestToplam { n3BTestNokta1 + n3BTestNokta2 };
  cout << "\nIki Noktanin toplami: (" << n3BTestToplam.x << ", " << n3BTestToplam.y << ", " << n3BTestToplam.z << ")\n";


  cout << "\n\n------------------Kare-Carpisma-Test------------------------\n\n";


  cout << "\n--------------test-1--------------------\n\n";

  cout << "iki kare arasinda carpisma: \n\n";
  cout << "1.Kare: Merkezi (0, -2), Bir kenar uzunlugu 6 metre\n\n";
  cout << "2.Kare: Merkezi (2, 4) , Bir kenar uzunlugu 5 metre\n\n";

  N2B n2BKareTest1Nokta1(0, -2);
  N2B n2BKareTest1Nokta2(0, 4);

  Kare test1Kare1(n2BKareTest1Nokta1, 6);
  Kare test1Kare2(n2BKareTest1Nokta2, 5);

  carpisma = Carpisma::kareCarpisma(test1Kare1, test1Kare2);
  cout << "Carpisma: " << carpismaBoolToString(carpisma) << '\n';


  cout << "\n--------------test-2--------------------\n\n";

  cout << "iki kare arasinda carpisma: \n\n";
  cout << "1.Kare: Merkezi (1, 5), Bir kenar uzunlugu 4 metre\n\n";
  cout << "2.Kare: Merkezi (3, 6), Bir kenar uzunlugu 2 metre\n\n";

  N2B n2BKareTest2Nokta1(1, 5);
  N2B n2BKareTest2Nokta2(3, 6);

  Kare test2Kare1(n2BKareTest2Nokta1, 4);
  Kare test2Kare2(n2BKareTest2Nokta2, 2);

  carpisma = Carpisma::kareCarpisma(test2Kare1, test2Kare2);
  cout << "Carpisma: " << carpismaBoolToString(carpisma) << '\n';


  cout << "\n\n-----------------DikDortgen-Carpisma-Test-------------------\n\n";


  cout << "\n--------------test-1--------------------\n\n";

  cout << "iki Dikdortgen arasinda carpisma: \n\n";
  cout << "1.Dikdortgen: Merkezi (7, 10) , yukseklik 3 metre, uzunlugu 5 metre\n\n";
  cout << "2.Dikdortgen: Merkezi (12, 25), yukseklik 4 metre, uzunlugu 2 metre\n\n";

  N2B n2BDikdortgenTest1Nokta1(7, 10);
  N2B n2BDikdortgenTest1Nokta2(12, 25);
  
  Dikdortgen test1Dikdortgen1(n2BDikdortgenTest1Nokta1, 3, 5);
  Dikdortgen test1Dikdortgen2(n2BDikdortgenTest1Nokta2, 4, 2);

  carpisma = Carpisma::dikdortgenCarpisma(test1Dikdortgen1, test1Dikdortgen2);
  cout << "Carpisma: " << carpismaBoolToString(carpisma) << '\n';


  cout << "\n--------------test-2--------------------\n\n";

  cout << "iki Dikdortgen arasinda carpisma: \n\n";
  cout << "1.Dikdortgen: Merkezi (15, 20), yukseklik 17 metre, taban uzunlugu 9 metre\n\n";
  cout << "2.Dikdortgen: Merkezi (12, 25), yukseklik 13 metre, taban uzunlugu 4 metre\n\n";

  N2B n2BDikdortgenTest2Nokta1(15, 20);
  N2B n2BDikdortgenTest2Nokta2(12, 25);
  
  Dikdortgen test2Dikdortgen1(n2BDikdortgenTest1Nokta1, 17, 9);
  Dikdortgen test2Dikdortgen2(n2BDikdortgenTest1Nokta2, 13, 4);

  carpisma = Carpisma::dikdortgenCarpisma(test2Dikdortgen1, test2Dikdortgen2);
  cout << "Carpisma: " << carpismaBoolToString(carpisma) << '\n';


  cout << "\n\n-----------------Cember-Carpisma-Test-----------------------\n\n";


  cout << "\n--------------test-1--------------------\n\n";

  cout << "iki Cemberin arasinda carpisma: \n\n";
  cout << "1.Cember: Merkezi (5, 6)  , Yaricap 5 metre\n\n";
  cout << "2.Cember: Merkezi (12, 16), Yaricap 4 metre\n\n";

  N2B n2BCemberTest1Nokta1(5, 6);
  N2B n2BCemberTest1Nokta2(12, 16);

  Cember test1Cember1(n2BCemberTest1Nokta1, 5);
  Cember test1Cember2(n2BCemberTest1Nokta2, 4);

  carpisma = Carpisma::cemberCarpisma(test1Cember1, test1Cember2);
  cout << "Carpisma: " << carpismaBoolToString(carpisma) << '\n'; 


  cout << "\n--------------test-2--------------------\n\n";

  cout << "iki Cemberin arasinda carpisma: \n\n";
  cout << "1.Cember: Merkezi (15, 7) , Yaricap 9 metre\n\n";
  cout << "2.Cember: Merkezi (11, 13), Yaricap 6 metre\n\n";

  N2B n2BCemberTest2Nokta1(15, 7);
  N2B n2BCemberTest2Nokta2(11, 13);

  Cember test2Cember1(n2BCemberTest2Nokta1, 9);
  Cember test2Cember2(n2BCemberTest2Nokta2, 6);

  carpisma = Carpisma::cemberCarpisma(test2Cember1, test2Cember2);
  cout << "Carpisma: " << carpismaBoolToString(carpisma) << '\n';


  cout << "\n\n--------------Cember-Dikdortgen-Carpisma-Test---------------\n\n";


  cout << "\n--------------test-1--------------------\n\n";

  cout << "Cember ile Dikdortgen arasinda carpisma: \n\n";
  cout << "1.Dikdortgen: Merkezi (15, 7) , Yaricap 9 metre\n\n";
  cout << "2.Dikdortgen: Merkezi (12, 25), yukseklik 13 metre, taban uzunlugu 4 metre\n\n";

  N2B N2bCemberDikdortgenTest1Nokta1(15, 7);
  N2B N2bCemberDikdortgenTest1Nokta2(12, 25);

  Cember test1CemberDikdorgen1(N2bCemberDikdortgenTest1Nokta1, 9);
  Dikdortgen test1CemberDikdorgen2(N2bCemberDikdortgenTest1Nokta2, 13, 4);

  carpisma = Carpisma::dikdortgenCemberCarpisma(test1CemberDikdorgen2, test1CemberDikdorgen1);
  cout << "Carpisma: " << carpismaBoolToString(carpisma) << '\n';


  cout << "\n--------------test-2--------------------\n\n";

  cout << "Cember ile Dikdortgen arasinda carpisma: \n\n";
  cout << "1.Dikdortgen: Merkezi (7, 6) , Yaricap 9 metre\n\n";
  cout << "2.Dikdortgen: Merkezi (12, 4), yukseklik 13 metre, taban uzunlugu 4 metre\n\n";

  N2B N2bCemberDikdortgenTest2Nokta1(7, 6);
  N2B N2bCemberDikdortgenTest2Nokta2(12, 4);

  Cember test2CemberDikdorgen1(N2bCemberDikdortgenTest2Nokta1, 9);
  Dikdortgen test2CemberDikdorgen2(N2bCemberDikdortgenTest2Nokta2, 13, 4);

  carpisma = Carpisma::dikdortgenCemberCarpisma(test2CemberDikdorgen2, test2CemberDikdorgen1);
  cout << "Carpisma: " << carpismaBoolToString(carpisma) << '\n';

  cout << "\n\n------------------Kure-Carpisma-Test------------------------\n\n";


  cout << "\n--------------test-1--------------------\n\n";

  cout << "iki Kure arasinda carpisma: \n\n";
  cout << "1.Kure: Merkezi (11, 7, 4) , Yaricap 2 metre\n\n";
  cout << "2.Kure: Merkezi (2, 12, 18), Yaricap 4 metre\n\n";

  N3B n3BKureTest1Nokta1(11, 7, 4);
  N3B n3BKureTest1Nokta2(2, 12, 18);

  Kure test1Kure1(n3BKureTest1Nokta1, 1);
  Kure test1Kure2(n3BKureTest1Nokta2, 4);

  carpisma = Carpisma::kureCarpisma(test1Kure1, test1Kure2);
  cout << "Carpisma: " << carpismaBoolToString(carpisma) << '\n';


  cout << "\n--------------test-2--------------------\n\n";

  cout << "iki Kure arasinda carpisma: \n\n";
  cout << "1.Kure: Merkezi (10, 12, 5), Yaricap 10 metre\n\n";
  cout << "2.Kure: Merkezi (6, 14, 15), Yaricap 9 metre\n\n";

  N3B n3BKureTest2Nokta1(10, 12, 5);
  N3B n3BKureTest2Nokta2(6, 14, 15);

  Kure test2Kure1(n3BKureTest2Nokta1, 10);
  Kure test2Kure2(n3BKureTest2Nokta2, 9);

  carpisma = Carpisma::kureCarpisma(test2Kure1, test2Kure2);
  cout << "Carpisma: " << carpismaBoolToString(carpisma) << '\n';


  cout << "\n\n-----------------Silindir-Carpisma-Test---------------------\n\n";


  cout << "\n--------------test-1--------------------\n\n";

  cout << "iki Silindir arasinda carpisma: \n\n";
  cout << "1.Silindir: Merkezi (10, 12, 5), Yaricap 10 metre, Yukseklik 5 metre \n\n";
  cout << "2.Silindir: Merkezi (6, 14, 15), Yaricap 9 metre , Yukseklik 8 metre\n\n";

  N3B n3BSilindirTest1Nokta1(10, 12, 5);
  N3B n3BSilindirTest1Nokta2(6, 14, 15);

  Silindir test1Silindir1(n3BSilindirTest1Nokta1, 10, 5);
  Silindir test1Silindir2(n3BSilindirTest1Nokta2, 9, 8);

  carpisma = Carpisma::silindirCarpisma(test1Silindir1, test1Silindir2);
  cout << "Carpisma: " << carpismaBoolToString(carpisma) << '\n';


  cout << "\n--------------test-2--------------------\n\n";
  
  cout << "iki Silindir arasinda carpisma: \n\n";
  cout << "1.Silindir: Merkezi (5, 12, 12), Yaricap 10 metre, Yukseklik 5 metre \n\n";
  cout << "2.Silindir: Merkezi (6, 14, 15), Yaricap 9 metre , Yukseklik 8 metre\n\n";

  N3B n3BSilindirTest2Nokta1(5, 12, 12);
  N3B n3BSilindirTest2Nokta2(6, 14, 15);

  Silindir test2Silindir1(n3BSilindirTest2Nokta1, 10, 5);
  Silindir test2Silindir2(n3BSilindirTest2Nokta2, 9, 8);

  carpisma = Carpisma::silindirCarpisma(test2Silindir1, test2Silindir2);
  cout << "Carpisma: " << carpismaBoolToString(carpisma) << '\n';


  cout << "\n\n-------------------Carpisma-Test-Sonu-----------------------\n\n";

  return 0;
}



string carpismaBoolToString(bool carpisma)
{
  if(carpisma)
  return "Vardir";

  return "Yoktur";
}