def triangle(n) :
  return n*(n+1)/2

def answer(x, y) :
  return str(triangle(x+y-1)-y+1)

print answer(3, 2)
print answer(5, 10)
