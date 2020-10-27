#ifndef _MEMORY_H_
#define _MEMORY_H_

size_t const token_capacity = 32;
typedef struct _memory_page_t {
   uint8_t* buffer;
   size_t available;
   size_t allocated;
   struct _memory_page_t* next;
   struct _memory_page_t* prev;
} memory_page_t;

typedef struct {
   memory_page_t* head;
   memory_page_t* current;
   size_t page_count;
} memory_state_t;

#define max(a, b) ((a) > (b) ? (a) : (b))
void* parser_malloc_impl(memory_state_t* const memory, size_t size)
{
   size_t const page_size = 1 << 12; // 4kB
   size_t const remainder = (size % 4); // align to 4-bytes
   size += (remainder == 0 ? 0 : 4 - remainder);
   memory_page_t* current = memory->current;
   if(current == nullptr || current->available < size) {
      current = (memory_page_t*) malloc(sizeof(memory_page_t));
      current->buffer = (uint8_t*) malloc(max(size, page_size));
      current->available = current->allocated = max(size, page_size);
      current->prev = memory->current;
      current->next = nullptr;
      ++memory->page_count;
      if(memory->head == nullptr) {
         memory->head = current;
         memory->current = current;
      } else {
         if(size >= page_size) {
            current->prev = memory->current->prev;
            current->next = memory->current;
            if(current->prev) {
               current->prev->next = current;
            } else {
               memory->head = current;
            }
            memory->current->prev = current;
         } else {
            memory->current->next = current;
            memory->current = current;
         }
      }
   }
   size_t offset = (current->allocated - current->available);
   current->available -= size;
   return current->buffer + offset;
}
#define parser_malloc(size) parser_malloc_impl(state->memory, size)

#endif //_MEMORY_H_
