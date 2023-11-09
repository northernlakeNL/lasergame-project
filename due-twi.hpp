#ifndef DUE_TWI_HPP
#define DUE_TWI_HPP

#include "hwlib.hpp"

#define TWI_CWGR_FREQ_RATIO(busclk, mck)	(((mck) >> 1) / (busclk))
#define TWI_CWGR_MIN_FREQ_RATIO				(4)
#define TWI_CWGR_CLDIV_MAX_VALUE			(0xFFu)
#define TWI_CWGR_CLDIV1(value)				((value) & TWI_CWGR_CLDIV_MAX_VALUE)
#define TWI_CWGR_CHDIV1(value) 				(TWI_CWGR_CLDIV(value) << 8)
#define TWI_CWGR_CKDIV_MAX_VALUE			(7u)
#define TWI_CWGR_CKDIV1(value) 				(((value) & TWI_CWGR_CKDIV_MAX_VALUE) << 16)
#define TWI_STANDARD_MODE_SPEED 100000U
#define TWI_FAST_MODE_SPEED 400000U

namespace due
{

	/**
	 * @class twi_bus_due
	 * @author Niels
	 * @date 04/11/2017
	 * @file due-twi.hpp
	 * @brief Hardware version of the TWI bus. For use with the arduino DUE.
	 */
	 
	class twi_bus_due : public hwlib::i2c_bus{
	private:
		/**
		* @brief Private write function for writing to the output register.
		* @param byte[in] The "to be written" byte.
		* 
		* Hwlib::wait_ns is needed for some reason that I haven't been able to get into yet.
		* It seems like the TXRDY register isn't quite as honest as I would have assumed.
		*/
		void write_byte(uint8_t byte) {
			TWI0->TWI_THR = byte;
			hwlib::wait_ns(28000);
		}
		
	public:
		/**
		 * @brief Public write function, written for compatibility with hwlib.
		 * @param a[in] Address to be written to.
		 * @param data[in] Array with data to be written to the device.
		 * @param n[in] Amount of data to be written.
		 * 
		 * A lot of registers need to be written to in order to make this work.
		 * Every registers has reasonably clear docs on what they do.
		 * Change TWI0 to TWI1 to swap the used TWI pins.
		 * 
		 * Wouter if ever read this: please start using more clear names for
		 * function parameters.
		 */
		void write(uint_fast8_t a, const uint8_t data[], size_t n) override {
			TWI0->TWI_MMR = 0; /**< Reset master mode register */
			TWI0->TWI_MMR = 0 << 12 | a << 16; /**< Set write and address */
			TWI0->TWI_IADR = 0; /**< Clear internal address */
			
			uint32_t status = 0;

			for(size_t i = 0; i < n; ++i) {
				status = TWI0->TWI_SR;
				if (status & TWI_SR_NACK)
					hwlib::cout << "status & NACK" << hwlib::endl;
				
				if (status & TWI_SR_TXRDY) {
					write_byte(*(data + i));
				}
			}
			
			while(1) {
				status = TWI0->TWI_SR;
				if (status & TWI_SR_NACK)
					return;
				if (status & TWI_SR_TXRDY) {
					break;
				}
			}
			
			TWI0->TWI_CR = TWI_CR_STOP;
			while (!(TWI0->TWI_SR & TWI_SR_TXCOMP));
		}

		//TODO: Needs a read function
		void read(uint_fast8_t a, 
					uint8_t data[], 
					size_t n ) override {
						
		}

		twi_bus_due() {
			/**
			 * Configure TWI pins.
			 */
			auto config_pin = [](uint32_t pin) {
				PIOA->PIO_ABSR &= (~pin & PIOA->PIO_ABSR);
				PIOA->PIO_PDR = pin;
				PIOA->PIO_IDR = pin;
				PIOA->PIO_PUER = pin;
			};
	
			config_pin(PIO_PA18A_TWCK0);
			config_pin(PIO_PA17A_TWD0);
		
			if ((PMC->PMC_PCSR0 & (1 << ID_TWI0)) != (1 << ID_TWI0))
				PMC->PMC_PCER0 = 1 << ID_TWI0;

			TWI0->TWI_CR = TWI_CR_SVEN;
			TWI0->TWI_CR = TWI_CR_SWRST;
			
			TWI0->TWI_CR = TWI_CR_SVDIS;
			TWI0->TWI_CR = TWI_CR_MSDIS;
			
			TWI0->TWI_CR = TWI_CR_MSEN;

			uint32_t dwCkDiv = 0;
			uint32_t dwClDiv = 0;
			uint32_t dwOk = 0;

			/**
			 * Setting the TWI clock.
			 * Calculating the clock periods is wonky but it seems to work.
			 * TWI bus is now set default to TWI fast mode (400kHz).
			 */
			while(!dwOk) {
				dwClDiv = ((84000000 / (2 * TWI_FAST_MODE_SPEED)) - 4) / (1<<dwCkDiv);

				if(dwClDiv <= 255)
					dwOk = 1;
				else
					dwCkDiv++;
			};
			
			TWI0->TWI_CWGR = 0;
			TWI0->TWI_CWGR = TWI_CWGR_CLDIV1(dwClDiv) | TWI_CWGR_CHDIV1(dwClDiv) | TWI_CWGR_CKDIV1(dwCkDiv);
		}

	};
}

#endif // DUE_TWI_HPP
