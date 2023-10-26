# Modified Dijkstra

This code runs a modified Dijkstra algorithm to find the optimum path in a graph from a source node to a goal node.

It solves the following problem: each edge of the graph (road) has a probability of not being abducted by aliens. The probability of not being abducted in the travel is the product of probabilities along each edge. We want to maximize this probability.

The cost of the path goes to zero as more edges are traversed and more numbers between 0 and 1 are multiplied together. To avoid overflow, I proposed to use the logarithm of the probabilities and sum the negative numbers.

## Runing the code

The code is prepared to run both in Linux and Windows, with the different between both systems located in the use of a function to read the graph.

It is compiled with 

gcc -o route mainBody.c dijkstra.c readGraph.c -lm

To execute the program, it requires as arguments the file where the graph is stored, the source node and the goal node. For example,

./route exampleGraph.txt 0 5

An example graph is provided with the source code.

## Code output

Once the optimal route is found, the program prints in the console the calculated logarithm of probability of no abduction on the road and displays the probability of abduction. Then it prints the path to follow from origin to destination.

If there is no route or an error occurs a message describing the issue will be printed.

## Graph format

The graph for the problem is stored in a txt file with the following structure: in the first line there is the number of nodes in the graph. Afterwards there is a block for each node containing:

number of adjacent nodes (int) <br>
id of adjacent nodes, separated by commas (int) <br>
probability of no abduction on the edge - weigth of the edge (float)

The nodes should be described sequentially: first block is for node 0, second block is for node 1, and so on.

The example graph provided is the following:
![example_graph](https://github.com/PhoenixBirdCreations/Cprojects/assets/55663736/22cc47b2-1104-4686-b765-01b732c527ae)
