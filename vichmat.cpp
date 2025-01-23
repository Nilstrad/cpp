#include <stdio.h>
#include <iostream>
#include <math.h>

double f(double x)
{
   return pow(x, 3) - 3* pow(x, 2) + 9 * x -8;
}

int main(int argc, char *argv[])
{
   double a, b, h;
   a = 1.1;
   b = 1.25;
   h = 0.01;
   do
   {
      b = a + h;
      if (f(a) * f(b) < 0)
      {
         std::cout << "Interval [" 
                   << a << ";" << b << "]" << std::endl;
         break;
      }
      a = b;
   } 
   while (b <= 1.25);
   system("pause");
   return 0;
}