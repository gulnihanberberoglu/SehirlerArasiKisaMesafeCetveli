#pragma once
#include "stdafx.h"
#include <stdlib.h>
#include <string.h>
#include "Yolculuk.h"

/// <summary>
/// Kaynak sehirde birden fazla komsuluk var ise mevcut adima kadar olan yolculugu kopyalar
/// </summary>
/// <param name="kaynak">Yapilan yolculuk</param>
/// <param name="kadar">Hangi sehire kadar kopyalanacak</param>
/// <returns></returns>
Yolculuk* yolculukKopyala(const Yolculuk* kaynak, Sehir* kadar) {
	//Yolculuk kopyalaniyor.
	Yolculuk* yolculuk = (Yolculuk*)malloc(sizeof(Yolculuk));
	yolculuk->baslangicSehri = kaynak->baslangicSehri;
	yolculuk->bitisSehri = NULL;
	yolculuk->toplamMesafe = 0;

	//Ad?mlar kopyalan?yor
	yolculuk->ilkAdim = (Adim*)malloc(sizeof(Adim));
	yolculuk->ilkAdim->onceki = NULL;
	yolculuk->ilkAdim->sehir = kaynak->ilkAdim->sehir;
	yolculuk->ilkAdim->sonraki = NULL;
	for (Adim* adim = kaynak->ilkAdim->sonraki; adim->sehir != kadar; adim = adim->sonraki) {
		Adim* kopyaAdim;
		for (kopyaAdim = yolculuk->ilkAdim; kopyaAdim->sonraki != NULL; kopyaAdim = kopyaAdim->sonraki);
		kopyaAdim->sonraki = (Adim*)malloc(sizeof(Adim));
		kopyaAdim->sonraki->sehir = adim->sehir;
		kopyaAdim->sonraki->onceki = kopyaAdim;
		kopyaAdim->sonraki->sonraki = NULL;
	}

	//Kopya yolculuk donuluyor.
	return yolculuk;
}

/// <summary>
/// Sehire onceden gidilmis mi?
/// </summary>
/// <param name="adim">En son atilan adim</param>
/// <param name="sehir">Gidilecek olan sehir</param>
/// <returns>Sehire onceden; true: gidilmis false: gidilmemis</returns>
bool oncedenGidilmisMi(Adim* adim, Sehir* sehir) {
	if (adim == NULL) {
		return false;
	}
	//Son adimdan geriye dogru gidilir ce onceki adimlarda hedefteki sehire gidilmis mi kontrolu yapar.
	for (Adim* i = adim; i != NULL; i = i->onceki) {
		if (sehir != NULL && strcmp(i->sehir->isim, sehir->isim) == 0) {
			return true;
		}
	}
	return false;
}

/// <summary>
/// Ilk yolculugu ve muhtemel diger yolculuklari hesaplayan fonksiyon
/// </summary>
/// <param name="komsuluklar">Ram'e yuklenmis olan komsular dizisinin ilk eleman?</param>
/// <param name="yolculuk">Mevut yolculuk</param>
void yolculukariBul(Komsu* komsuluklar, Yolculuk* yolculuk) {
	Adim* simdikiAdim;
	//Yolculukta atilan en son adimi hesaplayan for.
	for (simdikiAdim = yolculuk->ilkAdim; simdikiAdim->sonraki != NULL; simdikiAdim = simdikiAdim->sonraki);

	//En son adimda varilan sehirdeki komsuluklar bulunuyor.
	Komsu* komsularim = komsuluklariniBul(komsuluklar, simdikiAdim->sehir->isim);
	bool ilkYolculukAtamasiYapildiMi = false;
	Sehir* ilkKomsu = NULL;
	double toplamMesafe;

	//Bulunanan komsuluklarda geziliyor
	for (int j = 0; j < komsularim->toplam; j++)
	{
		//Eger ilk gidilecek komsu ise
		if (!oncedenGidilmisMi(simdikiAdim, komsularim[j].hedef)) {
			if (!ilkYolculukAtamasiYapildiMi) {
				//Sonraki adim olusturuluyor.
				ilkKomsu = komsularim[j].hedef;
				simdikiAdim->sonraki = (Adim*)malloc(sizeof(Adim));
				simdikiAdim->sonraki->sehir = komsularim[j].hedef;
				simdikiAdim->sonraki->onceki = simdikiAdim;
				simdikiAdim->sonraki->sonraki = NULL;
				yolculuk->toplamMesafe += komsularim[j].mesafe;
				//Bu adimda harcanan mesafe toplama ekleniyor
				toplamMesafe = yolculuk->toplamMesafe;
				//Bu adimdan sonra gidilecek sehir var ise bir sonraki adim hesaplanmasi icin
				//yada adimdan sonra gidilecek yer yok ise yolculugu tamamlamasi icin
				yolculukariBul(komsuluklar, yolculuk);
				ilkYolculukAtamasiYapildiMi = true;
			}
			//Eger ilk gidilecek komsu degil ise
			else {
				//Bir sonraki komsu icin mevcut yolculuk kopyalanip, bu komsu icin yeni adim olusturuluyor
				Yolculuk* yeni = yolculukKopyala(yolculuk, ilkKomsu);
				yeni->toplamMesafe = toplamMesafe;
				for (simdikiAdim = yeni->ilkAdim; simdikiAdim->sonraki != NULL; simdikiAdim = simdikiAdim->sonraki);
				simdikiAdim->sonraki = (Adim*)malloc(sizeof(Adim));
				simdikiAdim->sonraki->sehir = komsularim[j].hedef;
				simdikiAdim->sonraki->onceki = simdikiAdim;
				simdikiAdim->sonraki->sonraki = NULL;
				yeni->toplamMesafe += komsularim[j].mesafe;
				yeni->sonraki = NULL;

				//Bu adimdan sonra gidilecek sehir var ise bir sonraki adim hesaplanmasi icin
				//yada adimdan sonra gidilecek yer yok ise yolculugu tamamlamasi icin
				yolculukariBul(komsuluklar, yeni);

				//Yeni yolculuk; mevcut yolculugun sonraki elemanina ekleniyor.
				Yolculuk* gecici;
				for (gecici = yolculuk; gecici->sonraki != NULL; gecici = gecici->sonraki);
				gecici->sonraki = yeni;
				gecici->sonraki->sonraki = NULL;
			}
		}
	}
	//Ilk komsuluk aramasi yapildi ve sonuc yok ise yolculuk sonuna gelinmistir
	//Bitis seihiri ataniyor, sonraki adim NULL olarak atanir.
	if (!ilkYolculukAtamasiYapildiMi) {
		yolculuk->bitisSehri = simdikiAdim->sehir;
		simdikiAdim->sonraki = NULL;
		yolculuk->sonraki = NULL;
	}
}

/// <summary>
/// Kaynak sehirden yapilmasi muhtemel yolculuklari hesaplayan fonksiyondur.
/// </summary>
/// <param name="komsuluklar">Ram'e yuklenmis olan komsular dizisinin ilk eleman?</param>
/// <param name="baslangicSehri">Yolculuga baslanilacak olan sehir</param>
/// <returns>Muhtemel yolculuklar dizisinin ilk elemani</returns>
Yolculuk* tumYolculuklariBul(Komsu* komsuluklar, Sehir*  baslangicSehri) {
	//?lk yolculuk icin ram'de yer ayriliyor.
	Yolculuk* yolculuk = (Yolculuk*)malloc(sizeof(Yolculuk));
	//Baslangic sehri ve toplam mesafe degerleri ataniyor
	yolculuk->baslangicSehri = baslangicSehri;
	yolculuk->toplamMesafe = 0;

	//Ilk adim ataniyor ve ram'de yeri aciliyor
	yolculuk->ilkAdim = (Adim*)malloc(sizeof(Adim));
	yolculuk->ilkAdim->onceki = NULL;
	//Baslangic sehri ataniyor
	yolculuk->ilkAdim->sehir = baslangicSehri;
	yolculuk->ilkAdim->sonraki = NULL;

	//?lk yolculuk ve adimlari hesaplanmasi icin fonksyiyon cagriliyor.
	//Bu fonksiyon ayrica diger yolculularida bagli listeye ekler.
	yolculukariBul(komsuluklar, yolculuk);
	return yolculuk;
}