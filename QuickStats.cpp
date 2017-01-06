/* QuickStats.cpp - Library for quick descriptive statistics of an array samples[] of size m
 *  Created by David Dubins, January 10th, 2016.
 *  Updated by Joshua Baldwin, 01/05/2017.
 *  Version 1.2.0
 *  Released into the public domain.
 *  See Readme.txt for additional documentation.
 *  Requires Arduino 1.6.6 or greater.
 */

#include "Arduino.h"
#include "QuickStats.h"
#include <math.h>

QuickStats::QuickStats()
{
  // Nothing to construct
}

QuickStats::~QuickStats()
{
  // Nothing to destruct
}

float QuickStats::average(float samples[], int m)
{
  float total1 = 0.0;
  for(int i = 0; i < m; i++)
  {
    total1 = total1+samples[i];
  }
  return total1/(float)m;
}

float QuickStats::g_average(float samples[], int m)
{
  float total1 = 0.0;
  for(int i = 0; i < m; i++)
  {
    total1 = total1+log(samples[i]);
  }
  return exp(total1/(float)m);
}

float QuickStats::minimum(float samples[], int m)
{
  float sorted[m];    //Define and initialize sorted array
  for(int i = 0; i < m; i++)
  {
    sorted[i] = samples[i];
  }
  //bubbleSort(sorted, m);   // Sort the values
  mergeSort(sorted, 0, m);   // Sort the values
  return(sorted[0]);  // first element is the minimum
}

float QuickStats::maximum(float samples[], int m)
{
  float sorted[m];    //Define and initialize sorted array
  for(int i = 0; i < m; i++)
  {
    sorted[i] = samples[i];
  }
  //bubbleSort(sorted,m);   // Sort the values
  mergeSort(sorted, 0, m);   // Sort the values
  return(sorted[m - 1]);    // last element is the maximum
}

float QuickStats::stdev(float samples[], int m)
{
  float avg = 0.0;
  float total2 = 0.0;
  avg = average(samples,m);
  for(int i = 0; i < m; i++)
  {
    total2 = total2 + pow(samples[i] - avg,2);
  }
  return sqrt(total2/((float)m-1.0));
}

float QuickStats::stderror(float samples[], int m)
{
  float temp1 = 0.0;
  temp1 = stdev(samples, m);
  return (temp1 / sqrt((float)m));
}

float QuickStats::CV(float samples[], int m)  //Coefficient of variation (%RSD, or relative stdev)
{
  float avg = 0.0;
  float sd = 0.0;
  avg = average(samples, m);
  sd = stdev(samples, m);
  return 100.0*sd/avg;
}

void QuickStats::bubbleSort(float A[], int len) {
  unsigned long newn;
  unsigned long n = len;
  float temp = 0.0;
  do
  {
    newn = 1;
    for(int p = 1; p < len; p++)
    {
      if(A[p-1] > A[p])
      {
        temp = A[p]; // swap places in array
        A[p] = A[p - 1];
        A[p - 1] = temp;
        newn = p;
      }
    }
    n = newn;
  }
  while(n > 1);
}

float QuickStats::fabs(float sample) // calculate absolute value
{
  if(sample < 0.f)
  {
    return -sample;
  }
  else
  {
    return sample;
  }
}

float QuickStats::median(float samples[], int m) //calculate the median
{
  //First bubble sort the values: https://en.wikipedia.org/wiki/Bubble_sort
  float sorted[m];    //Define and initialize sorted array.
  //float temp = 0.0;       //Temporary float for swapping elements
  for(int i = 0; i < m; i++)
  {
    sorted[i] = samples[i];
  }
  //bubbleSort(sorted, m);   // Sort the values
  mergeSort(sorted, 0, m);
  if (bitRead(m,0) == 1)  //If the last bit of a number is 1, it's odd. This is equivalent to "TRUE". Also use if m%2! = 0.
  {
    return sorted[m/2];  //If the number of data points is odd, return middle number.
  }
  else
  {
    return (sorted[(m/2)-1]+sorted[m/2])/2;  //If the number of data points is even, return avg of the middle two numbers.
  }
}

float QuickStats::mode(float samples[], int m, float epsilon) //calculate the mode.
//epsilon is the tolerance for two measurements to be equivalent.
{
  //First bubble sort the values: https://en.wikipedia.org/wiki/Bubble_sort
  float sorted[m];    //Temporary array to sort values.
  //float temp = 0;       //Temporary float for swapping elements
  float unique[m];    //Temporary array to store unique values
  int uniquect[m];  //Temporary array to store unique counts
  for(int i = 0; i < m; i++)
  {
    sorted[i] = samples[i];
  }
  //bubbleSort(sorted, m);   // Sort the values
  mergeSort(sorted, 0, m);      // Sort the array
  // Now count the number of times each unique number appears in the sorted array.
  unique[0] = sorted[0];
  uniquect[0] = 1;
  int p = 0;  // counter for # unique numbers
  int maxp = 0;
  int maxidx = 0;
  for(int i = 1;  i < m;  i++)
  {
    if(fabs(sorted[i] - sorted[i - 1]) < epsilon)
    {
      uniquect[p]++;   //if same number again, add to count
      if(uniquect[p] > maxp)
      {
        maxp = uniquect[p];
        maxidx = p;
      }
    }
    else
    {
      p++;
      unique[p] = sorted[i];
      uniquect[p] = 1;
    }
  }
  if (maxp > 1)
  {
    return unique[maxidx];  //If there is more than one mode, return the lowest one.
  }
  else
  {
    return 0.0;  //If there is no mode, return a zero.
  }
}

// Merges two subarrays of arr[].
// First subarray is arr[left...middle]
// Second subarray is arr[middle+1..right]
void QuickStats::merge(float arr[], int left, int middle, int right)
{
  int i, j, k;
  int n1 = middle - left + 1;
  int n2 =  right - middle;

  // create temp arrays
  float L[n1], R[n2];

  // Copy data to temp arrays L[] and R[]
  for (i = 0;  i < n1;  i++)
  {
    L[i] = arr[left + i];
  }
  for (j = 0;  j < n2;  j++)
  {
    R[j] = arr[middle + 1 + j];
  }

  // Merge the temp arrays back into arr[left...right]
  i = 0;  // Initial index of first subarray
  j = 0;  // Initial index of second subarray
  k = left;  // Initial index of merged subarray
  while (i < n1 && j < n2)
  {
    if (L[i] <= R[j])
    {
      arr[k] = L[i];
      i++;
    }
    else
    {
      arr[k] = R[j];
      j++;
    }
    k++;
  }

  // Copy the remaining elements of L[], if there are any
  while (i < n1)
  {
    arr[k] = L[i];
    i++;
    k++;
  }

  // Copy the remaining elements of R[], if there are any
  while (j < n2)
  {
    arr[k] = R[j];
    j++;
    k++;
  }
}

// Mergesort implementation to sort arrays in O(nlogn) time
// "left" is for the left index of the sub-array of arr to be sorted
// "right" is for the right index of the sub-array of arr to be sorted
void QuickStats::mergeSort(float arr[], int left, int right)
{
  if (left < right)
  {
    // Same as (l+r)/2, but avoids overflow for large l and h
    int middle = left + (right - left)/2;

    // Sort first and second halves
    mergeSort(arr, left, middle);
    mergeSort(arr, middle + 1, right);
    merge(arr, left, middle, right);
  }
}



