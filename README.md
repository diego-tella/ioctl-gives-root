# IOCTL GIVES ROOT!
LKM that elevates the privileges of a userland process to root via an IOCTL command

# Usage

```
make
sudo insmod ioctl-lkm.ko
gcc user_land.c -o user_land
sudo ./file.sh
```

Now every time you run the *user_land* binary you will get root!

```
./user_land
```

Fun way to keep persistence through devices.
