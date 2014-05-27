/**
\file atomic_operations.hpp
\brief С++ Атомарные операции
Рекомендуется использовать специальный тип atomic_count_type для работы с атомарными функциями.
В случае использования другого типа на Unix не гарантируется прямое отражение
этих функций в процессорные инструкции для работы с атомарными операциями. Возможна эмуляция.
Т.е.:
1)для 64 bit сборки Unix/Linux вырожденная атомарность без эмуляции гарантируется только
  для 64 bit данных (long).
2)для 32 bit сборки Unix/Linux вырожденная атомарность без эмуляции гарантируется только
  для 32 bit данных (long).
3)для Windows рекомендуется придерживаться такого же принципа. Поддержка только 32 и 64 bit.

В атомарные операции рекомендуется передавать выравненные по void* данные. При использовании
невыравненных данных возможна ошибка выравнивания BUS_ERROR, которая приводит к аварийному
завершению приложения. В режиме отладки (_DEBUG) это контроллируется с помощью assert.

\author Коновкин А.В.

\par Application:
HAS_SERVER
\par Copyright notice:
Copyright (c) CJSC PETER-SERVICE, 2009.
*/

#ifndef _atomic_operations_hpp_
#define _atomic_operations_hpp_

#include <cassert>

#ifdef _WIN32
#pragma warning (push)
#pragma warning (disable:4311)
#pragma warning (disable:4312)
#include <intrin.h>
#include <boost/static_assert.hpp>
#include <windows.h>
#endif

namespace atomic
{
#ifdef _WIN32

#ifndef _WIN64
  typedef LONG atomic_count_type;
#else
  typedef __int64 atomic_count_type;
#endif

#else

  typedef long atomic_count_type;

#endif

#ifdef _WIN32

template <int ArgSize>
  struct ChooseType
  {
    template <class D, class I>
    inline static D atomic_exchange_add(volatile D& destination, I increment)
    {
      BOOST_STATIC_ASSERT(false);
    }
    template <class D, class C, class E>
    inline static D atomic_compare_and_swap(volatile D& destination, C comparand, E exchange)
    {
      BOOST_STATIC_ASSERT(false);
    }
    template <class D, class C, class E>
    inline static D *atomic_compare_and_swap(D * volatile &destination, C *comparand, E *exchange)
    {
      BOOST_STATIC_ASSERT(false);
    }
  };

template <>
  struct ChooseType<4>
  {
    template <class D, class I>
    inline static D atomic_exchange_add(volatile D& destination, I increment)
    {
      return (D)_InterlockedExchangeAdd((LONG volatile *)&destination, (LONG)increment);
    }
    template <class D, class C, class E>
    inline static D atomic_compare_and_swap(volatile D& destination, C comparand, E exchange)
    {
      return (D)_InterlockedCompareExchange((LONG volatile *)&destination, (LONG)exchange, (LONG)comparand);
    }
#ifndef _WIN64
    template <class D, class C, class E>
    inline static D *atomic_compare_and_swap(D * volatile &destination, C *comparand, E *exchange)
    {
      BOOST_STATIC_ASSERT(sizeof(C*) == 4);
      BOOST_STATIC_ASSERT(sizeof(E*) == 4);
      assert(  (((LONG) destination) & 3) == 0 ) ;
      return((D*)(LONG_PTR)_InterlockedCompareExchange((LONG volatile *)&destination, (LONG)(LONG_PTR)exchange, (LONG)(LONG_PTR)comparand));
    }
#endif
  };

  template <>
  struct ChooseType<8>
  {
    template <class D, class I>
    inline static D atomic_exchange_add(volatile D& destination, I increment)
    {
      return (D)_InterlockedExchangeAdd64((__int64 volatile *)&destination, (__int64)increment);
    }
    template <class D, class C, class E>
    inline static D atomic_compare_and_swap(volatile D& destination, C comparand, E exchange)
    {
      return (D)_InterlockedCompareExchange64((__int64 volatile *)&destination, (__int64)exchange, (__int64)comparand);
    }
#ifdef _WIN64
    template <class D, class C, class E>
    inline static D *atomic_compare_and_swap(D * volatile &destination, C *comparand, E *exchange)
    {
      BOOST_STATIC_ASSERT(sizeof(C*) == 8);
      BOOST_STATIC_ASSERT(sizeof(E*) == 8);
      assert(  (((__int64) destination) & 7) == 0 ) ;
      return((D*)(LONG_PTR)_InterlockedCompareExchange64((__int64 volatile *)&destination, (__int64)(__int64*)exchange, (__int64)(__int64*)comparand));
    }
#endif
  };
#endif

  template <class D, class I>
  inline D atomic_exchange_add(volatile D& destination, I increment)
  {
#ifndef _WIN32

    return __sync_fetch_and_add(&destination, increment);

#else
    return ChooseType<sizeof(D)>::atomic_exchange_add(destination,increment);

#endif
  }

  template <class D>
  inline D atomic_get(const volatile D& destination)
  {
    return atomic_exchange_add<D>(const_cast<D&>(destination), 0);
  }

  template <class D>
  inline D atomic_inc(volatile D& destination)
  {
    return atomic_exchange_add<D>(destination, 1);
  }

  template <class D>
  inline D atomic_dec(volatile D& destination)
  {
    return atomic_exchange_add<D>(destination, -1);
  }

  template <class D, class C, class E>
  inline D atomic_compare_and_swap(volatile D& destination, C comparand, E exchange)
  {
#ifndef _WIN32

    return __sync_val_compare_and_swap(&destination, comparand, exchange);

#else

    return ChooseType<sizeof(D)>::atomic_compare_and_swap(destination, comparand, exchange);

#endif
  }

  template <class D, class C, class E>
  inline D *atomic_compare_and_swap(D * volatile &destination, C *comparand, E *exchange)
  {
#ifdef _WIN32

    return ChooseType<sizeof(D*)>::atomic_compare_and_swap(destination, comparand, exchange);

#else

#if LONG_MAX == LLONG_MAX

    // 64 bit
    assert(  (((long) destination) & 7) == 0 ) ;

#else

    // 32 bit
    assert(  (((long) destination) & 3) == 0 ) ;

#endif

    return __sync_val_compare_and_swap(&destination, comparand, exchange);

#endif
  }

  template <class D, class E>
  inline D atomic_exchange(volatile D& destination, E exchange)
  {
    D pv;

    do
    {
      pv = destination;
    } while (pv != atomic_compare_and_swap(destination, pv, exchange));
    
    return pv;
  }

  template <class D, class E>
  inline D atomic_set(volatile D& destination, E exchange)
  {
    return atomic_exchange<D, E>(destination, exchange);
  }

#ifdef _WIN32

  template <class D, class E>
  inline D *atomic_set(D * volatile &destination, E *exchange)
  {
    D *pv;

    do
    {
      pv = destination;
    } while (pv != atomic_compare_and_swap(destination, pv, exchange));
    
    return pv;
  }

#endif

  struct scoped_counter
  {
    volatile atomic_count_type& _v;
    scoped_counter(volatile atomic_count_type& v)
      : _v(v)
    {
      atomic_inc(_v);
    }
    ~scoped_counter()
    {
      atomic_dec(_v);
    }
  };
}

#ifdef _WIN32
#pragma warning (pop)
#endif

#endif
