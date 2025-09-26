#include<iostream>
#include<vector>
#include<deque>
#include<array>
using namespace std;
using Square = pair<short, short>;

const char START = 's';
const char END = 'e';
const char ROAD = ' ';
const char WALL = '#';
const char PATH = '*';    // draw the path when solvable
const char VISITED = '@'; // all reached squares
const Square NULL_SQUARE {-1, -1};

inline bool valid_square(const Square& s, int rn, int cn) {
    return s.first >= 0 && s.second >= 0 && s.first < rn && s.second < cn;
}

void solve_maze(vector<string>& maze) {
    // row number and column number of maze
    int rn = maze.size();
    if (rn <= 0) return;
    int cn = maze[0].size();
    if (cn <= 0) return;

    // find starting and ending points
    Square start = NULL_SQUARE, end = NULL_SQUARE;
    for (int i = 0; i < rn; i++) {
        string& s = maze[i];
        for (int j = 0; j < cn; j++) {
            if (s[j] == START) start = Square{i, j};
            else if (s[j] == END) end = Square{i, j};
        }
    }
    if (start == NULL_SQUARE) return;
    if (end == NULL_SQUARE) return;
    
    // bfs queue
    deque<Square> queue {start};
    vector<vector<Square>> previous(rn, vector<Square>(cn, NULL_SQUARE));
    vector<vector<bool>> visited(rn, vector<bool>(cn, false));

    visited[start.first][start.second] = true;

    while (!queue.empty()) {
        Square s = queue.front(); queue.pop_front();
        if (s == end) break;
        array<Square, 4> dirs {
            Square {s.first+1, s.second},
            Square {s.first-1, s.second},
            Square {s.first, s.second+1},
            Square {s.first, s.second-1}
        };
        for (Square& d : dirs) {
            if (valid_square(d, rn, cn) &&
                    maze[d.first][d.second] != WALL &&
                    !visited[d.first][d.second]) {
                previous[d.first][d.second] = s;
                visited[d.first][d.second] = true;
                queue.push_back(d);
            }
        }
    }

    for(int i = 0; i < rn; i++) {
        for (int j = 0; j < cn; j++) {
            if (visited[i][j] && 
                  maze[i][j] == ROAD) { // avoid the start and end
                maze[i][j] = VISITED;
            }
        }
    }

    Square path = previous[end.first][end.second];
    if (path == NULL_SQUARE) return; // unsolvable

    // draw path
    for (;path != start; path = previous[path.first][path.second]) {
        maze[path.first][path.second] = PATH;
    }
}

int main() {
    cout << "solve maze" << endl;
    vector<string> maze {
        " #s##    #  ",
        " # ## ## ## ",
        " #    ##    ",
        " # ##### ###",
        "       #e###"
    };
    solve_maze(maze);
    for (auto &s : maze) {
        cout << '|' << s << '|' << endl;
    }
    /*
    solve maze
    |@#s##****#  |
    |@#*##*##*## |
    |@#****##*@@ |
    |@#@#####*###|
    |@@@@@@@#e###|
    */
}
