//
// Created by ojcch on 4/15/2020.
//

#ifndef GRAPHS_DIRECTEDGRAPH_H
#define GRAPHS_DIRECTEDGRAPH_H

#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

class DirectedGraph {
private:

public:



    vector<int> *in;
    vector<int> *out;
    int edge_num = 0;
    int vertices_num = 0;

    DirectedGraph() {

    }

    DirectedGraph(int numberOfVertices) {
        in = new vector<int> [numberOfVertices];
        out = new vector<int> [numberOfVertices];
        //vector<int> out[numberOfVertices];
        //vector<int> in[numberOfVertices];

    }

    //return the number of edges
    int num_edges() {
        cout << edge_num;
        return edge_num;

    }

    //return the number of vertices
    int num_vertices() {
        return vertices_num;

    }

    //adds an edge connecting v and w (v->w)
    void add_edge(int v, int w) {
        if (out[v].empty() && in[v].empty()){
            vertices_num +=1;
        }
        if (out[w].empty() && in[w].empty()){
            vertices_num +=1;
        }

        if (!edge(v,w)){
            out[v].push_back(w);
            in[w].push_back(v);
            edge_num++;
        }

//        for (auto x:dgraph[v])
//            cout<< x;
//        cout<<endl;
    }

    //checks if there is an edge connecting v and w (v->w)
    bool edge(int v, int w) {
        int count = 0;
        for (auto x: out[v]){
            if (x == w) return true;
        }
        return false;
    }

    //finds all edges (x, y) involving  v, i.e., x = v or y = v
    vector<pair<int, int>> *edges(int v) {
        vector<pair<int, int>> pairs;
        pair<int, int> temp;
        for (auto x: out[v]){
            temp = make_pair(v,x);
            pairs.push_back(temp);
        }

        for (auto x: in[v]){
            temp = make_pair(x,v);
            pairs.push_back(temp);
        }

        for (auto x: pairs){
            cout << "(" << x.first << ", " << x.second << ")" << " ";
        }

        return nullptr;
    }

    //finds all vertices that are neighbors of v (i.e. all vertices adjacent to v)
    vector<int> *adj(int v) {
        vector<int> temp;
        for (auto x: out[v]){
            temp.push_back(x);
        }

        for (auto x: in[v]){
            temp.push_back(x);
        }

        std::unordered_set<int> set(temp.begin(),temp.end());
        for (const int &x: set){
            cout << x << " ";
        }
        return nullptr;
    }

    //finds all vertices that v points to (v->x), ie., the vertices x in the edges (v, x)
    vector<int> *outAdj(int v) {
        vector<int> temp;
        for (auto x: out[v]){
            temp.push_back(x);
        }
        std::unordered_set<int> set(temp.begin(),temp.end());
        for (const int &x: set){
            cout << x << " ";
        }

        return nullptr;
    }

    void print() {
        cout << "Printing the graph..." << endl;
        for (int x = 0; x < 13; x++){
            cout << x << "->[";
            if ((out[x].empty()))
                cout << "]" << endl;

            for (auto i: out[x]){
                if (i == out[x].back())cout << i << "]" <<endl;
                else
                cout << i << ", ";
            }
        }


    }

};


#endif //GRAPHS_DIRECTEDGRAPH_H
