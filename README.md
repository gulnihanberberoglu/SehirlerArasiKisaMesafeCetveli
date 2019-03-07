<p style="margin-bottom: 12.0pt; background: white;"><strong><span style="font-family: 'Segoe UI',sans-serif; color: #24292e;">ŞEHİRLER ARASI KISA MESAFE CETVELİ</span></strong></p>
<p style="background: white; box-sizing: border-box; font-variant-ligatures: normal; font-variant-caps: normal; orphans: 2; text-align: start; widows: 2; -webkit-text-stroke-width: 0px; text-decoration-style: initial; text-decoration-color: initial; word-spacing: 0px; margin: 0cm 0cm 12.0pt 0cm;"><strong style="box-sizing: border-box;"><span style="box-sizing: border-box;"><span style="font-family: 'Segoe UI',sans-serif; color: #24292e;">&Ouml;zet:</span></span></strong></p>
<p>sehir.txt dosyasında tanımlanan şehirlerin uygulamanın hafızasına y&uuml;klenmesi gerekmektedir. Sonrasında Şehirler arasındaki komşulukları ve mesafe bilgisini tanımlandığı sehir mesafe.txt dosyası uygulama hafızasına y&uuml;klenir. Dosyalardaki veriler uygulamaya y&uuml;klendikten sonra kullanıcıdan yolculuğa başlanacak şehir ve gidilecek şehir bilgisi alınır. Kullanıcıdan bilgi alındıktan sonra kaynak şehirden yapılması muhtemel yolculukların listesi ekrana basılır ve sonrasında Dijkstra algoritması ile kaynak şehirden hedef şehire gidilirken kullanılacak en kısa mesafe bulunur.</p>
<p style="background: white; margin: 0cm 0cm 12.0pt 0cm;"><strong><span style="font-family: 'Segoe UI',sans-serif; color: #24292e;">Genel Yapı:</span></strong></p>
<p style="box-sizing: border-box; font-variant-ligatures: normal; font-variant-caps: normal; orphans: 2; text-align: start; widows: 2; -webkit-text-stroke-width: 0px; text-decoration-style: initial; text-decoration-color: initial; word-spacing: 0px;"><span style="box-sizing: border-box;">Problemin &ccedil;&ouml;z&uuml;m&uuml; C programlama dili aracılığı ile geliştirilmiştir. Program ilk &ccedil;alışmaya başladığında verileri ilgili dosyalardan hafızasına y&uuml;kler. Bu işlem sırasında sehir.txt dosyası Sehir.h dosyasındaki struct aracılığı ile hafızaya alınır. sehir mesafe.txt dosyası ise Komsu.h dosyasındaki struct aracılığı ile hafızaya alınır. </span></p>
<p>Bu işlemlerden sonra kullanıcıya men&uuml; g&ouml;sterilir ve giriş yapması istenir.</p>
<p>Eğer kullanıcı y&uuml;klenmemiş bir şehir girerse hata mesajı g&ouml;sterilir ve yeniden giriş yapması istenir.</p>
<p>Kullanıcı girişleri doğru ise;</p>
<ul>
<li style="margin-left: 53.4pt; text-indent: -18.0pt;">Kaynak şehirden yapılması muhtemel b&uuml;t&uuml;n yolculuklar hesaplanır.</li>
<li style="margin-left: 53.4pt; text-indent: -18.0pt;">Dijkstra algoritması ile kaynak şehir ile hedef şehir arasındaki en kısa mesafe bulunur.</li>
</ul>
<p>Ve sonu&ccedil;lar ekrana yazılır.</p>
<p>Eğer şehirler arasında yolculuk bulunamaz ise hata mesajı verilir.</p>
