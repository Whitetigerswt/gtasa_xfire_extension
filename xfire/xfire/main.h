static void WINAPI Load();
void SetStringFromCommandLine(char *szCmdLine, char *szString);
void LoadConfig();

#include "log.h"



char wNamesShortened[][32] = {
	{"Fist"}, // 0
	{"Brass Knuckles"}, // 1
	{"Golf Club"}, // 2
	{"Night Stick"}, // 3
	{"Knife"}, // 4
	{"Bat"}, // 5
	{"Shovel"}, // 6
	{"Pool Cue"}, // 7
	{"Katana"}, // 8
	{"Chainsaw"}, // 9
	{"Purple Dildo"}, // 10
	{"Dildo"}, // 11
	{"Vibrator"}, // 12
	{"Silver Vibrator"}, // 13
	{"Flowers"}, // 14
	{"Cane"}, // 15
	{"Grenade"}, // 16
	{"Teargas"}, // 17
	{"Molotov"}, // 18
	{" "}, // 19
	{" "}, // 20
	{" "}, // 21
	{"Colt 45"}, // 22
	{"Silenced"}, // 23
	{"Deagle"}, // 24
	{"Shotgun"}, // 25
	{"Sawnoff-Shotgun"}, // 26
	{"Combat Shotgun"}, // 27
	{"Uzi"}, // 28
	{"MP5"}, // 29
	{"AK47"}, // 30
	{"M4"}, // 31
	{"Tec9"}, // 32
	{"Rifle"}, // 33
	{"Sniper"}, // 34
	{"RPG"}, // 35
	{"Heat-Seeking RPG"}, // 36
	{"Flame"}, // 37
	{"Minigun"}, // 38
	{"Satchel"}, // 39
	{"Detonator"}, // 40
	{"Spray Can"}, // 41
	{"Fire Extinguisher"}, // 42
	{"Camera"}, // 43
	{"Night Vision"}, // 44
	{"Thermal Goggles"}, // 45
	{"Parachute"}, // 46
	{"Fake Pistol"} // 47
};