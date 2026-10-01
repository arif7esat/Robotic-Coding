#include <avr/io.h>

volatile uint8_t resetNedeni;

// setup'tan önce çalışır
void erkenBaslangic(void)
__attribute__((naked))
__attribute__((section(".init3")));

void erkenBaslangic(void)
{
    resetNedeni = MCUSR;
    MCUSR = 0;
}

void setup()
{
    Serial.begin(9600);

    Serial.print("MCUSR = ");
    Serial.println(resetNedeni, BIN);

    if (resetNedeni & (1 << PORF))
        Serial.println("Power On Reset");

    if (resetNedeni & (1 << EXTRF))
        Serial.println("External Reset");

    if (resetNedeni & (1 << BORF))
        Serial.println("Brown Out Reset");

    if (resetNedeni & (1 << WDRF))
        Serial.println("Watchdog Reset");
}

void loop()
{
}
