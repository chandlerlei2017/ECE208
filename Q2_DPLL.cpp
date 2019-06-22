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
  cout << "[";
  for ( int i = 0; i < temp.size(); i++ ){
    cout << "[";
    for( int j = 0; j < temp[i].size(); j++){
      cout << temp[i][j];
      if ( j != temp[i].size() - 1) cout << ", ";
    }
    cout << "]" ;
    if ( i != temp.size() - 1) cout << ", ";
  }
  cout << "]" << endl;
}

// Determine if element is in the vector
bool in_vector ( vector<int> vec, int item ) {
  vector<int>::iterator it;
  it = find(vec.begin(), vec.end(), item);

  if(it == vec.end()) return false;
  return true;
}

void UR( vector< vector< int > >& formula ){
  for ( int i = 0; i < formula.size(); i++ ) {
    if ( formula[i].size() != 1 ) break;
    bool flag = false;

    for( int j = 0; j < formula.size(); j++ ){
      if( formula[j].size() <= 1 || !in_vector(formula[j], -formula[i][0]) ) break;

      formula[j].erase(find( formula[j].begin(), formula[j].end(), -formula[i][0]));
      flag = true;
    }

    if (flag){
      formula.erase(formula.begin() + i);
      i--;
    }
  }
}

// BCP to simplify formula
enum bcp_status BCP(  vector< vector< int > >& formula, int var ) {
  vector< vector< int > > copy = formula;

  for ( int i = 0; i < copy.size(); i++ ) {
    if (in_vector(copy[i], var) && copy[i].size() > 1) {
      copy.erase(copy.begin() + i);
      i--;
    }
    else if(in_vector(copy[i], -var) && copy[i].size() > 1) {
      copy[i].erase(find(copy[i].begin(), copy[i].end(), -var));
    }
    else if(in_vector(copy[i], -var)) {
      return unsat;
    }
  }

  // Unit Resolution

  UR(copy);

  print_vector(copy);

  if ( copy.size() == 0 ) return sat;

  formula = copy;
  return cont;
}

// DPLL to determine satisfiability
bool DPLL(  vector<vector<int>> formula, int assn ) {
  enum bcp_status res = BCP(formula, assn);

  if ( res == sat ) return true;
  else if ( res == unsat ) return false;

  return DPLL( formula, formula[0][0] ) || DPLL( formula, -formula[0][0] );
}

int main()
{
  string line;
  vector<vector<int>> formula;

  //Open File
  ifstream file("Input/CNF_2.txt");
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

  bool ret = DPLL(formula, formula[0][0]) || DPLL(formula, -formula[0][0]) ;

  string ret_val = (ret) ? "SAT" : "UNSAT";

  cout << "This Formula is " << ret_val << endl;

  return 0;
}
