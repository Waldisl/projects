
#include "ft_printf.h"

int main(void)
{
   char g[] = "%-0.222s";
   g[5] = '1';
   ft_printf("I len : %d\n", ft_printf(g, "test"));
   printf("I len : %d\n", printf(g, "test"));
   return (0);
}