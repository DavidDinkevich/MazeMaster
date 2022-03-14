# MazeMaster
A fun little low-latency C++ project that graphically implements maze generation algorithms and solves them with different path-finding algorithms.
<br><br>
There are two modes in the program:
1) The first allows the user to generate a standard maze (and to select a maze-generation algorithm of his/her choice)
2) The second is a blank screen, on which the user can dynamically draw obstacles. The computer will actively search for a path around the user-drawn obstacles, even as the user draws them. 

<b>Tools:</b>
* SFML (C++ graphics library)
* CMake

<b>Algorithms implemented so far:</b>
* DFS (Maze generation)
* A-Star (Pathfinding)
***

<p align="center">

Maze Generator             |  Free Obstacle Creation
:-------------------------:|:-------------------------:
![Percolation Animation](https://github.com/DavidDinkevich/MazeMaster/blob/master/About/generated-maze-gif.gif) |   ![Percolation Animation](https://github.com/DavidDinkevich/MazeMaster/blob/master/About/custom-maze-gif.gif) 

