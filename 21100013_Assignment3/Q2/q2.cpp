#include <iostream>
#include <cstring>
#include <fstream>
#include <sstream>
#include <string>
#include <list>
#include <vector>
using namespace std;

struct Case
{
	int cells;
	int index;
};

int count = 0;
string answer = "";
void merge(Case sorted[], int left, int mid, int right)
{
    int firstsize = 1 + mid - left;
    int secondsize = right - mid ;
    Case leftarr[firstsize];
    Case rightarr[secondsize];
	for(int x = 0; x < secondsize; x++)
		rightarr[x] = sorted[1 + mid + x];
    for (int x = 0; x < firstsize; x++)
		leftarr[x] = sorted[left + x];

	int l = 0, r = 0;
	while(r < secondsize)
	{

		for (l = 0; l < firstsize; l++)
		{
			if(2*rightarr[r].cells < leftarr[l].cells)
			{
				answer += "(" + to_string(rightarr[r].index) + "," + to_string(leftarr[l].index) + ") ";
				count++;
			}
			answer = answer.substr(0, answer.length() - 1);
			answer += "\n";
		}
		r++;
	}
	while (r < secondsize)		
		r++;
	
	while (l < firstsize)
		l++;
}

void mergesort(Case sorted[], int left, int right)
{
	
 	if (left < right)
 	{
 		int mid = left + (right - left)/2;
 		mergesort(sorted, left, mid);
    	mergesort(sorted, mid+1, right);
    	merge(sorted, left, mid, right);

 	}
}


string line = "", ext = "";
int arr_size = 0,  i = 0;
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
	int data[arr_size];
	for (int i = 0; i < arr_size; i++)
		data[i] = 0;

	for (int i = 0; i < arr_size; i++)
	{
		int num;
		infile >> num;
		data[i] = num;
	}
	Case structarr[arr_size];
	for(int x = 0; x < arr_size; x++)
	{
		structarr[x].cells = data[x];
		structarr[x].index = x;
	}


	mergesort(structarr, 0, arr_size-1);
	string answer2 = "Failed Trials " + to_string(count) + "\n";
	answer2 += answer;
	cout <<answer2;
	return 0;
}