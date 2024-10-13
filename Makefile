# Top-level Makefile

# Default target
all: estimation prediction

# Compile estimation
estimation:
	@echo "Compiling estimation..."
	@$(MAKE) -C estimation

# Compile prediction
prediction:
	@echo "Compiling prediction..."
	@$(MAKE) -C prediction

# Clean both directories
clean:
	@echo "Cleaning estimation..."
	@$(MAKE) -C estimation clean
	@echo "Cleaning prediction..."
	@$(MAKE) -C prediction clean

.PHONY: all estimation prediction clean

