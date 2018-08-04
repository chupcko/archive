# https://oeis.org/A001951
# https://oeis.org/A194102
# https://oeis.org/A006337

MAX = 300

l = [0]*MAX
s = [0]*MAX
f = [0]*MAX

l[0] = 1
s[0] = 1
f[0] = 1
l[1] = 2
s[1] = 3
f[1] = 4

for i in xrange(2, MAX) :
  l[i] = l[i-2]+2*l[i-1]
  s[i] = s[i-2]+2*s[i-1]
  f[i] = f[i-2]+2*f[i-1]+l[i-2]*s[i-1]+l[i-1]*(s[i-2]+s[i-1])
#

def answer(str_n) :
  n = int(str_n)
  global l, s, f

  n_try = 0
  a = []
  i = 0
  while n_try < n :
    a.append(i)
    n_try += l[i]
    i += 1
  #
  b = []
  while n_try != n :
    if n_try > n :
      last = a.pop()
      n_try -= l[last]
      a.append(last-1)
      n_try += l[last-1]
      b.append(last-1)
      b.append(last-2)
    else :
      new = b.pop()
      a.append(new)
      n_try += l[new]
    #
  #
  lsum = [0]*len(a)
  lsum[len(a)-1] = l[a[len(a)-1]]
  for i in xrange(len(a)-2, 0, -1) :
    lsum[i] = l[a[i]]+lsum[i+1]
  #
  sum = f[a[len(a)-1]]
  for i in xrange(len(a)-1) :
    sum += f[a[i]]+s[a[i]]*lsum[i+1]
  #
  return str(sum)
#

print answer('5')
print answer('20')
print answer('77')
print answer('9999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999')
