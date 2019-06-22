#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

enum bcp_status{sat, unsat, cont};

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
    else cout << endl << endl;
  }
}

bool in_vector ( vector<int> vec, int item ) {
  vector<int>::iterator it;
  it = find(vec.begin(), vec.end(), item);

  if(it == vec.end()) return false;
  return true;
}

enum bcp_status BCP(  vector< vector< int > >& formula, int var) {
  vector< vector< int > > copy = formula;

  for ( int i = 0; i < copy.size(); i++ ) {

    if (in_vector(copy[i], var)) {
      copy.erase(copy.begin() + i);
      i--;
    }
    else if(in_vector(copy[i], -var) && copy[i].size() != 0) {
      copy[i].erase(find(copy[i].begin(), copy[i].end(), -var));
    }
    else if(in_vector(copy[i], -var)) {
      return unsat;
    }
  }

  if (copy.size() == 0) return sat;

  formula = copy;
  return cont;
}

string DPLL(  vector<vector<int>> formula, int assn ) {
  print_vector(formula);

  enum bcp_status res = BCP(formula, assn);

  if ( res == sat ) return "SAT";
  else if ( res == unsat ) return "UNSAT";

  if ( DPLL( formula, formula[0][0]) == "SAT" ) return "SAT";
  return DPLL( formula, -formula[0][0] );
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

  string ret = DPLL(formula, formula[0][0]);

  cout << "This Formula is " << ret << endl;

  return 0;
}
