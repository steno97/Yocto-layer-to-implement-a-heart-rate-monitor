# ***Yocto layer to implement a heart rate monitor***

In the following sentences I explain how to integrate my application in a Yocto-based distribution.

First of all we enter in the poky directory and we open the terminal, in the terminal we write the following
line to clone the git directory
```
git clone https://github.com/steno97/Yocto-layer-to-implement-a-heart-rate-monitor.git
```

After the clone operation is finished, we have to do these operations

in the poky directory, we prepare the build environment
```
source oe-init-build-env build_qemuarm
```

we can now add the layer to the image configuration
```
bitbake-layers add-layer ../Yocto-layer-to-implement-a-heart-rate-monitor/app/
```

after that we have to open the file "local.conf" (conf/local.conf) and add the following lines
```
IMAGE_INSTALL_append = " mymod"
KERNEL_MODULE_AUTOLOAD += "mymod"
IMAGE_INSTALL_append = " heartbeat"
```

We can now build the new image by issuing the command
```
bitbake core-image-minimal
```


now we can start our machine with the command
```
runqemu qemuarm
```

now, to run the application we have to execute on the qemuarm machine the following commands
```
root
heartbeat
```