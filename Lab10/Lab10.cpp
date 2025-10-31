/*
Program Name: EECS 348 Lab 10
Description: Double Addition without conversion in C++ 
Inputs: input with doubles to be added separated by spaces
Outputs: every pair of doubles added, if valid
Collaborators: 
Other Sources: ChatGPT, geeksforgeeks
Author: Warren Tan
Creation Date: 30/10/2025
*/

#include <iostream> // console printing/user input
#include <fstream> // file input
#include <string> // string class
#include <sstream> // split strings for processing

using namespace std;

// checks if the given string is an empty string (including new lines, spaces, etc.)
// function from ChatGPT
bool isBlank(const string& s) {
    // checks every character in the string
    for (char c : s)
        // if any character is not whitespace, the string is not blank.
        if (!isspace(static_cast<unsigned char>(c)))
            return false;
    // the string is blank
    return true;
}

// checks if a string contains a valid double
bool isValidDouble(const string & s){
    // there is nothing in the string. there cannot be a double
    if(s.empty()){
        return false;
    }

    // holds the current index being checked
    int i = 0;

    // requirements
    bool hasDecimal = false;
    bool hasDigitBefore = false;
    bool hasDigitAfter = false;

    // optional '+' or '-'
    if(s[0] == '+' || s[0] == '-'){
        i += 1;
    }

    while(i < s.size()){
        // query s[i] for digit or decimal
        if(isdigit(s[i])){
            // i is a digit
            if(hasDecimal){
                hasDigitAfter = true;
            }else{
                hasDigitBefore = true;
            }
        }else if(s[i] == '.'){
            if(hasDecimal){
                // encountered two decimals
                return false;
            }
            // first decimal encountered
            hasDecimal = true;
        }else{
            // invalid character
            return false;
        }
        ++i;
    }

    // no digit before decimal
    if(!hasDigitBefore){
        return false;
    }
    
    // decimal without digit after
    if(hasDecimal && !hasDigitAfter){
        return false;
    }

    return true;
}

// convert input to a readable double; assumes the double is valid through isValidDouble
string convertString(const string & s){
    // prevent empty strings
    if(s.empty()){
        cerr << "Error: Input is empty" << endl;
        return "";
    }
    
    // deep copy the string to new location
    string newString = s;

    // remove and remember leading '-'
    // substr from geeksforgeeks
    bool isNegative = false;
    if(newString[0] == '-'){
        isNegative = true;
        newString = newString.substr(1);
    
    // remove leading '+'
    }else if(newString[0] == '+'){
        newString = newString.substr(1);
    }

    // add decimal point, if necessary
    // find() and string::npos from geeksforgeeks
    if(newString.find('.') == string::npos){
        newString += ".0";
    }
    
    // remove leading '0'
    while(newString[0] == '0' && newString[1] != '.'){
        newString = newString.substr(1);
    }

    // re-add negative, if necessary
    if(isNegative && newString != "0.0"){
        newString = '-' + newString;
    }

    return newString;
}

// addition for two string integers
string addIntegers(const string & num1, const string & num2){
    // current calculated sum of digits
    string solution = "";
    int carryDigit = 0;

    // add digits one-by-one to get solution
    for(int i = num1.size() - 1; i >= 0; --i){
        // add digits together
        // subtracting '0' from the numbers converts the ASCII number to its integer number
        // subtracting '0' to get integer strategy from ChatGPT
        int sum = (num1[i] - '0') + (num2[i] - '0') + carryDigit;
        
        // calculate how much to carry
        carryDigit = sum / 10;

        // add non-carry digit to beginning of string
        solution.insert(0, to_string(sum % 10));
    }

    // add carry digit to end
    if(carryDigit != 0){
        solution.insert(0, to_string(carryDigit));
    }
    
    return solution;
}

// subtraction for two string integers
string subtractIntegers(const string & num1, const string & num2){
    // current calculated sum of digits
    string solution = "";
    int borrowDigit = 0;

    // add digits one-by-one to get solution
    for(int i = num1.size() - 1; i >= 0; --i){
        // find digits to subtract
        int digit1 = (num1[i] - '0') - borrowDigit;
        int digit2 = (num2[i] - '0');
        
        // needs a borrow digit
        if(digit1 < digit2){
            digit1 += 10;
            borrowDigit = 1;

        // no borrow digit
        }else{
            borrowDigit = 0;
        }
        
        // subtract digits
        solution.insert(0, to_string(digit1 - digit2));
    }
    
    return solution;
}

// returns 1 if num1 is greater, -1 if num2 is greater, and 0 if equal
// function from ChatGPT
int compareIntegers(string num1, string num2) {
    // remove leading zeros
    while (num1.size() > 1 && num1[0] == '0') num1.erase(0, 1);
    while (num2.size() > 1 && num2[0] == '0') num2.erase(0, 1);

    // compare sizes
    if (num1.size() > num2.size()) return 1;
    if (num1.size() < num2.size()) return -1;

    // check dictionary order
    if (num1 > num2) return 1;
    if (num1 < num2) return -1;
    return 0;
}

// add two string doubles together
string addDoubles(const string & s1, const string & s2){
    // find the numbers before and after each decimal
    string beforeDecimal1 = s1.substr(0, s1.find('.'));
    string beforeDecimal2 = s2.substr(0, s2.find('.'));
    string afterDecimal1 = s1.substr(s1.find('.') + 1);
    string afterDecimal2 = s2.substr(s2.find('.') + 1);

    // remove and store leading '-'
    bool s1Negative = false;
    bool s2Negative = false;
    if(beforeDecimal1[0] == '-'){
        s1Negative = true;
        beforeDecimal1 = beforeDecimal1.substr(1);
    }
    if(beforeDecimal2[0] == '-'){
        s2Negative = true;
        beforeDecimal2 = beforeDecimal2.substr(1);
    }

    // ensure equal length before decimal by add leading zeroes
    while(beforeDecimal1.size() < beforeDecimal2.size()){
        beforeDecimal1 = '0' + beforeDecimal1;
    }
    while(beforeDecimal2.size() < beforeDecimal1.size()){
        beforeDecimal2 = '0' + beforeDecimal2;
    }

    // ensure equal length after decimal by adding trailing zeroes
    while(afterDecimal1.size() < afterDecimal2.size()){
        afterDecimal1 += '0';
    }
    while(afterDecimal2.size() < afterDecimal1.size()){
        afterDecimal2 += '0';
    }
    
    string num1 = beforeDecimal1 + afterDecimal1;
    string num2 = beforeDecimal2 + afterDecimal2;

    // current calculated sum of digits
    string solution = "";

    // both are positive numbers
    if(!s1Negative && !s2Negative){
        // add the integers together
        solution = addIntegers(num1, num2);

        // re-insert decimal
        solution.insert(solution.size() - afterDecimal1.size(), ".");
    
    // both are negative
    }else if(s1Negative && s2Negative){
        // add the integers together
        solution = addIntegers(num1, num2);

        // add '-' to answer
        solution.insert(0, "-");

        // re-insert decimal
        solution.insert(solution.size() - afterDecimal1.size(), ".");
    
    // one is negative, the other is not
    }else{
        // 1 if num1 is greater, -1 if num2 is greater, and 0 if equal
        int largerS1 = compareIntegers(num1, num2);

        // larger s1
        if(largerS1 > 0){
            // subtract integers
            solution = subtractIntegers(num1, num2);

            if(s1Negative){
                // add '-' to answer
                solution.insert(0, "-");
            }

            // re-insert decimal
            solution.insert(solution.size() - afterDecimal1.size(), ".");

        // larger s2
        }else if(largerS1 < 0){
            // subtract integers
            solution = subtractIntegers(num2, num1);

            if(s2Negative){
                // add '-' to answer
                solution.insert(0, "-");
            }

            // re-insert decimal
            solution.insert(solution.size() - afterDecimal1.size(), ".");

        // equal s1 and s2
        }else{
            solution = "0.0";
        }
    }

    return solution;
}

// reads file and produces outputs based on file contents
void processFile(const string & inputFile){
// attempt to open the file in parameter 'fin'
    // ifstream from ChatGPT
    ifstream fin(inputFile);
    if (!fin) {
        cerr << "Error opening file." << endl;
        return;
    }
    
    // string to temporarily store each line from the file
    string line;
    
    // passes through every line in file
    while(getline(fin, line)){
        // skips empty lines
        if(isBlank(line)){
            continue;
        }

        // split string into two 
        istringstream ss(line);
        string s1, s2;
        ss >> s1 >> s2;
        
        // validate doubles
        if(!isValidDouble(s1)){
            cerr << "\"" << s1 << "\" is invalid" << endl;
            continue;
        }
        if(!isValidDouble(s2)){
            cerr << "\"" << s2 << "\" is invalid" << endl;
            continue;
        }

        // convert string to a readable string format
        string num1 = convertString(s1);
        string num2 = convertString(s2);

        // make solution
        string solution = convertString(addDoubles(num1, num2));
        
        // remove trailing zeroes
        while(solution[solution.size() - 1] == '0' && solution[solution.size() - 2] != '.'){
            solution = solution.substr(0, solution.size() - 1);
        }

        cout << solution << endl;
    }
}


int main(){
    // get user input
    string fileName;
    cout << "Name of file: ";
    cin >> fileName;

    // fileName = "input.txt";
    
    // process file
    processFile(fileName);
    
    return 0;
}