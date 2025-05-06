#ifndef S2_OBJC_SELECTOR
#define S2_OBJC_SELECTOR(...)
#endif

// general selectors

S2_OBJC_SELECTOR(alloc, "alloc")
S2_OBJC_SELECTOR(init, "init")

// device

S2_OBJC_SELECTOR(newLibraryWithData_error_, "newLibraryWithData:error:")
S2_OBJC_SELECTOR(newRenderPipelineStateWithDescriptor_error_, "newRenderPipelineStateWithDescriptor:error:")
S2_OBJC_SELECTOR(newCommandQueue, "newCommandQueue")

// library

S2_OBJC_SELECTOR(newFunctionWithName_, "newFunctionWithName:")

// function

S2_OBJC_SELECTOR(name, "name")
