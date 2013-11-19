BUILD = build/
ARCHIVE = vallee_a-42sh
EXEC = 42sh

all: $(BUILD)
	make -C $(BUILD)
	mv $(BUILD)$(EXEC) $(EXEC)

$(BUILD):
	@echo 'Please use ./configure before gmake'
	@./configure #find a way no to execute all: if $(BUILD) is not present


clean:
	make clean -C $(BUILD)
	$(RM) $(EXEC)
	$(RM) tree.dot
	$(RM) tree.png
distclean:
	$(RM) -r $(BUILD)
	$(RM) $(EXEC)
	@$(RM) tree.dot
	@$(RM) tree.png

# is using -r after $(RM) correct?

doc:
	doxygen doc/Doxyfile

check:
	python tests/test.py

export:
	git archive HEAD --prefix=$(ARCHIVE)/ | bzip2 > $(ARCHIVE).tar.bz2

.PHONY: all clean distclean doc check export
