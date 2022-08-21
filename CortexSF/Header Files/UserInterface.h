#pragma once 

namespace GlobalSettings
{ 
    inline bool MenuEnabled = false; 
     
    inline bool SkeletonESP = true;  
    inline bool EnableTeam = true;
    inline bool EnableBots = true;
    inline bool VisibleCheck = true;

    inline ImVec4 TeamVisibleColor = { 1.f, 0.56862745098f, 1.f, 1.f }; 
    inline ImVec4 TeamInvisibleColor = { 0.5529411765f, 0.9921568627, 0.9921568627, 1.f };

    inline ImVec4 EnemyVisibleColor = { 1.f, 0.3098039216f, 0.3098039216f, 1.f }; 
    inline ImVec4 EnemyInvisibleColor = { 0.3803921569, 1.f, 0.3098039216f, 1.f }; 

    inline ImVec4 BotVisibleColor = { 0.7803921569, 0.4549019608, 0.2823529412, 1.f };
    inline ImVec4 BotInvisibleColor = { 0.7803921569, 0.7137254902, 0.2823529412, 1.f }; 
}

namespace Menu
{
    ImGuiIO io;

    inline auto InitStyle( )
    {
        ImGuiStyle* style = &ImGui::GetStyle( );
        ImVec4* colors = style->Colors;

        style->WindowRounding = 0.f;
        style->FrameRounding = 0.f;
        style->TabRounding = 0.f;
        style->GrabRounding = 0.f;
        style->WindowTitleAlign = ImVec2( 0.5f, 0.5f );

        colors[ ImGuiCol_WindowBg ] = ImColor( 18, 18, 18, 255 );

        colors[ ImGuiCol_FrameBg ] = ImColor( 31, 31, 31, 255 );
        colors[ ImGuiCol_FrameBgActive ] = ImColor( 41, 41, 41, 255 );
        colors[ ImGuiCol_FrameBgHovered ] = ImColor( 41, 41, 41, 255 );

        colors[ ImGuiCol_Button ] = ImColor( 29, 29, 29, 255 );
        colors[ ImGuiCol_ButtonActive ] = ImColor( 32, 32, 32, 255 );
        colors[ ImGuiCol_ButtonHovered ] = ImColor( 36, 36, 36, 255 );

        colors[ ImGuiCol_Border ] = ImColor( 0, 0, 0, 0 );
        colors[ ImGuiCol_Separator ] = ImColor( 36, 36, 36, 255 );

        colors[ ImGuiCol_ResizeGrip ] = ImColor( 30, 30, 30, 255 );
        colors[ ImGuiCol_ResizeGripActive ] = ImColor( 30, 30, 30, 255 );
        colors[ ImGuiCol_ResizeGripHovered ] = ImColor( 30, 30, 30, 255 );

        colors[ ImGuiCol_ChildBg ] = ImColor( 26, 26, 26, 255 );

        colors[ ImGuiCol_ScrollbarBg ] = ImColor( 24, 24, 24, 255 );
        colors[ ImGuiCol_ScrollbarGrab ] = ImColor( 24, 24, 24, 255 );
        colors[ ImGuiCol_ScrollbarGrabActive ] = ImColor( 24, 24, 24, 255 );
        colors[ ImGuiCol_ScrollbarGrabActive ] = ImColor( 24, 24, 24, 255 );

        colors[ ImGuiCol_Header ] = ImColor( 39, 39, 39, 255 );
        colors[ ImGuiCol_HeaderActive ] = ImColor( 39, 39, 39, 255 );
        colors[ ImGuiCol_HeaderHovered ] = ImColor( 39, 39, 39, 255 );
        colors[ ImGuiCol_CheckMark ] = ImColor( 255, 255, 255, 255 );

        colors[ ImGuiCol_TitleBg ] = ImVec4( 0.058f, 0.058f, 0.058f, 1.f );
        colors[ ImGuiCol_TitleBgActive ] = ImVec4( 0.058f, 0.058f, 0.058f, 1.f );

        colors[ ImGuiCol_SliderGrab ] = ImColor( 186, 191, 46 );
        colors[ ImGuiCol_SliderGrabActive ] = ImColor( 186, 191, 46 );

    }

    inline auto CaptureInput( )
    {
        auto io = &ImGui::GetIO( );

        io->MouseDown[ 0 ] = ( GetAsyncKeyState( VK_LBUTTON ) & 0x8000 );
        io->MouseDown[ 1 ] = ( GetAsyncKeyState( VK_RBUTTON ) & 0x8000 );
        io->MouseDown[ 2 ] = ( GetAsyncKeyState( VK_MBUTTON ) & 0x8000 );
    }

    inline int MenuKeyDown = 0;
    inline int TabNumber = 0;
    inline bool CenterOnce = false;

    inline auto DrawMenu( ) // example UI, took out private stuff
    {
        io = ImGui::GetIO( );
        if ( GlobalSettings::MenuEnabled )
        {
            if ( !CenterOnce )
            {
                CenterOnce = true;
                ImGui::SetNextWindowPos( ImVec2( io.DisplaySize.x * 0.5f, io.DisplaySize.y * 0.5f ), ImGuiCond_Always, ImVec2( 0.5f, 0.5f ) );
            }
                

            CaptureInput( );
            Menu::InitStyle( );
            ImGui::SetNextWindowSize( ImVec2{ 300, 188 } );

            ImGui::Begin( x( "##CLIENT" ), 0, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar );
            {
                ImGui::BeginChild( "##LeftSide", ImVec2( 30, ImGui::GetContentRegionAvail( ).y ), TRUE );
                {
                    float width = ( ImGui::GetContentRegionAvail( ).x / 3 ) - ( 15 / 3 );

                    if ( ImGui::ButtonNew( x( "0" ), ImVec2{ width , 20 } ) )
                        TabNumber = 0;

                    if ( ImGui::ButtonNew( x( "1" ), ImVec2{ width, 20 } ) )
                        TabNumber = 0;

                    if ( ImGui::ButtonNew( x( "2" ), ImVec2{ width, 20 } ) )
                        TabNumber = 0;
                }
                ImGui::EndChild( );

                ImGui::SameLine( );

                ImGui::BeginChild( x( "##MiddleSide" ), ImVec2( ImGuiPP::GetX( ), ImGuiPP::GetY( ) ), TRUE );
                {
                    switch ( TabNumber )
                    {
                    case 0:
                        ImGui::Toggle( x( "##Enemy " ), &GlobalSettings::SkeletonESP );
                        ImGui::SameLine( );
                        ImGui::ColorEdit4( x( "Enemies  " ), &GlobalSettings::EnemyVisibleColor.x, ImGuiColorEditFlags_PickerHueWheel | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel, "Enemy" );
                        ImGui::SameLine( );
                        ImGui::ColorEdit4( x( "Invisible Enemies" ), &GlobalSettings::EnemyInvisibleColor.x, ImGuiColorEditFlags_PickerHueWheel | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel, "Visible" );
                        ImGui::Toggle( x( "##Team" ), &GlobalSettings::EnableTeam );
                        ImGui::SameLine( );
                        ImGui::ColorEdit4( x( "Team" ), &GlobalSettings::TeamVisibleColor.x, ImGuiColorEditFlags_PickerHueWheel | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel, "Team" );
                        ImGui::SameLine( );
                        ImGui::ColorEdit4( x( "Invisible Team" ), &GlobalSettings::TeamInvisibleColor.x, ImGuiColorEditFlags_PickerHueWheel | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel, "Visible" );
                        ImGui::Toggle( x( "##Bots" ), &GlobalSettings::EnableBots );
                        ImGui::SameLine( );
                        ImGui::ColorEdit4( x( "Bots" ), &GlobalSettings::BotVisibleColor.x, ImGuiColorEditFlags_PickerHueWheel | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel, "Bots" );
                        ImGui::SameLine( );
                        ImGui::ColorEdit4( x( "Invisible Bots" ), &GlobalSettings::BotInvisibleColor.x, ImGuiColorEditFlags_PickerHueWheel | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel, "Visible" ); 
                        ImGui::Toggle( x( "Visible Check" ), &GlobalSettings::VisibleCheck );
                        break; 
                    }
                }
                ImGui::EndChild( );
            }
            ImGui::End( );
        }
        if ( ( Backend::skGetAsyncKeyState( VK_INSERT ) & 0x8000 ) && ( MenuKeyDown == 0 ) )
        {
            GlobalSettings::MenuEnabled = !GlobalSettings::MenuEnabled;
            MenuKeyDown = 1;
        }
        if ( Backend::skGetAsyncKeyState( VK_INSERT ) == 0 ) {
            MenuKeyDown = 0;
        } 
    }
}