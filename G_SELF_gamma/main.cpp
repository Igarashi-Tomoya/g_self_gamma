#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <math.h>

typedef struct{
	BITMAPFILEHEADER fileheader;
	BITMAPINFOHEADER infoheader;
}BmpHeader;

typedef struct{
	unsigned char b;
	unsigned char g;
	unsigned char r;
}Rgb;


int main()
{
	FILE *fp_i, *fp_o;
	BmpHeader header = { 0 };
	

	if ((fp_i = fopen("input.bmp", "rb")) == NULL){
		MessageBox(NULL, "input file open is failed.", "error!", MB_OK);
		exit(EXIT_FAILURE);
	}
	if ((fp_o = fopen("output.bmp", "wb")) == NULL){
		MessageBox(NULL, "output file open is failed.", "error!", MB_OK);
		exit(EXIT_FAILURE);
	}

	//ファイルヘッダ読み込み
	fread(&header.fileheader.bfType, sizeof(WORD), 1, fp_i);
	fread(&header.fileheader.bfSize, sizeof(DWORD), 1, fp_i);
	fread(&header.fileheader.bfReserved1, sizeof(WORD), 1, fp_i);
	fread(&header.fileheader.bfReserved2, sizeof(WORD), 1, fp_i);
	fread(&header.fileheader.bfOffBits, sizeof(DWORD), 1, fp_i);

	//情報ヘッダ読み込み
	fread(&header.infoheader.biSize, sizeof(DWORD), 1, fp_i);
	fread(&header.infoheader.biWidth, sizeof(LONG), 1, fp_i);
	fread(&header.infoheader.biHeight, sizeof(LONG), 1, fp_i);
	fread(&header.infoheader.biPlanes, sizeof(WORD), 1, fp_i);
	fread(&header.infoheader.biBitCount, sizeof(WORD), 1, fp_i);
	fread(&header.infoheader.biCompression, sizeof(DWORD), 1, fp_i);
	fread(&header.infoheader.biSizeImage, sizeof(DWORD), 1, fp_i);
	fread(&header.infoheader.biXPelsPerMeter, sizeof(LONG), 1, fp_i);
	fread(&header.infoheader.biYPelsPerMeter, sizeof(LONG), 1, fp_i);
	fread(&header.infoheader.biClrUsed, sizeof(DWORD), 1, fp_i);
	fread(&header.infoheader.biClrImportant, sizeof(DWORD), 1, fp_i);

	//ファイルヘッダ書き込み
	fwrite(&header.fileheader.bfType, sizeof(WORD), 1, fp_o);
	fwrite(&header.fileheader.bfSize, sizeof(DWORD), 1, fp_o);
	fwrite(&header.fileheader.bfReserved1, sizeof(WORD), 1, fp_o);
	fwrite(&header.fileheader.bfReserved2, sizeof(WORD), 1, fp_o);
	fwrite(&header.fileheader.bfOffBits, sizeof(DWORD), 1, fp_o);

	//情報ヘッダ書き込み
	fwrite(&header.infoheader.biSize, sizeof(DWORD), 1, fp_o);
	fwrite(&header.infoheader.biWidth, sizeof(LONG), 1, fp_o);
	fwrite(&header.infoheader.biHeight, sizeof(LONG), 1, fp_o);
	fwrite(&header.infoheader.biPlanes, sizeof(WORD), 1, fp_o);
	fwrite(&header.infoheader.biBitCount, sizeof(WORD), 1, fp_o);
	fwrite(&header.infoheader.biCompression, sizeof(DWORD), 1, fp_o);
	fwrite(&header.infoheader.biSizeImage, sizeof(DWORD), 1, fp_o);
	fwrite(&header.infoheader.biXPelsPerMeter, sizeof(LONG), 1, fp_o);
	fwrite(&header.infoheader.biYPelsPerMeter, sizeof(LONG), 1, fp_o);
	fwrite(&header.infoheader.biClrUsed, sizeof(DWORD), 1, fp_o);
	fwrite(&header.infoheader.biClrImportant, sizeof(DWORD), 1, fp_o);

	double max = 255.0;
	double gamma = 2.5;

	for (int i = 0; i < header.infoheader.biWidth; i++){
		for (int j = 0; j < header.infoheader.biHeight; j++){
				Rgb color_i = { 0, 0, 0 };
				Rgb color_o = { 0, 0, 0 };
				fread(&color_i.b, sizeof(BYTE), 1, fp_i);
				fread(&color_i.g, sizeof(BYTE), 1, fp_i);
				fread(&color_i.r, sizeof(BYTE), 1, fp_i);
				color_o.b = max * pow(color_i.b / max, 1 / gamma);
				color_o.g = max * pow(color_i.g / max, 1 / gamma);
				color_o.r = max * pow(color_i.r / max, 1 / gamma);
				fwrite(&color_o.b, sizeof(BYTE), 1, fp_o);
				fwrite(&color_o.g, sizeof(BYTE), 1, fp_o);
				fwrite(&color_o.r, sizeof(BYTE), 1, fp_o);
		}
		if (header.infoheader.biHeight * 3 % 4 != 0){
			int padding = header.infoheader.biHeight * 3 % 4;
			int padding_f;
			fread(&padding_f, sizeof(BYTE), padding, fp_i);
			fwrite(&padding_f, sizeof(BYTE), padding, fp_o);
		}
	}

	fclose(fp_i);
	fclose(fp_o);

}