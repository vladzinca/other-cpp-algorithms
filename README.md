# Other C++ Algorithms

## 🧠 What is it?

This repository contains two C++ algorithms that I wrote in June 2022.

They are called *Cleaning* and *Beamdrone* and aim to solve concrete problems using graph theory.

They prove an apt use of algorithms, as well as a good capacity to implement artificial intelligence bots that can serve to video game development, such as in [matrix traversal](https://www.geeksforgeeks.org/check-possible-path-2d-matrix/).

## 🔧 How to run it?

1.  Clone this repository.
2.  Run automatic tests found in `public_tests/` using `./check` (I did not write the checker myself).
3.  Enjoy!

## 🤓 What do they do exactly?

### 🤖 Cleaning

The code for this is found in `curatare.cpp`.

It imagines a `N * M` dimensional floor on which there are clean tiles and dirty tiles, as well as cleaning robots, and it computes the least amount of time needed to clean the entire floor.

The program reads from an input file called `curatare.in`:

```
N M
e11 e12 ... e1M
e21 e22 ... e2M
...
eN1 eN2 ... eNM
```

where `eij` can either be a `.`, meaning a clean tile, `R` meaning that's a robot starting position, `S` meaning the tile is dirty, or `X` meaning the space is occupied (e.g. by furniture).

It then prints to a file called `curatare.out` the minimum amount of time needed for the robots to clean the dirty tiles.

#### Example 1
##### Input:
```
10 10
XX........
XS.......S
..........
.R........
..........
......R...
.....XXXXX
.......SXX
.........X
...S.....X
```
![image](https://user-images.githubusercontent.com/74200913/225120100-9250724f-92d9-4d80-b96d-30d492447895.png)
##### Output:
```
13
```

#### Example 2
##### Input:
```
10 10
..........
..S.....S.
X........X
XX......XX
X......XXX
.......XXX
..S.....RX
RXXXXX...X
.....XR..X
....SXXXXX
```
![image](https://user-images.githubusercontent.com/74200913/225120695-c3bceea8-3a82-42a4-964b-4a6f67c69e93.png)
##### Output:
```
11
```

There can be no more than 4 robots and 4 dirty spots.

For computing the distances between a dirty tile and all the robots/all the other spots, we use a BFS traversal on a matrix and check at every iteration whether the cells around a given cell are not occupied, in this case adding them to the queue and incrementing the distance.

For the cases that have 3 or 4 dirty spots, when there are so many possibilities, I opted for an approach that uses the STL function `next_permutation` in order to check all possible permutations of dirty spots.

The time complexity for this problem is `O(N * M)`, as it's given by the BFS traversal that has the complexity `O(V + E)`, where the number of vertices is `N + M` and the number of edges is `4 * (N + M)` (for every matrix cell, there are 4 available edges).

### 🚁 Beamdrone

The code for this is found in `beamdrone.cpp`.

This problem imagines a similar `N * M` space with walls in which drones can fly, and computes the number of turns needed for a drone to reach a certain position in said bidimensional space.

For every 90 degrees rotation, the drone makes a turn.

The program reads from an input file called `beamdrone.in`:

```
N M
xi yi xf yf
e11 e12 ... e1M
e21 e22 ... e2M
...
eN1 eN2 ... eNM
```

where `xi` and `yi` are the initial coordinates of the drone, `xf and yf` constitute the destination coordinates, and `eij` can either be a `.`, meaning an empty space, or `W`, meaning an occupied space (e.g. a wall).

It then prints to `beamdrone.out` the smallest amount of turns needed by a drone to reach the destination. 

#### Example 1
##### Input:
```
6 6
5 0 4 4
.....W
.W.W.W
.WW..W
.W.W..
...W..
.W...W
```
![image](https://user-images.githubusercontent.com/74200913/225147461-f45db99c-0530-4896-82da-6b1813b2c854.png)
##### Output:
```
2
```

#### Example 2
##### Input:
```
6 6
4 3 2 1
.W....
W..WW.
W.W...
W....W
..W..W
......
```
![image](https://user-images.githubusercontent.com/74200913/225147663-8638505a-34c6-488d-916c-3dcdeb6fb300.png)
##### Output:
```
2
```

This problem's solution starts from a BFS implementation for matrix traversal similar to the one exposed by **Cleaning**.

For computing the amount of turns, I identified 20 cases, defined by the direction the drone came from before reaching a node `i` (5 directions: `N`, `E`, `S`, `V` or `A`, meaning that the drone came from top, right, bottom, left or from the starting position) and 4 ways the drone can move from the node `i` (top, right, bottom or left).

Contrary to a usual BFS traversal, this algorithm can add a node to the queue more than once if it signals the possibility of finding a smaller, more advantageous amount of turns.

However, we can observe how adding a node that was already visited to the queue can lead to a disadvantageous time complexity. Because the worst case has every node added to the queue approximately `N * M` times, and because we have `N * M` nodes, we can estimate the complexity to be `O((N * M)^2)` (see the explanation for a BFS matrix traversal from **Cleaning**).

## 💡 How is this useful?

Pratice makes perfect.

And this is what this project represented for me. I got to practice my already existing knowledge of graph theory and graph specific algorithms by solving some problems one can find in the real world.

In a way, one can argue that I even wrote an AI here. Putting aside neural networks and ChatGPT, which is what is usually meant by AI these days, the programs I wrote are basically AI's that can "see" around them and solve very palpable problems with just a small amount of computations.

These programs serve as a basis for me to delve deeper into machine learning, computer vision and similar topics, and maybe, one day, I'll even make an intelligent vaccuum robot.

Or maybe something even bigger? 🌃

## 🤔 Did you know?

Working with graphs is both a blessing and a curse.

😇 On the one hand, they are a very powerful data structure, empowering a large section of modern app design, from maps programs to video games.

😈 On the other hand, graphs are not scalable, and using big graphs to solve a problem can lead to bad memory and time complexities. Also happened here.
