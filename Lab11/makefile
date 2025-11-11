# Program name
PROGRAM = Lab11.cpp
# Executable name
TARGET = Lab11

# Default rule
all: run

# Rule to build the executable
$(TARGET): $(PROGRAM)
# 	@echo
# 	@echo Compiling...
	@g++ -std=c++11 $(PROGRAM) -o $(TARGET)
# 	@echo
# 	@echo '$(PROGRAM)' Successfully Compiled

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
# 	@echo Successfully Cleaned
# 	@echo
