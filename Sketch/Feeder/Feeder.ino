#include "FeederServo.h"
#include "FeederRadio.h"
#include "Feeder.h"

//Set the remote or controller
bool remote = false;

void read_button()
{
	if (!digitalRead(BUTTON_A))
	{
		feeder_radio.send_cmd(0);
	}

	if (!digitalRead(BUTTON_B))
	{
		feeder_radio.send_cmd(1);
	}

	if (!digitalRead(BUTTON_C))
	{
		feeder_radio.send_cmd(2);
	}

	delay(200);
	yield();
	display.display();
}

void start_display()
{
	display.begin(0x3C, true); // Address 0x3C default

	// Show image buffer on the display hardware.
	display.display();
	delay(1000);

	// Clear the buffer.
	display.clearDisplay();
	display.display();

	display.setRotation(1);

	pinMode(BUTTON_A, INPUT_PULLUP);
	pinMode(BUTTON_B, INPUT_PULLUP);
	pinMode(BUTTON_C, INPUT_PULLUP);

	// text display tests
	display.setTextSize(1);
	display.setTextColor(SH110X_WHITE);
	display.setCursor(0, 0);

	display.println("Rapid Prototyping");
	display.println("AWH FEEDER");
	display.println("PRESS A. RUN");
	display.println("PRESS B. CLOSE");
	display.println("PRESS C. OPEN");
	display.display(); // display all of the above
}

void setup() {
	Serial.begin(115200);
	if(remote)
	{
		start_display();
	}
	feeder_radio.start_radio();
}

void loop() {
	if (remote)
	{
		read_button();
	}
	else
	{
		feeder_radio.rx_packet();
	}
}
