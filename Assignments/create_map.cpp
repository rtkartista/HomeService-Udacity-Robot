// Grid(5x6):

// 0 1 0 0 0 0
// 0 1 0 0 0 0
// 0 1 0 0 0 0
// 0 1 0 0 0 0
// 0 0 0 1 1 0
// Where 1's represent obstacles and 0's represent free space.

// Robot Start position: 0,0

// Robot Goal Position: 4,5

// Direction of Movement: Up(-1,0) - left(0,-1) - down(1,0) - right(0,1)

// The Direction of Movement vector is a collection of four different 2D vectors each of which enables you to move between grid cells in the map.

// Movement Arrows: Up(^) - left(<) - down(v) - right(>)

// The Movement Arrows vector store the robot actions, this vector will be used later in this lab to visualize the robot orientation at each grid cell on the shortest path.

// Cost of Movement: 1

// The Cost of Movement value indicates how much it cost to move from one cell to another. Here, the cost is equal for all possible movements

#include <iostream>
#include <string.h>
#include <vector>
#include <algorithm>

using namespace std;

/* TODO: Define a Map class
   Inside the map class, define the mapWidth, mapHeight and grid as a 2D vector
*/

/* TODO: Define a Planner class
   Inside the Planner class, define the start, goal, cost, movements, and movements_arrows
   Note: The goal should be defined it terms of the mapWidth and mapHeight
*/

/* TODO: Define a print2DVector function which will print 2D vectors of any data type
   Example
   
   Input: 
   vector<vector<int> > a{{ 1, 0 },{ 0, 1 }};
   print2DVector(a);
   vector<vector<string> > b{{ "a", "b" },{ "c", "d" }};
   print2DVector(b);
   
   Output:
   1 0
   0 1
   a b
   c d
   Hint: You need to use templates
*/

/*############ Map Class ############*/
class Map
{
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

/*############ Planner Class ############*/
class Planner : Map
{
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

/*############ print2DVector function############*/
template <class T>
void print2DVector(vector<vector<T>> vector2D)
{
    for (int j = 0; j < vector2D[0].size(); j++) // row
    {
        for (int i = 0; i < vector2D.size(); i++) // coloumn
        {
            cout<<" "<<vector2D[j][i];
        }
        cout<<endl;  
    }  
}

/*############ Don't modify the main function############*/
int main()
{
    // Instantiate map and planner objects
    Map map;
    Planner planner;

    // Print classes variables
    cout << "Map:" << endl;
    print2DVector(map.grid);
    cout << "Start: " << planner.start[0] << " , " << planner.start[1] << endl;
    cout << "Goal: " << planner.goal[0] << " , " << planner.goal[1] << endl;
    cout << "Cost: " << planner.cost << endl;
    cout << "Robot Movements: " << planner.movements_arrows[0] << " , " << planner.movements_arrows[1] << " , " << planner.movements_arrows[2] << " , " << planner.movements_arrows[3] << endl;
    cout << "Delta:" << endl;
    print2DVector(planner.movements);

    return 0;
}
