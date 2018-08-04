import math

def m(i) :
  return ((i+1)/2)*2
#

def a(i) :
  return 1-i%2*2
#

def answer(dimensions, captain_position, badguy_position, distance) :
  dx = distance/dimensions[0]+1
  dy = distance/dimensions[1]+1

  cD = {}
  for x in xrange(-dx, dx+1) :
    for y in xrange(-dy, dy+1) :
      if x != 0 or y != 0 :
        px = m(x)*dimensions[0]+a(x)*captain_position[0]-captain_position[0]
        py = m(y)*dimensions[1]+a(y)*captain_position[1]-captain_position[1]
        h = math.hypot(px, py)
        if h <= distance :
          angle = math.atan2(py, px)
          if cD.has_key(angle) :
            if h < cD[angle] :
              cD[angle] = h
            #
          else :
            cD[angle] = h
          #
        #
      #
    #
  #
  bD = {}
  for x in xrange(-dx, dx+1) :
    for y in xrange(-dy, dy+1) :
      px = m(x)*dimensions[0]+a(x)*badguy_position[0]-captain_position[0]
      py = m(y)*dimensions[1]+a(y)*badguy_position[1]-captain_position[1]
      h = math.hypot(px, py)
      if h <= distance :
        angle = math.atan2(py, px)
        if cD.has_key(angle) :
          if h < cD[angle] :
            bD[angle] = 1
          #
        else :
          bD[angle] = 1
        #
      #
    #
  #
  return len(bD)
#

print answer([3, 2], [1, 1], [2, 1], 4)
print answer([300, 275], [150, 150], [185, 100], 500)
