#pragma once

namespace Cheese::Offsets
{
	// CNetworkPlayerMgr
	inline unsigned int pCNetPlayerInfo = 0xA0;
	inline unsigned int pCNetPed = 0x1E8;
	inline unsigned int oNumPlayers = 0x180;
	inline unsigned int oRid = 0x090;

	// Landing Page Offsets for AutoConnect function / story mode.
	inline unsigned int oStartupFlow = 0x2B0;
	inline unsigned int oGTAOnline = 0xF0;

	// CPedFactory (WorldPTR)
	inline unsigned int pCPed = 0x8;

	// CPed Offsets
	inline unsigned int oEntityType = 0x2B; // int 156:Player 152:Other
	inline unsigned int pCNavigation = 0x30;
	inline unsigned int oVisualX = 0x90;
	inline unsigned int oVisualY = 0x94;
	inline unsigned int oVisualZ = 0x98; // float, vector3
	inline unsigned int oGod = 0x189;	 // int8 0:false 1:true
	inline unsigned int oHostility = 0x18C;
	inline unsigned int oHealth = 0x280; // float
	inline unsigned int oHealthMax = 0x2A0;
	inline unsigned int pAttackers = 0x2A8;
	inline unsigned int pCVehicle = 0xD30;
	inline unsigned int oRagdoll = 0x10B8; // int 32:false 1/0:true
	inline unsigned int pCPlayerInfo = 0x10C8;
	inline unsigned int pCPedWeaponManager = 0x10D8;
	inline unsigned int oSeatbelt = 0x140C;	 // byte 55:false 56:true
	inline unsigned int oInVehicle = 0x1477; // int 16:false 0:true
	inline unsigned int pedArmor = 0x14E0;	 // not working what

	// CNavigation Offsets
	inline unsigned int oHeading = 0x20; // float
	inline unsigned int oHeading2 = 0x24;
	inline unsigned int oRotation = 0x30;
	inline unsigned int oRotation2 = 0x34;
	inline unsigned int oRotation3 = 0x38; // float, vector3
	inline unsigned int oPositionX = 0x50;
	inline unsigned int oPositionY = 0x54;
	inline unsigned int oPositionZ = 0x58;

	// CPlayerInfo Offsets
	inline unsigned int oName = 0xA4;		// string[20]
	inline unsigned int oSwimSpeed = 0x170; // float
	inline unsigned int oFrameFlags = 0x219;
	inline unsigned int oWalkSpeed = 0x18C;
	inline unsigned int oWanted = 0x888;   // int8
	inline unsigned int oRunSpeed = 0xCF0; // float
	inline unsigned int oStamina = 0xCF4;
	inline unsigned int oStaminaRegen = 0xCF8;

	// CPedWeaponManager Offsets
	inline unsigned int pCWeaponInfo = 0x20;
	inline unsigned int oImpactType = 0x20;		 // int 3:bullet 5:explosion
	inline unsigned int oImpactExplosion = 0x24; // int32
	inline unsigned int oImpactType2 = 0x54;	 // int
	inline unsigned int pCAmmoInfo = 0x60;
	inline unsigned int pCVehicleWeapon = 0x70;
	inline unsigned int oSpread = 0x7C; // float
	inline unsigned int oDamage = 0xB0;
	inline unsigned int oForce = 0xD8;
	inline unsigned int oForcePed = 0xDC;
	inline unsigned int oForceVehicle = 0xE0;
	inline unsigned int oForceFlying = 0xE4;
	inline unsigned int oPenetration = 0x110;
	inline unsigned int oMuzzleVelocity = 0x11C;
	inline unsigned int oBulletBatch = 0x124;
	inline unsigned int oReloadVehicleMult = 0x130;
	inline unsigned int oReloadMult = 0x134;
	inline unsigned int oShotTime = 0x13C;
	inline unsigned int oLockRange = 0x288;
	inline unsigned int oRange = 0x28C;
	inline unsigned int pCAmmoWrap = 0x8;
	inline unsigned int oMaxAmmo = 0x28;
	inline unsigned int pCAmmo = 0x0;
	inline unsigned int oCurrentAmmo = 0x18;

	// CVehicle Offsets
	inline unsigned int pCModelInfo = 0x20;
	inline unsigned int oVInvisibility = 0x2C; // int
	inline unsigned int pCVehicleDrawHandler = 0x48;
	inline unsigned int oVPositionX = 0x90;
	inline unsigned int oVPositionY = 0x94;
	inline unsigned int oVPositionZ = 0x98; // float, vector3
	inline unsigned int oVState = 0xD8;		// int 0:Player 1:NPC 2:Unused 3:Destroyed
	inline unsigned int oVBurnt = 0x18A;	// int 64:off 72:on
	inline unsigned int oVHealth = 0x280;	// float
	inline unsigned int oVHealthMax = 0x2A0;
	inline unsigned int oVBoostSpeed = 0x120;
	inline unsigned int oVBoost = 0x320;
	inline unsigned int oVBoostRecharge = 0x324;
	inline unsigned int oVHealth2 = 0x840;
	inline unsigned int oVHealth3 = 0x844;		// used
	inline unsigned int oVEngineHealth = 0x908; // used
	inline unsigned int pCHandlingData = 0x938;
	inline unsigned int oVDirt = 0x9F8;			   // float
	inline unsigned int oBulletproofTires = 0x943; //int
	inline unsigned int oLightMult = 0xA14;		   // float
	inline unsigned int oVGravity = 0xC5C;		   // float
	inline unsigned int oCurPassenger = 0xC62;
	inline unsigned int oMk2Missiles = 0x12A4; // int
	inline unsigned int oAircraftBomb = 0x12B4;
	inline unsigned int oCountermeasures = 0x12B8;

	// CHandlingData Offsets
	inline unsigned int oMass = 0xC;	  // float
	inline unsigned int oBouyancy = 0x40; // float
	inline unsigned int oAcceleration = 0x4C;
	inline unsigned int oDriveInertia = 0x54;
	inline unsigned int oInitialDriveForce = 0x60;
	inline unsigned int oBrakeForce = 0x6C;
	inline unsigned int oHandbrakeForce = 0x7C;
	inline unsigned int oTractionCurveMax = 0x88;
	inline unsigned int oTractionCurveMin = 0x90;
	inline unsigned int oCollisionMult = 0xF0;
	inline unsigned int oWeaponMult = 0xF4;
	inline unsigned int oDeformationMult = 0xF8;
	inline unsigned int oEngineMult = 0xFC;
	inline unsigned int oThrust = 0x338;

	// CVehicleDrawHandler Offsets
	inline unsigned int pCVehicleVisual = 0x20;
	inline unsigned int oNeonR = 0x3A2; // int
	inline unsigned int oNeonG = 0x3A1;
	inline unsigned int oNeonB = 0x3A0;
	inline unsigned int oNeonLeft = 0x402;
	inline unsigned int oNeonRight = 0x403;
	inline unsigned int oNeonFront = 0x404;
	inline unsigned int oNeonBack = 0x405;
	inline unsigned int oEMS = 0x3D6;
	inline unsigned int oBrakes = 0x3D7;
	inline unsigned int oTransmission = 0x3D8;
	inline unsigned int oHorn = 0x3D9;
	inline unsigned int oSuspension = 0x3DA;
	inline unsigned int oArmor = 0x3DB;
	inline unsigned int oTurbo = 0x3DD;
	inline unsigned int oXenonLight = 0x3E1;
	inline unsigned int oSmokeR = 0x3FC;
	inline unsigned int oSmokeG = 0x3FD;
	inline unsigned int oSmokeB = 0x3FE;
	inline unsigned int oWindows = 0x3FF;
	inline unsigned int oColorLight = 0x406;

	// CVehicleVisual
	inline unsigned int oPrimaryR = 0xA6; // int
	inline unsigned int oPrimaryG = 0xA5;
	inline unsigned int oPrimaryB = 0xA4;
	inline unsigned int oSecondaryR = 0xAA;
	inline unsigned int oSecondaryG = 0xA9;
	inline unsigned int oSecondaryB = 0xA8;
	inline unsigned int oLicensePlate = 0x130; // dword / byte array [8]

	// CModelInfo
	inline unsigned int oModelHash = 0x18; // int
	inline unsigned int oCamDist = 0x38;   // float
	inline unsigned int oVName = 0x298;	   // string [10]
	inline unsigned int oVMaker = 0x2A4;   // string [10]
	inline unsigned int oVExtras = 0x58B;  // byte
	inline unsigned int oVParachute = 0x58C;

	// CReplayInterface Offsets and more below
	inline unsigned int pCPedInterface = 0x18;
	inline unsigned int pVehList = 0x180;
	inline unsigned int oVehNum = 0x190;
	inline unsigned int pPedList = 0x100;
	inline unsigned int oPedNum = 0x110;

	// CPickupData/CReplayInterface Offsets from DMKiller
	inline unsigned int pBST = 0x160;
	inline unsigned int pFixVeh = 0x228;
	inline unsigned int pPickupList = 0x100;
	inline unsigned int oPickupNum = 0x110;
	inline unsigned int pDroppedPickupData = 0x490;
	inline unsigned int pCPickupInterface = 0x20;
}
