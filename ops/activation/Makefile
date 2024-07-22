MAPPER_SRC ?= $(CURDIR)/../../CGRA-Mapper
MAPPER_BUILD_DIR ?= $(MAPPER_SRC)/build
PASS_DIR ?= $(MAPPER_BUILD_DIR)/src
BUILD_DIR ?= $(CURDIR)/build

KERNEL := kernel

$(target): 
	mkdir -p build
	clang-12 -emit-llvm -fno-unroll-loops -O3 -o $(BUILD_DIR)/$(target).bc -c $(target).cpp
	opt --loop-unroll --unroll-count=1 $(BUILD_DIR)/$(target).bc -o $(BUILD_DIR)/$(target).bc
	opt -load $(PASS_DIR)/libmapperPass.so -mapperPass $(BUILD_DIR)/$(target).bc
	# llvm-dis $(BUILD_DIR)/$(target).bc -o $(BUILD_DIR)/$(target).ll
	mv *.dot $(BUILD_DIR)	
	dot -Tpng $(BUILD_DIR)/*.dot -o $(BUILD_DIR)/$(target).png
	mv config.json $(BUILD_DIR)/$(target)_config.json
	mv dfg.json $(BUILD_DIR)/$(target)_dfg.json

clean:
	rm -rf $(BUILD_DIR)/*.dot
	rm -rf $(BUILD_DIR)/*.ll
	rm -rf $(BUILD_DIR)/*.bc
	rm -rf $(BUILD_DIR)/*.json

move:
	mv $(BUILD_DIR)/*.png ../../dfg/fused/activation/
