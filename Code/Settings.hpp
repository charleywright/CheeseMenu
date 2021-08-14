#pragma once

namespace Big
{
	class Settings
	{
	public:
#if _DEBUG
		std::atomic_bool m_LogWindow = true;
		std::atomic_bool m_LockMouse = true;
#else	
		std::atomic_bool m_LogWindow = false;
		std::atomic_bool m_LockMouse = false;
#endif
	};

	inline Settings g_Settings;
}
