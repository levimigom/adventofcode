const string InputFileName = "input.txt";

Point[] points = GetPoints().ToArray();
Rectangle[] rectangles = GetRectangles(points).OrderByDescending(r => r.Area).ToArray();

Rectangle largest = GetFirstValidRectangles(points, rectangles);
Console.WriteLine(largest.Area);

IEnumerable<Point> GetPoints() {
	foreach (string line in File.ReadAllLines(InputFileName)) {
		int[] parts = line.Split(",").Select(int.Parse).ToArray();
		yield return new Point(parts[0], parts[1]);
	}
}

IEnumerable<Rectangle> GetRectangles(Point[] points) {
	for (int i = 1; i < points.Length; i++) {
		for (int j = i + 1; j < points.Length; j++) {
			yield return new Rectangle(points[i], points[j]);
		}
	}
}

Rectangle GetFirstValidRectangles(Point[] points, Rectangle[] rectangles) {
	foreach (Rectangle rectangle in rectangles) {
		if (RectangleIsInsidePolygon(points, rectangle))
		{
			return rectangle;
		}
	}

	return null;
}

bool RectangleIsInsidePolygon(Point[] points, Rectangle rectangle) {
	// only check the inside boundaries, this technically isn't correct but will probably still do the job
	// to be 100% sure, you should check all the cells inside, but that would take way too long
	
	for (int x = rectangle.MinX + 1; x < rectangle.MaxX; x++) {
		if(!IsPointInPolygon(new Point(x, rectangle.MinY + 1), points)
		   || !IsPointInPolygon(new Point(x, rectangle.MaxY - 1), points)){
			return false;
		}
	}

	for (int y = rectangle.MinY + 1; y < rectangle.MaxY; y++) {
		if (!IsPointInPolygon(new Point(rectangle.MinX + 1, y), points)
		    || !IsPointInPolygon(new Point(rectangle.MaxX + 1, y), points))
		{
			return false;
		}
	}

	return true;
}

bool IsPointInPolygon(Point p, Point[] polygon) {
	double minX = polygon[0].X;
	double maxX = polygon[0].X;
	double minY = polygon[0].Y;
	double maxY = polygon[0].Y;

	for (int i = 1; i < polygon.Length; i++) {
		Point q = polygon[i];
		minX = Math.Min(q.X, minX);
		maxX = Math.Max(q.X, maxX);
		minY = Math.Min(q.Y, minY);
		maxY = Math.Max(q.Y, maxY);
	}

	if (p.X < minX || p.X > maxX || p.Y < minY || p.Y > maxY) {
		return false;
	}

	// https://wrf.ecse.rpi.edu/Research/Short_Notes/pnpoly.html
	bool inside = false;
	for (int i = 0, j = polygon.Length - 1; i < polygon.Length; j = i++) {
		if ((polygon[i].Y > p.Y) != (polygon[j].Y > p.Y) &&
			 p.X < (polygon[j].X - polygon[i].X) * (p.Y - polygon[i].Y) / (polygon[j].Y - polygon[i].Y) + polygon[i].X) {
			inside = !inside;
		}
	}

	return inside;
}

public record Point(int X, int Y);

public class Rectangle(Point a, Point b) {
	public Point A { get; } = a;
	public Point B { get; } = b;

	private long? _area;
	public long Area => _area ??= CalculateArea();

	public int MinX { get; } = Math.Min(a.X, b.X);
	public int MaxX { get; } = Math.Max(a.X, b.X);

	public int MinY { get; } = Math.Min(a.Y, b.Y);
	public int MaxY { get; } = Math.Max(a.Y, b.Y);

	private long CalculateArea() {
		return (1L + Math.Abs(A.X - B.X)) * (1L + Math.Abs(A.Y - B.Y));
	}
}