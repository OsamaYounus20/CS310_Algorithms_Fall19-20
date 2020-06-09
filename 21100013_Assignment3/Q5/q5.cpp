#include <iostream>
#include <cstring>
#include <fstream>
#include <sstream>
#include <string>
#include <list>
#include <vector>
using namespace std;

struct Val
{
	int values;
	int index;
};

void merge(Val sorted[], int left, int mid, int right)
{
    
    int firstsize = 1 + mid - left;
    int secondsize = right - mid ;

    Val leftarr[firstsize];
    Val rightarr[secondsize];
    
	for(int x = 0; x < secondsize; x++)
		rightarr[x] = sorted[1 + mid + x];
    for (int x = 0; x < firstsize; x++)
		leftarr[x] = sorted[left + x];

	int l = 0, r = 0, m = left;

	while(l < firstsize && r < secondsize)
	{
		if(leftarr[l].values <= rightarr[r].values)
		{
			sorted[m] = leftarr[l];
			l++;
		}
		else 
		{
			sorted[m] = rightarr[r];
			r++;
		}
		m++;
	}
	while (r < secondsize)
	{
		sorted[m] = rightarr[r];
		m++;
		r++;
	}
	while (l < firstsize)
	{
		sorted[m] = leftarr[l];
		m++;
		l++;
	}

}

void mergesort(Val sorted[], int left, int right)
{
 	if (left < right)
 	{
 		int mid = left + (right - left)/2;
 		mergesort(sorted, left, mid);
    	mergesort(sorted, mid+1, right);
    	merge(sorted, left, mid, right);
 	}
}
string decode(int a, int b)
{
	if (a != b)
		return "N";
	return "Y";
}
void solver(Val structarr[], int x,int y,vector<int>& frequencies)
{
	string check = decode(structarr[x].values, structarr[y].values);
	if(check == "Y")
	{
		frequencies[structarr[x].values] += 1 + y - x;
	}
	else
	{
		int mid = 0.5*(x+y);
		solver(structarr, x, mid, frequencies);
		solver(structarr, mid+1, y, frequencies);
	}
}
string line = "", ext = "";
int arr_size = 0,  i = 0;
string answer = "";
int m;
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
	// cout << arr_size<<endl;
	getline(infile, line);
	ext = line.substr(2);
	stringstream str2(ext);
	str2 >> m;
	int data[arr_size];
	for (int i = 0; i < arr_size; i++)
		data[i] = 0;

	for (int i = 0; i < arr_size; i++)
	{
		int num;
		infile >> num;
		data[i] = num;
	}
	Val structarr[arr_size];
	for(int x = 0; x < arr_size; x++)
	{
		structarr[x].values = data[x];
		structarr[x].index = x;
	}
	mergesort(structarr, 0, arr_size-1);

	vector<int> frequencies(structarr[arr_size - 1].values + 1, 0); 
	solver(structarr, 0, arr_size-1, frequencies);
	int maxval = 0;
	int index = 0;
	for (int i = 0; i< frequencies.size(); i++)
	{
		if (frequencies[i] > maxval)
		{
			maxval = frequencies[i];
			index = i;
		}
	}
	string answer = "";
	string ans = "";
	for (int i = 0;i<arr_size;i++)
	{
		if (structarr[i].values==index)
		{
			ans=ans+" "+to_string(structarr[i].index);
		}
	}
	if(maxval > arr_size/2)
	{
		answer += "Success";
		answer += "\n";
		answer += "Dominant Species Count " + to_string(maxval);
		answer += "\n";
		answer += "Dominant Species Indices" + ans+"\n";
	}
	else
	{
		answer = "Failure";
	}
	cout<<answer;
	return 0;
}
