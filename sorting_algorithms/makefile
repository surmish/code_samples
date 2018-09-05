# build an executable

CC          = g++
# CC        = clang++
BOOST_FLAGS = -lboost_program_options
CFLAGS      = -c
TARGET      = sort
OBJS        = main.o

all: $(TARGET)

$(TARGET):  $(OBJS)
	$(CC) $(BOOST_FLAGS) $(OBJS) -o $(TARGET)

bst_sort.hpp.gch: bst_sort.hpp
	$(CC) $(CFLAGS) bst_sort.hpp

bubble_sort.hpp.gch: bubble_sort.hpp
	$(CC) $(CFLAGS) bubble_sort.hpp

bucket_sort.hpp.gch: bucket_sort.hpp
	$(CC) $(CFLAGS) bucket_sort.hpp

heap_sort.hpp.gch: heap_sort.hpp
	$(CC) $(CFLAGS) heap_sort.hpp

insertion_sort.hpp.gch: insertion_sort.hpp
	$(CC) $(CFLAGS) insertion_sort.hpp

merge_sort.hpp.gch: merge_sort.hpp
	$(CC) $(CFLAGS) merge_sort.hpp

quick_sort.hpp.gch: quick_sort.hpp
	$(CC) $(CFLAGS) quick_sort.hpp

radix_sort.hpp.gch: radix_sort.hpp
	$(CC) $(CFLAGS) radix_sort.hpp

selection_sort.hpp.gch: selection_sort.hpp
	$(CC) $(CFLAGS) selection_sort.hpp

shell_sort.hpp.gch: shell_sort.hpp
	$(CC) $(CFLAGS) shell_sort.hpp

main.o: main.cpp bst_sort.hpp.gch bubble_sort.hpp.gch bucket_sort.hpp.gch heap_sort.hpp.gch insertion_sort.hpp.gch merge_sort.hpp.gch quick_sort.hpp.gch radix_sort.hpp.gch shell_sort.hpp.gch selection_sort.hpp.gch
	$(CC) $(CFLAGS) main.cpp -o main.o

clean: 
	rm -f sort *.o *~* *.gch
