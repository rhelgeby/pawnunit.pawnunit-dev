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
new bool:SuspendTested = false;


/**
 * Plugin is loading.
 */
public OnPluginStart()
{
    InitTestCases();
    RunTests();
    PawnUnit_PrintResults(ExampleCollection);
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

/**
 * Returns whether a number is a prime number.
 *
 * Source: http://stackoverflow.com/questions/1538644/c-determine-if-a-number-is-prime
 *
 * @param number    Number to test.
 *
 * @return          True if prime, false otherwise.
 */
bool:IsPrime(number)
{
    if (number <= 1)
    {
        return false;
    }
    
    for (new i = 2; i < number; i++)
    {
        if (number % i == 0 && i != number)
        {
            return false;
        }
    }
    
    return true;
}

/******************
 *   Test cases   *
 ******************/

InitTestCases()
{
    // Tests cases should be added to a collection. Collections can be used for
    // organizing test code or grouping test cases that need certain stuff to
    // be done before and after each test.
    ExampleCollection = PawnUnit_CreateTestCollection("Example tests");
    
    // Create a test case.
    new TestCase:primeTest = PawnUnit_CreateTestCase("Prime number test");
    
    // Add a test phase to it (callback for the actual test code).
    PawnUnit_AddTestPhase(primeTest, PrimeTest);
    
    // A test case supports multiple phases. They are executed sequentially in
    // the order they're added.
    new TestCase:phaseTest = PawnUnit_CreateTestCase("Should pass 5 phases");
    PawnUnit_AddTestPhase(phaseTest, ShouldPass);
    PawnUnit_AddTestPhase(phaseTest, ShouldPass);
    PawnUnit_AddTestPhase(phaseTest, ShouldPass);
    PawnUnit_AddTestPhase(phaseTest, ShouldPass);
    PawnUnit_AddTestPhase(phaseTest, ShouldPass);
    
    // If one phase fails, execution is stopped and the test case fails.
    new TestCase:phaseTestFail = PawnUnit_CreateTestCase("Should fail on third phase");
    PawnUnit_AddTestPhase(phaseTestFail, ShouldPass);
    PawnUnit_AddTestPhase(phaseTestFail, ShouldPass);
    PawnUnit_AddTestPhase(phaseTestFail, ShouldFail);
    PawnUnit_AddTestPhase(phaseTestFail, ShouldPass);
    PawnUnit_AddTestPhase(phaseTestFail, ShouldPass);
    
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
    
    new TestCase:floatEqPassMargin = PawnUnit_CreateTestCase("FloatEquals passing with margin");
    PawnUnit_AddTestPhase(floatEqPassMargin, FloatEqPassMargin);
    new TestCase:floatEqFailMargin = PawnUnit_CreateTestCase("FloatEquals failing with margin");
    PawnUnit_AddTestPhase(floatEqFailMargin, FloatEqFailMargin);
    
    new TestCase:suspendTest = PawnUnit_CreateTestCase("Suspending for 2 seconds");
    PawnUnit_AddTestPhase(suspendTest, SuspendTest);
    PawnUnit_AddTestPhase(suspendTest, SuspendTestResume);
    
    // Add test cases to the collection.
    PawnUnit_AddTestCase(ExampleCollection, primeTest);
    PawnUnit_AddTestCase(ExampleCollection, phaseTest);
    PawnUnit_AddTestCase(ExampleCollection, phaseTestFail);
    PawnUnit_AddTestCase(ExampleCollection, shouldPass);
    PawnUnit_AddTestCase(ExampleCollection, shouldFail);
    PawnUnit_AddTestCase(ExampleCollection, cellEqFail);
    PawnUnit_AddTestCase(ExampleCollection, cellEqPass);
    PawnUnit_AddTestCase(ExampleCollection, floatEqFail);
    PawnUnit_AddTestCase(ExampleCollection, floatEqPass);
    PawnUnit_AddTestCase(ExampleCollection, floatEqPassMargin);
    PawnUnit_AddTestCase(ExampleCollection, floatEqFailMargin);
    PawnUnit_AddTestCase(ExampleCollection, suspendTest);
}

public TestControlAction:PrimeTest(TestCase:testCase)
{
    Assert(False(IsPrime(-1)));
    Assert(False(IsPrime(0)));
    Assert(False(IsPrime(1)));

    Assert(True(IsPrime(2)));
    Assert(True(IsPrime(3)));
    Assert(False(IsPrime(4)));
    Assert(True(IsPrime(5)));
    Assert(False(IsPrime(6)));
    Assert(True(IsPrime(7)));
    Assert(False(IsPrime(8)));
    Assert(False(IsPrime(9)));
    Assert(False(IsPrime(10)));
    Assert(True(IsPrime(11)));
    Assert(False(IsPrime(12)));
    Assert(True(IsPrime(13)));
    Assert(False(IsPrime(14)));
    Assert(False(IsPrime(15)));
    Assert(False(IsPrime(16)));
    Assert(False(IsPrime(17)));
    Assert(True(IsPrime(17)));

    return Test_Continue;
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
    Assert(CellEquals(1, 2));
    return Test_Continue;
}

public TestControlAction:CellEqPass(TestCase:testCase)
{
    Assert(CellEquals(1, 1));
    return Test_Continue;
}

public TestControlAction:FloatEqFail(TestCase:testCase)
{
    Assert(FloatEquals(1.0, 2.0));
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

public TestControlAction:SuspendTest(TestCase:testCase)
{
    // Only test suspend once. We don't want a infinite loop.
    if (!SuspendTested)
    {
        // Create timer for resuming test.
        CreateTimer(2.0, SuspendTimer);

        // Suspend test engine.
        return Test_Suspend;
    }
    
    return Test_Continue;
}

public Action:SuspendTimer(Handle:timer)
{
    // Timer tick. Resume testing. It should continue where it left.
    SuspendTested = true;
    RunTests();
}

public TestControlAction:SuspendTestResume(TestCase:testCase)
{
    return Test_Continue;
}

