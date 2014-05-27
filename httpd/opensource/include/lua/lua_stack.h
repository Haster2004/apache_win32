#ifndef LUA_STACK_H
#define LUA_STACK_H

#include "lua_shared.h"

struct lua_State;
namespace lua_stack {
  class PS_LUAENGINE_API checker {
  public:
    checker(lua_State* L, int diff = 0, const char* filename = "", int line = 0, bool hard_mode = false);
    ~checker();
    bool check_stack() const;

  private:
    void pop_diff();

    lua_State* _luaState;
    const char* _filename;
    int _line;
    int _top;
    int _diff;
    bool _hard_mode;
  };

  class PS_LUAENGINE_API auto_poper {
  public:
    explicit auto_poper(lua_State* L);
    ~auto_poper();

  private:
    lua_State* _luaState;
    int _top;
  };
}

#ifdef _DEBUG
  #define set_lua_stack_change_checker(L, i) lua_stack::checker __lua_stack(L, i, __FILE__, __LINE__, true)
  #define set_lua_stack_checker(L) set_lua_stack_change_checker(L, 0)
#else
  #define set_lua_stack_checker(L) 
  #define set_lua_stack_change_checker(L, i) 
#endif

#endif
