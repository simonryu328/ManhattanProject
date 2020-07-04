#include "util_lcd.h"

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void lcd_print(String s)
{
  // Displays string s on the screen
  display.clearDisplay();
  display.setCursor(0,0);
  display.println(s);
  display.display();
}

void lcd_print_number(double n)
{
  // Displays number n on the screen
  display.clearDisplay();
  display.setCursor(0,0);
  display.println(n);
  display.display();
}

void lcd_print_str_number(String s, double n)
{
  display.clearDisplay();
  // Displays string s on the screen
  display.setCursor(0,0);
  display.println(s);
  // Displays number n in the next line on the screen
  display.setCursor(0,10);
  display.println(n);
  display.display();
}

void lcd_init()
{
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
 
  // Displays Adafruit logo by default. call clearDisplay immediately if you don't want this.
  display.display();
  delay(500);

  // Displays "Hello world!" on the screen
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,0);
  display.println("LCD initialized!");
  display.display();
  delay(500);
}

void lcd_print_array(int id, volatile uint32_t *sample) 
{
  display.clearDisplay();
  char sample_value_str[256];

  sprintf(sample_value_str, "%d: %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d", id,
    int(sample[0]), int(sample[1]), int(sample[2]), int(sample[3]), int(sample[4]), int(sample[5]) ,int(sample[6]), int(sample[7]), int(sample[8]),
    int(sample[9]), int(sample[10]), int(sample[11]), int(sample[12]), int(sample[13]), int(sample[14]), int(sample[15]));
  lcd_print(sample_value_str);

}