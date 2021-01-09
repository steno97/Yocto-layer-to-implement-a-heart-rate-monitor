# ***Yocto layer to implement a heart rate monitor***

In the following sentences I explain how to integrate my application in a Yocto-based distribution.

After the clone operation is finished, we have to do these operations:

in the poky directory, we prepare the build environment
```
source oe-init-build-env build_qemuarm
```

we can now add the layer to the image configuration
```
bitbake-layers add-layer ../app /
```

after that we have to open the file "local.conf" (conf/local.conf) and add the following lines:
```
IMAGE_INSTALL_append = " mymod"
KERNEL_MODULE_AUTOLOAD += "mymod"
IMAGE_INSTALL_append = " heartbeat"
```

We can now build the new image by issuing the command:
```
bitbake core-image-minimal
```


after running to run the application we have to execute on the qemuarm machine the following comands:
```
root
heartbeat
```