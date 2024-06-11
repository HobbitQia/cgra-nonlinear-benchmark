MAPPER_SRC ?= $(CURDIR)/../../CGRA-Mapper
MAPPER_BUILD_DIR ?= $(MAPPER_SRC)/build
PASS_DIR ?= $(MAPPER_BUILD_DIR)/src
BUILD_DIR ?= $(CURDIR)/build

KERNEL := _Z6kernelPfS_S_

$(target): 
	mkdir -p build
	clang-12 -emit-llvm -fno-unroll-loops -O3 -o $(BUILD_DIR)/$(target).bc -c $(target).cpp
	opt -load $(PASS_DIR)/libmapperPass.so -mapperPass $(BUILD_DIR)/$(target).bc
	mv *.dot $(BUILD_DIR)	
	dot -Tpng $(BUILD_DIR)/*.dot -o $(BUILD_DIR)/$(target).png
	mv config.json $(BUILD_DIR)/$(target)_config.json
	mv dfg.json $(BUILD_DIR)/$(target)_dfg.json

clean:
	rm -rf $(BUILD_DIR)/*.dot
