#pragma once
#include "UI/UIManager.hpp"
#include "Features.hpp"

namespace Big::Lists
{
	inline const char* HeaderTypesFrontend[]
	{
		"Static",
		"Gradient",
		"Image",
		"Animated"
	};
	inline UserInterface::HeaderType HeaderTypesBackend[]
	{
		UserInterface::HeaderType::Static,
		UserInterface::HeaderType::Gradient,
		UserInterface::HeaderType::Image,
		UserInterface::HeaderType::Animated
	};
	inline std::size_t HeaderTypesPosition = 2;

	inline const char* CayoPericoDifficultyFrontend[]
	{
		"Normal",
		"Hard"
	};
	inline Features::CayoPericoDifficulty CayoPericoDifficultyBackend[]
	{
		Features::CayoPericoDifficulty::Normal,
		Features::CayoPericoDifficulty::Hard
	};
	inline std::size_t CayoPericoDifficultyPosition = 0;

	inline const char* CayoPericoMainTargetFrontend[]
	{
		"Tequila",
		"Ruby Necklace",
		"Bearer Bonds",
		"Pink Diamond",
		"Madrazo Files",
		"Sapphire Panther"
	};
	inline Features::CayoPericoMainTarget CayoPericoMainTargetBackend[]{
		Features::CayoPericoMainTarget::Tequila,
		Features::CayoPericoMainTarget::RubyNecklace,
		Features::CayoPericoMainTarget::BearerBonds,
		Features::CayoPericoMainTarget::PinkDiamond,
		Features::CayoPericoMainTarget::MadrazoFiles,
		Features::CayoPericoMainTarget::SapphirePanther
	};
	inline std::size_t CayoPericoMainTargetPosition = 5;

	inline const char* CayoPericoWeaponFrontend[]
	{
			"None",
			"Aggressor",
			"Conspirator",
			"Crackshot",
			"Soboteur",
			"Marksman"
	};
	inline Features::CayoPericoWeapon CayoPericoWeaponBackend[]
	{
		Features::CayoPericoWeapon::None,
		Features::CayoPericoWeapon::Aggressor,
		Features::CayoPericoWeapon::Conspirator,
		Features::CayoPericoWeapon::Crackshot,
		Features::CayoPericoWeapon::Soboteur,
		Features::CayoPericoWeapon::Marksman
	};
	inline std::size_t CayoPericoWeaponPosition = 1;

	inline const char* CayoPericoSupplyTruckFrontend[]
	{
		"Airport",
		"North Dock",
		"Main Dock East",
		"Main Dock West",
		"Inside Compound"
	};
	inline Features::CayoPericoSupplyTruck CayoPericoSupplyTruckBackend[]
	{
		Features::CayoPericoSupplyTruck::Airport,
		Features::CayoPericoSupplyTruck::NorthDock,
		Features::CayoPericoSupplyTruck::MainDockEast,
		Features::CayoPericoSupplyTruck::MainDockWest,
		Features::CayoPericoSupplyTruck::InsideCompound
	};
	inline std::size_t CayoPericoSupplyTruckPosition = 4;

	inline const char* CayoPericoEntryFrontend[]
	{
		"Main Gate",
		"North Wall",
		"North Gate",
		"South Wall",
		"South Gate",
		"Drainage Tunnel"
	};
	inline Features::CayoPericoEntry CayoPericoEntryBackend[]
	{
		Features::CayoPericoEntry::MainGate,
		Features::CayoPericoEntry::NorthWall,
		Features::CayoPericoEntry::NorthGate,
		Features::CayoPericoEntry::SouthWall,
		Features::CayoPericoEntry::SouthGate,
		Features::CayoPericoEntry::DrainageTunnel
	};
	inline std::size_t CayoPericoEntryPosition = 5;

	inline const char* CayoPericoPlaythroughStatusFrontend[]
	{
		"First",
		"Second",
		"Skip Cutscenes"
	};
	inline Features::CayoPericoPlaythroughStatus CayoPericoPlaythroughStatusBackend[]
	{
		Features::CayoPericoPlaythroughStatus::First,
		Features::CayoPericoPlaythroughStatus::Second,
		Features::CayoPericoPlaythroughStatus::SkipCutscene
	};
	inline std::size_t CayoPericoPlaythroughStatusPosition = 2;
}
