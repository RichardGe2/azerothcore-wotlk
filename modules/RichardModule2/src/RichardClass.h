#pragma once


class Creature;
class Quest;
struct Loot;
class LootStore;
struct LootItem;


class CreatureModeDataRicha
{
public:
	CreatureModeDataRicha(Creature* thisOwner);

	~CreatureModeDataRicha();

	//  richar
	uint32 Richar_GetOriginalEntry();
	float Richar_difficuly_health;
	float Richar_difficuly_degat;
	static float GetRichardModForMap(const std::string& cPosRicha, const std::string& mobName, const Unit* richaOwner, float* donjonLevel, int* nbPlayerOriginal, float* difficultyHealth);
	static float GetRichardModForMap2(Creature* creatureeee, float* donjonLevel, int* nbPlayerOriginal, float* difficultyHealth);

	Creature* m_thisOwner;


};


class LootModeDataRicha
{
public:
	LootModeDataRicha(Loot* thisOwner  , Object* lootCreator);

	~LootModeDataRicha()
	{

	}

	void OnFillLoot();

	void AddItem_ri(uint32 itemId);

	void generateMoneyLoot_richa(uint32 minAmount, uint32 maxAmount, Creature* creatureLooting);

	Creature* GetCreature();// return null if not creature

	GameObject* GetGameObject();// return null if not GameObject

	uint32 GetGUIDLow() const;

	Loot* m_thisOwner;
	time_t m_richard_timeCreated;
	std::vector<LootItem> m_lootItems;
	Object* m_lootCreator;
};



class PlayerModeDataRicha
{
public:
	PlayerModeDataRicha(Player* thisOwner)
	{
		m_richa_scoreElderCourse = 0;
		m_thisOwner = thisOwner;
	}

	~PlayerModeDataRicha()
	{

	}

	void Richa_OnCanTakeQuest(Quest const* quest, bool msg) const;

	void richard_importVariables_START(uint64 guid__);
	void richard_importVariables_END(uint64 guid__);


	// richa :  essayer plutot d'utiliser   GetItemCount  si possible
	uint32 richard_countItem(uint32 item, bool inBankAlso = false, bool inEquipmentAlso = false, bool inKeyRingAlso = false, bool inInventoryAlso = true) const;
	void richard_countItem_pokeball(uint32& itemKeyRin0, uint32& quantity) const;





	///////////////////////////////////////////////////////////////////////////////////
	// richar
public:
	void Richard_InformDiscoveredNewArea(int areaFlag);
	struct MAP_SECONDA
	{
		MAP_SECONDA(const std::string& name_, bool explored_, int areaFlag_)
		{
			name = name_;
			explored = explored_;
			areaFlag__ = areaFlag_;
		}

		std::string name;
		bool explored;
		int areaFlag__;
	};

	int32 GetAreaFlagByAreaID_richa(uint32 area_id);
	void Richard_GetListExplored(std::map<std::string, std::vector<MAP_SECONDA>  >& mapsList, int&  nbAreaExplored, int&  nbAreaTotal);


	//int m_richar_paragon; // variable specifique a ce Player : Bouillot, Boulette....
	//int m_richar_paragonProgressFromFile; // only USED during loading, after that, it's always 0

	struct RICHA_NPC_KILLED_STAT
	{
		RICHA_NPC_KILLED_STAT(unsigned int npc_id_, unsigned int nb_killed_)
		{
			npc_id = npc_id_;
			nb_killed = nb_killed_;
		}

		unsigned int npc_id;
		unsigned int nb_killed;
	};
	std::vector<RICHA_NPC_KILLED_STAT> m_richa_NpcKilled;

	struct RICHA_PAGE_DISCO_STAT
	{
		RICHA_PAGE_DISCO_STAT(unsigned int pageId_, unsigned int objectID_, unsigned int itemID_)
		{
			pageId = pageId_;
			objectID = objectID_;
			itemID = itemID_;
		}

		unsigned int pageId;
		unsigned int objectID;
		unsigned int itemID;
	};
	std::vector<RICHA_PAGE_DISCO_STAT> m_richa_pageDiscovered;


	struct RICHA_LUNARFESTIVAL_ELDERFOUND
	{
		RICHA_LUNARFESTIVAL_ELDERFOUND(unsigned int year_, unsigned int questId_)
		{
			year = year_;
			questId = questId_;
		}

		unsigned int year;
		unsigned int questId;
	};
	std::vector<RICHA_LUNARFESTIVAL_ELDERFOUND> m_richa_lunerFestivalElderFound;

	// lorsqu'on fait la course a celui que trouve le + de Elder.
	// ce score je ne vais pas le sauvegarder
	// il se met a 0 quand le perso se connecte.
	// quand on fait la course, le premier qui atteind le score qu'on decide a gagné.
	//
	// dans l'idée : plus c'est un Elder qu'on a pas ve depuis longtemps, plus ca rapporte de points.
	//			   chaque année on peut affiner autour de cette regle
	//
	int m_richa_scoreElderCourse;


	struct RICHA_MAISON_TAVERN
	{
		RICHA_MAISON_TAVERN(uint32 a, uint32 b)
		{
			mapid = a;
			areaid = b;
		}

		uint32 mapid;
		uint32 areaid;
	};

	struct RICHA_ITEM_LOOT_QUEST
	{
		RICHA_ITEM_LOOT_QUEST(bool active_, uint32_t itemid_, float currentScore_, int nbFoisQueteDone_, bool LoopQuest_)
		{
			active = active_;
			itemid = itemid_;
			currentScore = currentScore_;
			nbFoisQueteDone = nbFoisQueteDone_;
			LoopQuest = LoopQuest_;

		}

		RICHA_ITEM_LOOT_QUEST()
		{
			itemid = 0;
			currentScore = 0.0f;
			active = false;
			nbFoisQueteDone = 0;
			LoopQuest = false;
		}

		bool active;
		uint32_t itemid;
		float currentScore; // quand il arrive a >= 1.0, on gagne l'objet et il repasse a 0.0 
		int nbFoisQueteDone; // nombre de fois que la quete a été terminée
		bool LoopQuest; // true is quand la quete est finie alors elle reprends automatiquement a 0

	};

	static void richa_importFrom_richaracter_(
		uint64 guid__,
		std::vector<RICHA_NPC_KILLED_STAT>& richa_NpcKilled,
		std::vector<RICHA_PAGE_DISCO_STAT>& richa_pageDiscovered,
		std::vector<RICHA_LUNARFESTIVAL_ELDERFOUND>& richa_lunerFestivalElderFound,
		std::vector<RICHA_MAISON_TAVERN>& richa_ListeMaison,
		std::vector<RICHA_ITEM_LOOT_QUEST>& richa_ListItemQuestLoot,
		std::string& namePerso);

	static void richa_exportTo_richaracter_(
		uint64 guid__,
		const std::vector<RICHA_NPC_KILLED_STAT>& richa_NpcKilled,
		const std::vector<RICHA_PAGE_DISCO_STAT>& richa_pageDiscovered,
		const std::vector<RICHA_LUNARFESTIVAL_ELDERFOUND>& richa_lunerFestivalElderFound,
		const std::vector<RICHA_MAISON_TAVERN>& richa_ListeMaison,
		const std::vector<RICHA_ITEM_LOOT_QUEST>& richa_ListItemQuestLoot,
		const char* name);

	//va exporter dans   _ri_stat_Grandjuge_2017_04_21.txt
	//le but de cet exporter est d'exporter TOUTES les donnée possible qui definissent ENTIEREMENT le PERSONNAGE
	//ceci dans un but de debug, et d'archivage
	//le fichier exporté n'est pas vraiment sensé etre relu et utilisé derriere par le serveur
	void richa_exportTo_ristat_();

	int GetParagonLevelFromItem();

	std::vector<RICHA_MAISON_TAVERN> m_richa_ListeMaison;

	// je vais me debrouille pour qu'il soit rangés pour que en premier position on a les actifs.
	//plus on est proche de [0], plus il est "prioritaire", c'est a dire moins suspetible d'etre automatiquement passé en   active=false
	std::vector<RICHA_ITEM_LOOT_QUEST> m_richa_itemLootQuests;

	///////////////////////////////////////////////////////////////////////////////////









	Player* m_thisOwner;

};

class RichardClass
{
public:

	static void OnFillLoot(uint32 lootId, LootStore const& store, Player* lootOwner, bool personal, bool noEmptyError, uint16 lootMode , Loot* this___);

	static bool Richard_lootCommunPourObjDeQuest(unsigned int itemID);

	bool ExecuteCommand_richard_B(const char* text, Player* playerrrr);

	static bool  ExtractUInt32Base(char** args, uint32& val, uint32 base) ;
	static bool  ExtractUInt32(char** args, uint32& val)  { return ExtractUInt32Base(args, val, 10); }

	// sert a avoir des information sur un Item a partir de son ID
	// return TRUE if taken in charge
	bool ExecuteCommand_richard_2(int numberID, Player* player);

	bool ExecuteCommand_richard_C(const char* text, Player* player);
	bool ExecuteCommand_richard_D(const char* text, Player* playerrr);

	bool ExecuteCommand_richard_A(const char* text, Player* playerrrr);

	static unsigned long Richa_NiceLinkToIitemID(const char* str);

	//convert example :
	// 3965 -->  "|cff9d9d9d|Hitem:3965:0:0:0|h[Gants en cuir épais]|h|r"
	static std::string Richa_itemIdToNiceLink(unsigned long itemID);


	//bool Richar_listeventquest(char* args);



	//  RETURN TRUE si le loot est accepté
	//  RETURN FALSE si le loot est refusé
	//
	// lootTypeItemOrGold = 1  pour item loot
	// lootTypeItemOrGold = 2  pour gold loot
	static bool RichaHandleLootRandom(Loot* loot, int lootTypeItemOrGold , Player* _player);



	////////////////////////////////////////////////////////////////////////////////////////////////
	// richard 

	class RICHARD_TRY_LOOT_WANT_NB
	{
	public:
		RICHARD_TRY_LOOT_WANT_NB() { nbFois = 0; scoreDice = -1; }

		int nbFois; // sert juste pour le debug - incremente a chaque fois que le joueur envoie sa candidature

		// le dé est lancé entre 2 et 1000.
		// plus le score est eleve, plus le joueur a de chance d avoir le loot.
		// qq scores spéciaux :
		// -1 : pas init
		// 0  : le joueur ne veut PAS le loot ( il a fait un OKWIN )
		// 1  : le joueur arrivé en retard ( mais il veut quand meme le loot )
		// 2 -> 1000 : cas normal
		int scoreDice;
	};

	class RICHARD_TRY_LOOT_WANT
	{
	public:
		RICHARD_TRY_LOOT_WANT()
		{
			winner = nullptr;
			//winnerSaidIWinAlone = false;
			messageSentToPlayer_po = false;
			messageSentToPlayer_loot = false;

			okWinDoneOnThisLoot = false;
		}

		//liste des candidats pour ce loot - avec leur score de dès
		std::map<Player *, RICHARD_TRY_LOOT_WANT_NB >  list;

		Player * winner;

		//bool winnerSaidIWinAlone;

		bool messageSentToPlayer_po;
		bool messageSentToPlayer_loot;

		bool okWinDoneOnThisLoot;

	};



	static std::map<time_t, RICHARD_TRY_LOOT_WANT  > g_wantLoot;








};


class BarGoLink_richa
{
public:												 // constructors
	explicit BarGoLink_richa(size_t row_count);
	~BarGoLink_richa();

public:												 // modifiers
	void step();

private:
	void init(size_t row_count);

	static bool m_showOutput;						   // not recommended change with existed active bar
	static char const* const empty;
	static char const* const full;

	size_t rec_no;
	size_t rec_pos;
	size_t num_rec;
	size_t indic_len;
};



//richard : check good config :
#ifndef _M_AMD64
#error  UTILISER LE 64 BIT !!!!
NE PAS UTILISER LE 64 BIT !!!!
#endif
//#ifndef _M_IA64
//#error  UTILISER LE 64 BIT !!!!
//NE PAS UTILISER LE 64 BIT !!!!
//#endif
#ifndef _M_X64
#error  UTILISER LE 64 BIT !!!!
NE PAS UTILISER LE 64 BIT !!!!
#endif
#ifndef _WIN64
#error  UTILISER LE 64 BIT !!!!
NE PAS UTILISER LE 64 BIT !!!!
#endif





