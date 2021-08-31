#pragma once
#include "Script.hpp"
#include <memory>

namespace Cheese
{
	class Features
	{
	public:
		void DisplayNotification(const char *text);

		const uint32_t Stat(std::string stat, int c_index);

		bool m_FreezeWeather = false;
		int m_hours = 12;
		int m_minutes = 30;
		int m_seconds = 0;
		bool m_FreezeTime = false;

		bool m_FixVehicle = true;
		void FixVehicle();

		void EnterSession(int type);
		void LeaveGTAOnline();
		void MaxStats();
		void MaxSnacks();
		void MaxArmour();
		void RPCorrection();
		int m_RPCorrectionLevel = 135;
		void OffRadar();
		void GhostOrg();

		bool m_AntiAFKKick = false;
		void EnableAntiAfkKick();
		void DisableAntiAfkKick();

		// Doomsday
		void DoomsdayPrerequisite();
		void SkipAct1();
		void SkipAct2();
		void SkipAct3();

		// Cayo Perico Heist
		void ApplyCayoPerico();
		void ApplyCayoPericoMaxPayout();

		enum class CayoPericoDifficulty : int
		{
			Normal = 126823,
			Hard = 131055
		};

		enum class CayoPericoMainTarget : int
		{
			Tequila = 0,
			RubyNecklace = 1,
			BearerBonds = 2,
			PinkDiamond = 3,
			MadrazoFiles = 4,
			SapphirePanther = 5
		};

		enum class CayoPericoWeapon : int
		{
			None = 0,
			Aggressor = 1,
			Conspirator = 2,
			Crackshot = 3,
			Soboteur = 4,
			Marksman = 5
		};

		enum class CayoPericoSupplyTruck : int
		{
			Airport = 1,
			NorthDock = 2,
			MainDockEast = 3,
			MainDockWest = 4,
			InsideCompound = 5
		};

		enum class CayoPericoEntry : int
		{
			MainGate = 1,
			NorthWall = 2,
			NorthGate = 4,
			SouthWall = 8,
			SouthGate = 16,
			DrainageTunnel = 32
		};

		enum class CayoPericoPlaythroughStatus : int
		{
			First = 0,
			Second = 1,
			SkipCutscene = 40000
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

		// Diamond Casino
		void ApplyDiamondCasino();

		enum class DiamondCasinoApproach : int
		{
			Stealth = 1,
			BigCon = 2,
			Loud = 3
		};

		enum class DiamondCasinoMainTarget : int
		{
			Cash = 0,
			Gold = 1,
			Art = 2,
			Diamonds = 3
		};

		enum class DiamondCasinoKeycard : int
		{
			None = 0,
			Level1 = 1,
			Level2 = 2
		};

		enum class DiamondCasinoWeaponsmith : int
		{
			None = 0,
			KarlAbolaji = 1,
			GustavoMota = 2,
			CharlieReed = 3,
			ChesterMcCoy = 4,
			PatrickMcReary = 5
		};

		enum class DiamondCasinoDriver : int
		{
			None = 0,
			KarimDenz = 1,
			TalianaMartinez = 2,
			EddieToh = 3,
			ZachNelson = 4,
			ChesterMcCoy = 5
		};

		enum class DiamondCasinoHacker : int
		{
			None = 0,
			RickieLukens = 1,
			ChristianFeltz = 2,
			YohanBlair = 3,
			AviSchwartzman = 4,
			PaigeHarris = 5
		};

		enum class DiamondCasinoVehicleType4 : int
		{
			Type1 = 0,
			Type2 = 1,
			Type3 = 2,
			Type4 = 3
		};

		enum class DiamondCasinoVehicleType5 : int
		{
			Type1 = 0,
			Type2 = 1,
			Type3 = 2,
			Type4 = 3,
			Type5 = 4
		};

		enum class DiamondCasinoWeapon : int
		{
			First = 0,
			Second = 2
		};

		bool m_DiamondCasinoAccessPointMainDoor = true;
		bool m_DiamondCasinoAccessPointNorthSideDoor = true;
		bool m_DiamondCasinoAccessPointEastSideDoor = true;
		bool m_DiamondCasinoAccessPointSouthwestRoofTerrace = true;
		bool m_DiamondCasinoAccessPointSoutheastRoofTerrace = true;
		bool m_DiamondCasinoAccessPointEastRoofTerrace = true;
		bool m_DiamondCasinoAccessPoint_wag1memeing_com_ = true;
		bool m_DiamondCasinoAccessPointRoof = true;
		bool m_DiamondCasinoAccessPointRoofStairs = true;
		bool m_DiamondCasinoAccessPointSecurityTunnel = true;
		bool m_DiamondCasinoAccessPointSewerTunnel = true;

		bool m_DiamondCasinoPOIGuard = true;
		bool m_DiamondCasinoPOISecurityCamera = true;
		bool m_DiamondCasinoPOIKeypad = true;
		bool m_DiamondCasinoPOIValet = true;
		bool m_DiamondCasinoPOIOldCamera = true;
		bool m_DiamondCasinoPOISecurityOffice = true;
		bool m_DiamondCasinoPOIStaffLobby = true;
		bool m_DiamondCasinoPOIStaffDoor = true;
		bool m_DiamondCasinoPOIMetalDetectors = true;
		bool m_DiamondCasinoPOIStaffElevator = true;

		DiamondCasinoApproach m_DiamondCasinoApproach = DiamondCasinoApproach::BigCon;
		DiamondCasinoMainTarget m_DiamondCasinoMainTarget = DiamondCasinoMainTarget::Art;
		bool m_DiamondCasinoDisrupt = true;
		DiamondCasinoKeycard m_DiamondCasinoKeycard = DiamondCasinoKeycard::Level2;
		DiamondCasinoWeaponsmith m_DiamondCasinoWeaponSmith = DiamondCasinoWeaponsmith::KarlAbolaji;
		DiamondCasinoDriver m_DiamondCasinoDriver = DiamondCasinoDriver::KarimDenz;
		DiamondCasinoHacker m_DiamondCasinoHacker = DiamondCasinoHacker::PaigeHarris;
		DiamondCasinoVehicleType4 m_DiamondCasinoVehicleType4 = DiamondCasinoVehicleType4::Type1;
		DiamondCasinoVehicleType5 m_DiamondCasinoVehicleType5 = DiamondCasinoVehicleType5::Type1;
		DiamondCasinoWeapon m_DiamondCasinoWeapon = DiamondCasinoWeapon::First;
	};

	inline std::unique_ptr<Features> g_Features;
}
