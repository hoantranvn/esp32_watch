#include <SPI.h>
#include <WiFi.h>
#include <time.h>
#include"draw_watch.h"

// Thông tin WiFi
const char* ssid = "Tiem";
const char* password = "11111111";

// Thông tin NTP Server
const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = 25200;  // UTC+7 (Việt Nam)
const int   daylightOffset_sec = 0;

// Biến lưu thời gian
int hour, minute, second;
int lastSecond = -1;




void setup() {
  Serial.begin(115200);
  
  // Kết nối WiFi để lấy thời gian
  Serial.print("Đang kết nối WiFi");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nĐã kết nối WiFi");

  // Cấu hình thời gian
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
 
  // Thêm số giờ

  watchInit();
}





void loop() {
  // Cập nhật thời gian
  updateTime();

  // Chỉ vẽ lại khi giây thay đổi
  if (second != lastSecond) {
    // Vẽ kim đồng hồ
    drawClockHands(hour, minute, second);
    // DisplayBuffers();
    
    lastSecond = second;
  }

  delay(100);
}

void updateTime() {
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    Serial.println("Không thể lấy thời gian");
    return;
  }

  hour = timeinfo.tm_hour % 12;
  minute = timeinfo.tm_min;
  second = timeinfo.tm_sec;
}
