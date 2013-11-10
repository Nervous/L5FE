BUILD = build/

all: $(BUILD)
	gmake --directory=build/

$(BUILD):
	./configure

clean:
	$(RM) -r $(BUILD)
# is using -r after $(RM) correct?

.PHONY: all clean
