//-----------------------------------------------------------------------------
// g_spawn.c
//
// $Id: g_spawn.c,v 1.6 2001/05/12 13:15:04 mort Exp $
//
//-----------------------------------------------------------------------------
// $Log: g_spawn.c,v $
// Revision 1.6  2001/05/12 13:15:04  mort
// Forces teamplay on when ctf is enabled
//
// Revision 1.5  2001/05/12 08:20:01  mort
// CTF bug fix, makes sure flags have actually spawned before certain functions attempt to use them
//
// Revision 1.4  2001/05/12 00:37:03  ra
//
//
// Fixing various compilerwarnings.
//
// Revision 1.3  2001/05/11 16:07:25  mort
// Various CTF bits and pieces...
//
// Revision 1.2  2001/05/11 12:21:19  slicerdw
// Commented old Location support ( ADF ) With the ML/ETE Compatible one
//
// Revision 1.1.1.1  2001/05/06 17:31:52  igor_rock
// This is the PG Bund Edition V1.25 with all stuff laying around here...
//
//-----------------------------------------------------------------------------

#include "g_local.h"

typedef struct
{
        char    *name;
        void    (*spawn)(edict_t *ent);
} spawn_t;


void SP_item_health (edict_t *self);
void SP_item_health_small (edict_t *self);
void SP_item_health_large (edict_t *self);
void SP_item_health_mega (edict_t *self);

void SP_info_player_start (edict_t *ent);
void SP_info_player_deathmatch (edict_t *ent);
void SP_info_player_coop (edict_t *ent);
void SP_info_player_intermission (edict_t *ent);

void SP_func_plat (edict_t *ent);
void SP_func_rotating (edict_t *ent);
void SP_func_button (edict_t *ent);
void SP_func_door (edict_t *ent);
void SP_func_door_secret (edict_t *ent);
void SP_func_door_rotating (edict_t *ent);
void SP_func_water (edict_t *ent);
void SP_func_train (edict_t *ent);
void SP_func_conveyor (edict_t *self);
void SP_func_wall (edict_t *self);
void SP_func_object (edict_t *self);
void SP_func_explosive (edict_t *self);
void SP_func_timer (edict_t *self);
void SP_func_areaportal (edict_t *ent);
void SP_func_clock (edict_t *ent);
void SP_func_killbox (edict_t *ent);

void SP_trigger_always (edict_t *ent);
void SP_trigger_once (edict_t *ent);
void SP_trigger_multiple (edict_t *ent);
void SP_trigger_relay (edict_t *ent);
void SP_trigger_push (edict_t *ent);
void SP_trigger_hurt (edict_t *ent);
void SP_trigger_key (edict_t *ent);
void SP_trigger_counter (edict_t *ent);
void SP_trigger_elevator (edict_t *ent);
void SP_trigger_gravity (edict_t *ent);
void SP_trigger_monsterjump (edict_t *ent);

void SP_target_temp_entity (edict_t *ent);
void SP_target_speaker (edict_t *ent);
void SP_target_explosion (edict_t *ent);
void SP_target_changelevel (edict_t *ent);
void SP_target_secret (edict_t *ent);
void SP_target_goal (edict_t *ent);
void SP_target_splash (edict_t *ent);
void SP_target_spawner (edict_t *ent);
void SP_target_blaster (edict_t *ent);
void SP_target_crosslevel_trigger (edict_t *ent);
void SP_target_crosslevel_target (edict_t *ent);
void SP_target_laser (edict_t *self);
void SP_target_help (edict_t *ent);
void SP_target_actor (edict_t *ent);
void SP_target_lightramp (edict_t *self);
void SP_target_earthquake (edict_t *ent);
void SP_target_character (edict_t *ent);
void SP_target_string (edict_t *ent);

void SP_worldspawn (edict_t *ent);
void SP_viewthing (edict_t *ent);

void SP_light (edict_t *self);
void SP_light_mine1 (edict_t *ent);
void SP_light_mine2 (edict_t *ent);
void SP_info_null (edict_t *self);
void SP_info_notnull (edict_t *self);
void SP_path_corner (edict_t *self);
void SP_point_combat (edict_t *self);

void SP_misc_explobox (edict_t *self);
void SP_misc_banner (edict_t *self);
void SP_misc_satellite_dish (edict_t *self);
void SP_misc_actor (edict_t *self);
void SP_misc_gib_arm (edict_t *self);
void SP_misc_gib_leg (edict_t *self);
void SP_misc_gib_head (edict_t *self);
void SP_misc_insane (edict_t *self);
void SP_misc_deadsoldier (edict_t *self);
void SP_misc_viper (edict_t *self);
void SP_misc_viper_bomb (edict_t *self);
void SP_misc_bigviper (edict_t *self);
void SP_misc_strogg_ship (edict_t *self);
void SP_misc_teleporter (edict_t *self);
void SP_misc_teleporter_dest (edict_t *self);
void SP_misc_blackhole (edict_t *self);
void SP_misc_eastertank (edict_t *self);
void SP_misc_easterchick (edict_t *self);
void SP_misc_easterchick2 (edict_t *self);


void SP_monster_berserk (edict_t *self);
void SP_monster_gladiator (edict_t *self);
void SP_monster_gunner (edict_t *self);
void SP_monster_infantry (edict_t *self);
void SP_monster_soldier_light (edict_t *self);
void SP_monster_soldier (edict_t *self);
void SP_monster_soldier_ss (edict_t *self);
void SP_monster_tank (edict_t *self);
void SP_monster_medic (edict_t *self);
void SP_monster_flipper (edict_t *self);
void SP_monster_chick (edict_t *self);
void SP_monster_parasite (edict_t *self);
void SP_monster_flyer (edict_t *self);
void SP_monster_brain (edict_t *self);
void SP_monster_floater (edict_t *self);
void SP_monster_hover (edict_t *self);
void SP_monster_mutant (edict_t *self);
void SP_monster_supertank (edict_t *self);
void SP_monster_boss2 (edict_t *self);
void SP_monster_jorg (edict_t *self);
void SP_monster_boss3_stand (edict_t *self);

void SP_monster_commander_body (edict_t *self);


void SP_turret_breach (edict_t *self);
void SP_turret_base (edict_t *self);
void SP_turret_driver (edict_t *self);

//zucc - item replacement function
void CheckItem(edict_t *ent, gitem_t *item);

//AQ2:TNG - Slicer New location code
int ml_count = 0;
char ml_build[5];
char ml_creator[100];
//AQ2:TNG END
placedata_t locationbase[MAX_LOCATIONS_IN_BASE];

//AQ2:M
spawn_t spawns[] = {
        {"item_health", SP_item_health},
        {"item_health_small", SP_item_health_small},
        {"item_health_large", SP_item_health_large},
        {"item_health_mega", SP_item_health_mega},

        {"info_player_start", SP_info_player_start},
        {"info_player_deathmatch", SP_info_player_deathmatch},
        {"info_player_coop", SP_info_player_coop},
        {"info_player_intermission", SP_info_player_intermission},

        {"func_plat", SP_func_plat},
        {"func_button", SP_func_button},
        {"func_door", SP_func_door},
        {"func_door_secret", SP_func_door_secret},
        {"func_door_rotating", SP_func_door_rotating},
        {"func_rotating", SP_func_rotating},
        {"func_train", SP_func_train},
        {"func_water", SP_func_water},
        {"func_conveyor", SP_func_conveyor},
        {"func_areaportal", SP_func_areaportal},
        {"func_clock", SP_func_clock},
        {"func_wall", SP_func_wall},
        {"func_object", SP_func_object},
        {"func_timer", SP_func_timer},
        {"func_explosive", SP_func_explosive},
        {"func_killbox", SP_func_killbox},

        {"trigger_always", SP_trigger_always},
        {"trigger_once", SP_trigger_once},
        {"trigger_multiple", SP_trigger_multiple},
        {"trigger_relay", SP_trigger_relay},
        {"trigger_push", SP_trigger_push},
        {"trigger_hurt", SP_trigger_hurt},
        {"trigger_key", SP_trigger_key},
        {"trigger_counter", SP_trigger_counter},
        {"trigger_elevator", SP_trigger_elevator},
        {"trigger_gravity", SP_trigger_gravity},
        {"trigger_monsterjump", SP_trigger_monsterjump},

        {"target_temp_entity", SP_target_temp_entity},
        {"target_speaker", SP_target_speaker},
        {"target_explosion", SP_target_explosion},
        {"target_changelevel", SP_target_changelevel},
        {"target_secret", SP_target_secret},
        {"target_goal", SP_target_goal},
        {"target_splash", SP_target_splash},
        {"target_spawner", SP_target_spawner},
        {"target_blaster", SP_target_blaster},
        {"target_crosslevel_trigger", SP_target_crosslevel_trigger},
        {"target_crosslevel_target", SP_target_crosslevel_target},
        {"target_laser", SP_target_laser},
        {"target_help", SP_target_help},
// monster      {"target_actor", SP_target_actor},
        {"target_lightramp", SP_target_lightramp},
        {"target_earthquake", SP_target_earthquake},
        {"target_character", SP_target_character},
        {"target_string", SP_target_string},

        {"worldspawn", SP_worldspawn},
        {"viewthing", SP_viewthing},

        {"light", SP_light},
        {"light_mine1", SP_light_mine1},
        {"light_mine2", SP_light_mine2},
        {"info_null", SP_info_null},
        {"func_group", SP_info_null},
        {"info_notnull", SP_info_notnull},
        {"path_corner", SP_path_corner},
        {"point_combat", SP_point_combat},

        {"misc_explobox", SP_misc_explobox},
        {"misc_banner", SP_misc_banner},
        {"misc_satellite_dish", SP_misc_satellite_dish},
        // monster {"misc_actor", SP_misc_actor},
        {"misc_gib_arm", SP_misc_gib_arm},
        {"misc_gib_leg", SP_misc_gib_leg},
        {"misc_gib_head", SP_misc_gib_head},
        // monster {"misc_insane", SP_misc_insane},
        {"misc_deadsoldier", SP_misc_deadsoldier},
        {"misc_viper", SP_misc_viper},
        {"misc_viper_bomb", SP_misc_viper_bomb},
        {"misc_bigviper", SP_misc_bigviper},
        {"misc_strogg_ship", SP_misc_strogg_ship},
        {"misc_teleporter", SP_misc_teleporter},
        {"misc_teleporter_dest", SP_misc_teleporter_dest},
        {"misc_blackhole", SP_misc_blackhole},
        {"misc_eastertank", SP_misc_eastertank},
        {"misc_easterchick", SP_misc_easterchick},
        {"misc_easterchick2", SP_misc_easterchick2},
/* // monsters
        {"monster_berserk", SP_monster_berserk},
        {"monster_gladiator", SP_monster_gladiator},
        {"monster_gunner", SP_monster_gunner},
        {"monster_infantry", SP_monster_infantry},
        {"monster_soldier_light", SP_monster_soldier_light},
        {"monster_soldier", SP_monster_soldier},
        {"monster_soldier_ss", SP_monster_soldier_ss},
        {"monster_tank", SP_monster_tank},
        {"monster_tank_commander", SP_monster_tank},
        {"monster_medic", SP_monster_medic},
        {"monster_flipper", SP_monster_flipper},
        {"monster_chick", SP_monster_chick},
        {"monster_parasite", SP_monster_parasite},
        {"monster_flyer", SP_monster_flyer},
        {"monster_brain", SP_monster_brain},
        {"monster_floater", SP_monster_floater},
        {"monster_hover", SP_monster_hover},
        {"monster_mutant", SP_monster_mutant},
        {"monster_supertank", SP_monster_supertank},
        {"monster_boss2", SP_monster_boss2},
        {"monster_boss3_stand", SP_monster_boss3_stand},
        {"monster_jorg", SP_monster_jorg},

        {"monster_commander_body", SP_monster_commander_body},

        {"turret_breach", SP_turret_breach},
        {"turret_base", SP_turret_base},
        {"turret_driver", SP_turret_driver},
*/
        {NULL, NULL}
};


/*
===============
ED_CallSpawn

Finds the spawn function for the entity and calls it
===============
*/
void ED_CallSpawn (edict_t *ent)
{
        spawn_t *s;
        gitem_t *item;
        int             i;

        if (!ent->classname)
        {
                gi.dprintf ("ED_CallSpawn: NULL classname\n");
                return;
        }

        // check item spawn functions
        for (i=0,item=itemlist ; i<game.num_items ; i++,item++)
        {
                if (!item->classname)
                        continue;
                if (!strcmp(item->classname, ent->classname))
                {       // found it
//FIREBLADE
                        if (!teamplay->value)
                        {
//FIREBLADE
                                if ( item->flags == IT_AMMO || item->flags == IT_WEAPON )
                                        SpawnItem (ent, item);
                        }
                
                        return;
                }
                // zucc - BD's item replacement idea
                else 
                {
                        CheckItem(ent, item);
                }
        }


        // check normal spawn functions
        for (s=spawns ; s->name ; s++)
        {
                if (!strcmp(s->name, ent->classname))
                {       // found it
                        s->spawn (ent);
                        return;
                }
        }
        gi.dprintf ("%s doesn't have a spawn function\n", ent->classname);
}

// zucc BD's checkitem function
//An 2D array of items to look for and replace with...
        //item[i][0] = the Q2 item to look for
        //item[i][1] = the NS2 item to actually spawn

#define ITEM_SWITCH_COUNT 15

char *sp_item[ITEM_SWITCH_COUNT][2]=
{
        {"weapon_machinegun","weapon_MP5"},
        //{"weapon_supershotgun","weapon_HC"},
        {"weapon_bfg", "weapon_M4"},
        {"weapon_shotgun","weapon_M3"},
        //{"weapon_grenadelauncher","weapon_M203"},
        {"weapon_chaingun","weapon_Sniper"},
        {"weapon_rocketlauncher","weapon_HC"},
        {"weapon_railgun","weapon_Dual"},
        {"ammo_bullets","ammo_clip"},
        {"ammo_rockets","ammo_mag"},
        {"ammo_cells", "ammo_m4"},
        {"ammo_slugs", "ammo_sniper"},
        {"ammo_shells", "ammo_m3"},
        {"ammo_grenades", "weapon_Grenade"}
		,
		{"ammo_box", "ammo_m3"},
		{"weapon_cannon", "weapon_HC"},
		{"weapon_sniper", "weapon_Sniper"}

};

void CheckItem(edict_t *ent, gitem_t *item)
{
        int i;
        
        for(i = 0;i < ITEM_SWITCH_COUNT; i++)
        {
                //If it's a null entry, bypass it
                if(!sp_item[i][0])
                        continue;
                //Do the passed ent and our list match?
                if(strcmp(ent->classname,sp_item[i][0])==0)
                {
                        //Yep. Replace the Q2 entity with our own.
                        ent->classname = item->classname = sp_item[i][1];
//FIREBLADE                     
                        if (!teamplay->value)
                        {
//FIREBLADE
                                SpawnItem(ent,item);
                        }
                        //We found it, so don't waste time looking for more.
                        //gi.bprintf(PRINT_HIGH,"Found %s\nReplaced with %s\n",ent->classname,test);
                        return;
                }
        }
}


/*
=============
ED_NewString
=============
*/
char *ED_NewString (char *string)
{
        char    *newb, *new_p;
        int             i,l;
        
        l = strlen(string) + 1;

        newb = gi.TagMalloc (l, TAG_LEVEL);

        new_p = newb;

        for (i=0 ; i< l ; i++)
        {
                if (string[i] == '\\' && i < l-1)
                {
                        i++;
                        if (string[i] == 'n')
                                *new_p++ = '\n';
                        else
                                *new_p++ = '\\';
                }
                else
                        *new_p++ = string[i];
        }
        
        return newb;
}




/*
===============
ED_ParseField

Takes a key/value pair and sets the binary values
in an edict
===============
*/
void ED_ParseField (char *key, char *value, edict_t *ent)
{
        field_t *f;
        byte    *b;
        float   v;
        vec3_t  vec;

        for (f=fields ; f->name ; f++)
        {
// FFL_NOSPAWN check in the following added in 3.20.  Adding here.  -FB
                if (!(f->flags & FFL_NOSPAWN) && !Q_stricmp(f->name, key))
                {       // found it
                        if (f->flags & FFL_SPAWNTEMP)
                                b = (byte *)&st;
                        else
                                b = (byte *)ent;

                        switch (f->type)
                        {
                        case F_LSTRING:
                                *(char **)(b+f->ofs) = ED_NewString (value);
                                break;
                        case F_VECTOR:
                                sscanf (value, "%f %f %f", &vec[0], &vec[1], &vec[2]);
                                ((float *)(b+f->ofs))[0] = vec[0];
                                ((float *)(b+f->ofs))[1] = vec[1];
                                ((float *)(b+f->ofs))[2] = vec[2];
                                break;
                        case F_INT:
                                *(int *)(b+f->ofs) = atoi(value);
                                break;
                        case F_FLOAT:
                                *(float *)(b+f->ofs) = atof(value);
                                break;
                        case F_ANGLEHACK:
                                v = atof(value);
                                ((float *)(b+f->ofs))[0] = 0;
                                ((float *)(b+f->ofs))[1] = v;
                                ((float *)(b+f->ofs))[2] = 0;
                                break;
                        case F_IGNORE:
                                break;
// AQ:TNG JBravo fixing compiler warning. Still not sure 'bout this
			default:
				return;
// End compiler warning fix
                        }
                        return;
                }
        }
        gi.dprintf ("%s is not a field\n", key);
}

/*
====================
ED_ParseEdict

Parses an edict out of the given string, returning the new position
ed should be a properly initialized empty edict.
====================
*/
char *ED_ParseEdict (char *data, edict_t *ent)
{
        qboolean        init;
        char            keyname[256];
        char            *com_token;

        init = false;
        memset (&st, 0, sizeof(st));

// go through all the dictionary pairs
        while (1)
        {       
        // parse key
                com_token = COM_Parse (&data);
                if (com_token[0] == '}')
                        break;
                if (!data)
                        gi.error ("ED_ParseEntity: EOF without closing brace");

                strncpy (keyname, com_token, sizeof(keyname)-1);
                
        // parse value  
                com_token = COM_Parse (&data);
                if (!data)
                        gi.error ("ED_ParseEntity: EOF without closing brace");

                if (com_token[0] == '}')
                        gi.error ("ED_ParseEntity: closing brace without data");

                init = true;    

        // keynames with a leading underscore are used for utility comments,
        // and are immediately discarded by quake
                if (keyname[0] == '_')
                        continue;

                ED_ParseField (keyname, com_token, ent);
        }

        if (!init)
                memset (ent, 0, sizeof(*ent));

        return data;
}


/*
================
G_FindTeams

Chain together all entities with a matching team field.

All but the first will have the FL_TEAMSLAVE flag set.
All but the last will have the teamchain field set to the next one
================
*/
void G_FindTeams (void)
{
        edict_t *e, *e2, *chain;
        int             i, j;
        int             c, c2;

        c = 0;
        c2 = 0;
        for (i=1, e=g_edicts+i ; i < globals.num_edicts ; i++,e++)
        {
                if (!e->inuse)
                        continue;
                if (!e->team)
                        continue;
                if (e->flags & FL_TEAMSLAVE)
                        continue;
                chain = e;
                e->teammaster = e;
                c++;
                c2++;
                for (j=i+1, e2=e+1 ; j < globals.num_edicts ; j++,e2++)
                {
                        if (!e2->inuse)
                                continue;
                        if (!e2->team)
                                continue;
                        if (e2->flags & FL_TEAMSLAVE)
                                continue;
                        if (!strcmp(e->team, e2->team))
                        {
                                c2++;
                                chain->teamchain = e2;
                                e2->teammaster = e;
                                chain = e2;
                                e2->flags |= FL_TEAMSLAVE;
                        }
                }
        }

        gi.dprintf ("%i teams with %i entities\n", c, c2);
}

/*
==============
SpawnEntities

Creates a server's entity / program execution context by
parsing textual entity definitions out of an ent file.
==============
*/
void SpawnEntities (char *mapname, char *entities, char *spawnpoint)
{
        edict_t         *ent;
        int                     inhibit;
        char            *com_token;
        int                     i;
        float           skill_level;
//AQ2:TNG New Location Code
		char locfile[256];
		char line[256];
		FILE *f;
		int readmore, x,y,z,rx,ry,rz,count;
		char *locationstr, *param;
		cvar_t *game_cvar;
		int u;
	//	placedata_t temp;
//AQ2:TNG END

//AQ2:M CTF
		if(ctf->value)
		{
			// Make sure teamplay is enabled
			if(!teamplay->value)
			{
				gi.dprintf("CTF Enabled - Forcing teamplay on\n");
				teamplay->value = 1;
				strcpy(teamplay->string,"1");
			}
		}
//AQ2:M CTF

        skill_level = floor (skill->value);
        if (skill_level < 0)
                skill_level = 0;
        if (skill_level > 3)
                skill_level = 3;
        if (skill->value != skill_level)
                gi.cvar_forceset("skill", va("%f", skill_level));

        SaveClientData ();

        gi.FreeTags (TAG_LEVEL);

        memset (&level, 0, sizeof(level));
        memset (g_edicts, 0, game.maxentities * sizeof (g_edicts[0]));

        strncpy (level.mapname, mapname, sizeof(level.mapname)-1);
        strncpy (game.spawnpoint, spawnpoint, sizeof(game.spawnpoint)-1);

        // set client fields on player ents
        for (i=0 ; i<game.maxclients ; i++)
                g_edicts[i+1].client = game.clients + i;

        ent = NULL;
        inhibit = 0;

// parse ents
        while (1)
        {
                // parse the opening brace      
                com_token = COM_Parse (&entities);
                if (!entities)
                        break;
                if (com_token[0] != '{')
                        gi.error ("ED_LoadFromFile: found %s when expecting {",com_token);

                if (!ent)
                        ent = g_edicts;
                else
                        ent = G_Spawn ();
                entities = ED_ParseEdict (entities, ent);

                // yet another map hack
                if (!Q_stricmp(level.mapname, "command") && !stricmp(ent->classname, "trigger_once") && !stricmp(ent->model, "*27"))
                        ent->spawnflags &= ~SPAWNFLAG_NOT_HARD;

                // remove things (except the world) from different skill levels or deathmatch
                if (ent != g_edicts)
                {
                        if (deathmatch->value)
                        {
                                if ( ent->spawnflags & SPAWNFLAG_NOT_DEATHMATCH )
                                {
                                        G_FreeEdict (ent);      
                                        inhibit++;
                                        continue;
                                }
                        }
                        else
                        {
                                if ( /* ((coop->value) && (ent->spawnflags & SPAWNFLAG_NOT_COOP)) || */
                                        ((skill->value == 0) && (ent->spawnflags & SPAWNFLAG_NOT_EASY)) ||
                                        ((skill->value == 1) && (ent->spawnflags & SPAWNFLAG_NOT_MEDIUM)) ||
                                        (((skill->value == 2) || (skill->value == 3)) && (ent->spawnflags & SPAWNFLAG_NOT_HARD))
                                        )
                                        {
                                                G_FreeEdict (ent);      
                                                inhibit++;
                                                continue;
                                        }
                        }

                        ent->spawnflags &= ~(SPAWNFLAG_NOT_EASY|SPAWNFLAG_NOT_MEDIUM|SPAWNFLAG_NOT_HARD|SPAWNFLAG_NOT_COOP|SPAWNFLAG_NOT_DEATHMATCH);
                }

                ED_CallSpawn (ent);
        }       

        gi.dprintf ("%i entities inhibited\n", inhibit);

        G_FindTeams ();

        PlayerTrail_Init ();

//FIREBLADE
        if (!teamplay->value)
        {
//FIREBLADE
                //zucc for special items
                SetupSpecSpawn();
        }
//AQ2:TNG Slicer - New location  code
	memset(ml_build,0,sizeof(ml_build));
	memset(ml_creator,0,sizeof(ml_creator));


	game_cvar = gi.cvar("game", "", 0);

	if(!*game_cvar->string)
		sprintf(locfile, "%s/tng/%s.aqg", GAMEVERSION, mapname);
	else
		sprintf(locfile, "%s/tng/%s.aqg", game_cvar->string, mapname);

	f = fopen(locfile,"rt");
	if (!f)
	{
		ml_count = 0;	
		gi.dprintf("No location file for %s\n",mapname);
		return;
	}

	gi.dprintf("Location file: %s\n",mapname);
		
	readmore = 1;
	count = 0;

	
	while (readmore)
	{
		readmore = ( fgets(line,256,f) != NULL );
		param = strtok(line, " :\n\0");
        if(line[0] == '#' && line[2] == 'C')
		{
			u = 0;
			for(i=10;line[i]!='\n';i++)
			{
				ml_creator[u] = line[i];
				u++;
			}
		}
		if(line[0] == '#' && line[2] == 'B')
		{
			u = 0;
			for(i=8;line[i]!='\n';i++)
			{
				if(line[i] != ' ')
				{
				ml_build[u] = line[i];
				u++;
				}
			}
			
		}
		ml_build[5] = 0;
		ml_creator[100] = 0;

		// TODO: better support for file comments
		if (!param || param[0] == '#')
		{
			continue;
		}


		x = atoi(param);
				
		param = strtok(NULL, " :\n\0");
		if (!param) continue;
		y = atoi(param);

		param = strtok(NULL, " :\n\0");
		if (!param) continue;
		z = atoi(param);

		param = strtok(NULL, " :\n\0");
		if (!param) continue;
		rx = atoi(param);

		param = strtok(NULL, " :\n\0");
		if (!param) continue;
		ry = atoi(param);

		param = strtok(NULL, " :\n\0");
		if (!param) continue;
		rz = atoi(param);

		param = strtok(NULL, "\n\0");
		if (!param) continue;
		locationstr = param;

		locationbase[count].x = x;
		locationbase[count].y = y;
		locationbase[count].z = z;
		locationbase[count].rx = rx;
		locationbase[count].ry = ry;
		locationbase[count].rz = rz;
		strcpy(locationbase[count].desc, locationstr);

		count++;
				
		if (count >= MAX_LOCATIONS_IN_BASE)
		{
			gi.dprintf("Cannot read more than %d locations.\n",MAX_LOCATIONS_IN_BASE);
			break;
		}
	}

	ml_count = count;
	fclose(f);
	gi.dprintf("Found %d locations.\n",count);


	// AQ2:TNG - Load ctf locations
	if(ctf->value)
	{
		spawnFlags(mapname);
	}
}


//===================================================================

#if 0
        // cursor positioning
        xl <value>
        xr <value>
        yb <value>
        yt <value>
        xv <value>
        yv <value>

        // drawing
        statpic <name>
        pic <stat>
        num <fieldwidth> <stat>
        string <stat>

        // control
        if <stat>
        ifeq <stat> <value>
        ifbit <stat> <value>
        endif

#endif

char *single_statusbar = 
"yb     -24 "

// health
"xv     0 "
"hnum "
"xv     50 "
"pic 0 "

// ammo
"if 2 "
"       xv      100 "
"       anum "
"       xv      150 "
"       pic 2 "
"endif "

/*
// armor
"if 4 "
"       xv      200 "
"       rnum "
"       xv      250 "
"       pic 4 "
"endif "
*/

// selected item
"if 6 "
"       xv      296 "
"       pic 6 "
"endif "

"yb     -50 "

// picked up item
"if 7 "
"       xv      0 "
"       pic 7 "
"       xv      26 "
"       yb      -42 "
"       stat_string 8 "
"       yb      -50 "
"endif "

// timer
"if 9 "
"       xv      262 "
"       num     2       10 "
"       xv      296 "
"       pic     9 "
"endif "

//  help / weapon icon 
"if 11 "
"       xv      148 "
"       pic     11 "
"endif "

// zucc

// sniper zoom graphic/icon

"if 18 "
"       xr      0 "
"       yb      0 "
"       xv      0 "
"       yv      0 "
"       pic 18 "
"endif "





// clip(s)
// puts them all the way on the right side of the screen
"if 16 "
"       xv      0 "
"       yv      0 "
"       yb      -24 "
"       xr      -60 "
"       num 2   17 "
"       xr      -24 "
"       pic 16 "
"endif "

// zucc special item ( vest etc )
"if 19 "
"       xv      0 "
"       yv      0 "
"       yb      -72 "
"       xr      -24 "
"       pic 19 "
"endif "

// zucc special weapon
"if 20 "
"       xv      0 "
"       yv      0 "
"       yb      -48 "
"       xr      -24 "
"       pic 20 "
"endif "

// zucc grenades

"if 28 "
"       xv      0 "
"               yv              0 "
"               yb              -96 "
"               xr              -60 "
"       num 2 29 "
"       xr      -24 "
"       pic 28 "
"endif "


"if 21 "
  "xv 0 "
  "yb -58 "
  "string \"Viewing\" "
  "xv 64 "
  "stat_string 21 "
"endif "
;


char *dm_statusbar =
"yb     -24 "

// health
"xv     0 "
"hnum "
"xv     50 "
"pic 0 "

// ammo
"if 2 "
"       xv      100 "
"       anum "
"       xv      150 "
"       pic 2 "
"endif "


/*
// armor
"if 4 "
"       xv      200 "
"       rnum "
"       xv      250 "
"       pic 4 "
"endif "
*/
// selected item
"if 6 "
"       xv      296 "
"       pic 6 "
"endif "

"yb     -50 "

// picked up item
"if 7 "
"       xv      0 "
"       pic 7 "
"       xv      26 "
"       yb      -42 "
"       stat_string 8 "
"       yb      -50 "
"endif "

/*
// timer
"if 9 "
"       xv      246 "
"       num     2       10 "
"       xv      296 "
"       pic     9 "
"endif "
*/
//  help / weapon icon 
"if 11 "
"       xv      148 "
"       pic     11 "
"endif "

// zucc
// clip(s)
"if 16 "
"       xv      0 "
"       yv      0 "
"       yb      -24 "
"       xr      -60 "
"       num 2   17 "
"       xr      -24 "
"       pic 16 "
"endif "

// zucc special item ( vest etc )
"if 19 "
"       xv      0 "
"       yv      0 "
"       yb      -72 "
"       xr      -24 "
"       pic 19 "
"endif "

// zucc special weapon
"if 20 "
"       xv      0 "
"       yv      0 "
"       yb      -48 "
"       xr      -24 "
"       pic 20 "
"endif "

// zucc grenades

"if 28 "
"       xv      0 "
"               yv              0 "
"               yb              -96 "
"               xr              -60 "
"       num 2 29 "
"       xr      -24 "
"       pic 28 "
"endif "

"if 21 "
  "xv 0 "
  "yb -58 "
  "string \"Viewing\" "
  "xv 64 "
  "stat_string 21 "
"endif "

// sniper graphic/icon

"if 18 "
"       xr      0 "
"       yb      0 "
"       xv      0 "
"       yv      0 "
"       pic 18 "
"endif "

//  frags
"xr     -50 "
"yt 2 "
"num 3 14"
;



/* DM status bar for teamplay without individual scores -FB: */
char *dm_noscore_statusbar =
"yb     -24 "

// health
"xv     0 "
"hnum "
"xv     50 "
"pic 0 "

// ammo
"if 2 "
"       xv      100 "
"       anum "
"       xv      150 "
"       pic 2 "
"endif "


/*
// armor
"if 4 "
"       xv      200 "
"       rnum "
"       xv      250 "
"       pic 4 "
"endif "
*/
// selected item
"if 6 "
"       xv      296 "
"       pic 6 "
"endif "

"yb     -50 "

// picked up item
"if 7 "
"       xv      0 "
"       pic 7 "
"       xv      26 "
"       yb      -42 "
"       stat_string 8 "
"       yb      -50 "
"endif "

/*
// timer
"if 9 "
"       xv      246 "
"       num     2       10 "
"       xv      296 "
"       pic     9 "
"endif "
*/
//  help / weapon icon 
"if 11 "
"       xv      148 "
"       pic     11 "
"endif "

// zucc
// clip(s)
"if 16 "
"       xv      0 "
"       yv      0 "
"       yb      -24 "
"       xr      -60 "
"       num 2   17 "
"       xr      -24 "
"       pic 16 "
"endif "

// zucc special item ( vest etc )
"if 19 "
"       xv      0 "
"       yv      0 "
"       yb      -72 "
"       xr      -24 "
"       pic 19 "
"endif "

// zucc special weapon
"if 20 "
"       xv      0 "
"       yv      0 "
"       yb      -48 "
"       xr      -24 "
"       pic 20 "
"endif "

// zucc grenades

"if 28 "
"       xv      0 "
"               yv              0 "
"               yb              -96 "
"               xr              -60 "
"       num 2 29 "
"       xr      -24 "
"       pic 28 "
"endif "

"if 21 "
  "xv 0 "
  "yb -58 "
  "string \"Viewing\" "
  "xv 64 "
  "stat_string 21 "
"endif "

// sniper graphic/icon

"if 18 "
"       xr      0 "
"       yb      0 "
"       xv      0 "
"       yv      0 "
"       pic 18 "
"endif "

/*
//  frags
"xr     -50 "
"yt 2 "
"num 3 14"
*/
;
// END FB

// AQ2:CTF
/* ctf status bar - Mort: */
char *ctf_statusbar =
"yb     -24 "

// health
"xv     0 "
"hnum "
"xv     50 "
"pic 0 "

// ammo
"if 2 "
"       xv      100 "
"       anum "
"       xv      150 "
"       pic 2 "
"endif "


/*
// armor
"if 4 "
"       xv      200 "
"       rnum "
"       xv      250 "
"       pic 4 "
"endif "
*/
// selected item
"if 6 "
"       xv      296 "
"       pic 6 "
"endif "

"yb     -50 "

// picked up item
"if 7 "
"       xv      0 "
"       pic 7 "
"       xv      26 "
"       yb      -42 "
"       stat_string 8 "
"       yb      -50 "
"endif "

/*
// timer
"if 9 "
"       xv      246 "
"       num     2       10 "
"       xv      296 "
"       pic     9 "
"endif "
*/
//  help / weapon icon
"if 11 "
"       xv      148 "
"       pic     11 "
"endif "

// zucc
// clip(s)
"if 16 "
"       xv      0 "
"       yv      0 "
"       yb      -24 "
"       xr      -60 "
"       num 2   17 "
"       xr      -24 "
"       pic 16 "
"endif "

// zucc special item ( vest etc )
"if 19 "
"       xv      0 "
"       yv      0 "
"       yb      -72 "
"       xr      -24 "
"       pic 19 "
"endif "

// zucc special weapon
"if 20 "
"       xv      0 "
"       yv      0 "
"       yb      -48 "
"       xr      -24 "
"       pic 20 "
"endif "

// zucc grenades

"if 28 "
"       xv      0 "
"               yv              0 "
"               yb              -96 "
"               xr              -60 "
"       num 2 29 "
"       xr      -24 "
"       pic 28 "
"endif "

"if 21 "
  "xv 0 "
  "yb -58 "
  "string \"Viewing\" "
  "xv 64 "
  "stat_string 21 "
"endif "

// sniper graphic/icon

"if 18 "
"       xr      0 "
"       yb      0 "
"       xv      0 "
"       yv      0 "
"       pic 18 "
"endif "

// flags

"if 30"
"		xr      -24 "
"		yt      30 "
"       pic 30 "
"endif"

"if 31"
"		xr     -48 "
"		yt      30 "
"       pic 31 "
"endif"


//  frags
"xr     -50 "
"yt 2 "
"num 3 14"

;


/*QUAKED worldspawn (0 0 0) ?

Only used for the world.
"sky"   environment map name
"skyaxis"       vector axis for rotating sky
"skyrotate"     speed of rotation in degrees/second
"sounds"        music cd track number
"gravity"       800 is default gravity
"message"       text to print at user logon
*/
void SP_worldspawn (edict_t *ent)
{
        ent->movetype = MOVETYPE_PUSH;
        ent->solid = SOLID_BSP;
        ent->inuse = true;                      // since the world doesn't use G_Spawn()
        ent->s.modelindex = 1;          // world model is always index 1

        //---------------

		// AQ2:TNG - CTF
		loadedFlags = 0; // Fixes a bug with when the flags load

        // reserve some spots for dead player bodies for coop / deathmatch
        InitBodyQue ();

        // set configstrings for items
        SetItemNames ();

        if (st.nextmap)
                strcpy (level.nextmap, st.nextmap);

        // make some data visible to the server

        if (ent->message && ent->message[0])
        {
                gi.configstring (CS_NAME, ent->message);
                strncpy (level.level_name, ent->message, sizeof(level.level_name));
        }
        else
                strncpy (level.level_name, level.mapname, sizeof(level.level_name));

        if (st.sky && st.sky[0])
                gi.configstring (CS_SKY, st.sky);
        else
                gi.configstring (CS_SKY, "unit1_");

        gi.configstring (CS_SKYROTATE, va("%f", st.skyrotate) );

        gi.configstring (CS_SKYAXIS, va("%f %f %f",
                st.skyaxis[0], st.skyaxis[1], st.skyaxis[2]) );

        gi.configstring (CS_CDTRACK, va("%i", ent->sounds) );

        gi.configstring (CS_MAXCLIENTS, va("%i", (int)(maxclients->value) ) );

//FIREBLADE
	if (nohud->value)
	{
		gi.configstring(CS_STATUSBAR, "");
	}
		else
//FIREBLADE
	{
        	// status bar program
			if(ctf->value)
			{
				gi.configstring (CS_STATUSBAR, ctf_statusbar);
			}
        	if (deathmatch->value)
//FIREBLADE
		{
			if (noscore->value && teamplay->value)
			{
               	 	gi.configstring (CS_STATUSBAR, dm_noscore_statusbar);
			}
				else
			{
               	 	gi.configstring (CS_STATUSBAR, dm_statusbar);
			}
		}
//FIREBLADE
        	else
                	gi.configstring (CS_STATUSBAR, single_statusbar);
	}

        //---------------


        // help icon for statusbar
        gi.imageindex ("i_help");
        level.pic_health = gi.imageindex ("i_health");
        gi.imageindex ("help");
        gi.imageindex ("field_3");

        // zucc - preload sniper stuff
        gi.imageindex ("scope2x");
        gi.imageindex ("scope4x");
        gi.imageindex ("scope6x");

//FIREBLADE
        gi.soundindex("atl/lights.wav");
        gi.soundindex("atl/camera.wav");
        gi.soundindex("atl/action.wav");
        gi.imageindex("tag1");
        gi.imageindex("tag2");
        gi.imageindex("tag3");
        if (teamplay->value)
        {
                if (team1_skin_index[0] == 0)
                {
                        gi.dprintf("No skin was specified for team 1 in config file.  Exiting.\n");
                        exit(1);
                }
                gi.imageindex(team1_skin_index);
                if (team2_skin_index[0] == 0)
                {
                        gi.dprintf("No skin was specified for team 2 in config file.  Exiting.\n");
                        exit(1);
                }
                gi.imageindex(team2_skin_index);
        }
        PrecacheRadioSounds();
//PG BUND - Begin
       	PrecacheUserSounds();
//AQ2:TNG - Slicer Old location support
       	//DescListInit(level.mapname);
//AQ2:TNG END
       	TourneyInit();
       	vInitLevel();
//PG BUND - End

        team_round_going = 0;
        lights_camera_action = 0;
        holding_on_tie_check = 0;
        team_round_countdown = 0;
	timewarning = 0;
	fragwarning = 0;
//FIREBLADE

        if (!st.gravity)
                gi.cvar_set("sv_gravity", "800");
        else
                gi.cvar_set("sv_gravity", st.gravity);

        snd_fry = gi.soundindex ("player/fry.wav");     // standing in lava / slime

        PrecacheItem (FindItem ("Blaster"));

        gi.soundindex ("player/lava1.wav");
        gi.soundindex ("player/lava2.wav");

        gi.soundindex ("misc/pc_up.wav");
        gi.soundindex ("misc/talk1.wav");

        gi.soundindex ("misc/udeath.wav");

        // gibs
        gi.soundindex ("items/respawn1.wav");

        // sexed sounds
        gi.soundindex ("*death1.wav");
        gi.soundindex ("*death2.wav");
        gi.soundindex ("*death3.wav");
        gi.soundindex ("*death4.wav");
        gi.soundindex ("*fall1.wav");
        gi.soundindex ("*fall2.wav");   
        gi.soundindex ("*gurp1.wav");           // drowning damage
        gi.soundindex ("*gurp2.wav");   
        gi.soundindex ("*jump1.wav");           // player jump
        gi.soundindex ("*pain25_1.wav");
        gi.soundindex ("*pain25_2.wav");
        gi.soundindex ("*pain50_1.wav");
        gi.soundindex ("*pain50_2.wav");
        gi.soundindex ("*pain75_1.wav");
        gi.soundindex ("*pain75_2.wav");
        gi.soundindex ("*pain100_1.wav");
        gi.soundindex ("*pain100_2.wav");

        //-------------------

        // precache vwep models
        gi.modelindex( "#w_mk23.md2");
        gi.modelindex( "#w_mp5.md2");
        gi.modelindex( "#w_m4.md2");
        gi.modelindex( "#w_cannon.md2");
        gi.modelindex( "#w_super90.md2");
        gi.modelindex( "#w_sniper.md2");
        gi.modelindex( "#w_akimbo.md2");
        gi.modelindex( "#w_knife.md2"); 
        gi.modelindex( "#a_m61frag.md2");

        gi.soundindex ("player/gasp1.wav");             // gasping for air
        gi.soundindex ("player/gasp2.wav");             // head breaking surface, not gasping

        gi.soundindex ("player/watr_in.wav");   // feet hitting water
        gi.soundindex ("player/watr_out.wav");  // feet leaving water

        gi.soundindex ("player/watr_un.wav");   // head going underwater
        
        gi.soundindex ("player/u_breath1.wav");
        gi.soundindex ("player/u_breath2.wav");

        gi.soundindex ("items/pkup.wav");               // bonus item pickup
        gi.soundindex ("world/land.wav");               // landing thud
        gi.soundindex ("misc/h2ohit1.wav");             // landing splash

        gi.soundindex ("items/damage.wav");
        gi.soundindex ("items/protect.wav");
        gi.soundindex ("items/protect4.wav");
        gi.soundindex ("weapons/noammo.wav");

        gi.soundindex ("infantry/inflies1.wav");

        sm_meat_index = gi.modelindex ("models/objects/gibs/sm_meat/tris.md2");
        gi.modelindex ("models/objects/gibs/arm/tris.md2");
        gi.modelindex ("models/objects/gibs/bone/tris.md2");
        gi.modelindex ("models/objects/gibs/bone2/tris.md2");
        gi.modelindex ("models/objects/gibs/chest/tris.md2");
        gi.modelindex ("models/objects/gibs/skull/tris.md2");
        gi.modelindex ("models/objects/gibs/head2/tris.md2");

		// AQ2:M - CTF stuff :)
		if(ctf->value)
		{
			gi.soundindex("ctf/flagret.wav");
			gi.soundindex("ctf/flagcap.wav");
			gi.soundindex("ctf/flagtk.wav");
			gi.modelindex("models/flags/flag1.md2");
			gi.modelindex("models/flags/flag2.md2");
			gi.imageindex("i_ctf1");
			gi.imageindex("i_ctf1t");
			gi.imageindex("i_ctf2");
			gi.imageindex("i_ctf2t");
		}

//
// Setup light animation tables. 'a' is total darkness, 'z' is doublebright.
//

        // 0 normal
        gi.configstring(CS_LIGHTS+0, "m");
        
        // 1 FLICKER (first variety)
        gi.configstring(CS_LIGHTS+1, "mmnmmommommnonmmonqnmmo");
        
        // 2 SLOW STRONG PULSE
        gi.configstring(CS_LIGHTS+2, "abcdefghijklmnopqrstuvwxyzyxwvutsrqponmlkjihgfedcba");
        
        // 3 CANDLE (first variety)
        gi.configstring(CS_LIGHTS+3, "mmmmmaaaaammmmmaaaaaabcdefgabcdefg");
        
        // 4 FAST STROBE
        gi.configstring(CS_LIGHTS+4, "mamamamamama");
        
        // 5 GENTLE PULSE 1
        gi.configstring(CS_LIGHTS+5,"jklmnopqrstuvwxyzyxwvutsrqponmlkj");
        
        // 6 FLICKER (second variety)
        gi.configstring(CS_LIGHTS+6, "nmonqnmomnmomomno");
        
        // 7 CANDLE (second variety)
        gi.configstring(CS_LIGHTS+7, "mmmaaaabcdefgmmmmaaaammmaamm");
        
        // 8 CANDLE (third variety)
        gi.configstring(CS_LIGHTS+8, "mmmaaammmaaammmabcdefaaaammmmabcdefmmmaaaa");
        
        // 9 SLOW STROBE (fourth variety)
        gi.configstring(CS_LIGHTS+9, "aaaaaaaazzzzzzzz");
        
        // 10 FLUORESCENT FLICKER
        gi.configstring(CS_LIGHTS+10, "mmamammmmammamamaaamammma");

        // 11 SLOW PULSE NOT FADE TO BLACK
        gi.configstring(CS_LIGHTS+11, "abcdefghijklmnopqrrqponmlkjihgfedcba");
        
        // styles 32-62 are assigned by the light program for switchable lights

        // 63 testing
        gi.configstring(CS_LIGHTS+63, "a");
	
//FB 6/2/99
        if (took_damage != NULL)
                gi.TagFree(took_damage);
        took_damage = (int *)gi.TagMalloc(sizeof(int) * game.maxclients, TAG_GAME);
//FB 6/2/99
}

