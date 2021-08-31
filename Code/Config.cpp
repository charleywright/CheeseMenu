#include "Config.hpp"
#include "Lists.hpp"
#include "QueueScript.hpp"
#include <filesystem>
#include <shlwapi.h>
#include "JSON/json.hpp"
using json = nlohmann::json;

namespace Cheese
{
	Config::Config()
	{
		if (this->FileExists(this->path()))
		{
			bool valid = true;
			json j;
			std::ifstream raw_config(this->path());
			try
			{
				j = json::parse(raw_config);
			}
			catch (json::exception&)
			{
				valid = false;
			}
			if (!valid) {
				g_QueueScript->Add([] { g_Features->DisplayNotification("~r~Failed to load config"); });
				return;
			}

			// General
			this->m_PosX = j.value("m_PosX", this->m_PosX);
			this->m_PosY = j.value("m_PosY", this->m_PosY);
			this->m_Width = j.value("m_Width", this->m_Width);
			this->m_OptionsPerPage = j.value("m_OptionsPerPage", this->m_OptionsPerPage);
			this->m_Sounds = j.value("m_Sounds", this->m_Sounds);
			this->m_FeatureTickSize = j.value("m_FeatureTickSize", this->m_FeatureTickSize);

			// Input
			this->m_OpenDelay = j.value("m_OpenDelay", this->m_OpenDelay);
			this->m_BackDelay = j.value("m_BackDelay", this->m_BackDelay);
			this->m_EnterDelay = j.value("m_EnterDelay", this->m_EnterDelay);
			this->m_VerticalDelay = j.value("m_VerticalDelay", this->m_VerticalDelay);
			this->m_HorizontalDelay = j.value("m_HorizontalDelay", this->m_HorizontalDelay);

			// Header
			this->m_HeaderHeight = j.value("m_HeaderHeight", this->m_HeaderHeight);
			this->m_HeaderText = j.value("m_HeaderText", this->m_HeaderText);
			this->m_HeaderTextSize = j.value("m_HeaderTextSize", this->m_HeaderTextSize);
			this->m_HeaderFont = Lists::FontTypes[j.value("m_HeaderFont", (int)this->m_HeaderFont)];
			this->m_HeaderBackgroundColor.r = j["m_HeaderBackgroundColor"].value("r", this->m_HeaderBackgroundColor.r);
			this->m_HeaderBackgroundColor.g = j["m_HeaderBackgroundColor"].value("g", this->m_HeaderBackgroundColor.g);
			this->m_HeaderBackgroundColor.b = j["m_HeaderBackgroundColor"].value("b", this->m_HeaderBackgroundColor.b);
			this->m_HeaderBackgroundColor.a = j["m_HeaderBackgroundColor"].value("a", this->m_HeaderBackgroundColor.a);
			this->m_HeaderTextColor.r = j["m_HeaderTextColor"].value("r", this->m_HeaderTextColor.r);
			this->m_HeaderTextColor.g = j["m_HeaderTextColor"].value("g", this->m_HeaderTextColor.g);
			this->m_HeaderTextColor.b = j["m_HeaderTextColor"].value("b", this->m_HeaderTextColor.b);
			this->m_HeaderTextColor.a = j["m_HeaderTextColor"].value("a", this->m_HeaderTextColor.a);
			Lists::HeaderTypesPosition = j.value("m_HeaderType", Lists::HeaderTypesPosition);
			this->m_HeaderType = Lists::HeaderTypesBackend[Lists::HeaderTypesPosition];
			this->m_HeaderGradientTransparent = j.value("m_HeaderGradientTransparent", this->m_HeaderGradientTransparent);
			this->m_HeaderGradientFlip = j.value("m_HeaderGradientFlip", this->m_HeaderGradientFlip);
			this->m_HeaderGradientStretch = j.value("m_HeaderGradientStretch", this->m_HeaderGradientStretch);
			this->m_HeaderGradientFiller = j.value("m_HeaderGradientFiller", this->m_HeaderGradientFiller);
			this->m_HeaderGradientColorLeft.r = j["m_HeaderGradientColorLeft"].value("r", this->m_HeaderGradientColorLeft.r);
			this->m_HeaderGradientColorLeft.g = j["m_HeaderGradientColorLeft"].value("g", this->m_HeaderGradientColorLeft.g);
			this->m_HeaderGradientColorLeft.b = j["m_HeaderGradientColorLeft"].value("b", this->m_HeaderGradientColorLeft.b);
			this->m_HeaderGradientColorLeft.a = j["m_HeaderGradientColorLeft"].value("a", this->m_HeaderGradientColorLeft.a);
			this->m_HeaderGradientColorRight.r = j["m_HeaderGradientColorRight"].value("r", this->m_HeaderGradientColorRight.r);
			this->m_HeaderGradientColorRight.g = j["m_HeaderGradientColorRight"].value("g", this->m_HeaderGradientColorRight.g);
			this->m_HeaderGradientColorRight.b = j["m_HeaderGradientColorRight"].value("b", this->m_HeaderGradientColorRight.b);
			this->m_HeaderGradientColorRight.a = j["m_HeaderGradientColorRight"].value("a", this->m_HeaderGradientColorRight.a);
			this->m_HeaderFilename = j.value("m_HeaderFilename", this->m_HeaderFilename);
			this->m_AnimatedHeaderCurrentImage = j.value("m_AnimatedHeaderCurrentImage", this->m_AnimatedHeaderCurrentImage);
			this->m_AnimatedHeaderTimerDelay = j.value("m_AnimatedHeaderTimerDelay", this->m_AnimatedHeaderTimerDelay);
			this->m_AnimatedHeaderFrameCount = j.value("m_AnimatedHeaderFrameCount", this->m_AnimatedHeaderFrameCount);

			// Scrollbar
			this->m_ScrollBarWidth = j.value("m_ScrollBarWidth", this->m_ScrollBarWidth);
			this->m_ScrollBarOffset = j.value("m_ScrollBarOffset", this->m_ScrollBarOffset);
			this->m_ScrollBarSpriteSize = j.value("m_ScrollBarSpriteSize", this->m_ScrollBarSpriteSize);
			this->m_ScrollBarBackgroundColor.r = j["m_ScrollBarBackgroundColor"].value("r", this->m_ScrollBarBackgroundColor.r);
			this->m_ScrollBarBackgroundColor.g = j["m_ScrollBarBackgroundColor"].value("g", this->m_ScrollBarBackgroundColor.g);
			this->m_ScrollBarBackgroundColor.b = j["m_ScrollBarBackgroundColor"].value("b", this->m_ScrollBarBackgroundColor.b);
			this->m_ScrollBarBackgroundColor.a = j["m_ScrollBarBackgroundColor"].value("a", this->m_ScrollBarBackgroundColor.a);
			this->m_ScrollBarForegroundColor.r = j["m_ScrollBarForegroundColor"].value("r", this->m_ScrollBarForegroundColor.r);
			this->m_ScrollBarForegroundColor.g = j["m_ScrollBarForegroundColor"].value("g", this->m_ScrollBarForegroundColor.g);
			this->m_ScrollBarForegroundColor.b = j["m_ScrollBarForegroundColor"].value("b", this->m_ScrollBarForegroundColor.b);
			this->m_ScrollBarForegroundColor.a = j["m_ScrollBarForegroundColor"].value("a", this->m_ScrollBarForegroundColor.a);
			this->m_ScrollBarEndColor.r = j["m_ScrollBarEndColor"].value("r", this->m_ScrollBarEndColor.r);
			this->m_ScrollBarEndColor.g = j["m_ScrollBarEndColor"].value("g", this->m_ScrollBarEndColor.g);
			this->m_ScrollBarEndColor.b = j["m_ScrollBarEndColor"].value("b", this->m_ScrollBarEndColor.b);
			this->m_ScrollBarEndColor.a = j["m_ScrollBarEndColor"].value("a", this->m_ScrollBarEndColor.a);

			// Seperator
			this->m_SeperatorEnabled = j.value("m_SeperatorEnabled", this->m_SeperatorEnabled);
			this->m_SeperatorHeight = j.value("m_SeperatorHeight", this->m_SeperatorHeight);
			this->m_SeperatorColorLeft.r = j["m_SeperatorColorLeft"].value("r", this->m_SeperatorColorLeft.r);
			this->m_SeperatorColorLeft.g = j["m_SeperatorColorLeft"].value("g", this->m_SeperatorColorLeft.g);
			this->m_SeperatorColorLeft.b = j["m_SeperatorColorLeft"].value("b", this->m_SeperatorColorLeft.b);
			this->m_SeperatorColorLeft.a = j["m_SeperatorColorLeft"].value("a", this->m_SeperatorColorLeft.a);
			this->m_SeperatorColorMiddle.r = j["m_SeperatorColorMiddle"].value("r", this->m_SeperatorColorMiddle.r);
			this->m_SeperatorColorMiddle.g = j["m_SeperatorColorMiddle"].value("g", this->m_SeperatorColorMiddle.g);
			this->m_SeperatorColorMiddle.b = j["m_SeperatorColorMiddle"].value("b", this->m_SeperatorColorMiddle.b);
			this->m_SeperatorColorMiddle.a = j["m_SeperatorColorMiddle"].value("a", this->m_SeperatorColorMiddle.a);
			this->m_SeperatorColorRight.r = j["m_SeperatorColorRight"].value("r", this->m_SeperatorColorRight.r);
			this->m_SeperatorColorRight.g = j["m_SeperatorColorRight"].value("g", this->m_SeperatorColorRight.g);
			this->m_SeperatorColorRight.b = j["m_SeperatorColorRight"].value("b", this->m_SeperatorColorRight.b);
			this->m_SeperatorColorRight.a = j["m_SeperatorColorRight"].value("a", this->m_SeperatorColorRight.a);

			// Submenu bar
			this->m_SubmenuBarHeight = j.value("m_SubmenuBarHeight", this->m_SubmenuBarHeight);
			this->m_SubmenuBarTextSize = j.value("m_SubmenuBarTextSize", this->m_SubmenuBarTextSize);
			this->m_SubmenuBarFont = Lists::FontTypes[j.value("m_SubmenuBarFont", (int)this->m_SubmenuBarFont)];
			this->m_SubmenuBarPadding = j.value("m_SubmenuBarPadding", this->m_SubmenuBarPadding);
			this->m_SubmenuBarBackgroundColor.r = j["m_SubmenuBarBackgroundColor"].value("r", this->m_SubmenuBarBackgroundColor.r);
			this->m_SubmenuBarBackgroundColor.g = j["m_SubmenuBarBackgroundColor"].value("g", this->m_SubmenuBarBackgroundColor.g);
			this->m_SubmenuBarBackgroundColor.b = j["m_SubmenuBarBackgroundColor"].value("b", this->m_SubmenuBarBackgroundColor.b);
			this->m_SubmenuBarBackgroundColor.a = j["m_SubmenuBarBackgroundColor"].value("a", this->m_SubmenuBarBackgroundColor.a);
			this->m_SubmenuBarTextColor.r = j["m_SubmenuBarTextColor"].value("r", this->m_SubmenuBarTextColor.r);
			this->m_SubmenuBarTextColor.g = j["m_SubmenuBarTextColor"].value("g", this->m_SubmenuBarTextColor.g);
			this->m_SubmenuBarTextColor.b = j["m_SubmenuBarTextColor"].value("b", this->m_SubmenuBarTextColor.b);
			this->m_SubmenuBarTextColor.a = j["m_SubmenuBarTextColor"].value("a", this->m_SubmenuBarTextColor.a);

			// Options
			this->m_OptionHeight = j.value("m_OptionHeight", this->m_OptionHeight);
			this->m_OptionTextSize = j.value("m_OptionTextSize", this->m_OptionTextSize);
			this->m_OptionPadding = j.value("m_OptionPadding", this->m_OptionPadding);
			this->m_OptionFont = Lists::FontTypes[j.value("m_OptionFont", (int)this->m_OptionFont)];
			this->m_OptionSelectedTextColor.r = j["m_OptionSelectedTextColor"].value("r", this->m_OptionSelectedTextColor.r);
			this->m_OptionSelectedTextColor.g = j["m_OptionSelectedTextColor"].value("g", this->m_OptionSelectedTextColor.g);
			this->m_OptionSelectedTextColor.b = j["m_OptionSelectedTextColor"].value("b", this->m_OptionSelectedTextColor.b);
			this->m_OptionSelectedTextColor.a = j["m_OptionSelectedTextColor"].value("a", this->m_OptionSelectedTextColor.a);
			this->m_OptionUnselectedTextColor.r = j["m_OptionUnselectedTextColor"].value("r", this->m_OptionUnselectedTextColor.r);
			this->m_OptionUnselectedTextColor.g = j["m_OptionUnselectedTextColor"].value("g", this->m_OptionUnselectedTextColor.g);
			this->m_OptionUnselectedTextColor.b = j["m_OptionUnselectedTextColor"].value("b", this->m_OptionUnselectedTextColor.b);
			this->m_OptionUnselectedTextColor.a = j["m_OptionUnselectedTextColor"].value("a", this->m_OptionUnselectedTextColor.a);
			this->m_OptionSelectedBackgroundColor.r = j["m_OptionSelectedBackgroundColor"].value("r", this->m_OptionSelectedBackgroundColor.r);
			this->m_OptionSelectedBackgroundColor.g = j["m_OptionSelectedBackgroundColor"].value("g", this->m_OptionSelectedBackgroundColor.g);
			this->m_OptionSelectedBackgroundColor.b = j["m_OptionSelectedBackgroundColor"].value("b", this->m_OptionSelectedBackgroundColor.b);
			this->m_OptionSelectedBackgroundColor.a = j["m_OptionSelectedBackgroundColor"].value("a", this->m_OptionSelectedBackgroundColor.a);
			this->m_OptionUnselectedBackgroundColor.r = j["m_OptionUnselectedBackgroundColor"].value("r", this->m_OptionUnselectedBackgroundColor.r);
			this->m_OptionUnselectedBackgroundColor.g = j["m_OptionUnselectedBackgroundColor"].value("g", this->m_OptionUnselectedBackgroundColor.g);
			this->m_OptionUnselectedBackgroundColor.b = j["m_OptionUnselectedBackgroundColor"].value("b", this->m_OptionUnselectedBackgroundColor.b);
			this->m_OptionUnselectedBackgroundColor.a = j["m_OptionUnselectedBackgroundColor"].value("a", this->m_OptionUnselectedBackgroundColor.a);

			// Footer
			this->m_FooterHeight = j.value("m_FooterHeight", this->m_FooterHeight);
			this->m_FooterSpriteSize = j.value("m_FooterSpriteSize", this->m_FooterSpriteSize);
			this->m_FooterBackgroundColor.r = j["m_FooterBackgroundColor"].value("r", this->m_FooterBackgroundColor.r);
			this->m_FooterBackgroundColor.g = j["m_FooterBackgroundColor"].value("g", this->m_FooterBackgroundColor.g);
			this->m_FooterBackgroundColor.b = j["m_FooterBackgroundColor"].value("b", this->m_FooterBackgroundColor.b);
			this->m_FooterBackgroundColor.a = j["m_FooterBackgroundColor"].value("a", this->m_FooterBackgroundColor.a);
			this->m_FooterSpriteColor.r = j["m_FooterSpriteColor"].value("r", this->m_FooterSpriteColor.r);
			this->m_FooterSpriteColor.g = j["m_FooterSpriteColor"].value("g", this->m_FooterSpriteColor.g);
			this->m_FooterSpriteColor.b = j["m_FooterSpriteColor"].value("b", this->m_FooterSpriteColor.b);
			this->m_FooterSpriteColor.a = j["m_FooterSpriteColor"].value("a", this->m_FooterSpriteColor.a);

			// Description
			this->m_DescriptionHeightPadding = j.value("m_DescriptionHeightPadding", this->m_DescriptionHeightPadding);
			this->m_DescriptionHeight = j.value("m_DescriptionHeight", this->m_DescriptionHeight);
			this->m_DescriptionTextSize = j.value("m_DescriptionTextSize", this->m_DescriptionTextSize);
			this->m_DescriptionFont = Lists::FontTypes[j.value("m_DescriptionFont", (int)this->m_DescriptionFont)];
			this->m_DescriptionBackgroundColor.r = j["m_DescriptionBackgroundColor"].value("r", this->m_DescriptionBackgroundColor.r);
			this->m_DescriptionBackgroundColor.g = j["m_DescriptionBackgroundColor"].value("g", this->m_DescriptionBackgroundColor.g);
			this->m_DescriptionBackgroundColor.b = j["m_DescriptionBackgroundColor"].value("b", this->m_DescriptionBackgroundColor.b);
			this->m_DescriptionBackgroundColor.a = j["m_DescriptionBackgroundColor"].value("a", this->m_DescriptionBackgroundColor.a);
			this->m_DescriptionTextColor.r = j["m_DescriptionTextColor"].value("r", this->m_DescriptionTextColor.r);
			this->m_DescriptionTextColor.g = j["m_DescriptionTextColor"].value("g", this->m_DescriptionTextColor.g);
			this->m_DescriptionTextColor.b = j["m_DescriptionTextColor"].value("b", this->m_DescriptionTextColor.b);
			this->m_DescriptionTextColor.a = j["m_DescriptionTextColor"].value("a", this->m_DescriptionTextColor.a);
			this->m_DescriptionSpriteSize = j.value("m_DescriptionSpriteSize", this->m_DescriptionSpriteSize);
			this->m_DescriptionPadding = j.value("m_DescriptionPadding", this->m_DescriptionPadding);
			this->m_DescriptionSpriteColor.r = j["m_DescriptionSpriteColor"].value("r", this->m_DescriptionSpriteColor.r);
			this->m_DescriptionSpriteColor.g = j["m_DescriptionSpriteColor"].value("g", this->m_DescriptionSpriteColor.g);
			this->m_DescriptionSpriteColor.b = j["m_DescriptionSpriteColor"].value("b", this->m_DescriptionSpriteColor.b);
			this->m_DescriptionSpriteColor.a = j["m_DescriptionSpriteColor"].value("a", this->m_DescriptionSpriteColor.a);

			g_QueueScript->Add([] { g_Features->DisplayNotification("~g~Loaded config"); });
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
		j["m_FeatureTickSize"] = this->m_FeatureTickSize;

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