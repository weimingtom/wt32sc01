# wt32sc01
[WIP] My ESP-IDF LVGL project for WT32-SC01

## How to burn to WT32-SC01  
* WT32-SC01 v3.2, ESP32-WROVER B.  
* When white english 'WT32-SC01' is north, connect  
bottom pins first row left 3 (pin 6)  
to first row left 12 (pin 24).  
* After burnning, connect   
bottom pins first row left 2 (pin 4)
to first row left 12 (pin 24).  
* If burn, use: idf.py flash, after burn, need to press RESET button on board       
* If build, use: idf.py build   
* Tested under esp-idf 4.4.3 (4.3 may be ok)  
* If install ESP-IDF for windows, see https://dl.espressif.cn/dl/esp-idf/  

## Ref  
* Wireless-Tag  
https://github.com/wireless-tag-com/WT32-SC01  
* https://github.com/wireless-tag-com/8ms-esp32  
* https://search.gitee.com/?q=wt32-sc01&type=repository  

## WT32-SC01-PLUS (with ESP32-S3) ref, not for WT32-SC01    
* not for WT32-SC01: https://github.com/wireless-tag-com/ZX3D50CE02S  
