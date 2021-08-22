#include "Features.hpp"
#include "Natives.hpp"
#include "Lists.hpp"
#include "RPLevels.hpp"
#include "QueueScript.hpp"

std::string GetStatString(std::string stat, int character) {
	switch (character) {
	case 0:
		stat[2] = '0';
		break;
	case 1:
		stat[2] = '1';
		break;
	}
	return stat;
}

int GetCharacterIndex() {
	int i;
	Big::STATS::STAT_GET_INT(CONSTEXPR_JOAAT("MPPLY_LAST_MP_CHAR"), &i, -1);
	return i;
}

void OffMap(int type) {
	Big::g_QueueScript->Add([] { *Big::ScriptGlobal(2426865).Add(1).Add(*Big::ScriptGlobal(2441237).As<int*>() * 449).Add(209).As<int*>() = 1; });
	Big::g_QueueScript->Add([] { *Big::ScriptGlobal(2441237).Add(70).As<int*>() = *Big::ScriptGlobal(1312603).Add(11).As<int*>(); });
	Big::g_QueueScript->Add([type] { *Big::ScriptGlobal(2544210).Add(4628).As<int*>() = type; });
}

namespace Big {
	void Features::SetIntStat(const char* s, int c, int value) {
		std::string stat = GetStatString(std::string(s), c);
		g_QueueScript->Add([stat, value] { STATS::STAT_SET_INT(Joaat(stat.c_str()), value, 1); });
	}

	void Features::GetIntStat(const char* s, int c, int *value) {
		std::string stat = GetStatString(std::string(s), c);
		STATS::STAT_GET_INT(Joaat(stat.c_str()), value, -1);
	}

	void Features::OffRadar() { OffMap(3); }

	void Features::GhostOrg() { OffMap(4); }

	void Features::EnableAntiAfkKick() {
		g_QueueScript->Add([] { *ScriptGlobal(262145).Add(87).As<int*>() = 99999999; });
		g_QueueScript->Add([] { *ScriptGlobal(262145).Add(88).As<int*>() = 99999999; });
		g_QueueScript->Add([] { *ScriptGlobal(262145).Add(89).As<int*>() = 99999999; });
		g_QueueScript->Add([] { *ScriptGlobal(262145).Add(90).As<int*>() = 99999999; });
		g_QueueScript->Add([] { *ScriptGlobal(262145).Add(7958).As<int*>() = 2000000000; });
		g_QueueScript->Add([] { *ScriptGlobal(262145).Add(7955).As<int*>() = 2000000000; });
		g_QueueScript->Add([] { *ScriptGlobal(262145).Add(7956).As<int*>() = 2000000000; });
		g_QueueScript->Add([] { *ScriptGlobal(262145).Add(7957).As<int*>() = 2000000000; });
		g_QueueScript->Add([] { g_Features->DisplayNotification("~g~Enabled Anti AFK kick"); });
	}

	void Features::DisableAntiAfkKick() {
		g_QueueScript->Add([] { *ScriptGlobal(262145).Add(87).As<int*>() = 120000; });
		g_QueueScript->Add([] { *ScriptGlobal(262145).Add(88).As<int*>() = 300000; });
		g_QueueScript->Add([] { *ScriptGlobal(262145).Add(89).As<int*>() = 600000; });
		g_QueueScript->Add([] { *ScriptGlobal(262145).Add(90).As<int*>() = 900000; });
		g_QueueScript->Add([] { *ScriptGlobal(262145).Add(7958).As<int*>() = 30000; });
		g_QueueScript->Add([] { *ScriptGlobal(262145).Add(7955).As<int*>() = 60000; });
		g_QueueScript->Add([] { *ScriptGlobal(262145).Add(7956).As<int*>() = 90000; });
		g_QueueScript->Add([] { *ScriptGlobal(262145).Add(7957).As<int*>() = 120000; });
		g_QueueScript->Add([] { g_Features->DisplayNotification("~r~Disabled Anti AFK kick"); });
	}

	void Features::DisplayNotification(const char* text) {
		HUD::_SET_NOTIFICATION_TEXT_ENTRY("STRING");
		HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(text);
		HUD::_DRAW_NOTIFICATION(false, false);
	}

	void Features::EnterSession(int type) {
		g_QueueScript->Add([type] {*ScriptGlobal(1312860).As<int*>() = type; });
		g_QueueScript->Add([] {*ScriptGlobal(1312443).As<int*>() = 1; });
		g_QueueScript->Delay(200ms);
		g_QueueScript->Add([] {*ScriptGlobal(1312443).As<int*>() = 0; });
	}
	void Features::LeaveGTAOnline() {
		if (NETWORK::NETWORK_IS_SESSION_ACTIVE()) {
			g_QueueScript->Add([] {*ScriptGlobal(1312443).Add(2).As<int*>() = -1; });
			g_QueueScript->Add([] {*ScriptGlobal(1312443).As<int*>() = 1; });
			g_QueueScript->Delay(200ms);
			g_QueueScript->Add([] {*ScriptGlobal(1312443).As<int*>() = 0; });
		}
	}

	void Features::RPCorrection() {
		int c_index = GetCharacterIndex();
		g_Features->SetIntStat("MPx_CHAR_SET_RP_GIFT_ADMIN", c_index, RPLevels[g_Features->m_RPCorrectionLevel - 1]);
		g_QueueScript->Add([] { g_Features->DisplayNotification("~b~Change session to apply rank"); });
	}

	void Features::MaxStats() {
		int c_index = GetCharacterIndex();
		g_Features->SetIntStat("MPx_SCRIPT_INCREASE_STAM", c_index, 100);
		g_Features->SetIntStat("MPx_SCRIPT_INCREASE_STRN", c_index, 100);
		g_Features->SetIntStat("MPx_SCRIPT_INCREASE_LUNG", c_index, 100);
		g_Features->SetIntStat("MPx_SCRIPT_INCREASE_DRIV", c_index, 100);
		g_Features->SetIntStat("MPx_SCRIPT_INCREASE_FLY", c_index, 100);
		g_Features->SetIntStat("MPx_SCRIPT_INCREASE_SHO", c_index, 100);
		g_Features->SetIntStat("MPx_SCRIPT_INCREASE_STL", c_index, 100);
		g_Features->SetIntStat("MPx_SCRIPT_INCREASE_MECH", c_index, 100);
		g_QueueScript->Add([] { g_Features->DisplayNotification("Maxed stats"); });
	}

	void Features::MaxSnacks() {
		int c_index = GetCharacterIndex();
		g_Features->SetIntStat("MPx_NO_BOUGHT_YUM_SNACKS", c_index, INT_MAX);
		g_Features->SetIntStat("MPx_NO_BOUGHT_HEALTH_SNACKS", c_index, INT_MAX);
		g_Features->SetIntStat("MPx_NO_BOUGHT_EPIC_SNACKS", c_index, INT_MAX);
		g_Features->SetIntStat("MPx_NUMBER_OF_ORANGE_BOUGHT", c_index, INT_MAX);
		g_Features->SetIntStat("MPx_NUMBER_OF_BOURGE_BOUGHT", c_index, INT_MAX);
		g_Features->SetIntStat("MPx_CIGARETTES_BOUGHT", c_index, INT_MAX);
		g_QueueScript->Add([] { g_Features->DisplayNotification("Maxed Snacks"); });
	}

	void Features::MaxArmour() {
		int c_index = GetCharacterIndex();
		g_Features->SetIntStat("MPx_MP_CHAR_ARMOUR_1_COUNT", c_index, INT_MAX);
		g_Features->SetIntStat("MPx_MP_CHAR_ARMOUR_2_COUNT", c_index, INT_MAX);
		g_Features->SetIntStat("MPx_MP_CHAR_ARMOUR_3_COUNT", c_index, INT_MAX);
		g_Features->SetIntStat("MPx_MP_CHAR_ARMOUR_4_COUNT", c_index, INT_MAX);
		g_Features->SetIntStat("MPx_MP_CHAR_ARMOUR_5_COUNT", c_index, INT_MAX);
		g_QueueScript->Add([] { g_Features->DisplayNotification("Maxed Armour"); });
	}

	void Features::DoomsdayPrerequisite() {
		int c_index = GetCharacterIndex();
		g_Features->SetIntStat("MPx_GANGOPS_HEIST_STATUS", c_index, 9999);
		g_QueueScript->Add([] { g_Features->DisplayNotification("~g~Call lester and cancel all 3 heists"); });
	}

	void Features::SkipAct1() {
		int c_index = GetCharacterIndex();
		g_Features->SetIntStat("MPx_GANGOPS_FLOW_MISSION_PROG", c_index, 503);
		g_Features->SetIntStat("MPx_GANGOPS_HEIST_STATUS", c_index, 229383);
		g_Features->SetIntStat("MPx_GANGOPS_FLOW_NOTIFICATIONS", c_index, 1557);
		g_QueueScript->Add([] { g_Features->DisplayNotification("~g~Skipped Act 1 preps & setups"); });
	}

	void Features::SkipAct2() {
		int c_index = GetCharacterIndex();
		g_Features->SetIntStat("MPx_GANGOPS_FLOW_MISSION_PROG", c_index, 240);
		g_Features->SetIntStat("MPx_GANGOPS_HEIST_STATUS", c_index, 229378);
		g_Features->SetIntStat("MPx_GANGOPS_FLOW_NOTIFICATIONS", c_index, 1557);
		g_QueueScript->Add([] { g_Features->DisplayNotification("~g~Skipped Act 2 preps & setups"); });
	}

	void Features::SkipAct3() {
		int c_index = GetCharacterIndex();
		g_Features->SetIntStat("MPx_GANGOPS_FLOW_MISSION_PROG", c_index, 16368);
		g_Features->SetIntStat("MPx_GANGOPS_HEIST_STATUS", c_index, 229380);
		g_Features->SetIntStat("MPx_GANGOPS_FLOW_NOTIFICATIONS", c_index, 1557);
		g_QueueScript->Add([] { g_Features->DisplayNotification("~g~Skipped Act 3 preps & setups"); });
	}

	void Features::ApplyCayoPerico() {
		int c_index = GetCharacterIndex();
		g_Features->SetIntStat("MPx_H4_PROGRESS", c_index, (int)g_Features->m_CayoPericoDifficulty);

		int h4_missions = 1;
		if (g_Features->m_CayoPericoKosatka) h4_missions += 2;
		if (g_Features->m_CayoPericoVelum) h4_missions += 8;
		if (g_Features->m_CayoPericoAnnihilator) h4_missions += 16;
		if (g_Features->m_CayoPericoPatrolBoat) h4_missions += 32;
		if (g_Features->m_CayoPericoLongfin) h4_missions += 64;
		if (g_Features->m_CayoPericoAlkonostAndStealthHeli) h4_missions += 132;

		if (g_Features->m_CayoPericoDemolitionCharges) h4_missions += 256;
		if (g_Features->m_CayoPericoCuttingTorch) h4_missions += 512;
		if (g_Features->m_CayoPericoPrimaryTool) h4_missions += 1024;
		if (g_Features->m_CayoPericoFingerprint) h4_missions += 2048;

		g_Features->SetIntStat("MPx_H4CNF_WEAPONS", c_index, (int)g_Features->m_CayoPericoWeapon);

		if (g_Features->m_CayoPericoDisruptWeapons) {
			h4_missions += 8192;
			g_Features->SetIntStat("MPx_H4CNF_WEP_DISRP", c_index, 3);
		}
		else g_Features->SetIntStat("MPx_H4CNF_WEP_DISRP", c_index, 0);
		if (g_Features->m_CayoPericoDisruptArmour) {
			h4_missions += 16384;
			g_Features->SetIntStat("MPx_H4CNF_ARM_DISRP", c_index, 3);
		}
		else g_Features->SetIntStat("MPx_H4CNF_ARM_DISRP", c_index, 0);
		
		
		if (g_Features->m_CayoPericoDisruptAirSupport) {
			h4_missions += 32768;
			g_Features->SetIntStat("MPx_H4CNF_HEL_DISRP", c_index, 3);
		}
		else g_Features->SetIntStat("MPx_H4CNF_HEL_DISRP", c_index, 0);

		g_Features->SetIntStat("MPx_H4_MISSIONS", c_index, h4_missions);

		g_Features->SetIntStat("MPx_H4CNF_TARGET", c_index, (int)g_Features->m_CayoPericoMainTarget);
		g_Features->SetIntStat("MPx_H4CNF_TROJAN", c_index, (int)g_Features->m_CayoPericoSupplyTruck);
		
		if (g_Features->m_CayoPericoUnlockAllPOI) g_Features->SetIntStat("MPx_H4CNF_BS_GEN", c_index, 131071);

		g_Features->SetIntStat("MPx_H4CNF_BS_ENTR", c_index, (int)g_Features->m_CayoPericoEntry);

		int bs_abil = 0;
		if (g_Features->m_CayoPericoSupportAirstrike) bs_abil += 1;
		if (g_Features->m_CayoPericoSupportSupplyDrop) bs_abil += 2;
		if (g_Features->m_CayoPericoSupportSniper) bs_abil += 4;
		if (g_Features->m_CayoPericoSupportHeliPickup) bs_abil += 8;
		if (g_Features->m_CayoPericoSupportReconDrone) bs_abil += 16;
		if (g_Features->m_CayoPericoSupportWeaponStash) bs_abil += 32;
		g_Features->SetIntStat("MPx_H4CNF_BS_ABIL", c_index, bs_abil);

		g_Features->SetIntStat("MPx_H4_PLAYTHROUGH_STATUS", c_index, (int)g_Features->m_CayoPericoPlaythroughStatus);

		int approach = 0;
		if (g_Features->m_CayoPericoApproachAirstrip) approach += 1;
		if (g_Features->m_CayoPericoApproachHaloJump) approach += 2;
		if (g_Features->m_CayoPericoApproachWestBeach) approach += 4;
		if (g_Features->m_CayoPericoApproachMainDock) approach += 8;
		if (g_Features->m_CayoPericoApproachNorthDock) approach += 16;
		if (g_Features->m_CayoPericoApproachNorthDrop) approach += 32;
		if (g_Features->m_CayoPericoApproachSouthDrop) approach += 64;
		if (g_Features->m_CayoPericoApproachDrainage) approach += 128;
		g_Features->SetIntStat("MPx_H4CNF_APPROACH", c_index, approach);
		g_QueueScript->Add([] { g_Features->DisplayNotification("~g~Cayo Perico settings applied"); });

		*ScriptGlobal(262145).Add(29227).As<int*>() = 1800 * g_Features->m_CayoPericoBagsizeMultiplier;
	}

	void Features::ApplyCayoPericoMaxPayout() {
		int h4_prog, target, c_index = GetCharacterIndex();
		g_Features->GetIntStat("MPx_H4_PROGRESS", c_index, &h4_prog);
		g_Features->GetIntStat("MPx_H4CNF_TARGET", c_index, &target);
		int amount = (h4_prog == 131055 ? 2634297 : 2897727) / g_Features->m_CayoPericoCut * 100;
		switch (target) {
		case 0:
			*ScriptGlobal(262145).Add(29461).As<int*>() = amount;
			break;
		case 1:
			*ScriptGlobal(262145).Add(29462).As<int*>() = amount;
			break;
		case 2:
			*ScriptGlobal(262145).Add(29463).As<int*>() = amount;
			break;
		case 3:
			*ScriptGlobal(262145).Add(29464).As<int*>() = amount;
			break;
		case 4:
			*ScriptGlobal(262145).Add(29465).As<int*>() = amount;
			break;
		case 5:
			*ScriptGlobal(262145).Add(29466).As<int*>() = amount;
			break;
		}

		g_Features->SetIntStat("MPx_H4LOOT_CASH_I", c_index, 1);
		g_Features->SetIntStat("MPx_H4LOOT_CASH_C", c_index, 1);
		g_Features->SetIntStat("MPx_H4LOOT_WEED_I", c_index, 1);
		g_Features->SetIntStat("MPx_H4LOOT_WEED_C", c_index, 1);
		g_Features->SetIntStat("MPx_H4LOOT_COKE_I", c_index, 1);
		g_Features->SetIntStat("MPx_H4LOOT_COKE_C", c_index, 1);
		g_Features->SetIntStat("MPx_H4LOOT_GOLD_I", c_index, 1);
		g_Features->SetIntStat("MPx_H4LOOT_GOLD_C", c_index, 1);
		g_Features->SetIntStat("MPx_H4LOOT_PAINT", c_index, 1);
		g_Features->SetIntStat("MPx_H4LOOT_CASH_I_SCOPED", c_index, 1);
		g_Features->SetIntStat("MPx_H4LOOT_CASH_C_SCOPED", c_index, 1);
		g_Features->SetIntStat("MPx_H4LOOT_WEED_I_SCOPED", c_index, 1);
		g_Features->SetIntStat("MPx_H4LOOT_WEED_C_SCOPED", c_index, 1);
		g_Features->SetIntStat("MPx_H4LOOT_COKE_I_SCOPED", c_index, 1);
		g_Features->SetIntStat("MPx_H4LOOT_COKE_C_SCOPED", c_index, 1);
		g_Features->SetIntStat("MPx_H4LOOT_GOLD_I_SCOPED", c_index, 1);
		g_Features->SetIntStat("MPx_H4LOOT_GOLD_C_SCOPED", c_index, 1);
		g_Features->SetIntStat("MPx_H4LOOT_PAINT_SCOPED", c_index, 1);
		g_QueueScript->Add([] { g_Features->DisplayNotification("~g~Max payout applied"); });
	}

	void Features::ApplyDiamondCasino() {
		int bitset0, bitset1, c_index = GetCharacterIndex();;
		g_Features->GetIntStat("MPx_H3OPT_BITSET1", c_index, &bitset1);
		if (bitset1 != 0) {
			g_Features->SetIntStat("MPx_H3OPT_BITSET1", c_index, 0);
			g_QueueScript->Add([] { g_QueueScript->Delay(5000ms); });
		}
		g_Features->GetIntStat("MPx_H3OPT_BITSET0", c_index, &bitset0);
		if (bitset0 != 0) {
			g_Features->SetIntStat("MPx_H3OPT_BITSET0", c_index, 0);
			g_QueueScript->Add([] { g_QueueScript->Delay(5000ms); });
		}
		g_Features->SetIntStat("MPx_H3OPT_TARGET", c_index, (int)g_Features->m_CayoPericoMainTarget);
		g_Features->SetIntStat("MPx_H3OPT_APPROACH", c_index, (int)g_Features->m_DiamondCasinoApproach);
		g_Features->SetIntStat("MPx_H3OPT_ACCESSPOINTS", c_index, 2047);
		g_Features->SetIntStat("MPx_H3OPT_POI", c_index, 1023);
		g_Features->SetIntStat("MPx_H3OPT_BITSET1", c_index, -1);
		g_QueueScript->Add([] { g_QueueScript->Delay(5000ms); });
		g_Features->SetIntStat("MPx_H3OPT_DISRUPTSHIP", c_index, g_Features->m_DiamondCasinoDisrupt ? 3 : 0);
		g_Features->SetIntStat("MPx_H3OPT_CREWWEAP", c_index, (int)g_Features->m_DiamondCasinoWeaponSmith);
		g_Features->SetIntStat("MPx_H3OPT_WEAPS", c_index, (int)g_Features->m_DiamondCasinoWeapon);
		g_Features->SetIntStat("MPx_H3OPT_CREWDRIVER", c_index, (int)g_Features->m_DiamondCasinoDriver);
		if (g_Features->m_DiamondCasinoDriver == Features::DiamondCasinoDriver::KarimDenz || g_Features->m_DiamondCasinoDriver == Features::DiamondCasinoDriver::TalianaMartinez || g_Features->m_DiamondCasinoDriver == Features::DiamondCasinoDriver::EddieToh) {
			g_Features->SetIntStat("MPx_H3OPT_VEHS", c_index, (int)g_Features->m_DiamondCasinoVehicleType5);
		}
		else {
			g_Features->SetIntStat("MPx_H3OPT_VEHS", c_index, (int)g_Features->m_DiamondCasinoVehicleType4);
		}
		g_Features->SetIntStat("MPx_H3OPT_CREWHACKER", c_index, (int)g_Features->m_DiamondCasinoHacker);
		g_Features->SetIntStat("MPx_H3OPT_KEYLEVELS", c_index, (int)g_Features->m_DiamondCasinoKeycard);
		g_Features->SetIntStat("MPx_H3OPT_BITSET0", c_index, -1);
		g_QueueScript->Add([] { g_QueueScript->Delay(5000ms); });
		g_QueueScript->Add([] { g_Features->DisplayNotification("~g~Diamond Casino settings applied"); });
	}
}