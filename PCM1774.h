#ifndef _PCM1774_H
#define _PCM1774_H

#include <Arduino.h>
#include <DTWI.h>
#include <I2S.h>

typedef struct {
    union {
        uint8_t val;
        struct {
            unsigned rsv1:1;
            unsigned enable:1;
            unsigned rsv2:1;
            unsigned filter:1;
            unsigned depth:4;
        } __attribute__((packed));
    } __attribute__((packed));
} __attribute__((packed)) reg3d;

class PCM1774 : public DAC {
	private:

        DTWI *dtwi;

        reg3d _3D;
        
        void setDAC(uint8_t reg, uint8_t val);

        void set3D();

	public:
        PCM1774(DTWI *d) : dtwi(d) {}
        PCM1774(DTWI &d) : dtwi(&d) {}

		void begin();

        void setGain(int8_t vol);
        void setVolume(uint8_t v);
        void setVolume(uint8_t l, uint8_t r);
        void setBass(int8_t cut);
        void setMid(int8_t cut);
        void setTreble(int8_t cut);

        void enable3D();
        void disable3D();
        void setWide3D();
        void setNarrow3D();
        void set3DDepth(uint8_t w);
};

#endif
