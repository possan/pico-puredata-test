# Running PureData on Raspberry Pi Pico

⚠️ 🐉 here be dragons 🐉 ⚠️

This is a very hacky attempt at running pd on a pico, i first tried to port regular libpd but never got it fully to work, then i switched to something based of Millers ESP32 hack and that seems to start without crashing at least.

After spending several days debugging on chip why the pico hardfaulted in code that shouldn't be able to crash, it boiled down to an alignment issue of an enum (i think)

The code is using libpd as a dependency but not really using it anymore, it also includes a couple of freertos projects as submodules that were used for testing earlier.



## Building

Clone repo and submodules, run cmake and build it.

```
git clone --recursive git@github.com:possan/pico-puredata-test.git
cd pico-puredata-test

mkdir build
cd build
cmake -DPICO=1  -DPICO_BOARD=pico  -DCMAKE_BUILD_TYPE=Debug -DPICO_SDK_PATH=../../../pico-sdk ..

make -j9

picotool load pdtest2.uf2
```

If you for some reason would like to run it locally, you can configure it without the PICO=1 flag

```
cmake -DPICO=1 -DCMAKE_BUILD_TYPE=Debug ..
```



## Changes to pure-data

* `t_atomtype` was changed from an unspecified enum to a `uint32_t` with a 4 byte alignment, using a `uint8_t` didn't work.

