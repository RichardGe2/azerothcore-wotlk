

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
	}


};

void AddMyGroupScripts()
{
	new MyGroup();
}


