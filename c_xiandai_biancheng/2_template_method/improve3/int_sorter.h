#ifndef int_sorter_header
#define int_sorter_header

#ifdef __cplusplus
extern "C" {
#endif

	typedef enum {
		ERR_CAT_OK = 0,
		ERR_CAT_FILE,
		ERR_CAT_MEMORY
	} IntSorterError;

	typedef struct {
		const char* const pFname;
		int errorCategory;
	} SortContext;

	IntSorterError int_sorter(const char* pFname);

#ifdef __cplusplus
}
#endif

#endif
