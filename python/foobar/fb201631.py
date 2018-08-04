def fill(maze, table, dx, dy, x, y, n) :
  if x >= 0 and x < dx and  y >= 0 and y < dy and maze[x][y] == 0 and ( table[x][y] == 0 or n < table[x][y] ) :
    table[x][y] = n
    fill(maze, table, dx, dy, x+1, y, n+1)
    fill(maze, table, dx, dy, x-1, y, n+1)
    fill(maze, table, dx, dy, x, y+1, n+1)
    fill(maze, table, dx, dy, x, y-1, n+1)
  #
#

def answer(maze) :
  dx = len(maze)
  dy = len(maze[0])

  table = []
  for xx in range(0, dx) :
    table.append([0]*dy)
  #
  fill(maze, table, dx, dy, 0, 0, 1)
  min = table[dx-1][dy-1]
  if min == 0 :
    min = dx*dy+1
  #
  if min == dx+dx-1 :
    return min
  #
  for x in range(0, dx) :
    for y in range(0, dy) :
      if maze[x][y] == 1 :
        maze[x][y] = 0
        table = []
        for xx in range(0, dx) :
          table.append([0]*dy)
        #
        fill(maze, table, dx, dy, 0, 0, 1)
        pmin = table[dx-1][dy-1]
        if pmin == 0 :
          pmin = dx*dy+1
        #
        if pmin < min :
          min = pmin
        #
        if min == dx+dx-1 :
          return min
        #
        maze[x][y] = 1
      #
    #
  #
  return min
#


print answer([
  [0, 1, 1, 0],
  [0, 0, 0, 1],
  [1, 1, 0, 0],
  [1, 1, 1, 0]
])
print answer([
  [0, 0, 0, 0, 0, 0],
  [1, 1, 1, 1, 1, 0],
  [0, 0, 0, 0, 0, 0],
  [0, 1, 1, 1, 1, 1],
  [0, 1, 1, 1, 1, 1],
  [0, 0, 0, 0, 0, 0]
])
print answer([
  [0, 0, 0, 0, 0, 0],
  [1, 1, 1, 1, 1, 0],
  [0, 0, 0, 0, 0, 0],
  [0, 1, 1, 0, 1, 1],
  [0, 1, 1, 0, 1, 1],
  [0, 0, 0, 0, 0, 0]
])
print answer([
  [0, 0, 0],
  [0, 1, 0],
  [0, 0, 0]
])
