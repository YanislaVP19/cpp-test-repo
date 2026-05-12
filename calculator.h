
#pragma once

#include <string>
#include <optional>
#include <cmath>
#include "rational.h"
#include "pow.h"

using Error = std::string;

using Number = double;
template <typename T>
class Calculator {
public:
    void Set(T n) {
        current_ = n;
    }

    T GetNumber() const {
        return current_;
    }

    std::optional<Error> Add(T n) {
        current_ += n;
        return std::nullopt;
    }

    std::optional<Error> Sub(T n) {
        current_ -= n;
        return std::nullopt;
    }

    std::optional<Error> Div(T n) {
        if constexpr (std::is_integral_v<T> || std::is_same_v<T, Rational>) {
            if (n == 0) {
                return Error("Division by zero");
            }
        }
        current_ /= n;
        return std::nullopt;
    }

    std::optional<Error> Mul(T n) {
        current_ *= n;
        return std::nullopt;
    }

    std::optional<Error> Pow(T n) {
        if (std::is_integral_v<T> || std::is_same_v<T, Rational>) {
            if ((current_ == 0) && (n == 0)) {
                return Error("Zero power to zero");
            }
        }
        if constexpr (std::is_same_v<T, Rational>) {
            if (n.GetDenominator() != 1) {
                return Error("Fractional power is not supported");
            }
        }
        if constexpr (std::is_integral_v<T>) {
            if (n < 0) {
                return Error("Integer negative power");
            }
        }
        if constexpr (std::is_same_v<T, Rational>) {
            current_ = ::Pow(current_, n);
        } else if constexpr (std::is_integral_v<T>) {
            current_ = IntegerPow(current_, n);
        } else {
            current_ = pow(current_, n);
        }
        return std::nullopt;
    }

    void Save() {
        remember_ = current_;
    }

    void Load() {
        if (remember_.has_value()) {
            current_ = remember_.value();
        }
    }

    bool GetHasMem() const {
        return remember_.has_value();
    }

    std::string GetNumberRepr() const {
        std::string result = std::to_string(current_);
        return result;
    }

private:
    T current_ = 0;
    std::optional<T> remember_ = std::nullopt;
};
