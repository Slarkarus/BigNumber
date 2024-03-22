//
// Created by marmlll on 21.03.2024.
//
#include <iostream>
#include "gtest/gtest.h"
#include "big_number.h"

TEST(TestBigNumber, StringTest){
    std::string a = "-123.51";
    BigNum::BigNumber x(a);
    //std::cout << x.to_string();
    EXPECT_EQ(a, x.to_string());
}

TEST(TestBigNumber, SumTest){
    BigNum::BigNumber x("0.08");
    BigNum::BigNumber y("0.02");
    std::cout << (x+y).to_string();
}