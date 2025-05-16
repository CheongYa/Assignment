T = int(input())

for testcase in range(1, T+1):
    line = int(input())
    arr = [[0] * line for _ in range(line)]

    dx = [0, 1, 0, -1]
    dy = [1, 0, -1, 0]
    direction = 0
    x, y = 0, 0

    for i in range(1, line*line + 1):
        arr[x][y] = i
        nx, ny = x + dx[direction], y + dy[direction]

        if 0 <= nx < line and 0 <= ny < line and arr[nx][ny] == 0:
            x, y = nx, ny
        else:
            direction = (direction + 1) % 4
            x += dx[direction]
            y += dy[direction]

    print(f"#{testcase}")
    for row in arr:
        print(' '.join(map(str, row)))