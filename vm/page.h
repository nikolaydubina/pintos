#ifndef VM_PAGE
#define VM_PAGE

#include <stdlib.h>
#include <inttypes.h>
#include "kernel/hash.h"
#include "kernel/list.h"
#include "threads/thread.h"
#include "threads/malloc.h"
#include "threads/palloc.h"

enum page_type{
  PAGE_FILE,
  PAGE_SWAP,
  PAGE_MMAP
};

struct page{
  void* vaddr;          /* page,  user,   virual   address */
  void* paddr;          /* frame, kernel, physical address */

  bool writable;        /* user allowed to write */
  bool loaded;          /* ready for read/write */
  bool pinned;          /* true if not in Interrupt context. FIXME*/

  enum page_type type;

  struct hash_elem hash_elem;
};

struct page_table{
  struct thread* thread;
  struct hash table;
};

void page_init(void);

void page_construct(void);
void page_destruct(void);

//void* page_allocate(enum palloc_flags flags);
//struct page* page_get(void* addr);
//void page_free(void* addr);

bool load_page(struct page* page);
bool grow_stack(void* vaddr);

#endif // VM_PAGE
