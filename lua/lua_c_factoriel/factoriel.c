#include <lua.h>

static int factoriel(lua_State *L)
{
  int n = lua_tonumber(L, -1);
  int p = 1;
  int i;
  for(i = 2; i <= n; i++)
    p *= i;
  lua_pushnumber(L, p);
  return 1;
}

int luaopen_factoriel(lua_State *L)
{
  lua_register(L, "factoriel", factoriel);
  return 0;
}
