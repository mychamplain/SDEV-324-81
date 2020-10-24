/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Champlain College SDEV-345-81
 *
 * C++ Week 8: Recursion (first semester) - (2020/10/24)
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *
 * Write a recursive algorithm to output the hexadecimal representation of an integer.
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *
 * Written by Llewellyn van der Merwe <llewellyn.vandermerw@mymail.champlain.edu>, October 2020
 * Copyright (C) 2020. All Rights Reserved
 * License GNU/GPL Version 2 or later - http://www.gnu.org/licenses/gpl-2.0.html
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include<iostream>

using namespace std;

// function declaration
void getHexadecimal();
string getHexadecimal(long value);
void getHexadecimal(long value, string& answer);

int main() {
    // lets start our program to get hexadecimal
    getHexadecimal();
    return 0;
}

// function to get the hexadecimal value
void getHexadecimal() {
    // long value to hold 64 bit integers
    long number;
    bool show = true;
    // ask the question
    while (true) {
        if (show) {
            cout << "Enter [n] at any time to stop." << endl;
            cout << endl;
            // show this notice only once
            show = false;
        }
        cout << "████████████████████████████████████" << endl;
        cout << " Convert a integer to hexadecimal" << endl;
        cout << " Enter an integer: ";
        cin >> number;
        // if no integer is added stop
        if (cin.fail()) {
            break;
        }
        // printout the answer in bold yellow
        cout << " Hexadecimal: \e[1m\e[33m" << getHexadecimal(number) << "\e[0m" << endl;
    }
}

// starter function to get the hexadecimal value
string getHexadecimal(long value) {
    // we use a string to hold the answer
    string answer;
    // we start the recursion quest
    getHexadecimal(value, answer);
    // we return the answer
    return answer;
}

// recursive function to get the hexadecimal value
void getHexadecimal(long value, string& answer) {
    // we have a sum value for calculation
    long sum;
    // we are at the end point and should start
    // working up the stack
    if (value == 0)
        return;
    // keep going
    getHexadecimal(value / 16, answer);
    // now work out each
    sum = (sum = value % 16) >= 10 ? sum + 55 : sum + 48;
    // add to our answer
    answer += (char) sum;
}
