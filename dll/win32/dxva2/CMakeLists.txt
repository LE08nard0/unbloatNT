spec2def(dxva2.dll dxva2.spec ADD_IMPORTLIB)

if(NOT REACTOS_USE_WDDM)
    # d3dumddi.h declares WDDM 2 UMD types that the Vista UMD ABI hides.
    remove_definitions(-DD3D_UMD_INTERFACE_VERSION=0x000C)
    add_definitions(-DD3D_UMD_INTERFACE_VERSION=0x6003)
endif()

add_library(dxva2 MODULE decoder.c main.c ${CMAKE_CURRENT_BINARY_DIR}/dxva2.def ${CMAKE_CURRENT_BINARY_DIR}/dxva2_stubs.c)
set_module_type(dxva2 win32dll)
target_compile_definitions(dxva2 PRIVATE __WINESRC__)
target_link_libraries(dxva2 uuid wine)
add_importlibs(dxva2 ole32 user32 gdi32 msvcrt kernel32 ntdll)
add_dependencies(dxva2 d3d_idl_headers)
add_cd_file(TARGET dxva2 DESTINATION reactos/system32 FOR all)
set_wine_module(dxva2)
