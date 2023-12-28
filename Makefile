CXX = g++-11 -std=c++20
CXXFLAGS = -Wall -g -MMD  # use -MMD to generate dependencies
SOURCES = $(wildcard *.cc)   # list of all .cc files in the current directory
OBJECTS = ${SOURCES:.cc=.o}  # .o files depend upon .cc files with same names
DEPENDS = ${OBJECTS:.o=.d}   # .d file is list of dependencies for corresponding .cc file
EXEC=raiinet

# First target in the makefile is the default target.
$(EXEC): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(EXEC) -lX11
#	@$(MAKE) clean_objects

# Rule to compile .cc to .o
%.o: %.cc 
	$(CXX) -c -o $@ $< $(CXXFLAGS)

-include ${DEPENDS}

# Rule to clean object files and dependency files
clean_objects:
	rm -f $(OBJECTS) $(DEPENDS)

# Phony target to clean everything
.PHONY: clean 
clean:
	rm -f $(OBJECTS) $(DEPENDS) $(EXEC)