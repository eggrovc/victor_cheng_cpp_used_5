# victor_cheng_cpp_used_5

### Q1
Essentially using an adjacency list to initialize the graph, every vertex is turned into its own disjointed set. Then using Kruskals algorithm to check to see which pairs of vertexes have the most similar edges are unioned together until there are only 3 unions left. Which is printed out and all done in O(nlogn).

## Output
Three group of photos:
Group 1 = 5; photos: p1, p13, p2, p5, 
Group 2 = 9; photos: p10, p12, p15, p16, p17, p19, p4, p6, 
Group 3 = 6; photos: p11, p14, p18, p20, p3, 

# Running Time: 
199 microseconds.

### Q2a
On this question, I also initialized my graph using an adjancey list. Then using Dijkstra, first to find the minimum path from my source vertex to the capital and then from the capital to my end vertex. Then reconstructing the path in reverse order to get the full path. This is done in O(nlogn) time while allowing cities to be visited more than once. 

## Output
Algorithm 1: Shortest path from d to i with capital a:
Shortest Path: d, f, j, a, i
Shortest distance: 42

Algorithm 1: Shortest path from f to g with capital a:
Shortest Path: f, j, a, g
Shortest distance: 41

# Running Time: 
651 microseconds.