#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include "MPQ.h"

using namespace std;

enum side {START, END};// enum type to store the side of the building
struct building {
	int x; // x coord of the building
	side s; // start or end of the building
	int h; // height of the building
};


// sorts the queries in order to make our job easier
bool sortHeight(const building & a, const  building & b)
{

	if(a.x == b.x)
	{
		if(a.s==b.s)
		{
			if(a.s==START)
			{
				return(a.h > b.h);
			}
			else
			{
				return (a.h < b.h);
			}
		}
		else
		{
			return (a.s == START);
		}
	}
	else
	{
		return (a.x<b.x);
	}

}

int main(){

	vector <building> start;
	vector <building> end;
	vector <building> finalArr;
	MPQ mpq;
	
	ifstream in;
	in.open("input.txt");

	int N,x1,h,x2;

	in >> N;

	while (N--)
	{
		in>>x1 >> h >> x2;
		building left;
		left.x=x1;
		left.h=h;
		left.s=START;
		start.push_back(left);
		building right;
		right.x=x2;
		right.h=h;
		right.s=END;
		end.push_back(right);
	}

	finalArr.reserve( start.size() + end.size() ); // preallocate memory
	finalArr.insert( finalArr.end(), start.begin(), start.end() );// merge the vectors
	finalArr.insert( finalArr.end(), end.begin(), end.end() );//merge the vectors
	std::sort(finalArr.begin(),finalArr.end(),sortHeight);// sort the final inputs

	int temp;

	mpq.insert(0);//insert 0 to the priority queue to have initial height
	if(finalArr[0].x!=0)// if the starting point of the building is not 0,0 , then print 0,0 as beginning
	{
	cout << 0<< " " << 0 << endl;
	}
	for(int i=0; i<finalArr.size(); i++)
	{
		if(finalArr[i].s==START)
		{
			temp=mpq.GetMax();//get the current max
			mpq.insert(finalArr[i].h);
			if(mpq.GetMax()!=temp)// if the new max after insertion is not the same then print it 
			{
			cout << finalArr[i].x << " " << mpq.GetMax() << endl;
			}
		}
		else if(finalArr[i].s==END)
		{
			temp= mpq.GetMax();// get the current max
			mpq.remove(finalArr[i].h);
			if(mpq.GetMax()!=temp)// if the new max after the remove operation is not the same then print it
			{
				cout << finalArr[i].x << " " << mpq.GetMax()<< endl;
			}
			
		}
	}
	mpq.~MPQ();//destructor (see explanation on definition of destructor)

	return 0;
}