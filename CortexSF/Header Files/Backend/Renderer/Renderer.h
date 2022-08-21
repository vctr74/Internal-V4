#pragma once
   
class Renderer
{
public:  
    void Initialize( );

    void BeginScene( );
    void EndScene( );

    float Text( const std::string& text, const ImVec2& position, float size, uint32_t color, bool center = false );
    float Text( const std::string& text, float x1, float y1, float size, uint32_t color, bool center = false );
    void DrawLine( const ImVec2& from, const ImVec2& to, uint32_t color, float thickness = 1.0f );
    void DrawLine( float x1, float y1, float x2, float y2, uint32_t color, float thickness = 1.0f );
    void DrawCircle( const ImVec2& position, float radius, uint32_t color, float thickness = 1.0f );
    void DrawCircle( float x, float y, float radius, uint32_t color, float thickness = 1.0f );
    void DrawCircleFilled( const ImVec2& position, float radius, uint32_t color );
    void DrawCircleFilled( float x, float y, float radius, uint32_t color );
    void DrawRect( const ImVec2& position, const ImVec2& dimensions, uint32_t color, float thickness = 1.0f );
    void DrawRect( float x, float y, float w, float h, uint32_t color, float thickness = 1.0f );
    void DrawRectFilled( const ImVec2& position, const ImVec2& dimensions, uint32_t color );
    void DrawRectFilled( float x, float y, float w, float h, uint32_t color );

    static Renderer* GetInstance( );

private:
	Renderer( ) = default;
	~Renderer( ) = default;

    ImFont* m_pFont;

    static Renderer* m_pInstance;
}; 

Renderer* Renderer::m_pInstance;
 

void Renderer::Initialize( )
{
	ImGuiIO& io = ImGui::GetIO( );

	// This is my example of font initializing
	// First font used for UI
	// Second for rendering, 32.0f is pixel size, not font size.
	io.Fonts->AddFontFromMemoryTTF( g_fRubik, sizeof( g_fRubik ), 12.0f, NULL, io.Fonts->GetGlyphRangesCyrillic( ) );
	m_pFont = io.Fonts->AddFontFromMemoryTTF( g_fRubik, sizeof( g_fRubik ), 32.0f, NULL, io.Fonts->GetGlyphRangesCyrillic( ) );

	io.Fonts->TexGlyphPadding = 1;
	for ( auto n = 0; n < io.Fonts->ConfigData.Size; n++ )
	{
		auto* const font_config = static_cast< ImFontConfig* >( &io.Fonts->ConfigData[ n ] );
		font_config->RasterizerMultiply = 1.5f;
	}
}

void Renderer::BeginScene( )
{
	ImGui_ImplDX11_NewFrame( );
	ImGui_ImplWin32_NewFrame( );
	ImGui::NewFrame( );

	ImGui::PushStyleColor( ImGuiCol_WindowBg, ImVec4( 0.0f, 0.0f, 0.0f, 0.0f ) );
	ImGui::PushStyleColor( ImGuiCol_Border, ImVec4( 0.0f, 0.0f, 0.0f, 0.0f ) );
	ImGui::Begin( x( "#" ), reinterpret_cast< bool* >( true ), ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoInputs );

	ImGui::SetWindowPos( ImVec2( 0, 0 ) );
	ImGui::SetWindowSize( ImVec2( ImGui::GetIO( ).DisplaySize.x, ImGui::GetIO( ).DisplaySize.y ) );
}

void Renderer::EndScene( )
{
	ImGuiWindow* window = ImGui::GetCurrentWindow( );
	window->DrawList->PushClipRectFullScreen( );

	ImGui::End( );
	ImGui::PopStyleColor( );
	ImGui::PopStyleColor( );

	ImGui::Render( );
	ImGui_ImplDX11_RenderDrawData( ImGui::GetDrawData( ) );
}

float Renderer::Text( const std::string& text, const ImVec2& pos, float size, uint32_t color, bool center )
{
	ImGuiWindow* window = ImGui::GetCurrentWindow( );

	float r = ( color ) & 0xff;
	float g = ( color >> 8 ) & 0xff;
	float b = ( color >> 16 ) & 0xff;
	float a = ( color >> 24 ) & 0xff;

	std::stringstream steam( text );
	std::string line;

	float y = 0.0f;
	int i = 0;

	while ( std::getline( steam, line ) )
	{
		ImVec2 textSize = m_pFont->CalcTextSizeA( size, FLT_MAX, 0.0f, line.c_str( ) );

		if ( center )
		{
			window->DrawList->AddText( m_pFont, size, ImVec2( ( pos.x - textSize.x / 2.0f ) + 1, ( pos.y + textSize.y * i ) + 1 ), ImGui::GetColorU32( ImVec4( 0, 0, 0, a / 255 ) ), line.c_str( ) );
			window->DrawList->AddText( m_pFont, size, ImVec2( ( pos.x - textSize.x / 2.0f ) - 1, ( pos.y + textSize.y * i ) - 1 ), ImGui::GetColorU32( ImVec4( 0, 0, 0, a / 255 ) ), line.c_str( ) );
			window->DrawList->AddText( m_pFont, size, ImVec2( ( pos.x - textSize.x / 2.0f ) + 1, ( pos.y + textSize.y * i ) - 1 ), ImGui::GetColorU32( ImVec4( 0, 0, 0, a / 255 ) ), line.c_str( ) );
			window->DrawList->AddText( m_pFont, size, ImVec2( ( pos.x - textSize.x / 2.0f ) - 1, ( pos.y + textSize.y * i ) + 1 ), ImGui::GetColorU32( ImVec4( 0, 0, 0, a / 255 ) ), line.c_str( ) );

			window->DrawList->AddText( m_pFont, size, ImVec2( pos.x - textSize.x / 2.0f, pos.y + textSize.y * i ), ImGui::GetColorU32( ImVec4( r / 255, g / 255, b / 255, a / 255 ) ), line.c_str( ) );
		}
		else
		{
			window->DrawList->AddText( m_pFont, size, ImVec2( ( pos.x ) + 1, ( pos.y + textSize.y * i ) + 1 ), ImGui::GetColorU32( ImVec4( 0, 0, 0, a / 255 ) ), line.c_str( ) );
			window->DrawList->AddText( m_pFont, size, ImVec2( ( pos.x ) - 1, ( pos.y + textSize.y * i ) - 1 ), ImGui::GetColorU32( ImVec4( 0, 0, 0, a / 255 ) ), line.c_str( ) );
			window->DrawList->AddText( m_pFont, size, ImVec2( ( pos.x ) + 1, ( pos.y + textSize.y * i ) - 1 ), ImGui::GetColorU32( ImVec4( 0, 0, 0, a / 255 ) ), line.c_str( ) );
			window->DrawList->AddText( m_pFont, size, ImVec2( ( pos.x ) - 1, ( pos.y + textSize.y * i ) + 1 ), ImGui::GetColorU32( ImVec4( 0, 0, 0, a / 255 ) ), line.c_str( ) );

			window->DrawList->AddText( m_pFont, size, ImVec2( pos.x, pos.y + textSize.y * i ), ImGui::GetColorU32( ImVec4( r / 255, g / 255, b / 255, a / 255 ) ), line.c_str( ) );
		}

		y = pos.y + textSize.y * ( i + 1 );
		i++;
	}

	return y;
}

float Renderer::Text( const std::string& text, float x1, float y1, float size, uint32_t color, bool center )
{
	return this->Text( text, ImVec2( x1, y1 ), size, color, center );
}

void Renderer::DrawLine( const ImVec2& from, const ImVec2& to, uint32_t color, float thickness )
{
	ImGuiWindow* window = ImGui::GetCurrentWindow( );

	float r = ( color ) & 0xff;
	float g = ( color >> 8 ) & 0xff;
	float b = ( color >> 16 ) & 0xff;
	float a = ( color >> 24 ) & 0xff;

	window->DrawList->AddLine( from, to, ImGui::GetColorU32( ImVec4( r / 255, g / 255, b / 255, a / 255 ) ), thickness );
}

void Renderer::DrawLine( float x1, float y1, float x2, float y2, uint32_t color, float thickness )
{
	return this->DrawLine( ImVec2( x1, y1 ), ImVec2( x2, y2 ), color, thickness );
}

void Renderer::DrawCircle( const ImVec2& position, float radius, uint32_t color, float thickness )
{
	ImGuiWindow* window = ImGui::GetCurrentWindow( );

	float r = ( color ) & 0xff;
	float g = ( color >> 8 ) & 0xff;
	float b = ( color >> 16 ) & 0xff;
	float a = ( color >> 24 ) & 0xff;

	window->DrawList->AddCircle( position, radius, ImGui::GetColorU32( ImVec4( r / 255, g / 255, b / 255, a / 255 ) ), 100.f, thickness );
}

void Renderer::DrawCircle( float x, float y, float radius, uint32_t color, float thickness )
{
	return this->DrawCircle( ImVec2( x, y ), radius, color, thickness );
}

void Renderer::DrawCircleFilled( const ImVec2& position, float radius, uint32_t color )
{
	ImGuiWindow* window = ImGui::GetCurrentWindow( );

	float r = ( color ) & 0xff;
	float g = ( color >> 8 ) & 0xff;
	float b = ( color >> 16 ) & 0xff;
	float a = ( color >> 24 ) & 0xff;

	window->DrawList->AddCircleFilled( position, radius, ImGui::GetColorU32( ImVec4( r / 255, g / 255, b / 255, a / 255 ) ), 12 );
}

void Renderer::DrawCircleFilled( float x, float y, float radius, uint32_t color )
{
	return this->DrawCircleFilled( ImVec2( x, y ), radius, color );
}

void Renderer::DrawRect( const ImVec2& position, const ImVec2& dimensions, uint32_t color, float thickness )
{
	ImGuiWindow* window = ImGui::GetCurrentWindow( );

	float r = ( color ) & 0xff;
	float g = ( color >> 8 ) & 0xff;
	float b = ( color >> 16 ) & 0xff;
	float a = ( color >> 24 ) & 0xff;

	window->DrawList->AddRect( position, ImVec2( position.x + dimensions.x, position.y + dimensions.y ), ImGui::GetColorU32( ImVec4( r / 255, g / 255, b / 255, a / 255 ) ), 0.f, 0, thickness );
}

void Renderer::DrawRect( float x, float y, float w, float h, uint32_t color, float thickness )
{
	return this->DrawRect( ImVec2( x, y ), ImVec2( w, h ), color, thickness );
}

void Renderer::DrawRectFilled( const ImVec2& position, const ImVec2& dimensions, uint32_t color )
{
	ImGuiWindow* window = ImGui::GetCurrentWindow( );

	float r = ( color ) & 0xff;
	float g = ( color >> 8 ) & 0xff;
	float b = ( color >> 16 ) & 0xff;
	float a = ( color >> 24 ) & 0xff;

	window->DrawList->AddRectFilled( position, ImVec2( position.x + dimensions.x, position.y + dimensions.y ), ImGui::GetColorU32( ImVec4( r / 255, g / 255, b / 255, a / 255 ) ) );
}

void Renderer::DrawRectFilled( float x, float y, float w, float h, uint32_t color )
{
	return this->DrawRectFilled( ImVec2( x, y ), ImVec2( w, h ), color );
}

Renderer* Renderer::GetInstance( )
{
	if ( !m_pInstance )
		m_pInstance = new Renderer( );

	return m_pInstance;
}

