#pragma once

struct BudgetPerDay {
    double income = 0;
    double spendings = 0;

    friend BudgetPerDay operator*(BudgetPerDay lhs, double rhs) {
        lhs.income *= rhs;
        lhs.spendings *= rhs;
        return lhs;
    }

    friend BudgetPerDay operator+(BudgetPerDay lhs, const BudgetPerDay rhs) {
        lhs.income += rhs.income;
        lhs.spendings += rhs.spendings;
        return lhs;
    }

    BudgetPerDay Tax(double tax) {
        income *= tax;
        return *this;
    }
};
