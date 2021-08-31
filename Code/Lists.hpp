#pragma once
#include "UI/UIManager.hpp"
#include "Features.hpp"

namespace Cheese::Lists
{
	inline const char* WeatherTypesFrontend[]
	{
		"Blizzard",
		"Clear",
		"Clearing",
		"Clouds",
		"Extra Sunny",
		"Foggy",
		"Halloween",
		"Neutral",
		"Overcast",
		"Rain",
		"Smog",
		"Snow",
		"Snowlight",
		"Thunder",
		"Christmas"
	};

	inline const char* WeatherTypesBackend[]
	{
		"BLIZZARD",
		"CLEAR",
		"CLEARING",
		"CLOUDS",
		"EXTRASUNNY",
		"FOGGY",
		"HALLOWEEN",
		"NEUTRAL",
		"OVERCAST",
		"RAIN",
		"SMOG",
		"SNOW",
		"SNOWLIGHT",
		"THUNDER",
		"XMAS"
	};

	inline std::size_t WeatherTypePosition = 1;

	inline UserInterface::Font FontTypes[]
	{
		UserInterface::Font::ChaletLondon,
	UserInterface::Font::HouseScript,
	UserInterface::Font::Monospace,
	UserInterface::Font::Wingdings,
	UserInterface::Font::ChaletComprimeCologne,
	UserInterface::Font::Pricedown
	};

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

	inline const char* DiamondCasinoApproachFrontend[]
	{
		"Silent & Sneaky",
		"The Big Con",
		"Aggressive"
	};
	inline Features::DiamondCasinoApproach DiamondCasinoApproachBackend[]
	{
		Features::DiamondCasinoApproach::Stealth,
		Features::DiamondCasinoApproach::BigCon,
		Features::DiamondCasinoApproach::Loud
	};
	inline std::size_t DiamondCasinoApproachPosition = 1;

	inline const char* DiamondCasinoMainTargetFrontend[]
	{
		"Cash",
		"Gold",
		"Art",
		"Diamonds"
	};
	inline Features::DiamondCasinoMainTarget DiamondCasinoMainTargetBackend[]
	{
		Features::DiamondCasinoMainTarget::Cash,
		Features::DiamondCasinoMainTarget::Gold,
		Features::DiamondCasinoMainTarget::Art,
		Features::DiamondCasinoMainTarget::Diamonds
	};
	inline std::size_t DiamondCasinoMainTargetPosition = 2;

	inline const char* DiamondCasinoKeycardFrontend[]
	{
		"None",
		"Level 1",
		"Level 2"
	};
	inline Features::DiamondCasinoKeycard DiamondCasinoKeycardBackend[]
	{
		Features::DiamondCasinoKeycard::None,
		Features::DiamondCasinoKeycard::Level1,
		Features::DiamondCasinoKeycard::Level2
	};
	inline std::size_t DiamondCasinoKeycardPosition = 2;

	inline const char* DiamondCasinoWeaponsmithFrontend[]
	{
		"None",
		"Karl Abolaji",
		"Gustavo Mota",
		"Charlie Reed",
		"Chester McCoy",
		"Patrick McReary"
	};
	inline Features::DiamondCasinoWeaponsmith DiamondCasinoWeaponsmithBackend[]
	{
		Features::DiamondCasinoWeaponsmith::None,
		Features::DiamondCasinoWeaponsmith::KarlAbolaji,
		Features::DiamondCasinoWeaponsmith::GustavoMota,
		Features::DiamondCasinoWeaponsmith::CharlieReed,
		Features::DiamondCasinoWeaponsmith::ChesterMcCoy,
		Features::DiamondCasinoWeaponsmith::PatrickMcReary
	};
	inline std::size_t DiamondCasinoWeaponsmithPosition = 1;

	inline const char* DiamondCasinoDriverFrontend[]
	{
		"None",
		"Karim Denz",
		"Taliana Martinez",
		"Eddie Toh",
		"Zach Nelson",
		"Chester McCoy"
	};
	inline Features::DiamondCasinoDriver DiamondCasinoDriverBackend[]
	{
		Features::DiamondCasinoDriver::None,
		Features::DiamondCasinoDriver::KarimDenz,
		Features::DiamondCasinoDriver::TalianaMartinez,
		Features::DiamondCasinoDriver::EddieToh,
		Features::DiamondCasinoDriver::ZachNelson,
		Features::DiamondCasinoDriver::ChesterMcCoy
	};
	inline std::size_t DiamondCasinoDriverPosition = 1;

	inline const char* DiamondCasinoHackerFrontend[]
	{
		"None",
		"Rickie Lukens",
		"Christian Feltz",
		"Yohan Blair",
		"Avi Schwartzman",
		"Paige Harris"
	};
	inline Features::DiamondCasinoHacker DiamondCasinoHackerBackend[]
	{
		Features::DiamondCasinoHacker::None,
		Features::DiamondCasinoHacker::RickieLukens,
		Features::DiamondCasinoHacker::ChristianFeltz,
		Features::DiamondCasinoHacker::YohanBlair,
		Features::DiamondCasinoHacker::AviSchwartzman,
		Features::DiamondCasinoHacker::PaigeHarris
	};
	inline std::size_t DiamondCasinoHackerPosition = 5;

	inline const char* DiamondCasinoVehicleType4Frontend[]
	{
		"Type 1",
		"Type 2",
		"Type 3",
		"Type 4",
	};
	inline Features::DiamondCasinoVehicleType4 DiamondCasinoVehicleType4Backend[]
	{
		Features::DiamondCasinoVehicleType4::Type1,
		Features::DiamondCasinoVehicleType4::Type2,
		Features::DiamondCasinoVehicleType4::Type3,
		Features::DiamondCasinoVehicleType4::Type4
	};
	inline std::size_t DiamondCasinoVehicleType4Position = 0;

	inline const char* DiamondCasinoVehicleType5Frontend[]
	{
		"Type 1",
		"Type 2",
		"Type 3",
		"Type 4",
		"Type 5"
	};
	inline Features::DiamondCasinoVehicleType5 DiamondCasinoVehicleType5Backend[]
	{
		Features::DiamondCasinoVehicleType5::Type1,
		Features::DiamondCasinoVehicleType5::Type2,
		Features::DiamondCasinoVehicleType5::Type3,
		Features::DiamondCasinoVehicleType5::Type4,
		Features::DiamondCasinoVehicleType5::Type5
	};
	inline std::size_t DiamondCasinoVehicleType5Position = 0;

	inline const char* DiamondCasinoWeaponFrontend[]
	{
		"First",
		"Second"
	};
	inline Features::DiamondCasinoWeapon DiamondCasinoWeaponBackend[]
	{
		Features::DiamondCasinoWeapon::First,
		Features::DiamondCasinoWeapon::Second
	};
	inline std::size_t DiamondCasinoWeaponPosition = 0;
}
