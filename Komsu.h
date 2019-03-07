#pragma once
#include "stdafx.h"
#include "Sehir.h"

/// <summary>
/// ?ehirlerin birbiriyle olan kom?uluklar?n? modalleyen veri türü
/// </summary>
struct Komsu {
	Sehir*  kaynak;	// Kom?ulu?a sahip olan ?ehir
	Sehir*  hedef;	// Kom?u olan ?ehir
	double  mesafe;	// Kom?u ?ehirler aras?ndaki mesafe
	int		indis;	// Dizinin kaç?nc? elaman?
	int		toplam;	// Dizide toplam kaç eleman var
};

/// <summary>
/// Dosyadan kom?uluk bilgilerini okuyup ram'e yükleyen fonksiyon
/// </summary>
/// <param name="sehirler">Ram'e yuklenmis olan sehirler dizisinin ilk eleman?</param>
/// <returns>Komsuluk dizisinin ilk eleman? (NULL : Dosya okunamad?)</returns>
Komsu* komsuluklariYukle(Sehir* sehirler);

/// <summary>
/// Gönderilen ?ehir ismine ait kom?ular? bulan fonksiyon.
/// </summary>
/// <param name="sehirler">Ram'e yuklenmis olan komsular dizisinin ilk eleman?</param>
/// <param name="sehirler">Ram'e yuklenmis olan sehirler dizisinin ilk eleman?</param>
/// <returns>Sehrin komsular?n? içeren dizinin ilk eleman? (NULL : Kom?u bulunamad?)</returns>
Komsu* komsuluklariniBul(Komsu* komsuluklar, const char* sehirIsmi);