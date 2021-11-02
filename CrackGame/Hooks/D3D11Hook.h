#pragma once

#ifndef D3D11_HOOK_H_INCLUDED_
#define D3D11_HOOK_H_INCLUDED_

#define D3D11_HOOK_API

struct ID3D11Device; // from d3d11.h
struct ID3D11DeviceContext; // from d3d11.h
struct IDXGISwapChain; // from d3d11.h

					   // Use for rendering graphical user interfaces (for example: ImGui) or other.
extern D3D11_HOOK_API void ImplHookDX11_Present(ID3D11Device* device, ID3D11DeviceContext* ctx, IDXGISwapChain* swap_chain);

// Use for initialize hook.
D3D11_HOOK_API void	       ImplHookDX11_Init(HMODULE hModule, void* hwnd);

// Use for untialize hook (ONLY AFTER INITIALIZE).
D3D11_HOOK_API void	       ImplHookDX11_Shutdown();

#endif