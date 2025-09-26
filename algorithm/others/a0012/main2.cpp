#include <iostream>
#include <vector>
#include <array>
using namespace std;

bool solve(vector<vector<bool>>& maze, pair<short, short> start, pair<short, short> end) {
    if (start.first == end.first) return true;
    if (start.second == end.second) return true;

    int rn = maze.size(), cn = maze[0].size();
    vector<vector<bool>> visited(rn, vector<bool>(cn, false));
    vector<pair<short, short>> q_start, q_end;
    q_start.push_back(start); q_end.push_back(end);

    vector<bool> row_start_visited(rn, false), row_end_visited(rn, false);
    vector<bool> col_start_visited(cn, false), col_end_visited(cn, false);

    while(!q_start.empty() || !q_end.empty()) {
        if (!q_start.empty()) {
            auto cur = q_start.back(); q_start.pop_back();
            short r = cur.first, c = cur.second;
            if (row_end_visited[r]) return true;
            if (col_end_visited[c]) return true;
            visited[r][c] = true;
            /**
             * Set the adjacent row / column visited
             * See the following example to understand
             * ..###
             * S####
             * #####
             * ##.E#
             */
            row_start_visited[r] = true; col_start_visited[c] = true;
            row_start_visited[r+1] = true; col_start_visited[c+1] = true;
            row_start_visited[r-1] = true; col_start_visited[c-1] = true;

            for (auto next : array<pair<short, short>, 4>{make_pair(r - 1, c), make_pair(r + 1, c), make_pair(r, c - 1), make_pair(r, c + 1)}) {
                short nr = next.first, nc = next.second;
                if (visited[nr][nc]) continue;
                if (!maze[nr][nc]) continue;
                q_start.push_back(make_pair(nr, nc));
            }
        }

        if (!q_end.empty()) {
            auto cur = q_end.back(); q_end.pop_back();
            short r = cur.first, c = cur.second;
            if (row_start_visited[r]) return true;
            if (col_start_visited[c]) return true;
            visited[r][c] = true;
            row_end_visited[r] = true; col_end_visited[c] = true;
            row_end_visited[r+1] = true; col_end_visited[c+1] = true;
            row_end_visited[r-1] = true; col_end_visited[c-1] = true;

            for (auto next : array<pair<short, short>, 4>{make_pair(r - 1, c), make_pair(r + 1, c), make_pair(r, c - 1), make_pair(r, c + 1)}) {
                short nr = next.first, nc = next.second;
                if (visited[nr][nc]) continue;
                if (!maze[nr][nc]) continue;
                q_end.push_back(make_pair(nr, nc));
            }
        }
    }
    return false;
}

int main() {
    int rn, cn;
    cin >> rn >> cn;
    
    pair<short, short> start, end;
    // surround maze with walls skipping validation
    vector<vector<bool>> maze(rn+2, vector<bool>(cn+2, false));
    for (int r = 1; r <= rn; r++) {
        for (int c = 1; c <= cn; c++) {
            char tile;
            cin >> tile;
            switch (tile) {
                case 'S':
                    start = make_pair(r, c);
                    maze[r][c] = true;
                    break;
                case 'E':
                    end = make_pair(r, c);
                    maze[r][c] = true;
                    break;
                case '.':
                    maze[r][c] = true;
                    break;
                case '#':
                    // maze[r][c] = false;
                    break;
                default:
                    cout << "Invalid tile: " << tile << endl;
                    return 1;
            }
        }
    }
    

    if (solve(maze, start, end)) {
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
    }
}
