#pragma once
#include "Script.hpp"

namespace Big
{
	class Features
	{
	public:
		void EnterSession(int type);
		void LeaveGTAOnline();
		
		// Cayo Perico Heist
		void ApplyCayoPerico();
		void ApplyCayoPericoMaxPayout();

		enum class CayoPericoDifficulty : int {
			Normal = 0,
			Hard = 1
		};

		enum class CayoPericoMainTarget : int {
			Tequila = 0,
			RubyNecklace = 1,
			BearerBonds = 2,
			PinkDiamond = 3,
			MadrazoFiles = 4,
			SapphirePanther = 5
		};
		
		enum class CayoPericoWeapon : int {
			None = 0,
			Aggressor = 1,
			Conspirator = 2,
			Crackshot = 3,
			Soboteur = 4,
			Marksman = 5
		};

		enum class CayoPericoSupplyTruck : int {
			Airport = 0,
			NorthDock = 1,
			MainDockEast = 2,
			MainDockWest = 3,
			InsideCompound = 4
		};

		enum class CayoPericoEntry : int {
			MainGate = 0,
			NorthWall = 1,
			NorthGate = 2,
			SouthWall = 3,
			SouthGate = 4,
			DrainageTunnel = 5
		};

		enum class CayoPericoPlaythroughStatus : int {
			First = 0,
			Second = 1,
			SkipCutscene = 2
		};

		CayoPericoDifficulty m_CayoPericoDifficulty = CayoPericoDifficulty::Normal;
		bool m_CayoPericoKosatka = true;
		bool m_CayoPericoVelum = false;
		bool m_CayoPericoAnnihilator = false;
		bool m_CayoPericoPatrolBoat = false;
		bool m_CayoPericoLongfin = false;
		bool m_CayoPericoAlkonostAndStealthHeli = false;
		bool m_CayoPericoDemolitionCharges = false;
		bool m_CayoPericoCuttingTorch = true;
		bool m_CayoPericoPrimaryTool = true;
		bool m_CayoPericoFingerprint = true;
		bool m_CayoPericoDisruptWeapons = true;
		bool m_CayoPericoDisruptArmour = true;
		bool m_CayoPericoDisruptAirSupport = true;
		bool m_CayoPericoUnlockAllPOI = true;
		CayoPericoMainTarget m_CayoPericoMainTarget = CayoPericoMainTarget::SapphirePanther;
		CayoPericoWeapon m_CayoPericoWeapon = CayoPericoWeapon::Aggressor;
		CayoPericoSupplyTruck m_CayoPericoSupplyTruck = CayoPericoSupplyTruck::InsideCompound;
		CayoPericoEntry m_CayoPericoEntry = CayoPericoEntry::DrainageTunnel;
		bool m_CayoPericoSupportAirstrike = true;
		bool m_CayoPericoSupportSupplyDrop = true;
		bool m_CayoPericoSupportSniper = true;
		bool m_CayoPericoSupportHeliPickup = true;
		bool m_CayoPericoSupportReconDrone = true;
		bool m_CayoPericoSupportWeaponStash = true;
		CayoPericoPlaythroughStatus m_CayoPericoPlaythroughStatus = CayoPericoPlaythroughStatus::SkipCutscene;
		bool m_CayoPericoApproachAirstrip = false;
		bool m_CayoPericoApproachHaloJump = false;
		bool m_CayoPericoApproachWestBeach = false;
		bool m_CayoPericoApproachMainDock = true;
		bool m_CayoPericoApproachNorthDock = false;
		bool m_CayoPericoApproachNorthDrop = false;
		bool m_CayoPericoApproachSouthDrop = false;
		bool m_CayoPericoApproachDrainage = true;
		bool m_CayoPericoMaxPayout = true;
		int m_CayoPericoCut = 100;
		int m_CayoPericoBagsizeMultiplier = 1;
	};

	inline std::unique_ptr<Features> g_Features;
}
