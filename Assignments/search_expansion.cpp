// you’ll write the search function which will expand the cells with the lowest cost until the goal is reached.

// For that, you will need to represent each cell with a triplet value [g, x, y] where g represents the total cost of expanding toward this cell, x is the row value, and y is the column value.

// Your function should print the final triplet value of the goal once it expands towards it.

/* Steps To Follow
As you expand towards a new cell, check if you have reached the goal; and once you reach it, print its triplet value.
Actively check if you have reached a roadblock. If you do, stop expanding and print a message indicating that you have failed to reach the goal.
Expand the cells with the lowest g value and store your expansions in an open vector. If two cells have equal g values, then you can to pick one of them to expand further.
Each cell in the expansion vector will store the order at which it was expanded. 
Some of the cells were never expanded, and should show a value of -1.
Expansion #: 11
Open List: [10 1 3 ], [10 0 2 ], [9 3 4 ], [9 2 3 ]
Cell Picked: [9 2 3]

The final step is to print the shortest path that the robot has to take in order to travel 
from start to goal. You will need to record each action that the robot should take
(ex: turning left <) and store all the actions in a policy 2D vector.



*/

#include <iostream>
#include <string.h>
#include <vector>
#include <algorithm>

using namespace std;

// Map class
class Map {
public:
    const static int mapWidth = 6;
    const static int mapHeight = 5;
    vector<vector<int> > grid = {
        { 0, 1, 0, 0, 0, 0 },
        { 0, 1, 0, 0, 0, 0 },
        { 0, 1, 0, 0, 0, 0 },
        { 0, 1, 0, 0, 0, 0 },
        { 0, 0, 0, 1, 1, 0 }
    };
};

// Planner class
class Planner : Map {
public:
    int start[2] = { 0, 0 };
    int goal[2] = { mapHeight - 1, mapWidth - 1 };
    int cost = 1;

    string movements_arrows[4] = { "^", "<", "v", ">" };

    vector<vector<int> > movements{
        { -1, 0 },
        { 0, -1 },
        { 1, 0 },
        { 0, 1 }
    };
};

// Template function to print 2D vectors of any type
template <typename T>
void print2DVector(T Vec)
{
    for (int i = 0; i < Vec.size(); ++i) {
        for (int j = 0; j < Vec[0].size(); ++j) {
            cout << Vec[i][j] << ' ';
        }
        cout << endl;
    }
}

/*#### TODO: Code the search function which will generate the expansion list ####*/
/* #### TODO: Modify the search function to generate and print the expansion 2D vector #### */

// You are only required to print the final triplet values
void search(Map map, Planner planner)
{
    // Create a closed 2 array filled with 0s and first element 1
    vector<vector<int> > closed(map.mapHeight, vector<int>(map.mapWidth));
    closed[planner.start[0]][planner.start[1]] = 1;

    // Defined the triplet values
    int x = planner.start[0];
    int y = planner.start[1];
    int g = 0;

    // Store the expansions
    vector<vector<int> > open;
    open.push_back({ g, x, y });

    // Flags
    bool found = false;
    bool resign = false;

    int x2;
    int y2;
    int count = 0;
    // Create expand array filled with -1
    vector<vector<int> > expand(map.mapHeight, vector<int>(map.mapWidth, -1));
    
    // While I am still searching for the goal and the problem is solvable
    while (!found && !resign) {
        // Resign if no values in the open list and you can't expand anymore
        if (open.size() == 0) {
            resign = true;
            cout << "Failed to reach a goal" << endl;
        }
        // Keep expanding
        else {
            // Remove triplets from the open list
            sort(open.begin(), open.end());
            reverse(open.begin(), open.end());
            vector<int> next;
            // Stored the poped value into next
            next = open.back();
            open.pop_back();

            x = next[1];
            y = next[2];
            g = next[0];

            // Fill the expand vectors with count
            expand[x][y] = count;
            count += 1;
            
            // Check if we reached the goal:
            if (x == planner.goal[0] && y == planner.goal[1]) {
                found = true;
                cout << "[" << g << ", " << x << ", " << y << "]" << endl;
            }

            //else expand new elements
            else {
                for (int i = 0; i < planner.movements.size(); i++) {
                    x2 = x + planner.movements[i][0];
                    y2 = y + planner.movements[i][1];
                    if (x2 >= 0 && x2 < map.grid.size() && y2 >= 0 && y2 < map.grid[0].size()) {
                        if (closed[x2][y2] == 0 and map.grid[x2][y2] == 0) {
                            int g2 = g + planner.cost;
                            open.push_back({ g2, x2, y2 });
                            closed[x2][y2] = 1;
                        }
                    }
                }
            }
        }
    }
    // Print the expansion List
    print2DVector(expand);
}

int main()
{
    // Instantiate map and planner objects
    Map map;
    Planner planner;

    // Search for the expansions
    search(map, planner);

    return 0;
}
