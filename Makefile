.PHONY: clean

OUT_DIR = build

SRC = \
	src/r2k_test_assert.c \
	src/r2k_test_runner.c \
	src/r2k_test_suite.c \
	src/r2k_test.c \
	test/main.c \

OBJ = $(patsubst %.c,$(OUT_DIR)/%.o,$(SRC))
DEBS = $(patsubst %.c,$(OUT_DIR)/%.d,$(SRC))

main: $(OBJ)
	gcc $^ -Iinclude -Wall -Werror -o $(OUT_DIR)/$@

$(OUT_DIR)/%.o: %.c
	@mkdir -p $(@D)
	gcc -c $< -MMD -MP --std=c99 -Iinclude -Wall -Werror -o $@

clean:
	@rm -rf $(OUT_DIR)

-include $(OBJ:.o=.d)
