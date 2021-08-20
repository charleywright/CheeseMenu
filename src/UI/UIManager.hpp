#pragma once
#include "../Common.hpp"
#include "../Types.hpp"
#include "TextBox.hpp"
#include "AbstractSubmenu.hpp"
#include "../Timer.hpp"

namespace Big::UserInterface
{
	enum class Font : std::int32_t
	{
		ChaletLondon = 0,
		HouseScript = 1,
		Monospace = 2,
		Wingdings = 3,
		ChaletComprimeCologne = 4,
		Pricedown = 7
	};

	enum class HeaderType : std::int32_t
	{
		Static = 0,
		Gradient = 1,
		Image = 2,
		Animated = 3
	};

	struct Rectangle
	{
		Vector2 m_Center;
		Vector2 m_Size;

		bool IsInBounds(Vector2 point)
		{
			auto left = m_Center.x - (m_Size.x / 2.f);
			auto right = m_Center.x + (m_Size.x / 2.f);
			auto top = m_Center.y + (m_Size.y / 2.f);
			auto bottom = m_Center.y - (m_Size.y / 2.f);

			if (point.x > right || point.x < left)
				return false;
			if (point.y > top || point.y < bottom)
				return false;

			return true;
		}
	};

	class UIManager
	{
	public:
		UIManager();
		~UIManager() noexcept = default;
		UIManager(UIManager const &) = delete;
		UIManager(UIManager &&) = delete;
		UIManager &operator=(UIManager const &) = delete;
		UIManager &operator=(UIManager &&) = delete;

		template <typename SubmenuType, typename... TArgs>
		void AddSubmenu(TArgs &&...args)
		{
			auto sub = std::make_unique<SubmenuType>(std::forward<TArgs>(args)...);
			if (m_SubmenuStack.empty())
			{
				m_SubmenuStack.push(sub.get());
			}

			m_AllSubmenus.push_back(std::move(sub));
		}

		void SwitchToSubmenu(std::uint32_t id)
		{
			for (auto &&sub : m_AllSubmenus)
			{
				if (sub->GetId() == id)
				{
					m_SubmenuStack.push(sub.get());
					return;
				}
			}
		}

		void OnTick();

	public:
		std::mutex m_Mutex;
		bool m_Opened = false;
		bool m_MouseLocked = false;

	private:
		bool m_OpenKeyPressed = false;
		bool m_BackKeyPressed = false;
		bool m_EnterKeyPressed = false;
		bool m_UpKeyPressed = false;
		bool m_DownKeyPressed = false;
		bool m_LeftKeyPressed = false;
		bool m_RightKeyPressed = false;
		void CheckForInput();
		void HandleInput();
		void ResetInput();

		bool FileExists(const std::string &fileName);
		const std::string GetModulePath(HMODULE module);

		float m_DrawBaseY{};
		void DrawHeader();
		void LoadHeader(std::string headerName);
		void DrawScrollBar(AbstractSubmenu *sub);
		void DrawSubmenuBar(AbstractSubmenu *sub);
		void DrawSeperator();
		void DrawOption(AbstractOption *opt, bool selected);
		void DrawFooter();
		void DrawDescription();

		void DrawRect(float x, float y, float width, float height, Color color);
		void DrawSprite(const char *dict, const char *texture, float x, float y, float width, float height, Color color, float rotation);
		void DrawLeftText(const char *text, float x, float y, float size, Font font, Color color, bool outline, bool shadow);
		void DrawCenteredText(const char *text, float x, float y, float size, Font font, Color color, bool outline, bool shadow);
		void DrawRightText(const char *text, float x, float y, float size, Font font, Color color, bool outline, bool shadow);
		float GetTextHeight(Font font, float size);
		Vector2 GetSpriteScale(float size);

		bool IsMouseLocked();
		Rectangle GetMenuRect();
		Vector2 GetMousePos();

		std::vector<std::unique_ptr<AbstractSubmenu>> m_AllSubmenus;
		std::stack<AbstractSubmenu *, std::vector<AbstractSubmenu *>> m_SubmenuStack;
	};
}

namespace Big
{
	inline std::unique_ptr<UserInterface::UIManager> g_UiManager;
}
