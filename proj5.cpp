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
    // cout << endl;
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
                this->sourceNode = value;
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
                this->sourceNode2 = value;
            }
        }
    }
    
    // printGraph();
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

            if (u.first < v)
                edges.push_back({u.first, v, w});
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

        if (disjointSets.unionSet(u, v))
            numSets--;
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
    
}


// void Proj5::q2b(ofstream& outfile) {


// }