/*
 * mm-naive.c - The fastest, least memory-efficient malloc package.
 * 
 * In this naive approach, a block is allocated by simply incrementing
 * the brk pointer.  A block is pure payload. There are no headers or
 * footers.  Blocks are never coalesced or reused. Realloc is
 * implemented directly using mm_malloc and mm_free.
 *
 * NOTE TO STUDENTS: Replace this header comment with your own header
 * comment that gives a high level description of your solution.
 */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include <string.h>

#include "mm.h"
#include "memlib.h"

/*********************************************************
 * NOTE TO STUDENTS: Before you do anything else, please
 * provide your team information in the following struct.
 ********************************************************/
team_t team = {
    /* Team name */
    "team name",
    /* First member's full name */
    "Fenil Mehta",
    /* First member's email address */
    "fenilgmehta@cse.iitb.ac.in",
    /* Second member's full name (leave blank if none) */
    "Vipin Mahawar",
    /* Second member's email address (leave blank if none) */
    "member_2@cse.iitb.ac.in"
};

/* single word (4) or double word (8) alignment */
#define ALIGNMENT 8

/* rounds up to the nearest multiple of ALIGNMENT */
#define ALIGN(size) (((size) + (ALIGNMENT-1)) & ~0x7)


#define SIZE_T_SIZE (ALIGN(sizeof(size_t)))

// ------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------


/* 
 * mm_init - initialize the malloc package.
 */

void *init_mem_sbrk_break = NULL;

struct MemoryMetaData{
	// Size with depend on the size of pointers => either 128 or 192 bytes
	u_int32_t sizeInBytes;
	u_int32_t isFree;
	struct MemoryMetaData *prev, *next;
};

// static size_t sizeofMemoryMetaData = ((sizeof(struct MemoryMetaData) + ALIGNMENT - 1) / ALIGNMENT) * ALIGNMENT;
static size_t sizeofMemoryMetaData = ALIGN(sizeof(struct MemoryMetaData));

static struct MemoryMetaData freeList;

int mm_init(void)
{
	/* 
	 * This function should initialize and reset any data structures used to represent the starting state(empty heap)
	 * 
	 * This function will be called multiple time in the driver code "mdriver.c"
	 */	
    
	// This function is called every time before each test run of the trace.

	// It should reset the entire state of your malloc or the consecutive
	// trace runs will give wrong answer.	
	mem_reset_brk();
    init_mem_sbrk_break = NULL;
	freeList.prev = NULL;
	freeList.next = NULL; // (struct MemoryMetaData *) mem_sbrk(1024);
	
	// if(((intptr_t) freeList.next) == (-1)) return -1;
	return 0;		// Returns 0 on successfull initialization.
}

//---------------------------------------------------------------------------------------------------------------
/* 
 * mm_malloc - Allocate a block by incrementing the brk pointer.
 *     Always allocate a block whose size is a multiple of the alignment.
 */
void *mm_malloc(size_t size) {	
	// static int callCount = 0;
	// printf("mm_malloc: %d\n", ++callCount);

	/* 
	 * This function should keep track of the allocated memory blocks.
	 * The block allocation should minimize the number of holes (chucks of unusable memory) in the heap memory.
	 * The previously freed memory blocks should be reused.
	 * If no appropriate free block is available then the increase the heap  size using 'mem_sbrk(size)'.
	 * Try to keep the heap size as small as possible.
	 */

	// Invalid request size
	if(size <= 0){
		return NULL;
	}

	// size alligned to 8 bytes
	// size = ((size + ALIGNMENT - 1)/ALIGNMENT)*ALIGNMENT;
	size = ALIGN(size);
	size_t sizeRequired = size + sizeofMemoryMetaData;

	// iter			: points to first element in free list
	// iterBestFit	: initially points to NULL
	//                after iterating the whole free list, it
	//                will point to the best fit free block
	struct MemoryMetaData *iter = freeList.next, *iterBestFit = NULL;
	while(iter != NULL) {
		if(iterBestFit == NULL) {
			if (iter->sizeInBytes >= sizeRequired) {
				iterBestFit = iter;
			}
		} else {
			if (iter->sizeInBytes >= sizeRequired && iter->sizeInBytes < iterBestFit->sizeInBytes) {
				iterBestFit = iter;
			}
		}
		iter = iter->next;
	}
	
	void *result = NULL;
	if (iterBestFit == NULL) {
		// all free blocks are smaller than the
		// required size, so we use mem_sbrk

		// mem_sbrk() is wrapper function for the sbrk() system call. 
		// Please use mem_sbrk() instead of sbrk() otherwise the evaluation
		// results may give wrong results

		result = mem_sbrk(sizeRequired);
		// TODO: check use of this
		init_mem_sbrk_break = result + sizeRequired;
		if(((intptr_t) result) == (-1)) {
			fprintf(stderr, "ERROR: mm_malloc ---> mem_sbrk(...) failled\n");
			fflush(stderr);
		}
	} else {
		if(iterBestFit->sizeInBytes < sizeRequired + sizeofMemoryMetaData + ALIGNMENT) {
			// the size of the free block which remains after allocating
			// the requested size is too small, then give away the full
			// space to this request
			result = (void *) iterBestFit;

			// adjust free list pointers for prev and next node of iterBestFit
			iterBestFit->prev->next = iterBestFit->next;
            if(iterBestFit->next != NULL)  // handle case if iterBestFit is the last node in the free list
                iterBestFit->next->prev = iterBestFit->prev;
		} else {
		    // give space from the end of the block
		    // TODO: test the performance if space is given from the start of the free block
			iterBestFit->sizeInBytes -= sizeRequired;
			result = ((void *) iterBestFit) + iterBestFit->sizeInBytes;
		}
	}

    struct MemoryMetaData *resultPtr = (struct MemoryMetaData *) result;
	resultPtr->prev = NULL;
	resultPtr->next = NULL;
	resultPtr->isFree = 0;
	resultPtr->sizeInBytes = sizeRequired;

	return (result + sizeofMemoryMetaData);
}


void mm_free(void *ptr)
{
	/* 
	 * Searches the previously allocated node for memory block with base address ptr.
	 * 
	 * It should also perform coalesceing on both ends i.e. if the consecutive memory blocks are 
	 * free(not allocated) then they should be combined into a single block.
	 * 
	 * It should also keep track of all the free memory blocks.
	 * If the freed block is at the end of the heap then you can also decrease the heap size 
	 * using 'mem_sbrk(-size)'.
	 */
	if(ptr == NULL) return;
	
	struct MemoryMetaData *ptrMetaData = (struct MemoryMetaData *) (ptr - sizeofMemoryMetaData);
	struct MemoryMetaData *adjFreeNextTest = (struct MemoryMetaData *) (ptr - sizeofMemoryMetaData + ptrMetaData->sizeInBytes);
    int adjFreeNextIsValid = (((void *) adjFreeNextTest) < init_mem_sbrk_break);

    ptrMetaData->isFree = 1;

	if(adjFreeNextIsValid && adjFreeNextTest->isFree) {
		// The block just after the block pointed by ptr is free
		// So, merge both of them and also see if the block just
		// before 'ptr' is also free or not.
		// TODO: DONE: handle case where adjFreeNextTest is outside limit
		// TODO: check the correctness of this implementation

		// - The second test "adjFreeNextTest->prev->isFree" tell us whether the node IS the "freeList" or NOT ?
		// - The third test verifies if the node to the left of "adjFreeNextTest" in the freeList is actually
		//   adjacent to the block at "ptrMetaData" or NOT
        if(adjFreeNextTest->prev != NULL
                && adjFreeNextTest->prev->isFree
                && ((void *)(adjFreeNextTest->prev)) + adjFreeNextTest->prev->sizeInBytes == ((void *) ptrMetaData)) {
            // Merge 3 blocks: prev, curr, next
            adjFreeNextTest->prev->sizeInBytes += ptrMetaData->sizeInBytes + adjFreeNextTest->sizeInBytes;
            adjFreeNextTest->prev->next = adjFreeNextTest->next;
            if(adjFreeNextTest->next != NULL)
                adjFreeNextTest->next->prev = adjFreeNextTest->prev;
        } else {
            // Merge 2 blocks:       curr, next
            ptrMetaData->sizeInBytes += adjFreeNextTest->sizeInBytes;
            ptrMetaData->next = adjFreeNextTest->next;
            ptrMetaData->prev = adjFreeNextTest->prev;
            ptrMetaData->prev->next = ptrMetaData;  // this is very important
            if(adjFreeNextTest->next != NULL)
                adjFreeNextTest->next->prev = ptrMetaData;
        }
	} else {
		// search through the free list and insert it
		struct MemoryMetaData *iter = freeList.next;
        if (freeList.next == NULL) {
            // freeList is empty
            freeList.next = ptrMetaData;
            ptrMetaData->prev = &freeList;
            ptrMetaData->next = NULL;
        }else if(ptrMetaData < iter) {
            // ptrMetaData is to be inserted at the start of the free list
            ptrMetaData->prev = &freeList;
            ptrMetaData->next = freeList.next;
            freeList.next = ptrMetaData;
            ptrMetaData->next->prev = ptrMetaData;
        } else if (((void *)iter) + iter->sizeInBytes == ((void *)ptrMetaData)) {
			// Handle case where the block adjacent to the left is also free
			// ptrMetaData is to be combined with the first element of the free list
			// i.e. Merge 2 blocks: prev, curr
			iter->sizeInBytes += ptrMetaData->sizeInBytes;
		} else {
			while(iter->next != NULL && iter->next < ptrMetaData) {
				iter = iter->next;
			}
			if (((void *)iter) + iter->sizeInBytes == ((void *)ptrMetaData)) {
				// Handle case where the block adjacent to the left is also free
				// i.e. Merge 2 blocks: prev, curr
				iter->sizeInBytes += ptrMetaData->sizeInBytes;
			} else {
				// insert ptrMetaData in between the free list
				ptrMetaData->prev = iter;
				ptrMetaData->next = iter->next;
				iter->next = ptrMetaData;
			}
		}
	}
}

/*
 * mm_realloc - Implemented simply in terms of mm_malloc and mm_free
 */

#define min(num1, num2) ((num1 < num2) ? num1 : num2)

void *mm_realloc(void *ptr, size_t size) {
	// memory was NOT previously allocated - just mm_malloc(...)
	if(ptr == NULL) {
		// mm_malloc internally handle the case where size == 0
		return mm_malloc(size);
	}
	
	// new size is zero - just use mm_free(...)
	if(size == 0) {
		mm_free(ptr);
		return NULL;
	}

	// TODO: check the use
	// size = ((size+7)/8)*8; //8-byte alignement	
	// size = ALIGN(size);

	void *newPtr = NULL;
	newPtr = mm_malloc(size);

	/*
	 * This function should also copy the content of the previous memory block into
	 * the new block. You can use 'memcpy()' for this purpose.
	 *
	 * The data structures corresponding to free memory blocks and allocated memory
	 * blocks should also be updated.
	 */

	u_int32_t oldAllocationSize = ((struct MemoryMetaData *) (ptr - sizeofMemoryMetaData))->sizeInBytes - sizeofMemoryMetaData;
	memcpy(newPtr, ptr, min(oldAllocationSize, size));
    mm_free(ptr);

	return newPtr;
}

#undef min



/*

make
OIFS="${IFS}"
IFS=" "
for i in $(echo "short1-bal.rep short2-bal.rep short3-bal.rep binary-bal.rep cp-decl-bal.rep random-bal.rep realloc-bal.rep");
do
echo "----------------- Working on ${i} -----------------"
./mdriver1 -V -f "traces/${i}"
done
IFS="${OIFS}"

 */








