// card.h
// Author: Nguyen Nguyen 
// All class declarations related to defining a single card go here

#ifndef CARD_H
#define CARD_H

#include <string>

class Card {
    public:
        Card(const std::string& suit, const std::string& rank);
        std::string toString() const;
        bool operator<(const Card& other) const;
        bool operator==(const Card& other) const;
    private:
        std::string suit;
        std::string rank;
};

#endif
