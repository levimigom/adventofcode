string[] lines = File.ReadLines("input.txt").ToArray();
IEnumerable<Problem> problems = ParseInput(lines);
	
Console.WriteLine(problems.Select(problem => problem.Solve()).Sum());

IEnumerable<Problem> ParseInput(string[] lines)
{
    string[] parts;
    int previousColumn = -1;
	
    for (int i = 0; i < lines[0].Length; i++)
    {
        if (IsColumnSeparator(lines, i))
        {
            parts = lines.Select(line => line[(previousColumn + 1)..(i)]).ToArray();
            yield return new Problem(parts);
            previousColumn = i;
        }
    }
	
    parts = lines.Select(line => line[(previousColumn + 1)..(line.Length)]).ToArray();
    yield return new Problem(parts);
}

bool IsColumnSeparator(string[] lines, int pos) => lines.Select(l => l[pos]).All(c => c == ' ');

public class Problem
{
    public Problem(IList<string> parts)
    {
        Op = parts.Last()[0];
		
        Numbers = new long[parts[0].Length];
        for(int i = 0; i < parts[0].Length; i++){
            for(int j = 0; j < parts.Count - 1; j++){
                if(parts[j][i] != ' '){
                    Numbers[i] = (10 * Numbers[i]) + parts[j][i] - '0';
                }
            }
        }
    }
	
    public long[] Numbers { get; set; }
    public char Op { get; set; }

    public long Solve()
    {
        if (Op.Equals('+'))
        {
            return Numbers.Sum();
        }

        return Numbers.Aggregate(1L, (x, y) => x * y);
    }
}