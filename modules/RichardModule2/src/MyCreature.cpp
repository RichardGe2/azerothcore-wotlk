

#include "ScriptMgr.h"
#include "Player.h"
#include "Configuration/Config.h"
#include "Chat.h"
#include "RichardClass.h"

class MyCreature : public CreatureScript
{
public:

	MyCreature() : CreatureScript("MyCreature")
	{
		int a=0;
	}

	void OnCreatureUpdate(Creature* creature, uint32 diff) // override
	{
		int a=0;
		return;
	}

};

void AddMyCreatureScripts()
{
	new MyCreature();
}


