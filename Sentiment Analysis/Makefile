all: debug run

checker:
	@if [ -d ./build/ ]; then echo "File Present" ; else mkdir ./build/ && cd ./build/; fi

configure: checker 
	@cd ./build/ && cmake --preset 'linux-debug' .. 
	@ln -s ./build/linux-debug/compile_commands.json  ./

debug:
	@cd ./build/linux-debug/ && cmake --build .
	@cp ./build/linux-debug/sentiment_model.cpython-313-x86_64-linux-gnu.so ./

run: debug
	@uv run ./main.py

clean:
	@rm -rf ./build/ ./.cache && rm ./compile_commands.json 

CPM_upgrade:
	@rm ./cmake/CPM.cmake
	@wget -O cmake/CPM.cmake https://github.com/cpm-cmake/CPM.cmake/releases/latest/download/get_cpm.cmake

shell:
	@./build/linux-debug/sqlite3shell ./build/linux-debug/akash.db

code_coverage: 
	@echo -e "\nCode Coverage.\n"
	@~/Python/myenv/bin/gcovr
	@cat ./build/coverage.txt
