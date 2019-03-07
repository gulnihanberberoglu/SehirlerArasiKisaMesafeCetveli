#pragma once
#include "stdafx.h"
#include <stdlib.h>
#include "Yardimci.h"
#include "Sehir.h"
#include "Komsu.h"

/// <summary>
/// Dosyadan kom?uluk bilgilerini okuyup ram'e yükleyen fonksiyon
/// </summary>
/// <param name="sehirler">Ram'e yuklenmis olan sehirler dizisinin ilk eleman?</param>
/// <returns>Komsuluk dizisinin ilk eleman? (NULL : Dosya okunamad?)</returns>
Komsu* komsuluklariYukle(Sehir* sehirler) {
	//sehir mesafe.txt dosyas? saltokunur olarak aç?l?yor.
	FILE *dosya = fopen("sehir mesafe.txt", "r");
	if (dosya != NULL)
	{
		//Yardimci.h yard?m? ile dosyada kaç sat?r(?ehir) oldu?u okunuyor
		int satirSayisi = dosyaSatirSayisi(dosya) + 1;
		int elemanSayac = 0;
		char line[256];
		//Dosyan?n ba??na geliniyor
		rewind(dosya);
		//Toplam komsuluk adeti kadar Ram'de dizi için yer aç?l?yor.
		//Komsuluk 2 yonlu olmasi geretigi icin islemler 2 kere yapiliyor.
		//komsuluklar[elemanSayac]     --> Ankara'dan Eskisehir'e
		//komsuluklar[elemanSayac + i] --> Eskisehir'den Ankara 'ya
		Komsu* komsuluklar = (Komsu*)calloc((satirSayisi - 1) * 2, sizeof(Komsu));
		//Dosya sat?r sat?r okunuyor
		while (fgets(line, sizeof line, dosya) != NULL)
		{
			//Sat?rdaki bilgiler "-" karakterine göre ay?r?l?yor
			char* tokenPtr = strtok(charKopyala(line), "-");
			int sayac = 1;
			while (tokenPtr != NULL)
			{
				if (sayac == 1) {
					//?lk eleman kaynak sehir
					komsuluklar[elemanSayac].kaynak = isimdenSehirBul(sehirler, charKopyala(tokenPtr));
					//?Kinci eleman hedef sehir
					komsuluklar[elemanSayac + 1].hedef = isimdenSehirBul(sehirler, charKopyala(tokenPtr));
				}
				if (sayac == 2) {
					//?Kinci eleman hedef sehir
					komsuluklar[elemanSayac].hedef = isimdenSehirBul(sehirler, charKopyala(tokenPtr));
					//?lk eleman kaynak sehir
					komsuluklar[elemanSayac + 1].kaynak = isimdenSehirBul(sehirler, charKopyala(tokenPtr));
				}
				if (sayac == 3) {
					//?cüncü eleman ?ehirler arasi mesafe
					komsuluklar[elemanSayac].mesafe = strtod(tokenPtr, NULL);
					komsuluklar[elemanSayac + 1].mesafe = strtod(tokenPtr, NULL);
				}
				tokenPtr = strtok(NULL, "-");
				sayac++;
			}
			//Yüklenen ?ehirin dizideki indisi
			komsuluklar[elemanSayac].indis = elemanSayac;
			komsuluklar[elemanSayac + 1].indis = elemanSayac + 1;

			//Yüklenen dizide toplam kaç eleman var
			komsuluklar[elemanSayac].toplam = (satirSayisi * 2) - 1;
			komsuluklar[elemanSayac + 1].toplam = (satirSayisi * 2) - 1;
			elemanSayac += 2;
		}
		//Dosya kapat?l?yor
		fclose(dosya);
		//Dizinin ilk elaman? dönülüyor.
		return komsuluklar;
	}

	return NULL;
}

/// <summary>
/// Sadece bu dosyada kullan?lan ve gönderilen ?ehir ismine ait kom?u n. ci komsuyu bulan fonksiyon.
/// </summary>
/// <param name="komsuluklar">Ram'e yuklenmis olan komsular dizisinin ilk eleman?</param>
/// <param name="sehirIsmi">Kom?ular? aranacak olan ?ehir ismi</param>
/// <param name="n">The n.</param>
/// <returns></returns>
Komsu* komsuBul(Komsu* komsuluklar, const char* sehirIsmi, int n) {
	int sayac = 0;
	//Ram'e yuklenen komsular dizisinde toplam adet kadar donuluyor
	for (int i = 0; i < komsuluklar->toplam; i++)
	{
		//komsudaki kaynak sehir ismi ile parametreden gelen ayni mi?
		if (strcmp(komsuluklar[i].kaynak->isim, sehirIsmi) == 0) {
			// Ayni ise kacinci komsu isteniyor.
			if (sayac == n) {
				//Bulunan komsu donuluyor.
				return &komsuluklar[i];
			}
			sayac++;
		}
	}
	return NULL;
}

/// <summary>
/// Sadece bu dosyada kullan?lan ve gönderilen ?ehir ismine ait kom?u say?s?n? bulan fonksiyon
/// </summary>
/// <param name="komsuluklar">Ram'e yuklenmis olan komsular dizisinin ilk eleman?</param>
/// <param name="sehirIsmi">Kom?ular? aranacak olan ?ehir ismi</param>
/// <returns></returns>
int toplamKomsuAdeti(Komsu* komsuluklar, const char* sehirIsmi) {
	int sayac = 0;
	//Ram'e yuklenen komsular dizisinde toplam adet kadar donuluyor
	for (int i = 0; i < komsuluklar->toplam; i++)
	{
		//i.ci komsudaki kaynak sehir ismi ile parametreden gelen ayni ise sayaci bir art?r
		if (strcmp(komsuluklar[i].kaynak->isim, sehirIsmi) == 0) {
			sayac++;
		}
	}
	//Sayac bilgisi donuluyor.
	return sayac;
}

/// <summary>
/// Gönderilen ?ehir ismine ait kom?ular? bulan fonksiyon.
/// </summary>
/// <param name="komsuluklar">Ram'e yuklenmis olan komsular dizisinin ilk eleman?</param>
/// <returns>Sehrin komsular?n? içeren dizinin ilk eleman? (NULL : Kom?u bulunamad?)</returns>
Komsu* komsuluklariniBul(Komsu* komsuluklar, const char* sehirIsmi) {
	//Sehire ait komsu sayisi hesaplaniyor
	int toplamKomsu = toplamKomsuAdeti(komsuluklar, sehirIsmi);
	//Sahip olunan komsu adeti kadar ram'de dizi icin yer olusturuluyor
	Komsu* sonuc = (Komsu*)calloc(toplamKomsu, sizeof(Komsu));
	if (toplamKomsu != 0) {
		//Bulunan komsularin kopyasi olusturulup, yeni dizi'ye atamasi yapiliyor
		for (int i = 0; i < toplamKomsu; i++)
		{
			Komsu* komsu = komsuBul(komsuluklar, sehirIsmi, i);
			sonuc[i].hedef = komsu->hedef;
			sonuc[i].kaynak = komsu->kaynak;
			sonuc[i].mesafe = komsu->mesafe;
			//Yeni indis ve toplam komsuluk bilgisi isleniyor
			sonuc[i].indis = i;
			sonuc[i].toplam = toplamKomsu;
		}
		//Dizinin ilk elemani donuluyor.
		return sonuc;
	}
	return NULL;
}