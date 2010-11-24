ACLOCAL_AMFLAGS = -I m4

SUBDIRS = debian include qa src

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = libdvbsi++.pc

EXTRA_DIST = autogen.sh genmakefileam

if HAVE_GNUPG
if HAVE_MD5SUM
DIST_HASHES = $(DIST_ARCHIVES:=.md5)
DIST_SIGNATURES = $(DIST_ARCHIVES:=.asc)

$(DIST_HASHES): $(DIST_ARCHIVES)
	@list='$(DIST_ARCHIVES)'; for i in $$list; do md5sum $$i > $$i.md5; done

$(DIST_SIGNATURES): $(DIST_ARCHIVES)
	@list='$(DIST_ARCHIVES)'; for i in $$list; do gpg --armor --detach-sign $$i; done

release: $(DIST_ARCHIVES) $(DIST_HASHES) $(DIST_SIGNATURES)
	@if [ ! -z "$(LIBDVBSI_RELEASE_PATH)" ]; then scp $^ $(LIBDVBSI_RELEASE_PATH); fi
endif
endif

if HAVE_GIT
GIT_DIR = $(top_srcdir)/.git

dist-hook:
	if test -d $(GIT_DIR); then \
		$(GIT) --git-dir=$(GIT_DIR) log --shortstat > $(distdir)/ChangeLog; \
	fi
endif
