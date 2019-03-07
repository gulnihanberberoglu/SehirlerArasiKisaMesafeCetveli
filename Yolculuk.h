#pragma once
#include "stdafx.h"
#include <stdlib.h>
#include "Sehir.h"
#include "Komsu.h"

/// <summary>
/// Yolculuk esnasindaki yapilan adimlarin bilgisini iceren struct(Çift bagli list - DoubleLinkedList)
/// </summary>
struct Adim
{
	Adim*   onceki;		// Bir onceki adim
	Sehir*  sehir;		// Adimin geldigi sehir 
	Adim*   sonraki;	// Sonra gidilecek olan adim
};

/// <summary>
/// Kaynak sehirden yapilacak yolculuk bilgisini iceren struct
/// </summary>
struct Yolculuk {
	Sehir* baslangicSehri;	// Yolculugun basladigi sehir
	Sehir* bitisSehri;		// Yolculugun tamamlandigi sehir
	Adim*  ilkAdim;			// Yolculukta yapilan ilk adim
	double toplamMesafe;	// Yolculukta alinan toplam mesafe
	Yolculuk* sonraki;		// Kaynak sehirden yapilacak sonraki yolculuk
};

/// <summary>
/// Kaynak sehirden yapilmasi muhtemel yolculuklari hesaplayan fonksiyondur.
/// </summary>
/// <param name="komsuluklar">Ram'e yuklenmis olan komsular dizisinin ilk eleman?</param>
/// <param name="baslangicSehri">Yolculuga baslanilacak olan sehir</param>
/// <returns>Muhtemel yolculuklar dizisinin ilk elemani</returns>
Yolculuk* tumYolculuklariBul(Komsu* komsuluklar, Sehir*  baslangicSehri);
