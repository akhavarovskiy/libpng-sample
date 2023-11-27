# How to add LIBPNG into CMAKE

```c
find_package(PNG REQUIRED)
include_directories(${PNG_INCLUDE_DIR})
link_libraries(${MY_EXEC} ${PNG_LIBRARY})
```