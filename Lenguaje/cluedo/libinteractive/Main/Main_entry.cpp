/* Auto-generated by libinteractive. Do not edit. */
#define _XOPEN_SOURCE 600
#if !defined(_WIN32) && !defined(_GNU_SOURCE)
#define _GNU_SOURCE
#endif
#include <fcntl.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "cluedo.h"

#if defined(__GNUC__)
#define __NOINLINE __attribute__((noinline))
#else
#define __NOINLINE
#endif

#if defined(_WIN32)
#if !defined(PRIuS)
#define PRIuS "Iu"
#endif
#else
#if !defined(PRIuS)
#define PRIuS "zu"
#endif
// Windows requires this flag to open files in binary mode using the
// open syscall.
#define O_BINARY 0
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if defined(_WIN32)
// declared in windows.h
void mainCRTStartup();
#elif !defined(__APPLE__)
// declared in crt1.o
void _start();
#endif

#if defined(__APPLE__) || defined(_WIN32)
// Apple's and Windows name mangling adds an extra underscore.
void _entry();
#else
void __entry();
#endif

struct __stream {
	int fd;
	size_t capacity;
	size_t pos;
	char buffer[4096];
};

static void openstream(struct __stream* stream, const char* path, int flags) {
	stream->fd = open(path, flags | O_BINARY);
	if (stream->fd == -1) {
		perror("open");
		exit(243);
	}
	stream->pos = 0;
	stream->capacity = 0;
}

static void closestream(struct __stream* stream) {
	if (close(stream->fd) == -1) {
		perror("close");
	}
}

static int readfull(struct __stream* stream, void* buf, size_t count, int fatal) {
	ssize_t bytes;
	while (count > 0) {
		if (stream->pos == stream->capacity) {
			stream->pos = 0;
			bytes = read(stream->fd, stream->buffer, sizeof(stream->buffer));
			if (bytes <= 0) {
				if (!fatal) return 0;
				fprintf(stderr, "Incomplete message missing %" PRIuS " bytes\n", count);
				exit(239);
			}
			stream->capacity = (size_t)bytes;
		}

		bytes = (count < stream->capacity - stream->pos) ? count : (stream->capacity - stream->pos);
		memcpy(buf, stream->buffer + stream->pos, bytes);
		stream->pos += bytes;
		count -= bytes;
		buf = bytes + (char*)buf;
	}
	return 1;
}

static void writeflush(struct __stream* stream) {
	const char* to_write = stream->buffer;
	size_t remaining = stream->pos;
	while (remaining > 0) {
		ssize_t bytes = write(stream->fd, to_write, remaining);
		if (bytes <= 0) {
			fprintf(stderr, "Incomplete message missing %" PRIuS " bytes\n", remaining);
			exit(239);
		}
		to_write = bytes + to_write;
		remaining -= bytes;
	}
	stream->pos = 0;
}

static void writefull(struct __stream* stream, const void* buf, size_t count) {
	ssize_t bytes;
	while (count > 0) {
		bytes = (count < sizeof(stream->buffer) - stream->pos) ? count : (sizeof(stream->buffer) - stream->pos);
		memcpy(stream->buffer + stream->pos, buf, bytes);
		stream->pos += bytes;
		buf = bytes + (char*)buf;
		count -= bytes;

		if (stream->pos == sizeof(stream->buffer)) {
			writeflush(stream);
		}
	}
}

static struct __stream __cluedo_in, __cluedo_out;

#ifdef __cplusplus
}
#endif

static void __NOINLINE __libinteractive_init() {
	openstream(&__cluedo_in, "cluedo_in", O_WRONLY);
	openstream(&__cluedo_out, "cluedo_out", O_RDONLY);
}

#if defined(__APPLE__) || defined(_WIN32)
// Apple's and Windows name mangling adds an extra underscore.
void _entry()
#else
void __entry()
#endif
{
	#if !defined(_WIN32)

	// _start expects the stack in a very specific configuration.
	#if defined(__x86_64__)
	__asm__(
		"popq %%rbp\n"	// Remove %rbp from the stack that gcc helpfully added.
		"pushq %%rdx\n" // Store %rdx since we will need it later.
		:::
	);
	#else
	__asm__(
		"popl %%ebp\n"	// Remove %ebp from the stack that gcc helpfully added.
		"pushl %%eax\n" // Save all registers that contain stuff _start expects.
		"pushl %%edx\n"
		"pushl %%ecx\n"
		:::
	);
	#endif // __x86_64__

	__libinteractive_init();

	// Perform regular libc startup
	// Restore all arch-specific registers.
	#if defined(__x86_64__)
	__asm__ (
		"popq %%rdx\n"
		:::
	);
	#else
	__asm__ (
		"popl %%ecx\n"
		"popl %%edx\n"
		"popl %%eax\n"
		:::
	);
	#endif // __x86_64__
	// We cannot call _start since that would add stuff to the stack.
	// Jump to it and everything should be exactly as it expects it to be.
	#if defined(__APPLE__)
	__asm__ (
		"jmp _main\n"
		:::
	);
	#else
	__asm__ (
		"jmp _start\n"
		:::
	);
	#endif

	#else

	// The Windows case is much simpler, fortunately :)
	__libinteractive_init();
	// Perform regular libc startup
	mainCRTStartup();

	#endif // _WIN32
}

static void __message_loop_cluedo(int __current_function, int __noreturn) {
	uint32_t __msgid;
	while (readfull(&__cluedo_out, &__msgid, sizeof(__msgid), 0)) {
		if (__msgid == __current_function) return;
		switch (__msgid) {
			case 0xf2ccbe76u: {
				// cluedo -> Main.Teoria
				uint32_t __cookie;
				int Teoria_c;
				readfull(&__cluedo_out, &Teoria_c, sizeof(int), 1);
				int Teoria_u;
				readfull(&__cluedo_out, &Teoria_u, sizeof(int), 1);
				int Teoria_a;
				readfull(&__cluedo_out, &Teoria_a, sizeof(int), 1);
				readfull(&__cluedo_out, &__cookie, sizeof(__cookie), 1);

				int result =
				Teoria(Teoria_c, Teoria_u, Teoria_a);

				writefull(&__cluedo_in, &__msgid, sizeof(__msgid));
				writefull(&__cluedo_in, &result, sizeof(result));
				writefull(&__cluedo_in, &__cookie, sizeof(__cookie));
				writeflush(&__cluedo_in);
				break;
			}

			default: {
				fprintf(stderr, "Unknown message id 0x%x\n", __msgid);
				exit(241);
			}
		}
	}
	if (__noreturn) {
		exit(0);
	}
	if (__current_function != -1) {
		fprintf(stderr, "Confused about exiting\n");
		exit(242);
	}
}

void ResolverCaso() {
	const uint32_t __msgid = 0x30533e6u;
	const uint32_t __cookie = 0xd55f1bc3u;

	writefull(&__cluedo_in, &__msgid, sizeof(__msgid));
	writefull(&__cluedo_in, &__cookie, sizeof(__cookie));
	writeflush(&__cluedo_in);

	__message_loop_cluedo(__msgid,  0 );
	uint32_t __cookie_result = 0;
	readfull(&__cluedo_out, &__cookie_result, sizeof(__cookie_result), 1);

	if (__cookie != __cookie_result) {
		fprintf(stderr, "invalid cookie\n");
		exit(240);
	}
}
