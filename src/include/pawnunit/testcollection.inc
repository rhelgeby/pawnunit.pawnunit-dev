/*
 * ============================================================================
 *
 *  PawnUnit
 *
 *  File:          testcollection.inc
 *  Type:          Include
 *  Description:   PawnUnit test collection data structure manager.
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

#if defined _pawnunit_testcollection_included
 #endinput
#endif
#define _pawnunit_testcollection_included

/**
 * Test collection reference tag.
 */
enum TestCollection
{
    INVALID_TEST_COLLECTION = -1;
}

/**
 * Defines the test collection data elements.
 *
 * Note: Do not modify the order of these elements. They are used to set data
 *       pack positions.
 */
enum TestCollectionData
{
    TestCollection_TestCases,   /** Array of test case references. */
    TestCollection_Before,      /** Function to execute before test case. */
    TestCollection_After,       /** Function to execute after test case. */
    TestCollection_Name,        /** Display name of test collection. */
}

/**
 * Creates a test collection.
 *
 * Note: The TestCollection reference must be deleted with
 *       PawnUnit_DeleteTestCollection when no longer in use.
 *
 * @param name          Name of test collection.
 * @param testCases     Optional. Array of test case references. Default is an
 *                      empty array.
 * @param before        Optional. Function to execute before every test case.
 * @param after         Optional. Function to execute after every test case.
 *
 * @return              Reference to the test collection data structure.
 */
stock TestCollection:PawnUnit_CreateTestCase(const String:name[],
        Handle:testCases = INVALID_HANDLE,
        Function:before = INVALID_FUNCTION,
        Function:after = INVALID_FUNCTION)
{
    new Handle:testCollection = CreateDataPack();
    
    // Create empty test case array if not specified.
    if (testCases == INVALID_HANDLE)
    {
        testCases = CreateArray();
    }
    
    // Write test collection data.
    WritePackCell(testCollection, _:phases);    // TestCollection_TestCases
    WritePackCell(testCollection, _:before);    // TestCollection_Before
    WritePackCell(testCollection, _:after);     // TestCollection_After
    WritePackString(testCollection, name);      // TestCollection_Name
    
    // Reset cursor.
    SetPackPosition(testCollection, 0);
    
    return TestCollection:testCollection;
}

/**
 * Deletes a test collection.
 *
 * @param testCollection    Test collection reference.
 * @param recursive         Whether to delete the test cases in the collection.
 *                          Warning: Not doing a recursive deletion may cause a
 *                          memory leak if its test cases aren't deleted
 *                          individually too.
 * @param resetReference    Optional. Reset testCollection to
 *                          INVALID_TEST_COLLECTION when deleted. Default is
 *                          true.
 */
stock Handle:PawnUnit_DeleteTestCollection(TestCase:&testCollection,
        bool:recursive = true,
        bool:resetReference = true)
{
    PawnUnit_ValidateTestCollection(testCollection);
    
    SetPackPosition(testCollection, _:TestCollection_TestCases);
    new Handle:testCases = Handle:ReadPackCell(testCollection);
    
    if (recursive)
    {
        new len = GetArraySize(testCases);
        for (new i = 0; i < len; i++)
        {
            TestCase:testCase = GetArrayCell(i);
            PawnUnit_DeleteTestCase(testCase);
        }
    }
    
    CloseHandle(testCases);
    CloseHandle(testCollection);
    
    if (resetReference)
    {
        testCollection = INVALID_TEST_COLLECTION;
    }
}

/**
 * Gets the test case array.
 *
 * @param testCollection    Test collection reference.
 *
 * @return          Handle to array.
 */
stock Handle:PawnUnit_GetTestCases(TestCollection:testCollection)
{
    PawnUnit_ValidateTestCollection(testCollection);
    
    SetPackPosition(testCollection, _:TestCollection_TestCases);
    return Handle:ReadPackCell(Handle:testCollection);
}

/**
 * Adds a test case to a test collection.
 *
 * @param testCollection    Test collection reference.
 * @param testCase          Test case to add.
 */
stock PawnUnit_AddTestCase(TestCollection:testCollection, TestCase:testCase)
{
    PawnUnit_ValidateTestCollection(testCollection);
    PawnUnit_ValidateTestCase(testCase);
    
    Handle:testCases = PawnUnit_GetTestPhases(testCollection);
    PushArrayCell(testCases, testCase);
}

/**
 * Gets the function reference for the function to execute before every test
 * case.
 *
 * @param testCollection    Test collection reference.
 *
 * @return                  Function reference or INVALID_FUNCTION if none
 *                          specified.
 */
stock Function:PawnUnit_GetBefore(TestCollection:testCollection)
{
    PawnUnit_ValidateTestCollection(testCollection);
    
    SetPackPosition(testCollection, _:TestCollection_Before);
    return Function:ReadPackCell(Handle:testCollection);
}

/**
 * Sets the function reference for the function to execute before every test
 * case.
 *
 * @param testCollection    Test collection reference.
 * @param before            New function to execute before every test case.
 *
 * @return                  Function reference or INVALID_FUNCTION if none
 *                          specified.
 */
stock PawnUnit_SetBefore(TestCollection:testCollection, Function:before)
{
    PawnUnit_ValidateTestCollection(testCollection);
    
    SetPackPosition(testCollection, _:TestCollection_Before);
    WritePackCell(Handle:testCollection, _:before);
}

/**
 * Gets the function reference for the function to execute after every test
 * case.
 *
 * @param testCollection    Test collection reference.
 *
 * @return                  Function reference or INVALID_FUNCTION if none
 *                          specified.
 */
stock Function:PawnUnit_GetAfter(TestCollection:testCollection)
{
    PawnUnit_ValidateTestCollection(testCollection);
    
    SetPackPosition(testCollection, _:TestCollection_After);
    return Function:ReadPackCell(Handle:testCollection);
}

/**
 * Sets the function reference for the function to execute after every test
 * case.
 *
 * @param testCollection    Test collection reference.
 * @param after             New function to execute after every test case.
 *
 * @return                  Function reference or INVALID_FUNCTION if none
 *                          specified.
 */
stock PawnUnit_SetAfter(TestCollection:testCollection, Function:after)
{
    PawnUnit_ValidateTestCollection(testCollection);
    
    SetPackPosition(testCollection, _:TestCollection_After);
    WritePackCell(Handle:testCollection, _:after);
}

/**
 * Gets the test collection name.
 *
 * @param testCollection    Test collection reference.
 * @param buffer            Destination string buffer.
 * @param maxlen            Size of buffer.
 */
stock PawnUnit_GetTestCollectionName(TestCollection:testCollection, String:buffer[], maxlen)
{
    PawnUnit_ValidateTestCollection(testCollection);
    
    SetPackPosition(testCollection, _:TestCollection_Name);
    ReadPackString(Handle:testCollection, buffer, maxlen);
}

/**
 * Sets the test collection name.
 *
 * @param testCollection    Test collection reference.
 * @param name          New name to set.
 */
stock PawnUnit_SetTestCollectionName(TestCollection:testCollection, const String:name[])
{
    PawnUnit_ValidateTestCollection(testCollection);
    
    SetPackPosition(testCollection, _:TestCollection_Name);
    WritePackString(Handle:testCollection, name);
}


/****************************
 *   Validation functions   *
 ****************************/

/**
 * Returns whether the test collection reference is valid.
 *
 * @param testCollection    Test collection reference to validate.
 *
 * @return                  True if valid, false otherwise.
 */
stock bool:PawnUnit_IsValidTestCollection(TestCollection:testCollection)
{
    return testCollection != INVALID_TEST_COLLECTION;
}

/**
 * Throws an error if the test collection is invalid.
 *
 * @param testCollection    Test collection reference to validate.
 */
stock PawnUnit_ValidateTestCase(TestCollection:testCollection)
{
    if (!PawnUnit_IsValidTestCollection(testCollection))
    {
        ThrowError("Invalid test collection.");
    }
}
