#include "Rover.h"



/* Ran on first bootup of Main*/
Rover::Rover() : m_max4280(MAX_CS, &SPI){
    m_rovInfo.id = CLIENT_ADDR;
    m_rovInfo.serverAddr = SERVER_ADDR;
    m_rovInfo.init_retries = INIT_RETRIES;
    m_rovInfo.timeout = INIT_TIMEOUT;
    m_rovInfo.radioBaud = RADIO_BAUD;
}

void Rover::request(){ 

    if(m_radio.getType() != FreewaveRadio::Z9C){    //if true, the radio is GXM or Z9-T, requiring the use of the MAX3243 translating IC
        m_max3243.enable();
    }

}

void Rover::powerRadio(){
    Serial.println("Powering radio on.");
    m_max4280.assertRail(0);
}

void Rover::powerDownRadio(){
    Serial.println("Powering radio down.");
    m_max4280.assertRail(1);
}

void Rover::powerGNSS(){
    Serial.println("Powering GNSS on.");
    m_max4280.assertRail(2);
}

void Rover::powerDownGNSS(){
    Serial.println("Powering GNSS down.");
    m_max4280.assertRail(3);
}

void Rover::setMux(MuxFormat format){
    if(format == RadioToFeather){
        m_multiplexer.comY1();          //Radio->Feather
    }else if(format == RadioToGNSS){
        m_multiplexer.comY2();          //Radio->GNSS
    }

}