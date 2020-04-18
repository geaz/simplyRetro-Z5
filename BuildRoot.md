The image was build with the LTS version - 2019.02.4 - of [BuildRoot](https://buildroot.org/downloads/buildroot-2019.02.4.tar.gz).

1. Download & Extract BuildRoot
2. Copy the content of the buildroot folder in the repository to the extracted buildroot LTS version
3. Add the content of the file buildroot/packages/Config.in.additions to the file packages/Config.in
4. sudo apt install libncurses5-dev
5. make simplyRetro-z5_defconfig
6. make menuconfig
7. make