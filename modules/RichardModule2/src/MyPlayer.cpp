    
//
//   plugin de Richard 
//
//
            
#include "ScriptMgr.h"
#include "Player.h"
#include "Configuration/Config.h"
#include "Chat.h"

class MyPlayer : public PlayerScript{
public:

MyPlayer() : PlayerScript("MyPlayer") { }

void OnLogin(Player* player) override
{
    if (sConfigMgr->GetBoolDefault("MyCustom.enableHelloWorld", false))
    {
        ChatHandler(player->GetSession()).SendSysMessage("Hello World from Skeleton-Module!");
    }
}

void OnLootItem(Player* player, Item* item, uint32 count, uint64 lootguid) override
{
    int a = 0;
    return;
}
               
  
void OnChat(Player* player, uint32 type, uint32 lang, std::string& msg) override
{
    if (msg == "--kill")
    {
        uint64 target = player->GetTarget();
        Unit* targte2 = player->GetSelectedUnit();
        if ( targte2 && targte2->IsAlive() )
        {
            Unit::DealDamage(player, targte2, targte2->GetHealth(), nullptr, DIRECT_DAMAGE, SPELL_SCHOOL_MASK_NORMAL, nullptr, false, true);
            int a= 0;

        }

    }

   

    int a = 0;
    return;
}

void OnChat(Player* player, uint32 type, uint32 lang, std::string& msg, Player* receiver) override
{
    int a = 0;
    return;
}

void OnChat(Player* player, uint32 type, uint32 lang, std::string& msg, Group* group) override
{
    int a = 0;
    return;
}

void OnChat(Player* player, uint32 type, uint32 lang, std::string& msg, Guild* guild) override
{
    int a = 0;
    return;
}

void OnChat(Player* player, uint32 type, uint32 lang, std::string& msg, Channel* channel) override
{
    int a = 0;
    return;
}
};

void AddMyPlayerScripts()
{
new MyPlayer();
}

