BUILD = build/
ARCHIVE = vallee_a-42sh
EXEC = 42sh

all: $(BUILD)
	gmake --directory=build
	mv $(BUILD)$(EXEC) $(EXEC)

$(BUILD):
	echo 'Please use ./configure before gmake'
	./configure #find a way no to execute all: if $(BUILD) is not present

clean:
	$(RM) -r $(BUILD)
	$(RM) $(EXEC)
distclean:
	$(RM) -r $(BUILD)
	$(RM) $(EXEC)
# is using -r after $(RM) correct?

doc:
	#TO BE DONE

check:
	#TO BE DONE

export:
	git archive HEAD --prefix=$(ARCHIVE)/ | bzip2 > $(ARCHIVE).tar.bz2

.PHONY: all clean distclean doc check export
