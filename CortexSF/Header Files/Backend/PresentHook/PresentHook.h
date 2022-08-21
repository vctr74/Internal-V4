#pragma once

namespace PresentHook
{
	inline bool UnHook = false;

	inline bool InitRenderer = false;
	inline ID3D11RenderTargetView* pRtv = nullptr;
	inline ID3D11Device* pDevice = nullptr;
	inline ID3D11DeviceContext* pContext = nullptr;

	inline HRESULT( *PresentOriginal )( IDXGISwapChain* swapChain, UINT syncInterval, UINT flags ) = nullptr;
	inline HRESULT PresentHook( IDXGISwapChain* swapChain, UINT syncInterval, UINT flags )
	{
		swapChain->GetDevice( __uuidof( pDevice ), ( void** ) &pDevice );
		pDevice->GetImmediateContext( &pContext );

		if ( !InitRenderer )
		{
			ID3D11Texture2D* renderTargetTexture = nullptr;
			if ( SUCCEEDED( swapChain->GetBuffer( 0, __uuidof( ID3D11Texture2D ), reinterpret_cast< LPVOID* >( &renderTargetTexture ) ) ) )
			{
				pDevice->CreateRenderTargetView( renderTargetTexture, NULL, &pRtv );
				renderTargetTexture->Release( );
			}

			DXGI_SWAP_CHAIN_DESC sd;
			swapChain->GetDesc( &sd );
			HWND hWindow = sd.OutputWindow;

			ImGui::CreateContext( );
			ImGuiIO& io = ImGui::GetIO( );
			io.ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange;

			ImGui_ImplWin32_Init( hWindow );
			ImGui_ImplDX11_Init( pDevice, pContext );
			 
			Renderer::GetInstance( )->Initialize( );

			InitRenderer = true;
		}

		Renderer::GetInstance( )->BeginScene( );

		Menu::DrawMenu( );  
		Cortex::Run( ); 
  
		pContext->OMSetRenderTargets( 1, &pRtv, NULL );
		Renderer::GetInstance( )->EndScene( );

		if( Backend::skGetAsyncKeyState( VK_F9 ) )
		{
			MH_DisableHook( MH_ALL_HOOKS );
			MH_RemoveHook( MH_ALL_HOOKS );
		}  

		return PresentOriginal( swapChain, syncInterval, flags );
	}

	inline HRESULT( *ResizeOriginal )( IDXGISwapChain* swapChain, UINT bufferCount, UINT width, UINT height, DXGI_FORMAT newFormat, UINT swapChainFlags ) = nullptr;
	inline HRESULT ResizeHook( IDXGISwapChain* swapChain, UINT bufferCount, UINT width, UINT height, DXGI_FORMAT newFormat, UINT swapChainFlags )
	{
		if ( InitRenderer )
		{
			ImGui_ImplWin32_Shutdown( );
			ImGui_ImplDX11_Shutdown( );

			pRtv->Release( );
			pDevice->Release( );
			pContext->Release( );

			InitRenderer = false;
		}

		return ResizeOriginal( swapChain, bufferCount, width, height, newFormat, swapChainFlags );
	}

	inline void Initialize(   )
	{ 
		AllocConsole( );
		freopen( "conin$", "r", stdin );
		freopen( "conout$", "w", stdout );
		freopen( "conout$", "w", stderr );
		   
		Anvil::Initialize( );

		IDXGISwapChain* swapChain = nullptr;
		ID3D11Device* device = nullptr;
		ID3D11DeviceContext* context = nullptr;
		auto featureLevel = D3D_FEATURE_LEVEL_11_0;

		DXGI_SWAP_CHAIN_DESC sd = { 0 };
		sd.BufferCount = 1;
		sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

		sd.OutputWindow = GetForegroundWindow( );
		sd.SampleDesc.Count = 1;
		sd.Windowed = TRUE;

		if ( FAILED( D3D11CreateDeviceAndSwapChain( nullptr, D3D_DRIVER_TYPE_HARDWARE, 0, 0, &featureLevel, 1, D3D11_SDK_VERSION, &sd, &swapChain, &device, nullptr, &context ) ) )
		{
			MessageBoxA( 0, x( "D3D11CreateDeviceAndSwapChain FAILED" ), x( "PresentHook" ), MB_ICONERROR );
			return;
		}

		auto table = *reinterpret_cast< PVOID** >( swapChain );
		auto present = table[ 8 ];
		auto resize = table[ 13 ];

		context->Release( );
		device->Release( );
		swapChain->Release( );

		auto status = MH_Initialize( );    
		// InitiateChams( );

		if ( status != MH_OK )
		{
			MessageBoxA( 0, x( "Failes to initialize." ), x( "MinHook" ), MB_ICONERROR );
			return;
		}

		MH_CreateHook( present, PresentHook, reinterpret_cast< PVOID* >( &PresentOriginal ) );
		if ( status != MH_OK )
		{
			MessageBoxA( 0, x( "Faied to hook present." ), x( "MinHook" ), MB_ICONERROR );
			return;
		}

		MH_EnableHook( present );
		if ( status != MH_OK )
		{
			MessageBoxA( 0, x( "Failes to enable present hook." ), x( "MinHook" ), MB_ICONERROR );
			return;
		}

		MH_CreateHook( resize, ResizeHook, reinterpret_cast< PVOID* >( &ResizeOriginal ) );
		if ( status != MH_OK )
		{
			MessageBoxA( 0, x( "Failed to hook resize." ), x( "MinHook" ), MB_ICONERROR );
			return;
		}

		MH_EnableHook( resize );
		if ( status != MH_OK )
		{
			MessageBoxA( 0, x( "Failed to enable resize hook." ), x( "MinHook" ), MB_ICONERROR );
			return;
		}

		MH_EnableHook( resize );  
		Beep( 500, 500 ); 
	}
}