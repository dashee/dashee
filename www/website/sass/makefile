SASS=sass -C
all: STYLE=--style compressed
pretty: STYLE=--style pretty
RM=rm -Rvf
MKDIR=mkdir -p

CSSDIR=css

CSS := $(addprefix $(CSSDIR)/, index.css download.css wiki.css licence.css about.css)

all: $(CSSDIR) $(CSS)

pretty: $(CSSDIR) $(CSS)

$(CSSDIR):
	mkdir css

$(CSSDIR)/index.css: index.scss
	$(SASS) $(STYLE) $^ $@

$(CSSDIR)/download.css: download.scss
	$(SASS) $(STYLE) $^ $@

$(CSSDIR)/wiki.css: wiki.scss
	$(SASS) $(STYLE) $^ $@

$(CSSDIR)/licence.css: licence.scss
	$(SASS) $(STYLE) $^ $@

$(CSSDIR)/about.css: about.scss
	$(SASS) $(STYLE) $^ $@

clean:
	$(RM) $(CSS)
	$(RM) $(CSSDIR)
