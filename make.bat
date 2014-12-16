cl GrayscaleFilter.c
cl GrayscaleFilterSIMD.c

for /f %%f in ('dir /b in\') do GrayscaleFilter in\%%f out\Serial\%%f
for /f %%f in ('dir /b in\') do GrayscaleFilterSIMD in\%%f out\SIMD\%%f
