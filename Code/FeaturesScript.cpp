#include "FeaturesScript.hpp"
#include "Features.hpp"

namespace Big
{
	bool FeaturesScript::IsInitialized()
	{
		return m_Initialized;
	}

	ScriptType FeaturesScript::GetType()
	{
		return ScriptType::Game;
	}

	void FeaturesScript::Initialize()
	{
		m_Initialized = true;
	}

	void FeaturesScript::Destroy()
	{
	}

	void FeaturesScript::Tick()
	{
		tickCount++;
		if (tickCount >= 10) {
			if (g_Features->m_FixVehicle) g_Features->FixVehicle();
			tickCount = 0;
		}
	}
}
