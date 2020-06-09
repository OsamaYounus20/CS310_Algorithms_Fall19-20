#include <iostream>
#include <vector>
#include <cstring>
#include <fstream>
#include <sstream>
#include <string>
#include <list>
#include <vector>
#include <cmath>
using namespace std;
string string1 = "", string2 = "", string3 = "";
int s1_size = 0, s2_size = 0, s3_size = 0;
// the time complexity would be n*m
vector<int> v;
bool CheckValid()
{
	if(s1_size+s2_size != s3_size)
		return false;
	bool check[s1_size+1][s2_size+1];
	for(int i = 0; i < s1_size +1; i++)
		for(int j = 0; j < s2_size + 1; j++)
			check[i][j] = false;

	check[0][0] = true;
	for(int i = 0; i < s1_size+1; i++)
	{
		for(int j = 0; j < s2_size+1; j++)
		{
			if(i == 0 && j == 0)
				continue;
			else if (i == 0)
			{
				if(string2[j-1] == string3[j-1])
					check[i][j] = check[i][j-1];
			}
			else if (j == 0)
			{
				if(string1[i-1] == string3[i-1])
					check[i][j] = check[i-1][j];
			}
			else if(string2[j-1] != string3[i+j-1] && string1[i-1] == string3[i+j-1])
				check[i][j] = check[i-1][j];
			else if(string2[j-1] == string3[i+j-1] && string1[i-1] != string3[i+j-1])
				check[i][j] = check[i][j-1];
			else if(string2[j-1] == string3[i+j-1] && string1[i-1] == string3[i+j-1])
				check[i][j] = (check[i-1][j] || check[i][j-1]);
		}
	}
	if(check[s1_size][s2_size] == true)
	{
		int i = s1_size;
		int j = s2_size;		
		while(i != 0 || j != 0)
		{
			if(check[i][j] == true)
			{
				if(check[i-1][j] == true)
				{
					i--;
					v.push_back(1);
				}
				else if (check[i][j-1] == true)
				{
					j--;
					v.push_back(2);
				}
			}
		}
	}

	return check[s1_size][s2_size];
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
	getline(infile, string1);
	getline(infile, string2);
	getline(infile, string3);
	s1_size = string1.length();
	s2_size = string2.length();
	s3_size = string3.length();
	bool newans = CheckValid();
	//cout <<newans;
	
	int size = v.size();
	//cout << size << endl;
	string ans = "";
	if (newans == false)
	{
		ans += "Invalid";
	}
	else{
		for(int i = size-1; i >= 0; i--)
		{
			if(v[i] != v[i+1])
			{
				int val = abs(i-s3_size+1);
				ans += "\n" + to_string(v[i]) + ":" + string3[val];
			}
			else 
			{
				int val = abs(i-s3_size+1);
				ans += string3[val];
			}
		}
		ans = "Valid\n" + ans.substr(1);
	}
	cout <<ans<<endl;
	return 0;
}