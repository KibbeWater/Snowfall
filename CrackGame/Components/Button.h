//
// Created by kibbe on 1/22/2025.
//

#ifndef BUTTON_H
#define BUTTON_H

enum ImGuiCustomButtonFlags_ {
    ImGuiCustomButtonFlags_None = 0,
    ImGuiCustomButtonFlags_AutoResizeX = 1 << 0,
    ImGuiCustomButtonFlags_AutoResizeY = 1 << 1
};

namespace Components {
    bool Button(const char *label, ImVec2 size = ImVec2(0, 40), int flags =
                        ImGuiCustomButtonFlags_AutoResizeX | ImGuiCustomButtonFlags_AutoResizeY);
}

#endif //BUTTON_H
