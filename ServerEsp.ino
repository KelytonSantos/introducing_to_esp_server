#include <WebServer.h>
#include <WiFi.h>

const char *ssid = "MultilaserPRO_ZTE_2.4G_TDEDEd";
const char *password = "PSRMFKfR";

WebServer server(80);

String calc(String data);
void setup() {
	Serial.begin(115200);
	WiFi.begin(ssid, password);

	while(WiFi.status() != WL_CONNECTED){
		delay(1000);
		Serial.println("Conectando ao Wi-Fi...");
	}

	Serial.println("Conectado ao Wi-Fi!");
	Serial.print("Endereço IP do ESP32: ");
	Serial.println(WiFi.localIP());

	server.on("/dado", HTTP_POST, [](){
		String data = server.arg("dado");
		String result = "Calculo do numero " + data + " tratado e igual a: " + calc(data);
		server.send(200, "text/plain", result);

		if(server.client().connected()){
			Serial.println("Dados enviados com sucesso!");
		} 
		else {
			Serial.println("Erro ao enviar dados.");
		}
	});

	server.begin();

}

void loop() {
	server.handleClient();
}


String calc(String data){
	unsigned d = data.toInt();
	unsigned r = d*100;
	String ret = String(r);
	
	return ret;
}



