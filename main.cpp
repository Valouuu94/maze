#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <bits/stdc++.h>


using namespace std;

int rows, cols = 0;
vector<vector<char>> maze;


const char Entree = '1';
const char Sortie = '2';


class Coordinate
{
public:
    int X;
    int Y;
    Coordinate(int x = 0, int y = 0){
     X = x, Y = y;
    }
};

Coordinate entree;
Coordinate sortie;


void readFile(std::string file) {
    ifstream fp(file);

    if (!fp) {
        cout << "impossible d'ouvrir le fichier" << endl;
    }

    string line, item;
    while ( getline( fp, line ) ){
        rows++;
        std::vector<char> row;
        for (char &c : line) {
            if (c != ',') {
                row.push_back(c);
            }
        }
        maze.push_back(row);
    }
    cols = line.size();

}
void afficher() {
    for(int i = 0; i<rows; i++) {
        for(int j = 0; j<cols; j++) {
            cout<<maze[i][j];
        }
        cout<<endl;
    }
}
bool resoure(int X, int Y) {
    if (maze[Y][X] == Sortie)
        return true;
    if (maze[Y][X] == '*' || maze[Y][X] == 'x')
        return false;
     else {
        maze[Y][X] = 'x';

        if(X+1<cols)
            if (resoure(X + 1, Y))
                return true;
        if(Y-1>=0)
            if (resoure(X, Y - 1))
                return true;
        if(X-1>=0)
            if ( resoure(X - 1, Y))
                return true;
        if(Y+1<rows)
            if (resoure(X, Y + 1))
                return true;

    
    }
    
    return false;
}

bool entreeSortie() { //si entree ou sortie n'est pas trouvé renvoie 0
    bool e, s = false;
    for(int i = 0; i<rows; i++) {
        for (int j = 0; j < cols; j++) {
            if(maze[i][j] == Entree) {
                entree = Coordinate(j, i);
                e=true;
            }
            if(maze[i][j] == Sortie) {
                sortie = Coordinate(j, i);
                s=true;
            }
        }
    }
    return e && s;
}
int main(int argc, char* argv[])
{
    //cout<< argv[1];
    clock_t start, end;
    readFile("../maps/rect_05.map");
    if(entreeSortie()) {
        start = clock();
        if(resoure(entree.X, entree.Y)) {
            printf("resolut \n");
        }
        end = clock();
        afficher();

        double time_taken = double(end - start) / double(CLOCKS_PER_SEC);
        cout << time_taken << endl;
    }

    return 0;
}