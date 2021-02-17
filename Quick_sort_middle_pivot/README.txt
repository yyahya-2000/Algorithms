Implement Hoare sort (quick, quicksort) non-decreasing for a given integer array of N elements 
with the choice of the processed part of the array as a reference element.
It is required to solve this problem according to the classical Hoare scheme: with two indices and 
the array is divided into 2 parts.
Determine the number of recursive calls.

Input format
The first line contains an integer N, the number of elements in the input array.
The second line contains an array of N signed integers, separated by a space.

Output format
The first line contains an integer, the number of recursive calls.
The second line contains N elements of an array sorted in non-decreasing order, separated by a space. 


Example 1:
Input: 
3
33 22 11

Output:
0
11 22 33

Example 2:
Input: 
30
7 49 73 58 30 72 44 78 23 9 40 65 92 42 87 3 27 29 40 12 3 69 9 57 60 33 99 78 16 35

Output:
26
3 3 7 9 9 12 16 23 27 29 30 33 35 40 40 42 44 49 57 58 60 65 69 72 73 78 78 87 92 99

Example 3
Input:
10
12 87 31 42 38 18 35 46 28 41

Output:
8
12 18 28 31 35 38 41 42 46 87 
