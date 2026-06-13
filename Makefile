BINDIR      = bin
TARGET_PREFIX ?=
CFLAGS      += -Isrc

# Source directories following GNU coreutils categorization
vpath %.c src/fileutils:src/textutils:src/shellutils

# fileutils
FILEUTILS   := cat cp ls mv
# textutils
TEXTUTILS   := head sort tail wc
# shellutils
SHELLUTILS  := echo ps
UTILS       := $(FILEUTILS) $(TEXTUTILS) $(SHELLUTILS)
BINS        := $(addprefix $(BINDIR)/$(TARGET_PREFIX),$(UTILS))

.PHONY: all clean install uninstall

all: $(BINDIR) $(BINS)

$(BINDIR):
	mkdir -p $(BINDIR)

$(BINDIR)/$(TARGET_PREFIX)%: %.c src/clibx.h
	$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS)

clean:
	rm -rf $(BINDIR)

INSTALL_PREFIX ?= $(HOME)/.local
INSTALLDIR      = $(INSTALL_PREFIX)/bin

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
	@echo "--- $(TARGET_PREFIX)cat ---"
	@echo "hello from $(TARGET_PREFIX)cat" > /tmp/clibx_test.txt
	@$(BINDIR)/$(TARGET_PREFIX)cat /tmp/clibx_test.txt
	@rm /tmp/clibx_test.txt

	@echo "--- $(TARGET_PREFIX)echo ---"
	@$(BINDIR)/$(TARGET_PREFIX)echo hello world

	@echo "--- $(TARGET_PREFIX)ps ---"
	@$(BINDIR)/$(TARGET_PREFIX)ps | head -5

	@echo "--- $(TARGET_PREFIX)ls ---"
	@$(BINDIR)/$(TARGET_PREFIX)ls . | head -5

	@echo "--- $(TARGET_PREFIX)wc ---"
	@echo -e "hello world\nfoo bar" > /tmp/clibx_test_wc.txt
	@$(BINDIR)/$(TARGET_PREFIX)wc /tmp/clibx_test_wc.txt
	@rm /tmp/clibx_test_wc.txt

	@echo "--- $(TARGET_PREFIX)head ---"
	@printf "line1\nline2\nline3\nline4\nline5\n" > /tmp/clibx_test_head.txt
	@$(BINDIR)/$(TARGET_PREFIX)head -n 2 /tmp/clibx_test_head.txt
	@rm /tmp/clibx_test_head.txt

	@echo "--- $(TARGET_PREFIX)tail ---"
	@printf "line1\nline2\nline3\nline4\nline5\n" > /tmp/clibx_test_tail.txt
	@$(BINDIR)/$(TARGET_PREFIX)tail -n 2 /tmp/clibx_test_tail.txt
	@rm /tmp/clibx_test_tail.txt

	@echo "--- $(TARGET_PREFIX)sort ---"
	@printf "banana\napple\ncherry\n" | $(BINDIR)/$(TARGET_PREFIX)sort

	@echo "--- $(TARGET_PREFIX)cp ---"
	@echo "copy test" > /tmp/clibx_test_cp_src.txt
	@$(BINDIR)/$(TARGET_PREFIX)cp /tmp/clibx_test_cp_src.txt /tmp/clibx_test_cp_dest.txt
	@$(BINDIR)/$(TARGET_PREFIX)cat /tmp/clibx_test_cp_dest.txt
	@rm /tmp/clibx_test_cp_src.txt /tmp/clibx_test_cp_dest.txt

	@echo "--- $(TARGET_PREFIX)mv ---"
	@echo "move test" > /tmp/clibx_test_mv_src.txt
	@$(BINDIR)/$(TARGET_PREFIX)mv /tmp/clibx_test_mv_src.txt /tmp/clibx_test_mv_dest.txt
	@$(BINDIR)/$(TARGET_PREFIX)cat /tmp/clibx_test_mv_dest.txt
	@rm /tmp/clibx_test_mv_dest.txt

	@echo "All tests passed."
