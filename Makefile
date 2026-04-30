BINDIR  = bin
SRCDIR  = .

SRCS    = cat.c echo.c ps.c ls.c wc.c head.c tail.c sort.c cp.c mv.c
BINS    = $(BINDIR)/ccat $(BINDIR)/cecho $(BINDIR)/cps \
          $(BINDIR)/cls $(BINDIR)/cwc $(BINDIR)/chead $(BINDIR)/ctail \
          $(BINDIR)/csort $(BINDIR)/ccp $(BINDIR)/cmv

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

	@echo "--- cls ---"
	@$(BINDIR)/cls . | head -5

	@echo "--- cwc ---"
	@echo -e "hello world\nfoo bar" > /tmp/clibx_test_wc.txt
	@$(BINDIR)/cwc /tmp/clibx_test_wc.txt
	@rm /tmp/clibx_test_wc.txt

	@echo "--- chead ---"
	@printf "line1\nline2\nline3\nline4\nline5\n" > /tmp/clibx_test_head.txt
	@$(BINDIR)/chead -n 2 /tmp/clibx_test_head.txt
	@rm /tmp/clibx_test_head.txt

	@echo "--- ctail ---"
	@printf "line1\nline2\nline3\nline4\nline5\n" > /tmp/clibx_test_tail.txt
	@$(BINDIR)/ctail -n 2 /tmp/clibx_test_tail.txt
	@rm /tmp/clibx_test_tail.txt

	@echo "--- csort ---"
	@printf "banana\napple\ncherry\n" | $(BINDIR)/csort

	@echo "--- ccp ---"
	@echo "copy test" > /tmp/clibx_test_cp_src.txt
	@$(BINDIR)/ccp /tmp/clibx_test_cp_src.txt /tmp/clibx_test_cp_dest.txt
	@$(BINDIR)/ccat /tmp/clibx_test_cp_dest.txt
	@rm /tmp/clibx_test_cp_src.txt /tmp/clibx_test_cp_dest.txt

	@echo "--- cmv ---"
	@echo "move test" > /tmp/clibx_test_mv_src.txt
	@$(BINDIR)/cmv /tmp/clibx_test_mv_src.txt /tmp/clibx_test_mv_dest.txt
	@$(BINDIR)/ccat /tmp/clibx_test_mv_dest.txt
	@rm /tmp/clibx_test_mv_dest.txt

	@echo "All tests passed."
