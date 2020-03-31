//
// Created by Joshua2018 on 2020/3/31.
//

#include "Customer.h"

Customer::Customer() {
    n_stars_ = 0;
    n_transactions_ = 0;
}

void Customer::ReceiveRating(int rating) {
    n_stars_ += rating;
    ++n_transactions_;
}

bool Customer::IsVIP() const {
    if (n_transactions_ >= min_vip_transactions_) {
        if (1.0 * n_stars_ / n_transactions_ > min_vip_average_rating_) {
            return true;
        }
    }

    return false;
}