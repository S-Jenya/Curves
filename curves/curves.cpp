/* 2018 ReVoL Primer Template */
/* curves.cpp */
#include "curves.h"

// ������ �������
#define GX (double)50
#define GY (double)15

// ��� �� X
#define DX 0.001

// ������ ���������� ������
int WX = 0, WY = 0;
// ������� ����
double SX = 0, SY = 0;
// ����� ������� ���������
int CX = 0, CY = 0;

// ��������� ������
void setview() {
	
	RECT rc;
	// �������� ������
	GetClientRect(hWndGDE, &rc);

	WX = rc.right - rc.left;
	WY = rc.bottom - rc.top;

	// ��������� ����� ������� ���������
	CX = 0;
	CY = WY / 2;

	//��������� �������/ ������� ������� �� �������
	SX = GX / WX;
	SY = GY / WY;

}

// ������������� ��� Y
void pixel(HDC hdc, int X, int Y) {
	// ������ �������
	SetPixel(hdc, X, CY - Y, RGB(255, 0, 0));
}

// ������������� ��� Y
void moveTo(HDC hdc, int X, int Y) {
	// ������������� ������� �����
	MoveToEx(hdc, X, CY - Y, 0);
}

// ������������� ��� Y
void lineTo(HDC hdc, int X, int Y) {
	// ������ �����
	LineTo(hdc, X, CY - Y);
}

// ������� �������
double func(double x) {
	return sin(x);
}

// ��������� �������
void byPoints(HDC GDC) {
	for (double x = 0; x <= WX; x++) {
		double y = func(x);
		pixel(GDC, x / SX, y / SY);
	}
}

// ��������� �������
void byLines(HDC hdc) {

	// ��������� ��������� ����� �������
	double x = 0;
	double y = func(x);
	// ���������� ����� ����� �������, ��� �������
	moveTo(hdc, x, y);

	// �������� ��������� �����
	for (x = DX; x <= WX; x = x + DX) {
		y = func(x);
		// ������ ����� 
		lineTo(hdc, x / SX, y / SY);
	}
}

/* �������� ���������� GDC */
void draw() {

	// ��������� ������
	setview();

	// ������������� ������� �����
	MoveToEx(GDC, 0, CY, 0);
	// ����� �� ������� �����
	LineTo(GDC, WX, CY);

	// ������������� ������� �����
	MoveToEx(GDC, CX, 0, 0);
	// ����� �� ������� �����
	LineTo(GDC, CX, WY);

	//������ ������ �������
	byLines(GDC);
	// ������ ������ �������
	byPoints(GDC);
	
}
