#include "FeaturesScript.hpp"
#include "Features.hpp"
#include "Natives.hpp"
#include "Lists.hpp"
#include "Config.hpp"
#include "Memory.hpp"
#include "Game.hpp"
#include "Offsets.hpp"

namespace Cheese
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
		byte *ffPtr = (byte *)DereferenceMultiLevel(g_GameVariables->m_WorldPtr, {Offsets::pCPed, Offsets::pCPlayerInfo, Offsets::oFrameFlags});
		byte frameFlags = *ffPtr;
		if (g_Features->m_ExplosiveAmmo)
			frameFlags = frameFlags | 0x8;
		if (g_Features->m_FireAmmo)
			frameFlags = frameFlags | 0x10;
		if (g_Features->m_ExplosiveFist)
			frameFlags = frameFlags | 0x20;
		if (g_Features->m_SuperJump)
			frameFlags = frameFlags | 0x40;
		*ffPtr = frameFlags;

		tickCount++;
		if (tickCount >= g_Config->m_FeatureTickSize)
		{
			if (g_Features->m_FixVehicle)
				g_Features->FixVehicle();
			if (g_Features->m_FreezeTime)
				NETWORK::NETWORK_OVERRIDE_CLOCK_TIME(g_Features->m_hours, g_Features->m_minutes, g_Features->m_seconds);
			if (g_Features->m_FreezeWeather)
				MISC::SET_WEATHER_TYPE_NOW_PERSIST(Lists::WeatherTypesBackend[Lists::WeatherTypePosition]);
			if (g_Features->m_FreezeWanted)
				*(int *)DereferenceMultiLevel(g_GameVariables->m_WorldPtr, {Offsets::pCPed, Offsets::pCPlayerInfo, Offsets::oWanted}) = g_Features->m_WantedLevel;
			if (g_Features->m_UnlimitedBoost)
				g_Features->UnlimitedBoost();
			*(byte *)DereferenceMultiLevel(g_GameVariables->m_WorldPtr, {Offsets::pCPed, Offsets::oGod}) = (g_Features->m_Godmode ? 0x01 : 0x00);
			g_Features->m_AntiAFKKick ? g_Features->EnableAntiAfkKick() : g_Features->DisableAntiAfkKick();

			tickCount = 0;
		}
	}
}
