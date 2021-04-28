An ordinary walk on a spring morning turned into an exciting adventure for a spherical horse in a vacuum - a series of time travel with a famous actor. Upon returning home, the horse discovered that something went wrong and now there are several copies of his companion-actor. Moreover, many of them are fathers to each other, and some thus generally became their own ancestors! The horse managed to figure out who is whose father, but to further solve the problem, he will need your help.
Help the horse select groups of actor copies, within which each copy is simultaneously a descendant of all other copies in the group and the ancestor of all other copies in the group.

Input format
N lines - a numbered list of the actor's copy names (example: "1 Kevin Smith"). 1 <= N <= 500
One line is the separator character '#'.
M lines - paternity links between copies (example: "1 2" - copy 1 is the father of copy 2).

Output format
X lines - the required copy groups in the form of lists of names.
Groups are listed alphabetically (by the first name in the group). The names within the group are also displayed in alphabetical order, each name on a new line.
There is 1 blank line between the groups.
The last group is also followed by 1 blank line.
A line feed is also performed after the last name.

Example
Input:
1 Бенедикт Камбербэтч
2 Беннихилл Кёнигсберг
3 Баттлфилд Камбердвач
4 Базилик Киберскотч
5 Бургеркинг Камамбер
6 Бекмамбет Контерстрайк
7 Бенефис Когтевран
8 Боромир Курткобейн
9 Букингем Комбикорм
10 Бранденбург Кайзершнаутц
11 Бартикрауч Курувпечь
12 Бандероль Кефирснэтч
#
1 2
2 3
2 4
2 5
5 2
3 6
6 3
5 6
5 7
6 8
7 8
9 7
10 9
7 10
8 11
11 12
12 10

Output:
Базилик Киберскотч

Бандероль Кефирснэтч
Бартикрауч Курувпечь
Бенефис Когтевран
Боромир Курткобейн
Бранденбург Кайзершнаутц
Букингем Комбикорм

Баттлфилд Камбердвач
Бекмамбет Контерстрайк

Бенедикт Камбербэтч

Беннихилл Кёнигсберг
Бургеркинг Камамбер

