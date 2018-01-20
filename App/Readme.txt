             应用层                                                 板级支持层                             固件库
-------------------------------------                      ------------------------------        --------------------------
1、主任务      main.c         main.h                                           
2、通信解析    dispose.c      dispose.h  
3、按键处理    key.c          key.h          <------------  gpio  spi  adc  pwm  timer    
4、指示灯      led.c          led.h          <------------  gpio  spi
5、程序升级    upgrade.c      upgrade.h      <------------  iap   usb
6、板卡信息    information.c  information.h  <------------  iic   gpio

