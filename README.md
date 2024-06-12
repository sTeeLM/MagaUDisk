# MagaUDisk
一个使用硬件而不是软件模拟方式实现的万能启动盘，有点类似于Ventoy，不过功能强大的多了！
1. 加密：
   对存储介质加密，如果丢失了不会造成风险。
2. 模拟普通U盘：
   不需要介绍，可以插在电脑上当U盘使
3. 对U盘上的镜像模拟成移动硬盘和光驱
   将镜像复制到U盘上之后，可以对每一个镜像模拟成移动硬盘和光驱
4. 模拟网卡
   对于没有无线网卡的笔记本（例如没装驱动），可以模拟成一个无线网卡
6. 模拟一个外接计算设备
   可以通过ssh或者serial登录

## 没做的很好的
1. 实现比较糙，直接在Pi Zero W上搞了，本来是想自己用STM单片机做一个的
2. 由于是linux，启动很慢
3. 软件用QT写的，边学边写，很糙


# A universal boot disk that uses hardware rather than software simulation, similar to Ventoy, but much more powerful!
1. Encryption:
   Encrypt the storage media so there is no risk if lost.
2. Simulate ordinary USB flash drive:
   No introduction is needed, you can plug it into your computer and use it as a USB flash drive
3. Simulate the image on the USB flash drive into a mobile hard disk and optical drive
   After copying the image to a USB flash drive, each image can be simulated as a mobile hard disk and optical drive.
4. Simulate network card
   For laptops without a wireless network card (for example, no driver installed), you can simulate a wireless network card.
6. Simulate an external computing device
   You can log in through ssh or serial
