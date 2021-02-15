// Hello World to sweep a servo through its full range
 
#include "mbed.h"
#include "rtos/rtos.h"
#include <Servo.h>

//static BufferedSerial serial_port(PA_2, PA_3, 9600); // TX, RX

#define BLINKING_RATE 20

//FileHandle *mbed::mbed_override_console(int fd)
//{
//    return &serial_port;
//}
//DigitalOut led(LED_BUILTIN);
Servo myservo(PB_4);
 
int main() {
    // Tested servo:
    // HiTec HS-322HD.
    // 0.19sec/60° for No-Load Speed (4.8V).
    // Found pulse width by increasing ms until servo made a whirring noise.
    // 2.39ms pulse width, max 100 degrees from center.
    // Note: The min and max are actually different.
    // In this specific case the max goes farther than the min.
    // This servo cannot travel to the farthest part of the min.
    // The code does not take that into account as the range is the same for min and max.
    // 0.00089 + 0.0015 = 0.00239
    myservo.calibrate(0.00089, 100);

    while (1) {
        for(float p=0; p<=1.0; p += 0.1) {
            //printf("p*100 ~= %i\r\n", int(p*100));
            myservo = p;
            ThisThread::sleep_for(BLINKING_RATE);
        }
        ThisThread::sleep_for(5000);
        for(float p=1.0; p>=0.0; p -= 0.1) {
            //printf("p*100 ~= %i\r\n", int(p*100));
            myservo = p;
            ThisThread::sleep_for(BLINKING_RATE);
        }
        ThisThread::sleep_for(5000);
    }
}