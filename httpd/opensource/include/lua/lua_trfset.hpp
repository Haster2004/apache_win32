#ifndef LUA_BIND_REGEX_H
#define LUA_BIND_REGEX_H

#include "lua_bind.h"
#include "boost/regex.hpp"

/**
  \namespace lua_trfset
  \brief Создает список lua_bind объектов по регулярному выражению из множества set. 
*/
namespace lua_trfset {
  /** \private */
  struct regex_filter {
    boost::regex _pattern;
    boost::match_results<std::string::const_iterator> _what;
    regex_filter(const std::string& pattern) : _pattern(pattern) {}
    bool operator ()(const std::string& value){
      return boost::regex_match(value, _what, _pattern);
    }
  };

  /** \private */
  struct pass_any {
    bool operator ()(const std::string&){ return true; }
  };

  /** \private */
  template<typename Pred, typename T>
  struct data_filler {
    lua_State* _state;
    Pred& _pred;
    int _counter;

    data_filler(lua_State* L, Pred& pred) : _state(L), _pred(pred), _counter(0){}
    void operator ()(const typename T::value_type& value){
      if (_pred(value->get_name())) {
        lua_pushnumber(_state, ++_counter);
        lua_bind::create(_state, value);
        lua_rawset(_state, -3);
      }
    }
  };

  /** Заполняет таблицу объектами по маске. У элементов контейнера должен быть реализован метод get_name. */
  PS_LUAENGINE_TEMPLATE_T int create(const T& container, lua_State *L, int index = -1)
  {
    const char* pattern = lua_tolstring(L, index, 0);

    lua_newtable(L);
    if (pattern && pattern[0]) {
      regex_filter pred(pattern);
      data_filler<regex_filter, T> filler(L, pred);
      std::for_each(container.begin(), container.end(), filler);
    } else {
      pass_any pred;
      data_filler<pass_any, T> filler(L, pred);
      std::for_each(container.begin(), container.end(), filler);
    }
    return 1;
  }
}

#endif
