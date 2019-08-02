// pin declarations
const int power_on_btn = 4;
const int led_message_indicator = 5;
const int buzzer_pin = 9;

// Variables
int lora_received_data = 0;
int power_on_btn_value = 0;
int buzzer_pmw_val = 0;

int power_btn_count = 0;

bool power_status = false;
int power_on_btn_value = 0;
int last_power_on_btn_value = 0;
