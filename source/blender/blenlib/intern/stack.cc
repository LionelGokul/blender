#include "BLI_stack.h"  // Include the header for function declarations
#include "BLI_utildefines.h"
#include "MEM_guardedalloc.h"

#include <cassert>
#include <cstring>

#define CHUNK_EMPTY ((size_t)-1)
#define CHUNK_SIZE_DEFAULT (1 << 16)
#define CHUNK_ELEM_MIN 32

// Class definitions should only appear once, typically in the .cc file if not shared
class StackChunk {
 public:
  StackChunk *next;
  char *data;

  explicit StackChunk(size_t dataSize) : next(nullptr)
  {
    data = static_cast<char *>(MEM_mallocN(dataSize, __func__));
    if (!data) {
      abort();  // Handle memory allocation failure
    }
  }

  ~StackChunk()
  {
    MEM_freeN(data);
  }
};

class Stack {
 private:
  StackChunk *chunk_curr;
  StackChunk *chunk_free;
  size_t chunk_index;
  size_t chunk_elem_max;
  size_t elem_size;
  size_t elem_num;

  void *getLastElem() const
  {
    return chunk_curr->data + (elem_size * chunk_index);
  }

  size_t calculateChunkElemMax(size_t chunk_size) const
  {
    const size_t elem_size_min = elem_size * CHUNK_ELEM_MIN;
    BLI_assert((elem_size != 0) && (chunk_size != 0));

    while (chunk_size <= elem_size_min) {
      chunk_size <<= 1;
    }

    chunk_size -= sizeof(StackChunk) + MEM_SIZE_OVERHEAD;
    return chunk_size / elem_size;
  }

  void freeChunks(StackChunk *data)
  {
    while (data) {
      StackChunk *next_chunk = data->next;
      delete data;
      data = next_chunk;
    }
  }

 public:
  explicit Stack(size_t elem_size, size_t chunk_size = CHUNK_SIZE_DEFAULT)
      : chunk_curr(nullptr), chunk_free(nullptr), chunk_index(0), elem_size(elem_size), elem_num(0)
  {
    chunk_elem_max = calculateChunkElemMax(chunk_size);
    chunk_index = chunk_elem_max - 1;
  }

  ~Stack()
  {
    freeChunks(chunk_curr);
    freeChunks(chunk_free);
  }

  void *push_r()
  {
    chunk_index++;

    if (chunk_index == chunk_elem_max) {
      StackChunk *chunk;
      if (chunk_free) {
        chunk = chunk_free;
        chunk_free = chunk_free->next;
      }
      else {
        chunk = new StackChunk(elem_size * chunk_elem_max);
      }

      chunk->next = chunk_curr;
      chunk_curr = chunk;
      chunk_index = 0;
    }

    elem_num++;
    return getLastElem();
  }

  void push(const void *src)
  {
    void *dst = push_r();
    std::memcpy(dst, src, elem_size);
  }

  void pop(void *dst)
  {
    BLI_assert(!isEmpty());
    std::memcpy(dst, getLastElem(), elem_size);
    discard();
  }

  void pop_n(void *dst, uint n)
  {
    BLI_assert(n <= count());
    while (n--) {
      pop(dst);
      dst = static_cast<char *>(dst) + elem_size;
    }
  }

  void pop_n_reverse(void *dst, uint n)
  {
    BLI_assert(n <= count());
    dst = static_cast<char *>(dst) + (elem_size * n);

    while (n--) {
      dst = static_cast<char *>(dst) - elem_size;
      pop(dst);
    }
  }

  void *peek() const
  {
    BLI_assert(!isEmpty());
    return getLastElem();
  }

  void discard()
  {
    BLI_assert(!isEmpty());
    elem_num--;

    if (--chunk_index == CHUNK_EMPTY) {
      StackChunk *chunk_to_free = chunk_curr;
      chunk_curr = chunk_curr->next;

      chunk_to_free->next = chunk_free;
      chunk_free = chunk_to_free;

      chunk_index = chunk_elem_max - 1;
    }
  }

  void clear()
  {
    if (elem_num == 0) {
      return;
    }

    elem_num = 0;
    chunk_index = chunk_elem_max - 1;

    if (chunk_free) {
      if (chunk_curr) {
        StackChunk *last_free_chunk = chunk_free;
        while (last_free_chunk->next) {
          last_free_chunk = last_free_chunk->next;
        }
        last_free_chunk->next = chunk_curr;
        chunk_curr = nullptr;
      }
    }
    else {
      chunk_free = chunk_curr;
      chunk_curr = nullptr;
    }
  }

  size_t count() const
  {
    return elem_num;
  }

  bool isEmpty() const
  {
    BLI_assert((chunk_curr == nullptr) == (elem_num == 0));
    return chunk_curr == nullptr;
  }
};

// C Interface Wrappers
extern "C" {
BLI_Stack *BLI_stack_new_ex(const size_t elem_size,
                            const char *description,
                            const size_t chunk_size)
{
  (void)description;  // Suppress unused parameter warning
  return reinterpret_cast<BLI_Stack *>(new Stack(elem_size, chunk_size));
}

BLI_Stack *BLI_stack_new(const size_t elem_size, const char *description)
{
  return BLI_stack_new_ex(elem_size, description, CHUNK_SIZE_DEFAULT);
}

void BLI_stack_free(BLI_Stack *stack)
{
  delete reinterpret_cast<Stack *>(stack);
}

void *BLI_stack_push_r(BLI_Stack *stack)
{
  return reinterpret_cast<Stack *>(stack)->push_r();
}

void BLI_stack_push(BLI_Stack *stack, const void *src)
{
  reinterpret_cast<Stack *>(stack)->push(src);
}

void BLI_stack_pop(BLI_Stack *stack, void *dst)
{
  reinterpret_cast<Stack *>(stack)->pop(dst);
}

void BLI_stack_pop_n(BLI_Stack *stack, void *dst, uint n)
{
  reinterpret_cast<Stack *>(stack)->pop_n(dst, n);
}

void BLI_stack_pop_n_reverse(BLI_Stack *stack, void *dst, uint n)
{
  reinterpret_cast<Stack *>(stack)->pop_n_reverse(dst, n);
}

void *BLI_stack_peek(BLI_Stack *stack)
{
  return reinterpret_cast<Stack *>(stack)->peek();
}

void BLI_stack_discard(BLI_Stack *stack)
{
  reinterpret_cast<Stack *>(stack)->discard();
}

void BLI_stack_clear(BLI_Stack *stack)
{
  reinterpret_cast<Stack *>(stack)->clear();
}

size_t BLI_stack_count(const BLI_Stack *stack)
{
  return reinterpret_cast<const Stack *>(stack)->count();
}

bool BLI_stack_is_empty(const BLI_Stack *stack)
{
  return reinterpret_cast<const Stack *>(stack)->isEmpty();
}
}
