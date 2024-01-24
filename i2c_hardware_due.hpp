// Bescherming tegen meerdere inclusies. Zorgt ervoor dat de inhoud van dit bestand slechts één keer wordt ingevoegd.
#ifndef DUE_TWI_HPP
#define DUE_TWI_HPP

// Inclusie van de noodzakelijke hwlib bibliotheek.
#include "hwlib.hpp"

// #include "mav_ILogger.h"
// extern mav::ILogger *pLogger;

// Definieer constanten en macro's die nodig zijn voor de configuratie van de TWI klok.
#define TWI_CWGR_FREQ_RATIO(busclk, mck) (((mck) >> 1) / (busclk))
#define TWI_CWGR_MIN_FREQ_RATIO (4)
#define TWI_CWGR_CLDIV_MAX_VALUE (0xFFu)
#define TWI_CWGR_CLDIV1(value) ((value)&TWI_CWGR_CLDIV_MAX_VALUE)
#define TWI_CWGR_CHDIV1(value) (TWI_CWGR_CLDIV(value) << 8)
#define TWI_CWGR_CKDIV_MAX_VALUE (7u)
#define TWI_CWGR_CKDIV1(value) (((value)&TWI_CWGR_CKDIV_MAX_VALUE) << 16)
#define TWI_STANDARD_MODE_SPEED 100000U
#define TWI_FAST_MODE_SPEED 400000U

// Definieer een namespace 'due' om naamgevingsconflicten te voorkomen.
namespace due
{
    // Een klasse genaamd 'twi_bus_due' die erft van 'hwlib::i2c_bus'. Deze klasse handelt de TWI-functionaliteit af voor de Arduino Due.
    class i2c_hardware : public hwlib::i2c_bus
    {
    private:
        // Een private helper functie die een byte naar het TWI output register schrijft.
        void write_byte(uint8_t byte)
        {
            TWI0->TWI_THR = byte; // Schrijf de byte naar het TWI output register.
            // hwlib::wait_us(28); .. blijkt niet nodig.
        }

    public:
        // Instead of write, one can opt for the more flexible (but error-prone) manual series:
        // write_begin, write_block (xn), write_end
        void write_begin(
            uint_fast8_t a) override
        {
            // pLogger->logText("write_begin");

            TWI0->TWI_MMR = 0;                 // Reset de master mode register.
            TWI0->TWI_MMR = 0 << 12 | a << 16; // Stel schrijfmodus in en bepaal het adres.
            TWI0->TWI_IADR = 0;                // Wis het interne adres.
        }

        void write_block(
            const uint8_t data[],
            size_t n) override
        {
            // pLogger->logText("write_block with n:");
            // pLogger->logUint32(n);

            uint32_t status = 0;

            for (size_t i = 0; i < n; ++i)
            {
                status = TWI0->TWI_SR; // Lees de huidige status.
                // Check voor eventuele problemen.
                if (status & TWI_SR_NACK)
                    ; //    pLogger->logText("status & Nack");

                // Controleer of de TWI klaar is om data te verzenden.
                while (!(TWI0->TWI_SR & TWI_SR_TXRDY))
                {
                    hwlib::wait_us(1);
                }

                write_byte(*(data + i));
                // pLogger->logUint32(*(data + i));
            }
        }

        void write_end() override
        {
            // pLogger->logText("write_end");
            uint32_t status = 0;

            // Wacht tot de overdracht klaar is.
            while (1)
            {
                status = TWI0->TWI_SR;
                if (status & TWI_SR_NACK)
                    return;
                if (status & TWI_SR_TXRDY)
                {
                    break;
                }
            }

            // Stop de TWI communicatie.
            TWI0->TWI_CR = TWI_CR_STOP;
            while (!(TWI0->TWI_SR & TWI_SR_TXCOMP))
            {
                hwlib::wait_us(1);
            }

            // pLogger->logText("write ended");
        }

        // Een openbare schrijffunctie voor het schrijven naar een specifiek adres op de TWI bus.
        void write(uint_fast8_t a, const uint8_t data[], size_t n) override
        {
            write_begin(a);
            write_block(data, n);
            write_end();
        }

        // Een placeholder leesfunctie die in de toekomst moet worden geïmplementeerd.
        void read(uint_fast8_t a, uint8_t data[], size_t n) override {}

        // De constructor van de klasse. Hier wordt de initiële configuratie van de TWI bus gedaan.
        i2c_hardware()
        {
            // Configureer de TWI pins.
            auto config_pin = [](uint32_t pin)
            {
                PIOA->PIO_ABSR &= (~pin & PIOA->PIO_ABSR); // Selecteer de juiste functie.
                PIOA->PIO_PDR = pin;                       // Schakel PIO controle uit.
                PIOA->PIO_IDR = pin;                       // Schakel interrupt afhandeling uit.
                PIOA->PIO_PUER = pin;                      // Schakel pull-up weerstand in.
            };

            config_pin(PIO_PA18A_TWCK0); // Configuratie voor TWI klok pin.
            config_pin(PIO_PA17A_TWD0);  // Configuratie voor TWI data pin.

            // Schakel de TWI klok in.
            if ((PMC->PMC_PCSR0 & (1 << ID_TWI0)) != (1 << ID_TWI0))
                PMC->PMC_PCER0 = 1 << ID_TWI0;

            // Reset en configureer de TWI interface.
            TWI0->TWI_CR = TWI_CR_SVEN;  // Schakel de slave mode in.
            TWI0->TWI_CR = TWI_CR_SWRST; // Software reset.
            TWI0->TWI_CR = TWI_CR_SVDIS; // Schakel de slave mode uit.
            TWI0->TWI_CR = TWI_CR_MSDIS; // Schakel de master mode uit.
            TWI0->TWI_CR = TWI_CR_MSEN;  // Schakel de master mode in.

            uint32_t dwCkDiv = 0;
            uint32_t dwClDiv = 0;
            uint32_t dwOk = 0;

            // Stel de TWI kloksnelheid in. De berekening hier is om de juiste delers voor de kloksnelheid te vinden.
            while (!dwOk)
            {
                dwClDiv = ((84000000 / (2 * TWI_FAST_MODE_SPEED)) - 4) / (1 << dwCkDiv);

                if (dwClDiv <= 255)
                    dwOk = 1;
                else
                    dwCkDiv++;
            };

            TWI0->TWI_CWGR = 0;
            TWI0->TWI_CWGR = TWI_CWGR_CLDIV1(dwClDiv) | TWI_CWGR_CHDIV1(dwClDiv) | TWI_CWGR_CKDIV1(dwCkDiv);
        };
    };
}

#endif // DUE_TWI_HPP
