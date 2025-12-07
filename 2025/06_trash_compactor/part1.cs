string[][] lines = ReadLines();
string[][] transposed = Transpose(lines);
Problem[] problems = transposed.Select(r => 
    new Problem(r[0..(r.Count() - 1)].Select(s => long.Parse(s)).ToList(), r.Last()[0])).ToArray();
	
Console.WriteLine(problems.Select(p => p.Solve()).Sum());

string[][] ReadLines() 
    => File.ReadLines("input.txt").Select(line => line.Split(" ", StringSplitOptions.RemoveEmptyEntries)).ToArray();
	
string[][] Transpose(string[][] lines)
{
    int rows = lines.Count();
    int cols = lines.First().Count();

    return Enumerable.Range(0, cols)
        .Select(c => Enumerable.Range(0, rows).Select(r => lines[r][c]).ToArray()).ToArray();
}

public class Problem(IList<long> numbers, char op)
{
    public IList<long> Numbers { get; set; } = numbers;
    public char Op { get; set; } = op;

    public long Solve()
    {
        if (Op.Equals('+'))
        {
            return Numbers.Sum();
        }

        return Numbers.Aggregate(1L, (x, y) => x * y);
    }
}