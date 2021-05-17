# autonomous-unicycle

tbd...


## Building and then running the tests on Mac

After cloning this repo in our mac computer, we run one by one the following commands in a terminal:

```bash
$ cd autonomous-unicycle
$ cd dockerfolder
$ bash mac_build.sh
$ bash mac_run.sh
```

Then, inside the ubuntu 20.04 container we just created:

```console
root@d59925879f1a:~# ls
autonomous-unicycle
root@d59925879f1a:~# cd autonomous-unicycle/
root@d59925879f1a:~/autonomous-unicycle# ls
CMakeLists.txt  LICENSE  README.md  dockerfolder  include  src  test
root@d59925879f1a:~/autonomous-unicycle# mkdir _build
root@d59925879f1a:~/autonomous-unicycle# cd _build/
root@d59925879f1a:~/autonomous-unicycle/_build# cmake ..
-- The C compiler identification is GNU 9.3.0
root@d59925879f1a:~/autonomous-unicycle/_build# make 
root@d59925879f1a:~/autonomous-unicycle/_build# ls
CMakeCache.txt  Makefile             libunicycle_control.a
CMakeFiles      cmake_install.cmake  test
root@d59925879f1a:~/autonomous-unicycle/_build# cd test
root@d59925879f1a:~/autonomous-unicycle/_build/test# ls
CMakeFiles  Makefile  cmake_install.cmake  test_model  test_position_controller
root@d59925879f1a:~/autonomous-unicycle/_build/test# ./test_model
All tests successfully passed.
root@d59925879f1a:~/autonomous-unicycle/_build/test# ./test_position_controller
v: 0, omega: 0
x: 9.99906
y: 9.99901
theta: 0.811262
v: 0.00138113, omega: 0
9.21
All tests successfully passed.
```