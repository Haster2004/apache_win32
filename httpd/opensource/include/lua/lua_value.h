#ifndef LUA_VALUE_H
#define LUA_VALUE_H

#include "lua_shared.h"
#include <string>
#include <boost/function.hpp>
#include <boost/bind.hpp>

struct lua_State;
namespace lua_value {
  class PS_LUAENGINE_API error_raiser {
  public:
    error_raiser(const char* sz_error);
    void exec(lua_State* L, int index, int tag);

  private:
    const char* _sz_error;
  };

  /** Определяет тип функции обработчика ошибки.*/
  typedef boost::function<void (lua_State*, int, int)> raise_error_t;

  /** Считать значение. */
  PS_LUAENGINE_TEMPLATE_T bool get(T& value, lua_State* L, int index);

  /** Считать значение с проверкой типов.*/
  PS_LUAENGINE_TEMPLATE_T void get_safe_with_callback(T& value, lua_State* L, int index, raise_error_t func);

  /** Считать значение с проверкой типов.*/
  PS_LUAENGINE_TEMPLATE_T void get_safe(T& value, lua_State* L, int index, const char* err_info = 0)
  {
    error_raiser raiser(err_info);
    get_safe_with_callback(value, L, index, boost::bind(&error_raiser::exec, raiser, _1, _2, _3));
  }

  /** Записать значение.*/
  PS_LUAENGINE_TEMPLATE_T void set(lua_State* L, T value);

  PS_LUAENGINE_API void set(lua_State* L, const std::string& value);
  PS_LUAENGINE_API void set(lua_State* L, const char* value);
};

#endif

