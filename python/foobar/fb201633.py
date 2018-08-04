def answer(l) :
  count = 0
  s = [0 for i in xrange(len(l))]
  s[len(l)-1] = 0
  for j in xrange(len(l)-2, -1, -1) :
    s[j] = 0
    for k in xrange(j+1, len(l)) :
      if l[k]%l[j] == 0 :
        s[j] += 1
        count += s[k]
      #
    #
  #
  return count
#

print answer([1, 1, 1])
print answer([1, 2, 3, 4, 5, 6])
print answer([1, 2, 3, 4, 5, 6, 12])
