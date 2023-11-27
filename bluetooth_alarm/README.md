# STM32F 보드를 활용한 블루투스 알람시계  

|개발 환경|개요|  
|:-------:|:---:|
|개발보드|Nucleo-F429ZI(Nucleo-144)|  
|MCU|STM32F429ZITx|  
|IDE|STM32Cube IDE 1.13.2|  
  
  ----  

**[ 프로젝트 개요 ]**

- 수행기간: 2023.11.10 ~ 2023.11.24  
- 담당업무: 회로 제작 및 소스코드 작성   
- 사용기능: GPIO, UART, ADC, I2C, EXT_INT, Timer, RTC, DMA, Flash Memory, PWM
- 사용디바이스: 16x2 Character LCD, Joystick, Piezo Buzzer     

**[ 기능 개요 ]**  
1.	조이스틱으로 시간, 알람, 노래 설정 및 LCD에 출력
2.	블루투스로 연결된 휴대폰으로 시간, 알람, 노래 설정 및 LCD에 출력
3.	Normal 모드에서 현재 시간 출력. 설정된 시간부터 시간이 흐름
4.	Time Setting, Alarm Setting 모드에서 각각 시간 설정
5.	Music Select 모드에서 알람 노래 설정. 노래 선택마다 해당 멜로디 출력
6.	모드 전환은 Normal 상태에서만 가능. Time, Alarm, Music 모드 간 전환 불가
7.	지난 세팅에서 설정한 시간, 알람시간, 노래가 플래시 메모리에 저장
8.	전원을 껐다가 켜면 지난 세팅에서 설정한 내용이 불러오기 됨 
  

<<<<<<< HEAD
**[ 상태 다이어그램 ]**  

![블루투스알람시계모드개요_크기수정](https://github.com/Minhee713/mini-projects-with-stm32f429/assets/127821647/4872cd51-0fec-486f-b5c9-c4781de79850)
- 총 4가지 상태로 구분  
- Normal mode 상태에서 각 모드로 진입 가능  
- Time Setting, Alarm Setting, Music Select 모드 간 전환 불가  

=======
>>>>>>> 9e711c17b8bf83a71dec6d5fd9eea92c2f7f2693
**[ 하드웨어 인터페이스 구성 ]**  

|기능|디바이스(모듈)|  
|:--:|:--:|  
|GPIO(External Interrupt)|Button|  
|UART|Bluetooth, ST-Link Debugger|  
|ADC|Joystick|  
|I2C|16x2 Character LCD|  
|PWM|Buzzer|   

**[ 핀 설정 ]**  
|모듈명|모듈 연결|보드 핀 번호|  
|:----:|:-----------:|:-----:|  
|LCD|SCL|PB8|    
| |SDA|PB9|  
|Joystick|VRX|PC0 (ADC1_IN10)|  
| |VRY|PC3 (ADC1_IN13)|  
| |SW|PF3|  
|Bluetooth|RXD|PD5 (USART2_TX)|  
| |TXD|PD6 (USART2_RX)|  

**[ 주요 함수 관계 다이어그램]**  

- main 함수 내부  

![main크기조정](https://github.com/Minhee713/mini-projects-with-stm32f429/assets/127821647/09156d4c-fba7-45bb-8193-6c6a80eefe9d)

- GPIO EX_INT Callback 함수와 main 함수 관계    

![gpio_](https://github.com/Minhee713/mini-projects-with-stm32f429/assets/127821647/4282b769-303b-4f63-824e-d0fb0ca4bed1)  

- 주요 함수 구현 개요    

![주요함수](https://github.com/Minhee713/mini-projects-with-stm32f429/assets/127821647/3ee429b0-aa42-4ca1-b039-6b31f5ac68a4)


