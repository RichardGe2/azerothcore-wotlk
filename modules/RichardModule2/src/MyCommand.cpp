

#include "ScriptMgr.h"
#include "Player.h"
#include "Configuration/Config.h"
#include "Chat.h"
#include "RichardClass.h"
#include "MapManager.h"
#include "Language.h"

class MyCommand : public CommandScript
{
public:

	MyCommand() : CommandScript("MyCommand")
	{
		//verifier qu'on lance pas le serveur plusieurs fois
		std::ifstream infile("RICHARDS_WOTLK/securityDoubleBoot.txt");
		if (  infile.good() )
		{
			infile.close();
			// error
			for(int i=0; ;i++)
			{
				sLog->outString("ERROR Serveur lance plusieurs fois ??? (ou mal ferme la derniere fois) (RICHARDS_WOTLK/securityDoubleBoot.txt) \n");
				Sleep(1000);
			}
		}
		else
		{
			// create it
			 std::ifstream infile2("RICHARDS_WOTLK/securityDoubleBoot.txt", std::ios_base::app);
			 infile2.close();
		}
	}

	~MyCommand() 
	{
		BOOL ret = DeleteFileA("RICHARDS_WOTLK/securityDoubleBoot.txt");
		if ( ret )
		{
			int a=0; // success
		}
		else
		{
			int a=0;
		}
		int a=0;
	}


	std::vector<ChatCommand> GetCommands() const override
	{
		static std::vector<ChatCommand> commandTable =
		{
			{ "exi",			 SEC_CONSOLE,	  true,   &HandleServerShutDownCommand_RICHA,		 "" },
			{ "okwin",			 SEC_PLAYER,	  true,   &HandleRichardCommand_clearLootWinners,		 "" },
			{ "stat",			 SEC_PLAYER,	  true,   &Richar_tellMobStats,		 "" },
			{ "notincombat",			 SEC_PLAYER,	  true,   &Richar_noMoreInComat,		 "" },

			{ "richardhelp",			 SEC_PLAYER,	  true,   &Richar_help,		 "" },
			{ "helprichard",			 SEC_PLAYER,	  true,   &Richar_help,		 "" },
			{ "richard",				 SEC_PLAYER,	  true,   &Richar_help,		 "" },

			{ "need",			 SEC_PLAYER,	  true,   &Richar_need,		 "" },
			{ "killrichard",   SEC_PLAYER,	  true,   &HandleCommandRicha__killrichard,		 "" },

			{ "rigocreature",   SEC_MODERATOR,	  true,   &HandleCommandRicha__GoCreatureCommand,		 "" },
			{ "rigo",             SEC_MODERATOR,          false, &HandleCommandRicha__GoPlayerCommand,                "" },
		};
		return commandTable;
	}

	static bool HandleCommandRicha__GoPlayerCommand(ChatHandler* handler, char const* arg___)
	{
		if (!*arg___)
			return false;

		Player* player = handler->GetSession()->GetPlayer();

		if ( strlen(arg___) > 4096 )
		{
			char messageee[2048];
			sprintf(messageee, "ERROR ARG 4096 - A\n");
			ChatHandler(player->GetSession()).SendSysMessage(messageee);
			return false;
		}

		char arg[4096];
		strcpy_s(arg,arg___);

		char comm[4096];
		sprintf(comm,".appear %s",arg);

		player->Say(comm,LANG_UNIVERSAL);

		int a=0;

		return true;
	}


	static bool HandleCommandRicha__GoCreatureCommand(ChatHandler* handler, char const* args)
	{
		//
		// je ne peux pas mettre d'espace, sinon la commande va etre coupée.
		// du coup, a la place des espaces, mettre des  #   
		//

		if (!*args)
			return false;

		Player* player = handler->GetSession()->GetPlayer();

		// "id" or number or [name] Shift-click form |color|Hcreature_entry:creature_id|h[name]|h|r
		char* param1 = handler->extractKeyFromLink((char*)args, "Hcreature");
		if (!param1)
			return false;

		std::ostringstream whereClause;

		std::string name = param1;

		// enlever les majuscules
		// remplacer les # par des espaces
		for(int iii=0; iii<name.size(); iii++)
		{
			if ( name[iii] >= 'A' && name[iii] <= 'Z' )
			{
				name[iii] = (name[iii]-'A')+'a';
			}
			if ( name[iii] == '#')
			{
				name[iii] = ' ';
			}
		}

		int32 entryFound = 0;
		for(int32 iEntry=0; iEntry<182772; iEntry++) // c'est super moche, mais j'ai pas compris comment lister les entry de creature template
		{
			CreatureLocale const* cl = sObjectMgr->GetCreatureLocale(iEntry);
			if (cl)
			{
				std::string nameFrench = "";
				if ( cl->Name.size() > LOCALE_frFR )
				{
					nameFrench = cl->Name[LOCALE_frFR];
				}

				// enlever les majuscules
				for(int iii=0; iii<nameFrench.size(); iii++)
				{
					if ( nameFrench[iii] >= 'A' && nameFrench[iii] <= 'Z' )
					{
						nameFrench[iii] = (nameFrench[iii]-'A')+'a';
					}
				}


				if ( nameFrench != "" && nameFrench.find(name) != std::string::npos  )
				{
					// nom trouvé !
					entryFound = iEntry;
					break;
				}
			}
		}

		if ( entryFound == 0 )
		{
			return false;
		}

		whereClause << "WHERE id = '" << entryFound << '\'';


		QueryResult result = WorldDatabase.PQuery("SELECT position_x, position_y, position_z, orientation, map, guid, id FROM creature %s", whereClause.str().c_str());
		if (!result)
		{
			handler->SendSysMessage(LANG_COMMAND_GOCREATNOTFOUND);
			handler->SetSentErrorMessage(true);
			return false;
		}
		if (result->GetRowCount() > 1)
			handler->SendSysMessage(LANG_COMMAND_GOCREATMULTIPLE);

		Field* fields = result->Fetch();
		float x = fields[0].GetFloat();
		float y = fields[1].GetFloat();
		float z = fields[2].GetFloat();
		float ort = fields[3].GetFloat();
		int mapId = fields[4].GetUInt16();
		uint32 guid = fields[5].GetUInt32();
		uint32 id = fields[6].GetUInt32();

		// if creature is in same map with caster go at its current location
		if (Creature* creature = ObjectAccessor::GetCreature(*player, MAKE_NEW_GUID(guid, id, HIGHGUID_UNIT)))
		{
			x = creature->GetPositionX();
			y = creature->GetPositionY();
			z = creature->GetPositionZ();
			ort = creature->GetOrientation();
		}

		if (!MapManager::IsValidMapCoord(mapId, x, y, z, ort))
		{
			handler->PSendSysMessage(LANG_INVALID_TARGET_COORD, x, y, mapId);
			handler->SetSentErrorMessage(true);
			return false;
		}

		// stop flight if need
		if (player->IsInFlight())
		{
			player->GetMotionMaster()->MovementExpired();
			player->CleanupAfterTaxiFlight();
		}
		// save only in non-flight case
		else
			player->SaveRecallPosition();

		player->TeleportTo(mapId, x, y, z, ort);
		return true;
	}



	static bool HandleCommandRicha__killrichard(ChatHandler* handler, char const* args)
	{
		Player* player = handler->GetSession()->GetPlayer();

		uint64 target = player->GetTarget();
		Unit* targte2 = player->GetSelectedUnit();
		if (targte2 && targte2->IsAlive())
		{
			Unit::DealDamage(player, targte2, targte2->GetHealth(), nullptr, DIRECT_DAMAGE, SPELL_SCHOOL_MASK_NORMAL, nullptr, false, true);
			int a = 0;

		}

		return true;
	}


	//  arg  est un string contenant tous les arguments a la suite
	static bool Richar_need(ChatHandler* handler, char const* arg___)
	{
		Player* player = handler->GetSession()->GetPlayer();


		if (player && arg___)
		{

			if ( strlen(arg___) > 4096 )
			{
				char messageee[2048];
				sprintf(messageee, "ERROR ARG 4096\n");
				ChatHandler(player->GetSession()).SendSysMessage(messageee);
				return false;
			}

			char arg[4096];
			strcpy_s(arg,arg___);


			if (arg[0] == '\0')
			{
				char messageee[2048];
				sprintf(messageee, "----------------------------------- Quetes Actives :\n");
				ChatHandler(player->GetSession()).SendSysMessage(messageee);

				bool inActif = true;

				// si pas d'argument on affiche juste la liste
				for (int i = 0; i < player->m_richa.m_richa_itemLootQuests.size(); i++)
				{

					if (inActif && !player->m_richa.m_richa_itemLootQuests[i].active)
					{
						char messageee[2048];
						sprintf(messageee, "----------------------------------- Quetes Inactives :\n");
						ChatHandler(player->GetSession()).SendSysMessage(messageee);

						inActif = false;
					}

					if (!inActif && player->m_richa.m_richa_itemLootQuests[i].active)
					{
						for (int i = 0; i < 5; i++)
						{
							char messageee[2048];
							sprintf(messageee, "ERREUR GRAVE EN PARLER A RICHARD 003\n");
							ChatHandler(player->GetSession()).SendSysMessage(messageee);
						}
					}



					std::string itemNameLink = RichardClass::Richa_itemIdToNiceLink(player->m_richa.m_richa_itemLootQuests[i].itemid);

					std::string boucle = "";
					if (player->m_richa.m_richa_itemLootQuests[i].LoopQuest)
					{
						boucle = " (mode boucle)";
					}

					char messageee[2048];
					if (player->m_richa.m_richa_itemLootQuests[i].currentScore*100.0f >= 0.001f
						&&  player->m_richa.m_richa_itemLootQuests[i].currentScore*100.0f <= 0.999f
						)
					{
						// for small value ( between 0 and 1 ) display the digits after comma
						sprintf(messageee, "%s %.2f/100 %s\n", itemNameLink.c_str(), player->m_richa.m_richa_itemLootQuests[i].currentScore*100.0f, boucle.c_str());
					}
					else
					{
						sprintf(messageee, "%s %.0f/100 %s\n", itemNameLink.c_str(), player->m_richa.m_richa_itemLootQuests[i].currentScore*100.0f, boucle.c_str());
					}
					ChatHandler(player->GetSession()).SendSysMessage(messageee);
				}

				// marquer la fin de la liste
				sprintf(messageee, "-------------------------------------------------------\n");
				ChatHandler(player->GetSession()).SendSysMessage(messageee);
			}
			else
			{
				char* argumentPointer = arg;

				bool modeDelete = false;
				bool modeBoucle = false;

				if (strcmp(arg, "help") == 0 || strcmp(arg, "aide") == 0)
				{
					char messageee[2048];
					sprintf(messageee, "La commande Need permet de gerer les quetes d'objets pour les Youhainis.");
					ChatHandler(player->GetSession()).SendSysMessage(messageee);

					sprintf(messageee, ".need --> avoir la liste des quetes.");
					ChatHandler(player->GetSession()).SendSysMessage(messageee);

					sprintf(messageee, ".need help --> avoir de l'aide sur la commande");
					ChatHandler(player->GetSession()).SendSysMessage(messageee);

					sprintf(messageee, ".need 4888 --> rajouter l'objet 4888 dans les quetes");
					ChatHandler(player->GetSession()).SendSysMessage(messageee);

					sprintf(messageee, ".need [Mucus de clampant] --> equivalent a:  .need 4888");
					ChatHandler(player->GetSession()).SendSysMessage(messageee);

					sprintf(messageee, ".need boucle [Mucus de clampant] --> faire quete en boucle");
					ChatHandler(player->GetSession()).SendSysMessage(messageee);

					sprintf(messageee, ".need stop 4888 --> retirer l'objet 4888 des quetes");
					ChatHandler(player->GetSession()).SendSysMessage(messageee);

					sprintf(messageee, ".need stop [Mucus de clampant] --> equivalent a:  .need stop 4888");
					ChatHandler(player->GetSession()).SendSysMessage(messageee);

					sprintf(messageee, ".need #189 --> need tout le set 189");
					ChatHandler(player->GetSession()).SendSysMessage(messageee);

					sprintf(messageee, ".need stop #189 --> retirer tout le set 189");
					ChatHandler(player->GetSession()).SendSysMessage(messageee);

					return true;
				}

				// delete  remove  stop  supprimer  suppr  ... tout ca revient au meme
				else if (strncmp(arg, "delete ", strlen("delete ")) == 0) // si la chaine commence par:  delete
				{
					argumentPointer += strlen("delete ");
					modeDelete = true;
					int a = 0;
				}
				else if (strncmp(arg, "remove ", strlen("remove ")) == 0) // si la chaine commence par:  remove
				{
					argumentPointer += strlen("remove ");
					modeDelete = true;
					int a = 0;
				}
				else if (strncmp(arg, "stop ", strlen("stop ")) == 0) // si la chaine commence par:  stop
				{
					argumentPointer += strlen("stop ");
					modeDelete = true;
					int a = 0;
				}

				else if (strncmp(arg, "supprimer ", strlen("supprimer ")) == 0) // si la chaine commence par:  supprimer
				{
					argumentPointer += strlen("supprimer ");
					modeDelete = true;
					int a = 0;
				}
				else if (strncmp(arg, "suppr ", strlen("suppr ")) == 0) // si la chaine commence par:  suppr
				{
					argumentPointer += strlen("suppr ");
					modeDelete = true;
					int a = 0;
				}


				else if (strncmp(arg, "boucle ", strlen("boucle ")) == 0)
				{
					argumentPointer += strlen("boucle ");
					modeBoucle = true;
					int a = 0;
				}
				else if (strncmp(arg, "loop ", strlen("loop ")) == 0)
				{
					argumentPointer += strlen("loop ");
					modeBoucle = true;
					int a = 0;
				}


				//uint32 itemID = 0;
				std::vector<uint32> itemIDs; // dans le cas d'un need de set, il peut y avoir plusieurs objets


				unsigned long itemFromLink = RichardClass::Richa_NiceLinkToIitemID(argumentPointer);
				if (itemFromLink != -1)
				{
					itemIDs.push_back(itemFromLink);
				}
				else if (argumentPointer[0] == '#')
				{
					//si on parle d'un set
					argumentPointer += 1;

					uint32 setID = 0;
					if (!RichardClass::ExtractUInt32(&argumentPointer, setID))
						return false;

					if (setID <= 0) // important de controler ca, sinon avec un .need #0  on prends pratiquement tous les items du jeu je pense
					{
						char messageee[2048];
						sprintf(messageee, "Erreur: ID de set INCORRECT.");
						ChatHandler(player->GetSession()).SendSysMessage(messageee);
						return false;
					}

					const int nbMaxItemEmptyInARow = 50000; // si on detecte une plage vide de 50000, on considere que c'est la fin de la database. c'est tres moche mais ca devrait bien marcher
					int countNotxistItem = 0;
					for (uint32 id = 0; ; ++id) 
					{
						//ItemPrototype const* pProto = sItemStorage.LookupEntry<ItemPrototype>(id);
						ItemTemplate const* pProto = sObjectMgr->GetItemTemplate(id);

						if (!pProto)
						{
							countNotxistItem++;

							if ( countNotxistItem >= nbMaxItemEmptyInARow )
								break;

							continue;
						}
						countNotxistItem = 0;

						if (pProto->ItemSet == setID)
						{
							itemIDs.push_back(pProto->ItemId);
							int a = 0;
						}
					}

					if (itemIDs.size() == 0)
					{
						char messageee[2048];
						sprintf(messageee, "Erreur: le Set n'existe pas ?");
						ChatHandler(player->GetSession()).SendSysMessage(messageee);
					}

					int a = 0;

				}
				else
				{
					uint32 itemID = 0;
					if (!RichardClass::ExtractUInt32(&argumentPointer, itemID))
						return false;

					itemIDs.push_back(itemID);
				}




				for (int iii = 0; iii < itemIDs.size(); iii++) // pour chaque item du set a ajouter / retirer du need
				{
					uint32 itemID = itemIDs[iii];

					std::string itemName = "objet inconnu";
					//ItemPrototype const* itemProto = sItemStorage.LookupEntry<ItemPrototype>(itemID);
					ItemTemplate const* itemProto = sObjectMgr->GetItemTemplate(itemID);
					if (itemProto)
					{

						std::string nameFrench = "";
						if (ItemLocale const* il = sObjectMgr->GetItemLocale(itemID))
						{
							if ( il->Name.size() > LOCALE_frFR )
							{
								nameFrench = il->Name[LOCALE_frFR];
							}
						}

						if ( nameFrench != "" )
						{
							itemName = nameFrench;
						}
						else
						{
							itemName = std::string(itemProto->Name1);
						}
					}

					// id dans la base de donnée
					const uint32 coinItemID1 = 70010; // YouhaiCoin Paragon
					// const uint32 coinItemID2 = 70007; // YouhaiCoin Cadeau <-- retiré de WOTLK

					// lister ici la liste des objets interdits a etre fait en quete
					if (!modeDelete)
					{
						if (
							itemID == 21301
							|| itemID == 21309
							|| itemID == 21305 // <-- les 4 items de noel à collectionner
							|| itemID == 21308

							// || itemID >= 100000 //  les youhaimon epiques ou non epiques   <---  pas de youhaimon sur WOTLK

							|| itemID == coinItemID1
							//|| itemID == coinItemID2
							)
						{
							char messageee[2048];
							sprintf(messageee, "Erreur: la quete pour %s est interdite.", itemName.c_str());
							ChatHandler(player->GetSession()).SendSysMessage(messageee);
							return true;
						}
					}



					if (!modeDelete)
					{
						//verifier qu'il existe pas deja
						bool already = false;
						for (int i = 0; i < player->m_richa.m_richa_itemLootQuests.size(); i++)
						{
							if (player->m_richa.m_richa_itemLootQuests[i].itemid == itemID)
							{
								already = true;

								char messageee[2048];
								sprintf(messageee, "La quete pour %s existe deja (%.0f/100).", itemName.c_str(), player->m_richa.m_richa_itemLootQuests[i].currentScore*100.0f);

								char messageee2[2048];
								messageee2[0] = 0;


								if (i != 0) // dès qu'un joueur fait  need   alors on passe toujours l'item en premiere position ( + "prioritaire" que les autres )
								{
									PlayerModeDataRicha::RICHA_ITEM_LOOT_QUEST save = player->m_richa.m_richa_itemLootQuests[i];

									//on change eventuellement le mode
									if (save.LoopQuest != modeBoucle)
									{
										save.LoopQuest = modeBoucle;

										if (modeBoucle)
										{
											sprintf(messageee2, " (mode boucle ative)");
										}
										else
										{
											sprintf(messageee2, " (mode boucle desactive)");
										}
									}

									//on le passe en actif
									save.active = true;

									player->m_richa.m_richa_itemLootQuests.erase(player->m_richa.m_richa_itemLootQuests.begin() + i);
									player->m_richa.m_richa_itemLootQuests.insert(player->m_richa.m_richa_itemLootQuests.begin() + 0, save);

								}
								else
								{
									//on change eventuellement le mode
									if (player->m_richa.m_richa_itemLootQuests[i].LoopQuest != modeBoucle)
									{
										player->m_richa.m_richa_itemLootQuests[i].LoopQuest = modeBoucle;

										if (modeBoucle)
										{
											sprintf(messageee2, " (mode boucle ativ\xc3\xa9\)");
										}
										else
										{
											sprintf(messageee2, " (mode boucle desactiv\xc3\xa9\)");
										}
									}

									//on le passe en actif
									player->m_richa.m_richa_itemLootQuests[i].active = true;
								}


								char messageee3[2048];
								sprintf(messageee3, "%s%s", messageee, messageee2);
								ChatHandler(player->GetSession()).SendSysMessage(messageee3);

								break;
							}
						}

						if (!already)
						{
							PlayerModeDataRicha::RICHA_ITEM_LOOT_QUEST newQuest;
							newQuest.active = true;
							newQuest.currentScore = 0.0f;
							newQuest.itemid = itemID;
							newQuest.nbFoisQueteDone = 0;
							newQuest.LoopQuest = modeBoucle;

							player->m_richa.m_richa_itemLootQuests.insert(player->m_richa.m_richa_itemLootQuests.begin() + 0, newQuest);

							char messageee[2048];
							sprintf(messageee, "Nouvelle quete pour: %s", itemName.c_str());
							ChatHandler(player->GetSession()).SendSysMessage(messageee);

						}
					}
					else
					{
						//// MODE DELETE

						//verifier qu'il existe
						bool found = false;
						for (int i = 0; i < player->m_richa.m_richa_itemLootQuests.size(); i++)
						{
							if (player->m_richa.m_richa_itemLootQuests[i].itemid == itemID)
							{
								found = true;

								player->m_richa.m_richa_itemLootQuests.erase(player->m_richa.m_richa_itemLootQuests.begin() + i);

								char messageee[2048];
								sprintf(messageee, "quete retir\xc3\xa9\e pour: %s", itemName.c_str());
								ChatHandler(player->GetSession()).SendSysMessage(messageee);

								break;
							}
						}

						if (!found)
						{

							char messageee[2048];
							sprintf(messageee, "Erreur: la quete de cet objet n'existe pas.");
							ChatHandler(player->GetSession()).SendSysMessage(messageee);


						}



					}


					// a partir de la on repasse en revue la liste :

					// a la fin, on verifie qu'il n'y a pas plus d'actif que permis par la regle.
					// je l'avais mis a 3 avant
					// en fait je pense qu'on va need pas mal de chose, genre tous les objets d'un set.
					// ... donc je le passe a une grande valeur, mais les joueur on pas trop le droit d'en abuser ( need 'tous' les item du jeu )
					const int maxActif = 1000;

					if (!modeDelete)
					{
						// comme on vient potentiellement de rajouter une quete en debut de liste, alors ca peut etre normal que le
						//  (maxActif) etait actif, et doivent passer inactif.
						if (player->m_richa.m_richa_itemLootQuests.size() >= maxActif + 1 && player->m_richa.m_richa_itemLootQuests[maxActif].active)
						{
							player->m_richa.m_richa_itemLootQuests[maxActif].active = false;
						}
					}
					else
					{
						//comme on vient potentiellement d'enlever une quete alors c'est possible qu'une place soit libre dans les quetes active

						if (player->m_richa.m_richa_itemLootQuests.size() >= maxActif && !player->m_richa.m_richa_itemLootQuests[maxActif - 1].active)
						{
							player->m_richa.m_richa_itemLootQuests[maxActif - 1].active = true;
						}

					}


					bool inActif = true;
					for (int i = 0; i < player->m_richa.m_richa_itemLootQuests.size(); i++)
					{
						if (player->m_richa.m_richa_itemLootQuests[i].active && i >= maxActif)
						{
							for (int i = 0; i < 5; i++)
							{
								char messageee[2048];
								sprintf(messageee, "ERREUR GRAVE EN PARLER A RICHARD 002\n");
								ChatHandler(player->GetSession()).SendSysMessage(messageee);
							}
						}



						if (inActif && !player->m_richa.m_richa_itemLootQuests[i].active)
						{
							inActif = false;
						}

						else if (!inActif && player->m_richa.m_richa_itemLootQuests[i].active)
						{
							// LA C'EST UNE ERREUR CAR TOUS LES ACTIF DOIVENT ETRE AU DEBUT DE LISTE

							for (int i = 0; i < 5; i++)
							{
								char messageee[2048];
								sprintf(messageee, "ERREUR GRAVE EN PARLER A RICHARD 001\n");
								ChatHandler(player->GetSession()).SendSysMessage(messageee);
							}

						}

					}

				}// pour chaque item du set a ajouter / retirer du need

			}



		}

		return true;


	}





	static bool Richar_help(ChatHandler* handler, char const* args)
	{
		Player* player = handler->GetSession()->GetPlayer();

		if (player)
		{
			char messageee[2048];

			sprintf(messageee, "richardhelp : cette commande");
			ChatHandler(player->GetSession()).SendSysMessage(messageee);

			sprintf(messageee, "notincombat : sortir du mode combat et se deco [CHEAT]");
			ChatHandler(player->GetSession()).SendSysMessage(messageee);

			sprintf(messageee, "stat : avoir info sur une cible");
			ChatHandler(player->GetSession()).SendSysMessage(messageee);

			sprintf(messageee, "okwin : donner le loot");
			ChatHandler(player->GetSession()).SendSysMessage(messageee);

			sprintf(messageee, "killrichard : tuer un mob [CHEAT]");
			ChatHandler(player->GetSession()).SendSysMessage(messageee);

			sprintf(messageee, "[i=123] : avoir info sur item 123");
			ChatHandler(player->GetSession()).SendSysMessage(messageee);
			sprintf(messageee, "[i=anneau] : avoir info sur item 'Anneau'");
			ChatHandler(player->GetSession()).SendSysMessage(messageee);
			sprintf(messageee, "majuscul + click gauche sur item : avoir info sur item");
			ChatHandler(player->GetSession()).SendSysMessage(messageee);

			sprintf(messageee, "q=Aventure : avoir info sur la quete 'Aventure'");
			ChatHandler(player->GetSession()).SendSysMessage(messageee);

			sprintf(messageee, "namegospeicialricha :  sort d'invocation demoniste [CHEAT]");
			ChatHandler(player->GetSession()).SendSysMessage(messageee);

			sprintf(messageee, "need help : details sur la commande NEED.");
			ChatHandler(player->GetSession()).SendSysMessage(messageee);

		}



		/*
		// garder ce source code, si je veux re-generer le TXT
		ofstream myfile;
		myfile.open ("RICHARDS_WOTLK/exportMapList.txt" , ios::binary);
		myfile << "Fichier genere. rechercher GENERATE_RICHA_MAP_LIST dans le source code.\r\n";
		int nb = sMapStore.GetNumRows(); // nb = 725  .  mais en fait il n'y a que 135 maps
        for (uint32 id = 0; id < nb; id++)
        {
            if (MapEntry const* mapInfo = sMapStore.LookupEntry(id))
            {
				// tous les name[ >0  ] semblent vides
                std::string name = mapInfo->name[0];
				std::string name1 = mapInfo->name[1];
				std::string name2 = mapInfo->name[2];
				std::string name3 = mapInfo->name[3];
				std::string name4 = mapInfo->name[4];
				std::string name5 = mapInfo->name[5];
				std::string name6 = mapInfo->name[6];
				std::string name7 = mapInfo->name[7];
				std::string name8 = mapInfo->name[8];
				std::string name9 = mapInfo->name[9];
				std::string name10 = mapInfo->name[10];
				std::string name11 = mapInfo->name[11];
				std::string name12 = mapInfo->name[12];
				std::string name13 = mapInfo->name[13];
				std::string name14 = mapInfo->name[14];
				std::string name15 = mapInfo->name[15];
                if (name.empty())
                    continue; // ceci n'arrive jamais  ( pour name[0] )

				myfile << id << ";";
				myfile << name << "\r\n";
			}
			else
			{
				int a=0;
			}
		}
		myfile.close();
		int a=0;
		*/



		return true;
	}


	static bool HandleRichardCommand_clearLootWinners(ChatHandler* handler, char const* args)
	{
		Player* playerEnterMessage = handler->GetSession()->GetPlayer();
		//if (!m_session)
		//{
		//	return false;
		//}

		//Player* playerEnterMessage = m_session->GetPlayer();

		if (!playerEnterMessage)
		{
			return false;
		}

		int nbModifie1 = 0;
		int nbModifie2 = 0;
		int nbLoot = 0;

		
		for (auto &ent : RichardClass::g_wantLoot)
		{


			if (ent.second.winner == playerEnterMessage) // si le winner est le joueur qui a fait le OKWIN
			{
				ent.second.winner = nullptr; // on efface le winner de ce loot
				ent.second.list.clear(); // on efface la liste des candidats pour ce loot
				ent.second.messageSentToPlayer_loot = false;
				ent.second.messageSentToPlayer_po = false;
				ent.second.okWinDoneOnThisLoot = true; // on signal qu'un OKWIN a été fait sur ce loot
				nbModifie1++;

				// on cree une candidature pour l'objet - pour eviter de bloquer les resultat d'election en attendant tous les candidats ou la fin du timing
				ent.second.list[playerEnterMessage].nbFois = 1;
				ent.second.list[playerEnterMessage].scoreDice = 0; // score 0 veut dire que le joueur ne veut PAS le loot
			}
			else
			{

				//si l'election est toujours en cours : gagnant non décidé
				//alors si le joueur a participé, on remplace son score par un score de 0
				//si je joueur n'a pas participé, on insert un candidature avec score 0
				if (ent.second.winner == nullptr) // si election en cours
				{
					if (ent.second.list.find(playerEnterMessage) != ent.second.list.end()) // si on trouve une candidature du joueur
					{
						ent.second.list[playerEnterMessage].scoreDice = 0; // on la remplace avec 0
					}
					else
					{
						// on cree une candidature pour l'objet - pour eviter de bloquer les resultat d'election en attendant tous les candidats ou la fin du timing
						ent.second.list[playerEnterMessage].nbFois = 1;
						ent.second.list[playerEnterMessage].scoreDice = 0; // score 0 veut dire que le joueur ne veut PAS le loot
					}
					ent.second.okWinDoneOnThisLoot = true; // on signal qu'un OKWIN a été fait sur ce loot
					nbModifie2++;
				}

			}



			//egalement, pour toutes les elections ou je ne me suis pas présenté

			nbLoot++; // nb total de loot

		}
		


		char messageee1[2048];
		sprintf(messageee1, "RICHAR: %s a clean ses %d/%d loots.", playerEnterMessage->GetName(), nbModifie1 + nbModifie2, nbLoot);
		sLog->outBasic(messageee1);

		char messageee2[2048];
		sprintf(messageee2, "clean %d/%d loots.", nbModifie1 + nbModifie2, nbLoot);
		ChatHandler(playerEnterMessage->GetSession()).SendSysMessage(messageee2);
		return true;
	}






	static bool Richar_noMoreInComat(ChatHandler* handler, char const* args)
	{
		Player* player = handler->GetSession()->GetPlayer();
		//Player* player = m_session->GetPlayer();
		if (player)
		{
			//player->ClearInCombat();
			player->CombatStop(true); // cette commande va vider la liste de mes attacker : si je fais LogoutPlayer  sans faire CombatStop, alors le jeu va me kill car je suis en combat
			player->GetSession()->LogoutPlayer(true); // logout
			//player->Say("CHEAT UTILISE : sortie du mode combat.",LANG_UNIVERSAL);
		}

		return true;
	}

	static bool Richar_tellMobStats(ChatHandler* handler, char const* args)
	{
		//Player* player = m_session->GetPlayer();
		Player* player = handler->GetSession()->GetPlayer();
		if (!player)
		{
			return true;
		}

		Unit* target = player->GetSelectedUnit();

		// if (!target || !player->GetSelectionGuid())
		// {
	   //	  SendSysMessage(LANG_SELECT_CHAR_OR_CREATURE);
		//	 SetSentErrorMessage(true);
		//	 return false;
		 //}


		if (!target || target->GetTypeId() == TYPEID_PLAYER)
		{

			float distanceFromObject = 0.0f;

			Player* playerTarget = 0;

			if (target)
			{
				playerTarget = dynamic_cast<Player*>(target);

				if (player && target != player)
				{
					distanceFromObject = player->GetDistance(target);
				}
			}
			else
			{
				playerTarget = player;
			}


			char messageee[2048];

			if (playerTarget)
			{


				sprintf(messageee, "==== INFO ========================");
				//sLog->outBasic(messageee);
				ChatHandler(player->GetSession()).SendSysMessage(messageee);

				sprintf(messageee, "TYPEID_PLAYER");
				//sLog->outBasic(messageee);
				ChatHandler(player->GetSession()).SendSysMessage(messageee);

				sprintf(messageee, "Name = %s", playerTarget->GetName().c_str());
				//sLog->outBasic(messageee);
				ChatHandler(player->GetSession()).SendSysMessage(messageee);

				sprintf(messageee, "Paragon = ??? TODO ???");//, playerTarget->GetParagonLevelFromItem());
				//sLog->outBasic(messageee);
				ChatHandler(player->GetSession()).SendSysMessage(messageee);


				sprintf(messageee, "Health = %d / %d", playerTarget->GetHealth(), playerTarget->GetMaxHealth());
				//sLog->outBasic(messageee);
				ChatHandler(player->GetSession()).SendSysMessage(messageee);

				//sprintf(messageee, "entry = %d", playerTarget->GetEntry() );
				//sLog->outBasic(messageee);
				//ChatHandler(player->GetSession()).SendSysMessage(messageee);

				sprintf(messageee, "GUIDlow = %d", playerTarget->GetGUIDLow());
				//sLog->outBasic(messageee);
				ChatHandler(player->GetSession()).SendSysMessage(messageee);

				sprintf(messageee, "distance = %f", distanceFromObject);
				// sLog->outBasic(messageee);
				ChatHandler(player->GetSession()).SendSysMessage(messageee);



			}
			else
			{
				sprintf(messageee, "ERROR playerTarget");
				//sLog->outBasic(messageee);
				ChatHandler(player->GetSession()).SendSysMessage(messageee);
			}
		}

		// if (target->isAlive() )
		else
		{
			float distanceFromObject = 0.0f;

			char messageee[4096];

			Creature* cast_creature = dynamic_cast<Creature*>(target);

			std::string nameFrench = "";
			if (cast_creature)
			{
				CreatureTemplate const* cinfo = cast_creature->GetCreatureTemplate();
				if ( cinfo )
				{
					CreatureLocale const* cl = sObjectMgr->GetCreatureLocale(cinfo->Entry);
					if (cl)
					{
						if ( cl->Name.size() > LOCALE_frFR )
						{
							nameFrench = cl->Name[LOCALE_frFR];
						}
					}
				}
			}


			sprintf(messageee, "==== INFO ========================");
			//sLog->outBasic(messageee);
			ChatHandler(player->GetSession()).SendSysMessage(messageee);

			sprintf(messageee, "Name = %s (%s)", nameFrench.c_str(), target->GetName().c_str());
			//sLog->outBasic(messageee);
			ChatHandler(player->GetSession()).SendSysMessage(messageee);

			sprintf(messageee, "Health = %d / %d ", target->GetHealth(), target->GetMaxHealth());
			//sLog->outBasic(messageee);
			ChatHandler(player->GetSession()).SendSysMessage(messageee);


			//sprintf(messageee, "entry = %d", target->GetEntry() );
			//sLog->outBasic(messageee);
			//ChatHandler(player->GetSession()).SendSysMessage(messageee);


			

			if (cast_creature)
			{
				

				distanceFromObject = player->GetDistance(cast_creature);


				//CreatureInfo const* cinfo = cast_creature->GetCreatureInfo();
				CreatureTemplate const* cinfo = cast_creature->GetCreatureTemplate();

				if ( cinfo->type == CREATURE_TYPE_BEAST )
				{
					bool adopatable_exotique = cinfo->IsTameable(true);
					bool adopatable_normal   = cinfo->IsTameable(false);

					if ( !adopatable_exotique && !adopatable_normal )
					{
						sprintf(messageee, "Cette bete n'est PAS adoptable.");
						ChatHandler(player->GetSession()).SendSysMessage(messageee);
					}
					else if ( adopatable_exotique && adopatable_normal )
					{
						sprintf(messageee, "Cette bete est adoptable.");
						ChatHandler(player->GetSession()).SendSysMessage(messageee);
					}
					else if ( adopatable_exotique && !adopatable_normal )
					{
						sprintf(messageee, "Cette bete est adoptable - et est EXOTIQUE.");
						ChatHandler(player->GetSession()).SendSysMessage(messageee);
					}
					else
					{
						// une bete ne peux pas etre non adoptable avec la spec exotique, et adoptable dans la spec, ca a pas de sens.
						sprintf(messageee, "BUG 9651 EN PARLER A RICHARD !!!!!!!!!!!!!!!!");
						ChatHandler(player->GetSession()).SendSysMessage(messageee);
					}
				}


				sprintf(messageee, "distance = %f", distanceFromObject);
				//sLog->outBasic(messageee);
				ChatHandler(player->GetSession()).SendSysMessage(messageee);

				//if (cinfo)
				if (true)
				{
					// valeur d'attaque qui ne prend PAS en compte Richar_difficuly_degat.
					// (et surement d'autres facteurs, cf. CalculateMinMaxDamage)
					// pour avoir la vraie valeur d'attaque, ca me semble un peu compliqué. donc je la donne pas pour l'instant
					sprintf(messageee, "dmg (avant Richar_difficuly) = %f->%f", cinfo->mindmg, cinfo->maxdmg );
					sLog->outBasic(messageee);
					ChatHandler(player->GetSession()).SendSysMessage(messageee);

					//  cinfo->Entry  et   cast_creature->GetEntry()  retournent la meme chose
					sprintf(messageee, "npc = %d", cinfo->Entry);
					sLog->outBasic(messageee);
					ChatHandler(player->GetSession()).SendSysMessage(messageee);

					sprintf(messageee, "creature GUID = %d", cast_creature->GetGUIDLow());
					//sLog->outBasic(messageee);
					ChatHandler(player->GetSession()).SendSysMessage(messageee);

					sprintf(messageee, "Richar_difficuly_health = %f", cast_creature->m_richa.Richar_difficuly_health);
					sLog->outBasic(messageee);
					ChatHandler(player->GetSession()).SendSysMessage(messageee);

					sprintf(messageee, "Richar_difficuly_degat = %f", cast_creature->m_richa.Richar_difficuly_degat);
					sLog->outBasic(messageee);
					ChatHandler(player->GetSession()).SendSysMessage(messageee);


					
					if (cinfo->rank == CREATURE_ELITE_RARE)
					{


						std::vector<int>  mainPlayerGUID;
						std::vector<std::string>  mainPlayerNames;



						// #LISTE_ACCOUNT_HERE   -  ce hashtag repere tous les endroit que je dois updater quand je rajoute un nouveau compte - ou perso important
						//
						//list de tous les perso principaux de tout le monde
						//mainPlayerGUID.push_back(XXX);  mainPlayerNames.push_back("PBody");
						//mainPlayerGUID.push_back(YYY);  mainPlayerNames.push_back("Atlas");  <----   TODO POUR WOTLK : rentrer les bon GUID des personnages
						sprintf(messageee, "WARNING : LISTE DE PERSO VIDE");
						ChatHandler(player->GetSession()).SendSysMessage(messageee);



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
								if (richa_NpcKilled[kk].npc_id == cinfo->Entry)
								{
									existInDataBaseV2 = jj;
									break;
								}
							}

							if (existInDataBaseV2 != -1) { break; }
						}



						if (existInDataBaseV2 == -1)
						{
							sprintf(messageee, "Cet Elite Gris n'a PAS ete decouvert.");
							//sLog->outBasic(messageee);
							ChatHandler(player->GetSession()).SendSysMessage(messageee);
						}
						else
						{
							sprintf(messageee, "Cet Elite Gris a DEJA ete decouvert par %s", mainPlayerNames[existInDataBaseV2].c_str());
							//sLog->outBasic(messageee);
							ChatHandler(player->GetSession()).SendSysMessage(messageee);
						}

					}
					


				}
				else
				{
					sprintf(messageee, "ERROR cinfo");
					//sLog->outBasic(messageee);
					ChatHandler(player->GetSession()).SendSysMessage(messageee);
				}
			}
			else
			{
				sprintf(messageee, "NOT_CREATURE");
				//sLog->outBasic(messageee);
				ChatHandler(player->GetSession()).SendSysMessage(messageee);
			}




		}

		return true;
	}




	static bool HandleServerShutDownCommand_RICHA(ChatHandler* /*handler*/, char const* args___not_used)
	{
		char const args[] = "0";


		//if (!*args)
		//	return false;

		char* timeStr = strtok((char*)args, " ");
		char* exitCodeStr = strtok(nullptr, "");

		int32 time = atoi(timeStr);
		//int32 time = 0;

		// Prevent interpret wrong arg value as 0 secs shutdown time
		if ((time == 0 && (timeStr[0] != '0' || timeStr[1] != '\0')) || time < 0)
			return false;

		if (exitCodeStr)
		{
			int32 exitCode = atoi(exitCodeStr);

			// Handle atoi() errors
			if (exitCode == 0 && (exitCodeStr[0] != '0' || exitCodeStr[1] != '\0'))
				return false;

			// Exit code should be in range of 0-125, 126-255 is used
			// in many shells for their own return codes and code > 255
			// is not supported in many others
			if (exitCode < 0 || exitCode > 125)
				return false;

			sWorld->ShutdownServ(time, 0, exitCode);
		}
		else
			sWorld->ShutdownServ(time, 0, SHUTDOWN_EXIT_CODE);

		return true;
	}


};

void AddMyCommandScripts()
{
	new MyCommand();
}


