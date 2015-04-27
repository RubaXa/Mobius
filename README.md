<table>
<tr>
	<td><img src="st/logo.png" height="450"/></td>
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



A very simple example
=====================

```c++
#include <Mobius.h>

use namespace Mobius;

Led *led = new Led(10);
Led::Array *indicator = Led::Array::range(2, 9);

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


### Сomponents

 * Led
 * Led::Bar
 * Button
 * Power
 * Motor
