#include <bits/stdc++.h>
#include "tree_generator.h"
using namespace std;
using namespace tree_generator;

int main() {
    Tree a(10);
    
    cout << a.getNodeCount() << ' ' << a.getEdgeCount() << '\n';
    for(auto edge : a.getEdges()) {
        cout << edge.first << ' ' << edge.second << '\n';
    }
    cout << '\n';
    
    a.deserialize("input.txt");
    
    cout << a.getNodeCount() << ' ' << a.getEdgeCount() << '\n';
    for(auto edge : a.getEdges()) {
        cout << edge.first << ' ' << edge.second << '\n';
    }
    cout << '\n';
}