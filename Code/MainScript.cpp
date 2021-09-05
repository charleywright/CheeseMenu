#include <windows.h>
#include <shellapi.h>
#include "MainScript.hpp"
#include "ScriptCallback.hpp"
#include "Lists.hpp"
#include "Natives.hpp"
#include "Timer.hpp"
#include "CustomText.hpp"
#include "Features.hpp"
#include "UI/UIManager.hpp"
#include "UI/BoolOption.hpp"
#include "UI/ChooseOption.hpp"
#include "UI/NumberOption.hpp"
#include "UI/RegularOption.hpp"
#include "UI/SubOption.hpp"
#include "UI/RegularSubmenu.hpp"
#include "UI/PlayerSubmenu.hpp"

#include "Game.hpp"
#include "Offsets.hpp"

namespace Cheese
{
	enum Submenu : std::uint32_t
	{
		SubmenuHome,
		SubmenuPlayer,
		SubmenuWorld,
		SubmenuHeists,
		SubmenuHeistsCayoPerico,
		SubmenuHeistsCayoPericoVehicle,
		SubmenuHeistsCayoPericoSupportTeam,
		SubmenuHeistsCayoPericoApproach,
		SubmenuHeistsCasino,
		SubmenuHeistsCasinoAccessPoints,
		SubmenuHeistsCasinoPOI,
		SubmenuHeistsDoomsday,
		SubmenuHeistsDoomsdayActOne,
		SubmenuHeistsDoomsdayActTwo,
		SubmenuHeistsDoomsdayActThree,
		SubmenuSession,
		SubmenuSettings,
		SubmenuSettingsHeader,
		SubmenuSettingsScrollbar,
		SubmenuSettingsSeperator,
		SubmenuSettingsHeaderStaticBackground,
		SubmenuSettingsHeaderGradientBackground,
		SubmenuSettingsHeaderAnimatedBackground,
		SubmenuSettingsHeaderText,
		SubmenuSettingsSubmenuBar,
		SubmenuSettingsOption,
		SubmenuSettingsFooter,
		SubmenuSettingsDescription,
		SubmenuSettingsInput,
		SubmenuSettingsLanguage,
		SubmenuSelectedPlayer,
		SubmenuPlayerList
	};

	bool MainScript::IsInitialized()
	{
		return m_Initialized;
	}

	ScriptType MainScript::GetType()
	{
		return ScriptType::Game;
	}

	void MainScript::Initialize()
	{
		m_Initialized = true;
		using namespace UserInterface;

		g_UiManager->AddSubmenu<RegularSubmenu>("Home", SubmenuHome, [](RegularSubmenu *sub)
												{
													sub->AddOption<SubOption>("Player", nullptr, SubmenuPlayer);
													// sub->AddOption<SubOption>("Players", nullptr, SubmenuPlayerList);
													sub->AddOption<SubOption>("World", nullptr, SubmenuWorld);
													sub->AddOption<SubOption>("Heists", nullptr, SubmenuHeists);
													sub->AddOption<SubOption>("Session", nullptr, SubmenuSession);
													sub->AddOption<SubOption>("Settings", nullptr, SubmenuSettings);
													sub->AddOption<RegularOption>(std::move(RegularOption("Server Invite", nullptr, []
																										  { ShellExecuteA(0, 0, "https://discord.gg/J8486xStu6", 0, 0, SW_SHOW); })
																								.SetRightText("discord.gg/J8486xStu6")));
													sub->AddOption<RegularOption>(std::move(RegularOption("Game Version").SetRightText(g_GameVariables->m_GameBuild)));
													sub->AddOption<RegularOption>("Unload", nullptr, []
																				  { g_Running = false; });
												});

		g_UiManager->AddSubmenu<RegularSubmenu>("Player", SubmenuPlayer, [](RegularSubmenu *sub)
												{
													sub->AddOption<RegularOption>("Toggle instant BST", nullptr, []
																				  { *ScriptGlobal(2441237).Add(4013).As<int *>() = 5; });
													sub->AddOption<RegularOption>("Off radar", nullptr, []
																				  { g_Features->OffRadar(); });
													sub->AddOption<RegularOption>("Ghost organization", "If not in CEO will default to Off Radar", []
																				  { g_Features->GhostOrg(); });
													sub->AddOption<BoolOption<bool>>("Fix Vehicle", nullptr, &g_Features->m_FixVehicle, BoolDisplay::OnOff);
													sub->AddOption<NumberOption<int>>("Wanted Level", nullptr, &g_Features->m_WantedLevel, 0, 5, 1, 3, true, "", "", []
																					  { *(int *)DereferenceMultiLevel(g_GameVariables->m_WorldPtr, {Offsets::pCPed, Offsets::pCPlayerInfo, Offsets::oWanted}) = g_Features->m_WantedLevel; });
													sub->AddOption<BoolOption<bool>>("Freeze Wanted Level", nullptr, &g_Features->m_FreezeWanted, BoolDisplay::OnOff);
													sub->AddOption<NumberOption<int>>("RP Correction Rank", nullptr, &g_Features->m_RPCorrectionLevel, 1, 8000, 1);
													sub->AddOption<RegularOption>("Set Rank", nullptr, []
																				  { g_Features->RPCorrection(); });
													sub->AddOption<RegularOption>("Max Stats", nullptr, []
																				  { g_Features->MaxStats(); });
													sub->AddOption<RegularOption>("Max Snacks", nullptr, []
																				  { g_Features->MaxSnacks(); });
													sub->AddOption<RegularOption>("Max Armor", nullptr, []
																				  { g_Features->MaxArmour(); });
													sub->AddOption<BoolOption<bool>>("Godmode", nullptr, &g_Features->m_Godmode, BoolDisplay::OnOff);
													sub->AddOption<BoolOption<bool>>("Anti AFK Kick", nullptr, &g_Features->m_AntiAFKKick, BoolDisplay::OnOff, false, []
																					 { g_Features->m_AntiAFKKick ? g_Features->EnableAntiAfkKick() : g_Features->DisableAntiAfkKick(); });
												});

		g_UiManager->AddSubmenu<RegularSubmenu>("World", SubmenuWorld, [](RegularSubmenu *sub)
												{
													sub->AddOption<ChooseOption<const char *, std::size_t>>("Weather", nullptr, &Lists::WeatherTypesFrontend, &Lists::WeatherTypePosition, false, []
																											{ MISC::SET_WEATHER_TYPE_NOW_PERSIST(Lists::WeatherTypesBackend[Lists::WeatherTypePosition]); });
													sub->AddOption<BoolOption<bool>>("Freeze Weather", nullptr, &g_Features->m_FreezeWeather, BoolDisplay::OnOff);
													sub->AddOption<NumberOption<int>>("Hours", nullptr, &g_Features->m_hours, 0, 23);
													sub->AddOption<NumberOption<int>>("Hours", nullptr, &g_Features->m_minutes, 0, 59);
													sub->AddOption<NumberOption<int>>("Hours", nullptr, &g_Features->m_seconds, 0, 59);
													sub->AddOption<RegularOption>("Set Time", nullptr, []
																				  { NETWORK::NETWORK_OVERRIDE_CLOCK_TIME(g_Features->m_hours, g_Features->m_minutes, g_Features->m_seconds); });
													sub->AddOption<BoolOption<bool>>("Freeze Time", nullptr, &g_Features->m_FreezeTime, BoolDisplay::OnOff);
													sub->AddOption<RegularOption>("Toggle Snow", nullptr, []
																				  {
																					  int *snow = ScriptGlobal(262145).Add(4724).As<int *>();
																					  *snow == 1 ? *snow = 0 : *snow = 1;
																				  });
												});

		g_UiManager->AddSubmenu<RegularSubmenu>("Heists", SubmenuHeists, [](RegularSubmenu *sub)
												{
													sub->AddOption<SubOption>("Cayo Perico", nullptr, SubmenuHeistsCayoPerico);
													sub->AddOption<SubOption>("Diamond Casino", nullptr, SubmenuHeistsCasino);
													sub->AddOption<SubOption>("Doomsday Scenario", nullptr, SubmenuHeistsDoomsday);
												});

		g_UiManager->AddSubmenu<RegularSubmenu>("Cayo Perico", SubmenuHeistsCayoPerico, [](RegularSubmenu *sub)
												{
													sub->AddOption<ChooseOption<const char *, std::size_t>>("Difficulty", nullptr, &Lists::CayoPericoDifficultyFrontend, &Lists::CayoPericoDifficultyPosition, true, []
																											{ g_Features->m_CayoPericoDifficulty = Lists::CayoPericoDifficultyBackend[Lists::CayoPericoDifficultyPosition]; });
													sub->AddOption<SubOption>("Approach Vehicle", nullptr, SubmenuHeistsCayoPericoVehicle);
													sub->AddOption<BoolOption<bool>>("Demolition Charges", nullptr, &g_Features->m_CayoPericoDemolitionCharges, BoolDisplay::YesNo);
													sub->AddOption<BoolOption<bool>>("Cutting Torch", nullptr, &g_Features->m_CayoPericoCuttingTorch, BoolDisplay::YesNo);
													sub->AddOption<BoolOption<bool>>("Plasma Cutter / Safe Code", nullptr, &g_Features->m_CayoPericoPrimaryTool, BoolDisplay::YesNo);
													sub->AddOption<BoolOption<bool>>("Fingerprint Cloner", nullptr, &g_Features->m_CayoPericoFingerprint, BoolDisplay::YesNo);
													sub->AddOption<BoolOption<bool>>("Disrupt Weapons", nullptr, &g_Features->m_CayoPericoDisruptWeapons, BoolDisplay::YesNo);
													sub->AddOption<BoolOption<bool>>("Disrupt Armour", nullptr, &g_Features->m_CayoPericoDisruptArmour, BoolDisplay::YesNo);
													sub->AddOption<BoolOption<bool>>("Disrupt Air Support", nullptr, &g_Features->m_CayoPericoDisruptAirSupport, BoolDisplay::YesNo);
													sub->AddOption<BoolOption<bool>>("Unlock All POI", "Unlock all Points of Interest", &g_Features->m_CayoPericoUnlockAllPOI, BoolDisplay::YesNo);
													sub->AddOption<ChooseOption<const char *, std::size_t>>("Main Target", nullptr, &Lists::CayoPericoMainTargetFrontend, &Lists::CayoPericoMainTargetPosition, true, []
																											{ g_Features->m_CayoPericoMainTarget = Lists::CayoPericoMainTargetBackend[Lists::CayoPericoMainTargetPosition]; });
													sub->AddOption<ChooseOption<const char *, std::size_t>>("Weapon Loadout", nullptr, &Lists::CayoPericoWeaponFrontend, &Lists::CayoPericoWeaponPosition, true, []
																											{ g_Features->m_CayoPericoWeapon = Lists::CayoPericoWeaponBackend[Lists::CayoPericoWeaponPosition]; });
													sub->AddOption<ChooseOption<const char *, std::size_t>>("Supply Truck", nullptr, &Lists::CayoPericoSupplyTruckFrontend, &Lists::CayoPericoSupplyTruckPosition, true, []
																											{ g_Features->m_CayoPericoSupplyTruck = Lists::CayoPericoSupplyTruckBackend[Lists::CayoPericoSupplyTruckPosition]; });
													sub->AddOption<ChooseOption<const char *, std::size_t>>("Entry Point", nullptr, &Lists::CayoPericoEntryFrontend, &Lists::CayoPericoEntryPosition, true, []
																											{ g_Features->m_CayoPericoEntry = Lists::CayoPericoEntryBackend[Lists::CayoPericoEntryPosition]; });
													sub->AddOption<SubOption>("Support Crew", nullptr, SubmenuHeistsCayoPericoSupportTeam);
													sub->AddOption<ChooseOption<const char *, std::size_t>>("Playthrough Status", nullptr, &Lists::CayoPericoPlaythroughStatusFrontend, &Lists::CayoPericoPlaythroughStatusPosition, true, []
																											{ g_Features->m_CayoPericoPlaythroughStatus = Lists::CayoPericoPlaythroughStatusBackend[Lists::CayoPericoPlaythroughStatusPosition]; });
													sub->AddOption<SubOption>("Infiltration & Escape Points", nullptr, SubmenuHeistsCayoPericoApproach);
													sub->AddOption<BoolOption<bool>>("Max Payout", "Don't get any secondary when using this", &g_Features->m_CayoPericoMaxPayout, BoolDisplay::OnOff);
													if (g_Features->m_CayoPericoMaxPayout)
													{
														sub->AddOption<NumberOption<int>>("Your Cut", nullptr, &g_Features->m_CayoPericoCut, 15, 100, 5, 3, true, "", "%");
														sub->AddOption<RegularOption>("Apply Max Payout", "Use this during the heist", []
																					  { g_Features->ApplyCayoPericoMaxPayout(); });
													}
													if (!g_Features->m_CayoPericoMaxPayout)
														sub->AddOption<NumberOption<int>>("Bag Size Multiplier", nullptr, &g_Features->m_CayoPericoBagsizeMultiplier, 1, 4, 1, 1, true, "", "x");
													sub->AddOption<RegularOption>("Apply Settings", nullptr, []
																				  { g_Features->ApplyCayoPerico(); });
												});

		g_UiManager->AddSubmenu<RegularSubmenu>("Approach Vehicle", SubmenuHeistsCayoPericoVehicle, [](RegularSubmenu *sub)
												{
													sub->AddOption<BoolOption<bool>>("Kosatka", nullptr, &g_Features->m_CayoPericoKosatka, BoolDisplay::YesNo);
													sub->AddOption<BoolOption<bool>>("Velum", nullptr, &g_Features->m_CayoPericoVelum, BoolDisplay::YesNo);
													sub->AddOption<BoolOption<bool>>("Stealth Annihilator", nullptr, &g_Features->m_CayoPericoAnnihilator, BoolDisplay::YesNo);
													sub->AddOption<BoolOption<bool>>("Patrol Boat", nullptr, &g_Features->m_CayoPericoPatrolBoat, BoolDisplay::YesNo);
													sub->AddOption<BoolOption<bool>>("Longfin", nullptr, &g_Features->m_CayoPericoLongfin, BoolDisplay::YesNo);
													sub->AddOption<BoolOption<bool>>("Alkonost & Stealth helicopter", nullptr, &g_Features->m_CayoPericoAlkonostAndStealthHeli, BoolDisplay::YesNo);
												});

		g_UiManager->AddSubmenu<RegularSubmenu>("Approach Vehicle", SubmenuHeistsCayoPericoSupportTeam, [](RegularSubmenu *sub)
												{
													sub->AddOption<BoolOption<bool>>("Airstrike", nullptr, &g_Features->m_CayoPericoSupportAirstrike, BoolDisplay::YesNo);
													sub->AddOption<BoolOption<bool>>("Supply Drop", nullptr, &g_Features->m_CayoPericoSupportSupplyDrop, BoolDisplay::YesNo);
													sub->AddOption<BoolOption<bool>>("Sniper", nullptr, &g_Features->m_CayoPericoSupportSniper, BoolDisplay::YesNo);
													sub->AddOption<BoolOption<bool>>("Helicopter Pickup", nullptr, &g_Features->m_CayoPericoSupportHeliPickup, BoolDisplay::YesNo);
													sub->AddOption<BoolOption<bool>>("Recon Drone", nullptr, &g_Features->m_CayoPericoSupportReconDrone, BoolDisplay::YesNo);
													sub->AddOption<BoolOption<bool>>("Weapon Stash", nullptr, &g_Features->m_CayoPericoSupportWeaponStash, BoolDisplay::YesNo);
												});

		g_UiManager->AddSubmenu<RegularSubmenu>("Infiltration & Escape Points", SubmenuHeistsCayoPericoApproach, [](RegularSubmenu *sub)
												{
													sub->AddOption<BoolOption<bool>>("Airstrip", "Infiltration & Escape", &g_Features->m_CayoPericoApproachAirstrip, BoolDisplay::YesNo);
													sub->AddOption<BoolOption<bool>>("Halo Jump", "Infiltration only", &g_Features->m_CayoPericoApproachHaloJump, BoolDisplay::YesNo);
													sub->AddOption<BoolOption<bool>>("West Beach", "Infiltration & Kosatka Escape", &g_Features->m_CayoPericoApproachWestBeach, BoolDisplay::YesNo);
													sub->AddOption<BoolOption<bool>>("Main Dock", "Infiltration & Escape", &g_Features->m_CayoPericoApproachMainDock, BoolDisplay::YesNo);
													sub->AddOption<BoolOption<bool>>("North Dock", "Infiltration & Escape", &g_Features->m_CayoPericoApproachNorthDock, BoolDisplay::YesNo);
													sub->AddOption<BoolOption<bool>>("North Drop Zone", "Infiltration only", &g_Features->m_CayoPericoApproachNorthDrop, BoolDisplay::YesNo);
													sub->AddOption<BoolOption<bool>>("South Drop Zone", "Infiltration only", &g_Features->m_CayoPericoApproachSouthDrop, BoolDisplay::YesNo);
													sub->AddOption<BoolOption<bool>>("Drainage Tunnel", "Infiltration only", &g_Features->m_CayoPericoApproachDrainage, BoolDisplay::YesNo);
												});

		g_UiManager->AddSubmenu<RegularSubmenu>("Diamond Casino Heist", SubmenuHeistsCasino, [](RegularSubmenu *sub)
												{
													sub->AddOption<SubOption>("Access Points", nullptr, SubmenuHeistsCasinoAccessPoints);
													sub->AddOption<SubOption>("Points of Interest", nullptr, SubmenuHeistsCasinoPOI);
													sub->AddOption<ChooseOption<const char *, std::size_t>>("Approach", nullptr, &Lists::DiamondCasinoApproachFrontend, &Lists::DiamondCasinoApproachPosition, true, []
																											{ g_Features->m_DiamondCasinoApproach = Lists::DiamondCasinoApproachBackend[Lists::DiamondCasinoApproachPosition]; });
													sub->AddOption<ChooseOption<const char *, std::size_t>>("Main Target", nullptr, &Lists::DiamondCasinoMainTargetFrontend, &Lists::DiamondCasinoMainTargetPosition, true, []
																											{ g_Features->m_DiamondCasinoMainTarget = Lists::DiamondCasinoMainTargetBackend[Lists::DiamondCasinoMainTargetPosition]; });
													sub->AddOption<BoolOption<bool>>("Duggan Shipments", nullptr, &g_Features->m_DiamondCasinoDisrupt, BoolDisplay::YesNo);
													sub->AddOption<ChooseOption<const char *, std::size_t>>("Keycards", nullptr, &Lists::DiamondCasinoKeycardFrontend, &Lists::DiamondCasinoKeycardPosition, true, []
																											{ g_Features->m_DiamondCasinoKeycard = Lists::DiamondCasinoKeycardBackend[Lists::DiamondCasinoKeycardPosition]; });
													sub->AddOption<ChooseOption<const char *, std::size_t>>("Weaponsmith", nullptr, &Lists::DiamondCasinoWeaponsmithFrontend, &Lists::DiamondCasinoWeaponsmithPosition, true, []
																											{ g_Features->m_DiamondCasinoWeaponSmith = Lists::DiamondCasinoWeaponsmithBackend[Lists::DiamondCasinoWeaponsmithPosition]; });
													sub->AddOption<ChooseOption<const char *, std::size_t>>("Weapons", nullptr, &Lists::DiamondCasinoWeaponFrontend, &Lists::CayoPericoWeaponPosition, true, []
																											{ g_Features->m_DiamondCasinoWeapon = Lists::DiamondCasinoWeaponBackend[Lists::CayoPericoWeaponPosition]; });
													sub->AddOption<ChooseOption<const char *, std::size_t>>("Driver", nullptr, &Lists::DiamondCasinoDriverFrontend, &Lists::DiamondCasinoDriverPosition, true, []
																											{ g_Features->m_DiamondCasinoDriver = Lists::DiamondCasinoDriverBackend[Lists::DiamondCasinoDriverPosition]; });
													if (g_Features->m_DiamondCasinoDriver == Features::DiamondCasinoDriver::KarimDenz || g_Features->m_DiamondCasinoDriver == Features::DiamondCasinoDriver::TalianaMartinez || g_Features->m_DiamondCasinoDriver == Features::DiamondCasinoDriver::EddieToh)
													{
														sub->AddOption<ChooseOption<const char *, std::size_t>>("Vehicle", nullptr, &Lists::DiamondCasinoVehicleType5Frontend, &Lists::DiamondCasinoVehicleType5Position, true, []
																												{ g_Features->m_DiamondCasinoVehicleType5 = Lists::DiamondCasinoVehicleType5Backend[Lists::DiamondCasinoVehicleType5Position]; });
													}
													else
													{
														sub->AddOption<ChooseOption<const char *, std::size_t>>("Vehicle", nullptr, &Lists::DiamondCasinoVehicleType4Frontend, &Lists::DiamondCasinoVehicleType4Position, true, []
																												{ g_Features->m_DiamondCasinoVehicleType4 = Lists::DiamondCasinoVehicleType4Backend[Lists::DiamondCasinoVehicleType4Position]; });
													}
													sub->AddOption<ChooseOption<const char *, std::size_t>>("Hacker", nullptr, &Lists::DiamondCasinoHackerFrontend, &Lists::DiamondCasinoHackerPosition, true, []
																											{ g_Features->m_DiamondCasinoHacker = Lists::DiamondCasinoHackerBackend[Lists::DiamondCasinoHackerPosition]; });
													sub->AddOption<RegularOption>("Apply Settings", nullptr, []
																				  { g_Features->ApplyDiamondCasino(); });
													;
												});

		g_UiManager->AddSubmenu<RegularSubmenu>("Casino Heist Access Points", SubmenuHeistsCasinoAccessPoints, [](RegularSubmenu *sub)
												{
													sub->AddOption<BoolOption<bool>>("Main Door", nullptr, &g_Features->m_DiamondCasinoAccessPointMainDoor, BoolDisplay::YesNo);
													sub->AddOption<BoolOption<bool>>("North Side Door", nullptr, &g_Features->m_DiamondCasinoAccessPointNorthSideDoor, BoolDisplay::YesNo);
													sub->AddOption<BoolOption<bool>>("East Side Door", nullptr, &g_Features->m_DiamondCasinoAccessPointEastSideDoor, BoolDisplay::YesNo);
													sub->AddOption<BoolOption<bool>>("Southwest Roof Terrace", nullptr, &g_Features->m_DiamondCasinoAccessPointSouthwestRoofTerrace, BoolDisplay::YesNo);
													sub->AddOption<BoolOption<bool>>("Southeast Roof Terrace", nullptr, &g_Features->m_DiamondCasinoAccessPointSoutheastRoofTerrace, BoolDisplay::YesNo);
													sub->AddOption<BoolOption<bool>>("East Roof Terrace", nullptr, &g_Features->m_DiamondCasinoAccessPointEastRoofTerrace, BoolDisplay::YesNo);
													sub->AddOption<BoolOption<bool>>("Roof", nullptr, &g_Features->m_DiamondCasinoAccessPointRoof, BoolDisplay::YesNo);
													sub->AddOption<BoolOption<bool>>("Roof Stairs", nullptr, &g_Features->m_DiamondCasinoAccessPointRoofStairs, BoolDisplay::YesNo);
													sub->AddOption<BoolOption<bool>>("Security Tunnel", nullptr, &g_Features->m_DiamondCasinoAccessPointSecurityTunnel, BoolDisplay::YesNo);
													sub->AddOption<BoolOption<bool>>("Sewer Tunnel", nullptr, &g_Features->m_DiamondCasinoAccessPointSewerTunnel, BoolDisplay::YesNo);
												});

		g_UiManager->AddSubmenu<RegularSubmenu>("Casino Heist Points of Interest", SubmenuHeistsCasinoPOI, [](RegularSubmenu *sub)
												{
													sub->AddOption<BoolOption<bool>>("Guard", nullptr, &g_Features->m_DiamondCasinoPOIGuard, BoolDisplay::YesNo);
													sub->AddOption<BoolOption<bool>>("Security Camera", nullptr, &g_Features->m_DiamondCasinoPOISecurityCamera, BoolDisplay::YesNo);
													sub->AddOption<BoolOption<bool>>("Keypad", nullptr, &g_Features->m_DiamondCasinoPOIKeypad, BoolDisplay::YesNo);
													sub->AddOption<BoolOption<bool>>("Valet", nullptr, &g_Features->m_DiamondCasinoPOIValet, BoolDisplay::YesNo);
													sub->AddOption<BoolOption<bool>>("Old Camera", nullptr, &g_Features->m_DiamondCasinoPOIOldCamera, BoolDisplay::YesNo);
													sub->AddOption<BoolOption<bool>>("Security Office", nullptr, &g_Features->m_DiamondCasinoPOISecurityOffice, BoolDisplay::YesNo);
													sub->AddOption<BoolOption<bool>>("Staff Lobby", nullptr, &g_Features->m_DiamondCasinoPOIStaffLobby, BoolDisplay::YesNo);
													sub->AddOption<BoolOption<bool>>("Staff Door", nullptr, &g_Features->m_DiamondCasinoPOIStaffDoor, BoolDisplay::YesNo);
													sub->AddOption<BoolOption<bool>>("Metal Detectors", nullptr, &g_Features->m_DiamondCasinoPOIMetalDetectors, BoolDisplay::YesNo);
													sub->AddOption<BoolOption<bool>>("Staff Elevator", nullptr, &g_Features->m_DiamondCasinoPOIStaffElevator, BoolDisplay::YesNo);
												});

		g_UiManager->AddSubmenu<RegularSubmenu>("The Doomsday Heist", SubmenuHeistsDoomsday, [](RegularSubmenu *sub)
												{
													sub->AddOption<SubOption>("Doomsday Scenario Act 1", "The Data Breaches", SubmenuHeistsDoomsdayActOne);
													sub->AddOption<SubOption>("Doomsday Scenario Act 2", "The Bogdan Problem", SubmenuHeistsDoomsdayActTwo);
													sub->AddOption<SubOption>("Doomsday Scenario Act 3", "The Doomsday Scenario", SubmenuHeistsDoomsdayActThree);
													sub->AddOption<RegularOption>("Hard Reset", "Remove ALL completion, will not be a replay", []
																				  { g_Features->DoomsdayHardReset(); });
													sub->AddOption<RegularOption>("Skip First Completion", nullptr, []
																				  { g_Features->DoomsdaySkipFirstCompletion(); });
												});

		g_UiManager->AddSubmenu<RegularSubmenu>("The Doomsday Heist Act 1", SubmenuHeistsDoomsdayActOne, [](RegularSubmenu *sub)
												{
													sub->AddOption<BoolOption<bool>>("Replay", nullptr, &g_Features->m_DoomsdayActOneReplay, BoolDisplay::YesNo);
													sub->AddOption<BoolOption<bool>>("Prep: Pramedic Equipment", nullptr, &g_Features->m_DoomsdayActOnePrepOne, BoolDisplay::YesNo);
													sub->AddOption<BoolOption<bool>>("Prep: Deluxos", nullptr, &g_Features->m_DoomsdayActOnePrepTwo, BoolDisplay::YesNo);
													sub->AddOption<BoolOption<bool>>("Prep: Akula", nullptr, &g_Features->m_DoomsdayActOnePrepThree, BoolDisplay::YesNo);
													sub->AddOption<BoolOption<bool>>("Setup: Dead Courier", nullptr, &g_Features->m_DoomsdayActOneSetupOne, BoolDisplay::YesNo);
													sub->AddOption<BoolOption<bool>>("Setup: Signal Intercepts", nullptr, &g_Features->m_DoomsdayActOneSetupTwo, BoolDisplay::YesNo);
													sub->AddOption<BoolOption<bool>>("Setup: Server Farm", nullptr, &g_Features->m_DoomsdayActOneSetupThree, BoolDisplay::YesNo);
													sub->AddOption<RegularOption>("Apply Settings", nullptr, []
																				  { g_Features->ApplyDoomsdayActOne(); });
												});

		g_UiManager->AddSubmenu<RegularSubmenu>("The Doomsday Heist Act 2", SubmenuHeistsDoomsdayActTwo, [](RegularSubmenu *sub)
												{
													sub->AddOption<BoolOption<bool>>("Replay", nullptr, &g_Features->m_DoomsdayActTwoReplay, BoolDisplay::YesNo);
													sub->AddOption<BoolOption<bool>>("Prep: Keycards", nullptr, &g_Features->m_DoomsdayActTwoPrepOne, BoolDisplay::YesNo);
													sub->AddOption<BoolOption<bool>>("Prep: ULP Intel", nullptr, &g_Features->m_DoomsdayActTwoPrepTwo, BoolDisplay::YesNo);
													sub->AddOption<BoolOption<bool>>("Prep: Riot Control Van", nullptr, &g_Features->m_DoomsdayActTwoPrepThree, BoolDisplay::YesNo);
													sub->AddOption<BoolOption<bool>>("Prep: Strombergs", nullptr, &g_Features->m_DoomsdayActTwoPrepFour, BoolDisplay::YesNo);
													sub->AddOption<BoolOption<bool>>("Prep: Torpedo ECU", nullptr, &g_Features->m_DoomsdayActTwoPrepFive, BoolDisplay::YesNo);
													sub->AddOption<BoolOption<bool>>("Setup: Avenger", nullptr, &g_Features->m_DoomsdayActTwoSetupOne, BoolDisplay::YesNo);
													sub->AddOption<BoolOption<bool>>("Setup: Rescue ULP", nullptr, &g_Features->m_DoomsdayActTwoSetupTwo, BoolDisplay::YesNo);
													sub->AddOption<BoolOption<bool>>("Setup: Salvage Hard Drives", nullptr, &g_Features->m_DoomsdayActTwoSetupThree, BoolDisplay::YesNo);
													sub->AddOption<BoolOption<bool>>("Setup: Submarine Recon", nullptr, &g_Features->m_DoomsdayActTwoSetupFour, BoolDisplay::YesNo);
													sub->AddOption<RegularOption>("Apply Settings", nullptr, []
																				  { g_Features->ApplyDoomsdayActTwo(); });
												});

		g_UiManager->AddSubmenu<RegularSubmenu>("The Doomsday Heist Act 3", SubmenuHeistsDoomsdayActThree, [](RegularSubmenu *sub)
												{
													sub->AddOption<BoolOption<bool>>("Replay", nullptr, &g_Features->m_DoomsdayActThreeReplay, BoolDisplay::YesNo);
													sub->AddOption<BoolOption<bool>>("Prep: Marked Cash", nullptr, &g_Features->m_DoomsdayActThreePrepOne, BoolDisplay::YesNo);
													sub->AddOption<BoolOption<bool>>("Prep: Recon", nullptr, &g_Features->m_DoomsdayActThreePrepTwo, BoolDisplay::YesNo);
													sub->AddOption<BoolOption<bool>>("Prep: Chernobog", nullptr, &g_Features->m_DoomsdayActThreePrepThree, BoolDisplay::YesNo);
													sub->AddOption<BoolOption<bool>>("Prep: Flight Path", nullptr, &g_Features->m_DoomsdayActThreePrepFour, BoolDisplay::YesNo);
													sub->AddOption<BoolOption<bool>>("Prep: Test Site Intel", nullptr, &g_Features->m_DoomsdayActThreePrepFive, BoolDisplay::YesNo);
													sub->AddOption<BoolOption<bool>>("Prep: Onboard Computer", nullptr, &g_Features->m_DoomsdayActThreePrepSix, BoolDisplay::YesNo);
													sub->AddOption<BoolOption<bool>>("Setup: Rescue Agent 14", nullptr, &g_Features->m_DoomsdayActThreeSetupOne, BoolDisplay::YesNo);
													sub->AddOption<BoolOption<bool>>("Setup: Escort ULP", nullptr, &g_Features->m_DoomsdayActThreeSetupTwo, BoolDisplay::YesNo);
													sub->AddOption<BoolOption<bool>>("Setup: Barrage", nullptr, &g_Features->m_DoomsdayActThreeSetupThree, BoolDisplay::YesNo);
													sub->AddOption<BoolOption<bool>>("Setup: Khanjali", nullptr, &g_Features->m_DoomsdayActThreeSetupFour, BoolDisplay::YesNo);
													sub->AddOption<BoolOption<bool>>("Setup: Air Defenses", nullptr, &g_Features->m_DoomsdayActThreeSetupFive, BoolDisplay::YesNo);
													sub->AddOption<RegularOption>("Apply Settings", nullptr, []
																				  { g_Features->ApplyDoomsdayActThree(); });
												});

		g_UiManager->AddSubmenu<RegularSubmenu>("Session", SubmenuSession, [](RegularSubmenu *sub)
												{
													sub->AddOption<RegularOption>("Join Public Session", nullptr, []
																				  { g_Features->EnterSession(0); });
													sub->AddOption<RegularOption>("New Public Session", nullptr, []
																				  { g_Features->EnterSession(1); });
													sub->AddOption<RegularOption>("Closed Crew Session", nullptr, []
																				  { g_Features->EnterSession(2); });
													sub->AddOption<RegularOption>("Crew Session", nullptr, []
																				  { g_Features->EnterSession(3); });
													sub->AddOption<RegularOption>("Closed Friend Session", nullptr, []
																				  { g_Features->EnterSession(6); });
													sub->AddOption<RegularOption>("Find Friend Session", nullptr, []
																				  { g_Features->EnterSession(9); });
													sub->AddOption<RegularOption>("Solo Session", nullptr, []
																				  { g_Features->EnterSession(10); });
													sub->AddOption<RegularOption>("Invite Only Session", nullptr, []
																				  { g_Features->EnterSession(11); });
													sub->AddOption<RegularOption>("Join Crew Session", nullptr, []
																				  { g_Features->EnterSession(12); });
													sub->AddOption<RegularOption>("Leave GTA Online", nullptr, []
																				  { g_Features->LeaveGTAOnline(); });
												});

		g_UiManager->AddSubmenu<RegularSubmenu>("Settings", SubmenuSettings, [](RegularSubmenu *sub)
												{
													sub->AddOption<SubOption>("Header", nullptr, SubmenuSettingsHeader);
													sub->AddOption<SubOption>("Scrollbar", nullptr, SubmenuSettingsScrollbar);
													sub->AddOption<SubOption>("Seperator", nullptr, SubmenuSettingsSeperator);
													sub->AddOption<SubOption>("Infobar", nullptr, SubmenuSettingsSubmenuBar);
													sub->AddOption<SubOption>("Options", nullptr, SubmenuSettingsOption);
													sub->AddOption<SubOption>("Footer", nullptr, SubmenuSettingsFooter);
													sub->AddOption<SubOption>("Description", nullptr, SubmenuSettingsDescription);
													sub->AddOption<SubOption>("Input", nullptr, SubmenuSettingsInput);
													sub->AddOption<SubOption>("Language", nullptr, SubmenuSettingsLanguage);
													sub->AddOption<NumberOption<float>>("X Position", nullptr, &g_Config->m_PosX, 0.f, 0.79f, 0.01f, 2);
													sub->AddOption<NumberOption<float>>("Y Position", nullptr, &g_Config->m_PosY, 0.f, 0.51f, 0.01f, 2);
													sub->AddOption<NumberOption<float>>("Width", nullptr, &g_Config->m_Width, 0.01f, 1.f, 0.01f, 2);
													sub->AddOption<NumberOption<size_t>>("Options Per Page", nullptr, &g_Config->m_OptionsPerPage, 1, static_cast<size_t>(20));
													sub->AddOption<BoolOption<bool>>("Sounds", nullptr, &g_Config->m_Sounds, BoolDisplay::OnOff);
													sub->AddOption<NumberOption<size_t>>("Feature Tick Size", "How many ticks to wait between feature ticks", &g_Config->m_FeatureTickSize, 1, 50);
													sub->AddOption<BoolOption<bool>>("Log Window", nullptr, &g_Config->m_LogWindow, BoolDisplay::OnOff);
													sub->AddOption<BoolOption<bool>>("Lock Cursor", nullptr, &g_Config->m_LockMouse, BoolDisplay::OnOff);
												});

		g_UiManager->AddSubmenu<RegularSubmenu>("Seperator", SubmenuSettingsSeperator, [](RegularSubmenu *sub)
												{
													sub->AddOption<BoolOption<bool>>("Enabled", nullptr, &g_Config->m_SeperatorEnabled, BoolDisplay::OnOff);
													sub->AddOption<NumberOption<float>>("Height", nullptr, &g_Config->m_SeperatorHeight, 0.001f, 0.01f, 0.001f, 3);
													sub->AddOption<NumberOption<std::uint8_t>>("Left R", nullptr, &g_Config->m_SeperatorColorLeft.r, '\0', static_cast<std::uint8_t>(255));
													sub->AddOption<NumberOption<std::uint8_t>>("Left G", nullptr, &g_Config->m_SeperatorColorLeft.g, '\0', static_cast<std::uint8_t>(255));
													sub->AddOption<NumberOption<std::uint8_t>>("Left B", nullptr, &g_Config->m_SeperatorColorLeft.b, '\0', static_cast<std::uint8_t>(255));
													sub->AddOption<NumberOption<std::uint8_t>>("Left A", nullptr, &g_Config->m_SeperatorColorLeft.a, '\0', static_cast<std::uint8_t>(255));
													sub->AddOption<NumberOption<std::uint8_t>>("Middle R", nullptr, &g_Config->m_SeperatorColorMiddle.r, '\0', static_cast<std::uint8_t>(255));
													sub->AddOption<NumberOption<std::uint8_t>>("Middle G", nullptr, &g_Config->m_SeperatorColorMiddle.g, '\0', static_cast<std::uint8_t>(255));
													sub->AddOption<NumberOption<std::uint8_t>>("Middle B", nullptr, &g_Config->m_SeperatorColorMiddle.b, '\0', static_cast<std::uint8_t>(255));
													sub->AddOption<NumberOption<std::uint8_t>>("Middle A", nullptr, &g_Config->m_SeperatorColorMiddle.a, '\0', static_cast<std::uint8_t>(255));
													sub->AddOption<NumberOption<std::uint8_t>>("Right R", nullptr, &g_Config->m_SeperatorColorRight.r, '\0', static_cast<std::uint8_t>(255));
													sub->AddOption<NumberOption<std::uint8_t>>("Right G", nullptr, &g_Config->m_SeperatorColorRight.g, '\0', static_cast<std::uint8_t>(255));
													sub->AddOption<NumberOption<std::uint8_t>>("Right B", nullptr, &g_Config->m_SeperatorColorRight.b, '\0', static_cast<std::uint8_t>(255));
													sub->AddOption<NumberOption<std::uint8_t>>("Right A", nullptr, &g_Config->m_SeperatorColorRight.a, '\0', static_cast<std::uint8_t>(255));
												});

		g_UiManager->AddSubmenu<RegularSubmenu>("Infobar", SubmenuSettingsSubmenuBar, [](RegularSubmenu *sub)
												{
													sub->AddOption<NumberOption<float>>("Height", nullptr, &g_Config->m_SubmenuBarHeight, 0.01f, 0.1f, 0.001f, 3);
													sub->AddOption<NumberOption<float>>("Text Size", nullptr, &g_Config->m_SubmenuBarTextSize, 0.01f, 1.f, 0.01f, 2);
													sub->AddOption<NumberOption<std::uint8_t>>("Background R", nullptr, &g_Config->m_SubmenuBarBackgroundColor.r, '\0', static_cast<std::uint8_t>(255));
													sub->AddOption<NumberOption<std::uint8_t>>("Background G", nullptr, &g_Config->m_SubmenuBarBackgroundColor.g, '\0', static_cast<std::uint8_t>(255));
													sub->AddOption<NumberOption<std::uint8_t>>("Background B", nullptr, &g_Config->m_SubmenuBarBackgroundColor.b, '\0', static_cast<std::uint8_t>(255));
													sub->AddOption<NumberOption<std::uint8_t>>("Background A", nullptr, &g_Config->m_SubmenuBarBackgroundColor.a, '\0', static_cast<std::uint8_t>(255));
													sub->AddOption<NumberOption<std::uint8_t>>("Text R", nullptr, &g_Config->m_SubmenuBarTextColor.r, '\0', static_cast<std::uint8_t>(255));
													sub->AddOption<NumberOption<std::uint8_t>>("Text G", nullptr, &g_Config->m_SubmenuBarTextColor.g, '\0', static_cast<std::uint8_t>(255));
													sub->AddOption<NumberOption<std::uint8_t>>("Text B", nullptr, &g_Config->m_SubmenuBarTextColor.b, '\0', static_cast<std::uint8_t>(255));
													sub->AddOption<NumberOption<std::uint8_t>>("Text A", nullptr, &g_Config->m_SubmenuBarTextColor.a, '\0', static_cast<std::uint8_t>(255));
												});

		g_UiManager->AddSubmenu<RegularSubmenu>("Options", SubmenuSettingsOption, [](RegularSubmenu *sub)
												{
													sub->AddOption<NumberOption<float>>("Height", nullptr, &g_Config->m_OptionHeight, 0.01f, 0.1f, 0.001f, 3);
													sub->AddOption<NumberOption<float>>("Text Size", nullptr, &g_Config->m_OptionTextSize, 0.01f, 1.f, 0.01f, 2);

													sub->AddOption<NumberOption<std::uint8_t>>("Selected Background R", nullptr, &g_Config->m_OptionSelectedBackgroundColor.r, '\0', static_cast<std::uint8_t>(255));
													sub->AddOption<NumberOption<std::uint8_t>>("Selected Background G", nullptr, &g_Config->m_OptionSelectedBackgroundColor.g, '\0', static_cast<std::uint8_t>(255));
													sub->AddOption<NumberOption<std::uint8_t>>("Selected Background B", nullptr, &g_Config->m_OptionSelectedBackgroundColor.b, '\0', static_cast<std::uint8_t>(255));
													sub->AddOption<NumberOption<std::uint8_t>>("Selected Background A", nullptr, &g_Config->m_OptionSelectedBackgroundColor.a, '\0', static_cast<std::uint8_t>(255));
													sub->AddOption<NumberOption<std::uint8_t>>("Unselected Background R", nullptr, &g_Config->m_OptionUnselectedBackgroundColor.r, '\0', static_cast<std::uint8_t>(255));
													sub->AddOption<NumberOption<std::uint8_t>>("Unselected Background G", nullptr, &g_Config->m_OptionUnselectedBackgroundColor.g, '\0', static_cast<std::uint8_t>(255));
													sub->AddOption<NumberOption<std::uint8_t>>("Unselected Background B", nullptr, &g_Config->m_OptionUnselectedBackgroundColor.b, '\0', static_cast<std::uint8_t>(255));
													sub->AddOption<NumberOption<std::uint8_t>>("Unselected Background A", nullptr, &g_Config->m_OptionUnselectedBackgroundColor.a, '\0', static_cast<std::uint8_t>(255));

													sub->AddOption<NumberOption<std::uint8_t>>("Selected Text R", nullptr, &g_Config->m_OptionSelectedTextColor.r, '\0', static_cast<std::uint8_t>(255));
													sub->AddOption<NumberOption<std::uint8_t>>("Selected Text G", nullptr, &g_Config->m_OptionSelectedTextColor.g, '\0', static_cast<std::uint8_t>(255));
													sub->AddOption<NumberOption<std::uint8_t>>("Selected Text B", nullptr, &g_Config->m_OptionSelectedTextColor.b, '\0', static_cast<std::uint8_t>(255));
													sub->AddOption<NumberOption<std::uint8_t>>("Selected Text A", nullptr, &g_Config->m_OptionSelectedTextColor.a, '\0', static_cast<std::uint8_t>(255));
													sub->AddOption<NumberOption<std::uint8_t>>("Unselected Text R", nullptr, &g_Config->m_OptionUnselectedTextColor.r, '\0', static_cast<std::uint8_t>(255));
													sub->AddOption<NumberOption<std::uint8_t>>("Unselected Text G", nullptr, &g_Config->m_OptionUnselectedTextColor.g, '\0', static_cast<std::uint8_t>(255));
													sub->AddOption<NumberOption<std::uint8_t>>("Unselected Text B", nullptr, &g_Config->m_OptionUnselectedTextColor.b, '\0', static_cast<std::uint8_t>(255));
													sub->AddOption<NumberOption<std::uint8_t>>("Unselected Text A", nullptr, &g_Config->m_OptionUnselectedTextColor.a, '\0', static_cast<std::uint8_t>(255));
												});

		g_UiManager->AddSubmenu<RegularSubmenu>("Footer", SubmenuSettingsFooter, [](RegularSubmenu *sub)
												{
													sub->AddOption<NumberOption<float>>("Height", nullptr, &g_Config->m_FooterHeight, 0.01f, 0.1f, 0.001f, 3);
													sub->AddOption<NumberOption<float>>("Sprite Size", nullptr, &g_Config->m_FooterSpriteSize, 0.01f, 1.f, 0.001f, 3);

													sub->AddOption<NumberOption<std::uint8_t>>("Background R", nullptr, &g_Config->m_FooterBackgroundColor.r, '\0', static_cast<std::uint8_t>(255));
													sub->AddOption<NumberOption<std::uint8_t>>("Background G", nullptr, &g_Config->m_FooterBackgroundColor.g, '\0', static_cast<std::uint8_t>(255));
													sub->AddOption<NumberOption<std::uint8_t>>("Background B", nullptr, &g_Config->m_FooterBackgroundColor.b, '\0', static_cast<std::uint8_t>(255));
													sub->AddOption<NumberOption<std::uint8_t>>("Background A", nullptr, &g_Config->m_FooterBackgroundColor.a, '\0', static_cast<std::uint8_t>(255));
													sub->AddOption<NumberOption<std::uint8_t>>("Sprite R", nullptr, &g_Config->m_FooterSpriteColor.r, '\0', static_cast<std::uint8_t>(255));
													sub->AddOption<NumberOption<std::uint8_t>>("Sprite G", nullptr, &g_Config->m_FooterSpriteColor.g, '\0', static_cast<std::uint8_t>(255));
													sub->AddOption<NumberOption<std::uint8_t>>("Sprite B", nullptr, &g_Config->m_FooterSpriteColor.b, '\0', static_cast<std::uint8_t>(255));
													sub->AddOption<NumberOption<std::uint8_t>>("Sprite A", nullptr, &g_Config->m_FooterSpriteColor.a, '\0', static_cast<std::uint8_t>(255));
												});

		g_UiManager->AddSubmenu<RegularSubmenu>("Scrollbar", SubmenuSettingsScrollbar, [](RegularSubmenu *sub)
												{
													sub->AddOption<NumberOption<float>>("Width", nullptr, &g_Config->m_ScrollBarWidth, 0.001f, 0.1f, 0.001f, 3);
													sub->AddOption<NumberOption<float>>("Offset", nullptr, &g_Config->m_ScrollBarOffset, 0.001f, 0.1f, 0.001f, 3);
													sub->AddOption<NumberOption<float>>("Sprite Size", nullptr, &g_Config->m_ScrollBarSpriteSize, 0.01f, 0.1f, 0.001f, 3);
													sub->AddOption<NumberOption<std::uint8_t>>("Background R", nullptr, &g_Config->m_ScrollBarBackgroundColor.r, '\0', static_cast<std::uint8_t>(255));
													sub->AddOption<NumberOption<std::uint8_t>>("Background G", nullptr, &g_Config->m_ScrollBarBackgroundColor.g, '\0', static_cast<std::uint8_t>(255));
													sub->AddOption<NumberOption<std::uint8_t>>("Background B", nullptr, &g_Config->m_ScrollBarBackgroundColor.b, '\0', static_cast<std::uint8_t>(255));
													sub->AddOption<NumberOption<std::uint8_t>>("Background A", nullptr, &g_Config->m_ScrollBarBackgroundColor.a, '\0', static_cast<std::uint8_t>(255));
													sub->AddOption<NumberOption<std::uint8_t>>("Foreground R", nullptr, &g_Config->m_ScrollBarForegroundColor.r, '\0', static_cast<std::uint8_t>(255));
													sub->AddOption<NumberOption<std::uint8_t>>("Foreground G", nullptr, &g_Config->m_ScrollBarForegroundColor.g, '\0', static_cast<std::uint8_t>(255));
													sub->AddOption<NumberOption<std::uint8_t>>("Foreground B", nullptr, &g_Config->m_ScrollBarForegroundColor.b, '\0', static_cast<std::uint8_t>(255));
													sub->AddOption<NumberOption<std::uint8_t>>("Foreground A", nullptr, &g_Config->m_ScrollBarForegroundColor.a, '\0', static_cast<std::uint8_t>(255));
													sub->AddOption<NumberOption<std::uint8_t>>("End Background R", nullptr, &g_Config->m_ScrollBarEndColor.r, '\0', static_cast<std::uint8_t>(255));
													sub->AddOption<NumberOption<std::uint8_t>>("End Background G", nullptr, &g_Config->m_ScrollBarEndColor.g, '\0', static_cast<std::uint8_t>(255));
													sub->AddOption<NumberOption<std::uint8_t>>("End Background B", nullptr, &g_Config->m_ScrollBarEndColor.b, '\0', static_cast<std::uint8_t>(255));
													sub->AddOption<NumberOption<std::uint8_t>>("End Background A", nullptr, &g_Config->m_ScrollBarEndColor.a, '\0', static_cast<std::uint8_t>(255));
												});

		g_UiManager->AddSubmenu<RegularSubmenu>("Header", SubmenuSettingsHeader, [](RegularSubmenu *sub)
												{
													sub->AddOption<ChooseOption<const char *, std::size_t>>("Type", nullptr, &Lists::HeaderTypesFrontend, &Lists::HeaderTypesPosition, true, []
																											{ g_Config->m_HeaderType = Lists::HeaderTypesBackend[Lists::HeaderTypesPosition]; });

													switch (g_Config->m_HeaderType)
													{
													case HeaderType::Static:
														sub->AddOption<SubOption>("Background", nullptr, SubmenuSettingsHeaderStaticBackground);
														break;
													case HeaderType::Gradient:
														sub->AddOption<SubOption>("Gradient", nullptr, SubmenuSettingsHeaderGradientBackground);
														break;
													case HeaderType::Animated:
														sub->AddOption<SubOption>("Animated", nullptr, SubmenuSettingsHeaderAnimatedBackground);
														break;
													}

													sub->AddOption<SubOption>("Text", nullptr, SubmenuSettingsHeaderText);
													sub->AddOption<NumberOption<float>>("Height", nullptr, &g_Config->m_HeaderHeight, 0.01f, 0.2f, 0.001f, 3);
												});

		g_UiManager->AddSubmenu<RegularSubmenu>("Header Background", SubmenuSettingsHeaderStaticBackground, [](RegularSubmenu *sub)
												{
													sub->AddOption<NumberOption<std::uint8_t>>("R", nullptr, &g_Config->m_HeaderBackgroundColor.r, '\0', static_cast<std::uint8_t>(255));
													sub->AddOption<NumberOption<std::uint8_t>>("G", nullptr, &g_Config->m_HeaderBackgroundColor.g, '\0', static_cast<std::uint8_t>(255));
													sub->AddOption<NumberOption<std::uint8_t>>("B", nullptr, &g_Config->m_HeaderBackgroundColor.b, '\0', static_cast<std::uint8_t>(255));
													sub->AddOption<NumberOption<std::uint8_t>>("A", nullptr, &g_Config->m_HeaderBackgroundColor.a, '\0', static_cast<std::uint8_t>(255));
												});

		g_UiManager->AddSubmenu<RegularSubmenu>("Header Gradient", SubmenuSettingsHeaderGradientBackground, [](RegularSubmenu *sub)
												{
													sub->AddOption<BoolOption<bool>>("Transparent", nullptr, &g_Config->m_HeaderGradientTransparent, BoolDisplay::YesNo);
													sub->AddOption<BoolOption<bool>>("Flip", nullptr, &g_Config->m_HeaderGradientFlip, BoolDisplay::YesNo);

													sub->AddOption<NumberOption<std::uint8_t>>("R1", nullptr, &g_Config->m_HeaderGradientColorLeft.r, '\0', static_cast<std::uint8_t>(255));
													sub->AddOption<NumberOption<std::uint8_t>>("G1", nullptr, &g_Config->m_HeaderGradientColorLeft.g, '\0', static_cast<std::uint8_t>(255));
													sub->AddOption<NumberOption<std::uint8_t>>("B1", nullptr, &g_Config->m_HeaderGradientColorLeft.b, '\0', static_cast<std::uint8_t>(255));
													sub->AddOption<NumberOption<std::uint8_t>>("A1", nullptr, &g_Config->m_HeaderGradientColorLeft.a, '\0', static_cast<std::uint8_t>(255));
													sub->AddOption<NumberOption<std::uint8_t>>("R2", nullptr, &g_Config->m_HeaderGradientColorRight.r, '\0', static_cast<std::uint8_t>(255));
													sub->AddOption<NumberOption<std::uint8_t>>("G2", nullptr, &g_Config->m_HeaderGradientColorRight.g, '\0', static_cast<std::uint8_t>(255));
													sub->AddOption<NumberOption<std::uint8_t>>("B2", nullptr, &g_Config->m_HeaderGradientColorRight.b, '\0', static_cast<std::uint8_t>(255));
													sub->AddOption<NumberOption<std::uint8_t>>("A2", nullptr, &g_Config->m_HeaderGradientColorRight.a, '\0', static_cast<std::uint8_t>(255));
												});

		g_UiManager->AddSubmenu<RegularSubmenu>("Header Animated", SubmenuSettingsHeaderAnimatedBackground, [](RegularSubmenu *sub)
												{
													sub->AddOption<NumberOption<int>>("Frame Delay", "The delay between each frame in ms", &g_Config->m_AnimatedHeaderTimerDelay, '\0', INT_MAX);
													sub->AddOption<NumberOption<int>>("Frame Count", "How many frames to render (inclusive)", &g_Config->m_AnimatedHeaderFrameCount, '\0', INT_MAX);
												});

		g_UiManager->AddSubmenu<RegularSubmenu>("Header Text", SubmenuSettingsHeaderText, [](RegularSubmenu *sub)
												{
													sub->AddOption<BoolOption<bool>>("Enable", nullptr, &g_Config->m_HeaderText, BoolDisplay::OnOff);
													sub->AddOption<NumberOption<float>>("Size", nullptr, &g_Config->m_HeaderTextSize, 0.1f, 2.f, 0.01f, 2);
													sub->AddOption<NumberOption<std::uint8_t>>("R", nullptr, &g_Config->m_HeaderTextColor.r, '\0', static_cast<std::uint8_t>(255));
													sub->AddOption<NumberOption<std::uint8_t>>("G", nullptr, &g_Config->m_HeaderTextColor.g, '\0', static_cast<std::uint8_t>(255));
													sub->AddOption<NumberOption<std::uint8_t>>("B", nullptr, &g_Config->m_HeaderTextColor.b, '\0', static_cast<std::uint8_t>(255));
													sub->AddOption<NumberOption<std::uint8_t>>("A", nullptr, &g_Config->m_HeaderTextColor.a, '\0', static_cast<std::uint8_t>(255));
												});

		g_UiManager->AddSubmenu<RegularSubmenu>("Description", SubmenuSettingsDescription, [](RegularSubmenu *sub)
												{
													sub->AddOption<NumberOption<float>>("Padding", "Padding before the description rect.", &g_Config->m_DescriptionHeightPadding, 0.01f, 1.f, 0.001f, 3);
													sub->AddOption<NumberOption<float>>("Height", "Size of the description rect.", &g_Config->m_DescriptionHeight, 0.01f, 1.f, 0.001f, 3);
													sub->AddOption<NumberOption<float>>("Text Size", "Size of the description text.", &g_Config->m_DescriptionTextSize, 0.1f, 2.f, 0.01f, 2);
												});

		g_UiManager->AddSubmenu<RegularSubmenu>("Input", SubmenuSettingsInput, [](RegularSubmenu *sub)
												{
													sub->AddOption<NumberOption<std::int32_t>>("Open Delay", nullptr, &g_Config->m_OpenDelay, 10, 1000, 10, 0);
													sub->AddOption<NumberOption<std::int32_t>>("Back Delay", nullptr, &g_Config->m_BackDelay, 10, 1000, 10, 0);
													sub->AddOption<NumberOption<std::int32_t>>("Enter Delay", nullptr, &g_Config->m_EnterDelay, 10, 1000, 10, 0);
													sub->AddOption<NumberOption<std::int32_t>>("Vertical Delay", nullptr, &g_Config->m_VerticalDelay, 10, 1000, 10, 0);
													sub->AddOption<NumberOption<std::int32_t>>("Horizontal Delay", nullptr, &g_Config->m_HorizontalDelay, 10, 1000, 10, 0);
												});

		g_UiManager->AddSubmenu<RegularSubmenu>("Players", SubmenuPlayerList, [](RegularSubmenu *sub)
												{
													for (std::uint32_t i = 0; i < 32; ++i)
													{
														if (auto ped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i))
														{
															sub->AddOption<SubOption>(PLAYER::GET_PLAYER_NAME(i), nullptr, SubmenuSelectedPlayer, [=]
																					  { g_SelectedPlayer = i; });
														}
													}
												});

		g_UiManager->AddSubmenu<PlayerSubmenu>(&g_SelectedPlayer, SubmenuSelectedPlayer, [](PlayerSubmenu *sub)
											   {
												   sub->AddOption<RegularOption>("Get player ID", nullptr, []
																				 {
																					 Player p = PLAYER::PLAYER_ID();
																					 g_Logger->Info(std::to_string(p).c_str());
																					 p = PLAYER::PLAYER_PED_ID();
																					 g_Logger->Info(std::to_string(p).c_str());
																				 });
											   });
	}

	void MainScript::Destroy()
	{
		g_UiManager.reset();
	}

	void MainScript::Tick()
	{
		g_UiManager->OnTick();
	}
}
