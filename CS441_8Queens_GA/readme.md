# 8 Queens Solver

## Link to Simulator
http://bridgeworxgames.com/8_Queens_GA/

## How To Use The Simulator

If while you’re running the simulator you notice that everything is all cluttered together, just click the full screen mode button on the bottom.

![Use Full Screen](https://github.com/williammcintosh/Portfolio/blob/master/CS441_8Queens_GA/images/fullscreen.png)

Select the **initial population** that the algorithm is set to start with, and to do so you can click on the box and then type in the information you want. Do the same with **Number of Iterations** and **Mutation Percentage**. 

If you notice that the start button is greyed out, that means you have some non-numerical text in the text boxes. Change that text into a numerical text and you’ll notice that the Start button becomes white and clickable.

Once you’re ready you can hit the **Start** button.
Press the ‘r’ key (without shift) to restart the simulation.

## The Board

The board and the “Clashes” are the best value from all iterations / generations. The board simply displays what that configuration would look like if the queens were placed on a board.

## The Algorithm

Initial Population
Each parent / child / being is simply a string of characters, each element representing a position of a queen on the board. Since no two Queens have the same column or row, this works out well.

The initial population is how many of those strings we use. Though we call it “initial” the population will never increase nor decrease throughout the algorithm. This is selected from the user in the simulation.
## Fitness Function

We calculate the amount of clashes that represents each configuration, and the lower value is better. The lesser number of Queen clashes, the more valuable the string is. Its value is calculated as a percentage of the total number of all clashes from all strings in the entire population. We want to have a higher percentage for the strings that have the optimal configuration of Queens. To do this, we take the highest possible number of clashes for eight Queens on an eight by eight board (which is 28) and subtract the number of clashes of any given string. Each string is also assigned (by sharing the same element location through the different arrays) a fitness value, and a fitness percentage in contrast to its peers.
	Fitness = 28-totalClashes
	TotalGlobalFitness = j=1populationSizeFitness
	FitnessPercentage = Fitness / TotalGlobalFitness
  $\sum_{i=1}^{10} t_i$
  
  \sum_{i=1}^{10} t_i
  
## Selection

Each string is selected to be a parent for reproduction based on random chance, with the higher percentage going to the strings with the highest fitness percentage.
  
## Crossover

We go through the entire array of selected parents in pairs of two. To each pair, a random location is selected from 1-7 which divides the two parents in half, then one parent of the pair gets the first half of that division while the other parent gets the other half.
  
## Mutation

Then, each child gets to “roll the die” based on the mutation percentage set by the user in the simulation. If mutation percent is for example as 0.05, some simple arithmetic is completed to make it into a whole number and also the decimal locations are stored. Then a random number is selected 0-100 and if the number is 5 is randomly selected, then that string gets chosen for mutation.

Once a string is chosen for mutation a random number 0-7 is created which represents the element in the string which states where the random number swap will take place. Lastly, another random number is generated 1-8 which then replaces the old number only if it’s not the same number as the previous one.

## Iterations

This whole cycle repeats by the number of iterations selected by the user. Since the optimal values are given a higher percentage and are more likely to be randomly selected as parents for reproduction, then running this algorithm in more iterations increases the chances of that taking place.
