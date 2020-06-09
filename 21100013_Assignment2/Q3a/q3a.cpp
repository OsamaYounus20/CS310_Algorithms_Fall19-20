#include <iostream>
#include <vector>
#include <cstring>
#include <fstream>
#include <sstream>
#include <string>
#include <list>
#include <utility>
#include <vector>
#include <algorithm>
#include <limits.h>
using namespace std;

string line = "", ext = "";
int size = 0,  i = 0;
vector<pair<int,pair<int,int>>> myvec;
//vector<pair<pair<int,int>,int>> myvec;
using namespace std; 

/*
	in this I have used Kruskal algorithm to find a minimum spanning tree. Time complexity of kruskal is O(E*(V+E))
*/
class Graph 
{ 
public: 
	int V; 
	list<int> *mylist;  
	Graph(int V);  
	bool DFS(int e1, bool visited[], int parent); 
	void add(int e1, int e2);  
	void Remove(int e1, int e2); 
	void disp();
	bool cycle(); 
}; 

Graph::Graph(int V) 
{ 
	this->V = V; 
	mylist = new list<int>[V]; 
} 

void Graph::add(int e1, int e2) 
{ 
	mylist[e1].push_back(e2);
}
void Graph::Remove(int e1, int e2) 
{ 
	mylist[e1].remove(e2); 
}
void Graph::disp()
{
	list<int>::iterator i;
	for (int j = 0; j < V; j++)
		for (i = mylist[j].begin(); i != mylist[j].end(); i++) 
			if(j < *i)
				cout<<"("<<j <<", "<<*i<<")";
}
bool Graph::DFS(int v, bool visited[], int parent) 
{ 
	list<int>::iterator i; 
	visited[v] = true; 

	for (i = mylist[v].begin(); i != mylist[v].end(); i++) 
	{ 
		if (!visited[*i]) 
			if (DFS(*i, visited, v)) 
				return true; 

		else if (*i != parent) 
			return true; 
	} 
	return false; 
} 

bool Graph::cycle() 
{ 
	bool *visited = new bool[V]; 
	for (int i = 0; i < V; i++) 
		visited[i] = false; 

	
	for (int u = 0; u < V; u++) 
		if (!visited[u])
			if (DFS(u, visited, -1)) 
				return true; 

	return false; 
} 

void kruskal(vector<pair<int,pair<int,int>>> myvec, int size)
{
	Graph g(size);
	for(int i = 0; i < myvec.size(); i++)
	{
		g.add(myvec[i].second.first, myvec[i].second.second);
		if(g.cycle())
			g.Remove(myvec[i].second.first, myvec[i].second.second);
	}
	g.disp();
} 


int main(int argc, char** argv)
{
	ifstream infile;
	string f = argv[1];
	infile.open(f);
	if (!infile) 
	{
		cout << "Unable to open file";
		return 0;
	}
	getline(infile, line);
	ext = line.substr(2);
	stringstream str(ext);
	str >> size;
	for (int i = 0; i < size; i++)
	{
		getline(infile, line);
		
		ext = line.substr(line.find(":") + 2);
		//cout <<ext<<endl;
		istringstream extracted(ext);
		while(extracted)
		{
			string x;
			int num;
			extracted >> x;
			if(x == "")
				continue;

			int k = x.find(';');
			int st1 = stoi(x.substr(k+1));
			int st2 = stoi(x.substr(0, k));
			
			myvec.push_back(make_pair(st1, make_pair(i,st2)));
		}	

	}
	// for (int i = 0; i < myvec.size(); i++)
	// {
	// 	cout<<"Weight"<<myvec[i].first<<endl;
	// 	cout<<myvec[i].second.first<<endl;
	// 	cout<<myvec[i].second.second<<endl;
	// }
	sort(myvec.begin(), myvec.end()); 
	// cout<<"\nafter sorting\n";
	// for (int i = 0; i < myvec.size(); i++)
	// {
	// 	cout<<"Weight"<<myvec[i].first<<endl;
	// 	cout<<myvec[i].second.first<<endl;
	// 	cout<<myvec[i].second.second<<endl;
	// }	
	kruskal(myvec, size);
	return 0;
}

