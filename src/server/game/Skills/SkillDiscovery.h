/*
 * Copyright (C) 2016+     AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license: https://github.com/azerothcore/azerothcore-wotlk/blob/master/LICENSE-GPL2
 * Copyright (C) 2008-2016 TrinityCore <http://www.trinitycore.org/>
 * Copyright (C) 2005-2009 MaNGOS <http://getmangos.com/>
 */

#ifndef TRINITY_SKILLDISCOVERY_H
#define TRINITY_SKILLDISCOVERY_H

#include "Common.h"

class Player;

void LoadSkillDiscoveryTable();
uint32 GetSkillDiscoverySpell(uint32 skillId, uint32 spellId, Player* player);
bool HasDiscoveredAllSpells(uint32 spellId, Player* player);
uint32 GetExplicitDiscoverySpell(uint32 spellId, Player* player);


// RICHA
struct SkillDiscoveryEntry
{
    uint32  spellId;                                        // discavered spell
    uint32  reqSkillValue;                                  // skill level limitation
    float   chance;                                         // chance

    SkillDiscoveryEntry()
        : spellId(0), reqSkillValue(0), chance(0) {}

    SkillDiscoveryEntry(uint32 _spellId, uint32 req_skill_val, float _chance)
        : spellId(_spellId), reqSkillValue(req_skill_val), chance(_chance) {}
};
const std::unordered_map<int32, std::list<SkillDiscoveryEntry>>& GetSkillDiscoveryStore();

#endif
