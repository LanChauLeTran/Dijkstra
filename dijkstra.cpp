#include <iostream>
#include <climits>
#include <string>
#include <vector>
#include <queue>
#include <iterator>
#include <map>

using namespace std;

struct Graph{
  int vertices;
  string name;
  map<string, vector< pair<string, int> > > m;

  void addEdge(string v, string n, int w){
    m[v].push_back(make_pair(n, w));
  }

  void print(){
    for(map<string, vector< pair<string, int> > >::iterator it = m.begin();
        it != m.end(); ++it){
      cout << "Current Location: " << it->first << endl;;
      for(vector< pair<string, int> >::iterator dis = it->second.begin();
        dis != it->second.end(); ++dis){
        cout << "Neighbor: " << dis->first << endl;
        cout << "Weight: " << dis->second << endl;
      }
    }
  }

};


Graph readInput(){
  string city;
  int locs;

  cin >> city >> locs;

  Graph gr;

  gr.vertices = locs;
  gr.name = city;

  for(int i = 0; i < locs; i++){
    string vertex;
    int adj;

    cin >> vertex >> adj;

    for(int j = 0; j < adj; j++){
      string neighbor;
      int weight;

      cin >> neighbor >> weight;
      gr.addEdge(vertex, neighbor, weight);
    }
  }
  return gr;
}

int main(){
  int runs;

  cin >> runs;

  for(int i = 0; i < runs; i++){
    Graph g = readInput();
    g.print();
  }

  return 0;
}
