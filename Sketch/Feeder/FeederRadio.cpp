// 
// 
// 

#include "FeederRadio.h"
#include "FeederServo.h"

// Singleton instance of the radio driver
RH_RF69 rf69(RFM69_CS, RFM69_INT);

char radiopacket[2];
unsigned long rx_received;
int16_t rssi;
int16_t packetnum = 0;

void FeederRadio::send_cmd(int cmd) const
{
	if(cmd == 0)
	{
		radiopacket[0] = 'A';
	}

	if (cmd == 1)
	{
		radiopacket[0] = 'B';
	}

	if (cmd == 2)
	{
		radiopacket[0] = 'C';
	}
	
	rf69.send((uint8_t*)radiopacket, strlen(radiopacket));
	rf69.waitPacketSent();
}

void FeederRadio::start_radio() const
{

	pinMode(RFM69_RST, OUTPUT);
	digitalWrite(RFM69_RST, LOW);

	// manual reset
	digitalWrite(RFM69_RST, HIGH);
	delay(10);
	digitalWrite(RFM69_RST, LOW);
	delay(10);

	if (!rf69.init()) {
		Serial.println("RFM69 radio init failed");
		while (true);
	}
	Serial.println("RFM69 radio init OK!");
	// Defaults after init are 434.0MHz, modulation GFSK_Rb250Fd250, +13dbM (for low power module)

	if (!rf69.setFrequency(RF69_FREQ)) {
		Serial.println("setFrequency failed");
	}

	// If you are using a high power RF69 eg RFM69HW, you *must* set a Tx power with flag like this:
	rf69.setTxPower(20, true);  // range from 14-20 for power, 2nd arg must be true for 69HCW

	// The encryption key has to be the same as the one in the server
	uint8_t key[] = { 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
					  0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08 };

	rf69.setEncryptionKey(key);
}

void FeederRadio::rx_packet() const
{
	if (rf69.available()) {
		uint8_t buf[RH_RF69_MAX_MESSAGE_LEN];
		uint8_t len = sizeof(buf);
		if (rf69.recv(buf, &len)) {
			if (!len) return;
			buf[len] = 0;

			if (strstr((char*)buf, "A")) {
				Serial.println("RUN");
				FeederServo::run();
			}

			if (strstr((char*)buf, "B")) {
				Serial.println("CLOSE");
				FeederServo::close();
			}

			if (strstr((char*)buf, "C")) {
				Serial.println("OPEN");
				FeederServo::open();
			}

		}
		else {
			Serial.println("Receive failed");
		}
	}

}

FeederRadio feeder_radio;

