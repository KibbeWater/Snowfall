#include "pch.h"
#include "Color.h"

Color::Color(int r, int g, int b, int a) {
	this->r = r;
	this->g = g;
	this->b = b;
	this->a = a;
}

Color Color::FromHSV(float h, float s, float v, int a) {
	float c = v * s;
	float x = c * (1 - abs(fmod(h / 60.0, 2) - 1));
	float m = v - c;

	float r, g, b;

	if (h >= 0 && h < 60) {
		r = c;
		g = x;
		b = 0;
	}
	else if (h >= 60 && h < 120) {
		r = x;
		g = c;
		b = 0;
	}
	else if (h >= 120 && h < 180) {
		r = 0;
		g = c;
		b = x;
	}
	else if (h >= 180 && h < 240) {
		r = 0;
		g = x;
		b = c;
	}
	else if (h >= 240 && h < 300) {
		r = x;
		g = 0;
		b = c;
	}
	else {
		r = c;
		g = 0;
		b = x;
	}

	return Color((r + m) * 255, (g + m) * 255, (b + m) * 255, a);
}

Color Color::White() {
	return Color(255, 255, 255, 255);
}

Color Color::Black() {
	return Color(0, 0, 0, 255);
}

ImColor Color::GetImGUI() {
	return ImColor(r, g, b, a);
}
