#ifndef LUA_BIND_H
#define LUA_BIND_H

#include "lauxlib.h"
#include "lua_shared.h"

#include <string>
#include <vector>
#include <boost/bind.hpp>
#include <boost/function.hpp>
#include <boost/shared_ptr.hpp>

#define LUA_BIND_THIS_FUNC(N,F) (add_bind(N, boost::bind(F, this, _1)))

namespace lua_bind {
  /** ���������� ��� ������� �������.*/
  typedef boost::function<int (lua_State*)> lua_cfunction_t;

  class object;
  PS_LUAENGINE_API int constructor(lua_State *L, object *obj);
  PS_LUAENGINE_API int constructor(lua_State *L, object *obj, lua_cfunction_t close_callback);

  class PS_LUAENGINE_API object {
  public:
    /** ��������� ������ ���� ������� Lua ������. */
    typedef std::vector<std::string> func_names_t;

    ///���������� �������������� ������ Lua �������.
    struct reg_func {
      /**��� ������� � Lua.*/
      std::string _name;
      /**����������.*/
      lua_cfunction_t _func;

      /**������������ ������.*/
      reg_func(const std::string& name, lua_cfunction_t func) 
        : _name(name), _func(func){}
    };

    /**���������� ��������� bind �������.*/
    typedef std::vector<reg_func> bind_func_list_t;
    /** ��������� ����������� ������. */
    typedef boost::shared_ptr<bind_func_list_t> bind_func_list_shared_t;

  protected:
    static int gc_obj( lua_State *L );

  public:
    object(const bind_func_list_shared_t& bind_vector);
    object();
    virtual ~object(){}

    void add_bind(const std::string& name, lua_cfunction_t func);
    void add_bind(const reg_func& value);
    virtual void get_funcs(func_names_t& names) const;
    virtual int exec_func(lua_State* L, int index);
    /** ���������� ������, ����������� ������� Lua c C++.*/
    inline const bind_func_list_shared_t& get_bind_vector() const { return _bind_vector;} 

    /** ���������� ������������� ������. */
    PS_LUAENGINE_TEMPLATE_T static T get_obj(lua_State *L, int index)
    {
      T res = 0;
      lua_pushvalue(L, index);

      lua_pushnumber(L, 0);
      lua_gettable(L, -2); // get the class table (i.e, self)

      void *p = lua_touserdata(L, -1);
      if (p != NULL) {  /* value is a userdata? */
        if (lua_getmetatable(L, -1)) {  /* does it have a metatable? */
          lua_getfield(L, LUA_REGISTRYINDEX, "__lua_bind_object");  /* get correct metatable */
          if (lua_rawequal(L, -1, -2))  {/* does it have the correct mt? */
            T* p_obj = static_cast<T*>(p);
            res = *p_obj;
          }
          lua_pop(L, 2);  /* remove both metatables */
        }
      }

      lua_pop(L, 1); // remove userdata
      lua_pop(L, 1); // remove copy source table

      return res;
    }

  private:
    bind_func_list_shared_t _bind_vector;
    lua_cfunction_t _close_callback;

    friend PS_LUAENGINE_API int constructor(lua_State *L, object *obj);
    friend PS_LUAENGINE_API int constructor(lua_State *L, object *obj, lua_cfunction_t close_callback);
  };

  /**
    \class wrapped_object
    \brief ��������� ������� ��� �++ ������ � Lua. 
  */
  PS_LUAENGINE_TEMPLATE_T class wrapped_object : public lua_bind::object {
  public:
    /** ��������� �����������. */
    wrapped_object(const T& value) : object(value->get_bind_vector()), _wrapped (value) { }
    /** ���������� ������������� ������. */
    static T get(lua_State *L, int index) 
    {
      wrapped_object* obj = get_obj<wrapped_object*>(L, index);
      if (obj) return obj->_wrapped;
      return T();
    }

  private:
    T _wrapped;
  };

  /** \brief ������� ������ C++ � Lua. */
  PS_LUAENGINE_TEMPLATE_T int create(lua_State *L, const T& value)
  {
    return lua_bind::constructor(L, new lua_bind::wrapped_object<T>(value));
  }

  /** \brief ������� ������ C++ � Lua. */
  PS_LUAENGINE_TEMPLATE_T int create(lua_State *L, const T& value, lua_cfunction_t close_callback)
  {
    return lua_bind::constructor(L, new lua_bind::wrapped_object<T>(value), close_callback);
  }

  /** \brief ���������� C++ ������ �� Lua. */
  PS_LUAENGINE_TEMPLATE_T T get(lua_State *L, int index)
  {
    return lua_bind::wrapped_object<T>::get(L, index);
  }
}

#endif
