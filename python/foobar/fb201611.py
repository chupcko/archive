def rot(text, steps) :
  return text[steps:len(text)]+text[0:steps]

def answer(s) :
  print s
  length = len(s)
  first_letter = s[0:1]
  for i in range(1, length) :
    if length%i == 0 and first_letter == s[i:i+1] and s == rot(s, i) :
      return length/i
    #
  #
#

print anwser("abccbaabccba")
print anwser("abcabcabcabc")
