// card_list.h
// Author: Nguyen Nguyen 
// All class declarations related to defining a BST that represents a player's hand

#ifndef CARD_LIST_H
#define CARD_LIST_H

#include "card.h"
#include <vector>

class CardList {
    private:
        struct Node {
            Card card;
            Node* left;
            Node* right;
            Node(const Card& c) : card(c), left(nullptr), right(nullptr) {}
        };
        Node* root;
        void clear(Node* node);
        void print(Node* node) const;
        Node* addHelper(Node* node, const Card& card);
        Node* removeHelper(Node* node, const Card& card);
        Node* findMin(Node* node) const;
        bool containsHelper(Node* node, const Card& card) const;
        void getCardsHelper(Node* node, std::vector<Card>& cards) const;
    public:
        CardList();
        ~CardList();
        void add(const Card& card);
        void remove(const Card& card);
        bool contains(const Card& card) const;
        void print() const;
        void getCards(std::vector<Card>& cards) const;
};

#endif
