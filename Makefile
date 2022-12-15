.PHONY: clean

OUT_DIR = build

SRC = \
	test/main.c \
	src/r2k_test.c \
	src/test_assert.c

OBJ = $(patsubst %.c,$(OUT_DIR)/%.o,$(SRC))

main: $(OBJ)
	gcc $^ -Iinclude -Wall -Werror -o $(OUT_DIR)/$@

$(OUT_DIR)/%.o: %.c
	@mkdir -p $(@D)
	gcc -c $^ --std=c11 -Iinclude -Wall -Werror -o $@

clean:
	@rm -rf $(OUT_DIR)
