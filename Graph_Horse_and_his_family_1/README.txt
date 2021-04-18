A significant event took place at PI - three whole days passed without a single pressing of the red button. The spherical horse in a vacuum decided to celebrate this and invite all his relatives to the holiday by publishing a list of invitees on his page on the social network.
In order not to offend anyone, he decided to arrange the names in the list as follows: first comes his name, then the names of his close relatives in alphabetical order, then the names of their not yet specified close relatives in alphabetical order, and so on.
He compiled an unordered list of all the invitees (including himself) and was able to get hold of his family's kinship chart. Due to spiritual decline and non-human social norms, this scheme is rather confusing compared to the usual family tree.
Write a program to help your horse organize a party.
Perform graph traversal in lexicographic order.

Input format
N lines (N <= 100000) - numbers and names of guests (eg "12 Vladislav Smith") in order (numbers start with 1).
1 line - # separator character.
M lines - close family ties (undirected) of guests by numbers (eg "3 7") in no particular order.
1 line - # separator character.
1 line - the number of the organizing horse in the list.

Output format
N lines - names of guests in a correctly ordered list (after the last line, a new line is also placed).

example:
input:
1 Vladislav Smith
2 Tarja Turunen
3 Will Smith
4 Zeus
5 Fishmaster
6 Chuck Norris
7 King Leonidas
8 Steven Seagull
9 Swiborg
10 Alexander Abdulov
11 Tim
12 Nils Patrik Johansson
#
1 2
1 3
2 7
3 7
7 11
11 12
2 4
2 5
3 5
3 6
4 8
4 9
6 10
#
1

output:
Vladislav Smith
Tarja Turunen
Will Smith
Chuck Norris
Fishmaster
King Leonidas
Zeus
Alexander Abdulov
Steven Seagull
Swiborg
Tim
Nils Patrik Johansson
