// HENRIQUE CURY
// he200230


#include <stdio.h>
#include <string.h>
#include "Ohce.h"

double difficultyRating(void)
{
    return 4.0;
}
double hoursSpent(void)
{
    return 10.0;
}

int main(int argc, char **argv)
{
  int i, j, x, length;

  //Goes through each argument
  for(i=1;i<argc;i++)
  {

    length = strlen(argv[i]);

    for(j = length-1; j >= 0; j--)
    {
      //Printing each letter 1by1 backwards
      printf("%c", argv[i][j]);

      //Checks for word echo embedded in string?
      if(argv[i][j] == 'e' || argv[i][j] == 'E')
      {
        if(argv[i][j+1] == 'c' || argv[i][j+1] == 'C')
        {
          if (argv[i][j+2] == 'h' || argv[i][j+2] == 'H')
          {
            if (argv[i][j+3] == 'o' || argv[i][j+3] == 'O')
            {
              x = 1;
            }
          }
        }
      }
      // end of loop
    }

    if (i < argc-1)
    {
        printf(" ");
    }
    else
    {
        printf("\n");
    }
  }


  if (x)
  {
    printf("Echo, echo, echo!\n");
  }

  return 0;
}
