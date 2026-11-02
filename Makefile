.PHONY: build verify verify-all test serve

build: notebook.pdf

verify:
	oj-verify run

verify-all:
	python3 test/verify_all.py

test:
	oj-verify run $(wildcard test/*.unit.test.cpp test/*/*.unit.test.cpp)

URL = "http://127.0.0.1:4000"

serve: build verify
	cp notebook.pdf .verify-helper/docs/static/
	cp build/notebook.html .verify-helper/docs/static/
	cp build/*.css .verify-helper/docs/static/
	oj-verify docs
	cd .verify-helper/markdown; \
	bundle install; \
	( sleep 5.5; \
	  ( command -v open && open $(URL) ) || \
	  ( command -v start && start $(URL) ) || \
	  xdg-open $(URL) ) & \
	bundle exec jekyll serve --incremental

notebook.pdf: build/base.css build/notebook.css build/notebook.html
	vivliostyle build build/notebook.html -o notebook.pdf

build/notebook.html: build/build.js build/hash.sh build/line-hash.js $(wildcard src/*/* src/*/*/*) .clang-format
	clang-format -i $(wildcard src/*/*.hpp src/*/*/*.hpp)
	node build/build.js

build/notebook.css: build/build.js
	node build/build.js
