# include <stdio.h>
# include <wiringPi.h>
#include <fcntl.h>
#include <fstream>

#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
using namespace std;

/*--------------------------------*/
struct hx711_pin {
    int SCK;
    int SDA;
    int EN;                        
    int calibration;            
    int coefficient;            
    int weight;                    
    unsigned long value;        
};

void set_pin(struct hx711_pin* value) {
    value->SCK = 22;
    value->SDA = 21;
    value->EN = 1;
    value->coefficient = 380;
}

void init_pin(struct hx711_pin* value) {
    pinMode(value->SCK, OUTPUT);
    pinMode(value->SDA, INPUT);
    pullUpDnControl(value->SDA, PUD_UP);
}

void start(struct hx711_pin* value) {
    int i;
    int n;
    digitalWrite(value->SCK, LOW);       
    while (digitalRead(value->SCK));
    value->value = 0;                   
    while (digitalRead(value->SDA));        
    value->value = 0;
    delay(10);
    for (i = 0; i < 24; i++) {                     //24
        digitalWrite(value->SCK, HIGH);
        while (0 == digitalRead(value->SCK))delay(1000);
        value->value = value->value * 2;
        digitalWrite(value->SCK, LOW);
        while (digitalRead(value->SCK));
        if (digitalRead(value->SDA))
            value->value = value->value + 1;
    }
    digitalWrite(value->SCK, HIGH);                //25
    digitalWrite(value->SCK, LOW);
    if ((value->EN == 1) && (value->value < 25000))
    {
        value->EN = 0;
        value->calibration = value->value;
    }
    else {
        n = (value->value - value->calibration) / value->coefficient;
    }
    if ((n < 5000)&&(n != 398)&&(n != 397)) {
        value->weight = n;
        n = 0;
    }
    printf("Weight is %d g\n", value->weight);
    ofstream outfile;
    outfile.open("/home/pi/RefrigeratorManager/weight.txt", ios::out | ios::trunc);
    outfile << value->weight;
    outfile.close();

}

/*-----------------Main-----------------*/
int setup(struct hx711_pin* value) {
    if (wiringPiSetup() == -1)return 1;
    set_pin(value);
    init_pin(value);
    return 0;
}

struct Type {

	char type[13];
};

const int N = 2;

void loop(struct hx711_pin* value) {
    while(true){
        start(value);}
}

int main(void) {
    struct hx711_pin value;
    if (0 == setup(&value))
        loop(&value);
    return 0;
}


