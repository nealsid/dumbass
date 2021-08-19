CXX_STANDARD = -std=c++2a
CPPFLAGS = -fmodule-map-file=/Library/Developer/CommandLineTools/usr/include/c++/v1/module.modulemap -fimplicit-modules -fprebuilt-module-path=.
MODULE_FLAGS = -Xclang -emit-module-interface

.DEFAULT_GOAL := main

tokenizer.pcm: parser.cc
	$(CC) -c -o tokenizer.pcm tokenizer.cc $(CXX_STANDARD) $(CPPFLAGS) $(MODULE_FLAGS)

parser.pcm: parser.cc tokenizer.pcm
	$(CC) -c -o parser.pcm parser.cc $(CXX_STANDARD) $(CPPFLAGS) $(MODULE_FLAGS)

main: parser.pcm tokenizer.pcm main.cc
	clang++ -o main main.cc $(CXX_STANDARD) parser.pcm tokenizer.pcm $(CPPFLAGS)

clean:
	rm main parser.pcm tokenizer.pcm
