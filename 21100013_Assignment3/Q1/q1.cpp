#include <iostream>
#include <cstring>
#include <fstream>
#include <sstream>
#include <string>
#include <list>
#include <vector>

using namespace std;

int findmin(int priority[], int size)
{
	int min = 99999999;
	int index = 0;
	for(int i = size-1; i >= 0; i--)
	{
		if (priority[i] < min)
		{
			min = priority[i];
			index = i;
		}
	}
	priority[index] = 88888888;
	return index;
}
string line = "", ext = "";
int arr_size = 0,  i = 0;
string answer = "";

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
	//cout << arr_size<<endl;
	string** data = new string*[arr_size];
	for (int i = 0; i < arr_size; i++)
		data[i] = new string[arr_size*2];
	
	int j = 0;
	while(!infile.eof())
	{
		string txt = "";
		getline(infile, line);
		string nline = line.substr(line.find(":")+2);
		// cout<<nline<<endl;
		istringstream extracted(nline);

		for(int i = 0; i <(2*arr_size); i++)
		{
			extracted >> txt;
			data[j][i] = txt;
		}
		j++;
		
	}
	vector<string> v;
	int priority[arr_size];
	for(int i = 0; i <arr_size; i++)
		priority[i] = 0;

	for(int x = 0; x < arr_size; x++)
	{
		for(int y = (arr_size*2) - 1; y>= 0; y--)
		{	
			string str = data[x][y];
			if (str == "-")
				continue;
			priority[x] = y;
			break;
		}
	}
	int count = 0;
	while(count < arr_size)
	{
		int x = findmin(priority, arr_size);
		for(int y = (arr_size*2) - 1; y>= 0; y--)
		{
			string str = data[x][y];
			if(str == "-")
				continue;
			vector<string>::iterator pointer;
			bool check = false;
			for(pointer = v.begin(); pointer < v.end(); pointer++)
			{
				if (*pointer == str)
				{
					check = true;
					break;
				}

			}
			if(check == true)
				continue;

			v.push_back(str);
			answer += str +" " + "T" + to_string((x+1)) + ", ";
			break;
		}	
		count++;
	}
	answer = "Final Destinations: " + answer.substr(0, answer.length()-2)+ "\n";
	cout << answer;
	return 0;
}