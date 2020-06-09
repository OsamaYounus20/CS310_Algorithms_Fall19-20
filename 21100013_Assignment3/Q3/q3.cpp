#include <iostream> 
#include <string.h>
#include <cstring>
#include <fstream>
#include <sstream>
#include <string>
#include <list>
#include <vector>
#include <utility> 

using namespace std;
  
// string boomerang(){
//  string ans = "";
//     ans = ans + to_string(1) + " ("+to_string(0)+","+to_string(1)+")" + " ("+to_string(1)+","+to_string(1)+") " + " ("+to_string(0)+","+to_string(0)+") " + "\n"; //trailing spaces and endlines dont matter
//     ans = ans + to_string(2)+" ("+to_string(0)+","+to_string(2)+")" + " ("+to_string(1)+","+to_string(3)+")  " + " ("+to_string(0)+","+to_string(3)+")" + "\n";
//     ans = ans + to_string(3)+" ("+to_string(2)+","+to_string(1)+") " + " ("+to_string(2)+","+to_string(2)+")" + " ("+to_string(1)+","+to_string(2)+")" + "\n";
//     ans = ans + to_string(4)+" ("+to_string(3)+","+to_string(1)+")" + " ("+to_string(2)+","+to_string(0)+")" + " ("+to_string(3)+","+to_string(0)+")" + "\n";
//     ans = ans + to_string(5)+" ("+to_string(2)+","+to_string(3)+")" + " ("+to_string(3)+","+to_string(2)+")" + " ("+to_string(3)+","+to_string(3)+")  " + "\n\n\n";
//     return ans;
// }
int** board;
int filler = 0;
int Case = 0;
struct MyIndexes
{
    int oneone;
    int onetwo;
    int twoone;
    int twotwo;
    int threeone;
    int threetwo;
};
vector<MyIndexes> v;
void BoardBreak(int indexr, int ind,  int indexc, int ind2, int intx,int inty)
{
    if(intx>=ind)
        if(inty>=ind2)
            Case = 4;
        else
            Case = 3;
    else
        if(inty>=ind2)
            Case = 2;
        else
            Case = 1;

    MyIndexes indexes;
    if(Case == 1)
    {
        board[ind][ind2] = filler;
        indexes.oneone = ind;
        indexes.onetwo = ind2;

        board[ind-1][ind2] = filler;
        indexes.twoone = ind-1;
        indexes.twotwo = ind2;
        board[ind][ind2-1] = filler;
        indexes.threeone = ind;
        indexes.threetwo = ind2-1;
        v.push_back(indexes);
        filler++;
        if(ind-indexr > 1)
        {
            BoardBreak(indexr, (indexr+ind)/2, indexc, (indexc+ ind2)/2, intx, inty);
            BoardBreak(indexr, (indexr+ind)/2, ind2, (ind2-indexc)/2+ind2, ind-1, ind2);
            BoardBreak(ind, (ind-indexr)/2+ind, indexc, (indexc+ ind2)/2, ind, ind2-1);
            BoardBreak(ind, (ind-indexr)/2+ind, ind2, (ind2-indexc)/2+ind2, ind, ind2);
        }
    }
    if(Case == 2)
    {
        board[ind][ind2] = filler;
        indexes.oneone = ind;
        indexes.onetwo = ind2;
        board[ind-1][ind2-1] = filler;
        indexes.twoone = ind-1;
        indexes.twotwo = ind2-1;
        board[ind][ind2-1] = filler;
        indexes.threeone = ind;
        indexes.threetwo = ind2-1;
        v.push_back(indexes);

        filler++;
        if(ind-indexr > 1)
        {
            BoardBreak(indexr, (indexr+ind)/2, indexc, (indexc+ ind2)/2, ind-1, ind2-1);
            BoardBreak(ind, (ind-indexr)/2+ind, indexc, (indexc+ ind2)/2, ind, ind2-1);
            BoardBreak(ind, (ind-indexr)/2+ind, ind2, (ind2-indexc)/2+ind2, ind, ind2);
            BoardBreak(indexr, (indexr+ind)/2, ind2, (ind2-indexc)/2+ind2, intx, inty);
        }
    }
    if(Case == 3)
    {
        board[ind][ind2] = filler;
        indexes.oneone = ind;
        indexes.onetwo = ind2;
        board[ind-1][ind2-1] = filler;
        indexes.twoone = ind-1;
        indexes.twotwo = ind2-1;
        board[ind-1][ind2] = filler;
        indexes.threeone = ind-1;
        indexes.threetwo = ind2;
        v.push_back(indexes);
        filler++;
        if(ind-indexr > 1)
        {
            BoardBreak(ind, (ind-indexr)/2+ind, ind2, (ind2-indexc)/2+ind2, ind, ind2);
            BoardBreak(indexr, (indexr+ind)/2, indexc,(indexc+ ind2)/2, ind-1, ind2-1);
            BoardBreak(ind, (ind-indexr)/2+ind, indexc, (indexc+ind2)/2, intx, inty);
            BoardBreak(indexr, (indexr+ind)/2, ind2, (ind2-indexc)/2+ind2, ind-1, ind2);
        }
    }
    if(Case == 4)
    {
        board[ind-1][ind2-1] = filler;
        indexes.oneone = ind-1;
        indexes.onetwo = ind2-1;
        board[ind-1][ind2] = filler;
        indexes.twoone = ind-1;
        indexes.twotwo = ind2;
        board[ind][ind2-1] = filler;
        indexes.threeone = ind;
        indexes.threetwo = ind2-1;
        v.push_back(indexes);
        filler++;
        if(ind-indexr > 1)
        {
            BoardBreak(indexr, (indexr+ind)/2, ind2, (ind2-indexc)/2+ind2, ind-1, ind2);
            BoardBreak(indexr, (indexr+ind)/2, indexc, (indexc+ ind2)/2, ind-1, ind2-1);
            BoardBreak(ind, (ind-indexr)/2+ind, ind2, (ind2-indexc)/2+ind2, intx, inty);
            BoardBreak(ind, (ind-indexr)/2+ind, indexc, (indexc+ ind2)/2, ind, ind2-1);
        }
    }
    return;
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
    // cout <<arr_size<<endl;
    getline(infile, line);
    // cout<<line<<endl;
    string x = line.substr(1, line.find(",")-1);
    //cout<<x<<endl;
    string y = line.substr(line.find(",")+1);
    y = y.substr(0, y.length()-1);
    //cout<<y<<endl;
    int intx = stoi(x);
    int inty = stoi(y);
    board = new int*[arr_size];
    for (int i = 0; i < arr_size; i++)
        board[i] = new int[arr_size];
    
    for(int i = 0; i< arr_size; i++)
        for(int j = 0; j< arr_size; j++)
            board[i][j] = 0;
    
    board[intx][inty] = -1;
    // for(int i = 0; i< arr_size; i++)
    // {
    //     for(int j = 0; j< arr_size; j++)
    //     {
    //         cout<<board[i][j];
    //     }
    //     cout<<endl;
    // }    

    BoardBreak(0, arr_size/2, 0, arr_size/2, intx, inty);

    // cout<<"New board"<<endl;
    string answer = "";
    for (int i = 0; i < v.size(); i++)
    {
        answer += to_string(i+1) + " (" + to_string(v[i].oneone) + "," + to_string(v[i].onetwo) + ") (" + to_string(v[i].twoone) + "," + to_string(v[i].twotwo) + ") (" + to_string(v[i].threeone) + "," + to_string(v[i].threetwo) +")\n";
    }
    
    cout<<answer;
    // string ans = boomerang();
 //    cout<<ans;

    return 0; 
} 
