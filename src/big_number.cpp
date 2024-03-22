#include "big_number.h"

#include <iostream>
#include <string.h>

namespace BigNum{

    std::string BigNumber::normalize_precision(std::string data, long long p1, long long p2){
        while(p1 < p2){
            data+= "0";
            p1++;
        }
        return data;
    }

    std::string BigNumber::sum(std::string x, std::string y) {
        x="0"+x;
        y="0"+y;

        while(x.length()<y.length()){
            x="0"+x;
        }
        while(y.length()<x.length()){
            y="0"+y;
        }
        std::string result = "";
        while(result.length() < x.length()){
            result += "0";
        }
        for(int i=result.length(); i>=0; --i){
            result[i]+= (ctoi(x[i]) + ctoi(y[i]));
            if(result[i]>'9'){
                result[i]-=10;
                result[i-1]+=1;
            }
        }
        while(result[0] == '0') {
            result.erase(0, 1);
        }
    }

    BigNumber BigNumber::sum(const BigNumber &x, const BigNumber &y) {

        if(x.sign == y.sign){
            std::string d1 = normalize_precision(x.data, x.point_pos, max(x.point_pos, y.point_pos));
            std::string d2 = normalize_precision(x.data, x.point_pos, max(x.point_pos, y.point_pos));
            return BigNumber(sum(d1, d2), x.point_pos, x.sign);
        }
        if()
    }

    //BigNumber BigNumber::dif(const BigNumber &x, const BigNumber &y) {}

    //BigNumber BigNumber::mul(const BigNumber &x, const BigNumber &y) {}

    //BigNumber BigNumber::div(const BigNumber &x, const BigNumber &y) {}

    //bool BigNumber::first_greater_then_second(const BigNumber &x, const BigNumber &y){return false;}

    bool BigNumber::first_greater_then_second(const std::string &x, const std::string &y){
        return x>y;
    }

    int BigNumber::ctoi(const char &x) {
        return x - '0';
    }

    BigNumber::BigNumber(const std::string &number) {

        sign = false;
        data = "";
        point_pos = 0;

        if(number.empty()){
            return;
        }

        for(int i=0; i<number.length(); ++i){
            if(number[i] == '-') {
                sign = true;
            }
            else if(number[i] == '.'){
                point_pos = number.length() - i - 1;
            }
            else{
                data += number[i];
            }
        }
    }

    BigNumber::BigNumber(long long pos){
        sign = false;
        data = "0";
        point_pos = pos;
        if(pos < 0){
            throw std::invalid_argument("Point position must be positive");
        }
    }

    std::string BigNumber::to_string() {
        std::string result;

        if(sign){
            result+='-';
        }
        for(int i=0; i<data.length()-point_pos-1; ++i){
            result+=data[i];
        }
        if(point_pos == 0){
            return result;
        }

        result += '.';
        for(int i=data.length()-point_pos-1; i<data.length(); ++i)
        {
            result+=data[i];
        }
        return result;
    }

    BigNumber operator+(BigNumber x, const BigNumber &y) {
        return BigNumber(__cxx11::basic_string());
    }



    BigNumber operator+(const BigNumber &x, const BigNumber &y){
        return sum(x,y);
    }

    //BigNumber operator-(BigNumber x, const BigNumber &y) {return BigNumber(__cxx11::basic_string());}

    //BigNumber operator*(BigNumber x, const BigNumber &y) {return BigNumber(__cxx11::basic_string());}

    //BigNumber operator/(BigNumber x, const BigNumber &y) {return BigNumber(__cxx11::basic_string());}

    bool operator==(BigNumber x, const BigNumber &y){
        return x.data == y.data && x.point_pos == y.point_pos && x.sign == y.sign;
    }

    //bool operator>(BigNumber x, const BigNumber &y) {return false;}

    //bool operator<(BigNumber x, const BigNumber &y) {return false;}

    //bool operator>=(BigNumber x, const BigNumber &y) {return false;}

    //bool operator<=(BigNumber x, const BigNumber &y) {return false;}

    //BigNumber &BigNumber::operator=(const BigNumber &x) {return <#initializer#>;}

    //BigNumber &BigNumber::operator+=(const BigNumber &x) {return <#initializer#>;}

    //BigNumber &BigNumber::operator-=(const BigNumber &x) {return <#initializer#>;}

    //BigNumber &BigNumber::operator*=(const BigNumber &x) {return <#initializer#>;}

    //BigNumber &BigNumber::operator/=(const BigNumber &x) {return <#initializer#>;}

    //BigNumber &BigNumber::operator++(int) {return <#initializer#>;}

    //BigNumber &BigNumber::operator--(int) {return <#initializer#>;}

    //BigNumber calc_pi(unsigned precision){}


}