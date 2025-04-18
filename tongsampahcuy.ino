#include <Servo.h>         // Library untuk mengontrol motor servo
Servo servo;               // Membuat objek servo

int angle = 10;            // Sudut awal servo

// Deklarasi pin untuk sensor ultrasonik
const int trigPin = 12;    // Pin TRIG sensor HC-SR04 dihubungkan ke pin digital 12 Arduino
const int echoPin = 11;    // Pin ECHO sensor HC-SR04 dihubungkan ke pin digital 11 Arduino

// Variabel untuk menyimpan hasil pengukuran jarak
long duration;
int distance;

void setup() {
  servo.attach(8);         // Menghubungkan servo ke pin digital 8 Arduino
  servo.write(angle);      // Mengatur posisi awal servo

  pinMode(trigPin, OUTPUT); // Mengatur trigPin sebagai output
  pinMode(echoPin, INPUT);  // Mengatur echoPin sebagai input
  Serial.begin(9600);       // Memulai komunikasi serial dengan baud rate 9600
}

void loop() {
  // Membersihkan sinyal pada trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // Mengirimkan sinyal ultrasonic selama 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Menghitung durasi pantulan suara
  duration = pulseIn(echoPin, HIGH);

  // Menghitung jarak berdasarkan waktu tempuh suara (cm)
  distance = duration * 0.034 / 2;

  // Menampilkan jarak di Serial Monitor
  Serial.print("Jarak: ");
  Serial.print(distance);
  Serial.println(" cm");

  delay(10); // Delay pendek agar pembacaan stabil

  // Jika jarak < 100 cm, buka tutup tong sampah
  if (distance < 100) {
    servo.write(180);      // Buka tutup (putar servo ke 180 derajat)
    delay(4000);           // Tunggu selama 4 detik
  } else {
    servo.write(0);        // Tutup kembali (putar servo ke 0 derajat)
  }
}
