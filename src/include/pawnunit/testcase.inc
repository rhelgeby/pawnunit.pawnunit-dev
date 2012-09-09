/*
 * ============================================================================
 *
 *  PawnUnit
 *
 *  File:          testcase.inc
 *  Type:          Include
 *  Description:   PawnUnit test case data structure manager.
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

#if defined _pawnunit_testcase_included
 #endinput
#endif
#define _pawnunit_testcase_included

enum TestCase
{
    INVALID_TEST_CASE = -1;
}

/**
 * Defines the test case data elements.
 *
 * Note: Do not modify the order of these elements. They are used to set data
 *       pack positions.
 */
enum TestCaseData
{
    TestCase_Phases,    /** Array of function handles. */
    TestCase_Passed,    /** Specifies whether the test passed or not. */
    TestCase_Name,      /** Display name of test case. */
}

/**
 * Creates a test case.
 *
 * Note: The TestCase reference must be deleted with PawnUnit_DeleteTestCase
 *       when no longer in use.
 *
 * @param name      Name of test case.
 * @param phases    Optional. Array of function handles. Default is an empty
 *                  array.
 *
 * @return          Reference to the test case data structure.
 */
stock TestCase:PawnUnit_CreateTestCase(const String:name[], Handle:phases = INVALID_HANDLE)
{
    new Handle:testCase = CreateDataPack();
    
    // Create empty phase array if not specified.
    if (phases == INVALID_HANDLE)
    {
        phases = CreateArray();
    }
    
    // Write test case data.
    WritePackCell(testCase, phases);    // TestCase_Phases
    WritePackCell(testCase, 0);         // TestCase_Passed
    WritePackString(testCase, name);    // TestCase_Name
    
    // Reset cursor.
    SetPackPosition(testCase, 0);
    
    return TestCase:testCase;
}

/**
 * Deletes a test case.
 *
 * @param testCase          Test case reference.
 * @param resetReference    Optional. Reset testCase to INVALID_TEST_CASE when
 *                          deleted. Default is true.
 */
stock Handle:PawnUnit_DeleteTestCase(TestCase:&testCase, bool:resetReference = true)
{
    PawnUnit_ValidateTestCase(testCase);
    
    SetPackPosition(testCase, _:TestCase_Phases);
    
    // Delete test phase array.
    CloseHandle(Handle:ReadPackCell(testCase));
    
    CloseHandle(testCase);
    
    if (resetReference)
    {
        testCase = INVALID_TEST_CASE;
    }
}

/**
 * Gets the test phase function array.
 *
 * @param testCase  Test case reference.
 *
 * @return          Handle to array.
 */
stock Handle:PawnUnit_GetTestPhases(TestCase:testCase)
{
    PawnUnit_ValidateTestCase(testCase);
    
    SetPackPosition(testCase, _:TestCase_Phases);
    return Handle:ReadPackCell(Handle:testCase);
}

/**
 * Adds a test phase function to a test case.
 *
 * @param testCase      Test case reference.
 * @param phase         Function to execute in this phase.
 */
stock PawnUnit_AddTestPhase(TestCase:testCase, PawnUnitTestPhase:phase)
{
    PawnUnit_ValidateTestCase(testCase);
    PawnUnit_ValidateTestCase(phase);
    
    Handle:phases = PawnUnit_GetTestPhases(testCase);
    PushArrayCell(phases, _:phase);
}

/**
 * Gets the test case name.
 *
 * @param testCase      Test case reference.
 * @param buffer        Destination string buffer.
 * @param maxlen        Size of buffer.
 */
stock PawnUnit_GetTestCaseName(TestCase:testCase, String:buffer[], maxlen)
{
    PawnUnit_ValidateTestCase(testCase);
    
    SetPackPosition(testCase, _:TestCase_Name);
    ReadPackString(Handle:testCase, buffer, maxlen);
}

/**
 * Sets the test case name.
 *
 * @param testCase      Test case reference.
 * @param name          New name to set.
 */
stock PawnUnit_SetTestCaseName(TestCase:testCase, const String:name[])
{
    PawnUnit_ValidateTestCase(testCase);
    
    SetPackPosition(testCase, _:TestCase_Name);
    WritePackString(Handle:testCase, name);
}

/**
 * Gets whether a test case passed the test.
 *
 * Note: Only valid after testing is done.
 *
 * @param testCase      Test case reference.
 *
 * @return              True if passed, false otherwise.
 */
stock bool:PawnUnit_GetTestPassed(TestCase:testCase)
{
    PawnUnit_ValidateTestCase(testCase);
    
    SetPackPosition(testCase, _:TestCase_Passed);
    return bool:ReadPackCell(Handle:testCase);
}

/**
 * Sets whether a test case passed the test.
 *
 * @param testCase      Test case reference.
 * @param passed        Passed state.
 */
stock bool:PawnUnit_SetTestPassed(TestCase:testCase, bool:passed)
{
    PawnUnit_ValidateTestCase(testCase);
    
    SetPackPosition(testCase, _:TestCase_Passed);
    WritePackCell(Handle:testCase, passed);
}


/****************************
 *   Validation functions   *
 ****************************/

/**
 * Returns whether the test case reference is valid.
 *
 * @param testCase      Test case reference to validate.
 *
 * @return              True if valid, false otherwise.
 */
stock bool:PawnUnit_IsValidTestCase(TestCase:testCase)
{
    return testCase != INVALID_TEST_CASE;
}

/**
 * Throws an error if the test case is invalid.
 *
 * @param testCase      Test case reference to validate.
 */
stock PawnUnit_ValidateTestCase(TestCase:testCase)
{
    if (!PawnUnit_IsValidTestCase(testCase))
    {
        ThrowError("Invalid test case.");
    }
}

/**
 * Returns whether the test phase function is valid.
 *
 * @param phase         Test phase function to validate.
 *
 * @return              True if valid, false otherwise.
 */
stock bool:PawnUnit_IsValidPhase(Function:phase)
{
    return phase != INVALID_FUNCTION;
}

/**
 * Throws an error if the test phase is invalid.
 *
 * @param phase         Test phase to validate.
 */
stock PawnUnit_ValidateTestCase(Function:phase)
{
    if (!PawnUnit_IsValidPhase(phase))
    {
        ThrowError("Invalid test phase function reference.");
    }
}
