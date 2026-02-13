#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <stdexcept>

// A class to represent and operate on high-precision decimals.
// Operations are done using string manipulation to simulate manual "vertical" arithmetic.
class BigDec {
public:
    bool is_negative = false;
    std::string integer_part = "0";
    std::string fraction_part = "0";

    // Default constructor
    BigDec() = default;

    // Constructor from a string representation
    BigDec(std::string s) {
        if (s.empty()) {
            return;
        }

        if (s[0] == '-') {
            is_negative = true;
            s = s.substr(1);
        } else if (s[0] == '+') {
            s = s.substr(1);
        }

        size_t dot_pos = s.find('.');
        if (dot_pos != std::string::npos) {
            integer_part = s.substr(0, dot_pos);
            fraction_part = s.substr(dot_pos + 1);
            if (integer_part.empty()) integer_part = "0";
            if (fraction_part.empty()) fraction_part = "0";
        } else {
            integer_part = s;
            fraction_part = "0";
        }
        remove_leading_zeros(integer_part);
        remove_trailing_zeros(fraction_part);
    }

    // Print the number
    void print() const {
        if (is_negative && (integer_part != "0" || fraction_part != "0")) {
            std::cout << "-";
        }
        std::cout << integer_part << "." << fraction_part << std::endl;
    }

    // Overload the + operator for addition
    BigDec operator+(const BigDec& other) const {
        if (this->is_negative == other.is_negative) {
            // Same sign: perform addition
            return add_abs(*this, other);
        } else {
            // Different signs: perform subtraction
            return subtract_abs(*this, other);
        }
    }

private:
    // Helper to compare absolute values of two BigDecs
    // Returns: 1 if |a| > |b|, -1 if |a| < |b|, 0 if |a| == |b|
    static int compare_abs(const BigDec& a, const BigDec& b) {
        if (a.integer_part.length() > b.integer_part.length()) return 1;
        if (a.integer_part.length() < b.integer_part.length()) return -1;
        if (a.integer_part > b.integer_part) return 1;
        if (a.integer_part < b.integer_part) return -1;
        
        // Integer parts are equal, compare fraction parts
        std::string fa = a.fraction_part;
        std::string fb = b.fraction_part;
        size_t max_len = std::max(fa.length(), fb.length());
        fa.resize(max_len, '0');
        fb.resize(max_len, '0');
        if (fa > fb) return 1;
        if (fa < fb) return -1;

        return 0;
    }

    // Adds two BigDecs with the same sign
    static BigDec add_abs(const BigDec& a, const BigDec& b) {
        BigDec result;
        result.is_negative = a.is_negative;

        // 1. Align fraction parts
        std::string fa = a.fraction_part;
        std::string fb = b.fraction_part;
        size_t max_frac_len = std::max(fa.length(), fb.length());
        fa.resize(max_frac_len, '0');
        fb.resize(max_frac_len, '0');

        // 2. Add fraction parts
        int carry = 0;
        std::string res_frac(max_frac_len, '0');
        for (int i = max_frac_len - 1; i >= 0; --i) {
            int digit_sum = (fa[i] - '0') + (fb[i] - '0') + carry;
            res_frac[i] = (digit_sum % 10) + '0';
            carry = digit_sum / 10;
        }
        result.fraction_part = res_frac;

        // 3. Add integer parts (with carry from fraction)
        std::string ia = a.integer_part;
        std::string ib = b.integer_part;
        std::string res_int = "";
        int i = ia.length() - 1;
        int j = ib.length() - 1;
        while (i >= 0 || j >= 0 || carry > 0) {
            int digit_sum = carry;
            if (i >= 0) digit_sum += (ia[i--] - '0');
            if (j >= 0) digit_sum += (ib[j--] - '0');
            res_int += (digit_sum % 10) + '0';
            carry = digit_sum / 10;
        }
        std::reverse(res_int.begin(), res_int.end());
        result.integer_part = res_int.empty() ? "0" : res_int;

        return result;
    }

    // Subtracts two BigDecs (handles different signs by delegating here)
    static BigDec subtract_abs(const BigDec& a, const BigDec& b) {
        int cmp = compare_abs(a, b);
        if (cmp == 0) {
            return BigDec("0.0");
        }

        const BigDec* p_larger = (cmp > 0) ? &a : &b;
        const BigDec* p_smaller = (cmp > 0) ? &b : &a;

        BigDec result;
        result.is_negative = p_larger->is_negative;

        // 1. Align fraction parts
        std::string fa = p_larger->fraction_part;
        std::string fb = p_smaller->fraction_part;
        size_t max_frac_len = std::max(fa.length(), fb.length());
        fa.resize(max_frac_len, '0');
        fb.resize(max_frac_len, '0');

        // 2. Subtract fraction parts
        int borrow = 0;
        std::string res_frac(max_frac_len, '0');
        for (int i = max_frac_len - 1; i >= 0; --i) {
            int digit_diff = (fa[i] - '0') - (fb[i] - '0') - borrow;
            if (digit_diff < 0) {
                digit_diff += 10;
                borrow = 1;
            } else {
                borrow = 0;
            }
            res_frac[i] = digit_diff + '0';
        }
        result.fraction_part = res_frac;

        // 3. Subtract integer parts
        std::string ia = p_larger->integer_part;
        std::string ib = p_smaller->integer_part;
        std::string res_int = "";
        int i = ia.length() - 1;
        int j = ib.length() - 1;
        while (i >= 0 || j >= 0) {
            int digit_diff = -borrow;
            if (i >= 0) digit_diff += (ia[i--] - '0');
            if (j >= 0) digit_diff -= (ib[j--] - '0');
            
            if (digit_diff < 0) {
                digit_diff += 10;
                borrow = 1;
            } else {
                borrow = 0;
            }
            res_int += digit_diff + '0';
        }
        std::reverse(res_int.begin(), res_int.end());
        remove_leading_zeros(res_int);
        result.integer_part = res_int;
        
        remove_trailing_zeros(result.fraction_part);
        return result;
    }
    
    static void remove_leading_zeros(std::string& s) {
        if (s.length() > 1) {
            s.erase(0, s.find_first_not_of('0'));
            if (s.empty()) s = "0";
        }
    }

    static void remove_trailing_zeros(std::string& s) {
        if (s != "0") {
            s.erase(s.find_last_not_of('0') + 1, std::string::npos);
            if (s.empty()) s = "0";
        }
    }
};

int main() {
    std::vector<BigDec> data = {
        BigDec("4042.045051380452"),
        BigDec("0.000531415926535"),
        BigDec("-2759471.276702747"),
        BigDec("0.0000557052996742895"),
        BigDec("2755463.874010974"),
        BigDec("-0.000031415926535"),
        BigDec("-34.64291531256604")
    };

    std::cout << "Starting manual high-precision summation..." << std::endl;

    BigDec sum("0.0");
    for (const auto& num : data) {
        sum = sum + num;
    }

    std::cout << "\nThe final precise sum is:" << std::endl;
    sum.print();

    return 0;
}
