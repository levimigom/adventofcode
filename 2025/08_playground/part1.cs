const int Iterations = 1000;
const string InputFileName = "input.txt";

List<JunctionBox> boxes = ReadInput().ToList();
List<Connection> connections = GetPossibleConnections(boxes).OrderBy(x => x.Distance).ToList();
	
for(int i = 0; i < Iterations; i++){
    connections[i].A.Neighbours.Add(connections[i].B);
    connections[i].B.Neighbours.Add(connections[i].A);
}
	
HashSet<JunctionBox> visited = [];
List<int> circuitSizes = [];
	
foreach(JunctionBox box in boxes){
    if(!visited.Contains(box)){
        circuitSizes.Add(Dfs(box, visited));
    }
}
	
List<int> orderedCircuitSizes = circuitSizes.OrderByDescending(x => x).ToList();
	
Console.WriteLine(orderedCircuitSizes[0] * orderedCircuitSizes[1] * orderedCircuitSizes[2]);

IEnumerable<JunctionBox> ReadInput(){
    foreach(string line in File.ReadLines(InputFileName)){
        int[] parts = line.Split(",").Select(p => int.Parse(p)).ToArray();
        yield return new JunctionBox(parts[0], parts[1], parts[2]);
    }
}

IEnumerable<Connection> GetPossibleConnections(List<JunctionBox> boxes){
    for (int i = 0; i < boxes.Count; i++){
        for (int j = i + 1; j < boxes.Count; j++){
            yield return new Connection(boxes[i], boxes[j], Distance(boxes[i], boxes[j]));
        }
    }
}

double Distance(JunctionBox from, JunctionBox to){
    double a = Math.Pow(Math.Abs(from.X - to.X), 2);
    double b = Math.Pow(Math.Abs(from.Y - to.Y), 2);
    double c = Math.Pow(Math.Abs(from.Z - to.Z), 2);
    return Math.Sqrt(a + b + c);
}

int Dfs(JunctionBox box, HashSet<JunctionBox> visited){
    if(visited.Contains(box)){
        return 0;
    }

    int junctions = 1;

    visited.Add(box);

    foreach (JunctionBox neighbour in box.Neighbours)
    {
        junctions += Dfs(neighbour, visited);
    }

    return junctions;
}

public class JunctionBox(int x, int y, int z)
{
    public int X { get; set; } = x;
    public int Y { get; set; } = y;
    public int Z { get; set; } = z;
    public HashSet<JunctionBox> Neighbours { get; } = [];
}

public record Connection(JunctionBox A, JunctionBox B, double Distance);