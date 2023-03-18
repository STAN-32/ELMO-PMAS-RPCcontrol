# ELMO-PMAS-RPCcontrol
This project is used for implement RPCcontrol with P-Mas controller in linux64 system.(Ubuntu 20.04 ours)

The RPC control is easy to implemented in Windows system, however, the relative support is limited in linux system.
This project can be further embedding into ROS system as you like.

A simple project is built, which can be easily extended to your own project.

# Using step

Compile the whole project via Cmake
```
cmake .
make -j4
```

Remember connect with P-Mas controller and set ip address in form of
```
192.168.1.x
```
Mask:
```
255.255.255.0
```
Gateway
```
192.168.1.1
```

# Development

Any question about connection problem can be raised by contacting me.
