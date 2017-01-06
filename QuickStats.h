/*  QuickStats.h - Library for quick descriptive statistics of an array samples[] of size m,
 *  assuming a normal distribution.
 *  Created by David Dubins, January 10th, 2016.
 *  Updated by Joshua Baldwin, 01/05/2017.
 *  Version 1.2.0
 *  Released into the public domain.
 *  See Readme.txt for additional documentation.
 */

#ifndef QuickStats_h
#define QuickStats_h

#include <Arduino.h>

class QuickStats
{

  private:

    // Private Methods
    void merge(float[], int, int, int);     // needed by the MergeSort implementation but should not be seen by the user

  public:
    // Constructor
    QuickStats();

    // Destructor
    ~QuickStats();

    // Public Methods
    float average(float samples[], int m);
    float g_average(float samples[], int m);
    float minimum(float samples[], int m);
    float maximum(float samples[], int m);
    float stdev(float samples[], int m);
    float stderror(float samples[], int m);
    float CV(float samples[], int m);
    void bubbleSort(float A[], int len);
    void mergeSort(float[], int, int);      // new in Version 1.2.0
    float fabs(float sample);
    float median(float samples[], int m);
    float mode(float samples[], int m, float epsilon);

};

#endif
