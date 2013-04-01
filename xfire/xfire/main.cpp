#define _CRT_SECURE_NO_WARNINGS

#include <tchar.h>
#include <windows.h>
#include <iostream>
#include <fstream>
#include <string>

#include "cfg.h"
#include "main.h"
#include "xfire.h"

CFG *cfg = new CFG;

// disable any key/value we want to hide from a cfg file
// fix free() crashes
// real server IP, ingame name, skin ID, car ID if in car, packetloss, position, 0xBAA420 - wanted level


BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		if ( CreateThread( 0, 0, (LPTHREAD_START_ROUTINE)Load, NULL, 0, 0) == NULL ) {
			ExitProcess(GetLastError());
			return FALSE; 
		}
		return TRUE;
	}
	return TRUE;
}

static void WINAPI Load() {
	const char *key[14],*value[14];

	for(int i=0; i < sizeof(value); ++i) {
		value[i] = new char[30];
	}
	Sleep(1000);
	LoadConfig();
	

	while(true) {
		if(XfireIsLoaded()) {
			
			int player = *(int*)0xB6F5F0;
			

			if(player != 0) { // game not loaded yet

				int idx = 0;
		
				// KEYS/VALUES //
				if(cfg->health) {
					key[idx] = "Health";
					float f = *(float*)(player+0x540);
					if(f > 999) f = 999.0;

					//value[idx] = new char[10];
					sprintf((char*)value[idx], "%d", (int)f);

					idx++;
				}

				if(cfg->armour) {
					key[idx] = "Armour";
					float f = *(float*)(player+0x548);
					if(f > 999) f = 999.0;

					//value[idx] = new char[10];
					sprintf((char*)value[idx], "%d", (int)f);

					idx++;
				}

				if(cfg->state) {
					key[idx] = "State";
					BYTE b = *(BYTE*)(player+0x46C);
					//value[idx] = new char[30];
					if(b == 0) {
						sprintf((char*)value[idx], "In Air/water");
					} else if(b == 1) {
						sprintf((char*)value[idx], "In car");
					} else if(b == 2) {
						sprintf((char*)value[idx], "Entering an interior");
					} else if(b == 3) {
						sprintf((char*)value[idx], "On foot");
					} else if(b == 8) {
						sprintf((char*)value[idx], "Spectating");
					} else {
						sprintf((char*)value[idx], "%d", b);
					} 

					idx++;
				}

				if(cfg->weather) {

					key[idx] = "Weather";
					int i = *(int*)0xC81320;

					//value[idx] = new char[10];
					sprintf((char*)value[idx], "%d", i);

					idx++;
				}

				if(cfg->time) {
					key[idx] = "Time";
					BYTE b = *(BYTE*)0xB70153;		// hour
					BYTE bb = *(BYTE*)0xB70152; // minute

					//value[idx] = new char[10];
					sprintf((char*)value[idx], "%d:%.2d", b, bb);

					idx++;
				}

				if(cfg->weapon) {
					key[idx] = "Current Weapon";
					int i = *(int*)0x0BAA410;

					//value[idx] = new char[25];
					sprintf((char*)value[idx], "%s", wNamesShortened[i]);

					idx++;
				}

				if(cfg->money) {
					key[idx] = "Money";
					int i = *(int*)0xB7CE50;

					//value[idx] = new char[15];
					sprintf((char*)value[idx], "$%d", i);

					idx++;
				}

				if(cfg->resolution) {
					key[idx] = "Resolution";
					int i = *(int*)0x0C17044;
					int ii = *(int*)0x0C17048;

					//value[idx] = new char[15];
					sprintf((char*)value[idx], "%dx%d", i, ii);

					idx++;
				}

				if(cfg->fps) {
					key[idx] = "FPS";
					int i = *(int*)0x0B729A0;
					//value[idx] = new char[10];
					sprintf((char*)value[idx], "%d", i);

					idx++;
				}

				if(cfg->gravity) {
					key[idx] = "Gravity"; 
					float f = *(float*)0x863984;

					//value[idx] = new char[11];
					sprintf((char*)value[idx], "%.8f", f);

					idx++;
				}

				if(cfg->pos) {
					key[idx] = "Position";
					float x = *(float*)0x0B6F2E4;
					float y = *(float*)0x0B6F2E8;
					float z = *(float*)0x08CCC44;

					sprintf((char*)value[idx], "X: %.3f Y: %.3f Z: %.3f", x, y, z);

					idx++;
				}

				if(cfg->wantedlevel) {
					key[idx] = "Wanted Level";
					int i = *(int*)0x0BAA420;
					sprintf((char*)value[idx], "%d", i);

					idx++;
				}

				// determine if we're playing sa-mp or single player:
				TCHAR wintitle[50];
				ZeroMemory(wintitle, sizeof(wintitle));
				HWND hwnd = *(HWND*)0xC97C1C;
				GetWindowText(hwnd, wintitle, sizeof(wintitle));

				if(cfg->paused) {
				HWND ActiveWin = GetForegroundWindow();  // Gets a handle to the window..
 
				TCHAR WindowText[50];
					GetWindowText(ActiveWin, WindowText, sizeof(WindowText));
					if(_tcsstr(wintitle, WindowText)) {
						// active window is the game
						key[idx] = "Paused";
						BYTE b = *(BYTE*)0xB7CB49;

						//value[idx] = new char[5];
						if(b) {
							sprintf((char*)value[idx], "Yes");
						} else {
							sprintf((char*)value[idx], "No");
						}

						idx++;

					} else {
						key[idx] = "Paused";
						sprintf((char*)value[idx], "Yes");

						idx++;
					}
				}

				
				if(_tcsstr(wintitle, _T("GTA:SA:MP"))) {
					if(cfg->serverip || cfg->name) {
						PCHAR szCmdLine = GetCommandLineA();

						char server[20];
						char port[9];
						char name[26];

						while(*szCmdLine) {

							if(*szCmdLine == '-' || *szCmdLine == '/') {
								szCmdLine++;
								switch(*szCmdLine) {

									case 'h':
										szCmdLine++;
										SetStringFromCommandLine(szCmdLine, server);
										break;
									case 'p':
										szCmdLine++;
										SetStringFromCommandLine(szCmdLine, port);
										break;
									case 'n':
										szCmdLine++;
										SetStringFromCommandLine(szCmdLine, name);
										break;
								}
							}
							szCmdLine++;
						}

						if(cfg->serverip) {
							key[idx] = "Server IP";

							//value[idx] = new char[30];
							sprintf((char*)value[idx], "%s:%s", server, port);

							idx++;
						}

						if(cfg->name) {
							key[idx] = "Name";
							//value[idx] = new char[26];
							sprintf((char*)value[idx], "%s", name);

							idx++;
						}
					}

				} else {
					// Single player
				}

				XfireSetCustomGameDataA(idx, key, value);
			}
		}
		Sleep(5000);
	}
}


void SetStringFromCommandLine(char *szCmdLine, char *szString)
{
	while(*szCmdLine == ' ') szCmdLine++;
	while(*szCmdLine &&
		  *szCmdLine != ' ' &&
		  *szCmdLine != '-' &&
		  *szCmdLine != '/') 
	{
		*szString = *szCmdLine;
		szString++; szCmdLine++;
	}
	*szString = '\0';
}


void LoadConfig() {
	string type = "";
	int enabled = 0;

	ifstream ifile("xfire.cfg");
	if (ifile) {
		// Our file exists already, now we can read from it.

		while(ifile >> type >> enabled) {
			if(type.compare("health") == 0) {
				cfg->health = enabled;
			} else if(type.compare("armour") == 0) {
				cfg->armour = enabled;
			} else if(type.compare("state") == 0) {
				cfg->state = enabled;
			} else if(type.compare("weather") == 0) {
				cfg->weather = enabled;
			} else if(type.compare("time") == 0) {
				cfg->time = enabled;
			} else if(type.compare("weapon") == 0) {
				cfg->weapon = enabled;
			} else if(type.compare("money") == 0) {
				cfg->money = enabled;
			} else if(type.compare("resolution") == 0) {
				cfg->resolution = enabled;
			} else if(type.compare("fps") == 0) {
				cfg->fps = enabled;
			} else if(type.compare("serverip") == 0) {
				cfg->serverip = enabled;
			} else if(type.compare("name") == 0) {
				cfg->name = enabled;
			} else if(type.compare("gravity") == 0) {
				cfg->gravity = enabled;
			} else if(type.compare("position") == 0) {
				cfg->pos = enabled;
			} else if(type.compare("wantedlevel") == 0) {
				cfg->wantedlevel = enabled;
			}
		}
		ifile.close();
	} else {
		// Else create the file and set defaults.
		ofstream ofile("xfire.cfg");
		ofile << "health 1" << endl;
		ofile << "armour 1" << endl;
		ofile << "state 1" << endl;
		ofile << "weather 1" << endl;
		ofile << "weapon 1" << endl;
		ofile << "money 1" << endl;
		ofile << "resolution 1" << endl;
		ofile << "fps 1" << endl;
		ofile << "serverip 1" << endl;
		ofile << "name 1" << endl;
		ofile << "gravity 1" << endl;
		ofile << "position 1" << endl;
		ofile << "wantedlevel 1" << endl;

		ofile.close();
		LoadConfig();
	}
}