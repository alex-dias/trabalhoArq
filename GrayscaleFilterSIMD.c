#define _CRT_SECURE_NO_WARNINGS

#include <time.h>
#include <stdio.h>
#include <stdlib.h>


int main(int argc, char * argv[]) {

	clock_t start, end;
	double cpu_time_used;

	FILE *infile, *outfile;
	char r, g, b, m, filetype[256], *ptri, *ptro, *img;
	int i;
	int width, height, depth, pixels, tam;

	char mult[8] = { 77, 151, 28, 77, 151, 28, 1, 1 };
	char divs[8] = { 0, 0, 0, 0, 0, 0, 1, 1 };
	char res[8] = { 1, 0, 0, 1, 0, 0, 0, 0 };


	char *mu = mult;
	char *d = divs;
	char *re = res;

	if (argc < 3) {
		printf("Usage: %s input output", argv[0]);
		exit(1);
	}

	infile = fopen(argv[1], "rb");
	if (!infile) {
		printf("File %s not found!", argv[1]);
		exit(1);
	}

	outfile = fopen(argv[2], "wb");
	if (!outfile) {
		printf("Unable to create file %s!", argv[2]);
		exit(1);
	}

	fscanf(infile, "%s\n", filetype);
	fprintf(outfile, "%s%c", filetype, 10);

	fscanf(infile, "%d %d %d\n", &width, &height, &depth);
	fprintf(outfile, "%d %d %d%c", width, height, depth, 10);

	pixels = width * height;

	tam = (pixels * 3) + (8 - ((pixels * 3) % 8));
	ptri = ptro = img = (char *)malloc(tam);

	fread(img, 3, pixels, infile);

	start = clock();

	for (i = 0; i < tam / 6; i++) {
		__asm {
			mov esi, ptri
			mov edi, ptro

			//se nao for a primeira execucao, nao eh necessario carregar novamente
			//os valores do vetor na memoria
			cmp i, 0
			jne continua

			//carrega na memoria do SIMD os valores de cada vetor
			mov eax, mu
			movlpd xmm6, [eax]
			mov eax, d
			movlpd xmm7, [eax]
			mov eax, re
			movlpd xmm4, [eax]

			//expande os valores
			punpcklbw xmm4, xmm5
			punpcklbw xmm6, xmm5
			punpcklbw xmm7, xmm5

			pcmpgtw xmm4, xmm5
			pcmpgtw xmm7, xmm5


			continua :
			movlpd xmm0, [esi]
			punpcklbw xmm0, xmm5

			movdqa xmm2, xmm7
			pand xmm2, xmm0

			pmullw xmm0, xmm6

			movdqa xmm1, xmm0
			psrldq xmm1, 2
			paddw xmm0, xmm1

			psrldq xmm1, 2
			paddw xmm0, xmm1

			movdqa xmm1, xmm0
			psrlw xmm1, 8

			pand xmm1, xmm4
			packuswb xmm1, xmm5

			movdqa xmm3, xmm1
			psllq xmm3, 8
			por xmm1, xmm3

			psllq xmm3, 8
			por xmm1, xmm3

			punpcklbw xmm1, xmm5

			movdqa xmm3, xmm7
			pcmpeqw xmm3, xmm5
			pand xmm3, xmm1

			pxor xmm2, xmm3

			packuswb xmm2, xmm5
			movlpd[edi], xmm2
		}
		ptri += 6;
		ptro += 6;
	}
	end = clock();

	fwrite(img, 3, pixels, outfile);

	fclose(infile);
	fclose(outfile);
	free(img);

	cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
	printf("time = %f seconds\n", cpu_time_used);
	return 0;
}