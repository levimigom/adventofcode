string[] grid = ReadLines();
int rows = grid.Length;
int cols = grid[0].Length;
	
bool[,] visited = new bool[rows, cols];
	
for(int i = 0; i < rows; i++){
    for(int j = 0; j < cols; j++){
        if(grid[i][j] == 'S'){
            Console.WriteLine(Dfs(grid, grid.Length, grid[i].Length, i, j, visited));
        }
    }
}

string[] ReadLines() => File.ReadAllLines("input.txt");

bool IsValidPosition(int rows, int cols, int row, int col){
    return(0 <= row && row < rows && 0 <= col && col < cols);
}

int Dfs(string[] grid, int rows, int cols, int row, int col, bool[,] visited){
    if(!IsValidPosition(rows, cols, row, col) || visited[row, col]){
        return 0;
    }
	
    visited[row, col] = true;
    if(grid[row][col] == '^'){
        return 1 + Dfs(grid, rows, cols, row + 1, col - 1, visited) + Dfs(grid, rows, cols, row + 1, col + 1, visited);
    } else {
        return Dfs(grid, rows, cols, row + 1, col, visited);
    }
}