#pragma once
#include "stdafx.h"

/// <summary>
/// sehir.txt dosyas?ndaki her sat?rdaki ?ehire kar??l?k gelicek olan veri türü.
/// </summary>
struct Sehir {
	char* isim;	// ?ehirin isim bilgisi
	int kod;	// ?ehirin kod bilgisi
	int	indis;  // Dizinin kaç?nc? elaman?
	int	toplam; // Dizide toplam kaç eleman var
};

/// <summary>
/// sehir.txt dosyas?n? okuyup Ram'e yükleyen fonksiyon
/// </summary>
/// <returns>Ram'e yüklenen ?ehirler dizisinin ilk elaman?n? döner(NULL : dosya yüklenemedi)</returns>
Sehir* sehirleriYukle();

/// <summary>
/// Isimdens the sehir bul.
/// </summary>
/// <param name="sehirler">Ram'e yüklenmi? olan ?ehirler</param>
/// <param name="sehirIsmi">Aranacak olan ?ehirin ismi</param>
/// <returns>Bulunan ?ehir.(NULL : ?ehir bulunamad?)</returns>
Sehir* isimdenSehirBul(Sehir* sehirler, const char* sehirIsmi);