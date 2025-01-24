//
// Created by kibbe on 1/21/2025.
//

#include "pch.h"

bool LoadTextureFromMemory(const void* data, size_t data_size, ID3D11ShaderResourceView** out_srv, int* out_width, int* out_height)
{
    // Load from disk into a raw RGBA buffer
    int image_width = 0;
    int image_height = 0;
    unsigned char* image_data = stbi_load_from_memory((const unsigned char*)data, (int)data_size, &image_width, &image_height, NULL, 4);
    if (image_data == NULL)
        return false;

    // Create texture
    D3D11_TEXTURE2D_DESC desc;
    ZeroMemory(&desc, sizeof(desc));
    desc.Width = image_width;
    desc.Height = image_height;
    desc.MipLevels = 1;
    desc.ArraySize = 1;
    desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    desc.SampleDesc.Count = 1;
    desc.Usage = D3D11_USAGE_DEFAULT;
    desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
    desc.CPUAccessFlags = 0;

    ID3D11Texture2D* pTexture = NULL;
    D3D11_SUBRESOURCE_DATA subResource;
    subResource.pSysMem = image_data;
    subResource.SysMemPitch = desc.Width * 4;
    subResource.SysMemSlicePitch = 0;
    G::g_pd3dDevice->CreateTexture2D(&desc, &subResource, &pTexture);

    // Create texture view
    D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
    ZeroMemory(&srvDesc, sizeof(srvDesc));
    srvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
    srvDesc.Texture2D.MipLevels = desc.MipLevels;
    srvDesc.Texture2D.MostDetailedMip = 0;
    G::g_pd3dDevice->CreateShaderResourceView(pTexture, &srvDesc, out_srv);
    pTexture->Release();

    *out_width = image_width;
    *out_height = image_height;
    stbi_image_free(image_data);

    return true;
}

// Open and read a file, then forward to LoadTextureFromMemory()
bool LoadTextureFromFile(const char* file_name, ID3D11ShaderResourceView** out_srv, int* out_width, int* out_height)
{
    FILE* f = nullptr;
    errno_t err = fopen_s(&f, file_name, "rb"); // Use fopen_s instead of fopen
    if (err != 0 || f == nullptr)
        return false;

    fseek(f, 0, SEEK_END);
    size_t file_size = (size_t)ftell(f);
    if (file_size == -1)
    {
        fclose(f); // Close the file before returning
        return false;
    }

    fseek(f, 0, SEEK_SET);
    void* file_data = IM_ALLOC(file_size);
    if (file_data == nullptr)
    {
        fclose(f); // Close the file before returning
        return false;
    }

    fread(file_data, 1, file_size, f);
    fclose(f); // Close the file as soon as you're done reading

    bool ret = LoadTextureFromMemory(file_data, file_size, out_srv, out_width, out_height);
    IM_FREE(file_data);
    return ret;
}

void Components::FileImage(std::string path, ImVec2 size, float rounding, ImGuiImageFlags flags) {
    int img_width = 0;
    int img_height = 0;
    ImTextureID texture = 0;

    static std::map<std::string, CachedImage*> s_loadedImages{};
    if (!s_loadedImages.contains(path)) {
        ID3D11ShaderResourceView* _txt = 0;

        bool ret = LoadTextureFromFile(path.c_str(), &_txt, &img_width, &img_height);
        IM_ASSERT(ret);

        texture = (intptr_t)_txt;

        // Probably leaks lmao but idgaf
        s_loadedImages.emplace(path, new CachedImage{
            texture,
            ImVec2(img_width, img_height)
            });
    } else {
        auto cached = s_loadedImages.at(path);

        img_width = cached->size.x;
        img_height = cached->size.y;
        texture = cached->texture_id;
    }

    assert((flags & ImGuiImageFlags_AutoResizeX) != (flags & ImGuiImageFlags_AutoResizeY));

    ImVec2 _size = (size.x == -1 && size.y == -1) ? ImGui::GetContentRegionAvail() : size;
    if (flags & ImGuiImageFlags_AutoResizeX) {
        float scaling = _size.x / img_width;
        _size.y = img_height * scaling; // Maintain aspect ratio
    } else if (flags & ImGuiImageFlags_AutoResizeY) {
        float scaling = _size.y / img_height;
        _size.x = img_width * scaling; // Maintain aspect ratio
    }

    ImVec2 p_min = ImGui::GetCursorScreenPos();
    ImVec2 p_max = ImVec2(p_min.x + _size.x, p_min.y + _size.y);
    ImGui::GetWindowDrawList()->AddImageRounded(texture, p_min, p_max, ImVec2(0, 0), ImVec2(1, 1), IM_COL32(255, 255, 255, 255), rounding);
    ImGui::Dummy(_size);
}
