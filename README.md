**Version**: 1.0.0
**Author**: Group 5
**Update**: 2025-08-28

# Button FSM to Control 3 LEDs

<details>
  <summary>Table of Contents</summary>
  <ol>
    <li>
      <a href="#about-the-project">About The Project</a>
    </li>
    <li>
      <a href="#build-instruction">Build Instruction</a>
      <ul>
        <li><a href="#fsm-finate-state-machine">FSM (Finate State Machine)</a></li>
        <li><a href="#hardware-used">Hardware Used</a></li>
        <li><a href="#software-and-tools">Software and Tools</a></li>
        <li><a href="#overall-architecture">Overall Architecture</a></li>
      </ul>
    </li>
    <li><a href="#detailed-components">Detailed Components</a></li>
    <ul>
        <li><a href="#stm32-configuration">STM32 Configuration</a></li>
        <li><a href="#led-library">LED Library</a></li>
        <li><a href="#button-library">Button Library</a></li>
        <li><a href="#execution-model-of-mainc">Execution Model of main.c</a></li>
      </ul>
    <li><a href="#usage">Usage</a></li>
    <li><a href="#result">Result</a></li>
    <li><a href="#acknowledgments">Acknowledgments</a></li>
  </ol>
</details>

## About The Project

This project demonstrates how to control three LEDs with a single button on the **STM32F407VGT6** (STM32F4 DISCOVERY) board using a **Finite State Machine** (FSM) approach. The system recognizes different types of button interactions: **SINGLE_CLICK**, **DOUBLE_CLICK**, and **LONG_CLICK** (>3 seconds)—and changes the LED states accordingly.

By separating the logic into **drivers** (Button, LED) and **the application layer** (FSM in main.c), the project achieves a clean architecture that is easy to extend

This project is an educational example of:
- Using **GPIO** and **interrupt** for button debouncing.
- Implementing a **finite state machine** in embedded systems.
- Structuring STM32 projects with clear separation of concerns.

## Build Instruction

### FSM (Finate State Machine)
![FSM](./image/FSM.png)

The Finite State Machine (FSM) is a method of organizing control logic based on discrete states. In this project, the FSM is used to detect button actions (**SINGLE_CLICK**, **DOUBLE_CLICK**, **LONG_CLICK**) and control the states of three LEDs accordingly. The state diagram illustrates the transitions between LED states based on button events, making the code clear, maintainable, and easy to extend.

### Hardware Used
- **Board**: STM32F4DISCOVERY – MCU **STM32F407VGT6**, 168 MHz, 1 MB Flash, 192 KB SRAM.
- **User Button**: PA0 (GPIO_Input)
- **On-board LEDs**:
  - LED1 → PD12
  - LED2 → PD13
  - LED3 → PD14
![STM32](./image/STM32.jpg)

### Software and Tools
- **STM32CubeMX**: A hardware configuration tool that automatically generates HAL code for peripherals such as GPIO, EXTI, and TIM, helping to shorten development time.
![STM32CubeMX](./image/STM32CubeMX.png)
- **Keil µVision 5**: An integrated development environment (IDE) for ARM, supporting compilation, programming, and debugging for STM32.
![KeilC](./image/KeilC.png)
- **STM32CubeF4 HAL Library**: A hardware abstraction library provided by ST, making peripheral operations easier, increasing compatibility, and reducing errors from direct register programming.
![STM32F4Library](./image/STM32F4Library.png)

### Overall Architecture

```C
Application (FSM)
   └── main.c            (main loop, FSM, LED state control)
Drivers (User)
  ├── Button.c/.h       (button interrupt, debounce logic, event detection)
  └── LED.c/.h          (LED driver functions)
HAL (STM32Cube)
  └── CMSIS + HAL       (GPIO, EXTI, TIM, SysTick)
```

## Detailed Components
### STM32 Configuration

- **Pinout Configuration**: STM32CubeMX is used to configure GPIO pins for LEDs (PD12, PD13, PD14) and the button (PA0), as well as to set up interrupt functionality for the button.
![GPIO](./image/GPIO.png)

- **SYS Configuration**: System features such as debug and clock output are enabled if needed, ensuring stable operation and easier debugging.
![SYSWire](./image/SYSWire.png)
![SYSPin](./image/SYSPin.png)
 


![Pinout](./image/Pinout.png)
<p align="center">
  Pinout configuration
</p>

- **Clock Configuration**: The system clock is set to an appropriate frequency (72 MHz) to ensure performance for real-time tasks and button debounce handling.
![Clock](./image/Clock.png)

### LED Library

The LED Library provides an abstraction for controlling three on-board LEDs on the STM32F4 Discovery board. It defines a `LED` structure to store the GPIO port and pin numbers for each LED, and offers simple functions to control their states.

**Key features:**
- Encapsulates LED pin configuration in a `LED` struct (`myLED`), making it easy to manage multiple LEDs.
- Provides functions to turn on each LED individually (`LED1_ON()`, `LED2_ON()`, `LED3_ON()`), ensuring only one LED is active at a time. 
- Provides functions to turn off all LEDs `LED_OFF()`, ensuring all LEDs are inactive at a time.
- Uses the STM32 HAL library for GPIO operations, ensuring portability and reliability.

**Main API:**
- `void LED1_ON();` — Turns on LED1 (PD12), turns off LED2 and LED3.
- `void LED2_ON();` — Turns on LED2 (PD13), turns off LED1 and LED3.
- `void LED3_ON();` — Turns on LED3 (PD14), turns off LED1 and LED2.
- `void LED_OFF();` — Turns off LED1 (PD12), LED2 (PD13), LED3 (PD14).

**Implementation:**
```C
void LED1_ON()
{
	HAL_GPIO_WritePin(myLED.PORT_D, myLED.D1, 1); // Turn on LED 1
	HAL_GPIO_WritePin(myLED.PORT_D, myLED.D2, 0); // Turn off LED 2
	HAL_GPIO_WritePin(myLED.PORT_D, myLED.D3, 0); // Turn off LED 3
}

void LED2_ON()
{
	HAL_GPIO_WritePin(myLED.PORT_D, myLED.D1, 0); // Turn off LED 1
	HAL_GPIO_WritePin(myLED.PORT_D, myLED.D2, 1); // Turn on LED 2
	HAL_GPIO_WritePin(myLED.PORT_D, myLED.D3, 0); // Turn off LED 3
}

void LED3_ON()
{
	HAL_GPIO_WritePin(myLED.PORT_D, myLED.D1, 0); // Turn off LED 1
	HAL_GPIO_WritePin(myLED.PORT_D, myLED.D2, 0); // Turn off LED 2
	HAL_GPIO_WritePin(myLED.PORT_D, myLED.D3, 1); // Turn on LED 3
}

void LED_OFF()
{
	HAL_GPIO_WritePin(myLED.PORT_D, myLED.D1, 0); // Turn off LED 1
	HAL_GPIO_WritePin(myLED.PORT_D, myLED.D2, 0); // Turn off LED 2
	HAL_GPIO_WritePin(myLED.PORT_D, myLED.D3, 0); // Turn off LED 3
}
```

This modular approach allows the application (FSM) to control LED states with simple function calls, improving code readability and maintainability.

### Button Library

The Button Library provides an abstraction for handling the user button on the STM32F4 Discovery board, supporting detection of different button events such as single click, double click, and long click.

**Key features:**
- Defines a `button` structure to manage button state, debounce timing, and event detection.
- Implements software debouncing and timing logic to reliably distinguish between SINGLE_CLICK, DOUBLE_CLICK, and LONG_CLICK events.
- Provides a `button_read()` function that reads the button state and returns the detected event, making it easy for the FSM to process user input.
- Uses STM32 HAL for GPIO reading and timing, ensuring portability and accuracy.

**Main API:**
- `button_state button_read(button *Button);` — Reads the button and returns the detected event (`SINGLE_CLICK`, `DOUBLE_CLICK`, `LONG_CLICK`, or `NO_CLICK`).

**Flowchart:**
![Button_Flowchart](./image/Button_Flowchart.png)

**Implementation:**
```C
button myButton;
case_fsm case_itr = off;

button_state button_read(button *Button)
{
  Button->state = NO_CLICK;
	while (HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_0) == 1) 			// Button is pressed
	{
		Button->timePress++;																// Increase time when hold the button 
		Button->isPress = 1;
		HAL_Delay(1);
	}
	if (Button->isPress)
	{
		while (HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_0) == 0)			// Stop pressing button
		{
			Button->timeDouble++;															// Increase time when release the button
			HAL_Delay(1);
			if (Button->timeDouble > DOUBLE_CLICK_TIME)				// Check button's state			
			{
				if (Button->timePress > DEBOUND_TIME && Button->timePress <= SINGLE_CLICK_TIME)	// Press the button 1 time (SINGLE CLICK)
				{
					Button->isPress = 0;
					Button->timePress = 0;
					Button->timeDouble = 0;
					Button->state = SINGLE_CLICK;
					return Button->state;
				}
				else if (Button->timePress > SINGLE_CLICK_TIME)	// Hold the button (LONG CLICK)
				{
					Button->isPress = 0;
					Button->timePress = 0;
					Button->timeDouble = 0;
					Button->state = LONG_CLICK;
					return Button->state;
				}
			}
		}
		while (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) == 1) 		// Press the button 2 times (DOUBLE CLICK)
		{
			Button->state = DOUBLE_CLICK;
			Button->isPress = 0;
			Button->timePress = 0;
			Button->timeDouble = 0;
			return Button->state;
		}
	}
	return NO_CLICK;																			// Default Button's State
}
```

This modular design allows the application to handle complex button interactions with simple function calls, improving code clarity and robustness.
### Execution Model of main.c

The `main.c` file implements the application logic using a Finite State Machine (FSM) to control the LEDs based on button events. The main loop continuously checks the current FSM state and responds to user input as follows:

**Key steps:**
- Initializes the LED and button structures, configures GPIO, and sets up the system clock.
- In the infinite loop, uses a `switch` statement on the FSM state (`case_itr`) to determine which LED should be active.
- Transitions between states are triggered by button events detected via `button_read(&myButton)`:
	- `SINGLE_CLICK` from OFF state turns on LED1.
	- `DOUBLE_CLICK` cycles through LED1 → LED2 → LED3 → LED1.
	- `LONG_CLICK` from any ON state turns all LEDs off.
- Each state ensures only the correct LED is on, or all are off.

**FSM State Transitions:**
- `off` → `led1_on` (SINGLE_CLICK)
- `led1_on` → `led2_on` (DOUBLE_CLICK), or `off` (LONG_CLICK)
- `led2_on` → `led3_on` (DOUBLE_CLICK), or `off` (LONG_CLICK)
- `led3_on` → `led1_on` (DOUBLE_CLICK), or `off` (LONG_CLICK)

**Flowchart:**
![main.c](./image/main.jpg)

**Implementation:**
```C
extern LED myLED;
extern button myButton;
extern case_fsm case_itr;

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */
	/* Private defines ----------------------------------------------------- */
	myLED.PORT_D = GPIOD;
	myLED.D1 = GPIO_PIN_12;
  myLED.D2 = GPIO_PIN_13;
	myLED.D3 = GPIO_PIN_14;
	
	myButton.PORT_BUTTON = GPIOA;
	myButton.BUTTON_PIN = GPIO_PIN_0;
	myButton.state = NO_CLICK;
	myButton.isPress = 0;
	myButton.timePress = 0;
	myButton.timeDouble = 0;
	
	
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */
    /* USER CODE BEGIN 3 */
		switch(case_itr)
		{
			case off:			// Turn off all LEDS
				if(button_read(&myButton) == SINGLE_CLICK)
				{
					case_itr = led1_on;
				}
				LED_OFF();
				break;
				
			case led1_on: // Turn on LED 1
				LED1_ON();
				if(button_read(&myButton) == DOUBLE_CLICK)
				{
					case_itr = led2_on;
				}
				if(button_read(&myButton) == LONG_CLICK)
				{
					case_itr = off;
				}
				break;
				
			case led2_on:	// Turn on LED 2
				LED2_ON();
				if(button_read(&myButton) == DOUBLE_CLICK)
				{
					case_itr = led3_on;
				}
				if(button_read(&myButton) == LONG_CLICK)
				{
					case_itr = off;
				}
				break;
				
			case led3_on:	// Turn on LED 3
				LED3_ON();
				if(button_read(&myButton) == DOUBLE_CLICK)
				{
					case_itr = led1_on;
				}
				if(button_read(&myButton) == LONG_CLICK)
				{
					case_itr = off;
				}
				break;
				
			default:
				break;
		}
  }
  /* USER CODE END 3 */
}
```

This structure separates hardware control (LED, Button) from application logic, making the code modular, readable, and easy to maintain.

## Usage
**Directory Tree**
```C
.
├─ Inc/
│  ├─ LED.h
│  ├─ Button.h
│  ├─ main.h
│  └─ ...
├─ Src/
│  ├─ LED.c
│  ├─ Button.c
│  ├─ main.c
|  └─ ...
├─ Drivers/            
│  ├─ CMSIS/...
│  └─ STM32F4xx_HAL_Driver/...
├─ images/
│  └─ ...
|
└─ README.md
```
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
Below are the results corresponding to each scenario, as shown in the images:

- **Result 1:** LED1 is ON, while LED2 and LED3 are OFF.  
![result1](./image/result1.jpg)  
<br>

- **Result 2:** LED2 is ON, while LED1 and LED3 are OFF.
![result2](./image/result2.jpg)
<br>

- **Result 3:** LED3 is ON, while LED1 and LED2 are OFF.
![result3](./image/result3.jpg)
<br>

- **Result 4:** All LEDs (LED1, LED2, and LED3) are OFF.
![result4](./image/result4.jpg)

## Acknowledgments

* [KeilC](https://www.keil.com/demo/eval/arm.htm)
* [STM32F4 Reference manual](https://www.st.com/resource/en/reference_manual/dm00031020-stm32f405-415-stm32f407-417-stm32f427-437-and-stm32f429-439-advanced-arm-based-32-bit-mcus-stmicroelectronics.pdf)
* [STM32F407G-DISC1 Datasheet](https://www.alldatasheet.com/datasheet-pdf/download/792967/ETC2/STM32F407G-DISC1.html)
* [STM32F407G-DISC1 schematic](https://www.st.com/resource/en/schematic_pack/mb997-f407vgt6-e01_schematic.pdf)
* [STM32 with single click, double click and long click](https://khuenguyencreator.com/stm32-voi-nut-nhan-3-che-do-click-double-click-va-long-click/)
