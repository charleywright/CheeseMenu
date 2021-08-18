#include "Config.hpp"
#include "Lists.hpp"
#include <filesystem>
#include <shlwapi.h>
#include "JSON/json.hpp"
using json = nlohmann::json;

namespace Big
{
	Config::Config()
	{
		if (this->FileExists(this->path()))
		{
			std::string raw_config;
			std::getline(std::ifstream(this->path()), raw_config, '\0');
			json j = json::parse(raw_config);
			// General
			this->m_PosX = j["m_PosX"];
			this->m_PosY = j["m_PosY"];
			this->m_Width = j["m_Width"];
			this->m_OptionsPerPage = j["m_OptionsPerPage"];
			this->m_Sounds = j["m_Sounds"];

			// Input
			this->m_OpenDelay = j["m_OpenDelay"];
			this->m_BackDelay = j["m_BackDelay"];
			this->m_EnterDelay = j["m_EnterDelay"];
			this->m_VerticalDelay = j["m_VerticalDelay"];
			this->m_HorizontalDelay = j["m_HorizontalDelay"];

			// Header
			this->m_HeaderHeight = j["m_HeaderHeight"];
			this->m_HeaderText = j["m_HeaderText"];
			this->m_HeaderTextSize = j["m_HeaderTextSize"];
			this->m_HeaderFont = Lists::FontTypes[j["m_HeaderFont"]];
			m_HeaderBackgroundColor.r = j["m_HeaderBackgroundColor"]["r"];
			m_HeaderBackgroundColor.g = j["m_HeaderBackgroundColor"]["g"];
			m_HeaderBackgroundColor.b = j["m_HeaderBackgroundColor"]["b"];
			m_HeaderBackgroundColor.a = j["m_HeaderBackgroundColor"]["a"];
			m_HeaderTextColor.r = j["m_HeaderTextColor"]["r"];
			m_HeaderTextColor.g = j["m_HeaderTextColor"]["g"];
			m_HeaderTextColor.b = j["m_HeaderTextColor"]["b"];
			m_HeaderTextColor.a = j["m_HeaderTextColor"]["a"];
			Lists::HeaderTypesPosition = j["m_HeaderType"];
			this->m_HeaderType = Lists::HeaderTypesBackend[Lists::HeaderTypesPosition];
			this->m_HeaderGradientTransparent = j["m_HeaderGradientTransparent"];
			this->m_HeaderGradientFlip = j["m_HeaderGradientFlip"];
			this->m_HeaderGradientStretch = j["m_HeaderGradientStretch"];
			this->m_HeaderGradientFiller = j["m_HeaderGradientFiller"];
			m_HeaderGradientColorLeft.r = j["m_HeaderGradientColorLeft"]["r"];
			m_HeaderGradientColorLeft.g = j["m_HeaderGradientColorLeft"]["g"];
			m_HeaderGradientColorLeft.b = j["m_HeaderGradientColorLeft"]["b"];
			m_HeaderGradientColorLeft.a = j["m_HeaderGradientColorLeft"]["a"];
			m_HeaderGradientColorRight.r = j["m_HeaderGradientColorRight"]["r"];
			m_HeaderGradientColorRight.g = j["m_HeaderGradientColorRight"]["g"];
			m_HeaderGradientColorRight.b = j["m_HeaderGradientColorRight"]["b"];
			m_HeaderGradientColorRight.a = j["m_HeaderGradientColorRight"]["a"];
			this->m_HeaderFilename = j["m_HeaderFilename"];
			this->m_AnimatedHeaderCurrentImage = j["m_AnimatedHeaderCurrentImage"];
			this->m_AnimatedHeaderTimerDelay = j["m_AnimatedHeaderTimerDelay"];
			this->m_AnimatedHeaderFrameCount = j["m_AnimatedHeaderFrameCount"];

			// Scrollbar
			this->m_ScrollBarWidth = j["m_ScrollBarWidth"];
			this->m_ScrollBarOffset = j["m_ScrollBarOffset"];
			this->m_ScrollBarSpriteSize = j["m_ScrollBarSpriteSize"];
			m_ScrollBarBackgroundColor.r = j["m_ScrollBarBackgroundColor"]["r"];
			m_ScrollBarBackgroundColor.g = j["m_ScrollBarBackgroundColor"]["g"];
			m_ScrollBarBackgroundColor.b = j["m_ScrollBarBackgroundColor"]["b"];
			m_ScrollBarBackgroundColor.a = j["m_ScrollBarBackgroundColor"]["a"];
			m_ScrollBarForegroundColor.r = j["m_ScrollBarForegroundColor"]["r"];
			m_ScrollBarForegroundColor.g = j["m_ScrollBarForegroundColor"]["g"];
			m_ScrollBarForegroundColor.b = j["m_ScrollBarForegroundColor"]["b"];
			m_ScrollBarForegroundColor.a = j["m_ScrollBarForegroundColor"]["a"];
			m_ScrollBarEndColor.r = j["m_ScrollBarEndColor"]["r"];
			m_ScrollBarEndColor.g = j["m_ScrollBarEndColor"]["g"];
			m_ScrollBarEndColor.b = j["m_ScrollBarEndColor"]["b"];
			m_ScrollBarEndColor.a = j["m_ScrollBarEndColor"]["a"];

			// Seperator
			this->m_SeperatorEnabled = j["m_SeperatorEnabled"];
			this->m_SeperatorHeight = j["m_SeperatorHeight"];
			m_SeperatorColorLeft.r = j["m_SeperatorColorLeft"]["r"];
			m_SeperatorColorLeft.g = j["m_SeperatorColorLeft"]["g"];
			m_SeperatorColorLeft.b = j["m_SeperatorColorLeft"]["b"];
			m_SeperatorColorLeft.a = j["m_SeperatorColorLeft"]["a"];
			m_SeperatorColorMiddle.r = j["m_SeperatorColorMiddle"]["r"];
			m_SeperatorColorMiddle.g = j["m_SeperatorColorMiddle"]["g"];
			m_SeperatorColorMiddle.b = j["m_SeperatorColorMiddle"]["b"];
			m_SeperatorColorMiddle.a = j["m_SeperatorColorMiddle"]["a"];
			m_SeperatorColorRight.r = j["m_SeperatorColorRight"]["r"];
			m_SeperatorColorRight.g = j["m_SeperatorColorRight"]["g"];
			m_SeperatorColorRight.b = j["m_SeperatorColorRight"]["b"];
			m_SeperatorColorRight.a = j["m_SeperatorColorRight"]["a"];

			// Submenu bar
			this->m_SubmenuBarHeight = j["m_SubmenuBarHeight"];
			this->m_SubmenuBarTextSize = j["m_SubmenuBarTextSize"];
			this->m_SubmenuBarFont = Lists::FontTypes[j["m_SubmenuBarFont"]];
			this->m_SubmenuBarPadding = j["m_SubmenuBarPadding"];
			m_SubmenuBarBackgroundColor.r = j["m_SubmenuBarBackgroundColor"]["r"];
			m_SubmenuBarBackgroundColor.g = j["m_SubmenuBarBackgroundColor"]["g"];
			m_SubmenuBarBackgroundColor.b = j["m_SubmenuBarBackgroundColor"]["b"];
			m_SubmenuBarBackgroundColor.a = j["m_SubmenuBarBackgroundColor"]["a"];
			m_SubmenuBarTextColor.r = j["m_SubmenuBarTextColor"]["r"];
			m_SubmenuBarTextColor.g = j["m_SubmenuBarTextColor"]["g"];
			m_SubmenuBarTextColor.b = j["m_SubmenuBarTextColor"]["b"];
			m_SubmenuBarTextColor.a = j["m_SubmenuBarTextColor"]["a"];

			// Options
			this->m_OptionHeight = j["m_OptionHeight"];
			this->m_OptionTextSize = j["m_OptionTextSize"];
			this->m_OptionFont = Lists::FontTypes[j["m_OptionFont"]];
			this->m_OptionPadding = j["m_OptionPadding"];
			m_OptionSelectedTextColor.r = j["m_OptionSelectedTextColor"]["r"];
			m_OptionSelectedTextColor.g = j["m_OptionSelectedTextColor"]["g"];
			m_OptionSelectedTextColor.b = j["m_OptionSelectedTextColor"]["b"];
			m_OptionSelectedTextColor.a = j["m_OptionSelectedTextColor"]["a"];
			m_OptionUnselectedTextColor.r = j["m_OptionUnselectedTextColor"]["r"];
			m_OptionUnselectedTextColor.g = j["m_OptionUnselectedTextColor"]["g"];
			m_OptionUnselectedTextColor.b = j["m_OptionUnselectedTextColor"]["b"];
			m_OptionUnselectedTextColor.a = j["m_OptionUnselectedTextColor"]["a"];
			m_OptionSelectedBackgroundColor.r = j["m_OptionSelectedBackgroundColor"]["r"];
			m_OptionSelectedBackgroundColor.g = j["m_OptionSelectedBackgroundColor"]["g"];
			m_OptionSelectedBackgroundColor.b = j["m_OptionSelectedBackgroundColor"]["b"];
			m_OptionSelectedBackgroundColor.a = j["m_OptionSelectedBackgroundColor"]["a"];
			m_OptionUnselectedBackgroundColor.r = j["m_OptionUnselectedBackgroundColor"]["r"];
			m_OptionUnselectedBackgroundColor.g = j["m_OptionUnselectedBackgroundColor"]["g"];
			m_OptionUnselectedBackgroundColor.b = j["m_OptionUnselectedBackgroundColor"]["b"];
			m_OptionUnselectedBackgroundColor.a = j["m_OptionUnselectedBackgroundColor"]["a"];

			// Footer
			this->m_FooterHeight = j["m_FooterHeight"];
			this->m_FooterSpriteSize = j["m_FooterSpriteSize"];
			m_FooterBackgroundColor.r = j["m_FooterBackgroundColor"]["r"];
			m_FooterBackgroundColor.g = j["m_FooterBackgroundColor"]["g"];
			m_FooterBackgroundColor.b = j["m_FooterBackgroundColor"]["b"];
			m_FooterBackgroundColor.a = j["m_FooterBackgroundColor"]["a"];
			m_FooterSpriteColor.r = j["m_FooterSpriteColor"]["r"];
			m_FooterSpriteColor.g = j["m_FooterSpriteColor"]["g"];
			m_FooterSpriteColor.b = j["m_FooterSpriteColor"]["b"];
			m_FooterSpriteColor.a = j["m_FooterSpriteColor"]["a"];

			// Description
			this->m_DescriptionHeightPadding = j["m_DescriptionHeightPadding"];
			this->m_DescriptionHeight = j["m_DescriptionHeight"];
			this->m_DescriptionTextSize = j["m_DescriptionTextSize"];
			this->m_DescriptionFont = Lists::FontTypes[j["m_DescriptionFont"]];
			m_DescriptionBackgroundColor.r = j["m_DescriptionBackgroundColor"]["r"];
			m_DescriptionBackgroundColor.g = j["m_DescriptionBackgroundColor"]["g"];
			m_DescriptionBackgroundColor.b = j["m_DescriptionBackgroundColor"]["b"];
			m_DescriptionBackgroundColor.a = j["m_DescriptionBackgroundColor"]["a"];
			m_DescriptionTextColor.r = j["m_DescriptionTextColor"]["r"];
			m_DescriptionTextColor.g = j["m_DescriptionTextColor"]["g"];
			m_DescriptionTextColor.b = j["m_DescriptionTextColor"]["b"];
			m_DescriptionTextColor.a = j["m_DescriptionTextColor"]["a"];
			this->m_DescriptionSpriteSize = j["m_DescriptionSpriteSize"];
			this->m_DescriptionPadding = j["m_DescriptionPadding"];
			m_DescriptionSpriteColor.r = j["m_DescriptionSpriteColor"]["r"];
			m_DescriptionSpriteColor.g = j["m_DescriptionSpriteColor"]["g"];
			m_DescriptionSpriteColor.b = j["m_DescriptionSpriteColor"]["b"];
			m_DescriptionSpriteColor.a = j["m_DescriptionSpriteColor"]["a"];
		}
	}

	std::string Config::path()
	{
		std::string path;
		char buffer[MAX_PATH];
		GetModuleFileNameA(g_Module, buffer, MAX_PATH);
		PathRemoveFileSpecA(buffer);
		path = buffer;
		path.append("\\config.json");
		return path;
	};

	bool Config::FileExists(std::string path)
	{
		struct stat buffer;
		return (stat(path.c_str(), &buffer) == 0);
	}

	void Config::Save()
	{
		json j;
		// General
		j["m_PosX"] = this->m_PosX;
		j["m_PosY"] = this->m_PosY;
		j["m_Width"] = this->m_Width;
		j["m_OptionsPerPage"] = this->m_OptionsPerPage;
		j["m_Sounds"] = this->m_Sounds;

		// Input
		j["m_OpenDelay"] = this->m_OpenDelay;
		j["m_BackDelay"] = this->m_BackDelay;
		j["m_EnterDelay"] = this->m_EnterDelay;
		j["m_VerticalDelay"] = this->m_VerticalDelay;
		j["m_HorizontalDelay"] = this->m_HorizontalDelay;

		// Header
		j["m_HeaderHeight"] = this->m_HeaderHeight;
		j["m_HeaderText"] = this->m_HeaderText;
		j["m_HeaderTextSize"] = this->m_HeaderTextSize;
		j["m_HeaderFont"] = (int)this->m_HeaderFont;
		j["m_HeaderBackgroundColor"]["r"] = m_HeaderBackgroundColor.r;
		j["m_HeaderBackgroundColor"]["g"] = m_HeaderBackgroundColor.g;
		j["m_HeaderBackgroundColor"]["b"] = m_HeaderBackgroundColor.b;
		j["m_HeaderBackgroundColor"]["a"] = m_HeaderBackgroundColor.a;
		j["m_HeaderTextColor"]["r"] = m_HeaderTextColor.r;
		j["m_HeaderTextColor"]["g"] = m_HeaderTextColor.g;
		j["m_HeaderTextColor"]["b"] = m_HeaderTextColor.b;
		j["m_HeaderTextColor"]["a"] = m_HeaderTextColor.a;
		j["m_HeaderType"] = (int)this->m_HeaderType;
		j["m_HeaderGradientTransparent"] = this->m_HeaderGradientTransparent;
		j["m_HeaderGradientFlip"] = this->m_HeaderGradientFlip;
		j["m_HeaderGradientStretch"] = this->m_HeaderGradientStretch;
		j["m_HeaderGradientFiller"] = this->m_HeaderGradientFiller;
		j["m_HeaderGradientColorLeft"]["r"] = m_HeaderGradientColorLeft.r;
		j["m_HeaderGradientColorLeft"]["g"] = m_HeaderGradientColorLeft.g;
		j["m_HeaderGradientColorLeft"]["b"] = m_HeaderGradientColorLeft.b;
		j["m_HeaderGradientColorLeft"]["a"] = m_HeaderGradientColorLeft.a;
		j["m_HeaderGradientColorRight"]["r"] = m_HeaderGradientColorRight.r;
		j["m_HeaderGradientColorRight"]["g"] = m_HeaderGradientColorRight.g;
		j["m_HeaderGradientColorRight"]["b"] = m_HeaderGradientColorRight.b;
		j["m_HeaderGradientColorRight"]["a"] = m_HeaderGradientColorRight.a;
		j["m_HeaderFilename"] = this->m_HeaderFilename;
		j["m_AnimatedHeaderCurrentImage"] = this->m_AnimatedHeaderCurrentImage;
		j["m_AnimatedHeaderTimerDelay"] = this->m_AnimatedHeaderTimerDelay;
		j["m_AnimatedHeaderFrameCount"] = this->m_AnimatedHeaderFrameCount;

		// Scrollbar
		j["m_ScrollBarWidth"] = this->m_ScrollBarWidth;
		j["m_ScrollBarOffset"] = this->m_ScrollBarOffset;
		j["m_ScrollBarSpriteSize"] = this->m_ScrollBarSpriteSize;
		j["m_ScrollBarBackgroundColor"]["r"] = m_ScrollBarBackgroundColor.r;
		j["m_ScrollBarBackgroundColor"]["g"] = m_ScrollBarBackgroundColor.g;
		j["m_ScrollBarBackgroundColor"]["b"] = m_ScrollBarBackgroundColor.b;
		j["m_ScrollBarBackgroundColor"]["a"] = m_ScrollBarBackgroundColor.a;
		j["m_ScrollBarForegroundColor"]["r"] = m_ScrollBarForegroundColor.r;
		j["m_ScrollBarForegroundColor"]["g"] = m_ScrollBarForegroundColor.g;
		j["m_ScrollBarForegroundColor"]["b"] = m_ScrollBarForegroundColor.b;
		j["m_ScrollBarForegroundColor"]["a"] = m_ScrollBarForegroundColor.a;
		j["m_ScrollBarEndColor"]["r"] = m_ScrollBarEndColor.r;
		j["m_ScrollBarEndColor"]["g"] = m_ScrollBarEndColor.g;
		j["m_ScrollBarEndColor"]["b"] = m_ScrollBarEndColor.b;
		j["m_ScrollBarEndColor"]["a"] = m_ScrollBarEndColor.a;

		// Seperator
		j["m_SeperatorEnabled"] = this->m_SeperatorEnabled;
		j["m_SeperatorHeight"] = this->m_SeperatorHeight;
		j["m_SeperatorColorLeft"]["r"] = m_SeperatorColorLeft.r;
		j["m_SeperatorColorLeft"]["g"] = m_SeperatorColorLeft.g;
		j["m_SeperatorColorLeft"]["b"] = m_SeperatorColorLeft.b;
		j["m_SeperatorColorLeft"]["a"] = m_SeperatorColorLeft.a;
		j["m_SeperatorColorMiddle"]["r"] = m_SeperatorColorMiddle.r;
		j["m_SeperatorColorMiddle"]["g"] = m_SeperatorColorMiddle.g;
		j["m_SeperatorColorMiddle"]["b"] = m_SeperatorColorMiddle.b;
		j["m_SeperatorColorMiddle"]["a"] = m_SeperatorColorMiddle.a;
		j["m_SeperatorColorRight"]["r"] = m_SeperatorColorRight.r;
		j["m_SeperatorColorRight"]["g"] = m_SeperatorColorRight.g;
		j["m_SeperatorColorRight"]["b"] = m_SeperatorColorRight.b;
		j["m_SeperatorColorRight"]["a"] = m_SeperatorColorRight.a;

		// Submenu bar
		j["m_SubmenuBarHeight"] = this->m_SubmenuBarHeight;
		j["m_SubmenuBarTextSize"] = this->m_SubmenuBarTextSize;
		j["m_SubmenuBarFont"] = (int)this->m_SubmenuBarFont;
		j["m_SubmenuBarPadding"] = this->m_SubmenuBarPadding;
		j["m_SubmenuBarBackgroundColor"]["r"] = m_SubmenuBarBackgroundColor.r;
		j["m_SubmenuBarBackgroundColor"]["g"] = m_SubmenuBarBackgroundColor.g;
		j["m_SubmenuBarBackgroundColor"]["b"] = m_SubmenuBarBackgroundColor.b;
		j["m_SubmenuBarBackgroundColor"]["a"] = m_SubmenuBarBackgroundColor.a;
		j["m_SubmenuBarTextColor"]["r"] = m_SubmenuBarTextColor.r;
		j["m_SubmenuBarTextColor"]["g"] = m_SubmenuBarTextColor.g;
		j["m_SubmenuBarTextColor"]["b"] = m_SubmenuBarTextColor.b;
		j["m_SubmenuBarTextColor"]["a"] = m_SubmenuBarTextColor.a;

		// Options
		j["m_OptionHeight"] = this->m_OptionHeight;
		j["m_OptionTextSize"] = this->m_OptionTextSize;
		j["m_OptionFont"] = (int)this->m_OptionFont;
		j["m_OptionPadding"] = this->m_OptionPadding;
		j["m_OptionSelectedTextColor"]["r"] = m_OptionSelectedTextColor.r;
		j["m_OptionSelectedTextColor"]["g"] = m_OptionSelectedTextColor.g;
		j["m_OptionSelectedTextColor"]["b"] = m_OptionSelectedTextColor.b;
		j["m_OptionSelectedTextColor"]["a"] = m_OptionSelectedTextColor.a;
		j["m_OptionUnselectedTextColor"]["r"] = m_OptionUnselectedTextColor.r;
		j["m_OptionUnselectedTextColor"]["g"] = m_OptionUnselectedTextColor.g;
		j["m_OptionUnselectedTextColor"]["b"] = m_OptionUnselectedTextColor.b;
		j["m_OptionUnselectedTextColor"]["a"] = m_OptionUnselectedTextColor.a;
		j["m_OptionSelectedBackgroundColor"]["r"] = m_OptionSelectedBackgroundColor.r;
		j["m_OptionSelectedBackgroundColor"]["g"] = m_OptionSelectedBackgroundColor.g;
		j["m_OptionSelectedBackgroundColor"]["b"] = m_OptionSelectedBackgroundColor.b;
		j["m_OptionSelectedBackgroundColor"]["a"] = m_OptionSelectedBackgroundColor.a;
		j["m_OptionUnselectedBackgroundColor"]["r"] = m_OptionUnselectedBackgroundColor.r;
		j["m_OptionUnselectedBackgroundColor"]["g"] = m_OptionUnselectedBackgroundColor.g;
		j["m_OptionUnselectedBackgroundColor"]["b"] = m_OptionUnselectedBackgroundColor.b;
		j["m_OptionUnselectedBackgroundColor"]["a"] = m_OptionUnselectedBackgroundColor.a;

		// Footer
		j["m_FooterHeight"] = this->m_FooterHeight;
		j["m_FooterSpriteSize"] = this->m_FooterSpriteSize;
		j["m_FooterBackgroundColor"]["r"] = m_FooterBackgroundColor.r;
		j["m_FooterBackgroundColor"]["g"] = m_FooterBackgroundColor.g;
		j["m_FooterBackgroundColor"]["b"] = m_FooterBackgroundColor.b;
		j["m_FooterBackgroundColor"]["a"] = m_FooterBackgroundColor.a;
		j["m_FooterSpriteColor"]["r"] = m_FooterSpriteColor.r;
		j["m_FooterSpriteColor"]["g"] = m_FooterSpriteColor.g;
		j["m_FooterSpriteColor"]["b"] = m_FooterSpriteColor.b;
		j["m_FooterSpriteColor"]["a"] = m_FooterSpriteColor.a;

		// Description
		j["m_DescriptionHeightPadding"] = this->m_DescriptionHeightPadding;
		j["m_DescriptionHeight"] = this->m_DescriptionHeight;
		j["m_DescriptionTextSize"] = this->m_DescriptionTextSize;
		j["m_DescriptionFont"] = (int)this->m_DescriptionFont;
		j["m_DescriptionBackgroundColor"]["r"] = m_DescriptionBackgroundColor.r;
		j["m_DescriptionBackgroundColor"]["g"] = m_DescriptionBackgroundColor.g;
		j["m_DescriptionBackgroundColor"]["b"] = m_DescriptionBackgroundColor.b;
		j["m_DescriptionBackgroundColor"]["a"] = m_DescriptionBackgroundColor.a;
		j["m_DescriptionTextColor"]["r"] = m_DescriptionTextColor.r;
		j["m_DescriptionTextColor"]["g"] = m_DescriptionTextColor.g;
		j["m_DescriptionTextColor"]["b"] = m_DescriptionTextColor.b;
		j["m_DescriptionTextColor"]["a"] = m_DescriptionTextColor.a;
		j["m_DescriptionSpriteSize"] = this->m_DescriptionSpriteSize;
		j["m_DescriptionPadding"] = this->m_DescriptionPadding;
		j["m_DescriptionSpriteColor"]["r"] = m_DescriptionSpriteColor.r;
		j["m_DescriptionSpriteColor"]["g"] = m_DescriptionSpriteColor.g;
		j["m_DescriptionSpriteColor"]["b"] = m_DescriptionSpriteColor.b;
		j["m_DescriptionSpriteColor"]["a"] = m_DescriptionSpriteColor.a;

		std::ofstream config_file;
		config_file.open(this->path().c_str());
		config_file << j << std::endl;
		config_file.close();
	}
}