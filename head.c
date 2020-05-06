#include "types.h"
#include "stat.h"
#include "user.h"

char buf[512];
int q = 1;

void head(int fd, int line)
{
  int n;
  int l = 1;

  while ((n = read(fd, buf, sizeof(buf))) > 0 )
  {
    for(int i = 0; i <= n; i++)
    {				
      if (buf[i] != '\n')
      	printf(1,"%c",buf[i]);
      
      else if (l == line)
      {
        printf(1,"\n");	
        exit();
      }

      else
      {
      	printf(1, "\n");
      	l++;
      } 
    }
  }

  if (n < 0)
  {
    printf(1, "head: read error\n");
    exit();
  }
}

void headQ(int fd)
{
  int n;

  while ((n = read(fd, buf, sizeof(buf))) > 0 )
  {
    for (int i = 0; i <= n; i++)
    {
      if (buf[i] != '\n')
      	printf(1,"%c",buf[i]);
      
      else if (q == 20)
      {
        printf(1,"\n");	
        exit();
      }

      else
      {
      	printf(1, "\n");
      	q++;
      } 
    }
  }
  q++;
  printf(1, "\n");

  if (n < 0)
  {
    printf(1, "head: read error\n");
    exit();
  }
}

void headByte(int fd, int byte)
{
  int n;
  int b = 0;
  while ((n = read(fd, buf, sizeof(buf))) > 0)
  {
    for (int i = 0; i <= n; i++)
    {
      printf(1,"%c",buf[i]);
      b++;
      if (b == byte)
      {
        printf(1, "\n");	
        exit();
      }
    }
  }
  printf(1,"\n");
  
  if (n < 0)
  {
    printf(1, "head: read error\n");
    exit();
  }
}

int main(int argc, char *argv[]) 
{
  int fd = 0;
  int x = 10;

  if (argc <= 1) 
  {	
    head(0, 10);
    exit();
  }

  else 
  {
    if (argv[1][0] == '-')
    {
      if (argv[1][1] == 'n')
      {
        x = atoi(argv[2]);
        if ((fd = open(argv[3], 0)) < 0) 
        {
          printf(1, "head: cannot open %s\n", argv[3]);
          exit();
        }

        head(fd, x);
      }
      else if (argv[1][1] == 'c')
      {
        x = atoi(argv[2]);
        if ((fd = open(argv[3], 0)) < 0) 
        {
          printf(1, "head: cannot open %s\n", argv[3]);
          exit();
        }

        headByte(fd, x);
      }
      else if (argv[1][1] == 'q')
      {
        int i = 2;
        while (q > 0)
        {
          if ((fd = open(argv[i], 0)) < 0) 
          {
            printf(1, "head: cannot open %s\n", argv[i]);
            exit();
          }

          headQ(fd);
          i++;
        }
      }
      else if (argv[1][1] == 'v')
      {
        printf(1, "==> %s <==\n", argv[2]);

        x = 10;
        if ((fd = open(argv[2], 0)) < 0) 
        {
          printf(1, "head: cannot open %s\n", argv[2]);
          exit();
        }

        head(fd, x);
      }
    }

    head(fd, x);
    close(fd);
    exit();    

  }
}