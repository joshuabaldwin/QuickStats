Readme file for Arduino QuickStats Library

============================
Development Information:
============================
Developer: Joshua Baldwin
           Chief Software Engineering Lead
           joshua@compupartners.com
           www.github.com/joshuabaldwin
Version:   1.2.0
Date:      01/05/2017


============================
Description:
============================
QuickStats is a library that provides sorting and simple descriptive statistics for elements in float arrays for use in Arduino. 

This library was originally created for a data smoothing strategy for float variables. Using a median or mode filtering strategy (opposed to mean filtering) is better at removing spikes from aberrant readings. The other functions (stdev, stderror, CV, etc.) were included to provide additional value to this software library.

A sorting algorithm is also included, which is necessary for calculation of median and mode.

Currently, each function takes a float array and the dimension of the float array as inputs.


============================
Requirements:
============================
- Arduino 1.6.6 or greater


============================
Available Functions:
============================
The functions available in this updated release of the QuickStats library include:

   average(samples[], m);              // The average of elements in samples[m]
   g_average(samples[], m);            // The geometric mean of elements in samples[m]
   minimum(samples[], m);              // The minimum value in samples[m]
   maximum(samples[], m);              // The maximum value in samples[m]
   stdev(samples[], m);                // The sample standard deviation of elements in samples[m]
   stderror(samples[], m);             // The standard error of elements in samples[m] calculated as stdev/sqrt(m)
   CV(samples[], m);                   // The coefficient of variation in samples[m] in percent, calculated as 100*stdev/average
   bubbleSort(samples[], m);           // An inefficient sorting algorithm to arrange the elements in samples[] to array index "m" in ascending order
                                       //      Retained only for backward compatibility with previous library versions
                                       //      Recommendation: Replace bubbleSort invocation with mergeSort invocation with 0 for left and m for right
   mergeSort(samples[], left, right);  // An efficient sorting algorithm to arrange the elements in samples[] from array index "start" to array index "end" in ascending order
   fabs(sample);                       // The absolute value of a single float value
   median(samples[], m);               // The median of elements in samples[m]
   mode(samples[], m, epsilon);        // The mode of elements in samples[m]. This function returns a zero if there is no mode
                                       //      epsilon is the tolerance of accepting measurements as being equal
                                    
============================
Usage Directions:
============================
To use the library, 
   - Copy the unzipped download to the Arduino Library directory
OR...
   - In the Arduino IDE, navigate to "Sketch" > "Include Library" > "Add .ZIP Library" and add the zipped download of this library


============================
Technical Notes:
============================
- Both the mergesort implementation and the bubble sort implementation will re-order the input array. The array is passed by reference.
- The bubble sort implementation runs in O(n2) time, which is a slower worst-case runtime than the O(nlogn) worst-case runtime of the mergesort implementation.  Usage of mergesort is recommended, while bubblesort is provided for backward compatibility. The functions that require sorting (median and mode) use the mergesort implementation.
- The library only currently works on float arrays. Future releases could create functions to work on arrays of other data types.


============================
Examples:
============================
The example sketch, "statistics.ino" illustrates how to call each function.

