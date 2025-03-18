all: balatro64.z64
.PHONY: all

SOURCE_DIR = src
BUILD_DIR = build
include $(N64_INST)/include/n64.mk

OBJS = $(BUILD_DIR)/main.o $(BUILD_DIR)/deck.o $(BUILD_DIR)/state.o $(BUILD_DIR)/poker_hand.o

balatro64.z64: N64_ROM_TITLE = "Balatro64"
balatro64.z64: N64_ROM_RTC = true

$(BUILD_DIR)/balatro64.elf: $(OBJS)

# Rule to compile .c files into .o files
$(BUILD_DIR)/%.o: $(SOURCE_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Create the build directory if it doesn't exist
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR) *.z64
.PHONY: clean

-include $(wildcard $(BUILD_DIR)/*.d)
