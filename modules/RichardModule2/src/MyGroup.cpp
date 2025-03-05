

#include "ScriptMgr.h"
#include "Player.h"
#include "Configuration/Config.h"
#include "Chat.h"
#include "RichardClass.h"
#include "Group.h"


class MyGroup : public GroupScript
{
public:

	MyGroup() : GroupScript("MyGroup") { }


	void OnAddMember(Group* group, uint64 guid) override
	{
		if ( group->GetLootMethod() != FREE_FOR_ALL )
		{
			group->SetLootMethod(FREE_FOR_ALL);

			Player* leader = ObjectAccessor::FindPlayerInOrOutOfWorld(group->GetLeaderGUID());
			if ( leader )
			{
				leader->Say("On passe en Free for all.",LANG_UNIVERSAL);
			}
			else
			{
				int a=0;
			}
		}

		/*
		Player* player = ObjectAccessor::FindPlayerInOrOutOfWorld(guid);
        if (player)
        {
			std::string name = player->GetName();
			m_allPlayersAddedInGroups.insert(name);
		}
		*/

	}

	/*
	static void ForceValidInstance()
	{
		for(auto& i : m_allPlayersAddedInGroups)
		{
			Player* player = ObjectAccessor::FindPlayerByName(i);
			if ( player )
			{
				if ( !player->m_InstanceValid )
				{
					player->Say("DEBUG - pas kick",LANG_UNIVERSAL);
					player->m_InstanceValid = true;
				}
				else
				{
					int j=0;
				}
			}
		}
	}
	*/

	void OnRemoveMember(Group* group, uint64 guid, RemoveMethod method, uint64 kicker, const char* reason) override
	{
		/*
		Player* player = ObjectAccessor::FindPlayerInOrOutOfWorld(guid);
        if (player)
        {
			if ( !player->m_InstanceValid )
			{
				player->Say("DEBUG - pas kick",LANG_UNIVERSAL);
				player->m_InstanceValid = true;
			}
			else
			{
				int j=0;
			}
		}
		else
		{
			int r=0;
		}


		int a=0;
		*/

		//ForceValidInstance();

		return;
	}

	void OnDisband(Group* group) override
	{
		//ForceValidInstance();
	}

	// pour eviter les pointer invalid, je ne garde pas de  Group*  ou  Player* .
	// cette liste est juste la liste de tous les noms de joueur qui on été ajouté a des groupe depuis que le serveur est allumé
	//static std::set<std::string> m_allPlayersAddedInGroups;

};

//std::set<std::string> MyGroup::m_allPlayersAddedInGroups;

void AddMyGroupScripts()
{
	new MyGroup();
}


