# C++17 URL Parser w/ string_view

This header file and source file are designed to be just copied directly into your C++17 project.

Pull requests and issues welcome!

### Running Tests

```
cmake .
make && ./url_test
```


### Tested On

```
Ubuntu 18.04.3 LTS
gcc version 7.5.0
x86_64-linux-gnu
```


### Profiling

```
cmake -DCMAKE_CXX_FLAGS=-pg -DCMAKE_EXE_LINKER_FLAGS=-pg -DCMAKE_SHARED_LINKER_FLAGS=-pg .
make
time ./url_profile
gprof url_profile gmon.out > outfile.txt
```