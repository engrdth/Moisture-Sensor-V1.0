// Soil Sensor and Battery Monitoring Node 200

// Enable debug prints
#define MY_DEBUG
//#define MY_RF24_CE_PIN 10 
//#define MY_RF24_CS_PIN 9
//#define MY_PARENT_NODE_ID 0
//#define MY_PARENT_NODE_IS_STATIC

// Enable passive mode
#define MY_PASSIVE_NODE

// Passive mode requires static node ID
#define MY_NODE_ID 200

// Enable and select radio type attached
#define MY_RADIO_RF24
//#define MY_RADIO_NRF5_ESB
//#define MY_RADIO_RFM69
//#define MY_RADIO_RFM95

#include <MySensors.h>

#define SoilSensor_ID 0   // Id of the Soil Sensor
#define Battery_ID 1   // Id of the Battery

// Initialize general message
MyMessage msg(SoilSensor_ID, V_LEVEL);
MyMessage bat(Battery_ID, V_VOLTAGE);

//Initialize Sensor pin and output value sent 
int sensor_pin = A1; 
int battery_pin = A0;
float output_value;
float decimals;

//Initialize resistors and voltage calculations
float value = 0.0;
float voltage;
float R1 = 100000.0;
float R2 = 10000.0;


void setup()
{
  Serial.begin(9600);
 
}

void presentation()
{
  // Send the sketch version information to the gateway and controller
  sendSketchInfo("Soil Sensor Node 200", "1.0");

  // Register all sensors to gw (they will be created as child devices)
  present(SoilSensor_ID, S_MOISTURE);
  present(Battery_ID, S_MULTIMETER);
  
}

void loop()
{
  // generate soil sensor data and send
  output_value= analogRead(sensor_pin);
  output_value = map(output_value,600,10,0,100);
  Serial.print("Moisture : ");
  Serial.print(output_value);
  Serial.println("%");
  send(msg.set(output_value, decimals));
  delay(1000);

  //Send Battery Voltage
  value = analogRead(battery_pin);
  voltage = value * ((5.0 / 1024) * ((R1 + R2) / R2));
  Serial.print("Battery Voltage = ");
  Serial.println(voltage);
  send(bat.set(voltage, decimals));
  delay(1000);

  
}
