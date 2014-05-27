#ifndef LUA_MODULE_H
#define LUA_MODULE_H

#include "lua_shared.h"
#include <string>

struct lua_State;
struct luaL_Reg;

#define STRINGIFY_BUILD_STRING(X) #X
#define MAKE_BUILD_STRING(X) STRINGIFY_BUILD_STRING(X)
#if defined(BUILD_NUMBER_STR)
  #define MAKE_BUILD_STRING(X) STRINGIFY_BUILD_STRING(X)
  #define get_bc_build_number() MAKE_BUILD_STRING(BUILD_NUMBER_STR)
#else
  #define get_bc_build_number() __TIMESTAMP__
#endif

namespace lua_module {
  PS_LUAENGINE_API int reg(lua_State *L, const luaL_Reg* funcs);
  PS_LUAENGINE_API std::string get_cpath(lua_State* L);
  PS_LUAENGINE_API std::string get_path(lua_State* L);
  PS_LUAENGINE_API void set_path(lua_State* L, const std::string& value);
  PS_LUAENGINE_API void set_cpath(lua_State* L, const std::string& value);
  PS_LUAENGINE_API std::string get_current_binary_ext();
};

#endif

