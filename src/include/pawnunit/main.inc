/*
 * ============================================================================
 *
 *  PawnUnit
 *
 *  File:          main.inc
 *  Type:          Include
 *  Description:   PawnUnit testing API.
 *  Notes:         Main components of the testing API. See also testcase.inc
 *                 and testcollection.inc.
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

#if defined _pawnunit_main_included
 #endinput
#endif
#define _pawnunit_main_included

#define NAME_LEN 64

/**
 * Called when a test phase is executed.
 *
 * @param testEngine    Reference to the main test engine.
 */
functag public PawnUnitTestPhase(TestEngine:testEngine);
