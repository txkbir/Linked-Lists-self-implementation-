#ifndef SEQUENCE_H
#define SEQUENCE_H

#include <string>
using ItemType = std::string;

class Sequence {
public:
    Sequence();
    ~Sequence();
    Sequence(const Sequence& other);
    Sequence& operator= (const Sequence& rhs);
    bool empty() const;
    int  size()  const;
    int  insert(int pos, const ItemType& value);
    int  insert(const ItemType& value);
    bool erase(int pos);
    int  remove(const ItemType& value);
    bool get(int pos, ItemType& value) const;
    bool set(int pos, const ItemType& value);
    int  find(const ItemType& value) const;
    void swap(Sequence& other);
    
private:
struct Node {
    ItemType val;
    Node* next;
    Node* prev;
};
    Node* head;
    int m_size;
};

 // non-member functions
int  subsequence(const Sequence& seq1, const Sequence& seq2);
void concatReverse(const Sequence& seq1, const Sequence& seq2, Sequence& result);

#endif
