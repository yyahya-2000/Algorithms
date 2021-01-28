As you know, in the near future, ordinary couriers will be replaced by flying drones that will deliver parcels to the windows of buyers.
One well-known company decided to buy up all the drones that could be bought and put them in a warehouse. Each drone is known for its ID and carrying capacity. 
Now, in order to organize the storage of drones and launch them in operation, it is necessary to arrange them in order of non-increasing carrying capacity. 
Since there are a lot of drones, this should be done as quickly as possible.
It is also important to preserve the relative position of the drone IDs while the load capacity is equal, that is, the sorting by load capacity must be stable. 

input format:
The first line contains one integer N - the number of drones in the warehouse. 
The next N lines contain pairs of integers, separated by tabs, - the drone ID and its carrying capacity.
It is guaranteed that 0 ≤ N ≤ 1,000,000, respectively, ID is not more than 1,000,000.
 It is guaranteed that the carrying capacity can take integer values ​​from 0 to 1,000,000 inclusive.

Output format:
Print N pairs of numbers, drone ID and carrying capacity, separated by tabs, each pair on a new line. Pairs should be ordered in non-increasing capacity.
IMPORTANT!!! The order of the drone IDs in case of equal payload should be the same as in the original list.

Example 1
Input:
5
130 6
481 32
542 13
1283
36 58

Output:
12 83
36 58
481 32
542 13
130 6

Example 2
Input:
12
213 10000
442 1000
123 100
142 10
364 1
34 0
234 0
367 1
138 10
673,100
449 1000
200 10000

Output:
213 10000
200 10000
442 1000
449 1000
123 100
673,100
142 10
138 10
364 1
367 1
34 0
234 0

Notes:
You are not allowed to use built-in sorts in this task. 