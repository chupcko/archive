def answer(M, F) :
  M = int(M)
  F = int(F)
  count = 0

  while M != 0 and F != 0 and M != F :
    print M, F, count
    if M == 1 :
      count = count+F-1
      F = 1
    elif F == 1 :
      count = count+M-1
      M = 1
    else :
      if M > F :
        count = count+M/F
        M = M%F
      else :
        count = count+F/M
        F = F%M
      #
    #
  #
  if M == 1 and F == 1:
    return str(count)
  else :
    return 'impossible'
#

print answer("2", "1")
print answer("4", "7")
