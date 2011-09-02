
CXXFLAGS = 
LDFLAGS =
LIBS = $(libMPOST)

libMPOST = ../MPOST_Linux/Debug/libMPOST_Linux.a

# All Target
all: libpympost.so

$(libMPOST): ../MPOST_Linux/*.h ../MPOST_Linux/*.cpp
	make -C ../MPOST_Linux/Debug clean all

# Tool invocations
libpympost.so: main.o $(LIBS)
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

test: test.o main.o
	g++ -o test test.o -lpthread main.o $(LIBS)

testso: test.o libpympost.so
	g++ -o testso test.o -lpthread -L. -lpympost

# Other Targets
clean:
	-$(RM) main.o libpympost.so libpympost.a test testso test.o
	-@echo ' '

TAGS:
	etags *.cpp ../MPOST_Linux/*.h ../MPOST_Linux/*.cpp

.PHONY: all clean
