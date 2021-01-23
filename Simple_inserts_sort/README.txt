You need to implement sorting by simple insertions in non-decreasing order and count the number of elements that, when added to the sorted part, were already in place, that is, that did not have to be moved.

Input format:
The first line contains one integer N - the number of numbers to be sorted. The second line contains N positive integers not exceeding one hundred.
It is guaranteed that 0 ≤ N <100.

Output format:
First, print the sorted array separated by a space, and then on a new line one number - the number of elements that were already in their place when sorting in their place.

Example 1
Input: 
5
1 2 5 3 4

Output:
1 2 3 4 5
2

Example 2
Input: 
5
1 2 3 4 5

Output:
1 2 3 4 5
4

Notes
Explanation for example 1:

The initially sorted part consists of one item.
Step 1.
The number 2 is in its place, add 1 to the answer.
1 2 5 3 4

Step 2.
The number 5 is in its place, we add 1 to the answer.
1 2 5 3 4

Step 3.
The number 3 is not in its place, we move it.
1 2 3 5 4

Step 4.
The number 5 is not in its place, we move it.
1 2 3 4 5
The array is sorted, the answer is 2.

Explanation for example 2:

Initially, the sorted part consists of one element, the other four elements are already in place, so the answer is 4.