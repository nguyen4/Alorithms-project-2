#include <iostream>
#include <array>

using namespace std;

bool isThereSmallerRight(int boxes[], int arraySize, int index)
{
  bool flag = false;

  for (int i = index + 1; i < arraySize; i++)
  {
    if (boxes[index] >= boxes[i])
    {
      flag = true;
      break;
    }
  }

  return flag;
}

int impatientMover(int boxes[], int arraySize, int index, int count[])
{
  int currentMax = 0;

  if (index == arraySize - 1)
  {
    count[index] = 1;
    return count[index];
  }
  else
  {
    impatientMover(boxes, arraySize, index + 1, count);
  }

  if (!isThereSmallerRight(boxes, arraySize, index))
  {
    count[index] = 1;
    return count[index];
  }
  else
  {
      for (int i = index + 1; i < arraySize; i++)
      {
        if (boxes[index] >= boxes[i] && count[i] > currentMax)
        {
            currentMax = count[i];
        }
      }

      count[index] = 1 + currentMax;
  }

  return count[index];
}

int main()
{
  int arr1[20] = {38,35,45,39,23,16,26,28,20,5,8,17,12,10,13,42,6,34,33,37};
  int arr2[20] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

  cout << impatientMover(arr1, 20, 0, arr2);

  return 0;
}
