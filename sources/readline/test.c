#include <unistd.h>

int main(void)
{
  char str[10];
  read(0, str, 9);
  str[9] = '\0';
  for (int i = 0; i < 10; i++)
    write(1, &str[i], 1);
  return (0);
}