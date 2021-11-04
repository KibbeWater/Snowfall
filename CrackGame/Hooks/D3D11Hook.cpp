#include "pch.h"

#include <d3d11.h>
#include <mutex>

#pragma comment(lib, "d3d11.lib")


// KeyBoard Options.
const int OpenMenuKey = VK_INSERT;
const int UninjectLibraryKey = VK_DELETE;

typedef HRESULT(__stdcall* D3D11PresentHook) (IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);
typedef void(__stdcall* D3D11DrawIndexedHook) (ID3D11DeviceContext* pContext, UINT IndexCount, UINT StartIndexLocation, INT BaseVertexLocation);
typedef void(__stdcall* D3D11CreateQueryHook) (ID3D11Device* pDevice, const D3D11_QUERY_DESC* pQueryDesc, ID3D11Query** ppQuery);
typedef void(__stdcall* D3D11PSSetShaderResourcesHook) (ID3D11DeviceContext* pContext, UINT StartSlot, UINT NumViews, ID3D11ShaderResourceView* const* ppShaderResourceViews);
typedef void(__stdcall* D3D11ClearRenderTargetViewHook) (ID3D11DeviceContext* pContext, ID3D11RenderTargetView* pRenderTargetView, const FLOAT ColorRGBA[4]);

static HWND                     g_hWnd = nullptr;
static HMODULE					g_hModule = nullptr;
static ID3D11Device* g_pd3dDevice = nullptr;
static ID3D11DeviceContext* g_pd3dContext = nullptr;
static IDXGISwapChain* g_pSwapChain = nullptr;
static std::once_flag           g_isInitialized;

D3D11PresentHook                phookD3D11Present = nullptr;
D3D11DrawIndexedHook            phookD3D11DrawIndexed = nullptr;
D3D11CreateQueryHook			phookD3D11CreateQuery = nullptr;
D3D11PSSetShaderResourcesHook	phookD3D11PSSetShaderResources = nullptr;
D3D11ClearRenderTargetViewHook  phookD3D11ClearRenderTargetViewHook = nullptr;

DWORD** pSwapChainVTable = nullptr;
DWORD** pDeviceVTable = nullptr;
DWORD** pDeviceContextVTable = nullptr;

InputHook inputHook = InputHook();

template <typename T = void*>
__forceinline T GetVirtual(void* thisptr, int iIndex)
{
	return (*static_cast<T**>(thisptr))[iIndex];
}


D3D11_HOOK_API void ImplHookDX11_Present(ID3D11Device* device, ID3D11DeviceContext* ctx, IDXGISwapChain* swap_chain)
{
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();

	//if (FontSys::BuildFonts())
	//{
	//	ImGui_ImplDX9_InvalidateDeviceObjects();
	//	ImGui_ImplDX9_CreateDeviceObjects();
	//	SkipRenderTicks = 2;
	//}

	ImGui::NewFrame();







	{
		if (GetAsyncKeyState(OpenMenuKey) & 0x1) {
			Menu::bIsOpen = !Menu::bIsOpen;
		}

		static bool no_titlebar = false;
		static bool no_border = true;
		static bool no_resize = false;
		static bool auto_resize = false;
		static bool no_move = false;
		static bool no_scrollbar = false;
		static bool no_collapse = false;
		static bool no_menu = true;
		static bool start_pos_set = false;

		ImVec4* colors = ImGui::GetStyle().Colors;
		colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
		colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
		colors[ImGuiCol_WindowBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.83f);
		colors[ImGuiCol_ChildBg] = ImVec4(1.00f, 1.00f, 1.00f, 0.00f);
		colors[ImGuiCol_PopupBg] = ImVec4(0.08f, 0.08f, 0.08f, 0.94f);
		colors[ImGuiCol_Border] = ImVec4(0.43f, 0.43f, 0.50f, 0.50f);
		colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
		colors[ImGuiCol_FrameBg] = ImVec4(0.16f, 0.29f, 0.48f, 0.54f);
		colors[ImGuiCol_FrameBgHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.40f);
		colors[ImGuiCol_FrameBgActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
		colors[ImGuiCol_TitleBg] = ImVec4(0.04f, 0.04f, 0.04f, 1.00f);
		colors[ImGuiCol_TitleBgActive] = ImVec4(0.16f, 0.29f, 0.48f, 1.00f);
		colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
		colors[ImGuiCol_MenuBarBg] = ImVec4(1.00f, 0.00f, 0.00f, 0.61f);
		colors[ImGuiCol_ScrollbarBg] = ImVec4(0.02f, 0.02f, 0.02f, 0.53f);
		colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.16f, 0.29f, 0.48f, 0.54f);
		colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
		colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
		colors[ImGuiCol_CheckMark] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
		colors[ImGuiCol_SliderGrab] = ImVec4(0.24f, 0.52f, 0.88f, 1.00f);
		colors[ImGuiCol_SliderGrabActive] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
		colors[ImGuiCol_Button] = ImVec4(0.26f, 0.59f, 0.98f, 0.40f);
		colors[ImGuiCol_ButtonHovered] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
		colors[ImGuiCol_ButtonActive] = ImVec4(0.06f, 0.53f, 0.98f, 1.00f);
		colors[ImGuiCol_Header] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
		colors[ImGuiCol_HeaderHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.80f);
		colors[ImGuiCol_HeaderActive] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
		colors[ImGuiCol_Separator] = ImVec4(0.43f, 0.43f, 0.50f, 0.50f);
		colors[ImGuiCol_SeparatorHovered] = ImVec4(0.10f, 0.40f, 0.75f, 0.78f);
		colors[ImGuiCol_SeparatorActive] = ImVec4(0.10f, 0.40f, 0.75f, 1.00f);
		colors[ImGuiCol_ResizeGrip] = ImVec4(0.26f, 0.59f, 0.98f, 0.25f);
		colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
		colors[ImGuiCol_ResizeGripActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
		colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
		colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
		colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
		colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
		colors[ImGuiCol_TextSelectedBg] = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
		//colors[ImGuiCol_ModalWindowDarkening] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);
		colors[ImGuiCol_DragDropTarget] = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);

		ImGuiWindowFlags	window_flags = 0;
		if (no_titlebar)	window_flags |= ImGuiWindowFlags_NoTitleBar;
		if (no_resize)		window_flags |= ImGuiWindowFlags_NoResize;
		if (auto_resize)	window_flags |= ImGuiWindowFlags_AlwaysAutoResize;
		if (no_move)		window_flags |= ImGuiWindowFlags_NoMove;
		if (no_scrollbar)	window_flags |= ImGuiWindowFlags_NoScrollbar;
		if (no_collapse)	window_flags |= ImGuiWindowFlags_NoCollapse;
		if (!no_menu)		window_flags |= ImGuiWindowFlags_MenuBar;
		ImGui::SetNextWindowSize(ImVec2(450, 600));
		if (!start_pos_set) { ImGui::SetNextWindowPos(ImVec2(25, 25)); start_pos_set = true; }

		ImGui::GetIO().MouseDrawCursor = Menu::bIsOpen;

		if (Menu::bIsOpen)
		{
			ImGui::GetBackgroundDrawList()->AddRectFilled(ImVec2(0, 0), ImVec2(10, 10), 0xFFFFFFFF);


			ImGui::Begin("ImGui Menu", &Menu::bIsOpen, window_flags);

			ImGui::PushItemWidth(ImGui::GetWindowWidth() * 0.65f);
			ImGui::PushItemWidth(-140);

			if (ImGui::CollapsingHeader("MENU"))
			{
				if (ImGui::TreeNode("SUB MENU"))
				{
					ImGui::Text("Text Test");
					if (ImGui::Button("Button Test")) {}
					ImGui::Checkbox("CheckBox Test", &no_titlebar);
					//ImGui::SliderFloat("Slider Test", &test, 1.0f, 100.0f);

					ImGui::TreePop();
				}
			}

			ImGui::End();
		}
	}






	ImGui::EndFrame();
	ImGui::Render();

	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}


HRESULT __stdcall PresentHook(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags)
{
	static bool IsInited = false;
	if (!IsInited)
	{
		pSwapChain->GetDevice(__uuidof(g_pd3dDevice), reinterpret_cast<void**>(&g_pd3dDevice));
		g_pd3dDevice->GetImmediateContext(&g_pd3dContext);

		ImGui::CreateContext();

		inputHook.Init(g_hWnd);

		ImGui_ImplWin32_Init(g_hWnd);
		ImGui_ImplDX11_Init(g_pd3dDevice, g_pd3dContext);

		IsInited = true;
	}

	ImplHookDX11_Present(g_pd3dDevice, g_pd3dContext, g_pSwapChain);

	return phookD3D11Present(pSwapChain, SyncInterval, Flags);
}

void __stdcall DrawIndexedHook(ID3D11DeviceContext* pContext, UINT IndexCount, UINT StartIndexLocation, INT BaseVertexLocation)
{
	return phookD3D11DrawIndexed(pContext, IndexCount, StartIndexLocation, BaseVertexLocation);
}

void __stdcall hookD3D11CreateQuery(ID3D11Device* pDevice, const D3D11_QUERY_DESC* pQueryDesc, ID3D11Query** ppQuery)
{
	if (pQueryDesc->Query == D3D11_QUERY_OCCLUSION)
	{
		D3D11_QUERY_DESC oqueryDesc = CD3D11_QUERY_DESC();
		(&oqueryDesc)->MiscFlags = pQueryDesc->MiscFlags;
		(&oqueryDesc)->Query = D3D11_QUERY_TIMESTAMP;

		return phookD3D11CreateQuery(pDevice, &oqueryDesc, ppQuery);
	}

	return phookD3D11CreateQuery(pDevice, pQueryDesc, ppQuery);
}

UINT pssrStartSlot;
D3D11_SHADER_RESOURCE_VIEW_DESC Descr;

void __stdcall hookD3D11PSSetShaderResources(ID3D11DeviceContext* pContext, UINT StartSlot, UINT NumViews, ID3D11ShaderResourceView* const* ppShaderResourceViews)
{
	pssrStartSlot = StartSlot;

	for (UINT j = 0; j < NumViews; j++)
	{
		ID3D11ShaderResourceView* pShaderResView = ppShaderResourceViews[j];
		if (pShaderResView)
		{
			pShaderResView->GetDesc(&Descr);

			if ((Descr.ViewDimension == D3D11_SRV_DIMENSION_BUFFER) || (Descr.ViewDimension == D3D11_SRV_DIMENSION_BUFFEREX))
			{
				continue; //Skip buffer resources
			}
		}
	}

	return phookD3D11PSSetShaderResources(pContext, StartSlot, NumViews, ppShaderResourceViews);
}

void __stdcall ClearRenderTargetViewHook(ID3D11DeviceContext* pContext, ID3D11RenderTargetView* pRenderTargetView, const FLOAT ColorRGBA[4])
{
	return phookD3D11ClearRenderTargetViewHook(pContext, pRenderTargetView, ColorRGBA);
}

DWORD __stdcall HookDX11_Init()
{
	D3D_FEATURE_LEVEL levels[] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_1 };
	D3D_FEATURE_LEVEL obtainedLevel;
	DXGI_SWAP_CHAIN_DESC sd;
	{
		ZeroMemory(&sd, sizeof(sd));
		sd.BufferCount = 1;
		sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
		sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
		sd.OutputWindow = g_hWnd;
		sd.SampleDesc.Count = 1;
		sd.Windowed = ((GetWindowLongPtr(g_hWnd, GWL_STYLE) & WS_POPUP) != 0) ? false : true;
		sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
		sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

		sd.BufferDesc.Width = 1;
		sd.BufferDesc.Height = 1;
		sd.BufferDesc.RefreshRate.Numerator = 0;
		sd.BufferDesc.RefreshRate.Denominator = 1;
	}

	HRESULT hr = D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0, levels, sizeof(levels) / sizeof(D3D_FEATURE_LEVEL), D3D11_SDK_VERSION, &sd, &g_pSwapChain, &g_pd3dDevice, &obtainedLevel, &g_pd3dContext);
	if (FAILED(hr))
	{
		MessageBox(g_hWnd, L"Failed to create device and swapchain.", L"Fatal Error", MB_ICONERROR);
		return E_FAIL;
	}

	pSwapChainVTable = ((DWORD***)g_pSwapChain)[0];
	pDeviceVTable = ((DWORD***)g_pd3dDevice)[0];
	pDeviceContextVTable = ((DWORD***)g_pd3dContext)[0];

	if (MH_CreateHook(pSwapChainVTable[8], PresentHook, reinterpret_cast<void**>(&phookD3D11Present)) != MH_OK) { return 1; }
	if (MH_CreateHook(pDeviceContextVTable[12], DrawIndexedHook, reinterpret_cast<void**>(&phookD3D11DrawIndexed)) != MH_OK) { return 1; }
	if (MH_CreateHook(pDeviceVTable[24], hookD3D11CreateQuery, reinterpret_cast<void**>(&phookD3D11CreateQuery)) != MH_OK) { return 1; }
	if (MH_CreateHook(pDeviceContextVTable[8], hookD3D11PSSetShaderResources, reinterpret_cast<void**>(&phookD3D11PSSetShaderResources)) != MH_OK) { return 1; }
	if (MH_CreateHook(pSwapChainVTable[50], ClearRenderTargetViewHook, reinterpret_cast<void**>(&phookD3D11ClearRenderTargetViewHook)) != MH_OK) { return 1; }

	if (MH_EnableHook(MH_ALL_HOOKS) != MH_OK)
		return false;

	if (MH_Initialize() != MH_OK) { return 1; }
	if (MH_CreateHook((DWORD_PTR*)pSwapChainVTable[8], PresentHook, reinterpret_cast<void**>(&phookD3D11Present)) != MH_OK) { return 1; }
	if (MH_EnableHook((DWORD_PTR*)pSwapChainVTable[8]) != MH_OK) { return 1; }
	if (MH_CreateHook((DWORD_PTR*)pDeviceContextVTable[12], DrawIndexedHook, reinterpret_cast<void**>(&phookD3D11DrawIndexed)) != MH_OK) { return 1; }
	if (MH_EnableHook((DWORD_PTR*)pDeviceContextVTable[12]) != MH_OK) { return 1; }
	if (MH_CreateHook((DWORD_PTR*)pDeviceVTable[24], hookD3D11CreateQuery, reinterpret_cast<void**>(&phookD3D11CreateQuery)) != MH_OK) { return 1; }
	if (MH_EnableHook((DWORD_PTR*)pDeviceVTable[24]) != MH_OK) { return 1; }
	if (MH_CreateHook((DWORD_PTR*)pDeviceContextVTable[8], hookD3D11PSSetShaderResources, reinterpret_cast<void**>(&phookD3D11PSSetShaderResources)) != MH_OK) { return 1; }
	if (MH_EnableHook((DWORD_PTR*)pDeviceContextVTable[8]) != MH_OK) { return 1; }
	if (MH_CreateHook((DWORD_PTR*)pSwapChainVTable[50], ClearRenderTargetViewHook, reinterpret_cast<void**>(&phookD3D11ClearRenderTargetViewHook)) != MH_OK) { return 1; }
	if (MH_EnableHook((DWORD_PTR*)pSwapChainVTable[50]) != MH_OK) { return 1; }

	DWORD old_protect;
	VirtualProtect(phookD3D11Present, 2, PAGE_EXECUTE_READWRITE, &old_protect);

	do {
		Sleep(100);
	} while (!(GetAsyncKeyState(UninjectLibraryKey) & 0x1));

	g_pd3dDevice->Release();
	g_pd3dContext->Release();
	g_pSwapChain->Release();

	ImplHookDX11_Shutdown();
	inputHook.Remove(g_hWnd);

	Beep(220, 100);

	FreeLibraryAndExitThread(g_hModule, 0);

	return S_OK;
}

D3D11_HOOK_API void ImplHookDX11_Init(HMODULE hModule, void* hwnd)
{
	g_hWnd = (HWND)hwnd;
	g_hModule = hModule;
	auto retVal = HookDX11_Init();
}

D3D11_HOOK_API void ImplHookDX11_Shutdown()
{
	if (MH_DisableHook(MH_ALL_HOOKS)) { return; };
	if (MH_Uninitialize()) { return; }
}