# Mountain Algorithm

A C implementation of a local search algorithm designed to locate the highest point in a procedurally generated terrain used for a preformance based competition with the gradient.c code given for the parameters of the project.

The gradient_sol.c Shows the algorithim itself while the gradient.c procedurely generates the terrain and allows for the use of testcases.

## Features
- Gradient-based direction selection
- Plateau detection and handling
- Multiple search directions
- Performance testing across 100 generated landscapes
- Query counting to evaluate algorithm efficiency

## How It Works

The algorithm operates on a generated terrain represented by a two-dimensional floating-point matrix.

A peak is first generated at a random location. The terrain is then modified with randomly positioned plateaus to make the search more challenging.

The search algorithm begins by examining a local view of the terrain and identifying the highest value within that view.

The location of the highest value is used to determine the direction of the next search.

If the highest value is not at the centre of the current view, the algorithm moves towards it and performs another search.

If the highest value is at the centre, the algorithm checks surrounding areas to determine whether it has reached a peak or is currently located on a plateau.

----Plateau Handling----

Plateaus make local searches more difficult because multiple positions can have the same altitude.

The algorithm checks up to two additional distances in eight directions:

North
South
East
West
North-East
North-West
South-East
South-West

If a higher value is discovered, the search moves towards that location.

If no higher value is found, the current position is considered the peak.

Performance Testing

The program includes a performance evaluation mode which runs the algorithm across 100 generated landscapes.

For each run, the number of queries made by the algorithm is recorded.

The average number of queries is then calculated:

Average Queries = Total Queries / Number of Runs

This allows the efficiency of the search algorithm to be evaluated without requiring the entire terrain to be scanned.



----What I Learned----

This project provided practical experience with:

Implementing search algorithms in C
Working with dynamically allocated matrices
Managing contiguous memory
Using pointers and pointer parameters
Breaking a larger algorithm into reusable functions
Handling fail cases such as plateaus and terrain boundaries
Measuring algorithm performance
