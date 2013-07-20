#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

typedef struct wav_head {
	char chunk_id[4];
	uint32_t chunksize;
	char RIFF_type[4];
} wav_head;

typedef struct format_head {
	char chunk_id[4];
	uint32_t chunksize;
	uint16_t compression;
	uint16_t channels;
	uint32_t samplerate;
	uint32_t bytes_per_second;
	uint16_t block_align;
	uint16_t bits_per_samp;
} format_head;

typedef struct data_head {
	char chunk_id[4];
	uint32_t chunksize;

} data_head;

void add_sinewave(short *buffer, int buffer_length, float frequency, float sampling_ratio, float amplitude)
{
	int i;
	for (i = 0; i < buffer_length; i++)
	{
		float theta = ((float)i / sampling_ratio) * M_PI;
		// Be sure to add code against overflows on the next line
		buffer[i] += (short)(sin(theta * frequency) * 32767.0f * amplitude);
	}
}

void make_squarewave(short *buffer, int buffer_length, float frequency, float sampling_ratio, float amplitude)
{
	short period = (short) (sampling_ratio / frequency);
	int i;
	for (i = 0; i < buffer_length; i++) {
		buffer[i] = (short) (32767.0f * amplitude);
		if (i % period) {
			amplitude = -amplitude;
		}
	}
}

void write_wav(short *buffer, size_t len)
{
	//Allocate memory for wav file
	size_t size = sizeof(wav_head) + sizeof(format_head) + sizeof(data_head) + len;
	void *write_buffer = malloc(size);

	//Fill buffer with headers
	wav_head *wh = (wav_head *) write_buffer;
	format_head *fh = (format_head *) (wh + 1);
	data_head *dh = (data_head *) (fh + 1);

	strcpy(wh->chunk_id, "RIFF");
	wh->chunksize = (uint32_t) size - 8;
	strcpy(wh->RIFF_type, "WAVE");

	strcpy(fh->chunk_id, "fmt ");
	fh->chunksize = 16;
	fh->compression = 1;
	fh->channels = 1;
	fh->samplerate = (uint32_t) 44100;
	fh->bits_per_samp = 16;
	fh->block_align = 2;
	fh->bytes_per_second = fh->block_align * 44100;

	strcpy(dh->chunk_id, "data");
	dh->chunksize = len;

	memcpy(dh + 1, buffer, len);

	//Write buffer to file
	FILE *out = fopen("out.wav", "w");
	fwrite(write_buffer, size, 1, out);
	printf("wrote notes to %s\n", "out.wav");
}

int main(int argc, char *argv[]) {

	FILE *trackfile = fopen(argv[1], "r");

	int note_length = 44100 / atoi(argv[2]);

	char *linebuf = NULL;
	size_t len = 0;

	len = getline(&linebuf, &len, trackfile) - 1;

	printf("%d notes in file\n", len);

	size_t pcmdata_len = len * note_length * sizeof(short);
	short *pcmdata = (short *) malloc(pcmdata_len);
	memset(pcmdata, 0, pcmdata_len);

	int notespacing = note_length/2;

	int i;
	for (i = 0; i < len; i++) {
		char cur = linebuf[i];
		switch(cur) {
			case 'a':
				if (linebuf[i+1] == ' ') {
					make_squarewave(pcmdata + (i * note_length), note_length - notespacing, 440.0f, 44100.0f, 0.5f);
				} else {
					make_squarewave(pcmdata + (i * note_length), note_length, 440.0f, 44100.0f, 0.5f);
				}
				break;
			case 'b':
				if (linebuf[i+1] == ' ') {
					make_squarewave(pcmdata + (i * note_length), note_length - notespacing, 493.88f, 44100.0f, 0.5f);
				} else {
					make_squarewave(pcmdata + (i * note_length), note_length, 493.88f, 44100.0f, 0.5f);
				}
				break;
			case 'c':
				if (linebuf[i+1] == ' ') {
					make_squarewave(pcmdata + (i * note_length), note_length - notespacing, 523.25f, 44100.0f, 0.5f);
				} else {
					make_squarewave(pcmdata + (i * note_length), note_length, 523.25f, 44100.0f, 0.5f);
				}
				break;
			case 'd':
				if (linebuf[i+1] == ' ') {
					make_squarewave(pcmdata + (i * note_length), note_length - notespacing, 587.33f, 44100.0f, 0.5f);
				} else {
					make_squarewave(pcmdata + (i * note_length), note_length, 587.33f, 44100.0f, 0.5f);
				}
				break;
			case 'e':
				if (linebuf[i+1] == ' ') {
					make_squarewave(pcmdata + (i * note_length), note_length - notespacing, 659.26f, 44100.0f, 0.5f);
				} else {
					make_squarewave(pcmdata + (i * note_length), note_length, 659.26f, 44100.0f, 0.5f);
				}
				break;
			case 'f':
				if (linebuf[i+1] == ' ') {
					make_squarewave(pcmdata + (i * note_length), note_length - notespacing, 701.00f, 44100.0f, 0.5f);
				} else {
					make_squarewave(pcmdata + (i * note_length), note_length, 701.00f, 44100.0f, 0.5f);
				}
				break;
			case 'g':
				if (linebuf[i+1] == ' ') {
					make_squarewave(pcmdata + (i * note_length), note_length - notespacing, 783.99f, 44100.0f, 0.5f);
				} else {
					make_squarewave(pcmdata + (i * note_length), note_length, 783.99f, 44100.0f, 0.5f);
				}
				break;
			case ' ':
				make_squarewave(pcmdata + (i * note_length) + note_length - notespacing, notespacing, 0.0f, 44100.0f, 0.0f);
				break;
			default:
				break;
		}
	}

	write_wav(pcmdata, pcmdata_len);

	return 0;
}
