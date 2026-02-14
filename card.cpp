// card.cpp
// Author: Nguyen Nguyen 
// Implementation of the classes defined in card.h

#include "card.h"
#include <iostream>
#include <string>

using namespace std;

Card::Card(const string& suit, const string& rank) {
    this->suit = suit;
    this->rank = rank;
}

string Card::toString() const {
    return suit + " " + rank;
}

bool Card::operator<(const Card& other) const {
    if (suit != other.suit) {
        // Suit order: clubs < diamonds < spades < hearts
        string suitOrder = "cdsh";
        size_t thisPos = suitOrder.find(suit);
        size_t otherPos = suitOrder.find(other.suit);
        if (thisPos == string::npos) thisPos = 999;
        if (otherPos == string::npos) otherPos = 999;
        return thisPos < otherPos;
    }
    // If suits are equal, compare ranks
    // Ace is treated as low (before 2)
    string rankOrder = "a2345678910jqk";
    size_t thisPos = rankOrder.find(rank);
    size_t otherPos = rankOrder.find(other.rank);
    if (thisPos == string::npos) thisPos = 999;
    if (otherPos == string::npos) otherPos = 999;
    return thisPos < otherPos;
}

bool Card::operator==(const Card& other) const {
    return suit == other.suit && rank == other.rank;
}                   