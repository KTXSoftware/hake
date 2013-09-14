#include "Reader.h"
#include <cstdlib>
#include <cstring>
#include <stdio.h>

using namespace Kore;

float Reader::readF32LE(u8* data) {
#ifdef SYS_LITTLE_ENDIAN //speed optimization
	return *(float*)data;
#else //works on all architectures
	int i = (data[0] << 0) | (data[1] << 8) | (data[2] << 16) | (data[3] << 24);
	return *(float*)&i;
#endif
}

float Reader::readF32BE(u8* data) {
#ifdef SYS_BIG_ENDIAN //speed optimization
	return *(float*)data;
#else //works on all architectures
	int i = (data[3] << 0) | (data[2] << 8) | (data[1] << 16) | (data[0] << 24);
	return *(float*)&i;
#endif
}

u32 Reader::readU32LE(u8* data) {
#ifdef SYS_LITTLE_ENDIAN
	return *(u32*)data;
#else
	return (data[0] << 0) | (data[1] << 8) | (data[2] << 16) | (data[3] << 24);
#endif
}

u32 Reader::readU32BE(u8* data) {
#ifdef SYS_BIG_ENDIAN
	return *(u32*)data;
#else
	return (data[3] << 0) | (data[2] << 8) | (data[1] << 16) | (data[0] << 24);
#endif
}

s32 Reader::readS32LE(u8* data) {
#ifdef SYS_LITTLE_ENDIAN
	return *(s32*)data;
#else
	return (data[0] << 0) | (data[1] << 8) | (data[2] << 16) | (data[3] << 24);
#endif
}

s32 Reader::readS32BE(u8* data) {
#ifdef SYS_BIG_ENDIAN
	return *(s32*)data;
#else
	return (data[3] << 0) | (data[2] << 8) | (data[1] << 16) | (data[0] << 24);
#endif
}

u16 Reader::readU16LE(u8* data) {
#ifdef SYS_LITTLE_ENDIAN
	return *(u16*)data;
#else
	return (data[0] << 0) | (data[1] << 8);
#endif
}

u16 Reader::readU16BE(u8* data) {
#ifdef SYS_BIG_ENDIAN
	return *(u16*)data;
#else
	return (data[1] << 0) | (data[0] << 8);
#endif
}

s16 Reader::readS16LE(u8* data) {
#ifdef SYS_LITTLE_ENDIAN
	return *(s16*)data;
#else
	return (data[0] << 0) | (data[1] << 8);
#endif
}

s16 Reader::readS16BE(u8* data) {
#ifdef SYS_BIG_ENDIAN
	return *(s16*)data;
#else
	return (data[1] << 0) | (data[0] << 8);
#endif
}

float Reader::readF32LE() {
	u8 data[4];
	read(data, 4);
	return readF32LE(&data[0]);
}

float Reader::readF32BE() {
	u8 data[4];
	read(data, 4);
	return readF32BE(&data[0]);
}

u32 Reader::readU32LE() {
	u8 data[4];
	read(data, 4);
	return readU32LE(&data[0]);
}

u32 Reader::readU32BE() {
	u8 data[4];
	read(data, 4);
	return readU32BE(&data[0]);
}

s32 Reader::readS32LE() {
	u8 data[4];
	read(data, 4);
	return readS32LE(&data[0]);
}

s32 Reader::readS32BE() {
	u8 data[4];
	read(data, 4);
	return readS32BE(&data[0]);
}

u16 Reader::readU16LE() {
	u8 data[2];
	read(data, 2);
	return readU16LE(&data[0]);
}

u16 Reader::readU16BE() {
	u8 data[2];
	read(data, 2);
	return readU16BE(&data[0]);
}

s16 Reader::readS16LE() {
	u8 data[2];
	read(data, 2);
	return readS16LE(&data[0]);
}

s16 Reader::readS16BE() {
	u8 data[2];
	read(data, 2);
	return readS16BE(&data[0]);
}

u8 Reader::readU8() {
	u8 data;
	read(&data, 1);
	return data;
}

s8 Reader::readS8() {
	s8 data;
	read(&data, 1);
	return data;
}
