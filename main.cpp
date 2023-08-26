#include "Sequence.h"
#include <string>
#include <iostream>
#include <cassert>

void test() {
     // default constructor
    Sequence s;
    assert(s.empty());  // list should be empty
    assert(s.size() == 0);
    assert(s.remove("paratha") == 0);   // shouldn't be able to remove anything
    assert(s.insert(0, "lavash") == 0);
    assert(s.insert(0, "tortilla") == 0);
    assert(s.insert(1, "roti") == 1);
    assert(s.insert(1, "bread") == 1);
    assert(s.size() == 4);  // make sure all 4 items were inserted
    ItemType x = "injera";
    assert(s.get(0, x)  &&  x == "tortilla");
    assert(s.get(1, x)  &&  x == "bread");
    assert(s.get(2, x)  &&  x == "roti");
    assert(s.get(3, x)  &&  x == "lavash"); // see if all items were rearranged as should be
    for (int i = 0; i < s.size(); i++) {
        s.get(i, x);
        // std::cerr << x << std::endl;    // to make sure everything sorted properly
    }

    Sequence t;
    t.insert("how");
    t.insert("will");
    t.insert("this");
    t.insert("list");
    t.insert("be");
    t.insert("sorted");
    for (int k = 0; k < 3; k++)
        t.insert("?");
    for (int i = 0; i < t.size(); i++) {
        t.get(i, x);
        std::cerr << x << std::endl;    // make sure everything sorted by ASCII standards
    }
    assert(t.size() == 9);
    t.remove("?");
    std::cerr << "=================" << std::endl;
    for (int i = 0; i < t.size(); i++) {
        t.get(i, x);
        std::cerr << x << std::endl;
    }
    assert(t.size() == 9 - 3);  // make sure all the ? were removed
    t.erase(0);
    assert(t.size() == 6 - 1);  // make sure one spot was erased
    assert(t.get(0, x)  &&  x == "how"); // make sure "be" was erased
    assert(t.find("sorted") == 2);  // is "sorted" in the right position?

    Sequence z = t;
    assert(z.size() == t.size());
    ItemType y;
    for (int i = 0; i < z.size(); i++) {
        z.get(i, x);
        t.get(i, y);
        assert(x == y); // make sure copy constructor works properly
    }

    t = s;
    assert(t.size() == s.size());
    for (int i = 0; i < t.size(); i++) {
        t.get(i, x);
        s.get(i, y);
        assert(x == y); // make sure = operator was properly overloaded
    }
    Sequence SwapMe;
    SwapMe.insert(0, "im");
    SwapMe.insert(1, "ready");
    SwapMe.insert(2, "to");
    SwapMe.insert(3, "be");
    SwapMe.insert(4, "swapped!");
    t.swap(SwapMe); // swap t with new Sequence
    std::cerr << "==============" << std::endl;
    for (int i = 0; i < t.size(); i++) {
        t.get(i, x);
        std::cerr << x << std::endl; // print out contents of t to make sure swap works
    }
    int sizeswap = SwapMe.size();
    std::cerr << sizeswap << std::endl;
    t.set(4, "changed!");
    assert(t.get(4, x)  &&  x == "changed!");   // make sure set works properly
    assert(!t.erase(9));    // can't erase anything greater than the size
    assert(t.remove("") == 0);  // you shouldn't be able to remove the empty string from this list

    Sequence sub1;
    Sequence sub2;
    sub1.insert(0, "is");
    sub1.insert(1, "there");
    sub1.insert(2, "a");
    sub1.insert(3, "subsequence");
    sub1.insert(4, "to");
    sub1.insert(5, "this?");

    sub2.insert(0, "there");
    sub2.insert(1, "a");
    sub2.insert(2, "subsequence");
    assert(subsequence(sub1, sub2) == 1);   // see if subsequence works
    Sequence Yes = sub2;
    Yes.insert(0, "no");
    Yes.insert(1, "isnt");
    assert(subsequence(sub1, Yes) == -1);   // there shouldn't be a subsequence
    assert(subsequence(Yes, Yes) == 0);     // a sequence can be a subsequence of itself
    Sequence oneword;
    oneword.insert("this?");
    assert(subsequence(sub1, oneword) == 5);    // a one word subsequence which is at the end of seq1

    Sequence newSeq1;
    Sequence newSeq2;
    Sequence seqResult;

    newSeq1.insert(0, "6");
    newSeq1.insert(1, "7");
    newSeq1.insert(2, "9");
    assert (newSeq1.size() == 3);
    newSeq2.insert(0, "1");
    newSeq2.insert(1, "7");
    newSeq2.insert(2, "3");
    newSeq2.insert(3, "8");
    assert (newSeq2.size() == 4);

    concatReverse(newSeq1, newSeq2, seqResult);
    assert (seqResult.size() == 7);
    std::cerr << "=================" << std::endl;
    for (int i = 0; i < seqResult.size(); i++) {
        seqResult.get(i, x);
        std::cerr << x << std::endl;    // make sure seq1 and seq2 were reverse-concatenated properly
    }
}

int main()
{
    test();
    std::cerr << std::endl << "=================" << std::endl;
    std::cerr << "Passed all tests!" << std::endl << std::endl;;
    Sequence s;
}

