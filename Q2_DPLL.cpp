#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

// Use to debug program

void print_vector( vector<vector<int>> temp ){
  for ( int i = 0; i < temp.size(); i++ ){
    cout << "[";
    for( int j = 0; j < temp[i].size(); j++){
      cout << temp[i][j];
      if ( j != temp[i].size() - 1) cout << ", ";
    }
    cout << "]" ;
    if ( i != temp.size() - 1) cout << ", ";
    else cout << endl;
  }
}

int main()
{
  string line;
  vector<vector<int>> formula;

  //Open File
  ifstream file("Input/CNF_1.txt");
  if( !file.is_open() ){
    cout << "Couldn't open the file" << "\n";
    return -1;
  }

  //Extract formula from the file
  while( getline(file,line) ){
    istringstream is( line );
    int n;
    vector<int> clause;

    while (is >> n) {
      clause.push_back(n);
    }

    formula.push_back(clause);
  }
  file.close();



  // print_vector( formula );

  return 0;
}
