String html_main = "<!DOCTYPE html><html><head><meta charset='UTF-8' name='viewport' content='width=device-width, initial-scale=1'><title>Connectiprise</title><style>body{background-color: #3D3D3D;color: white;font-family: Arial, Helvetica, sans-serif;}.side-panel{background-color: #1D1D1D;position: absolute;top: 0px;left: 0px;height: 100%;width: 150px;}.name{font-size: 20px;width: 100%;margin-top: 10px;text-align: center;}.separator{width: 100%;height: 1px;margin-top: 10px;background-color: white;}.side-menu{padding-left: 0px;width: 100%;}.side-menu > li {text-align: center;list-style-type: none;list-style-position: inside;height: 30px;}.side-menu > li > a{color: inherit;vertical-align: middle;text-decoration: none;}.side-menu :hover{background-color: #2d2d2d;}.content-container{margin-left: 160px;margin-top: 10px;}</style><head><body><div class='side-panel'><div class='name'>Connectiprise</div><div class='separator'></div><ul class='side-menu'><li><a href='/connection'>Connection</a></li><li><a href='/parametre'>Parametres</a></li><li><a href='/statistique'>Statistiques</a></li></ul></div><!-- <iframe class='content-container' src='./connection.html'></iframe> --><div class='content-container'>{{{content}}}</div><script>var date = new Date();var time = {hours: date.toTimeString().slice(0,2), minutes: date.toTimeString().slice(3,5), seconds: date.toTimeString().slice(6,8)};var xhr = new XMLHttpRequest();xhr.open('POST', '/updateDate', true);xhr.send(JSON.stringify(time));</script></body></html>";
String html_param = "<style>.content-title{color: white;}.switch {position: relative;display: inline-block;width: 60px;height: 34px;}.switch input {display:none;}.slider {position: absolute;cursor: pointer;top: 0;left: 0;right: 0;bottom: 0;background-color: #BB2500;-webkit-transition: .4s;transition: .4s;}.slider:before {position: absolute;content: '';height: 26px;width: 26px;left: 4px;bottom: 4px;background-color: white;-webkit-transition: .4s;transition: .4s;}input:checked + .slider {background-color: #408F00;}input:focus + .slider {box-shadow: 0 0 1px #2196F3;}input:checked + .slider:before {-webkit-transform: translateX(26px);-ms-transform: translateX(26px);transform: translateX(26px);}</style><div><span class='content-title'>Etats des prises</span><div><div class='prise' id='p1'><label class='switch'><input type='checkbox' id='c1' onclick='swap()' {{{ischecked}}}><span class='slider round'></span></label><span>Details</span></div></div></div><script>function swap(){var xhr = new XMLHttpRequest();xhr.open('POST', '/swap1', true);xhr.send(null);}</script>";
String html_stat = "";
String html_connec = "<span>{{{isConnected}}}</span><form action='/submitConnectionForm'><input type='text' name='ssid' placeholder='SSID'/><input type='text' name='password' placeholder='password'/><input type='submit' value='Submit'/></form>";

// on appelle la bibliothèque qui gère le Wemos D1 mini
#include <ESP8266WiFi.h> 
#include <ESP8266HTTPClient.h>

// Gestion du Wifi
#include <ESP8266WebServer.h>
#include <DNSServer.h>
#include <ESP8266mDNS.h>
#include <WiFiClient.h> 

//Clock
int currSec = 0;
int currMin = 0;
int currHou = 0;
unsigned long prevTime = 0;
unsigned long diff = 0;
// Definition du WiFi 

bool val = false;
bool isConnected = false;

const char ssid[] = "Livebox-092d";
const char password[] = "wifieasy";
// const char password[] = "7e2a4769";

//google
String googleSheetKey = "";
String googleAPIKey = "AIzaSyDurvFbr7YphjCduCd0QxRq2nQ2l_IXjc4";

char *nomDuReseau = "Connectiprise"; // Nom du réseau wifi du petit bot
char *motDePasse = ""; // Mot de passe du réseau wifi du petit bot
ESP8266WebServer monServeur(80); 

void requestHandler(){
  monServeur.on("/", HTTP_GET, []() { 
    // redactionPageWeb();
    monServeur.send(200, "text/html", templateParser(html_main, "content", ""));
  });

  monServeur.on("/swap1", HTTP_POST, []() {
    val = !val;
    // val = (monServeur.arg(0) == "checked=1") ? true : false; a remettre pour le multi
    digitalWrite(14, val);
    monServeur.send(200, "text/html", "");
  });

  monServeur.on("/parametre", HTTP_GET, []() {
    monServeur.send(200, "text/html", templateParser(html_main, "content", templateParser(html_param, "ischecked" ,((val == true)? " checked " : "" ))));
  });

  monServeur.on("/statistique", HTTP_GET, [](){
    monServeur.send(200, "text/html", templateParser(html_main, "content", html_stat));
  });

  monServeur.on("/connection", HTTP_GET, [](){
    monServeur.send(200, "text/html", templateParser(html_main, "content", templateParser(html_connec, "isConnected" ,((isConnected == true)? "Vous etes connecte" : "Vous n etes pas connecte"))));    
  });

  monServeur.on("/submitConnectionForm", HTTP_POST, [](){

    String tmp = postParser(monServeur.arg(0), "ssid");
    char* test = new char[10];

    delete(test);

    monServeur.send(200, "text/html", "");    
  });

  monServeur.on("/updateDate", HTTP_POST, [](){
    currHou = (jsonParser(monServeur.arg(0), "hours")).toInt();
    currMin = (jsonParser(monServeur.arg(0), "minutes")).toInt();
    currSec = (jsonParser(monServeur.arg(0), "seconds")).toInt();
    Serial.println("time updated");
    monServeur.send(200, "text/html", "");
  });

  monServeur.on("/debug/time", HTTP_POST, [](){
    Serial.println(currHou + String(" : ") + currMin + String(" : ") + currSec);
    monServeur.send(200, "text/html", "");    
  });

  
}

void configDuWifi(){ // Fonction de configuratio du Wifi
  WiFi.mode(WIFI_AP); // le wemos est en mode "Point d'Accès" (il déploie un réseau wifi)
  WiFi.softAP(nomDuReseau, motDePasse, 2); // on démarre le "Point d'Accès".
  MDNS.begin(nomDuReseau); // gérer les DNS ce qui rendra votre petit bot accessible
  MDNS.addService("http", "tcp", 80); // via http://nomDuReseau.local
  IPAddress monIP = WiFi.softAPIP(); // on récupère l'adresse IP du petit Bot
  requestHandler();
  monServeur.begin(); //Démarrage du monServeur
  return; // on retourne à l'endroit ou la fonction a été appelée.
}

void connectWifi(){
    Serial.print("Connecting to ");
    Serial.println(ssid);

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("");
    Serial.println("WiFi connected");
    isConnected = true;
}

void beginServer(){
  requestHandler();
  monServeur.begin();

      // Print the IP address
  Serial.print("Server is open\nUse this URL : ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
}


void setup(){
  Serial.begin(115200);
  // configDuWifi();
  // monServeur.stop();
  connectWifi();
  pinMode(14, OUTPUT);
  digitalWrite(14, 0);

  //test google sheet api v4
  // Serial.println("Debut de la requete");
  // HTTPClient http;
  // http.begin("https://sheets.googleapis.com/v4/spreadsheets/1pKn7I-hutNm8xxxcroU5slIk2geOH_B5IETeXtLjRn4/values/A1:A1");
  // Serial.println(http.GET());
  // String payload = http.getString();
  // Serial.println(payload);
  // Serial.println("fin de la requete");
  // http.end();

  beginServer();
}

void loop(){
  unsigned long temp = millis();
  diff += temp - prevTime;
  if(diff > 1000){
    currSec++;
    diff -= 1000;
  }
  if(currSec > 59){
    currMin++;
    currSec=0;
  }
  if(currMin > 59){
    currHou++;
    currMin=0;
  }
  if(currHou > 23){
    currHou=0;
  }
  prevTime = temp;


  monServeur.handleClient();
  monServeur.send(200, "text/event-stream", "coucou");
}

String templateParser(String s, String key, String t){
  while (s.indexOf("{{{" + key + "}}}") != -1){
    int b = s.indexOf("{{{" + key + "}}}");
    int e = b + ("{{{" + key + "}}}").length();
    s = s.substring(0, b) + t + s.substring(e);
  }
  return s;
}

String jsonParser(String s, String key){
  int pos = s.indexOf('"' + key + '"');
  pos += key.length() + 4;
  int fin = s.indexOf('"', pos);
  String res = s.substring(pos, fin);
  return res;
}
String postParser(String s, String key){
  int pos = s.indexOf(key + '=');
  pos += key.length() + 2;
  int fin = s.indexOf('&', pos);
  fin = (fin == -1) ? s.indexOf('\0', pos) : fin;
  String res = s.substring(pos, fin);
  return res;
}