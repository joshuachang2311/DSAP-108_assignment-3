//
// Created by Joshua2018 on 2020/3/31.
//

#include <string>
#include "Merchandiser.h"

Merchandiser::Merchandiser() {
    n_stars_ = 0;
    n_transactions_ = 0;
}

void Merchandiser::AddProduct(const std::string &product) {
    products_.insert(product);
}

void Merchandiser::ReceiveRating(int rating) {
    n_stars_ += rating;
    ++n_transactions_;
}

int Merchandiser::GetNTransactions() const {
    return n_transactions_;
}

double Merchandiser::GetAverageRating() const {
    if (n_transactions_ == 0) {
        return 0.0;
    } else {
        return 1.0 * n_stars_ / n_transactions_;
    }
}

bool Merchandiser::HasProduct(const std::string &product) const {
    return products_.count(product);
}
