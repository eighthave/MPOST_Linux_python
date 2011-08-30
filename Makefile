
CXXFLAGS = 
LDFLAGS =
LIBS = 

# All Target
all: libpympost.so

# Tool invocations
libpympost.so: main.o
	@echo 'Building target: $@'
	@echo 'Invoking: GCC C++ Linker'
	$(CXX) -rdynamic -shared -fPIC -o $@ main.o $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

libpympost.a: main.o
	@echo 'Building target: $@'
	@echo 'Invoking: GCC C++ Linker'
	ar -r "libpympost.a" main.o
	@echo 'Finished building target: $@'
	@echo ' '

test: libpympost.a test.c
	gcc -o test.o -c test.c
	g++ -o test test.o -lpthread main.o ../MPOST_Linux/Debug/libMPOST_Linux.a

# Other Targets
clean:
	-$(RM) main.o libpympost.so libpympost.a test test.o
	-@echo ' '

TAGS:
	etags *.cpp ../MPOST_Linux/*.h ../MPOST_Linux/*.cpp

.PHONY: all clean
