string[] grid = File.ReadAllLines("input.txt");
int rows = grid.Length;
int cols = grid[0].Length;

long[,] cache = new long[rows, cols];
cache.Fill(Constants.CacheMiss);

for (int i = 0; i < rows; i++)
{
    for (int j = 0; j < cols; j++)
    {
        if (grid[i][j] == Constants.Start)
        {
            Console.WriteLine(Dfs(grid, grid.Length, grid[i].Length, i, j, cache));
        }
    }
}

bool IsValidPosition(int rows, int cols, int row, int col){
    return(0 <= row && row <= rows && 0 <= col && col < cols);
}

long Dfs(string[] grid, int rows, int cols, int row, int col, long[,] cache){
    if(!IsValidPosition(rows, cols, row, col)){
        return 0;
    }

    if (row == rows)
    {
        return 1;
    }

    if (cache[row, col] == Constants.CacheMiss)
    {
        if (grid[row][col] == Constants.Splitter)
        {
            cache[row, col] = Dfs(grid, rows, cols, row + 1, col - 1, cache) 
                              + Dfs(grid, rows, cols, row + 1, col + 1, cache);
        }
        else
        {
            cache[row, col] = Dfs(grid, rows, cols, row + 1, col, cache);
        }
    }

    return cache[row, col];
}

public static class Constants
{
    public const long CacheMiss = -1L;
    public const char Start = 'S';
    public const char Splitter = '^';
}

public static class Extensions {
    public static void Fill<T>(this T[,] arr, T value){
        for(int i = 0; i < arr.GetLength(0); i++){
            for(int j = 0; j < arr.GetLength(1); j++){
                arr[i, j] = value;
            }
        }
    }
}