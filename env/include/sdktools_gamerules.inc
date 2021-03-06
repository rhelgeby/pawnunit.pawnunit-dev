/**
 * vim: set ts=4 :
 * =============================================================================
 * SourceMod (C)2004-2011 AlliedModders LLC.  All rights reserved.
 * =============================================================================
 *
 * This file is part of the SourceMod/SourcePawn SDK.
 *
 * This program is free software; you can redistribute it and/or modify it under
 * the terms of the GNU General Public License, version 3.0, as published by the
 * Free Software Foundation.
 * 
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * As a special exception, AlliedModders LLC gives you permission to link the
 * code of this program (as well as its derivative works) to "Half-Life 2," the
 * "Source Engine," the "SourcePawn JIT," and any Game MODs that run on software
 * by the Valve Corporation.  You must obey the GNU General Public License in
 * all respects for all other code used.  Additionally, AlliedModders LLC grants
 * this exception to all derivative works.  AlliedModders LLC defines further
 * exceptions, found in LICENSE.txt (as of this writing, version JULY-31-2007),
 * or <http://www.sourcemod.net/license.php>.
 *
 * Version: $Id$
 */

#if defined _sdktools_gamerules_included
  #endinput
#endif
#define _sdktools_gamerules_included

enum RoundState {
	// initialize the game, create teams
	RoundState_Init,
	
	//Before players have joined the game. Periodically checks to see if enough players are ready
	//to start a game. Also reverts to this when there are no active players
	RoundState_Pregame,
	
	//The game is about to start, wait a bit and spawn everyone
	RoundState_StartGame,
	
	//All players are respawned, frozen in place
	RoundState_Preround,
	
	//Round is on, playing normally
	RoundState_RoundRunning,
	
	//Someone has won the round
	RoundState_TeamWin,
	
	//Noone has won, manually restart the game, reset scores
	RoundState_Restart,
	
	//Noone has won, restart the game
	RoundState_Stalemate,
	
	//Game is over, showing the scoreboard etc
	RoundState_GameOver,
	
	//Game is over, doing bonus round stuff
	RoundState_Bonus,
};

/**
 * Retrieves an integer value from a property of the gamerules entity.
 * 
 * @param prop			Property name.
 * @param size			Number of bytes to read (valid values are 1, 2, or 4).
 *						This value is auto-detected, and the size parameter is 
 *						only used as a fallback in case detection fails.
 * @param element		Element # (starting from 0) if property is an array.
 * @return				Value at the given property offset.
 * @error				Not supported.
 */
native GameRules_GetProp(const String:prop[], size=4, element=0);

/**
 * Sets an integer value for a property of the gamerules entity.
 *
 * @param prop			Property name.
 * @param value			Value to set.
 * @param size			Number of bytes to write (valid values are 1, 2, or 4).
 *						This value is auto-detected, and the size parameter is 
 *						only used as a fallback in case detection fails.
 * @param element		Element # (starting from 0) if property is an array.
 * @error				Not supported.
 * @noreturn
 */
native GameRules_SetProp(const String:prop[], any:value, size=4, element=0, bool:changeState=false);

/**
 * Retrieves a float value from a property of the gamerules entity.
 * 
 * @param prop			Property name.
 * @param element		Element # (starting from 0) if property is an array.
 * @return				Value at the given property offset.
 * @error				Not supported.
 */
native Float:GameRules_GetPropFloat(const String:prop[], element=0);

/**
 * Sets a float value for a property of the gamerules entity.
 * 
 * @param prop			Property name.
 * @param value			Value to set.
 * @param element		Element # (starting from 0) if property is an array.
 * @noreturn
 * @error				Not supported.
 */
native GameRules_SetPropFloat(const String:prop[], Float:value, element=0, bool:changeState=false);

/**
 * Retrieves a entity index from a property of the gamerules entity.
 * 
 * @param prop			Property name.
 * @param element		Element # (starting from 0) if property is an array.
 * @return				Entity index at the given property.
 *						If there is no entity, or the entity is not valid, 
 *						then -1 is returned.
 * @error				Not supported.
 */
native GameRules_GetPropEnt(const String:prop[], element=0);

/**
 * Sets an entity index for a property of the gamerules entity.
 * 
 * @param prop			Property name.
 * @param other			Entity index to set, or -1 to unset.
 * @param element		Element # (starting from 0) if property is an array.
 * @noreturn
 * @error				Not supported.
 */
native GameRules_SetPropEnt(const String:prop[], other, element=0, bool:changeState=false);

/**
 * Retrieves a vector of floats from the gamerules entity, given a named network property.
 * 
 * @param prop			Property name.
 * @param vec			Vector buffer to store data in.
 * @param element		Element # (starting from 0) if property is an array.
 * @noreturn
 * @error				Not supported.
 */
native GameRules_GetPropVector(const String:prop[], Float:vec[3], element=0);

/**
 * Sets a vector of floats in the gamerules entity, given a named network property.
 *
 * @param prop			Property name.
 * @param vec			Vector to set.
 * @param element		Element # (starting from 0) if property is an array.
 * @noreturn
 * @error				Not supported.
 */
native GameRules_SetPropVector(const String:prop[], const Float:vec[3], element=0, bool:changeState=false);

/**
 * Gets a gamerules property as a string.
 * 
 * @param prop			Property to use.
 * @param buffer		Destination string buffer.
 * @param maxlen		Maximum length of output string buffer.
 * @return				Number of non-null bytes written.
 * @error				Not supported.
 */
native GameRules_GetPropString(const String:prop[], String:buffer[], maxlen);

/**
 * Sets a gamerules property as a string.
 *
 * @param prop			Property to use.
 * @param buffer		String to set.		
 * @return				Number of non-null bytes written.
 * @error				Not supported.
 */
native GameRules_SetPropString(const String:prop[], const String:buffer[], bool:changeState=false);

/**
 * Gets the current round state.
 *
 * @return				Round state.
 * @error				Game doesn't support round state.
 */
stock RoundState:GameRules_GetRoundState()
{
	return RoundState:GameRules_GetProp("m_iRoundState");
}
