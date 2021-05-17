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
root@d59925879f1a:~/autonomous-unicycle/_build# ctest --output-on-failure
Test project /root/autonomous-unicycle/_build
    Start 1: test_model
1/2 Test #1: test_model .......................   Passed    0.02 sec
    Start 2: test_position_controller
2/2 Test #2: test_position_controller .........   Passed    0.01 sec

100% tests passed, 0 tests failed out of 2

Total Test time (real) =   0.03 sec
```