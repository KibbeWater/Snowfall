#include "pch.h"

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
static ID3D11Device*			g_pd3dDevice = nullptr;
static ID3D11DeviceContext*		g_pd3dContext = nullptr;
static IDXGISwapChain*			g_pSwapChain = nullptr;
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
ELockState oldLockState = LOCKSTATE_NONE;

template <typename T = void*>
__forceinline T GetVirtual(void* thisptr, int iIndex)
{
	return (*static_cast<T**>(thisptr))[iIndex];
}


D3D11_HOOK_API void ImplHookDX11_Present(ID3D11Device* device, ID3D11DeviceContext* ctx, IDXGISwapChain* swap_chain)
{
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();

	ImGui::NewFrame();
	Config::newFrame();

	ImDrawList* draw = ImGui::GetBackgroundDrawList();
	G::pDrawList = draw;
	G::oCallbackManager->trigger_event(Callbacks::Event::Render);
	G::pDrawList = nullptr;
	
	// Super advanced menu code in here
	{
		Menu::Render();
	}

	{
		bool bESP = Config::get("visual_esp_state_enabled", false);

		if (bESP && false)
			for (auto player : GameAPI::GetPlayersAlive()) {
				if (!player) continue;

				Unity::CComponent* playerComponent = reinterpret_cast<Unity::CComponent*>(player);
				if (!playerComponent) continue;

				Unity::CGameObject* gameObject = playerComponent->GetMemberValue<Unity::CGameObject*>("gameObject");
				if (!gameObject) continue;

				auto bounds = GameAPI::GetBounds(gameObject);

				Vector3 origin = Vector3(bounds->m_vCenter);
				Vector3 extent = Vector3(bounds->m_vExtents);

				Vector3 Corners[8]{ Vector3(0,0,0),Vector3(0,0,0),Vector3(0,0,0),Vector3(0,0,0),Vector3(0,0,0),Vector3(0,0,0),Vector3(0,0,0),Vector3(0,0,0) };
				Corners[0] = origin + Vector3(-extent.x, -extent.y, -extent.z);
				Corners[1] = origin + Vector3(extent.x, -extent.y, -extent.z);
				Corners[2] = origin + Vector3(extent.x, extent.y, -extent.z);
				Corners[3] = origin + Vector3(-extent.x, extent.y, -extent.z);
				Corners[4] = origin + Vector3(-extent.x, -extent.y, extent.z);
				Corners[5] = origin + Vector3(extent.x, -extent.y, extent.z);
				Corners[6] = origin + Vector3(extent.x, extent.y, extent.z);
				Corners[7] = origin + Vector3(-extent.x, extent.y, extent.z);

				Vector3 ScreenCorners[8]{ Vector3(0,0,0),Vector3(0,0,0),Vector3(0,0,0),Vector3(0,0,0),Vector3(0,0,0),Vector3(0,0,0),Vector3(0,0,0),Vector3(0,0,0) };
				for (int i = 0; i < 8; ++i) {
					auto screen = Engine::WorldToScreen(Corners[i]);
					ScreenCorners[i] = screen;
				}

				auto DrawLine = [&](int Index1, int Index2)
					{
						auto p1 = ScreenCorners[Index1];
						auto p2 = ScreenCorners[Index2];
						draw->AddLine(ImVec2(p1.x, p1.y), ImVec2(p2.x, p2.y), IM_COL32(255,0,0,255));
					};

				// Bottom face
				DrawLine(0, 1);
				DrawLine(1, 2);
				DrawLine(2, 3);
				DrawLine(3, 0);

				// Top face
				DrawLine(4, 5);
				DrawLine(5, 6);
				DrawLine(6, 7);
				DrawLine(7, 4);

				// Vertical lines
				DrawLine(0, 4);
				DrawLine(1, 5);
				DrawLine(2, 6);
				DrawLine(3, 7);
			}
		
		////Temporary solution, just wanted it to work for now
		static bool hasTeleported = false;
		auto iClickTPKey = Config::get("movement_clicktp_hotkey", (int)ImGuiKey_None);
		bool bClickTPDown = iClickTPKey != ImGuiKey_None ? ImGui::IsKeyPressed(
			static_cast<ImGuiKey>(iClickTPKey),
			false) : false;
		if (!hasTeleported && bClickTPDown) {
			auto m_pPlayer = Unity::GameObject::Find("Player");

			auto curCam = reinterpret_cast<Unity::CTransform*>(GameAPI::GetPlayerInput()->static_fields->_Instance_k__BackingField->fields.playerCam);
			auto pos = new Vector3(curCam->GetPosition());
			auto fwd = new Vector3(curCam->GetMemberValue<Unity::Vector3>("forward"));

			UnityEngine_RaycastHit_o hit = {};
			if (GameAPI::Raycast(pos->ToEngine(), fwd->ToEngine(), &hit, 1000, GameAPI::GetGamemanager()->static_fields->Instance->fields.whatIsHittableBullet.fields.m_Mask)) {
				auto tpPos = new Vector3(hit.fields.m_Point);
				tpPos->y++;
				m_pPlayer->GetTransform()->SetPosition(*tpPos->ToUnity());
			}

			hasTeleported = true;
		}
		else if (hasTeleported && !bClickTPDown) {
			hasTeleported = false;
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
		G::g_pd3dDevice = g_pd3dDevice;

		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

		io.Fonts->AddFontFromFileTTF(FS::GetAsset("roboto.ttf").c_str(), 16);

		ImFontConfig config;
		config.MergeMode = true;
		config.GlyphMinAdvanceX = 13.0f; // Use if you want to make the icon monospaced
		static constexpr ImWchar icon_ranges[] = { 0xe000, 0xe007, 0 };
		io.Fonts->AddFontFromFileTTF(FS::GetAsset("snowfall.ttf").c_str(), 24, &config, icon_ranges);

		io.Fonts->Build();

		ImGui::StyleColorsDark();

		ImGui_ImplWin32_Init(g_hWnd);
		ImGui_ImplDX11_Init(g_pd3dDevice, g_pd3dContext);

		inputHook.Init(g_hWnd);

		IsInited = true;
	}

	if (GetAsyncKeyState(OpenMenuKey) & 0x1) {
		Menu::bIsOpen = !Menu::bIsOpen;

		if (Menu::bIsOpen) {
			oldLockState = GameAPI::GetLockState();
			GameAPI::SetLockState(LOCKSTATE_NONE);
		}
		else {
			auto curLockstate = GameAPI::GetLockState();
			if (curLockstate == LOCKSTATE_NONE)
				GameAPI::SetLockState(oldLockState);
		}
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