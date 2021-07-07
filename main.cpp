#include<iostream>
#include<vector>
#include<unordered_map>
#include<map>
#include<queue>
#include<set>
using namespace std;

class Graph{


public:
    Graph(){};
    unordered_map<string,vector<pair<string,int>>> adjlist;

    void addEdge(string u, string v,int dist,bool bidir = true)
    {
        adjlist[u].push_back(make_pair(v,dist));
        if(bidir == true)
            adjlist[v].push_back(make_pair(u,dist));
    }

    void show(){
        for(auto x: adjlist){
            cout<<x.first;
            for(auto y: x.second) cout<<" -> "<<y.first<<"("<<y.second<<") ";
            cout<<endl;
        }
    }

    void bfs(string src,string dest)
    {

        map<string, int> distance;
        map<string, string> parent;

        for (auto i : adjlist)
        {
            distance[i.first] = INT_MAX;
        }

        queue<string> q;
        q.push(src);
        distance[src] = 0;
        parent[src]=src;

        while (!q.empty())
        {
            string front_element = q.front();
            q.pop();

            for (auto neighbours : (adjlist[front_element]))
            {
                if (distance[neighbours.first] == INT_MAX)
                {
                    q.push(neighbours.first);
                    distance[neighbours.first] = distance[front_element] + 1;
                    parent[neighbours.first] = front_element;
                }
            }
        }

        int fare=0;
        int time_of_journey = 0;
        int distance_of_journey = 0;
        int stations = 0;

        cout<<"PATH: ";
        string temp = dest;

        while (parent[temp] != temp)
        {
            fare=fare+5;
            stations++;
            for(auto x : adjlist[temp]){
                if(x.first == parent[temp]){
                   distance_of_journey += x.second;
                }
            }
            cout << temp << "<--";
            temp = parent[temp];
        }
        cout << src << endl;

        time_of_journey += 2*distance_of_journey;  //for every 1KM , time taken = 2M

        cout<<"Total fare of the journey = "<<fare<<endl;
        cout<<"Total number of stations in the journey = "<<stations+1<<endl;
        cout<<"Total distance of the journey = "<<distance_of_journey<<endl;
        cout<<"Time taken to reach from "<<src<<" to "<<dest<<time_of_journey<<endl;

    }

    void dijkstra(string src,string destination){

        unordered_map<string,int> dist;
        map<string, string> parent;

        parent[src]=src;

        //Set all distance to infinity
        for(auto j:adjlist){
            dist[j.first] = INT_MAX;
        }

        //Make a set to find a out node with the minimum distance
        set<pair<int, string> > s;

        dist[src] = 0;
        s.insert({0,src});

        while(!s.empty()){  //while set is not empty;

            //Find the pair at the front.
            auto p =   *(s.begin());
            string node = p.second;

            int nodeDist = p.first;
            s.erase(s.begin());

            //Iterate over neighbours/children of the current node
            for(auto childPair : adjlist[node]){

                if(nodeDist + childPair.second < dist[childPair.first]){

                    //In the set updation of a particular is not possible
                    // we have to remove the old pair, and insert the new pair to simulation updation
                    string dest = childPair.first;
                    auto f = s.find( make_pair(dist[dest],dest));
                    if(f!=s.end()){
                        s.erase(f);
                    }

                    //Insert the new pair
                    dist[dest] = nodeDist + childPair.second;
                    s.insert(make_pair(dist[dest],dest));

                    parent[childPair.first]=node;

                }

            }
        }

        //printing the path with minimum distance between src and destinaion;
        int fare=0;
        int stations = 0;

        cout<<"PATH: ";
        string temp = destination;
        while (parent[temp] != temp)
        {
            fare=fare+5;
            stations++;
            cout << temp << "<--";
            temp = parent[temp];
        }
        cout << src << endl;


        cout<<"Total fare of the journey = "<<fare<<endl;
        cout<<"Total number of stations in the journey = "<<stations+1<<endl;
        cout<<"Total distance of the journey = "<<dist[destination]<<endl;
        cout<<"Time taken to reach from "<<src<<" to "<<destination<<" = "<<2*dist[destination]<<endl;


    }


void path_counter(string src, string dst, int& path_count, map<string,bool> visited)
{
    // If we've reached the destination, then increment
    // count...
   visited[src]=true;
   if(src == dst) {
        path_count++;
    }
    // ...otherwise recurse into all neighbours...
    else {
        for (auto neighbour : adjlist[src]) {
          if(visited[neighbour.first]==false) //not visited;
            path_counter(neighbour.first, dst, path_count, visited);
        }
        visited[src]=false;
    }
}


int count_paths(string src, string dst)
{
    int path_count = 0;
    map<string,bool> visited;
    for(auto x : adjlist){
        visited[x.first]=false;
    }
    path_counter(src, dst, path_count, visited);
    return path_count;
}

void dfs(string src,string dest,int cnt,vector<int> &v,map<string,bool> visited){
        visited[src]=true;
        if(src == dest){
            v.push_back(cnt);
        }
        for(auto neighbour : adjlist[src]){
            if(visited[neighbour.first]==false){
                dfs(neighbour.first,dest,cnt+1,v,visited);
            }
        }
    }

   bool no_of_stations_of_diff_paths(string src, string dest){
       vector<int> v;
       map<string,bool> visited;

       dfs(src,dest,0,v,visited);

       sort(v.begin(),v.end());
       if(v[0]==v[v.size()-1]){
           //number of stations in different paths are same;
           return true;
       }
       else{
           //number of stations in different paths are different;
           return false;
       }
   }

};
//S1 = Delhi, D1 = Pune, S2 = Kanyakumari, D3 = Kochi,
//D2 = Hyderabad, S3 = Nashik, D4 = Patna, S4 = Ladakh
int main(){
    Graph train;
    train.addEdge("Delhi","Jaipur",30);
    train.addEdge("Jaipur","Kota",10);
    train.addEdge("Kota","Jaiselmer",20);
    train.addEdge("Jaiselmer","Udaipur",30);
    train.addEdge("Udaipur","Surat",40);
    train.addEdge("Surat","Daman and Diu",25);
    train.addEdge("Daman and Diu","Ahmedabad",30);
    train.addEdge("Amhedabad","Pune",45);
    train.addEdge("Jaipur","Lucknow",20);
    train.addEdge("Lucknow","Prayagraj",40);
    train.addEdge("Prayagraj","Ghaziabad",50);
    train.addEdge("Ghaziabad","Noida",30);
    train.addEdge("Noida","Bhopal",25);
    train.addEdge("Bhopal","Raipur",60);
    train.addEdge("Raipur","Pune",90);
    train.addEdge("Pune","Mumbai",80);
    train.addEdge("Mumbai","Goa",90);
    train.addEdge("Goa","Munnar",50);
    train.addEdge("Munnar","Kanyakumari",60);
    train.addEdge("Kanyakumari","Rameshwaram",50);
    train.addEdge("Rameshwaram","Chennai",40);
    train.addEdge("Chennai","Hyderabad",30);
    train.addEdge("Hyderabad","Goa",30);
    train.addEdge("Pune","Amravati",70);
    train.addEdge("Amravati","Bhubaneshwar",90);
    train.addEdge("Bhubaneshwar","Puducherry",70);
    train.addEdge("Puducherry","Tirupati",10);
    train.addEdge("Tirupati","Mysuru",20);
    train.addEdge("Mysuru","Vellore",30);
    train.addEdge("Vellore","Madurai",40);
    train.addEdge("Madurai","Kochi",10);
    train.addEdge("Kochi","Kollam",50);
    train.addEdge("Kollam","Warangal",50);
    train.addEdge("Warangal","Nashik",10);
    train.addEdge("Nashik","Tirupati",10);
    train.addEdge("Warangal","Ranchi",95);
    train.addEdge("Ranchi","Jabalpur",100);
    train.addEdge("Jabalpur","Patna",50);
    train.addEdge("Patna","Agra",60);
    train.addEdge("Patna","Shillong",25);
    train.addEdge("Agra","Meerut",20);
    train.addEdge("Meerut","Haridwar",20);
    train.addEdge("Haridwar","Dehradun",55);
    train.addEdge("Dehradun","Shimla",45);
    train.addEdge("Shimla","Manali",40);
    train.addEdge("Manali","Ladakh",10);
    train.addEdge("Patna","Agra",95);
    train.addEdge("Shillong","Meghalaya",30);
    train.addEdge("Meghalaya","Cheerapunjee",15);
    train.addEdge("Cheerapunjee","Gangtok",35);
    train.addEdge("Gangtok","Varanasi",25);
    train.addEdge("Varanasi","Bareilly",20);
    train.addEdge("Bareilly","Manali",20);

   // train.show();
   string command;

    do{
    cout<<"Enter source station :";
    string source; cin>>source;
    cout<<"Enter Destination station :";
    string desti; cin>>desti;

    int no_of_paths = train.count_paths(source,desti);  //dfs
    if(no_of_paths == 1){
        train.bfs(source,desti);
    }
    else if(no_of_paths > 1){
        if(train.no_of_stations_of_diff_paths(source,desti)==true){
            //if number of stations of differenct paths are equal in multiple paths --> means bfs lagane se same result aayega -> same money on both the paths;
            train.dijkstra(source,desti);  //calling dijkstra for default minimum distance path;
        }
        else{
            //number of stations are different in the multiple paths.
            while(true){
                cout<<"\nThere exist multiple paths between "<<source<<" and "<<desti<<endl;
                cout<<"\nEnter your prefernce between Money and time :\n Press 1 for money \n Press 2 from time"<<endl;
                int preference; cin>>preference;
                if(preference == 1){
                    //preferene is money (means less number of stations)
                    train.bfs(source,desti);
                    break;
                }
                else if(preference == 2){
                    //preference is time (means minimum distance)
                    train.dijkstra(source,desti);
                    break;
                }
                else{
                    cout<<"INVALID INPUT"<<endl;
                }
            }

        }
    }
    else{
        cout<<"\nThere exist no path between "<<source<<" and "<<desti<<"\n";
    }

    cout<<"Do you want to continue ?"<<endl<<"Enter YES or NO : ";
    cin>>command;
    }
    while(command =="YES" or command =="Yes" or command =="yes");

}

