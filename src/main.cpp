#include <Arduino.h>

#include <SPI.h>
#include <LoRa.h>
#include <Wire.h>

/// CUSTOM HEADERS ///

#include "variables.h"
#include "oled_definitions.h"

void setup()
{
  Serial.begin(9600);

  pinMode(led_message_indicator, OUTPUT);

  while (!Serial)
    ;
  Serial.println("LoRa Receiver");
  if (!LoRa.begin(433E6))
  {
    Serial.println("Starting LoRa failed!");
    while (1)
      ;
  }

  Serial.println(message_counter);

  // initialize and clear display
  display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR);
  display.clearDisplay();
  display.display();

  // display a line of text
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(5, 0);
  display.print("LoRa Pager");
  display.setCursor(49, 10);
  display.print("0 Messages");
  // update display with all of the above graphics
  display.display();
}

void loop()
{
  button_power_count();
  receive_lora_message();
}

void receive_lora_message()
{
  if ((power_btn_count % 2) != 0)

  {
    power_status = true;
    if (power_status)
    {

      // try to parse packet
      int packetSize = LoRa.parsePacket();
      if (packetSize)
      {
        // received a packet
        Serial.print("Received packet '");

        // read packet
        while (LoRa.available())
        {
          lora_data_recevied = LoRa.read();
          Serial.print((char)lora_data_recevied);
          //      Serial.print((char)LoRa.read());
          (lora_data_recevied == '7') ? update_message_on_display() : led_indicator_off();
        }

        //         print RSSI of packet
        Serial.print("' with RSSI ");
        Serial.println(LoRa.packetRssi());
      }
    }
  }
}

int button_power_count()
{
  button_states();

  if (power_on_btn_value != last_power_on_btn_value)
  {
    if (power_on_btn_value == 1)
    {
      power_btn_count++;
      //      silent_btn_count = 0;
    }
    delay(10);
  }
  last_power_on_btn_value = power_on_btn_value;

  if (power_btn_count > 50)
  {
    power_btn_count = 0;
  }
  //    Serial.print("Power Count: ");
  //    Serial.println(power_btn_count);
}

void button_states()
{
  power_on_btn_value = digitalRead(power_on_btn);
  //  Serial.println(power_on_btn_value);
}

void led_indicator_on()
{
  digitalWrite(led_message_indicator, HIGH);
}

void led_indicator_off()
{
  digitalWrite(led_message_indicator, LOW);
}

void update_message_on_display()
{
  display.clearDisplay();
  display.display();
  // display a line of text
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(5, 0);
  display.print("LoRa Pager");
  display.setCursor(49, 10);
  display.print("Alert on Gate A");
  // update display with all of the above graphics
  display.display();
}
