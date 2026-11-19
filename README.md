# drv-mpu60x0-gy85
This driver was made for the mpu60x0 Invensense sensor, mounted on GY85 flight-controller sensor.

In order to initialize the west versioning for the first time:
```shell
$ mkdir .west
$ touch .west/config
$ west config manifest.path .
$ west config manifest.file west.yml 
```

Then to keep the libraries updated:
```shell
$ west update
```