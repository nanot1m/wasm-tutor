all: main.wasm

main.wasm: main.c
	clang --target=wasm32 -O3 -nostdlib \
		-Wno-incompatible-library-redeclaration \
		-Wl,--no-entry -Wl,--export-all \
		-Wl,--import-memory \
		-o main.wasm main.c

clean:
	rm -f main.wasm