

#include "RichardClass.h"


#include "ScriptMgr.h"
#include "Player.h"
#include "Configuration/Config.h"
#include "Chat.h"
#include "DBCStores.h"
#include "GuildMgr.h"
#include "ReputationMgr.h"
#include "InstanceSaveMgr.h"
#include "DisableMgr.h"
#include "LootItemStorage.h"
#include "Group.h"
#include "WorldDatabase.h"


#define ZONE_UPDATE_INTERVAL (2*IN_MILLISECONDS)

#define PLAYER_SKILL_INDEX(x)	   (PLAYER_SKILL_INFO_1_1 + ((x)*3))
#define PLAYER_SKILL_VALUE_INDEX(x) (PLAYER_SKILL_INDEX(x)+1)
#define PLAYER_SKILL_BONUS_INDEX(x) (PLAYER_SKILL_INDEX(x)+2)

#define SKILL_VALUE(x)		 PAIR32_LOPART(x)
#define SKILL_MAX(x)		   PAIR32_HIPART(x)
#define MAKE_SKILL_VALUE(v, m) MAKE_PAIR32(v, m)

#define SKILL_TEMP_BONUS(x)	int16(PAIR32_LOPART(x))
#define SKILL_PERM_BONUS(x)	int16(PAIR32_HIPART(x))
#define MAKE_SKILL_BONUS(t, p) MAKE_PAIR32(t, p)




// example  [i=4536]
// return TRUE if taken in charge
bool RichardClass::ExecuteCommand_richard_B(const char* text, Player* playerrrr)
{


	if (text == 0)
	{
		return false;
	}

	if (text[0] == 0)
	{
		return false;
	}

	int lennn = strlen(text);
	if (lennn < 5)
	{
		return false;
	}


	if (text[lennn - 1] != ']')
	{
		return false;
	}


	if (text[0] == '['
		&&  text[1] == 'i'
		&&  text[2] == '='
		)
	{
		char number[1024];
		number[0] = 0;
		for (int i = 3; ; i++)
		{
			if (text[i] >= '0' &&  text[i] <= '9')
			{
				number[i - 3] = text[i];
				number[i - 3 + 1] = 0;
			}
			else
			{
				break;
			}
		}

		int numberID = atoi(number);

		bool charggeee = ExecuteCommand_richard_2(numberID, playerrrr);

		return charggeee;
	}


	return false;

}


bool StrCmp_noCase(const char* a, const char* b)
{
	for (int i = 0; ; i++)
	{
		char minus_a = a[i];
		char minus_b = b[i];

		if (minus_a >= 'A' && minus_a <= 'Z')
		{
			minus_a = minus_a - 'A' + 'a';
		}
		if (minus_b >= 'A' && minus_b <= 'Z')
		{
			minus_b = minus_b - 'A' + 'a';
		}

		if (minus_a != minus_b)
		{
			return false;
		}

		if (minus_a == 0)
		{
			break;
		}

	}

	return true;
}



// example  [i=canine de lion des savanes]  
//   ou	 [i="canine de lion des savanes"]  
// la casse n'est PAS prise en compte
// return TRUE if taken in charge
bool RichardClass::ExecuteCommand_richard_C(const char* text, Player* playerrr)
{

	int SIZE___ = 3;

	if (text == 0)
	{
		return false;
	}

	if (text[0] == 0)
	{
		return false;
	}

	int lennn = strlen(text);
	if (lennn < SIZE___ + 2)
	{
		return false;
	}


	if (text[lennn - 1] != ']')
	{
		return false;
	}


	if (text[SIZE___] == '\"')
	{
		if (text[lennn - 2] != '\"')
		{
			return false;
		}
	}

	bool takenInCharge = false;

	if (text[SIZE___ - 3] == '['
		&&  text[SIZE___ - 2] == 'i'
		&&  text[SIZE___ - 1] == '='
		)
	{

		bool guillementUse = false;
		int txtOffset = SIZE___;
		if (text[txtOffset] == '\"')
		{
			guillementUse = true;
			txtOffset++;
		}


		char itemName[1024];
		itemName[0] = 0;
		for (int i = txtOffset; ; i++)
		{
			if (guillementUse && text[i] == '\"')
			{
				break;
			}

			if (!guillementUse && text[i] == ']')
			{
				break;
			}

			if (text[i] == 0)
			{
				break;
			}

			itemName[i - txtOffset] = text[i];
			itemName[i - txtOffset + 1] = 0;

		}

		bool objectFound = false;

		/*

		TODO !!!!!  trouver comment faire sur azecore

		// sItemStorage se remplace par  sItemSetStore ??

	   // for (uint32 itemID = 0; itemID < sItemStorage.GetMaxEntry(); ++itemID) <-- version cmangos
		for (uint32 itemID = 0; itemID < sItemSetStore.GetNumRows(); ++itemID)
		{
			//ItemPrototype const* prototype = sObjectMgr.GetItemPrototype(itemID);
			ItemPrototype const* prototype = sItemSetStore.LookupEntry<ItemPrototype>(itemID);

			if (prototype && StrCmp_noCase(prototype->Name1, itemName))
			{
				objectFound = true;
				takenInCharge = ExecuteCommand_richard_2(itemID);
				break;
			}

		}
		*/



		if (!objectFound)
		{
			char messageOUt[2048];
			sprintf(messageOUt, "item '%s' not found. (TODO !!!)", itemName);
			//ChatHandler(player->GetSession()).SendSysMessage(messageOUt);
			ChatHandler(playerrr->GetSession()).SendSysMessage(messageOUt);
		}

	}


	return takenInCharge;

}


// example  q=L'impact
//   ou	 q="L'impact" 
// la casse n'est PAS prise en compte
bool RichardClass::ExecuteCommand_richard_D(const char* text, Player* playerrr)
{


	if (text == 0)
	{
		return false;
	}

	if (text[0] == 0)
	{
		return false;
	}

	int SIZE___ = 2;

	int lennn = strlen(text);
	if (lennn < SIZE___ + 1)
	{
		return false;
	}


	//if ( text[lennn-1] != ']' )
	//{
	//	return false;
	//}


	if (text[SIZE___] == '\"')
	{
		if (text[lennn - 2] != '\"')
		{
			return false;
		}
	}


	if (text[0] == 'q'
		&&  text[1] == '='
		)
	{

		bool guillementUse = false;
		int txtOffset = SIZE___;
		if (text[txtOffset] == '\"')
		{
			guillementUse = true;
			txtOffset++;
		}


		char questName[1024];

		questName[0] = 0;
		for (int i = txtOffset; ; i++)
		{
			if (guillementUse && text[i] == '\"')
			{
				break;
			}

			if (!guillementUse && text[i] == '\0')
			{
				break;
			}

			if (text[i] == 0)
			{
				//command syntax error
				return false;
			}

			questName[i - txtOffset] = text[i];
			questName[i - txtOffset + 1] = 0;

		}

		bool objectFound = false;

		//   Player* playerrr = m_session->GetPlayer();

		if (!playerrr)
		{
			//error ?
			return false;
		}


		std::string questNameStr = std::string(questName);

		unsigned int nbQuest = 0;
		unsigned int questID = 0;
		Quest* queeeFound = 0;


		//for (const auto& ques : sObjectMgr.GetQuestTemplates())
		//{

		ObjectMgr::QuestMap const& questTemplates = sObjectMgr->GetQuestTemplates();
		for (ObjectMgr::QuestMap::const_iterator iter = questTemplates.begin(); iter != questTemplates.end(); ++iter)
		{
			Quest* queee = iter->second;

			uint32 idd = queee->GetQuestId();

			// on est obligé de faire ca, car plusieurs quetes peuvent avoir le meme noms, genre Tome of the Cabal - 
			// donc il faut s'assurer de prendre la quete qui est dans l'inventaire du joueur
			bool thisQuestIsInPlayerList = false;
			for (int i = 0; i < MAX_QUEST_LOG_SIZE; ++i)
			{
				uint32 questidFromPlayer = playerrr->GetQuestSlotQuestId(i);
				if (questidFromPlayer == idd)
				{
					thisQuestIsInPlayerList = true;
				}
			}


			//Quest* queee = ques.second;
			std::string title = queee->GetTitle();
			int aaa = 0;
			if (thisQuestIsInPlayerList && title == questNameStr)
			{
				queeeFound = queee;
				objectFound = true;
				questID = idd;
				int aaa = 0;
			}
			nbQuest++;
		}






		if (!objectFound)
		{
			char messageOUt[2048];
			sprintf(messageOUt, "quest '%s' not found.", questName);
			ChatHandler(playerrr->GetSession()).SendSysMessage(messageOUt);
		}
		else
		{



			char messageOUt[2048];
			sprintf(messageOUt, "quest=%d", questID);
			ChatHandler(playerrr->GetSession()).SendSysMessage(messageOUt);

			if (queeeFound->RequiredItemCount[0])
			{
				std::string itemNameLink = Richa_itemIdToNiceLink(queeeFound->RequiredItemId[0]);
				char messageOUt[2048];
				sprintf(messageOUt, "%d %s (item=%d)", queeeFound->RequiredItemCount[0], itemNameLink.c_str(), queeeFound->RequiredItemId[0]);
				ChatHandler(playerrr->GetSession()).SendSysMessage(messageOUt);
			}
			if (queeeFound->RequiredItemCount[1])
			{
				std::string itemNameLink = Richa_itemIdToNiceLink(queeeFound->RequiredItemId[1]);
				char messageOUt[2048];
				sprintf(messageOUt, "%d %s (item=%d)", queeeFound->RequiredItemCount[1], itemNameLink.c_str(), queeeFound->RequiredItemId[1]);
				ChatHandler(playerrr->GetSession()).SendSysMessage(messageOUt);
			}
			if (queeeFound->RequiredItemCount[2])
			{
				std::string itemNameLink = Richa_itemIdToNiceLink(queeeFound->RequiredItemId[2]);
				char messageOUt[2048];
				sprintf(messageOUt, "%d %s (item=%d)", queeeFound->RequiredItemCount[2], itemNameLink.c_str(), queeeFound->RequiredItemId[2]);
				ChatHandler(playerrr->GetSession()).SendSysMessage(messageOUt);
			}
			if (queeeFound->RequiredItemCount[3])
			{
				std::string itemNameLink = Richa_itemIdToNiceLink(queeeFound->RequiredItemId[3]);
				char messageOUt[2048];
				sprintf(messageOUt, "%d %s (item=%d)", queeeFound->RequiredItemCount[3], itemNameLink.c_str(), queeeFound->RequiredItemId[3]);
				ChatHandler(playerrr->GetSession()).SendSysMessage(messageOUt);
			}
			if (queeeFound->RequiredNpcOrGoCount[0])
			{
				char messageOUt[2048];
				if (queeeFound->RequiredNpcOrGo[0] > 0)
				{
					sprintf(messageOUt, "%d npc=%d", queeeFound->RequiredNpcOrGoCount[0], queeeFound->RequiredNpcOrGo[0]);
				}
				else
				{
					sprintf(messageOUt, "%d object=%d", queeeFound->RequiredNpcOrGoCount[0], -queeeFound->RequiredNpcOrGo[0]);
				}
				ChatHandler(playerrr->GetSession()).SendSysMessage(messageOUt);
			}
			if (queeeFound->RequiredNpcOrGoCount[1])
			{
				char messageOUt[2048];
				if (queeeFound->RequiredNpcOrGo[1] > 0)
				{
					sprintf(messageOUt, "%d npc=%d", queeeFound->RequiredNpcOrGoCount[1], queeeFound->RequiredNpcOrGo[1]);
				}
				else
				{
					sprintf(messageOUt, "%d object=%d", queeeFound->RequiredNpcOrGoCount[1], -queeeFound->RequiredNpcOrGo[1]);
				}
				ChatHandler(playerrr->GetSession()).SendSysMessage(messageOUt);
			}
			if (queeeFound->RequiredNpcOrGoCount[2])
			{
				char messageOUt[2048];
				if (queeeFound->RequiredNpcOrGo[2] > 0)
				{
					sprintf(messageOUt, "%d npc=%d", queeeFound->RequiredNpcOrGoCount[2], queeeFound->RequiredNpcOrGo[2]);
				}
				else
				{
					sprintf(messageOUt, "%d object=%d", queeeFound->RequiredNpcOrGoCount[2], -queeeFound->RequiredNpcOrGo[2]);
				}
				ChatHandler(playerrr->GetSession()).SendSysMessage(messageOUt);
			}
			if (queeeFound->RequiredNpcOrGoCount[3])
			{
				char messageOUt[2048];
				if (queeeFound->RequiredNpcOrGo[3] > 0)
				{
					sprintf(messageOUt, "%d npc=%d", queeeFound->RequiredNpcOrGoCount[3], queeeFound->RequiredNpcOrGo[3]);
				}
				else
				{
					sprintf(messageOUt, "%d object=%d", queeeFound->RequiredNpcOrGoCount[3], -queeeFound->RequiredNpcOrGo[3]);
				}
				ChatHandler(playerrr->GetSession()).SendSysMessage(messageOUt);
			}

		}

		return true; // si le string commence par  q=   on va considerer que c'est pris en charge dans tous les cas
	}


	return false;

}


inline bool isWhiteSpace_ri(char c)
{
	return ::isspace(int(c)) != 0;
}


/**
 * Function skip all whitespaces in args string
 *
 * @param args variable pointer to non parsed args string, updated at function call to new position (with skipped white spaces)
 *			 allowed nullptr string pointer stored in *args
 */
void SkipWhiteSpaces_ri(char** args)
{
	if (!*args)
		return;

	while (isWhiteSpace_ri(**args))
		++(*args);
}



/**
 * Function extract to val arg unsigned integer value or fail
 *
 * @param args variable pointer to non parsed args string, updated at function call to new position (with skipped white spaces)
 * @param val  return extracted value if function success, in fail case original value unmodified
 * @param base set used base for extracted value format (10 for decimal, 16 for hex, etc), 0 let auto select by system internal function
 * @return	 true if value extraction successful
 */
bool  RichardClass::ExtractUInt32Base(char** args, uint32& val, uint32 base) 
{
	if (!*args || !** args)
		return false;

	char* tail = *args;

	unsigned long valRaw = strtoul(*args, &tail, base);

	if (tail != *args && isWhiteSpace_ri(*tail))
		*(tail++) = '\0';
	else if (tail && *tail)								 // some not whitespace symbol
		return false;									   // args not modified and can be re-parsed

	if (valRaw > std::numeric_limits<uint32>::max())
		return false;

	// value successfully extracted
	val = uint32(valRaw);
	*args = tail;

	SkipWhiteSpaces_ri(args);
	return true;
}


//convert example :
// "|cff9d9d9d|Hitem:3965:0:0:0|h[Gants en cuir épais]|h|r"  -->  3965 
// return -1 if fail.
unsigned long RichardClass::Richa_NiceLinkToIitemID(const char* str)
{
	std::string input = std::string(str);

	if (
		input.size() > 24
		&& input[0] == '|'
		&&  input[1] == 'c'
		&&  input[10] == '|'
		&&  input[11] == 'H'
		&&  input[12] == 'i'
		&&  input[13] == 't'
		&&  input[14] == 'e'
		&&  input[15] == 'm'
		&&  input[16] == ':'
		)
	{
		std::string id = "";
		for (int i = 17; ; i++)
		{
			if (i >= input.size())
			{
				return -1;
			}

			if (input[i] < '0' || input[i] > '9')
				break;

			id += input[i];
		}

		unsigned long idFinal = std::strtoul(id.c_str(), NULL, 10);

		return idFinal;
	}
	return -1;
}


//deja, on regarde si   text est un lien vers un objet  (joueur a fait  Majuscule + click gauche sur objet)
//
// exemple :  |cffffffff|Hitem:2692:0:0:0|h[Hot Spices]|h|r
// exemple :  |cff1eff00|Hitem:70010:0:0:0|h[YouhaiCoin Paragon]|h|r
//exemple :   |cffa335ee|Hitem:13353:0:0:0|h[Book of the Dead]|h|r
//
// exemple pour WOTLK :
// " |cffffffff|Hitem:6948:0:0:0:0:0:0:0:1|h[Pierre de foyer]|h|r"   ( avec un espace au debut ! )
//
//je crois que le premier nombre est la couleur
bool RichardClass::ExecuteCommand_richard_A(const char* text, Player* playerrrr)
{

	//
	//
	// TODO : utiliser : Richa_NiceLinkToIitemID plutot,  pour unifier
	//
	//

	if (text == 0)
	{
		return false;
	}

	if (text[0] == 0)
	{
		return false;
	}

	const char beg[] = " |cffffffff|Hitem:";

	int i = 0;
	for (;; i++)
	{
		if (beg[i] == 0)
		{
			break;
		}

		if (i >= 3 && i <= 10)
		{
			if (text[i] >= '0' && text[i] <= '9'
				|| text[i] >= 'a' && text[i] <= 'f')
			{
				// ok : info sur la couleur
			}
			else
			{
				return false;
			}

		}


		else if (text[i] != beg[i])
		{
			return false;
		}
	}

	char number[1024];
	int j = 0;
	for (;; i++)
	{
		if (text[i] == ':')
		{
			break;
		}

		if (text[i] == 0)
		{
			return false;
		}

		if (j > 100)
		{
			return false;
		}

		number[j] = text[i]; j++;
		number[j] = 0;

	}

	int numberID = atoi(number);

	bool chargeee = ExecuteCommand_richard_2(numberID, playerrrr);

	return chargeee;
}



bool RichardClass::ExecuteCommand_richard_2(int numberID, Player* player)
{


	// CETTE FONCTION EST  COMPLIQUEE a porter dans azecore ... TODO : la recoder. ......

	return false;
	/*






	char messageOUt[2048];

	ItemPrototype const* itemProtoype = sItemStorage.LookupEntry<ItemPrototype>(numberID);
	if (!itemProtoype)
		return false;


   // if (m_session == 0)
   // {
   //	 return false;
   // }


	//Player* player = m_session->GetPlayer();

	if (player == 0)
	{
		return false;
	}







	bool developerInfo = false;
	ObjectGuid const& guiiddd = player->GetObjectGuid();
	uint32 account_guid = sObjectMgr.GetPlayerAccountIdByGUID(guiiddd);

	// #LISTE_ACCOUNT_HERE  -   ce hashtag repere tous les endroit que je dois updater quand je rajoute un nouveau compte - ou perso important
	if (account_guid == 5  // richard
		|| account_guid == 7  // grandjuge
		|| account_guid == 10  // richard2
		)
	{
		developerInfo = true;
	}




	if (developerInfo)
	{
		sprintf(messageOUt, "Item.entry=%d", numberID);
		ChatHandler(player->GetSession()).SendSysMessage(messageOUt);
	}
	else
	{
		sprintf(messageOUt, "item=%d", numberID);
		ChatHandler(player->GetSession()).SendSysMessage(messageOUt);
	}


	sprintf(messageOUt, "name=%s", itemProtoype->Name1);
	ChatHandler(player->GetSession()).SendSysMessage(messageOUt);


	if (itemProtoype->ItemSet != 0)
	{
		sprintf(messageOUt, "Id de Set = %d", itemProtoype->ItemSet);
		ChatHandler(player->GetSession()).SendSysMessage(messageOUt);
	}


	int goldAmount = itemProtoype->SellPrice;
	int nbpo = goldAmount / 10000;
	int nbpa = (goldAmount - nbpo * 10000) / 100;
	int nbpc = (goldAmount - nbpo * 10000 - nbpa * 100);
	if (developerInfo)
	{
		sprintf(messageOUt, "Item.SellPrice= %d  %d  %d", nbpo, nbpa, nbpc);
		ChatHandler(player->GetSession()).SendSysMessage(messageOUt);
	}
	else
	{
		if (goldAmount == 0)
		{
			sprintf(messageOUt, "Pas de prix de vente");
			ChatHandler(player->GetSession()).SendSysMessage(messageOUt);
		}
		else
		{
			sprintf(messageOUt, "Prix de vente : %d - %d - %d", nbpo, nbpa, nbpc);
			ChatHandler(player->GetSession()).SendSysMessage(messageOUt);
		}
	}



	if (developerInfo)
	{
		sprintf(messageOUt, "Item.spellid_1=%d", itemProtoype->Spells[0].SpellId);
		ChatHandler(player->GetSession()).SendSysMessage(messageOUt);
	}

	int searchKnowSpell = 0;

	SpellEntry const* spellProtoypeLearn = 0;

	if (itemProtoype->Spells[0].SpellId != 0)
	{
		SpellEntry const* spellProtoype = sSpellStore.LookupEntry(itemProtoype->Spells[0].SpellId);
		if (spellProtoype)
		{

			if (spellProtoype->Effect[0] == SPELL_EFFECT_LEARN_SPELL)
			{
				spellProtoypeLearn = sSpellStore.LookupEntry(spellProtoype->EffectTriggerSpell[0]);
				if (spellProtoypeLearn)
				{
					sprintf(messageOUt, "Item.spellid_1->effect#1= Learn Spell %d (%s)", spellProtoype->EffectTriggerSpell[0], spellProtoypeLearn->SpellName[0]);
					searchKnowSpell = spellProtoype->EffectTriggerSpell[0];
				}
				else
				{
					sprintf(messageOUt, "Item.spellid_1->effect#1= Learn Spell %d (???)", spellProtoype->EffectTriggerSpell[0]);
				}


				if (developerInfo)
				{
					ChatHandler(player->GetSession()).SendSysMessage(messageOUt);
				}
			}

			else if (spellProtoype->Effect[0] == SPELL_EFFECT_CREATE_ITEM)
			{
				if (developerInfo)
				{
					sprintf(messageOUt, "Item.spellid_1->effect#1= Create Item %d ", 0);
					ChatHandler(player->GetSession()).SendSysMessage(messageOUt);
				}
			}

			else if (spellProtoype->Effect[0] == SPELL_EFFECT_APPLY_AURA)
			{
				if (developerInfo)
				{
					sprintf(messageOUt, "Item.spellid_1->effect#1= apply aura ");
					ChatHandler(player->GetSession()).SendSysMessage(messageOUt);
				}
			}

			else
			{
				if (developerInfo)
				{
					sprintf(messageOUt, "Item.spellid_1->effect#1= ?%d? ", spellProtoype->Effect[0]);
					ChatHandler(player->GetSession()).SendSysMessage(messageOUt);
				}
			}

			int aaa = 0;

		}

	}




	if (searchKnowSpell != 0)
	{
		bool KnownByPlayer = false;

		std::string nameToSearch = "";

		// #LISTE_ACCOUNT_HERE  -   ce hashtag repere tous les endroit que je dois updater quand je rajoute un nouveau compte - ou perso important
		if (strcmp(player->GetName(), "Bouzigouloum") == 0)
		{
			nameToSearch = "Boulette";
		}
		else if (strcmp(player->GetName(), "Adibou") == 0)
		{
			nameToSearch = "Bouillot";
		}
		else if (strcmp(player->GetName(), "Grandtroll") == 0)
		{
			nameToSearch = "Bouillot"; // for debug
		}
		else if (strcmp(player->GetName(), "Grandjuge") == 0)
		{
			nameToSearch = "Boulette"; // for debug
		}
		else if (strcmp(player->GetName(), "Bouillot") == 0)
		{
			nameToSearch = "Bouillot"; // for debug
		}
		else if (strcmp(player->GetName(), "Boulette") == 0)
		{
			nameToSearch = "Boulette"; // for debug
		}
		else
		{
			sprintf(messageOUt, "INFO : pas de perso primaire associe a ce perso");
			ChatHandler(player->GetSession()).SendSysMessage(messageOUt);
			return false;
		}

		// en fait je pense que c'est mieux d'utiliser la liste ci dessous plutot que la liste ci dessus
		// c'est mieux de faire ca dans tous les cas ,  c'est a dire associer un metier a notre premier perso :
		// lister ici LE perso PRINCIPAL qui est responsable du metier.
		if (false) {}
		if (itemProtoype->RequiredSkill == SKILL_COOKING
			|| itemProtoype->RequiredSkill == SKILL_ALCHEMY
			|| itemProtoype->RequiredSkill == SKILL_HERBALISM
			|| itemProtoype->RequiredSkill == SKILL_LEATHERWORKING
			|| itemProtoype->RequiredSkill == SKILL_TAILORING
			|| itemProtoype->RequiredSkill == SKILL_FIRST_AID
			)
		{
			nameToSearch = "Boulette";
		}
		if (itemProtoype->RequiredSkill == SKILL_ENGINEERING
			|| itemProtoype->RequiredSkill == SKILL_BLACKSMITHING
			|| itemProtoype->RequiredSkill == SKILL_FISHING
			|| itemProtoype->RequiredSkill == SKILL_ENCHANTING
			|| itemProtoype->RequiredSkill == SKILL_MINING
			)
		{
			nameToSearch = "Bouillot";
		}
		else
		{
			//sprintf(messageOUt,"INFO : pas de perso primaire associe a ce type de plan");
			//ChatHandler(player->GetSession()).SendSysMessage(messageOUt);
			//return;
			int aaa = 0;
		}




		//find most recent file
		time_t t = time(0);   // get time now
		struct tm * now = localtime(&t);


		int day = now->tm_mday;
		int mon = now->tm_mon + 1;
		int yea = now->tm_year + 1900;

		char nameFile[2048];
		nameFile[0] = 0;

		for (;;)
		{

			sprintf(nameFile, "RICHARDS_WOTLK/_ri_stat_%s_%d_%02d_%02d.txt",
				nameToSearch.c_str(),
				yea,
				mon,
				day
			);

			std::ifstream file(nameFile);
			if (file)
			{
				file.close();
				break;
			}

			day--;
			if (day == 0)
			{
				day = 31;
				mon--;
				if (mon == 0)
				{
					mon = 12;
					yea--;
					if (yea == 2016)
					{
						nameFile[0] = 0;
						sprintf(messageOUt, "ERROR: pas de fichier pour le perso primaire");
						ChatHandler(player->GetSession()).SendSysMessage(messageOUt);
						return false;
					}
				}
			}
		}


		std::ifstream myfile(nameFile);

		if (myfile.is_open())
		{
			bool insideSpellList = false;
			std::string line;
			int lineInsideListSpellSection = 0;
			int nbSpellsInSection_1 = -1; // read depuis la ligne ListSpellCount,
			int nbSpellsInSection_2 = -1; // on compte le nombre de spell reel
			while (std::getline(myfile, line))
			{
				if (line == "#LIST_SPELLS =================================")
				{
					insideSpellList = true;
					lineInsideListSpellSection = 0;
					nbSpellsInSection_2 = 0;
				}

				//si on rencontre une nouvelle section
				else if (insideSpellList && line.length() >= 1 && line[0] == '#')
				{
					insideSpellList = false;
					break;
				}

				else if (insideSpellList)
				{

					//si c'est la premiere ligne, ca indique le nombre de spell
					if (lineInsideListSpellSection == 0)
					{
						if (line.size() >= 16
							&& line.substr(0, 15) == "ListSpellCount,"
							)
						{
							nbSpellsInSection_1 = atoi(&((line.c_str())[15]));
							int ggg = 0;
						}
						else
						{
							sprintf(messageOUt, "ERREUR DE LECTURE DE FICHIER 001 !!!!");
							ChatHandler(player->GetSession()).SendSysMessage(messageOUt);
							myfile.close();
							return false;
						}
					}
					else if (line.size() == 0)
					{
						int aa = 0;
					}
					else
					{

						char number[2048];
						number[0] = 0;
						for (int i = 0; i < line.length(); i++)
						{
							if (line[i] == ',')
							{
								break;
							}

							if (i > 100)
							{
								myfile.close();
								return false;
							}

							number[i] = line[i];
							number[i + 1] = 0;
						}

						if (number[0] >= '0' && number[0] <= '9')
						{
							int spellID = atoi(number);

							if (searchKnowSpell == spellID)
							{
								KnownByPlayer = true;
								//break;  <--- on ne break PAS  car on doit compter tous les spell,  juste dans un but de bien verifier que tout est OK.
							}

							int aa = 0;
						}


						nbSpellsInSection_2++;

					}

					lineInsideListSpellSection++;
				}
			} // pour chaque ligne du fichier


			myfile.close();


			if (nbSpellsInSection_1 != nbSpellsInSection_2)
			{
				sprintf(messageOUt, "ERREUR DE LECTURE DE FICHIER 002 !!!!");
				ChatHandler(player->GetSession()).SendSysMessage(messageOUt);
				return false;
			}


			if (nbSpellsInSection_1 <= 0)
			{
				sprintf(messageOUt, "ERREUR DE LECTURE DE FICHIER 003 !!!!");
				ChatHandler(player->GetSession()).SendSysMessage(messageOUt);
				return false;
			}


		}





		if (KnownByPlayer)
		{
			sprintf(messageOUt, "%s est CONNU par %s", spellProtoypeLearn->SpellName[0], nameToSearch.c_str());
			ChatHandler(player->GetSession()).SendSysMessage(messageOUt);
		}
		else
		{
			sprintf(messageOUt, "%s est INCONNU par %s", spellProtoypeLearn->SpellName[0], nameToSearch.c_str());
			ChatHandler(player->GetSession()).SendSysMessage(messageOUt);
		}




	}




	if (itemProtoype->Flags & 2048)
	{
		sprintf(messageOUt, "objet est en loot commun");
		ChatHandler(player->GetSession()).SendSysMessage(messageOUt);
	}
	else
	{

		bool forceLootCommun = LootItem::Richard_lootCommunPourObjDeQuest(numberID);
		if (forceLootCommun)
		{
			sprintf(messageOUt, "objet sera FORCE en loot commun.");
		}
		else
		{
			sprintf(messageOUt, "objet n'est PAS en loot commun.");
		}
		ChatHandler(player->GetSession()).SendSysMessage(messageOUt);
	}



	struct LOOT_CHANCE
	{
		LOOT_CHANCE(int32 entry_, float chances_)
		{
			entry = entry_;
			chances = chances_;
		}
		int32 entry; // entry  du tableau reference_loot_template
		float chances;
	};


	struct LOOT_CHANCE_REFERENCE
	{
		LOOT_CHANCE_REFERENCE(int32 entry_, float chances_)
		{
			entry = entry_;
			chances = chances_;
			nombreItemInThisReference = 0;
		}
		int32 entry; // entry  du tableau reference_loot_template
		float chances;
		int nombreItemInThisReference;
	};



	std::vector<LOOT_CHANCE_REFERENCE> listChances_fromReference;

	{
		int itemmmCommand = numberID;
		char command1[2048];
		sprintf(command1, "SELECT entry FROM reference_loot_template WHERE item = '%d' ", itemmmCommand);

		if (QueryResult* result1 = WorldDatabase.PQuery(command1))
		{
			BarGoLink bar(result1->GetRowCount());
			do
			{
				bar.step();
				Field* fields = result1->Fetch();

				bool refFound = false;

				{
					int32 entryItem = fields->GetInt32();
					char command2[2048];
					sprintf(command2, "SELECT ChanceOrQuestChance FROM reference_loot_template WHERE item = '%d' AND entry = '%d' ", itemmmCommand, entryItem);




					if (QueryResult* result2 = WorldDatabase.PQuery(command2))
					{

						if (result2->GetRowCount() != 1)
						{
							// ERROR ?????  LA COMMANDE  doit donner pile 1 resultat
							sprintf(messageOUt, "ERROR 303 avec le taux de loot");
							ChatHandler(player->GetSession()).SendSysMessage(messageOUt);
							delete result2;
							delete result1;
							return false;
						}

						BarGoLink bar(result2->GetRowCount());
						do
						{
							bar.step();
							Field* fields = result2->Fetch();

							float chancesItem = fields->GetFloat();

							listChances_fromReference.push_back(LOOT_CHANCE_REFERENCE(entryItem, chancesItem));
							refFound = true;


							int aaaa = 0;

						} while (result2->NextRow());

						delete result2;
					}
					else
					{
						// ERROR ?????
						sprintf(messageOUt, "ERROR 104 avec le taux de loot");
						ChatHandler(player->GetSession()).SendSysMessage(messageOUt);
						delete result1;
						return false;
					}

				}


				int nbRef = 0;
				{
					int32 entryItem = fields->GetInt32();
					char command2[2048];
					sprintf(command2, "SELECT ChanceOrQuestChance FROM reference_loot_template WHERE entry = '%d' ", entryItem);

					if (QueryResult* result2 = WorldDatabase.PQuery(command2))
					{

						BarGoLink bar(result2->GetRowCount());
						do
						{
							bar.step();
							Field* fields = result2->Fetch();

							float chancesItem = fields->GetFloat();

							nbRef++;

							int aaaa = 0;

						} while (result2->NextRow());

						delete result2;
					}
					else
					{
						// ERROR ?????
						sprintf(messageOUt, "ERROR 153 avec le taux de loot");
						ChatHandler(player->GetSession()).SendSysMessage(messageOUt);
						delete result1;
						return false;
					}

				}


				if (refFound)
				{
					listChances_fromReference.back().nombreItemInThisReference = nbRef;
				}
				else
				{
					// ERROR ?????
					sprintf(messageOUt, "ERROR 337 avec le taux de loot");
					ChatHandler(player->GetSession()).SendSysMessage(messageOUt);
					delete result1;
					return false;
				}



				int aaaa = 0;

			} while (result1->NextRow());
			delete result1;
		}
		else
		{
			int aaa = 0;
		}

	}

	std::vector<LOOT_CHANCE> listChances_fromCreature;

	{
		int itemmmCommand = numberID;
		char command1[2048];
		sprintf(command1, "SELECT entry FROM creature_loot_template WHERE item = '%d' ", itemmmCommand);

		if (QueryResult* result1 = WorldDatabase.PQuery(command1))
		{
			BarGoLink bar(result1->GetRowCount());
			do
			{
				bar.step();
				Field* fields = result1->Fetch();

				int32 entryItem = fields->GetInt32();

				char command2[2048];
				sprintf(command2, "SELECT ChanceOrQuestChance FROM creature_loot_template WHERE item = '%d' AND entry = '%d' ", itemmmCommand, entryItem);




				if (QueryResult* result2 = WorldDatabase.PQuery(command2))
				{

					if (result2->GetRowCount() != 1)
					{
						// ERROR ?????
						sprintf(messageOUt, "ERROR 907 avec le taux de loot");
						ChatHandler(player->GetSession()).SendSysMessage(messageOUt);
						delete result2;
						delete result1;
						return false;
					}

					BarGoLink bar(result2->GetRowCount());
					do
					{
						bar.step();
						Field* fields = result2->Fetch();

						float chancesItem = fields->GetFloat();

						listChances_fromCreature.push_back(LOOT_CHANCE(entryItem, chancesItem));

						int aaaa = 0;

					} while (result2->NextRow());

					delete result2;
				}
				else
				{
					// ERROR ?????
					sprintf(messageOUt, "ERROR 104 avec le taux de loot");
					ChatHandler(player->GetSession()).SendSysMessage(messageOUt);
					delete result1;
					return false;
				}






				int aaaa = 0;

			} while (result1->NextRow());
			delete result1;
		}
		else
		{
			int aaa = 0;
		}

	}

	int nombreFoisReferenceUtiliseParCreature = 0;

	for (int iRef = 0; iRef < listChances_fromReference.size(); iRef++)
	{
		int itemmmCommand = numberID;
		char command1[2048];
		sprintf(command1, "SELECT entry FROM creature_loot_template WHERE mincountOrRef = '-%d' ", listChances_fromReference[iRef].entry);

		if (QueryResult* result1 = WorldDatabase.PQuery(command1))
		{
			BarGoLink bar(result1->GetRowCount());
			do
			{
				bar.step();
				Field* fields = result1->Fetch();

				int32 entryItem = fields->GetInt32();

				char command2[2048];
				sprintf(command2, "SELECT ChanceOrQuestChance FROM creature_loot_template WHERE mincountOrRef = '-%d' AND entry = '%d' ", listChances_fromReference[iRef].entry, entryItem);




				if (QueryResult* result2 = WorldDatabase.PQuery(command2))
				{

					if (result2->GetRowCount() != 1)
					{
						// ERROR ?????
						sprintf(messageOUt, "ERROR 343 avec le taux de loot");
						ChatHandler(player->GetSession()).SendSysMessage(messageOUt);
						delete result2;
						delete result1;
						return false;
					}

					BarGoLink bar(result2->GetRowCount());
					do
					{
						bar.step();
						Field* fields = result2->Fetch();

						float chancesItem = fields->GetFloat();

						nombreFoisReferenceUtiliseParCreature++;

						int aaaa = 0;

					} while (result2->NextRow());

					delete result2;
				}
				else
				{
					// ERROR ?????
					sprintf(messageOUt, "ERROR 104 avec le taux de loot");
					ChatHandler(player->GetSession()).SendSysMessage(messageOUt);
					delete result1;
					return false;
				}






				int aaaa = 0;

			} while (result1->NextRow());
			delete result1;
		}
		else
		{
			int aaa = 0;
		}

	}

	//on les range :
	if (listChances_fromCreature.size() > 1)
	{
		for (unsigned int i = 0; i < listChances_fromCreature.size(); i++)
		{
			for (unsigned int j = 0; j < listChances_fromCreature.size(); j++)
			{
				if (i < j)
				{
					if (fabsf(listChances_fromCreature[i].chances) < fabsf(listChances_fromCreature[j].chances))
					{
						LOOT_CHANCE iii = listChances_fromCreature[i];
						listChances_fromCreature[i] = listChances_fromCreature[j];
						listChances_fromCreature[j] = iii;
					}



				}
			}
		}
	}

	//on les enum :
	sprintf(messageOUt, "-----------");
	ChatHandler(player->GetSession()).SendSysMessage(messageOUt);

	if (listChances_fromCreature.size() > 0)
	{
		for (int i = 0; i < 5; i++)
		{
			if (i < listChances_fromCreature.size())
			{

				std::string creatNamStr = "<nom inconnu ?>";

				CreatureInfo const* creatureProto = sCreatureStorage.LookupEntry<CreatureInfo>(listChances_fromCreature[i].entry);
				if (creatureProto)
				{
					creatNamStr = std::string(creatureProto->Name);
				}


				sprintf(messageOUt, "%.0f pourcent  -  %s(%d)", listChances_fromCreature[i].chances, creatNamStr.c_str(), listChances_fromCreature[i].entry);
				ChatHandler(player->GetSession()).SendSysMessage(messageOUt);
			}
		}


		if (!developerInfo && nombreFoisReferenceUtiliseParCreature != 0)
		{
			sprintf(messageOUt, "-----------");
			ChatHandler(player->GetSession()).SendSysMessage(messageOUt);
			sprintf(messageOUt, "se loot aussi a priori sur %d mobs.", nombreFoisReferenceUtiliseParCreature);
			ChatHandler(player->GetSession()).SendSysMessage(messageOUt);
			sprintf(messageOUt, "mais eux je sais pas pourcentage.\n");
			ChatHandler(player->GetSession()).SendSysMessage(messageOUt);
		}
	}
	else
	{
		if (developerInfo)
		{
			sprintf(messageOUt, "Ne se loot PAS sur des mobs.");
			ChatHandler(player->GetSession()).SendSysMessage(messageOUt);
		}
		else
		{
			//message pour diane
			if (nombreFoisReferenceUtiliseParCreature == 0)
			{
				sprintf(messageOUt, "Ne se loot PAS sur des mobs.");
				ChatHandler(player->GetSession()).SendSysMessage(messageOUt);
			}
			else
			{
				sprintf(messageOUt, "se loot a priori sur %d mobs.", nombreFoisReferenceUtiliseParCreature);
				ChatHandler(player->GetSession()).SendSysMessage(messageOUt);
				sprintf(messageOUt, "mais je sais pas trop qui et le pourcentage.\n");
				ChatHandler(player->GetSession()).SendSysMessage(messageOUt);
			}
		}
	}

	if (listChances_fromReference.size() > 0)
	{
		if (developerInfo)
		{
			sprintf(messageOUt, "-----------");
			ChatHandler(player->GetSession()).SendSysMessage(messageOUt);

			sprintf(messageOUt, "Il est reference %d fois dans reference_loot_template.", listChances_fromReference.size());
			ChatHandler(player->GetSession()).SendSysMessage(messageOUt);

			if (listChances_fromReference.size() == 1)
			{
				//ma theorie c'est que la chande de looter l'item est de :
				//<chance de la creature de looter la reference> divisée par <nom d'item dans cette reference>
				sprintf(messageOUt, "cette reference contient %d items.", listChances_fromReference[0].nombreItemInThisReference);
				ChatHandler(player->GetSession()).SendSysMessage(messageOUt);

				sprintf(messageOUt, "cette reference a reference_loot_template.entry = %d", listChances_fromReference[0].entry);
				ChatHandler(player->GetSession()).SendSysMessage(messageOUt);

				sprintf(messageOUt, "cette reference est utilisee par %d creatures", nombreFoisReferenceUtiliseParCreature);
				ChatHandler(player->GetSession()).SendSysMessage(messageOUt);
			}
			else
			{
				sprintf(messageOUt, "ces references sont utilisees par %d creatures", nombreFoisReferenceUtiliseParCreature);
				ChatHandler(player->GetSession()).SendSysMessage(messageOUt);
			}



		}
	}


	int aaaaaa = 0;



	//sprintf(messageOUt,"Item.spellid_1.category=%d",itemProtoype->Spells[0].SpellCategory);
	//ChatHandler(player->GetSession()).SendSysMessage(messageOUt);




	return true;

	*/

}


std::string RichardClass::Richa_itemIdToNiceLink(unsigned long itemID)
{
	std::string itemName = "objet inconnu";
	std::string qualityStr = "9d9d9d";

	//ItemPrototype const* itemProto = sItemStorage.LookupEntry<ItemPrototype>(itemID);
	ItemTemplate const* itemProto = sObjectMgr->GetItemTemplate(itemID);

	if (itemProto)
	{
		itemName = std::string(itemProto->Name1);


		//0xff9d9d9d,		// GREY
		//0xffffffff,		// WHITE
		//0xff1eff00,		// GREEN
		//0xff0070dd,		// BLUE
		//0xffa335ee,		// PURPLE
		//0xffff8000,		// ORANGE
		//0xffe6cc80		 // LIGHT YELLOW


		if (itemProto->Quality == 0)
		{
			qualityStr = "9d9d9d";
		}
		else if (itemProto->Quality == 1)
		{
			qualityStr = "ffffff";
		}
		else if (itemProto->Quality == 2)
		{
			qualityStr = "1eff00";
		}
		else if (itemProto->Quality == 3)
		{
			qualityStr = "0070dd";
		}
		else if (itemProto->Quality == 4)
		{
			qualityStr = "a335ee";
		}
		else if (itemProto->Quality == 5)
		{
			qualityStr = "ff8000";
		}
		else if (itemProto->Quality == 6)
		{
			qualityStr = "e6cc80";
		}
	}
	else
	{
		char itemNameUnkonwn[4096];
		sprintf(itemNameUnkonwn, "objet inconnu id=%d", itemID);
		itemName = std::string(itemNameUnkonwn);
	}


	//std::string out;

	char outStr[4096];
	sprintf(outStr, "|cff%s|Hitem:%d:0:0:0|h[%s]|h|r", qualityStr.c_str(), itemID, itemName.c_str());

	return std::string(outStr);
}










uint32 CreatureModeDataRicha::Richar_GetOriginalEntry()
{
	return  m_thisOwner->m_originalEntry;
}



CreatureModeDataRicha::CreatureModeDataRicha(Creature* thisOwner)
{
	m_thisOwner = thisOwner;

	Richar_difficuly_health = -1.0f;
	Richar_difficuly_degat = -1.0f;


}

CreatureModeDataRicha::~CreatureModeDataRicha()
{

}




// RETURN :
// retourne le coefficient de difficulté par lequel on va multiplier les vies et les points d'attaque Spell/corps a corps   du NPC.
// example :
// retourne 1.0 -> difficulté non modifié
// retoune 0.5 -> difficulté divisiée par 2
// nouveau : j'ai decouplé la difficulté Degat et la difficulté Health.
//		   la fonction retourne la difficulté DEGAT
//		   difficultyHealth  va retourner la difficulté HEATH
//
//
//  donjonLevel
//  correspond a un niveau de Paragon
//  c'est un indice indicatif, permettant d'estimer la difficulté du mob en fonction de sa provenance de donjon.
//  ce nombre est utilisé uniquement pour ajuster le probabilité de drop de youhaicoin .
//  pour eviter qu'un 60 paragon 30  farme des petit level 60 elite de Scholomance, et loot plein de youhaicoin.
//  ce nombre sera donc utilisé uniquement pour les mob lvl 60
//
//  représente grosso modo le niveau de paragon qu'il faut etre pour etre du meme niveau que le mob.
//  essayer d'estimer au mieux.
//  0.0 ou 1.0 correspond a la meme chose  -  puisque   paragon 1 :  + 00 %		   coeff : x 1
//  cependant je vais quand meme mettre une difference :  0.0 correspondra a un mob "d'exterieur"  et 1.0 correspondra a un mob de donjon LowLevel
//
//
//
// out_nbPlayerOriginal [OUT - optional, can be nullptr] 
// retourne le nombre de joueur(s) pour lequel a la base Blizzard avait dimensionné le NPC.
// pour la majorité des mobs d'exterieurs, ca sera 1 ( sauf si vraiment je fais du cas pas cas avec les noms )
// sinon pour les mob d'instance, c'est simplement le nombre de joueur prévu dans l'instance.
//
//
float CreatureModeDataRicha::GetRichardModForMap(const std::string& cPosRicha, const std::string& mobName, const Unit* richaOwner, float* donjonLevel, int* out_nbPlayerOriginal, float* difficultyHealth)
{
	int out_nbPlayerOriginal__ = 1;


	if (out_nbPlayerOriginal)
		*out_nbPlayerOriginal = 1;



	if (donjonLevel)
		*donjonLevel = 0.0f; // par defaut

	if (difficultyHealth)
		*difficultyHealth = 1.0f; // par defaut

	// RICHARD - ajustement des coeff de difficulté on fonction de la position du mob

	//j ai rajouté ca quand je me suis rendu compte que le pet demoniste etait affaiblie dans les donjons
	const Unit* ownerrr = richaOwner; //GetOwner();
	if (ownerrr)
	{
		uint8 ownerid = ownerrr->GetTypeId();
		if (ownerid == TYPEID_PLAYER)
		{
			// du coup, si le owner est un joueur, on va en profiter pour modifer ici la difficulté de son pet en fonction du paragon du joueur :

			Player* ownerCastPlayer = (Player*)ownerrr;

			int paralvl = ownerCastPlayer->m_richa.GetParagonLevelFromItem();

			if (paralvl <= 1)
			{
				return 1.0;
			}
			else
			{
				// #PARAGON_COMPUTE  -  ce hashtag est la pour identifier tous les spot ou le paragon va etre utilise pour modifier les characteristiques

				//ancien calcul :
				//si 2 joueurs sont paragon N, cela veut dire que dans un groupe de 2, ils vont etre equivalent a N+1 joueurs
				//float coeffParagon = ((float)paralvl + 1.0) / 2.0;

				//nouveau calcul
				// paragon 1 :  + 00 %		   coeff : x 1
				// paragon 2 :  + 20 %		   coeff : x 1.2
				// paragon 3 :  + 40 %		   coeff : x 1.4
				// paragon 4 :  + 60 %		   coeff : x 1.6
				// paragon N :  + ( N-1 ) * 20   coeff : x ( 1 + (N-1)*0.2   )
				float coeffParagon = (1.0f + ((float)paralvl - 1.0f) * 0.2f);

				if (donjonLevel)
					*donjonLevel = 0.0; // on s'en fou pour mon pet


				int aaaa = 0;

				return coeffParagon;

			}


		}
		else
		{
			int ggg = 0;
		}
	}
	else
	{
		int gggf = 0;
	}


	//liste d'exception ici - j'ai en tete les mobs gentils dans les donjons qui vont se battre a nos coté.
	//style les quetes d'escorte.
	//d'un coté je me dis que je pourrais prendre tous les mob avec faction gentil.
	//mais de l'autre je pense que c'est BEACOUP plus safe de faire du cas par cas.
	//par exemple imaginons un boss mechant qui est gentil a la creation du donjon
	if (mobName == "Disciple of Naralex") { return 1.0; } // quete d'escorte dans les cavernes des lamentation


	static bool messageSaidDungeaon = false;


	float outNumber = 1.0; // difficulte de DEGAT
	float outDifficulteHeath = 1.0f; // difficulte HEATH
	float donjonLevel_out = 0.0f;

	//pendant longtemps ce coeff etait a 0.40 (2.0/5.0)  pour le donjon low level 5 joueurs
	//mais c'etait trop facile, et apres etude je me suis rendu compte que les vie des mob etait plutot mutliplié par 2 que par 5  (en comparant les non elite de dehors avec les elite du donjon)
	//  voir   StudyNPCstats  dans projet :  Wowhainy_webdatabase
	//donc un peu au pif (mais pas trop) je mets 0.65  .
	//
	// pour donner un petit example, on a joué a Hache Tripe, on difficulté 1.0, puis en difficulté 1.2.
	// on a vraiment senti une grosse difference.
	// donc chaque 0.1 de cette valeur est importante.
	// 
	const float coeffDiffLowlevel_DEGAT = 0.65;
	const float coeffDiffLowlevel_HEALTH = 1.0; // a voir si 1.0 pour la vie, c'est bien ...

	// note : si j'aim généré les map a partir d'un jeu FR  (comme j'ai fait pour WOTLK)  , alors les noms seront en FR


	if (cPosRicha == "Eastern Kingdoms" || cPosRicha == "Royaumes de l'est") { outNumber = 1.0; outDifficulteHeath = 1.0; donjonLevel_out = 0.0f; out_nbPlayerOriginal__ = 1; }
	else if (cPosRicha == "Kalimdor") { outNumber = 1.0; outDifficulteHeath = 1.0; donjonLevel_out = 0.0f; out_nbPlayerOriginal__ = 1; }
	else if (cPosRicha == "Norfendre" || cPosRicha == "Northrend" ) { outNumber = 1.0; outDifficulteHeath = 1.0; donjonLevel_out = 0.0f; out_nbPlayerOriginal__ = 1; }
	else if (cPosRicha == "Outreterre" || cPosRicha == "Outland") { outNumber = 1.0; outDifficulteHeath = 1.0; donjonLevel_out = 0.0f; out_nbPlayerOriginal__ = 1; }
	else if (cPosRicha == "Deeprun Tram") { outNumber = 1.0; outDifficulteHeath = 1.0; donjonLevel_out = 0.0f; out_nbPlayerOriginal__ = 1; }
	else if (cPosRicha == "Alliance PVP Barracks") { outNumber = 1.0; outDifficulteHeath = 1.0; donjonLevel_out = 0.0f; out_nbPlayerOriginal__ = 1; }
	else if (cPosRicha == "Horde PVP Barracks") { outNumber = 1.0; outDifficulteHeath = 1.0; donjonLevel_out = 0.0f; out_nbPlayerOriginal__ = 1; } // j'ai donné le nom au hasard, faudra verifier que c'est bien ca

	//donjons low level :  
	// pour des details concerant l'equilibrage des donjons / choix des coeffs  et nos feeling de joueurs quand on a fait le donjon, voir wowServ\_DOC\____richard_ALL.txt
	else if (cPosRicha == "Ragefire Chasm") { outNumber = coeffDiffLowlevel_DEGAT;  outDifficulteHeath = coeffDiffLowlevel_HEALTH; donjonLevel_out = 1.0f; out_nbPlayerOriginal__ = 5; }
	else if (cPosRicha == "Wailing Caverns") { outNumber = coeffDiffLowlevel_DEGAT;  outDifficulteHeath = coeffDiffLowlevel_HEALTH; donjonLevel_out = 1.0f; out_nbPlayerOriginal__ = 5; } // 17-24   5 joueurs
	else if (cPosRicha == "Deadmines") { outNumber = coeffDiffLowlevel_DEGAT;  outDifficulteHeath = coeffDiffLowlevel_HEALTH; donjonLevel_out = 1.0f; out_nbPlayerOriginal__ = 5; }
	else if (cPosRicha == "Shadowfang Keep") { outNumber = coeffDiffLowlevel_DEGAT;  outDifficulteHeath = coeffDiffLowlevel_HEALTH; donjonLevel_out = 1.0f; out_nbPlayerOriginal__ = 5; }
	else if (cPosRicha == "Blackfathom Deeps") { outNumber = coeffDiffLowlevel_DEGAT;  outDifficulteHeath = coeffDiffLowlevel_HEALTH; donjonLevel_out = 1.0f; out_nbPlayerOriginal__ = 5; }
	else if (cPosRicha == "The Stockade") { outNumber = coeffDiffLowlevel_DEGAT;  outDifficulteHeath = coeffDiffLowlevel_HEALTH; donjonLevel_out = 1.0f; out_nbPlayerOriginal__ = 5; }
	else if (cPosRicha == "Gnomeregan") { outNumber = coeffDiffLowlevel_DEGAT;  outDifficulteHeath = coeffDiffLowlevel_HEALTH; donjonLevel_out = 1.0f; out_nbPlayerOriginal__ = 5; }
	else if (cPosRicha == "Razorfen Kraul") { outNumber = coeffDiffLowlevel_DEGAT;  outDifficulteHeath = coeffDiffLowlevel_HEALTH; donjonLevel_out = 1.0f; out_nbPlayerOriginal__ = 5; }
	else if (cPosRicha == "Scarlet Monastery") { outNumber = coeffDiffLowlevel_DEGAT;  outDifficulteHeath = coeffDiffLowlevel_HEALTH; donjonLevel_out = 1.0f; out_nbPlayerOriginal__ = 5; }
	else if (cPosRicha == "Razorfen Downs") { outNumber = coeffDiffLowlevel_DEGAT;  outDifficulteHeath = coeffDiffLowlevel_HEALTH; donjonLevel_out = 1.0f; out_nbPlayerOriginal__ = 5; }
	else if (cPosRicha == "Uldaman") { outNumber = coeffDiffLowlevel_DEGAT;  outDifficulteHeath = coeffDiffLowlevel_HEALTH; donjonLevel_out = 1.0f; out_nbPlayerOriginal__ = 5; }
	else if (cPosRicha == "Zul'Farrak") { outNumber = coeffDiffLowlevel_DEGAT;  outDifficulteHeath = coeffDiffLowlevel_HEALTH; donjonLevel_out = 1.0f; out_nbPlayerOriginal__ = 5; }
	else if (cPosRicha == "Maraudon") { outNumber = coeffDiffLowlevel_DEGAT;  outDifficulteHeath = coeffDiffLowlevel_HEALTH; donjonLevel_out = 1.0f; out_nbPlayerOriginal__ = 5; }
	else if (cPosRicha == "Sunken Temple") { outNumber = coeffDiffLowlevel_DEGAT;  outDifficulteHeath = coeffDiffLowlevel_HEALTH; donjonLevel_out = 1.0f; out_nbPlayerOriginal__ = 5; }
	else if (cPosRicha == "Blackrock Depths") { outNumber = coeffDiffLowlevel_DEGAT;  outDifficulteHeath = coeffDiffLowlevel_HEALTH; donjonLevel_out = 1.0f; out_nbPlayerOriginal__ = 5; }



	//
	// donjon High Level : on les ramene a une difficulté de 5 joueurs ou plus
	//
	//



	// le cas de  Blackrock Spire  est spécial : 
	// il y a lower et upper.  5 joueur pour lower  10 pour upper  -  

	/*
	else if ( cPosRicha == "Blackrock Spire" )
	{
		bool mobLower = false;
		bool mobUpper = false;

		// Lower Spire -  mob names
		if (
			   mobName == "XXxxxxxxxxX"
			|| mobName == "Scarshield Acolyte"
			|| mobName == "Scarshield Legionnaire"
			|| mobName == "Scarshield Raider"
			|| mobName == "Scarshield Spellbinder"
			|| mobName == "Scarshield Worg"
			|| mobName == "Spire Scarab"
			|| mobName == "Spire Scorpid"
			|| mobName == "Bloodaxe Evoker"
			|| mobName == "Bloodaxe Raider"
			|| mobName == "Bloodaxe Summoner"
			|| mobName == "Bloodaxe Veteran"
			|| mobName == "Bloodaxe Warmonger"
			|| mobName == "Bloodaxe Worg"
			|| mobName == "Firebrand Darkweaver"
			|| mobName == "Firebrand Grunt"
			|| mobName == "Firebrand Invoker"
			|| mobName == "Scarshield Acolyte"
			|| mobName == "Scarshield Legionnaire"
			|| mobName == "Scarshield Raider"
			|| mobName == "Scarshield Spellbinder"
			|| mobName == "Scarshield Warlock"
			|| mobName == "Scarshield Worg"
			|| mobName == "Smolderthorn Axe Thrower"
			|| mobName == "Smolderthorn Mystic"
			|| mobName == "Smolderthorn Shadow Priest"
			|| mobName == "Spirestone Battle Mage"
			|| mobName == "Spirestone Enforcer"
			|| mobName == "Spirestone Ogre Magus"
			|| mobName == "Spirestone Reaver"
			|| mobName == "Spirestone Warlord"
			|| mobName == "Urok Enforcer"
			|| mobName == "Urok Ogre Mage"
			|| mobName == "Spire Scarab"
			|| mobName == "Spire Scorpid"
			|| mobName == "Spirestone Enforcer"
			|| mobName == "Spirestone Mystic"
			|| mobName == "Spirestone Ogre Magus"
			|| mobName == "Spirestone Reaver"
			|| mobName == "Smolderthorn Axe Thrower"
			|| mobName == "Smolderthorn Berserker"
			|| mobName == "Smolderthorn Headhunter"
			|| mobName == "Smolderthorn Mystic"
			|| mobName == "Smolderthorn Seer"
			|| mobName == "Smolderthorn Shadow Hunter"
			|| mobName == "Smolderthorn Shadow Priest"
			|| mobName == "Smolderthorn Witch Doctor"
			|| mobName == "Spire Spider"
			|| mobName == "Spire Spiderling"
			|| mobName == "Bloodaxe Evoker"
			|| mobName == "Bloodaxe Warmonger"
			|| mobName == "Bloodaxe Worg Pup"
			|| mobName == "Bloodaxe Evoker"
			|| mobName == "Bloodaxe Raider"
			|| mobName == "Bloodaxe Veteran"
			|| mobName == "Bloodaxe Worg"
			|| mobName == "Smolderthorn Berserker"
			|| mobName == "Smolderthorn Shadow Priest"
			|| mobName == "Spirestone Warlord"

			|| mobName == "Bannok Grimaxe"
			|| mobName == "Burning Felguard"
			|| mobName == "Ghok Bashguud"
			|| mobName == "Spirestone Butcher"
			|| mobName == "Urok Doomhowl"
			|| mobName == "Highlord Omokk"
			|| mobName == "Spirestone Battle Lord"
			|| mobName == "Spirestone Lord Magus"
			|| mobName == "Mor Grayhoof"
			|| mobName == "Shadow Hunter Vosh'gajin"
			|| mobName == "War Master Voone"
			|| mobName == "Crystal Fang"
			|| mobName == "Mother Smolderweb"
			|| mobName == "Quartermaster Zigris"
			|| mobName == "Gizrul the Slavener"
			|| mobName == "Halycon"
			|| mobName == "Overlord Wyrmthalak"

			|| mobName == "Firebrand Legionnaire"
			|| mobName == "Firebrand Dreadweaver"
			|| mobName == "Firebrand Pyromancer"


			//les mini mob
			|| mobName == "Roach"
			|| mobName == "Black Rat"

			//les gentils
			|| mobName == "Warosh"

			//les unkonwn que je mets a la difficulte la plus dure
			|| mobName == "Mor Grayhoof Trigger"
			)
		{
			mobLower = true;
		}

		// UPPER Spire - mob names list
		if (
			   mobName == "xxxxxxxxxxxxxxxxxxxxxxxxxxxXXX"
			|| mobName == "Blackhand Dreadweaver"
			|| mobName == "Blackhand Summoner"
			|| mobName == "Blackhand Veteran"
			|| mobName == "Rage Talon Dragonspawn"
			|| mobName == "Blackhand Incarcerator"
			|| mobName == "Rage Talon Dragonspawn"
			|| mobName == "Rage Talon Flamescale"
			|| mobName == "Rookery Guardian"
			|| mobName == "Rookery Hatcher"
			|| mobName == "Rookery Whelp"
			|| mobName == "Blackhand Dreadweaver"
			|| mobName == "Blackhand Elite"
			|| mobName == "Blackhand Summoner"
			|| mobName == "Blackhand Veteran"
			|| mobName == "Rage Talon Dragonspawn"
			|| mobName == "Rage Talon Flamescale"
			|| mobName == "Blackhand Assassin"
			|| mobName == "Blackhand Dragon Handler"
			|| mobName == "Blackhand Dreadweaver"
			|| mobName == "Blackhand Elite"
			|| mobName == "Blackhand Iron Guard"
			|| mobName == "Blackhand Summoner"
			|| mobName == "Blackhand Veteran"
			|| mobName == "Chromatic Dragonspawn"
			|| mobName == "Chromatic Whelp"
			|| mobName == "Rage Talon Dragon Guard"
			|| mobName == "Rage Talon Dragonspawn"
			|| mobName == "Rage Talon Fire Tongue"
			|| mobName == "Rage Talon Flamescale"
			|| mobName == "Blackhand Assassin"
			|| mobName == "Blackhand Elite"
			|| mobName == "Blackhand Iron Guard"
			|| mobName == "Rage Talon Dragon Guard"
			|| mobName == "Rage Talon Fire Tongue"
			|| mobName == "Blackhand Assassin"
			|| mobName == "Blackhand Elite"
			|| mobName == "Blackhand Iron Guard"
			|| mobName == "Blackhand Thug"
			|| mobName == "Rage Talon Dragon Guard"
			|| mobName == "Blackhand Assassin"
			|| mobName == "Blackhand Elite"
			|| mobName == "Blackhand Iron Guard"
			|| mobName == "Chromatic Elite Guard"
			|| mobName == "Rage Talon Captain"
			|| mobName == "Rage Talon Fire Tongue"

			|| mobName == "Pyroguard Emberseer"
			|| mobName == "Solakar Flamewreath"
			|| mobName == "Goraluk Anvilcrack"
			|| mobName == "Jed Runewatcher"
			|| mobName == "Warchief Rend Blackhand"
			|| mobName == "General Drakkisath"

			|| mobName == "Scarshield Infiltrator"


			|| mobName == "Awbee"


			)
		{
			mobUpper = true;
		}

		if ( mobLower && mobUpper )
		{
			sLog->outBasic("RICHAR: --------------- WARNING ------------- unknown BlackrockSpire Mob - UP ET DOWN: '%s'" ,  mobName.c_str()  );

			//dans le doute on va dire qu'il sont lower
			mobUpper = false; mobLower = true;
		}

		if ( !mobLower && !mobUpper )
		{
			sLog->outBasic("RICHAR: --------------- WARNING ------------- unknown BlackrockSpire Mob - NI UP NI DOWN: '%s'" ,  mobName.c_str()  );

			//dans le doute on va dire qu'il sont lower
			mobUpper = false; mobLower = true;
		}

		if ( mobLower )
		{
			out_nbPlayerOriginal__=5;
			outNumber =  1.1f;
			outDifficulteHeath = 1.1f;
			donjonLevel_out = 999.0f;
		}
		else
		{
			out_nbPlayerOriginal__=10;
			outNumber =  2.0f;
			outDifficulteHeath = 2.0f;
			donjonLevel_out = 999.0f;
		}

	}
	*/


	else if (cPosRicha == "Blackrock Spire")
	{
		/*

		// TODO : dés qu'avec Diane on aura termine le donjon, je pourrai terminer le code proprement

		bool mobLower = false;
		if ( mobName.size() > 2 && mobName[0] == '-' && mobName[1] == ' ' )
		{
			mobLower = true;
		}
		else if ( mobName.size() > 2 &&  mobName[0] == '+' && mobName[1] == ' ' )
		{
			mobLower = false;
		}
		else
		{
			sLog->outBasic("RICHAR: --------------- WARNING ------------- unknown BlackrockSpire Mob - NI UP NI DOWN: '%s'" ,  mobName.c_str()  );
			//dans le doute on va dire qu'il sont lower
			mobLower = true;
		}
		*/

		/*
		// bouillot paragon 28 - boulette paragon 24
		// on a trouve que c'etait tres bien avec cette difficulete pour LOWER
		// pour l'instant on va deja considere qu'on est que dans blackrock inferieur
		out_nbPlayerOriginal__=5;
		outNumber =  1.96f;
		outDifficulteHeath = 4.20f;
		donjonLevel_out = 28.0f; // paragon 28
		*/

		// on essaye ca pour UPPER :
		out_nbPlayerOriginal__ = 10;
		outNumber = 1.96f;
		outDifficulteHeath = 4.20f;
		donjonLevel_out = 28.0f; // paragon 28


	}



	// pour des details concerant l'equilibrage des donjons / choix des coeffs  et nos feeling de joueurs quand on a fait le donjon, voir wowServ\_DOC\____richard_ALL.txt
	//
	// concernant 'outNumber' je rappelle que chaque 0.1 de cette valeur compte : un Hache Tripes a 1.0 sera bcp plus facile qu'un Hache Tripes 1.2
	//
	// pour le  'donjonLevel_out'  , je conseille de jouer un premier rdv de tester, et voir si le donjon est difficile ou pas
	// puis pour le 2ieme rdv, mettre le 'donjonLevel_out' que je pense etre bon.
	//
	else if (cPosRicha == "Dire Maul") { outNumber = 1.0f;	outDifficulteHeath = 1.000f;   donjonLevel_out = 11.0f; out_nbPlayerOriginal__ = 5; } // apres tests : on confirme que pour difficulté=1.0 - pour 2 joueurs - ce donjon est fait pour paragon 11  
	else if (cPosRicha == "Stratholme") { outNumber = 1.100f;  outDifficulteHeath = 1.100f;   donjonLevel_out = 13.0f; out_nbPlayerOriginal__ = 5; }

	else if (cPosRicha == "Scholomance")
	{
		if (mobName == "Etudiant de la Scholomance") // petite exception pour les  npc=10475  on trouvais ca vraiment ennuyeux de les tuer 1 a 1 - ca met 1000 ans, et c'est sans interet.  par contre en contre partie il ne vont pas looter de youhaicoin
		{
			outNumber = 1.400f;   outDifficulteHeath = 0.500f;  donjonLevel_out = 20.0f; out_nbPlayerOriginal__ = 5;
		}
		else
		{
			outNumber = 1.400f;   outDifficulteHeath = 3.000f;  donjonLevel_out = 20.0f; out_nbPlayerOriginal__ = 5;
		}
	}

	//else if ( cPosRicha == "Blackrock Spire" )	{ outNumber =  1.0f;	outDifficulteHeath = 1.0f;	 donjonLevel_out = 999.0f;  } // je le mets a la limite de difficulté entre 5 et 10 joueurs.  comme ca c'est easy pour moi
	else if (cPosRicha == "Zul'Gurub") { outNumber = 1.0f;	outDifficulteHeath = 1.0f;	 donjonLevel_out = 999.0f; out_nbPlayerOriginal__ = 20; }
	else if (cPosRicha == "Molten Core") { outNumber = 0.5f;   outDifficulteHeath = 0.5f;	  donjonLevel_out = 999.0f; out_nbPlayerOriginal__ = 40; }
	else if (cPosRicha == "Onyxias Lair") { outNumber = 0.625f;  outDifficulteHeath = 0.625f;	 donjonLevel_out = 999.0f; out_nbPlayerOriginal__ = 40; }
	else if (cPosRicha == "Blackwing Lair") { outNumber = 0.75f;   outDifficulteHeath = 0.75f;	 donjonLevel_out = 999.0f; out_nbPlayerOriginal__ = 40; }
	else if (cPosRicha == "Ruins of Ahnqiraj") { outNumber = 1.25f;  outDifficulteHeath = 1.25f;	  donjonLevel_out = 999.0f; out_nbPlayerOriginal__ = 20; }	// AQ20
	else if (cPosRicha == "Temple of Ahnqiraj") { outNumber = 0.875f;  outDifficulteHeath = 0.875f;	 donjonLevel_out = 999.0f; out_nbPlayerOriginal__ = 40; }	// AQ40
	else if (cPosRicha == "Naxxramas") { outNumber = 1.0f;   outDifficulteHeath = 1.0f;	  donjonLevel_out = 999.0f; out_nbPlayerOriginal__ = 40; }



	else if (cPosRicha == "??POSRICH??")
	{
		// diane a deja eu ce warning pdt qu'elle survollait en griphon entre Darnassus  et Theramor
		// a l'epoque j'avais pas le nom du mob, donc a refaire le vol
		// j'ai pas eussi a revoir le message en faisant le vol
		// peut etre que Diane a survolé un bateau ? ca fait ptete ca quand on rentre dans bateau.
		// je sais pas... ca doit pas etre bien grave mais a surveiller, ca sertai cool de le repro
		// 
		// c'est fort probable que ce soit un totem, car j'avais pas rajouté la position pour le totem
		// example de mob a aller voir :   "Foulweald Warrior"   qui invoque un   "Strength of Earth Totem II"

		sLog->outBasic("RICHAR: --------------- WARNING ------------- unknown region A - mob=%s : '%s'", mobName.c_str(), cPosRicha.c_str());
		outNumber = 1.0;
		outDifficulteHeath = 1.0f;
	}
	else if (cPosRicha == "")
	{
		sLog->outBasic("RICHAR: --------------- WARNING ------------- unknown region B - mob=%s : '%s'", mobName.c_str(), cPosRicha.c_str());
		outNumber = 1.0;
		outDifficulteHeath = 1.0f;
	}
	else
	{
		static bool messageDisplayed = false;



		sLog->outBasic("RICHAR: --------------- WARNING ------------- unknown region C - mob=%s : '%s'", mobName.c_str(), cPosRicha.c_str());


		if (!messageDisplayed)
		{
			MessageBoxA(NULL, cPosRicha.c_str(), "unkownZone", NULL);
			messageDisplayed = true;
		}



		outNumber = 1.0;
		outDifficulteHeath = 1.0f;
	}




	if (cPosRicha != "Eastern Kingdoms"
		&&  cPosRicha != "Kalimdor"
		&&  cPosRicha != "Royaumes de l'est" // WOTLK server a les regions en FR
		&&  cPosRicha != "Norfendre"
		&&  cPosRicha != "Outreterre"
		&&  cPosRicha != "Northrend"
		&&  cPosRicha != "Outland"
		&& !messageSaidDungeaon)
	{
		messageSaidDungeaon = true;
		sLog->outBasic("RICHAR: INSTANCE DETECTE : %s", cPosRicha.c_str());
	}

	if (donjonLevel)
		*donjonLevel = donjonLevel_out;

	if (out_nbPlayerOriginal)
		*out_nbPlayerOriginal = out_nbPlayerOriginal__;

	if (difficultyHealth)
		*difficultyHealth = outDifficulteHeath;


	return  outNumber;
}


float CreatureModeDataRicha::GetRichardModForMap2(Creature* creatureeee, float* donjonLevel, int* nbPlayerOriginal, float* difficultyHealth)
{
   return GetRichardModForMap(
		creatureeee->m_richar_lieuOrigin, creatureeee->GetName(), creatureeee->GetOwner(),
		donjonLevel, nbPlayerOriginal, difficultyHealth
	);
}



/*
int32 PlayerModeDataRicha::GetAreaFlagByAreaID_richa(uint32 area_id)
{
	AreaFlagByAreaID::iterator i = sAreaFlagByAreaID.find(area_id);
	if (i == sAreaFlagByAreaID.end())
		return -1;

	return i->second;
}
*/

void PlayerModeDataRicha::Richard_GetListExplored(std::map<std::string, std::vector<MAP_SECONDA>  >& mapsList, int&  nbAreaExplored, int&  nbAreaTotal)
{

	int loc = m_thisOwner->GetSession()->GetSessionDbcLocale();


	AreaTableEntry const* aEntry = nullptr;
	for (uint32 i = 0; i <= sAreaTableStore.GetNumRows(); i++)
	{
		if (AreaTableEntry const* AreaEntry = sAreaTableStore.LookupEntry(i))
		{
			AreaEntry->exploreFlag;
			AreaEntry->area_name[loc];
			AreaEntry->ID;
			AreaEntry->zone; // parent area ID


			std::string parentName = "?? parent name inconnu ??";

			AreaTableEntry const* AreaEntryParent = sAreaTableStore.LookupEntry(AreaEntry->zone);
			if (AreaEntryParent)
			{
				parentName = std::string(AreaEntryParent->area_name[loc]);
			}
			else
			{
				if (AreaEntry->zone == 0)
				{
					parentName = "AAA__ROOT_0"; // si la zone parent est l'indice 0 -> pas de parent
				}
				int aaaa = 0;
			}

			AreaTableEntry const* areaEntry = sAreaTableStore.LookupEntry(AreaEntry->ID);

			//int areaFlag_ = GetAreaFlagByAreaID_richa(AreaEntry->ID);

			//if (areaFlag_ == -1)
			//{
			//	int aaa = 0;
			//	continue; // ERRORR
			//}

			//int offset = areaFlag_ / 32;

			//uint32 val = (uint32)(1 << (areaFlag_ % 32));
			uint32 val = (uint32)(1 << (areaEntry->exploreFlag % 32));

			uint32 offset = areaEntry->exploreFlag / 32;


			if (strcmp((char*)AreaEntry->area_name[loc], "Southfury River") == 0)
			{
				int aaa = 0;
			}

			if (offset < PLAYER_EXPLORED_ZONES_SIZE && offset >= 0)
			{
				const uint32 explorred = m_thisOwner->GetUInt32Value(PLAYER_EXPLORED_ZONES_1 + offset);


				//liste des exclus :
				if (strcmp(AreaEntry->area_name[loc], "City") == 0
					|| strcmp(AreaEntry->area_name[loc], "***On Map Dungeon***") == 0

					|| strcmp(AreaEntry->area_name[loc], "UNUSED Stratholme") == 0
					|| strcmp(AreaEntry->area_name[loc], "UNUSEDShadowfang Keep 003") == 0
					|| strcmp(AreaEntry->area_name[loc], "Unused The Deadmines 002") == 0
					|| strcmp(AreaEntry->area_name[loc], "UNUSEDAlcaz Island") == 0
					|| strcmp(AreaEntry->area_name[loc], "DELETE ME") == 0
					|| strcmp(AreaEntry->area_name[loc], "Darrowmere Lake UNUSED") == 0
					|| strcmp(AreaEntry->area_name[loc], "South Seas UNUSED") == 0
					|| strcmp(AreaEntry->area_name[loc], "UNUSED Stonewrought Pass") == 0
					|| strcmp(AreaEntry->area_name[loc], "Unused Ironcladcove") == 0
					|| strcmp(AreaEntry->area_name[loc], "***On Map Dungeon***") == 0
					|| strcmp(AreaEntry->area_name[loc], "Programmer Isle") == 0
					|| strcmp(AreaEntry->area_name[loc], "Caer Darrow UNUSED") == 0
					|| strcmp(AreaEntry->area_name[loc], "The Maul UNUSED") == 0
					|| strcmp(AreaEntry->area_name[loc], "Unused Ironclad Cove 003") == 0
					|| strcmp(AreaEntry->area_name[loc], "GM Island") == 0
					|| strcmp(AreaEntry->area_name[loc], "Designer Island") == 0
					|| strcmp(AreaEntry->area_name[loc], "Island of Doctor Lapidis") == 0

					//List des zone : on retire quand le nom du sub-area correspond au nom d'une zone entiere
					|| strcmp(AreaEntry->area_name[loc], "Alterac Mountains") == 0
					|| strcmp(AreaEntry->area_name[loc], "Alterac Valley") == 0
					|| strcmp(AreaEntry->area_name[loc], "Arathi Basin") == 0
					|| strcmp(AreaEntry->area_name[loc], "Arathi Highlands") == 0
					|| strcmp(AreaEntry->area_name[loc], "Ashenvale") == 0
					|| strcmp(AreaEntry->area_name[loc], "Azshara") == 0
					|| strcmp(AreaEntry->area_name[loc], "Badlands") == 0
					|| strcmp(AreaEntry->area_name[loc], "Blasted Lands") == 0
					|| strcmp(AreaEntry->area_name[loc], "Burning Steppes") == 0
					|| strcmp(AreaEntry->area_name[loc], "Darkshore") == 0
					|| strcmp(AreaEntry->area_name[loc], "Darnassus") == 0
					|| strcmp(AreaEntry->area_name[loc], "Deadwind Pass") == 0
					|| strcmp(AreaEntry->area_name[loc], "Desolace") == 0
					|| strcmp(AreaEntry->area_name[loc], "Dun Morogh") == 0
					|| strcmp(AreaEntry->area_name[loc], "Durotar") == 0
					|| strcmp(AreaEntry->area_name[loc], "Duskwood") == 0
					|| strcmp(AreaEntry->area_name[loc], "Dustwallow Marsh") == 0
					|| strcmp(AreaEntry->area_name[loc], "Eastern Plaguelands") == 0
					|| strcmp(AreaEntry->area_name[loc], "Elwynn Forest") == 0
					|| strcmp(AreaEntry->area_name[loc], "Felwood") == 0
					|| strcmp(AreaEntry->area_name[loc], "Feralas") == 0
					|| strcmp(AreaEntry->area_name[loc], "Hillsbrad Foothills") == 0
					|| strcmp(AreaEntry->area_name[loc], "Loch Modan") == 0
					|| strcmp(AreaEntry->area_name[loc], "Moonglade") == 0
					|| strcmp(AreaEntry->area_name[loc], "Mulgore") == 0
					|| strcmp(AreaEntry->area_name[loc], "Old Hillsbrad Foothills") == 0
					|| strcmp(AreaEntry->area_name[loc], "Redridge Mountains") == 0
					|| strcmp(AreaEntry->area_name[loc], "Ruins of Ahn'Qiraj") == 0
					|| strcmp(AreaEntry->area_name[loc], "Searing Gorge") == 0
					|| strcmp(AreaEntry->area_name[loc], "Silithus") == 0
					|| strcmp(AreaEntry->area_name[loc], "Silverpine Forest") == 0
					|| strcmp(AreaEntry->area_name[loc], "Stonetalon Mountains") == 0
					|| strcmp(AreaEntry->area_name[loc], "Stranglethorn Vale") == 0
					|| strcmp(AreaEntry->area_name[loc], "Swamp of Sorrows") == 0
					|| strcmp(AreaEntry->area_name[loc], "Tanaris") == 0
					|| strcmp(AreaEntry->area_name[loc], "Teldrassil") == 0
					|| strcmp(AreaEntry->area_name[loc], "The Barrens") == 0
					|| strcmp(AreaEntry->area_name[loc], "The Hinterlands") == 0
					|| strcmp(AreaEntry->area_name[loc], "Thousand Needles") == 0
					|| strcmp(AreaEntry->area_name[loc], "Thunder Bluff") == 0
					|| strcmp(AreaEntry->area_name[loc], "Tirisfal Glades") == 0
					|| strcmp(AreaEntry->area_name[loc], "Un'Goro Crater") == 0
					|| strcmp(AreaEntry->area_name[loc], "Warsong Gulch") == 0
					|| strcmp(AreaEntry->area_name[loc], "Western Plaguelands") == 0
					|| strcmp(AreaEntry->area_name[loc], "Westfall") == 0
					|| strcmp(AreaEntry->area_name[loc], "Wetlands") == 0
					|| strcmp(AreaEntry->area_name[loc], "Winterspring") == 0
					|| strcmp(AreaEntry->area_name[loc], "Zul'Gurub") == 0


					//on retire les  zone entirere qui nous interresse pas dans les stats
					|| parentName == "Programmer Isle"


					// || strcmp(AreaEntry->area_name[loc], "XXXXXX") == 0 
					)
				{
					int eeee = 0;
				}
				else
				{

					if (explorred & val)
					{
						nbAreaExplored++;
					}

					mapsList[parentName].push_back(MAP_SECONDA(AreaEntry->area_name[loc], explorred & val, areaEntry->exploreFlag));

					nbAreaTotal++;
				}



			}
			else
			{
				int aa = 0;  // ERRORR
			}

			int aaa = 0;
		}
	}

}


void PlayerModeDataRicha::richard_importVariables_END(uint64 guid__)
{

	/*
	int lvl = getLevel();
	if ( lvl == 60  )
	{
		if ( m_richar_paragon >= 1 )
		{
			int aaaa=0;
		}
		else
		{
			//si ca arrive, c'est surement parce que
			//le joueur n'est pas dans la liste des joueur niveau 60
			//dans  Player::richard_importVariables_START
			//il faut donc updater la liste
			//
			//Enfin si je suis la, qqchose ne va pas, il faut enqueter
			sLog->outBasic("RICHAR: WARNING 53610 IMPORTANT !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
			//
			m_richar_paragon = 0;
		}
	}
	else
	{
		if ( m_richar_paragon != 0 )
		{
			//ERREUR ???
			int aaa=0;
		}
		m_richar_paragon = 0;
	}
	m_richar_paragonProgressFromFile = 0;
	*/
}


void PlayerModeDataRicha::richa_exportTo_richaracter_(
	uint64 guid,
	const std::vector<RICHA_NPC_KILLED_STAT>& richa_NpcKilled,
	const std::vector<RICHA_PAGE_DISCO_STAT>& richa_pageDiscovered,
	const std::vector<RICHA_LUNARFESTIVAL_ELDERFOUND>& richa_lunerFestivalElderFound,
	const std::vector<RICHA_MAISON_TAVERN>& richa_ListeMaison,
	const std::vector<RICHA_ITEM_LOOT_QUEST>& richa_ListItemQuestLoot,
	const char* characterName
)
{
	const int richa_language = 2;  // 0 pour US  -  2 pour FR  - langue de client utilisé pour extraire les bases de données

	char outt[4096];

	time_t t = time(0);   // get time now
	struct tm * now = localtime(&t);

	//// sauvegarde des custom variables - pour les CHARACTER (bouillot, boulette, Inge, Herbo ...etc...)

	//ObjectGuid const& guiiddd = GetObjectGuid();
	//uint32 entryy = guiiddd.GetEntry();
	//uint64 guid = guiiddd.GetRawValue();

	char nameFile2[2048];
	sprintf(nameFile2, "RICHARDS_WOTLK/_ri_character_%d.txt", guid);
	FILE* fcustom = fopen(nameFile2, "wb"); // w : create an empty file - if file already exist content are discarded , and treated as new empty file


	if (!fcustom)
	{

		sLog->outBasic("WARNING IMPORTANT  45RT6 :  arrive pas a ouvrir un fichier pour exporter les data - pause de 60 secondes !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! ");

		// je prefere bloquer le serveur plutot que charger n'importe quoi ou prendre le risque d'effacer des data
		for (int i = 0; i < 60; i++)
		{
			Sleep(1000);
			int aaaa = 0;
		}

		int aaa = 0;

		return;
	}


	sprintf(outt, "// generated on %02d/%02d/%d \r\n", now->tm_mday, now->tm_mon + 1, now->tm_year + 1900);
	fwrite(outt, 1, strlen(outt), fcustom);

	sprintf(outt, "// but de ce fichier : sauvegarder des donnees en plus (qui ne sont pas sauvegardee par la vraie database) propres aux PERSONNAGES.\r\n");
	fwrite(outt, 1, strlen(outt), fcustom);

	sprintf(outt, "CHARACTER_STAT\r\n"); // juste un code pour savoir si tout est ok
	fwrite(outt, 1, strlen(outt), fcustom);

	sprintf(outt, "VERSION_254\r\n"); // la version
	fwrite(outt, 1, strlen(outt), fcustom);

	sprintf(outt, "%s\r\n", characterName);//GetName()); // name
	fwrite(outt, 1, strlen(outt), fcustom);

	//sprintf(outt, "%d\r\n",m_richar_paragon);  // <--- TODO : retirer lui car il est save dans  _ri_human_%s
	//fwrite(outt, 1, strlen(outt), fcustom);	//

	sprintf(outt, "\r\n/////////////////////////////////////////////////////////////////\r\n");
	fwrite(outt, 1, strlen(outt), fcustom);

	sprintf(outt, "#LIST_NPC_KILLED\r\n");
	fwrite(outt, 1, strlen(outt), fcustom);

	sprintf(outt, "%d\r\n", richa_NpcKilled.size());
	fwrite(outt, 1, strlen(outt), fcustom);

	for (int i = 0; i < richa_NpcKilled.size(); i++)
	{
		sprintf(outt, "%d,%d\r\n", richa_NpcKilled[i].npc_id, richa_NpcKilled[i].nb_killed);
		fwrite(outt, 1, strlen(outt), fcustom);
	}


	sprintf(outt, "\r\n/////////////////////////////////////////////////////////////////\r\n");
	fwrite(outt, 1, strlen(outt), fcustom);

	sprintf(outt, "#LIST_PAGE_DISCOVERED\r\n");
	fwrite(outt, 1, strlen(outt), fcustom);

	sprintf(outt, "%d\r\n", richa_pageDiscovered.size());
	fwrite(outt, 1, strlen(outt), fcustom);

	for (int i = 0; i < richa_pageDiscovered.size(); i++)
	{
		sprintf(outt, "%d,%d,%d,%d\r\n", richa_pageDiscovered[i].pageId, richa_pageDiscovered[i].objectID, richa_pageDiscovered[i].itemID, 0);
		fwrite(outt, 1, strlen(outt), fcustom);
	}

	sprintf(outt, "\r\n/////////////////////////////////////////////////////////////////\r\n");
	fwrite(outt, 1, strlen(outt), fcustom);

	sprintf(outt, "#LIST_LUNARFESTIVAL_ELDERFOUND\r\n");
	fwrite(outt, 1, strlen(outt), fcustom);
	for (int i = 0; i < richa_lunerFestivalElderFound.size(); i++)
	{
		sprintf(outt, "%d,%d\r\n", richa_lunerFestivalElderFound[i].year, richa_lunerFestivalElderFound[i].questId);
		fwrite(outt, 1, strlen(outt), fcustom);
	}



	sprintf(outt, "\r\n/////////////////////////////////////////////////////////////////\r\n");
	fwrite(outt, 1, strlen(outt), fcustom);

	sprintf(outt, "#LIST_MAISON_TAVERN\r\n");
	fwrite(outt, 1, strlen(outt), fcustom);
	for (int i = 0; i < richa_ListeMaison.size(); i++)
	{
		//AreaTableEntry const* zoneEntry = GetAreaEntryByAreaID(zone_id);
		//AreaTableEntry const* areaEntry = GetAreaEntryByAreaID(richa_ListeMaison[i].areaid);
		AreaTableEntry const* areaEntry = sAreaTableStore.LookupEntry(richa_ListeMaison[i].areaid);

		sprintf(outt, "%d,%d,%s\r\n", richa_ListeMaison[i].mapid, richa_ListeMaison[i].areaid, areaEntry ? areaEntry->area_name[richa_language] : "unknown");
		fwrite(outt, 1, strlen(outt), fcustom);
	}




	sprintf(outt, "\r\n/////////////////////////////////////////////////////////////////\r\n");
	fwrite(outt, 1, strlen(outt), fcustom);

	sprintf(outt, "#LIST_ITEM_LOOT_QUEST\r\n");
	fwrite(outt, 1, strlen(outt), fcustom);
	for (int i = 0; i < richa_ListItemQuestLoot.size(); i++)
	{
		sprintf(outt, "%d,%d,%f,%d,%d\r\n",
			richa_ListItemQuestLoot[i].active,
			richa_ListItemQuestLoot[i].itemid,
			richa_ListItemQuestLoot[i].currentScore,
			richa_ListItemQuestLoot[i].nbFoisQueteDone,
			richa_ListItemQuestLoot[i].LoopQuest
		);
		fwrite(outt, 1, strlen(outt), fcustom);
	}



	sprintf(outt, "\r\n/////////////////////////////////////////////////////////////////\r\n");
	fwrite(outt, 1, strlen(outt), fcustom);

	sprintf(outt, "#FIN_DOCUMENT\r\n");
	fwrite(outt, 1, strlen(outt), fcustom);

	//sprintf(outt, "3146\r\n"); // juste un code pour savoir si tout est ok
	//fwrite(outt, 1, strlen(outt), fcustom);
	fclose(fcustom); fcustom = 0;


}



void PlayerModeDataRicha::richa_importFrom_richaracter_(uint64 guid__,
	std::vector<RICHA_NPC_KILLED_STAT>& richa_NpcKilled,
	std::vector<RICHA_PAGE_DISCO_STAT>& richa_pageDiscovered,
	std::vector<RICHA_LUNARFESTIVAL_ELDERFOUND>& richa_lunerFestivalElderFound,
	std::vector<RICHA_MAISON_TAVERN>& richa_ListeMaison,
	std::vector<RICHA_ITEM_LOOT_QUEST>& richa_ListItemQuestLoot,
	std::string& namePerso
)
{

	char nameFile2[2048];
	//const char* playerName = GetName();
	sprintf(nameFile2, "RICHARDS_WOTLK/_ri_character_%d.txt", guid__);

	std::ifstream infile(nameFile2);




	if (!infile.is_open() || infile.fail())
	{
		// si on arrive la c'est certainement car un nouveau perso a été créé.
		//  NON EN FAIT car  richa_exportTo_richaracter_  est appelé au moment de creation du perso
		// donc il n'y a aucune raison de ne pas pouvroi ouvrir ce fichier
		// et donc c'est une errur tres grave 

		char NPath[1024];
		GetCurrentDirectoryA(1024, NPath);

		sLog->outBasic("RICHAR WARNING GRAVE 85XC2 : Can't find save file for guid = %d : !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!", (int32_t)guid__);
		sLog->outBasic("						   : working dir = %s", NPath);


		// je prefere bloquer le serveur plutot que charger n'importe quoi ou prendre le risque d'effacer des data
		for (int i = 0; ; i++)
		{
			Sleep(1000);
			int aaaa = 0;
		}


		//on RESET toutes la variables importées par ce TXT :
		richa_NpcKilled.clear();
		richa_pageDiscovered.clear();
		richa_lunerFestivalElderFound.clear();
		richa_ListeMaison.clear();
		richa_ListItemQuestLoot.clear();
		namePerso = "";

		return;
	}




	int nbOk = 0;
	bool error = false;
	int errorCode = 0;


	if (richa_NpcKilled.size() != 0)
	{
		sLog->outBasic("RICHAR WARNING !!!!!!!!!!!!!!!!!!! - LIST3265 !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
	}
	if (richa_pageDiscovered.size() != 0)
	{
		sLog->outBasic("RICHAR WARNING !!!!!!!!!!!!!!!!!!! - LIST3266 !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
	}
	if (richa_lunerFestivalElderFound.size() != 0)
	{
		sLog->outBasic("RICHAR WARNING !!!!!!!!!!!!!!!!!!! - LIST3267 !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
	}

	richa_NpcKilled.clear();
	richa_pageDiscovered.clear();
	richa_lunerFestivalElderFound.clear();

	std::string line;
	int lineCount = 0; // ne compte PAS les ligne ignorées par le lecteur (ligne vides, commentaires....)
	int nbNpcKilled = 0;
	int nbPageDiscoverd = 0;
	std::string currentSectionName = ""; // string vide si on est pas dans une section
	int currentSectionLine = 0; //  line 0 = 1ere ligne de la section, sans compter la ligne de titre de la section
	while (std::getline(infile, line))
	{
		//std::istringstream iss(line);
		//int a, b;
		//if (!(iss >> a >> b)) { break; } // error

		// process pair (a,b)

		if (line == "#FIN_DOCUMENT") // critere d'arret
		{
			nbOk++;
			break;
		}

		else if (line == "") // on ignore les ligne vide
		{
			lineCount--;
		}

		else if (line.size() >= 2 && line[0] == '/' &&  line[1] == '/') // on ignore les ligne qui commencent par //
		{
			lineCount--;
		}

		else if (lineCount == 0)
		{
			if (line != "CHARACTER_STAT")
			{
				error = true; errorCode = 1; break;
			}
			else
			{
				nbOk++;
			}
		}

		else if (lineCount == 1)
		{
			if (line != "VERSION_254") // version
			{
				error = true; errorCode = 2; break;
			}
			else
			{
				nbOk++;
			}
		}

		else if (lineCount == 2)
		{
			// character name
			namePerso = line;
			int aa = 0;
		}

		else if (lineCount == 3)
		{
			if (line != "#LIST_NPC_KILLED") // version
			{
				error = true; errorCode = 3; break;
			}
		}

		else if (lineCount == 4)
		{
			int nb = atoi(line.c_str());
			nbNpcKilled = nb;
		}

		else if (lineCount >= 5 && lineCount <= 5 + nbNpcKilled - 1)
		{
			int npcid = 0;
			int npckilled = 0;
			if (sscanf(line.c_str(), "%d,%d", &npcid, &npckilled) != 2)
			{
				error = true;
				errorCode = 4;
				break;
			}
			richa_NpcKilled.push_back(RICHA_NPC_KILLED_STAT(npcid, npckilled));
		}


		else if (lineCount == 5 + nbNpcKilled - 1 + 1)
		{
			if (line != "#LIST_PAGE_DISCOVERED") // version
			{
				error = true; errorCode = 5; break;
			}
		}

		else if (lineCount == 5 + nbNpcKilled - 1 + 2)
		{
			int nb = atoi(line.c_str());
			nbPageDiscoverd = nb;
		}

		else if (lineCount >= 5 + nbNpcKilled - 1 + 3 && lineCount <= (5 + nbNpcKilled - 1 + 3) + nbPageDiscoverd - 1)
		{
			int pageid = 0;
			int objectid = 0;
			int itemid = 0;
			int unuseddd = 0;
			if (sscanf(line.c_str(), "%d,%d,%d,%d", &pageid, &objectid, &itemid, &unuseddd) != 4)
			{
				error = true; errorCode = 6;
				break;
			}

			if (objectid == 0 && itemid == 0)
			{
				error = true; errorCode = 7;  break;
			}
			if (objectid != 0 && itemid != 0)
			{
				error = true; errorCode = 8; break;
			}
			if (unuseddd != 0)
			{
				error = true; errorCode = 9;  break;
			}

			richa_pageDiscovered.push_back(RICHA_PAGE_DISCO_STAT(pageid, objectid, itemid));
		}




		// mettre les section ici  AVANT les IF qui vont lire dans les sections
		else if (line == "#LIST_LUNARFESTIVAL_ELDERFOUND")
		{
			currentSectionName = line;
			currentSectionLine = 0;
		}
		else if (line == "#LIST_MAISON_TAVERN")
		{
			currentSectionName = line;
			currentSectionLine = 0;
		}
		else if (line == "#LIST_ITEM_LOOT_QUEST")
		{
			currentSectionName = line;
			currentSectionLine = 0;
		}




		else if (currentSectionName == "#LIST_LUNARFESTIVAL_ELDERFOUND")
		{
			int year = 0;
			int questid = 0;
			int nbnb = sscanf(line.c_str(), "%d,%d", &year, &questid);
			if (nbnb != 2)
			{
				error = true; errorCode = 10;
				break;
			}
			richa_lunerFestivalElderFound.push_back(RICHA_LUNARFESTIVAL_ELDERFOUND(year, questid));
			currentSectionLine++;
		}

		else if (currentSectionName == "#LIST_MAISON_TAVERN")
		{
			int mapid = 0;
			int areaid = 0;
			char sonzename[4096];
			if (sscanf(line.c_str(), "%d,%d,%s", &mapid, &areaid, sonzename) != 3)
			{
				error = true; errorCode = 11;
				break;
			}
			richa_ListeMaison.push_back(RICHA_MAISON_TAVERN(mapid, areaid));
			currentSectionLine++;
		}

		else if (currentSectionName == "#LIST_ITEM_LOOT_QUEST")
		{
			int i0 = 0;
			int i1 = 0;
			float f0 = 0.0f;
			int i3 = 0;
			int i4 = 0;
			if (sscanf(line.c_str(), "%d,%d,%f,%d,%d", &i0, &i1, &f0, &i3, &i4) != 5)
			{
				error = true; errorCode = 15;
				break;
			}
			richa_ListItemQuestLoot.push_back(RICHA_ITEM_LOOT_QUEST(i0, i1, f0, i3, i4));
			currentSectionLine++;
		}

		else
		{
			error = true; errorCode = 12;
			break;
		}


		lineCount++;
	}

	if (richa_NpcKilled.size() != nbNpcKilled)
	{
		error = true; errorCode = 13;
	}
	if (richa_pageDiscovered.size() != nbPageDiscoverd)
	{
		error = true; errorCode = 14;
	}


	if (nbOk != 3 || error || errorCode != 0)
	{
		if (error)
		{
			int aaaaa = 0;
		}

		char finalErro[4096];
		sprintf(finalErro, "RICHAR WARNING GRAVE cant load save for guid= %d   errorCode= %d -  JE BLOQUE LE SERVER !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!",
			(uint32_t)guid__,
			errorCode);

		sLog->outBasic(finalErro);

		// je prefere bloquer le serveur plutot que charger n'importe quoi ou prendre le risque d'effacer des data
		for (int i = 0; ; i++)
		{
			Sleep(1000);
			int aaaa = 0;
		}


		//si on arrive dans cette erreur, ca veut dire que	_ri_character_%d.txt
		//n'a pas été chargé correctment.


		//on RESET toutes la variables importées par ce TXT :
		richa_NpcKilled.clear();
		richa_pageDiscovered.clear();
		richa_lunerFestivalElderFound.clear();
		richa_ListeMaison.clear();
		richa_ListItemQuestLoot.clear();
		namePerso = "";


	}


	infile.close();
}

void PlayerModeDataRicha::richard_importVariables_START(uint64 guid__)
{
	sLog->outBasic("Start richard_importVariables....");

	std::string persoNameImport;
	richa_importFrom_richaracter_(
		guid__,
		m_richa_NpcKilled,
		m_richa_pageDiscovered,
		m_richa_lunerFestivalElderFound,
		m_richa_ListeMaison,
		m_richa_itemLootQuests,
		persoNameImport
	);

	sLog->outBasic("FINISH richard_importVariables");
}


int PlayerModeDataRicha::GetParagonLevelFromItem()
{
	for (int i = 1; i < 100; i++)
	{
		int countitem = m_thisOwner->GetItemCount(71000 + i);
		if (countitem >= 1) // normallement c'est juste 0  ou 1
		{
			return i;
		}
	}

	return 0;
}

inline bool IsSpellHaveEffect_richa(SpellEntry const* spellInfo, SpellEffects effect)
{
	for (unsigned int i : spellInfo->Effect)
		if (SpellEffects(i) == effect)
			return true;
	return false;
}

bool IsPassiveSpell_richa(SpellEntry const* spellInfo)
{
	const SpellInfo* spellInfo__ = sSpellMgr->GetSpellInfo(spellInfo->Id);
	return spellInfo__->IsPassive();
}
bool IsPassiveSpell_richa(uint32 spellId)
{
	SpellEntry const* spellInfo = sSpellStore.LookupEntry(spellId);
	if (!spellInfo)
		return false;
	return IsPassiveSpell_richa(spellInfo);
}

static std::string GetTimeString_richa(uint64 time)
{
	uint64 days = time / DAY, hours = (time % DAY) / HOUR, minute = (time % HOUR) / MINUTE;
	std::ostringstream ss;
	if (days)
		ss << days << "d ";
	if (hours)
		ss << hours << "h ";
	ss << minute << 'm';
	return ss.str();
}

void PlayerModeDataRicha::richa_exportTo_ristat_()
{
	const int richa_language = m_thisOwner->GetSession()->GetSessionDbcLocale();  // 0 pour US  -  2 pour FR  - langue de client utilisé pour extraire les bases de données


	time_t t = time(0);   // get time now
	struct tm * now = localtime(&t);

	char outt[4096];

	// id dans la base de donnée
	const uint32 coinItemID1 = 70010; // YouhaiCoin Paragon
	const uint32 coinItemID2 = 70007; // YouhaiCoin Cadeau

	char nameFile[2048];
	const char* playerName = m_thisOwner->GetName().c_str();
	sprintf(nameFile, "RICHARDS_WOTLK/_ri_stat_%s_%d_%02d_%02d.txt",
		playerName,
		now->tm_year + 1900,
		now->tm_mon + 1,
		now->tm_mday
	);
	FILE* fout = fopen(nameFile, "wb");

	// pour faciliter la comparaison entre 2 fichier, c'est mieux je pense de mettre les 2 parametres de temps (qui bougent tout le temps)
	// au debut du fichier

	sprintf(outt, "played,%d\r\n", m_thisOwner->GetTotalPlayedTime());
	fwrite(outt, 1, strlen(outt), fout);

	sprintf(outt, "timenow,%d_%02d_%02d_%02d_%02d_%02d\r\n",
		now->tm_year + 1900,
		now->tm_mon + 1,
		now->tm_mday,
		now->tm_hour,
		now->tm_min,
		now->tm_sec);
	fwrite(outt, 1, strlen(outt), fout);


	int nbyouhaiCadeau = richard_countItem(coinItemID2, true, true, true, true);
	int nbyouhaiPara = richard_countItem(coinItemID1, true, true, true, true);

	int nbyouhaiCadeau_2 = m_thisOwner->GetItemCount(coinItemID2, true);
	int nbyouhaiPara_2 = m_thisOwner->GetItemCount(coinItemID1, true);


	if (nbyouhaiCadeau != nbyouhaiCadeau_2
		|| nbyouhaiPara != nbyouhaiPara_2
		)
	{
		// ERREUR GRAVE !
		sLog->outBasic("WARNING GRAVE 2369 !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
		Sleep(20000);
		int rrr = 0;
	}


	sprintf(outt, "youhaicoin,%d\r\n", nbyouhaiPara + nbyouhaiCadeau);
	fwrite(outt, 1, strlen(outt), fout);

	sprintf(outt, "youhaicoin_paragon,%d\r\n", nbyouhaiPara);
	fwrite(outt, 1, strlen(outt), fout);

	sprintf(outt, "youhaicoin_cadeau,%d\r\n", nbyouhaiCadeau);
	fwrite(outt, 1, strlen(outt), fout);

	sprintf(outt, "level,%d\r\n", m_thisOwner->getLevel());
	fwrite(outt, 1, strlen(outt), fout);

	sprintf(outt, "xp,%d\r\n", m_thisOwner->GetUInt32Value(PLAYER_XP));
	fwrite(outt, 1, strlen(outt), fout);

	sprintf(outt, "xpNextLevel,%d\r\n", m_thisOwner->GetUInt32Value(PLAYER_NEXT_LEVEL_XP));
	fwrite(outt, 1, strlen(outt), fout);

	sprintf(outt, "paragon,%d\r\n", GetParagonLevelFromItem());
	fwrite(outt, 1, strlen(outt), fout);




	//get & save GPS info
	{
		uint32 zone_id, area_id;
		m_thisOwner->GetZoneAndAreaId(zone_id, area_id);

		MapEntry const* mapEntry = sMapStore.LookupEntry(m_thisOwner->GetMapId());
		AreaTableEntry const* zoneEntry = sAreaTableStore.LookupEntry(zone_id);
		AreaTableEntry const* areaEntry = sAreaTableStore.LookupEntry(area_id);

		float zone_x = m_thisOwner->GetPositionX();
		float zone_y = m_thisOwner->GetPositionY();

		Map2ZoneCoordinates(zone_x, zone_y, zone_id);


		Map const* map = m_thisOwner->GetMap();
		//float ground_z = map->GetHeight(GetPositionX(), GetPositionY(), MAX_HEIGHT);
		//float floor_z = map->GetHeight(GetPositionX(), GetPositionY(), GetPositionZ());
		float ground_z = map->GetHeight(m_thisOwner->GetPhaseMask(), m_thisOwner->GetPositionX(), m_thisOwner->GetPositionY(), MAX_HEIGHT);
		float floor_z = map->GetHeight(m_thisOwner->GetPhaseMask(), m_thisOwner->GetPositionX(), m_thisOwner->GetPositionY(), m_thisOwner->GetPositionZ());

		/*
		GridPair p = MaNGOS::ComputeGridPair(GetPositionX(), GetPositionY());

		int gx = 63 - p.x_coord;
		int gy = 63 - p.y_coord;

		uint32 have_map = GridMap::ExistMap(GetMapId(), gx, gy) ? 1 : 0;
		uint32 have_vmap = GridMap::ExistVMap(GetMapId(), gx, gy) ? 1 : 0;
		

		TerrainInfo const* terrain = GetTerrain();
		*/

		//if (have_vmap)
		//{
		//	if (terrain->IsOutdoors(GetPositionX(), GetPositionY(), GetPositionZ()))
		//		PSendSysMessage("You are OUTdoor");
		//	else
		//		PSendSysMessage("You are INdoor");
		//}
		//else PSendSysMessage("no VMAP available for area info");

		//ca m'arrive de voir une difference de ~0.01 entre 2 fichiers alors que le perso n'a pas ete deplacé.
		//Donc pour faciliter la comparaison, je vais arrondir.
		//ca ne change pas grand chose car les nombre sont de l'ordre du centaine/millier
		sprintf(outt, "GPS_GetPositionXYZ,%d,%d,%d\r\n", (int)m_thisOwner->GetPositionX(), (int)m_thisOwner->GetPositionY(), (int)m_thisOwner->GetPositionZ());
		fwrite(outt, 1, strlen(outt), fout);

		sprintf(outt, "GPS_GetOrientation,%.2f\r\n", m_thisOwner->GetOrientation());
		fwrite(outt, 1, strlen(outt), fout);

		sprintf(outt, "GPS_GetMapId,%d\r\n", m_thisOwner->GetMapId());
		fwrite(outt, 1, strlen(outt), fout);
		sprintf(outt, "GPS_zoneID,%d\r\n", zone_id);
		fwrite(outt, 1, strlen(outt), fout);
		sprintf(outt, "GPS_areaID,%d\r\n", area_id);
		fwrite(outt, 1, strlen(outt), fout);
		sprintf(outt, "GPS_mapEntry,\"%s\"\r\n", mapEntry ? mapEntry->name[richa_language] : "<unknown>");
		fwrite(outt, 1, strlen(outt), fout);
		sprintf(outt, "GPS_zoneEntry,\"%s\"\r\n", zoneEntry ? zoneEntry->area_name[richa_language] : "<unknown>");
		fwrite(outt, 1, strlen(outt), fout);
		sprintf(outt, "GPS_areaEntry,\"%s\"\r\n", areaEntry ? areaEntry->area_name[richa_language] : "<unknown>");
		fwrite(outt, 1, strlen(outt), fout);

	}



	sprintf(outt, "isDead,%d\r\n", m_thisOwner->isDead() ? 1 : 0);
	fwrite(outt, 1, strlen(outt), fout);


	//sprintf(outt, "isFlying,%d\r\n", m_thisOwner->IsTaxiFlying() ? 1 : 0);
	//fwrite(outt, 1, strlen(outt), fout);


	sprintf(outt, "queteList,");
	fwrite(outt, 1, strlen(outt), fout);
	int nbQuete = 0;
	std::vector<uint32> questInLog;
	for (int i = 0; i < MAX_QUEST_LOG_SIZE; ++i)
	{
		uint32 questid = m_thisOwner->GetQuestSlotQuestId(i);
		questInLog.push_back(questid);

		if (questid != 0)
		{
			nbQuete++;
		}
	}
	//on les range par ordre croissant, c'est toujours mieux de faire ca, en cas de comparaison entre 2 fichiers
	std::sort(questInLog.begin(), questInLog.end());
	if (questInLog.size() != 25)
	{
		sLog->outBasic("RICHAR: WARNING 53644 !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
		int errror = 0;
	}
	for (int i = 0; i < questInLog.size(); ++i)
	{
		sprintf(outt, "%d,", questInLog[i]);
		fwrite(outt, 1, strlen(outt), fout);
	}
	sprintf(outt, "\r\n");
	fwrite(outt, 1, strlen(outt), fout);

	sprintf(outt, "nbQuete,%d\r\n", nbQuete);
	fwrite(outt, 1, strlen(outt), fout);


	sprintf(outt, "version,10\r\n"); // version of THIS save file, think to increment it each time you add update
	fwrite(outt, 1, strlen(outt), fout);


	// QUEST_STATUS_NONE, je crois qu'une quete NONE peut correspondre a 2 choses uniquement :
	// - je l'ai deja prise - deja eu dans mon journal - mais je l'ai refusée <- donc elle n'est plus dans mon journal
	// OU
	// - c'est une quete repetable que j'ai Complete.  dans ce cas, cmangos va lui assigner le status  NONE	  <- donc elle n'est plus dans mon journal
	//
	// pour distinguer les 2 je crois qu'il suffit de regarder si la quete est dans la liste  REWARDED_TRUE (deja fait une fois, donc repetable)
	// ou  REWARDED_FALSE --> donc non repetable
	//
	sprintf(outt, "questList_NONE,");
	fwrite(outt, 1, strlen(outt), fout);
	int nbQuete_NONE = 0;
	for (QuestStatusMap::iterator i = m_thisOwner->m_QuestStatus.begin(); i != m_thisOwner->m_QuestStatus.end(); ++i)
	{
		uint32 questid = i->first;
		QuestStatusData& questStatus = i->second;

		// le 7 mars 2018, je me rends compte d'une erreur, je vois   questStatus.m_rewarded   alors que ca doit etre  questStatus.m_status !
		if (questStatus.Status == QUEST_STATUS_NONE)
		{
			sprintf(outt, "%d,", questid);
			fwrite(outt, 1, strlen(outt), fout);
			nbQuete_NONE++;
		}





		//juste un petit check de debug  pour voir si j'ai bien tout compris
		Quest const* pQuest = sObjectMgr->GetQuestTemplate(questid);
		if (!pQuest || pQuest->GetQuestId() != questid)
		{
			sLog->outBasic("RICHAR: WARNING 53641 !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
			int errror = 0;
		}
		else
		{
			/*
			if (questStatus.Status == QUEST_STATUS_NONE)
			{
				//
				if (questStatus.m_rewarded && pQuest->IsRepeatable())
				{
					//soit c'est une quete que j'ai deja fini au moins une fois, et qui est repetable
				}
				else if (!questStatus.m_rewarded && !pQuest->IsRepeatable())
				{
					//soit j'ai annulé cette quete non repetable
				}
				else if (!questStatus.m_rewarded && pQuest->IsRepeatable())
				{
					//soit j'ai annulé cette quete repetable
				}
				else
				{
					// du coup, ce cas ne peut jamais arriver ?
					//c'est a dire un quete avec status = NONE   qui est récompensé, mais non repetable
					//pour moi ca ne doit pas arriver , car une quete non repetable, qui est réompensé, doit forcément avoir le status=COMPLETE
					//je teste ca juste en dessous
					sLog->outBasic("RICHAR: WARNING 53642 !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
					int errror = 0;
				}
			}

			if (questStatus.m_rewarded && !pQuest->IsRepeatable())
			{
				if (questStatus.m_status != QUEST_STATUS_COMPLETE)
				{
					// j ai deja reussi a reproduire ce warning, sans faire expres, 
					// avec le grandjuge, en gros en faisant un  .quest remove
					sLog->outBasic("RICHAR: WARNING 53643 !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
					int errror = 0;
				}

			}
			*/

		}





	}
	sprintf(outt, "\r\nnbQuest_NONE,%d\r\n", nbQuete_NONE);
	fwrite(outt, 1, strlen(outt), fout);



	sprintf(outt, "questList_COMPLETE,");
	fwrite(outt, 1, strlen(outt), fout);
	int nbQuete_COMPLETE = 0;
	for (QuestStatusMap::iterator i = m_thisOwner->m_QuestStatus.begin(); i != m_thisOwner->m_QuestStatus.end(); ++i)
	{
		uint32 questid = i->first;
		QuestStatusData& questStatus = i->second;

		// le 7 mars 2018, je me rends compte d'une erreur, je vois   questStatus.m_rewarded   alors que ca doit etre  questStatus.m_status !
		if (questStatus.Status == QUEST_STATUS_COMPLETE)
		{
			sprintf(outt, "%d,", questid);
			fwrite(outt, 1, strlen(outt), fout);
			nbQuete_COMPLETE++;
		}
	}
	sprintf(outt, "\r\nnbQuest_COMPLETE,%d\r\n", nbQuete_COMPLETE);
	fwrite(outt, 1, strlen(outt), fout);



	sprintf(outt, "questList_UNAVAILABLE,");
	fwrite(outt, 1, strlen(outt), fout);
	int nbQuete_UNAVAILABLE = 0;
	for (QuestStatusMap::iterator i = m_thisOwner->m_QuestStatus.begin(); i != m_thisOwner->m_QuestStatus.end(); ++i)
	{
		uint32 questid = i->first;
		QuestStatusData& questStatus = i->second;
		/*
		// le 7 mars 2018, je me rends compte d'une erreur, je vois   questStatus.m_rewarded   alors que ca doit etre  questStatus.m_status !
		if (questStatus.Status == QUEST_STATUS_UNAVAILABLE)
		{
			sprintf(outt, "%d,", questid);
			fwrite(outt, 1, strlen(outt), fout);
			nbQuete_UNAVAILABLE++;
		}*/

	}
	sprintf(outt, "\r\nnbQuest_UNAVAILABLE,%d\r\n", nbQuete_UNAVAILABLE);
	fwrite(outt, 1, strlen(outt), fout);



	sprintf(outt, "questList_INCOMPLETE,");
	fwrite(outt, 1, strlen(outt), fout);
	int nbQuete_INCOMPLETE = 0;
	for (QuestStatusMap::iterator i = m_thisOwner->m_QuestStatus.begin(); i != m_thisOwner->m_QuestStatus.end(); ++i)
	{
		uint32 questid = i->first;
		QuestStatusData& questStatus = i->second;

		// le 7 mars 2018, je me rends compte d'une erreur, je vois   questStatus.m_rewarded   alors que ca doit etre  questStatus.m_status !
		if (questStatus.Status == QUEST_STATUS_INCOMPLETE)
		{
			sprintf(outt, "%d,", questid);
			fwrite(outt, 1, strlen(outt), fout);
			nbQuete_INCOMPLETE++;
		}
	}
	sprintf(outt, "\r\nnbQuest_INCOMPLETE,%d\r\n", nbQuete_INCOMPLETE);
	fwrite(outt, 1, strlen(outt), fout);


	//je crois que  QUEST_STATUS_AVAILABLE  est inutilisé.
	sprintf(outt, "questList_AVAILABLE,");
	fwrite(outt, 1, strlen(outt), fout);
	int nbQuete_AVAILABLE = 0;
	for (QuestStatusMap::iterator i = m_thisOwner->m_QuestStatus.begin(); i != m_thisOwner->m_QuestStatus.end(); ++i)
	{
		uint32 questid = i->first;
		QuestStatusData& questStatus = i->second;
		/*
		// le 7 mars 2018, je me rends compte d'une erreur, je vois   questStatus.m_rewarded   alors que ca doit etre  questStatus.m_status !
		if (questStatus.Status == QUEST_STATUS_AVAILABLE)
		{
			sprintf(outt, "%d,", questid);
			fwrite(outt, 1, strlen(outt), fout);
			nbQuete_AVAILABLE++;
		}*/
	}
	sprintf(outt, "\r\nnbQuest_AVAILABLE,%d\r\n", nbQuete_AVAILABLE);
	fwrite(outt, 1, strlen(outt), fout);



	sprintf(outt, "questList_FAILED,");
	fwrite(outt, 1, strlen(outt), fout);
	int nbQuete_FAILED = 0;
	for (QuestStatusMap::iterator i = m_thisOwner->m_QuestStatus.begin(); i != m_thisOwner->m_QuestStatus.end(); ++i)
	{
		uint32 questid = i->first;
		QuestStatusData& questStatus = i->second;

		// le 7 mars 2018, je me rends compte d'une erreur, je vois   questStatus.m_rewarded   alors que ca doit etre  questStatus.m_status !
		if (questStatus.Status == QUEST_STATUS_FAILED)
		{
			sprintf(outt, "%d,", questid);
			fwrite(outt, 1, strlen(outt), fout);
			nbQuete_FAILED++;
		}
	}
	sprintf(outt, "\r\nnbQuest_FAILED,%d\r\n", nbQuete_FAILED);
	fwrite(outt, 1, strlen(outt), fout);




	// ajouté le  7 mars 2018  quand je me suis rendu compte de l'erreur
	sprintf(outt, "questList_REWARDED_TRUE,");
	fwrite(outt, 1, strlen(outt), fout);
	int nbQuete_REWARDED_TRUE = 0;
	for (QuestStatusMap::iterator i = m_thisOwner->m_QuestStatus.begin(); i != m_thisOwner->m_QuestStatus.end(); ++i)
	{
		uint32 questid = i->first;
		QuestStatusData& questStatus = i->second;
		/*
		if (questStatus.m_rewarded)
		{
			sprintf(outt, "%d,", questid);
			fwrite(outt, 1, strlen(outt), fout);
			nbQuete_REWARDED_TRUE++;
		}*/
	}
	sprintf(outt, "\r\nnbQuest_REWARDED_TRUE,%d\r\n", nbQuete_REWARDED_TRUE);
	fwrite(outt, 1, strlen(outt), fout);

	sprintf(outt, "questList_REWARDED_FALSE,");
	fwrite(outt, 1, strlen(outt), fout);
	int nbQuete_REWARDED_FALSE = 0;
	for (QuestStatusMap::iterator i = m_thisOwner->m_QuestStatus.begin(); i != m_thisOwner->m_QuestStatus.end(); ++i)
	{
		uint32 questid = i->first;
		QuestStatusData& questStatus = i->second;
		/*
		if (!questStatus.m_rewarded)
		{
			sprintf(outt, "%d,", questid);
			fwrite(outt, 1, strlen(outt), fout);
			nbQuete_REWARDED_FALSE++;
		}*/
	}
	sprintf(outt, "\r\nnbQuest_REWARDED_FALSE,%d\r\n", nbQuete_REWARDED_FALSE);
	fwrite(outt, 1, strlen(outt), fout);





	//sauvegarde des mails
	sprintf(outt, "MAIL,");
	fwrite(outt, 1, strlen(outt), fout);
	int nbMAIL = 0;
	for (PlayerMails::iterator itr = m_thisOwner->m_mail.begin(); itr != m_thisOwner->m_mail.end(); ++itr)
	{
		uint32 mailid = (*itr)->messageID;
		sprintf(outt, "%d,", mailid);
		fwrite(outt, 1, strlen(outt), fout);
		nbMAIL++;
	}
	sprintf(outt, "\r\nnbMAIL,%d\r\n", nbMAIL);
	fwrite(outt, 1, strlen(outt), fout);








	sprintf(outt, "\r\n#LIST_SPELLS =================================\r\n");
	fwrite(outt, 1, strlen(outt), fout);

	// COUNTER
	int nbSpell = 0;
	for (auto itr = m_thisOwner->m_spells.begin(); itr != m_thisOwner->m_spells.end(); ++itr)
	{
		//SpellEntry const* spellInfo = sSpellStore.LookupEntry(itr->first);
		SpellEntry const* spellInfo = sSpellStore.LookupEntry(itr->first);
		if (!spellInfo)
			continue;
		nbSpell++;
	}
	sprintf(outt, "ListSpellCount,%d\r\n", nbSpell);
	fwrite(outt, 1, strlen(outt), fout);


	//je convertis m_spells qui est un std::unordered_map  en un  map qui est ordonné.
	//ca devrait normallement me ranger mes nombre dans l'order croissant,  ce qui est toujours plus pratique quand il faudra comparer 2 fichiers
	std::map<uint32, PlayerSpell>  orderedMapSpell;
	for (PlayerSpellMap::const_iterator itr = m_thisOwner->m_spells.begin(); itr != m_thisOwner->m_spells.end(); ++itr)
	{
		orderedMapSpell[itr->first] = *(itr->second);
	}

	if (orderedMapSpell.size() != m_thisOwner->m_spells.size())
	{
		//les 2 tailles doivent etre toujours egales
		sLog->outBasic("RICHAR: WARNING 53645 !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
		int errror = 0;
	}

	for (auto itr = orderedMapSpell.begin(); itr != orderedMapSpell.end(); ++itr)
	{
		//SpellEntry const* spellInfo = sSpellStore.LookupEntry(itr->first);
		SpellEntry const* spellInfo = sSpellStore.LookupEntry(itr->first);
		if (!spellInfo)
			continue;

		PlayerSpell const& playerSpell = itr->second;

		//if ( HasSpell();
		//S_GNOMISH

		//if (playerSpell.state == PLAYERSPELL_REMOVED)
		//	continue;

		//if (!playerSpell.active || playerSpell.disabled)
		//	continue;


		std::string effectName = "";
		for (int i = SPELL_EFFECT_INSTAKILL; i < TOTAL_SPELL_EFFECTS; i++)
		{
			bool eff = IsSpellHaveEffect_richa(spellInfo, (SpellEffects)i);
			if (eff)
			{
				if (false) {}
				//else if ( i == SPELL_EFFECT_NONE ) { effectName = "SPELL_EFFECT_NONE"; }
				else if (i == SPELL_EFFECT_INSTAKILL) { effectName += "SPELL_EFFECT_INSTAKILL "; }


				else if (i == SPELL_EFFECT_LEARN_SPELL) { effectName += "SPELL_EFFECT_LEARN_SPELL "; }

				else if (i == SPELL_EFFECT_DEFENSE) { effectName += "SPELL_EFFECT_DEFENSE "; }


				else if (i == SPELL_EFFECT_ENCHANT_ITEM) { effectName += "SPELL_EFFECT_ENCHANT_ITEM "; }
				else if (i == SPELL_EFFECT_ENCHANT_ITEM_TEMPORARY) { effectName += "SPELL_EFFECT_ENCHANT_ITEM_TEMPORARY "; }

				//else if ( i == XXXX ) { effectName = "XXXX"; }
				//break;
			}
		}


		int loc = m_thisOwner->GetSession()->GetSessionDbcLocale();

		//if (  strcmp(spellInfo->SpellName[loc], "Dragonscale Leatherworking") == 0 )
		//{
		//	int a=0;
		//}


		sprintf(outt, "%d,\"%s\",%d,0x%llx,%s\r\n",
			itr->first,
			spellInfo->SpellName[0], // la il faut rester sur SpellName[0] car cette database vient du server, et pas des FBC, donc c'est anglais only
			spellInfo->Category,
			spellInfo->SpellFamilyFlags,
			effectName.c_str()  // ...

		);
		fwrite(outt, 1, strlen(outt), fout);
	}





	//save items of player
	{


		//bool inBankAlso = true; // count bank or not
		//bool inEquipmentAlso = true;
		//bool inKeyRingAlso = true;
		//bool inInventoryAlso = true;

		sprintf(outt, "\r\n#LIST_ITEMS_INVENTORY_BAG ==========\r\n");
		fwrite(outt, 1, strlen(outt), fout);

		// COUNTER
		{
			int nb = 0;

			for (int i = INVENTORY_SLOT_BAG_START; i < INVENTORY_SLOT_BAG_END; ++i)
			{
				if (Bag* pBag = (Bag*)m_thisOwner->GetItemByPos(INVENTORY_SLOT_BAG_0, i))
				{
					Item* pItem = pBag;
					if (pItem)
					{

						nb++;
					}
				}
			}
			sprintf(outt, "Counter,%d\r\n", nb);
			fwrite(outt, 1, strlen(outt), fout);
		}

		for (int i = INVENTORY_SLOT_BAG_START; i < INVENTORY_SLOT_BAG_END; ++i)
		{
			if (Bag* pBag = (Bag*)m_thisOwner->GetItemByPos(INVENTORY_SLOT_BAG_0, i))
			{
				Item* pItem = pBag;
				if (pItem)
				{
					//ItemPrototype const* itemProto = sItemStorage.LookupEntry<ItemPrototype>(pItem->GetEntry());
					ItemTemplate const* itemProto = sObjectMgr->GetItemTemplate(pItem->GetEntry());

					sprintf(outt, "%d,%d,\"%s\"\r\n", pItem->GetEntry(), pBag->GetBagSize(), itemProto->Name1);
					fwrite(outt, 1, strlen(outt), fout);
				}
			}
		}


		sprintf(outt, "\r\n#LIST_ITEMS_EQUIPED ==========\r\n");
		fwrite(outt, 1, strlen(outt), fout);

		// COUNTER
		{
			int nb = 0;

			for (int i = EQUIPMENT_SLOT_START; i < EQUIPMENT_SLOT_END; ++i)
			{
				Item* pItem = m_thisOwner->GetItemByPos(INVENTORY_SLOT_BAG_0, i);
				if (pItem)
				{

					nb++;
				}
			}
			sprintf(outt, "Counter,%d\r\n", nb);
			fwrite(outt, 1, strlen(outt), fout);
		}

		//if (inEquipmentAlso)
		{
			for (int i = EQUIPMENT_SLOT_START; i < EQUIPMENT_SLOT_END; ++i)
			{
				Item* pItem = m_thisOwner->GetItemByPos(INVENTORY_SLOT_BAG_0, i);
				if (pItem)
				{
					//ItemPrototype const* itemProto = sItemStorage.LookupEntry<ItemPrototype>(pItem->GetEntry());
					ItemTemplate const* itemProto = sObjectMgr->GetItemTemplate(pItem->GetEntry());
					sprintf(outt, "%d,%d,\"%s\"\r\n", pItem->GetEntry(), pItem->GetCount(), itemProto->Name1);
					fwrite(outt, 1, strlen(outt), fout);
				}
				else
				{
					int aa = 0;
				}
			}
		}

		sprintf(outt, "\r\n#LIST_ITEMS_KEYRING ==========\r\n");
		fwrite(outt, 1, strlen(outt), fout);


		// COUNTER
		{
			int nb = 0;

			for (int i = KEYRING_SLOT_START; i < KEYRING_SLOT_END; ++i)
			{
				Item* pItem = m_thisOwner->GetItemByPos(INVENTORY_SLOT_BAG_0, i);
				if (pItem)
				{

					nb++;
				}
			}
			sprintf(outt, "Counter,%d\r\n", nb);
			fwrite(outt, 1, strlen(outt), fout);
		}


		//if (inKeyRingAlso)
		{
			for (int i = KEYRING_SLOT_START; i < KEYRING_SLOT_END; ++i)
			{
				Item* pItem = m_thisOwner->GetItemByPos(INVENTORY_SLOT_BAG_0, i);
				if (pItem)
				{
					//ItemPrototype const* itemProto = sItemStorage.LookupEntry<ItemPrototype>(pItem->GetEntry());
					ItemTemplate const* itemProto = sObjectMgr->GetItemTemplate(pItem->GetEntry());
					sprintf(outt, "%d,%d,\"%s\"\r\n", pItem->GetEntry(), pItem->GetCount(), itemProto->Name1);
					fwrite(outt, 1, strlen(outt), fout);
				}
			}
		}





		sprintf(outt, "\r\n#LIST_ITEMS_INVENTORY ==========\r\n");
		fwrite(outt, 1, strlen(outt), fout);

		// COUNTER
		{
			int nb = 0;

			for (int i = INVENTORY_SLOT_BAG_START; i < INVENTORY_SLOT_BAG_END; ++i)
			{
				if (Bag* pBag = (Bag*)m_thisOwner->GetItemByPos(INVENTORY_SLOT_BAG_0, i))
				{
					for (uint32 j = 0; j < pBag->GetBagSize(); ++j)
					{

						nb++;
					}
				}
			}
			sprintf(outt, "Counter,%d\r\n", nb);
			fwrite(outt, 1, strlen(outt), fout);
		}

		//if (inInventoryAlso)
		{
			for (int i = INVENTORY_SLOT_BAG_START; i < INVENTORY_SLOT_BAG_END; ++i)
			{
				if (Bag* pBag = (Bag*)m_thisOwner->GetItemByPos(INVENTORY_SLOT_BAG_0, i))
				{
					for (uint32 j = 0; j < pBag->GetBagSize(); ++j)
					{

						Item* pItem = m_thisOwner->GetItemByPos(i, j);

						if (pItem)
						{
							//	sLog->outBasic("RICHAR: item = %d",pItem->GetEntry());
						}
						else
						{
							//	sLog->outBasic("RICHAR: item = nothing");
						}

						if (pItem)
						{
							//ItemPrototype const* itemProto = sItemStorage.LookupEntry<ItemPrototype>(pItem->GetEntry());
							ItemTemplate const* itemProto = sObjectMgr->GetItemTemplate(pItem->GetEntry());
							sprintf(outt, "%d,%d,\"%s\"\r\n", pItem->GetEntry(), pItem->GetCount(), itemProto->Name1);
							fwrite(outt, 1, strlen(outt), fout);
						}
					}
				}
			}

			for (int i = INVENTORY_SLOT_ITEM_START; i < INVENTORY_SLOT_ITEM_END; ++i) // les 16 place du packback de default
			{
				Item* pItem = m_thisOwner->GetItemByPos(INVENTORY_SLOT_BAG_0, i);
				if (pItem)
				{
					//ItemPrototype const* itemProto = sItemStorage.LookupEntry<ItemPrototype>(pItem->GetEntry());
					ItemTemplate const* itemProto = sObjectMgr->GetItemTemplate(pItem->GetEntry());
					sprintf(outt, "%d,%d,\"%s\"\r\n", pItem->GetEntry(), pItem->GetCount(), itemProto->Name1);
					fwrite(outt, 1, strlen(outt), fout);
				}
			}
		}


		sprintf(outt, "\r\n#LIST_ITEMS_BANK_BAG ==========\r\n");
		fwrite(outt, 1, strlen(outt), fout);

		// COUNTER
		{
			int nb = 0;

			for (int i = BANK_SLOT_BAG_START; i < BANK_SLOT_BAG_END; ++i)
			{
				if (Bag* pBag = (Bag*)m_thisOwner->GetItemByPos(INVENTORY_SLOT_BAG_0, i))
				{
					Item* pItem = pBag;
					if (pItem)
					{

						nb++;
					}
				}
			}
			sprintf(outt, "Counter,%d\r\n", nb);
			fwrite(outt, 1, strlen(outt), fout);
		}

		for (int i = BANK_SLOT_BAG_START; i < BANK_SLOT_BAG_END; ++i)
		{
			if (Bag* pBag = (Bag*)m_thisOwner->GetItemByPos(INVENTORY_SLOT_BAG_0, i))
			{
				Item* pItem = pBag;
				if (pItem)
				{
					//ItemPrototype const* itemProto = sItemStorage.LookupEntry<ItemPrototype>(pItem->GetEntry());
					ItemTemplate const* itemProto = sObjectMgr->GetItemTemplate(pItem->GetEntry());
					sprintf(outt, "%d,%d,\"%s\"\r\n", pItem->GetEntry(), pBag->GetBagSize(), itemProto->Name1);
					fwrite(outt, 1, strlen(outt), fout);
				}
			}
		}


		sprintf(outt, "\r\n#LIST_ITEMS_BANK ==========\r\n");
		fwrite(outt, 1, strlen(outt), fout);

		// COUNTER
		{
			int nb = 0;

			for (int i = BANK_SLOT_ITEM_START; i < BANK_SLOT_ITEM_END; ++i)
			{
				Item* pItem = m_thisOwner->GetItemByPos(INVENTORY_SLOT_BAG_0, i);
				if (pItem)
				{

					nb++;
				}
			}

			for (int i = BANK_SLOT_BAG_START; i < BANK_SLOT_BAG_END; ++i)
			{
				if (Bag* pBag = (Bag*)m_thisOwner->GetItemByPos(INVENTORY_SLOT_BAG_0, i))
				{
					for (uint32 j = 0; j < pBag->GetBagSize(); ++j)
					{
						nb++;
					}
				}
			}

			sprintf(outt, "Counter,%d\r\n", nb);
			fwrite(outt, 1, strlen(outt), fout);
		}

		//if (inBankAlso)
		{
			for (int i = BANK_SLOT_ITEM_START; i < BANK_SLOT_ITEM_END; ++i)
			{
				Item* pItem = m_thisOwner->GetItemByPos(INVENTORY_SLOT_BAG_0, i);
				if (pItem)
				{
					//ItemPrototype const* itemProto = sItemStorage.LookupEntry<ItemPrototype>(pItem->GetEntry());
					ItemTemplate const* itemProto = sObjectMgr->GetItemTemplate(pItem->GetEntry());
					sprintf(outt, "%d,%d,\"%s\"\r\n", pItem->GetEntry(), pItem->GetCount(), itemProto->Name1);
					fwrite(outt, 1, strlen(outt), fout);
				}
			}
			for (int i = BANK_SLOT_BAG_START; i < BANK_SLOT_BAG_END; ++i)
			{
				if (Bag* pBag = (Bag*)m_thisOwner->GetItemByPos(INVENTORY_SLOT_BAG_0, i))
				{
					for (uint32 j = 0; j < pBag->GetBagSize(); ++j)
					{
						Item* pItem = m_thisOwner->GetItemByPos(i, j);
						if (pItem)
						{
							//ItemPrototype const* itemProto = sItemStorage.LookupEntry<ItemPrototype>(pItem->GetEntry());
							ItemTemplate const* itemProto = sObjectMgr->GetItemTemplate(pItem->GetEntry());
							sprintf(outt, "%d,%d,\"%s\"\r\n", pItem->GetEntry(), pItem->GetCount(), itemProto->Name1);
							fwrite(outt, 1, strlen(outt), fout);
						}
					}
				}
			}
		}



	}





	sprintf(outt, "\r\n#LIST_SKILLS =================================\r\n");
	fwrite(outt, 1, strlen(outt), fout);

	// COUNTER
	{
		int nb = 0;

		for (SkillStatusMap::const_iterator itr = m_thisOwner->mSkillStatus.begin(); itr != m_thisOwner->mSkillStatus.end(); ++itr)
		{
			SkillStatusData const& skillStatus = itr->second;
			if (skillStatus.uState == SKILL_DELETED)
				continue;

			nb++;
		}

		sprintf(outt, "Counter,%d\r\n", nb);
		fwrite(outt, 1, strlen(outt), fout);
	}


	for (SkillStatusMap::const_iterator itr = m_thisOwner->mSkillStatus.begin(); itr != m_thisOwner->mSkillStatus.end(); ++itr)
	{
		SkillStatusData const& skillStatus = itr->second;
		if (skillStatus.uState == SKILL_DELETED)
			continue;

		//par exemple, les humains on +5 en sword et en mass
		uint32 bonus = m_thisOwner->GetUInt32Value(PLAYER_SKILL_BONUS_INDEX(skillStatus.pos));
		//bonus va contenir le temporaire et le permanent  (en LO, et en HI)

		int32 value_ = int32(SKILL_VALUE(m_thisOwner->GetUInt32Value(PLAYER_SKILL_VALUE_INDEX(skillStatus.pos))));
		int32 value_max = int32(SKILL_MAX(m_thisOwner->GetUInt32Value(PLAYER_SKILL_VALUE_INDEX(skillStatus.pos))));

		std::string finalName;

		for (uint32 id = 0; id < sSkillLineStore.GetNumRows(); ++id)
		{
			SkillLineEntry const* skillInfo = sSkillLineStore.LookupEntry(id);
			if (skillInfo)
			{
				int loc = m_thisOwner->GetSession()->GetSessionDbcLocale();
				std::string name = skillInfo->name[loc];

				if (itr->first == id)
				{
					finalName = name;
					break;
				}

				int aa = 0;
			}
		}

		sprintf(outt, "%d,\"%s\",%d,%d,%d,%d\r\n", itr->first, finalName.c_str(), value_, value_max, SKILL_TEMP_BONUS(bonus), SKILL_PERM_BONUS(bonus));
		fwrite(outt, 1, strlen(outt), fout);
	}


	sprintf(outt, "\r\n#LIST_REPUTATION =================================\r\n");
	fwrite(outt, 1, strlen(outt), fout);

	// COUNTER
	{
		int nb = 0;

		for (auto itr = m_thisOwner->GetReputationMgr().GetStateList().begin(); itr != m_thisOwner->GetReputationMgr().GetStateList().end(); ++itr)
		{

			nb++;
		}

		sprintf(outt, "Counter,%d\r\n", nb);
		fwrite(outt, 1, strlen(outt), fout);
	}

	for (auto itr = m_thisOwner->GetReputationMgr().GetStateList().begin(); itr != m_thisOwner->GetReputationMgr().GetStateList().end(); ++itr)
	{
		const RepListID& faction_1 = itr->first;
		const FactionState& faction_2 = itr->second;


		ReputationRank rank = m_thisOwner->GetReputationRank(faction_2.ID);

		int32 reput = m_thisOwner->GetReputationMgr().GetReputation(faction_2.ID);



		FactionEntry const* factionEntry = sFactionStore.LookupEntry(faction_2.ID);

		std::string nameeeee = std::string(factionEntry->name[richa_language]);

		std::string rank_str = "??rank inconnu??";

		if (rank == REP_HATED) { rank_str = "HATED";			reput = 36000 + 3000 + 3000 + reput; }
		if (rank == REP_HOSTILE) { rank_str = "HOSTILE";		reput = 3000 + 3000 + reput; }
		if (rank == REP_UNFRIENDLY) { rank_str = "UNFRIENDLY";  reput = 3000 + reput; }
		if (rank == REP_NEUTRAL) { rank_str = "NEUTRAL"; }
		if (rank == REP_FRIENDLY) { rank_str = "FRIENDLY";  reput -= 3000; }
		if (rank == REP_HONORED) { rank_str = "HONORED";   reput -= 3000;  reput -= 6000; }
		if (rank == REP_REVERED) { rank_str = "REVERED";   reput -= 3000;  reput -= 6000; reput -= 12000; }
		if (rank == REP_EXALTED) { rank_str = "EXALTED";   reput -= 3000;   reput -= 6000; reput -= 12000; reput -= 21000; }

		//if (faction.needSave)
	   // {
		//	stmtDel.PExecute(m_player->GetGUIDLow(), faction.ID);
		//	stmtIns.PExecute(m_player->GetGUIDLow(), faction.ID, faction.Standing, faction.Flags);
		//	faction.needSave = false;
		//}


		sprintf(outt, "%d,\"%s\",\"%s\",%d\r\n", faction_2.ID, nameeeee.c_str(), rank_str.c_str(), reput);
		fwrite(outt, 1, strlen(outt), fout);


		int aa = 0;
	}



	{
		sprintf(outt, "\r\n#LIST_HONOR =================================\r\n");
		fwrite(outt, 1, strlen(outt), fout);

		// TODO

	}


	//save talent tree
	{

		sprintf(outt, "\r\n#LIST_TALENT_TREE =================================\r\n");
		fwrite(outt, 1, strlen(outt), fout);

		int nbTotalPoint = 0;
		int nbTotalSpells = 0;

		for (unsigned int i = 0; i < sTalentStore.GetNumRows(); ++i)
		{
			TalentEntry const* talentInfo = sTalentStore.LookupEntry(i);

			if (!talentInfo)
				continue;

			TalentTabEntry const* talentTabInfo = sTalentTabStore.LookupEntry(talentInfo->TalentTab);

			if (!talentTabInfo)
				continue;

			if ((m_thisOwner->getClassMask() & talentTabInfo->ClassMask) == 0)
				continue;

			int loc = m_thisOwner->GetSession()->GetSessionDbcLocale();

			int maxRank = -1;



			for (int j = 0; j < MAX_TALENT_RANK; ++j)
			{
				if (talentInfo->RankID[j])
				{
					uint32 spell_id__ = talentInfo->RankID[j];

					bool playerHasSpell = false;

					for (PlayerSpellMap::const_iterator itr = m_thisOwner->m_spells.begin(); itr != m_thisOwner->m_spells.end(); ++itr)
					{
						//SpellEntry const* spellInfo = sSpellStore.LookupEntry(itr->first);
						SpellEntry const* spellInfo___ = sSpellStore.LookupEntry(itr->first);
						if (!spellInfo___)
							continue;

						if (itr->first == spell_id__)
						{
							playerHasSpell = true;
							break;
						}


					}


					if (playerHasSpell)
					{

						maxRank = j;
					}

					int a = 0;
				}
			}

			//  maxRank = 0 veut dire qu'on a mis 1 point dans ce talen

			if (maxRank >= 0)
			{
				uint32 spell_id__ = talentInfo->RankID[maxRank];
				bool passivv = IsPassiveSpell_richa(talentInfo->RankID[maxRank]);

				std::string spellNameStr = "??spellname??";
				SpellEntry const* spellInfo = sSpellStore.LookupEntry(spell_id__);
				if (spellInfo)
				{
					spellNameStr = std::string(spellInfo->SpellName[loc]);
				}
				else
				{
					int erer = 0;
				}

				sprintf(outt, "%d,\"%s\",%d\r\n", spell_id__, spellNameStr.c_str(), maxRank + 1);
				fwrite(outt, 1, strlen(outt), fout);

				nbTotalPoint += maxRank + 1;

				nbTotalSpells++;

			}


		}


		sprintf(outt, "nbTotalTalentPoint,%d\r\n", nbTotalPoint);
		fwrite(outt, 1, strlen(outt), fout);

		sprintf(outt, "nbTotalTalentSpells,%d\r\n", nbTotalSpells);
		fwrite(outt, 1, strlen(outt), fout);


		int nbPointDispo = m_thisOwner->getLevel() - 9;
		if (nbPointDispo < 0) { nbPointDispo = 0; }

		// a titre indicatif, on dit le nombdre de point qu'il doit rester logiquement au joueur
		// celui ci peut etre faux, pour les GM par exemple
		int nbPointUnspent = nbPointDispo - nbTotalPoint;
		sprintf(outt, "pointUnspentShouldBe,%d\r\n", nbPointUnspent);
		fwrite(outt, 1, strlen(outt), fout);

	}


	/*
	//!  ASUP   !!!!!!
	//save explored areas
	{
		int loc = GetSession()->GetSessionDbcLocale();
		int nbAreaExplored = 0;
		//int nbAreaTotal = 0;
		sprintf(outt, "\r\n#LIST_EXPLORED_AREAS =================================\r\n");
		fwrite(outt, 1, strlen(outt), fout);
		int generalVisitID = 0;
		for (uint32 i = 0; i < PLAYER_EXPLORED_ZONES_SIZE; ++i) // string
		{
			const uint32 explorred = GetUInt32Value(PLAYER_EXPLORED_ZONES_1 + i) ;
			for(int areaFlag=0; areaFlag<32; areaFlag++)
			{
				uint32 val = (uint32)(1 << (areaFlag % 32));
				//uint32 mappId = GetMapId();
				if ( explorred & val )
				{

					bool areaFound = false;
					uint32 areaFound_mapID = 0;
					std::string areaName = "?????";
					AreaTableEntry const* aEntry = nullptr;
					for (uint32 i = 0; i <= sAreaStore.GetNumRows(); i++)
					{
						//if (area_flag != 0)
						{
							if (AreaTableEntry const* AreaEntry = sAreaStore.LookupEntry(i))
							{
								//if (AreaEntry->exploreFlag == area_flag)
								{
									// area_flag found but it lets test map_id too
									//if (AreaEntry->mapid == map_id)
									uint32 mapID =  AreaEntry->mapid;
									AreaTableEntry const* p = GetAreaEntryByAreaFlagAndMap(generalVisitID, mapID);
									if ( p != 0 )
									{
										areaFound = true;
										areaFound_mapID = mapID;
										areaName = std::string( p->area_name[loc] );
										break;
									}
									int aaaaa=0;
								}
							}
						}
					}

					if ( !areaFound )
					{
						//erreur etrange ????
						areaName = "??errorr???";
						int a=0;
					}
					else
					{

					}
					sprintf(outt, "%d,%d,%d,\"%s\"\r\n",  areaFound_mapID ,  i, areaFlag ,  areaName.c_str()  );
					fwrite(outt, 1, strlen(outt), fout);
					nbAreaExplored++;

				}
				generalVisitID++;
			}
			int a=0;
		}
		sprintf(outt, "nbAreaVisited,%d\r\n", nbAreaExplored);
		fwrite(outt, 1, strlen(outt), fout);
		//sprintf(outt, "nbAreaTotal,%d\r\n", nbAreaTotal);
		//fwrite(outt, 1, strlen(outt), fout);
	}
	*/


	//save list GRYPHONS KNOWN
	{
		sprintf(outt, "\r\n#LIST_GRYPHON_NAMES =================================\r\n");
		fwrite(outt, 1, strlen(outt), fout);


		// COUNTER
		{
			int nb = 0;

			for (int iNode = 1; iNode < TaxiMaskSize * 32; iNode++)
			{
				bool knownnn = m_thisOwner->m_taxi.IsTaximaskNodeKnown(iNode);
				if (knownnn)
				{

					nb++;
				}
			}

			sprintf(outt, "Counter,%d\r\n", nb);
			fwrite(outt, 1, strlen(outt), fout);
		}




		//sprintf(outt, "GryphonListNames,");
		//fwrite(outt, 1, strlen(outt), fout);
		for (int iNode = 1; iNode < TaxiMaskSize * 32; iNode++)
		{
			bool knownnn = m_thisOwner->m_taxi.IsTaximaskNodeKnown(iNode);
			if (knownnn)
			{

				std::string taxiiName = "?ERROR?";

				if (iNode < sTaxiNodesStore.GetNumRows())
				{
					TaxiNodesEntry const* nodeEntry = sTaxiNodesStore.LookupEntry(iNode);
					if (nodeEntry)
					{
						int loc = m_thisOwner->GetSession()->GetSessionDbcLocale();
						taxiiName = nodeEntry->name[loc];
					}
					else
					{
						taxiiName = "?ERROR?";
						int aa = 0; // error ????
					}
				}

				sprintf(outt, "%d,\"%s\"\r\n", iNode, taxiiName.c_str());
				fwrite(outt, 1, strlen(outt), fout);
			}
		}
		sprintf(outt, "\r\n");
		fwrite(outt, 1, strlen(outt), fout);
	}




	{

		sprintf(outt, "\r\n#LIST_EXPLORED_AREAS_2 =================================\r\n");
		fwrite(outt, 1, strlen(outt), fout);

		int nbAreaExplored = 0;
		int nbAreaTotal = 0;



		std::map<std::string, std::vector<MAP_SECONDA>  > mapsList;
		Richard_GetListExplored(mapsList, nbAreaExplored, nbAreaTotal);

		sprintf(outt, "nbAreaVisited,%d\r\n", nbAreaExplored);
		fwrite(outt, 1, strlen(outt), fout);
		sprintf(outt, "nbAreaTotal,%d\r\n", nbAreaTotal);
		fwrite(outt, 1, strlen(outt), fout);


		for (const auto& elemI : mapsList)
		{
			for (const auto& elemJ : elemI.second)
			{
				sprintf(outt, "\"%s\",\"%s\",%d\r\n", elemI.first.c_str(), elemJ.name.c_str(), elemJ.explored);
				fwrite(outt, 1, strlen(outt), fout);
			}
		}
		sprintf(outt, "\r\n");
		fwrite(outt, 1, strlen(outt), fout);


	}

	/*
	{
		sprintf(outt, "\r\n#ELITE_GRIS_TUES_COMMUN =================================\r\n");
		fwrite(outt, 1, strlen(outt), fout);
		sprintf(outt, "0\r\n"); // NOT USED ANYMORE
		fwrite(outt, 1, strlen(outt), fout);
		sprintf(outt, "\r\n");
		fwrite(outt, 1, strlen(outt), fout);
	}
	*/


	{

		sprintf(outt, "\r\n#LIST_NPC_KILLED =================================\r\n");
		fwrite(outt, 1, strlen(outt), fout);

		sprintf(outt, "Counter,%d\r\n", m_richa_NpcKilled.size());
		fwrite(outt, 1, strlen(outt), fout);

		for (int i = 0; i < m_richa_NpcKilled.size(); i++)
		{
			sprintf(outt, "%d,%d\r\n", m_richa_NpcKilled[i].npc_id, m_richa_NpcKilled[i].nb_killed);
			fwrite(outt, 1, strlen(outt), fout);
		}

		sprintf(outt, "\r\n");
		fwrite(outt, 1, strlen(outt), fout);
	}

	{

		sprintf(outt, "\r\n#LIST_PAGE_DISCOVERED =================================\r\n");
		fwrite(outt, 1, strlen(outt), fout);

		sprintf(outt, "Counter,%d\r\n", m_richa_pageDiscovered.size());
		fwrite(outt, 1, strlen(outt), fout);

		for (int i = 0; i < m_richa_pageDiscovered.size(); i++)
		{
			sprintf(outt, "%d,%d,%d,%d\r\n", m_richa_pageDiscovered[i].pageId, m_richa_pageDiscovered[i].objectID, m_richa_pageDiscovered[i].itemID, 0);
			fwrite(outt, 1, strlen(outt), fout);
		}

		sprintf(outt, "\r\n");
		fwrite(outt, 1, strlen(outt), fout);
	}

	{

		sprintf(outt, "\r\n#LIST_LUNARFESTIVAL_ELDERFOUND =================================\r\n");
		fwrite(outt, 1, strlen(outt), fout);

		sprintf(outt, "Counter,%d\r\n", m_richa_lunerFestivalElderFound.size());
		fwrite(outt, 1, strlen(outt), fout);

		for (int i = 0; i < m_richa_lunerFestivalElderFound.size(); i++)
		{
			sprintf(outt, "%d,%d\r\n", m_richa_lunerFestivalElderFound[i].year, m_richa_lunerFestivalElderFound[i].questId);
			fwrite(outt, 1, strlen(outt), fout);
		}

		sprintf(outt, "\r\n");
		fwrite(outt, 1, strlen(outt), fout);
	}

	{


		sprintf(outt, "\r\n#LIST_MAISON_TAVERN =================================\r\n");
		fwrite(outt, 1, strlen(outt), fout);

		sprintf(outt, "Counter,%d\r\n", m_richa_ListeMaison.size());
		fwrite(outt, 1, strlen(outt), fout);

		for (int i = 0; i < m_richa_ListeMaison.size(); i++)
		{
			//AreaTableEntry const* zoneEntry = GetAreaEntryByAreaID(zone_id);
			//AreaTableEntry const* areaEntry = GetAreaEntryByAreaID(m_richa_ListeMaison[i].areaid);
			AreaTableEntry const* areaEntry = sAreaTableStore.LookupEntry(m_richa_ListeMaison[i].areaid);

			sprintf(outt, "%d,%d,%s\r\n", m_richa_ListeMaison[i].mapid, m_richa_ListeMaison[i].areaid, areaEntry ? areaEntry->area_name[richa_language] : "unknown");
			fwrite(outt, 1, strlen(outt), fout);
		}

		sprintf(outt, "\r\n");
		fwrite(outt, 1, strlen(outt), fout);




	}

	{


		sprintf(outt, "\r\n#LIST_ITEM_LOOT_QUEST =================================\r\n");
		fwrite(outt, 1, strlen(outt), fout);

		sprintf(outt, "Counter,%d\r\n", m_richa_itemLootQuests.size());
		fwrite(outt, 1, strlen(outt), fout);

		for (int i = 0; i < m_richa_itemLootQuests.size(); i++)
		{
			sprintf(outt, "%d,%d,%f,%d,%d\r\n",
				m_richa_itemLootQuests[i].active,
				m_richa_itemLootQuests[i].itemid,
				m_richa_itemLootQuests[i].currentScore,
				m_richa_itemLootQuests[i].nbFoisQueteDone,
				m_richa_itemLootQuests[i].LoopQuest
			);
			fwrite(outt, 1, strlen(outt), fout);
		}

		sprintf(outt, "\r\n");
		fwrite(outt, 1, strlen(outt), fout);




	}


	for (uint8 iDiffic = 0; iDiffic < MAX_DIFFICULTY; ++iDiffic)
	{
		sprintf(outt, "\r\n#LIST_INSTANCES_SAVES_DIFF%d =================================\r\n", iDiffic);
		fwrite(outt, 1, strlen(outt), fout);

		Player* player = m_thisOwner;
		if (!player) player = m_thisOwner->m_session->GetPlayer();
		uint32 counter = 0;

		BoundInstancesMap const& binds = sInstanceSaveMgr->PlayerGetBoundInstances(m_thisOwner->GetGUIDLow(), Difficulty(iDiffic));
		for (BoundInstancesMap::const_iterator itr = binds.begin(); itr != binds.end(); ++itr)
		{

			//InstancePlayerBind seccc = itr->second;
			/*
			DungeonPersistentState* state = itr->second.state;
			std::string timeleft = secsToTimeString(state->GetResetTime() - time(nullptr), true);
			if (const MapEntry* entry = sMapStore.LookupEntry(itr->first))
			{
				sprintf(outt, "map: %d (%s) inst: %d perm: %s canReset: %s TTR: %s\r\n",
					itr->first, entry->name[richa_language], state->GetInstanceId(), itr->second.perm ? "yes" : "no",
					state->CanReset() ? "yes" : "no", timeleft.c_str());
				fwrite(outt, 1, strlen(outt), fout);
			}
			else
			{
				sprintf(outt, "bound for a nonexistent map %u\r\n", itr->first);
				fwrite(outt, 1, strlen(outt), fout);
			}
			*/

			InstanceSave* save = itr->second.save;
			uint32 resetTime = itr->second.extended ? save->GetExtendedResetTime() : save->GetResetTime();
			uint32 ttr = (resetTime >= time(nullptr) ? resetTime - time(nullptr) : 0);
			std::string timeleft = GetTimeString_richa(ttr);
			sprintf(outt, "map: %d, inst: %d, perm: %s, diff: %d, canReset: %s, TTR: %s%s", itr->first, save->GetInstanceId(), itr->second.perm ? "yes" : "no", save->GetDifficulty(), save->CanReset() ? "yes" : "no", timeleft.c_str(), (itr->second.extended ? " (extended)" : ""));
			fwrite(outt, 1, strlen(outt), fout);

			counter++;
		}

		sprintf(outt, "player binds: %d\r\n", counter);
		fwrite(outt, 1, strlen(outt), fout);

		/*
		counter = 0;
		if (Group* group = player->GetGroup())
		{
		   
			Group::BoundInstancesMap& binds = group->GetBoundInstances(Difficulty(iDiffic));
			for (Group::BoundInstancesMap::const_iterator itr = binds.begin(); itr != binds.end(); ++itr)
			{
				DungeonPersistentState* state = itr->second.state;
				std::string timeleft = secsToTimeString(state->GetResetTime() - time(nullptr), true);

				if (const MapEntry* entry = sMapStore.LookupEntry(itr->first))
				{
					sprintf(outt, "map: %d (%s) inst: %d perm: %s canReset: %s TTR: %s\r\n",
						itr->first, entry->name[richa_language], state->GetInstanceId(), itr->second.perm ? "yes" : "no",
						state->CanReset() ? "yes" : "no", timeleft.c_str());
					fwrite(outt, 1, strlen(outt), fout);
				}
				else
				{
					sprintf(outt, "bound for a nonexistent map %u\r\n", itr->first);
					fwrite(outt, 1, strlen(outt), fout);
				}
				counter++;
			}
		}
		sprintf(outt, "group binds: %d\r\n", counter);
		fwrite(outt, 1, strlen(outt), fout);
		*/


	}


	{
		sprintf(outt, "\r\n#LES_CONSTANTES =================================\r\n");
		fwrite(outt, 1, strlen(outt), fout);


		sprintf(outt, "name,%s\r\n", m_thisOwner->GetName());
		fwrite(outt, 1, strlen(outt), fout);

		uint8 race = m_thisOwner->getRace();
		std::string raceStr = "?race?";
		if (race == RACE_HUMAN) { raceStr = "HUMAN"; }
		if (race == RACE_ORC) { raceStr = "ORC"; }
		if (race == RACE_DWARF) { raceStr = "DWARF"; }
		if (race == RACE_NIGHTELF) { raceStr = "NIGHTELF"; }
		if (race == RACE_UNDEAD_PLAYER) { raceStr = "UNDEAD"; }
		if (race == RACE_TAUREN) { raceStr = "TAUREN"; }
		if (race == RACE_GNOME) { raceStr = "GNOME"; }
		if (race == RACE_TROLL) { raceStr = "TROLL"; }
		if (race == RACE_BLOODELF) { raceStr = "BLOODELF"; }
		if (race == RACE_DRAENEI) { raceStr = "DRAENEI"; }
		sprintf(outt, "race,%s\r\n", raceStr.c_str());
		fwrite(outt, 1, strlen(outt), fout);


		uint8 classe = m_thisOwner->getClass();
		std::string classeStr = "?class?";
		if (classe == CLASS_WARRIOR) { classeStr = "WARRIOR"; }
		if (classe == CLASS_PALADIN) { classeStr = "PALADIN"; }
		if (classe == CLASS_HUNTER) { classeStr = "HUNTER"; }
		if (classe == CLASS_ROGUE) { classeStr = "ROGUE"; }
		if (classe == CLASS_PRIEST) { classeStr = "PRIEST"; }
		if (classe == CLASS_SHAMAN) { classeStr = "SHAMAN"; }
		if (classe == CLASS_MAGE) { classeStr = "MAGE"; }
		if (classe == CLASS_WARLOCK) { classeStr = "WARLOCK"; }
		if (classe == CLASS_DRUID) { classeStr = "DRUID"; }
		if (classe == CLASS_DEATH_KNIGHT) { classeStr = "DEATH_KNIGHT"; }
		sprintf(outt, "class,%s\r\n", classeStr.c_str());
		fwrite(outt, 1, strlen(outt), fout);


		uint8 gendere = m_thisOwner->getGender();
		std::string gendereStr = "?gendere?";
		if (gendere == GENDER_FEMALE) { gendereStr = "FEMALE"; }
		if (gendere == GENDER_MALE) { gendereStr = "MALE"; }
		if (gendere == GENDER_NONE) { gendereStr = "NONE"; }
		sprintf(outt, "gender,%s\r\n", gendereStr.c_str());
		fwrite(outt, 1, strlen(outt), fout);


		uint8 skin = m_thisOwner->GetByteValue(PLAYER_BYTES, 0);
		uint8 face = m_thisOwner->GetByteValue(PLAYER_BYTES, 1);
		uint8 hairstyle = m_thisOwner->GetByteValue(PLAYER_BYTES, 2);
		uint8 haircolor = m_thisOwner->GetByteValue(PLAYER_BYTES, 3);
		uint8 facialhair = m_thisOwner->GetByteValue(PLAYER_BYTES_2, 0);

		sprintf(outt, "apparence_skin,%d\r\n", skin);
		fwrite(outt, 1, strlen(outt), fout);
		sprintf(outt, "apparence_face,%d\r\n", face);
		fwrite(outt, 1, strlen(outt), fout);
		sprintf(outt, "apparence_hairstyle,%d\r\n", hairstyle);
		fwrite(outt, 1, strlen(outt), fout);
		sprintf(outt, "apparence_haircolor,%d\r\n", haircolor);
		fwrite(outt, 1, strlen(outt), fout);
		sprintf(outt, "apparence_facialhair,%d\r\n", facialhair);
		fwrite(outt, 1, strlen(outt), fout);



	}




	{
		sprintf(outt, "\r\n#GUILD =================================\r\n");
		fwrite(outt, 1, strlen(outt), fout);

		uint64_t playerguid = m_thisOwner->GetGUID();

		Guild* guild = sGuildMgr->GetGuildById(m_thisOwner->GetGuildId());
		

		if (guild != nullptr)
		{
			sprintf(outt, "guildid,%d\r\n", guild->GetId());
			fwrite(outt, 1, strlen(outt), fout);


			sprintf(outt, "guildname,%s\r\n", guild->GetName().c_str());
			fwrite(outt, 1, strlen(outt), fout);

			/*
			int32 rankInGuild = guild->GetRank(playerguid);
			sprintf(outt, "rankInGuild,%d\r\n", rankInGuild);
			fwrite(outt, 1, strlen(outt), fout);

			uint32 guildBorderColor = guild->GetBorderColor();
			sprintf(outt, "guildBorderColor,%d\r\n", guildBorderColor);
			fwrite(outt, 1, strlen(outt), fout);

			uint32 guildEmblemStyle = guild->GetEmblemStyle();
			sprintf(outt, "guildEmblemStyle,%d\r\n", guildEmblemStyle);
			fwrite(outt, 1, strlen(outt), fout);

			uint32 guildEmblemColor = guild->GetEmblemColor();
			sprintf(outt, "guildEmblemColor,%d\r\n", guildEmblemColor);
			fwrite(outt, 1, strlen(outt), fout);

			uint32 guildBorderStyle = guild->GetBorderStyle();
			sprintf(outt, "guildBorderStyle,%d\r\n", guildBorderStyle);
			fwrite(outt, 1, strlen(outt), fout);

			uint32 guildBackgroundColor = guild->GetBackgroundColor();
			sprintf(outt, "guildBackgroundColor,%d\r\n", guildBackgroundColor);
			fwrite(outt, 1, strlen(outt), fout);
			*/

		 
		}
		else
		{
			sprintf(outt, "NO_GUILD\r\n");
			fwrite(outt, 1, strlen(outt), fout);
		}

	}





	sprintf(outt, "\r\n#END_OF_FILE =================================\r\n");
	fwrite(outt, 1, strlen(outt), fout);


	fclose(fout);
	fout = NULL;


	// pour faciliter le debug, je vais copier coller le fichier quotidien dans des fichiers qui vont tout garder
	// du coup je pourrai me permettre de regulierement effacer l'interieur du dossier TEMP qui va grossir vite
	char nameFile2[2048];
	sprintf(nameFile2, "RICHARDS_WOTLK/TEMP/_ri_stat_%s_%d_%02d_%02d_%02d_%02d_%02d.txt",
		playerName,
		now->tm_year + 1900,
		now->tm_mon + 1,
		now->tm_mday,
		now->tm_hour,
		now->tm_min,
		now->tm_sec
	);
	BOOL succesCopy = CopyFileA(nameFile, nameFile2, TRUE);
	if (!succesCopy)
	{
		DWORD laster = GetLastError();

		sLog->outBasic("WARNING FAIL COPY FILE (GetLastError = %d) (on va retry avec nouveau nom) !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!", laster);
		sLog->outBasic("	nameFile = %s", nameFile);
		sLog->outBasic("	nameFile2 = %s", nameFile2);
		//Sleep(20000);

		//c'est deja arrive je sais pas pk, j'ai rajoute getlasterror.
		//
		//
		//en fait je me demande si c'est pas juste si par hasard je me deco a la meme seconde du save auto.
		//du coup ca va fail car meme file name
		//du coup je regenere un nouveau nom, avec +1 seconde
		sprintf(nameFile2, "RICHARDS_WOTLK/TEMP/_ri_stat_%s_%d_%02d_%02d_%02d_%02d_%02d.txt",
			playerName,
			now->tm_year + 1900,
			now->tm_mon + 1,
			now->tm_mday,
			now->tm_hour,
			now->tm_min,
			now->tm_sec + 1
		);


		//on va reessayer avec le nouveau nom...
		BOOL succesCopy2 = CopyFileA(nameFile, nameFile2, TRUE);
		if (succesCopy2)
		{
			sLog->outBasic("try 2 - ca a marche .");
			sLog->outBasic("	nameFile = %s", nameFile);
			sLog->outBasic("	nameFile2 = %s", nameFile2);
			int aaa = 0;
		}
		else
		{
			DWORD laster2 = GetLastError();
			sLog->outBasic("try 2 - ca a PAS marche (GetLastError = %d) !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!", laster2);
			sLog->outBasic("	nameFile = %s", nameFile);
			sLog->outBasic("	nameFile2 = %s", nameFile2);

			Sleep(20000);

			int aaa = 0;
		}

	}

}




void PlayerModeDataRicha::Richard_InformDiscoveredNewArea(int areaFlag)
{

	std::map<std::string, std::vector<MAP_SECONDA>  > mapsList;
	int nbAreaExplored = 0;
	int nbAreaTotal = 0;
	Richard_GetListExplored(mapsList, nbAreaExplored, nbAreaTotal);


	//on recherche l'area flag :
	bool areaFound = false;
	for (const auto& elemI : mapsList)
	{
		for (const auto& elemJ : elemI.second)
		{
			elemI.first.c_str();
			elemJ.name.c_str();
			elemJ.explored;


			if (elemJ.areaFlag__ == areaFlag)
			{
				areaFound = true;

				int nbSubZone = 0;
				int nbSubDiscovered = 0;

				if (elemI.first == "AAA__ROOT_0")
				{
					nbSubZone = 1;
					nbSubDiscovered = 1;
				}
				else
				{

					for (const auto& elemK : elemI.second)
					{
						if (elemK.explored) { nbSubDiscovered++; }
						nbSubZone++;
					}
				}

				sLog->outBasic("RICHAR:  %s has discovered new : %s,%s  score=%d/%d ", m_thisOwner->GetName(), elemI.first.c_str(), elemJ.name.c_str(), nbSubDiscovered, nbSubZone);

				char messageOut[2048];
				sprintf(messageOut, "Decouverte zone (%d/%d)", nbSubDiscovered, nbSubZone);
				m_thisOwner->Say(messageOut, LANG_UNIVERSAL);


				//pour l'instan je cache
				//Say("INFO", LANG_UNIVERSAL);


				break;
			}

		}

		if (areaFound) { break; }
	}

}




uint32 PlayerModeDataRicha::richard_countItem(uint32 item, bool inBankAlso, bool inEquipmentAlso, bool inKeyRingAlso, bool inInventoryAlso) const
{
	//bool inBankAlso = false; // count bank or not
	//bool inEquipmentAlso = false;
	//bool inKeyRingAlso = false;
	//bool inInventoryAlso = true;

	uint32 tempcount = 0;

	if (inEquipmentAlso)
	{
		for (int i = EQUIPMENT_SLOT_START; i < EQUIPMENT_SLOT_END; ++i)
		{
			Item* pItem = m_thisOwner->GetItemByPos(INVENTORY_SLOT_BAG_0, i);
			if (pItem && pItem->GetEntry() == item && !pItem->IsInTrade())
			{
				tempcount += pItem->GetCount();
			}
		}
	}


	if (inKeyRingAlso)
	{
		for (int i = KEYRING_SLOT_START; i < KEYRING_SLOT_END; ++i)
		{
			Item* pItem = m_thisOwner->GetItemByPos(INVENTORY_SLOT_BAG_0, i);
			if (pItem && pItem->GetEntry() == item && !pItem->IsInTrade())
			{
				tempcount += pItem->GetCount();
			}
		}
	}

	if (inInventoryAlso)
	{
		for (int i = INVENTORY_SLOT_BAG_START; i < INVENTORY_SLOT_BAG_END; ++i)
		{
			if (Bag* pBag = (Bag*)m_thisOwner->GetItemByPos(INVENTORY_SLOT_BAG_0, i))
			{
				for (uint32 j = 0; j < pBag->GetBagSize(); ++j)
				{

					Item* pItem = m_thisOwner->GetItemByPos(i, j);

					if (pItem)
					{
						//	sLog->outBasic("RICHAR: item = %d",pItem->GetEntry());
					}
					else
					{
						//	sLog->outBasic("RICHAR: item = nothing");
					}

					if (pItem && pItem->GetEntry() == item && !pItem->IsInTrade())
					{
						tempcount += pItem->GetCount();
					}
				}
			}
		}

		for (int i = INVENTORY_SLOT_ITEM_START; i < INVENTORY_SLOT_ITEM_END; ++i) // les 16 place du packback de default
		{
			Item* pItem = m_thisOwner->GetItemByPos(INVENTORY_SLOT_BAG_0, i);
			if (pItem && pItem->GetEntry() == item && !pItem->IsInTrade())
			{
				tempcount += pItem->GetCount();
			}
		}
	}

	if (inBankAlso)
	{
		for (int i = BANK_SLOT_ITEM_START; i < BANK_SLOT_ITEM_END; ++i)
		{
			Item* pItem = m_thisOwner->GetItemByPos(INVENTORY_SLOT_BAG_0, i);
			if (pItem && pItem->GetEntry() == item && !pItem->IsInTrade())
			{
				tempcount += pItem->GetCount();
			}
		}
		for (int i = BANK_SLOT_BAG_START; i < BANK_SLOT_BAG_END; ++i)
		{
			if (Bag* pBag = (Bag*)m_thisOwner->GetItemByPos(INVENTORY_SLOT_BAG_0, i))
			{
				for (uint32 j = 0; j < pBag->GetBagSize(); ++j)
				{
					Item* pItem = m_thisOwner->GetItemByPos(i, j);
					if (pItem && pItem->GetEntry() == item && !pItem->IsInTrade())
					{
						tempcount += pItem->GetCount();
					}
				}
			}
		}
	}

	//sLog->outBasic("RICHAR: _ %s has %d item id %d", GetName(), tempcount, item);

	return tempcount;
}



void PlayerModeDataRicha::richard_countItem_pokeball(uint32& itemKeyRin0, uint32& quantity) const
{

	itemKeyRin0 = 0;
	quantity = 0;

	Item* pItem = m_thisOwner->GetItemByPos(INVENTORY_SLOT_BAG_0, KEYRING_SLOT_START);
	if (pItem && pItem->GetEntry() && !pItem->IsInTrade())
	{
		if (pItem->GetEntry() >= 100000 && pItem->GetEntry() < 300000)
		{
			itemKeyRin0 = pItem->GetEntry();
			quantity = pItem->GetCount();
		}
	}





	return;
}





///////////////////////////////////////////////
// RICHARD DEBUG INFO :
void PlayerModeDataRicha::Richa_OnCanTakeQuest(Quest const* quest, bool msg) const
{



   bool canTake = !DisableMgr::IsDisabledFor(DISABLE_TYPE_QUEST, quest->GetQuestId(), m_thisOwner)
		&& m_thisOwner->SatisfyQuestStatus(quest, msg) && m_thisOwner->SatisfyQuestExclusiveGroup(quest, msg)
		&& m_thisOwner->SatisfyQuestClass(quest, msg) && m_thisOwner->SatisfyQuestRace(quest, msg) && m_thisOwner->SatisfyQuestLevel(quest, msg)
		&& m_thisOwner->SatisfyQuestSkill(quest, msg) && m_thisOwner->SatisfyQuestReputation(quest, msg)
		&& m_thisOwner->SatisfyQuestPreviousQuest(quest, msg) && m_thisOwner->SatisfyQuestTimed(quest, msg)
		&& m_thisOwner->SatisfyQuestNextChain(quest, msg) && m_thisOwner->SatisfyQuestPrevChain(quest, msg)
		&& m_thisOwner->SatisfyQuestDay(quest, msg) && m_thisOwner->SatisfyQuestWeek(quest, msg)
		&& m_thisOwner->SatisfyQuestMonth(quest, msg) && m_thisOwner->SatisfyQuestSeasonal(quest, msg)
		&& m_thisOwner->SatisfyQuestConditions(quest, msg);

	if (!canTake)
	{
		bool b0 = m_thisOwner->SatisfyQuestStatus(quest, msg);
		bool b1 = m_thisOwner->SatisfyQuestExclusiveGroup(quest, msg);
		bool b2 = m_thisOwner->SatisfyQuestClass(quest, msg);
		bool b3 = m_thisOwner->SatisfyQuestRace(quest, msg);
		bool b4 = m_thisOwner->SatisfyQuestLevel(quest, msg);
		bool b5 = m_thisOwner->SatisfyQuestSkill(quest, msg);
		bool b6 = m_thisOwner->SatisfyQuestReputation(quest, msg);
		bool b7 = m_thisOwner->SatisfyQuestPreviousQuest(quest, msg);
		bool b8 = m_thisOwner->SatisfyQuestTimed(quest, msg);
		bool b9 = m_thisOwner->SatisfyQuestNextChain(quest, msg);
		bool ba = m_thisOwner->SatisfyQuestPrevChain(quest, msg);
		//bool bb = m_thisOwner->quest->IsActive();
		bool bc = m_thisOwner->SatisfyQuestConditions(quest, msg);




		std::string finalMessage;


		finalMessage += "RICHARD: ";
		finalMessage += std::string(m_thisOwner->GetName());
		finalMessage += " can t take quest ";
		finalMessage += std::to_string(quest->GetQuestId());
		finalMessage += " because :";


		//sLog->outBasic("RICHAR: %s can t take quest %d because :", GetName(), quest->GetQuestId());


		if (!b2)
		{
			uint32 reqClass = quest->GetRequiredClasses();
			finalMessage += std::string("-- SatisfyQuestClass, class=");
			finalMessage += std::to_string(reqClass);
			finalMessage += std::string("->");

			//c'est un masque, donc ca peut concerner plusieur class
			if ((reqClass & (1 << (CLASS_MAGE - 1))) != 0) { finalMessage += std::string("MAGE,"); }
			if ((reqClass & (1 << (CLASS_PALADIN - 1))) != 0) { finalMessage += std::string("PALADIN,"); }
			if ((reqClass & (1 << (CLASS_WARRIOR - 1))) != 0) { finalMessage += std::string("WARRIOR,"); }
			if ((reqClass & (1 << (CLASS_HUNTER - 1))) != 0) { finalMessage += std::string("HUNTER,"); }
			if ((reqClass & (1 << (CLASS_ROGUE - 1))) != 0) { finalMessage += std::string("ROGUE,"); }
			if ((reqClass & (1 << (CLASS_PRIEST - 1))) != 0) { finalMessage += std::string("PRIEST,"); }
			if ((reqClass & (1 << (CLASS_SHAMAN - 1))) != 0) { finalMessage += std::string("SHAMAN,"); }
			if ((reqClass & (1 << (CLASS_WARLOCK - 1))) != 0) { finalMessage += std::string("WARLOCK,"); }
			if ((reqClass & (1 << (CLASS_DRUID - 1))) != 0) { finalMessage += std::string("DRUID,"); }
			if ((reqClass & (1 << (CLASS_DEATH_KNIGHT - 1))) != 0) { finalMessage += std::string("DEATH_KNIGHT,"); }



		}
		else if (!b3) { finalMessage += std::string("-- SatisfyQuestRace"); }
		else if (!b4)
		{
			finalMessage += std::string("-- SatisfyQuestLevel(");
			finalMessage += std::to_string(quest->GetMinLevel());
			finalMessage += std::string(")");
		}
		else if (!b5) { finalMessage += std::string("-- SatisfyQuestSkill"); }



		else if (!b0)
		{

			QuestStatusMap::const_iterator itr = m_thisOwner->m_QuestStatus.find(quest->GetQuestId());

			if (itr != m_thisOwner->m_QuestStatus.end() && itr->second.Status != QUEST_STATUS_NONE)
			{
				finalMessage += std::string("-- SatisfyQuestStatus:");

				if (itr->second.Status == QUEST_STATUS_COMPLETE)
				{
					finalMessage += std::string("(complete) ");
				}
				//else if (itr->second.Status == QUEST_STATUS_UNAVAILABLE)
				//{
				//	finalMessage += std::string("(unvailable) ");
				//}
				else if (itr->second.Status == QUEST_STATUS_INCOMPLETE)
				{
					finalMessage += std::string("(incomplete) ");
				}
				else if (itr->second.Status == QUEST_STATUS_FAILED)
				{
					finalMessage += std::string("(failed) ");
				}
				//else if (itr->second.Status == QUEST_STATUS_AVAILABLE)
				//{
				//	finalMessage += std::string("(available?????) "); // ne devrait pas etre utilisé ?????
				//}
				else
				{
					finalMessage += std::string("(???) ");
				}

			}


		}

		else if (!b7)
		{
			//sLog->outBasic("	 b7 - SatisfyQuestPreviousQuest");

			std::string fullmessage = "-- SatisfyQuestPreviousQuest list = ";


			for (Quest::PrevQuests::const_iterator iter = quest->prevQuests.begin(); iter != quest->prevQuests.end(); ++iter)
			{
				uint32 prevId = abs(*iter);
				fullmessage += std::to_string(prevId);
				fullmessage += " ";

			}

			finalMessage += std::string(fullmessage.c_str());

		}

		else if (!b1)
		{
			/*
			std::string fullmessage = "-- SatisfyQuestExclusiveGroup list = ";


			Quest const* qInfo = quest;


			ExclusiveQuestGroupsMapBounds bounds = sObjectMgr->GetExclusiveQuestGroupsMapBounds(qInfo->GetExclusiveGroup());

			MANGOS_ASSERT(bounds.first != bounds.second);		   // must always be found if qInfo->ExclusiveGroup != 0

			for (ExclusiveQuestGroupsMap::const_iterator iter = bounds.first; iter != bounds.second; ++iter)
			{
				uint32 exclude_Id = iter->second;

				// skip checked quest id, only state of other quests in group is interesting
				if (exclude_Id == qInfo->GetQuestId())
					continue;

				QuestStatusMap::const_iterator i_exstatus = m_thisOwner->m_QuestStatus.find(exclude_Id);

				// alternative quest already started or completed
				if (i_exstatus != m_thisOwner->m_QuestStatus.end()
					&&
					(i_exstatus->second.Status == QUEST_STATUS_COMPLETE ||
						i_exstatus->second.Status == QUEST_STATUS_INCOMPLETE))
				{
					//if (msg)
					//	SendCanTakeQuestResponse(INVALIDREASON_DONT_HAVE_REQ);

					fullmessage += std::to_string(exclude_Id);
					fullmessage += " ";
				}
			}


			finalMessage += std::string(fullmessage.c_str());
			*/
			finalMessage += std::string("-- SatisfyQuestExclusiveGroup");
		}


		else if (!b6) { finalMessage += std::string("-- SatisfyQuestReputation"); }

		else if (!b8) { finalMessage += std::string("-- SatisfyQuestTimed"); }
		else if (!b9) { finalMessage += std::string("-- SatisfyQuestNextChain"); }
		else if (!ba) { finalMessage += std::string("-- SatisfyQuestPrevChain"); }
		//else if (!bb) { finalMessage += std::string("-- IsActive"); }

		else if (!bc)
		{
		/*
			uint32 conditionId = quest->GetRequiredCondition();
			const PlayerCondition* condition = sConditionStorage.LookupEntry<PlayerCondition>(conditionId);
			if (condition)
			{
				// todo : afficher le message qui est dans  la databse :  condition.comments.  ca peut pas mal aider
			}
			finalMessage += std::string("-- SatisfyQuestCondition - conditionID=");
			finalMessage += std::to_string(conditionId);
			*/
			finalMessage += std::string("-- SatisfyQuestConditions");
		}

		else
		{
			finalMessage += std::string("-- ERROR UNKONWN REASON ??????????????");
		}


		sLog->outBasic(finalMessage.c_str());


	}
}






std::map<time_t, RichardClass::RICHARD_TRY_LOOT_WANT  > RichardClass::g_wantLoot;


bool RichardClass::RichaHandleLootRandom(Loot* loot, int lootTypeItemOrGold, Player* _player)
{

	// a l'epoque de boulette et bouillot on a mis  2000.  c'etait tres bien, pour 2 corp a corp
	// avec adibou et bouzigouloum , c'est trop court.
	const uint32 g___palier_ms = 15000; // richard

	const uint32 maxDice = 1000; // richard

	std::string DEBUG_TEXT_LOOT = "??";
	if (lootTypeItemOrGold == 1)
	{
		DEBUG_TEXT_LOOT = "LOOT-ITEM";
	}
	if (lootTypeItemOrGold == 2)
	{
		DEBUG_TEXT_LOOT = "LOOT-GOLD";
	}


	//richard : pour eviter d'avantager qqun qui est plus proche du server, tout les auto store loot sont interdit avant X secondes
	/*
	bool lootOrigin_creature = false;
	bool lootOrigin_gameobj = false;
	bool lootOrigin_item = false;
	*/




	//Item* item = GetItemByGuid(guid);
	/*
	LootItemContainer::iterator itr = sLootItemStorage->lootItemStore.find(loot->containerId);
	StoredLootItemList lootItems = itr->second;
	if (lootItems.size() != 1 )
	{
		int a=0;
		return false;
	}
	StoredLootItem firstLooter = lootItems.front();
	//firstLooter.
	*/
	/*
	if (loot->GetLootTarget())
	{
		lootOrigin_creature = loot->GetLootTarget()->GetObjectGuid().IsCreature();
		lootOrigin_gameobj = loot->GetLootTarget()->GetObjectGuid().IsGameObject();
	}
	//lootOrigin_item = loot->item->GetObjectGuid().IsItem();
	*/
	LootType lootType = loot->loot_type;

	// 0   undef
	// 1   creature corpse
	// 2   gameobj
	// 3   item - marche pas
	// 4  skinning
	// 5  pickpocket ( peut etre ouverture d'un item aussi , bug ?)
	int lootOrigin = 0;
	if (lootType == LOOT_CORPSE)
		lootOrigin = 1;
	if (lootType == LOOT_SKINNING)
		lootOrigin = 4;


	/*
	if (lootOrigin_creature && !lootOrigin_gameobj && !lootOrigin_item)
	{
		if (lootType == LOOT_SKINNING)
		{
			lootOrigin = 4;
		}
		else if (lootType == LOOT_CORPSE)
		{
			lootOrigin = 1;
		}
		else
		{
			sLog->outBasic("RICHAR: LOOT - type lootOrigin_creature + ????(%d)", lootType);
			lootOrigin = 0;
			int aa = 0;
		}


		//sLog->outBasic("RICHAR: LOOT - type creature" );

	}
	else if (!lootOrigin_creature && lootOrigin_gameobj && !lootOrigin_item)
	{
		//sLog->outBasic("RICHAR: LOOT - type gameobj" );
		lootOrigin = 2;
	}
	else if (!lootOrigin_creature && !lootOrigin_gameobj  && lootOrigin_item)
	{
		// j'ai pas encore reussi a trouver quand ca vient d'un objet (exemple quand on desanchante)
		//sLog->outBasic("RICHAR: LOOT - type item" ); 
		lootOrigin = 3;
	}
	else
	{
		if (lootType == LOOT_PICKPOCKETING)
		{
			lootOrigin = 5;
		}
		else
		{

			bool isItem = false;
			bool isDynamicObject = false;
			if (loot && loot->GetLootTarget() && loot->GetLootTarget()->GetObjectGuid())
			{
				isItem = loot->GetLootTarget()->GetObjectGuid().IsItem();
				isDynamicObject = loot->GetLootTarget()->GetObjectGuid().IsDynamicObject();
			}
			sLog->outBasic("RICHAR: LOOT - type ??? (object loot?)  -  isItem=%d  isDynamicObject=%d ", isItem, isDynamicObject);
			lootOrigin = 0;
			int aa = 0;
		}
	}
	*/


	uint32 difference = getMSTime() - loot->m_richa.m_richard_timeCreated;

	g_wantLoot[loot->m_richa.m_richard_timeCreated].list[_player].nbFois++;

	Group* groupPlay = _player->GetGroup();
	int nbPLayInGroup = 1;
	if (groupPlay)
	{
		nbPLayInGroup = groupPlay->GetMembersCount();
	}

	if (g_wantLoot[loot->m_richa.m_richard_timeCreated].list[_player].scoreDice == -1) // si le dés n'est pas jeté
	{
		uint32 scorede = urand(2, maxDice);
		const char* playerName = _player->GetName().c_str();

		g_wantLoot[loot->m_richa.m_richard_timeCreated].list[_player].scoreDice = scorede;

		//si le joueur se présente en retard, on lui donne un très mauvais dès
		if (difference >= g___palier_ms)
		{
			g_wantLoot[loot->m_richa.m_richard_timeCreated].list[_player].scoreDice = 1; // 1 correspond au score de retard
		}

		if (!g_wantLoot[loot->m_richa.m_richard_timeCreated].okWinDoneOnThisLoot  // ca sert a rien d'embrouiller les joueurs avec des infos useless - on s'en fou du score quand c'est pour looter un OKWIN
			&& lootOrigin == 1 // on dit le MOI que sur les cadavres
			&& nbPLayInGroup > 1 // on dit MOI que dans un groupe
			)
		{
			char sayMoiMoiMoi[256];
			sprintf_s(sayMoiMoiMoi, "Moi! %d", g_wantLoot[loot->m_richa.m_richard_timeCreated].list[_player].scoreDice);
			_player->Say(sayMoiMoiMoi, LANG_UNIVERSAL);
		}

	}

	if (
		//!g_wantLoot[loot->m_richa.m_richard_timeCreated].okWinDoneOnThisLoot // si un OKWIN a été fait pour ce loot, ---> alors on peut direct aller a l'election du vainqueur  <-- pas besoin de ce check , car maintenant un OKWIN va creer une candidature avec score de 0 pour celui qui a fait le OKWIN
		//&&
		difference < g___palier_ms  // si le temps de présentation est passé ---> alors on peut direct aller a l'election du vainqueur
		&&
		g_wantLoot[loot->m_richa.m_richard_timeCreated].list.size() < nbPLayInGroup  // si on est deja 2 joueurs a se présenter ---> alors on peut direct aller a l'election du vainqueur
		&&
		lootOrigin == 1 // si le loot est pas de type creature ---> alors on peut direct aller a l'election du vainqueur
		&&
		g_wantLoot[loot->m_richa.m_richard_timeCreated].winner == nullptr // si le winner a deja été decidé ---> alors on peut direct aller a l'election du vainqueur

		// .... dans tous les autres cas, on attends d'avoir une de ces condition de respecter, avant d'elir le winner ...

		) // pour rajouter un peu d'aleatoire, le palier est re-tiré au random a chaque fois 
	{
		sLog->outBasic("RICHAR: DEBUG_TEXT_LOOT - REFUSE a %s - %d < %d  (nbCandidat=%d) (group de %d)", _player->GetName().c_str(), difference, g___palier_ms, g_wantLoot[loot->m_richa.m_richard_timeCreated].list.size(), nbPLayInGroup);
		return false;
	}
	else
	{

		//si le gagnant a pas encore été decidé, c'est le moment
		if (g_wantLoot[loot->m_richa.m_richard_timeCreated].winner == nullptr)
		{

			int nbJoueur = g_wantLoot[loot->m_richa.m_richard_timeCreated].list.size();


			if (nbJoueur == 0)
			{
				//je crois que ce cas est pas possible
				sLog->outBasic("RICHAR: DEBUG_TEXT_LOOT - personne a reclame le loot donc on donne direct a %s", _player->GetName());
				g_wantLoot[loot->m_richa.m_richard_timeCreated].winner = _player;
			}
			else
			{
				int bestScoreDice = -1;
				for (auto const &ent1 : g_wantLoot[loot->m_richa.m_richard_timeCreated].list)
				{
					if (ent1.second.scoreDice >= bestScoreDice)
					{
						g_wantLoot[loot->m_richa.m_richard_timeCreated].winner = ent1.first;
						bestScoreDice = ent1.second.scoreDice;
					}
				}

				//si on est dans un groupe et que un seul joueur etait candidat, c'est pas mal
				//de le signaler pour s'assurer que tout le groupe est d'accord qu'il y a des gens qui
				//ne se sont pas présenté aux elections
				if (groupPlay != NULL
					&& nbJoueur < nbPLayInGroup
					&& lootOrigin == 1
					//&& !g_wantLoot[loot->m_richa.m_richard_timeCreated].winnerSaidIWinAlone 
					&& !g_wantLoot[loot->m_richa.m_richard_timeCreated].okWinDoneOnThisLoot // ca sert a rien de /SAY pour looter un okwin
					)
				{
					char messageOut[1024];
					
					if (loot->m_richa.GetCreature())
					{
						sprintf(messageOut, "je gagne seul '%s' !", loot->m_richa.GetCreature()->GetName().c_str());
					}
					else
					{
						sprintf(messageOut, "je gagne seul '????' !");
					}
					

					g_wantLoot[loot->m_richa.m_richard_timeCreated].winner->Say(messageOut, LANG_UNIVERSAL);
					//g_wantLoot[loot->m_richa.m_richard_timeCreated].winnerSaidIWinAlone = true;
				}

				sLog->outBasic("RICHAR: DEBUG_TEXT_LOOT - le joueur qui gagne le loot est %s ", g_wantLoot[loot->m_richa.m_richard_timeCreated].winner->GetName());

			}

		}

		if (lootTypeItemOrGold == 1) // si loot de type item
		{
			if (!g_wantLoot[loot->m_richa.m_richard_timeCreated].messageSentToPlayer_loot)
			{
				if (//loot->GetLootTarget()
					//&&
					lootOrigin == 1  // pour les item, on envoie un message QUE si c'est sur un cadavre qu'on loot ca
					)
				{
					//envoie message a tous les joueurs:
					for (auto const &ent1 : g_wantLoot[loot->m_richa.m_richard_timeCreated].list)
					{
						if (ent1.first == g_wantLoot[loot->m_richa.m_richard_timeCreated].winner)
						{
							char messageOut[1024];
							sprintf(messageOut, "vous gagnez le loot 'objet' (score=%d)", ent1.second.scoreDice);
							if (!g_wantLoot[loot->m_richa.m_richard_timeCreated].okWinDoneOnThisLoot)// ca sert a rien de messager pour looter un okwin
							{
								if (nbPLayInGroup == 1)
								{
									//si on est tout seul dans le group, ca sert a rien d'annoncer au joueur qu'il a gagné le loot
								}
								else
								{
									ChatHandler(ent1.first->GetSession()).PSendSysMessage(messageOut);
								}
							}
						}
						else
						{
							char messageOut[1024];
							sprintf(messageOut, "vous perdez le loot 'objet' (score=%d)", ent1.second.scoreDice);
							if (!g_wantLoot[loot->m_richa.m_richard_timeCreated].okWinDoneOnThisLoot)// ca sert a rien de messager pour looter un okwin
							{
								ChatHandler(ent1.first->GetSession()).PSendSysMessage(messageOut);
							}

						}
					}
				}

				g_wantLoot[loot->m_richa.m_richard_timeCreated].messageSentToPlayer_loot = true;
			}
		}
		if (lootTypeItemOrGold == 2) // si loot de type gold
		{
			if (!g_wantLoot[loot->m_richa.m_richard_timeCreated].messageSentToPlayer_po)
			{
				if (
					//loot->GetLootTarget()
					true
					)
				{
					//envoie message a tous les joueurs:
					for (auto const &ent1 : g_wantLoot[loot->m_richa.m_richard_timeCreated].list)
					{
						if (ent1.first == g_wantLoot[loot->m_richa.m_richard_timeCreated].winner)
						{
							//chuchoter la somme au joueur (car elle est ecrit nul part)
							int goldAmount = loot->gold;
							int nbpo = goldAmount / 10000;
							int nbpa = (goldAmount - nbpo * 10000) / 100;
							int nbpc = (goldAmount - nbpo * 10000 - nbpa * 100);

							char messageOut[1024];
							sprintf(messageOut, "vous gagnez les PO %d-%d-%d (score=%d)", nbpo, nbpa, nbpc, ent1.second.scoreDice);
							if (!g_wantLoot[loot->m_richa.m_richard_timeCreated].okWinDoneOnThisLoot)// ca sert a rien de messager pour looter un okwin
							{
								if (nbPLayInGroup == 1 && lootOrigin == 1)
								{
									// dans le cas spécial d'un cadavre et qu'on est tout seul danbs le groupe, le jeu va deja dire : 
									//"Vous ramassez 6 Argent, 16 Cuivre"
									//donc ca sert a rien de dire en doublon ma phrase.
								}
								else
								{
									ChatHandler(ent1.first->GetSession()).PSendSysMessage(messageOut);
								}
							}
						}
						else
						{
							char messageOut[1024];
							sprintf(messageOut, "vous perdez les PO (score=%d)", ent1.second.scoreDice);
							if (!g_wantLoot[loot->m_richa.m_richard_timeCreated].okWinDoneOnThisLoot)// ca sert a rien de messager pour looter un okwin
							{
								ChatHandler(ent1.first->GetSession()).PSendSysMessage(messageOut);
							}

						}
					}
				}

				g_wantLoot[loot->m_richa.m_richard_timeCreated].messageSentToPlayer_po = true;
			}
		}


		if (_player == g_wantLoot[loot->m_richa.m_richard_timeCreated].winner)
		{
			//sLog->outBasic("RICHAR: DEBUG_TEXT_LOOT - le winner %s prend son loot "  , g_wantLoot[loot->m_richa.m_richard_timeCreated].winner->GetName()   );
		}
		else
		{
			//sLog->outBasic("RICHAR: DEBUG_TEXT_LOOT - REFUSE : le looser %s essaye de prendre loot. "  , _player->GetName()   );
			//pour se faire autoriser un loot, le looser devra demander au winner de faire la commande :  .okwin
			return false;
		}


		//sLog->outBasic("RICHAR: loot accepete a %s - %d < %d", _player->GetName() ,difference, palier  );
	}



	return true;
}


void RichardClass::OnFillLoot(uint32 lootId, LootStore const& store, Player* lootOwner, bool personal, bool noEmptyError, uint16 lootMode, Loot* this___)
{
	this___->m_richa.OnFillLoot();

	LootTemplate const* tab = store.GetLootFor(lootId);


	//setup
	int nbItemTotalInLoot = this___->quest_items.size() + this___->items.size();

	
	if ( this___->m_richa.m_lootItems.size() == 0 && // loot deja rempli
		 this___->m_richa.m_lootItems.size() != nbItemTotalInLoot ) // ancien nombre d'objet ne correspondant pas au nouveau nombre d'objet
	{
		int a=0;
		// cela peut arriver, comme dit dans mon exemple du coffre
	}

	// il vaut mieux clear, et le re-remplir a chaque fois -  si par exemple on ouvre un coffre, on respawn le coffre, et on reloot le coffre,
	//alors je crois que ca sera le meme  Loot*  mais avec des nouveau objets
	this___->m_richa.m_lootItems.clear();
  
	//if ( this___->m_richa.m_lootItems.size() == 0 )
	{
		//si c'est la premiere fois, on init la liste

		for (int i = 0; i < this___->items.size(); i++)
		{
			this___->m_richa.m_lootItems.push_back(this___->items[i]);
		}

		for(int i=0; i< this___->quest_items.size(); i++)
		{
			this___->m_richa.m_lootItems.push_back(  this___->quest_items[i]   );
		}

	}

	


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// DEBUT GROSSE MODIF RICHARD
	//richard : add coin on loot


	// id dans la base de donnée
	const uint32 coinItemID1 = 70010; // YouhaiCoin Paragon
	const uint32 coinItemID2 = 70007; // YouhaiCoin Cadeau



	// on liste tous les joueurs le la team
	bool bugEtrangeDetecte = false;
	std::vector<Player*> playerList;
	if (
		lootOwner &&
		lootOwner->GetGroup() &&
		lootOwner->GetGroup()->GetMembersCount() > 1)
	{
		//si une team
		Group* gr = lootOwner->GetGroup();
		Group::MemberSlotList const& memberList = gr->GetMemberSlots();
		for (const auto& memberItr : memberList)
		{
			Player* looter = ObjectAccessor::FindPlayer(memberItr.guid);
			if (looter)
			{
				playerList.push_back(looter);
			}
			else
			{
				//ce bug arrive tres rarement mais il peut arriver !
				//je sais pas trop comlment le provoquer, c'est peut etre une histoire de deco reco
				//
				// ce bug est arrive une deuxieme fois : Diane avait été déco ( a cause d'une coupure internet )
				//
				sLog->outBasic("RICHAR - BUGGGGGGGGGGGGGGGGGGGGGGGGGGG !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
				bugEtrangeDetecte = true;
			}
		}
	}
	else
	{
		//si pas d'equipe
		if (lootOwner)
		{
			playerList.push_back(lootOwner);
		}
	}

	if (bugEtrangeDetecte)
	{
		if (playerList.size() > 0)
		{
			char messageJoueur[4096];
			sprintf(messageJoueur, "BUG POINTEUR NULL RICHARD DETECTE !!!!!!!!!!!!!!!!!!!!!!!!");
			playerList[0]->Say(messageJoueur, LANG_UNIVERSAL);
		}
	}



	//Gestion de la quete d'objet
	{

		//il y a 2 mode de gameplay possible : 
		//
		// mode_itemCanLoot=false ( mode plus mechant )
		// si l'item a 10% de chance de tomber, alors on est sur que les 9 premier kill ne looteront pas, et le 10ieme donnera l'item
		//
		// mode_itemCanLoot=true  ( mode plus gentil )
		// si l'item a 10% de chance de tomber, alors les 9 premier kill on 10% de chance de looter l'item. 
		// s'il tombe pendant ces 9 kill, la quete est reset
		// s'il tombe pas, on a la garantie de l'avoir au 10ieme
		const bool mode_itemCanLoot = true;

		//on liste tous les item qui sont en cours de quete
		struct ITEM_NEED
		{
			ITEM_NEED()
			{
				statisqueDropOfThisItemOnCurrentNPC = 0.0f;
				nbFound = 0;
				itemDropOnThisLoot = false;
			}

			std::vector<Player*> playerNeedThisItem;//liste des joueurs qui on une quete active de cet item
			std::vector<int> playerNeedThisItem_indexQuest;  // meme taille /  meme ordre  que  playerNeedThisItem - juste pour accelerer -   correspond pour chaque Player de playerNeedThisItem a l'index la la quete dans la propre liste du joueur
			float statisqueDropOfThisItemOnCurrentNPC; // entre 0.0 et 1.0
			unsigned int nbFound; // combien de fois cet item est tombé sur les 'nbTry' creations de loot 
			bool itemDropOnThisLoot; // true si l'item est tombé sur la cadavre reel du mob
		};

		//first is an item ID  -  second is a ITEM_NEED
		std::map<uint32_t, ITEM_NEED> listItemThatPlayersNeed;

		for (int iPLayer = 0; iPLayer < playerList.size(); iPLayer++)
		{
			const std::vector<PlayerModeDataRicha::RICHA_ITEM_LOOT_QUEST>& lit = playerList[iPLayer]->m_richa.m_richa_itemLootQuests;
			for (int iQuest = 0; iQuest < lit.size(); iQuest++)
			{
				if (lit[iQuest].active)
				{
					if (listItemThatPlayersNeed.find(lit[iQuest].itemid) != listItemThatPlayersNeed.end())
					{
						//si un des joueur est deja sur cet item
						listItemThatPlayersNeed[lit[iQuest].itemid].playerNeedThisItem.push_back(playerList[iPLayer]);
						listItemThatPlayersNeed[lit[iQuest].itemid].playerNeedThisItem_indexQuest.push_back(iQuest);
					}
					else
					{
						//si personne n'est sur cet item
						listItemThatPlayersNeed[lit[iQuest].itemid].playerNeedThisItem.push_back(playerList[iPLayer]);
						listItemThatPlayersNeed[lit[iQuest].itemid].playerNeedThisItem_indexQuest.push_back(iQuest);
						listItemThatPlayersNeed[lit[iQuest].itemid].statisqueDropOfThisItemOnCurrentNPC = 0.0f;
						listItemThatPlayersNeed[lit[iQuest].itemid].nbFound = 0;
						listItemThatPlayersNeed[lit[iQuest].itemid].itemDropOnThisLoot = false;
					}
				}
			}
		}


		//deja il suffit qu'un joueur soit sur un item , pour qu'on le retire du loot du mob, s'il etait dans la loot liste. ( si on est en mode mechant )
		for (auto& iItemNeed : listItemThatPlayersNeed)
		{

			//this___->containerId


			for (int i = 0; i < this___->m_richa.m_lootItems.size(); i++)
			{
				if (
				//this___->m_richa.m_lootItems[i] &&
				this___->m_richa.m_lootItems[i].itemid == iItemNeed.first)
				{
					iItemNeed.second.itemDropOnThisLoot = true;

					if (!mode_itemCanLoot) // si mode mechant : on retire l'item
					{
						LootItem ii = this___->m_richa.m_lootItems[i];
						this___->m_richa.m_lootItems.erase(this___->m_richa.m_lootItems.begin() + i);
						//delete ii;

						sLog->outBasic("RICHAR - ITEM QUEST - l objet etait loote mais on le retire.");
					}
					else
					{
						int a = 0;
					}
				}
			}
		}

		// 5000 c'etait trop, on pouvait attendre jusqu'a 1 secondes de pause. (en DEBUG)
		// 1000 quand on sait on voit la pause, mais ca me semble assez subtil
		// je vais mettre 500 pour vraiment que ce soit fluide
		const int nbTry = 500;

		//unsigned int nbFound = 0;

		for (int iTry = 0; iTry < nbTry; iTry++)
		{


			//on cree une version simplifié de Loot, pour accelerer le process des 'nbTry' fabrications de loot
			class Loot_RICHA : public Loot
			{
			public:

				Loot_RICHA() : Loot(0,nullptr)
				{

				}

				void AddItem(LootStoreItem const& item) override
				{
					// NOTE : je ne prends pas en compte le count pour l'instant.

					listItem.push_back(item.itemid);
					//item.mincountOrRef
				}

				//void AddItem(uint32 itemid, uint32 count, uint32 randomSuffix, int32 randomPropertyId) override
				//{
				//	listItem.push_back(itemid);
				//}

				std::vector<uint32_t> listItem;
			};

			Loot_RICHA newLoot;
			//tab->Process(newLoot, lootOwner, store, store.IsRatesAllowed());
			tab->Process(newLoot, store, lootMode, lootOwner);

			for (auto& iItemNeed : listItemThatPlayersNeed)
			{
				for (int i = 0; i < newLoot.listItem.size(); i++)
				{
					if (newLoot.listItem[i] == iItemNeed.first)
					{
						iItemNeed.second.nbFound++;
					}
				}
			}

		}


		struct LIST_QUEST_TO_REMOVE
		{
			Player* player;

			// ca paraitrai bcp plus imple de sauvegarder l'index dans m_richa_itemLootQuests plutot que l'item ID
			// mais je ne le fait pas, car si un meme joueur a plusieur quete a delete dans sa liste, alors il faut gerer le fait que les indices changent a chaque delete.
			int itemID_in____m_richa_itemLootQuests;
			//int index_in___m_richa_itemLootQuests;

			LIST_QUEST_TO_REMOVE()
			{
				player = nullptr;
				itemID_in____m_richa_itemLootQuests = -1;
			}
		};
		std::vector<LIST_QUEST_TO_REMOVE> listQuestToRemove;

		for (auto& iItemNeed : listItemThatPlayersNeed)
		{

			bool itemEnLootCommun = false;
			ItemTemplate const* itemProto = sObjectMgr->GetItemTemplate(iItemNeed.first);
			if (itemProto)
			{
				const unsigned int ITEM_FLAG_MULTI_DROP___ = 0x00000800;
				itemEnLootCommun = (itemProto->Flags & ITEM_FLAG_MULTI_DROP___) != 0;
			}


			// j'ai remarqué que  Richard_lootCommunPourObjDeQuest est assez lent.  si listItemThatPlayersNeed  a genre > 10 objets , ca peut creer un mini lag
			// a 30 objets on voit un vrai bloquage de > 1 seconde
			// donc pour resoudre ca, je fais un petit static moche ici, pour ne chercher que une seule fois.
			static std::map<uint32_t, bool> lootCommunForceParRichard;
			auto& ittt = lootCommunForceParRichard.find(iItemNeed.first);
			if (ittt == lootCommunForceParRichard.end())
			{
				lootCommunForceParRichard[iItemNeed.first] = RichardClass::Richard_lootCommunPourObjDeQuest(iItemNeed.first);
				ittt = lootCommunForceParRichard.find(iItemNeed.first);
			}



			itemEnLootCommun = ittt->second ? true : itemEnLootCommun;




			std::string gagantDebug = "";

			//pour chaque item, on ne choisi que 1 seul joueur a incrémenter le score
			//sauf si objet en loot commun, dans ce cas on donne les points toujours au meme joueur.
			//voir diapo dans H: ou je parle plus préciséments des regle de ces quetes.
			//
			//
			//si item en loot commun, et plusieurs joueurs sont sur la quete, alors on donne toujours au meme joueur
			//ceci va garantir que si un item a 10% de chance de tomber, alors il tombera pour tout le monde au bout de 10 kill
			uint32 indexPlayerChosen = 0;
			if (itemEnLootCommun && iItemNeed.second.playerNeedThisItem.size() > 1)
			{
				// on va dire par exemple qu'on donne toujours au joueur avec le plus petit GUID
				uint32 lowerGUID = 0xFFffFFff;
				int playerIndexChoosen = -1;
				for (int i = 0; i < iItemNeed.second.playerNeedThisItem.size(); i++)
				{
					uint32 guidd = iItemNeed.second.playerNeedThisItem[i]->GetGUIDLow();
					if (guidd < lowerGUID)
					{
						playerIndexChoosen = i;
						lowerGUID = guidd;
					}
				}
				indexPlayerChosen = playerIndexChoosen;
			}
			else
			{
				indexPlayerChosen = uint32(urand(0, iItemNeed.second.playerNeedThisItem.size() - 1));
			}
			Player* winner = iItemNeed.second.playerNeedThisItem[indexPlayerChosen];
			PlayerModeDataRicha::RICHA_ITEM_LOOT_QUEST& quest = winner->m_richa.m_richa_itemLootQuests[iItemNeed.second.playerNeedThisItem_indexQuest[indexPlayerChosen]];

			std::string itemName = "objet inconnu";
			//ItemPrototype const* itemProto = sItemStorage.LookupEntry<ItemPrototype>(  iItemNeed.first  );
			if (itemProto)
			{
				itemName = std::string(itemProto->Name1);
			}

			iItemNeed.second.statisqueDropOfThisItemOnCurrentNPC = (float)iItemNeed.second.nbFound / (float)nbTry;

			//si on est en mode gentil et que l'objet est tombé, alors on reset la quete 


			if (mode_itemCanLoot && iItemNeed.second.itemDropOnThisLoot)
			{
				//for each player on this item quest
				//for(int iPLayer=0; iPLayer<iItemNeed.second.playerNeedThisItem.size(); iPLayer++)
				//
				// en fait on va etre encore plus gentil, et on va reset uniquement la quete de un joueur choisi au hasard.
				// ce joueur sera celui qui remporte ce loot

				{
					//Player* playy = iItemNeed.second.playerNeedThisItem[iPLayer];
					Player* playy = winner;


					//Player::RICHA_ITEM_LOOT_QUEST& quest = playy->m_richa_itemLootQuests[ iItemNeed.second.playerNeedThisItem_indexQuest[iPLayer] ];


					//
					//on cloture la quete :
					//

					if (quest.LoopQuest)
					{
						quest.currentScore = 0.0f;

						// quest.nbFoisQueteDone ++; <-- on va dire qu'on on incrémente pas si la quete est pas reelement faite.. ca change pas grand chose.
					}
					else
					{
						//even if the quest will be removed, more secure to finish it as if it's a loop
						quest.currentScore = 0.0f;
						quest.active = false;

						LIST_QUEST_TO_REMOVE questRem;
						questRem.player = playy;
						questRem.itemID_in____m_richa_itemLootQuests = iItemNeed.first;
						listQuestToRemove.push_back(questRem);
					}







				}

				char messageJoueur[4096];
				sprintf(messageJoueur, "quete termin\xc3\xa9\e avant la fin - %s est pour moi.", itemName.c_str());
				winner->Say(messageJoueur, LANG_UNIVERSAL);



				gagantDebug += "l'objet est tombe naturellement ";
				gagantDebug += "on reset donc la quete de ";
				//gagantDebug += std::to_string( iItemNeed.second.playerNeedThisItem.size() );
				//gagantDebug += "joueurs.";
				gagantDebug += winner->GetName();

			}
			else
			{


				quest.currentScore += iItemNeed.second.statisqueDropOfThisItemOnCurrentNPC;
				if (quest.currentScore >= 1.0) // si le joueur termine sa quete
				{

					if (quest.LoopQuest)
					{
						quest.currentScore -= 1.0f; // on reinit ( en accordant au joueur l'eventuel delta qu'il avait au dessus de 1.0
						if (quest.currentScore >= 1.0f)
						{
							//je pense pas que ce cas devrait arriver, mais on sait jamais.
							//on s'il est toujours au dessus de 1, malgrés mon reset, autant faire un vrai reset a 0
							quest.currentScore = 0.0f;
						}

						quest.nbFoisQueteDone++;
					}
					else
					{
						//even if the quest will be removed, more secure to finish it as if it's a loop
						quest.nbFoisQueteDone++;
						quest.currentScore = 0.0f;
						quest.active = false;

						LIST_QUEST_TO_REMOVE questRem;
						questRem.player = winner;
						//questRem.index_in___m_richa_itemLootQuests = iItemNeed.second.playerNeedThisItem_indexQuest[indexPlayerChosen];
						questRem.itemID_in____m_richa_itemLootQuests = iItemNeed.first;
						listQuestToRemove.push_back(questRem);
					}




					char messageJoueur[4096];
					sprintf(messageJoueur, "quete termin\xc3\xa9\e - %s est pour moi.", itemName.c_str());

					winner->Say(messageJoueur, LANG_UNIVERSAL);

					//d'un coté c'est mieux de le donner direct au joueur
					//de l'autre c'est bcp plus simple de le mettre dans le loot, ca evite d'avoir a gerer les inventaire pleins
					//ca permet aussi de gerer les item en loot commun

					//this___->AddItem(iItemNeed.first, 1, 0, 0); <-- version CMANGOS
					this___->m_richa.AddItem_ri(iItemNeed.first);


					

					gagantDebug = "Gagnant=";
					gagantDebug += std::string(winner->GetName());
				}

			}

			if (iItemNeed.second.statisqueDropOfThisItemOnCurrentNPC > 0.0f) // on va affichier que les item que ce NPC peut looter
			{
				// si besoin : printf pour debug
				sLog->outBasic("RICHAR - ITEM QUEST : probability item=%d  :  %f/100  %s",
					iItemNeed.first,
					iItemNeed.second.statisqueDropOfThisItemOnCurrentNPC * 100.0f,
					gagantDebug.c_str());
			}


		}




		// a la toute fin de cette etape, on retire les eventuelles quete d'item qui doivent etre retiré
		// ( c'est mieux de ne rien deplacer/retirer les elements de  m_richa_itemLootQuests	 avant de fin de l'etape de gestion des quete d'item )
		for (int i = 0; i < listQuestToRemove.size(); i++)
		{
			Player* player__ = listQuestToRemove[i].player;

			//search the itemID
			int index = -1;
			for (int j = 0; j < player__->m_richa.m_richa_itemLootQuests.size(); j++)
			{
				if (player__->m_richa.m_richa_itemLootQuests[j].itemid == listQuestToRemove[i].itemID_in____m_richa_itemLootQuests)
				{
					index = j;
					break;
				}
			}

			if (index == -1)
			{
				// ERREUR
				player__->Say("ERROR MQH2 !!!!!!", LANG_UNIVERSAL);
			}
			else
			{

				player__->m_richa.m_richa_itemLootQuests.erase(player__->m_richa.m_richa_itemLootQuests.begin() + index);
			}
		}


	} // FIN de - Gestion de la quete d'objet










	
	//bool lootOrigin_creature = false;
	//bool lootOrigin_gameobj = false;
	//bool lootOrigin_item = false;
	//if ( GetLootTarget() )
	//{
	//	lootOrigin_creature = GetLootTarget()->GetObjectGuid().IsCreature();
	//	lootOrigin_gameobj = GetLootTarget()->GetObjectGuid().IsGameObject();
	//}
	////lootOrigin_item = loot->item->GetObjectGuid().IsItem();
	

	// 0 unknown
	// 1 creature cadavre loot classic
	// 2 gameobjet
	// 3 item
	// 4 depecage
	int lootOrigin = 0;



	if (strcmp(store.GetName(), "creature_loot_template") == 0)
	{
		lootOrigin = 1;
	}
	else if (strcmp(store.GetName(), "disenchant_loot_template") == 0)
	{
		int aaa = 0;
	}
	else if (strcmp(store.GetName(), "fishing_loot_template") == 0)
	{
		int aaa = 0;
	}
	else if (strcmp(store.GetName(), "gameobject_loot_template") == 0)
	{
		lootOrigin = 2;
	}
	else if (strcmp(store.GetName(), "item_loot_template") == 0)
	{
		lootOrigin = 3;
	}
	else if (strcmp(store.GetName(), "pickpocketing_loot_template") == 0)
	{
		int aaa = 0;
	}
	else if (strcmp(store.GetName(), "skinning_loot_template") == 0)
	{
		lootOrigin = 4;
	}
	else if (strcmp(store.GetName(), "mail_loot_template") == 0)
	{
		int aaa = 0;
	}
	else
	{
		int aa = 0;
		sLog->outBasic("RICHAR: ERRRROR !!!!!!!!!!!!!!!!   unkonwn type loot  = '%s'", store.GetName());

	}



	
	//if ( lootOrigin_creature && !lootOrigin_gameobj && !lootOrigin_item )
	//{
	//	Creature* creature__ = GetLootTarget()->GetMap()->GetCreature(  GetLootTarget()->GetObjectGuid()  );
	//	CreatureInfo const* creatureInfo = creature__->GetCreatureInfo();
	//	if ( creatureInfo->SkinningLootId == loot_id )
	//	{
	//		lootOrigin = 4;
	//	}
	//	else
	//	{
	//		//sLog.outBasic("RICHAR: LOOT - type creature" );
	//		lootOrigin = 1;
	//	}

	//}
	//else if ( !lootOrigin_creature && lootOrigin_gameobj  && !lootOrigin_item )
	//{
	//	//sLog.outBasic("RICHAR: LOOT - type gameobj" );
	//	lootOrigin = 2;
	//}
	//else if ( !lootOrigin_creature && !lootOrigin_gameobj  && lootOrigin_item )
	//{
	//	// j'ai pas encore reussi a trouver quand ca vient d'un objet (exemple quand on desanchante)
	//	//sLog.outBasic("RICHAR: LOOT - type item" );
	//	lootOrigin = 3;
	//}
	//else
	//{
	//	//sLog.outBasic("RICHAR: LOOT - type ???" );
	//	int aa=0;
	//}
	


	// parametre richard01_test est la source :  0=unknown   1=cadavre	2=coffre (TODO ?)
	//
	// parametre richard02_test :
	// si cadavre alors correspond au niveau du cadavre  (Negatif si la creature est elite)
	//

	int32 richard01_test = 0;
	int32 richard02_test = 0;

	Creature* creatureLooting = 0;

	if (lootOrigin == 1) // creature
	{

		creatureLooting = this___->m_richa.GetCreature(); //   GetLootTarget()->GetMap()->GetCreature(GetLootTarget()->GetObjectGuid());
		richard02_test = creatureLooting->getLevel();
		if (creatureLooting->isElite())
		{
			richard02_test = -richard02_test;
		}

		richard01_test = 1;

	}
	else if (lootOrigin == 2) // game object  (genre : coffre)
	{
		GameObject* goLooting = this___->m_richa.GetGameObject();  // GetLootTarget()->GetMap()->GetGameObject(GetLootTarget()->GetObjectGuid());
		//const char* nameGo = goLooting->GetName();

		if (goLooting)
		{
			GameObjectTemplate const* goinfo = goLooting->GetGOInfo();

			if (goinfo)
			{

				const char* nameGo = goinfo->name.c_str();

				//  RICHARD_LOOT_COFFRE

				// comme les Elite gris :
				//
				// 1PA si notre perso est niveau  >=1  et  <10   
				// 10PA si notre perso est niveau  >=10  et  <20   
				// 50PA si notre perso est niveau  >=20  et  <30 
				// 1PO si notre perso est niveau  >=30  et  <40 
				// 2PO si notre perso est niveau  >=40  et  <50 
				// 4PO si notre perso est niveau  >=50  et  <60 
				// 5PO pour 60

				if (
					nameGo
					&&
					(

						//maintenanir la meme liste en ici et  _______richard_ALL.txt
						// il doit y avoir 37 coffres de ces 9 types  dans tous wowhainy
						strcmp(nameGo, "Solid Chest") == 0 || strcmp(nameGo, "Coffre solide") == 0
						|| strcmp(nameGo, "Battered Chest") == 0 || strcmp(nameGo, "Coffre endommag\xc3\xa9") == 0
						|| strcmp(nameGo, "Locked Chest") == 0 || strcmp(nameGo, "Coffre verrouill\xc3\xa9") == 0
						|| strcmp(nameGo, "Large Solid Chest") == 0 || strcmp(nameGo, "Grand coffre solide") == 0
						|| strcmp(nameGo, "Large Mithril Bound Chest") == 0 || strcmp(nameGo, "Grand coffre cercl\xc3\xa9 de mithril") == 0
						|| strcmp(nameGo, "Large Iron Bound Chest") == 0 || strcmp(nameGo, "Grand coffre cercl\xc3\xa9 de fer") == 0
						|| strcmp(nameGo, "Ancient Treasure") == 0 || strcmp(nameGo, "Tr\xc3\xa9sor ancien") == 0
						|| strcmp(nameGo, "Witch Doctor\'s Chest") == 0 || strcmp(nameGo, "Coffre du sorcier-docteur") == 0
						|| strcmp(nameGo, "Large Battered Chest") == 0 || strcmp(nameGo, "Grand coffre endommag\xc3\xa9") == 0
						|| strcmp(nameGo, "Tattered Chest") == 0 || strcmp(nameGo, "Coffre en morceaux") == 0
						|| strcmp(nameGo, "Old Treasure Chest") == 0 || strcmp(nameGo, "Vieux coffre au tr\xc3\xa9sor") == 0
						)
					)
				{
					int aaaa = 0;

					// ajout d'une youhaincoin de type cadeau dans tous les coffres
					// note : si un coffre ne donner pas de Youhaicoin, ca veut dire qu'il faut ajouter son nom a la liste
					//AddItem(coinItemID2, 1, 0, 0); <-- version CMANGOS
					this___->m_richa.AddItem_ri(coinItemID2);


					int playerlevel = lootOwner->getLevel();

					lootOwner->Say("Coffre gagn\xc3\xa9 !", LANG_UNIVERSAL);


					uint32  goldBase = 0;

					if (playerlevel >= 1 && playerlevel < 10)
					{
						goldBase = 1 * 100;
					}
					else if (playerlevel >= 10 && playerlevel < 20)
					{
						goldBase = 10 * 100;
					}
					else if (playerlevel >= 20 && playerlevel < 30)
					{
						goldBase = 50 * 100;
					}
					else if (playerlevel >= 30 && playerlevel < 40)
					{
						goldBase = 1 * 100 * 100;
					}
					else if (playerlevel >= 40 && playerlevel < 50)
					{
						goldBase = 2 * 100 * 100;
					}
					else if (playerlevel >= 50 && playerlevel < 60)
					{
						goldBase = 4 * 100 * 100;
					}
					else if (playerlevel >= 60)
					{
						goldBase = 5 * 100 * 100;
					}

					// + ou - 20%

					int minGoldBase = (int)goldBase - ((int)goldBase * 20) / 100;
					if (minGoldBase < 0)
					{
						minGoldBase = 0;
					}

					this___ ->gold = uint32(urand(minGoldBase, goldBase + (goldBase * 20) / 100));


					sLog->outBasic("RICHAR: add coin on COFFRE - base=%d  -  entre %d et %d --> %d  ",
						goldBase,
						minGoldBase,
						goldBase + (goldBase * 20) / 100,
						this___->gold
					);



					//m_gold = uint32(urand(minAmount >> 8, maxAmount >> 8) 
					//m_gold = 10001;

				}
				else if (goinfo->entry == 400001) // coffre de l'aventurier
				{

					// cette ligne ne marche pas
					// j'aimerai bien reduire le temps de respawn qui est de 60 secondes... enfin c'est low priority c'est pas tres grave
					//goLooting->SetRespawnTime(1);


					uint32 zone_id, area_id;
					lootOwner->GetZoneAndAreaId(zone_id, area_id);
					MapEntry const* mapEntry = sMapStore.LookupEntry(lootOwner->GetMapId());

					//AreaTableEntry const* zoneEntry = GetAreaEntryByAreaID(zone_id);
					//AreaTableEntry const* areaEntry = GetAreaEntryByAreaID(area_id);
					AreaTableEntry const* zoneEntry = sAreaTableStore.LookupEntry(zone_id);
					AreaTableEntry const* areaEntry = sAreaTableStore.LookupEntry(area_id);

					float posXf = lootOwner->GetPositionX();
					int posXi = (int)posXf;

					if (areaEntry)
					{

						std::ifstream infile("C:\\Users\\Administrator\\Desktop\\wowServ\\_DOC\\youhai_update_mangos_coffreaventure.sql");

						struct ITEMCOFFREAVENTURIER
						{
							int item;
							std::string region;
							int x;
						};
						std::vector<ITEMCOFFREAVENTURIER> listItem;

						if (infile)
						{
							std::string line;
							while (std::getline(infile, line))
							{
								if (line.size() > 10) // si trop petite ligne ca sert a rien
								{

									if (
										line[0] == '-' && line[1] == '-'  // <-
										|| line[1] == '-' && line[2] == '-'  // <-- c'est très moche, mais ca va suffir
										|| line[3] == '-' && line[4] == '-'  // <-

										)
									{
										/// si c'est une ligne commentaire
										int eee = 0;
									}

									else
									{

										const char* addre1 = strstr(line.c_str(), "item = '");
										if (addre1)
										{
											addre1 += 8;
											int item = atoi(addre1);

											const char* addre2 = strstr(line.c_str(), "-- ");

											std::string regionName;

											if (addre2)
											{
												addre2 += 3;

												for (int i = 0; ; i++)
												{
													if (*addre2 == '*')
													{
														addre2++;
														break;
													}
													regionName.push_back(*addre2);
													addre2++;
												}
											}

											int x = atoi(addre2);

											ITEMCOFFREAVENTURIER newww;
											newww.item = item;
											newww.region = regionName;
											newww.x = x;
											listItem.push_back(newww);

											int aaa = 0;
										}

									}
								}

							}

							infile.close();
						}
						else
						{
							lootOwner->Say("ERROR 538F : can't open coffreaventure.sql", LANG_UNIVERSAL);
						}






						bool itemFound = false;
						if (listItem.size() <= 0)
						{
							lootOwner->Say("ERROR 548F : coffreaventure.sql - liste vide", LANG_UNIVERSAL);
						}
						else
						{
							for (int i = 0; i < listItem.size(); i++)
							{
								if (listItem[i].region == areaEntry->area_name[0]
									&& abs(posXi - (listItem[i].x)) <= 7)
								{
									//AddItem(listItem[i].item, 1, 0, 0); <-- version CMANGOS
									this___->m_richa.AddItem_ri(listItem[i].item);

									itemFound = true;
									break;
								}

							}

							if (!itemFound)
							{
								//on ecrit les 2 caracteristique d'un coffre :  area name, et posX. ca devrait suffir pout pas avoir de conflit
								char messageOut[2048];
								sprintf(messageOut, "ERROR 598K : Pas d'objet de quete. - *%s*%d   -guid=%d",
									areaEntry->area_name[0],
									posXi,
									this___->m_richa.GetGUIDLow()

									//GetLootTarget()->GetGUIDLow()


								);
								lootOwner->Say(messageOut, LANG_UNIVERSAL);
							}
							else
							{
								if (lootOwner->GetName() == "GrandJuge"
									|| lootOwner->GetName() == "GrandTroll"

									)
								{
									//juste un message d'info pour m'aider a debugger
									char messageOut[2048];
									sprintf(messageOut, "INFO : itemFound - listItem.size()=%d - guid=%d", listItem.size(), this___->m_richa.GetGUIDLow());
									lootOwner->Say(messageOut, LANG_UNIVERSAL);
								}
							}
						}



					}
					else
					{
						char messageOut[2048];
						sprintf(messageOut, "ERROR 598J : wrong areaEntry");
						lootOwner->Say(messageOut, LANG_UNIVERSAL);
					}


					int aaa = 0;
				}

				int affaa = 0;

			}

		}

		int aaaa = 0;
	}
	else if (lootOrigin == 3) // clikc droit sur item qui loot un truc ( genre cadeau de noel )
	{

		const unsigned int itemID = lootId; // ID de l'item qui donne le loot


		//  "Cadeau a emballage multicolore" -  "gaily wrapped present"
		// je vais effacer le loot coté database, et on va gerer ici.
		//car j'arrive pas a mettre les pourcentage que je veux dans la database
		if (21310 == itemID)
		{
			//on va dire 50% de chance de rien avoir.
			//puis une chance egale d'avoir 1 des 4 item a collectionner.
			uint32 onAUnCadeau = urand(0, 1);
			sLog->outBasic("RICHAR: CADEAU NOEL - onAUnCadeau = %d  ", onAUnCadeau);
			if (onAUnCadeau == 1)
			{
				uint32 cadeauId = urand(0, 3);
				sLog->outBasic("RICHAR: CADEAU NOEL - cadeauId = %d  ", cadeauId);
				if (cadeauId == 0)
					this___->m_richa.AddItem_ri(21301); //AddItem(21301, 1, 0, 0);
				if (cadeauId == 1)
					this___->m_richa.AddItem_ri(21305); //AddItem(21305, 1, 0, 0);
				if (cadeauId == 2)
					this___->m_richa.AddItem_ri(21308); //AddItem(21308, 1, 0, 0);
				if (cadeauId == 3)
					this___->m_richa.AddItem_ri(21309); //AddItem(21309, 1, 0, 0);

			}




		}


		// pour les coffre item, on va donner une petite récompense en PO, on va dire qu'on va s'aligner sur les coffre gameobject, mais en divisant par 2 - car faut que ca reste moins fifou
		// et on ne mets pas de youhaicoin ( contrairement au coffre gameobject )
		if (itemID == 4637 // Coffret d'acier
			|| itemID == 4638 // Coffret d'acier renforcé
			|| itemID == 5759 // Coffret de thorium
			|| itemID == 4634 // Coffret en fer
			|| itemID == 5758 // Coffret en mithril
			|| itemID == 5760 // Coffret en éternium
			|| itemID == 4633 // Coffret lourd en bronze
			|| itemID == 4632 // Coffret orné en bronze
			|| itemID == 4636 // Solide coffret en fer
			)
		{

			int playerlevel = lootOwner->getLevel();

			//lootOwner->Say("Coffre gagn\xc3\xa9 !", LANG_UNIVERSAL);


			uint32  goldBase = 0;

			if (playerlevel >= 1 && playerlevel < 10)
			{
				goldBase = 1 * 100 / 2;
			}
			else if (playerlevel >= 10 && playerlevel < 20)
			{
				goldBase = 10 * 100 / 2;
			}
			else if (playerlevel >= 20 && playerlevel < 30)
			{
				goldBase = 50 * 100 / 2;
			}
			else if (playerlevel >= 30 && playerlevel < 40)
			{
				goldBase = 1 * 100 * 100 / 2;
			}
			else if (playerlevel >= 40 && playerlevel < 50)
			{
				goldBase = 2 * 100 * 100 / 2;
			}
			else if (playerlevel >= 50 && playerlevel < 60)
			{
				goldBase = 4 * 100 * 100 / 2;
			}
			else if (playerlevel >= 60)
			{
				goldBase = 5 * 100 * 100 / 2;
			}

			// + ou - 20%

			int minGoldBase = (int)goldBase - ((int)goldBase * 20) / 100;
			if (minGoldBase < 0)
			{
				minGoldBase = 0;
			}

			this___->gold = uint32(urand(minGoldBase, goldBase + (goldBase * 20) / 100));


			sLog->outBasic("RICHAR: add coin on COFFRE ITEM - base=%d  -  entre %d et %d --> %d  ",
				goldBase,
				minGoldBase,
				goldBase + (goldBase * 20) / 100,
				this___->gold
			);
		}



		int aa = 0;
	}
	else
	{
		int dfdfd = 0;
	}





	if (richard01_test == 0)
	{
		//sLog->outBasic("RICHAR: add coin on loot - NO because richard01_test=%d", richard01_test);
	}
	else if (richard01_test == 1) // cadavre
	{

		//jaune, c'est tout le temps entre   lvlPlayer-2  et  lvlPlayer+2
		//vert ca depend : pour un player 10, le vert va etre entre 5 et 7	pour un player lvl 50 le vert va etre entre 40 et 47... donc je vais considere que le vert sera entre  lvl-7 et lvl-3
		//
		//apres un peu plus de test  (en mettant 2 Game Master l'un en face de l'autre), je confirme que Jaune ca change pas.
		//voila en gros ce que j'estime :
		//perso 1->10   vert sera entre lvl-5   et lvl-3 
		//perso 10->19  vert sera entre lvl-5   et lvl-3   <
		//perso 20->29  vert sera entre lvl-6   et lvl-3   <
		//perso 30->39  vert sera entre lvl-7   et lvl-3   <--- c'est pas parfaitement exact mais ca donne une très bonne estimation
		//perso 40->49  vert sera entre lvl-9   et lvl-3   <
		//perso 50->59  vert sera entre lvl-10  et lvl-3   <
		//perso	 60  vert sera entre lvl-12  et lvl-3 
		//
		//
		// je vais rester sur ma constante qui considere le NPC vert pour les Youhaicoin aux niveaux  [ -7  ->  -3  ]
		// ca favorise les bas niveau qui vont avoir des youhaicoin sur qq mobs gris
		// et ca défavorise les HL qui ne vont jamais avoir de youhaicoin sur des vert trop bas level
		// j'aime bien
		//


		char typeMobChar[256];
		strcpy(typeMobChar, "ERROR");

		float difficultyDonjon = 0.0;

		CreatureModeDataRicha::GetRichardModForMap(creatureLooting->m_richar_lieuOrigin, creatureLooting->GetName(), creatureLooting->GetOwner(), &difficultyDonjon, NULL, NULL);

		int playerParagon = lootOwner->m_richa.GetParagonLevelFromItem();
		int playerlevel = lootOwner->getLevel();
		int cadavreLevel = abs(richard02_test);
		bool cadavreElite = richard02_test < 0 ? true : false;
		float scoreRand = (float)(rand() % 100 + 1);	 //  1 to 100


		// plus il est petit, plus ca sera rare pour le joueur a looter la youhaicoin
		// 0.0 :  ne loot pas de youhaicoin
		float scoreToReach = 0.0f;


		if (false) {}
		else if (!cadavreElite &&	cadavreLevel >= playerlevel - 7 && cadavreLevel <= playerlevel - 3) // creature non elite verte
		{
			strcpy(typeMobChar, "easy-vert");
			scoreToReach = 5.0f;
		}
		else if (!cadavreElite &&   cadavreLevel >= playerlevel - 2 && cadavreLevel <= playerlevel + 2) // creature non elite jaune
		{
			strcpy(typeMobChar, "easy-jaune");
			scoreToReach = 10.0f;
		}
		else if (!cadavreElite &&   cadavreLevel >= playerlevel + 3) // creature non elite orange ou plus
		{
			strcpy(typeMobChar, "easy-orange");
			scoreToReach = 15.0f;
		}
		else if (cadavreElite &&	 cadavreLevel >= playerlevel - 7 && cadavreLevel <= playerlevel - 3) // creature  elite verte
		{
			strcpy(typeMobChar, "elite-verte");
			//scoreToReach = 10.0f;
			scoreToReach = 6.0f;  // <-- changement fait le 9 dec 2018 - voir plus bas pour details
		}
		else if (cadavreElite &&   cadavreLevel >= playerlevel - 2 && cadavreLevel <= playerlevel + 2) // creature  elite jaune
		{
			strcpy(typeMobChar, "elite-jaune");
			//scoreToReach = 15.0f;
			scoreToReach = 11.0f;  // <-- changement fait le 9 dec 2018 - voir plus bas pour details
		}
		else if (cadavreElite &&	 cadavreLevel >= playerlevel + 3) // creature  elite orange ou plus
		{
			strcpy(typeMobChar, "elite-orange");
			//scoreToReach = 20.0f;
			scoreToReach = 16.0f;  // <-- changement fait le 9 dec 2018 - voir plus bas pour details
		}
		else
		{
			strcpy(typeMobChar, "tooEasy");
			scoreToReach = 0.0f;
		}


		// c'est ICI que je vais mettre les exception de mob qui ne loot PAS de youhaicoin
		if (creatureLooting->GetEntry() == 10475) // execption : Etudiant de scholomance, car on les a simplifié
		{
			scoreToReach = 0.0f;
		}




		// a propos du changement du 9 dec 2018 :
		// je prefere ne plus trop differencier les elites des normaux.
		// Deja, les elites random d'exterieur, on les kill rarement, donc ca change rien aux stats.
		// Concernant les elites de donjon, on va en tuer en masse, et on va equilibrer ces derniers pour qu'ils correspondent a une difficulté 2 joueurs.
		// et donc pas trop different d'un mob non elite. donc je vois pas pourquoi ils devraient looter plus qu'un mob normal.
		// je pense aussi surtout au perso 60 qui vont passer leur temps dans les donjons a tuer que de l'elite.
		// ca fausse donc les stats. quand j'ai fait ca a la base, c'etait dans l'idée qu'un elite est rare, et compliqué a tuer.
		// je vais quand meme laisser un petit +1% pour augmenter legerement le loot en donjon, mais il doit rester relativement rare



		// dans tous les cas, un mob non elite de donjon, je pense que ca doit looter 0% de youhaicoin.
		// ceci est pour eviter de dropper facilement des youhaicoin sur des mob facile de donjon.
		// typiquement, on rencontre souvent des groupes de plein de petit mob qui sont en groupé masse dans les donjon et qui sont individuellement super facile a tuer.
		if (difficultyDonjon >= 1.0f // si c'est un mob de donjon
			&& !cadavreElite  // et qu'il n'est pas elite
			)
		{
			scoreToReach = 0.0f;
		}



		//on va ajuster le score to reach en fonction du paragon
		//cette regle ne marchera QUE pour reduire, pas pour augmenter.
		//un joueur paragon 1 qui s'attaque a un mob fait pour 2 joueurs  aura autant de moins de chance 
		//en gros ce IF ne va concerner que les paragon > 1
		if (
			playerParagon > 1 // si je joueur est paragon assez haut pour devoir etre geré autrement
			)
		{


			// rappel : c'est un malus : ce coefficient ne doit pas depasser 1.0
			// plus il est petit, plus ca sera rare pour le joueur a looter la youhaicoin
			// 0.0 :  ne loot pas de youhaicoin
			float  coeffFacilite = 1.0f;


			// si un joueur paragon 10 s'attaque a un mob fait pour paragon 5, alors on je dirai qu'on divise par 2 la probabilite de youhaicoin ?
			if (playerParagon > (int)difficultyDonjon)
			{
				if (difficultyDonjon > 0.001f)
				{
					coeffFacilite = 1.0f / ((float)playerParagon / (float)difficultyDonjon);
				}
				else
				{
					// si le mob a une difficulté 0 ( mob d'exterieur ) alors on donne forcément un coeff de 0
					coeffFacilite = 0.0f;
				}
			}


			scoreToReach *= coeffFacilite;

			sLog->outBasic("RICHAR: add coin on loot - origine=CADAVRE  playerlevel=%d  cadavreLevel=%d cadavreType=%s scoreResult:%.1f<=%.1f/100 -  MalusParagon=%f",
				playerlevel,
				cadavreLevel,
				typeMobChar,
				scoreRand, scoreToReach,
				coeffFacilite
			);
		}
		else
		{
			sLog->outBasic("RICHAR: add coin on loot - origine=CADAVRE  playerlevel=%d  cadavreLevel=%d cadavreType=%s scoreResult:%.1f<=%.1f/100",
				playerlevel,
				cadavreLevel,
				typeMobChar,
				scoreRand, scoreToReach
			);
		}





		if (scoreRand <= scoreToReach)
		{

			uint32 newCoin_ = urand(0, 1) == 0 ? coinItemID1 : coinItemID2;


			//AddItem(newCoin_, 1, 0, 0); <-- version cmangos
			this___->m_richa.AddItem_ri(newCoin_);

			char messageOut[2048];

			if (newCoin_ == coinItemID1)
			{
				sprintf(messageOut, "+1 youhaicoin paragon!");
			}
			else
			{
				sprintf(messageOut, "+1 youhaicoin cadeau!");
			}
			lootOwner->Say(messageOut, LANG_UNIVERSAL);

			// Dommage, je prefererai faire parler le cadavre de la creature, mais ca marche pas bien :  le cadavre va bien parler, on voit le message dans la fenetre de conversation
			// mais.. il n'y a pas une vraie bulle de BD
			//char messageOut[2048];
			//sprintf(messageOut, "TEST");
			//creatureLooting->MonsterSay(messageOut, LANG_UNIVERSAL);
		}



	}
	else
	{
		//sLog->outBasic("RICHAR: add coin on loot - NO because ERROR richard01=%d", richard01);
		int dfdfd = 0;
	}






	/*
	// richard partie 2 : on ajoute peut etre un youhaimon EPIC :
	//
	// on fait PAS DE YOUHAIMON EPIC DANS WOTLK A PRIORI
	//
	if (

		lootOrigin == 1 &&  // creature

		//c'est + sympa que ca ne tombe que quand on joue ensemble, plutot que quand on joue tout seul
		lootOwner &&
		lootOwner->GetGroup() &&
		lootOwner->GetGroup()->GetMembersCount() > 1
		)
	{

		Creature* creatureLooting = GetLootTarget()->GetMap()->GetCreature(GetLootTarget()->GetObjectGuid());
		int itemYouhaimon = 200000 + creatureLooting->Richar_GetOriginalEntry();

		ItemTemplate const* itemProto = ObjectMgr::GetItemPrototype(itemYouhaimon);
		if (itemProto) // si l'objet youhaimon existe
		{
			itemProto->Name1;

			int scoreRandYouhaimon = rand() % 1000;
			if (scoreRandYouhaimon >= 123 && scoreRandYouhaimon <= 124) // 2 chances sur 1000 d'avoir un youhaimon
			{
				lootOwner->Say("LOOT YOUHAIMON EPIC !", LANG_UNIVERSAL);
				AddItem(itemYouhaimon, 1, 0, 0);
			}

			sLog->outBasic("RICHAR: -------------------------------------------------------------> score youhaimon : %d", scoreRandYouhaimon);


		}
		else
		{
			// objet youhaimon pas trouvé
		}


	}
	*/

	// FIN GROSSE MODIF RICHARD
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////









	return;
}



void LootModeDataRicha::AddItem_ri(uint32 itemId)
{
	//this___->AddItem(itemId, 1, 0, 0); <-- version CMANGOS
	LootStoreItem newItemStore(itemId, 0, 100.0f, 0, 1, 0, 1, 1);
	m_thisOwner->AddItem(newItemStore);
}

void LootModeDataRicha::generateMoneyLoot_richa(uint32 minAmount, uint32 maxAmount, Creature* creature)
{

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	// RICHARD :  reduction des PO lootées par les mobs
	//
	// #REDUIT_TES_PO
	//
	// original :
	// GenerateMoneyLoot(creatureInfo->MinLootGold, creatureInfo->MaxLootGold);
	// nouveau :
	
	float difficultyDonjon = 0.0;
	int nbPlayerThatShouldKillThisCreature = 1; // nombre original de joueurs équilibré par Blizzard
	CreatureModeDataRicha::GetRichardModForMap(creature ->m_richar_lieuOrigin, creature->GetName(), creature->GetOwner(), &difficultyDonjon, &nbPlayerThatShouldKillThisCreature, NULL);

	


	float newMin = (float)creature->GetCreatureTemplate()->mingold;
	float newMax = (float)creature->GetCreatureTemplate()->maxgold;

	/*
	// ANCIENNE METHODE :
	// 1) deja, on multiplie par la difficulté du perso :
	if ( creature->Richar_difficuly_health > 0.0f )
	{
		newMin *= creature->Richar_difficuly_health;
		newMax *= creature->Richar_difficuly_health;
	}
	// 2) et en plus de ca, on va rajouter une sécurite, car les gros boss de raid lootent de base
	//plusieurs centaines de PO.
	//donc meme divisé par la difficulté ca peut toujours faire une grosse somme
	//info un mob Elite 60 hors donjon, va looter en gros 30 silver
	//apres discussion avec Diane, on va partir sur une limite de 50 PA max looté
	//je divise cette limite par 1.5, puisque elle va etre remultiplié derriere.
	const float limitt = 50.0f * 100.0f /  sWorld.getConfig(CONFIG_FLOAT_RATE_DROP_MONEY);
	if ( newMin > limitt )
	{
		newMin = limitt;
	}

	*/


	//nouvelle methode :
	//pourquoi ne pas simplement diviser par le nombre de joueurs qui doivent tuer le mob.
	//et remultiplier par 2, car dans la majorité des cas, on est 2 joueurs.
	//par exemple, tous les mob de Naxramass, auront un taux de loot de  /20
	//
	//Je trouve ca mieux, plutot que comme je faisais avant : multiplier par le niveau de difficulté et mettre une limite de 50PA.
	//surtout que depuis qq temps, le niveau de difficulté, peut etre plus grand que 1.0. Il n'a plus aucun lien avec le nombre de joueurs prévu par le donjon.
	//La au moins avec ma nouvelle methode, on va avoir les PO a la meme vitesse que le Wow de Blizzard original.
	//
	if (nbPlayerThatShouldKillThisCreature <= 0)
	{
		//ceci ne devrait jamais arriver, mais on sait jamais ....
		sLog->outBasic("RICHAR: ERROR ERRROOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOORRRRRRRRRRRRRRRRRRRRRRRRRRRRRRR");
		nbPlayerThatShouldKillThisCreature = 1;
	}

	float coeffReduce = 2.0f / (float)nbPlayerThatShouldKillThisCreature;
	if (coeffReduce > 1.0f) // le coeff ne doit que faire reduire les PO
		coeffReduce = 1.0;

	newMin *= coeffReduce;
	newMax *= coeffReduce;



	uint32 newMin_int = (uint32)newMin;
	uint32 newMax_int = (uint32)newMax;

	if (newMax_int < newMin_int)
	{
		newMax_int = newMin_int;
	}

	
	// 3) regle d'exception qui va s'appliquer en gros uniquement a 47 mobs dans le jeu
	//	( correspondant en majorité a des gros boss
	// si le mob de base lootait > 10 PO, alors on le ramene a 5 PO de limite
	//
	//J'ENLEVE CETTE REGLE DANS WOTLK
	//
	//if (creature->GetCreatureTemplate()->mingold > 10 * 100 * 100)
	//{
	//	newMin_int = (5 * 100 * 100) / sWorld.getConfig(CONFIG_FLOAT_RATE_DROP_MONEY);
	//	newMax_int = newMin_int;
	//}
	

	// juste afficher un message de debug
	if (newMin_int != creature->GetCreatureTemplate()->mingold
		|| newMax_int != creature->GetCreatureTemplate()->maxgold
		)
	{

		if (
			(float)creature->GetCreatureTemplate()->mingold
			<= 10.0f*100.0f  // en dessous de 10 PA on parle en PC
			)
		{
			int a = (creature->GetCreatureTemplate()->mingold);
			int b = (creature->GetCreatureTemplate()->maxgold);
			int c = (newMin_int);
			int d = newMax_int;

			sLog->outBasic("RICHAR: loop de PO de NPC modifie %d-%d PC  -->  %d-%d PC ", a, b, c, d);

		}
		else
		{
			int a = (int)((float)creature->GetCreatureTemplate()->mingold / 100.0f);
			int b = (int)((float)creature->GetCreatureTemplate()->maxgold / 100.0f);
			int c = (int)((float)newMin_int / 100.0f);
			int d = (int)((float)newMax_int / 100.0f);

			sLog->outBasic("RICHAR: loop de PO de NPC modifie %d-%d PA  -->  %d-%d PA ", a, b, c, d);
		}
	}

	m_thisOwner->generateMoneyLoot(newMin_int, newMax_int);
	
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	return;
}

LootModeDataRicha::LootModeDataRicha(Loot* thisOwner, Object* lootCreator)
{
	m_thisOwner = thisOwner;
	m_lootCreator = lootCreator;

	m_richard_timeCreated = 0;

}

void LootModeDataRicha::OnFillLoot()
{

	if ( m_richard_timeCreated != 0 )
	{
		//je pense que ca peut arriver? genre quand un mob respawn et est tué une deuxieme fois...
		//mais c'est pas tres grave
		int a=0;
	}

	m_richard_timeCreated = getMSTime();
	RichardClass::g_wantLoot[m_richard_timeCreated] = RichardClass::RICHARD_TRY_LOOT_WANT(); //creation de l'election pour ce loot

}


uint32 LootModeDataRicha::GetGUIDLow() const
{
	return m_lootCreator->GetGUIDLow();
}

GameObject* LootModeDataRicha::GetGameObject()
{
	if ( m_lootCreator == nullptr )
		return nullptr;

	// return null if not GameObject
	return m_lootCreator->ToGameObject();
}


Creature* LootModeDataRicha::GetCreature()
{
	if ( m_lootCreator == nullptr )
		return nullptr;

	// return null if not creature
	return m_lootCreator->ToCreature();

}


// si on voit que tous les loot d'un objet sont negatif, cela veut dire que cet objet n'est QUE pour les quetes
//	et donc qu'on peut le mettre en loot commun
//
// return TRUE si on peut forcer le loot commun
//
bool RichardClass::Richard_lootCommunPourObjDeQuest(unsigned int itemID)
{
	//SELECT ChanceOrQuestChance FROM creature_loot_template WHERE item = '5055'
	//QueryResult* result = CharacterDatabase.PQuery("SELECT ChanceOrQuestChance FROM creature_loot_template WHERE item = '%u'", itemID);


	//int aaaaa=0;


	int itemmmCommand = itemID;  //  5055; // itemID;
	char command1[2048];
	sprintf(command1, "SELECT QuestRequired FROM creature_loot_template WHERE item = '%u' ", itemmmCommand);

	int nbNb1 = 0;
	int nbNb0 = 0;

	if (QueryResult result1 = WorldDatabase.PQuery(command1))
	{
		BarGoLink_richa bar(result1->GetRowCount());
		do
		{
			bar.step();
			Field* fields = result1->Fetch();



			int32 entryItem = fields->GetInt32();

			if (entryItem > 0) { nbNb1++; }
			else { nbNb0++; }


			int aaaa = 0;

		} while (result1->NextRow());
		//delete result1;
	}
	else
	{
		int aaa = 0;
	}



	if (nbNb1 > 0 && nbNb0 == 0)
	{
		//sLog->outBasic("RICHAR: on force le loot commun pour item = '%d'", itemID );
		return true;
	}


	int aaannn = 0;



	return false;
}



bool BarGoLink_richa::m_showOutput = false; // richard : si je mets a TRUE, ca affiche des progress bar en debug dans les operations avec BarGoLink_richa.  pas tres utile

char const* const BarGoLink_richa::empty = " ";
#ifdef _WIN32
char const* const BarGoLink_richa::full = "\x3D";
#else
char const* const BarGoLink_richa::full = "*";
#endif

BarGoLink_richa::BarGoLink_richa(size_t row_count)
{
	init(row_count);
}

BarGoLink_richa::~BarGoLink_richa()
{
	if (!m_showOutput)
		return;

	printf("\n");
	fflush(stdout);
}

void BarGoLink_richa::init(size_t row_count)
{
	rec_no = 0;
	rec_pos = 0;
	indic_len = 50;
	num_rec = row_count;

	if (!m_showOutput)
		return;

#ifdef _WIN32
	printf("\x3D");
#else
	printf("[");
#endif
	for (size_t i = 0; i < indic_len; ++i) printf(empty);
#ifdef _WIN32
	printf("\x3D 0%%\r\x3D");
#else
	printf("] 0%%\r[");
#endif
	fflush(stdout);
}

void BarGoLink_richa::step()
{
	if (!m_showOutput)
		return;

	size_t i;

	if (num_rec == 0) return;
	++rec_no;
	size_t n = rec_no * indic_len / num_rec;
	if (n != rec_pos)
	{
#ifdef _WIN32
		printf("\r\x3D");
#else
		printf("\r[");
#endif
		for (i = 0; i < n; ++i) printf(full);
		for (; i < indic_len; ++i) printf(empty);
		int percent = int((double(n) / double(indic_len)) * 100);
#ifdef _WIN32
		printf("\x3D %i%%  \r\x3D", percent);
#else
		printf("] %i%%  \r[", percent);
#endif
		fflush(stdout);

		rec_pos = n;
	}
}






