//
// Created by marmlll on 21.03.2024.
//
#include <iostream>
#include "gtest/gtest.h"
#include "big_number.h"

using namespace BigNum;

TEST(TestBigNumber, CopyAssignmentTest){
    BigNum::BigNumber x("-123.512");
    BigNum::BigNumber y(1);
    BigNum::BigNumber z(5);
    y = x;
    z = x;
    EXPECT_EQ(y.to_string(), "-123.5");
    EXPECT_EQ(z.to_string(), "-123.51200");
}

TEST(TestBigNumber, StringTest){
    std::string a = "-123.51";
    BigNum::BigNumber x(a);
    //std::cout << x.to_string();
    EXPECT_EQ(a, x.to_string());

    std::string b = "-0.0";
    BigNum::BigNumber y(b);
    EXPECT_EQ(y.to_string(), "0.0");

    BigNum::BigNumber g("");
    EXPECT_EQ(g.to_string(), "0");

    EXPECT_EQ("-123.51"_b.to_string(), "-123.51");
}

TEST(TestBigNumber, SumTest){
    BigNum::BigNumber x("123.54");
    BigNum::BigNumber y("412.12");
    BigNum::BigNumber z("0.000000123");

    BigNum::BigNumber a("0.010");
    BigNum::BigNumber b("0.09");

    BigNum::BigNumber c("-0.0");
    BigNum::BigNumber d("0.0");

    BigNum::BigNumber g("-9469.12");
    BigNum::BigNumber f("-7647.12");

    EXPECT_EQ((x+y).to_string(), "535.66");
    EXPECT_EQ((x+z).to_string(), "123.540000123");

    EXPECT_EQ((a+b).to_string(), "0.100");

    EXPECT_EQ((c+d).to_string(), "0.0");

    EXPECT_EQ((g+f).to_string(), "-17116.24");
    EXPECT_EQ((x+g).to_string(), "-9345.58");
    EXPECT_EQ((z+g).to_string(), "-9469.119999877");
    EXPECT_EQ((f+y).to_string(), "-7235.00");
}

TEST(TestBigNumber, DiffTest){
    BigNum::BigNumber x("123.54");
    BigNum::BigNumber y("412.12");
    BigNum::BigNumber z("0.000000123");

    BigNum::BigNumber a("0.010");
    BigNum::BigNumber b("0.09");

    BigNum::BigNumber c("-0.0");
    BigNum::BigNumber d("0.0");

    BigNum::BigNumber g("-9469.12");
    BigNum::BigNumber f("-7647.12");

    EXPECT_EQ((a-b).to_string(), "-0.080");
    EXPECT_EQ((b-a).to_string(), "0.080");

    EXPECT_EQ((x-y).to_string(), "-288.58");
    EXPECT_EQ((y-x).to_string(), "288.58");
    EXPECT_EQ((x-c).to_string(), x.to_string());
    EXPECT_EQ((c-x).to_string(), (-x).to_string());

    EXPECT_EQ((x-z).to_string(), "123.539999877");

    EXPECT_EQ((g-f).to_string(), "-1822.00");
    EXPECT_EQ((f-g).to_string(), "1822.00");
    EXPECT_EQ((x-g).to_string(), "9592.66");
    EXPECT_EQ((z-g).to_string(), "9469.120000123");
    EXPECT_EQ((f-y).to_string(), "8059.24");
}

TEST(TestBigNumber, MulTest){
    BigNum::BigNumber x("123.54");
    BigNum::BigNumber y("412.12");
    BigNum::BigNumber z("0.000000123");

    BigNum::BigNumber a("999.999");
    BigNum::BigNumber b("9999.9999");

    BigNum::BigNumber c("-0.0");
    BigNum::BigNumber d("0.0");

    EXPECT_EQ((x*y).to_string(), "50913.3048");
    EXPECT_EQ((x*z).to_string(), "0.00001519542");

    EXPECT_EQ((z*c).to_string(), "0.0000000000");

    EXPECT_EQ((a*b).to_string(), "9999989.9000001");

}

TEST(TestBigNumber, DivTest){
    BigNum::BigNumber x("123.54");
    BigNum::BigNumber y("412.12");
    BigNum::BigNumber z("0.000000123");



    EXPECT_EQ((x/y).to_string(), "0.29");
    EXPECT_EQ((x/z).to_string(), "1004390243.902439024");

    BigNum::BigNumber first("1.000000");
    BigNum::BigNumber second("3.000000");
    BigNum::BigNumber third("1000.000000");

    EXPECT_EQ((first/second).to_string(), "0.333333");

    EXPECT_EQ((third/second).to_string(), "333.333333");

    BigNum::BigNumber a("-0.0");

    EXPECT_EQ((a/x).to_string(), "0.00");

    EXPECT_EQ((a/x).to_string(), "0.00");
}

TEST(TestBigNumber, EqualTest)
{

    BigNum::BigNumber a("123.45");
    BigNum::BigNumber b("123.450");
    BigNum::BigNumber c("123.4500");
    BigNum::BigNumber d("-123.45");
    BigNum::BigNumber e("-123.4500000");
    BigNum::BigNumber f("123.451");
    BigNum::BigNumber h("125.451");

    EXPECT_EQ(a==b, true);
    EXPECT_EQ(b==c, true);
    EXPECT_EQ(a==d, false);
    EXPECT_EQ(d==e, true);

    EXPECT_EQ(b==a, true);
    EXPECT_EQ(c==b, true);
    EXPECT_EQ(d==a, false);
    EXPECT_EQ(e==d, true);

    EXPECT_EQ(a!=b, false);
    EXPECT_EQ(b!=c, false);
    EXPECT_EQ(a!=d, true);
    EXPECT_EQ(d!=e, false);

    EXPECT_EQ(a==f, false);
    EXPECT_EQ(f==a, false);
    EXPECT_EQ(b==f, false);
    EXPECT_EQ(c==f, false);
    EXPECT_EQ(h==f, false);
}

TEST(TestBigNumber, ComparsionTest){
    std::vector <BigNum::BigNumber> arr;

    arr.push_back(BigNum::BigNumber ("11.0"));
    arr.push_back(BigNum::BigNumber ("10.10"));
    arr.push_back(BigNum::BigNumber ("10"));
    arr.push_back(BigNum::BigNumber ("5.9"));
    arr.push_back(BigNum::BigNumber ("0"));
    arr.push_back(BigNum::BigNumber ("-10.0"));
    arr.push_back(BigNum::BigNumber ("-10.1"));

    for(int i=0; i<arr.size(); ++i){
        for(int j=i+1; j<arr.size(); ++j){
            EXPECT_EQ(arr[i] > arr[j], true);
        }
    }

    for(int i=0; i<arr.size(); ++i){
        for(int j=i+1; j<arr.size(); ++j){
            EXPECT_EQ(arr[i] < arr[j], false);
        }
    }

    EXPECT_EQ(BigNum::BigNumber("10.00")<BigNum::BigNumber("10.00"), false);
    EXPECT_EQ(BigNum::BigNumber("10.00")>BigNum::BigNumber("10.00"), false);

    EXPECT_EQ(BigNum::BigNumber("-10.00")<BigNum::BigNumber("-10.00"), false);
    EXPECT_EQ(BigNum::BigNumber("-10.00")>BigNum::BigNumber("-10.00"), false);

}
