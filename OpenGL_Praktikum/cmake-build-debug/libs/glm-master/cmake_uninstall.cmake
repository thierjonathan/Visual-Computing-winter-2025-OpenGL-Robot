if(NOT EXISTS "/cygdrive/c/Users/ryanz/OneDrive/Desktop/infor hda/Semester 4/Visual Computing/VC_OpenGL_Praktikum_Framework (1)/OpenGL_Praktikum/cmake-build-debug/libs/glm-master/install_manifest.txt")
  message(FATAL_ERROR "Cannot find install manifest: /cygdrive/c/Users/ryanz/OneDrive/Desktop/infor hda/Semester 4/Visual Computing/VC_OpenGL_Praktikum_Framework (1)/OpenGL_Praktikum/cmake-build-debug/libs/glm-master/install_manifest.txt")
endif(NOT EXISTS "/cygdrive/c/Users/ryanz/OneDrive/Desktop/infor hda/Semester 4/Visual Computing/VC_OpenGL_Praktikum_Framework (1)/OpenGL_Praktikum/cmake-build-debug/libs/glm-master/install_manifest.txt")

if (NOT DEFINED CMAKE_INSTALL_PREFIX)
  set (CMAKE_INSTALL_PREFIX "/usr/local")
endif ()
 message(${CMAKE_INSTALL_PREFIX})

file(READ "/cygdrive/c/Users/ryanz/OneDrive/Desktop/infor hda/Semester 4/Visual Computing/VC_OpenGL_Praktikum_Framework (1)/OpenGL_Praktikum/cmake-build-debug/libs/glm-master/install_manifest.txt" files)
string(REGEX REPLACE "\n" ";" files "${files}")
foreach(file ${files})
  message(STATUS "Uninstalling $ENV{DESTDIR}${file}")
  if(IS_SYMLINK "$ENV{DESTDIR}${file}" OR EXISTS "$ENV{DESTDIR}${file}")
    exec_program(
      "/cygdrive/c/Users/ryanz/AppData/Local/JetBrains/CLion2023.2/cygwin_cmake/bin/cmake.exe" ARGS "-E remove \"$ENV{DESTDIR}${file}\""
      OUTPUT_VARIABLE rm_out
      RETURN_VALUE rm_retval
      )
    if(NOT "${rm_retval}" STREQUAL 0)
      message(FATAL_ERROR "Problem when removing $ENV{DESTDIR}${file}")
    endif(NOT "${rm_retval}" STREQUAL 0)
  else(IS_SYMLINK "$ENV{DESTDIR}${file}" OR EXISTS "$ENV{DESTDIR}${file}")
    message(STATUS "File $ENV{DESTDIR}${file} does not exist.")
  endif(IS_SYMLINK "$ENV{DESTDIR}${file}" OR EXISTS "$ENV{DESTDIR}${file}")
endforeach(file)
