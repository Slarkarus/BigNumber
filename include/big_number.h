#ifndef LIB_BIG_NUMBER_H
#define LIB_BIG_NUMBER_H

#include <string>

namespace BigNum {
    long long max(long long a, long long b);

    long long min(long long a, long long b);

    class BigNumber {
    private:
        bool sign;
        std::string data_1; // data before point
        std::string data_2; // data after point
        long long point_pos;

        static std::string sum(std::string x, std::string y); // v2
        static std::string diff(std::string x, std::string y); // v2
        static std::string mul(const std::string &x, const std::string &y);

        static std::string div(std::string x, std::string y);

        static std::string div2(std::string x);

        //char to int
        static int ctoi(const char &x); // v2

        // normalize precision
        static void norm_prec(std::string &data, long long p1, long long p2);

        static void add_left_zeros(std::string &data_1, std::string &data_2);

        static bool a_less_than_b(const std::string &a, const std::string &b);

        void fix_negative_zero();

        static BigNumber sum(BigNumber x, BigNumber y);

        static BigNumber diff(BigNumber x, BigNumber y);

        static BigNumber mul(BigNumber x, BigNumber y);

        static BigNumber div(BigNumber x, BigNumber y);

    public:


        explicit BigNumber(const std::string &number); // v2
        explicit BigNumber(long long point_pos); // v2
        BigNumber &operator=(const BigNumber &x);

        std::string to_string(); // v2
        bool is_zero();

        BigNumber operator+(BigNumber x);

        BigNumber operator-(BigNumber x);

        BigNumber operator*(BigNumber x);

        BigNumber operator/(BigNumber x);

        BigNumber operator-();

        friend bool operator==(const BigNumber &x, const BigNumber &y);

        friend bool operator!=(const BigNumber &x, const BigNumber &y);

        friend bool operator<(const BigNumber &x, const BigNumber &y);

        friend bool operator>(const BigNumber &x, const BigNumber &y);


    };


    BigNumber operator "" _b(const char *str, size_t size);

}

#endif //LIB_BIG_NUMBER_H
