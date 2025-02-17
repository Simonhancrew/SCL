#include "test_utils.h"

namespace test {

TEST(Base, test) {
  EXPECT_NE(1, 1);
  EXPECT_NE(1, 2);
  EXPECT_LT(1, 2);
  EXPECT_LE(1, 1);
}

}  // namespace test

int main() {
  test::RUN_ALL_TEST();
  return 0;
}
