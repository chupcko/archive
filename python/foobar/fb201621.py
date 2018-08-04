def answer(total_lambs) :
  min = 0
  p = 1
  sum = 1
  while sum <= total_lambs :
    p = p*2
    sum += p
    min = min+1

  max = 1
  a = 1
  b = 1
  sum = 2
  while sum <= total_lambs :
    c = a+b
    a = b
    b = c
    sum += c
    max = max+1
  return max-min

print answer(10)
print answer(143)
