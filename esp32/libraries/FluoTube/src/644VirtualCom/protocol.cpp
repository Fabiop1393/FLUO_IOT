#include <Arduino.h>

#include "protocol.h"

//global
int servo_pos[32];

boolean isNumeric(String str) {
    unsigned int stringLength = str.length();
 
    if (stringLength == 0) {
        return false;
    }
 
    boolean seenDecimal = false;
 
    for(unsigned int i = 0; i < stringLength; ++i) {
        if (isDigit(str.charAt(i))) {
            continue;
        }
 
        if (str.charAt(i) == '.') {
            if (seenDecimal) {
                return false;
            }
            seenDecimal = true;
            continue;
        }
        return false;
    }
    return true;
}


String cmdBuild(String cmd, String args)
{
    String str = "@{cmd}%{args}$!" ;

    str.replace("{cmd}", cmd );
    str.replace("{args}", args );

    return str;
}

void VirtualdigitalWrite(int pin, int val)
{
    String args; 

    if (val == 0) //LOW 0x0
        args += '-';

    args += String(pin);

    SerialInternal.print( cmdBuild("dw", args) );

}

int VirtualdigitalRead(int pin) // no
{
    String args;

    args += String(pin); // handle eventually more args method

    SerialInternal.print( cmdBuild("dr", args) );

    // Read reply
    String rd = SerialInternal.readString();
    rd.replace("\r\n", "");

    return rd.toInt();
}

int VirtualanalogWrite(int pin, int val)
{
    String args;

    if (val > 255)
        val = 255;
    else if (val < 0)
        val = 0;

    args += String(pin); // handle eventually more args method
    args += '%' ;
    args += String(val) ;

    SerialInternal.print( cmdBuild("aw", args) );
}




int VirtualUseCase()
{
    String args = "";

    SerialInternal.print( cmdBuild("mode", args) );
        
    // Read reply -- MODE
    String rd = SerialInternal.readString();
    rd.replace("\r\n", "");

    //Serial.println("VirtualUseCase"); DBG
    //Serial.println(rd.toInt()); DBG

    return rd.toInt();
}

int VirtualStringSend(String data)
{
    SerialInternal.print( cmdBuild("string", data) );
}

void VirtualserialSend(String data)
{
    SerialInternal.print( cmdBuild("srs", data) ); // sr -> serial / s -> send
}

String VirtualSSID()
{
    String args = "";

    SerialInternal.print( cmdBuild("ssid", args) );
        
    // Read reply -- ACK
    String rd = SerialInternal.readString();
    rd.replace("\r\n", "");

    return rd;
}

String VirtualHOSTNAME()
{
    String args = "";

    SerialInternal.print( cmdBuild("host", args) );
        
    // Read reply -- ACK
    String rd = SerialInternal.readString();
    rd.replace("\r\n", "");

    return rd;
}

String VirtualPASSKEY()
{
    String args = "";

    SerialInternal.print( cmdBuild("key", args) );
        
    // Read reply -- ACK
    String rd = SerialInternal.readString();
    rd.replace("\r\n", "");

    return rd;
}

String VirtualRESTAPI()
{
    String args = "";

    SerialInternal.print( cmdBuild("rest", args) );
        
    // Read reply -- ACK
    String rd = SerialInternal.readString();
    rd.replace("\r\n", "");

    return rd;
}

void VirtualConnection(String tmp)
{
    //Serial.println(tmp); //dbg
    SerialInternal.print( cmdBuild("conn", tmp ));
}

String VirtualReadAvrMsg(String data){

    String rd = SerialInternal.readString();
    rd.replace("\r\n", "");
    //Serial.println("[VirtualReadAvrMsg]Mess ricevuto:"+rd+"\n");
    if(rd != "")SerialInternal.print( cmdBuild("ackToAVR", data) );

    return rd;
}

int VirtualMacADDR(String tmp)
{

    SerialInternal.print( cmdBuild("mac", tmp ));
    return 1;
}

int VirtualanalogRead(int pin) // no
{
    String args;

    args += String(pin); // handle eventually more args method

    SerialInternal.print( cmdBuild("ar", args) );

    // Read reply
    String rd = SerialInternal.readString();
    rd.replace("\r\n", "");

    return rd.toInt();
}

void VirtualpinMode(int pin, int val)
{
    String args; 

    if (val == 0) //LOW 0x0
        args += '-';

    args += String(pin);

    SerialInternal.print( cmdBuild("pm", args) );

}

float VirtualpulseIn(int pin, int val) // no
{
    String args;

    if (val == 0) //LOW 0x0
        args += '-';

    args += String(pin);

    SerialInternal.print( cmdBuild("pi", args) );

    // Read reply
    String rd = SerialInternal.readString();
    rd.replace("\r\n", "");

    return rd.toFloat();
}

float VirtualpulseIn_set(int pin, int val, int trials) // no
{
    String args;

    if (val == 0) //LOW 0x0
        args += '-';

    args += String(pin);

    SerialInternal.print( cmdBuild("ps", args) );

    float durations[32];
    float duration;
    int len = 0;
    float somma = 0;

    for(int i=0; i < trials; i++)
    {

        SerialInternal.print( cmdBuild("ps", args) );

        String rd = SerialInternal.readString();
        rd.replace("\r\n", "");

        if ( isNumeric(rd) )
        {
            if ( rd.toInt() > 1 )
                { 
                    durations[i] = rd.toInt();
                    len++;
                }
        }
    }

    for(int i=0; i < len; i++) 
        somma = somma + durations[i];

    if (len > 0)
        duration = somma / len;
    else
        duration = 0;

    return duration;
}

int VirtualservoAttach(int pin, int min, int max)
{
    String args;
    String rd;
    int trials = 0;

    args += String(pin); // handle eventually more args method
    args += '%' ;
    args += String(min);
    args += '%' ;
    args += String(max);

    while(1)
    {
        SerialInternal.print( cmdBuild("sva", args) );

        delay(20);

        rd = SerialInternal.readString();   // Read reply
        rd.replace("\r\n", "");

        trials++;

        if(trials > 20) // 100 milli x 20 trials = 2 seconds max wait
            return -1; // error
        
        if(rd != 0)
            break;
    }

    servo_pos[pin] = rd.toInt();

    return 1; //ok
}

void VirtualservoDetach(int pin)
{
    String args;

    args += String(servo_pos[pin]);

    SerialInternal.print( cmdBuild("svd", args) );

    servo_pos[pin] = 0;
}

void VirtualservoWrite(int pin, int angle)
{
    String args;

    args += String(servo_pos[pin]);

    args += '%' ;
    args += String(angle);

    SerialInternal.print( cmdBuild("svw", args) );
}

void VirtualservoWriteMicroseconds(int pin, int uS)
{
    String args;

    args += String(servo_pos[pin]);

    args += '%' ;
    args += String(uS);

    SerialInternal.print( cmdBuild("svwm", args) );
}

int VirtualservoRead(int pin)
{

    String args;

    args += String(servo_pos[pin]);

    SerialInternal.print( cmdBuild("svr", args) );

    String rd = SerialInternal.readString();   // Read reply
    rd.replace("\r\n", "");

    return rd.toInt(); // angle
}

