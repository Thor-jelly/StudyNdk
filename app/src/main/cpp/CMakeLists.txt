# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.
#cmake最低版本要求
cmake_minimum_required(VERSION 3.4.1)

# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.
#添加库
add_library( # Sets the name of the library.
        # 库名
        native-lib

        # Sets the library as a shared library.
        # 类型：
        # SHARED 是指动态库，对应的是.so文件
        # STATIC 是指静态库，对应的是.a文件
        # 其他类型:略
        SHARED

        # Provides a relative path to your source file(s).
        # native类路径
        native-lib.cpp md5.cpp)

# Searches for a specified prebuilt library and stores the path as a
# variable. Because CMake includes system libraries in the search path by
# default, you only need to specify the name of the public NDK library
# you want to add. CMake verifies that the library exists before
# completing its build.
# 查找依赖库
find_library( # Sets the name of the path variable.
        # 依赖库别名
        log-lib

        # Specifies the name of the NDK library that
        # you want CMake to locate.
        # 希望加到本地的NDK库名称，log指NDK的日志库
        log)

# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in this
# build script, prebuilt third-party libraries, or system libraries.
# 链接库，建立关系（ 此处就是指把log-lib 链接给 native-lib使用 ）
target_link_libraries( # Specifies the target library.
        # 目标库名称（native-lib 是咱们要生成的so库）
        native-lib

        # Links the target library to the log library
        # included in the NDK.
        # 要链接的库（log-lib 是上面查找的log库）
        ${log-lib})