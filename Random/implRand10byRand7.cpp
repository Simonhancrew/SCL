#include <iostream>

using namespace std;

// rand7 => [1, 7], rand10 => [1, 10]

int rand7() {
  return rand() % 7 + 1;
}

int rand10() {
  int res = rand7() + (rand7() - 1) * 7;
  if (res > 40) {
    return rand10();
  }
  return res % 10 + 1;
}

int main() {
  srand(time(NULL));
  cout << rand10() << endl;
}
