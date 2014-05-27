#ifndef LUA_PROC_H
#define LUA_PROC_H

#include "lua_shared.h"
#include "lua.h"
#include <exception>
#include <string>

struct lua_State;

namespace lua_proc {
  class PS_LUAENGINE_API panic_exception: public std::exception {
  public:
    explicit panic_exception(lua_State* L);
    virtual ~panic_exception() throw() {}
    virtual const char *what() const throw() { return _what.c_str(); }

  private:
    std::string _what;
  };

  PS_LUAENGINE_API void init_lpanic(lua_State* L);
  PS_LUAENGINE_API int restore_lstack(lua_State* L);

  PS_LUAENGINE_API void lcopy_value(lua_State *dst, lua_State *src, int index);
  PS_LUAENGINE_API void lcopy(lua_State *dst, lua_State *src, int amount, int start = 1);
  PS_LUAENGINE_API void lcopy_ldenv(lua_State* dst, lua_State* src);
  PS_LUAENGINE_API bool lbcall(lua_State* L, int args = 0);
  PS_LUAENGINE_API bool lpcall(lua_State* L, int nargs = 0, int nresults = LUA_MULTRET);
  PS_LUAENGINE_API int  lcpcall(lua_State* dst, lua_State* src, int start);
  PS_LUAENGINE_API void lfcall(lua_State* L, int nargs, int nresults, const char* func, const char* require = 0);
}

#endif
