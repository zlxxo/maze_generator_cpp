#include <iostream>
#include <vector>
#include <utility>
#include <stack>
#include <time.h>
#include <stdlib.h>

int main() {

    int length = 6;
    const int mul = 5; // barem 3

    std::vector<std::vector<int>> maze(length, std::vector<int>(length, -1));
    std::vector<std::vector<char>> gmaze(length*mul, std::vector<char>(length*mul, '#'));

    std::stack<std::pair<int, int>> current_path;

    srand((unsigned) time(NULL));
    int side = rand() % 4;
    int poc = rand() % length;
    std::pair<int, int> start(0, poc);
    if(side == 1) {
        start = std::make_pair(poc, 0);
    } else if(side == 2) {
        start = std::make_pair(length - 1, poc);
    } else if(side == 3) {
        start = std::make_pair(poc, length - 1);
    }

    maze[start.first][start.second] = 0;

    std::vector<std::pair<int, int>> selected;
    selected.push_back(start);
    std::pair<int, int> current(start);
    current_path.push(current);

    while(selected.size() < length*length) {

        int x = current.first;
        int y = current.second;
        int depth = maze[x][y];
        std::vector<std::pair<int, int>> neighbours;
        if(x > 0) {
            std::pair<int, int> p(x-1, y);
            bool contain = false;
            for(auto pr : selected) {
                if(pr.first == x-1 && pr.second == y) {
                    contain = true;
                    break;
                }
            }
            if(!contain) {
                neighbours.push_back(p);
                if(maze[p.first][p.second] == -1) {
                    maze[p.first][p.second] = depth + 1;
                }
            }
        }
        if(x < length - 1) {
            std::pair<int, int> p(x+1, y);
            bool contain = false;
            for(auto pr : selected) {
                if(pr.first == x+1 && pr.second == y) {
                    contain = true;
                    break;
                }
            }
            if(!contain) {
                neighbours.push_back(p);
                if(maze[p.first][p.second] == -1) {
                    maze[p.first][p.second] = depth + 1;
                }
            }
        }
        if(y > 0) {
            std::pair<int, int> p(x, y-1);
            bool contain = false;
            for(auto pr : selected) {
                if(pr.first == x && pr.second == y-1) {
                    contain = true;
                    break;
                }
            }
            if(!contain) {
                neighbours.push_back(p);
                if(maze[p.first][p.second] == -1) {
                    maze[p.first][p.second] = depth + 1;
                }
            }
        }
        if(y < length - 1) {
            std::pair<int, int> p(x, y+1);
            bool contain = false;
            for(auto pr : selected) {
                if(pr.first == x && pr.second == y+1) {
                    contain = true;
                    break;
                }
            }
            if(!contain) {
                neighbours.push_back(p);
                if(maze[p.first][p.second] == -1) {
                    maze[p.first][p.second] = depth + 1;
                }
            }
        }
        bool exist = neighbours.size() > 0;
        std::pair<int, int> next;
        int deapest = -1;
        if(exist) {
            next = neighbours[0];
            deapest = maze[next.first][next.second];
        }
        if(neighbours.size() > 1) {
            for(std::pair<int, int> p : neighbours) {
                if(maze[p.first][p.second] > deapest) {
                    next = p;
                    deapest = maze[p.first][p.second];
                } else if(maze[p.first][p.second] == deapest) {
                    int ran = rand() % 2;
                    if(ran == 1) {
                        next = p;
                    }
                }
            }
        }
        if(exist) {
            if(current.first == next.first - 1 && current.second == next.second) {
                for(int i = 1; i <= mul*2 - 2; i++) {
                    for(int j = 1; j <= mul - 2; j++) {
                        gmaze[current.first*mul + i][current.second*mul + j] = ' ';
                    }
                }
            } else if(current.first == next.first + 1 && current.second == next.second) {
                for(int i = 1; i <= mul*2 - 2; i++) {
                    for(int j = 1; j <= mul - 2; j++) {
                        gmaze[next.first*mul + i][next.second*mul + j] = ' ';
                    }
                }
            } else if(current.first == next.first && current.second == next.second - 1) {
                for(int i = 1; i <= mul*2 - 2; i++) {
                    for(int j = 1; j <= mul - 2; j++) {
                        gmaze[current.first*mul + j][current.second*mul + i] = ' ';
                    }
                }
            } else {
                for(int i = 1; i <= mul*2 - 2; i++) {
                    for(int j = 1; j <= mul - 2; j++) {
                        gmaze[next.first*mul + j][next.second*mul + i] = ' ';
                    }
                }
            }

            current = next;
            current_path.push(next);
            selected.push_back(next);
        } else {
            current_path.pop();
            if(!current_path.empty()) {
                current = current_path.top();
            } else {
                break;
            }
        }
    }

    std::pair<int, int> ending = start;
    int maxd = 0;
    for(int i = 0; i < length; i++){
        if(maxd < maze[i][0]) {
            ending = std::make_pair(i, 0);
            maxd = maze[i][0];
        }
    }

    for(int i = 0; i < length; i++){
        if(maxd < maze[0][i]) {
            ending = std::make_pair(0, i);
            maxd = maze[0][i];
        }
    }

    for(int i = 1; i <= mul - 2 ; i++) {
        for(int j = 1; j <= mul - 2; j++) {
            gmaze[start.first*mul + i][start.second*mul + j] = 's';
            gmaze[ending.first*mul + i][ending.second*mul + j] = 'e';
        }
    }

    std::vector<std::vector<char>> g; //(length*(mul - 1) + 2, std::vector<char>(length*(mul - 1) + 2, '#'));

    for(int i = 0; i < length*mul; i++){
        if(i % mul == mul - 1 && i != length*mul - 1) {
            continue;
        }
        std::vector<char> row;
        std::cout << "  ";
        for(int j = 0; j < length*mul; j++) {
            if(j % mul == mul - 1 && j != length*mul - 1) {
                continue;
            }
            row.push_back(gmaze[i][j]);
        }
        g.push_back(row);
        std::cout << std::endl;
    }

    for(int i = 0; i < g.size(); i++){
        std::cout << "  ";
        for(int j = 0; j < g[i].size(); j++) {
            std::cout << g[i][j] << g[i][j];
        }
        std::cout << std::endl;
    }

    return 0;
}
