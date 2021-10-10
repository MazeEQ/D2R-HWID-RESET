/*
I put this in its own class/file because "using namespace ..." was being weird in the global scope.
So I decided to put it into a new file/class to put it in an anonymous namespace and evade these issues :)
*/

/*
    Successor of Anti-Flag and Anti-Flag-V2.

    Developers:
    - DWORD64
    - Sixmax
    - MazeEQ
*/

#pragma once 

#include <Windows.h>
#include <iostream>
#include <algorithm>

#include "Console.hpp"
#include "WinColor.hpp"

#include "System.hpp"
#include "Processes.hpp"

#include "Extensions.hpp"

#include "Patch.hpp"

#include "D2R.hpp"

#include "Net.hpp"

#define NEWLINE cout << endl;

namespace
{
    using namespace std;
    using namespace colorwin;

    void PrintWatermark(CW_COLORS color = red)
    {
        withcolor watermarkColor(color);

        /*
        string* watermark = Help::readFile("./watermark.txt");
        if (watermark == nullptr)
        {
            delete watermark;
            Console::Log("Failed to get Watermark!", LogType::Error);
            return;
        }
        cout << (*watermark) << endl << endl;

        delete watermark;
        */

        std::cout << colorwin::color(yellow) << "This will reset your Diablo 2 Resurrected HWID ban. Please reboot after completion." << std::endl;
        std::cout << std::endl << std::endl << std::endl;

        std::cout << colorwin::color(red) << "WARNING:" << std::endl;
        std::cout << colorwin::color(yellow) << "all instances of 'D2 Resurrected' and 'Battle.Net' will be closed." << std::endl;
        std::cout << colorwin::color(yellow) << "Also your Browser Cookies will be cleared, so make sure you have all your Login's saved." << std::endl;
        
        std::cout << std::endl;
        withcolor reset(white);
       
    }

    class Exe
    {
    public:
        static int run()
        {
            Console::CentralizeConsole();
            Console::randomizeTitle();
            PrintWatermark();

                //return 0;

                
#if !_DEBUG
                Console::Log("Are you sure you want to run this program? [Y/N]", LogType::Info);
                if (tolower(cin.get()) != 'y')
                {
                    Console::Log("Done.");
                    return 0;
                }
#endif


                list<IPatch*>* patches = new list<IPatch*>
                {
                    new D2R,
                    new Networking
                };


                NEWLINE


#pragma region Process Killer
                    Console::Log("Killing Processes...", LogType::Warning);

                for_each(patches->begin(), patches->end(), [](IPatch* patch)
                    {
                        list<string>* procs = patch->GetProcesses();

                        for (string proc : *procs)
                        {
                            if (ProcessHandler::killByName(proc))
                            {
                                Console::Log(string("Killed '" + proc + "'.").c_str(), LogType::Success);
                            }
                        }

                        delete procs;
                    });

                Console::Log("Done killing.", LogType::Info);
#pragma endregion


                NEWLINE


#pragma region Patching
                    Console::Log("Patching...", LogType::Warning);

                for_each(patches->begin(), patches->end(), [](IPatch* patch)
                    {
                        Help::EnumDrives([=](char drive)
                            {

                               Console::Log(string("Patching: '" + patch->GetID()).c_str(), LogType::Info);
                                //Console::Log(string("Patching: '" + patch->GetID()).c_str());
                                patch->DoPatch(drive);

                                Console::Log(string("Finished patching " + patch->GetID()).c_str(), LogType::Success);

                                NEWLINE

                            });
                    });

                Console::Log("Done patching.", LogType::Info);
#pragma endregion


                NEWLINE


#pragma region Cleanup
                    for (IPatch* patch : *patches)
                        delete patch;

                patches->clear();

                delete patches;
#pragma endregion

                /*
                char a = 2;
                auto test = [a](char poop) mutable {
                    a++;
                };
                */


                Console::Log("Finished.", LogType::Info);
            

            NEWLINE

                Console::Log("You can RESTART your Computer now to finish the cleaning.", LogType::Info);

#if _DEBUG
            Cmd::Run("pause");
#else 
            Cmd::RunSilent("pause");
#endif 

            return 0;
        }
    };
}

#undef NEWLINE

/*
    Successor of Anti-Flag and Anti-Flag-V2.

    Developers:
    - DWORD64
    - Sixmax
*/
