#pragma once
#include "stdafx.h"

/// <summary>
/// sehir.txt dosyas?ndaki her sat?rdaki ?ehire kar??l?k gelicek olan veri t�r�.
/// </summary>
struct Sehir {
	char* isim;	// ?ehirin isim bilgisi
	int kod;	// ?ehirin kod bilgisi
	int	indis;  // Dizinin ka�?nc? elaman?
	int	toplam; // Dizide toplam ka� eleman var
};

/// <summary>
/// sehir.txt dosyas?n? okuyup Ram'e y�kleyen fonksiyon
/// </summary>
/// <returns>Ram'e y�klenen ?ehirler dizisinin ilk elaman?n? d�ner(NULL : dosya y�klenemedi)</returns>
Sehir* sehirleriYukle();

/// <summary>
/// Isimdens the sehir bul.
/// </summary>
/// <param name="sehirler">Ram'e y�klenmi? olan ?ehirler</param>
/// <param name="sehirIsmi">Aranacak olan ?ehirin ismi</param>
/// <returns>Bulunan ?ehir.(NULL : ?ehir bulunamad?)</returns>
Sehir* isimdenSehirBul(Sehir* sehirler, const char* sehirIsmi);