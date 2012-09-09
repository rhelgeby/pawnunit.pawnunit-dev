/*
 * ============================================================================
 *
 *  PawnUnit Demo
 *
 *  File:          pawnunitdemo.sp
 *  Type:          Main
 *  Description:   Example usage of PawnUnit.
 *
 *  Copyright (C) 2012  Richard Helgeby
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * ============================================================================
 */

// Comment out to not require semicolons at the end of each line of code.
#pragma semicolon 1

#include <sourcemod>
#include <pawnunit>

#define PLUGIN_VERSION "1.0.0-dev"

/**
 * Record plugin info.
 */
public Plugin:myinfo =
{
    name = "PawnUnit Demo",
    author = "Richard Helgeby",
    description = "Example usage of PawnUnit.",
    version = PLUGIN_VERSION,
    url = "http://www.helgeby.net"
};

/**
 * Plugin is loading.
 */
public OnPluginStart()
{
    // Print message in server console.
    PrintToServer("Hello world!");
}
