<table>
<tr>
	<td><img src="st/logo.png" width="360" alt="Möbius"/></td>
	<td>
		<h1>Features</h1>
		<ul>
			<li>Event-driven architecture</li>
			<li>Maximum abstraction</li>
			<li>Demonstrativeness and ease of assembly</li>
			<li>Visual effects</li>
			<li>No delays!</li>
		</ul>
		<p>&nbsp;</p>
		<p>&nbsp;</p>
		<p>&nbsp;</p>
		<p>&nbsp;</p>
		<p>&nbsp;</p>
	</td>
</tr>
</table>


---


A very simple example
=====================

```c++
#include <Mobius.h>

use namespace Mobius;

LED *led = new LED(10);
LED::Array *indicator = LED::Array::range(2, 9);

Power *power = new Power(500); // duration, ms
Button *btn = new Button(11);

void setup() {
	led->setEffect(new Effects::Blink(500));

	power->attach(indicator);
	btn->attach(power);

	power->bind(Power::PRGORESS, &handleEvent);
}

void handleEvent(int id) {
	switch (id) {
		case Power::VALUE:
			if (power->value == 1) {
				led->on();
			} else if (led->value) {
				led->off();
			}
			break;
	}
}

void loop() {
	Mobius::strip();
}
```


---


### Using motor

```c++
#include <Mobius.h>

use namespace Mobius;

Button *btn = new Button(2);
Motor *motor = new Motor(3, 4);
Power *acceleration = new Power(1000);

void setup() {
	motor->setDirection(Motor::CW);
	acceleration->attach(motor);
	btn->attach(acceleration);
}

void loop() {
	Mobius::strip();
}
```


---


### Сomponents

 * LED
 * LED::Bar
 * Button
 * Power
 * Motor


---


### Installation
 1. [Download the Arduino Software](http://www.arduino.cc/en/Main/Software)
 2. Run IDE
 3. Clone this repository: `git@github.com:RubaXa/Mobius.git`
 4. `cd Mobius`
 5. `make all` (Create a `Mobius.zip`)
 6. IDE: [Sketch] > [Include Library] -> [Add .ZIP Library]
 7. Enjoy!


```c++
#include <Mobius.h>

use namespace Mobius;

// Variables

void setup() {
	// Logic
}

void loop() {
	Mobius::strip();
}
```


---


### MIT LICENSE
