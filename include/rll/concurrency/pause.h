#pragma once

#include <cstdlib>
#include <cstdio>
#include <string>
#include <thread>

/**
 * This function is used in spin-wait loops to hint the CPU that the current * thread is in a
 * busy-wait state. * It helps reduce power consumption and improves performance on hyper-threaded
 * processors * by preventing the CPU from consuming unnecessary cycles while waiting. * It is
 * particularly useful in low-contention scenarios, where the thread * is likely to quickly acquire
 * the lock or condition it's waiting for, * avoiding an expensive context switch. * On modern x86
 * processors, this instruction can be invoked using @c __builtin_ia32_pause() * in GCC/Clang or @c
 * _mm_pause() in MSVC. In non-x86 architectures, alternative mechanisms such as yielding the CPU
 * may be used instead.
 *
 */
inline void pause() {
#if defined(__x86_64__) || defined(_M_X64) || defined(__i386__) || defined(_M_IX86)
  // x86 and x86_64: Use the PAUSE instruction
#  if defined(_MSC_VER)
  // Microsoft Visual C++
  _mm_pause();
#  elif defined(__GNUC__) || defined(__clang__)
  // GCC and Clang
  __builtin_ia32_pause();
#  else
  asm volatile("pause" ::: "memory");
#  endif

#elif defined(__aarch64__) || defined(__arm__)
  // ARM and AArch64: Use the YIELD instruction
#  if defined(__GNUC__) || defined(__clang__)
  asm volatile("yield" ::: "memory");
#  endif

#else
  // Fallback: Portable yield for unknown architectures
  std::this_thread::yield();
#endif
}

/**
 * @brief pause CPU for a specified number of iterations
 * @param count Number of iterations
 */
inline void pause(std::size_t count) {
  while(count-- > 0)
    pause();
}
