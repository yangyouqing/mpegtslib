#ifndef TS_API_H
#define TS_API_H
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

int mpegts_init(int (* packet_output)( uint8_t *buf, uint32_t len ));

int mpegts_write_vframe(uint8_t *frame, int len, int iskey, int64_t timestamp);

int mpegts_write_aframe(uint8_t *frame, int len, int64_t timestamp);

#endif