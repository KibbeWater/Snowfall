//
// Created by kibbe on 1/21/2025.
//

#ifndef IMAGE_H
#define IMAGE_H

typedef int ImGuiImageFlags;

enum ImGuiImageFlags_ {
    ImGuiImageFlags_None        = 0,
    ImGuiImageFlags_AutoResizeX = 1 << 0,
    ImGuiImageFlags_AutoResizeY = 1 << 1
};

struct CachedImage {
    ImTextureID texture_id;
    ImVec2 size;
};

namespace Components {
    void FileImage(std::string path, ImVec2 size = ImVec2(-1, -1), float rounding = 0.0f, ImGuiImageFlags flags = ImGuiImageFlags_None);
}

#endif //IMAGE_H
