#include "Plip.h"

Plip::Plip(int pin, int period = 2000) {
	pinMode(pin, OUTPUT);
	digitalWrite(pin, HIGH);
	_pin = pin;
	// Calculate timings based on period
	_pulse = period / 40;      // Default 50us
	_oneSpace1 = _pulse * 9;       // Default 450us
	_oneSpace2 = _pulse * 2;       // Default 100us
	_zeroSpace = _pulse * 39;		// Default 1950us
}

void Plip::send(long code, int repeats) {
	if (repeats <= 0) return;

	if (code < 0 || code > 88888) {
		#if defined(SERIAL_DEBUG) || defined(ARDUINO)
		Serial.println("Warning: Plip code out of range (0-88888). Clamping value.");
		#endif
	}
	code = constrain(code, 0, 88888);

	// Extract 5 digits from code
	byte digit[5];
	long temp = code;
	for (int i = 4; i >= 0; --i) {
		digit[i] = temp % 10;
		temp /= 10;
	}

	for (int i = 0; i < repeats; i++) {
		for (int j = 0; j < 5; ++j) {
			sendDigit(digit[j]);
		}
		sendDigit(0xFF); // End marker
	}
}

// Helper to send a sequence of pulses: 1 = sendOne, 0 = sendZero
void Plip::pulseSequence(const int* sequence, int length) {
	for (int i = 0; i < length; ++i) {
		if (sequence[i])
			sendOne();
		else
			sendZero();
	}
}

void Plip::sendDigit(byte num) {
	// Each digit 0-8 is represented by a sequence of 4 bits
	static const int digitPatterns[9][4] = {
		{1,0,1,0}, // 0
		{1,0,0,1}, // 1
		{1,0,0,0}, // 2
		{0,1,1,0}, // 3
		{0,1,0,1}, // 4
		{0,1,0,0}, // 5
		{0,0,1,0}, // 6
		{0,0,0,1}, // 7
		{0,0,0,0}  // 8
	};
	static const int endPattern[4] = {0, 1, 1, 1}; // End marker

	if (num <= 8) {
		pulseSequence(digitPatterns[num], 4);
	} else {
		pulseSequence(endPattern, 4);
	}
}

// Inline sendOne and sendZero for performance
inline void Plip::sendOne() {
	// Send a "one" sequence
	digitalWrite(_pin, LOW);
	delayMicroseconds(_pulse);
	digitalWrite(_pin, HIGH);
	delayMicroseconds(_oneSpace1);
	digitalWrite(_pin, LOW);
	delayMicroseconds(_pulse);
	digitalWrite(_pin, HIGH);
	delayMicroseconds(_oneSpace2);
}

inline void Plip::sendZero() {
	// Send a "zero" sequence
	digitalWrite(_pin, LOW);
	delayMicroseconds(_pulse);
	digitalWrite(_pin, HIGH);
	delayMicroseconds(_zeroSpace);
}