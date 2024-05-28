#pragma once

class Render {
public:
	static void Rect(float x, float y, float w, float h, Color color, float rounding = 0.0f, float thickness = 1.0f);
	static void RectFilled(float x, float y, float w, float h, Color color, float rounding = 0.0f);

	static void Triangle(ImVec2 a, ImVec2 b, ImVec2 c, Color color, float thickness = 1.0f);
	static void TriangleFilled(ImVec2 a, ImVec2 b, ImVec2 c, Color color);

	static void Quad(ImVec2 a, ImVec2 b, ImVec2 c, ImVec2 d, Color color, float thickness = 1.0f);
	static void QuadFilled(ImVec2 a, ImVec2 b, ImVec2 c, ImVec2 d, Color color);

	static void Circle(float x, float y, float radius, Color color, float thickness = 1.0f, int segments = 12);
	static void CircleFilled(float x, float y, float radius, Color color, int segments = 12);

	static void Line(float x1, float y1, float x2, float y2, Color color, float thickness = 1.0f);
	// static void PolyLine(const std::vector<ImVec2>& points, Color color, bool closed, float thickness = 1.0f);
	static void Text(float x, float y, const char* text, Color color, bool center = false);
};

