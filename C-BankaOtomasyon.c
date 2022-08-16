#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <conio.h>

//                  <<BANKAMATIK OTOMASYONU>>
typedef struct Hesaplar{
    char Adi[40];
    char Soyadi[40];
    int hesapNo;
    int bakiye;

    struct Borclar{
        int krediKarti;
        int elektrikFaturasi;
        int suFaturasi;
        int gazFaturasi;
    }borclar;
}kayitliHesap;


kayitliHesap *hesaplarBasi;

int hesapNo = 1;
int hesapAdedi=0;

void menuBas(){
    printf("\n************* MENU *************");
    printf("\n ( 1 ) | Hesap Ekle");
    printf("\n ( 2 ) | Hesap Bilgileri Guncelle");
    printf("\n ( 3 ) | Hesaplari Listele");
    printf("\n ( 4 ) | Hesap Sil");
    printf("\n ( 5 ) | Para Yatirma / Cekme");
    printf("\n ( 6 ) | Harcama Ekle");
    printf("\n ( 7 ) | Fatura Ode");
    printf("\n ( 8 ) | Mali Durumum Ozeti");
    printf("\n ( 0 ) | Cikis");
    printf("\n********************************");
}

void ekleme(char Adi[40], char Soyadi[40], int yatirilanPara){
    if(hesapAdedi == 0) {
        hesaplarBasi = (kayitliHesap *) malloc(sizeof(kayitliHesap));
    }
    else
    {
        hesaplarBasi=(kayitliHesap*)realloc(hesaplarBasi,sizeof(kayitliHesap)*(hesapAdedi+1));

    }

    strcpy((hesaplarBasi+hesapAdedi)->Adi,Adi);
    strcpy((hesaplarBasi+hesapAdedi)->Soyadi,Soyadi);
    (hesaplarBasi+hesapAdedi)->bakiye = yatirilanPara;
    (hesaplarBasi+hesapAdedi)->hesapNo = hesapNo;
    (hesaplarBasi+hesapAdedi)->borclar.krediKarti =0;
    (hesaplarBasi+hesapAdedi)->borclar.gazFaturasi =0;
    (hesaplarBasi+hesapAdedi)->borclar.elektrikFaturasi =0;
    (hesaplarBasi+hesapAdedi)->borclar.suFaturasi =0;

    printf("\n>%s",(hesaplarBasi+hesapAdedi)->Adi);
    printf("\n>%s",(hesaplarBasi+hesapAdedi)->Soyadi);
    printf("\n>%d",(hesaplarBasi+hesapAdedi)->bakiye);
    printf("\n>%d",(hesaplarBasi+hesapAdedi)->borclar.elektrikFaturasi);

    hesapNo++;
    hesapAdedi++;
}

void silme(int hesapNumarasi)
{
    if(hesapNumarasi > 0 || hesapNumarasi < hesapAdedi)
    {
        for(int i=hesapNumarasi;i<hesapAdedi;i++)
        {
            *(hesaplarBasi+(i-1))=*(hesaplarBasi+i);
        }
        hesapAdedi--;
        hesaplarBasi=(kayitliHesap *)realloc(hesaplarBasi,sizeof(kayitliHesap)*hesapAdedi);    }
    else
    {
        printf("\nGirdiginiz hesap numarasinde bir hata var...");
    }
}

void listeleme(){
    printf("\n--- Tum Hesaplarin Listesi ---");
    printf("\nHesapNo\t\tAdi\t\tSoyadi\t\tBakiye");
    for(int i=0; i<hesapAdedi;i++){
        printf("\n%d\t\t%s\t\t%s\t\t%d",(hesaplarBasi+i)->hesapNo,(hesaplarBasi+i)->Adi,(hesaplarBasi+i)->Soyadi, (hesaplarBasi+i)->bakiye);
    }
    printf("\nAnamenu icin lutfen bir tusa basiniz...");
    getch();
}

void guncelleme(int hesapNumarasi) {

    if (hesapNumarasi != 0) {
        for (int i = 0; i < hesapAdedi; i++) {
            if ((hesaplarBasi + i)->hesapNo == hesapNumarasi) {
                printf("\n%d numarali hesabin yeni adini giriniz:> ", (hesaplarBasi + i)->hesapNo);
                scanf("%s", &(hesaplarBasi + i)->Adi);
                printf("\n%d numarali hesabin yeni soyadini giriniz:> ", (hesaplarBasi + i)->hesapNo);
                scanf("%s", &(hesaplarBasi + i)->Soyadi);
                printf("\n%d numarali hesabin yeni bakiyesini giriniz:> ", (hesaplarBasi + i)->hesapNo);
                scanf("%d", &(hesaplarBasi + i)->bakiye);
                printf("\nHesabiniz guncellenmistir...");
                break;
            }
            printf("\nGirmis oldunuz numara kayitlarimizda gorulmemistir...");
        }
    }
}

int hesapNumarasiBul (char gelenAd[20]){

    for (int i = 0; i < hesapAdedi; i++) {
        if ((hesaplarBasi + i)->Adi == gelenAd) {
            return (hesaplarBasi + i)->hesapNo;
        }

    }
    return 0;
}

void paraYatirCek(int hesapNumarasi,int yatirilanPara, int yatirVeyaCek){
    if (hesapNumarasi != 0) {
        for (int i = 0; i < hesapAdedi; i++) {
            if ((hesaplarBasi + i)->hesapNo == hesapNumarasi) {
                if(yatirVeyaCek == 1){
                    (hesaplarBasi + i)->bakiye = (hesaplarBasi + i)->bakiye + yatirilanPara;
                    break;
                }
                if(yatirVeyaCek == 0){
                    (hesaplarBasi + i)->bakiye = (hesaplarBasi + i)->bakiye - yatirilanPara;
                    break;
                }
            }
            printf("\nGirmis oldunuz numara kayitlarimizda gorulmemistir...");
        }
    }
}

void borcListele(int hesapNumarasi){
    for (int i = 0; i < hesapAdedi; i++) {
        if ((hesaplarBasi + i)->hesapNo == hesapNumarasi) {
            printf("\nKredi karti borcunuz: %d TL",(hesaplarBasi + i)->borclar.krediKarti);
            printf("\nElektrik faturasi borcunuz: %d TL",(hesaplarBasi + i)->borclar.elektrikFaturasi);
            printf("\nSu faturasi borcunuz: %d TL",(hesaplarBasi + i)->borclar.suFaturasi);
            printf("\nGaz faturasi borcunuz: %d TL",(hesaplarBasi + i)->borclar.gazFaturasi);
            printf("\nDevam etmek icin bir tusa basiniz...");
            getch();
        }
    }
}

void harcamaEkle(int hesapNumarasi, int miktar, int tip){

    if (hesapNumarasi != 0) {
        for (int i = 0; i < hesapAdedi; i++) {
            if ((hesaplarBasi + i)->hesapNo == hesapNumarasi) {

                if(tip == 1){
                    (hesaplarBasi + i)->borclar.krediKarti = (hesaplarBasi + i)->borclar.krediKarti + miktar;
                    borcListele(hesapNumarasi);
                    break;
                }
                else if(tip == 2){
                    (hesaplarBasi + i)->borclar.elektrikFaturasi = (hesaplarBasi + i)->borclar.elektrikFaturasi + miktar;
                    borcListele(hesapNumarasi);
                    break;
                }
                else if(tip == 3){
                    (hesaplarBasi + i)->borclar.suFaturasi = (hesaplarBasi + i)->borclar.suFaturasi + miktar;
                    borcListele(hesapNumarasi);
                    break;
                }
                else if(tip == 4){
                    (hesaplarBasi + i)->borclar.gazFaturasi = (hesaplarBasi + i)->borclar.gazFaturasi + miktar;
                    borcListele(hesapNumarasi);
                    break;
                }
                else
                {
                    printf("\nHarcama ekraninda hatali birsey oldu...");
                }
            }
            printf("\nGirmis oldunuz numara kayitlarimizda gorulmemistir...");
        }
    }

}

void borcOde(int hesapNumarasi, int tip){

    if (hesapNumarasi != 0) {
        for (int i = 0; i < hesapAdedi; i++) {
            if ((hesaplarBasi + i)->hesapNo == hesapNumarasi) {

                if(tip == 1){
                    (hesaplarBasi + i)->bakiye = (hesaplarBasi + i)->bakiye - (hesaplarBasi + i)->borclar.krediKarti;
                    (hesaplarBasi + i)->borclar.krediKarti = 0;
                    borcListele(hesapNumarasi);
                    break;
                }
                else if(tip == 2){
                    (hesaplarBasi + i)->bakiye = (hesaplarBasi + i)->bakiye - (hesaplarBasi + i)->borclar.elektrikFaturasi;
                    (hesaplarBasi + i)->borclar.elektrikFaturasi = 0;
                    borcListele(hesapNumarasi);
                    break;
                }
                else if(tip == 3){
                    (hesaplarBasi + i)->bakiye = (hesaplarBasi + i)->bakiye - (hesaplarBasi + i)->borclar.suFaturasi;
                    (hesaplarBasi + i)->borclar.suFaturasi = 0;
                    borcListele(hesapNumarasi);
                    break;
                }
                else if(tip == 4){
                    (hesaplarBasi + i)->bakiye = (hesaplarBasi + i)->bakiye - (hesaplarBasi + i)->borclar.gazFaturasi;
                    (hesaplarBasi + i)->borclar.gazFaturasi = 0;
                    borcListele(hesapNumarasi);
                    break;
                }
                else
                {
                    printf("\nOdeme ekraninda hatali birsey oldu...");
                }
            }
            printf("\nGirmis oldunuz numara kayitlarimizda gorulmemistir...");
        }
    }

}


void Ozet(int hesapNumarasi){
    for (int i = 0; i < hesapAdedi; i++) {
        if ((hesaplarBasi + i)->hesapNo == hesapNumarasi) {
            printf("\nHesapNo\t\tAdi\t\tSoyadi\t\tBakiye");
            printf("\n%d\t\t%s\t\t%s\t\t%d",(hesaplarBasi+i)->hesapNo,(hesaplarBasi+i)->Adi,(hesaplarBasi+i)->Soyadi, (hesaplarBasi+i)->bakiye);

            printf("\n\nKredi karti borcunuz: %d TL",(hesaplarBasi + i)->borclar.krediKarti);
            printf("\nElektrik faturasi borcunuz: %d TL",(hesaplarBasi + i)->borclar.elektrikFaturasi);
            printf("\nSu faturasi borcunuz: %d TL",(hesaplarBasi + i)->borclar.suFaturasi);
            printf("\nGaz faturasi borcunuz: %d TL",(hesaplarBasi + i)->borclar.gazFaturasi);

            int toplamBorc = (hesaplarBasi + i)->borclar.krediKarti+(hesaplarBasi + i)->borclar.elektrikFaturasi+(hesaplarBasi + i)->borclar.suFaturasi+(hesaplarBasi + i)->borclar.gazFaturasi;

            printf("\n\nTum borcunuzun toplami:%d",toplamBorc);
            printf("\nTum borcunuzu oderseniz hesabinizda kalacak para: %d",(hesaplarBasi+i)->bakiye-toplamBorc);

            printf("\nDevam etmek icin bir tusa basiniz...");
            getch();
        }
    }
}

int main() {



    int secilen;
    int bekleme;




    while(1){

        menuBas();
        printf("\nYapmak istediginiz islemi giriniz:> ");
        scanf("%d",&secilen);

        if(secilen == 1){

            char ad[20];
            char soyad[20];
            int yatirilanPara;
            printf("\n--- Yeni Musteri Hesabi Acilisi ---");
            printf("\nLutfen adinizi giriniz:> ");
            scanf("%s",&ad);
            printf("\nLutfen soyadinizi giriniz:> ");
            scanf("%s",&soyad);
            printf("\nLutfen hesabiniza yatiracaginiz tutari giriniz:> ");
            scanf("%d",&yatirilanPara);

            ekleme(ad,soyad,yatirilanPara);

            printf("\nHesabiniz acilmistir.");
            printf("\nAnamenuye donmek icin lutfen herhangi bir karaktere basiniz...");
            getch();
        }
        else if(secilen == 2){


            if(hesapAdedi == 0){
                printf("\nHenuz kayitli herhangi bir hesap olmadigi icin bu islemi yapamazsiniz...");
                printf("\nAnamenuye donmek icin lutfen herhangi bir karaktere basiniz...");
                getch();
                continue;
            }

            int girilen;
            printf("\n---Hesap Bilgilerini Guncelleme ---");
            printf("\nGuncellenecek hesabin numarasi icin (1) veya adi icin (2) giriniz:>");
            scanf("%d",&girilen);
            if(girilen == 1){
                int girilenNumara;
                printf("\nKullanicinin numarasini girerek guncelleme islemini sectiniz.");
                printf("\nLutfen kullanicinin hesap numarasini (hesapNo) giriniz:> ");
                scanf("%d",&girilenNumara);
                guncelleme(girilenNumara);
            }
            else if(girilen == 2){
                char girilenAd[20];
                printf("\nKullanicinin adini girerek guncelleme islemini sectiniz.");
                printf("\nLutfen kullanicinin sadece adini giriniz:> ");
                scanf("%s",&girilenAd);
                int numara=hesapNumarasiBul(girilenAd);
                guncelleme(numara);
            }
            else
            {
                printf("\nHatali bir giris yaptiniz...");
                printf("\nAnamenuye donmek icin lutfen herhangi bir karaktere basiniz...");
                getch();
                continue;
            }

            printf("\nAnamenuye donmek icin lutfen herhangi bir karaktere basiniz...");
            getch();
        }
        else if(secilen == 3){
            listeleme();
        }
        else if(secilen == 4){
            int hesap;
            printf("\n---Hesap Silme ---");
            printf("\nSilinecek hesap numarasini giriniz:> ");
            scanf("%d",&hesap);
            silme(hesap);
            printf("\n%d numarali hesabiniz silindi...",hesap);
            printf("\nAnamenuye donmek icin lutfen herhangi bir karaktere basiniz...");
            getch();
        }
        else if(secilen == 5){
            int girilen;
            int hesap;
            printf("\n---Para Yatirma / Cekme �slemi ---");
            printf("\nIslem yapilacak hesap numarasini giriniz:> ");
            scanf("%d",&hesap);
            printf("\nPara yatirma icin (1) para cekme icin (2) giriniz:> ");
            scanf("%d",&girilen);
            if(girilen == 1){
                int yatirilanPara;
                printf("\nYatirmak istediginiz tutari giriniz:>");
                scanf("%d",&yatirilanPara);
                paraYatirCek(hesap,yatirilanPara,1);
                printf("\n%d tutarindaki paraniz hesabiniza yatirilmistir...",yatirilanPara);
                printf("\nMenuye donmek icin lutfen bir tusa basiniz...");
                getch();
            }
            else if (girilen == 2){
                int cekilenPara;
                printf("\nCekmek istediginiz tutari giriniz:>");
                scanf("%d",&cekilenPara);
                paraYatirCek(hesap,cekilenPara,0);
                printf("\n%d tutarindaki paraniz cekilmistir...",cekilenPara);
                printf("\nMenuye donmek icin lutfen bir tusa basiniz...");
                getch();
            }
            else
            {
                printf("\nHatali bir secim yaptiniz...");
                printf("\nMenuye donmek icin lutfen bir tusa basiniz...");
                getch();
            }
        }
        else if(secilen == 6){
            int girilen;
            int hesap;
            printf("\n---Harcama Ekleme Ekrani ---");
            printf("\nEklenebilecek Harcamalar:");
            printf("\n[ 1 ] Kredi Kart� Harcamasi");
            printf("\n[ 2 ] Elektrik Faturasi");
            printf("\n[ 3 ] Su Faturasi");
            printf("\n[ 4 ] Gaz Faturasi");
            printf("\nLutfen harcamalardan birini seciniz:> ");
            scanf("%d",&girilen);
            printf("\nLutfen islem yapan hesap numarasini seciniz:> ");
            scanf("%d",&hesap);
            if(girilen == 1){
                int miktar;
                printf("\nKredi kartindan yapilacak harcama miktarini giriniz:>");
                scanf("%d",&miktar);

                harcamaEkle(hesap,miktar,girilen);
            }
            else if(girilen == 2){

                int miktar;
                printf("\nElektrik faturasi tutarini giriniz:>");
                scanf("%d",&miktar);

                harcamaEkle(hesap,miktar,girilen);

            }
            else if(girilen == 3){
                int miktar;
                printf("\nSu faturasi tutarini giriniz:>");
                scanf("%d",&miktar);

                harcamaEkle(hesap,miktar,girilen);
            }
            else if(girilen == 4){
                int miktar;
                printf("\nGaz faturasi tutarini giriniz:>");
                scanf("%d",&miktar);

                harcamaEkle(hesap,miktar,girilen);
            }
            else
            {
                printf("\nHatali bir secim yaptiniz...");
                printf("\nMenuye donmek icin lutfen bir tusa basiniz...");
                getch();
            }
        }
        else if(secilen == 7){
            int girilen;
            int hesap;
            printf("\n---Odeme Ekrani ---");
            printf("\nOdemeler:");
            printf("\n[ 1 ] Kredi Kart� Borcu Ode");
            printf("\n[ 2 ] Elektrik Faturasi Borcu Ode");
            printf("\n[ 3 ] Su Faturasi Borcu Ode");
            printf("\n[ 4 ] Gaz Faturasi Borcu Ode");
            printf("\nLutfen bir odeme turu seciniz:> ");
            scanf("%d",&girilen);
            printf("\nLutfen islem yapan hesap numarasini seciniz:> ");
            scanf("%d",&hesap);
            if(girilen == 1){

                borcOde(hesap,girilen);
                printf("\nKredi karti borcunuz hesabinizdan odenmistir.");
                printf("\nMenuye donmek icin lutfen bir tusa basiniz...");
                getch();
            }
            else if(girilen == 2){

                borcOde(hesap,girilen);
                printf("\nElektrik faturasi borcunuz hesabinizdan odenmistir.");
                printf("\nMenuye donmek icin lutfen bir tusa basiniz...");
                getch();

            }
            else if(girilen == 3){
                borcOde(hesap,girilen);
                printf("\nSu faturasi borcunuz hesabinizdan odenmistir.");
                printf("\nMenuye donmek icin lutfen bir tusa basiniz...");
                getch();
            }
            else if(girilen == 4){
                borcOde(hesap,girilen);
                printf("\nDogalgaz borcunuz hesabinizdan odenmistir.");
                printf("\nMenuye donmek icin lutfen bir tusa basiniz...");
                getch();
            }
            else
            {
                printf("\nHatali bir secim yaptiniz...");
                printf("\nMenuye donmek icin lutfen bir tusa basiniz...");
                getch();
            }
        }
        else if(secilen == 8){
            int girilen;
            printf("\n--- Hesap Ozeti ---");
            printf("\nHesap ozetini istediginiz hesap numarasini giriniz:> ");
            scanf("%d",&girilen);
            Ozet(girilen);
            printf("\nMenuye donmek icin lutfen bir tusa basiniz...");
            getch();

        }
        else if(secilen == 0){
            printf("\nProgramdan cikiyorsunuz...");
            break;
        }
        else{

            printf("\nHatali bir islem yaptiniz.");
            printf("\nMenuye donmek icin lutfen bir tusa basiniz...");
            getch();

        }
    }

    return 0;
}
