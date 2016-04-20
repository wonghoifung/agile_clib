#ifndef buffer_header
#define buffer_header

#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

	typedef struct BufferContext {
		void* pBuf;
		size_t size;
		void (*processor)(struct BufferContext* p);
	} BufferContext;

	bool buffer(BufferContext* pThis);

#ifdef __cplusplus
}
#endif

#endif
