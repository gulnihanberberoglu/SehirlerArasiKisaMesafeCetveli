// SehirlerArasiMesafeCetveli.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdlib.h>
#include "Sehir.h"
#include "Komsu.h"
#include "Yolculuk.h"
#include "Yardimci.h"

/// <summary>
/// Kaynak ?ehirden yap?lacak muhtemel yolculuklar? ekrana yazd?r?r.
/// </summary>
/// <param name="komsular">Ram'e yüklenen komsuluklar</param>
/// <param name="kaynakSehir">Yolculu?a ba?lanacak ?ehir</param>
void tumYolculuklariniYazdir(Komsu* komsular, Sehir* kaynakSehir) {
	Yolculuk* yolculuk = tumYolculuklariBul(komsular, kaynakSehir);
	for (Yolculuk* i = yolculuk; i != NULL; i = i->sonraki) {
		for (Adim* j = i->ilkAdim; j != NULL; j = j->sonraki) {
			printf("%s->", j->sehir->isim);
		}
		printf("(Toplam : %lf)\n", i->toplamMesafe);
	}
}

/// <summary>
/// Ens the kisa yolculugu hesapla.
/// </summary>
/// <param name="komsular">Ram'e yüklenen komsuluklar</param>
/// <param name="kaynakSehir">Yolculu?a ba?lanacak ?ehir</param>
/// <param name="kaynakSehir">Yolculukta gidilecek ?ehir</param>
void enKisaYolculuguHesapla(Komsu* komsular, Sehir* kaynakSehir, Sehir* hedefSehir) {
	Yolculuk* yolculuk = tumYolculuklariBul(komsular, kaynakSehir);
	Yolculuk* enKisaYolculuk = NULL;
	for (Yolculuk* i = yolculuk; i != NULL; i = i->sonraki) {
		if (i->bitisSehri == hedefSehir && (enKisaYolculuk == NULL || enKisaYolculuk->toplamMesafe > i->toplamMesafe)) {
			enKisaYolculuk = i;
		}
	}

	//Ekran ç?kt?s? yazd?rma
	if (enKisaYolculuk != NULL) {
		printf("%s sehirinden %s sehirine en kisa rota : \n", kaynakSehir->isim, hedefSehir->isim);
		for (Adim* j = yolculuk->ilkAdim; j != NULL; j = j->sonraki) {
			printf("%s->", j->sehir->isim);
		}
		printf("(Toplam : %lf)\n", yolculuk->toplamMesafe);
	}
	else {
		printf("%s sehirinden %s sehirine rota bulunamadi\n", kaynakSehir->isim, hedefSehir->isim);
	}
}

/// <summary>
/// Program?n giri? fonksiyonu.
/// </summary>
/// <returns>Program sonucu (0: ba?ar?l?)</returns>
int main()
{
	printf("Sehirler dosyasindaki veriler yukleniyor.....\n");
	Sehir* sehirler = sehirleriYukle();
	printf("Komsular dosyasindaki veriler yukleniyor.....\n");
	Komsu* komsular = komsuluklariYukle(sehirler);
	printf("Veriler basariyla yuklendi\n");

	bool menuGoster = true;

	Sehir *kaynakSehir = NULL, *hedefSehir = NULL;
	while (menuGoster) {
		char kaynakSehirIsmi[1024];
		printf("Kaynak sehiri giriniz : \n");
		scanf("%s", &kaynakSehirIsmi);
		kaynakSehir = isimdenSehirBul(sehirler, kaynakSehirIsmi);

		char hedefSehirIsmi[1024];;
		printf("Hedef sehiri giriniz : \n");
		scanf("%s", &hedefSehirIsmi);
		hedefSehir = isimdenSehirBul(sehirler, hedefSehirIsmi);

		if (kaynakSehir == NULL || hedefSehir == NULL) {
			printf("Kaynak yada hedef sehir sistemde bulunamadi, yeniden giris yapiniz\n");
		}
		else {
			menuGoster = false;
		}
	}

	tumYolculuklariniYazdir(komsular, kaynakSehir);
	enKisaYolculuguHesapla(komsular, kaynakSehir, hedefSehir);
	system("PAUSE");
	return 0;
}

