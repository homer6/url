# C++17 URL Parser

This header file and source file are designed to be just copied directly into your C++17 project.

Pull requests and issues welcome!

v0.2.0 uses string_view throughout. However, I reverted it back to strings in v0.3.0 because the
performance was only 25% faster with string_view, but it made it harder (and less safe) to work with.

	- 11.9s for 10 million parsed URLs with string
	- 8.8s for 10 million parsed URLs with string_view

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