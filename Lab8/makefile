# Program name
PROGRAM1 = Task1.c
PROGRAM2 = Task2.c
# Executable name
TARGET1 = Task1
TARGET2 = Task2

# Default rule
all: $(TARGET1) $(TARGET2)

# Rule to build the executable
$(TARGET1): $(PROGRAM1)
	@echo
	@echo Compiling...
	@gcc -std=c11 $(PROGRAM1) -o $(TARGET1)
	@echo
	@echo '$(PROGRAM1)' Successfully Compiled
	@echo

# Rule to build the executable
$(TARGET2): $(PROGRAM2)
	@echo
	@echo Compiling...
	@gcc -std=c11 $(PROGRAM2) -o $(TARGET2)
	@echo
	@echo '$(PROGRAM2)' Successfully Compiled
	@echo

# Clean rule
clean:
	@echo
	@echo Cleaning...
	@rm -f $(TARGET1) $(TARGET2)
	@echo
	@echo Successfully Cleaned
	@echo
