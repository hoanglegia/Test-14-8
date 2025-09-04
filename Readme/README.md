**Version**: 1.0.0  
**Author**: Group 5  
**Update**: 2025-09-04  

# Generate 1Hz Wave to Control RGB LED

<details>
  <summary>Table of Contents</summary>
  <ol>
    <li><a href="#about-the-project">About The Project</a></li>
    <li>
      <a href="#build-instruction">Build Instruction</a>
      <ul>
        <li><a href="#exercise-1-hal-timer">Exercise 1: HAL TIMER</a></li>
        <li><a href="#exercise-2-hal-pwm">Exercise 2: HAL PWM</a></li>
        <li><a href="#exercise-3-led-fade">Exercise 3: LED FADE</a></li>
        <li><a href="#software-and-overall-architecture">Software and Overall Architecture</a></li>
      </ul>
    <li><a href="#usage">Usage</a></li>
    <li><a href="#result">Result</a></li>
    <li><a href="#acknowledgments">Acknowledgments</a></li>
  </ol>
</details>

## About The Project
This project includes three exercises that demonstrate how to control an **RGB LED** on the **STM32F103C8T6** board using the HAL library:

**HAL TIMER** – Configure a hardware timer in interrupt mode to generate a 1 Hz square wave, toggling the RGB LED ON/OFF.

**HAL PWM** – Use a timer in PWM mode to automatically create a 1 Hz signal with 50% duty cycle for LED control.

**LED Fade (PWM Timers)** – Apply PWM with a higher frequency and adjust duty cycles gradually to produce a smooth fading effect on the RGB LED.

Through these exercises, the project provides a clear introduction to:
- Using **HAL Timers** for periodic interrupts.
- Configuring **PWM channels** for both low-frequency blinking and high-frequency brightness control.
- Building modular STM32 projects with a separation between **application code** and **driver layers**.

## Build Instruction

### Exercise 1: HAL TIMER
- **Description**
  - Use the STM32F103C8T6 HAL TIMER library to generate a 1Hz square wave.
  - The 1Hz signal is used to toggle the RGB LED on and off.

- **Hardware**
  - Board: STM32F103C8T6 (Blue Pill)
  - RGB LED connected to GPIO pins 
    - GND → GND
    - 3V → 3V
    - Red → PB3
    - Green → PB5
    - Blue → PB7
- **Software configuration**
![IOC1](./image/IOC1.png)
- **Timer Configuration**
  - System Clock: 72 MHz
  - Target Frequency: 1 Hz
  - Prescaler (PSC): To get 1Hz from 72MHz
   ```sh 
    Timer frequency = 72,000,000 / (PSC + 1) / (ARR + 1)
      Choose PSC = 7199, ARR = 9999
    72,000,000 / (7199 + 1) / (9999 + 1) = 1 Hz
    ```
- **Code Placeholder:**
    ```c
    // === TIMER Initialization Code Here ===

    // === RGB LED Toggle Code Here ===
    ```

### Exercise 2: HAL PWM
- **Description**
  - Use the STM32F103C8T6 HAL PWM library to generate a 1Hz PWM signal.
  - The PWM output is used to control the RGB LED (on/off at 1Hz).

- **Hardware**
  - Board: STM32F103C8T6 (Blue Pill)
  - RGB LED connected to GPIO pins 
    - GND → GND
    - 3V → 3V
    - Red → PB3
    - Green → PB5
    - Blue → PB7
    
- **Software configuration**
![IOC2](./image/IOC2.png)
- **Timer Configuration**
  - **System Clock:** 72 MHz
  - **Target Frequency:** 1 Hz
  - **Prescaler (PSC):** 7199
  - **Duty Cycle:** 50% duty
        CCR = ARR / 2 = 5000
- **Code Placeholder:**
    ```c
    // === TIMER Initialization Code Here ===

    // === RGB LED Toggle Code Here ===
    ```

### Exercise 3: LED FADE
- **Description**
  - Use PWM timers to gradually increase and decrease the brightness of the RGB LED (fade effect).

- **Hardware**
  - Board: STM32F103C8T6 (Blue Pill)
  - RGB LED connected to GPIO pins 
    - GND → GND
    - 3V → 3V
    - Red → PB3
    - Green → PB5
    - Blue → PB7

- **Software configuration**
![IOC3](./image/IOC3.png)

- **Timer Configuration**
  - **System Clock:** 72 MHz
  - **PWM Frequency:** 1 kHz (for smooth fading)
  - **Prescaler (PSC):** 71
  - **Duty Cycle:**
    - Vary CCR from 0 to 999 for 0% to 100% brightnes
- **Code Placeholder:**
    ```c
    // === TIMER Initialization Code Here ===

    // === RGB LED Toggle Code Here ===
    ```

### Software and Overall Architecture
#### Software
- **STM32CubeMX**: A hardware configuration tool that automatically generates HAL code for peripherals such as GPIO, EXTI, and TIM, helping to shorten development time.
![STM32CubeMX](./image/STM32CubeMX.png)
- **Keil µVision 5**: An integrated development environment (IDE) for ARM, supporting compilation, programming, and debugging for STM32.
![KeilC](./image/KeilC.png)
- **STM32CubeF4 HAL Library**: A hardware abstraction library provided by ST, making peripheral operations easier, increasing compatibility, and reducing errors from direct register programming.
![STM32F4Library](./image/STM32F4Library.png)
#### Architecture
```text
Application Layer
  └── main.c
      - Initializes hardware, selects exercise mode, and runs the main control loop for each exercise:
        * Exercise 1: Timer interrupt toggling RGB LED
        * Exercise 2: PWM output for 1Hz ON/OFF
        * Exercise 3: PWM output with variable duty for LED fading

Drivers (User)
  ├── rgb_led.c/.h   // Functions to control RGB LED (on/off/toggle, set color, set brightness)
  ├── timer.c/.h     // Timer initialization, interrupt handler (for Exercise 1)
  └── pwm.c/.h       // PWM initialization, set frequency/duty (for Exercise 2 & 3)

HAL (STM32Cube)
  └── CMSIS + HAL    // Low-level drivers for GPIO, TIM, PWM, NVIC, etc.
```

## Usage
**Operations with Keil C**
After configuring and generating code from **STM32CubeMX**, open the project in **Keil C**.
Navigate to the file main.c located under **Application/User**.

 - Use the **Build (F7)** button to compile the program.

 - Use the **Load (F8)** button to flash the program to the board.
![keilcide.c](./image/keilcide.png)

***Notes when flashing the program***

Click on the Option for Target icon (or go to Project → Option for Target) to perform several necessary configurations:

 - In the Option for Target window, select the Debug tab and tick Use ST-Link Debugger in order to download the program to the development board.
(If you choose Use Simulator, the program will only run in simulation mode.)

 - Click Settings next to Use: ST-Link Debugger. In the Cortex-M Target Driver Setup window, go to the Flash Download tab:
![option4target](./image/option4target.png)
    - If you tick Reset and Run, the program will automatically run right after flashing.

    - If you do not tick this option, after flashing you will need to press the Reset button on the board to start the program.
![resetnrun](./image/resetnrun.png)

## Result

## Acknowledgments
* [KeilC](https://www.keil.com/demo/eval/arm.htm)
* [STM32F1 Reference manual](https://www.st.com/resource/en/reference_manual/rm0008-stm32f101xx-stm32f102xx-stm32f103xx-stm32f105xx-and-stm32f107xx-advanced-armbased-32bit-mcus-stmicroelectronics.pdf)
* [STM32F103C8T6 Datasheet](https://www.alldatasheet.com/datasheet-pdf/pdf/201596/STMICROELECTRONICS/STM32F103C8T6.html)
* [STM32F103C8T6 schematic](https://stm32-base.org/assets/pdf/boards/original-schematic-STM32F103C8T6-Blue_Pill.pdf)