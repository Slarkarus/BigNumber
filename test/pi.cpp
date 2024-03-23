//
// Created by marmlll on 21.03.2024.
//
#include <iostream>
#include <ctime>
#include "big_number.h"

using  namespace BigNum;

BigNumber calc_atan(const BigNumber x, unsigned precision){
    BigNumber result(precision);
    result = x;
    result = result-x;
    std::string small = "1";
    for(int i=0; i<precision; ++i){
        small = "0"+small;
    }
    small[1]='.';
    BigNumber down(small);

    BigNumber numerator = x;
    BigNumber denominator(precision);
    denominator = "1"_b;
    BigNumber two = "2"_b;

    BigNumber tmp(precision);
    tmp = x;
    std::cout << tmp.to_string() << '\n';
    std::cout << down.to_string() << '\n';
    int count = 0;
    while(tmp > down){
        std::cout << count << '\n';
        tmp = numerator / denominator;
        if(count%2==0) {
            result = result + tmp;
        }
        else{
            result = result - tmp;
        }
        count++;

        numerator = numerator*x*x;
        denominator = denominator + two;
    }
    return result;
}

BigNumber calc_pi(unsigned precision){
    precision +=20;
    BigNumber one(precision), two(precision), three(precision), four(precision);
    one = "1"_b;
    two = "2"_b;
    three = "3"_b;
    four = "4"_b;
    return two  * (calc_atan(one/two, precision) + calc_atan(one/three, precision));
}

int main(){
    unsigned precision;
    std::cin >> precision;

    clock_t time;
    time = clock();
    calc_pi(precision);

    time = clock() - time;
    std::cout <<  "It took me " << ((float)time)/CLOCKS_PER_SEC << " seconds\n";
    return 0;
}