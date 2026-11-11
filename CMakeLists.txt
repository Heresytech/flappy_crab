cmake_minimum_required(VERSION 3.29.3)

#имя проекта
project(flappy_crab)

#создание бибилиотеки GLAD
add_library(GLAD)
#создание библиотеки GLFW3
add_library(GLFW3 INTERFACE) #создание цели библиотеки GLFW3 (interface, т.к в библиотеке нет файлов  .c)

add_library(ORGANISED)

#создание цели со всеми бибилиотеками, упрощающими в-действие с OPENGL
target_sources(ORGANISED
  PUBLIC
     ${CMAKE_CURRENT_SOURCE_DIR}/src/VAO.cpp
     ${CMAKE_CURRENT_SOURCE_DIR}/src/VBO.cpp
     ${CMAKE_CURRENT_SOURCE_DIR}/src/EBO.cpp
     ${CMAKE_CURRENT_SOURCE_DIR}/src/shaderClass.cpp

  PUBLIC
    FILE_SET new_Headers #название заголовков(чтобы применять в других целях)
    TYPE HEADERS
    BASE_DIRS #папка, в которой лежат заголовки
      ${CMAKE_CURRENT_SOURCE_DIR}/headers
      ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/glad/include
    FILES
      ${CMAKE_CURRENT_SOURCE_DIR}/headers/VAO.h
      ${CMAKE_CURRENT_SOURCE_DIR}/headers/VBO.h
      ${CMAKE_CURRENT_SOURCE_DIR}/headers/EBO.h
      ${CMAKE_CURRENT_SOURCE_DIR}/headers/shaderClass.h
)


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

#описание исходников GLFW3
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

#автоматическое добавление файла динамической библиотеки
#glfw3 в папку build для исполняемого файла
add_custom_command(
  TARGET flappy_crab_app
  POST_BUILD
  COMMAND ${CMAKE_COMMAND}
  ARGS -E copy  ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/GLFW/lib-mingw-w64/glfw3.dll  ${CMAKE_CURRENT_SOURCE_DIR}/build
  )

#автоматическое добавление папки с шейдерами в папку с исполняемым файлом
add_custom_command(
  TARGET flappy_crab_app
  POST_BUILD
  COMMAND ${CMAKE_COMMAND}
  ARGS -E make_directory "${CMAKE_CURRENT_SOURCE_DIR}/build/Shaders" 
  )

add_custom_command(
  TARGET flappy_crab_app
  POST_BUILD
  COMMAND ${CMAKE_COMMAND}
  ARGS -E copy_directory "${CMAKE_CURRENT_SOURCE_DIR}/Shaders"  "${CMAKE_CURRENT_SOURCE_DIR}/build/Shaders"
  )


#прописываем путь для линкующихся библиотек отдельным флагом
target_link_options(flappy_crab_app PUBLIC  -L${CMAKE_CURRENT_SOURCE_DIR}/dependencies/GLFW/lib-mingw-w64/  )
#линкуем файл приложения с библиотеками
target_link_libraries(flappy_crab_app PUBLIC ORGANISED GLFW3 GLAD opengl32 glfw3dll)





