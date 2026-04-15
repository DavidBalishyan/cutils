BINDIR  = bin
SRCDIR  = .

SRCS    = cat.c echo.c ps.c
BINS    = $(BINDIR)/ccat $(BINDIR)/cecho $(BINDIR)/cps

.PHONY: all clean install uninstall

all: $(BINDIR) $(BINS)

$(BINDIR):
	mkdir -p $(BINDIR)

$(BINDIR)/c%: $(SRCDIR)/%.c clibx.h
	$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS)

clean:
	rm -rf $(BINDIR)

PREFIX     ?= $(HOME)/.local
INSTALLDIR  = $(PREFIX)/bin

install: all
	install -d $(INSTALLDIR)
	install -m 755 $(BINS) $(INSTALLDIR)
	@echo "Installed to $(INSTALLDIR)"
	@echo "Make sure $(INSTALLDIR) is in your PATH."

uninstall:
	@for bin in $(BINS:$(BINDIR)/%=%); do \
		rm -fv $(INSTALLDIR)/$$bin; \
	done

# Quick smoke-tests
test: all
	@echo "--- ccat ---"
	@echo "hello from ccat" > /tmp/clibx_test.txt
	@$(BINDIR)/ccat /tmp/clibx_test.txt
	@rm /tmp/clibx_test.txt

	@echo "--- cecho ---"
	@$(BINDIR)/cecho hello world

	@echo "--- cps ---"
	@$(BINDIR)/cps | head -5

	@echo "All tests passed."
