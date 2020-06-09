#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <list>
#include <vector>
using namespace std;

string line, ext;
int arr_size,  i = 0;
vector<int> answer;
/*
Recurrence relation would be fun(vertex) = min(1 + fun(all child), total child + fun(all childs child))
Function will be called on the root. fun(all child) will do recurrsive call to each child of vertex and 
fun(all childs child) means recursive calls for each childs child. The function will return the least number of 
vertices that must be illuminated.
the base case of this would be fun(leaf) = 0
the time complexity of this would be O(V+E)
*/
int Light(int check[], vector<int> ll_array[], int vertex)
{
	vector<int> rootinc;
	vector<int> rootexc;
	// cout<<vertex<<endl;
	if(vertex != 0 && ll_array[vertex].size() == 1)
	{
		return 0;
	}
	if(check[vertex] != -1)
	{
		return check[vertex];
	}
	int totexc = 0;
	for (int i = 0; i < ll_array[vertex].size(); i++) 
	{
		int child = ll_array[vertex][i];
		if (ll_array[vertex][i] < vertex)
			continue;
		totexc++;
		rootexc.push_back(ll_array[vertex][i]);
		for(int j=1; j<ll_array[child].size(); j++)
		{
				totexc += Light(check, ll_array, ll_array[child][j]);
		}
	}
	int totinc = 1;
	rootinc.push_back(vertex);
	for (int i = 0; i < ll_array[vertex].size(); i++) 
	{

		if (ll_array[vertex][i] < vertex)
			continue;

		totinc += Light(check, ll_array, ll_array[vertex][i]);
	}
	int minlit = min(totinc, totexc);
	check[vertex]=minlit;
	bool checker = false;
	if (totinc <= totexc)
	{
		for (int i = 0; i < rootinc.size(); i++)
		{
			for (int j = 0; j < answer.size(); j++)
			{
				if (rootinc[i] == answer[j])
					checker = true;
			}
		if (checker == false)
			answer.push_back(rootinc[i]);
		}
	}
	else
	{
		for (int i = 0; i < rootexc.size(); i++)
		{
			for (int j = 0; j < answer.size(); j++)
			{
				if (rootexc[i] == answer[j])
					checker = true;
			}
		if (checker == false)
			answer.push_back(rootexc[i]);
		}
	}


	return check[vertex];

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
	vector<int>ll_array[arr_size]; 
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
	// 	cout<<i<<" -> ";
	// 	for(int j = 0; j < ll_array[i].size();j++)
	// 	{
	// 		cout<<ll_array[i][j]<<" ";
	// 	}
	// 	cout<<endl;
	// }

	int check[arr_size];
	for(int i = 0; i < arr_size; i++)
		check[i] = -1;
	int val = Light(check, ll_array, 0);
	string ans = "Minimum Lights " + to_string(val)+"\n{";

	for(int i = 0; i < answer.size(); i++)
	{
		ans+= to_string(answer[i])+", ";
	}
	ans = ans.substr(0, ans.length()-2) + "}\n";
	cout<<ans;
	return 0;
}