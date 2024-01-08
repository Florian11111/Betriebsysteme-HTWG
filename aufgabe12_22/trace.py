import matplotlib.pyplot as plt

# Sample valgrind trace data (replace this with actual parsing)
valgrind_trace = ["0x1000", "0x2000", "0x1000", "0x3000", "0x4000", "0x2000"]

# Transform references into virtual page numbers
virtual_page_numbers = [int(addr, 16) >> 12 for addr in valgrind_trace]

# Simulate cache with varying sizes
cache_sizes = range(1, 6)
working_set_sizes = []

for cache_size in cache_sizes:
    cache = set()
    working_set_size = 0

    for page_number in virtual_page_numbers:
        if page_number not in cache:
            cache.add(page_number)
            working_set_size += 1

            if len(cache) > cache_size:
                evicted_page = cache.pop()
                if evicted_page in cache:
                    cache.remove(evicted_page)

    working_set_sizes.append(working_set_size)

# Plot the graph
plt.plot(cache_sizes, working_set_sizes, marker='o')
plt.xlabel('Cache Size')
plt.ylabel('Working Set Size')
plt.title('Working Set Size vs Cache Size')
plt.savefig('/home/bsys/betriebsystem/homework/aufgabe12_22/ergebnis.png')
