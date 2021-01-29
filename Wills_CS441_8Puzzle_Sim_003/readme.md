#Link to playable simulator
http://bridgeworxgames.com/8_Puzzle_Simulator/

If I had unlimited time, I would discover why the same node it being revisited,
triggering the break condition to prevent unlimited loops. Something within
the checks that I’ve created which examines the memory for each recursive call,
causes just the last child node to be re-visited, even though I’ve told it otherwise.
In other words, when a parent creates it’s children, it will create a node that
we’ve already visited, which is fine (that is behavior that I want to allow).
Yet, the recursive function shouldn’t be passing in that previously created (copied) node,
yet should instead recognize that it’s a copy and return to break out of the recursive call.
This all works yet not if child node happens to be the last node of the children.
I think this has something to do with how I implemented the A Star algorithm which not
only requires us to consider which nodes we’ve visited, yet also requires us to prioritize
the nodes, choosing the one with the lowest F(n). I’m sure that in my attempts to prioritize
the prevention of revisiting nodes, I placed secondarily the check if one of the child nodes
has a lower F(n) than another.
