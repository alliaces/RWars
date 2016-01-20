#ifndef UTILS_H_
#define UTILS_H_

#include <cmath>
#include <sys/time.h>
#include <string>
#include <sstream>

class Utils
{
public:
  inline static void doubleToTimeval(double d_time, struct timeval *time)
  {
    time->tv_sec = std::floor(d_time);
    time->tv_usec = (d_time - floor(d_time)) * 1000000;
  }

  inline static bool contentEquals(const void *ptr1, const void *ptr2, int size)
  {
    const char *x = static_cast<const char *>(ptr1);
    const char *y = static_cast<const char *>(ptr2);
    for (int i = 0; i < size; ++i)
    {
      if (x[i] != y[i])
        return (false);
    }
    return (true);
  }

  template <typename T>
    static inline std::string to_string( const T& n )
  {
    std::ostringstream stm ;
    stm << n ;
    return stm.str() ;
  }
};

#endif
