#include "types.h"
#include "fcntl.h"
#include "fs.h"
#include "stat.h"
#include "user.h"

#define NULL   ((void*)0)
#define False  (0)
#define True   (1)

static int goDown(int fd, int ino, char* p)
{
  struct dirent de;
  while (read(fd, &de, sizeof(de)) == sizeof(de)) 
  {
    if (de.inum == 0)
      continue;
    
    if (de.inum == ino) 
    {
      strcpy(p, de.name);
      return True;
    }
  }
  return False;
}

static char* goUp(int ino, char* ancestorPath, char* resultPath)
{
  strcpy(ancestorPath + strlen(ancestorPath), "/..");
  
  struct stat st;
  if (stat(ancestorPath, &st) < 0)
    return NULL;

  if (st.ino == ino)
    return resultPath;

  char* foundPath = NULL;

  int fd = open(ancestorPath, O_RDONLY);
  
  if (fd >= 0) 
  {
    char* p = goUp(st.ino, ancestorPath, resultPath);
    if (p != NULL) 
    {
      strcpy(p, "/");

      p += sizeof("/") - 1;

      if (goDown(fd, ino, p))
        foundPath = p + strlen(p);
    }
    close(fd);
  }
  return foundPath;
}

static int getcwd(char* resultPath)
{
  resultPath[0] = '\0';

  char ancestorPath[512];
  strcpy(ancestorPath, ".");

  struct stat st;
  if (stat(ancestorPath, &st) < 0)
    return False;

  char* p = goUp(st.ino, ancestorPath, resultPath);
  if (p == NULL)
    return False;

  if (resultPath[0] == '\0')
    strcpy(resultPath, "/");

  return True;
}

int main(int argc, char *argv[]) 
{
  char resultPath[512];

  if (getcwd(resultPath))
    printf(1, "%s\n", resultPath);
  else
    printf(2, "pwd failed");

  exit();
}