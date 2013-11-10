BUILD = build/

all: $(BUILD)
	gmake --directory=build/

$(BUILD):
	./configure

clean:
	rm -rf $(BUILD)

.PHONY: all clean
