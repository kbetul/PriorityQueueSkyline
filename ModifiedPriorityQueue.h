#ifndef ModifiedPriorityQueue_h
#define ModifiedPriorityQueue_h

#include <vector>

using namespace std;

struct MPQobj{
    int value;
    int label;
    MPQobj(int value, int label): value(value), label(label) {}
};

class ModifiedPriorityQueue
{
    private:
        int size;
        vector<MPQobj> MPQarr;
        vector<int> locationList;
        void percolateUp(int x);
    public:
        ModifiedPriorityQueue(int labelSize); //constructor
        ~ModifiedPriorityQueue(); //destructor
        void insert(int value, int label);
        int remove(int label); //This method removes the value with this label and returns it
        int getMax();
        bool isEmpty(); //check if it is empty
};


#endif