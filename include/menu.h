#ifndef MENU_H
#define MENU_H

#include "keypadlcd.h"
#include "config.h"

enum MenuItem{
    INITIAL,
    WATERRING_START,
    WATERRING_STOP,
};

/**
 * @brief Menu class
*/

class Menu{
    public:
        Menu(KeypadLCDControl* keypad) : currentMenuItem(MenuItem::WATERRING_START), keypadLCDControl(keypad) {}
        void setup_hook();
        void loop_hook();
        void printMenuItem();
        void initialMenuPrint();
        void initialMenuKeys();
        void waterringStartMenuPrint();
        void waterringStartMenuKeys();
        void keys();
        void navKeys();
        void waterringStopMenuPrint();
        void waterringStopMenuKeys();
        void callCommand(const char* command);

    private:
        MenuItem previousMenuItem;
        MenuItem currentMenuItem;
        KeypadLCDControl * keypadLCDControl;
        bool state;
};

void Menu::setup_hook(){
    keypadLCDControl->setup_hook();
}

void Menu::loop_hook(){
    keypadLCDControl->loop_hook();
    keys();
    //printMenuItem();
    keypadLCDControl->printNavNext();
    keypadLCDControl->printNavPrev();
}

void Menu::keys(){
    switch(currentMenuItem){
        case MenuItem::WATERRING_START:
            waterringStartMenuKeys();
            break;
        case MenuItem::WATERRING_STOP:
            waterringStopMenuKeys();
            break;
    }
    navKeys();
}

void Menu::navKeys(){
    if(keypadLCDControl->keyPressed() == ButtonPressed::LEFT){
        while(keypadLCDControl->keyPressed() == ButtonPressed::LEFT){
            delay(100);
        }
        previousMenuItem = currentMenuItem;
        currentMenuItem = static_cast<MenuItem>((static_cast<int>(currentMenuItem) - 1) % sizeof(MenuItem));
        keypadLCDControl->clear();
    }else if(keypadLCDControl->keyPressed() == ButtonPressed::RIGHT){
        while(keypadLCDControl->keyPressed() == ButtonPressed::RIGHT){
            delay(100);
        }
        previousMenuItem = currentMenuItem;
        currentMenuItem = static_cast<MenuItem>((static_cast<int>(currentMenuItem) + 1) % sizeof(MenuItem));
        keypadLCDControl->clear();
    }
}

void Menu::waterringStartMenuKeys(){
    if(keypadLCDControl->keyPressed() == ButtonPressed::SELECT){
        while (keypadLCDControl->keyPressed() == ButtonPressed::SELECT){ delay(100);}
        
        keypadLCDControl->printTextDown(OK_TEXT);
        delay(1000);
        //switch to stop menu
        keypadLCDControl->printTextDown(STATUS_WATERRING_ON_TEXT);
        currentMenuItem = MenuItem::WATERRING_STOP;
    }
}

void Menu::waterringStopMenuKeys(){
    if(keypadLCDControl->keyPressed() == ButtonPressed::SELECT){
        while (keypadLCDControl->keyPressed() == ButtonPressed::SELECT)
        {
            delay(100);
        }
        keypadLCDControl->printTextDown(OK_TEXT);
    }
}

void Menu::waterringStopMenuPrint(){
    keypadLCDControl->printTextUp(ACTION_WATERRING_OFF_TEXT);
}

void Menu::initialMenuPrint(){
    bool previousState = state;
    keypadLCDControl->printTextUp(WATER_BOOT_TEXT);
    callCommand("STATE");
    if(state != previousState){
        if (state)
        {
            keypadLCDControl->printTextDown(STATUS_WATERRING_ON_TEXT);
        }
    }
}

void Menu::initialMenuKeys(){
}

void Menu::callCommand(const char* command){
    Serial.println(command);
    int i = 0;
    char buf[10];
    while (Serial.available() > 0) {
        int incomingByte = 0;
        // read the incoming byte:
        incomingByte = Serial.read();
        buf[i] = incomingByte;
        i++;
    }
    if(strcmp(buf, "ON") == 0){
        state = true;
    }
    else if(strcmp(buf, "OFF") == 0){
        state = false;
    }
}

void Menu::printMenuItem(){
    keypadLCDControl->clear();
    switch(currentMenuItem){
        case MenuItem::INITIAL:
            initialMenuPrint();
            break;
        case MenuItem::WATERRING_START:
            waterringStartMenuPrint();
            break;
        case MenuItem::WATERRING_STOP:
            waterringStopMenuPrint();
            break;
    }
}

void Menu::waterringStartMenuPrint(){
    keypadLCDControl->printTextUp(ACTION_WATERRING_ON_TEXT);
    keypadLCDControl->printTextDown(OK_TEXT);
}


#endif