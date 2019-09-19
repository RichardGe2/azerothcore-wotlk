

#include "ScriptMgr.h"
#include "Player.h"
#include "Configuration/Config.h"
#include "Chat.h"
#include "RichardClass.h"

#include <unordered_map>

class MyAllCreature : public AllCreatureScript
{
public:

	MyAllCreature() : AllCreatureScript("MyAllCreature")
	{
		int a = 0;
	}

	void Creature_SelectLevel(const CreatureTemplate* cinfo, Creature* creature)  override
	{
		return;
	}

	virtual void OnAllCreatureUpdate(Creature* creature, uint32 diff) override
	{
		return;
	}

private:

	class CreatureRicha
	{
	public:
		CreatureRicha()
		{
			Richar_difficuly_health = 1.0;
			Richar_difficuly_degat = 1.0;
		}

		float Richar_difficuly_health;
		float Richar_difficuly_degat;
	};


};

void AddMyAllCreatureScripts()
{
	new MyAllCreature();
}


