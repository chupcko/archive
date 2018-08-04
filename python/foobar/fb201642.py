def answer(entrances, exits, path) :
  n = len(path)
  F = [[0]*n for _ in xrange(n)]
  MAX = 2000000

  height = [0]*n
  excess = [0]*n
  seen = [0]*n
  nodelist = [i for i in xrange(n) if i not in entrances and i not in exits]

  def push(u, v) :
    send = min(excess[u], path[u][v] - F[u][v])
    F[u][v] += send
    F[v][u] -= send
    excess[u] -= send
    excess[v] += send
  #

  def relabel(u) :
    min_height = MAX
    for v in xrange(n) :
      if path[u][v]-F[u][v] > 0 :
        min_height = min(min_height, height[v])
        height[u] = min_height+1
      #
    #
  #

  def discharge(u) :
    while excess[u] > 0 :
      if seen[u] < n :
        v = seen[u]
        if path[u][v]-F[u][v] > 0 and height[u] > height[v] :
          push(u, v)
        else :
          seen[u] += 1
        #
      else :
        relabel(u)
        seen[u] = 0
      #
    #
  #

  for start in entrances :
    height[start] = n
    excess[start] = MAX
    for i in xrange(n) :
      push(start, i)
    #
  #

  p = 0
  while p < len(nodelist) :
    u = nodelist[p]
    old_height = height[u]
    discharge(u)
    if height[u] > old_height :
      nodelist.insert(0, nodelist.pop(p))
      p = 0
    else :
      p += 1
    #
  #

  max = 0
  for start in entrances :
    max += sum(F[start])
  #
  return max
#

print answer([0], [3], [[0, 7, 0, 0], [0, 0, 6, 0], [0, 0, 0, 8], [9, 0, 0, 0]])

print answer([0], [3], [[0, 10, 1, 0], [0, 0, 10, 1], [0, 0, 0, 20], [0, 0, 0, 0]])

print answer([0], [4], [[0, 10, 1, 0, 0], [0, 0, 5, 0, 0], [0, 0, 0, 7, 0], [0, 1, 0, 0, 20], [0, 0, 0, 0, 0]])

print answer([0, 1], [4, 5], [[0, 0, 4, 6, 0, 0], [0, 0, 5, 2, 0, 0], [0, 0, 0, 0, 4, 4], [0, 0, 0, 0, 6, 6], [0, 0, 0, 0, 0, 0], [0, 0, 0, 0, 0, 0]])
