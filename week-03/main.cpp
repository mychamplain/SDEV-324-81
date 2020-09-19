/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Champlain College SDEV-345-81
 *
 * C++ Week 3: Discussion (first semester) - Go Fish (2020/09/17)
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *
 * “Go Fish” is a classic children’s card game
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *
 * Written by Llewellyn van der Merwe <llewellyn.vandermerw@mymail.champlain.edu>, September 2020
 * Copyright (C) 2020. All Rights Reserved
 * License GNU/GPL Version 2 or later - http://www.gnu.org/licenses/gpl-2.0.html
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <iostream>
#include <string>
#include <stack>
#include <vector>

// H = hearts   = 1
// D = diamonds = 2
// S = spades   = 3
// C = clubs    = 4

// 1,  2,  3,  4,  5,  6,  7,  8,  9,  10,  11, 12, 13  Number
// 1H, 2H, 3H ,4H, 5H, 6H, 7H, 8H, 9H, 10H, JH, QH, QH  1
// 1D, 2D, 3D ,4D, 5D, 6D, 7D, 8D, 9D, 10D, JD, QD, QD  2
// 1S, 2S, 3S ,4S, 5S, 6S, 7S, 8S, 9S, 10S, JS, QS, QS  3
// 1C, 2C, 3C ,4C, 5C, 6C, 7C, 8C, 9C, 10C, JC, QC, QC  4

// the actual array positions will then be
// 0=1H,  1=2H,  2=3H,  3=4H,  4=5H,  5=6H,  6=7H,  7=8H,  8=9H,  9=10H,  10=JH, 11=QH, 12=QH
// 13=1D, 14=2D, 15=3D, 16=4D, 17=5D, 18=6D, 19=7D, 20=8D, 21=9D, 22=10D, 23=JD, 24=QD, 25=QD
// 26=1S, 27=2S, 28=3S, 29=4S, 30=5S, 31=6S, 32=7S, 33=8S, 34=9S, 35=10S, 36=JS, 37=QS, 38=QS
// 39=1C, 40=2C, 41=3C, 42=4C, 43=5C, 44=6C, 45=7C, 46=8C, 47=9C, 48=10C, 49=JC, 50=QC, 51=QC

using namespace std;

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
