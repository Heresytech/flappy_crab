cmake_minimum_required(VERSION 3.29.3)

#имя проекта
project(flappy_crab)

#создание бибилиотеки GLAD
add_library(GLAD)
add_library(GLFW3 INTERFACE) #создание цели библиотеки GLFW3 (interface, т.к в библиотеке нет файлов  .c)

#описание исходников GLAD
target_sources(GLAD
  PUBLIC
    ./dependencies/glad/src/glad.c #файл .c

  PUBLIC
    FILE_SET myHeaders #название заголовков(чтобы применять в других целях)
    TYPE HEADERS
    BASE_DIRS #папка, в которой лежат заголовки
      ./dependencies/glad/include
    FILES
      ./dependencies/glad/include/glad/glad.h
)


target_sources(GLFW3
  PUBLIC
    FILE_SET hdrs
    TYPE HEADERS
    BASE_DIRS
      ./dependencies/GLFW/include
    FILES
      ./dependencies/GLFW/include/GLFW/glfw3.h
      ./dependencies/GLFW/include/GLFW/glfw3native.h
)

#создание исполняемого файла с указанием исходника main.cpp
add_executable(flappy_crab_app ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp) 

#прописываем путь для линкующихся библиотек отдельным флагом
target_link_options(flappy_crab_app PUBLIC  -L${CMAKE_CURRENT_SOURCE_DIR}/dependencies/GLFW/lib-mingw-w64/  )
#линкуем файл приложения с библиотеками
target_link_libraries(flappy_crab_app PRIVATE GLFW3 GLAD opengl32 glfw3dll)





