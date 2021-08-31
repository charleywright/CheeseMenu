#include "UI/UIManager.hpp"

#pragma once

namespace Big {
	class Config {
	public:
		Config();
		void Save();

		std::atomic_bool m_LockMouse = false;
		std::atomic_bool m_LogWindow = false;

		// General
		float m_PosX = 0.01f;
		float m_PosY = 0.2f;
		float m_Width = 0.2f;
		std::size_t m_OptionsPerPage = 11;
		bool m_Sounds = true;
		std::size_t m_FeatureTickSize = 10;

		// Input
		std::int32_t m_OpenDelay = 120;
		std::int32_t m_BackDelay = 120;
		std::int32_t m_EnterDelay = 120;
		std::int32_t m_VerticalDelay = 120;
		std::int32_t m_HorizontalDelay = 120;

		// Header
		float m_HeaderHeight = 0.1f;
		bool m_HeaderText = false;
		float m_HeaderTextSize = 1.f;
		UserInterface::Font m_HeaderFont = UserInterface::Font::HouseScript;
		Color m_HeaderBackgroundColor{ 2, 130, 53, 255 };
		Color m_HeaderTextColor{ 255, 255, 255, 255 };
		UserInterface::HeaderType m_HeaderType = UserInterface::HeaderType::Image;

		bool m_HeaderGradientTransparent = false;
		bool m_HeaderGradientFlip = false;
		float m_HeaderGradientStretch = 0.f;
		float m_HeaderGradientFiller = 0.f;
		Color m_HeaderGradientColorLeft{ 0, 186, 255, 255 };
		Color m_HeaderGradientColorRight{ 252, 0, 255, 255 };

		std::string m_HeaderFilename = "header.ytd";

		int m_AnimatedHeaderCurrentImage = 1;
		int m_AnimatedHeaderTimerDelay = 10;
		int m_AnimatedHeaderFrameCount = 39;
		Timer m_AnimatedHeaderTimer = Timer(10ms);

		// Scrollbar
		float m_ScrollBarWidth = 0.01f;
		float m_ScrollBarOffset = 0.003f;
		float m_ScrollBarSpriteSize = 0.015f;
		Color m_ScrollBarBackgroundColor{ 0, 0, 0, 220 };
		Color m_ScrollBarForegroundColor{ 255, 255, 255, 255 };
		Color m_ScrollBarEndColor{ 0, 0, 0, 255 };

		// Seperator
		bool m_SeperatorEnabled = true;
		float m_SeperatorHeight = 0.003f;
		Color m_SeperatorColorLeft{ 71, 28, 236, 255 };
		Color m_SeperatorColorMiddle{ 222, 12, 99, 255 };
		Color m_SeperatorColorRight{ 163, 18, 194, 255 };

		// Submenu bar
		float m_SubmenuBarHeight = 0.025f;
		float m_SubmenuBarTextSize = 0.28f;
		UserInterface::Font m_SubmenuBarFont = UserInterface::Font::ChaletLondon;
		float m_SubmenuBarPadding = 2.1f;
		Color m_SubmenuBarBackgroundColor{ 0, 0, 0, 255 };
		Color m_SubmenuBarTextColor{ 255, 255, 255, 255 };

		// Options
		float m_OptionHeight = 0.03f;
		float m_OptionTextSize = 0.25f;
		UserInterface::Font m_OptionFont = UserInterface::Font::ChaletLondon;
		float m_OptionPadding = 2.1f;
		Color m_OptionSelectedTextColor{ 0, 0, 0, 255 };
		Color m_OptionUnselectedTextColor{ 255, 255, 255, 255 };
		Color m_OptionSelectedBackgroundColor{ 255, 255, 255, 255 };
		Color m_OptionUnselectedBackgroundColor{ 0, 0, 0, 220 };

		// Footer
		float m_FooterHeight = 0.03f;
		float m_FooterSpriteSize = 0.025f;
		Color m_FooterBackgroundColor{ 0, 0, 0, 255 };
		Color m_FooterSpriteColor{ 255, 255, 255, 255 };

		// Description
		float m_DescriptionHeightPadding = 0.01f;
		float m_DescriptionHeight = 0.03f;
		float m_DescriptionTextSize = 0.25f;
		UserInterface::Font m_DescriptionFont = UserInterface::Font::ChaletLondon;
		Color m_DescriptionBackgroundColor{ 0, 0, 0, 220 };
		Color m_DescriptionTextColor{ 255, 255, 255, 255 };
		float m_DescriptionSpriteSize = 0.025f;
		float m_DescriptionPadding = 2.1f;
		Color m_DescriptionSpriteColor{ 255, 255, 255, 255 };

	private:
		std::string path();
		bool FileExists(std::string path);
	};

	inline std::unique_ptr<Config> g_Config;
}