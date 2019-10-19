#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <pwd.h>
#include <grp.h>
#include <unistd.h>
#include <sys/sysmacros.h>
#include <string.h>
#define FILETYPE 0
#define PERMIT 1
//This function is for Step 4
char * time2str(const time_t * when, long ns) {
  char * ans = malloc(128 * sizeof(*ans));
  char temp1[64];
  char temp2[32];
  const struct tm * t= localtime(when);
  strftime(temp1,512,"%Y-%m-%d %H:%M:%S",t);  
  strftime(temp2,32,"%z",t);
  snprintf(ans,128,"%s.%09ld %s", temp1, ns, temp2);
  return ans;
}
//This function is for outputing filetype and permitssion
void ft(struct stat * sb, char * out, int chose){
  char filetype[30];
  char permit;
  switch ((*sb).st_mode & S_IFMT) {
  case S_IFBLK:
    strncpy(filetype, "block special file", 30);
    permit = 'b';
    break;
  case S_IFCHR:
    strncpy(filetype, "character special file", 30);
    permit = 'c';
    break;
  case S_IFDIR:
    strncpy(filetype, "directory", 30);
    permit = 'd';
    break;
  case S_IFIFO:
    strncpy(filetype, "fifo", 30);
    permit = 'p';
    break;
  case S_IFLNK:
    strncpy(filetype, "symbolic link", 30);
    permit = 'l';
    break;
  case S_IFREG:
    permit = '-';
    strncpy(filetype, "regular file", 30);
    break;
  case S_IFSOCK:
    strncpy(filetype, "socket", 30);
    permit = 's';
    break;
  default:
    strncpy(filetype, "unknown?", 30);
    break;
  }
  if(chose == FILETYPE){
    strncpy(out, filetype, 30);
  }
  else{
    out[0] = permit;
  }
}

void Access(struct stat * sb, char * strs){
  ft(sb, strs, PERMIT);
  if((*sb).st_mode & ~S_IFMT){
    strs[1] = 'r';
  }
  else{
    strs[1] = '-';
  }
  
  if((*sb).st_mode & S_IWUSR){
    strs[2] = 'w';
  }
  else{
    strs[2] = '-';
  }
  
  if((*sb).st_mode & S_IXUSR){
    strs[3] = 'x';
  }
  else{
    strs[3] = '-';
  }
  
  if((*sb).st_mode & S_IRGRP){
    strs[4] = 'r';
  }
  else{
    strs[4] = '-';
  }
  
  if((*sb).st_mode & S_IWGRP){
    strs[5] = 'w';
  }
  else{
    strs[5] = '-';
  }
  
  if((*sb).st_mode & S_IXGRP){
    strs[6] = 'x';
  }
  else{
    strs[6] = '-';
  }
  
  if((*sb).st_mode & S_IROTH){
    strs[7] = 'r';
  }
  else{
      strs[7] = '-';
  }
  
  if((*sb).st_mode & S_IWOTH){
    strs[8] = 'w';
  }
    else{
      strs[8] = '-';
    }
  
  if((*sb).st_mode & S_IXOTH){
    strs[9] = 'x';
  }
  else{
    strs[9] = '-';
  }
  strs[10] = '\0';
}
//construct type stat
void loadsb(char * filename, struct stat * sb){
  if (lstat(filename, sb) == -1) {
    perror("stat");
    exit(EXIT_FAILURE);
  }
}
//constuct line1234
void line1234(char * filename){
    struct stat sb;
    loadsb(filename, &sb);
    //first line
    if((sb.st_mode & S_IFMT) == S_IFLNK ) {
      char linktarget[256];
      ssize_t len = readlink(filename, linktarget, 256);
      linktarget[len] = '\0';
      printf("  File: %s -> %s\n", filename, linktarget);
    }
    else{
      printf("  File: %s\n", filename);
    }
    //second line
    char filetype[30];
    ft(&sb, filetype, FILETYPE);
    printf("  Size: %-10lu\tBlocks: %-10lu IO Block: %-6lu %s\n",
	   sb.st_size,
	   sb.st_blocks,
	   sb.st_blksize,
	   filetype
	   );
    //third line
    if( S_ISCHR(sb.st_mode) || S_ISBLK(sb.st_mode) ){
      printf("Device: %lxh/%lud\tInode: %-10lu  Links: %-5lu Device type: %d,%d\n",
	     sb.st_dev,
	     sb.st_dev,
	     sb.st_ino,
	     sb.st_nlink,
	     major(sb.st_rdev),
	     minor(sb.st_rdev)
	     );
    }
    else{
      printf("Device: %lxh/%lud\tInode: %-10lu  Links: %lu\n",
	     sb.st_dev,
	     sb.st_dev,
	     sb.st_ino,
	     sb.st_nlink);
    }
    //fourth line
    char strs[11];
    Access(&sb, strs);
    struct passwd * psw = getpwuid(sb.st_uid);
    struct group * grd = getgrgid(sb.st_gid); 
    printf("Access: (%04o/%s)  Uid: (%5d/%8s)   Gid: (%5d/%8s)\n",
	   sb.st_mode & ~S_IFMT,
	   strs,
	   sb.st_uid,
	   psw->pw_name,
	   sb.st_gid,
	   grd->gr_name
	   );
}
//construct line5678
void line5678(char *filename){
  struct stat sb;
  loadsb(filename, &sb);
  char *timestr_a =   time2str(&sb.st_atime, 
			       sb.st_atim.tv_nsec);
  char *timestr_m =   time2str(&sb.st_mtime, 
			       sb.st_mtim.tv_nsec);
  char *timestr_c =   time2str(&sb.st_ctime, 
			       sb.st_ctim.tv_nsec);
  printf("Access: %s\n", timestr_a);
  printf("Modify: %s\n", timestr_m);
  printf("Change: %s\n", timestr_c);
  printf(" Birth: -\n");
  free(timestr_a);
  free(timestr_m);
  free(timestr_c);
}

int main(int argc, char ** argv) {
    if (argc < 2) {
      fprintf(stderr, "Usage: %s <pathname>\n", argv[0]);
      return EXIT_FAILURE;
    }
    for(int i = 1; i < argc; i++){
      line1234(argv[i]);
      line5678(argv[i]);
    }
    return EXIT_SUCCESS;
}

