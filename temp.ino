#include<WiFi.h>
#include<DHT.h>
#include<AWS_IOT.h>

#define DHT_PIN 33 // pin connected to data pin of DHT11
#define DHT_TYPE DHT11  // Type of the DHT Sensor, DHT11/DHT22

#define WIFI_SSID "NETGEAR23" // SSID of your WIFI
#define WIFI_PASSWD "greenprairie221" //your wifi password

#define CLIENT_ID "Temp_Humidity"// thing unique ID, this id should be unique among all things associated with your AWS account.
#define MQTT_TOPIC "$aws/things/DHT11_Demo/shadow/update" //topic for the MQTT data
#define AWS_HOST "auz0gmuq1udbf-ats.iot.us-west-1.amazonaws.com" // your host for uploading data to AWS,

DHT dht(DHT_PIN, DHT_TYPE);
AWS_IOT aws;
char reportpayload[512];
void setup(){
  Serial.begin(9600);
  Serial.print("\nInitializing thing Temp_Humidity_DHT11_0 \n");

  Serial.print("\n  Initializing WIFI: Connecting to ");
  Serial.println(WIFI_SSID);
  WiFi.begin(WIFI_SSID, WIFI_PASSWD);
  Serial.print("  ");
  while(WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(500);
  }
  Serial.println("\n  Connected.\n  Done");

  Serial.print("\n  Initializing DHT11...");
  dht.begin();
  Serial.println("  Done.");

  Serial.println("\n  Initializing connetction to AWS....");
  if(aws.connect(AWS_HOST, CLIENT_ID) == 0){ // connects to host and returns 0 upon success
    Serial.println("  Connected to AWS\n  Done.");
  }
  else {
    Serial.println("  Connection failed!\n make sure your subscription to MQTT in the test page");
  }
  Serial.println("  Done.\n\nDone.\n");
}

void loop(){
  // read temperature and humidity
  float temp = dht.readTemperature(); // return temperature in °C
  float humidity = dht.readHumidity();// return humidity in %

  // check whether reading was successful or not
  if(temp == NAN || humidity == NAN){ // NAN means no available data
    Serial.println("Reading failed.");
  }
  else{
    //create string payload for publishing
    String temp_humidity = "Temperature: ";
    temp_humidity += String(temp);
    temp_humidity += "°C Humidity: ";
    temp_humidity += String(humidity);
    temp_humidity += " %";

   
    char payload[40];
    temp_humidity.toCharArray(payload, 40);
    sprintf(reportpayload,"{\"state\": {\"reported\": {\"temperature\": \"%0.1f\",\"humidity\": \"%0.1f\"}}}",temp, humidity);
    Serial.println("Publishing:- ");
    Serial.println(payload);
    Serial.println(reportpayload);
     if(aws.publish(MQTT_TOPIC, reportpayload) == 0){// publishes payload and returns 0 upon success
      Serial.println("Success\n");
    }
    else{
      
      Serial.println("Failed!\n");
    }
  }

  delay(1000);
}
