
//
//   plugin de Richard 
//
//
			
#include "ScriptMgr.h"
#include "Player.h"
#include "Configuration/Config.h"
#include "Chat.h"
#include "RichardClass.h"
#include "Group.h"
#include "GroupReference.h"
#include "Reference.h"

class MyPlayer : public PlayerScript
{
public:

MyPlayer() : PlayerScript("MyPlayer") { }

void OnLogin(Player* player) override
{
		bool RichardAddon_exampleOfBoolConfig = sConfigMgr->GetBoolDefault("RichardAddon.exampleOfBoolConfig", false);


	// envoyer un message de type "Jaune" au joueur
	ChatHandler(player->GetSession()).SendSysMessage("Hello World from Richard Addon!");


}

void OnLootItem(Player* player, Item* item, uint32 count, uint64 lootguid) override
{
	int a = 0;
	return;
}


  
void OnChat(Player* player, uint32 type, uint32 lang, std::string& msg) override
{
	/*
	if (msg == "--killrichard")
	{
		uint64 target = player->GetTarget();
		Unit* targte2 = player->GetSelectedUnit();
		if ( targte2 && targte2->IsAlive() )
		{
			Unit::DealDamage(player, targte2, targte2->GetHealth(), nullptr, DIRECT_DAMAGE, SPELL_SCHOOL_MASK_NORMAL, nullptr, false, true);
			int a= 0;

		}

	}
	
	else if (msg == "--okwin")
	{
		RichardClass::HandleRichardCommand_clearLootWinners(nullptr, player);
	}
   
	else if (msg == "--stat")
	{
		RichardClass::Richar_tellMobStats(nullptr, player);
	}

	else if (msg == "--notincombat")
	{
		RichardClass::Richar_noMoreInComat(nullptr, player);
	}


	else if (msg == "--richardhelp")
	{
		RichardClass::Richar_help(nullptr, player);
	}


	else if (msg == "--need")
	{
		RichardClass::Richar_need(nullptr, player);
	}
	*/


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

void OnPlayerCompleteQuest(Player* player____, Quest const* quest_id____) override
{



	Quest const* pQuest = quest_id____;

	Object* questGiver = nullptr; // TODO


	////////////////////////////////////////////////////////////////////////////////
	//richard : add coin in quest reward
	{
		int32 questLevel = pQuest->GetQuestLevel();
		int32 playerLevel = player____->getLevel();
		uint32 questType = pQuest->GetType();
		bool questIsDungeon = questType & QUEST_TYPE_DUNGEON;
		bool questIsElite = questType & QUEST_TYPE_ELITE;
		bool questIsRaid = questType & QUEST_TYPE_RAID;
		bool questIsLegendary = questType & QUEST_TYPE_LEGENDARY;
		bool questIsEscort = questType & QUEST_TYPE_ESCORT;
		uint32 questID = pQuest->GetQuestId();
		bool questIsHarder = questIsDungeon | questIsElite | questIsRaid | questIsLegendary | questIsEscort;
		bool questIsRepeatable = pQuest->IsRepeatable();


		//si c'est = a true, ca veut dire qu'une quete verte ou grises donnera des youhaicoi comme si c'etait une quete jaune
		//on fait ca pour les event
		bool rewardGreyAndGreenAsYellow_event = false;


		//
		//
		//
		//
		// Cette longue liste est en 3 exemplaires : un dans __RICHARD_ALL.txt et un dans Player.cpp de CLASSIC, un dans Player de WOTLK
		// donc IMPORTANT de maintenanir LA MEME liste des 2 cotés
		// toutefois attention a pas la copier coller betement - les 2 listes ne sont pas communes pour les comment-out
		// en effet, celle de __RICHARD_ALL.txt va comment-out les quete qu'on ne doit pas reset regulierement
		// alors que la liste de Player.cpp ca comment-out les quetes qui ne merite pas les youhaicoin bonus
		//
		//
		if (questID == 0
			//
			// Ci Dessous - les quetes ouverture des cadeaux de Noel   2
			//	
			|| questID == 6963 //# Horde	- faut retrouver le bonhomme de neige - 1 - demarré par "Kaymard Copperpinch"
			|| questID == 6983 //# Horde	- faut retrouver le bonhomme de neige - 2
			|| questID == 6984 //# Horde	- faut retrouver le bonhomme de neige - 3
			|| questID == 7042 //# Alliance - ou faut retrouver le bonhomme de neige - 1 - demarré par Wulmort Jinglepocket a Ironforge
			|| questID == 7043 //# Alliance - ou faut retrouver le bonhomme de neige - 2
			|| questID == 7045 //# Alliance - ou faut retrouver le bonhomme de neige - 3
			|| questID == 6961 //# Horde	- Great-father Winter is Here! - demarré par "Kaymard Copperpinch"
			|| questID == 7021 //# Horde	- Great-father Winter is Here! - demarré par "Whulwert Copperpinch"
			|| questID == 7024 //# Horde	- Great-father Winter is Here! - demarré par  Nardstrum Copperpinch a Under City
			|| questID == 7022 //# Horde	- Great-father Winter is Here! - demarré par  Nardstrum Copperpinch a Under City
			|| questID == 7023 //# Horde	- Great-father Winter is Here! - demarré par  Nardstrum Copperpinch a Under City
			|| questID == 8746 //# Horde	- quete de Metzen le cerf - demarré par "Kaymard Copperpinch"
			|| questID == 8762 //# Alliance - quete de Metzen le cerf -
			|| questID == 6964 //# Horde	- Speak with Sagorne Creststrider in the Valley of Wisdom of Orgrimmar
			|| questID == 7061 //# Horde	- suite de 6964 - deliver it to Cairne Bloodhoof in Thunder Bluff
			|| questID == 7062 //# Alliance - "The reason for the season" - Speak with Historian Karnik at the Explorer's League in Ironforge
			|| questID == 7063 //# Alliance - suite de 7062 - deliver it to King Magni Bronzebeard in Ironforge
			|| questID == 8763 //# Alliance - "The Hero of the Day" - demande 300 en cooking - il faut donner du "Deeprock Salt" a une machine et en echange elle donne du "Preserved Holly" - donne par Wulmort a IronForge
			|| questID == 8799 //# Horde	- "The Hero of the Day"  version Horde de 8763
			|| questID == 6962 //# Horde	- "Treats for Great-father Winter" - Faut donner des cookie et du lait ai pere noel - donné par pere noel
			|| questID == 7025 //# Alliance - version Alliance de 6962
			//
			//  Ci Dessous - les quetes ouverture des cadeaux de Noel   21
			//
			|| questID == 8827 //# Alliance - "Winter's Presents" - je crois que c'est juste pour aller voir le pere noel pour ouvrir les cadeaux - donné par "Wonderform Operator" trouvable un peu partout
			|| questID == 8828 //# Horde	- version Horde de 8827
			//||questID==8744 //# A Carefully Wrapped Present
			//||questID==8768 //# A Gaily Wrapped Present
			//||questID==8769 //# A Ticking Present  
			//||questID==8788 //# A Gently Shaken Gift	<----- PAS DE BONUS YOUHAICOIN - car sont deja dans les cadeaux
			//||questID==8803 //# A Festive Gift
			//||questID==8767 //# A Gently Shaken Gift
			//
			//  Ci Dessous - les quetes de la saint valentin  8
			//
			|| questID == 8903 // Alliance - suite de quete Alliance qui se commence aupre de Mottar a SW
			|| questID == 9024 // Alliance - suite de 8903
			|| questID == 9025 // Alliance - suite de 9024
			|| questID == 9026 // Alliance - suite de 9025
			|| questID == 9027 // Alliance - suite de 9026
			|| questID == 9028 // Alliance - suite de 9027
			|| questID == 8899 // Alliance - transmettre une lettre de Aldris (Darnassus) -> Colara ( SW )
			|| questID == 8897 // Alliance - transmettre une lettre de					-> Colara ( SW )
			|| questID == 8898 // Alliance - transmettre une lettre de					-> Colara ( SW )
			|| questID == 8900 // Horde	- transmettre une lettre de					-> Elenia ( UC ) 
			|| questID == 8901 // Horde	- transmettre une lettre de					-> Elenia ( UC ) 
			|| questID == 8902 // Horde	- transmettre une lettre de					-> Elenia ( UC ) 
			|| questID == 8904 // Horde	- suite de quete Horde qui se commence aupre de Fenstad Argyle a UC
			|| questID == 8979 // Horde	- suite de 8904
			|| questID == 8980 // Horde	- suite de 8979
			|| questID == 8982 // Horde	- suite de 8980
			|| questID == 8983 // Horde	- suite de 8982
			|| questID == 8984 // Horde	- suite de 8983
			|| questID == 8981 // Horde	- quete : Faire des cadeaux
			|| questID == 8993 // Alliance - quete : Faire des cadeaux
			|| questID == 9029 // quete: un chaudron Bouillonnant - je crois que c'est la quete de fin Horde/Alliance de la suite de 6 quetes. récompense : des beaux habits
			//
			//  Ci Dessous - les quetes de la fete des morts
			//
			|| questID == 8149
			|| questID == 8150
			//
			//  Ci Dessous - les quetes pour halloween  12
			//
			|| questID == 1658  // Alliance
			|| questID == 8373  // Alliance  
			|| questID == 8311  // Alliance
			|| questID == 8353  // Alliance
			|| questID == 8355  // Alliance
			|| questID == 8356  // Alliance
			|| questID == 8357  // Alliance
			|| questID == 1657  // Horde
			|| questID == 8322  // Horde
			|| questID == 8409  // Horde
			|| questID == 8312  // Horde
			|| questID == 8354  // Horde
			|| questID == 8358  // Horde
			|| questID == 8359  // Horde
			|| questID == 8360  // Horde
			//
			//  Ci Dessous - les quetes pour Lunar Festival  (nouvel an chinois)  7
			//
			|| questID == 8868 // Elune's Blessing - donné par Valadar a Moonglade - Raid ? - il faut tuer Omen - en récompense, donne une lenterne qui permet de placer des rayons de lumiere sur la map
			//|| questID == 8619 // Morndeep the Elder 
			//|| questID == 8635 // Splitrock the Elder 
			//|| questID == 8636 // Rumblerock the Elder 
			//|| questID == 8642 // Silvervein the Elder
			//|| questID == 8651 // Ironband the Elder
			//|| questID == 8727 // Farwhisper the Elder
			//|| questID == 8645 // Obsidian the Elder
			//|| questID == 8643 // Highpeak the Elder
			//|| questID == 8644 // Stonefort the Elder
			//|| questID == 8646 // Hammershout the Elder
			//|| questID == 8647 // Bellowrage the Elder
			//|| questID == 8648 // Darkcore the Elder
			//|| questID == 8649 // Stormbrow the Elder
			//|| questID == 8650 // Snowcrown the Elder
			//|| questID == 8652 // Graveborn the Elder
			//|| questID == 8653 // Goldwell the Elder
			//|| questID == 8654 // Primestone the Elder
			//|| questID == 8670 // Runetotem the Elder
			//|| questID == 8671 // Ragetotem the Elder
			//|| questID == 8672 // Stonespire the Elder
			//|| questID == 8673 // Bloodhoof the Elder	<----- PAS DE YOUHAICOIN CADEAU POUR LES 50 ELDER - ca fait trop
			//|| questID == 8674 // Winterhoof the Elder
			//|| questID == 8675 // Skychaser the Elder
			//|| questID == 8676 // Wildmane the Elder
			//|| questID == 8677 // Darkhorn the Elder
			//|| questID == 8678 // Elder Proudhorn
			//|| questID == 8679 // Grimtotem the Elder
			//|| questID == 8680 // Windtotem the Elder
			//|| questID == 8681 // Thunderhorn the Elder
			//|| questID == 8682 // Skyseer the Elder
			//|| questID == 8683 // Dawnstrider the Elder
			//|| questID == 8684 // Dreamseer the Elder
			//|| questID == 8685 // Mistwalker the Elder
			//|| questID == 8686 // High Mountain the Elder
			//|| questID == 8688 // Windrun the Elder
			//|| questID == 8713 // Starsong the Elder
			//|| questID == 8714 // Moonstrike the Elder
			//|| questID == 8715 // Bladeleaf the Elder
			//|| questID == 8716 // Starglade the Elder
			//|| questID == 8717 // Moonwarden the Elder
			//|| questID == 8718 // Bladeswift the Elder
			//|| questID == 8719 // Bladesing the Elder
			//|| questID == 8720 // Skygleam the Elder
			//|| questID == 8721 // Starweave the Elder
			//|| questID == 8722 // Meadowrun the Elder
			//|| questID == 8723 // Nightwind the Elder
			//|| questID == 8724 // Morningdew the Elder
			//|| questID == 8725 // Riversong the Elder
			//|| questID == 8726 // Brightspear the Elder
			//|| questID == 8866 // Bronzebeard the Elder
			|| questID == 8872 // The Lunar Festival - demande d'aller voir un responsable du Lunar festival dans une des capitale
			|| questID == 8870 // comme 8872
			|| questID == 8871 // comme 8872
			|| questID == 8873 // comme 8872
			|| questID == 8875 // comme 8872
			|| questID == 8867 // suite de 8872 - demande de lancer des feu d'artifices
			|| questID == 8883 // suite de 8867 - demande d'aller voir Valadar a Moonglade
			|| questID == 8878 // quete donnée par Fariel Chantétoile a Moonglade : echange des coin of ancestry contre des cadeaux
			|| questID == 8882 // comme 8878
			|| questID == 8877 // comme 8878
			|| questID == 8880 // comme 8878
			|| questID == 8881 // comme 8878
			|| questID == 8879 // comme 8878
			|| questID == 8876 // comme 8878
			|| questID == 8863 // donné par Valadar a Moonglade
			|| questID == 8862 // donné par Valadar a Moonglade
			|| questID == 8865 // donné par Valadar a Moonglade
			|| questID == 8864 // donné par Valadar a Moonglade
			//
			//  Ci Dessous - les quetes du nouvel an occidental
			//
			|| questID == 8860
			|| questID == 8861
			|| questID == 8827
			//
			//  Ci Dessous - les quetes de la semaine de l'enfant (10)
			//
			|| questID == 172  // - quete coté Horde
			|| questID == 1468 // - quete coté Alliance
			|| questID == 171
			|| questID == 5502
			|| questID == 3861
			|| questID == 925
			|| questID == 910
			|| questID == 911
			|| questID == 558
			|| questID == 1800
			|| questID == 1687
			|| questID == 1479
			|| questID == 1558
			|| questID == 915
			|| questID == 4822
			//
			//  Ci Dessous - les quetes de la fete du feu (1)
			//
			|| questID == 9386
			|| questID == 9319
			|| questID == 9322
			|| questID == 9323
			|| questID == 9324
			|| questID == 9325
			|| questID == 9326
			|| questID == 9330
			|| questID == 9368
			|| questID == 9365
			|| questID == 9339
			|| questID == 9332
			|| questID == 9331
			|| questID == 9367
			|| questID == 9389
			//
			//  Ci Dessous - les quetes de l ouverture des portes anquiraj  22
			//
			//||questID==8795  //PAS DE BONUS YOUHAICOIN
			//||questID==8796  //PAS DE BONUS YOUHAICOIN
			//||questID==8831  //PAS DE BONUS YOUHAICOIN
			//||questID==8833  //PAS DE BONUS YOUHAICOIN
			//||questID==8835  //PAS DE BONUS YOUHAICOIN
			//||questID==8837  //PAS DE BONUS YOUHAICOIN
			//||questID==8839  //PAS DE BONUS YOUHAICOIN
			//||questID==8841  //PAS DE BONUS YOUHAICOIN
			//||questID==8843  //PAS DE BONUS YOUHAICOIN
			//||questID==8845  //PAS DE BONUS YOUHAICOIN
			//
			// Ci Dessous - les quetes de la foire de sombre lune (Drakmoon Faire / Foire de Sombrelune) ( 4 et 5 )
			//
			|| questID == 7905 // mec qui circule dans Iron Forge pour nous dire que la Foire est prete - raporte 5 tickets si on y va.
			|| questID == 7929
			|| questID == 7926
			|| questID == 7939
			|| questID == 7941
			|| questID == 7942
			|| questID == 7946
			|| questID == 7981
			|| questID == 8223
			//
			// Ci Dessous - les quetes du concours de peche   14   15
			//
			//||questID==8229  //PAS DE BONUS YOUHAICOIN
			//||questID==8194  //PAS DE BONUS YOUHAICOIN
			//||questID==8225  //PAS DE BONUS YOUHAICOIN
			//||questID==8193  //PAS DE BONUS YOUHAICOIN
			//
			// Ci Dessous - la quete d'arene de strongleronce  16
			//
			//||questID==7838  //PAS DE BONUS YOUHAICOIN
			//
			//
			// FIN LISTE
			//
			)
		{
			rewardGreyAndGreenAsYellow_event = true;
		}

		// id dans la base de donnée
		const uint32 coinItemID1 = 70010; // YouhaiCoin Paragon
		const uint32 coinItemID2 = 70007; // YouhaiCoin Cadeau


		if (
			//ici mettre la liste d'exception 
			// des quetes qui raportent PAS de youhaicoin :

			// les quetes du vendeur youhainy
			questID < 20000

			// je pense que c'est mieux d'enlever toutes les quete repetable.
			// je pense par exemple a toutes les quete du  style Bone Fragments pour gagner des insigna of the crusade.
			&& !questIsRepeatable

			//je retire les 5 quetes d'ouverture de cadeaux de noel.
			//on a deja plein de youhaicoin dans les cadeaux qu'on ouvre !
			&& questID != 8744
			&& questID != 8768
			&& questID != 8769
			&& questID != 8788
			&& questID != 8803
			&& questID != 8767

			// pas de youhaicoin pour les 50 Elder du nouvel an chinois
			&& questID != 8619 // Morndeep the Elder 
			&& questID != 8635 // Splitrock the Elder 
			&& questID != 8636 // Rumblerock the Elder 
			&& questID != 8642 // Silvervein the Elder
			&& questID != 8651 // Ironband the Elder
			&& questID != 8727 // Farwhisper the Elder
			&& questID != 8645 // Obsidian the Elder
			&& questID != 8643 // Highpeak the Elder
			&& questID != 8644 // Stonefort the Elder
			&& questID != 8646 // Hammershout the Elder
			&& questID != 8647 // Bellowrage the Elder
			&& questID != 8648 // Darkcore the Elder
			&& questID != 8649 // Stormbrow the Elder
			&& questID != 8650 // Snowcrown the Elder
			&& questID != 8652 // Graveborn the Elder
			&& questID != 8653 // Goldwell the Elder
			&& questID != 8654 // Primestone the Elder
			&& questID != 8670 // Runetotem the Elder
			&& questID != 8671 // Ragetotem the Elder
			&& questID != 8672 // Stonespire the Elder
			&& questID != 8673 // Bloodhoof the Elder
			&& questID != 8674 // Winterhoof the Elder
			&& questID != 8675 // Skychaser the Elder
			&& questID != 8676 // Wildmane the Elder
			&& questID != 8677 // Darkhorn the Elder
			&& questID != 8678 // Elder Proudhorn
			&& questID != 8679 // Grimtotem the Elder
			&& questID != 8680 // Windtotem the Elder
			&& questID != 8681 // Thunderhorn the Elder
			&& questID != 8682 // Skyseer the Elder
			&& questID != 8683 // Dawnstrider the Elder
			&& questID != 8684 // Dreamseer the Elder
			&& questID != 8685 // Mistwalker the Elder
			&& questID != 8686 // High Mountain the Elder
			&& questID != 8688 // Windrun the Elder
			&& questID != 8713 // Starsong the Elder
			&& questID != 8714 // Moonstrike the Elder
			&& questID != 8715 // Bladeleaf the Elder
			&& questID != 8716 // Starglade the Elder
			&& questID != 8717 // Moonwarden the Elder
			&& questID != 8718 // Bladeswift the Elder
			&& questID != 8719 // Bladesing the Elder
			&& questID != 8720 // Skygleam the Elder
			&& questID != 8721 // Starweave the Elder
			&& questID != 8722 // Meadowrun the Elder
			&& questID != 8723 // Nightwind the Elder
			&& questID != 8724 // Morningdew the Elder
			&& questID != 8725 // Riversong the Elder
			&& questID != 8726 // Brightspear the Elder
			&& questID != 8866 // Bronzebeard the Elder

			)

		{

			//jaune, c'est tout le temps entre   lvlPlayer-2  et  lvlPlayer+2
			//vert ca depend : pour un player 10, le vert va etre entre 5 et 7	pour un player lvl 50 le vert va etre entre 40 et 47... donc je vais considere que le vert sera entre  lvl-7 et lvl-3

			char typeQuestChar[256];
			strcpy(typeQuestChar, "ERROR");

			int nbCoinToReceiveMax = 0;
			if (!questIsHarder &&	 questLevel >= playerLevel - 2 && questLevel <= playerLevel + 2) // si la quete est jaune 
			{
				strcpy(typeQuestChar, "easy-jaune");
				nbCoinToReceiveMax = 1;
			}
			else if (!questIsHarder &&  questLevel >= playerLevel + 3)  // si la quete est orange ou plus
			{
				strcpy(typeQuestChar, "easy-orange");
				nbCoinToReceiveMax = 2;
			}
			else if (questIsHarder &&	 questLevel >= playerLevel - 7 && questLevel <= playerLevel - 3) // si la quete est dongeon et verte
			{
				strcpy(typeQuestChar, "hard-vert");
				nbCoinToReceiveMax = 1;
			}
			else if (questIsHarder &&	questLevel >= playerLevel - 2 && questLevel <= playerLevel + 2) // si la quete est dongeon et jaune
			{
				strcpy(typeQuestChar, "hard-jaune");
				nbCoinToReceiveMax = 2;
			}
			else if (questIsHarder &&	questLevel >= playerLevel + 3)  // si la quete est dongeon et orange ou plus
			{
				strcpy(typeQuestChar, "hard-orange");
				nbCoinToReceiveMax = 3;
			}
			else
			{
				strcpy(typeQuestChar, "tooEasy");
				nbCoinToReceiveMax = 0;
			}



			if (rewardGreyAndGreenAsYellow_event)
			{
				if (nbCoinToReceiveMax < 2)
				{
					nbCoinToReceiveMax = 2;
				}
			}



			int nbCoinToReceiveReally = rand() % (nbCoinToReceiveMax + 1);	 //  0 to nbCoinToReceive

			sLog->outBasic("RICHAR:  add coin in quest reward - player=%d questLvl=%d quest=%s nbCoin=%d/%d",
				playerLevel,
				questLevel,
				typeQuestChar,
				nbCoinToReceiveReally, nbCoinToReceiveMax
			);



			char prefix[32];
			prefix[0] = 0;

			if (rewardGreyAndGreenAsYellow_event)
			{
				//rajouter ca me permet de voir si les quete sont dans la bonne catégorie :  event ou pas  event
				sprintf_s(prefix, "event - ");
			}


			if (nbCoinToReceiveReally > 0)
			{
				uint32 newCoin_ = urand(0, 1) == 0 ? coinItemID1 : coinItemID2;

				ItemPosCountVec dest;
				if (player____->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, newCoin_, nbCoinToReceiveReally) == EQUIP_ERR_OK)
				{
					Item* item = player____->StoreNewItem(dest, newCoin_, true, Item::GenerateItemRandomPropertyId(newCoin_));
					player____->SendNewItem(item, nbCoinToReceiveReally, true, false);

					if (newCoin_ == coinItemID1)
					{
						char messageOut[2048];
						sprintf(messageOut, "%s+%d/%d youhaicoin paragon!", prefix, nbCoinToReceiveReally, nbCoinToReceiveMax);
						player____->Say(messageOut, LANG_UNIVERSAL);
					}
					else
					{
						char messageOut[2048];
						sprintf(messageOut, "%s+%d/%d youhaicoin cadeau!", prefix, nbCoinToReceiveReally, nbCoinToReceiveMax);
						player____->Say(messageOut, LANG_UNIVERSAL);
					}
				}
				else
				{
					if (newCoin_ == coinItemID1)
					{
						char messageOut[2048];
						sprintf(messageOut, "ERREUR : je n'ai pas recu mes %d youhaicoin paragon car inventaire plein", nbCoinToReceiveReally);
						player____->Say(messageOut, LANG_UNIVERSAL);
					}
					else
					{
						char messageOut[2048];
						sprintf(messageOut, "ERREUR : je n'ai pas recu mes %d youhaicoin cadeau car inventaire plein", nbCoinToReceiveReally);
						player____->Say(messageOut, LANG_UNIVERSAL);
					}
				}




			}
			else if (nbCoinToReceiveReally == 0 && nbCoinToReceiveMax > 0)
			{
				char messageOut[2048];
				sprintf(messageOut, "%s+%d/%d youhaicoin :(", prefix, nbCoinToReceiveReally, nbCoinToReceiveMax);
				player____->Say(messageOut, LANG_UNIVERSAL);
			}

		}


		//cas special du paragon
		if (questID == 20001)
		{
			uint8 questGiverType = questGiver->GetTypeId();
			Unit* quesGiverUnit = 0;
			if (questGiverType == TYPEID_UNIT)
			{
				quesGiverUnit = dynamic_cast<Unit*>(questGiver);
				if (quesGiverUnit)
				{

					int aa = 0;

				}
				else
				{
					player____->Say("ERREUR 632 : en parler a Richard", LANG_UNIVERSAL);
				}
			}


			int currentParagonLvl = player____->m_richa.GetParagonLevelFromItem();

			const int spellParagonIDBase = 94000; // <-- attention : pas le meme ID entre CLASSIC et WOTLK

			//bool paragonPasse = false;
			//for(int i=1; i<100; i++)

			if (currentParagonLvl >= 2)
			{
				//int countitem = GetItemCount(71000+i);
				//if ( countitem >= 1 ) // normallement c'est juste 0  ou 1
				{

					//if ( countitem > 1 )
					//{
					//	//etrange
					//	int aaaaaaaaaaaaaaaaaaaaaaaa=0;
					//}

					player____->DestroyItemCount(71000 + currentParagonLvl, 1, true);

					int newItemId = 71000 + currentParagonLvl + 1;

					//ItemPrototype const* pProto = ObjectMgr::GetItemPrototype(newItemId);
					ItemTemplate const* pProto = sObjectMgr->GetItemTemplate(newItemId);

					if (!pProto)
					{
						//si on arrive la, il faut surement creer des nouveau template item /spell paragon

						// si j'ai cette erreur, il faudra donner manuellement l'item paragon au joueur
						// normallement ses YCP auront deja été déduie, et son ancien item paragon deja detruit

						char messageOut[2048];
						sprintf(messageOut, "ERREUR 48 - ne plus toucher a rien et en parler a Richard");

						if (quesGiverUnit)
							quesGiverUnit->MonsterSay(messageOut, LANG_UNIVERSAL, nullptr);


						sLog->outBasic("RICHAR ERROR : item %d (item paragon %d) pas trouve ---------------------------------------------------------------", newItemId, currentParagonLvl + 1);
					}
					else
					{

						ItemPosCountVec dest;
						int nbCoinToReceiveReally = 1;
						int newItemreceived = newItemId;
						if (player____->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, newItemreceived, nbCoinToReceiveReally) == EQUIP_ERR_OK)
						{
							Item* item = player____->StoreNewItem(dest, newItemreceived, true, Item::GenerateItemRandomPropertyId(newItemreceived));
							player____->SendNewItem(item, nbCoinToReceiveReally, true, false);

							char messageOut[2048];
							sprintf(messageOut, "%s, Vous passez Paragon %d ! (-%d YCP)",  GetName().c_str(),   currentParagonLvl+1  ,  (currentParagonLvl % 2) ? 5 : 4 );

							// petit warning quand on arrive a la limite, ca fait pas de mal
							if (sObjectMgr->GetItemTemplate(newItemId + 5) == nullptr)
							{
								strcat(messageOut, " -- ATTENTION on arrive bientot a la limite !!!! ");
							}


							if (quesGiverUnit)
							{
								quesGiverUnit->MonsterSay(messageOut, LANG_UNIVERSAL, nullptr);


							}

							// spell Paragon Up
							if (SpellEntry const* spellProto = sSpellStore.LookupEntry(spellParagonIDBase))
							{
								//player____->CastSpell(this, spellProto, TRIGGERED_OLD_TRIGGERED);
								player____->CastSpell(player____, spellParagonIDBase);
							}


							//on retire le spell du paragon precedent pour pas que le joueur stack les paragon
							//player____->RemoveAurasDueToSpellByCancel(spellParagonIDBase + currentParagonLvl);
							player____->RemoveAura(spellParagonIDBase + currentParagonLvl);


						}
						else
						{
							//ca ne devrait pas arriver car en principe on retire l'item precedent, ce qui libere une place

							char messageOut[2048];
							sprintf(messageOut, "ERREUR 47A - inventaire plein - ne plus toucher a rien et en parler a Richard");

							if (quesGiverUnit)
								quesGiverUnit->MonsterSay(messageOut, LANG_UNIVERSAL,nullptr);

							sLog->outBasic("RICHAR ERROR 47B : item %d pas donne car inventaire full ---------------------------------------------------------------", newItemId);
						}



					}


					//comme c'est 4.5 youhaicon paragon par level, a tous les niveau pair, on doit donner un YCP au joueur
					if (currentParagonLvl % 2 == 0)
					{
						ItemPosCountVec dest;
						int nbCoinToReceiveReally = 1;
						const int newItemreceived = coinItemID1;
						if (player____->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, newItemreceived, nbCoinToReceiveReally) == EQUIP_ERR_OK)
						{
							Item* item = player____->StoreNewItem(dest, newItemreceived, true, Item::GenerateItemRandomPropertyId(newItemreceived));
							player____->SendNewItem(item, nbCoinToReceiveReally, true, false);
						}
						else
						{
							char messageOut[2048];
							sprintf(messageOut, "ERREUR 147 - inventaire plein - ne plus toucher a rien et en parler a Richard");

							if (quesGiverUnit)
								quesGiverUnit->MonsterSay(messageOut, LANG_UNIVERSAL, nullptr);

							sLog->outBasic("RICHAR ERROR 149 : item %d pas donne car inventaire full ---------------------------------------------------------------", newItemreceived);
						}
					}


					//paragonPasse = true;
					//break;
				}
			}


			else
			{


				int newItemId = 71000 + 2;

				ItemPosCountVec dest;
				int nbCoinToReceiveReally = 1;
				int newItemreceived = newItemId;
				if (player____->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, newItemreceived, nbCoinToReceiveReally) == EQUIP_ERR_OK)
				{
					Item* item = player____->StoreNewItem(dest, newItemreceived, true, Item::GenerateItemRandomPropertyId(newItemreceived));
					player____->SendNewItem(item, nbCoinToReceiveReally, true, false);

					char messageOut[2048];
					sprintf(messageOut, "Vous passez Paragon 2 !");

					if (quesGiverUnit)
					{
						quesGiverUnit->MonsterSay(messageOut, LANG_UNIVERSAL, nullptr);


					}

					// spell Paragon Up
					if (SpellEntry const* spellProto = sSpellStore.LookupEntry(spellParagonIDBase))
					{
						player____->CastSpell(player____, spellParagonIDBase);
					}

				}
				else
				{
					char messageOut[2048];
					sprintf(messageOut, "ERREUR 51 - inventaire plein - ne plus toucher a rien et en parler a Richard");

					if (quesGiverUnit)
						quesGiverUnit->MonsterSay(messageOut, LANG_UNIVERSAL, nullptr);

					sLog->outBasic("RICHAR ERROR 51 : item %d pas donne car inventaire full ---------------------------------------------------------------", newItemId);
				}




				//si on trouve pas d'item, on va considerer qu'on passe paragon 2.
				//dans le doute, j'ecris un petit warning dans le log
				sLog->outBasic("RICHAR WARNING : pas d'item paragon trouve - si le joueur passe vraiment de paragon 1 a 2, alors c est normal.");
			}
		}


		//dans le cas des 50 Elder, pour le nouvel an chinois, on sauvegarde 
		if (
			questID == 8619 // Morndeep the Elder 
			|| questID == 8635 // Splitrock the Elder 
			|| questID == 8636 // Rumblerock the Elder 
			|| questID == 8642 // Silvervein the Elder
			|| questID == 8651 // Ironband the Elder
			|| questID == 8727 // Farwhisper the Elder
			|| questID == 8645 // Obsidian the Elder
			|| questID == 8643 // Highpeak the Elder
			|| questID == 8644 // Stonefort the Elder
			|| questID == 8646 // Hammershout the Elder
			|| questID == 8647 // Bellowrage the Elder
			|| questID == 8648 // Darkcore the Elder
			|| questID == 8649 // Stormbrow the Elder
			|| questID == 8650 // Snowcrown the Elder
			|| questID == 8652 // Graveborn the Elder
			|| questID == 8653 // Goldwell the Elder
			|| questID == 8654 // Primestone the Elder
			|| questID == 8670 // Runetotem the Elder
			|| questID == 8671 // Ragetotem the Elder
			|| questID == 8672 // Stonespire the Elder
			|| questID == 8673 // Bloodhoof the Elder
			|| questID == 8674 // Winterhoof the Elder
			|| questID == 8675 // Skychaser the Elder
			|| questID == 8676 // Wildmane the Elder
			|| questID == 8677 // Darkhorn the Elder
			|| questID == 8678 // Elder Proudhorn
			|| questID == 8679 // Grimtotem the Elder
			|| questID == 8680 // Windtotem the Elder
			|| questID == 8681 // Thunderhorn the Elder
			|| questID == 8682 // Skyseer the Elder
			|| questID == 8683 // Dawnstrider the Elder
			|| questID == 8684 // Dreamseer the Elder
			|| questID == 8685 // Mistwalker the Elder
			|| questID == 8686 // High Mountain the Elder
			|| questID == 8688 // Windrun the Elder
			|| questID == 8713 // Starsong the Elder
			|| questID == 8714 // Moonstrike the Elder
			|| questID == 8715 // Bladeleaf the Elder
			|| questID == 8716 // Starglade the Elder
			|| questID == 8717 // Moonwarden the Elder
			|| questID == 8718 // Bladeswift the Elder
			|| questID == 8719 // Bladesing the Elder
			|| questID == 8720 // Skygleam the Elder
			|| questID == 8721 // Starweave the Elder
			|| questID == 8722 // Meadowrun the Elder
			|| questID == 8723 // Nightwind the Elder
			|| questID == 8724 // Morningdew the Elder
			|| questID == 8725 // Riversong the Elder
			|| questID == 8726 // Brightspear the Elder
			|| questID == 8866 // Bronzebeard the Elder
			)
		{
			// 1ere etape, on sauvegarde que ce personnage a rendu la quete pour cette année

			time_t t = time(0);   // get time now
			struct tm * now = localtime(&t);
			int day = now->tm_mday;
			int mon = now->tm_mon + 1;
			int yea = now->tm_year + 1900;


			//on verifie qu'il existe pas deja
			bool trouveePourCetteQueteEtCetteAnnee = false;
			unsigned int anneeLaPlusHaute = 0; // année la plus recente ou ce personnage a rendu la quete auprès de cet Elder
			for (int i = 0; i < player____->m_richa.m_richa_lunerFestivalElderFound.size(); i++)
			{
				if (player____->m_richa.m_richa_lunerFestivalElderFound[i].year == yea &&
					player____->m_richa.m_richa_lunerFestivalElderFound[i].questId == questID)
				{
					trouveePourCetteQueteEtCetteAnnee = true;
					//break;
				}

				if (player____->m_richa.m_richa_lunerFestivalElderFound[i].questId == questID
					&& player____->m_richa.m_richa_lunerFestivalElderFound[i].year > anneeLaPlusHaute
					)
				{
					anneeLaPlusHaute = player____->m_richa.m_richa_lunerFestivalElderFound[i].year;
				}
			}

			if (!trouveePourCetteQueteEtCetteAnnee)
			{
				player____->m_richa.m_richa_lunerFestivalElderFound.push_back(PlayerModeDataRicha::RICHA_LUNARFESTIVAL_ELDERFOUND(yea, questID));
			}
			else
			{
				char messageOut[4096];
				sprintf(messageOut, "ERREUR 5321 - existe deja cette annee ???");
				player____->Say(messageOut, LANG_UNIVERSAL);
			}

			if (anneeLaPlusHaute == 0)
			{


				int nbPointGagne = 2;

				player____->m_richa.m_richa_scoreElderCourse += nbPointGagne;

				char messageOut[4096];
				sprintf(messageOut, "Je n'ai jamais rencontre cet Ancien. Je gagne %d point. Mon score passe a %d",
					nbPointGagne,
					player____->m_richa.m_richa_scoreElderCourse
				);
				player____->Say(messageOut, LANG_UNIVERSAL);
			}
			else
			{
				int nbPointGagne = 1;

				// nombre d'années depuis que je l'ai pas vu
				// nombre entre 1  et  N
				int nbAnneDepuisDerniereVisite = (yea - anneeLaPlusHaute);


				player____->m_richa.m_richa_scoreElderCourse += nbPointGagne;

				char messageOut[4096];
				sprintf(messageOut, "la derniere fois c'etait en %d. Je gagne %d point. Mon score passe a %d",
					anneeLaPlusHaute,
					nbPointGagne,
					player____->m_richa.m_richa_scoreElderCourse
				);
				player____->Say(messageOut, LANG_UNIVERSAL);
			}

			//etant donné que   m_richa_scoreElderCourse  n'est pas sauvegardé,  si jamais un joueur deco sans faire expres
			//c'est pas mal d'ecrire regulierement son score dans la console du server, pour le garder qqpart
			char messageOut[4096];
			sprintf(messageOut, "RICHA ELDER -------- le score Elder de %s passe a %d", GetName(), player____->m_richa.m_richa_scoreElderCourse);
			sLog->outBasic(messageOut);



			// 2ieme etape, on ecrit un feedback au joueur pour savoir si d'autre perso a lui on deja fait cette quete d'autre années
			//			  c'est juste un feedback pour donner une info - cette etape ne modifie rien
			//
			{
				std::vector<int>  associatedPlayerGUID;
				// #LISTE_ACCOUNT_HERE   -  ce hashtag repere tous les endroit que je dois updater quand je rajoute un nouveau compte - ou perso important
				//                     pour WOTLK, dans un premier temps, il n'y aura que 1 perso principal par joueur, donc pas besoin de ces linkage
				/*
				{
					if (player____->GetGUIDLow() == 4)// boulette
					{
						associatedPlayerGUID.push_back(27); // Bouzigouloum
					}
					if (player____->GetGUIDLow() == 27)//  Bouzigouloum 
					{
						associatedPlayerGUID.push_back(4); // boulette
					}
					if (player____->GetGUIDLow() == 5)// Bouillot
					{
						associatedPlayerGUID.push_back(28); // Adibou
					}
					if (player____->GetGUIDLow() == 28)// Adibou 
					{
						associatedPlayerGUID.push_back(5); //  Bouillot
					}

					//juste pour le debug je vais lier grandjuge et grandtroll
					if (player____->GetGUIDLow() == 19)// grandjuge
					{
						associatedPlayerGUID.push_back(29); // grandtroll
					}
					if (player____->GetGUIDLow() == 29)// grandtroll 
					{
						associatedPlayerGUID.push_back(19); //  grandjuge
					}
				}
				*/

				std::map<int, int> queteConnuEnTout; // sans prendre en compte l annee  -  je n'utilise pas le right
				std::map<int, int> queteConnuCetteAnnee; // cette l annee   -  je n'utilise pas le right

				// on rempli deja avec le perso courant
				for (int i = 0; i < player____->m_richa.m_richa_lunerFestivalElderFound.size(); i++)
				{
					queteConnuEnTout[player____->m_richa.m_richa_lunerFestivalElderFound[i].questId] = 0;

					if (player____->m_richa.m_richa_lunerFestivalElderFound[i].year == yea)
					{
						queteConnuCetteAnnee[player____->m_richa.m_richa_lunerFestivalElderFound[i].questId] = 0;
					}
				}

				// ensuite on rempli avec son / ses perso associé au meme joueur
				for (int i = 0; i < associatedPlayerGUID.size(); i++)
				{
					std::vector<PlayerModeDataRicha::RICHA_NPC_KILLED_STAT> richa_NpcKilled;
					std::vector<PlayerModeDataRicha::RICHA_PAGE_DISCO_STAT> richa_pageDiscovered;
					std::vector<PlayerModeDataRicha::RICHA_LUNARFESTIVAL_ELDERFOUND> richa_lunerFestivalElderFound;
					std::vector<PlayerModeDataRicha::RICHA_MAISON_TAVERN> richa_maisontavern;
					std::vector<PlayerModeDataRicha::RICHA_ITEM_LOOT_QUEST> richa_lootquest;
					std::string persoNameImport;
					PlayerModeDataRicha::richa_importFrom_richaracter_(
						associatedPlayerGUID[i],
						richa_NpcKilled,
						richa_pageDiscovered,
						richa_lunerFestivalElderFound,
						richa_maisontavern,
						richa_lootquest,
						persoNameImport
					);


					for (int i = 0; i < richa_lunerFestivalElderFound.size(); i++)
					{
						queteConnuEnTout[richa_lunerFestivalElderFound[i].questId] = 0;

						if (richa_lunerFestivalElderFound[i].year == yea)
						{
							queteConnuCetteAnnee[richa_lunerFestivalElderFound[i].questId] = 0;
						}
					}

				}//pour chaque perso associé

				char messageOut[4096];
				sprintf(messageOut, "Cette annee : %d/50 / En tout %d/50", queteConnuCetteAnnee.size(), queteConnuEnTout.size());

				//pour l'instant je mets en commentaire ce feedback pour pas qu'il rentre en conflit avec le Say() dit précédement par le Joueur.
				//Say(messageOut, LANG_UNIVERSAL);


			}


		}
	} // END : add coin in quest reward

	////////////////////////////////////////////////////////////////////////////////



}



void OnSave(Player* player) override
{
	sLog->outBasic("critical part START - Player::SaveToDB (%s)", GetName().c_str() ); // s'il y a un crash pdt cette partie, ca peut etre grave

	/////////////////////////////////////////////////////////////////////////////////////////////////
	//RICHARD - auto save of _ri_character_
	//ObjectGuid const& guiiddd = player->GetObjectGuid();
	//uint64 guid = guiiddd.GetRawValue();

	uint64 guid = player->GetGUID();

	PlayerModeDataRicha::richa_exportTo_richaracter_(
		guid,
		player->m_richa.m_richa_NpcKilled,
		player->m_richa.m_richa_pageDiscovered,
		player->m_richa.m_richa_lunerFestivalElderFound,
		player->m_richa.m_richa_ListeMaison,
		player->m_richa.m_richa_itemLootQuests,
		player->GetName().c_str()
	);

	player->m_richa.richa_exportTo_ristat_();

	time_t t = time(0);   // get time now
	struct tm * now = localtime(&t);



	sLog->outBasic("critical part END (%02d:%02d) - Player::SaveToDB (%s)", now->tm_hour, now->tm_min, GetName().c_str());
	/////////////////////////////////////////////////////////////////////////////////////////////////



}

void OnLogout(Player* player) override
{
	int a=0;
	return;
}

void OnCreatureKilledByPet(Player* killer, Creature* victim) override
{
	OnCreatureKill(killer, victim);
}

void OnCreatureKill(Player* killer, Creature* victim) override
{


	int a=0;




	////////////////////////////////////////////////////////////////////////////////////
	//  RICHARD  ---  quand on KILL une creature
	//  mettre ici toutes les custom action de quand on tue une creature

	if (


		/*
		// si le tuer est un joueur
		GetTypeId() == TYPEID_PLAYER
		|| GetOwner() && GetOwner()->GetTypeId() == TYPEID_PLAYER   // ca arrive quand c'est un pet du joueur qui donne le coup de grace
		|| responsiblePlayer
		*/



		true
		)
	{


		Player* thisPLayer = 0; // ceci est le joueur qui sera considere par moi comme le vrai tuer qui merrite la récompense


								/*
		if (GetTypeId() == TYPEID_PLAYER)
		{
			thisPLayer = ((Player*)this);
		}
		else if (GetOwner() && GetOwner()->GetTypeId() == TYPEID_PLAYER)
		{
			//ce cas arrive quand un de nos pet tue un PNJ
			const char* nameThis = GetName();
			thisPLayer = (Player*)GetOwner();
		}
		else if (responsiblePlayer)
		{
			//ce cas est assez rare mais devrait arriver dans 2 cas :
			// - un garde d'une ville tue un mob qu'on a aggro
			// - pendant une quete d'escorte, l'escorté tue un mob
			thisPLayer = responsiblePlayer;
		}
		else
		{
			int aaa = 0; // on devrait pas etre ici ??
		}


		if (responsiblePlayer != thisPLayer)
		{
			const char* name1 = 0;
			const char* name2 = 0;

			if (responsiblePlayer)
			{
				name1 = responsiblePlayer->GetName();
			}

			if (thisPLayer)
			{
				name2 = thisPLayer->GetName();
			}



			// ceci arrive souvent quand on est groupé,
			// on aura  name1 = perso de Dian, et name2 = perso de richar
			// par convention, ce bout de code ne va utiliser que  thisPLayer  et pas   responsiblePlayer
			// a surveiller, mais je pense que ca changerai pas grand chose si je faisais l'inverse.  

			//int aaaa=0;
			//sLog->outBasic("RICHAR WARNING !!!!!!!!!!!!!!!!!!! - TML35018 !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" );
			//Sleep(20000);


			int aaa = 0;
		}
		*/
		thisPLayer = killer; // pour azecore, je simplifie par rapport a cmangos




		const char* namePlayer___ = thisPLayer->GetName().c_str();

		//ObjectGuid playerGUID___2 = thisPLayer->GetObjectGuid();
		uint64_t playerGUID___2 = thisPLayer->GetGUID();

		uint32 player_account = sObjectMgr->GetPlayerAccountIdByGUID(playerGUID___2);
		
		uint32 Victime_rank = victim->GetCreatureTemplate()->rank;
		uint32 Victime_entry = victim->GetEntry(); //  npc=XXX

		Group* thisPlayer_group = thisPLayer->GetGroup();
		std::vector<Player*> groupMembers;
		if (thisPlayer_group)
		{
			int groupSize = thisPlayer_group->GetMembersCount();

			int groupSize2 = 0;

			for (GroupReference* itr = thisPlayer_group->GetFirstMember(); itr != nullptr; itr = itr->next())
			{
				Player* Target = itr->GetSource();

				// IsHostileTo check duel and controlled by enemy
				if (Target
					//&& Target != thisPLayer 
					)
					groupMembers.push_back(Target);

				groupSize2++;
			}




			if (groupSize2 != groupSize)
			{
				//ce peut arriver par example si Dian_e a été deconnecté.
				//du coup, la taille du groupe sera 2.
				//mais quand on enum les joueurs, il n'y a que Richar_d
				//donc rien de mechant si j'ai ce WARNING a cause de ca.
				int aaaa = 0;
				sLog->outBasic("RICHAR WARNING !!!! %d != %d !!!!!!!!!!!!!!! - TML35118 !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!",
					groupSize2, groupSize
				);
				//Sleep(10000);
			}

			int	aaaaa = 0;
		}
		else
		{
			groupMembers.push_back(thisPLayer);
		}


		if (Victime_rank == CREATURE_ELITE_RARE)
		{



			std::vector<int>  mainPlayerGUID;
			std::vector<std::string>  mainPlayerNames;





			// #LISTE_ACCOUNT_HERE   -  ce hashtag repere tous les endroit que je dois updater quand je rajoute un nouveau compte - ou perso important
			//
			//list de tous les perso principaux de tout le monde
			//mainPlayerGUID.push_back(4);  mainPlayerNames.push_back("Boulette");
			//mainPlayerGUID.push_back(5);  mainPlayerNames.push_back("Bouillot");  <---- TODO pour WOTLK quand on aura créé nos persos
			{
				char messageOut[2048];
				sprintf(messageOut, "ATTENTION! PAS DE LISTE DE PERSO !! TODO !!!!");
				thisPLayer->Yell(messageOut, LANG_UNIVERSAL);
			}




			int existInDataBaseV2 = -1;
			for (int jj = 0; jj < mainPlayerGUID.size(); jj++)
			{
				std::vector<PlayerModeDataRicha::RICHA_NPC_KILLED_STAT> richa_NpcKilled;
				std::vector<PlayerModeDataRicha::RICHA_PAGE_DISCO_STAT> richa_pageDiscovered;
				std::vector<PlayerModeDataRicha::RICHA_LUNARFESTIVAL_ELDERFOUND> richa_lunerFestivalElderFound;
				std::vector<PlayerModeDataRicha::RICHA_MAISON_TAVERN> richa_maisontavern;
				std::vector<PlayerModeDataRicha::RICHA_ITEM_LOOT_QUEST> richa_lootquest;
				std::string persoNameImport;
				PlayerModeDataRicha::richa_importFrom_richaracter_(
					mainPlayerGUID[jj],
					richa_NpcKilled,
					richa_pageDiscovered,
					richa_lunerFestivalElderFound,
					richa_maisontavern,
					richa_lootquest,
					persoNameImport
				);

				for (int kk = 0; kk < richa_NpcKilled.size(); kk++)
				{
					if (richa_NpcKilled[kk].npc_id == Victime_entry)
					{
						existInDataBaseV2 = jj;
						break;
					}
				}

				if (existInDataBaseV2 != -1) { break; }
			}

			if (existInDataBaseV2 == -1)
			{
				bool pushedDone = false;

				//pour chaque player du groupe
				for (int i = 0; i < groupMembers.size(); i++)
				{

					//1PA si notre perso est niveau  >=1  et  <10   
					//10PA si notre perso est niveau  >=10  et  <20   
					//50PA si notre perso est niveau  >=20  et  <30 
					//1PO si notre perso est niveau  >=30  et  <40 
					//2PO si notre perso est niveau  >=40  et  <50 
					//4PO si notre perso est niveau  >=50  et  <60 
					//5PO pour 60

					int lvlPlayer = groupMembers[i]->getLevel();
					int winPO = 0;
					if (lvlPlayer < 10) { winPO = 1 * 100; }
					if (lvlPlayer >= 10 && lvlPlayer < 20) { winPO = 10 * 100; }
					if (lvlPlayer >= 20 && lvlPlayer < 30) { winPO = 50 * 100; }
					if (lvlPlayer >= 30 && lvlPlayer < 40) { winPO = 1 * 100 * 100; }
					if (lvlPlayer >= 40 && lvlPlayer < 50) { winPO = 2 * 100 * 100; }
					if (lvlPlayer >= 50 && lvlPlayer < 60) { winPO = 4 * 100 * 100; }
					if (lvlPlayer >= 60) { winPO = 5 * 100 * 100; }

					groupMembers[i]->ModifyMoney(winPO);

					int goldAmount = winPO;
					int nbpo = goldAmount / 10000;
					int nbpa = (goldAmount - nbpo * 10000) / 100;
					int nbpc = (goldAmount - nbpo * 10000 - nbpa * 100);

					uint32 groupMember_account = sObjectMgr->GetPlayerAccountIdByGUID(groupMembers[i]->GetGUID());

					char messageOut[2048];
					sprintf(messageOut, "Elite gris decouvert ! + %d-%d-%d !", nbpo, nbpa, nbpc);
					groupMembers[i]->Say(messageOut, LANG_UNIVERSAL);

				}

			}
			else
			{
				char messageOut[2048];
				sprintf(messageOut, "Cet Elite Gris a DEJA ete decouvert par %s", mainPlayerNames[existInDataBaseV2].c_str());
				thisPLayer->Say(messageOut, LANG_UNIVERSAL);
			}

		} // si elite gris



		//on chercher si  Victime_entry  est dans  m_richa_NpcKilled
		bool existInDataBase = false;
		for (int i = 0; i < thisPLayer->m_richa.m_richa_NpcKilled.size(); i++)
		{
			if (thisPLayer->m_richa.m_richa_NpcKilled[i].npc_id == Victime_entry)
			{
				sLog->outBasic("RICHAR INFO - %s - %d  %d->%d", thisPLayer->GetName(), Victime_entry, thisPLayer->m_richa.m_richa_NpcKilled[i].nb_killed, thisPLayer->m_richa.m_richa_NpcKilled[i].nb_killed + 1);
				thisPLayer->m_richa.m_richa_NpcKilled[i].nb_killed++; // on incremente le nb de killed
				existInDataBase = true;
				break;
			}
		}

		if (!existInDataBase)
		{
			sLog->outBasic("RICHAR INFO - %s - %d  1", thisPLayer->GetName(), Victime_entry);
			thisPLayer->m_richa.m_richa_NpcKilled.push_back(PlayerModeDataRicha::RICHA_NPC_KILLED_STAT(Victime_entry, 1));
		}


	}//si l'attaquant / tueur  est un joueur

	// DU COUP , j'ai changé : CE CAS SI DESSOUS EST GERE AU DESSUS
	/*
	else if ( responsiblePlayer )
	{
		//c'est pas du tout normal d'arriver la. ca devrait etre géré par le if precedent

		//c'est arrivé une fois j'ai pas bien compris,
		//je vais rajouter plus d'info pour debugger la prochaine fois :

		// je CROIS que ce "bug" arrive quand un Garde tue un mob qu'on a aggro
		// si c'est le cas , c'est tellement rare que c'est pas bien grave
		// a surveiller
		// a surveiller aussi dans une quete d'escorte comment ca se passe si l'escorté kill le mob
		//le joueur que le jeux considere responsable de la mort
		const char* name1 = responsiblePlayer->GetName();

		//le mob qui est mort
		const char* name2 = 0;
		if ( victim )
		{
			name2 = victim->GetName();
		}
		//celui qui a tué le mob
		const char* name3 = this->GetName();
		uint8 typeIdthis__ = this->GetTypeId();
		int aaaa=0;
		sLog->outBasic("RICHAR WARNING !!!!!!!!!!!!!!!!!!! - TML35019 !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" );
		Sleep(20000);
		int adddaaa=0;
	}
	*/

	// richar - END
	////////////////////////////////////////////////////////////////////////////////////








}


};

void AddMyPlayerScripts()
{
	new MyPlayer();
}



//////////////////////////////////////////////////////////////////////////////////////////
