#ifndef CRITICAL_SECTION_HPP
#define CRITICAL_SECTION_HPP

#include <boost/thread.hpp> 

namespace threads
{
  /** Определение критической секции. */
  typedef boost::mutex mutex;
  /** Определение автообъекта для критической секции. */
  typedef boost::lock_guard<mutex> lock_guard;

  /** Определение "разделяемого" мьютекса. */
  typedef boost::shared_mutex shared_mutex;
  /** Определение RW блокировщика. */
  typedef boost::unique_lock<shared_mutex> unique_lock;
  /** Определение RD блокировщика. */
  typedef boost::shared_lock<shared_mutex> shared_lock;
}

#endif