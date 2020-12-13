![C/C++ CI](https://github.com/spirit0908/STM32F103C8T6/workflows/C/C++%20CI/badge.svg)

# Presentation of the project

## Modules
- Light management (dimmer, timer, LED strips...)
- Switch management
- Security Keypad
- Heat management

## Boards
- Development board (Proto board)
- Wall switch board
- Light control board
- Heater control board


## Architecture

Distributed network based on CAN bus

```
                        temp.                   wall
  I/O  I/O              sensor          light  switch
   |    |                 |               |       |
 +-+----+-----+     +-----+------+     +--+-------+-+
 |            |     |            |     |            |
 |  Module 1  |     |  Module 3  |     |  Moduel 5  |
 |            |     |            |     |            |
 +-----+------+     +-----+------+     +-----+------+ 
       |                  |                  |
       +-----+------------+-----+------------+-------- CAN Bus
             |                  |
       +-----+------+     +-----+------+ 
       |            |     |            |
       |  Module 2  |     |  Module 4  |
       |            |     |            |
       +-+-------+--+     +-----+------+
         |       |              |
       RFID   iButton      smart meter
      reader  reader        interface
```

## Boards

### Proto board
- LCD
- 4x switch
- 4x control output (RGBW)
- RS232
- CAN

### Relay board
- 4x switch
- 4x control output (RGBW)
- 6x relay output
- RS232
- CAN

### Intercom board
- 3x sensor input
- 2x relay output
- RS232
- CAN

# How to use

## How to compile

make

## How to execute the tests

make test

Test results location: out/tests/Test_report.html


