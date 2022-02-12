# Weather Melody
*description coming soon, link to blog post...*
* *arduino_secrets.h* — required, but not included in this repo. You will need create one of your own with the following format:
  ```C++
  //arduino_secrets.h
  char ssid[] = "your network's name";             // network SSID (name)
  char pass[] = "your network password"; // network password (use for WPA, or use as key for WEP)
  int keyIndex = 0;                     // network key Index number (needed only for WEP)
  ```
* weatherMelody.ino — the Arduino sketch

## Arduino Libraries
* [WiFi101](https://www.arduino.cc/en/Reference/WiFi101)
* [ArduinoHttpClient](https://github.com/arduino-libraries/ArduinoHttpClient)
* [MIDIUSB](https://github.com/arduino-libraries/MIDIUSB)

## Data
A data frame [fetched by id](http://weatherband.itp.io:3000/data/id/31) from the ITP Weather Band's [Weather Server DB Web API](https://github.com/ITPNYU/Weather-Band/tree/main/database-api) looks like this:
```JSON
{
  "id": 31,
  "mac_address": "A4:CF:12:8A:C8:24",
  "recorded_at": "2020-11-25T06:28:47.000Z",
  "wind_dir": 90,
  "winddir_avg2m": 50,
  "windspeedmph": 1.23,
  "windgustdir_10m": 90,
  "windgustmph_10m": 4.51,
  "rainin": 0,
  "dailyrainin": 0,
  "rain_avg1m": null,
  "rain_avg10m": null,
  "temperature": 18.25,
  "humidity": 61.02,
  "pressure": 102.97,
  "illuminance": 1.61,
  "uva": 0,
  "uvb": 0,
  "uvindex": 0
}
```

## Assemble the circuit
*coming soon...*

## Contributing
To contribute to this project please contact [Amped Atelier](ampedatelier@gmail.com).