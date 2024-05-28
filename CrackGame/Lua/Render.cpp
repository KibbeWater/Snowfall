#include "pch.h"
#include "Render.h"

void Render::Rect(float x, float y, float w, float h, Color color, float rounding, float thickness) {
	if (!G::pDrawList) return;

	G::pDrawList->AddRect(ImVec2(x, y), ImVec2(x + w, y + h), color.GetImGUI(), rounding, 0, thickness);
}

void Render::RectFilled(float x, float y, float w, float h, Color color, float rounding) {
	if (!G::pDrawList) return;

	G::pDrawList->AddRectFilled(ImVec2(x, y), ImVec2(x + w, y + h), color.GetImGUI(), rounding);
}

void Render::Triangle(ImVec2 a, ImVec2 b, ImVec2 c, Color color, float thickness) {
	if (!G::pDrawList) return;

	G::pDrawList->AddTriangle(a, b, c, color.GetImGUI(), thickness);
}

void Render::TriangleFilled(ImVec2 a, ImVec2 b, ImVec2 c, Color color) {
	if (!G::pDrawList) return;

	G::pDrawList->AddTriangleFilled(a, b, c, color.GetImGUI());
}

void Render::Quad(ImVec2 a, ImVec2 b, ImVec2 c, ImVec2 d, Color color, float thickness) {
	if (!G::pDrawList) return;

	G::pDrawList->AddQuad(a, b, c, d, color.GetImGUI(), thickness);
}

void Render::QuadFilled(ImVec2 a, ImVec2 b, ImVec2 c, ImVec2 d, Color color) {
	if (!G::pDrawList) return;

	G::pDrawList->AddQuadFilled(a, b, c, d, color.GetImGUI());
}

void Render::Circle(float x, float y, float radius, Color color, float thickness, int segments) {
	if (!G::pDrawList) return;

	G::pDrawList->AddCircle(ImVec2(x, y), radius, color.GetImGUI(), segments, thickness);
}

void Render::CircleFilled(float x, float y, float radius, Color color, int segments) {
	if (!G::pDrawList) return;

	G::pDrawList->AddCircleFilled(ImVec2(x, y), radius, color.GetImGUI(), segments);
}

void Render::Line(float x1, float y1, float x2, float y2, Color color, float thickness) {
	if (!G::pDrawList) return;

	G::pDrawList->AddLine(ImVec2(x1, y1), ImVec2(x2, y2), color.GetImGUI(), thickness);
}

void Render::Text(float x, float y, const char* text, Color color, bool center) {
	if (!G::pDrawList) return;

	ImVec2 textSize = ImGui::CalcTextSize(text);
	if (center) x -= textSize.x / 2;

	G::pDrawList->AddText(ImVec2(x, y), color.GetImGUI(), text);
}
