#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

int main(int argc, char **argv)
{
  int pid, nice;

  pid = atoi (argv[1]);
  nice = atoi (argv[2]);

  printf(1, "pid: %d, nice: %d, setnice return value: %d\n", pid, nice, setnice(pid, nice));

  exit();
}
