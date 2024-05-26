use std::env;
use std::fs::File;
use std::io::{ BufRead, BufReader };
use std::collections::HashMap;

#[derive(Clone, Debug, PartialEq)]
enum State {
  Free,
  Queen,
  Taken,
}

impl State {

  #[allow(dead_code)]
  fn to_char(& self) -> char {
    match *self {
      State::Free => ' ',
      State::Queen => '*',
      State::Taken => '.',
    }
  }

}

type Color = char;

#[derive(Clone, Debug)]
struct Field {
  color: Color,
  state: State,
}

#[derive(Clone, Debug)]
struct Cordinate {
  row: usize,
  column: usize,
}

#[derive(Clone, Debug)]
struct Game {
  size: usize,
  board: Vec<Vec<Field>>,
  colors: HashMap<Color, Vec<Cordinate>>,
}

impl Game {
  fn new() -> Game {
    Game { size: 0, board: vec!(), colors: HashMap::new() }
  }

  fn load(& mut self, file_name: String) -> Result<(), String> {
    let file = match File::open(file_name) {
      Ok(file) => file,
      Err(e) => return Err(e.to_string()),
    };
    let reader = BufReader::new(file);
    let mut row = 0;
    for line in reader.lines() {
      let line = match line {
        Ok(line) => line,
        Err(e) => return Err(e.to_string()),
      };
      if row == 0 {
        self.size = line.len();
      } else {
        if row >= self.size {
          return Err(format!("Garbage after {} lines", self.size));
        }
        if self.size != line.len() {
          return Err(format!("Wrong length of line {}", row+1));
        }
      }
      let mut fields: Vec<Field> = vec!();
      let mut column = 0;
      for color in line.chars() {
        fields.push(Field { color: color, state: State:: Free });
        if let Some(cordinates) = self.colors.get_mut(&color) {
          cordinates.push(Cordinate { row: row, column: column });
        } else {
          self.colors.insert(color, vec!(Cordinate { row: row, column: column }));
        }
        column += 1;
      }
      self.board.push(fields);
      row += 1;
    }
    if row == 0 {
      return Err("Empty file".to_string());
    }
    if row < self.size {
      return Err(format!("Missing {} lines", self.size-row));
    }
    if self.colors.len() != self.size {
      return Err("Mismatch between size and number of colors".to_string());
    }
    Ok(())
  }

  #[allow(dead_code)]
  fn print(& self) {
    for row in & self.board {
      for field in row {
        print!("{}{}", field.color, field.state.to_char());
      }
      println!();
    }
    println!();
  }

  fn draw(& self) {

    fn border(n: usize) {
      print!("+");
      for _ in 0 .. n {
        print!("---+");
      }
      println!();
    }

    border(self.size);
    for row in 0 .. self.size {
      print!("|");
      for column in 0 .. self.size {
        if self.board[row][column].state == State::Queen {
          print!(" Q ");
        } else {
          print!("   ");
        }
        if column == self.size-1 {
          break;
        }
        if self.board[row][column].color != self.board[row][column+1].color {
          print!("|");
        } else {
          print!(" ");
        }
      }
      println!("|");
      if row == self.size-1 {
        break;
      }
      print!("+");
      for column in 0 .. self.size {
        if self.board[row][column].color != self.board[row+1][column].color {
          print!("---+");
        } else {
          print!("   +");
        }
      }
      println!();
    }
    border(self.size);
  }

  fn solve(& self) {

    fn mark_one(game: &mut Game, row: usize, column: usize) -> bool {
      if game.board[row][column].state == State::Queen {
        return false;
      }
      game.board[row][column].state = State::Taken;
      true
    }

    fn mark_all(game: &mut Game, row: usize, column: usize) -> bool {
      for i in 0 .. game.size {
        if
          !mark_one(game, row, i) ||
          !mark_one(game, i, column)
        {
          return false;
        }
      }
      if
        (
          row > 0 &&
          (
            (column > 0 && !mark_one(game, row-1, column-1)) ||
            (column < game.size-1 && !mark_one(game, row-1, column+1))
          )
        ) ||
        (
          row < game.size-1 &&
          (
            (column > 0 && !mark_one(game, row+1, column-1)) ||
            (column < game.size-1 && !mark_one(game, row+1, column+1))
          )
        )
      {
        return false;
      }
      let colors = game.colors.get(&game.board[row][column].color).cloned();
      let Some(colors) = colors else {
        panic!("WRONG DATA");
      };
      for cordinate in colors {
        if !mark_one(game, cordinate.row, cordinate.column) {
          return false;
        }
      }
      game.board[row][column].state = State::Queen;
      true
    }

    fn solve_helper(game: & Game, row: usize) {
      for column in 0 .. game.size {
        let mut g = game.clone();
        if g.board[row][column].state == State::Free && mark_all(&mut g, row, column) {
          if row == game.size-1 {
            g.draw();
          }
          else {
            solve_helper(& g, row+1);
          }
        }
      }
    }

    solve_helper(self, 0);
  }

}

fn main() {
  let file_name: String = env::args().nth(1).unwrap_or("/dev/stdin".to_string());
  let mut game: Game = Game::new();
  if let Err(e) = game.load(file_name) {
    panic!("Can't load: {:?}", e);
  }
  game.solve();
}
