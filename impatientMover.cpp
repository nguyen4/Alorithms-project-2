//====================================================================================================================//
//=11/09/2018                                                          COT 4400.001 Analysis of Algorithms - Group 14=//
//=impatientMover.cpp                                                            Alexander Alava Chonchol - U35432961=//
//=                                                                                    Christopher Khalil - U91696367=//
//=                                                                                            Tom Nguyen - U63542702=//
//=                                                                                                                  =//
//=                 This file contains the recursive dynamic solution to the impatient mover problem                 =//
//====================================================================================================================//

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <array>
#include <string>
#include <string.h>
#include <sstream>
#include <algorithm>

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

// Declaring and defining wrapper function for our recursive dynamic solution //
int impatientMoverWrapper(int boxes[], int arraySize)
{
  // Declaring our memoization data structure and initializing it with the sentinel value (0) //
  int count[arraySize];
  fill_n(count, arraySize, 0);

  // Calling the recursive function //
  impatientMover(boxes, arraySize, 0, count);

  // Returning the maximum element in the array box counts //
  return *max_element(count, count + arraySize);
}


// Declaring and defining main function //
int main()
{
  // Declaring and initialazing integer variables //
  int problemCount = 0;
  int problemSize = 0;

  // Declaring string variables //
  string newLine;
  string list;

  // Declaring input/output stream variables //
  ifstream inputFile;
  ofstream outputFile;

  // Opening input file and assigning it to the input stream variable //
  inputFile.open("input5.txt");

  // Opening input file and assigning it to the output stream variable //
  outputFile.open("output.txt");

  // Reading in the number of problems to be solved from the text file and converting it into an integer //
  getline(inputFile, newLine);
  problemCount = stoi(newLine);

  // Running through all problems to be solved //
  for (int i = 0; i < problemCount; i++)
  {
    // Reading in the size of the current problem to be solved and converting it into an integer //
    getline(inputFile, newLine);
    problemSize = stoi(newLine);

    // Declaring an array of size equal to the size of the current problem to be solved //
    int numberList[problemSize];

    // Reading in the values of the problem to be solved and converting it into an iss object //
    getline(inputFile, newLine);
    istringstream iss (newLine);

    // Running through all the values in the problem //
    for (int j = 0; j < problemSize; j++)
    {
      // Converting the values in the iss object into integers //
      int number;
      iss >> number;

      // Storing integers into their respective indexes in the array //
      numberList[j] = number;
    }

  // Writing result of the current problem into the output file //
  outputFile << impatientMoverWrapper(numberList, problemSize) << "\n";

  }

  // Closing input and output files //
  inputFile.close();
  outputFile.close();

  return 0;
}
