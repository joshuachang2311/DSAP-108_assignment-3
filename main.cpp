#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <map>

#include "Customer.h"
#include "Merchandiser.h"

constexpr char ADD_CUSTOMER = 'C';
constexpr char ADD_MERCHANDISER = 'M';
constexpr char ADD_TRANSACTION = 'T';
constexpr char ADD_PRODUCT = 'A';
constexpr char SEARCH = 'S';

std::vector<std::string> SplitStringWith(const std::string &string, char character);

int StringToInt(const std::string &string);

template <typename ElementType>
void PrintVector(std::vector<ElementType> &vector);

int main() {
    std::string buffer_string;
    std::map<std::string, Customer> customers;
    std::map<std::string, Merchandiser> merchandisers;
    std::map<std::string, std::map<std::string, std::pair<std::string, int>>> transactions;

    while (std::getline(std::cin, buffer_string)) {
        std::vector<std::string> arguments = SplitStringWith(buffer_string, ' ');
        if (arguments[0][0] == ADD_CUSTOMER) {
            std::string customer_id = arguments[1];
            if (!customers.count(customer_id)) {
                customers[customer_id] = Customer();
            }
        }
        if (arguments[0][0] == ADD_MERCHANDISER) {
            std::string merchandiser_id = arguments[1];
            if (!merchandisers.count(merchandiser_id)) {
                merchandisers[merchandiser_id] = Merchandiser();
            }
        }
        if (arguments[0][0] == ADD_TRANSACTION) {
            std::string customer_id = arguments[1];
            std::string merchandiser_id = arguments[2];
            std::string product_id = arguments[3];
            int merchandiser_rating = StringToInt(arguments[4]);
            int customer_rating = StringToInt(arguments[5]);

            customers[customer_id].ReceiveRating(customer_rating);
            merchandisers[merchandiser_id].ReceiveRating(merchandiser_rating);
            if (!transactions.count(customer_id)) {
                transactions[customer_id]
                    = std::map<std::string, std::pair<std::string, int>>();
            }
            transactions[customer_id][merchandiser_id]
                = std::make_pair(product_id, merchandiser_rating);
            if (!transactions.count(merchandiser_id)) {
                transactions[merchandiser_id]
                    = std::map<std::string, std::pair<std::string, int>>();
            }
            transactions[merchandiser_id][customer_id]
                = std::make_pair(product_id, customer_rating);
        }
        if (arguments[0][0] == ADD_PRODUCT) {
            std::string merchandiser_id = arguments[1];
            std::string product_id = arguments[2];
            merchandisers[merchandiser_id].AddProduct(product_id);
        }
        if (arguments[0][0] == SEARCH) {
            std::string customer_id = arguments[1];
            std::string queried_product_id = arguments[2];
            std::vector<std::string> qualified_merchandisers;

            if (arguments.size() == 3) {
                int max_rating = 0;

                for (const auto &pair : transactions[customer_id]) {
                    std::string merchandiser_id = pair.first;
                    std::string product_id = pair.second.first;
                    int rating = pair.second.second;
                    if (product_id != queried_product_id) {
                        continue;
                    }

                    if (rating > max_rating) {
                        qualified_merchandisers.clear();
                        qualified_merchandisers.push_back(merchandiser_id);
                        max_rating = rating;
                    } else if (rating == max_rating) {
                        qualified_merchandisers.push_back(merchandiser_id);
                    }
                }

                PrintVector(qualified_merchandisers);
                std::cout << '\n';
            }
            if (arguments.size() == 5) {
                if (customers[customer_id].IsVIP()) {
                    int min_transactions = StringToInt(arguments[3]);
                    bool is_global = StringToInt(arguments[4]) == 1;

                    if (is_global) {
                        double max_rating = 0.0;

                        for (const auto &pair : merchandisers) {
                            std::string merchandiser_id = pair.first;
                            const Merchandiser &merchandiser = pair.second;
                            if (!merchandiser.HasProduct(queried_product_id) or
                                merchandiser.GetNTransactions() < min_transactions) {
                                continue;
                            }

                            if (merchandiser.GetAverageRating() > max_rating) {
                                qualified_merchandisers.clear();
                                qualified_merchandisers.push_back(merchandiser_id);
                                max_rating = merchandiser.GetAverageRating();
                            } else if (merchandiser.GetAverageRating() == max_rating) {
                                qualified_merchandisers.push_back(merchandiser_id);
                            }
                        }
                    } else {
                        int max_rating = 0;

                        for (const auto &pair : transactions[customer_id]) {
                            std::string merchandiser_id = pair.first;
                            std::string product_id = pair.second.first;
                            int rating = pair.second.second;
                            if (product_id != queried_product_id or
                                merchandisers[merchandiser_id].GetNTransactions() < min_transactions) {
                                continue;
                            }

                            if (rating > max_rating) {
                                qualified_merchandisers.clear();
                                qualified_merchandisers.push_back(merchandiser_id);
                                max_rating = rating;
                            } else if (rating == max_rating) {
                                qualified_merchandisers.push_back(merchandiser_id);
                            }
                        }
                    }

                    PrintVector(qualified_merchandisers);
                    std::cout << '\n';
                } else {
                    std::cout << "reject\n";
                }
            }
        }
    }

    return 0;
}

// Code below derived from:
// https://stackoverflow.com/questions/10058606/splitting-a-string-by-a-character/10058756
std::vector<std::string> SplitStringWith(const std::string &string, char character) {
    std::stringstream string_stream(string);
    std::string buffer_string;
    std::vector<std::string> splitted_strings;
    while (std::getline(string_stream, buffer_string, character)) {
        splitted_strings.push_back(buffer_string);
    }

    return splitted_strings;
}

// Code below derived from:
// https://www.geeksforgeeks.org/converting-strings-numbers-cc/
int StringToInt(const std::string &string) {
    std::stringstream string_stream(string);
    int integer;
    string_stream >> integer;

    return integer;
}

template <typename ElementType>
void PrintVector(std::vector<ElementType> &vector) {
    if (vector.empty()) {
        return;
    }
    std::cout << vector[0];
    for (int i = 1; i < vector.size(); ++i) {
        std::cout << ' ' << vector[i];
    }
}
