//Code HTML/CS/JS du site web
String html_main = "<!DOCTYPE html><html><head><meta charset='UTF-8' name='viewport' content='width=device-width, initial-scale=1'><title>Connectiprise</title><style>body{background-color: #3D3D3D;color: white;font-family: Arial, Helvetica, sans-serif;}.side-panel{background-color: #1D1D1D;position: absolute;top: 0px;left: 0px;height: 100%;width: 150px;}.name{font-size: 20px;width: 100%;margin-top: 10px;text-align: center;}.separator{width: 100%;height: 1px;margin-top: 10px;background-color: white;}.side-menu{padding-left: 0px;width: 100%;}.side-menu > li {text-align: center;list-style-type: none;list-style-position: inside;height: 30px;}.side-menu > li > a{color: inherit;vertical-align: middle;text-decoration: none;}.side-menu :hover{background-color: #2d2d2d;}.content-container{margin-left: 160px;margin-top: 10px;}</style><head><body><div class='side-panel'><div class='name'>Connectiprise</div><div class='separator'></div><ul class='side-menu'><li><a href='/connection'>Connection</a></li><li><a href='/parametre'>Parametres</a></li> </ul></div><!-- <iframe class='content-container' src='./parametre.html' style="width:1000px;height:600px;"></iframe> --><div class='content-container'>{{{content}}}</div><script>var date = new Date();var time = {hours: date.toTimeString().slice(0,2), minutes: date.toTimeString().slice(3,5), seconds: date.toTimeString().slice(6,8)};var xhr = new XMLHttpRequest();xhr.open('POST', '/updateDate', true);xhr.send(JSON.stringify(time));</script></body></html>";
String html_param = "<style>.content-title{color: white;}.switch {position: relative;display: inline-block;width: 60px;height: 34px;}.switch input {display:none;}.slider {position: absolute;cursor: pointer;top: 0;left: 0;right: 0;bottom: 0;background-color: #BB2500;-webkit-transition: .4s;transition: .4s;}.slider:before {position: absolute;content: '';height: 26px;width: 26px;left: 4px;bottom: 4px;background-color: white;-webkit-transition: .4s;transition: .4s;}input:checked + .slider {background-color: #408F00;}input:focus + .slider {box-shadow: 0 0 1px #2196F3;}input:checked + .slider:before {-webkit-transform: translateX(26px);-ms-transform: translateX(26px);transform: translateX(26px);}.prise{float: left;}.priseParent{height: 34px;width: 100%;margin: 10px;}.modal {display: none; /* Hidden by default */position: fixed; /* Stay in place */z-index: 1; /* Sit on top */left: 0;top: 0;width: 100%; /* Full width */height: 100%; /* Full height */overflow: auto; /* Enable scroll if needed */background-color: rgb(0,0,0); /* Fallback color */background-color: rgba(0,0,0,0.4); /* Black w/ opacity */-webkit-animation-name: fadeIn; /* Fade in the background */-webkit-animation-duration: 0.4s;animation-name: fadeIn;animation-duration: 0.4s}/* Modal Content */.modal-content {position: fixed;bottom: 0;background-color: #fefefe;width: 100%;-webkit-animation-name: slideIn;-webkit-animation-duration: 0.4s;animation-name: slideIn;animation-duration: 0.4s}@-webkit-keyframes slideIn {from {bottom: -300px; opacity: 0} to {bottom: 0; opacity: 1}}@keyframes slideIn {from {bottom: -300px; opacity: 0}to {bottom: 0; opacity: 1}}@-webkit-keyframes fadeIn {from {opacity: 0} to {opacity: 1}}@keyframes fadeIn {from {opacity: 0} to {opacity: 1}}</style><!-- The Modal --><div id='myModal' class='modal'><div class='modal-content'><form action='/setRule' class='ruler'><input name='num' id='idInput' style='display:none'/><input type='time' name='min'/><input type='time' name='max'/><input type='submit' value='Valider'></form></div></div><div><span class='content-title'>Etats des prises</span><div class='priseParent'><div class='prise'><label class='switch'><input type='checkbox' onclick='swap(event, 0)' {{{ischecked0}}}><span class='slider round'></span></label></div><button onclick='openParam(0)'>+</button></div><div class='priseParent'><div class='prise'><label class='switch'><input type='checkbox' onclick='swap(event, 1)' {{{ischecked1}}}><span class='slider round'></span></label></div><button onclick='openParam(1)'>+</button></div><div class='priseParent'><div class='prise'><label class='switch'><input type='checkbox' onclick='swap(event, 2)' {{{ischecked2}}}><span class='slider round'></span></label></div><button onclick='openParam(2)'>+</button></div><div class='priseParent'><div class='prise'><label class='switch'><input type='checkbox' onclick='swap(event, 3)' {{{ischecked3}}}><span class='slider round'></span></label></div><button onclick='openParam(3)'>+</button></div><div class='priseParent'><div class='prise'><label class='switch'><input type='checkbox' onclick='swap(event, 4)' {{{ischecked4}}}><span class='slider round'></span></label></div><button onclick='openParam(4)'>+</button></div><div class='priseParent'><div class='prise'><label class='switch'><input type='checkbox' onclick='swap(event, 5)' {{{ischecked5}}}><span class='slider round'></span></label></div><button onclick='openParam(5)'>+</button></div></div><script>var modal = document.getElementById('myModal');var modalContent = document.getElementById('modal-content');function openParam(i){document.getElementById('idInput').value = i;modal.style.display = 'block';}// When the user clicks anywhere outside of the modal, close itwindow.onclick = function(event) {if (event.target == modal) {modal.style.display = 'none';}}function swap(e, i){var payload = {num : i, val : e.target.checked};console.log(payload);var xhr = new XMLHttpRequest();xhr.open('POST', '/swap', true);xhr.send(JSON.stringify(payload));}</script>";
String html_connec = "<span>{{{isConnected}}}</span><form action='/submitConnectionForm'><input type='text' name='ssid' placeholder='SSID'/><input type='text' name='password' placeholder='password'/><input type='submit' value='Submit'/></form><form action='/submitSheetKey'><input type='text' name='key' placeholder='Google Sheet Key'/><input type='submit' value='Submit'/></form>";

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

//Etats des relais commandant les prises
bool plugIsOn[6] = {false, false, false, false, false, false};
//
int plugPins[6] = {14,12,5,4,0,2};
//Etats de la connection au wifi
bool isConnected = false;
//ssid et mot de passe du wifi auquel on veut ce connecter
String ssid, password;

//google
String googleSheetKey = "";
String googleAPIKey = "AIzaSyDurvFbr7YphjCduCd0QxRq2nQ2l_IXjc4";

char *nomDuReseau = "Connectiprise"; // Nom du réseau wifi du petit bot
char *motDePasse = ""; // Mot de passe du réseau wifi du petit bot
ESP8266WebServer monServeur(80); //Creation objet serveur

//Gestion des requetes
void requestHandler(){
  //page de base
  monServeur.on("/", HTTP_GET, []() { 
    monServeur.send(200, "text/html", templateParser(html_main, "content", "")); //Envoi de la requete
  });

  //switch etats des relais
  monServeur.on("/swap", HTTP_POST, []() {
    Serial.println(monServeur.arg(0));
    int plugID = jsonParser(monServeur.arg(0), "num").toInt(); //recuperation du numero du relais à changer
    plugIsOn[plugID] = (jsonParser(monServeur.arg(0), "val") == "true") ? true : false; //changement etat du relais
    digitalWrite(plugPins[plugID], plugIsOn[plugID]);//-------------------------------------------------------------------------------------------------------pas fini
    monServeur.send(200, "text/html", "");
  });

  //page des parametres
  monServeur.on("/parametre", HTTP_GET, []() {
    monServeur.send(200, "text/html", 
      templateParser(html_main, "content", 
      templateParser(templateParser(templateParser(templateParser(templateParser(templateParser(html_param, 
      "ischecked5" ,((plugIsOn[5] == true)? " checked " : "" )), 
      "ischecked4" ,((plugIsOn[4] == true)? " checked " : "" )),
      "ischecked3" ,((plugIsOn[3] == true)? " checked " : "" )),
      "ischecked2" ,((plugIsOn[2] == true)? " checked " : "" )),
      "ischecked1" ,((plugIsOn[1] == true)? " checked " : "" )),
      "ischecked0" ,((plugIsOn[0] == true)? " checked " : "" ))));
  });

  //page de connection
  monServeur.on("/connection", HTTP_GET, [](){
    monServeur.send(200, "text/html", templateParser(html_main, "content", templateParser(html_connec, "isConnected" ,((isConnected == true)? "Vous etes connecte" : "Vous n etes pas connecte"))));    
  });

  //recuperation formulaire de connection à un wifi
  monServeur.on("/submitConnectionForm", HTTP_GET, [](){
    ssid = monServeur.arg(0);
    password = monServeur.arg(1);

    monServeur.send(200, "text/html", templateParser(html_main, "content", templateParser(html_connec, "isConnected" ,((isConnected == true)? "Vous etes connecte" : "Vous n etes pas connecte"))));    
    connectWifi();
  });

  //mise a jour de l'heure
  monServeur.on("/updateDate", HTTP_POST, [](){
    currHou = (jsonParser(monServeur.arg(0), "hours")).toInt();
    currMin = (jsonParser(monServeur.arg(0), "minutes")).toInt();
    currSec = (jsonParser(monServeur.arg(0), "seconds")).toInt();
    Serial.println("time updated");
    monServeur.send(200, "text/html", "");
  });

  //affichage de l'heure
  monServeur.on("/debug/time", HTTP_POST, [](){
    Serial.println(currHou + String(" : ") + currMin + String(" : ") + currSec);
    monServeur.send(200, "text/html", "");    
  });

  //Recuperation de l'id d'un tableur google
  monServeur.on("/submitSheetKey", HTTP_GET, [](){
    googleAPIKey = monServeur.arg(0);
    monServeur.send(200, "text/html", templateParser(html_main, "content", templateParser(html_connec, "isConnected" ,((isConnected == true)? "Vous etes connecte" : "Vous n etes pas connecte"))));    
  });

  monServeur.on("/setRule", HTTP_GET, [](){
    Serial.println(monServeur.arg(0));
    monServeur.send(200, "text/html", 
      templateParser(html_main, "content", 
      templateParser(templateParser(templateParser(templateParser(templateParser(templateParser(html_param, 
      "ischecked5" ,((plugIsOn[5] == true)? " checked " : "" )), 
      "ischecked4" ,((plugIsOn[4] == true)? " checked " : "" )),
      "ischecked3" ,((plugIsOn[3] == true)? " checked " : "" )),
      "ischecked2" ,((plugIsOn[2] == true)? " checked " : "" )),
      "ischecked1" ,((plugIsOn[1] == true)? " checked " : "" )),
      "ischecked0" ,((plugIsOn[0] == true)? " checked " : "" ))));
  });
}

void configDuWifi(){ // Fonction de configuratio du Wifi
  WiFi.mode(WIFI_AP); // le wemos est en mode "Point d'Accès" (il déploie un réseau wifi)
  WiFi.softAP(nomDuReseau, motDePasse, 2); // on démarre le "Point d'Accès".
  MDNS.begin(nomDuReseau); // gérer les DNS ce qui rendra votre petit bot accessible
  MDNS.addService("http", "tcp", 80); // via http://nomDuReseau.local
  IPAddress monIP = WiFi.softAPIP(); // on récupère l'adresse IP du petit Bot
  Serial.print("Server is open\nUse this URL : ");
  Serial.print("http://");
  Serial.print(monIP);
  Serial.println("/");
}

void connectWifi(){
    Serial.print("Connecting to ");
    Serial.println(ssid);


    WiFi.begin(ssid.c_str(), password.c_str()); //connection au reseau wifi

    //marche pas
    // IPAddress ip(192,168,2,1);   
    // IPAddress gateway(192,168,1,254);   
    // IPAddress subnet(255,255,255,0);   
    // WiFi.config(ip, gateway, subnet);
   
    while (WiFi.status() != WL_CONNECTED) { //tant que le wemos n'est pas connecté, affiche un point
        delay(500);
        Serial.print(".");
    }
    Serial.println("");
    Serial.println("WiFi connected");
      // Print the IP address
    Serial.print("Server is open\nUse this URL : ");
    Serial.print("http://");
    Serial.print(WiFi.localIP());
    Serial.println("/");
    isConnected = true;
}

void beginServer(){
  requestHandler(); //Gestion des requetes
  monServeur.begin(); //demarage du serveur
  
  configDuWifi();
}


void setup(){
  Serial.begin(115200);
  Serial.println("");

  //reset sorties relais
  for(int i = 0; i < 6; i++){
    pinMode(plugPins[i], OUTPUT);
    digitalWrite(plugPins[i], 0);
  }

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
  //Mise a jour de l'heure
  unsigned long temp = millis();
  diff += temp - prevTime;
  if(diff > 1000){ //seconde
    currSec++;
    diff -= 1000;
  }
  if(currSec > 59){//minure
    currMin++;
    currSec=0;
  }
  if(currMin > 59){//heures
    currHou++;
    currMin=0;
  }
  if(currHou > 23){//jour
    currHou=0;
  }
  prevTime = temp;


  monServeur.handleClient();
}

//parse code html pour ajouter des templates dedans
String templateParser(String s, String key, String t){
  while (s.indexOf("{{{" + key + "}}}") != -1){
    int b = s.indexOf("{{{" + key + "}}}");
    int e = b + ("{{{" + key + "}}}").length();
    s = s.substring(0, b) + t + s.substring(e);
  }
  return s;
}

//parse json pour les requetes post
String jsonParser(String s, String key){
  int pos = s.indexOf('"' + key + '"');
  pos += key.length() + 3;
  int fin = s.indexOf(',', pos);
  if(fin == -1)
    fin = s.indexOf("}", pos);

  if(s.charAt(fin-1) == '"'){
    pos++;
    fin--;
  }
  String res = s.substring(pos, fin);
  return res;
}
// String queryParser(String s, String key){
//   int pos = s.indexOf(key + '=');
//   pos += key.length() + 2;
//   int fin = s.indexOf('&', pos);
//   fin = (fin == -1) ? s.indexOf('\0', pos) : fin;
//   String res = s.substring(pos, fin);
//   return res;
// }