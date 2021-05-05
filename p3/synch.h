#define NTHREAD 8

struct mutex_t
{
  int initialized; // is initialized?
  struct spinlock lock; // spinlock for mutex
  struct proc *current; // current locked thread
  struct proc *queue[NTHREAD - 1]; // queueing thread list
  int qsize; // queue size
};

struct cond_t
{
  int initialized;
  struct spinlock lock;
  struct proc *queue[NTHREAD - 1];
  int qsize;
};

struct spinlock;
struct proc;
