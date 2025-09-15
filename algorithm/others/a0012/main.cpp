#include <iostream>
#include <vector>
using namespace std;

using tile = bool;
const tile BLANK = true;
const tile WALL = false;

class Location {
public:
    int r, c;
    Location(int r, int c) : r(r), c(c) {}
    Location() = default;
};

class Maze {
public:
    int rn, cn;
    vector<vector<tile>> maze;
    Maze(int rn, int cn) : rn(rn), cn(cn) {
        maze.resize(rn, vector<tile>(cn, WALL));
    }
    void set(Location loc, tile tile) {
        maze[loc.r][loc.c] = tile;
    }
};

int main() {


    int rn, cn;
    cin >> rn >> cn;
    
    Location start, end;
    Maze maze(rn, cn);
    for (int r = 0; r < rn; r++) {
        for (int c = 0; c < cn; c++) {
            char tile;
            cin >> tile;
            switch (tile) {
                case 'S':
                    start = Location(r, c);
                    break;
                case 'E':
                    end = Location(r, c);
                    break;
                case '.':
                    maze.set(Location(r, c), BLANK);
                    break;
                case '#':
                    maze.set(Location(r, c), WALL);
                    break;
                default:
                    cout << "Invalid tile: " << tile << endl;
                    return 1;
            }
        }
    }
    
}
