# Linux Device Drivers

## System Information
+ Installed linux kernel using [rpi-source](https://github.com/notro/rpi-source/wiki).
+ **Hardware:** Raspberry Pi 3B+

>If you are not able to explain some erratic behaviour, check your power supply. Your Raspberry Pi might be in an `undervoltage` state. Get a good power supply(3 amps).

+ **OS Information:**
    ```bash
    pi@raspberrypi:~/ldd $ cat /etc/os-release 
    PRETTY_NAME="Raspbian GNU/Linux 9 (stretch)"
    NAME="Raspbian GNU/Linux"
    VERSION_ID="9"
    VERSION="9 (stretch)"
    ID=raspbian
    ID_LIKE=debian
    HOME_URL="http://www.raspbian.org/"
    SUPPORT_URL="http://www.raspbian.org/RaspbianForums"
    BUG_REPORT_URL="http://www.raspbian.org/RaspbianBugs"
    ```
+ **Kernel Information**:
    ```bash
    pi@raspberrypi:~/ldd $ uname -a
    Linux raspberrypi 4.19.106-v7+ #1 SMP Sun Mar 1 11:56:22 IST 2020 armv7l GNU/Linux
    ```
    