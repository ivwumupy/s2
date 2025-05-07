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

S2_OBJC_SELECTOR(setPixelFormat_, "setPixelFormat:")

S2_OBJC_SELECTOR(objectAtIndexedSubscript_, "objectAtIndexedSubscript:")
S2_OBJC_SELECTOR(setObject_atIndexedSubscript_, "setObject:atIndexedSubscript:")

S2_OBJC_SELECTOR(format, "format")
S2_OBJC_SELECTOR(setFormat_, "setFormat:")
S2_OBJC_SELECTOR(offset, "offset")
S2_OBJC_SELECTOR(setOffset_, "setOffset:")
S2_OBJC_SELECTOR(bufferIndex, "bufferIndex")
S2_OBJC_SELECTOR(setBufferIndex_, "setBufferIndex:")
