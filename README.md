# CGRA-Nonlinear-Benchmark

* `CGRA-Mapper` is a mapper to map the target loops onto the CGRA. Details can be found at the [repo](https://github.com/tancheng/CGRA-Mapper).
* `dfg/`: There are dataflow graphs of nonlinear operations produced by the mapper, which can be used to analyze the patterns.
* `ops/`: There are source codes of nonlinear opearations implemented in C++. So far we provide these ops:
    * Activation functions: CELU, GELU, ELU, GLU, Hardswish, Leakyrelu, Logsigmoid, SELU, Softmax, Softplus, Softsign, Tanh, Tanhshrink.
    * Normalization functions: LayerNorm, RMSNorm.
    * Embedding: Rotary Embedding(RoPE)

If you want to reproduce graphs or run the mapper on your own, you should do this:
``` shell
git clone https://github.com/HobbitQia/cgra-nonlinear-benchmark.git --recursive
# compile CGRA-Mapper
mkdir build
cd build
cmake ..
make
# map the target operations
cd path/to/ops
cd activation # Alternatively, you can cd norm/embedding to try other classes of function
make target=<operation-name> # <operation-name> can be softmax, elu, glu and so on. Make sure you execute make clean before mapping.
# Compile information will be printed on the shell. The result .dot and .png files will in the build/ folder. 
```