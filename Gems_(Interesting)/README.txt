Carolina loves to travel the world and collect gems. Recently, however, there is no way to travel. In order not to get bored, 
she decided to choose the most beautiful stones from her collection and show them to her friends.

She has nr gems of red color, ng ems of green color and nb blue gems, each of them is characterized by its own weight. Given three arrays
r, g, b (weight of red, green and blue gems) size nr, ng, nb respectively. Caroline wants to choose three stones. In doing so, she chooses exactly one gem of each color.
To make the three stones look more effective together, the difference between all possible pairs of weights from the selected stones should be minimal. The difference in weight of the three stones 
ri ,gj, bk 
Carolina counts by the formula:
(ri - gj)^2 + (gj - bk)^2 + (ri - bk)^2 → min, Where ri(1 ≤ i ≤nr)- the weight of the red gem, gj(1 ≤ j ≤ ng)
 - the weight of the green gem and bk(1 ≤ k≤ nb)- the weight of the blue gem.
Unfortunately, she herself could not choose such stones, there are too many of them, and even the formula is complicated. 
Therefore, she turned to you for help, because you are her best friend. Will you be able to help her?

Input format:

The first line of each test case contains a number t(1 ≤ t ≤ 100)- the number of tests in the set. A description of each test follows:
The first line contains three natural numbers separated by a space nr,ng,nb(1 ≤ nr, ng, nb ≤ 10^5)
 - the number of gems in red, green and blue, respectively.
The second line contains nr space-separated integers r1,r2,.........,rn(1 ≤ ri ≤ 10^9) where ri- the weighti the red gem.
The third line contains ng space-separated integers g1,g2,.........,gn(1 ≤ gi ≤ 10^9)where gi- the weight i green gem. 
The fourth line contains nb space-separated integers b1,b2,.........,bn(1≤ bi ≤ 10^9)where bi- the weight i blue gem.
It is guaranteed that the total number of stones of each color in one test does not exceed 10^5, i.e.,
 the sum of all nr≤10^5(in one test in total in all tests of the set no more than 10^5 red stones), the sum of all ng≤one0five, the sum of all nb ≤ 10^5...

Output format
For each test case from the set, print on a separate line three numbers separated by a space - the weights of the red, green, and blue gems, for which the difference in weight is minimal. 
The color order cannot be disturbed.
If there are several suitable answers, print any. 

Example:
input:
3
3 4 4
7 12 10
9 6 3 4
8 2 1 5

1 3 5
20
2 1 19
3 10 2 2 7

3 5 4
13 24 3
9 5 10 27 16
7 19 27 17

output: 
7 6 8
20 19 10
24 27 27