#ifndef LUA_TABLE_H
#define LUA_TABLE_H

#include "lua_value.h"
#include "lua.h"
#include <vector>

namespace lua_table {
  /** Определяет имена подтаблиц требуемой таблицы.*/
  typedef std::vector<std::string> table_name_list_t;

  class PS_LUAENGINE_API error_raiser {
  public:
    error_raiser(const std::string& key, const char* sz_error);
    void exec(lua_State* L, int index, int tag);

  private:
    std::string _key;
    const char* _sz_error;
  };

  /** Вставить значение в индексную таблицу.*/
  PS_LUAENGINE_TEMPLATE_T void insert(lua_State* L, const T& val, int pos, int index = -1)
  {
    lua_pushvalue(L, index);

    lua_getglobal(L, "table");
    lua_getfield(L, -1, "insert");
    lua_remove(L, -2); 
    lua_insert(L, -2);

    lua_value::set(L, pos);
    lua_value::set(L, val);
    lua_call(L, 3, 0);
  }

  /** Выполняет поиск элемента в индексной таблице. */
  PS_LUAENGINE_TEMPLATE_T bool find(lua_State* L, const T& val, int index = -1)
  {
    lua_pushvalue(L, index);

    T v_val;
    bool fl_eq = false;

    lua_pushnil(L);  
    while (!fl_eq && lua_next(L, -2)) {
      fl_eq = lua_value::get(v_val, L, -1);

      if (fl_eq && v_val == val) lua_pop(L, 1); //ключ больше не нужен
      else fl_eq = false;

      //Выталкиваем значение
      lua_pop(L, 1);
    }

    lua_pop(L, 1);
    return fl_eq;
  }

  /** Установить значение поля в таблице.*/
  PS_LUAENGINE_TEMPLATE_T void set(lua_State* L, const std::string& key, const T& val, int index = -1)
  {
    if (index != -1) lua_pushvalue(L, index);

    lua_value::set(L, val);
    lua_setfield(L, -2, key.c_str());

    if (index != -1) lua_pop(L, 1);
  }
  
  /** Считать значение поля в таблице.*/
  PS_LUAENGINE_TEMPLATE_T bool get(T& val, lua_State* L, const std::string& key, int index = -1)
  {
    lua_getfield(L, index, key.c_str()); // stack: table value
    bool res = lua_value::get(val, L, -1);
    lua_pop(L, 1); 
	
    return res;  
  }

  /** Считать значение с проверкой типов.*/
  PS_LUAENGINE_TEMPLATE_T void get_safe_with_callback(T& value, lua_State* L, const std::string& key, int index, lua_value::raise_error_t func)
  {
    lua_getfield(L, index, key.c_str()); // stack: table value
    lua_value::get_safe_with_callback(value, L, -1, func);
    lua_pop(L, 1); 
  }

  /** Считать значение поля в таблице с проверкой.*/
  PS_LUAENGINE_TEMPLATE_T void get_safe(T& value, lua_State* L, const std::string& key, int index = -1, const char* err_info = 0)
  {
    error_raiser raiser(key, err_info);
    get_safe_with_callback(value, L, key, index, boost::bind(&error_raiser::exec, raiser, _1, _2, _3));
  }

  PS_LUAENGINE_API table_name_list_t split_name(const std::string& value);
  PS_LUAENGINE_API int create_nested_table(lua_State* L, const std::string& value, int index = -1);
};

#endif

