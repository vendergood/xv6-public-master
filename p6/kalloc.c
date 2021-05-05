// Physical memory allocator, intended to allocate
// memory for user processes, kernel stacks, page table pages,
// and pipe buffers. Allocates 4096-byte pages.

#include "types.h"
#include "defs.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "spinlock.h"

void freerange(void *vstart, void *vend);
extern char end[]; // first address after kernel loaded from ELF file
                   // defined by the kernel linker script in kernel.ld

struct run {
  struct run *next;
};

struct {
  struct spinlock lock;
  int use_lock;
  struct run *freelist;
  int num_of_free_pages;
  int reference_count[100000];
} kmem;

// Initialization happens in two phases.
// 1. main() calls kinit1() while still using entrypgdir to place just
// the pages mapped by entrypgdir on free list.
// 2. main() calls kinit2() with the rest of the physical pages
// after installing a full page table that maps them on all cores.
void
kinit1(void *vstart, void *vend)
{
  initlock(&kmem.lock, "kmem");
  kmem.use_lock = 0;
  kmem.num_of_free_pages = 0; // initialize number of pages to zero
  freerange(vstart, vend);
  for (int i = 0; i < 100000; i++) kmem.reference_count[i] = 0;
}

void
kinit2(void *vstart, void *vend)
{
  freerange(vstart, vend);
  kmem.use_lock = 1;
}

void
freerange(void *vstart, void *vend)
{
  char *p;
  p = (char*)PGROUNDUP((uint)vstart);
  for(; p + PGSIZE <= (char*)vend; p += PGSIZE)
  {
    kfree(p);
  }
}
//PAGEBREAK: 21
// Free the page of physical memory pointed at by v,
// which normally should have been returned by a
// call to kalloc().  (The exception is when
// initializing the allocator; see kinit above.)
void
kfree(char *v) // v: virtual address
{
  struct run *r;

  if((uint)v % PGSIZE || v < end || V2P(v) >= PHYSTOP)
    panic("kfree");


  if(kmem.use_lock)
    acquire(&kmem.lock);
  r = (struct run*)v;

  if (kmem.reference_count[V2P(v) / PGSIZE] > 0) // if there are some processes that reference this page
    kmem.reference_count[V2P(v) / PGSIZE]--;

  if (!kmem.reference_count[V2P(v) / PGSIZE])// if no process references this page
  {
    // Fill with junk to catch dangling refs.
    memset(v, 1, PGSIZE);
    r->next = kmem.freelist;
    kmem.freelist = r;
    kmem.num_of_free_pages++;
  }

  if(kmem.use_lock)
    release(&kmem.lock);
}

// Allocate one 4096-byte page of physical memory.
// Returns a pointer that the kernel can use.
// Returns 0 if the memory cannot be allocated.
char*
kalloc(void)
{
  struct run *r;

  if(kmem.use_lock)
    acquire(&kmem.lock);
  r = kmem.freelist;
  if(r)
  {
    //char *v = (char*)r;
    kmem.freelist = r->next;
    kmem.reference_count[V2P((char*)r) / PGSIZE] = 1;
    kmem.num_of_free_pages--;
  }
  if(kmem.use_lock)
    release(&kmem.lock);
  return (char*)r;
}

int
numfree(void)
{
  if(kmem.use_lock)
    acquire(&kmem.lock);
  
  int result = kmem.num_of_free_pages;
  
  if(kmem.use_lock)
    release(&kmem.lock);

  return result;
}

void
increase_refcount(uint pa)
{
  if(kmem.use_lock)
    acquire(&kmem.lock);
  kmem.reference_count[pa / PGSIZE]++;
  if(kmem.use_lock)
    release(&kmem.lock);
}

int
num_refcount(uint pa)
{
  int count = 0;
  if(kmem.use_lock)
    acquire(&kmem.lock);
  count = kmem.reference_count[pa / PGSIZE];
  if(kmem.use_lock)
    release(&kmem.lock);

  return count;
}

void
decrease_refcount(uint pa)
{
  if(kmem.use_lock)  
    acquire(&kmem.lock);
  kmem.reference_count[pa / PGSIZE]--;
  if(kmem.use_lock)
    release(&kmem.lock);
}