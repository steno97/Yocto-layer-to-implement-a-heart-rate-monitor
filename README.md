# ***Yocto layer to implement a heart rate monitor***

In the following sentences I explain how to integrate my application in a Yocto-based distribution.

After the clone operation is finished, we have to do these operations:

in the poky directory, we prepare the build environment
```
source oe-init-build-env build_qemuarm
```

we can now add the layer to the image configuration
```
bitbake-layers add-layer ../layer_name /
```

We can now build the new image by issuing the command:
```
bitbake core-image-minimal
```
