#ifndef PROJ5_H
#define PROJ54_H

using namespace std;
#include <fstream>
#include <chrono>
#include <string>
#include <sstream>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <utility>
#include <map>
#include <vector>
#include <set>
#include <algorithm>
#include <queue>

struct DisjointSet {
    map<string, string> parent;
    map<string, int> size;
    int numSets;

    DisjointSet(vector<string> &elements) {
        for (auto &e : elements) {
            parent[e] = e;
            size[e] = 1;
        }
        numSets = elements.size();
    }

    string find(string v) {
        if (parent[v] != v)
            parent[v] = find(parent[v]);
        return parent[v];
    }

    bool unionSet(string a, string b) {
        a = find(a);
        b = find(b);
        if (a == b) return false;
        if (size[a] < size[b]) swap(a, b);
        parent[b] = a;
        size[a] += size[b];
        numSets--;
        return true;
    }
};

class Proj5 {

    public:
        
        // Helper functions
        void q1read(string& input);
        void q2read(string& input);

        // Part B2a
        void runDijkstra(string source);
        void reconstructPath(string source, string target);
        void q2aAlg(string start, string end);

        // Part B2b
        void q2bAlg(string start, string end);
        void removeNodesFromGraph(const vector<string>& nodesToRemove, map<string, vector<pair<string, int>>>& graph);

        // Questions
        void q1(ofstream& outfile); 
        void q2a(ofstream& outfile); 
        void q2b(ofstream& outfile);


    private:

        map<string, vector<pair<string, int>>> stringAdjGraph;
        string sourceNode, destinationNode;
        string sourceNode2, destinationNode2;
        string capital = "a";

        map<string, int> shortestPaths;
        vector<string> newPath;
        vector<string> alg1;

        vector<string> alg2;

        void stringAddEdge(string u, string v, int weight) {
            stringAdjGraph[u].push_back({v, weight});
            stringAdjGraph[v].push_back({u, weight});  

        }

        void printGraph() {
    
            // We use a set to track which edges we've already printed
            set<pair<string, string>> printedEdges;

            for (const auto& mapEntry : stringAdjGraph) {
                string node1 = mapEntry.first;
        
                for (const auto& edge : mapEntry.second) {
                    string node2 = edge.first;
                    int weight = edge.second;

                    string key1 = (node1 < node2) ? node1 : node2;
                    string key2 = (node1 < node2) ? node2 : node1;

                    if (printedEdges.find({key1, key2}) == printedEdges.end()) {
            
                        cout << key1 << " " << key2 << " " << weight << endl;
                        printedEdges.insert({key1, key2});
                    }
                }
            }
        }

};
#endif