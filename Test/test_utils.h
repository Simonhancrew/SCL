#pragma once

#include <cstdio>

#if defined(_linux) || defined(_unix)

#define COLOR(msg, code) "\033[0;1;" #code "m" msg "\033[0m"
#define RED(msg)         COLOR(msg, 31)
#define GREEN(msg)       COLOR(msg, 32)
#define YELLOW(msg)      COLOR(msg, 33)
#define BLUE(msg)        COLOR(msg, 34)

#elif defined(_WIN32) || defined(_WIN64)
#include <windows.h>

inline void SetConsoleColor(WORD color) {
  HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
  SetConsoleTextAttribute(hConsole, color);
}

#define COLOR_WIN(color) SetConsoleColor(color)

inline void ResetConsoleColor() {
  SetConsoleColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

#define RESET_WIN() ResetConsoleColor()

#define RED()   COLOR_WIN(FOREGROUND_RED | FOREGROUND_INTENSITY)
#define GREEN() COLOR_WIN(FOREGROUND_GREEN | FOREGROUND_INTENSITY)
#define YELLOW() \
  COLOR_WIN(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY)
#define BLUE() COLOR_WIN(FOREGROUND_BLUE | FOREGROUND_INTENSITY)

#else

#define RED(msg)    msg
#define GREEN(msg)  msg
#define YELLOW(msg) msg
#define BLUE(msg)   msg

#endif

// EXPECT define
#if defined(_WIN32) || defined(_WIN64)

#define EXPECT(a, cmp, b)                                                   \
  {                                                                         \
    decltype(a) __a = (a), __b = (b);                                       \
    if (!((__a)cmp(__b))) {                                                 \
      RED();                                                                \
      printf("%s:%d : Failure\n", __FILE__, __LINE__);                      \
      RESET_WIN();                                                          \
      YELLOW();                                                             \
      printf("Expect: (%s) %s (%s), actual: %d vs %d\n", #a, #cmp, #b, __a, \
             __b);                                                          \
      RESET_WIN();                                                          \
    }                                                                       \
  }

#else

// EXPECT define
#define EXPECT(a, cmp, b)                                                      \
  {                                                                            \
    decltype(a) __a = (a), __b = (b);                                          \
    if (!((__a)cmp(__b))) {                                                    \
      printf("%s:%d : Failure\n", __FILE__, __LINE__);                         \
      printf(YELLOW("Expect: (%s) %s (%s), actual: %d vs %d\n"), #a, #cmp, #b, \
             __a, __b);                                                        \
    }                                                                          \
  }

#endif

#define EXPECT_EQ(a, b) EXPECT(a, ==, b)
#define EXPECT_NE(a, b) EXPECT(a, !=, b)
#define EXPECT_LT(a, b) EXPECT(a, <, b)
#define EXPECT_LE(a, b) EXPECT(a, <=, b)

namespace test {

constexpr size_t kFuncSize = 1000;

struct RegisterNode {
  void (*func)();
  const char *funcname;
};

RegisterNode func_array[kFuncSize];
int func_cnt = 0;

inline void add_func(void (*func)(), const char *str_name) {
  func_array[func_cnt].func     = func;
  func_array[func_cnt].funcname = str_name;
  func_cnt++;
}

#if defined(_WIN32) || defined(_WIN64)

#define TEST(a, b)                                   \
  void a##_##b();                                    \
  static void reg_##a##_##b() {                      \
    add_func(a##_##b, #a "." #b);                    \
  }                                                  \
  struct reg_##a##_##b##_t {                         \
    reg_##a##_##b##_t() {                            \
      reg_##a##_##b();                               \
    }                                                \
  };                                                 \
  static reg_##a##_##b##_t reg_##a##_##b##_instance; \
  void a##_##b()

#else

#define TEST(a, b)                                    \
  void a##_##b();                                     \
  __attribute__((constructor)) void reg_##a##_##b() { \
    add_func(a##_##b, #a "." #b);                     \
  }                                                   \
  void a##_##b()

#endif

int RUN_ALL_TEST() {
  for (int i = 0; i < func_cnt; i++) {
#if defined(_WIN32) || defined(_WIN64)
    GREEN();
    printf("[  RUN   ] ");
    RESET_WIN();
    printf("%s\n", func_array[i].funcname);
#else
    printf(GREEN("[  RUN   ] ") "%s\n", func_array[i].funcname);
#endif
    func_array[i].func();
  }
  return 0;
}

}  // namespace test
