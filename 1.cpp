// ... (جميع مكتباتك الحالية مثل ESP8266WiFi.h, SoftwareSerial.h, إلخ)
#include <ESP8266WebServer.h> // <-- أضف هذه المكتبة الجديدة

// ========== إعدادات خادم الويب ==========
ESP8266WebServer server(80); // إنشاء خادم ويب على المنفذ 80

// ... (باقي تعريفاتك مثل ssid, password, متغيرات النظام تبقى كما هي)

// ========== دوال مساعدة (حافظ على دوالك الحالية: initDisplay, initSIM, sendSMS, updateDisplay, showMessage) ==========
// ...

// ========== دالة جديدة لإرسال الحالة بصيغة JSON ==========
void sendStatusAsJSON() {
  // نسمح لأي موقع بالاتصال بنا (لحل مشكلة CORS)
  server.sendHeader("Access-Control-Allow-Origin", "*");
  
  // نحضر البيانات في كائن JSON
  StaticJsonDocument<200> doc;
  doc["internet"] = internetConnected ? "online" : "offline"; // حالة الإنترنت
  doc["smsCount"] = smsCount; // عدد الرسائل المرسلة
  // doc["lastCheck"] = millis(); // يمكنك إضافة المزيد من البيانات إن أردت

  String jsonResponse;
  serializeJson(doc, jsonResponse); // تحويل الكائن إلى نص JSON
  
  server.send(200, "application/json", jsonResponse); // إرسال الرد
  Serial.println("JSON response sent: " + jsonResponse);
}

// ========== دالة الإعدادات (setup) المعدلة ==========
void setup() {
  Serial.begin(115200);
  delay(1000);
  
  // ... (تهيئة الشاشة، SIM، والاتصال بالواي فاي كما في كودك الأصلي)
  
  // بعد الاتصال بالواي فاي، أضف هذه الأوامر:
  // تعريف المسار الذي سيستمع إليه الخادم
  server.on("/status", HTTP_GET, sendStatusAsJSON);
  
  // تشغيل الخادم
  server.begin();
  Serial.println("HTTP server started");
  Serial.print("Open browser to: http://");
  Serial.println(WiFi.localIP()); // اطبع عنوان IP في الشاشة التسلسلية
}

// ========== الحلقة الرئيسية (loop) المعدلة ==========
void loop() {
  server.handleClient(); // <-- أمر مهم جداً! يجب إضافته ليستمع للطلبات
  // ... (باقي الكود الخاص بفحص الإنترنت وإرسال الـ SMS يبقى كما هو)
}
