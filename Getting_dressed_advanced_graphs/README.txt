A spherical horse in a vacuum is sent to a very important and formal event. True, as a toastmaster. Nevertheless, he will be required to be dressed according to all the secular rules of spherical horses in a vacuum, and he is not used to that. He was able to get hold of all the necessary wardrobe items and even got hold of a diagram of what to wear over what, but in order not to get confused, he decided to rewrite the diagram as a list of what to wear in what order.
Help the horse get ready for the event - write a program that will allow him to make such a list.

Input format
N lines - numbered wardrobe items (example: "1 Boyarsky's Hat"). 1 <= N <= 500
1 line - separator character '#'.
M lines - links between items of clothing (example: "1 2" - item 1 must be worn before item 2).

Output format
N lines - wardrobe items (example: "Boyarsky's hat").
After the last line, there is also a line break.

Example:
Input:
1 Шаровары Свиборга
2 Плащ-отладка
3 Грибная шляпка Ленина
4 Карманцы Бильбо
5 Свинцовые подштанники
6 Платье из мяса
7 Ежовые рукавицы
8 Перчатки LaTeX
9 Брючный ремень безопасности
10 Телескопический монокль
11 Непомерно большие наплечники
12 Футболка с постыдным принтом
13 Потерянный левый носок
#
5 1
13 1
1 4
1 6
1 9
6 12
6 7
6 2
6 3
6 10
12 11
7 8
11 2

Output:
Свинцовые подштанники
Потерянный левый носок
Шаровары Свиборга
Платье из мяса
Футболка с постыдным принтом
Непомерно большие наплечники
Телескопический монокль
Плащ-отладка
Ежовые рукавицы
Перчатки LaTeX
Грибная шляпка Ленина
Карманцы Бильбо
Брючный ремень безопасности
