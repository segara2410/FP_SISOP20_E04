#include "types.h"
#include "user.h"
#include "stat.h"
#include "fcntl.h"
#include "fs.h"

char* strcat(char *target, char *source)
{
  char *temp = target;
  while(*target) 
    ++target;
  while(*source) 
    *target++ = *source++;
  
  *target = 0;
  return temp;
}

char *getFileName(char *s) 
{
	char *filename = s;
	char *temp = s;
	int i;

	for (i = strlen(temp); i >= 0; i--) 
  {
		if (temp[i] == '/') 
    {
			filename = &temp[i + 1];
			break;
		}
	}

	return filename;
}

int isDirectory(char *s) 
{
	struct stat st;

	int fd = open(s, O_RDONLY);
	fstat(fd, &st);
	int is_directory;

	if (st.type == T_DIR) 
		is_directory = 1;
	else
		is_directory = 0;

	close(fd);
	return is_directory;
}

void move_file(char *source, char *target) 
{

	char *newtarget = (char *) malloc(strlen(getFileName(source)) + strlen(target) + 2);
	strcpy(newtarget, target);

	if (isDirectory(target)) 
  {
		if (target[strlen(target) - 1] != '/') 
      strcat(newtarget, "/");

		strcat(newtarget, getFileName(source));
	} 
  else if (target[strlen(target) - 1] == '/') 
  {
		printf(1, "mv: %s is not a directory\n", target);
		return;
	}

	int fs;
	if ((fs = open(source, O_RDONLY)) < 0) 
  {
		printf(1, "mv: cannot open %s\n", source);
		return;
	}

  int fd;
	if ((fd = open(newtarget, O_CREATE | O_RDWR)) < 0) 
  {
		printf(1, "mv: cannot open %s\n", target);
		return;
	}

	int fb;
  char buffer[512];
	while ((fb = read(fs, buffer, sizeof(buffer))) > 0) 
		write(fd, buffer, fb);

	close(fs);
	close(fd);

	unlink(source);
}

void move_dir(char *source, char *target) 
{

	int fd;
	if((fd = open(source, 0)) < 0)
  {
		printf(2, "mv: cannot open %s\n", source);
		return;
	}

  char bufdir[512];
	strcpy(bufdir, target);
	if (target[strlen(target)-1] != '/') 
    strcat(bufdir, "/");
	
  strcat(bufdir, getFileName(source));

	if (mkdir(bufdir) < 0) 
  {
		mkdir(target);
		strcpy(bufdir, target);
	}

	char buffer[512];
	strcpy(buffer, source);

  char *p;
	p = buffer + strlen(buffer);
	*p = '/';
	p++;

	struct dirent de;
	while(read(fd, &de, sizeof(de)) == sizeof(de)) 
  {
		if(de.inum == 0 || !strcmp(de.name, ".") || !strcmp(de.name, ".."))
			continue;

		memmove(p, de.name, strlen(de.name));
		p[strlen(de.name)] = 0;

		if (isDirectory(buffer))
			move_dir(buffer, bufdir);
		else
			move_file(buffer, bufdir);
	}

	close(fd);

	unlink(source);
}

void move_one(char *source, char *target) 
{
	if (isDirectory(source))
		move_dir(source, target);
	else
		move_file(source, target);
}

void move_all(char *target) 
{
  move_dir(".", target);
}

int main(int argc, char *argv[]) {
	if (argc < 2) 
  {
		printf(1, "mv: missing file operand\n");
		exit();
	} 
  else if (argc < 3) 
  {
		printf(1, "mv: missing destination file operand after '%s'\n", argv[1]);
		exit();
	}

	if (!strcmp(argv[1], "*"))
		move_all(argv[2]);
	else
  {
    if (argc > 3 && !isDirectory(argv[argc - 1]))
    {
		  printf(2, "mv: target '%s' is not a directory\n", argv[argc - 1]);
      exit();
    }

    for (int i = 1; i < argc - 1; i++)
		  move_one(argv[i], argv[argc - 1]);
  }

	exit();
}