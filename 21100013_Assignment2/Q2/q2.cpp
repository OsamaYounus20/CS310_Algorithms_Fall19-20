#include <iostream>
#include <vector>
#include <cstring>
#include <fstream>
#include <sstream>
#include <string>
#include <list>

using namespace std;
/*
In this we made a structure of Rack which stores the value of length/probability and the index of the rack. Then we sorted the rack 
with value of lenght/prob using mergesort implemented by arrays. Then using this sorted array we used the values in the given formula to find
the time. The time complexity of this algorithm is O(nlog(n)) due to mergesort.
*/
string line = "", ext = "";
int arr_size = 0,  i = 0;
struct Rack
{
	double lp;
	int index;
};

void merge(Rack sorted[], int left, int mid, int right)
{
    
    int firstsize = 1 + mid - left;
    int secondsize = right - mid ;

    Rack leftarr[firstsize];
    Rack rightarr[secondsize];
    
	for(int x = 0; x < secondsize; x++)
		rightarr[x] = sorted[1 + mid + x];
    for (int x = 0; x < firstsize; x++)
		leftarr[x] = sorted[left + x];

	int l = 0, r = 0, m = left;

	while(l < firstsize && r < secondsize)
	{
		if(leftarr[l].lp <= rightarr[r].lp)
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

void mergesort(Rack sorted[], int left, int right)
{
 	if (left < right)
 	{
 		int mid = left + (right - left)/2;
 		mergesort(sorted, left, mid);
    	mergesort(sorted, mid+1, right);
    	merge(sorted, left, mid, right);
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
	//cout << arr_size;

	getline(infile, line);
	ext = line.substr(2);
	int i = 0, j = 0;
	double length[arr_size], prob[arr_size], lp[arr_size];
	
	for(int x = 0; x < arr_size; x++)
		length[x] = 0;

	istringstream extracted(ext);
	while(extracted)
	{
		string x;
		double num;
		extracted >> x;

		stringstream to_num(x);
		to_num >> num;
		length[i] = num;
		i++;
		//cout<<num<<endl;
	}


	getline(infile, line);
	ext = line.substr(2);
	//cout << ext2<<endl;

	for(int x = 0; x < arr_size; x++)
		prob[x] = 0.0;

	
	istringstream extracted2(ext);
	while(extracted2)
	{
		string x;
		double num;
		extracted2 >> x;

		stringstream to_num2(x);
		to_num2 >> num;
		prob[j] = num;
		j++;
		//cout<<num<<endl;
	}

	// for(int x = 0; x < arr_size; x++)
	// 	cout << length[x]<< endl;

	// cout << "--------------------"<<endl;

	// for(int x = 0; x < arr_size; x++)
	// 	cout << prob[x]<< endl;

	for(int x = 0; x < arr_size; x++)
		lp[x] = length[x]/prob[x];

	// for(int x = 0; x < arr_size; x++)
	// 	cout << lp[x] << endl;

	Rack structarr[arr_size];
	for(int x = 0; x < arr_size; x++)
	{
		structarr[x].lp = lp[x];
		structarr[x].index = x;
	}


	mergesort(structarr, 0, arr_size - 1);	
	double val;
	int in, in2;
	for(int x = 0; x < arr_size; x++)
	{
		in2 = structarr[x].index;

		for(int y = 0; y <= x; y++)
		{
			in = structarr[y].index;
			val = val + (prob[in2] * length[in]);
		}
	}

	string answer = "";
	for(int x = 0; x < arr_size; x++)
	{
		ostringstream convert;
		convert << structarr[x].index + 1;
		string conc_st = convert.str();
		answer += conc_st + " ";
	}
	answer = answer.substr(0, answer.length()-1);
	ostringstream convert;
	convert << val;
	string conc_st = convert.str();
	answer += "\nExpected Time " + conc_st;
	cout << answer;

	

	return 0;
}