# victor_cheng_cpp_used_5

### Q1
Essentially using an adjacency list to initialize the graph, every vertex is turned into its own disjointed set. Then using Kruskals algorithm to check to see which pairs of vertexes have the most similar edges are unioned together until there are only 3 unions left. Which is printed out and all done in O(nlogn).

Initialize, stores all distinct edges in a vector then sorts my edges by descending weight. Using the highest weighted edges first and union them until there are only 3 left. Then store each of the disjoint sets into a map which can then be iterated through to print out the results. 

## Output
Three group of photos:
Group 1 = 5; photos: p1, p13, p2, p5, p9
Group 2 = 9; photos: p10, p12, p15, p16, p17, p19, p4, p6, p8
Group 3 = 6; photos: p11, p14, p18, p20, p3, p7

# Running Time: 
176 microseconds.

### Q2a
On this question, I also initialized my graph using an adjacencey list. Then using Dijkstra, first to find the minimum path from my source vertex to the capital and then from the capital to my end vertex this is done by using a min priority queue that stores weights. Then reconstructing the path in reverse order to get the full path. This is done in O(nlogn) time while allowing cities to be visited more than once. 

It first initializes a map that represents the distances between nodes and sets it all to infinity besides our source distance d. Then using a priority queue we are able to check every neighboring node of our t node to see if its weight is optimal. This is then done again with the capital node and the end one. Then to actually find the full path, we reverse through starting at end node using our tracked neighboring weights equal the weight we saved at that spot.

## Output
Algorithm 1: Shortest path from d to i with capital a:
Shortest Path: d, f, j, a, i
Shortest distance: 42

Algorithm 1: Shortest path from f to g with capital a:
Shortest Path: f, j, a, g
Shortest distance: 41

# Running Time: 
651 microseconds.

### Q2b
On question 2 part b, Similarly to Q2a, I initialized my graph using an adjacency list, and then using Dijkstras, I also first found the minimum path from my source vertex to the capital and then instead of straight from the capital to my end vertex, I remove all the nodes part of my min path from source to capital and then I continue on with the search from capital to end. Then the paths are reconstructed and printed out again just like the other part. This is done in O(n^2)

## Output
Algorithm 2: Shortest path from d to i with capital a (no repeated cities):
Shortest Path: d, f, j, a, i
Shortest distance: 42

Algorithm 2: Shortest path from f to g with capital a (no repeated cities):
Shortest Path: f, j, a, g
Shortest distance: 41


# Running Time: 
533 microseconds.

### TODO: To run the program simply type make in terminal.