# Program name
PROGRAM = main.c
# Odd function
ODD = isOdd.c
# Even function
EVEN = isEven.c
# Executable name
TARGET = Lab02.exe

# Default rule
all: run

# Rule to build the executable
$(TARGET): $(PROGRAM) 
# 	@echo
# 	@echo Compiling...
	@g++ -std=c++11 $(PROGRAM) $(ODD) $(EVEN) -o $(TARGET)

# Rule to run the program
run: $(TARGET)
# 	@echo
# 	@echo Running Program...
	./$(TARGET)
# 	@echo

# Clean rule
clean:
# 	@echo
# 	@echo Cleaning...
	@rm -f $(TARGET)
# 	@echo
