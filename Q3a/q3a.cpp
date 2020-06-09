#include <iostream> 
#include <string.h>
#include <fstream>
#include <string>
#include <sstream>
#include <list>
#include <vector>

using namespace std; 

list <int> myqueue;
list <int> sorted;
string line, ext;
int arr_size,  i = 0;


void Topo_Sort(int arr_size, list<int> ll_array[])
{
	vector <int> myvector(arr_size, 0);
	for (int i = 0; i < arr_size; i++)
	{
		while(!ll_array[i].empty())
		{
			cout <<"works 1"<<endl;
			int x = ll_array[i].front();
			ll_array[i].pop_front();
			myvector[x]++;
		}
	}
	int size = myvector.size();
	for (int i = 0; i < size; i++) 
	{
		if(myvector[i] == 0)
			myqueue.push_front(i);
	}

	while(!myqueue.empty())
	{
		cout <<"works 2"<<endl;
		int val = myqueue.front();
		cout << val<< endl;
		myqueue.pop_front();
		sorted.push_front(val);
		while(!ll_array[val].empty())
		{
			cout << "Hi" << endl;
			myvector[val]--;
			if (myvector[val] == 0)
			{
				myqueue.push_front(val);
				ll_array[val].pop_front();		
			}
		}
	}




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
 		if (line.size() < 4)
 		{
 			continue;
 		}
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

	Topo_Sort(arr_size, ll_array);
	string st = "";
	string answer = "";
	while(!sorted.empty())
	{
		st = to_string(sorted.front());
		answer += st + " ";
		sorted.pop_front();
	}
	cout << answer;

    return 0; 
} 

