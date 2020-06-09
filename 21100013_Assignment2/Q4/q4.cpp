#include <iostream>
#include <string.h>
#include <vector>
#include <cstring>
#include <fstream>
#include <sstream>
#include <string>
#include <list>

using namespace std;
/*
We made a structure for rooms. Then we set all doors status according to the array. Then we found the gate with max repitions and for that 
gate we updated the status. We check if the returned max is 0 then it is not possible otherwise for the max value we update the value
of the doors and then update status. of the doors. If all doors are open then it is possible otherwise repeat until false the order
of this algorithm will be O(n^2).
*/
string line = "", ext = "";
int size = 0,  i = 0, k = 0;

struct myDoor
{
	string door1;
	string door2;
	char d1_st;
	char d2_st;
};

void checkdoors(myDoor doorarr[], char openclose[], int size)
{
	for(int i = 0; i < size; i++)
	{	
		string st1 = doorarr[i].door1;
		string st2 = doorarr[i].door2;
		if (st1[1] != 'a')
		{
			int ind1 = stoi(st1.substr(1));
			doorarr[i].d1_st = openclose[ind1]; 
		}
		else
		{
			int ind1 = stoi(st1.substr(2));
			if (openclose[ind1] == 'C')
				doorarr[i].d1_st = 'O';
			else
				doorarr[i].d1_st = 'C';
		}
		if (st2[1] != 'a')
		{
			int ind1 = stoi(st2.substr(1));
			doorarr[i].d2_st = openclose[ind1]; 
		}
		else
		{
			int ind1 = stoi(st2.substr(2));
			if (openclose[ind1] == 'C')
				doorarr[i].d2_st = 'O';
			else
				doorarr[i].d2_st = 'C';
		}

	}
}

int max(int arr[], int n)
{
	int max = 0;
	int maxi = 0;
	for (int i = 0; i < n; i++)
	{
		if(arr[i] >= max)
		{
			max = arr[i];
			maxi = i;
		}
	}
	return maxi;
}

bool checkopenclose(int doornums[], char openclose[], myDoor doorarr[], int size, int k)
{
	while (true)
	{
		int index = max(doornums, 2*k);
		if(doornums[index] == 0)
		{
			return false;
		}
		else
		{
		if(index%2 == 1)
		{
			doornums[index] = 0;
			int y = index/2;
			openclose[y] = 'C';

		}
		else
		{
			doornums[index] = 0;
			int y = index/2;
			openclose[y] = 'O';
		}
		checkdoors(doorarr, openclose, size);
		int counter = 0;
		for (int i = 0; i < k; i++)
		{	
			if(doorarr[i].d1_st == 'O' || doorarr[i].d2_st == 'O')
			{
				counter++;
			}
		}
		if (counter == k)
		{
			return true;
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
	str >> size;
	//cout << size<<endl;
	myDoor doorarr[size];
	int n = 0;
	getline(infile, line);
	ext = line.substr(2);
	stringstream str1(ext);
	str1 >> k;
	char openclose[k];
	int doornums[2*k];
	for(int i = 0; i < 2*k; i++)
		doornums[i] = 0;
	
	for (int i = 0; i < k; i++)
		openclose[i] = 'C';

	while(!infile.eof())
	{
		while(n < size)
		{	
			string x;
			infile >> x;
			doorarr[n].door1 = x;
			//cout << doorarr[n].door1 <<endl;
			infile >> x;
			doorarr[n].door2 = x;
			//cout << doorarr[n].door2 <<endl;
			n++;
		}
	}
	// for(int i = 0; i < size; i++)
	// {	
	// 	cout<<i<<endl;
	// 	cout<<doorarr[i].door1<<endl;
	// 	cout << doorarr[i].door2 <<endl;
	// }
	checkdoors(doorarr, openclose, size);
	
	for (int i = 0; i < size; i++)
	{
		if (doorarr[i].door1[1] == 'a')
		{
			int ind1 = stoi(doorarr[i].door1.substr(2));
			int x = (2*ind1) + 1;
			doornums[x]++;
		}
		else
		{
			int ind1 = stoi(doorarr[i].door1.substr(1));
			int x = 2*ind1;
			doornums[x]++;	
		}

		if (doorarr[i].door2[1] == 'a')
		{
			int ind1 = stoi(doorarr[i].door2.substr(2));
			int x = (2*ind1) + 1;
			doornums[x]++;
		}
		else
		{
			int ind1 = stoi(doorarr[i].door2.substr(1));
			int x = 2*ind1 ;
			doornums[x]++;	
		}

	}
	// for(int i = 0; i < 2*k; i++)
	// {
	// 	cout << doornums[i]<<endl; 
	// }

	
	bool check = checkopenclose(doornums,openclose,doorarr,size,k);
	string answer = "";
	if (check == true)
	{
		answer ="Yes\n";
		for(int i = 0; i < size; i++)
		{
			if(openclose[i] == 'C')
				answer += "0\n";
			else if(openclose[i] == 'O')
				answer += "1\n";
		}
	}
	else
	{
		answer = "No\n";
	}
	cout <<answer;
	


	return 0;
}