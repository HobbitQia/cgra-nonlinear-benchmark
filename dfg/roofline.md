
* DFG-Level
    
    |Function|Computation Nodes|Memory Nodes|Compute/Memory|
    |:-|-|-|-|
    |CELU|18|2|9.0|
    |ELU|16|2|8.0|
    |GELU|26|2|13.0|
    |GLU|15|2|7.5|
    |Hardswish|15|2|7.5|
    |LeakyRelu|9|2|4.5|
    |LogSigmoid|19|2|9.5|
    |SELU|18|2|9.0|
    |Softplus|20|2|10.0|
    |Softsign|11|2|5.5|
    |Tanh|14|2|7.0|
    |Tanhshrink|15|2|7.5|
    |Softmax|8/13/8|1/2/2|8.0/6.5/4.0|
    |LayerNorm|10/12|1/2|10.0/6.0|
    |RMSNorm|8/10|1/2|8.0/5.0|
    |RoPE|23|4|5.75|

* Pytorch-level (suppose fp32)

    |Function|Computations|Memory Bytes|Compute/Memory(flops/bytes)|
    |:-|-|-|-|
    |CELU|7|8|0.625|
    |ELU|3|8|0.375|
    |GELU|13|8|1.625|
    |GLU|4|12|0.333|
    |Hardswish|3|8|0.375|
    |LeakyRelu|1|8|0.125|
    |LogSigmoid|21|8|2.625|
    |SELU|7|8|0.875|
    |Softplus|5|8|0.625|
    |Softsign|3|8|0.375|
    |Tanh|4|8|0.500|
    |Tanhshrink|6|8|0.750|
    |Softmax|1/3/1|4/8/8|0.250/0.375/0.125|
    |LayerNorm|3/4|4/8|0.750/0.500|
    |RMSNorm|2/2|4/8|0.500/0.250|
    |RoPE|6|16|0.375|
