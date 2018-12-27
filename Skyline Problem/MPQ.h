#include <vector>
#include <iostream>

using namespace std;

class MPQ 
{
private:
	// Construct the initial empty vector
	vector<int> prqueue;

	// return the parent of given 
	int parent(int i) 
	{ 
		return (i - 1) / 2; 
	}

	// return the left child of the prqueue[i]
	int left_child(int i) 
	{ 
		return (2 * i + 1); 
	}

	// return the right child of prqueue[i]
	int right_child(int i) 
	{ 
		return (2 * i + 2); 
	}

	// this function makes sure that the heap structure is correct by percolating up
	void percolateDown(int value)
	{
		// get the left and right child values of index "value"
		int l = left_child(value);
		int r = right_child(value);

		int greatest = value; 

		// compare it with the values and get the greatest
		if (l < size() && prqueue[l] > prqueue[value])
			greatest = l;

		if (r < size() && prqueue[r] > prqueue[greatest])
			greatest = r;

		// swap with the greatest and call percolateDown
		if (greatest != value) {
			swap(prqueue[value], prqueue[greatest]);
			percolateDown(greatest);
		}
	}

	// percolateUp to satisfy the heap property
	void percolateUp(int value)
	{
		// check if heap property violated
		if (value && prqueue[parent(value)] < prqueue[value]) 
		{
			// make a swap operation if the property is violated
			swap(prqueue[value], prqueue[parent(value)]);

			// make a percolateUp call on parent 
			percolateUp(parent(value));
		}
	}

public:
	unsigned int size()// this function returns the current size of the priority queue
	{
		return prqueue.size();
	}
	// this function checks if the priority queue is empty
	bool isEmpty()
	{
		if(prqueue.size()==0)
			return true;
		return false;
	}
	// insert the value given as parameter to the priority queue
	void insert(int value)
	{
		// insert at the end
		prqueue.push_back(value);

		// obtain the index and percolate it up
		int temp = size() - 1;
		percolateUp(temp);
	}
	~MPQ()
	{
		// vector will be deleted automatically since it is created as a static member
	}
	// this function removes the integer given as parameter from the priority queue 
	void remove(int height)
	{	
		auto it = std::find(this->prqueue.begin(), this->prqueue.end(), height);
		if (it != this->prqueue.end())
		{
			this->prqueue.erase(it);
			std::make_heap(this->prqueue.begin(), this->prqueue.end());
		}
	}

	// this functions returns the maximum element in priority queue
	int GetMax()
	{
		return prqueue[0];	
	}
};