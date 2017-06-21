#include <SparkFun_MMA8452Q.h>
#include <SoftwareSerial.h>
#include <Wire.h> // Must include Wire library for I2C


SoftwareSerial BTSerial(4, 5); //Connect HC-06. Use your (TX, RX) settings

// Begin using the library by creating an instance of the MMA8452Q
//  class. We'll call it "accel". That's what we'll reference from
//  here on out.
MMA8452Q accel;

void setup() {
  Serial.begin(9600);
  Serial.println("Hello!");

  BTSerial.begin(9600);  // set the data rate for the BT port

  // Choose your adventure! There are a few options when it comes
  // to initializing the MMA8452Q:
  //  1. Default init. This will set the accelerometer up
  //     with a full-scale range of +/-2g, and an output data rate
  //     of 800 Hz (fastest).

  // accel.init();

  accel.init(SCALE_8G,ODR_200); 
  
  //  2. Initialize with FULL-SCALE setting. You can set the scale
  //     using either SCALE_2G, SCALE_4G, or SCALE_8G as the value.
  //     That'll set the scale to +/-2g, 4g, or 8g respectively.
  //accel.init(SCALE_4G); // Uncomment this out if you'd like
  //  3. Initialize with FULL-SCALE and DATA RATE setting. If you
  //     want control over how fast your accelerometer produces
  //     data use one of the following options in the second param:
  //     ODR_800, ODR_400, ODR_200, ODR_100, ODR_50, ODR_12,
  //     ODR_6, or ODR_1.
  //     Sets to 800, 400, 200, 100, 50, 12.5, 6.25, or 1.56 Hz.
}

void loop() {
  if (accel.available()) {
    accel.read();
  
    float svm = 
      sqrt(
        ((accel.cx)*(accel.cx)) + 
        ((accel.cy)*(accel.cy)) + 
        ((accel.cz)*(accel.cz))
      );
    
    String value;
    value.concat(svm);
    value.concat("/");
    BTSerial.write(string2char(value));
  }
}

char* string2char(String command){
    if(command.length()!=0){
        char *p = const_cast<char*>(command.c_str());
        return p;
    }
}
