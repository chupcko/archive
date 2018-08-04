from random import randint as _randint
from re import match as _match

class cpp :
  """Chess Prisoner Problem"""

  DIMENSION = 6
  POW_DIMESNION = 2**DIMENSION

  def _table_number(self, table) :
    table_number = 0
    for i in range(self.POW_DIMESNION) :
      if table[i] == '1' :
        table_number ^= i
    return table_number


  def random_table(self) :
    return ''.join(str(_randint(0, 1)) for j in range(self.POW_DIMESNION))
# from random import randrange as _randrange
#   return ('{0:0'+str(self.POW_DIMESNION)+'b}').format(_randrange(2**self.POW_DIMESNION))


  def encode(self, table, number) :
    if _match('[01]{'+str(self.POW_DIMESNION)+'}', table) is None :
      raise NameError('Bad Table')
    number = int(number)
    if number < 0 or number > self.POW_DIMESNION :
      raise NameError('Bad Number')

    index_number = self._table_number(table)^number
    if table[index_number] == '0' :
      return table[:index_number]+'1'+table[index_number+1:]
    else :
      return table[:index_number]+'0'+table[index_number+1:]
#   table_list = list(table)
#   table_list[index_number] = str(1-int(table_list[index_number]))
#   table = ''.join(table_list)


  def decode(self, table) :
    if _match('[01]{'+str(self.POW_DIMESNION)+'}', table) is None :
      raise NameError('Bad Table')

    return self._table_number(table)


def _test(N = 1000) :
  for i in range(N) :
    table = random_table()
    for n in range(cpp.POW_DIMESNION) :
      en = encode(table, n)
      de = decode(en)
      if de != n :
        print 'Error '+table+' '+n
  print 'Done'


_inst = cpp()
random_table = _inst.random_table
encode = _inst.encode
decode = _inst.decode


if __name__ == '__main__' :
  _test()
