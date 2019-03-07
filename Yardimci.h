#pragma once
#include "stdafx.h"
#include <stdlib.h>
#include <string.h>

//http://stackoverflow.com/questions/3501338/c-read-file-line-by-line
/// <summary>
/// Dosyada kac adet satir oldugunu hesaplayan fonksiyon
/// </summary>
/// <param name="dosya">Acilan dosya</param>
/// <returns>Satir sayisi</returns>
int dosyaSatirSayisi(FILE* dosya);

//http://stackoverflow.com/questions/481673/make-a-copy-of-a-char
/// <summary>
/// karakter dizisinin kopyasini olusturan fonksiyon.
/// </summary>
/// <param name="kaynak">kaynak karakter dizisi</param>
/// <returns>kopya karakter dizisi</returns>
char* charKopyala(const char* kaynak);