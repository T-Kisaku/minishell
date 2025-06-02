#include <stdio.h>
#include "testdata.h"
int main()
{
  t_testdata testdata_ls = ls();
  printf("test data ls's input: %s\n", testdata_ls.input);
  puts("FIRE");
}
