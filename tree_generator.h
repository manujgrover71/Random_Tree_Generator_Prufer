#ifndef TREE_GENERATOR
#define TREE_GENERATOR

#include <vector>
#include <random>
#include <time.h>
#include <assert.h>
#include <queue>

using namespace std;

namespace tree_generator {
    
    mt19937 rng(time(0));
    
    class Tree {
    private:
        vector<pair<int, int>> edges;
        vector<int> prufer;
        int n;
        
    public:
        Tree(int n) : n(n) {
            
            assert(n > 0);
            
            if(n == 2) {
                edges.push_back({1, 2});
            }
            
            if(n > 2) {
                generate_prufer_sequence(n);
                generate_random_tree();
            }
        }
        
        void generate_prufer_sequence(int n) {
            
            for(int i = 0; i < (n - 2); i++) {
                prufer.push_back((rng() % n) + 1);
            }
            
        }
        
        void generate_random_tree() {
            
            queue<int> p;
            priority_queue<int, vector<int>, greater<int>> r;
            vector<int> freq(n + 1); 
            
            for(auto &node : prufer) {
                freq[node]++;
                p.push(node);
            }
            
            for(int i = 1; i <= n; i++) {
                if(!freq[i]) {
                    r.push(i);
                }
            }
            
            int delimiter = r.top();
            
            while(p.size() && p.front() != delimiter) {
                
                int u = p.front();
                int v = r.top();
                
                p.pop();
                r.pop();
                
                edges.push_back({u, v});
                
                freq[u]--;
                freq[v]++;
                
                p.push(v);
                
                if(!freq[u]) {
                    r.push(u);
                }
            }
            
            if(r.size() > 1) {
                int u = r.top(); r.pop();
                int v = r.top(); r.pop();
                
                edges.push_back({u, v});
            }
            
        }
        
        vector<pair<int, int>> getEdges() {
            return this->edges;
        }
        
        int getNodeCount() {
            return n;
        }
        
        int getEdgeCount() {
            return n - 1;
        }
    };
};

#endif