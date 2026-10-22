
add_executable(inkball inkball.c)
set_module_type(inkball win32gui UNICODE)
add_importlibs(inkball user32 gdi32 msvcrt kernel32)
add_cd_file(TARGET inkball DESTINATION reactos/system32 FOR all)
