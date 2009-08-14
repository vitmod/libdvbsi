SUBDIRS = debian include qa src

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = libdvbsi++.pc

EXTRA_DIST = autogen.sh genmakefileam

if HAVE_GNUPG
if HAVE_MD5SUM
DIST_HASHES = $(addsuffix .md5,$(DIST_ARCHIVES))
DIST_SIGNATURES = $(addsuffix .asc,$(DIST_ARCHIVES))

$(DIST_HASHES): $(DIST_ARCHIVES)
	@list='$(DIST_ARCHIVES)'; for i in $$list; do md5sum $$i > $$i.md5; done

$(DIST_SIGNATURES): $(DIST_ARCHIVES)
	@list='$(DIST_ARCHIVES)'; for i in $$list; do gpg --armor --detach-sign $$i; done

release: $(DIST_ARCHIVES) $(DIST_HASHES) $(DIST_SIGNATURES)
	@if [ ! -z "$(LIBDVBSI_RELEASE_PATH)" ]; then scp $^ $(LIBDVBSI_RELEASE_PATH); fi
endif
endif

if HAVE_GIT
dist-hook:
	@if test -d "$(top_srcdir)/.git"; then \
		( $(top_srcdir)/missing --run git --git-dir=$(top_srcdir)/.git log --shortstat && \
		  cat $(top_srcdir)/ChangeLog ) > $(distdir)/ChangeLog; \
	fi
endif

