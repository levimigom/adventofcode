const string InputFileName = "input.txt";

Point[] points = GetPoints().ToArray();
Rectangle[] rectangles = GetRectangles(points).OrderByDescending(r => r.Area).ToArray();
Console.WriteLine(rectangles.First().Area);

IEnumerable<Point> GetPoints(){
    foreach(string line in File.ReadAllLines(InputFileName)){
        int[] parts = line.Split(",").Select(int.Parse).ToArray();
        yield return new Point(parts[0], parts[1]);
    }
}

IEnumerable<Rectangle> GetRectangles(Point[] points){
    for(int i = 1; i < points.Length; i++){
        for(int j = i + 1; j < points.Length; j++){
            yield return new Rectangle(points[i], points[j]);
        }
    }
}

public record Point(int X, int Y);

public class Rectangle(Point a, Point b){
    public Point A { get; set; } = a;
    public Point B { get; set; } = b;
	
    private long? _area;
    public long Area => _area ??= CalculateArea();
	
    private long CalculateArea(){
        return (1L + Math.Abs(A.X - B.X)) * (1L + Math.Abs(A.Y - B.Y));
    }
}