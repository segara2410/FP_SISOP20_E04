#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

char* strcat(char *d, char *s)
{
  char *temp=d;
  while(*d) ++d;
  while(*s) *d++=*s++;
  *d=0;
  return temp;
}

int isDir(char * path)
{
  int fd;
  fd = open (path, 0);
  if (fd<0)
  {
    return -1;
  }

  struct stat st;
  if(fstat(fd, &st) < 0)
  {
    return -1;
  }
  if (st.type == T_FILE)
  {
    return 0;
  }
  else if (st.type == T_DIR)
  {
    return 1;
  }
  else 
    return -1;

}

void cp (char *src, char *dest)
{
  printf(1, "%s to %s", src, dest);
  if ((link(src, dest) < 0))
    printf(2, "cp %s to %s failed\n", src, dest);
}

// void cpDir (char *src, char *dest)
// {

// }

int main (int argc, char *argv[]){
  if (argc != 3)
  {
    printf(2, "Usage: cp oldname newname\n");
    exit();
  }
  
  // if (argv[1][0] == '-' && argv[1][1] == 'r' && strlen(argv[1]) == 2)
  //   cpDir(argv[2], argv[3]);
  // else
  // {
    if (isDir(argv[2]))
    {
      char *new_target = "a";
      strcpy(new_target, argv[2]);
      strcpy(new_target + strlen(new_target), "/");
      strcpy(new_target + strlen(new_target), argv[1]);
      cp(argv[1], new_target);
      exit();
    }

    cp(argv[1], argv[2]);
  // }

  exit();
}