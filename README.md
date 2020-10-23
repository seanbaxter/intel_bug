# Intel SPIR-V compiler bug

```
Extended renderer info (GLX_MESA_query_renderer):
    Vendor: Intel Open Source Technology Center (0x8086)
    Device: Mesa DRI Intel(R) UHD Graphics 620 (WHL GT2) (0x3ea0)
    Version: 20.0.8
    Accelerated: yes
    Video memory: 3072MB
    Unified memory: yes
    Preferred profile: core (0x1)
    Max core profile version: 4.6
    Max compat profile version: 3.0
    Max GLES1 profile version: 1.1
    Max GLES[23] profile version: 3.2
```

Intel driver freaks out when a single SPIR-V module has more than one buffer with different definitions bound to the same OpDecorate Binding. In this example I spirv-link two vertex shaders together into linked_bad.spv. When I try to compile a shader program, the driver reports this conflict:

```
program log: error: buffer block with binding `0' has mismatching definitions
```

linked_good.spv only has one vertex shader and the frag shader together, and that executes correctly.
