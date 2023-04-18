![[_08c_garbage_collector.pdf]]

# Tombstones
Helps the garbage collector
bad performance

# Key and lock
bad performance

# Garbage collection

## Reference count

### problem
circular structures, and keeping the meta-data of the count is extra memory 

### solution
mark and sweep (do a pass on the memory, remove the memory which is not referenced)

#### problem
time proportional to the length of the heap
Should then be used only when free memory is low

### copy and compact & copy

## Stop and copy
make the memory contigous, copying such that it will become contiguous

## Cheneys algorithm

# recap
user is able to allocate memory, and then the language itself will garbage collect.
