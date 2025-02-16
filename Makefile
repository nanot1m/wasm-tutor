all: main.wasm

main.wasm: main.c
	clang --target=wasm32 -O3 \
		-Wl,--no-entry -Wl,--export=on_render \
		-Wl,--export=setup_frame_arena \
		-Wl,--import-memory \
		-Wl,--export=__heap_base \
		--std=c99 \
		-Wl,--allow-undefined \
		-nostdlib \
		-o main.wasm main.c
	@echo "main.wasm size:"
	@stat -f%z main.wasm | awk '{printf "%.2f KB\n", $$1/1024}'

clean:
	rm -f main.wasm