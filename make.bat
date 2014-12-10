cl GrayscaleFilter.c

for /f %%f in ('dir /b in\') do GrayscaleFilter in\%%f  out\%%f
