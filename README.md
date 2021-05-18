Smart Temperature and Humidity Device
=============

Our project interfaces a room temperature and humidity sensor connected to an Arduino platform with Amazon web services through an ESP32 WiFi chip. The scope of our project primarily focuses on the utility Amazon Web Services provide, so we use an Alexa enabled device connected to our Amazon account to receive and read out current temperature and humidity. We can also ask Alexa to email the data to us through SNS to have records of our temperature and humidity along with time stamps email clients provide. We also have a graph of the current and past temperatures and humidities running on a localhost website written in html which can be used to see fluctuations which might be abnormal.The use cases of our project include pet monitoring and baby room condition monitoring. This will be especially useful if the end user has an Air Conditioner or Humidifier that can be controlled through Amazon Alexa. Others include similar monitoring for office or business environments over the weekend, or extended periods of holidays which would have come in handy during the lockdown caused by the pandemic. These will help us save energy in the long term which is a huge financial and environmental benefit.


Requirements
---------------
* ESP32 Microcomtroller
* DHT11 Temperature and Humidity Sensor
* Access to Amazon Web Services (AWS)
