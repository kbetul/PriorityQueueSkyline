#include <iostream>
#include "ModifiedPriorityQueue.h"

using namespace std;

ModifiedPriorityQueue::ModifiedPriorityQueue(int labelSize)
{
    locationList.resize(labelSize+1);
    size = 0;
}

void ModifiedPriorityQueue::percolateUp(int idx){ //creating the heap
    int value = MPQarr[idx].value;
    int current = idx;
    int parent = (current-1)/2;

    for (; parent >= 0 && value > MPQarr[parent].value; current = parent, parent = (parent-1)/2){
        
        locationList[MPQarr[current].label] = parent;//swapping the indexes in location list first
        locationList[MPQarr[parent].label] = current;
        
        MPQobj tmp = MPQarr[parent];
        MPQarr[parent] = MPQarr[current]; //then swapping in the heap
        MPQarr[current] = tmp;

    }

}

void ModifiedPriorityQueue::insert(int value, int label)
{ //inserting in true index of heap
    MPQobj obj = MPQobj(value, label);
    MPQarr.push_back(obj);
    locationList[label] = size;
    percolateUp(size);
    size++;
}

int ModifiedPriorityQueue::remove(int label)
{ //removing the object with the given label and returning its value
    int cur = locationList[label];
    int leftChild = 2*cur+1;
    int rightChild = 2*cur+2;

    while (leftChild < size) {
        int maxChildIdx = leftChild;
        if (rightChild < size && MPQarr[rightChild].value > MPQarr[leftChild].value){
            maxChildIdx = rightChild;
        }

        locationList[MPQarr[cur].label] = maxChildIdx;
        locationList[MPQarr[maxChildIdx].label] = cur;
        MPQobj tmp = MPQarr[cur];
        MPQarr[cur] = MPQarr[maxChildIdx];
        MPQarr[maxChildIdx] = tmp;

        cur = maxChildIdx;
        leftChild = 2*cur+1;
        rightChild = 2*cur+2;
    }
    
    MPQobj lastElement = MPQarr[MPQarr.size()-1];
    MPQarr.pop_back();
    size--;
    
    return lastElement.value;
}
       
int ModifiedPriorityQueue::getMax()
{ //getting the max element which is the first element of the heap
    if(isEmpty()){
        return 0;
    }
    return MPQarr[0].value;

}

bool ModifiedPriorityQueue::isEmpty()
{
    return size == 0;
}

ModifiedPriorityQueue::~ModifiedPriorityQueue()
{

}