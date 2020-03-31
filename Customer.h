//
// Created by Joshua2018 on 2020/3/31.
//

#ifndef ASSIGNMENT_3__CUSTOMER_H_
#define ASSIGNMENT_3__CUSTOMER_H_

class Customer {
public:
    Customer();
    void ReceiveRating(int rating);
    bool IsVIP() const;

private:
    static constexpr int min_vip_transactions_ = 3;
    static constexpr double min_vip_average_rating_ = 3.0;
    int n_stars_;
    int n_transactions_;
};

#endif //ASSIGNMENT_3__CUSTOMER_H_
