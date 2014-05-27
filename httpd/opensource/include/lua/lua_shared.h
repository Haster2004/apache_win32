#ifndef LUA_SHARED_H
#define LUA_SHARED_H

#ifdef WIN32
  #define PS_LUAENGINE_FXIMPORT __declspec(dllimport)
  #define PS_LUAENGINE_FXEXPORT __declspec(dllexport)
#else
  #ifdef GCC_HASCLASSVISIBILITY
    #ifndef __sun__
      #define PS_LUAENGINE_FXIMPORT __attribute__ ((visibility("default")))
      #define PS_LUAENGINE_FXEXPORT __attribute__ ((visibility("default")))
    #endif
  #endif
#endif

#ifndef PS_LUAENGINE_FXIMPORT
  #define PS_LUAENGINE_FXIMPORT
  #define PS_LUAENGINE_FXEXPORT
#endif

/*! \defgroup ps_engine_macro Форматы API функций
 *  Форматы вызовов API функций библиотеки.
 */
//@{
#ifndef PS_LUAENGINE_AS_DLL
  /** Определение типа импортируемой функции. */
  #define PS_LUAENGINE_API PS_LUAENGINE_FXIMPORT
#else
  /** Определение типа экспортируемой функции. */
  #define PS_LUAENGINE_API PS_LUAENGINE_FXEXPORT
#endif
/** Определение шаблона. */
#define PS_LUAENGINE_TEMPLATE_T template<typename T> 
/** Параметризированный шаблон. */
#define PS_LUAENGINE_API_TEMPLATE template<> PS_LUAENGINE_API
//@}

#ifdef WIN32
  #pragma warning( disable : 4290 )
  #pragma warning( disable : 4251 )
  #pragma warning( disable : 4231 )
#endif

#endif
