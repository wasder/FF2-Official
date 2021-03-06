//Freak Fortress 2 include file.
#include <morecolors>
#include <sdktools>
#include <tf2>

#define FF2FLAG_UBERREADY				(1<<1)		//Used when medic says "I'm charged!"
#define FF2FLAG_ISBUFFED				(1<<2)		//Used when soldier uses the Battalion's Backup
#define FF2FLAG_CLASSTIMERDISABLED 		(1<<3)		//Used to prevent clients' timer
#define FF2FLAG_HUDDISABLED				(1<<4)		//Used to prevent custom hud from clients' timer
#define FF2FLAG_BOTRAGE					(1<<5)		//Used by bots to use Boss's rage
#define FF2FLAG_TALKING					(1<<6)		//Used by Bosses with "sound_block_vo" to disable block for some lines
#define FF2FLAG_ALLOWSPAWNINBOSSTEAM	(1<<7)		//Used to allow spawn players in Boss's team
#define FF2FLAG_USEBOSSTIMER			(1<<8)		//Used to prevent Boss's timer
#define FF2FLAG_USINGABILITY			(1<<9)		//Used to prevent Boss's hints about abilities buttons
#define FF2FLAG_CLASSHELPED				(1<<10)
#define FF2FLAG_HASONGIVED				(1<<11)
#define FF2FLAG_CHANGECVAR				(1<<12)		//Used to prevent SMAC from kicking bosses who are using certain rages
#define FF2FLAGS_SPAWN					~FF2FLAG_UBERREADY & ~FF2FLAG_ISBUFFED & ~FF2FLAG_TALKING & ~FF2FLAG_ALLOWSPAWNINBOSSTEAM & ~FF2FLAG_CHANGECVAR & FF2FLAG_USEBOSSTIMER & FF2FLAG_USINGABILITY

#if defined _FF2_included
 #endinput
#endif
#define _FF2_included

/**
 * Is Freak Fortress enabled?
 *
 * @return	False if FF2 is disabled
 *			True if FF2 is enabled
 */
native bool:FF2_IsFF2Enabled();

/**
 * Gets current round state
 *
 * @return	0 - in setup
 *			1 - round is in progress (due to a bug in arena mode, stalemate will also return 1)
 *			2 - someone wins
 */
native FF2_GetRoundState();

/**
 * Gets UserID of current Boss
 *
 * @param client	Boss's index
 * @return			Userid of boss (-1 if Boss does not exist)
 */
native FF2_GetBossUserId(client=0);

/**
 * Gets the boss index of a client
 *
 * @param client	The client used to search for the boss index
 * @return			Boss index of that client.  If client is not boss, returns -1
 */
native FF2_GetBossIndex(client);

/**
 * Gets current team of Boss
 * @return	Number of boss's team
 */
native FF2_GetBossTeam();

/**
 * Gets character name of current Boss
 *
 * @param client 			Boss's index
 * @param buffer			Buffer for boss' character name
 * @param bufferLength		Length of buffer string
 * @param clientMeaning		0 - "client" parameter means index of current Boss
 *							1 - "client" parameter means number of Boss in characters.cfg-1
 * @return					True if boss exists, false if not
 */
native bool:FF2_GetBossSpecial(client=0, String:buffer[], bufferLength, clientMeaning=0);

/**
 * Gets current health of the current Boss
 *
 * @param client	Boss's index
 * @return			Current health of the Boss
 */
native FF2_GetBossHealth(client=0);

/**
 * Sets health of the current Boss
 *
 * @param client	Boss's index
 * @param health	New health value
 * @noreturn
 */
native FF2_SetBossHealth(client, health);

/**
 * Gets max Health of current Boss
 *
 * @param client 	Boss's index
 * @return			Max health of Boss
 */
native FF2_GetBossMaxHealth(client=0);

/**
 * Sets max health of the current Boss
 *
 * @param client	Boss's index
 * @param health	New max health value
 * @noreturn
 */
native FF2_SetBossMaxHealth(client, health);

/**
 * Gets current number of lives of the current Boss
 *
 * @param client	Boss's index
 * @return 			Number of lives the boss has remaining
 */
native FF2_GetBossLives(client);

/**
 * Sets current number of lives of the current Boss
 *
 * @param client	Boss's index
 * @param lives		New number of lives
 * @noreturn
 */
native FF2_SetBossLives(client, lives);

/**
 * Gets max number of lives of the current Boss
 *
 * @param client	Boss's index
 * @return			Max number of lives of the Boss
 */
native FF2_GetBossMaxLives(client);

/**
 * Sets max number of lives of the current Boss
 *
 * @param client	Boss's index
 * @param lives		New max number of lives
 * @noreturn
 */
native FF2_SetBossMaxLives(client, lives);

/**
 * Gets charge meter value of current Boss
 *
 * @param client	Boss's index
 * @param slot		Slot of charge meter
 *						0 - rage
 *						1 - as usual, used for brave jump or teleport
 *						2 - other charged abilities
 * @return			Charge value of the Boss
 */
native Float:FF2_GetBossCharge(client, slot);

/**
 * Sets charge meter value of current Boss
 *
 * @param client	Boss's index
 * @param slot		Slot of charge meter
 *						0 - rage
 *						1 - as usual, used for brave jump or teleport
 *						2 - other charged abilities
 * @param value		New value of charge
 * @noreturn
 */
native FF2_SetBossCharge(client, slot, Float:value);

/**
 * Gets damage dealt by this client
 *
 * @param client 	Client's index
 * @return			Damage dealt
 */
native FF2_GetClientDamage(client);

/**
 * Gets an ability's rage distance
 *
 * @param client		Boss's index
 * @param pluginName	Name of plugin with this ability
 * @param abilityName	Name of ability (use null string if you want get boss's global "ragedist" value)
 * @return				Ability's rage distance
 */
native Float:FF2_GetRageDist(client=0, const String:pluginName[]="", const String:abilityName[]="");

/**
 * Finds if a Boss has a certain ability
 *
 * @param client		Boss's index
 * @param pluginName	Name of plugin with this ability
 * @param abilityName 	Name of ability
 * @return				True if the boss has this ability, false if it doesn't
 */
native bool:FF2_HasAbility(client, const String:pluginName[], const String:abilityName[]);

/**
 * Determines how the Boss should use a certain ability
 *
 * @param client		Boss's index
 * @param pluginName	Name of plugin with this ability
 * @param abilityName 	Name of ability
 * @param slot			Slot of charge meter
 *							0 - rage
 *							1 - as usual, used for brave jump or teleport
 *							2 - other charged abilities
 * @param buttonMode	How to activate the ability
 *							0 - by taunt
 *							1 - by right mouse button or duck
 *							2 - by reload button
 * @noreturn
 */
native FF2_DoAbility(client, const String:pluginName[], const String:abilityName[], slot, buttonMode=0);

/**
 * Gets integer argument of ability
 *
 * @param client		Boss's index
 * @param pluginName	Name of plugin with this ability
 * @param abilityName 	Name of ability
 * @param argument 		Number of argument
 * @param defValue 		Returns if argument is not defined
 * @return				Value of argument
 */
native FF2_GetAbilityArgument(client, const String:pluginName[], const String:abilityName[], argument, defValue=0);

/**
 * Gets float argument of ability
 *
 * @param client		Boss's index
 * @param pluginName	Name of plugin with this ability
 * @param abilityName 	Name of ability
 * @param argument 		Number of argument
 * @param defValue 		Returns if argument is not defined
 * @return				Value of argument
 */
native Float:FF2_GetAbilityArgumentFloat(client, const String:plugin_name[], const String:ability_name[], argument, Float:defValue=0.0);

/**
 * Gets string argument of ability
 *
 * @param client 		Boss's index
 * @param pluginName	Name of plugin with this ability
 * @param abilityName 	Name of ability
 * @param argument 		Number of argument
 * @param buffer 		Buffer for value of argument
 * @param bufferLength	Length of buffer string
 * @noreturn
 */
native FF2_GetAbilityArgumentString(client, const String:pluginName[], const String:abilityName[], argument, String:buffer[], bufferLength);

/**
 * Starts a random Boss sound from its config file
 *
 * @param keyvalue		Name of sound container
 * @param buffer		Buffer for result sound path
 * @param bufferLength	Length of buffer
 * @param client		Boss's index
 * @param slot			Only for "sound_ability" - slot of ability
 * @return				True if sound has been found, false otherwise
 */
native bool:FF2_RandomSound(const String:keyvalue[], String:buffer[], bufferLength, client=0, slot=0);

/**
 * Stops boss's music for all players
 *
 * @param client	Client's index.  0 is for all clients.
 * @noreturn
 */
native FF2_StopMusic(client=0);

/**
 * Gets keyvalues handle of Boss
 *
 * @param client			Boss's index
 * @param specialIndex		0 - "client" parameter means the index of the boss
 *							1 - "client" parameter means number of the boss in characters.cfg-1
 * @return					Handle of Boss's keyvalues
 */
native Handle:FF2_GetSpecialKV(client, specialIndex=0);

/**
 * Gets client's flags for FF2
 *
 * @param client	Client's index
 * @return			Client's FF2 flags
 */
native FF2_GetFF2flags(client);

/**
 * Sets client's flags for FF2
 *
 * @param client	Client's index
 * @param flags		New flag values
 * @noreturn
 */
native FF2_SetFF2flags(client, flags);

/**
 * Gets client's queue points
 *
 * @param client	Client's index
 * @return			Client's queue points
 */
native FF2_GetQueuePoints(client);

/**
 * Sets client's queue points
 *
 * @param client	Client's index
 * @param value		New value of client's queue points
 * @noreturn
 */
native FF2_SetQueuePoints(client, value);

/**
 * Gets client's glow timer
 *
 * @param client	Client's index
 * @return			Number of seconds left until client glow disappears (-1 if invalid client)
 */
native Float:FF2_GetClientGlow(client);

/**
 * Sets client's glow timer
 *
 * @param client	Client's index
 * @param time1		Number of seconds to add to the glow timer (can be negative)
 * @param time2		New value of glow timer
 * @noreturn
 */
native FF2_SetClientGlow(client, Float:time1, Float:time2=-1.0);

/**
 * Retrieves the number of alive players left (not including bosses)
 *
 * @return			Number of non-boss players left alive
 */
native FF2_GetAlivePlayers();

/**
 * Retrieves the number of boss players left (including minions)
 *
 * @return          Number of boss players left alive
 */
native FF2_GetBossPlayers();

/**
 * Returns whether or not debug is enabled
 * @return			True if enabled, false otherwise
 */
native bool:FF2_Debug();

/**
 * FF2_OnAbility:
 * Begins when Boss uses ability (Rage, jump, teleport, etc)
 * Calls every 0.2 seconds for charge abilities
 *
 * Use FF2_PreAbility with enabled=false ONLY to prevent FF2_OnAbility!
 *
 * @param client 		Boss's index
 * @param pluginName	Name of plugin with this ability
 * @param abilityName 	Name of ability
 * @param slot 			Slot of ability
 *							0 - Rage
 *							1 - Jump/teleport
 *							2 - Other charge
 * @param status		Status of ability (for slots 1 and 2)
 *							0 - Not in use
 *							1 - Charging
 *							2 - Charged
 *							3 - In use
 * @return				Plugin_Stop can not prevent the ability. Use FF2_PreAbility with enabled=false
 */
forward FF2_PreAbility(client, const String:pluginName[], const String:abilityName[], slot, status, &enabled=true);
forward Action:FF2_OnAbility(client, const String:pluginName[], const String:abilityName[], slot, status);

/**
 * Begins when Boss gets hurt by environmental damage
 *
 * @param client 		Boss's index
 * @param triggerHurt	Entity index of "trigger_hurt"
 * @param damage 		Damage by "trigger_hurt".  Cutomizable.
 * @return				Plugin_Stop will prevent forward, Plugin_Changed will change damage.
 */
forward Action:FF2_OnTriggerHurt(index, triggerHurt, &Float:damage);

/**
 * Begins when Boss's music begins
 *
 * @param path 			Path to music sound file
 * @param time			Length of music
 * @return				Plugin_Stop will prevent music, Plugin_Changed will change it.
 */
forward Action:FF2_OnMusic(String:path[], &Float:time);


/**
 * Begins when FF2 picks Special for Boss
 *
 * @param client		Boss's index
 * @param specialNum	Number of boss
 * @param specialName	Name of boss
 * @return				You can NOT use Plugin_Stop to prevent this, but you can change specialName and use Plugin_Changed to change the boss.  If you want to change specialNum, then make SpecialName null.
 */
forward Action:FF2_OnSpecialSelected(index, &specialNum, String:specialName[]);

/**
 * Begins when FF2 adds queue points
 *
 * @param	add_points[MAXPLAYERS+1]
 *				Use array to get and/or change additional points.
 * @return	Plugin_Stop will prevent this, Plugin_Changed will change it.
 */
forward Action:FF2_OnAddQueuePoints(add_points[MAXPLAYERS+1]);

/**
 * Begins when FF2 picks a character set for the map
 *
 * @param charSetNum	Number of boss
 * @param charSetName	Name of boss
 * @return				You can NOT use Plugin_Stop to prevent this, but you can change CharSetName and use Plugin_Changed to change the character set.  If you want to change charSetNum, then make charSetName null.
 */
forward Action:FF2_OnLoadCharacterSet(&charSetNum, String:charSetName[]);

/**
 * Begins when a Boss loses a life
 *
 * @param client	Boss's index
 * @param lives		Number of lives left
 * @param maxLives	Max number of lives
 * @return			Plugin_Stop or Plugin_Handled to prevent damage that would remove a life, Plugin_Changed if you want to change the number of lives left.
*/
forward Action:FF2_OnLoseLife(client, &lives, maxLives);

/**
 * Used to consolidate debug messages
 *
 * @param buffer	Debug string to display
 * @param any:...	Formatting rules
 * @noreturn
 */
stock Debug(String:buffer[], any:...)
{
	if(FF2_Debug())
	{
		decl String:message[192];
		VFormat(message, sizeof(message), buffer, 2);
		CPrintToChatAll("{olive}[FF2 {darkorange}DEBUG{olive}]{default} %s", message);
		PrintToServer("[FF2 DEBUG] %s", message);
	}
}

// These exist for compatibility reasons (<1.10.1)
#pragma deprecated Use TF2_RemoveWeaponSlot
stock TF2_RemoveWeaponSlot2(client, slot)
{
	TF2_RemoveWeaponSlot(client, slot);
}

#pragma deprecated Use TF2_RemoveAllWeapons
stock TF2_RemoveAllWeapons2(client)
{
	for(new slot=0; slot<=5; slot++)
	{
		TF2_RemoveWeaponSlot(client, slot);
	}
}

public SharedPlugin:__pl_FF2=
{
	name="freak_fortress_2",
	file="freak_fortress_2.smx",
	#if defined REQUIRE_PLUGIN
		required=1,
	#else
		required=0,
	#endif
};

#if !defined REQUIRE_PLUGIN
public __pl_FF2_SetNTVOptional()
{
	MarkNativeAsOptional("FF2_IsFF2Enabled");
	MarkNativeAsOptional("FF2_GetBossUserId");
	MarkNativeAsOptional("FF2_GetBossIndex");
	MarkNativeAsOptional("FF2_GetBossTeam");
	MarkNativeAsOptional("FF2_GetBossSpecial");
	MarkNativeAsOptional("FF2_GetBossHealth");
	MarkNativeAsOptional("FF2_SetBossHealth");
	MarkNativeAsOptional("FF2_GetBossMaxHealth");
	MarkNativeAsOptional("FF2_SetBossMaxHealth");
	MarkNativeAsOptional("FF2_GetBossLives");
	MarkNativeAsOptional("FF2_SetBossLives");
	MarkNativeAsOptional("FF2_GetBossMaxLives");
	MarkNativeAsOptional("FF2_SetBossMaxLives");
	MarkNativeAsOptional("FF2_GetBossCharge");
	MarkNativeAsOptional("FF2_SetBossCharge");
	MarkNativeAsOptional("FF2_GetClientDamage");
	MarkNativeAsOptional("FF2_GetRoundState");
	MarkNativeAsOptional("FF2_GetRageDist");
	MarkNativeAsOptional("FF2_HasAbility");
	MarkNativeAsOptional("FF2_GetAbilityArgument");
	MarkNativeAsOptional("FF2_GetAbilityArgumentFloat");
	MarkNativeAsOptional("FF2_GetAbilityArgumentString");
	MarkNativeAsOptional("FF2_RandomSound");
	MarkNativeAsOptional("FF2_StopMusic");
	MarkNativeAsOptional("FF2_GetSpecialKV");
	MarkNativeAsOptional("FF2_GetQueuePoints");
	MarkNativeAsOptional("FF2_SetQueuePoints");
	MarkNativeAsOptional("FF2_GetFF2flags");
	MarkNativeAsOptional("FF2_SetFF2flags");
	MarkNativeAsOptional("FF2_DoAbility");
    MarkNativeAsOptional("FF2_GetClientGlow");
    MarkNativeAsOptional("FF2_SetClientGlow");
    MarkNativeAsOptional("FF2_GetAlivePlayers");
    MarkNativeAsOptional("FF2_GetBossPlayers");
}
#endif
