

#include "ScriptMgr.h"
#include "Player.h"
#include "Configuration/Config.h"
#include "Chat.h"
#include "RichardClass.h"

class MyWorld : public WorldScript
{
public:

    MyWorld() : WorldScript("MyWorld") { }


    void OnStartup() override 
	{ 
		RichardClass::StaticRichardVariables_Init();

		////////////////////////////////////////////////////////
		//richard - init message
        sLog->outBasic("\n\n\n\n--------------------------------------\n\nMODE RICHARD WOTLK VERSION 10 -  version wolkainy2 ");

		char outt[4096];

		time_t t = time(0);   // get time now
		struct tm * now = localtime(&t);

		sprintf(outt, "Time : %02d/%02d/%d  -  %02d:%02d:%02d",
			now->tm_mday,
			now->tm_mon+1,
			now->tm_year + 1900,
			now->tm_hour,
			now->tm_min,
			now->tm_sec);

        sLog->outBasic(outt);
        sLog->outBasic("CMAKE_INTDIR = "  CMAKE_INTDIR);
        sLog->outBasic("\n\n--------------------------------------\n\n\n\n\n\n");
		////////////////////////////////////////////////////////




	}


};

void AddMyWorldScripts()
{
    new MyWorld();
}


