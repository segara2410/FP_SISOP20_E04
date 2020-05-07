#include "types.h"
#include "stat.h"
#include "user.h"

char buf[512];
int q = 1;

void
head(int fd, char *name, int line)
{
  int n;
  int l = 1;

  while((n = read(fd, buf, sizeof(buf))) > 0 )
  {
    for(int i = 0; i <= n; i++)
    {				
      //print the characters in the line 
      if (buf[i] != '\n')
      	printf(1,"%c",buf[i]);
      
      //if the number of lines is equal to l, then exit
      else if (l == line)
      {
        printf(1,"\n");	
        exit();
      }

      //if the number of lines is not equal to l, then jump to next line and increment the value of l 
      else
      {
      	printf(1, "\n");
      	l++;
      } 
    }
  }

  if(n < 0){
    printf(1, "head: read error\n");
    exit();
  }
}

void
headQ(int fd, char *name)
{
  int n;

  while((n = read(fd, buf, sizeof(buf))) > 0 )
  {
    for(int i = 0; i <= n; i++)
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

  if(n < 0){
    printf(1, "head: read error\n");
    exit();
  }
}

void headByte(int fd, char *name, int byte)
{
  int n;
  int b = 0;
  while((n = read(fd, buf, sizeof(buf))) > 0 )
  {
    for(int i = 0; i <= n; i++)
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
  
  if(n < 0){
    printf(1, "head: read error\n");
    exit();
  }
}

int
main(int argc, char *argv[]) 
{
  int fd = 0;	// when the file is not specified, then it will take input from the user
  int x = 10;	// will read the first 10 lines by default
  char *file;	// pointer to the name of the file

  file = ""; // in the case when no file name is specified, it will take input from the user

  if (argc <= 1) 
  {	
    head(0, "", 10);	// handles the default case of taking input from user for 10 lines
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

        head(fd, file, x);
      }
      else if (argv[1][1] == 'c')
      {
        x = atoi(argv[2]);
        if ((fd = open(argv[3], 0)) < 0) 
        {
          printf(1, "head: cannot open %s\n", argv[3]);
          exit();
        }

        headByte(fd, file, x);
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

          headQ(fd, file);
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

        head(fd, file, x);
      }
    }
    // for (i = 1; i < argc; i++) 
    // {

    //   if (a == '-')  // it means that -NUM is provided, hence limited number of lines are to be printed
    //   {
    //     argv[i]++;
    //     x = atoi(argv[i]++);
    //   }
      
    //   else 
    //   {
    //     if ((fd = open(argv[i], 0)) < 0) 
    //     {
    //       printf(1, "head: cannot open %s\n", argv[i]);
    //       exit();
    //     }
    //   }
    // }
  
    head(fd, file, x);
    close(fd);
    exit();    

  }
}