def assembly_line_scheduling(a, t, e, x):
    n = len(a[0])
    line1 = [0] * n
    line2 = [0] * n

    line1[0] = e[0] + a[0][0]
    line2[0] = e[1] + a[1][0]

    for i in range(1, n):
        line1[i] = min(line1[i - 1] + a[0][i], line2[i - 1] + t[1][i] + a[0][i])
        line2[i] = min(line2[i - 1] + a[1][i], line1[i - 1] + t[0][i] + a[1][i])

    # Total minimum time is the minimum of leaving the last station plus the exit time
    return min(line1[n - 1] + x[0], line2[n - 1] + x[1])


a = [[4, 5, 3, 2], [2, 10, 1, 4]]
t = [[0, 7, 4, 5], [0, 9, 2, 8]]
e = [10, 12]
x = [18, 7]
print(f"Minimum time through assembly lines: {assembly_line_scheduling(a, t, e, x)}")
