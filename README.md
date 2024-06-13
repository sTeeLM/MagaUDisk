# MagaUDisk
一个使用硬件而不是软件模拟方式实现的万能启动盘，有点类似于Ventoy，不过功能强大的多了！
完美解决了经常需要重装系统，又不像来回写U盘，倒腾U盘启动的各种问题
1. 加密：
   对存储介质加密，如果丢失了不会造成风险。
2. 模拟普通U盘：
   不需要介绍，可以插在电脑上当U盘使
3. 对U盘上的镜像模拟成移动硬盘和光驱
   将镜像复制到U盘上之后，可以对每一个镜像模拟成移动硬盘和光驱，这就解决了Ventoy的所有兼容性问题
   当然也可以dd一个空文件，模拟为移动硬盘，然后在上面以常规手段做启动盘（用工具从ISO写U盘）
5. 模拟网卡
   对于没有无线网卡的笔记本（例如暂时还没装驱动），可以模拟成一个无线网卡，可以先上网再装驱动。。
6. 模拟一个外接计算设备
   可以通过ssh或者serial登录，这个功能就是用来修设备的。。。

## 硬件
1. [waveshare的显示屏](https://www.waveshare.net/shop/1.3inch-LCD-HAT.htm)
2. [zero w USB扩展板](https://www.1688.com/huo/detail-678778501887.html?spm=a262i4.9164788.zhaohuo-list-offerlist.7.db0c6712fqvtJX)

## 其他
1. 实现的比较简单，直接在Pi Zero W上搞了，本来是想自己用STM单片机做一个的，但是在高速USB上模拟阶段暂时碰到了些困难
2. 由于是linux，启动比较慢，需要等一等，可以精简服务或者裸写一个小系统的，太懒了，会但是不想弄
3. 软件用QT写的，边学边写，有点儿糙，三天学一个新语言且熟练使用的能力好像还没退化
4. 大部分时间消耗在怎么调通硬件（大坑是说好的128X128的屏幕，其实是130X130的，如果真按单配置就会有白边，ft），以及写程序，QT确实很好用，一学就会～
5. 模拟网卡其实可以进一步加强，变为连接VPN，但是界面有点儿麻烦，暂时不做了吧，我会，就是懒
6. 硬件上其实可以加一个电池，唯一的用途是不插在USB口上先把系统启动起来，方便一点点吧，有点儿鸡肋，不搞了吧

## 完成状态
![pic](https://github.com/sTeeLM/MegaUDisk/blob/main/pics/cover.jpg)
![pic](https://github.com/sTeeLM/MegaUDisk/blob/main/pics/pic1.jpg)
![pic](https://github.com/sTeeLM/MegaUDisk/blob/main/pics/pic2.jpg)

## A universal boot disk 
that uses hardware rather than software simulation, similar to Ventoy, but much more powerful!
1. Encryption:
   Encrypt the storage media so there is no risk if lost.
2. Simulate ordinary USB flash drive:
   You can plug it into your computer and use it as a USB flash drive
3. Simulate the image on the USB flash drive into a mobile hard disk and optical drive
   After copying the image to a USB flash drive, each image can be simulated as a mobile hard disk or optical drive.
4. Simulate network card
   For laptops without a wireless network card (for example, no driver installed yet), you can simulate a wireless network card.
6. Simulate an external computing device
   You can log in through ssh or serial
