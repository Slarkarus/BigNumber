#include "big_number.h"

#include <iostream>
#include <string>
#include <vector>

namespace BigNum {

    long long max(long long a, long long b) {
        return a < b ? b : a;
    }

    long long min(long long a, long long b) {
        return a > b ? b : a;
    }


    bool BigNumber::a_less_than_b(const std::string &a, const std::string &b) {
        if (a.size() != b.size()) {
            return a.size() < b.size();
        }
        return a < b;
    }

    void BigNumber::norm_prec(std::string &data, long long p1, long long p2) {
        while (p1 < p2) {
            data += "0";
            p1++;
        }
    }

    std::string BigNumber::sum(std::string x, std::string y) {
        add_left_zeros(x, y);
        std::string result = "";
        while (result.length() < x.length()) {
            result += "0";
        }
        for (int i = result.length() - 1; i >= 0; --i) {
            result[i] += (ctoi(x[i]) + ctoi(y[i]));
            if (result[i] > '9') {
                result[i] -= 10;
                result[i - 1] += 1;
            }
        }

        while (result[0] == '0') {
            result.erase(0, 1);
        }

        return result;
    }

    std::string BigNumber::diff(std::string x, std::string y) {
        add_left_zeros(x, y);

        std::string result = "";
        while (result.length() < x.length()) {
            result += "0";
        }

        for (int i = result.length() - 1; i >= 0; --i) {
            result[i] += ctoi(x[i]) - ctoi(y[i]);
            if (result[i] < '0') {
                result[i] += 10;
                result[i - 1] -= 1;
            }
        }

        while (result[0] == '0') {
            result.erase(0, 1);
        }
        return result;
    }

    std::string BigNumber::mul(const std::string &x, const std::string &y) {
        std::string result;
        while (result.size() < x.size() + y.size()) {
            result.push_back('0');
        }
        int pos;
        for (int i = x.length() - 1; i >= 0; --i) {
            for (int j = y.length() - 1; j >= 0; --j) {
                pos = i + j + 1;
                result[pos] += (ctoi(x[i]) * ctoi(y[j])) % 10;
                result[pos - 1] += (ctoi(x[i]) * ctoi(y[j])) / 10;

                while (result[pos] > '9') {
                    result[pos] -= 10;
                    result[pos - 1] += 1;
                    pos--;
                }
            }
        }
        while (result[0] == '0') {
            result.erase(0, 1);
        }
        return result;
    }

    std::string BigNumber::div2(std::string x) {
        std::string result;

        while (x != "") {
            result += '0' + ctoi(x[0]) / 2;
            x[0] -= 2 * (ctoi(x[0]) / 2);
            if (ctoi(x[0]) % 2 == 1 && x.size() != 1) {
                x[0]--;
                x[1] += 10;
            }
            x.erase(0, 1);
        }
        while (result[0] == '0') {
            result.erase(0, 1);
        }
        return result;
    }

    std::string BigNumber::div(std::string x, std::string y) {

        bool flag = true;
        for (int i = 0; i < x.size(); ++i) {
            if (x[i] != '0') {
                flag = false;
                break;
            }
        }
        if (flag) { return "0"; }

        std::string left = "0";
        std::string right = x;
        std::string mid;

        while (a_less_than_b(sum(left, "1"), right)) {

            mid = div2(sum(left, right));

            if (a_less_than_b(mul(mid, y), x)) {
                left = mid;
            } else {
                right = mid;
            }
        }
        return left;
    }


    void BigNumber::add_left_zeros(std::string &x, std::string &y) {
        x = "0" + x;
        y = "0" + y;

        while (x.length() < y.length()) {
            x = "0" + x;
        }
        while (y.length() < x.length()) {
            y = "0" + y;
        }
    }

    int BigNumber::ctoi(const char &x) {
        return x - '0';
    }

    // constructors

    BigNumber::BigNumber(const std::string &number) {

        sign = false;
        data_1 = "";
        data_2 = "";
        point_pos = 0;


        if (number.empty()) {
            data_1 = "0";
            return;
        }
        bool flag = false;
        for (int i = 0; i < number.length(); ++i) {
            if (number[i] == '-') {
                if (sign) {
                    throw std::invalid_argument("BigNumber constructor: bad argument: double sign in string");
                }
                sign = true;
            } else if (number[i] == '.') {
                if (flag) {
                    throw std::invalid_argument("BigNumber constructor: bad argument: double dot in string");
                }
                point_pos = number.length() - i - 1;
                flag = true;
            } else if (flag) {
                data_2 += number[i];
            } else {
                data_1 += number[i];
            }
        }
        fix_negative_zero();
    }

    BigNumber::BigNumber(long long pos) {
        sign = false;
        data_1 = "0";
        data_2 = "";
        point_pos = pos;
        if (pos < 0) {
            throw std::invalid_argument("BigNumber constructor: bad argument: dot position must be positive or zero");
        }
    }

    BigNumber BigNumber::sum(BigNumber x, BigNumber y) {
        if (x.sign != y.sign) {
            if (y.sign) {
                y.sign = false;
                return diff(x, y);
            }
            x.sign = false;
            return diff(y, x);
        }
        BigNumber result(max(x.point_pos, y.point_pos));
        std::string x_data = x.data_1 + x.data_2;
        std::string y_data = y.data_1 + y.data_2;
        norm_prec(x_data, x.point_pos, max(x.point_pos, y.point_pos));
        norm_prec(y_data, y.point_pos, max(x.point_pos, y.point_pos));

        std::string result_data = sum(x_data, y_data);
        while (result_data.length() <= result.point_pos) {
            result_data = "0" + result_data;
        }

        result.data_1 = result_data.substr(0, result_data.length() - max(x.point_pos, y.point_pos));
        result.data_2 = result_data.substr(result_data.length() - max(x.point_pos, y.point_pos),
                                           max(x.point_pos, y.point_pos));
        result.sign = x.sign;
        result.fix_negative_zero();
        return result;
    }

    BigNumber BigNumber::diff(BigNumber x, BigNumber y) {
        if (x.sign != y.sign) {
            if (y.sign) {
                y.sign = false;
                return sum(x, y);
            }
            x.sign = false;
            return sum(x, y);
        }
        BigNumber result(max(x.point_pos, y.point_pos));
        bool change_sign = false;
        if (x.sign) {
            x.sign = false;
            y.sign = false;
            change_sign = true;
        }
        if (x < y) {
            if (change_sign) {
                return diff(y, x);
            }
            return -diff(y, x);
        }

        std::string x_data = x.data_1 + x.data_2;
        std::string y_data = y.data_1 + y.data_2;
        norm_prec(x_data, x.point_pos, max(x.point_pos, y.point_pos));
        norm_prec(y_data, y.point_pos, max(x.point_pos, y.point_pos));

        std::string result_data = diff(x_data, y_data);
        while (result_data.length() <= result.point_pos) {
            result_data = "0" + result_data;
        }

        result.data_1 = result_data.substr(0, result_data.length() - result.point_pos);
        result.data_2 = result_data.substr(result_data.length() - result.point_pos,
                                           result.point_pos);
        result.sign = change_sign;

        result.fix_negative_zero();
        return result;
    };

    BigNumber BigNumber::mul(BigNumber x, BigNumber y) {
        BigNumber result(x.point_pos + y.point_pos);

        std::string x_data = x.data_1 + x.data_2;
        std::string y_data = y.data_1 + y.data_2;
        std::string result_data = mul(x_data, y_data);

        while (result_data.length() <= result.point_pos) {
            result_data = "0" + result_data;
        }

        result.data_1 = result_data.substr(0, result_data.length() - result.point_pos);
        result.data_2 = result_data.substr(result_data.length() - result.point_pos,
                                           result.point_pos);
        result.sign = x.sign ^ y.sign;

        result.fix_negative_zero();
        return result;
    }

    BigNumber BigNumber::div(BigNumber x, BigNumber y) {

        BigNumber result(max(0, max(x.point_pos, y.point_pos)));

        std::string x_data = x.data_1 + x.data_2;
        std::string y_data = y.data_1 + y.data_2;

        norm_prec(x_data, x.point_pos, max(x.point_pos, y.point_pos));
        norm_prec(y_data, x.point_pos, max(x.point_pos, y.point_pos));
        for (int i = 0; i < result.point_pos + max(y.point_pos - x.point_pos, 0); ++i) {
            x_data += '0';
        }
        std::string result_data = div(x_data, y_data);

        while (result_data.length() <= result.point_pos) {
            result_data = "0" + result_data;
        }

        result.data_1 = result_data.substr(0, result_data.length() - result.point_pos);
        result.data_2 = result_data.substr(result_data.length() - result.point_pos,
                                           result.point_pos);
        result.sign = x.sign ^ y.sign;

        result.fix_negative_zero();
        return result;
    }


    std::string BigNumber::to_string() {
        std::string result;

        if (sign) {
            result += '-';
        }

        result += data_1;

        if (point_pos == 0) {
            return result;
        }

        result += '.';
        result += data_2;
        return result;
    }

    BigNumber BigNumber::operator+(BigNumber x) {
        return sum(*this, x);
    }

    BigNumber BigNumber::operator-(BigNumber x) {
        return diff(*this, x);
    }

    BigNumber BigNumber::operator*(BigNumber x) {
        return mul(*this, x);
    }

    BigNumber BigNumber::operator/(BigNumber x) {
        return div(*this, x);
    }

    BigNumber BigNumber::operator-() {
        BigNumber res = (*this);
        res.sign = !res.sign;
        res.fix_negative_zero();
        return res;
    }

    bool operator==(const BigNumber &x, const BigNumber &y) {
        if (x.sign != y.sign) {
            return false;
        }
        if (x.data_1 != y.data_1) {
            return false;
        }
        for (int i = 0; i < min(x.point_pos, y.point_pos); ++i) {
            if (x.data_2[i] != y.data_2[i]) {
                return false;
            }
        }
        if (x.data_2.size() > y.data_2.size()) {
            for (int i = y.data_2.size(); i < x.data_2.size(); ++i) {
                if (x.data_2[i] != '0') {
                    return false;
                }
            }
        } else if (x.data_2.size() < y.data_2.size()) {
            for (int i = x.data_2.size(); i < y.data_2.size(); ++i) {
                if (y.data_2[i] != '0') {
                    return false;
                }
            }
        }
        return true;
    }

    bool operator!=(const BigNumber &x, const BigNumber &y) {
        return !(x == y);
    }

    bool operator<(const BigNumber &x, const BigNumber &y) {
        bool change_answ = false;
        if (x.sign != y.sign) {
            return x.sign;
        }
        if (x.sign) {
            change_answ = true;
        }
        if (x.data_1 != y.data_1) {
            if (x.data_1.size() < y.data_1.size())
                return !change_answ;
            else if (x.data_1.size() > y.data_1.size()) {
                return change_answ;
            }
            return (x.data_1 < y.data_1) ^ change_answ;
        }
        for (int i = 0; i < min(x.point_pos, y.point_pos); ++i) {
            if (x.data_2[i] < y.data_2[i]) {
                return !change_answ;
            }
            if (x.data_2[i] > y.data_2[i]) {
                return change_answ;
            }
        }
        if (x.point_pos > y.point_pos) {
            return change_answ;
        }
        for (int i = x.point_pos; i < y.point_pos; ++i) {
            if (y.data_2[i] != '0') {
                return !change_answ;
            }
        }
        return false;
    }

    bool operator>(const BigNumber &x, const BigNumber &y) {
        return y < x;
    }

    void BigNumber::fix_negative_zero() {
        if (is_zero() && sign) {
            sign = false;
        }
    }


    bool BigNumber::is_zero() {
        for (auto c: data_2) {
            if (c != '0') {
                return false;
            }
        }
        if (data_1 != "0") {
            return false;
        }
        return true;
    }

    BigNumber &BigNumber::operator=(const BigNumber &x) {
        sign = x.sign;
        data_1 = x.data_1;
        data_2 = x.data_2;
        while (data_2.size() < point_pos) {
            data_2 += '0';
        }
        if (data_2.size() > point_pos) {
            data_2 = data_2.substr(0, point_pos);
        }
        return *this;
    }


    BigNumber operator ""_b(const char *str, size_t size) {
        return BigNumber(std::string(str, size));
    }



}