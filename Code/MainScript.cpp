#include <windows.h>
#include <shellapi.h>
#include "MainScript.hpp"
#include "ScriptCallback.hpp"
#include "Lists.hpp"
#include "Natives.hpp"
#include "Timer.hpp"
#include "CustomText.hpp"
#include "Features.hpp"
#include "UI/UIManager.hpp"
#include "UI/BoolOption.hpp"
#include "UI/ChooseOption.hpp"
#include "UI/NumberOption.hpp"
#include "UI/RegularOption.hpp"
#include "UI/SubOption.hpp"
#include "UI/RegularSubmenu.hpp"
#include "UI/PlayerSubmenu.hpp"

namespace Big
{
	enum Submenu : std::uint32_t
	{
		SubmenuHome,
		SubmenuSelf,
		SubmenuHeists,
		SubmenuSession,
		SubmenuSettings,
		SubmenuSettingsHeader,
		SubmenuSettingsScrollbar,
		SubmenuSettingsSeperator,
		SubmenuSettingsHeaderStaticBackground,
		SubmenuSettingsHeaderGradientBackground,
		SubmenuSettingsHeaderAnimatedBackground,
		SubmenuSettingsHeaderText,
		SubmenuSettingsSubmenuBar,
		SubmenuSettingsOption,
		SubmenuSettingsFooter,
		SubmenuSettingsDescription,
		SubmenuSettingsInput,
		SubmenuSettingsLanguage,
		SubmenuSelectedPlayer,
		SubmenuPlayerList
	};

	bool MainScript::IsInitialized()
	{
		return m_Initialized;
	}

	ScriptType MainScript::GetType()
	{
		return ScriptType::Game;
	}

	void MainScript::Initialize()
	{
		m_Initialized = true;
		using namespace UserInterface;

		g_UiManager->AddSubmenu<RegularSubmenu>("Home", SubmenuHome, [](RegularSubmenu* sub)
			{
				sub->AddOption<SubOption>("Self", nullptr, SubmenuSelf);
				sub->AddOption<SubOption>("Players", nullptr, SubmenuPlayerList);
				sub->AddOption<SubOption>("Heists", nullptr, SubmenuHeists);
				sub->AddOption<SubOption>("Session", nullptr, SubmenuSession);
				sub->AddOption<SubOption>("Settings", nullptr, SubmenuSettings);
				sub->AddOption<RegularOption>(std::move(RegularOption("Server Invite", nullptr, [] {
					ShellExecuteA(0, 0, "https://discord.gg/J8486xStu6", 0, 0, SW_SHOW);
					}).SetRightText("discord.gg/J8486xStu6")));
				sub->AddOption<RegularOption>(std::move(RegularOption("Game Version").SetRightText(g_GameVariables->m_GameBuild)));

				sub->AddOption<RegularOption>("Unload", nullptr, []
					{
						g_Running = false;
					});
			});

		g_UiManager->AddSubmenu<RegularSubmenu>("Self", SubmenuSelf, [](RegularSubmenu* sub) {

		});

		g_UiManager->AddSubmenu<RegularSubmenu>("Heists", SubmenuHeists, [](RegularSubmenu* sub) {
	
		});

		g_UiManager->AddSubmenu<RegularSubmenu>("Session", SubmenuSession, [](RegularSubmenu* sub) {
			sub->AddOption<RegularOption>("Join Public Session", nullptr, [] {
				Features::EnterSession(0);
			});
			sub->AddOption<RegularOption>("New Public Session", nullptr, []{
				Features::EnterSession(1);
			});
			sub->AddOption<RegularOption>("Closed Crew Session", nullptr, [] {
				Features::EnterSession(2);
			});
			sub->AddOption<RegularOption>("Crew Session", nullptr, [] {
				Features::EnterSession(3);
			});
			sub->AddOption<RegularOption>("Closed Friend Session", nullptr, [] {
				Features::EnterSession(6);
			});
			sub->AddOption<RegularOption>("Find Friend Session", nullptr, [] {
				Features::EnterSession(9);
			});
			sub->AddOption<RegularOption>("Solo Session", nullptr, [] {
				Features::EnterSession(10);
			});
			sub->AddOption<RegularOption>("Invite Only Session", nullptr, [] {
				Features::EnterSession(11);
			});
			sub->AddOption<RegularOption>("Join Crew Session", nullptr, [] {
				Features::EnterSession(12);
			});
			sub->AddOption<RegularOption>("Leave GTA Online", nullptr, [] {
				Features::LeaveGTAOnline();
			});
		});

		g_UiManager->AddSubmenu<RegularSubmenu>("Settings", SubmenuSettings, [](RegularSubmenu* sub)
			{
				sub->AddOption<SubOption>("Header", nullptr, SubmenuSettingsHeader);
				sub->AddOption<SubOption>("Scrollbar", nullptr, SubmenuSettingsScrollbar);
				sub->AddOption<SubOption>("Seperator", nullptr, SubmenuSettingsSeperator);
				sub->AddOption<SubOption>("Infobar", nullptr, SubmenuSettingsSubmenuBar);
				sub->AddOption<SubOption>("Options", nullptr, SubmenuSettingsOption);
				sub->AddOption<SubOption>("Footer", nullptr, SubmenuSettingsFooter);
				sub->AddOption<SubOption>("Description", nullptr, SubmenuSettingsDescription);
				sub->AddOption<SubOption>("Input", nullptr, SubmenuSettingsInput);
				sub->AddOption<SubOption>("Language", nullptr, SubmenuSettingsLanguage);
				sub->AddOption<NumberOption<float>>("X Position", nullptr, &g_UiManager->m_PosX, 0.f, 1.f, 0.01f, 2);
				sub->AddOption<NumberOption<float>>("Y Position", nullptr, &g_UiManager->m_PosY, 0.f, 1.f, 0.01f, 2);
				sub->AddOption<NumberOption<float>>("Width", nullptr, &g_UiManager->m_Width, 0.01f, 1.f, 0.01f, 2);
				sub->AddOption<NumberOption<size_t>>("Options Per Page", nullptr, &g_UiManager->m_OptionsPerPage, 1, static_cast<size_t>(20));
				sub->AddOption<BoolOption<bool>>("Sounds", nullptr, &g_UiManager->m_Sounds, BoolDisplay::OnOff);
#if _DEBUG
				sub->AddOption<BoolOption<std::atomic_bool>>("Log Window", nullptr, &g_Settings.m_LogWindow, BoolDisplay::OnOff);
				sub->AddOption<BoolOption<std::atomic_bool>>("Lock Cursor", nullptr, &g_Settings.m_LockMouse, BoolDisplay::OnOff);
#endif
			});

		g_UiManager->AddSubmenu<RegularSubmenu>("Seperator", SubmenuSettingsSeperator, [](RegularSubmenu* sub) {
			sub->AddOption<BoolOption<bool>>("Enabled", nullptr, &g_UiManager->m_SeperatorEnabled, BoolDisplay::OnOff);
			sub->AddOption<NumberOption<float>>("Height", nullptr, &g_UiManager->m_SeperatorHeight, 0.001f, 0.01f, 0.001f, 3);
			sub->AddOption<NumberOption<std::uint8_t>>("Left R", nullptr, &g_UiManager->m_SeperatorColorLeft.r, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("Left G", nullptr, &g_UiManager->m_SeperatorColorLeft.g, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("Left B", nullptr, &g_UiManager->m_SeperatorColorLeft.b, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("Left A", nullptr, &g_UiManager->m_SeperatorColorLeft.a, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("Middle R", nullptr, &g_UiManager->m_SeperatorColorMiddle.r, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("Middle G", nullptr, &g_UiManager->m_SeperatorColorMiddle.g, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("Middle B", nullptr, &g_UiManager->m_SeperatorColorMiddle.b, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("Middle A", nullptr, &g_UiManager->m_SeperatorColorMiddle.a, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("Right R", nullptr, &g_UiManager->m_SeperatorColorRight.r, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("Right G", nullptr, &g_UiManager->m_SeperatorColorRight.g, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("Right B", nullptr, &g_UiManager->m_SeperatorColorRight.b, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("Right A", nullptr, &g_UiManager->m_SeperatorColorRight.a, '\0', static_cast<std::uint8_t>(255));
		});

		g_UiManager->AddSubmenu<RegularSubmenu>("Infobar", SubmenuSettingsSubmenuBar, [](RegularSubmenu* sub)
			{
				sub->AddOption<NumberOption<float>>("Height", nullptr, &g_UiManager->m_SubmenuBarHeight, 0.01f, 0.1f, 0.001f, 3);
				sub->AddOption<NumberOption<float>>("Text Size", nullptr, &g_UiManager->m_SubmenuBarTextSize, 0.01f, 1.f, 0.01f, 2);
				sub->AddOption<NumberOption<std::uint8_t>>("Background R", nullptr, &g_UiManager->m_SubmenuBarBackgroundColor.r, '\0', static_cast<std::uint8_t>(255));
				sub->AddOption<NumberOption<std::uint8_t>>("Background G", nullptr, &g_UiManager->m_SubmenuBarBackgroundColor.g, '\0', static_cast<std::uint8_t>(255));
				sub->AddOption<NumberOption<std::uint8_t>>("Background B", nullptr, &g_UiManager->m_SubmenuBarBackgroundColor.b, '\0', static_cast<std::uint8_t>(255));
				sub->AddOption<NumberOption<std::uint8_t>>("Background A", nullptr, &g_UiManager->m_SubmenuBarBackgroundColor.a, '\0', static_cast<std::uint8_t>(255));
				sub->AddOption<NumberOption<std::uint8_t>>("Text R", nullptr, &g_UiManager->m_SubmenuBarTextColor.r, '\0', static_cast<std::uint8_t>(255));
				sub->AddOption<NumberOption<std::uint8_t>>("Text G", nullptr, &g_UiManager->m_SubmenuBarTextColor.g, '\0', static_cast<std::uint8_t>(255));
				sub->AddOption<NumberOption<std::uint8_t>>("Text B", nullptr, &g_UiManager->m_SubmenuBarTextColor.b, '\0', static_cast<std::uint8_t>(255));
				sub->AddOption<NumberOption<std::uint8_t>>("Text A", nullptr, &g_UiManager->m_SubmenuBarTextColor.a, '\0', static_cast<std::uint8_t>(255));
			});

		g_UiManager->AddSubmenu<RegularSubmenu>("Options", SubmenuSettingsOption, [](RegularSubmenu* sub)
			{
				sub->AddOption<NumberOption<float>>("Height", nullptr, &g_UiManager->m_OptionHeight, 0.01f, 0.1f, 0.001f, 3);
				sub->AddOption<NumberOption<float>>("Text Size", nullptr, &g_UiManager->m_OptionTextSize, 0.01f, 1.f, 0.01f, 2);

				sub->AddOption<NumberOption<std::uint8_t>>("Selected Background R", nullptr, &g_UiManager->m_OptionSelectedBackgroundColor.r, '\0', static_cast<std::uint8_t>(255));
				sub->AddOption<NumberOption<std::uint8_t>>("Selected Background G", nullptr, &g_UiManager->m_OptionSelectedBackgroundColor.g, '\0', static_cast<std::uint8_t>(255));
				sub->AddOption<NumberOption<std::uint8_t>>("Selected Background B", nullptr, &g_UiManager->m_OptionSelectedBackgroundColor.b, '\0', static_cast<std::uint8_t>(255));
				sub->AddOption<NumberOption<std::uint8_t>>("Selected Background A", nullptr, &g_UiManager->m_OptionSelectedBackgroundColor.a, '\0', static_cast<std::uint8_t>(255));
				sub->AddOption<NumberOption<std::uint8_t>>("Unselected Background R", nullptr, &g_UiManager->m_OptionUnselectedBackgroundColor.r, '\0', static_cast<std::uint8_t>(255));
				sub->AddOption<NumberOption<std::uint8_t>>("Unselected Background G", nullptr, &g_UiManager->m_OptionUnselectedBackgroundColor.g, '\0', static_cast<std::uint8_t>(255));
				sub->AddOption<NumberOption<std::uint8_t>>("Unselected Background B", nullptr, &g_UiManager->m_OptionUnselectedBackgroundColor.b, '\0', static_cast<std::uint8_t>(255));
				sub->AddOption<NumberOption<std::uint8_t>>("Unselected Background A", nullptr, &g_UiManager->m_OptionUnselectedBackgroundColor.a, '\0', static_cast<std::uint8_t>(255));

				sub->AddOption<NumberOption<std::uint8_t>>("Selected Text R", nullptr, &g_UiManager->m_OptionSelectedTextColor.r, '\0', static_cast<std::uint8_t>(255));
				sub->AddOption<NumberOption<std::uint8_t>>("Selected Text G", nullptr, &g_UiManager->m_OptionSelectedTextColor.g, '\0', static_cast<std::uint8_t>(255));
				sub->AddOption<NumberOption<std::uint8_t>>("Selected Text B", nullptr, &g_UiManager->m_OptionSelectedTextColor.b, '\0', static_cast<std::uint8_t>(255));
				sub->AddOption<NumberOption<std::uint8_t>>("Selected Text A", nullptr, &g_UiManager->m_OptionSelectedTextColor.a, '\0', static_cast<std::uint8_t>(255));
				sub->AddOption<NumberOption<std::uint8_t>>("Unselected Text R", nullptr, &g_UiManager->m_OptionUnselectedTextColor.r, '\0', static_cast<std::uint8_t>(255));
				sub->AddOption<NumberOption<std::uint8_t>>("Unselected Text G", nullptr, &g_UiManager->m_OptionUnselectedTextColor.g, '\0', static_cast<std::uint8_t>(255));
				sub->AddOption<NumberOption<std::uint8_t>>("Unselected Text B", nullptr, &g_UiManager->m_OptionUnselectedTextColor.b, '\0', static_cast<std::uint8_t>(255));
				sub->AddOption<NumberOption<std::uint8_t>>("Unselected Text A", nullptr, &g_UiManager->m_OptionUnselectedTextColor.a, '\0', static_cast<std::uint8_t>(255));
			});

		g_UiManager->AddSubmenu<RegularSubmenu>("Footer", SubmenuSettingsFooter, [](RegularSubmenu* sub)
			{
				sub->AddOption<NumberOption<float>>("Height", nullptr, &g_UiManager->m_FooterHeight, 0.01f, 0.1f, 0.001f, 3);
				sub->AddOption<NumberOption<float>>("Sprite Size", nullptr, &g_UiManager->m_FooterSpriteSize, 0.01f, 1.f, 0.001f, 3);

				sub->AddOption<NumberOption<std::uint8_t>>("Background R", nullptr, &g_UiManager->m_FooterBackgroundColor.r, '\0', static_cast<std::uint8_t>(255));
				sub->AddOption<NumberOption<std::uint8_t>>("Background G", nullptr, &g_UiManager->m_FooterBackgroundColor.g, '\0', static_cast<std::uint8_t>(255));
				sub->AddOption<NumberOption<std::uint8_t>>("Background B", nullptr, &g_UiManager->m_FooterBackgroundColor.b, '\0', static_cast<std::uint8_t>(255));
				sub->AddOption<NumberOption<std::uint8_t>>("Background A", nullptr, &g_UiManager->m_FooterBackgroundColor.a, '\0', static_cast<std::uint8_t>(255));
				sub->AddOption<NumberOption<std::uint8_t>>("Sprite R", nullptr, &g_UiManager->m_FooterSpriteColor.r, '\0', static_cast<std::uint8_t>(255));
				sub->AddOption<NumberOption<std::uint8_t>>("Sprite G", nullptr, &g_UiManager->m_FooterSpriteColor.g, '\0', static_cast<std::uint8_t>(255));
				sub->AddOption<NumberOption<std::uint8_t>>("Sprite B", nullptr, &g_UiManager->m_FooterSpriteColor.b, '\0', static_cast<std::uint8_t>(255));
				sub->AddOption<NumberOption<std::uint8_t>>("Sprite A", nullptr, &g_UiManager->m_FooterSpriteColor.a, '\0', static_cast<std::uint8_t>(255));
			});

		g_UiManager->AddSubmenu<RegularSubmenu>("Scrollbar", SubmenuSettingsScrollbar, [](RegularSubmenu* sub) {
			sub->AddOption<NumberOption<float>>("Width", nullptr, &g_UiManager->m_ScrollBarWidth, 0.001f, 0.1f, 0.001f, 3);
			sub->AddOption<NumberOption<float>>("Offset", nullptr, &g_UiManager->m_ScrollBarOffset, 0.001f, 0.1f, 0.001f, 3);
			sub->AddOption<NumberOption<float>>("Sprite Size", nullptr, &g_UiManager->m_ScrollBarSpriteSize, 0.01f, 0.1f, 0.001f, 3);
			sub->AddOption<NumberOption<std::uint8_t>>("Background R", nullptr, &g_UiManager->m_ScrollBarBackgroundColor.r, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("Background G", nullptr, &g_UiManager->m_ScrollBarBackgroundColor.g, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("Background B", nullptr, &g_UiManager->m_ScrollBarBackgroundColor.b, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("Background A", nullptr, &g_UiManager->m_ScrollBarBackgroundColor.a, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("Foreground R", nullptr, &g_UiManager->m_ScrollBarForegroundColor.r, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("Foreground G", nullptr, &g_UiManager->m_ScrollBarForegroundColor.g, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("Foreground B", nullptr, &g_UiManager->m_ScrollBarForegroundColor.b, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("Foreground A", nullptr, &g_UiManager->m_ScrollBarForegroundColor.a, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("End Background R", nullptr, &g_UiManager->m_ScrollBarEndColor.r, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("End Background G", nullptr, &g_UiManager->m_ScrollBarEndColor.g, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("End Background B", nullptr, &g_UiManager->m_ScrollBarEndColor.b, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("End Background A", nullptr, &g_UiManager->m_ScrollBarEndColor.a, '\0', static_cast<std::uint8_t>(255));
		});

		g_UiManager->AddSubmenu<RegularSubmenu>("Header", SubmenuSettingsHeader, [](RegularSubmenu* sub)
			{
				sub->AddOption<ChooseOption<const char*, std::size_t>>("Type", nullptr, &Lists::HeaderTypesFrontend, &Lists::HeaderTypesPosition, true, []
					{
						g_UiManager->m_HeaderType = Lists::HeaderTypesBackend[Lists::HeaderTypesPosition];
					});

				switch (g_UiManager->m_HeaderType)
				{
				case HeaderType::Static:
					sub->AddOption<SubOption>("Background", nullptr, SubmenuSettingsHeaderStaticBackground);
					break;
				case HeaderType::Gradient:
					sub->AddOption<SubOption>("Gradient", nullptr, SubmenuSettingsHeaderGradientBackground);
					break;
				case HeaderType::Animated:
					sub->AddOption<SubOption>("Animated", nullptr, SubmenuSettingsHeaderAnimatedBackground);
					break;
				}

				sub->AddOption<SubOption>("Text", nullptr, SubmenuSettingsHeaderText);
				sub->AddOption<NumberOption<float>>("Height", nullptr, &g_UiManager->m_HeaderHeight, 0.01f, 0.2f, 0.001f, 3);
			});

		g_UiManager->AddSubmenu<RegularSubmenu>("Header Background", SubmenuSettingsHeaderStaticBackground, [](RegularSubmenu* sub)
			{
				sub->AddOption<NumberOption<std::uint8_t>>("R", nullptr, &g_UiManager->m_HeaderBackgroundColor.r, '\0', static_cast<std::uint8_t>(255));
				sub->AddOption<NumberOption<std::uint8_t>>("G", nullptr, &g_UiManager->m_HeaderBackgroundColor.g, '\0', static_cast<std::uint8_t>(255));
				sub->AddOption<NumberOption<std::uint8_t>>("B", nullptr, &g_UiManager->m_HeaderBackgroundColor.b, '\0', static_cast<std::uint8_t>(255));
				sub->AddOption<NumberOption<std::uint8_t>>("A", nullptr, &g_UiManager->m_HeaderBackgroundColor.a, '\0', static_cast<std::uint8_t>(255));
			});

		g_UiManager->AddSubmenu<RegularSubmenu>("Header Gradient", SubmenuSettingsHeaderGradientBackground, [](RegularSubmenu* sub)
			{
				sub->AddOption<BoolOption<bool>>("Transparent", nullptr, &g_UiManager->m_HeaderGradientTransparent, BoolDisplay::YesNo);
				sub->AddOption<BoolOption<bool>>("Flip", nullptr, &g_UiManager->m_HeaderGradientFlip, BoolDisplay::YesNo);

				sub->AddOption<NumberOption<std::uint8_t>>("R1", nullptr, &g_UiManager->m_HeaderGradientColorLeft.r, '\0', static_cast<std::uint8_t>(255));
				sub->AddOption<NumberOption<std::uint8_t>>("G1", nullptr, &g_UiManager->m_HeaderGradientColorLeft.g, '\0', static_cast<std::uint8_t>(255));
				sub->AddOption<NumberOption<std::uint8_t>>("B1", nullptr, &g_UiManager->m_HeaderGradientColorLeft.b, '\0', static_cast<std::uint8_t>(255));
				sub->AddOption<NumberOption<std::uint8_t>>("A1", nullptr, &g_UiManager->m_HeaderGradientColorLeft.a, '\0', static_cast<std::uint8_t>(255));
				sub->AddOption<NumberOption<std::uint8_t>>("R2", nullptr, &g_UiManager->m_HeaderGradientColorRight.r, '\0', static_cast<std::uint8_t>(255));
				sub->AddOption<NumberOption<std::uint8_t>>("G2", nullptr, &g_UiManager->m_HeaderGradientColorRight.g, '\0', static_cast<std::uint8_t>(255));
				sub->AddOption<NumberOption<std::uint8_t>>("B2", nullptr, &g_UiManager->m_HeaderGradientColorRight.b, '\0', static_cast<std::uint8_t>(255));
				sub->AddOption<NumberOption<std::uint8_t>>("A2", nullptr, &g_UiManager->m_HeaderGradientColorRight.a, '\0', static_cast<std::uint8_t>(255));
			});

		g_UiManager->AddSubmenu<RegularSubmenu>("Header Animated", SubmenuSettingsHeaderAnimatedBackground, [](RegularSubmenu* sub) {
			sub->AddOption<NumberOption<int>>("Frame Delay", "The delay between each frame in ms", &g_UiManager->m_AnimatedHeaderTimerDelay, '\0', INT_MAX);
			sub->AddOption<NumberOption<int>>("Frame Count", "How many frames to render (inclusive)", &g_UiManager->m_AnimatedHeaderFrameCount, '\0', INT_MAX);
			});

		g_UiManager->AddSubmenu<RegularSubmenu>("Header Text", SubmenuSettingsHeaderText, [](RegularSubmenu* sub)
			{
				sub->AddOption<BoolOption<bool>>("Enable", nullptr, &g_UiManager->m_HeaderText, BoolDisplay::OnOff);
				sub->AddOption<NumberOption<float>>("Size", nullptr, &g_UiManager->m_HeaderTextSize, 0.1f, 2.f, 0.01f, 2);
				sub->AddOption<NumberOption<std::uint8_t>>("R", nullptr, &g_UiManager->m_HeaderTextColor.r, '\0', static_cast<std::uint8_t>(255));
				sub->AddOption<NumberOption<std::uint8_t>>("G", nullptr, &g_UiManager->m_HeaderTextColor.g, '\0', static_cast<std::uint8_t>(255));
				sub->AddOption<NumberOption<std::uint8_t>>("B", nullptr, &g_UiManager->m_HeaderTextColor.b, '\0', static_cast<std::uint8_t>(255));
				sub->AddOption<NumberOption<std::uint8_t>>("A", nullptr, &g_UiManager->m_HeaderTextColor.a, '\0', static_cast<std::uint8_t>(255));
			});

		g_UiManager->AddSubmenu<RegularSubmenu>("Description", SubmenuSettingsDescription, [](RegularSubmenu* sub)
			{
				sub->AddOption<NumberOption<float>>("Padding", "Padding before the description rect.", &g_UiManager->m_DescriptionHeightPadding, 0.01f, 1.f, 0.001f,
					3);
				sub->AddOption<NumberOption<float>>("Height", "Size of the description rect.", &g_UiManager->m_DescriptionHeight, 0.01f, 1.f, 0.001f, 3);
				sub->AddOption<NumberOption<float>>("Text Size", "Size of the description text.", &g_UiManager->m_DescriptionTextSize, 0.1f, 2.f, 0.01f, 2);
			});

		g_UiManager->AddSubmenu<RegularSubmenu>("Input", SubmenuSettingsInput, [](RegularSubmenu* sub)
			{
				sub->AddOption<NumberOption<std::int32_t>>("Open Delay", nullptr, &g_UiManager->m_OpenDelay, 10, 1000, 10, 0);
				sub->AddOption<NumberOption<std::int32_t>>("Back Delay", nullptr, &g_UiManager->m_BackDelay, 10, 1000, 10, 0);
				sub->AddOption<NumberOption<std::int32_t>>("Enter Delay", nullptr, &g_UiManager->m_EnterDelay, 10, 1000, 10, 0);
				sub->AddOption<NumberOption<std::int32_t>>("Vertical Delay", nullptr, &g_UiManager->m_VerticalDelay, 10, 1000, 10, 0);
				sub->AddOption<NumberOption<std::int32_t>>("Horizontal Delay", nullptr, &g_UiManager->m_HorizontalDelay, 10, 1000, 10, 0);
			});

		g_UiManager->AddSubmenu<RegularSubmenu>("Players", SubmenuPlayerList, [](RegularSubmenu* sub)
			{
				for (std::uint32_t i = 0; i < 32; ++i)
				{
					if (auto ped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i))
					{
						sub->AddOption<SubOption>(PLAYER::GET_PLAYER_NAME(i), nullptr, SubmenuSelectedPlayer, [=]
							{
								g_SelectedPlayer = i;
							});
					}
				}
			});

		g_UiManager->AddSubmenu<PlayerSubmenu>(&g_SelectedPlayer, SubmenuSelectedPlayer, [](PlayerSubmenu* sub)
			{
				sub->AddOption<RegularOption>("Get player ID", nullptr, [] {
					Player p = PLAYER::PLAYER_ID();
					g_Logger->Info(std::to_string(p).c_str());
					p = PLAYER::PLAYER_PED_ID();
					g_Logger->Info(std::to_string(p).c_str());
					});
			});
	}

	void MainScript::Destroy()
	{
		g_UiManager.reset();
	}

	void MainScript::Tick()
	{
		g_UiManager->OnTick();
	}
}
