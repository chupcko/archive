/*
gcc -o lua_factoriel lua_factoriel.c liblua.a -lm -ldl
*/

#include <stdio.h>
#include <stdlib.h>

#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"

#define P                        \
"function factoriel(n)\n"        \
"  if n < 2 then return 1 end\n" \
"  return n*factoriel(n-1)\n"    \
"end"                            \

#define ERROR                                     \
do                                                \
{                                                 \
  fprintf(stderr, "%s\n", lua_tostring(lua, -1)); \
  lua_pop(lua, 1);                                \
  return EXIT_FAILURE;                            \
}                                                 \
while(0)                                          \

int main(void)
{
  lua_State* lua = luaL_newstate();
  luaL_openlibs(lua);

  if(luaL_loadstring(lua, P) || lua_pcall(lua, 0, 0, 0))
    ERROR;

  lua_getglobal(lua, "factoriel");
  lua_pushinteger(lua, 5);
  if(lua_pcall(lua, 1, 1, 0))
    ERROR;
  printf("%d\n", lua_tointeger(lua, -1));
  lua_pop(lua, 1);

  lua_close(lua);
  return EXIT_SUCCESS;
}
