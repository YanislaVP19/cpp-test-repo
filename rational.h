#pragma once

#include <iostream>
#include <cstdint>
#include <numeric>
#include <cstdlib>

class Rational {
public:
    Rational(int numerator, int denominator)
        : numerator_(numerator)
        , denominator_(denominator) {
        if (denominator_ == 0) {
            std::abort();
        }
        Reduction();
    }
    Rational(int value) : numerator_(value), denominator_(1) {}

    Rational() : numerator_(0), denominator_(1) {}

    Rational(const Rational&) = default;

    Rational operator+(const Rational& r2) const {
        Rational other{*this};
        other += r2;
        return other;
    }

    Rational operator-(const Rational& r2) const {
        Rational other{*this};
        other -= r2;
        return other;
    }

    Rational operator*(const Rational& r2) const {
        Rational other{*this};
        other *= r2;
        return other;
    }

    Rational operator/(const Rational& r2) const {
        Rational other{*this};
        other /= r2;
        return other;
    }

    Rational& operator+=(const Rational& r2) {
        numerator_ = numerator_ * r2.denominator_ + denominator_ * r2.numerator_;
        denominator_ = denominator_ * r2.denominator_;
        Reduction();
        return *this;
    }

    Rational& operator-=(const Rational& r2) {
        numerator_ = numerator_ * r2.denominator_ - denominator_ * r2.numerator_;
        denominator_ = denominator_ * r2.denominator_;
        Reduction();
        return *this;
    }

    Rational& operator*=(const Rational& r2) {
        numerator_ = numerator_ * r2.numerator_;
        denominator_ = denominator_ * r2.denominator_;
        Reduction();
        return *this;
    }

    Rational& operator/=(const Rational& r2) {
        numerator_ = numerator_ * r2.denominator_;
        denominator_ = denominator_ * r2.numerator_;
        Reduction();
        return *this;
    }

    Rational& operator=(const Rational&) = default;

    Rational operator+() const {
        return *this;
    }

    Rational operator-() const {
        return Rational(-numerator_, denominator_);
    }

    bool operator==(const Rational& other) const {
        return (numerator_ == other.numerator_) && (denominator_ == other.denominator_);
    }

    std::strong_ordering operator<=>(const Rational& other) const {
        int left  = numerator_ * other.denominator_;
        int right = other.numerator_ * denominator_;
        return left <=> right;
    }

    friend std::ostream& operator<<(std::ostream& os, const Rational& r);
    friend std::istream& operator>>(std::istream& is, Rational& r);

    Rational Inv() const {
        if(numerator_ == 0) {
            std::abort();
        }
        return Rational(denominator_, numerator_);
    }

    int GetNumerator() const {
        return numerator_;
    }

    int GetDenominator() const {
        return denominator_;
    }

    void Reduction() {
        if (denominator_ < 0) {
            numerator_ = -numerator_;
            denominator_ = -denominator_;
        }
        const int divisor = std::gcd(numerator_, denominator_);
        numerator_ /= divisor;
        denominator_ /= divisor;
    }

private:
    int numerator_ = 0;
    int denominator_ = 1;
};

inline std::ostream& operator<<(std::ostream& os, const Rational& r) {
    if (r.denominator_ == 1)
        os << r.numerator_;
    else
        os << r.numerator_ << " / " << r.denominator_;
    return os;
}

inline std::istream& operator>>(std::istream& is, Rational& r) {
    int num = 0, den = 1;
    char ch = 0;
    if (!(is >> num)) return is;

    if (is >> ch) {
        if (ch == '/') {
            if (!(is >> den)) {
                is.setstate(std::ios::failbit);
                return is;
            }
            if (den == 0) {
                is.setstate(std::ios::failbit);
                return is;
            }
        } else {
            is.unget();
        }
    } else {
        is.clear();
    }

    r = Rational(num, den);
    return is;
}
