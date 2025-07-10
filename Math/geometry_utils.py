import math


# === Basic Point Class ===
class Point:
    def __init__(self, x, y):
        self.x = x
        self.y = y

    def __lt__(self, other):  # for sorting
        return (self.x, self.y) < (other.x, other.y)

    def __sub__(self, other):  # Vector subtraction
        return Point(self.x - other.x, self.y - other.y)

    def __repr__(self):
        return f"({self.x}, {self.y})"


# === 1. Distance between two points ===
def distance(p1, p2):
    """
    Returns Euclidean distance between p1 and p2.
    """
    return math.hypot(p1.x - p2.x, p1.y - p2.y)


# === 2. Orientation test (Cross Product) ===
def cross(o, a, b):
    """
    Cross product of vectors OA and OB.
    Positive if counter-clockwise, negative if clockwise.
    """
    return (a.x - o.x) * (b.y - o.y) - (a.y - o.y) * (b.x - o.x)


# === 3. Area of a Polygon using Shoelace Formula ===
def polygon_area(poly):
    """
    Returns area of polygon (list of Points) using Shoelace formula.
    Assumes polygon is simple and points are in order.
    """
    n = len(poly)
    area = 0
    for i in range(n):
        j = (i + 1) % n
        area += poly[i].x * poly[j].y
        area -= poly[i].y * poly[j].x
    return abs(area) / 2


# === 4. Convex Hull using Andrew’s Monotone Chain Algorithm ===
def convex_hull(points):
    """
    Returns convex hull in counter-clockwise order.
    Removes duplicate endpoints.
    """
    points = sorted(set((p.x, p.y) for p in points))
    points = [Point(x, y) for x, y in points]

    if len(points) <= 1:
        return points

    lower = []
    for p in points:
        while len(lower) >= 2 and cross(lower[-2], lower[-1], p) <= 0:
            lower.pop()
        lower.append(p)

    upper = []
    for p in reversed(points):
        while len(upper) >= 2 and cross(upper[-2], upper[-1], p) <= 0:
            upper.pop()
        upper.append(p)

    # Remove last point of each half because it's repeated
    return lower[:-1] + upper[:-1]


# === 5. Line Intersection (2 lines in general form) ===
def line_intersection(p1, p2, q1, q2):
    """
    Returns intersection point of lines (p1, p2) and (q1, q2), or None if parallel.
    Uses determinant method.
    """
    A1 = p2.y - p1.y
    B1 = p1.x - p2.x
    C1 = A1 * p1.x + B1 * p1.y

    A2 = q2.y - q1.y
    B2 = q1.x - q2.x
    C2 = A2 * q1.x + B2 * q1.y

    det = A1 * B2 - A2 * B1
    if det == 0:
        return None  # Lines are parallel

    x = (B2 * C1 - B1 * C2) / det
    y = (A1 * C2 - A2 * C1) / det
    return Point(x, y)


# === 6. Angle Between Two Vectors ===
def angle_between(p1, p2):
    """
    Returns angle in radians between vectors p1 and p2 (from origin).
    """
    dot = p1.x * p2.x + p1.y * p2.y
    norm1 = math.hypot(p1.x, p1.y)
    norm2 = math.hypot(p2.x, p2.y)
    cos_theta = dot / (norm1 * norm2)
    return math.acos(max(-1, min(1, cos_theta)))  # Clamp for safety


# === SAMPLE DRIVER ===
if __name__ == "__main__":
    A = Point(0, 0)
    B = Point(4, 0)
    C = Point(4, 3)

    print("Distance AB:", distance(A, B))  # 4.0
    print("Orientation of ABC:", cross(A, B, C))  # >0 (counter-clockwise)

    triangle = [A, B, C]
    print("Area of triangle:", polygon_area(triangle))  # 6.0

    pts = [Point(0, 0), Point(1, 1), Point(0, 1), Point(1, 0), Point(0.5, 0.5)]
    hull = convex_hull(pts)
    print("Convex Hull:", hull)  # Should print square corners

    # Line intersection
    inter = line_intersection(Point(0, 0), Point(4, 4), Point(0, 4), Point(4, 0))
    print("Intersection:", inter)  # (2.0, 2.0)

    # Angle
    ang = angle_between(Point(1, 0), Point(0, 1))
    print("Angle (in degrees):", math.degrees(ang))  # 90.0
