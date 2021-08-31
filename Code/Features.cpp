#include "Features.hpp"
#include "Natives.hpp"
#include "Lists.hpp"
#include "RPLevels.hpp"
#include "QueueScript.hpp"

std::string GetStatString(std::string stat, int character)
{
	switch (character)
	{
	case 0:
		stat[2] = '0';
		break;
	case 1:
		stat[2] = '1';
		break;
	}
	return stat;
}

int GetCharacterIndex()
{
	int i;
	Cheese::STATS::STAT_GET_INT(CONSTEXPR_JOAAT("MPPLY_LAST_MP_CHAR"), &i, -1);
	return i;
}

void OffMap(int type)
{
	Cheese::g_QueueScript->Add([]
							   { *Cheese::ScriptGlobal(2426865).Add(1).Add(*Cheese::ScriptGlobal(2441237).As<int *>() * 449).Add(209).As<int *>() = 1; });
	Cheese::g_QueueScript->Add([]
							   { *Cheese::ScriptGlobal(2441237).Add(70).As<int *>() = *Cheese::ScriptGlobal(1312603).Add(11).As<int *>(); });
	Cheese::g_QueueScript->Add([type]
							   { *Cheese::ScriptGlobal(2544210).Add(4628).As<int *>() = type; });
}

namespace Cheese
{
	const uint32_t Features::Stat(std::string stat, int c_index)
	{
		return Cheese::Joaat(stat.substr(0, 2).append(std::to_string(c_index)).append(stat.substr(3)).c_str());
	}

	void Features::FixVehicle()
	{
		Ped playerPed = PLAYER::PLAYER_PED_ID();
		bool pedExists = ENTITY::DOES_ENTITY_EXIST(playerPed);
		if (pedExists && PED::IS_PED_IN_ANY_VEHICLE(playerPed, false))
		{
			Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(playerPed, true);
			VEHICLE::SET_VEHICLE_FIXED(veh);
			VEHICLE::SET_VEHICLE_DIRT_LEVEL(veh, 0);
		}
	}

	void Features::OffRadar() { OffMap(3); }

	void Features::GhostOrg() { OffMap(4); }

	void Features::EnableAntiAfkKick()
	{
		*ScriptGlobal(262145).Add(87).As<int *>() = 99999999;
		*ScriptGlobal(262145).Add(88).As<int *>() = 99999999;
		*ScriptGlobal(262145).Add(89).As<int *>() = 99999999;
		*ScriptGlobal(262145).Add(90).As<int *>() = 99999999;
		*ScriptGlobal(262145).Add(7958).As<int *>() = 2000000000;
		*ScriptGlobal(262145).Add(7955).As<int *>() = 2000000000;
		*ScriptGlobal(262145).Add(7956).As<int *>() = 2000000000;
		*ScriptGlobal(262145).Add(7957).As<int *>() = 2000000000;
	}

	void Features::DisableAntiAfkKick()
	{
		*ScriptGlobal(262145).Add(87).As<int *>() = 120000;
		*ScriptGlobal(262145).Add(88).As<int *>() = 300000;
		*ScriptGlobal(262145).Add(89).As<int *>() = 600000;
		*ScriptGlobal(262145).Add(90).As<int *>() = 900000;
		*ScriptGlobal(262145).Add(7958).As<int *>() = 30000;
		*ScriptGlobal(262145).Add(7955).As<int *>() = 60000;
		*ScriptGlobal(262145).Add(7956).As<int *>() = 90000;
		*ScriptGlobal(262145).Add(7957).As<int *>() = 120000;
	}

	void Features::DisplayNotification(const char *text)
	{
		HUD::_SET_NOTIFICATION_TEXT_ENTRY("STRING");
		HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(text);
		HUD::_DRAW_NOTIFICATION(false, false);
	}

	void Features::EnterSession(int type)
	{
		g_QueueScript->Add([type]
						   { *ScriptGlobal(1312860).As<int *>() = type; });
		g_QueueScript->Add([]
						   { *ScriptGlobal(1312443).As<int *>() = 1; });
		g_QueueScript->Delay(200ms);
		g_QueueScript->Add([]
						   { *ScriptGlobal(1312443).As<int *>() = 0; });
		g_QueueScript->Add([]
						   { g_UiManager->m_Opened = false; });
	}
	void Features::LeaveGTAOnline()
	{
		if (NETWORK::NETWORK_IS_SESSION_ACTIVE())
		{
			g_QueueScript->Add([]
							   { *ScriptGlobal(1312443).Add(2).As<int *>() = -1; });
			g_QueueScript->Add([]
							   { *ScriptGlobal(1312443).As<int *>() = 1; });
			g_QueueScript->Delay(200ms);
			g_QueueScript->Add([]
							   { *ScriptGlobal(1312443).As<int *>() = 0; });
			g_QueueScript->Add([]
							   { g_UiManager->m_Opened = false; });
		}
	}

	void Features::RPCorrection()
	{
		int c_index = GetCharacterIndex();
		STATS::STAT_SET_INT(Stat("MPx_CHAR_SET_RP_GIFT_ADMIN", c_index), RPLevels[g_Features->m_RPCorrectionLevel - 1], 1);
		g_QueueScript->Add([]
						   { g_Features->DisplayNotification("~b~Change session to apply rank"); });
	}

	void Features::MaxStats()
	{
		int c_index = GetCharacterIndex();
		STATS::STAT_SET_INT(Stat("MPx_SCRIPT_INCREASE_STAM", c_index), 100, 1);
		STATS::STAT_SET_INT(Stat("MPx_SCRIPT_INCREASE_STRN", c_index), 100, 1);
		STATS::STAT_SET_INT(Stat("MPx_SCRIPT_INCREASE_LUNG", c_index), 100, 1);
		STATS::STAT_SET_INT(Stat("MPx_SCRIPT_INCREASE_DRIV", c_index), 100, 1);
		STATS::STAT_SET_INT(Stat("MPx_SCRIPT_INCREASE_FLY", c_index), 100, 1);
		STATS::STAT_SET_INT(Stat("MPx_SCRIPT_INCREASE_SHO", c_index), 100, 1);
		STATS::STAT_SET_INT(Stat("MPx_SCRIPT_INCREASE_STL", c_index), 100, 1);
		STATS::STAT_SET_INT(Stat("MPx_SCRIPT_INCREASE_MECH", c_index), 100, 1);
		g_QueueScript->Add([]
						   { g_Features->DisplayNotification("Maxed stats"); });
	}

	void Features::MaxSnacks()
	{
		int c_index = GetCharacterIndex();
		STATS::STAT_SET_INT(Stat("MPx_NO_BOUGHT_YUM_SNACKS", c_index), INT_MAX, 1);
		STATS::STAT_SET_INT(Stat("MPx_NO_BOUGHT_HEALTH_SNACKS", c_index), INT_MAX, 1);
		STATS::STAT_SET_INT(Stat("MPx_NO_BOUGHT_EPIC_SNACKS", c_index), INT_MAX, 1);
		STATS::STAT_SET_INT(Stat("MPx_NUMBER_OF_ORANGE_BOUGHT", c_index), INT_MAX, 1);
		STATS::STAT_SET_INT(Stat("MPx_NUMBER_OF_BOURGE_BOUGHT", c_index), INT_MAX, 1);
		STATS::STAT_SET_INT(Stat("MPx_CIGARETTES_BOUGHT", c_index), INT_MAX, 1);
		g_QueueScript->Add([]
						   { g_Features->DisplayNotification("Maxed Snacks"); });
	}

	void Features::MaxArmour()
	{
		int c_index = GetCharacterIndex();
		STATS::STAT_SET_INT(Stat("MPx_MP_CHAR_ARMOUR_1_COUNT", c_index), INT_MAX, 1);
		STATS::STAT_SET_INT(Stat("MPx_MP_CHAR_ARMOUR_2_COUNT", c_index), INT_MAX, 1);
		STATS::STAT_SET_INT(Stat("MPx_MP_CHAR_ARMOUR_3_COUNT", c_index), INT_MAX, 1);
		STATS::STAT_SET_INT(Stat("MPx_MP_CHAR_ARMOUR_4_COUNT", c_index), INT_MAX, 1);
		STATS::STAT_SET_INT(Stat("MPx_MP_CHAR_ARMOUR_5_COUNT", c_index), INT_MAX, 1);
		g_QueueScript->Add([]
						   { g_Features->DisplayNotification("Maxed Armour"); });
	}

	void Features::DoomsdayPrerequisite()
	{
		int c_index = GetCharacterIndex();
		STATS::STAT_SET_INT(Stat("MPx_GANGOPS_HEIST_STATUS", c_index), 9999, 1);
		g_QueueScript->Add([]
						   { g_Features->DisplayNotification("~g~Call lester and cancel all 3 heists"); });
	}

	void Features::SkipAct1()
	{
		int c_index = GetCharacterIndex();
		STATS::STAT_SET_INT(Stat("MPx_GANGOPS_FLOW_MISSION_PROG", c_index), 503, 1);
		STATS::STAT_SET_INT(Stat("MPx_GANGOPS_HEIST_STATUS", c_index), 229383, 1);
		STATS::STAT_SET_INT(Stat("MPx_GANGOPS_FLOW_NOTIFICATIONS", c_index), 1557, 1);
		g_QueueScript->Add([]
						   { g_Features->DisplayNotification("~g~Skipped Act 1 preps & setups"); });
	}

	void Features::SkipAct2()
	{
		int c_index = GetCharacterIndex();
		STATS::STAT_SET_INT(Stat("MPx_GANGOPS_FLOW_MISSION_PROG", c_index), 240, 1);
		STATS::STAT_SET_INT(Stat("MPx_GANGOPS_HEIST_STATUS", c_index), 229378, 1);
		STATS::STAT_SET_INT(Stat("MPx_GANGOPS_FLOW_NOTIFICATIONS", c_index), 1557, 1);
		g_QueueScript->Add([]
						   { g_Features->DisplayNotification("~g~Skipped Act 2 preps & setups"); });
	}

	void Features::SkipAct3()
	{
		int c_index = GetCharacterIndex();
		STATS::STAT_SET_INT(Stat("MPx_GANGOPS_FLOW_MISSION_PROG", c_index), 16368, 1);
		STATS::STAT_SET_INT(Stat("MPx_GANGOPS_HEIST_STATUS", c_index), 229380, 1);
		STATS::STAT_SET_INT(Stat("MPx_GANGOPS_FLOW_NOTIFICATIONS", c_index), 1557, 1);
		g_QueueScript->Add([]
						   { g_Features->DisplayNotification("~g~Skipped Act 3 preps & setups"); });
	}

	void Features::ApplyCayoPerico()
	{
		int c_index = GetCharacterIndex();
		STATS::STAT_SET_INT(Stat("MPx_H4_PROGRESS", c_index), (int)g_Features->m_CayoPericoDifficulty, 1);

		int h4_missions = 1;
		if (g_Features->m_CayoPericoKosatka)
			h4_missions += 2;
		if (g_Features->m_CayoPericoVelum)
			h4_missions += 8;
		if (g_Features->m_CayoPericoAnnihilator)
			h4_missions += 16;
		if (g_Features->m_CayoPericoPatrolBoat)
			h4_missions += 32;
		if (g_Features->m_CayoPericoLongfin)
			h4_missions += 64;
		if (g_Features->m_CayoPericoAlkonostAndStealthHeli)
			h4_missions += 132;

		if (g_Features->m_CayoPericoDemolitionCharges)
			h4_missions += 256;
		if (g_Features->m_CayoPericoCuttingTorch)
			h4_missions += 512;
		if (g_Features->m_CayoPericoPrimaryTool)
			h4_missions += 1024;
		if (g_Features->m_CayoPericoFingerprint)
			h4_missions += 2048;

		STATS::STAT_SET_INT(Stat("MPx_H4CNF_WEAPONS", c_index), (int)g_Features->m_CayoPericoWeapon, 1);

		if (g_Features->m_CayoPericoDisruptWeapons)
		{
			h4_missions += 8192;
			STATS::STAT_SET_INT(Stat("MPx_H4CNF_WEP_DISRP", c_index), 3, 1);
		}
		else
			STATS::STAT_SET_INT(Stat("MPx_H4CNF_WEP_DISRP", c_index), 0, 1);
		if (g_Features->m_CayoPericoDisruptArmour)
		{
			h4_missions += 16384;
			STATS::STAT_SET_INT(Stat("MPx_H4CNF_ARM_DISRP", c_index), 3, 1);
		}
		else
			STATS::STAT_SET_INT(Stat("MPx_H4CNF_ARM_DISRP", c_index), 0, 1);

		if (g_Features->m_CayoPericoDisruptAirSupport)
		{
			h4_missions += 32768;
			STATS::STAT_SET_INT(Stat("MPx_H4CNF_HEL_DISRP", c_index), 3, 1);
		}
		else
			STATS::STAT_SET_INT(Stat("MPx_H4CNF_HEL_DISRP", c_index), 0, 1);

		STATS::STAT_SET_INT(Stat("MPx_H4_MISSIONS", c_index), h4_missions, 1);

		STATS::STAT_SET_INT(Stat("MPx_H4CNF_TARGET", c_index), (int)g_Features->m_CayoPericoMainTarget, 1);
		STATS::STAT_SET_INT(Stat("MPx_H4CNF_TROJAN", c_index), (int)g_Features->m_CayoPericoSupplyTruck, 1);

		if (g_Features->m_CayoPericoUnlockAllPOI)
			STATS::STAT_SET_INT(Stat("MPx_H4CNF_BS_GEN", c_index), 131071, 1);

		STATS::STAT_SET_INT(Stat("MPx_H4CNF_BS_ENTR", c_index), (int)g_Features->m_CayoPericoEntry, 1);

		int bs_abil = 0;
		if (g_Features->m_CayoPericoSupportAirstrike)
			bs_abil += 1;
		if (g_Features->m_CayoPericoSupportSupplyDrop)
			bs_abil += 2;
		if (g_Features->m_CayoPericoSupportSniper)
			bs_abil += 4;
		if (g_Features->m_CayoPericoSupportHeliPickup)
			bs_abil += 8;
		if (g_Features->m_CayoPericoSupportReconDrone)
			bs_abil += 16;
		if (g_Features->m_CayoPericoSupportWeaponStash)
			bs_abil += 32;
		STATS::STAT_SET_INT(Stat("MPx_H4CNF_BS_ABIL", c_index), bs_abil, 1);

		STATS::STAT_SET_INT(Stat("MPx_H4_PLAYTHROUGH_STATUS", c_index), (int)g_Features->m_CayoPericoPlaythroughStatus, 1);

		int approach = 0;
		if (g_Features->m_CayoPericoApproachAirstrip)
			approach += 1;
		if (g_Features->m_CayoPericoApproachHaloJump)
			approach += 2;
		if (g_Features->m_CayoPericoApproachWestBeach)
			approach += 4;
		if (g_Features->m_CayoPericoApproachMainDock)
			approach += 8;
		if (g_Features->m_CayoPericoApproachNorthDock)
			approach += 16;
		if (g_Features->m_CayoPericoApproachNorthDrop)
			approach += 32;
		if (g_Features->m_CayoPericoApproachSouthDrop)
			approach += 64;
		if (g_Features->m_CayoPericoApproachDrainage)
			approach += 128;
		STATS::STAT_SET_INT(Stat("MPx_H4CNF_APPROACH", c_index), approach, 1);
		g_QueueScript->Add([]
						   { g_Features->DisplayNotification("~g~Cayo Perico settings applied"); });

		*ScriptGlobal(262145).Add(29227).As<int *>() = 1800 * g_Features->m_CayoPericoBagsizeMultiplier;
	}

	void Features::ApplyCayoPericoMaxPayout()
	{
		int h4_prog, target, c_index = GetCharacterIndex();
		STATS::STAT_GET_INT(Stat("MPx_H4_PROGRESS", c_index), &h4_prog, -1);
		STATS::STAT_GET_INT(Stat("MPx_H4CNF_TARGET", c_index), &target, -1);
		int amount = (h4_prog == (int)CayoPericoDifficulty::Hard ? 2634297 : 2897727) / g_Features->m_CayoPericoCut * 100;
		switch (target)
		{
		case 0:
			*ScriptGlobal(262145).Add(29461).As<int *>() = amount;
			break;
		case 1:
			*ScriptGlobal(262145).Add(29462).As<int *>() = amount;
			break;
		case 2:
			*ScriptGlobal(262145).Add(29463).As<int *>() = amount;
			break;
		case 3:
			*ScriptGlobal(262145).Add(29464).As<int *>() = amount;
			break;
		case 4:
			*ScriptGlobal(262145).Add(29465).As<int *>() = amount;
			break;
		case 5:
			*ScriptGlobal(262145).Add(29466).As<int *>() = amount;
			break;
		}

		STATS::STAT_SET_INT(Stat("MPx_H4LOOT_CASH_I", c_index), 1, 1);
		STATS::STAT_SET_INT(Stat("MPx_H4LOOT_CASH_C", c_index), 1, 1);
		STATS::STAT_SET_INT(Stat("MPx_H4LOOT_WEED_I", c_index), 1, 1);
		STATS::STAT_SET_INT(Stat("MPx_H4LOOT_WEED_C", c_index), 1, 1);
		STATS::STAT_SET_INT(Stat("MPx_H4LOOT_COKE_I", c_index), 1, 1);
		STATS::STAT_SET_INT(Stat("MPx_H4LOOT_COKE_C", c_index), 1, 1);
		STATS::STAT_SET_INT(Stat("MPx_H4LOOT_GOLD_I", c_index), 1, 1);
		STATS::STAT_SET_INT(Stat("MPx_H4LOOT_GOLD_C", c_index), 1, 1);
		STATS::STAT_SET_INT(Stat("MPx_H4LOOT_PAINT", c_index), 1, 1);
		STATS::STAT_SET_INT(Stat("MPx_H4LOOT_CASH_I_SCOPED", c_index), 1, 1);
		STATS::STAT_SET_INT(Stat("MPx_H4LOOT_CASH_C_SCOPED", c_index), 1, 1);
		STATS::STAT_SET_INT(Stat("MPx_H4LOOT_WEED_I_SCOPED", c_index), 1, 1);
		STATS::STAT_SET_INT(Stat("MPx_H4LOOT_WEED_C_SCOPED", c_index), 1, 1);
		STATS::STAT_SET_INT(Stat("MPx_H4LOOT_COKE_I_SCOPED", c_index), 1, 1);
		STATS::STAT_SET_INT(Stat("MPx_H4LOOT_COKE_C_SCOPED", c_index), 1, 1);
		STATS::STAT_SET_INT(Stat("MPx_H4LOOT_GOLD_I_SCOPED", c_index), 1, 1);
		STATS::STAT_SET_INT(Stat("MPx_H4LOOT_GOLD_C_SCOPED", c_index), 1, 1);
		STATS::STAT_SET_INT(Stat("MPx_H4LOOT_PAINT_SCOPED", c_index), 1, 1);
		g_QueueScript->Add([]
						   { g_Features->DisplayNotification("~g~Max payout applied"); });
	}

	void Features::ApplyDiamondCasino()
	{
		int bitset0, bitset1, c_index = GetCharacterIndex();
		;
		STATS::STAT_GET_INT(Stat("MPx_H3OPT_BITSET1", c_index), &bitset1, -1);
		if (bitset1 != 0)
		{
			STATS::STAT_SET_INT(Stat("MPx_H3OPT_BITSET1", c_index), 0, 1);
			g_QueueScript->Add([]
							   { g_QueueScript->Delay(5000ms); });
		}
		STATS::STAT_GET_INT(Stat("MPx_H3OPT_BITSET0", c_index), &bitset0, -1);
		if (bitset0 != 0)
		{
			STATS::STAT_SET_INT(Stat("MPx_H3OPT_BITSET0", c_index), 0, 1);
			g_QueueScript->Add([]
							   { g_QueueScript->Delay(5000ms); });
		}
		STATS::STAT_SET_INT(Stat("MPx_H3OPT_TARGET", c_index), (int)g_Features->m_CayoPericoMainTarget, 1);
		STATS::STAT_SET_INT(Stat("MPx_H3OPT_APPROACH", c_index), (int)g_Features->m_DiamondCasinoApproach, 1);

		// Update
		STATS::STAT_SET_INT(Stat("MPx_H3OPT_ACCESSPOINTS", c_index), 2047, 1);
		STATS::STAT_SET_INT(Stat("MPx_H3OPT_POI", c_index), 1023, 1);
		int access_points = 0;
		if (m_DiamondCasinoAccessPointMainDoor)
			access_points += 1;
		if (m_DiamondCasinoAccessPointNorthSideDoor)
			access_points += 2;
		if (m_DiamondCasinoAccessPointEastSideDoor)
			access_points += 4;
		if (m_DiamondCasinoAccessPointSouthwestRoofTerrace)
			access_points += 8;
		if (m_DiamondCasinoAccessPointSoutheastRoofTerrace)
			access_points += 16;
		if (m_DiamondCasinoAccessPointEastRoofTerrace)
			access_points += 32;
		if (m_DiamondCasinoAccessPoint_wag1memeing_com_)
			access_points += 64;
		if (m_DiamondCasinoAccessPointRoof)
			access_points += 128;
		if (m_DiamondCasinoAccessPointRoofStairs)
			access_points += 256;
		if (m_DiamondCasinoAccessPointSecurityTunnel)
			access_points += 512;
		if (m_DiamondCasinoAccessPointSewerTunnel)
			access_points += 1024;
		STATS::STAT_SET_INT(Stat("MPx_H3OPT_ACCESSPOINTS", c_index), access_points, 1);
		int poi = 0;
		if (m_DiamondCasinoPOIGuard)
			poi += 1;
		if (m_DiamondCasinoPOISecurityCamera)
			poi += 2;
		if (m_DiamondCasinoPOIKeypad)
			poi += 4;
		if (m_DiamondCasinoPOIValet)
			poi += 8;
		if (m_DiamondCasinoPOIOldCamera)
			poi += 16;
		if (m_DiamondCasinoPOISecurityOffice)
			poi += 32;
		if (m_DiamondCasinoPOIStaffLobby)
			poi += 64;
		if (m_DiamondCasinoPOIStaffDoor)
			poi += 128;
		if (m_DiamondCasinoPOIMetalDetectors)
			poi += 256;
		if (m_DiamondCasinoPOIStaffElevator)
			poi += 512;
		STATS::STAT_SET_INT(Stat("MPx_H3OPT_POI", c_index), poi, 1);
		STATS::STAT_SET_INT(Stat("MPx_H3OPT_BITSET1", c_index), -1, 1);
		g_QueueScript->Add([]
						   { g_QueueScript->Delay(5000ms); });
		STATS::STAT_SET_INT(Stat("MPx_H3OPT_DISRUPTSHIP", c_index), g_Features->m_DiamondCasinoDisrupt ? 3 : 0, 1);
		STATS::STAT_SET_INT(Stat("MPx_H3OPT_CREWWEAP", c_index), (int)g_Features->m_DiamondCasinoWeaponSmith, 1);
		STATS::STAT_SET_INT(Stat("MPx_H3OPT_WEAPS", c_index), (int)g_Features->m_DiamondCasinoWeapon, 1);
		STATS::STAT_SET_INT(Stat("MPx_H3OPT_CREWDRIVER", c_index), (int)g_Features->m_DiamondCasinoDriver, 1);
		if (g_Features->m_DiamondCasinoDriver == Features::DiamondCasinoDriver::KarimDenz || g_Features->m_DiamondCasinoDriver == Features::DiamondCasinoDriver::TalianaMartinez || g_Features->m_DiamondCasinoDriver == Features::DiamondCasinoDriver::EddieToh)
		{
			STATS::STAT_SET_INT(Stat("MPx_H3OPT_VEHS", c_index), (int)g_Features->m_DiamondCasinoVehicleType5, 1);
		}
		else
		{
			STATS::STAT_SET_INT(Stat("MPx_H3OPT_VEHS", c_index), (int)g_Features->m_DiamondCasinoVehicleType4, 1);
		}
		STATS::STAT_SET_INT(Stat("MPx_H3OPT_CREWHACKER", c_index), (int)g_Features->m_DiamondCasinoHacker, 1);
		STATS::STAT_SET_INT(Stat("MPx_H3OPT_KEYLEVELS", c_index), (int)g_Features->m_DiamondCasinoKeycard, 1);
		STATS::STAT_SET_INT(Stat("MPx_H3OPT_BITSET0", c_index), -1, 1);
		g_QueueScript->Add([]
						   { g_QueueScript->Delay(5000ms); });
		g_QueueScript->Add([]
						   { g_Features->DisplayNotification("~g~Diamond Casino settings applied"); });
	}
}