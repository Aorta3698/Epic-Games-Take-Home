#include <string>
#include <iostream>


/*

I wrote a detailed explanation of my thought process with markdown and LaTex
and put them in the submission.md file.

I am not allowed to submit PDF or share GitHub repo,
so if you would like to see the rendered version of it, I'd suggest Typora or Obsidian.
If you don't have either of those,
you can go to https://stackedit.io/app# and paste the codes in .md in there, and it will render it for you.

*/


// My g++ Version: 11.2.0. Compiled with -std=c++20


/**
 * Convert input value into base between 2 - 16 in string format
 * The output string is allocated on behalf of the caller
 *
 * If the value is negative, '-' is added to the front of the resulting string.
 * Any alphbetic letters in the string will be in lower case
 *
 * Input:
 * value (int) - decimal value to be converted to a string
 * base  (int) - base used to represent the value as a string
 *
 * Output:
 * (char*) - A pointer to the resulting null-terminated string
 */
char* itoa(int value, int base){
    if (base <= 1 || base > 16){
        throw std::invalid_argument("base must satisfy 2 <= base <= 16 \n");
    }

    // I am assuming the following
    // - .size()       member   functions are all banned
    // - realloc()     built-in functions are all banned.
    // - int()         casting  functions are all banned.
    // - There is can no function call except for malloc() and new keyword
    // - itoa(-10, 2) is valid. That is, value can be negative.
    // - iota(10, -2) or iota(10, 1) is not valid.

    std::string letter = "0123456789abcdef"; // all the letters we need
    std::string tmp;
    int sz = 0;
    if (value < 0){ // if negative, make it positive and insert -
        tmp += '-';
        value *= -1;
        ++sz;
    }

    // Find the highest digit we care about
    int curBase = 1;
    while(1LL * curBase * base <= value){
        curBase *= base;
    }

    // Then, we start calculating from high to low digits
    while(curBase){
        int curDigit = value / curBase;
        value -= curDigit * curBase;
        tmp += letter[curDigit];
        curBase /= base;
        ++sz;
    }

    // We loop to sz inclusive, tmp[sz] will null-terminated for us
    char* ans = new char[sz+1];
    for (int i = 0; i <= sz; ++i){
        ans[i] = tmp[i];
    }
    return ans;
}
