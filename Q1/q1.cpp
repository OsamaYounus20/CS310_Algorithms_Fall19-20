#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <list>
using namespace std;
/*
I used adjacency list to store the data. I started with the first vertice and ran DFS on it. Time complexity of it will be O(V+E) where v
is the number of vertices and E is the number of edges. I stored the final vertices in an array colouring them according to the box they
should go in. To make the adjacency list I created an array of list. The time complexity for printing is O(V). Time complexity for file 
parsing is also O(V+E) 
*/ 
string line, ext;
int arr_size,  i = 0;
list <int> myqueue;
bool findcycle(list<int> ll_array[], int arr_size, int colorarray[]) 
{
	int i = 0;
	int qval = 0;
	int temp = 0;
	for (int i = 0; i < arr_size; i++) 
		colorarray[i] = 0;
	
	//color 1 = 1
	//color 2 = 2

	colorarray[0] = 1;
	myqueue.push_front(0);


	while (!myqueue.empty())
	{
		qval = myqueue.front();
		myqueue.pop_front();
		while(!ll_array[qval].empty())
		{
			temp = ll_array[qval].front();
			ll_array[qval].pop_front();
			if (colorarray[qval] == colorarray[temp])
			{
				myqueue.push_front(temp);
				//bipartite = true;
				return true;
			}
			else if (qval == temp)
			{
				myqueue.push_front(qval);
				//bipartite = true;
				return true;
			}
			else if (colorarray[temp] == 0)
			{
				if(colorarray[qval] == 1)
				{
					colorarray[temp] = 2;
					qval = temp;
					myqueue.push_front(qval);

				}
				else if (colorarray[qval] == 2)
				{
					colorarray[temp] = 1;
					qval = temp;
					myqueue.push_front(qval);
				}
			}
		}
	}
	return false;
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
    str >> arr_size;
    int colorarray[arr_size];

	list<int> ll_array[arr_size]; 
    //cout << arr_size<< endl << endl;
	while (!infile.eof()) 
	{
 		getline(infile, line);
 		ext = line.substr(line.find(":") + 2);
    	//cout<<ext<<endl<<endl;
    	istringstream extracted(ext);
    	while(extracted)
    	{
			string x;
			int num;
    		extracted >> x;
	    	if (x < "0" || x> "9")
    			break;

    		stringstream to_num(x);
    		to_num >> num;
    		ll_array[i].push_back(num);
    		//cout<<num<<endl;
    	}
    	//cout << endl;
    	i++;
	}
	infile.close();
	// for(int i = 0; i < arr_size; i++) {
	// while (!ll_array[i].empty()) {
	//     cout << ll_array[i].front()<<",";
	//     ll_array[i].pop_front();
	// 	}
	// 	cout << endl;
	// }
	
	bool cycle = findcycle(ll_array, arr_size, colorarray);
	if (cycle == true) 
	{
		string answer = "No\n";
		string conc;
		string conc_st;
		while(myqueue.size() > 1) 
		{
			conc = to_string(myqueue.front());
			myqueue.pop_front();
			answer += conc + "->";
		}
			conc = to_string(myqueue.front());
			answer += conc;
			myqueue.pop_front();
			cout<< answer;
	}
	else 
	{
		string answer = "Yes\n";
		for (int i = 0; i < arr_size; i++) 
		{
			if (colorarray[i] == 1)	
			{
				ostringstream convert;
				convert << i;
				string conc_st = convert.str();
				answer += conc_st + " ";
			}
		}
		answer= answer.substr(0, answer.length()-1);
		//cout << answer;
		answer += "\n";
		for (int i = 0; i < arr_size; i++) 
		{
			if (colorarray[i] == 2)
			{
				ostringstream convert;
				convert << i;
				string conc_st = convert.str();
				answer += conc_st + " ";
			}			
		}
		answer = answer.substr(0, answer.length()-1);
		answer += "\n";
		cout << answer;
	}
	return 0;
}
