/* 2018 ReVoL Primer Template */
/* curves.cpp */
#include "curves.h"

// размер графики
#define GX (double)50
#define GY (double)15

// шаг по X
#define DX 0.001

// размер устройства вывода
int WX = 0, WY = 0;
// масштаб осей
double SX = 0, SY = 0;
// центр системы координат
int CX = 0, CY = 0;

// параметры вывода
void setview() {
	
	RECT rc;
	// получаем размер
	GetClientRect(hWndGDE, &rc);

	WX = rc.right - rc.left;
	WY = rc.bottom - rc.top;

	// вычисляем центр системы координат
	CX = 0;
	CY = WY / 2;

	//вычисляем масштаб/ Единицы графика на пиксель
	SX = GX / WX;
	SY = GY / WY;

}

// разворачивает ось Y
void pixel(HDC hdc, int X, int Y) {
	// рисует пиксель
	SetPixel(hdc, X, CY - Y, RGB(255, 0, 0));
}

// разворачивает ось Y
void moveTo(HDC hdc, int X, int Y) {
	// устанавливает текущую точку
	MoveToEx(hdc, X, CY - Y, 0);
}

// разворачивает ось Y
void lineTo(HDC hdc, int X, int Y) {
	// рисуем линию
	LineTo(hdc, X, CY - Y);
}

// функция графика
double func(double x) {
	return sin(x);
}

// рисование точками
void byPoints(HDC GDC) {
	for (double x = 0; x <= WX; x++) {
		double y = func(x);
		pixel(GDC, x / SX, y / SY);
	}
}

// рисование линиями
void byLines(HDC hdc) {

	// вычисляем начальную точку графика
	double x = 0;
	double y = func(x);
	// выставляем новую точку графика, как текущую
	moveTo(hdc, x, y);

	// вычиялем следующие точки
	for (x = DX; x <= WX; x = x + DX) {
		y = func(x);
		// рисуем линию 
		lineTo(hdc, x / SX, y / SY);
	}
}

/* контекст устройства GDC */
void draw() {

	// параметры вывода
	setview();

	// устанавливаем текущую точку
	MoveToEx(GDC, 0, CY, 0);
	// линия от текущей точки
	LineTo(GDC, WX, CY);

	// устанавливаем текущую точку
	MoveToEx(GDC, CX, 0, 0);
	// линия от текущей точки
	LineTo(GDC, CX, WY);

	//рисуем график линиями
	byLines(GDC);
	// рисуем график точками
	byPoints(GDC);
	
}
