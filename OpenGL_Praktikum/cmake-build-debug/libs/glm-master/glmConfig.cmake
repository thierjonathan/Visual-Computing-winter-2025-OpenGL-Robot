set(GLM_VERSION "0.9.9")
set(GLM_INCLUDE_DIRS "/cygdrive/c/Users/ryanz/OneDrive/Desktop/infor hda/Semester 4/Visual Computing/VC_OpenGL_Praktikum_Framework (1)/OpenGL_Praktikum/libs/glm-master")

if (NOT CMAKE_VERSION VERSION_LESS "3.0")
    include("${CMAKE_CURRENT_LIST_DIR}/glmTargets.cmake")
endif()
