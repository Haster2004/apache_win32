#ifndef CRITICAL_SECTION_HPP
#define CRITICAL_SECTION_HPP

#include <boost/thread.hpp> 

namespace threads
{
  /** ����������� ����������� ������. */
  typedef boost::mutex mutex;
  /** ����������� ����������� ��� ����������� ������. */
  typedef boost::lock_guard<mutex> lock_guard;

  /** ����������� "������������" ��������. */
  typedef boost::shared_mutex shared_mutex;
  /** ����������� RW ������������. */
  typedef boost::unique_lock<shared_mutex> unique_lock;
  /** ����������� RD ������������. */
  typedef boost::shared_lock<shared_mutex> shared_lock;
}

#endif