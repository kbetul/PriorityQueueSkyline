#include "ModifiedPriorityQueue.h"
#include <iostream>
#include <fstream>
#include <vector>

struct Point
{ //struct for containing building x coordinate, id, and if its left or right x coordinate 
    int x, id;
    bool begin; // true if its left, false if its right
    Point(): x(), id(), begin() {}
    Point(int x, int id, bool begin): x(x), id(id), begin(begin) {}
};

struct Building
{ //struct for reading the file
    int x_left, y, x_right;
};

void swap(int a, int b, vector<Point> & arr){ //swapping a'th and b'th element
    Point tmp = arr[a];
    arr[a] = arr[b];
    arr[b] = tmp;
}

/***********From the cs300 lecture slides***********/
void perculatedown(vector<Point> &a, int n, int root)
{
   int largest = root; int leftChild = 2*root + 1; int rightChild = 2*root + 2;
  
   if (leftChild < n && a[leftChild].x > a[largest].x){
       //checks if left child is smaller than n, which means that it exists, and leftchild's x is bigger than root
       largest = leftChild; //left child is the new largest
    }
   if (rightChild < n && a[rightChild].x > a[largest].x) //same as the upper if statement
       largest = rightChild;
  
    if (largest != root){ //if largest is not the root
        swap(root, largest, a); //swap root with the largest
        perculatedown(a, n, largest); //recursively perculate down
      }
}

void heapsort(vector<Point> &a)
{   //sorting algorithm
    int size = int(a.size());
    for (int i = size / 2 - 1; i >= 0; i--)
        perculatedown(a, size, i);
  
    for (int i=size-1; i>=0; i--)
    {
        swap(0,i,a);
        perculatedown(a, i, 0);
    }
}
/***********End of cs300 lecture codes***********/

int main() {
    ifstream myfile;
    myfile.open("input.txt");

    int buildingCount, x_left, y ,x_right;
    myfile >> buildingCount; //reading the build count from the first line

    vector<Building> buildings(buildingCount+1);
    for(int i = 1; i <= buildingCount; i++ ){
        myfile >> x_left >> y >> x_right;
        buildings[i].x_left = x_left;
        buildings[i].y = y;
        buildings[i].x_right = x_right;
    } //buildings vector has left and right x coordinates and y coordinated
    
    vector<Point> points(2*buildingCount); //vector for storing points

    int j = 0;
    for (int i = 1; i <= buildingCount; i++) {
        points[j].x = buildings[i].x_left;
        points[j].begin = true;
        points[j].id = i;
        j++;
        points[j].x = buildings[i].x_right;
        points[j].begin = false;
        points[j].id = i;
        j++;
    }//changing the point vector accordingly
    
    heapsort(points); //sort the point vector
    
    
    ModifiedPriorityQueue MPQ = ModifiedPriorityQueue(buildingCount);
    int prev_y = 0;
    if(points[0].x!=0){ //if the first point's left x coord is not 0 print
        cout << "0 0" << endl;
    }
    for (int i = 0; i < 2*buildingCount; i++) {
        int cur_x = points[i].x;
        int cur_begin = points[i].begin;
        int cur_id = points[i].id;
        int deleted_val;

        if (cur_begin) { //if its the left x coord insert it into heap
            MPQ.insert(buildings[cur_id].y, cur_id);
        } else { //if its the right x coord remove it
            deleted_val = MPQ.remove(cur_id);
        }

        int cur_y = MPQ.getMax();
        if (i+1 < 2*buildingCount && prev_y != cur_y && cur_x!=points[i+1].x){ 
        //if its not the last element, their y's are not equal, and current x and next x is not equal
            cout << cur_x << " " << cur_y << endl;
            prev_y = cur_y;
        } else if (i == 2*buildingCount-1 && prev_y != cur_y) { //if its the last element
            cout << cur_x << " " << cur_y << endl;
        }
    }

    return 0;
}
