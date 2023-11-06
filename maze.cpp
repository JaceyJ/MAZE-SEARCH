/* CSCI 200: Assignment 5: Maze Search
 *
 * Author: Jacey Jonson
 *
 * Uses BFS and DFS to traverse a 2D array maze and reach the end (if possible)
 *    
 */


#include <iostream>
#include <fstream>
#include <stack>
#include <queue>
using namespace std;

//prints out the maze
void printMaze(char **MAZE_ARR, const size_t ROWS, const size_t COLS);

//performs BFS search
bool BFS(char **&maze,  int* START, const size_t ROWS, const size_t COLS, const bool TRACE);

//performs DFS search
bool DFS(char **&maze,  int* START, const size_t ROWS, const size_t COLS, const bool TRACE);

//checks if the index is valid in the list
bool valid(const int ROW, const int COL, const int R_MAX, const int C_MAX);

int main(int argc, char* argv[]) {
    // check program was started correctly
    string fileName;
    if(argc != 2) {
        cout << "Enter a file name to open: ";
        cin >> fileName;
       
    } else {
        fileName = argv[1];
    }

    cout << "Opening file \"" << fileName << "\"" << endl;
    ifstream fileIn;
    fileIn.open(fileName);
    if(fileIn.fail()){
        cerr << "Failed to Open File" << endl;
        return -1;
    } else {
        cout << "File opened successfully!" << endl;
    }

    
    //read the file into a maze vector 
    //read the length and width
    int rows, cols;
    int* start = new int[2];
    fileIn >> rows >> cols;
    char** maze = new char*[cols]; //is this process neccessary/helpful??
    //populate the number of rows need with temp values
    for(int i = 0; i < rows; i++){
        maze[i] = new char[cols];
    }
    //read the maze from the input file and add to array
    string x;
    int j = 0;
    while(!fileIn.eof()){
        fileIn >> x; //reads in a row
        for(int i = 0; i < x.size(); i++){
            maze[j][i] = x.at(i);
            if(x.at(i) == 'S'){
                start[0] = j;
                start[1] = i;
            }
        }
        j++; //move to the next row 
    }
    printMaze(maze, rows, cols);
//=========================================================================================
    //searching the list
    int choice;
    cout << endl << endl << "Enter 1 to search via BFS." << endl << "Enter 2 to search via DFS." << endl << "Choice: ";
    cin >> choice;
    while(cin.fail() || choice > 2 || choice < 0){
        cin.clear();
        cin.ignore();
        cout << endl << endl << "Enter 1 to search via BFS." << endl << "Enter 2 to search via DFS." << endl << "Choice: ";
        cin >> choice;
    }
    //prompts the user to enter whether or not they want to watch the maze solving process
    bool trace;
    char toFollow;
    cout << "Enter 'Y' to Follow the Maze Process: ";
    cin >> toFollow;
    if(toFollow == 'Y'){
        trace = true;
    }
    bool end;
    if(choice == 1){
        end = BFS(maze, start,rows, cols, trace);
    } else if (choice == 2){
        end = DFS(maze, start,rows, cols, trace);
    }

    cout << "===============================================" << endl;
    printMaze(maze, rows, cols);
    if(end){
        cout << "End was reached" << endl;
    } else {
        cout << "End cannot be reached" << endl;
    }
//==========================================================================================
    //print the list
    
    return 0;
}


bool BFS(char **&maze, int* START, const size_t ROWS, const size_t COLS, const bool TRACE){
    queue<int*> que;
    bool end = false;
    bool isVisited[ROWS][COLS];
    que.push(START);
    while(!que.empty()){
        int* curr = que.front();
        int x = curr[1];
        int y = curr[0];
        que.pop();
        
                if(!isVisited[y][x]){
                    //mark the current cell as visited
                    isVisited[y][x] = true;
                    if(maze[y][x] == 'E'){
                        end = true;
                        break;
                    }
                    maze[y][x] = '@';


                    //push all adjacent cells 
                        //add them regardless of if they are valid or not
                    int adjRow[4] = {1, -1, 0, 0};
                    int adjCol[4] = {0, 0, 1, -1};
                    for(int i = 0; i < 4; i++){
                        int* temp = new int[2];
                        temp[0] = y + adjRow[i];
                        temp[1] = x + adjCol[i];
                        if(valid(y + adjRow[i], x + adjCol[i], ROWS, COLS)){
                            if(maze[temp[0]][temp[1]] == '.' || maze[temp[0]][temp[1]] == 'E'){
                                que.push(temp);
                            }
                        }
                    }

                
            
        }
        if(TRACE){
            printMaze(maze, ROWS, COLS);
        }
    }
    if(end){
        return true;
    } 
    return false;
}



bool DFS(char **&maze, int* START, const size_t ROWS, const size_t COLS, const bool TRACE){
    stack<int*> st;
    bool end = false;
    bool isVisited[ROWS][COLS];
    st.push(START);
    while(!st.empty()){
        int* curr = st.top();
        int x = curr[1];
        int y = curr[0];
        st.pop();
        
                if(!isVisited[y][x]){
                    //mark the current cell as visited
                    isVisited[y][x] = true;
                    if(maze[y][x] == 'E'){
                        end = true;
                        break;
                    }
                    maze[y][x] = '@';


                    //push all adjacent cells 
                        //add them regardless of if they are valid or not
                    int adjRow[4] = {1, -1, 0, 0};
                    int adjCol[4] = {0, 0, 1, -1};
                    for(int i = 0; i < 4; i++){
                        int* temp = new int[2];
                        temp[0] = y + adjRow[i];
                        temp[1] = x + adjCol[i];
                        if(valid(y + adjRow[i], x + adjCol[i], ROWS, COLS)){
                            if(maze[temp[0]][temp[1]] == '.' || maze[temp[0]][temp[1]] == 'E'){
                                st.push(temp);
                            }
                        }
                    }

                
            
        }
        if(TRACE){
            printMaze(maze, ROWS, COLS);
        }
    }
    if(end){
        return true;
    } 
    return false;

}

void printMaze(char** MAZE_ARR, const size_t ROWS, const size_t COLS){
    for(int i = 0; i < ROWS; i++){
        for(int j = 0; j < COLS; j++){
            cout << MAZE_ARR[i][j];
        }
        cout << endl;
    }
    cout << endl;
}

bool valid(const int ROW, const int COL, const int R_MAX, const int C_MAX){
    if(ROW < 0 || COL < 0 || ROW >= R_MAX || COL >= C_MAX){
        return false;
    }
    return true;
}