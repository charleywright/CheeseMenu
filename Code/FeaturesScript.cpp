#include "FeaturesScript.hpp"
#include "Features.hpp"
#include "Natives.hpp"
#include "Lists.hpp"

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
			if(g_Features->m_FreezeTime) NETWORK::NETWORK_OVERRIDE_CLOCK_TIME(g_Features->m_hours, g_Features->m_minutes, g_Features->m_seconds);
			if(g_Features->m_FreezeWeather) MISC::SET_WEATHER_TYPE_NOW_PERSIST(Lists::WeatherTypesBackend[Lists::WeatherTypePosition]);
			tickCount = 0;
		}
	}
}
