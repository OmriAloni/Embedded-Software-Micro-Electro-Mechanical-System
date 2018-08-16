/*
 * main implementation: use this 'C++' sample to create your own application
 *
 */



#include "derivative.h" /* include peripheral declarations */
# include "TFC.h"


char DataReady=0;

int PCwantData=1;

char state='0'; //0- manu D-3D, C-compass and temp, P-draw
  
		uint8_t rawAccelData [6];		
		uint8_t rawGyroData [6];		
		uint8_t rawMagData [6];
		uint8_t rawTempData[2];
		
		int16_t MPU9250Data[7]; // used to read all 14 bytes at once from the MPU9250 accel/gyro
		int16_t magCount[3];    // Stores the 16-bit signed magnetometer sensor output
		
		float a12, a22, a31, a32, a33;            // rotation matrix coefficients for Euler angles and gravity components
		uint8_t  yawBytes[4], pitchBytes[4], rollBytes[4], tempBytes[4];
		
		extern float eInt[3];
		extern float q[4];
		
		bool wakeup;
		
		int ready=0; //ready=1- PC is ready to get info. ready=0- PC isn't ready 

		void readAllData(); //read x y z
		
		
		int main()
  		{
			ClockSetup();
			InitGPIO(); //for Led and LCD
			initalizeLCD();
			
			initializeMPU9250Parameters (); //initlize MPU9250
			
			//mpu9250
			MCU_Init1(); //set the I2C connections of the mpu9250
			MPU9250SelfTest(mpu9250.SelfTest); //checking if the results are reasonable
			getAres(); //set the accelerometer scales  
			getGres();  //set the gyro scales  
			getMres(); //set the manometer scales  
			calibrateMPU9250(mpu9250.gyroBias, mpu9250.accelBias); // calibrate the gyro  bias and accl bias  
			initMPU9250(); //set the setting of the sampling  (sample rate 200Hz)
			initAK8963(mpu9250.magCalibration); // calibrate the mag 
			//magcalMPU9250(mpu9250.magbias, mpu9250.magScale);
			
			
			
		    //35 building
		    /*mpu9250.magbias[0] = -284.035;  // User environmental x-axis correction in milliGauss, should be automatically calculated
		    mpu9250.magbias[1] = 96.4646;  // User environmental x-axis correction in milliGauss
		    mpu9250.magbias[2] = -140.72;  // User environmental x-axis correction in milliGauss
		    mpu9250.magScale[0]=1.13913;
		    mpu9250.magScale[1]=1.07377;
		    mpu9250.magScale[2]=0.839744;
		*/
			/*
			//ofir's home
			mpu9250.magbias[0] = -291.18;  // User environmental x-axis correction in milliGauss, should be automatically calculated
			mpu9250.magbias[1] = 25.0093;  // User environmental x-axis correction in milliGauss
			mpu9250.magbias[2] = -99.5337;  // User environmental x-axis correction in milliGauss
			mpu9250.magScale[0]=1.12585;
			mpu9250.magScale[1]=0.939007;
			mpu9250.magScale[2]=0.955267;
		 */
			
			
			/* first working in lab
			mpu9250.magbias[0] = -292.967;  // User environmental x-axis correction in milliGauss, should be automatically calculated
			mpu9250.magbias[1] = 66.0961;  // User environmental x-axis correction in milliGauss
			mpu9250.magbias[2] = -106.398;  // User environmental x-axis correction in milliGauss
			mpu9250.magScale[0]=1.2029;
			mpu9250.magScale[1]=0.904984;
			mpu9250.magScale[2]=0.940129;
			 */
			
			/* second working in lab
			mpu9250.magbias[0] = -301.899;  // User environmental x-axis correction in milliGauss, should be automatically calculated
			mpu9250.magbias[1] = 51.8051;  // User environmental x-axis correction in milliGauss
			mpu9250.magbias[2] = -154.449;  // User environmental x-axis correction in milliGauss
			mpu9250.magScale[0]=1.05202;
			mpu9250.magScale[1]=0.947917;
			mpu9250.magScale[2]=1.00552;
		 */

		    /* third working in lab
			mpu9250.magbias[0] = -307.258;  // User environmental x-axis correction in milliGauss, should be automatically calculated
			mpu9250.magbias[1] = 57.1642;  // User environmental x-axis correction in milliGauss
			mpu9250.magbias[2] = -126.991;  // User environmental x-axis correction in milliGauss
			mpu9250.magScale[0]=1.05556;
			mpu9250.magScale[1]=0.953405;
			mpu9250.magScale[2]=0.996255;
		   */
		    
			/* 12:52 working in lab
			mpu9250.magbias[0] = -319.762;  // User environmental x-axis correction in milliGauss, should be automatically calculated
			mpu9250.magbias[1] = 7.14553;  // User environmental x-axis correction in milliGauss
			mpu9250.magbias[2] = -135.572;  // User environmental x-axis correction in milliGauss
			mpu9250.magScale[0]=1.10536;
			mpu9250.magScale[1]=0.854815;
			mpu9250.magScale[2]=1.08052;
		   */
			
			
			//mpu9250.magbias[0] = -332.267;  // User environmental x-axis correction in milliGauss, should be automatically calculated
			//mpu9250.magbias[1] = 16.0774;  // User environmental x-axis correction in milliGauss
			//mpu9250.magbias[2] = -102.966; // User environmental x-axis correction in milliGauss
			//mpu9250.magScale[0]=1.16098;
			//mpu9250.magScale[1]=0.840878;
			//mpu9250.magScale[2]=1.05326;
			
			mpu9250.magbias[0] = -319.762;  // User environmental x-axis correction in milliGauss, should be automatically calculated
			mpu9250.magbias[1] = 7.14553;  // User environmental x-axis correction in milliGauss
			mpu9250.magbias[2] = -135.572;  // User environmental x-axis correction in milliGauss
			mpu9250.magScale[0]=1.10536;
			mpu9250.magScale[1]=0.854815;
			mpu9250.magScale[2]=1.08052;

		    //MMA8451Q
		    MCU_Init0(); //set the I2C connections of the MMA8451Q 
		    Accelerometer_Init (); // set the setting of the sampling of the MMA8451Q sensor 
		    Calibrate(); // calibrate the the offset of the MMA8451Q accl 

			InitUARTs(); //set the Uart connections 
			delayForUpdatetime(); //start the pit timer for the mpu9250.deltat for MahonyQuaternionUpdate
			
			//lcd_put_string("can move the device." ,20);
			while(1){
				
				  readAllData(); //read all the data from sensors
				
				  //mpu9250.deltat = 0.01495;
				  updateTime(); // Calculate the time between the last time we run the function updateTime() to this time. 
				 // if(mpu9250.deltat==0)
				//  {
				//	  delayForUpdatetime();
				 // }
				  if (mpu9250.deltat<=0){
					  mpu9250.deltat = 0.0435; 
				  }
				  MahonyQuaternionUpdate(mpu9250.ax, mpu9250.ay,  mpu9250.az , mpu9250.gx*PI/180.0f, mpu9250.gy*PI/180.0f, mpu9250.gz*PI/180.0f,  mpu9250.my,  mpu9250.mx, -mpu9250.mz , mpu9250.deltat);
				   
				  
				      a12 =   2.0f * (q[1] * q[2] + q[0] * q[3]);
				      a22 =   q[0] * q[0] + q[1] * q[1] - q[2] * q[2] - q[3] * q[3];
				      a31 =   2.0f * (q[0] * q[1] + q[2] * q[3]);
				      a32 =   2.0f * (q[1] * q[3] - q[0] * q[2]);
				      a33 =   q[0] * q[0] - q[1] * q[1] - q[2] * q[2] + q[3] * q[3];
				      mpu9250.pitch = -asinf(a32);
				      mpu9250.roll  = atan2f(a31, a33);
				      mpu9250.yaw   = atan2f(a12, a22);
				      mpu9250.pitch *= 180.0f / pi;
				      mpu9250.yaw   *= 180.0f / pi; 
				      mpu9250.yaw   -= 4.65f; // Declination at Danville, California is 13 degrees 48 minutes and 47 seconds on 2014-04-04
				      if(mpu9250.yaw < 0) mpu9250.yaw   += 360.0f; // Ensure yaw stays between 0 and 360
				      mpu9250.roll  *= 180.0f / pi;
				    
				      mpu9250.lin_ax = mpu9250.ax + a31;
				      mpu9250.lin_ay = mpu9250.ay + a32;
				      mpu9250.lin_az = mpu9250.az - a33;
				      
				      
				      while(PCwantData==1);
				      PCwantData=1;
				      switch(state) {
				      
				      case 'D':
				            IntTostring((int)(mpu9250.pitch*1000.0));
				            IntTostring((int)(mpu9250.yaw*1000.0)); 
				            IntTostring((int)(mpu9250.roll*1000.0));
				      break;
				      
				      case 'C':
				    	    IntTostring((int)(mpu9250.yaw*1000.0));
				    		IntTostring((int)(mpu9250.temperature*1000.0));
				      break;
				      case 'P':
				    	    IntTostring((int)(mpu9250.pitch*1000.0));
				    	    IntTostring((int)(mpu9250.yaw*1000.0)); 
				    	    IntTostring((int)(mpu9250.roll*1000.0));
				    	    IntTostring((int)(Xout_g*1000.0));
				    		IntTostring((int)(Yout_g*1000.0));
				    		IntTostring((int)(Zout_g*1000.0));
				      break;
				      }
				     
				    	//state='0';
				    	

		}
		}



//-----------------------------------------------------------------
//  UART0 - ISR
//-----------------------------------------------------------------
void UART0_IRQHandler(){
	volatile char temp= UART0_D;
    if(temp=='D' || temp=='C' || temp=='P'){
      PCwantData=0;
      state=temp;
    }

}





void readAllData()
{
	if((readByte(MPU9250_ADDRESS, INT_STATUS) & 0x01))
	    {

	     readGyroData(mpu9250.gyroCount);
		 mpu9250.gx = (float)mpu9250.gyroCount[0]*mpu9250.gRes - mpu9250.gyroBias[0];  // get actual gyro value, this depends on scale being set
		 mpu9250.gy = (float)mpu9250.gyroCount[1]*mpu9250.gRes - mpu9250.gyroBias[1];  
		 mpu9250.gz = (float)mpu9250.gyroCount[2]*mpu9250.gRes - mpu9250.gyroBias[2];   
		 readMagData(mpu9250.magCount);
		 mpu9250.mx = ((float)mpu9250.magCount[0]*mpu9250.mRes*mpu9250.magCalibration[0] - mpu9250.magbias[0])*mpu9250.magScale[0];  // get actual magnetometer value, this depends on scale being set
		 mpu9250.my = ((float)mpu9250.magCount[1]*mpu9250.mRes*mpu9250.magCalibration[1] - mpu9250.magbias[1])*mpu9250.magScale[1];  
		 mpu9250.mz = ((float)mpu9250.magCount[2]*mpu9250.mRes*mpu9250.magCalibration[2] - mpu9250.magbias[2])*mpu9250.magScale[2]; 
		 readAccelData(mpu9250.accelCount);
		 mpu9250.ax = (float)mpu9250.accelCount[0]*mpu9250.aRes - mpu9250.accelBias[0];  // get actual g value, this depends on scale being set
		 mpu9250.ay = (float)mpu9250.accelCount[1]*mpu9250.aRes - mpu9250.accelBias[1];   
		 mpu9250.az = (float)mpu9250.accelCount[2]*mpu9250.aRes - mpu9250.accelBias[2];  
		 
		 
		 if(state=='P')
		 {
		   unsigned char reg_val = 0;
		 	
		 while (!reg_val)		// Wait for a first set of data		 
		 {
		 	reg_val = I2C_ReadRegister(MMA845x_I2C_ADDRESS, STATUS_REG) & 0x08; 
		 } 		
		 I2C_ReadMultiRegisters(MMA845x_I2C_ADDRESS, OUT_X_MSB_REG, 6, AccData);		// Read data output registers 0x01-0x06 
		 			        
		 Xout_14_bit =  ((short) (AccData[0]<<8 | AccData[1])) >> 2;		// Compute 14-bit X-axis output value
		 Yout_14_bit = ((short) (AccData[2]<<8 | AccData[3])) >> 2;		// Compute 14-bit Y-axis output value
		 Zout_14_bit = ((short) (AccData[4]<<8 | AccData[5])) >> 2;		// Compute 14-bit Z-axis output value
		 						
	
		 
		 Xout_g = ((float) Xout_14_bit) / SENSITIVITY_2G;		// Compute X-axis output value in g's
		 Yout_g = ((float) Yout_14_bit) / SENSITIVITY_2G;		// Compute Y-axis output value in g's
		 Zout_g = ((float) Zout_14_bit) / SENSITIVITY_2G;		// Compute Z-axis output value in g's
		 
		 }

	 mpu9250.tempCount= readTempData();
	 mpu9250.temperature = ((float) mpu9250.tempCount) / 333.87f + 21.0f; // Temperature in degrees Centigrade
	          }
}




