#include <PCM1774.h>

void PCM1774::begin() {
    dtwi->beginMaster();

    setDAC(0x7D, 0b01011100);
//    setDAC(0x40, 0x27);
//    setDAC(0x41, 0x27);
//    setDAC(0x44, 0x3F);
//    setDAC(0x45, 0x3F);
//    setDAC(0x45, 0xC1);
//    setDAC(0x49, 0xE0);
//    setDAC(0x56, 0x01); 
//    setDAC(0x48, 0x03);
//    setDAC(0x58, 0x11);
//    setDAC(0x49, 0xEC);
//    setDAC(0x4A, 0x01);
//    setDAC(0x52, 0x00);
//    setDAC(0x57, 0x11);

    setDAC(0x40, 0x3F);
    setDAC(0x41, 0x3F);
    setDAC(0x44, 0x3F);
    setDAC(0x45, 0x3F);
    setDAC(0x46, 0x00);
    setDAC(0x49, 0xE0);
    setDAC(0x56, 0x01);
    setDAC(0x48, 0x03);
    setDAC(0x58, 0x11);
    setDAC(0x49, 0xEC);
    setDAC(0x4A, 0x01);
    setDAC(0x52, 0x30);
    setDAC(0x57, 0x00);
}

void PCM1774::setGain(int8_t g) {
    switch (g) {
        case 0: setDAC(0x46, 0b00000000); break;
        case 1: setDAC(0x46, 0b00000100); break;
        case 2: setDAC(0x46, 0b00001000); break;
        case 3: setDAC(0x46, 0b00001100); break;
    }
}

void PCM1774::setDAC(uint8_t reg, uint8_t val) {
    uint8_t state = 0;
    while (1) {
        switch (state) {
            case 0: // begin write
                if (dtwi->startMasterWrite(0x47)) {
                    state = 1;
                }
                break;
            case 1: // Send register address
                if (dtwi->write(&reg, 1) == 1) {
                    state = 2;
                }
                break;
            case 2: // Send register address
                if (dtwi->write(&val, 1) == 1) {
                    state = 3;
                }
                break;
            case 3: // Stop Master
                if (dtwi->stopMaster()) {
                    return;
                }
                break;
        }
    }
}

void PCM1774::setBass(int8_t cut) {
    if (cut > 0) cut = 0;
    if (cut < -12) cut = -12;

    setDAC(0x5C, 15 + abs(cut));
}

void PCM1774::setMid(int8_t cut) {
    if (cut > 0) cut = 0;
    if (cut < -12) cut = -12;

    setDAC(0x5D, 15 + abs(cut));
}

void PCM1774::setTreble(int8_t cut) {
    if (cut > 0) cut = 0;
    if (cut < -12) cut = -12;

    setDAC(0x5E, 15 + abs(cut));
}

void PCM1774::setVolume(uint8_t v) {
    setVolume(v, v);
}

void PCM1774::setVolume(uint8_t l, uint8_t r) {
    setDAC(0x40, l & 0x3F);
    setDAC(0x41, r & 0x3F);
}

void PCM1774::set3D() {
    setDAC(0x5F, _3D.val);
}

void PCM1774::enable3D() {
    _3D.enable = 1;
    set3D();
}

void PCM1774::disable3D() {
    _3D.enable = 0;
    set3D();
}

void PCM1774::setWide3D() {
    _3D.filter = 1;
    set3D();
}

void PCM1774::setNarrow3D() {
    _3D.filter = 0;
    set3D();
}

void PCM1774::set3DDepth(uint8_t w) {
    _3D.depth = w;
    set3D();
}
