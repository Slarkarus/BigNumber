#ifndef LIB_BIG_NUMBER_H
#define LIB_BIG_NUMBER_H

#include <string>

namespace BigNum{
    long long max(long long a, long long b){
        return a < b ? b : a;
    }

    class BigNumber{
    private:
        bool sign;
        std::string data;
        long long point_pos;

        std::string sum(std::string x, std::string y);

        std::string diff(const std::string &x, const std::string &y){
            if(x<y){
                return diff(y, x);
            }
        }



        bool first_greater_then_second(const BigNumber &x, const BigNumber &y);
        bool first_greater_then_second(const std::string &x, const std::string &y);
        //char to int
        int ctoi(const char &x);

        std::string normalize_precision(std::string data, long long p1, long long p2);

        void ready_to_compare(std::string &data1, std::string &data2){
            while(data1.size() < data2.size()){
                data1 +='0';
            }
        }

        BigNumber(const std::string &data, long long pos, bool sign){

        }
    public:
        BigNumber sum(const BigNumber &x, const BigNumber &y);
        BigNumber dif(const BigNumber &x, const BigNumber &y);
        BigNumber mul(const BigNumber &x, const BigNumber &y);
        BigNumber div(const BigNumber &x, const BigNumber &y);

        explicit BigNumber(const std::string &number);
        explicit BigNumber(long long point_pos);

        std::string to_string();

        friend BigNumber operator+(BigNumber x, const BigNumber &y);
        friend BigNumber operator-(BigNumber x, const BigNumber &y);
        friend BigNumber operator*(BigNumber x, const BigNumber &y);
        friend BigNumber operator/(BigNumber x, const BigNumber &y);

        friend bool operator==(BigNumber x, const BigNumber &y);
        friend bool operator!=(BigNumber x, const BigNumber &y);
        friend bool operator<(BigNumber x, const BigNumber &y);
    };

    BigNumber calc_pi(unsigned precision);
    //BigNumber operator "" _42(std::string);
}

#endif //LIB_BIG_NUMBER_H
