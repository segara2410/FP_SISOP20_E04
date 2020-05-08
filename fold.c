#include "types.h"
#include "stat.h"
#include "user.h"

char buf[512];

void fold(int fd, int count)
{
  int n;
  int c = 0;

  while((n = read(fd, buf, sizeof(buf))) > 0 )
  {
    for(int i = 0; i < n; i++)
    {				
      if (buf[i] != '\n')
      {			
      	printf(1, "%c", buf[i]);
        c++;
      }
      else
      {
        if (c == 0)
          continue;
      	printf(1, "\n");
      	c = 0;
      } 

      if (c == count)
      {
      	printf(1, "\n");
        c = 0;
      }
    }
  }
  printf(1, "\n");

  if(n < 0)
  {
    printf(1, "fold: read error\n");
    exit();
  }
  exit();
}

int main(int argc, char *argv[]) 
{
  int i;
  int fd = 0;
  int x = 80;
  char a;

  if (argc <= 1) 
  {	
    fold(0, x);
    exit();
  }

  else 
  {
    for (i = 1; i < argc; i++) 
    {
      a = *argv[i];

      if (a == '-') 
      { 
        argv[i]++;
        a = *argv[i];

        if (a == 'w')
        {
          argv[i]++;

          if (atoi(argv[i]) == 0)
            i++;
        }
        x = atoi(argv[i]);
      }
      else 
      {	
        if ((fd = open(argv[i], 0)) < 0) 
        {
          printf(1, "fold: cannot open %s\n", argv[i]);
          exit();
        }
      }
    }
  
    fold(fd, x);
    close(fd);
    exit();
  }
}