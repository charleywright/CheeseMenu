#include "Features.hpp"
#include "Natives.hpp"
#include "Lists.hpp"

namespace Big {
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

	void Features::ApplyCayoPerico() {
		if (g_Features->m_CayoPericoDifficulty == CayoPericoDifficulty::Hard) {
			STATS::STAT_SET_INT(CONSTEXPR_JOAAT("MP0_H4_PROGRESS"), 131055, 1);
		}
		else STATS::STAT_SET_INT(CONSTEXPR_JOAAT("MP0_H4_PROGRESS"), 126823, 1);

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
		if (g_Features->m_CayoPericoWeapon != CayoPericoWeapon::None) {
			h4_missions += 4096;
			STATS::STAT_SET_INT(CONSTEXPR_JOAAT("MP0_H4CNF_WEAPONS"), Lists::CayoPericoWeaponPosition, 1);
		} else STATS::STAT_SET_INT(CONSTEXPR_JOAAT("MP0_H4CNF_WEAPONS"), 0, 1);

		if (g_Features->m_CayoPericoDisruptWeapons) { 
			h4_missions += 8192; 
			STATS::STAT_SET_INT(CONSTEXPR_JOAAT("MP0_H4CNF_WEP_DISRP"), 3, 1);
		} else STATS::STAT_SET_INT(CONSTEXPR_JOAAT("MP0_H4CNF_WEP_DISRP"), 0, 1);
		if (g_Features->m_CayoPericoDisruptArmour) {
			h4_missions += 16384;
			STATS::STAT_SET_INT(CONSTEXPR_JOAAT("MP0_H4CNF_ARM_DISRP"), 3, 1);
		} else STATS::STAT_SET_INT(CONSTEXPR_JOAAT("MP0_H4CNF_ARM_DISRP"), 0, 1);
		if (g_Features->m_CayoPericoDisruptAirSupport) {
			h4_missions += 32768;
			STATS::STAT_SET_INT(CONSTEXPR_JOAAT("MP0_H4CNF_HEL_DISRP"), 3, 1);
		} else STATS::STAT_SET_INT(CONSTEXPR_JOAAT("MP0_H4CNF_HEL_DISRP"), 0, 1);

		STATS::STAT_SET_INT(CONSTEXPR_JOAAT("MP0_H4_MISSIONS"), h4_missions, 1);

		STATS::STAT_SET_INT(CONSTEXPR_JOAAT("MP0_H4CNF_TARGET"), Lists::CayoPericoMainTargetPosition, 1);
		STATS::STAT_SET_INT(CONSTEXPR_JOAAT("MP0_H4CNF_TROJAN"), Lists::CayoPericoSupplyTruckPosition, 1);
		if (g_Features->m_CayoPericoUnlockAllPOI) STATS::STAT_SET_INT(CONSTEXPR_JOAAT("MP0_H4CNF_BS_GEN"), 131071, 1);

		switch (g_Features->m_CayoPericoEntry) {
		case CayoPericoEntry::MainGate:
			STATS::STAT_SET_INT(CONSTEXPR_JOAAT("MP0_H4CNF_BS_ENTR"), 1, 1);
			break;
		case CayoPericoEntry::NorthWall:
			STATS::STAT_SET_INT(CONSTEXPR_JOAAT("MP0_H4CNF_BS_ENTR"), 2, 1);
			break;
		case CayoPericoEntry::NorthGate:
			STATS::STAT_SET_INT(CONSTEXPR_JOAAT("MP0_H4CNF_BS_ENTR"), 4, 1);
			break;
		case CayoPericoEntry::SouthWall:
			STATS::STAT_SET_INT(CONSTEXPR_JOAAT("MP0_H4CNF_BS_ENTR"), 8, 1);
			break;
		case CayoPericoEntry::SouthGate:
			STATS::STAT_SET_INT(CONSTEXPR_JOAAT("MP0_H4CNF_BS_ENTR"), 16, 1);
			break;
		case CayoPericoEntry::DrainageTunnel:
			STATS::STAT_SET_INT(CONSTEXPR_JOAAT("MP0_H4CNF_BS_ENTR"), 32, 1);
			break;
		}

		int bs_abil = 0;
		if (g_Features->m_CayoPericoSupportAirstrike) bs_abil += 1;
		if (g_Features->m_CayoPericoSupportSupplyDrop) bs_abil += 2;
		if (g_Features->m_CayoPericoSupportSniper) bs_abil += 4;
		if (g_Features->m_CayoPericoSupportHeliPickup) bs_abil += 8;
		if (g_Features->m_CayoPericoSupportReconDrone) bs_abil += 16;
		if (g_Features->m_CayoPericoSupportWeaponStash) bs_abil += 32;
		STATS::STAT_SET_INT(CONSTEXPR_JOAAT("MP0_H4CNF_BS_ABIL"), bs_abil, 1);

		switch (g_Features->m_CayoPericoPlaythroughStatus) {
		case CayoPericoPlaythroughStatus::First:
			STATS::STAT_SET_INT(CONSTEXPR_JOAAT("MP0_H4_PLAYTHROUGH_STATUS"), 0, 1);
			break;
		case CayoPericoPlaythroughStatus::Second:
			STATS::STAT_SET_INT(CONSTEXPR_JOAAT("MP0_H4_PLAYTHROUGH_STATUS"), 1, 1);
			break;
		case CayoPericoPlaythroughStatus::SkipCutscene:
			STATS::STAT_SET_INT(CONSTEXPR_JOAAT("MP0_H4_PLAYTHROUGH_STATUS"), 40000, 1);
			break;
		}

		int approach = 0;
		if (g_Features->m_CayoPericoApproachAirstrip) approach += 1;
		if (g_Features->m_CayoPericoApproachHaloJump) approach += 2;
		if (g_Features->m_CayoPericoApproachWestBeach) approach += 4;
		if (g_Features->m_CayoPericoApproachMainDock) approach += 8;
		if (g_Features->m_CayoPericoApproachNorthDock) approach += 16;
		if (g_Features->m_CayoPericoApproachNorthDrop) approach += 32;
		if (g_Features->m_CayoPericoApproachSouthDrop) approach += 64;
		if (g_Features->m_CayoPericoApproachDrainage) approach += 128;
		STATS::STAT_SET_INT(CONSTEXPR_JOAAT("MP0_H4CNF_APPROACH"), approach, 1);

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
	}
}