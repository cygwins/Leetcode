#include <iostream>
#include <fstream>
#include <string>
#include <set>
using std::set;
using std::string;
using std::cout;
using std::ofstream;
using std::cin;
using std::endl;

set<string> possible;
int c;
void put( string, int);
bool win( string&);

int main() {
    ofstream fout("table.txt");
    cout << possible.size() << endl;
    put( string( 9, ' '), 1);
    int count = 0;
    possible. insert( string( 9, ' '));
    cout << possible.size() << endl;
    for( auto &s : possible) {
        fout << "\"" + s + "\",";
        if( ++count % 8 == 0) fout << endl;
    }
    return 0;
}

void put( string board, int who) { // who: 1='X', 0='O'
    for( int i = 0; i < 9; ++i) {
        if( board[i] == ' ') {
            if( who == 1) {
                board[i] = 'X';
            } else {
                board[i] = 'O';
            }
            possible. insert( board);
            if( win( board)) {
                board[i] = ' '; // restore original state
                continue;
            }
            put (board, 1 - who);
            board[i] = ' ';
        }
    }
}

bool win( string &board) {
    if(( board[0] != ' ' && board[0] == board[1] && board[2] == board[0]) || // upper row
       ( board[3] != ' ' && board[3] == board[4] && board[5] == board[3]) || // mid row
       ( board[6] != ' ' && board[6] == board[7] && board[8] == board[6]) || // mid row
       ( board[0] != ' ' && board[0] == board[3] && board[6] == board[0]) || // left col
       ( board[1] != ' ' && board[1] == board[4] && board[7] == board[1]) || // mid col
       ( board[2] != ' ' && board[2] == board[5] && board[8] == board[2]) || // right col
       ( board[0] != ' ' && board[0] == board[4] && board[8] == board[0]) || // diagonal
       ( board[2] != ' ' && board[2] == board[4] && board[6] == board[2]))   // anti diag
        return true;
    return false;
}
