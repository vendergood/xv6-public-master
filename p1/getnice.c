#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

int main(int argc, char **argv)
{
  int pid;

  pid = atoi (argv[1]);

  printf(1, "pid: %d, getnice return value: %d\n", pid, getnice(pid));

  exit();
}
