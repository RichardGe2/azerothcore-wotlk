

#include "ScriptMgr.h"
#include "Player.h"
#include "Configuration/Config.h"
#include "Chat.h"
#include "RichardClass.h"

class MyWorld : public WorldScript
{
public:

    MyWorld() : WorldScript("MyWorld")
	{
	//	m_lastTime_UpdateGroup3 = 0;
	}


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

	void OnUpdate(uint32 diff) override
	{
		// Retrieves the number of milliseconds that have elapsed since the system was started
		// up to 49.7 days.
		DWORD timeMS = GetTickCount();

		if ( timeMS - m_lastTime_UpdateGroup5 > 5000 )
		{
			//sWorld->getpl
			//GetPlayers();

			const SessionMap& sessions = sWorld->GetAllSessions();

			// enum connected players
			SessionMap::const_iterator itr;
			for (itr = sessions.begin(); itr != sessions.end(); ++itr)
			{
				if (itr->second &&
					itr->second->GetPlayer() 
					//itr->second->GetPlayer()->IsInWorld() &&
					)
				{
					Player* playy = itr->second->GetPlayer();
					const std::string& namm = playy->GetName();


					if ( !playy->m_InstanceValid )
					{
					//	playy->Say("DEBUG - pas kick",LANG_UNIVERSAL);
					//	playy->m_InstanceValid = true;
						int a=0;
					}
					else
					{
						int j=0;
					}


					//   #RICHA_PERMA_INSTANCE
					Map* playerMap = playy->GetMap();
					if ( playerMap )
					{
						InstanceMap* playerInstance = playerMap->ToInstanceMap();
						if ( playerInstance )
						{
							if (playerInstance->IsDungeon())
							{
								// pour faire ce bout de code, je me suis inspiré de    PermBindAllPlayers

								InstanceSave* save = sInstanceSaveMgr->GetInstanceSave(playerInstance->GetInstanceId());
								if (save)
								{
									const MapRefManager& mapRefManager = playerInstance->GetPlayers();

									Player* player = nullptr;
									Group* group = nullptr;
									// group members outside the instance group don't get bound
									for (MapRefManager::const_iterator itr = mapRefManager.begin(); itr != mapRefManager.end(); ++itr)
									{
										player = itr->GetSource();
										group = player->GetGroup();

										// players inside an instance cannot be bound to other instances
										// some players may already be permanently bound, in this case nothing happens
										InstancePlayerBind* bind = sInstanceSaveMgr->PlayerGetBoundInstance(player->GetGUIDLow(), save->GetMapId(), save->GetDifficulty());

										if (!bind || !bind->perm) // si l'intance n'est pas permanante
										{
											//WorldPacket data(SMSG_INSTANCE_SAVE_CREATED, 4); // message :  "You are now saved to this instance"
											//data << uint32(0);
											//player->GetSession()->SendPacket(&data);

											sInstanceSaveMgr->PlayerBindToInstance(player->GetGUIDLow(), save, true, player); // lier l'instance de facon permanante.

											char messageee[2048];
											sprintf(messageee, "RICHA - instance %d permanente cree.\n" , save->GetInstanceId() );

											ChatHandler(player->GetSession()).SendSysMessage(messageee);
										}

										// Xinef: Difficulty change prevention
										//if (group)
										//	group->SetDifficultyChangePrevention(DIFFICULTY_PREVENTION_CHANGE_BOSS_KILLED);
									}
								}
							}
							

						}
					}





					int a=0;
				}
			}


			int aaaa=0;

			m_lastTime_UpdateGroup5 = timeMS;
		}

	}


	DWORD m_lastTime_UpdateGroup5; // le groupe "5" correspond a des updates toutes les 3 secondes


};

void AddMyWorldScripts()
{
    new MyWorld();
}


