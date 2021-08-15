#include "Features.hpp"
#include "Natives.hpp"

namespace Big {
	void Features::EnterSession(int type) {
		*ScriptGlobal(1312854).As<int*>() = type;
		g_Logger->Info(std::to_string(type).c_str());
		MISC::SET_BIT(&*ScriptGlobal(1312443).As<int*>(), 1);
		MISC::SET_BIT(&*ScriptGlobal(1312443).As<int*>(), 0);
	}
	void Features::LeaveGTAOnline() {
		*ScriptGlobal(1312443).Add(2).As<int*>() = -1;
		MISC::SET_BIT(&*ScriptGlobal(1312443).As<int*>(), 1);
		MISC::SET_BIT(&*ScriptGlobal(1312443).As<int*>(), 0);
	}
}