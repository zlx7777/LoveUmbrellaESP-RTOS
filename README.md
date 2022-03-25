# LoveUmbrellaESP-RTOS

第二代爱心雨伞控制器程序，基于 FreeRTOS 操作系统。

> 爱心雨伞控制器使用 [ESP8266开发板](https://github.com/HNIT-IoT-Lab/ESP8266-board) 作为核心板。

## Todo

- [x] 在不重刷固件的情况下更新 WIFI 配置
  - [x] 使用微信小程序配网 (AirKiss 协议)
  - [ ] ~~使用 APP 配网~~
  - [x] 重新配网 (复位5次恢复出厂设置)
- [ ] 与服务器通信
  - [x] 嵌入 KCP 协议
  - [ ] 连接服务器
- [ ] 使用 Json 格式通信
  - [ ] Json 格式约定
  - [ ] Json 解析
- [ ] 使用 LED 灯展示状态
- [ ] 使用 蜂鸣器 展示状态