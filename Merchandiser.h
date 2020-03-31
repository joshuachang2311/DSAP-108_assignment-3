//
// Created by Joshua2018 on 2020/3/31.
//

#include <string>
#include <set>

#ifndef ASSIGNMENT_3__MERCHANDISER_H_
#define ASSIGNMENT_3__MERCHANDISER_H_

class Merchandiser {
public:
    Merchandiser();
    void AddProduct(const std::string &product);
    void ReceiveRating(int rating);
    int GetNTransactions() const;
    double GetAverageRating() const;
    bool HasProduct(const std::string &product) const;

private:
    int n_stars_;
    int n_transactions_;
    std::set<std::string> products_{};
};

#endif //ASSIGNMENT_3__MERCHANDISER_H_
