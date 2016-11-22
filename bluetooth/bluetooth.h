/* 
 * \file bluetooth.h
 * \author Ramy Elminyawi
 * \brief provides AT&T Clinic specific interface for BlueSmirf bluetooth 
 *  connection
 */

#ifndef BLUETOOTH_H_INCLUDED
#define BLUETOOTH_H_INCLUDED

class Bluetooth {
	public:
	   	/**
		  * \brief default constructor
		  */
		 // Bluetooth();
		/**
		  * \brief opens serial port
		  */
		  int openPort();
		 /**
		   * \brief configures serial port
		   */
		  void configurePort(int);
		 /**
		   * \brief reads serial port
		   */
		  void readPort();
		 /**
		   * \brief writes to serial port
		   */
		  int writePort();
		 /**
		   * \brief default destructor
		   */
		  //~Bluetooth();
	private:
		int numVar;
		int serialHandle;
};

#endif

