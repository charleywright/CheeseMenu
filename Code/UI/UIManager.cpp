#include "UIManager.hpp"
#include "../Timer.hpp"
#include "../Natives.hpp"
#include <Shlwapi.h>

namespace Big::UserInterface
{
	UIManager::UIManager() {}

	void UIManager::OnTick()
	{
		std::lock_guard lock(m_Mutex);

		if (g_UiManager->m_Opened && g_Config->m_LockMouse)
		{
			PAD::DISABLE_ALL_CONTROL_ACTIONS(0);
		}

		CheckForInput();
		HandleInput();

		if (m_Opened)
		{
			PAD::DISABLE_CONTROL_ACTION(0, 27, true); // Disable phone
			g_Config->m_AnimatedHeaderTimer.SetDelay(std::chrono::milliseconds(g_Config->m_AnimatedHeaderTimerDelay));
			m_DrawBaseY = g_Config->m_PosY;
			DrawHeader();
			if (!m_SubmenuStack.empty())
			{
				auto sub = m_SubmenuStack.top();
				sub->Reset();
				sub->Execute();

				DrawSubmenuBar(sub);
				if (g_Config->m_SeperatorEnabled) DrawSeperator();
				DrawScrollBar(sub);
				if (sub->GetNumOptions() != 0)
				{
					std::size_t startPoint = 0;
					std::size_t endPoint = sub->GetNumOptions() > g_Config->m_OptionsPerPage ? g_Config->m_OptionsPerPage : sub->GetNumOptions();
					if (sub->GetNumOptions() > g_Config->m_OptionsPerPage && sub->GetSelectedOption() >= g_Config->m_OptionsPerPage)
					{
						startPoint = sub->GetSelectedOption() - g_Config->m_OptionsPerPage + 1;
						endPoint = sub->GetSelectedOption() + 1;
					}

					for (std::size_t i = startPoint, j = 0; i < endPoint; ++i, ++j)
					{
						DrawOption(sub->GetOption(i), i == sub->GetSelectedOption());
					}
				}
				if (g_Config->m_SeperatorEnabled) DrawSeperator();
			}

			DrawFooter();
			DrawDescription();
		}
	}

	void UIManager::CheckForInput()
	{
		ResetInput();

		m_OpenKeyPressed = IsKeyPressed(VK_INSERT);
		m_BackKeyPressed = IsKeyPressed(VK_BACK);
		m_EnterKeyPressed = IsKeyPressed(VK_RETURN);
		m_UpKeyPressed = IsKeyPressed(VK_UP);
		m_DownKeyPressed = IsKeyPressed(VK_DOWN);
		m_LeftKeyPressed = IsKeyPressed(VK_LEFT);
		m_RightKeyPressed = IsKeyPressed(VK_RIGHT);
	}

	void UIManager::HandleInput()
	{
		static auto openTicker = GetTickCount();
		if (m_OpenKeyPressed && GetTickCount() - openTicker >= static_cast<std::uint32_t>(g_Config->m_OpenDelay))
		{
			openTicker = GetTickCount();
			m_Opened ^= true;

			if (g_Config->m_Sounds)
				AUDIO::PLAY_SOUND_FRONTEND(-1, m_Opened ? "SELECT" : "BACK", "HUD_FRONTEND_DEFAULT_SOUNDSET", false);
		}

		static Timer backTimer(0ms);
		backTimer.SetDelay(std::chrono::milliseconds(g_Config->m_BackDelay));
		if (m_Opened && m_BackKeyPressed && backTimer.Update())
		{
			if (g_Config->m_Sounds)
				AUDIO::PLAY_SOUND_FRONTEND(-1, "BACK", "HUD_FRONTEND_DEFAULT_SOUNDSET", false);

			if (m_SubmenuStack.size() > 1)
			{
				m_SubmenuStack.pop();
			}
		}

		if (m_Opened && !m_SubmenuStack.empty())
		{
			auto sub = m_SubmenuStack.top();

			static Timer enterTimer(0ms);
			enterTimer.SetDelay(std::chrono::milliseconds(g_Config->m_EnterDelay));
			if (m_EnterKeyPressed && sub->GetNumOptions() != 0 && enterTimer.Update())
			{
				if (g_Config->m_Sounds)
					AUDIO::PLAY_SOUND_FRONTEND(-1, "SELECT", "HUD_FRONTEND_DEFAULT_SOUNDSET", false);

				if (auto opt = sub->GetOption(sub->GetSelectedOption()))
				{
					opt->HandleAction(OptionAction::EnterPress);
				}
			}

			static Timer upTimer(0ms);
			upTimer.SetDelay(std::chrono::milliseconds(g_Config->m_VerticalDelay));
			if (m_UpKeyPressed && sub->GetNumOptions() != 0 && upTimer.Update())
			{
				if (g_Config->m_Sounds)
					AUDIO::PLAY_SOUND_FRONTEND(-1, "NAV_UP_DOWN", "HUD_FRONTEND_DEFAULT_SOUNDSET", false);

				sub->ScrollBackward();
			}

			static Timer downTimer(0ms);
			downTimer.SetDelay(std::chrono::milliseconds(g_Config->m_VerticalDelay));
			if (m_DownKeyPressed && sub->GetNumOptions() != 0 && downTimer.Update())
			{
				if (g_Config->m_Sounds)
					AUDIO::PLAY_SOUND_FRONTEND(-1, "NAV_UP_DOWN", "HUD_FRONTEND_DEFAULT_SOUNDSET", false);

				sub->ScrollForward();
			}

			static Timer leftTimer(0ms);
			leftTimer.SetDelay(std::chrono::milliseconds(g_Config->m_HorizontalDelay));
			if (m_LeftKeyPressed && sub->GetNumOptions() != 0 && leftTimer.Update())
			{
				if (g_Config->m_Sounds)
					AUDIO::PLAY_SOUND_FRONTEND(-1, "NAV_LEFT_RIGHT", "HUD_FRONTEND_DEFAULT_SOUNDSET", false);

				if (auto opt = sub->GetOption(sub->GetSelectedOption()))
				{
					opt->HandleAction(OptionAction::LeftPress);
				}
			}

			static Timer rightTimer(0ms);
			rightTimer.SetDelay(std::chrono::milliseconds(g_Config->m_HorizontalDelay));
			if (m_RightKeyPressed && sub->GetNumOptions() != 0 && rightTimer.Update())
			{
				if (g_Config->m_Sounds)
					AUDIO::PLAY_SOUND_FRONTEND(-1, "NAV_LEFT_RIGHT", "HUD_FRONTEND_DEFAULT_SOUNDSET", false);

				if (auto opt = sub->GetOption(sub->GetSelectedOption()))
				{
					opt->HandleAction(OptionAction::RightPress);
				}
			}
		}
	}

	void UIManager::ResetInput()
	{
		m_OpenKeyPressed = false;
		m_BackKeyPressed = false;
		m_EnterKeyPressed = false;
		m_UpKeyPressed = false;
		m_DownKeyPressed = false;
		m_LeftKeyPressed = false;
		m_RightKeyPressed = false;
	}

	void UIManager::DrawHeader()
	{
		switch (g_Config->m_HeaderType)
		{
		case HeaderType::Static:
			DrawRect(
				g_Config->m_PosX + (g_Config->m_Width * 0.5f) + g_Config->m_ScrollBarWidth + g_Config->m_ScrollBarOffset,
				m_DrawBaseY + (g_Config->m_HeaderHeight / 2.f), g_Config->m_Width,
				g_Config->m_HeaderHeight,
				g_Config->m_HeaderBackgroundColor);
			break;
		case HeaderType::Gradient:
			for (std::size_t i = 0; i < (g_Config->m_HeaderGradientTransparent ? 1 : 20); ++i)
			{
				DrawSprite(
					"aircraft_dials",
					"aircraft_dials_g0",
					g_Config->m_PosX - (g_Config->m_HeaderGradientStretch / 2.f) + (g_Config->m_Width * 0.5f) + g_Config->m_ScrollBarWidth + g_Config->m_ScrollBarOffset,
					m_DrawBaseY + (g_Config->m_HeaderHeight / 2.f),
					g_Config->m_Width + g_Config->m_HeaderGradientStretch + g_Config->m_HeaderGradientFiller,
					g_Config->m_HeaderHeight,
					g_Config->m_HeaderGradientColorRight,
					g_Config->m_HeaderGradientFlip ? 0.f : 180.f);
				DrawSprite(
					"aircraft_dials",
					"aircraft_dials_g0",
					g_Config->m_PosX + (g_Config->m_HeaderGradientStretch / 2.f) + (g_Config->m_Width * 0.5f) + g_Config->m_ScrollBarWidth + g_Config->m_ScrollBarOffset,
					m_DrawBaseY + (g_Config->m_HeaderHeight / 2.f),
					g_Config->m_Width + g_Config->m_HeaderGradientStretch + g_Config->m_HeaderGradientFiller,
					g_Config->m_HeaderHeight,
					g_Config->m_HeaderGradientColorLeft,
					g_Config->m_HeaderGradientFlip ? 180.f : 0.f);
			}
			break;
		case HeaderType::Image:
			LoadHeader(g_Config->m_HeaderFilename);
			DrawSprite(
				g_Config->m_HeaderFilename.substr(0, g_Config->m_HeaderFilename.find(".")).c_str(),
				"static",
				g_Config->m_PosX + (g_Config->m_Width * 0.5f) + g_Config->m_ScrollBarWidth + g_Config->m_ScrollBarOffset,
				m_DrawBaseY + (g_Config->m_HeaderHeight / 2.f) + 0.005f, // Doesn't line up without offset
				g_Config->m_Width,
				g_Config->m_HeaderHeight,
				Color{ 255, 255, 255, 255 },
				0.f);
			break;
		case HeaderType::Animated:
			LoadHeader(g_Config->m_HeaderFilename);
			if (g_Config->m_AnimatedHeaderTimer.Update()) {
				g_Config->m_AnimatedHeaderCurrentImage++;
				if (g_Config->m_AnimatedHeaderCurrentImage > g_Config->m_AnimatedHeaderFrameCount)
					g_Config->m_AnimatedHeaderCurrentImage = 1;
			}

			std::string imgName = std::to_string(g_Config->m_AnimatedHeaderCurrentImage);
			DrawSprite(
				g_Config->m_HeaderFilename.substr(0, g_Config->m_HeaderFilename.find(".")).c_str(),
				imgName.c_str(),
				g_Config->m_PosX + (g_Config->m_Width * 0.5f) + g_Config->m_ScrollBarWidth + g_Config->m_ScrollBarOffset,
				m_DrawBaseY + (g_Config->m_HeaderHeight / 2.f) + 0.005f, // Doesn't line up without offset
				g_Config->m_Width,
				g_Config->m_HeaderHeight,
				Color{ 255, 255, 255, 255 },
				0.f);
			break;
		}

		if (g_Config->m_HeaderText)
		{
			DrawCenteredText(
				BIGBASE_NAME,
				g_Config->m_PosX + (g_Config->m_Width * 0.5f) + g_Config->m_ScrollBarWidth + g_Config->m_ScrollBarOffset,
				m_DrawBaseY + (g_Config->m_HeaderHeight / 2.f) - (GetTextHeight(g_Config->m_HeaderFont, g_Config->m_HeaderTextSize) / 2.f),
				g_Config->m_HeaderTextSize,
				g_Config->m_HeaderFont,
				g_Config->m_HeaderTextColor,
				false, true);
		}

		m_DrawBaseY += g_Config->m_HeaderHeight;
	}

	void UIManager::LoadHeader(std::string headerName) {
		static std::uint32_t* (*FileRegister)(int*, const char*, bool, const char*, bool) = Signature("48 89 5C 24 ? 48 89 6C 24 ? 48 89 7C 24 ? 41 54 41 56 41 57 48 83 EC 50 48 8B EA 4C 8B FA 48 8B D9 4D 85 C9").Scan().As<decltype(FileRegister)>();
		std::string delim = "\\";
		std::string fullPath = GetModulePath(g_Module) + delim + headerName;
		if (FileExists(fullPath))
		{
			int textureID;
			FileRegister(&textureID, fullPath.c_str(), true, headerName.c_str(), false);
			if (textureID == -1)
			{
				g_Logger->Error("Failed to register %s", fullPath.c_str());
			}
		}
	}

	bool UIManager::FileExists(const std::string& fileName)
	{
		struct stat buffer;
		return (stat(fileName.c_str(), &buffer) == 0);
	}

	const std::string UIManager::GetModulePath(HMODULE module)
	{
		std::string path;
		char buffer[MAX_PATH];
		GetModuleFileNameA(module, buffer, MAX_PATH);
		PathRemoveFileSpecA(buffer);
		path = buffer;
		return path;
	}

	void UIManager::DrawScrollBar(AbstractSubmenu* sub) {
		Vector2 sprite_size = GetSpriteScale(g_Config->m_ScrollBarSpriteSize);
		size_t num_options = sub->GetNumOptions() > g_Config->m_OptionsPerPage ? g_Config->m_OptionsPerPage : sub->GetNumOptions();
		DrawRect(
			g_Config->m_PosX + g_Config->m_ScrollBarWidth * 0.5f,
			m_DrawBaseY - g_Config->m_ScrollBarWidth,
			g_Config->m_ScrollBarWidth, g_Config->m_ScrollBarWidth * 2,
			g_Config->m_SubmenuBarBackgroundColor);
		DrawSprite(
			"commonmenu",
			"arrowright",
			g_Config->m_PosX + g_Config->m_ScrollBarWidth * 0.5f,
			m_DrawBaseY - g_Config->m_ScrollBarWidth,
			sprite_size.x,
			sprite_size.y,
			g_Config->m_FooterSpriteColor,
			270.f);
		DrawRect(
			g_Config->m_PosX + g_Config->m_ScrollBarWidth * 0.5f,
			m_DrawBaseY + (g_Config->m_OptionHeight * num_options * 0.5f),
			g_Config->m_ScrollBarWidth,
			g_Config->m_OptionHeight * num_options,
			g_Config->m_ScrollBarBackgroundColor
		);
		if (num_options != 0) {
			DrawRect(
				g_Config->m_PosX + g_Config->m_ScrollBarWidth * 0.5f,
				m_DrawBaseY + (g_Config->m_OptionHeight * 0.5f) + (g_Config->m_OptionHeight * (sub->GetSelectedOption() >= g_Config->m_OptionsPerPage ? g_Config->m_OptionsPerPage - 1 : sub->GetSelectedOption())),
				g_Config->m_ScrollBarWidth - 0.0025f,
				g_Config->m_OptionHeight - 0.005f,
				g_Config->m_ScrollBarForegroundColor
			);
		}
		DrawRect(
			g_Config->m_PosX + g_Config->m_ScrollBarWidth * 0.5f,
			m_DrawBaseY + g_Config->m_ScrollBarWidth + (g_Config->m_OptionHeight * num_options),
			g_Config->m_ScrollBarWidth, g_Config->m_ScrollBarWidth * 2,
			g_Config->m_SubmenuBarBackgroundColor);
		DrawSprite(
			"commonmenu",
			"arrowright",
			g_Config->m_PosX + g_Config->m_ScrollBarWidth * 0.5f,
			m_DrawBaseY + g_Config->m_ScrollBarWidth + (g_Config->m_OptionHeight * num_options),
			sprite_size.x,
			sprite_size.y,
			g_Config->m_FooterSpriteColor,
			90.f);
	}

	void UIManager::DrawSubmenuBar(AbstractSubmenu* sub)
	{
		char leftText[64] = {};
		std::strncpy(&leftText[0], sub->GetName(), sizeof(leftText) - 1);
		std::transform(std::begin(leftText), std::end(leftText), std::begin(leftText), [](char c) { return static_cast<char>(toupper(c)); });

		char rightText[32] = {};
		std::snprintf(rightText, sizeof(rightText) - 1, "%zu / %zu", sub->GetSelectedOption() + 1, sub->GetNumOptions());

		DrawRect(
			g_Config->m_PosX + (g_Config->m_Width * 0.5f) + g_Config->m_ScrollBarWidth + g_Config->m_ScrollBarOffset,
			m_DrawBaseY + (g_Config->m_SubmenuBarHeight / 2.f),
			g_Config->m_Width, g_Config->m_SubmenuBarHeight,
			g_Config->m_SubmenuBarBackgroundColor);
		DrawLeftText(
			&leftText[0],
			g_Config->m_PosX - (g_Config->m_Width / g_Config->m_SubmenuBarPadding) + (g_Config->m_Width * 0.5f) + g_Config->m_ScrollBarWidth + g_Config->m_ScrollBarOffset,
			m_DrawBaseY + (g_Config->m_SubmenuBarHeight / 2.f) - (GetTextHeight(g_Config->m_SubmenuBarFont, g_Config->m_SubmenuBarTextSize) / 1.5f),
			g_Config->m_SubmenuBarTextSize, g_Config->m_SubmenuBarFont,
			g_Config->m_SubmenuBarTextColor,
			false, true);
		DrawRightText(
			&rightText[0],
			g_Config->m_PosX + (g_Config->m_Width / g_Config->m_SubmenuBarPadding) + (g_Config->m_Width * 0.5f) + g_Config->m_ScrollBarWidth + g_Config->m_ScrollBarOffset,
			m_DrawBaseY + (g_Config->m_SubmenuBarHeight / 2.f) - (GetTextHeight(g_Config->m_SubmenuBarFont, g_Config->m_SubmenuBarTextSize) / 1.5f),
			g_Config->m_SubmenuBarTextSize, g_Config->m_SubmenuBarFont,
			g_Config->m_SubmenuBarTextColor,
			false, true);

		m_DrawBaseY += g_Config->m_SubmenuBarHeight;
	}

	void UIManager::DrawSeperator() {
		for (short i = 0; i < 20; i++) {
			DrawSprite(
				"aircraft_dials",
				"aircraft_dials_g0",
				g_Config->m_PosX + (g_Config->m_Width * 0.25f) + g_Config->m_ScrollBarWidth + g_Config->m_ScrollBarOffset,
				m_DrawBaseY + g_Config->m_SeperatorHeight * 0.5f,
				g_Config->m_Width * 0.5f,
				g_Config->m_SeperatorHeight,
				g_Config->m_SeperatorColorLeft,
				0.f);
			DrawSprite(
				"aircraft_dials",
				"aircraft_dials_g0",
				g_Config->m_PosX + (g_Config->m_Width * 0.25f) + g_Config->m_ScrollBarWidth + g_Config->m_ScrollBarOffset,
				m_DrawBaseY + g_Config->m_SeperatorHeight * 0.5f,
				g_Config->m_Width * 0.5f,
				g_Config->m_SeperatorHeight,
				g_Config->m_SeperatorColorMiddle,
				180.f);
			DrawSprite(
				"aircraft_dials",
				"aircraft_dials_g0",
				g_Config->m_PosX + (g_Config->m_Width * 0.75f) + g_Config->m_ScrollBarWidth + g_Config->m_ScrollBarOffset,
				m_DrawBaseY + g_Config->m_SeperatorHeight * 0.5f,
				g_Config->m_Width * 0.5f,
				g_Config->m_SeperatorHeight,
				g_Config->m_SeperatorColorMiddle,
				0.f);
			DrawSprite(
				"aircraft_dials",
				"aircraft_dials_g0",
				g_Config->m_PosX + (g_Config->m_Width * 0.75f) + g_Config->m_ScrollBarWidth + g_Config->m_ScrollBarOffset,
				m_DrawBaseY + g_Config->m_SeperatorHeight * 0.5f,
				g_Config->m_Width * 0.5f,
				g_Config->m_SeperatorHeight,
				g_Config->m_SeperatorColorRight,
				180.f);
		}
		m_DrawBaseY += g_Config->m_SeperatorHeight;
	}

	void UIManager::DrawOption(AbstractOption* opt, bool selected)
	{
		DrawRect(
			g_Config->m_PosX + (g_Config->m_Width * 0.5f) + g_Config->m_ScrollBarWidth + g_Config->m_ScrollBarOffset,
			m_DrawBaseY + (g_Config->m_OptionHeight / 2.f),
			g_Config->m_Width,
			g_Config->m_OptionHeight,
			selected ? g_Config->m_OptionSelectedBackgroundColor : g_Config->m_OptionUnselectedBackgroundColor);
		DrawLeftText(
			opt->GetLeftText(),
			g_Config->m_PosX - (g_Config->m_Width / g_Config->m_OptionPadding) + (g_Config->m_Width * 0.5f) + g_Config->m_ScrollBarWidth + g_Config->m_ScrollBarOffset,
			m_DrawBaseY + (g_Config->m_OptionHeight / 2.f) - (GetTextHeight(g_Config->m_OptionFont, g_Config->m_OptionTextSize) / 1.5f),
			g_Config->m_OptionTextSize,
			g_Config->m_OptionFont,
			selected ? g_Config->m_OptionSelectedTextColor : g_Config->m_OptionUnselectedTextColor,
			false, false);
		DrawRightText(
			opt->GetRightText(),
			g_Config->m_PosX + (g_Config->m_Width / g_Config->m_OptionPadding) + (g_Config->m_Width * 0.5f) + g_Config->m_ScrollBarWidth + g_Config->m_ScrollBarOffset,
			m_DrawBaseY + (g_Config->m_OptionHeight / 2.f) - (GetTextHeight(g_Config->m_OptionFont, g_Config->m_OptionTextSize) / 1.5f),
			g_Config->m_OptionTextSize,
			g_Config->m_OptionFont,
			selected ? g_Config->m_OptionSelectedTextColor : g_Config->m_OptionUnselectedTextColor,
			false, false);

		if (opt->GetFlag(OptionFlag::Enterable))
		{
			DrawRightText(
				">",
				g_Config->m_PosX + (g_Config->m_Width / g_Config->m_OptionPadding) + (g_Config->m_Width * 0.5f) + g_Config->m_ScrollBarWidth + g_Config->m_ScrollBarOffset,
				m_DrawBaseY + (g_Config->m_OptionHeight / 2.f) - (GetTextHeight(Font::Monospace, g_Config->m_OptionTextSize) / 1.725f),
				g_Config->m_OptionTextSize,
				Font::Monospace,
				selected ? g_Config->m_OptionSelectedTextColor : g_Config->m_OptionUnselectedTextColor,
				false, false);
		}

		m_DrawBaseY += g_Config->m_OptionHeight;
	}

	void UIManager::DrawFooter()
	{
		DrawRect(
			g_Config->m_PosX + (g_Config->m_Width * 0.5f) + g_Config->m_ScrollBarWidth + g_Config->m_ScrollBarOffset,
			m_DrawBaseY + (g_Config->m_FooterHeight / 2.f),
			g_Config->m_Width,
			g_Config->m_FooterHeight,
			g_Config->m_FooterBackgroundColor);

		float size = g_Config->m_FooterSpriteSize;
		float rotation = 0.f;
		const char* texture = "shop_arrows_upanddown";

		if (!m_SubmenuStack.empty())
		{
			texture = "arrowright";
			size *= 0.8f;
			rotation = m_SubmenuStack.top()->GetSelectedOption() == 0 ? 90.f : 270.f;
		}

		auto sizee = GetSpriteScale(size);

		DrawSprite(
			"commonmenu",
			texture,
			g_Config->m_PosX + (g_Config->m_Width * 0.5f) + g_Config->m_ScrollBarWidth + g_Config->m_ScrollBarOffset,
			m_DrawBaseY + (g_Config->m_FooterHeight / 2.f),
			sizee.x,
			sizee.y,
			g_Config->m_FooterSpriteColor,
			rotation);

		m_DrawBaseY += g_Config->m_FooterHeight;
	}

	void UIManager::DrawDescription()
	{
		const char* description{};

		if (!m_SubmenuStack.empty())
		{
			auto sub = m_SubmenuStack.top();
			if (sub->GetNumOptions())
			{
				if (auto opt = sub->GetOption(sub->GetSelectedOption()))
				{
					description = opt->GetDescription();
				}
			}
		}

		if (!description || !*description)
			return;

		m_DrawBaseY += g_Config->m_DescriptionHeightPadding;

		DrawRect(
			g_Config->m_PosX + (g_Config->m_Width * 0.5f) + g_Config->m_ScrollBarWidth + g_Config->m_ScrollBarOffset,
			m_DrawBaseY + (g_Config->m_DescriptionHeight / 2.f),
			g_Config->m_Width,
			g_Config->m_DescriptionHeight,
			g_Config->m_DescriptionBackgroundColor);

		auto spriteSize = GetSpriteScale(g_Config->m_DescriptionSpriteSize);
		DrawSprite(
			"shared", "info_icon_32",
			g_Config->m_PosX - (g_Config->m_Width / g_Config->m_DescriptionPadding) + (spriteSize.x / 2.f) + (g_Config->m_Width * 0.5f) + g_Config->m_ScrollBarWidth + g_Config->m_ScrollBarOffset,
			m_DrawBaseY + (g_Config->m_DescriptionHeight / 2.f),
			spriteSize.x,
			spriteSize.y,
			g_Config->m_DescriptionSpriteColor,
			0.f
		);

		DrawLeftText(
			description,
			g_Config->m_PosX - (g_Config->m_Width / g_Config->m_DescriptionPadding) + (spriteSize.x * 1.15f) + (g_Config->m_Width * 0.5f) + g_Config->m_ScrollBarWidth + g_Config->m_ScrollBarOffset,
			m_DrawBaseY + (g_Config->m_DescriptionHeight / 2.f) - (GetTextHeight(g_Config->m_DescriptionFont, g_Config->m_DescriptionTextSize) / 1.35f),
			g_Config->m_DescriptionTextSize,
			g_Config->m_DescriptionFont,
			g_Config->m_DescriptionTextColor,
			false, false
		);

		m_DrawBaseY += g_Config->m_DescriptionHeight;
	}

	void UIManager::DrawRect(float x, float y, float width, float height, Color color)
	{
		GRAPHICS::DRAW_RECT(x, y, width, height, color.r, color.g, color.b, color.a, 0);
	}

	void UIManager::DrawSprite(const char* dict, const char* texture, float x, float y, float width, float height, Color color, float rotation)
	{
		if (GRAPHICS::HAS_STREAMED_TEXTURE_DICT_LOADED(dict))
		{
			GRAPHICS::DRAW_SPRITE(dict, texture, x, y, width, height, rotation, color.r, color.g, color.b, color.a, 0);
		}
		else
		{
			GRAPHICS::REQUEST_STREAMED_TEXTURE_DICT(dict, false);
		}
	}

	void UIManager::DrawLeftText(const char* text, float x, float y, float size, Font font, Color color, bool outline, bool shadow)
	{
		HUD::SET_TEXT_SCALE(size, size);
		HUD::SET_TEXT_FONT(static_cast<int>(font));
		HUD::SET_TEXT_COLOUR(color.r, color.g, color.b, color.a);
		if (outline)
			HUD::SET_TEXT_OUTLINE();
		if (shadow)
			HUD::SET_TEXT_DROP_SHADOW();

		HUD::BEGIN_TEXT_COMMAND_DISPLAY_TEXT("STRING");
		HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(text);
		HUD::END_TEXT_COMMAND_DISPLAY_TEXT(x, y, 0);
	}

	void UIManager::DrawCenteredText(const char* text, float x, float y, float size, Font font, Color color, bool outline, bool shadow)
	{
		HUD::SET_TEXT_CENTRE(true);
		DrawLeftText(text, x, y, size, font, color, outline, shadow);
	}

	void UIManager::DrawRightText(const char* text, float x, float y, float size, Font font, Color color, bool outline, bool shadow)
	{
		HUD::SET_TEXT_WRAP(0.f, x);
		HUD::SET_TEXT_RIGHT_JUSTIFY(true);
		DrawLeftText(text, x, y, size, font, color, outline, shadow);
	}

	float UIManager::GetTextHeight(Font font, float size)
	{
		return HUD::_GET_TEXT_SCALE_HEIGHT(size, static_cast<int>(font));
	}

	Vector2 UIManager::GetSpriteScale(float size)
	{
		int x;
		int y;
		GRAPHICS::_GET_ACTIVE_SCREEN_RESOLUTION(&x, &y);

		return { (static_cast<float>(y) / static_cast<float>(x)) * size, size };
	}

	bool UIManager::IsMouseLocked()
	{
		return m_Opened && m_MouseLocked;
	}

	Vector2 UIManager::GetMousePos()
	{
		POINT point;
		GetCursorPos(&point);

		return Vector2{ static_cast<float>(point.x), static_cast<float>(point.y) };
	}
}
