#pragma once

#include "entities.h"
#include "summing_segment_tree.h"

#include <cstdint>
#include <cmath>
#include <utility>
#include <vector>

struct BulkMoneyAdder {
    BudgetPerDay delta = {};
};

struct BulkTaxApplier {
    BulkTaxApplier() {}

    BulkTaxApplier(int tax) {
        factors.push_back(1 - (0.01 * tax));
    }

    double ComputeFactor() const {
        // static const double factor = 0.87;
        // return std::pow(factor, count);
        double res = 1;
        for (auto f : factors) {
            res *= f;
        }
        return res;
    }

    // int count = 0;
    std::vector<double> factors;
};

class BulkLinearUpdater {
public:
    BulkLinearUpdater() = default;

    BulkLinearUpdater(const BulkMoneyAdder& add)
        : add_(add) {
    }

    BulkLinearUpdater(const BulkTaxApplier& tax)
        : tax_(tax) {
    }

    void CombineWith(const BulkLinearUpdater& other) {
        tax_.factors.reserve(tax_.factors.size() + other.tax_.factors.size());
        tax_.factors.insert(tax_.factors.end(), other.tax_.factors.begin(), other.tax_.factors.end());
        // tax_.count += other.tax_.count;
        // add_.delta = add_.delta * other.tax_.ComputeFactor() + other.add_.delta;
        add_.delta = add_.delta.Tax(other.tax_.ComputeFactor()) + other.add_.delta;
    }

    BudgetPerDay Collapse(BudgetPerDay origin, IndexSegment segment) const {
        // return origin * tax_.ComputeFactor() + add_.delta * static_cast<double>(segment.length());
        return origin.Tax(tax_.ComputeFactor()) + add_.delta * static_cast<double>(segment.length());
    }

private:
    // apply tax first, then add
    BulkTaxApplier tax_;
    BulkMoneyAdder add_;
};
