#pragma once
#include "stdafx.h"
#include <stdlib.h>
#include "Yardimci.h"
#include "Sehir.h"

/// <summary>
/// sehir.txt dosyas?n? okuyup Ram'e yükleyen fonksiyon
/// </summary>
/// <returns>Ram'e yüklenen ?ehirler dizisinin ilk elaman?n? döner(NULL : dosya yüklenemedi)</returns>
Sehir* sehirleriYukle() {
	//sehir kod.txt dosyas? saltokunur olarak aç?l?yor.
	FILE *dosya = fopen("sehir kod.txt", "r");
	if (dosya != NULL)
	{
		//Yardimci.h yard?m? ile dosyada kaç sat?r(?ehir) oldu?u okunuyor
		int satirSayisi = dosyaSatirSayisi(dosya) + 1;
		int elemanSayac = 0;
		char line[256];
		//Dosyan?n ba??na geliniyor
		rewind(dosya);
		//Toplam ?ehir adeti kadar Ram'de dizi için yer aç?l?yor.
		Sehir* sehirler = (Sehir*)calloc((satirSayisi - 1), sizeof(Sehir));
		//Dosya sat?r sat?r okunuyor
		while (fgets(line, sizeof line, dosya) != NULL)
		{
			//Sat?rdaki bilgiler "-" karakterine göre ay?r?l?yor
			char* tokenPtr = strtok(charKopyala(line), "-");
			int sayac = 1;
			while (tokenPtr != NULL)
			{
				if (sayac == 1) {
					//?lk eleman ?ehir ismidir
					sehirler[elemanSayac].isim = charKopyala(tokenPtr);
				}
				if (sayac == 2) {
					//?kinci eleman ?ehir kodudur
					sehirler[elemanSayac].kod = strtod(tokenPtr, NULL);
				}
				tokenPtr = strtok(NULL, "-");
				sayac++;
			}
			//Yüklenen ?ehirin dizideki indisi
			sehirler[elemanSayac].indis = elemanSayac;
			//Yüklenen dizide toplam kaç eleman var
			sehirler[elemanSayac].toplam = satirSayisi;
			elemanSayac++;
		}
		//Dosya kapat?l?yor
		fclose(dosya);
		//Dizinin ilk elaman? dönülüyor.
		return sehirler;
	}

	return NULL;
}

/// <summary>
/// Isimdens the sehir bul.
/// </summary>
/// <param name="sehirler">Ram'e yüklenmi? olan ?ehirler</param>
/// <param name="sehirIsmi">Aranacak olan ?ehirin ismi</param>
/// <returns>Bulunan ?ehir.(NULL : ?ehir bulunamad?)</returns>
Sehir* isimdenSehirBul(Sehir* sehirler, const char* sehirIsmi) {
	//?ehirler dizisinde for ile geziliyor
	for (int i = 0; i < sehirler->toplam; i++)
	{
		if (strcmp(sehirler[i].isim, sehirIsmi)== 0) {
			//?ehirler dizisinin i.ci elaman? aranan isimle e?le?iyor ise dönülüyor.
			return sehirler + i;
		}
	}
	//Aranan ?ehir bulunamad?.
	return NULL;
}