#include "proj5.h"

void Proj5::q1read(string& input) {
    ifstream currFile(input);
    string currLine;

    while(getline(currFile, currLine)) {
        if (currLine.empty()) {
            break;
        }

        stringstream line(currLine);
        
        string u, v;
        int weight;
        line >> u >> v >> weight;

        this->stringAddEdge(u, v, weight);
    }

    // printGraph();
    // outfile << endl;
}

void Proj5::q2read(string& input) {
    this->stringAdjGraph.clear();
    ifstream currFile(input);
    string currLine;

    int blanks = 0;
    while(getline(currFile, currLine)) {
        if (currLine.empty()) {
            blanks++;
            continue;
        }

        if (blanks == 1) {
            stringstream line(currLine);
        
            string u, v;
            int weight;
            line >> u >> v >> weight;

            this->stringAddEdge(u, v, weight);
        }

        if (blanks == 2) {
            stringstream line(currLine);
        
            string str, value;
            line >> str >> value;

            if (str == "Source:") {
                this->sourceNode = value;
            }

            if (str == "Destination:") {
                this->destinationNode = value;
            }
        }

        if (blanks == 3) {
            stringstream line(currLine);
        
            string str, value;
            line >> str >> value;

            if (str == "Source:") {
                this->sourceNode2 = value;
            }

            if (str == "Destination:") {
                this->destinationNode2 = value;
            }
        }
    }
    
    // printGraph();
}

void Proj5::runDijkstra(string source) {
    shortestPaths.clear();
    
    for (auto& node : stringAdjGraph) {
        shortestPaths[node.first] = 1e8;
    }

    shortestPaths[source] = 0;

    priority_queue<pair<int, string>, vector<pair<int, string>>, greater<pair<int, string>>> priorityQueue;

    priorityQueue.push(make_pair(0, source));

    while (!priorityQueue.empty()) {

        pair<int, string> topElement = priorityQueue.top();
        int currDist = topElement.first;
        string currNode = topElement.second;
        priorityQueue.pop();

        if (currDist > shortestPaths[currNode]) {
            continue;
        }

        for (auto& neighbor : stringAdjGraph[currNode]) {

            string nextNode = neighbor.first;
            int weight = neighbor.second;
            int newDist = currDist + weight;

            if (newDist < shortestPaths[nextNode]) {

                shortestPaths[nextNode] = newDist;
                priorityQueue.push(make_pair(newDist, nextNode));
                
            }
        }
    }
}

void Proj5::reconstructPath(string source, string target) {
    newPath.clear();
    
    if (shortestPaths[target] == 1e8) {
        return; // No path exists
    }

    // Reconstruct by going backwards from target to source
    vector<string> tempPath;
    string current = target;
    
    // Keep track of visited nodes to stop cycles
    set<string> visited;
    
    while (current != source && visited.find(current) == visited.end()) {
        visited.insert(current);
        tempPath.push_back(current);
        
        bool foundPrevious = false;
        for (auto& neighbor : stringAdjGraph[current]) {
            string prevNode = neighbor.first;
            int weight = neighbor.second;
            
            // Check if this is the previous node in the shortest path
            if (shortestPaths[prevNode] + weight == shortestPaths[current]) {
                current = prevNode;
                foundPrevious = true;
                break;
            }
        }
        
        if (!foundPrevious) {
            newPath.clear();
            return;
        }
    }
    
    tempPath.push_back(source);
    
    reverse(tempPath.begin(), tempPath.end());
    newPath = tempPath;
}

void Proj5::q2aAlg(string start, string end) {
    alg1.clear();
    
    // Get shortest paths from start to capital
    runDijkstra(start);
    int distToCapital = shortestPaths[capital];
    
    if (distToCapital == 1e8) {
        return; 
    }
    
    // Store first part of path to capital
    reconstructPath(start, capital);
    vector<string> path1 = newPath;
    
    // Get shortest paths from capital to end
    runDijkstra(capital);
    int distFromCapital = shortestPaths[end];
    
    if (distFromCapital == 1e8) {
        alg1.clear();
        return; 
    }
    
    // Store second part of path (capital to end)
    reconstructPath(capital, end);

    vector<string> path2 = newPath;
    
    // Combine paths and store in alg1
    alg1.clear();

    for (const auto& node : path1) {

        alg1.push_back(node);

    }

    for (int i = 1; i < (int)path2.size(); i++) { 

        alg1.push_back(path2[i]);

    }
}

void Proj5::q1(ofstream& outfile) {

    vector<string> photoNames;

    for (auto &entry : stringAdjGraph)
        photoNames.push_back(entry.first);

    DisjointSet disjointSets(photoNames);

    vector<tuple<string, string, int>> edges;

    for (auto &u : stringAdjGraph) {

        for (auto &pair : u.second) {

            string v = pair.first;
            int w = pair.second;

            if (u.first < v) {
                edges.push_back({u.first, v, w});
            }
        }
    }

    sort(edges.begin(), edges.end(),
        [](const tuple<string, string, int> &a, const tuple<string, string, int> &b) {
            
        return get<2>(a)> get<2>(b);
    });

    int maxSets = 3;
    int numSets = disjointSets.numSets;

    for (int i = 0; i < (int)edges.size(); i++) {

        if (numSets == maxSets) {
           break;
        }
    
        string u = get<0>(edges[i]);
        string v = get<1>(edges[i]);

        if (disjointSets.unionSet(u, v)) {

            numSets--;
        } 
    }

    map<string, vector<string>> setGroups;

    for (int i = 0; i < (int)photoNames.size(); i++) {

        string rep = disjointSets.find(photoNames[i]);
        setGroups[rep].push_back(photoNames[i]);

    }

    int clusterNum = 1;

    outfile << "Three group of photos:" << endl;

    for (map<string, vector<string> >::iterator it = setGroups.begin(); it != setGroups.end(); it++) {
        outfile << "Group " << clusterNum++ << " = " << it->second.size() << "; photos: ";

        for (int j = 0; j < (int)it->second.size() - 1; j++)

            outfile << it->second[j] << ", ";

    outfile << endl;


    }
}

void Proj5::q2a(ofstream& outfile) {
    // Test path from d to i via capital a
    outfile << "Algorithm 1: Shortest path from d to i with capital a:" << endl;

    q2aAlg(sourceNode, destinationNode);
    
    if (alg1.empty()) {

        outfile << "No path exists" << endl;

    } else {

        outfile << "Shortest Path: ";

        for (int i = 0; i < (int)alg1.size(); i++) {

            outfile << alg1[i];

            if (i < (int)alg1.size() - 1) {
                
                outfile << ", ";
            }
        }
        outfile << endl;
        
        // Calculate total distance
        runDijkstra(sourceNode);

        int distToCapital = shortestPaths[capital];

        runDijkstra(capital);

        int distFromCapital = shortestPaths[destinationNode];

        int totalDist = distToCapital + distFromCapital;

        outfile << "Shortest distance: " << totalDist << endl;
    }
    outfile << endl;

    // Test path from f to g via capital a
    outfile << "Algorithm 1: Shortest path from f to g with capital a:" << endl;

    q2aAlg(sourceNode2, destinationNode2);
    
    if (alg1.empty()) {
        outfile << "No path exists" << endl;

    } else {

        outfile << "Shortest Path: ";

        for (int i = 0; i < (int)alg1.size(); i++) {

            outfile << alg1[i];
            if (i < (int)alg1.size() - 1) {
                
                outfile << ", ";

            }

        }

        outfile << endl;
        
        // Calculate total distance
        runDijkstra(sourceNode2);

        int distToCapital = shortestPaths[capital];

        runDijkstra(capital);

        int distFromCapital = shortestPaths[destinationNode2];

        int totalDist = distToCapital + distFromCapital;

        outfile << "Shortest distance: " << totalDist << endl;
    }
    outfile << endl;
}



// void Proj5::q2b(ofstream& outfile) {


// }