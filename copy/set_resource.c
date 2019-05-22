#include <sys/time.h>
#include <sys/resource.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char **argv)
{
 struct rlimit rlim;
 int res;

 getrlimit(RLIMIT_NOFILE, &rlim);
 printf("Open file before  %d : %d\n", (int)rlim.rlim_cur, (int)rlim.rlim_max);
 
 rlim.rlim_cur += 1024;
 rlim.rlim_max += 1024;
 if((res=setrlimit(RLIMIT_NOFILE, &rlim)) == -1) {
  printf("setrlimint =  %d\n ", res);
  return 0;
}
 printf("Open file after  %d : %d\n", (int)rlim.rlim_cur, (int)rlim.rlim_max);
 return 0;

}
