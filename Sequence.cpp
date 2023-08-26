//
//  Sequence.cpp
//  cs32proj2
//
//  Created by Takbir Rahman on 4/19/23.
//

#include "Sequence.h"

 // create a dummy node when constructing a Sequence
Sequence::Sequence() : m_size(0) {
    head = new Node;
    head->next = head;
    head->prev = head;
}

Sequence::~Sequence() {
    Node* p = head->next;
    while (p != head) { // delete all Nodes first (if there are any)
        Node* nextNode = p->next;   // copy p->next so it can still be accessed after deleting p
        delete p;
        p = nextNode;   // next iteration
    }
    delete head;
}

Sequence::Sequence(const Sequence& other)
  : m_size(other.m_size) {
    if (this == &other)
        return;
     // this is still a constructor to create a new Sequence; a dummy node still needs to be init'd
    head = new Node;
    head->next = head;
    head->prev = head;
      // iterate through other's Nodes and append to *this Sequence
    for (Node* p = other.head->next; p != other.head; p = p->next) {
        Node* newNode = new Node;
        newNode->val = p->val;
        Node* LastNode = head->prev;    // rearrange pointers
        LastNode->next = newNode;
        newNode->prev = LastNode;
        newNode->next = head;
        head->prev = newNode;
    }
}

Sequence& Sequence::operator= (const Sequence& rhs) {
    if (this == &rhs)
        return *this;
    
    Node* p = head->next;
    while (p != head) {
        Node* nextNode = p->next;   // make a copy of p->next for ability to access it after deleting p
        delete p;
        p = nextNode;   // iterate to next instance
    }
    head->next = head;
    head->prev = head;
    for (Node* q = rhs.head->next; q != rhs.head; q = q->next) {
        Node* newNode = new Node;
        newNode->val = q->val;
        Node* LastNode = head->prev;    // pointers need to be arranged
        LastNode->next = newNode;
        newNode->prev = LastNode;
        newNode->next = head;
        head->prev = newNode;
    }
    m_size = rhs.m_size;
    return *this;
}

bool Sequence::empty() const { return (m_size == 0); }

int Sequence::size() const { return m_size; }

int Sequence::insert(int pos, const ItemType& value) {
    if (pos < 0  ||  pos > m_size)
        return -1;
    
    Node* newNode = new Node;
    newNode->val = value;
    m_size++;
     // counter b/c linked lists don't have a way to check position
    int position = -1;
    Node* p;
    for (p = head->next; p != head; p = p->next) {
        position++;
        if (position == pos) break;
        else if (pos == m_size - 1) {   // check if item being inserted would go at end of list
            p = head->prev;
            newNode->next = head;
            head->prev = newNode;
            p->next = newNode;
            newNode->prev = p;
            return pos;
        }
    }
    newNode->next = p;
    newNode->prev = p->prev;    // rearrange pointers to accomodate new Node
    p->prev->next = newNode;
    p->prev = newNode;
    return pos;
}

int Sequence::insert(const ItemType& value) {
    int pos = 0;
    Node* newNode = new Node;
    newNode->val = value;
    m_size++;
    for (Node* p = head; p->next != head; p = p->next) {
        pos++;
        if (newNode->val <= p->next->val) { // sort by ASCII values
            Node* q = p->next;
            newNode->next = q;
            q->prev = newNode;
            newNode->prev = p;
            p->next = newNode;
            return (pos - 1);
        }     // skip to the end if the new Node is the largest value in the list
        else if (newNode->val >= head->prev->val) break;
    }
    Node* LastNode = head->prev;
    LastNode->next = newNode;   // rearrange pointers to accomodate new Node
    newNode->prev = LastNode;
    newNode->next = head;
    head->prev = newNode;
    pos = m_size - 1;
    return pos;
}

bool Sequence::erase(int pos) {
    if (m_size == 0  ||  pos < 0  ||  pos >= m_size)
        return false;
        
    int position = 0;
    Node* p;
    for (p = head->next; p != head && position < pos; p = p->next)
        position++; // break when position is no longer less than passed in param
    
    Node* previous = p->prev;   // rearrange pointers
    Node* nextNode = p->next;
    previous->next = nextNode;
    nextNode->prev = previous;
    delete p;
    m_size--;
    return true;
}

int Sequence::remove(const ItemType& value) {
    int numRemove = 0;
    if (find(value) == -1)  // check if the value even exists in the list first
        return numRemove;

    int pos = -1;
    Node* q = head->next;
    while (q != head) {
        pos++;
        if (q->val == value) {
            Node* nextNode = q->next;   // make copy of q->next for access after erasing q
            erase(pos);
            q = nextNode;
            pos--;
            numRemove++;
            continue;   // go straight back to loop because q was already assigned to q->next
        }
        q = q->next;
    }
    return numRemove;
}
                   // modify and "return" value
bool Sequence::get(int pos, ItemType& value) const {
    if (pos < 0  ||  pos >= m_size)
        return false;
    
    int position = -1;
    Node* p;
    for (p = head->next; p != head; p = p->next) {
        position++;
        if (position == pos) {
            value = p->val;
            return true;
        }
    }
    return false;
}
         // change list's position with passed-in value
bool Sequence::set(int pos, const ItemType& value) {
    if (pos < 0  ||  pos >= m_size)
        return false;
    
    int position = -1;
    Node* p;
    for (p = head->next; p != head; p = p->next) {
        position++;
        if (position == pos) {
            p->val = value;
            return true;
        }
    }
    return false;
}

int Sequence::find(const ItemType& value) const {
    if (m_size == 0)
        return -1;
    
    int pos = -1;
    Node* p;
    for (p = head->next; p != head; p = p->next) {
        pos++;
        if (p->val == value)    // traverse thru list in hopes of finding value
            return pos;
    }
    return -1;
}

void Sequence::swap(Sequence& other) {
    Sequence copy = *this;
    *this = other;
    other = copy;
}

int subsequence(const Sequence& seq1, const Sequence& seq2) {
    ItemType value1;
    seq2.get(0, value1);         // init x to seq2's first item and see if x is in seq1
    if (seq1.find(value1) == -1  ||  seq2.size() > seq1.size()  ||  seq2.empty())
        return -1;
    
    int seq1size = seq1.size();
    int seq2size = seq2.size();
    ItemType value2;
    int i, k, pos;
        // seq2 must always be within the bounds of seq1 for it to be a potential subsequence
    for (i = 0; i <= seq1size - seq2size; i++) {
        int counter = 0;
        for (k = 0; k < seq2size; k++) {
            seq1.get(i, value1);
            seq2.get(k, value2);
            if (value1 != value2) {
                k = 0;  // force reset k
                break;
            } // else continue with the inner for loop b/c value1 == value2
            pos = i - k;
            counter++;
            if (counter == seq2size)
                return pos;
            i++;
        }
    }
    return -1;
}

void concatReverse(const Sequence& seq1, const Sequence& seq2, Sequence& result) {
    int s1size = seq1.size();
    int s2size = seq2.size();
    if (s1size + s2size == 0) {
        for (int i = 0; i < result.size(); i++)
            result.erase(i);
        return;
    } else if (s1size == 0) {
        result = seq2;
        return;
    } else if (s2size == 0) {
        result = seq1;
        return;
    }
    Sequence resultCopy = result; // in the event that result is a reference to seq1 or seq2, copy it
    int newResultSize = s1size + s2size;
    ItemType x;
    seq1.get(0, x); // this line's only purpose is to init x
     // erase everything in the copy of result
    for (int i = 0; i < resultCopy.size(); i++)
        resultCopy.erase(i);
     // insert new Nodes into the copy of result
    for (int k = 0; k < newResultSize; k++)
        resultCopy.insert(k, x);
     // get every value of seq1 (starting from end). set each value to each resultCopy element
    for (int i = 0; i < s1size; i++) {
        seq1.get(s1size - (i + 1), x);
        resultCopy.set(i, x);
    } // get every value of seq2 (starting from end). set each value to each resultCopy element
    for (int k = 0; k < s2size; k++) {
        seq2.get(s2size - (k + 1), x);
        resultCopy.set(k + s1size, x);
    }
    result = resultCopy;    // copy resultCopy into result
    return;
}
