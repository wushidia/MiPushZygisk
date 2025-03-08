# MiPush Zygisk

一个用于为应用伪装小米设备的 Magisk/Zygisk 模块，以便于使用 [MiPush](https://github.com/NihilityT/MiPushFramework.git)

### 下载
前往 [Release](https://github.com/wushidia/MiPushZygisk/releases) 下载

### 配置
手动编辑 `/data/adb/modules/zygisk_mipushfake/config` 文件

配置示例：
```
#对该应用所有进程进行伪装
com.example.app

#对该应用指定进程进行伪装，格式：包名|进程名
com.example.app|com.example.app:push
```


### 构建
配置 ndk 路径后在项目根目录执行，构建产物在 `build` 目录下
```shell
./build.sh
```

### 致谢
感谢[HMSPush](https://github.com/fei-ke/HmsPushZygisk.git)，这个项目99%的代码都是从那边抄的

### License
[GNU General Public License v3 (GPL-3)](http://www.gnu.org/copyleft/gpl.html)。
