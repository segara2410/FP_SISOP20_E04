#include "types.h"
#include "stat.h"
#include "user.h"

char buf[512];

void fold(int fd, char *name, int count)
{
  int n; //here the size of the read chunk is defined by n
  int c = 0;

  while((n = read(fd, buf, sizeof(buf))) > 0 )
  {
    for(int i=0; i<=n ;i++)
    {				
      //print the characters in the count 
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
  int fd = 0;	// when the file is not specified, then it will take input from the user
  int x = 100;	// will read the first 100 counts by default
  char *file;	// pointer to the name of the file
  char a;

  file = ""; // in the case when no file name is specified, it will take input from the user

  if (argc <= 1) 
  {	
    fold(0, "", 100);	// handles the default case of taking input from user for 100 counts
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
        printf(1, "argvi %s\n", argv[i]);
        a = *argv[i];

        if (a == 'w')
        {
          argv[i]++;
          printf(1, "argvi %s\n", argv[i]);

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