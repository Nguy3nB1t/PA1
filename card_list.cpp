// card_list.cpp
// Author: Nguyen Nguyen 
// Implementation of the classes defined in card_list.h
#include "card_list.h"
#include <iostream>
#include <string>

using namespace std;

CardList::CardList() {
    root = nullptr;
}   

CardList::~CardList() {
    clear(root);
}

void CardList::clear(Node* node) {
    if (node != nullptr) {
        clear(node->left);
        clear(node->right);
        delete node;
    }
}

void CardList::add(const Card& card) {
    root = addHelper(root, card);
}

CardList::Node* CardList::addHelper(Node* node, const Card& card) {
    if (node == nullptr) {
        return new Node(card);
    }
    if (card < node->card) {
        node->left = addHelper(node->left, card);
    } else if (node->card < card) {
        node->right = addHelper(node->right, card);
    }
    return node;
}

void CardList::remove(const Card& card) {
    root = removeHelper(root, card);
}

CardList::Node* CardList::removeHelper(Node* node, const Card& card) {
    if (node == nullptr) {
        return nullptr;
    }
    if (card < node->card) {
        node->left = removeHelper(node->left, card);
    } else if (node->card < card) {
        node->right = removeHelper(node->right, card);
    } else {
        if (node->left == nullptr) {
            Node* temp = node->right;
            delete node;
            return temp;
        } else if (node->right == nullptr) {
            Node* temp = node->left;
            delete node;
            return temp;
        }
        Node* temp = findMin(node->right);
        node->card = temp->card;
        node->right = removeHelper(node->right, temp->card);
    }
    return node;
}

CardList::Node* CardList::findMin(Node* node) const {
    while (node->left != nullptr) {
        node = node->left;
    }
    return node;
}

bool CardList::contains(const Card& card) const {
    return containsHelper(root, card);
}

bool CardList::containsHelper(Node* node, const Card& card) const {
    if (node == nullptr) {
        return false;
    }
    if (card == node->card) {
        return true;
    }
    if (card < node->card) {
        return containsHelper(node->left, card);
    } else {
        return containsHelper(node->right, card);
    }
}

void CardList::print() const {
    print(root);
}

void CardList::print(Node* node) const {
    if (node != nullptr) {
        print(node->left);
        cout << node->card.toString() << endl;
        print(node->right);
    }
}

void CardList::getCards(vector<Card>& cards) const {
    getCardsHelper(root, cards);
}

void CardList::getCardsHelper(Node* node, vector<Card>& cards) const {
    if (node != nullptr) {
        getCardsHelper(node->left, cards);
        cards.push_back(node->card);
        getCardsHelper(node->right, cards);
    }
}           