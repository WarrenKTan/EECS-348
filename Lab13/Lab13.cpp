/*
Program Name: EECS 348 Lab 13
Description: Faults, Errors, and Failures in software testing
Inputs: None
Outputs: Actual output for various test cases defined by questions 2-5
Collaborators: 
Other Sources: 
Author: Warren Tan
Creation Date: 25/11/2025
*/

#include <iostream> // input and output
#include <vector> // hold attendance_records

// bring std functions into scope
using namespace std;

// check if 'attendance_records' has 3+ missed attendances
bool fail_lecture_erroneous(const vector<int>& attendance_records){
    // count of the amount of zeroes in 'attendance_records'
    int absent_count = 0;
    
    // check every* index in 'attendance_records'
    for (int i = 1; i < attendance_records.size(); ++i){
        // increment 'absent_count' upon reading an absence ('0')
        absent_count += attendance_records[i] == 0;
    }

    // return true 
    return absent_count >= 3;
}

// check if 'attendance_records' has 3+ missed attendances
bool fail_lecture(const vector<int>& attendance_records){
    // count of the amount of zeroes in 'attendance_records'
    int absent_count = 0;
    
    // check every* index in 'attendance_records'
    for (int i = 1; i < attendance_records.size(); ++i){
        // increment 'absent_count' upon reading an absence ('0')
        absent_count += attendance_records[i] == 0;
    }

    // return true 
    return absent_count >= 3;
}

int main(){
    // testcases
    vector<int> records;
    
    // 1. Is there a fault in the program? If so, locate it and explain
    // There is a fault in the indexing of the 'for' loop.
    // for (int i = 1; i < attendance_records.size(); ++i)
    // Indexing starts at '1', resulting in an unread value at index '0'.

    // 2. Define a test case that does not execute the fault:
    // It is imposible to avoid execution of the fault since the fault
    // occurs inside a loop that always executes given any valid input.

    // 3. Define a test case that executes the fault but does not result in an error state:
    // expected output: True
    // actual output: True
    records = {1, 0, 1, 1, 0, 1, 1, 1, 0, 1};
    cout << "Question 3:" << endl;
    cout << "expected output: " << fail_lecture(records) << endl;
    cout << "actual output: " << fail_lecture_erroneous(records) << endl;

    // 4. Define a test case that results in an error state but not a failure.
    // expected output: False
    // actual output: False
    records = {0, 1, 1, 1, 1, 1, 0, 1, 1, 1};
    cout << "Question 4:" << endl;
    cout << "expected output: " << fail_lecture(records) << endl;
    cout << "actual output: " << fail_lecture_erroneous(records) << endl;

    // 5. Define a test case that results in failure.
    // expected output: True
    // actual output: False
    records = {0, 1, 1, 1, 1, 1, 0, 1, 0, 1};
    cout << "Question 5:" << endl;
    cout << "expected output: " << fail_lecture(records) << endl;
    cout << "actual output: " << fail_lecture_erroneous(records) << endl;

    return 0;
}