/*
	Successor of Anti-Flag and Anti-Flag-V2.

	Developers:
	- DWORD64
	- Sixmax
	- Maze
*/

#pragma once 

#include "Patch.hpp"
#include "Help.hpp"

#include <iostream>
#include <filesystem>

namespace
{
	using namespace std;

	namespace fs = std::filesystem;

	class D2R : public IPatch
	{
	public:
		std::string GetID()
		{
			return "D2R";
		}

		list<string>* GetProcesses()
		{
			return new list<string>{
				"battle.net",
				"agent",
				"d2r",
			};
		}

		bool DoPatch(char drive)
		{
#pragma region General Blizz shit

			DELDIR(drive + S(":\\Users\\") + USER + S("\\AppData\\Local\\Battle.net\\"));
			DELDIR(drive + S(":\\Users\\") + USER + S("\\AppData\\Local\\Blizzard\\"));
			DELDIR(drive + S(":\\Users\\") + USER + S("\\AppData\\Local\\Blizzard Entertainment\\"));
			
			DELDIR(drive + S(":\\Users\\") + USER + S("\\AppData\\Roaming\\Battle.net\\"));
			
			DELDIR(drive + S(":\\Users\\") + USER + S("\\Documents\\Diablo II\\"));
			
			DELDIR(drive + S(":\\ProgramData\\Battle.net\\Setup\\"));
			
			DELDIR(drive + S(":\\ProgramData\\Battle.net\\Agent\\data\\"));
			
			DELDIR(drive + S(":\\ProgramData\\Battle.net\\Agent\\Logs\\"));
			
			DELDIR(drive + S(":\\ProgramData\\Blizzard Entertainment\\"));
			

			// clear db files and stuff // 
			DELFILE(drive + S(":\\Program Files (x86)\\Diablo II Resurrected\\.patch.result"));
			DELFILE(drive + S(":\\Program Files (x86)\\Diablo II Resurrected\\.product.db"));
			DELFILE(drive + S(":\\Program Files (x86)\\Diablo II Resurrected\\.product.db.old"));
			DELFILE(drive + S(":\\Program Files (x86)\\Diablo II Resurrected\\Launcher.db.old"));
			DELFILE(drive + S(":\\Program Files (x86)\\Diablo II Resurrected\\.product.db.old.new"));
			DELFILE(drive + S(":\\Program Files (x86)\\Diablo II Resurrected\\Launcher.db.old.new"));
			DELFILE(drive + S(":\\Program Files (x86)\\Diablo II Resurrected\\Launcher.db"));
			DELFILE(drive + S(":\\Program Files (x86)\\Diablo II Resurrected\\.build.info"));
			DELFILE(drive + S(":\\Program Files (x86)\\Diablo II Resurrected\\blz-log.txt"));
			DELFILE(drive + S(":\\Program Files (x86)\\Battle.net\\.product.db"));
			DELFILE(drive + S(":\\Program Files (x86)\\Battle.net\\Launcher.db"));
			DELFILE(drive + S(":\\Program Files (x86)\\Battle.net\\.product.db.new"));
			DELFILE(drive + S(":\\Program Files (x86)\\Battle.net\\.product.db.old"));
			DELFILE(drive + S(":\\Program Files (x86)\\Battle.net\\Launcher.db.new"));
			DELFILE(drive + S(":\\Program Files (x86)\\Battle.net\\Launcher.db.old"));
			DELFILE(drive + S(":\\Program Files (x86)\\Battle.net\\.build.info"));
			DELFILE(drive + S(":\\Program Files (x86)\\Battle.net\\.patch.result"));
			DELFILE(drive + S(":\\ProgramData\\Battle.net\\Agent\\.patch.result"));
			DELFILE(drive + S(":\\Program Files (x86)\\Battle.net\\Agent\\.product.db"));
			DELFILE(drive + S(":\\Program Files (x86)\\Battle.net\\Agent\\product.db"));


			// delete old bnet agents. the one with the greatest number is the latest one all other can be deleted
			{
				string agentsPath = S(drive + S(":\\ProgramData\\Battle.net\\Agent\\"));

				if (fs::exists(agentsPath))
				{
					string latestAgent = "";
					int greatest = 0;

					for (const auto& entry : fs::directory_iterator(agentsPath))
					{
						if (entry.is_directory() == false)
							continue;

						auto path = entry.path().u8string();
						auto args = Help::split(path, '\\');
						auto folder = args[args.size() - 1];

						if (folder._Starts_with("Agent") == false)
							continue;

						int agentID = stoi(Help::split(folder, '.')[1]);

						if (agentID > greatest)
						{
							greatest = agentID;
							latestAgent = path;
						}
					}

					for (const auto& entry : fs::directory_iterator(agentsPath))
					{
						if (entry.is_directory() == false)
							continue;

						auto path = entry.path().u8string();
						auto args = Help::split(path, '\\');
						auto folder = args[args.size() - 1];

						if (folder._Starts_with("Agent") == false)
							continue;

						if (path != latestAgent)
						{
							DELDIR(path);
						}
					}
				}
			}

			REGDEL("HKEY_CURRENT_USER\\SOFTWARE\\Blizzard Entertainment\\Battle.net");
			REGDEL("HKEY_LOCAL_MACHINE\\SOFTWARE\\WOW6432Node\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\Battle.net");
			REGDEL("HKEY_LOCAL_MACHINE\\SOFTWARE\\WOW6432Node\\Blizzard Entertainment");
			REGDEL("HKEY_CURRENT_USER\\SOFTWARE\\Blizzard Entertainment");
			REGDEL("HKEY_CURRENT_USER\\SOFTWARE\\Activision");
			REGDEL("HKEY_CLASSES_ROOT\\Applications\\D2R.exe");
			REGDEL("HKEY_CURRENT_USER\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\CapabilityAccessManager\\ConsentStore\\microphone\\NonPackaged\\C:#Program Files (x86)#Battle.net#Battle.net.exe");
			REGDEL("HKEY_CURRENT_USER\\SOFTWARE\\Microsoft\\RADAR\\HeapLeakDetection\\DiagnosedApplications\\D2R.exe");
			REGDEL("HKEY_CURRENT_USER\\VirtualStore\\MACHINE\\SOFTWARE\\WOW6432Node\\Activision");
			REGDEL("HKEY_CURRENT_USER\\SOFTWARE\\Classes\\VirtualStore\\MACHINE\\SOFTWARE\\WOW6432Node\\Activision");
#pragma endregion 

#pragma region Cheats n stuff
			/* Useless for Diablo 2, will revisit when Bots/Hacks become a thing*/
			/* Start of Ow-Cheat Orion*/
			DELDIR(drive + S(":\\ProgramData\\Orion\\"));
			/* END of Ow-Cheat Orion*/
			
			
			/* START of Ow-Cheat Critical Hit */
			REGDEL("HKLM\\SOFTWARE\\00330-80000-00000-AA302");
			/* END of Ow-Cheat Critical Hit */


			/*Start of Ow-Cheat: Noble*/
			/*END of Ow-Cheat: Noble*/

#pragma endregion

			return true;
		}
	};
}

/*
	Successor of Anti-Flag and Anti-Flag-V2.

	Developers:
	- DWORD64
	- Sixmax
*/