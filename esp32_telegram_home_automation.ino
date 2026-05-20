#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>

const char* ssid = "YOUR_WIFI_NAME";
const char* password = "YOUR_WIFI_PASSWORD";

#define BOTtoken "YOUR_BOT_TOKEN"
#define CHAT_ID "YOUR_CHAT_ID"

WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);

#define RELAY1 4
#define RELAY2 5
#define RELAY3 18
#define RELAY4 19

#define DOOR_SENSOR 27

bool lastDoorState = HIGH;

unsigned long bot_lasttime;
const unsigned long BOT_MTBS = 1000;

void setup() {

  Serial.begin(115200);

  pinMode(RELAY1, OUTPUT);
  pinMode(RELAY2, OUTPUT);
  pinMode(RELAY3, OUTPUT);
  pinMode(RELAY4, OUTPUT);

  pinMode(DOOR_SENSOR, INPUT_PULLUP);

  digitalWrite(RELAY1, HIGH);
  digitalWrite(RELAY2, HIGH);
  digitalWrite(RELAY3, HIGH);
  digitalWrite(RELAY4, HIGH);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }

  client.setInsecure();

  bot.sendMessage(CHAT_ID,
                  "ESP32 HOME AUTOMATION ONLINE",
                  "");
}

void handleNewMessages(int numNewMessages) {

  for (int i = 0; i < numNewMessages; i++) {

    String chat_id = String(bot.messages[i].chat_id);
    String text = bot.messages[i].text;

    if (text == "/relay1_on") {
      digitalWrite(RELAY1, LOW);
      bot.sendMessage(chat_id, "Relay 1 ON", "");
    }

    if (text == "/relay1_off") {
      digitalWrite(RELAY1, HIGH);
      bot.sendMessage(chat_id, "Relay 1 OFF", "");
    }

    if (text == "/relay2_on") {
      digitalWrite(RELAY2, LOW);
      bot.sendMessage(chat_id, "Relay 2 ON", "");
    }

    if (text == "/relay2_off") {
      digitalWrite(RELAY2, HIGH);
      bot.sendMessage(chat_id, "Relay 2 OFF", "");
    }

    if (text == "/relay3_on") {
      digitalWrite(RELAY3, LOW);
      bot.sendMessage(chat_id, "Relay 3 ON", "");
    }

    if (text == "/relay3_off") {
      digitalWrite(RELAY3, HIGH);
      bot.sendMessage(chat_id, "Relay 3 OFF", "");
    }

    if (text == "/relay4_on") {
      digitalWrite(RELAY4, LOW);
      bot.sendMessage(chat_id, "Relay 4 ON", "");
    }

    if (text == "/relay4_off") {
      digitalWrite(RELAY4, HIGH);
      bot.sendMessage(chat_id, "Relay 4 OFF", "");
    }
  }
}

void loop() {

  bool currentDoorState = digitalRead(DOOR_SENSOR);

  if (currentDoorState != lastDoorState) {

    if (currentDoorState == LOW) {

      bot.sendMessage(CHAT_ID,
                      "DOOR OPENED",
                      "");

    } else {

      bot.sendMessage(CHAT_ID,
                      "DOOR CLOSED",
                      "");
    }

    lastDoorState = currentDoorState;

    delay(500);
  }

  if (millis() > bot_lasttime + BOT_MTBS) {

    int numNewMessages =
      bot.getUpdates(bot.last_message_received + 1);

    while (numNewMessages) {

      handleNewMessages(numNewMessages);

      numNewMessages =
        bot.getUpdates(bot.last_message_received + 1);
    }

    bot_lasttime = millis();
  }
}
