/*
 * Major Credit to:
 * Rui Santos: Complete project details at http://randomnerdtutorials.com
 * major referance for setting up a HTML server on the ESP32 and figuring out how to use buttons
 */

  #ifndef CONFIG_H
  #define CONFIG_H
    const char* ssid = "Kittler House";
    const char* password = "69kittler";
    const long timeoutTime = 2000;
    const String pageTitle = "Drink Bot";
    
    const String dropDownStyle = ".dropbtn {\n  background-color: #4CAF50;\n  color: white;\n  padding: 16px;\n  font-size: 16px;\n  border: none;\n}\n\n.dropdown {\n  position: relative;\n  display: inline-block;\n}\n\n.dropdown-content {\n  display: none;\n  position: absolute;\n  background-color: #f1f1f1;\n  min-width: 160px;\n  box-shadow: 0px 8px 16px 0px rgba(0,0,0,0.2);\n  z-index: 1;\n}\n\n.dropdown-content a {\n  color: black;\n  padding: 12px 16px;\n  text-decoration: none;\n  display: block;\n}\n\n.dropdown-content a:hover {background-color: #ddd;}\n\n.dropdown:hover .dropdown-content {display: block;}\n\n.dropdown:hover .dropbtn {background-color: #3e8e41;}";
   #endif
