#include <iostream>
#include <vector>
#include <queue>
using namespace std;

using Square = bool;
const Square BLANK = true;
const Square WALL = false;

class Location {
public:
    int r, c;

    Location() = default;
    Location(int r, int c) : r(r), c(c) {}
    bool operator==(const Location &loc) const {
        return r == loc.r && c == loc.c;
    }
};

using LaserDirect = char;
const LaserDirect UP = 1;
const LaserDirect DW = 2;
const LaserDirect LE = 3;
const LaserDirect RI = 4;

class Maze;

class Status {
public:
    Location loc;
    bool has_laser;
    Location laser_loc;
    LaserDirect laser_direct;

    Status(Location loc, bool has_laser): loc(loc), has_laser(has_laser) {}

    void next(Maze &m, vector<Status>& next_status);
};

class Maze {
public:
    int rn, cn;
    vector<vector<Square>> maze;
    vector<vector<vector<Status>>> visited;

    Maze(int rn, int cn) : rn(rn), cn(cn) {
        maze.resize(rn, vector<Square>(cn, WALL));
        visited.resize(rn, vector<vector<Status>>(cn));
    }

    void set(Location loc, Square tile) {
        maze[loc.r][loc.c] = tile;
    }

    void set_visited(const Status& s) {
        visited[s.loc.r][s.loc.c].push_back(s);
    }

    bool is_visited(const Status& s) {
        for (const auto& v : visited[s.loc.r][s.loc.c]) {
            if (!s.has_laser) {
                if (v.has_laser) return true;
                else {
                    if (s.laser_loc == v.laser_loc && s.laser_direct == v.laser_direct) {
                        return true;
                    }
                }
            } else {
                if (v.has_laser) return true;
            }
        }
        return false;
    }

    Square get(Location loc) {
        return maze[loc.r][loc.c];
    }

    bool solve(Location start, Location end) {
        queue<Status> q;
        q.push(Status(start, true));
        vector<Status> next;
        while (!q.empty()) {
            Status s = q.front(); q.pop();
            if (s.loc == end) {
                return true;
            }
            set_visited(s);

            s.next(*this, next);
            for (const auto& n: next) q.push(n);
        }
        return false;
    }
};

void Status::next(Maze &m, vector<Status>& next_status) {
    next_status.clear();

    // up
    if (loc.r > 0) {
        Status n(*this);
        n.loc.r--;
        if (m.get(n.loc) == BLANK) {if (!m.is_visited(n)) next_status.push_back(n);}
        else if (!n.has_laser) { // check laser
            if (n.laser_loc.c == n.loc.c && n.laser_loc.r > n.loc.r) {
                if (!m.is_visited(n)) next_status.push_back(n);
            }
        } else { // use laser
            n.has_laser = false;
            n.laser_loc = loc;
            n.laser_direct = UP;
            {if (!m.is_visited(n)) next_status.push_back(n);}
        }
    }
    // down
    if (loc.r < m.rn - 1) {
        Status n(*this);
        n.loc.r++;
        if (m.get(n.loc) == BLANK) {if (!m.is_visited(n)) next_status.push_back(n);}
        else if (!n.has_laser) { // check laser
            if (n.laser_loc.c == n.loc.c && n.laser_loc.r < n.loc.r) {
                if (!m.is_visited(n)) next_status.push_back(n);
            }
        } else { // use laser
            n.has_laser = false;
            n.laser_loc = loc;
            n.laser_direct = DW;
            {if (!m.is_visited(n)) next_status.push_back(n);}
        }
    }
    // left
    if (loc.c > 0) {
        Status n(*this);
        n.loc.c--;
        if (m.get(n.loc) == BLANK) {if (!m.is_visited(n)) next_status.push_back(n);}
        else if (!n.has_laser) { // check laser
            if (n.laser_loc.r == n.loc.r && n.laser_loc.c > n.loc.c) {
                if (!m.is_visited(n)) next_status.push_back(n);
            }
        }  else { // use laser
            n.has_laser = false;
            n.laser_loc = loc;
            n.laser_direct = LE;
            {if (!m.is_visited(n)) next_status.push_back(n);}
        }
    }
    // right
    if (loc.c < m.cn - 1) {
        Status n(*this);
        n.loc.c++;
        if (m.get(n.loc) == BLANK) {if (!m.is_visited(n)) next_status.push_back(n);}
        else if (!n.has_laser) { // check laser
            if (n.laser_loc.r == n.loc.r && n.laser_loc.c < n.loc.c) {
                if (!m.is_visited(n)) next_status.push_back(n);
            }
        } else { // use laser
            n.has_laser = false;
            n.laser_loc = loc;
            n.laser_direct = RI;
            {if (!m.is_visited(n)) next_status.push_back(n);}
        }
    }
}



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
                    maze.set(Location(r, c), BLANK);
                    break;
                case 'E':
                    end = Location(r, c);
                    maze.set(Location(r, c), BLANK);
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
    

    if (maze.solve(start, end)) {
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
    }
}
