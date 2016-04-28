void print_EC_data(void) {                            //this function will pars the string  
  char sensorstring_array[100];                        //we make a char array
  char *deviceName;                                           //char pointer used in string parsing
  char *sensorName;                                          //char pointer used in string parsing
  char *sensorType;                                          //char pointer used in string parsing
  char *sensorUnit;                                          //char pointer used in string parsing
  char *posix;                                         //char pointer used in string parsing
  char *reading;                                         //char pointer used in string parsing
  char *messageType;                                         //char pointer used in string parsing
  
  float f_ec;                                         //used to hold a floating point number that is the EC

//Serial.println(sensorstring);
  
  sensorstring.toCharArray(sensorstring_array, 100);   //convert the string to a char array 
  deviceName = strtok(sensorstring_array, ",");               //let's pars the array at each comma
  sensorName = strtok(NULL, ",");                            //let's pars the array at each comma
  sensorType = strtok(NULL, ",");                            //let's pars the array at each comma
  sensorUnit = strtok(NULL, ",");                            //let's pars the array at each comma
  posix = strtok(NULL, ",");                           //let's pars the array at each comma
  reading = strtok(NULL, ",");                           //let's pars the array at each comma
  messageType = strtok(NULL, ",");                           //let's pars the array at each comma

  if (messageType[0] == 'M'){
    messageType = "METRIC";
  }

  //msg ='{\nmetric: "%s",\ndatapoints: [\n{\ntags: {"arduino.name":"%s","rpi.hostname": "%s","rpi.ip": "%s","rpi.datatype": "%s", "sensor.name": "%s","sensor.unit": "%s"},\nvalues: {"%s":"%s"}\n}]\n}' % (sensorMetric,device,RPIhostname,RPIip,dataType,sensorName,sensorUnit,sensorTimeStamp,sensorValue)

  //Serial.println("local IP: ");
  //Serial.println(WiFi.localIP());



  //lines below merge parameters to create TAGs
  stringPayload = "{\nmetric: \"";
  stringPayload += sensorType ;
  stringPayload += "\",\ndatapoints: [\n{\ntags: {\"device.name\":\"";
  stringPayload += deviceName;
  stringPayload += "\",\"device.hostname\":\"" ;
  stringPayload += sensorName;
  stringPayload += "\",\"device.ip\":\"";
  stringPayload += myIpString;
  stringPayload += "\",\"device.datatype\":\"";
  stringPayload += messageType;
  stringPayload += "\",\"sensor.name\":\"";
  stringPayload += sensorType;
  stringPayload += "\",\"sensor.unit\":\"";
  stringPayload += sensorUnit;
  stringPayload += "\"},\nvalues: {\"";
  stringPayload += readTime;
  stringPayload += "\":\"";
  stringPayload += reading;
  stringPayload += "\"}\n}]\n}";

  Serial.println(stringPayload);

  for (int i=0 ; i < 300 ; i++){    //clean the payload
    payload[i]='\0';
  }
 
  
  for (int i=0 ; i < stringPayload.length() ; i++){ //transfer stringPayload to payload
    payload[i]= stringPayload.charAt(i);

  }

    client.publish("javier/board1", payload); //publish payload to MQTT
  
}
