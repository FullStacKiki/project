#include "types.h"
#include "utils.h"
#include <stdio.h>
void clear_screen() { printf("\033[2J\033[2H"); }

int main() {
  printf("hello");
  clear_screen();
}
