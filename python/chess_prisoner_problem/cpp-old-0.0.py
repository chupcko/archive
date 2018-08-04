from random import randint as _randint
from re import match as _match

class cpp :
  """Chess Prisoner Problem"""


  def _to_bin(self, n) :
    return ('00000'+bin(n)[2:])[-6:]


  def _table_number_dict(self, table) :
    table_number_dict = {}
    for j in range(6) :
      table_number_dict[j] = 0

    for i in range(64) :
      if table[i] == '1' :
        i_bin = self._to_bin(i)
        for j in range(6) :
          if i_bin[j] == '1' :
            table_number_dict[j] += 1
    return table_number_dict


  def random_table(self) :
    table = ""
    for i in range(64) :
      table += str(_randint(0, 1))
    return table


  def encode(self, table, number) :
    if _match('[01]{64}', table) is None :
      raise NameError('Bad Table')
    number = int(number)
    if number < 0 or number > 63 :
      raise NameError('Bad Number')

    table_number_dict = self._table_number_dict(table)

    number_bin = self._to_bin(number)
    index_number = 0
    for j in range(6) :
      if int(number_bin[j]) != table_number_dict[j]%2 :
        index_number += 2**(5-j)

    if table[index_number] == '0' :
      return table[:index_number]+'1'+table[index_number+1:]
    else :
      return table[:index_number]+'0'+table[index_number+1:]


  def decode(self, table) :
    if _match('[01]{64}', table) is None :
      raise NameError('Bad Table')

    table_number_dict = self._table_number_dict(table)

    table_number = 0
    for j in range(6) :
      table_number += table_number_dict[j]%2*2**(5-j)
    return table_number


def _test(N = 1000) :
  for i in range(N) :
    table = random_table()
    for n in range(64) :
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
