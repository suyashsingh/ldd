# Hello World Lodable Kernel Module

1. Compiling the module:
`make`
Cleaning the directory: `make clean`

2. Loading the module:
`sudo insmod hello-world.ko`

3. Unloading the module:
`sudo rmmod hello-world`

4. Checking prink messages:
`dmesg`

5. Exported Parameters in `sysfs`:
`$ cat /sys/module/parameters_lkm/parameters/nos`