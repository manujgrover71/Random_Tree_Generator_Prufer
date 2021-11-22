#ifndef TREE_GENERATOR
#define TREE_GENERATOR

#include <vector>
#include <random>
#include <time.h>
#include <assert.h>
#include <queue>
#include <fstream>

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
        
        Tree(const string file_name) {
            deserialize(file_name);
        }
        
        void deserialize(const string file_name) {
            
            ifstream fin;
            fin.open(file_name);
            
            if(!fin) {
                cout << "Unable to open file!\n";
                return;
            }
            
            vector<string> input;
            string temp;
            
            while(getline(fin, temp)) {
                input.push_back(temp);
            }
            
            fin.close();
            
            assert(input.size() >= 1 && input.size() <= 2);
            
            int N = stoi(input[0]);
            
            if(N <= 2) {
                n = N;
                prufer.clear();
                edges.clear();
                
                if(N == 2) {
                    edges.push_back({1, 2});
                }
                
                return;
            } 
            
            stringstream ss(input[1]);
            vector<int> temp_prufer;
            
            while(getline(ss, temp, ',')) {
                temp_prufer.push_back(stoi(temp));
            }
            
            assert(N == temp_prufer.size() + 2);
            
            for(auto &el : prufer) {
                assert(1 <= el && el <= N);
            }
            
            prufer.clear();
            edges.clear();
            
            prufer = temp_prufer;
            n = N;
            generate_random_tree();
        }
        
        void serialize(const string file_name) {
            
            ofstream fout;
            fout.open(file_name);
            
            if(!fout) {
                cout << "Unable to create / write to file\n";
                return;
            }
            
            if(n == 1) {
                fout << "1\n";
                return;
            } else if(n == 2) {
                fout << "2\n";
                return;
            }
            
            fout << prufer.size() + 2 << '\n';
            
            for(int i = 0; i < prufer.size(); i++) {
                fout << prufer[i];
                
                if(i != (int)prufer.size() - 1) {
                    fout << ',';
                }
            }
            
            fout.close();
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