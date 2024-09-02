#define TINY_GSM_MODEM_SIM800
#include <TinyGsmClient.h>
#include <SoftwareSerial.h>

#define MODEM_RST            5
#define MODEM_PWRKEY         4
#define MODEM_POWER_ON       23
#define MODEM_TX             17  // Pino de TX do ESP32 (conectado ao RX do módulo GSM)
#define MODEM_RX             16  // Pino de RX do ESP32 (conectado ao TX do módulo GSM)
#define MODEM_BAUD           9600
#define SerialMon            Serial

SoftwareSerial SerialAT(MODEM_RX, MODEM_TX);
TinyGsm modem(SerialAT);

void setup() {
  SerialMon.begin(9600);
  delay(10);

  // Configurações dos pinos do modem (dependendo do modelo, alguns podem não ser necessários)
  pinMode(MODEM_PWRKEY, OUTPUT);
  pinMode(MODEM_POWER_ON, OUTPUT);
  pinMode(MODEM_RST, OUTPUT);

  SerialMon.println("Iniciando o modem...");
  SerialAT.begin(MODEM_BAUD);
  modem.restart();

  String modemInfo = modem.getModemInfo();
  SerialMon.print("Modem: ");
  SerialMon.println(modemInfo);

  int16_t signal = modem.getSignalQuality();
  SerialMon.print("Qualidade do sinal: ");
  SerialMon.println(signal);

  SerialMon.print("Conectando à rede...");
  if (!modem.waitForNetwork()) {
    SerialMon.println(" Falha ao conectar à rede");
    while (true);
  }
  SerialMon.println(" Conectado à rede com sucesso!");

  SerialMon.println("Enviando SMS...");
  modem.sendSMS("+5511999999999", "Teste de envio de SMS com ESP32 e módulo GSM");
  SerialMon.println("SMS enviado com sucesso!");
}

void loop() {
}