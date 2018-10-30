#include <iostream>
#include <array>

using namespace std;

// Declaring and defining the function that will check if there is a smaller weight to the right of the current index //
bool isThereSmallerRight(int boxes[], int arraySize, int index)
{
  // Setting the boolean flag to false initially //
  bool flag = false;

  // Running through all the elements in the array to the right of our current index //
  for (int i = index + 1; i < arraySize; i++)
  {
    // Checking if the current element is smaller than the one at our original index //
    if (boxes[index] >= boxes[i])
    {
      // Setting flag to true and breaking out of the loop //
      flag = true;
      break;
    }
  }

  // Returning wether there is a smaller value to the right or not //
  return flag;
}

// Declaring and defining the memoized version of the recursive algortihm that will solve this problem //
int impatientMover(int boxes[], int arraySize, int index, int count[])
{
  // Declaring, defining and resetting the current maximum value for each iteration of our recursion //
  int currentMax = 0;

  // Checking if the current index is the last one in the array - Base case //
  if (index == arraySize - 1)
  {
    // Storing 1 into the respective index in count array and returning such value //
    count[index] = 1;
    return count[index];
  }
  else
  {
    // Reaching the end of the list in order to iterate backwards in our recursion //
    impatientMover(boxes, arraySize, index + 1, count);
  }

  // Checking if the value at the current index has already been set //
  if (count[index] != 0)
  {
    // Returning the value previously calculated //
    return count[index];
  }
  // Checking if there are no smaller or equal values to the right - Base case //
  else if (!isThereSmallerRight(boxes, arraySize, index))
  {
    // Storing 1 into the respective index in count array and returning such value //
    count[index] = 1;
    return count[index];
  }
  else
  {
      // Running through all the elements in the array to the right of our current index //
      for (int i = index + 1; i < arraySize; i++)
      {
        // Checking if the current value is less that the initial and if its respective count is greater that the max //
        if (boxes[index] >= boxes[i] && count[i] > currentMax)
        {
            // Establishing the respective count as the current max //
            currentMax = count[i];
        }
      }

      // Storing the count of boxes respective to the current index //
      count[index] = 1 + currentMax;
  }

  return count[index];
}


// Declaring and defining main function //
int main()
{
  int arr1[20] = {38,35,45,39,23,16,26,28,20,5,8,17,12,10,13,42,6,34,33,37};
  int arr2[20] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

  cout << impatientMover(arr1, 20, 0, arr2);

  return 0;
}
