# Characters Drivers

## Workflow: 
1. Allocate a Device Number
    + [Link: Formatting device numbers](https://github.com/torvalds/linux/blob/master/include/linux/kdev_t.h)
    + Buffer should be atleast 20 bytes long if you are using: `print_dev_t`
    or `alloc_chrdev_region`

2. Create Device File
    + `sudo mknod /dev/my_driver c Major Minor`
    + Change the ownership as well for writing to the file
        `chown py /dev/my_device`
    + Check by `ls -l` on device file.


3. Set up file operations
    + https://elixir.bootlin.com/linux/latest/source/include/linux/fs.h#L1821
    + https://elixir.bootlin.com/linux/latest/source/drivers/char/adi.c#L206

4. Allocate, initialize and add cdev to system.
    + https://elixir.bootlin.com/linux/latest/source/fs/char_dev.c#L236
    + https://elixir.bootlin.com/linux/latest/source/fs/char_dev.c#L648
    + If you forget to add cdev to the system, this happens:
        ```bash
        pi@raspberrypi:~ $ cat /dev/my_driver
        cat: /dev/my_driver: No such device or address
        ```
5. Testing the driver
    + Reading the device file using `cat`:
        `cat /dev/my_driver`
    + Else you can use python shell as well: `python3`
        + Open python shell
            `$ python3`
        + Open the file and read:
            ```python
            f=open('/dev/my_driver', 'r')
            f.read(1) # Read one byte from the file
            f.read() # To read the entire contents
            f.close()
            ```
    + For writing using bash:`echo "Hello" > /dev/my_driver` make sure you have
    appropriate ownership for the file.
    + With python shell:
        ```python
        f.open('/dev/my_driver','w')
        f.write('Hello')
        f.close() # Data would be flushed when the file is closed.
        ```