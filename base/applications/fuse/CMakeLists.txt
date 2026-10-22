
add_executable(fuse fuse.c)
set_module_type(fuse win32gui UNICODE)
add_importlibs(fuse shell32 user32 msvcrt kernel32)
add_cd_file(TARGET fuse DESTINATION reactos/system32 FOR all)
