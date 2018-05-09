all: docs

docs:
	rm *.png *.css *.html *.md5 *.map *.js *.txt search -rf && \
	cd ../.. && \
	doxygen ./Docs/Doxyfile-build

