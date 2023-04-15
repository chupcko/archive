local gameClass = {}
gameClass.__index = gameClass

function gameClass:new(dimension)
  local instance = {
    dimension = dimension,
    fields = {}
  }
  setmetatable(instance, self)
  instance:fill()
  return instance
end

function gameClass:fill()
  for x = 1, self.dimension do
    self.fields[x] = {}
    for y = 1, self.dimension do
      self.fields[x][y] = true
    end
  end
end

function gameClass:win()
  for x = 1, self.dimension do
    self.fields[x] = {}
    for y = 1, self.dimension do
      self.fields[x][y] = false
    end
  end
end

function gameClass:validOne(x)
  return x >= 1 and x <= self.dimension
end

function gameClass:valid(x, y)
  return self:validOne(x) and self:validOne(y)
end

function gameClass:change(x, y)
  if self:valid(x, y) then
    self.fields[x][y] = not self.fields[x][y]
  end
end

function gameClass:play(x, y)
  if self:valid(x, y) then
    self:change(x-1, y)
    self:change(x, y-1)
    self:change(x, y)
    self:change(x, y+1)
    self:change(x+1, y)
  end
end

function gameClass:shuffle(steps)
  steps = steps or self.dimension^2
  for i = 1, steps do
    self:play(
      math.random(1, self.dimension),
      math.random(1, self.dimension)
    )
  end
end

function gameClass:get(x, y)
  if self:valid(x, y) then
    return self.fields[x][y]
  end
  return false
end

function gameClass:isWin()
  for x = 1, self.dimension do
    for y = 1, self.dimension do
      if self.fields[x][y] then
        return false
      end
    end
  end
  return true
end

return gameClass
