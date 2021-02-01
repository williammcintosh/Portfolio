#8Puzzle Solver
Here is a link to the playable simulator:
http://bridgeworxgames.com/8PuzzleSim/

This simulator isn't a brute force, yet instead uses best-first and A* search
algorithms to solve the 8-puzzle. This uses three different heuristics,
counting misplaces tiles, summing the total of the manhattan distance from
their current positions to the desired goal positions, or the Gashcnig's swaps.
It builds a tree of nodes from it's current permutation to the desired goal position.

The file named "SimManagerScript.cs" is responsible for building the tree.
The file named "PuzzleNodeScript.cs" is the node of the tree.

This assignment was for my CS441 course which is AI, but the assignment didn't
require that the program be built in Unity, just that it be built. I wanted
to make the data more visual.

If I had unlimited time I would discover what causes the delays, removing some
of the extra features that Unity offers like Text Mesh Pro and figure out why
printing out 150 nodes causes such a delay. If entering the permutation
807415236 it'll never solve it yet only reach the upper limit and be very slow.

I'd also work on a making a printed list for the solution so the text could be
copied and pasted.
