/*
 * Copyright (C) 2005-2011 MaNGOS <http://getmangos.com/>
 * Copyright (C) 2009-2011 MaNGOSZero <https://github.com/mangos/zero>
 * Copyright (C) 2011-2016 Nostalrius <https://nostalrius.org>
 * Copyright (C) 2016-2017 Elysium Project <https://github.com/elysium-project>
 * Copyright (C) 2017-2024 VMangos <https://github.com/vmangos/core>
 * Copyright (C) 2024+ RaspyWoW <https://raspywow.com/>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include "scriptPCH.h"
#include "Opcodes_1_12_1.h"
#include "Utilities/EventMap.h"
#include "Config/Config.h"

// Hair style names by race
constexpr std::array<const char*, 11> HumanMaleHairstyles =
{"Bald", "Short Cropped", "Wild Tuft", "Topknot", "Long and Flowing", "Slicked Back", "Pigtails", "Mullet", "Ponytail", "Tall Mohawk", "Low Mohawk"};
constexpr std::array<const char*, 18> HumanFemaleHairstyles =
{"Tribal", "Pixie", "Ponytail", "Looped Ponytail", "Big Pigtails", "Long Wave", "Flowing Locks", "Topknots", "Pigtails", "Loose and Short", "Faux Hawk", "Blunt Cut", "Wavy", "Bob Cut", "Twin Braids", "Mullet", "Straight Ponytail", "High Ponytail"};
constexpr std::array<const char*, 7>  OrcMaleHairstyles =
{"Bald", "Topknot", "Mohawk", "Double Braids", "Warrior's Tail", "Ponytail", "Side Braids"};
constexpr std::array<const char*, 7>  OrcFemaleHairstyles =
{"Pixie", "Topknot", "Side Ponytail", "Wild", "Braided Knot", "Mohawk", "Side Braids"};
constexpr std::array<const char*, 11> DwarfMaleHairstyles =
{"Bald", "Highland Top", "Viking Braids", "Mountain Braids", "Wild Mountain", "Berrigan's Cut", "Weathered Spikes", "Master Explorer", "Wild Traveler", "Forgemaster's Cut", "Dignified Noble"};
constexpr std::array<const char*, 14> DwarfFemaleHairstyles =
{"Smooth Updo", "Ironforge Royal", "Mountain Locks", "Twin Braids", "Rugged Heirloom", "Short Cropped", "Noble Braids", "Warrior's Ponytail", "Hearth Keeper", "Highland Braids", "Blackrock Cut", "Elegant Braids", "Dignified Twin Braids", "Stonemother's Style"};
constexpr std::array<const char*, 6>  NightElfMaleHairstyles =
{"Bald", "Long Flowing", "Wild Growth", "Woodland Warrior", "Druidic Spikes", "Guardian Knot"};
constexpr std::array<const char*, 11> NightElfFemaleHairstyles =
{"Smooth Updo", "Moonwell Braids", "Forest Knots", "Wild Locks", "Elune's Braids", "Sentinel's Dignity", "Priestess Plait", "Twin Braids", "Feathered Crest", "Temple Knot", "Darnassian Noble"};
constexpr std::array<const char*, 10> UndeadMaleHairstyles =
{"Bald", "Death Knight", "Ghoul Spikes", "Withered", "Banshee's Victim", "Decrepit Mohawk", "Lichborne Tufts", "Ravaged Locks", "Forsaken Ritual", "Dark Bangs"};
constexpr std::array<const char*, 9>  UndeadFemaleHairstyles =
{"Bald", "Stringy Locks", "Decrepit Bun", "Matted Strands", "Dark Lindsey", "Ragged Knots", "Banshee's Veil", "Sylvanas Style", "Withered Elegance"};
constexpr std::array<const char*, 6>  TaurenMaleHairstyles =
{"Ceremonial Horns", "Shaman's Mane", "Chieftain's Pride", "Elder Braids", "Thunderhorn", "Bloodhoof Warrior"};
constexpr std::array<const char*, 8>  TaurenFemaleHairstyles =
{"Unadorned", "Tribal Braids", "Mulgore Pride", "Hunter's Knots", "Earthmother Locks", "Chieftain's Daughter", "Braided Dignity", "Steppe Warrior"};
constexpr std::array<const char*, 7>  GnomeMaleHairstyles =
{"Bald", "Tinker's Cut", "Engineer's Creativity", "Mechanostrider Pilot", "Cogwheel Spikes", "Gadgetzan Special", "Gnomeregan Pride"};
constexpr std::array<const char*, 7>  GnomeFemaleHairstyles =
{"Inventor's Pigtails", "Mechanic's Ponytail", "Tinkerer's Buns", "Fizzcrank Top", "Ironforge Bob", "Dimensional Spikes", "Gnomeregan Graduate"};
constexpr std::array<const char*, 10> TrollMaleHairstyles =
{"Central Mohawk", "Jeklik's Pride", "Darkspear Ritual", "Zul'Gurub Warrior", "Sen'jin Guardian", "Bloodscalp Brave", "Voodoo Master", "Shadow Hunter", "Witch Doctor", "Zandalari Noble"};
constexpr std::array<const char*, 11> TrollFemaleHairstyles =
{"Ritual Mohawk", "Savage Knots", "Priestess Braids", "Echo Isles Style", "Darkspear Pride", "Jungle Survivor", "Voodoo Elegance", "Shadow Huntress", "Spirit Caller", "Loa Blessed", "Zandalari Royal"};

// Hair color names by race
constexpr std::array<const char*, 10> HumanHairColors =
{"Black", "Brown", "Light Brown", "Copper Brown", "Red", "Blonde", "Golden Blonde", "Auburn", "Grey", "White"};
constexpr std::array<const char*, 8>  OrcHairColors =
{"Blue", "Brown", "Red", "Purple", "Dark Purple", "Green", "Grey", "White"};
constexpr std::array<const char*, 10> DwarfHairColors =
{"Bronze", "Blonde", "Red", "White", "Brown", "MidnightBlack", "Light Brown", "Gray", "Dark Grey", "Black"};
constexpr std::array<const char*, 9>  NightElfHairColors =
{"Light Green", "Green", "Dark Green", "Teal", "Grey", "Cyan", "Dark Blue", "Purple"};
constexpr std::array<const char*, 10> UndeadHairColors =
{"Green", "Lichen Purple", "Dark Gay", "Lichen Green", "Gray", "Cyan", "Lichen Brown", "Decaying Cyan", "Purple", "Lichen Black"};
constexpr std::array<const char*, 3>  TaurenHairColors =
{"Black", "Brown", "White"};
constexpr std::array<const char*, 9>  GnomeHairColors =
{"Black", "Brown", "White", "White", "Grey", "Pink", "Snow White", "Green", "Neon Pink"};
constexpr std::array<const char*, 10> TrollHairColors =
{"Pink", "Red", "Orange", "Yellow", "Green", "Teal", "Cyan", "Blue", "Dark Grey", "Light Grey"};

// Facial hair names by race
constexpr std::array<const char*, 9> HumanMaleFacial =
{"Clean Shaven", "Five O'clock Shadow", "Mustache", "Short Beard", "Goatee", "Handlebar Mustache", "Full Beard", "Viking Beard", "Long Beard"};
constexpr std::array<const char*, 9> DwarfMaleFacial =
{"Clean Shaven", "Ironforge Commander", "Wildhammer Braids", "Mountain King", "Imperial Cut", "Bronzebeard Pride", "Forged in Fire", "Ancient Warrior", "Thane's Dignity"};
constexpr std::array<const char*, 8> OrcMaleFacial =
{"Clean Shaven", "Warlord's Pride", "Thrall's Honor", "Grunt's Stubble", "Hellscream's Fury", "Saurfang's Dignity", "Blackrock Raider"};
constexpr std::array<const char*, 7> TrollMaleFacial =
{"Clean Shaven", "Tusked Pride", "Spirit Caller", "Voodoo Markings", "Darkspear Honor", "Berserker's Edge", "Zul'jin's Legacy"};
constexpr std::array<const char*, 7> GnomeMaleFacial =
{"Clean Shaven", "Tinker's Mustache", "Inventor's Goatee", "Mechanostrider Designer", "Gadgetzan Trader", "High Tinker's Choice", "Gnomeregan Exile"};
constexpr std::array<const char*, 7> TaurenMaleFacial =
{"Clean Shaven", "Chieftain's Pride", "Bloodhoof Honor", "Grimtotem Markings", "Elder's Dignity", "Thunderhorn", "Great Plains Hunter"};
constexpr std::array<const char*, 7> UndeadMaleFacial =
{"Clean Jaw", "Rotting Stubble", "Decayed Beard", "Skeletal Remains", "Forsaken Pride", "Lichborne Wisps", "Dark Ranger's Trophy"};
constexpr std::array<const char*, 2> NightElfMaleFacial =
{"Clean Shaven", "Night Elf Beard"};

// Troll tusk options
constexpr std::array<const char*, 10> TrollTusks = 
{"Small Tusks", "Curved Tusks", "Upright Tusks", "Long Tusks", "Wide Tusks", "Sharpened Tusks", "Jungle Tusks", "Shadowhunter Tusks", "Berserker Tusks", "Bloodscalp Tusks"};

// Undead facial features
constexpr std::array<const char*, 10> UndeadFeatures = 
{"Light Decomposition", "Moderate Decay", "Advanced Rot", "Exposed Jaw", "Skeletal Features", "Withered Face", "Ghoulish Appearance", "Sunken Eyes", "Plague Marks", "Death Knight Features"};

// Tauren horn options
constexpr std::array<const char*, 10> TaurenHornStyles = 
{"Short Horns", "Curved Horns", "Long Straight Horns", "Bull Horns", "Tribal Horns", "Spiraled Horns", "Weathered Horns", "Bloodhoof Horns", "Grimtotem Horns", "Elder's Horns"};

// Tauren horn colors
constexpr std::array<const char*, 5> TaurenHornColors = 
{"Dark Brown", "Light Brown", "White", "Black", "Gray"};

enum HairstyleChange : uint32
{
    // Actions

    // 18 options
    ACTION_HAIRSTYLE_MIN = 0,
    ACTION_HAIRSTYLE_MAX = 17,

    // 9 options
    ACTION_HAIRCOLOR_MIN = 18,
    ACTION_HAIRCOLOR_MAX = 27,

    // 9 options
    ACTION_FACIALSTYLE_MIN = 28,
    ACTION_FACIALSTYLE_MAX = 37,
    
    // 10 options for troll tusks
    ACTION_TROLLTUSK_MIN = 38,
    ACTION_TROLLTUSK_MAX = 47,
    
    // 10 options for undead features
    ACTION_UNDEADFEATURE_MIN = 48,
    ACTION_UNDEADFEATURE_MAX = 57,
    
    // 10 options for tauren horn styles
    ACTION_HORNSTYLE_MIN = 58,
    ACTION_HORNSTYLE_MAX = 67,
    
    // 5 options for tauren horn colors
    ACTION_HORNCOLOR_MIN = 68,
    ACTION_HORNCOLOR_MAX = 72,
    
    ACTION_MENU_HAIRSTYLE     = 80,
    ACTION_MENU_HAIRCOLOR     = 81,
    ACTION_MENU_FACIALSTYLE   = 82,
    ACTION_MENU_SHOP          = 83,
    ACTION_MENU_TROLLTUSK     = 84,
    ACTION_MENU_UNDEADFEATURE = 85,
    ACTION_MENU_HORNSTYLE     = 86,
    ACTION_MENU_HORNCOLOR     = 87,
    ACTION_GO_BACK            = 90,
    
    // Custom actions for human female hairstyles pagination
    ACTION_HUMAN_FEMALE_PAGE_1 = 100,
    ACTION_HUMAN_FEMALE_PAGE_2 = 101,

    // Gossip menu text (npc_text + broadcast_text)
    GOSSIP_MENU_HAIRSTYLE_MAIN   = 60114,
    GOSSIP_MENU_HAIRSTYLE_SELECT = 60115,

    // Menu navigation (broadcast_text)
    GOSSIP_TEXT_CHANGE_HAIR_STYLE      = 200162,
    GOSSIP_TEXT_CHANGE_HAIR_COLOR      = 200163,
    GOSSIP_TEXT_CHANGE_FACIAL_HAIR     = 200164,
    GOSSIP_TEXT_SHOW_VENDOR_MENAU      = 200165,
    GOSSIP_TEXT_NAV_BACK               = 200166,
    GOSSIP_TEXT_NAV_NEXT               = 200172,
    GOSSIP_TEXT_CHANGE_TROLL_TUSKS     = 200174,
    GOSSIP_TEXT_CHANGE_UNDEAD_FEATURES = 200175,
    GOSSIP_TEXT_CHANGE_HORN_STYLE      = 200176,
    GOSSIP_TEXT_CHANGE_HORN_COLOR      = 200177,

    // Spoken text (broadcast_text)
    SAY_HAIR_STYLE_CHANGED_1 = 200168,
    SAY_HAIR_STYLE_CHANGED_2 = 200169,
    SAY_HAIR_STYLE_CHANGED_3 = 200170,
    SAY_HAIR_STYLE_CHANGED_4 = 200171,

    // Server message (mangos_string)
    MESSAGE_MISSING_ITEM = 20082,

    // Custom item entry (item_template)
    ITEM_BEAUTIFYING_TONIC = 30064
};

struct custom_hairstyle_npc : public ScriptedAI
{
    explicit custom_hairstyle_npc(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_hasActiveEmote = false;
        Reset();
    }

    static const uint32 EVENT_ENABLE_GOSSIP = 1;
    EventMap m_events;
    bool m_hasActiveEmote;

    void RemoveGossip()
    {
        if (m_creature->HasFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP))
        {
            m_creature->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
        }
        m_hasActiveEmote = true;
        m_creature->HandleEmoteState(EMOTE_STATE_USESTANDING); // Using scissors emote
    }

    void RestoreGossip()
    {
        if (!m_creature->HasFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP))
        {
            m_creature->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
        }
        if (m_hasActiveEmote)
        {
            m_hasActiveEmote = false;
            m_creature->HandleEmoteState(0);
        }
    }

    void Reset() override
    {
        m_events.Reset();

        if (!sWorld.getConfig(CONFIG_BOOL_FEATURE_BARBER_SHOP))
        {
            // Feature disabled.
            m_creature->SetVisibility(VISIBILITY_OFF);
            m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
            return;
        }

        RestoreGossip();
    }

    void HasSpokenTo()
    {
        RemoveGossip();
        m_events.RescheduleEvent(EVENT_ENABLE_GOSSIP, Seconds(1));
    }

    void UpdateGossipEvents(const uint32 eventId)
    {
        switch (eventId)
        {
            case EVENT_ENABLE_GOSSIP:
            {
                RestoreGossip();
                break;
            }
        }
    }

    void UpdateAI(const uint32 uiDiff) override
    {
        m_events.Update(uiDiff);

        while (const uint32 eventId = m_events.ExecuteEvent())
        {
            UpdateGossipEvents(eventId);
        }
    }
};

static void ShowHumanFemaleHairstylePage(Player* pPlayer, Creature* pCreature, uint8 page)
{
    uint8 startIndex = (page == 1) ? 0 : uint8(HumanFemaleHairstyles.size() / 2);
    uint8 endIndex = (page == 1) ? uint8(HumanFemaleHairstyles.size() / 2) : HumanFemaleHairstyles.size();

    // Hairstyle options
    for (uint8 i = startIndex; i < endIndex; ++i)
    {
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, HumanFemaleHairstyles[i], GOSSIP_SENDER_MAIN, ACTION_HAIRSTYLE_MIN + i);
    }

    // Navigation buttons
    if (page == 1)
    {
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_NAV_NEXT, GOSSIP_SENDER_MAIN, ACTION_HUMAN_FEMALE_PAGE_2);
    }
    else
    {
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_NAV_BACK, GOSSIP_SENDER_MAIN, ACTION_HUMAN_FEMALE_PAGE_1);
    }

    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_NAV_BACK, GOSSIP_SENDER_MAIN, ACTION_GO_BACK);
    pPlayer->SEND_GOSSIP_MENU(GOSSIP_MENU_HAIRSTYLE_SELECT, pCreature->GetGUID());
}

static void ShowHairstyleMenu(Player* pPlayer, Creature* pCreature)
{
    uint8 race = pPlayer->GetRace();
    uint8 gender = pPlayer->GetGender();

    switch (race)
    {
        case RACE_HUMAN:
        {
            if (gender == GENDER_MALE)
            {
                for (uint8 i = 0; i < HumanMaleHairstyles.size(); ++i)
                {
                    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, HumanMaleHairstyles[i], GOSSIP_SENDER_MAIN, ACTION_HAIRSTYLE_MIN + i);
                }
            }
            else
            {
                // Too many options -> pagination
                ShowHumanFemaleHairstylePage(pPlayer, pCreature, 1 /*page*/);
                return;
            }
            break;
        }
        case RACE_ORC:
        {
            if (gender == GENDER_MALE)
            {
                for (uint8 i = 0; i < OrcMaleHairstyles.size(); ++i)
                {
                    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, OrcMaleHairstyles[i], GOSSIP_SENDER_MAIN, ACTION_HAIRSTYLE_MIN + i);
                }
            }
            else
            {
                for (uint8 i = 0; i < OrcFemaleHairstyles.size(); ++i)
                {
                    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, OrcFemaleHairstyles[i], GOSSIP_SENDER_MAIN, ACTION_HAIRSTYLE_MIN + i);
                }
            }
            break;
        }
        case RACE_DWARF:
        {
            if (gender == GENDER_MALE)
            {
                for (uint8 i = 0; i < DwarfMaleHairstyles.size(); ++i)
                {
                    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, DwarfMaleHairstyles[i], GOSSIP_SENDER_MAIN, ACTION_HAIRSTYLE_MIN + i);
                }
            }
            else
            {
                for (uint8 i = 0; i < DwarfFemaleHairstyles.size(); ++i)
                {
                    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, DwarfFemaleHairstyles[i], GOSSIP_SENDER_MAIN, ACTION_HAIRSTYLE_MIN + i);
                }
            }
            break;
        }
        case RACE_NIGHTELF:
        {
            if (gender == GENDER_MALE)
            {
                for (uint8 i = 0; i < NightElfMaleHairstyles.size(); ++i)
                {
                    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, NightElfMaleHairstyles[i], GOSSIP_SENDER_MAIN, ACTION_HAIRSTYLE_MIN + i);
                }
            }
            else
            {
                for (uint8 i = 0; i < NightElfFemaleHairstyles.size(); ++i)
                {
                    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, NightElfFemaleHairstyles[i], GOSSIP_SENDER_MAIN, ACTION_HAIRSTYLE_MIN + i);
                }
            }
            break;
        }
        case RACE_UNDEAD:
        {
            if (gender == GENDER_MALE)
            {
                for (uint8 i = 0; i < UndeadMaleHairstyles.size(); ++i)
                {
                    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, UndeadMaleHairstyles[i], GOSSIP_SENDER_MAIN, ACTION_HAIRSTYLE_MIN + i);
                }
            }
            else
            {
                for (uint8 i = 0; i < UndeadFemaleHairstyles.size(); ++i)
                {
                    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, UndeadFemaleHairstyles[i], GOSSIP_SENDER_MAIN, ACTION_HAIRSTYLE_MIN + i);
                }
            }
            break;
        }
        case RACE_GNOME:
        {
            if (gender == GENDER_MALE)
            {
                for (uint8 i = 0; i < GnomeMaleHairstyles.size(); ++i)
                {
                    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GnomeMaleHairstyles[i], GOSSIP_SENDER_MAIN, ACTION_HAIRSTYLE_MIN + i);
                }
            }
            else
            {
                for (uint8 i = 0; i < GnomeFemaleHairstyles.size(); ++i)
                {
                    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GnomeFemaleHairstyles[i], GOSSIP_SENDER_MAIN, ACTION_HAIRSTYLE_MIN + i);
                }
            }
            break;
        }
        case RACE_TROLL:
        {
            if (gender == GENDER_MALE)
            {
                for (uint8 i = 0; i < TrollMaleHairstyles.size(); ++i)
                {
                    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, TrollMaleHairstyles[i], GOSSIP_SENDER_MAIN, ACTION_HAIRSTYLE_MIN + i);
                }
            }
            else
            {
                for (uint8 i = 0; i < TrollFemaleHairstyles.size(); ++i)
                {
                    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, TrollFemaleHairstyles[i], GOSSIP_SENDER_MAIN, ACTION_HAIRSTYLE_MIN + i);
                }
            }
            break;
        }
    }

    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_NAV_BACK, GOSSIP_SENDER_MAIN, ACTION_GO_BACK);
    pPlayer->SEND_GOSSIP_MENU(GOSSIP_MENU_HAIRSTYLE_SELECT, pCreature->GetGUID());
}

static void ShowHairColorMenu(Player* pPlayer, Creature* pCreature)
{
    const uint8 race = pPlayer->GetRace();
    
    switch (race)
    {
        case RACE_HUMAN:
        {
            for (uint8 i = 0; i < HumanHairColors.size(); i++)
            {
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, HumanHairColors[i], GOSSIP_SENDER_MAIN, ACTION_HAIRCOLOR_MIN + i);
            }
            break;
        }
        case RACE_ORC:
        {
            for (uint8 i = 0; i < OrcHairColors.size(); i++)
            {
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, OrcHairColors[i], GOSSIP_SENDER_MAIN, ACTION_HAIRCOLOR_MIN + i);
            }
            break;
        }
        case RACE_DWARF:
        {
            for (uint8 i = 0; i < DwarfHairColors.size(); i++)
            {
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, DwarfHairColors[i], GOSSIP_SENDER_MAIN, ACTION_HAIRCOLOR_MIN + i);
            }
            break;
        }
        case RACE_NIGHTELF:
        {
            for (uint8 i = 0; i < NightElfHairColors.size(); i++)
            {
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, NightElfHairColors[i], GOSSIP_SENDER_MAIN, ACTION_HAIRCOLOR_MIN + i);
            }
            break;
        }
        case RACE_UNDEAD:
        {
            for (uint8 i = 0; i < UndeadHairColors.size(); i++)
            {
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, UndeadHairColors[i], GOSSIP_SENDER_MAIN, ACTION_HAIRCOLOR_MIN + i);
            }
            break;
        }
        case RACE_GNOME:
        {
            for (uint8 i = 0; i < GnomeHairColors.size(); i++)
            {
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GnomeHairColors[i], GOSSIP_SENDER_MAIN, ACTION_HAIRCOLOR_MIN + i);
            }
            break;
        }
        case RACE_TROLL:
        {
            for (uint8 i = 0; i < TrollHairColors.size(); i++)
            {
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, TrollHairColors[i], GOSSIP_SENDER_MAIN, ACTION_HAIRCOLOR_MIN + i);
            }
            break;
        }
    }
    
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_NAV_BACK, GOSSIP_SENDER_MAIN, ACTION_GO_BACK);
    pPlayer->SEND_GOSSIP_MENU(GOSSIP_MENU_HAIRSTYLE_SELECT, pCreature->GetGUID());
}

static void ShowFacialHairMenu(Player* pPlayer, Creature* pCreature)
{
    const uint8 race = pPlayer->GetRace();
    
    switch (race)
    {
        case RACE_HUMAN:
        {
            for (uint8 i = 0; i < HumanMaleFacial.size(); i++)
            {
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, HumanMaleFacial[i], GOSSIP_SENDER_MAIN, ACTION_FACIALSTYLE_MIN + i);
            }
            break;
        }
        case RACE_ORC:
        {
            for (uint8 i = 0; i < OrcMaleFacial.size(); i++)
            {
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, OrcMaleFacial[i], GOSSIP_SENDER_MAIN, ACTION_FACIALSTYLE_MIN + i);
            }
            break;
        }
        case RACE_DWARF:
        {
            for (uint8 i = 0; i < DwarfMaleFacial.size(); i++)
            {
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, DwarfMaleFacial[i], GOSSIP_SENDER_MAIN, ACTION_FACIALSTYLE_MIN + i);
            }
            break;
        }
        case RACE_NIGHTELF:
        {
            for (uint8 i = 0; i < NightElfMaleFacial.size(); i++)
            {
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, NightElfMaleFacial[i], GOSSIP_SENDER_MAIN, ACTION_FACIALSTYLE_MIN + i);
            }
            break;
        }
        case RACE_GNOME:
        {
            for (uint8 i = 0; i < GnomeMaleFacial.size(); i++)
            {
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GnomeMaleFacial[i], GOSSIP_SENDER_MAIN, ACTION_FACIALSTYLE_MIN + i);
            }
            break;
        }
    }
    
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_NAV_BACK, GOSSIP_SENDER_MAIN, ACTION_GO_BACK);
    pPlayer->SEND_GOSSIP_MENU(GOSSIP_MENU_HAIRSTYLE_SELECT, pCreature->GetGUID());
}

static void ShowTrollTuskMenu(Player* pPlayer, Creature* pCreature)
{
    for (uint8 i = 0; i < TrollTusks.size(); i++)
    {
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, TrollTusks[i], GOSSIP_SENDER_MAIN, ACTION_TROLLTUSK_MIN + i);
    }
    
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_NAV_BACK, GOSSIP_SENDER_MAIN, ACTION_GO_BACK);
    pPlayer->SEND_GOSSIP_MENU(GOSSIP_MENU_HAIRSTYLE_SELECT, pCreature->GetGUID());
}

static void ShowUndeadFeatureMenu(Player* pPlayer, Creature* pCreature)
{
    for (uint8 i = 0; i < UndeadFeatures.size(); i++)
    {
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, UndeadFeatures[i], GOSSIP_SENDER_MAIN, ACTION_UNDEADFEATURE_MIN + i);
    }
    
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_NAV_BACK, GOSSIP_SENDER_MAIN, ACTION_GO_BACK);
    pPlayer->SEND_GOSSIP_MENU(GOSSIP_MENU_HAIRSTYLE_SELECT, pCreature->GetGUID());
}

static void ShowTaurenHornStyleMenu(Player* pPlayer, Creature* pCreature)
{
    for (uint8 i = 0; i < TaurenHornStyles.size(); i++)
    {
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, TaurenHornStyles[i], GOSSIP_SENDER_MAIN, ACTION_HORNSTYLE_MIN + i);
    }
    
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_NAV_BACK, GOSSIP_SENDER_MAIN, ACTION_GO_BACK);
    pPlayer->SEND_GOSSIP_MENU(GOSSIP_MENU_HAIRSTYLE_SELECT, pCreature->GetGUID());
}

static void ShowTaurenHornColorMenu(Player* pPlayer, Creature* pCreature)
{
    for (uint8 i = 0; i < TaurenHornColors.size(); i++)
    {
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, TaurenHornColors[i], GOSSIP_SENDER_MAIN, ACTION_HORNCOLOR_MIN + i);
    }
    
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_NAV_BACK, GOSSIP_SENDER_MAIN, ACTION_GO_BACK);
    pPlayer->SEND_GOSSIP_MENU(GOSSIP_MENU_HAIRSTYLE_SELECT, pCreature->GetGUID());
}

static void ShowMainMenu(Player* pPlayer, Creature* pCreature)
{
    uint8 race = pPlayer->GetRace();
    uint8 gender = pPlayer->GetGender();

    // Hair style options - available for all races except Tauren
    if (race != RACE_TAUREN)
    {
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_CHANGE_HAIR_STYLE, GOSSIP_SENDER_MAIN, ACTION_MENU_HAIRSTYLE);
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_CHANGE_HAIR_COLOR, GOSSIP_SENDER_MAIN, ACTION_MENU_HAIRCOLOR);
    }

    // Only show facial hair option for male characters of certain races
    if (gender == GENDER_MALE)
    {
        switch (race)
        {
            case RACE_HUMAN:
            case RACE_ORC:
            case RACE_DWARF:
            case RACE_NIGHTELF:
            case RACE_GNOME:
            {
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_CHANGE_FACIAL_HAIR, GOSSIP_SENDER_MAIN, ACTION_MENU_FACIALSTYLE);
                break;
            }
        }
    }

    // Race-specific customization options
    switch (race)
    {
        case RACE_TROLL:
        {
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_CHANGE_TROLL_TUSKS, GOSSIP_SENDER_MAIN, ACTION_MENU_TROLLTUSK);
            break;
        }
        case RACE_UNDEAD:
        {
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_CHANGE_UNDEAD_FEATURES, GOSSIP_SENDER_MAIN, ACTION_MENU_UNDEADFEATURE);
            break;
        }
        case RACE_TAUREN:
        {
            // Tauren-specific horn options
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_CHANGE_HORN_STYLE, GOSSIP_SENDER_MAIN, ACTION_MENU_HORNSTYLE);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_CHANGE_HORN_COLOR, GOSSIP_SENDER_MAIN, ACTION_MENU_HORNCOLOR);
            break;
        }
    }

    // Add shop option
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, GOSSIP_TEXT_SHOW_VENDOR_MENAU, GOSSIP_SENDER_MAIN, ACTION_MENU_SHOP);
    pPlayer->SEND_GOSSIP_MENU(GOSSIP_MENU_HAIRSTYLE_MAIN, pCreature->GetGUID());
}

bool GossipHello_HairstyleChangeNpc(Player* pPlayer, Creature* pCreature)
{
    ShowMainMenu(pPlayer, pCreature);
    return true;
}

void OnHairstyleChanged(Player* pPlayer, Creature* pCreature)
{
    const uint32 randomText = PickRandomValue(
        SAY_HAIR_STYLE_CHANGED_1,
        SAY_HAIR_STYLE_CHANGED_2,
        SAY_HAIR_STYLE_CHANGED_3,
        SAY_HAIR_STYLE_CHANGED_4);

    DoScriptText(randomText, pCreature);
    pCreature->PlayDistanceSound(1205, pPlayer); // https://www.wowhead.com/classic/sound=1205/putdownherb

    pPlayer->SetDisplayId(4); // BOX
    pPlayer->DirectSendPublicValueUpdate(UNIT_FIELD_DISPLAYID);
    pPlayer->SetDisplayId(pPlayer->GetNativeDisplayId());

    pPlayer->CLOSE_GOSSIP_MENU();
    if (auto* pAI = dynamic_cast<custom_hairstyle_npc*>(pCreature->AI()))
    {
        pAI->HasSpokenTo();
    }
}

bool GossipSelect_HairstyleChangeNpc(Player* pPlayer, Creature* pCreature, const uint32 sender, const uint32 action)
{
    // Menu navigation
    switch (action)
    {
        case ACTION_GO_BACK:
        {
            ShowMainMenu(pPlayer, pCreature);
            return true;
        }
        case ACTION_MENU_HAIRSTYLE:
        {
            ShowHairstyleMenu(pPlayer, pCreature);
            return true;
        }
        case ACTION_MENU_HAIRCOLOR:
        {
            ShowHairColorMenu(pPlayer, pCreature);
            return true;
        }
        case ACTION_MENU_FACIALSTYLE:
        {
            ShowFacialHairMenu(pPlayer, pCreature);
            return true;
        }
        case ACTION_MENU_TROLLTUSK:
        {
            ShowTrollTuskMenu(pPlayer, pCreature);
            return true;
        }
        case ACTION_MENU_UNDEADFEATURE:
        {
            ShowUndeadFeatureMenu(pPlayer, pCreature);
            return true;
        }
        case ACTION_MENU_HORNSTYLE:
        {
            ShowTaurenHornStyleMenu(pPlayer, pCreature);
            return true;
        }
        case ACTION_MENU_HORNCOLOR:
        {
            ShowTaurenHornColorMenu(pPlayer, pCreature);
            return true;
        }
        case ACTION_MENU_SHOP:
        {
            pPlayer->SEND_VENDORLIST(pCreature->GetGUID());
            return true;
        }
        case ACTION_HUMAN_FEMALE_PAGE_1:
        {
            ShowHumanFemaleHairstylePage(pPlayer, pCreature, 1);
            return true;
        }
        case ACTION_HUMAN_FEMALE_PAGE_2:
        {
            ShowHumanFemaleHairstylePage(pPlayer, pCreature, 2);
            return true;
        }
    }

    // Free feature usage for premium accounts
    if (sWorld.getConfig(CONFIG_BOOL_FEATURE_PREMIUM_ACCOUNTS) && !pPlayer->GetSession()->IsPremiumAccount())
    {
        if (pPlayer->HasItemCount(ITEM_BEAUTIFYING_TONIC, 1, false))
        {
            pPlayer->DestroyItemCount(ITEM_BEAUTIFYING_TONIC, 1, true, false);
        }
        else
        {
            ChatHandler(pPlayer).SendSysMessage(MESSAGE_MISSING_ITEM);
            pPlayer->CLOSE_GOSSIP_MENU();
            return true;
        }
    }
    
    // Handle hairstyle changes
    if (action >= ACTION_HAIRSTYLE_MIN && action <= ACTION_HAIRSTYLE_MAX)
    {
        uint8 newHairstyle = action - ACTION_HAIRSTYLE_MIN;
        pPlayer->SetByteValue(PLAYER_BYTES, PLAYER_BYTES_OFFSET_HAIR_STYLE_ID, newHairstyle);
        OnHairstyleChanged(pPlayer, pCreature);
        return true;
    }
    
    // Handle hair color changes
    if (action >= ACTION_HAIRCOLOR_MIN && action <= ACTION_HAIRCOLOR_MAX)
    {
        uint8 newHairColor = action - ACTION_HAIRCOLOR_MIN;
        pPlayer->SetByteValue(PLAYER_BYTES, PLAYER_BYTES_OFFSET_HAIR_COLOR_ID, newHairColor);
        OnHairstyleChanged(pPlayer, pCreature);
        return true;
    }
    
    // Handle facial hair changes
    if (action >= ACTION_FACIALSTYLE_MIN && action <= ACTION_FACIALSTYLE_MAX)
    {
        uint8 newFacialStyle = action - ACTION_FACIALSTYLE_MIN;
        pPlayer->SetByteValue(PLAYER_BYTES_2, PLAYER_BYTES_2_OFFSET_FACIAL_STYLE, newFacialStyle);
        OnHairstyleChanged(pPlayer, pCreature);
        return true;
    }
    
    // Handle troll tusk changes
    if (action >= ACTION_TROLLTUSK_MIN && action <= ACTION_TROLLTUSK_MAX)
    {
        uint8 newTuskStyle = action - ACTION_TROLLTUSK_MIN;
        // For trolls, the tusk style is stored in facial hair
        pPlayer->SetByteValue(PLAYER_BYTES_2, PLAYER_BYTES_2_OFFSET_FACIAL_STYLE, newTuskStyle);
        OnHairstyleChanged(pPlayer, pCreature);
        return true;
    }
    
    // Handle undead feature changes
    if (action >= ACTION_UNDEADFEATURE_MIN && action <= ACTION_UNDEADFEATURE_MAX)
    {
        uint8 newFeature = action - ACTION_UNDEADFEATURE_MIN;
        // For undead, facial features are stored in facial hair
        pPlayer->SetByteValue(PLAYER_BYTES_2, PLAYER_BYTES_2_OFFSET_FACIAL_STYLE, newFeature);
        OnHairstyleChanged(pPlayer, pCreature);
        return true;
    }
    
    // Handle tauren horn style changes
    if (action >= ACTION_HORNSTYLE_MIN && action <= ACTION_HORNSTYLE_MAX)
    {
        uint8 newHornStyle = action - ACTION_HORNSTYLE_MIN;
        // For tauren, horn style is stored in hair style
        pPlayer->SetByteValue(PLAYER_BYTES, PLAYER_BYTES_OFFSET_HAIR_STYLE_ID, newHornStyle);
        OnHairstyleChanged(pPlayer, pCreature);
        return true;
    }
    
    // Handle tauren horn color changes
    if (action >= ACTION_HORNCOLOR_MIN && action <= ACTION_HORNCOLOR_MAX)
    {
        uint8 newHornColor = action - ACTION_HORNCOLOR_MIN;
        // For tauren, horn color is stored in hair color
        pPlayer->SetByteValue(PLAYER_BYTES, PLAYER_BYTES_OFFSET_HAIR_COLOR_ID, newHornColor);
        OnHairstyleChanged(pPlayer, pCreature);
        return true;
    }

    sLog.Out(LOG_BASIC, LOG_LVL_ERROR, "[ERROR] Custom Hairstyle NPC: action could not be processed -> action = %u", action);
    return true;
}

CreatureAI* GetAI_custom_hairstyle_npc(Creature* pCreature)
{
    return new custom_hairstyle_npc(pCreature);
}

void AddSC_custom_hairstyle_npc()
{
    Script* pNewScript = new Script;
    pNewScript->Name = "custom_hairstyle_npc";
    pNewScript->GetAI = &GetAI_custom_hairstyle_npc;
    pNewScript->pGossipHello = &GossipHello_HairstyleChangeNpc;
    pNewScript->pGossipSelect = &GossipSelect_HairstyleChangeNpc;
    pNewScript->RegisterSelf();
}
