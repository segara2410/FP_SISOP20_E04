#include "types.h"
#include "stat.h"
#include "user.h"

char buf[512];

void fold(int fd, char *name, int count)
{
  int n;
  int c = 0;

  while((n = read(fd, buf, sizeof(buf))) > 0 )
  {
    for(int i=0; i<=n ;i++)
    {				
      if (buf[i]!='\n')
      {			
      	printf(1,"%c",buf[i]);
        c++;
      }
      else
      {
      	printf(1,"\n");
      	c = 0;
      } 

      if (c == count)
      {
      	printf(1,"\n");
        c = 0;
      }
    }
  }
  printf(1,"\n");

  if(n < 0){
    printf(1, "fold: read error\n");
    exit();
  }
  exit();
}

int main(int argc, char *argv[]) 
{
  int i;
  int fd = 0;
  int x = 100;
  char *file = "";
  char a;

  if (argc <= 1) 
  {	
    fold(0, "", 100);
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
  
    fold(fd, file, x);
    close(fd);
    exit();
  }
}