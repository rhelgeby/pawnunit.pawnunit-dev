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

new TestCollection:ExampleCollection = INVALID_TEST_COLLECTION;

/**
 * Plugin is loading.
 */
public OnPluginStart()
{
    InitTestCases();
    RunTests();
}

/**
 * Plugin is unloading.
 */
public OnPluginEnd()
{
    // Delete collection and test cases. Not really necessary in this example
    // plugin since they're only created once anyways.
    PawnUnit_DeleteTestCollection(ExampleCollection);
}

RunTests()
{
    PawnUnit_Run(ExampleCollection);
}

/******************
 *   Test cases   *
 ******************/

InitTestCases()
{
    ExampleCollection = PawnUnit_CreateTestCollection("Example tests");
    
    new TestCase:phaseTest = PawnUnit_CreateTestCase("Should pass 5 phases");
    PawnUnit_AddTestPhase(phaseTest, ShouldPass);
    PawnUnit_AddTestPhase(phaseTest, ShouldPass);
    PawnUnit_AddTestPhase(phaseTest, ShouldPass);
    PawnUnit_AddTestPhase(phaseTest, ShouldPass);
    PawnUnit_AddTestPhase(phaseTest, ShouldPass);
    
    new TestCase:phaseTestFail = PawnUnit_CreateTestCase("Should fail on third phase");
    PawnUnit_AddTestPhase(phaseTestFail, ShouldPass);
    PawnUnit_AddTestPhase(phaseTestFail, ShouldPass);
    PawnUnit_AddTestPhase(phaseTestFail, ShouldFail);
    PawnUnit_AddTestPhase(phaseTestFail, ShouldPass);
    PawnUnit_AddTestPhase(phaseTestFail, ShouldPass);
    
    new TestCase:floatEqPassMargin = PawnUnit_CreateTestCase("FloatEquals passing with margin");
    PawnUnit_AddTestPhase(floatEqPassMargin, FloatEqPassMargin);
    new TestCase:floatEqFailMargin = PawnUnit_CreateTestCase("FloatEquals failing with margin");
    PawnUnit_AddTestPhase(floatEqFailMargin, FloatEqFailMargin);
    
    new TestCase:shouldPass = PawnUnit_CreateTestCase("Should pass");
    PawnUnit_AddTestPhase(shouldPass, ShouldPass);
    
    new TestCase:shouldFail = PawnUnit_CreateTestCase("Should fail");
    PawnUnit_AddTestPhase(shouldFail, ShouldFail);
    
    new TestCase:cellEqFail = PawnUnit_CreateTestCase("CellEquals failing");
    PawnUnit_AddTestPhase(cellEqFail, CellEqFail);
    new TestCase:cellEqPass = PawnUnit_CreateTestCase("CellEquals passing");
    PawnUnit_AddTestPhase(cellEqPass, CellEqPass);
    
    new TestCase:floatEqFail = PawnUnit_CreateTestCase("FloatEquals failing");
    PawnUnit_AddTestPhase(floatEqFail, FloatEqFail);
    new TestCase:floatEqPass = PawnUnit_CreateTestCase("FloatEquals passing");
    PawnUnit_AddTestPhase(floatEqPass, FloatEqPass);
    
    PawnUnit_AddTestCase(ExampleCollection, shouldPass);
    PawnUnit_AddTestCase(ExampleCollection, shouldFail);
    PawnUnit_AddTestCase(ExampleCollection, cellEqFail);
    PawnUnit_AddTestCase(ExampleCollection, cellEqPass);
    PawnUnit_AddTestCase(ExampleCollection, floatEqFail);
    PawnUnit_AddTestCase(ExampleCollection, floatEqPass);
    PawnUnit_AddTestCase(ExampleCollection, floatEqPassMargin);
    PawnUnit_AddTestCase(ExampleCollection, floatEqFailMargin);
    PawnUnit_AddTestCase(ExampleCollection, phaseTest);
    PawnUnit_AddTestCase(ExampleCollection, phaseTestFail);
}

public TestControlAction:ShouldPass(TestCase:testCase)
{
    return Test_Continue;
}

public TestControlAction:ShouldFail(TestCase:testCase)
{
    FailTest("Failed on purpose.");
}

public TestControlAction:CellEqFail(TestCase:testCase)
{
    Assert(CellEquals(1, 2, "Failing on purpose."));
    return Test_Continue;
}

public TestControlAction:CellEqPass(TestCase:testCase)
{
    Assert(CellEquals(1, 1));
    return Test_Continue;
}

public TestControlAction:FloatEqFail(TestCase:testCase)
{
    Assert(FloatEquals(1.0, 2.0, _, "Failing on purpose."));
    return Test_Continue;
}

public TestControlAction:FloatEqPass(TestCase:testCase)
{
    Assert(FloatEquals(1.0, 1.0));
    return Test_Continue;
}

public TestControlAction:FloatEqPassMargin(TestCase:testCase)
{
    Assert(FloatEquals(1.0, 1.01, 0.1));
    return Test_Continue;
}

public TestControlAction:FloatEqFailMargin(TestCase:testCase)
{
    Assert(FloatEquals(1.0, 1.01, 0.001));
    return Test_Continue;
}
