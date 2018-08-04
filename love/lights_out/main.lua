DIMENSION = 5
FIELD_SIZE = 40
PAD_SIZE = 5

BACKGROUND_COLOR = {255, 255, 255}
BACKGROUND_WIN_COLOR = {127, 255, 127}
FIELD_ON_COLOR = {63, 63, 255}
FIELD_OFF_COLOR = {191, 191, 255}
BORDER_COLOR = {0, 0, 255}

function offset(x)
  return PAD_SIZE+(FIELD_SIZE+PAD_SIZE)*x
end

WIDTH = offset(DIMENSION)

gameClass = require 'game'

function love.load()
  math.randomseed(os.time())
  love.window.setMode(WIDTH, WIDTH, {})
  love.window.setTitle('Love Lights Out')
  game = gameClass:new(DIMENSION)
end

function love.draw()
  if game:isWin() then
    love.graphics.setBackgroundColor(BACKGROUND_WIN_COLOR)
  else
    love.graphics.setBackgroundColor(BACKGROUND_COLOR)
  end
  for x = 1, game.dimension do
    for y = 1, game.dimension do
      if game:get(x, y) then
        love.graphics.setColor(FIELD_ON_COLOR)
      else
        love.graphics.setColor(FIELD_OFF_COLOR)
      end
      love.graphics.rectangle('fill', offset(x-1), offset(y-1), FIELD_SIZE, FIELD_SIZE)
      love.graphics.setColor(BORDER_COLOR)
      love.graphics.rectangle('line', offset(x-1), offset(y-1), FIELD_SIZE, FIELD_SIZE)
    end
  end
end

function inFieldOne(x)
  return x%(PAD_SIZE+FIELD_SIZE) > PAD_SIZE
end

function inField(x, y)
  return inFieldOne(x) and inFieldOne(y)
end

function love.mousepressed(x, y, button, istouch)
  if inField(x, y) then
    game:play(
      math.floor(x/(PAD_SIZE+FIELD_SIZE))+1,
      math.floor(y/(PAD_SIZE+FIELD_SIZE))+1
    )
    love.draw()
  end
end

function love.keypressed(key, isrepeat)
  if key == 'q' then
    love.event.quit()
  elseif key == 's' then
    game:shuffle()
    love.draw()
  elseif key == 'f' then
    game:fill()
    love.draw()
  elseif key == 'w' then
    game:win()
    love.draw()
  end
end
