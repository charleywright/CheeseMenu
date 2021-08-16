#include "Features.hpp"
#include "Natives.hpp"
#include "Lists.hpp"
#include "RPLevels.hpp"
#include "QueueScript.hpp"

namespace Big {
	void Features::DisplayNotification(const char* text) {
		HUD::_SET_NOTIFICATION_TEXT_ENTRY("STRING");
		HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(text);
		HUD::_DRAW_NOTIFICATION(false, false);
	}

	void Features::EnterSession(int type) {
		*ScriptGlobal(1312854).As<int*>() = type;
		g_Logger->Info(std::to_string(type).c_str());
		MISC::SET_BIT(&*ScriptGlobal(1312443).As<int*>(), 1);
		MISC::SET_BIT(&*ScriptGlobal(1312443).As<int*>(), 0);
	}
	void Features::LeaveGTAOnline() {
		if (NETWORK::NETWORK_IS_SESSION_ACTIVE()) {
			*ScriptGlobal(1312443).Add(2).As<int*>() = -1;
			MISC::SET_BIT(&*ScriptGlobal(1312443).As<int*>(), 1);
			MISC::SET_BIT(&*ScriptGlobal(1312443).As<int*>(), 0);
		}
	}

	void Features::RPCorrection() {
		STATS::STAT_SET_INT(CONSTEXPR_JOAAT("MP0_CHAR_SET_RP_GIFT_ADMIN"), RPLevels[g_Features->m_RPCorrectionLevel - 1], 1);
		g_Features->DisplayNotification("~b~Change session to apply rank");
	}

	void Features::ApplyCayoPerico() {
		g_QueueScript->Add([] { STATS::STAT_SET_INT(CONSTEXPR_JOAAT("MP0_H4_PROGRESS"), (int)g_Features->m_CayoPericoDifficulty, 1); });

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
		g_QueueScript->Add([] { STATS::STAT_SET_INT(CONSTEXPR_JOAAT("MP0_H4CNF_WEAPONS"), (int)g_Features->m_CayoPericoWeapon, 1); });

		if (g_Features->m_CayoPericoDisruptWeapons) {
			h4_missions += 8192;
			g_QueueScript->Add([] { STATS::STAT_SET_INT(CONSTEXPR_JOAAT("MP0_H4CNF_WEP_DISRP"), 3, 1); });
		}
		else g_QueueScript->Add([] { STATS::STAT_SET_INT(CONSTEXPR_JOAAT("MP0_H4CNF_WEP_DISRP"), 0, 1); });
		if (g_Features->m_CayoPericoDisruptArmour) {
			h4_missions += 16384;
			g_QueueScript->Add([] { STATS::STAT_SET_INT(CONSTEXPR_JOAAT("MP0_H4CNF_ARM_DISRP"), 3, 1); });
		}
		else g_QueueScript->Add([] { STATS::STAT_SET_INT(CONSTEXPR_JOAAT("MP0_H4CNF_ARM_DISRP"), 0, 1); });
		if (g_Features->m_CayoPericoDisruptAirSupport) {
			h4_missions += 32768;
			g_QueueScript->Add([] { STATS::STAT_SET_INT(CONSTEXPR_JOAAT("MP0_H4CNF_HEL_DISRP"), 3, 1); });
		}
		else g_QueueScript->Add([] { STATS::STAT_SET_INT(CONSTEXPR_JOAAT("MP0_H4CNF_HEL_DISRP"), 0, 1); });

		g_QueueScript->Add([&] { STATS::STAT_SET_INT(CONSTEXPR_JOAAT("MP0_H4_MISSIONS"), h4_missions, 1); });

		g_QueueScript->Add([] { STATS::STAT_SET_INT(CONSTEXPR_JOAAT("MP0_H4CNF_TARGET"), (int)g_Features->m_CayoPericoMainTarget, 1); });
		g_QueueScript->Add([] { STATS::STAT_SET_INT(CONSTEXPR_JOAAT("MP0_H4CNF_TROJAN"), (int)g_Features->m_CayoPericoSupplyTruck, 1); });
		if (g_Features->m_CayoPericoUnlockAllPOI) g_QueueScript->Add([] { STATS::STAT_SET_INT(CONSTEXPR_JOAAT("MP0_H4CNF_BS_GEN"), 131071, 1); });

		g_QueueScript->Add([] { STATS::STAT_SET_INT(CONSTEXPR_JOAAT("MP0_H4CNF_BS_ENTR"), (int)g_Features->m_CayoPericoEntry, 1); });

		int bs_abil = 0;
		if (g_Features->m_CayoPericoSupportAirstrike) bs_abil += 1;
		if (g_Features->m_CayoPericoSupportSupplyDrop) bs_abil += 2;
		if (g_Features->m_CayoPericoSupportSniper) bs_abil += 4;
		if (g_Features->m_CayoPericoSupportHeliPickup) bs_abil += 8;
		if (g_Features->m_CayoPericoSupportReconDrone) bs_abil += 16;
		if (g_Features->m_CayoPericoSupportWeaponStash) bs_abil += 32;
		g_QueueScript->Add([&] { STATS::STAT_SET_INT(CONSTEXPR_JOAAT("MP0_H4CNF_BS_ABIL"), bs_abil, 1); });

		g_QueueScript->Add([] { STATS::STAT_SET_INT(CONSTEXPR_JOAAT("MP0_H4_PLAYTHROUGH_STATUS"), (int)g_Features->m_CayoPericoPlaythroughStatus, 1); });

		int approach = 0;
		if (g_Features->m_CayoPericoApproachAirstrip) approach += 1;
		if (g_Features->m_CayoPericoApproachHaloJump) approach += 2;
		if (g_Features->m_CayoPericoApproachWestBeach) approach += 4;
		if (g_Features->m_CayoPericoApproachMainDock) approach += 8;
		if (g_Features->m_CayoPericoApproachNorthDock) approach += 16;
		if (g_Features->m_CayoPericoApproachNorthDrop) approach += 32;
		if (g_Features->m_CayoPericoApproachSouthDrop) approach += 64;
		if (g_Features->m_CayoPericoApproachDrainage) approach += 128;
		g_QueueScript->Add([&] { STATS::STAT_SET_INT(CONSTEXPR_JOAAT("MP0_H4CNF_APPROACH"), approach, 1); });
		g_QueueScript->Add([] { g_Features->DisplayNotification("~g~Cayo Perico settings applied"); });

		*ScriptGlobal(262145).Add(29227).As<int*>() = 1800 * g_Features->m_CayoPericoBagsizeMultiplier;
	}

	void Features::ApplyCayoPericoMaxPayout() {
		int h4_prog, target;
		STATS::STAT_GET_INT(CONSTEXPR_JOAAT("MP0_H4_PROGRESS"), &h4_prog, -1);
		STATS::STAT_GET_INT(CONSTEXPR_JOAAT("MP0_H4CNF_TARGET"), &target, -1);
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

		g_QueueScript->Add([] { STATS::STAT_SET_INT(CONSTEXPR_JOAAT("MP0_H4LOOT_CASH_I"), 0, 1); });
		g_QueueScript->Add([] { STATS::STAT_SET_INT(CONSTEXPR_JOAAT("MP0_H4LOOT_CASH_C"), 0, 1); });
		g_QueueScript->Add([] { STATS::STAT_SET_INT(CONSTEXPR_JOAAT("MP0_H4LOOT_WEED_I"), 0, 1); });
		g_QueueScript->Add([] { STATS::STAT_SET_INT(CONSTEXPR_JOAAT("MP0_H4LOOT_WEED_C"), 0, 1); });
		g_QueueScript->Add([] { STATS::STAT_SET_INT(CONSTEXPR_JOAAT("MP0_H4LOOT_COKE_I"), 0, 1); });
		g_QueueScript->Add([] { STATS::STAT_SET_INT(CONSTEXPR_JOAAT("MP0_H4LOOT_COKE_C"), 0, 1); });
		g_QueueScript->Add([] { STATS::STAT_SET_INT(CONSTEXPR_JOAAT("MP0_H4LOOT_GOLD_I"), 0, 1); });
		g_QueueScript->Add([] { STATS::STAT_SET_INT(CONSTEXPR_JOAAT("MP0_H4LOOT_GOLD_C"), 0, 1); });
		g_QueueScript->Add([] { STATS::STAT_SET_INT(CONSTEXPR_JOAAT("MP0_H4LOOT_PAINT"), 0, 1); });
		g_QueueScript->Add([] { STATS::STAT_SET_INT(CONSTEXPR_JOAAT("MP0_H4LOOT_CASH_I_SCOPED"), 0, 1); });
		g_QueueScript->Add([] { STATS::STAT_SET_INT(CONSTEXPR_JOAAT("MP0_H4LOOT_CASH_C_SCOPED"), 0, 1); });
		g_QueueScript->Add([] { STATS::STAT_SET_INT(CONSTEXPR_JOAAT("MP0_H4LOOT_WEED_I_SCOPED"), 0, 1); });
		g_QueueScript->Add([] { STATS::STAT_SET_INT(CONSTEXPR_JOAAT("MP0_H4LOOT_WEED_C_SCOPED"), 0, 1); });
		g_QueueScript->Add([] { STATS::STAT_SET_INT(CONSTEXPR_JOAAT("MP0_H4LOOT_COKE_I_SCOPED"), 0, 1); });
		g_QueueScript->Add([] { STATS::STAT_SET_INT(CONSTEXPR_JOAAT("MP0_H4LOOT_COKE_C_SCOPED"), 0, 1); });
		g_QueueScript->Add([] { STATS::STAT_SET_INT(CONSTEXPR_JOAAT("MP0_H4LOOT_GOLD_I_SCOPED"), 0, 1); });
		g_QueueScript->Add([] { STATS::STAT_SET_INT(CONSTEXPR_JOAAT("MP0_H4LOOT_GOLD_C_SCOPED"), 0, 1); });
		g_QueueScript->Add([] { STATS::STAT_SET_INT(CONSTEXPR_JOAAT("MP0_H4LOOT_PAINT_SCOPED"), 0, 1); });
		g_QueueScript->Add([] { g_Features->DisplayNotification("~g~Max payout applied"); });
	}

	void Features::ApplyDiamondCasino() {
		int bitset1;
		STATS::STAT_GET_INT(CONSTEXPR_JOAAT("MP0_H3OPT_BITSET1"), &bitset1, -1);
		if (bitset1 != 0) {
			g_QueueScript->Add([] { STATS::STAT_SET_INT(CONSTEXPR_JOAAT("MP0_H3OPT_BITSET1"), 0, 1); });
			g_QueueScript->Add([] { g_QueueScript->Delay(5000ms); });
		}
		int bitset0;
		STATS::STAT_GET_INT(CONSTEXPR_JOAAT("MP0_H3OPT_BITSET0"), &bitset0, -1);
		if (bitset0 != 0) {
			g_QueueScript->Add([] { STATS::STAT_SET_INT(CONSTEXPR_JOAAT("MP0_H3OPT_BITSET0"), 0, 1); });
			g_QueueScript->Add([] { g_QueueScript->Delay(5000ms); });
		}
		g_QueueScript->Add([] { STATS::STAT_SET_INT(CONSTEXPR_JOAAT("MP0_H3OPT_TARGET"), (int)g_Features->m_CayoPericoMainTarget, 1); });
		g_QueueScript->Add([] { STATS::STAT_SET_INT(CONSTEXPR_JOAAT("MP0_H3OPT_APPROACH"), (int)g_Features->m_DiamondCasinoApproach, 1); });
		g_QueueScript->Add([] { STATS::STAT_SET_INT(CONSTEXPR_JOAAT("MP0_H3OPT_BITSET1"), -1, 1); });
		g_QueueScript->Add([] { g_QueueScript->Delay(5000ms); });
		g_QueueScript->Add([] { STATS::STAT_SET_INT(CONSTEXPR_JOAAT("MP0_H3OPT_DISRUPTSHIP"), g_Features->m_DiamondCasinoDisrupt ? 3 : 0, 1); });
		g_QueueScript->Add([] { STATS::STAT_SET_INT(CONSTEXPR_JOAAT("MP0_H3OPT_CREWWEAP"), (int)g_Features->m_DiamondCasinoWeaponSmith, 1); });
		g_QueueScript->Add([] { STATS::STAT_SET_INT(CONSTEXPR_JOAAT("MP0_H3OPT_WEAPS"), (int)g_Features->m_DiamondCasinoWeapon, 1); });
		g_QueueScript->Add([] { STATS::STAT_SET_INT(CONSTEXPR_JOAAT("MP0_H3OPT_CREWDRIVER"), (int)g_Features->m_DiamondCasinoDriver, 1); });
		if (g_Features->m_DiamondCasinoDriver == Features::DiamondCasinoDriver::KarimDenz || g_Features->m_DiamondCasinoDriver == Features::DiamondCasinoDriver::TalianaMartinez || g_Features->m_DiamondCasinoDriver == Features::DiamondCasinoDriver::EddieToh) {
			g_QueueScript->Add([] { STATS::STAT_SET_INT(CONSTEXPR_JOAAT("MPx_H3OPT_VEHS"), (int)g_Features->m_DiamondCasinoVehicleType5, 1); });
		}
		else {
			g_QueueScript->Add([] { STATS::STAT_SET_INT(CONSTEXPR_JOAAT("MPx_H3OPT_VEHS"), (int)g_Features->m_DiamondCasinoVehicleType4, 1); });
		}
		g_QueueScript->Add([] { STATS::STAT_SET_INT(CONSTEXPR_JOAAT("MPx_H3OPT_CREWHACKER"), (int)g_Features->m_DiamondCasinoHacker, 1); });
		g_QueueScript->Add([] { STATS::STAT_SET_INT(CONSTEXPR_JOAAT("MP0_H3OPT_KEYLEVELS"), (int)g_Features->m_DiamondCasinoKeycard, 1); });
		g_QueueScript->Add([] { STATS::STAT_SET_INT(CONSTEXPR_JOAAT("MP0_H3OPT_BITSET0"), -1, 1); });
		g_QueueScript->Add([] { g_QueueScript->Delay(5000ms); });
		g_QueueScript->Add([] { g_Features->DisplayNotification("~g~Diamond Casino settings applied"); });
	}
}