#pragma once

class Color {
public:
	int r, g, b, a;

	Color(int r, int g, int b, int a);
	static Color FromHSV(float h, float s, float v, int a);
	static Color White();
	static Color Black();

	ImColor GetImGUI();
};
