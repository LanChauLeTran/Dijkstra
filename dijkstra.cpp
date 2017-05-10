#include <iostream>
#include <climits>
#include <string>
#include <vector>
#include <queue>
#include <iterator>
#include <map>

using namespace std;

class Compare{
public:
  bool operator()(pair<string, int> v, pair<string, int> v2){
    return(v2.second > v.second);
  }
};

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
        cout << "Weight: " << dis->second << endl << endl;
      }
    }
  }

  map<string, int> dijkstra(string source, string target){

//    cout << "target: " << target << endl;

    priority_queue<pair<string, int>, vector< pair<string, int> >, Compare> pq;

    //initialize a vector of location and distances of infinity
    //vector< pair<string, int> > distance;

    map<string, int> dist;
    for(map<string, vector< pair<string, int> > >::iterator it = m.begin();
        it != m.end(); ++it){
          dist.insert(pair<string, int>(it->first, INT_MAX));
    }

    dist.insert(pair<string, int>(target, INT_MAX));

    pq.push(make_pair(source, 0));
    dist[source] = 0;

/*
    cout << "---------------------------------------------------------------"<<endl;
    for(map<string, int>:: iterator it = dist.begin();
        it != dist.end(); ++it){
          cout << it->first << ":  " << it->second << endl;
        }
    cout << "---------------------------------------------------------------"<<endl;
*/

    //while queue is not empty
    while(!pq.empty()){
      //extract min distance, vertex U
      pair<string, int> U = pq.top();
      string cur = U.first;
      int d = U.second;
      pq.pop();


      for(vector< pair<string, int> >::iterator it = m[cur].begin();
          it != m[cur].end(); ++it){

        //vertex adj to current and weight from current to vertex
        string n = it->first;
        int weight = it->second;

  //      cout << "current's neighbors " << n << endl << endl;

        if(dist[n] > (dist[cur] + weight)){
  //        cout << "N: " << n << "   " << dist[n] << endl;
          dist[n] = dist[cur] + weight;
          pq.push(make_pair(n, dist[n]));
        }
      }
    }

/*
    cout << "---------------------------------------------------------------"<<endl;
    for(map<string, int>:: iterator it = dist.begin();
        it != dist.end(); ++it){
          cout << it->first << ":  " << it->second << endl;
        }
    cout << "---------------------------------------------------------------"<<endl;
*/

    return dist;
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
//    g.print();

    map<string, int> distance = g.dijkstra("airport", "robotbar");

    /*cout << "this is the distance map" << endl;
    for(map<string, int>:: iterator it = distance.begin();
        it != distance.end(); ++it){
          cout << it->first << ":  " << it->second << endl;
        }*/

    cout << "#" << i+1 << " : " << g.name << ", ";
    cout << distance["robotbar"] << " tokens." <<endl;

  }

  return 0;
}
