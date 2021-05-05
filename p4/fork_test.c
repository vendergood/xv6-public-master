#include "types.h"
#include "stat.h"
#include "user.h"

int main(int argc, char **argv){

  int pid = fork();
  printf(1, "before change: %d\n", getnice(pid));
  setnice(pid, 30);
  printf(1, "after change: %d\n", getnice(pid));
  exit();
}
