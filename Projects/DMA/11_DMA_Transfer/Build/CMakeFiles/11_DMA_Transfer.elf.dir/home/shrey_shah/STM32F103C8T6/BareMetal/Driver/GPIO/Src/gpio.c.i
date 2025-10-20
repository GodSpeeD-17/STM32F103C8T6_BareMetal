# 0 "/home/shrey_shah/STM32F103C8T6/BareMetal/Driver/GPIO/Src/gpio.c"
# 1 "/home/shrey_shah/STM32F103C8T6/Projects/DMA/11_DMA_Transfer/Build//"
# 0 "<built-in>"
# 0 "<command-line>"
# 1 "/home/shrey_shah/STM32F103C8T6/BareMetal/Driver/GPIO/Src/gpio.c"

# 1 "/home/shrey_shah/STM32F103C8T6/BareMetal/Driver/GPIO/Inc/gpio.h" 1





# 1 "/home/shrey_shah/STM32F103C8T6/BareMetal/Driver/GPIO/Inc/gpio_config.h" 1
# 16 "/home/shrey_shah/STM32F103C8T6/BareMetal/Driver/GPIO/Inc/gpio_config.h"
# 1 "/home/shrey_shah/STM32F103C8T6/BareMetal/Driver/reg_map.h" 1
# 46 "/home/shrey_shah/STM32F103C8T6/BareMetal/Driver/reg_map.h"
# 1 "/home/shrey_shah/STM32F103C8T6/BareMetal/Core/Inc/cmsis_gcc.h" 1
# 34 "/home/shrey_shah/STM32F103C8T6/BareMetal/Core/Inc/cmsis_gcc.h"
# 1 "/opt/arm-gnu-toolchain-14.3/lib/gcc/arm-none-eabi/14.3.1/include/stdint.h" 1 3 4
# 9 "/opt/arm-gnu-toolchain-14.3/lib/gcc/arm-none-eabi/14.3.1/include/stdint.h" 3 4
# 1 "/opt/arm-gnu-toolchain-14.3/arm-none-eabi/include/stdint.h" 1 3 4
# 12 "/opt/arm-gnu-toolchain-14.3/arm-none-eabi/include/stdint.h" 3 4
# 1 "/opt/arm-gnu-toolchain-14.3/arm-none-eabi/include/machine/_default_types.h" 1 3 4







# 1 "/opt/arm-gnu-toolchain-14.3/arm-none-eabi/include/sys/features.h" 1 3 4
# 28 "/opt/arm-gnu-toolchain-14.3/arm-none-eabi/include/sys/features.h" 3 4
# 1 "/opt/arm-gnu-toolchain-14.3/arm-none-eabi/include/_newlib_version.h" 1 3 4
# 29 "/opt/arm-gnu-toolchain-14.3/arm-none-eabi/include/sys/features.h" 2 3 4
# 9 "/opt/arm-gnu-toolchain-14.3/arm-none-eabi/include/machine/_default_types.h" 2 3 4
# 41 "/opt/arm-gnu-toolchain-14.3/arm-none-eabi/include/machine/_default_types.h" 3 4

# 41 "/opt/arm-gnu-toolchain-14.3/arm-none-eabi/include/machine/_default_types.h" 3 4
typedef signed char __int8_t;

typedef unsigned char __uint8_t;
# 55 "/opt/arm-gnu-toolchain-14.3/arm-none-eabi/include/machine/_default_types.h" 3 4
typedef short int __int16_t;

typedef short unsigned int __uint16_t;
# 77 "/opt/arm-gnu-toolchain-14.3/arm-none-eabi/include/machine/_default_types.h" 3 4
typedef long int __int32_t;

typedef long unsigned int __uint32_t;
# 103 "/opt/arm-gnu-toolchain-14.3/arm-none-eabi/include/machine/_default_types.h" 3 4
typedef long long int __int64_t;

typedef long long unsigned int __uint64_t;
# 134 "/opt/arm-gnu-toolchain-14.3/arm-none-eabi/include/machine/_default_types.h" 3 4
typedef signed char __int_least8_t;

typedef unsigned char __uint_least8_t;
# 160 "/opt/arm-gnu-toolchain-14.3/arm-none-eabi/include/machine/_default_types.h" 3 4
typedef short int __int_least16_t;

typedef short unsigned int __uint_least16_t;
# 182 "/opt/arm-gnu-toolchain-14.3/arm-none-eabi/include/machine/_default_types.h" 3 4
typedef long int __int_least32_t;

typedef long unsigned int __uint_least32_t;
# 200 "/opt/arm-gnu-toolchain-14.3/arm-none-eabi/include/machine/_default_types.h" 3 4
typedef long long int __int_least64_t;

typedef long long unsigned int __uint_least64_t;
# 214 "/opt/arm-gnu-toolchain-14.3/arm-none-eabi/include/machine/_default_types.h" 3 4
typedef long long int __intmax_t;







typedef long long unsigned int __uintmax_t;







typedef int __intptr_t;

typedef unsigned int __uintptr_t;
# 13 "/opt/arm-gnu-toolchain-14.3/arm-none-eabi/include/stdint.h" 2 3 4
# 1 "/opt/arm-gnu-toolchain-14.3/arm-none-eabi/include/sys/_intsup.h" 1 3 4
# 35 "/opt/arm-gnu-toolchain-14.3/arm-none-eabi/include/sys/_intsup.h" 3 4
       
       
       
       
       
       
       
       
# 190 "/opt/arm-gnu-toolchain-14.3/arm-none-eabi/include/sys/_intsup.h" 3 4
       
       
       
       
       
       
       
       
# 14 "/opt/arm-gnu-toolchain-14.3/arm-none-eabi/include/stdint.h" 2 3 4
# 1 "/opt/arm-gnu-toolchain-14.3/arm-none-eabi/include/sys/_stdint.h" 1 3 4
# 20 "/opt/arm-gnu-toolchain-14.3/arm-none-eabi/include/sys/_stdint.h" 3 4
typedef __int8_t int8_t ;



typedef __uint8_t uint8_t ;







typedef __int16_t int16_t ;



typedef __uint16_t uint16_t ;







typedef __int32_t int32_t ;



typedef __uint32_t uint32_t ;







typedef __int64_t int64_t ;



typedef __uint64_t uint64_t ;






typedef __intmax_t intmax_t;




typedef __uintmax_t uintmax_t;




typedef __intptr_t intptr_t;




typedef __uintptr_t uintptr_t;
# 15 "/opt/arm-gnu-toolchain-14.3/arm-none-eabi/include/stdint.h" 2 3 4






typedef __int_least8_t int_least8_t;
typedef __uint_least8_t uint_least8_t;




typedef __int_least16_t int_least16_t;
typedef __uint_least16_t uint_least16_t;




typedef __int_least32_t int_least32_t;
typedef __uint_least32_t uint_least32_t;




typedef __int_least64_t int_least64_t;
typedef __uint_least64_t uint_least64_t;
# 51 "/opt/arm-gnu-toolchain-14.3/arm-none-eabi/include/stdint.h" 3 4
  typedef int int_fast8_t;
  typedef unsigned int uint_fast8_t;
# 61 "/opt/arm-gnu-toolchain-14.3/arm-none-eabi/include/stdint.h" 3 4
  typedef int int_fast16_t;
  typedef unsigned int uint_fast16_t;
# 71 "/opt/arm-gnu-toolchain-14.3/arm-none-eabi/include/stdint.h" 3 4
  typedef int int_fast32_t;
  typedef unsigned int uint_fast32_t;
# 81 "/opt/arm-gnu-toolchain-14.3/arm-none-eabi/include/stdint.h" 3 4
  typedef long long int int_fast64_t;
  typedef long long unsigned int uint_fast64_t;
# 10 "/opt/arm-gnu-toolchain-14.3/lib/gcc/arm-none-eabi/14.3.1/include/stdint.h" 2 3 4
# 35 "/home/shrey_shah/STM32F103C8T6/BareMetal/Core/Inc/cmsis_gcc.h" 2
# 1 "/opt/arm-gnu-toolchain-14.3/arm-none-eabi/include/string.h" 1 3
# 10 "/opt/arm-gnu-toolchain-14.3/arm-none-eabi/include/string.h" 3
# 1 "/opt/arm-gnu-toolchain-14.3/arm-none-eabi/include/_ansi.h" 1 3
# 10 "/opt/arm-gnu-toolchain-14.3/arm-none-eabi/include/_ansi.h" 3
# 1 "/opt/arm-gnu-toolchain-14.3/arm-none-eabi/include/newlib-nano/newlib.h" 1 3 4
# 11 "/opt/arm-gnu-toolchain-14.3/arm-none-eabi/include/_ansi.h" 2 3
# 1 "/opt/arm-gnu-toolchain-14.3/arm-none-eabi/include/sys/config.h" 1 3



# 1 "/opt/arm-gnu-toolchain-14.3/arm-none-eabi/include/machine/ieeefp.h" 1 3
# 5 "/opt/arm-gnu-toolchain-14.3/arm-none-eabi/include/sys/config.h" 2 3
# 12 "/opt/arm-gnu-toolchain-14.3/arm-none-eabi/include/_ansi.h" 2 3
# 11 "/opt/arm-gnu-toolchain-14.3/arm-none-eabi/include/string.h" 2 3
# 1 "/opt/arm-gnu-toolchain-14.3/arm-none-eabi/include/sys/reent.h" 1 3
# 13 "/opt/arm-gnu-toolchain-14.3/arm-none-eabi/include/sys/reent.h" 3
# 1 "/opt/arm-gnu-toolchain-14.3/arm-none-eabi/include/_ansi.h" 1 3
# 14 "/opt/arm-gnu-toolchain-14.3/arm-none-eabi/include/sys/reent.h" 2 3
# 1 "/opt/arm-gnu-toolchain-14.3/lib/gcc/arm-none-eabi/14.3.1/include/stddef.h" 1 3 4
# 160 "/opt/arm-gnu-toolchain-14.3/lib/gcc/arm-none-eabi/14.3.1/include/stddef.h" 3 4
typedef int ptrdiff_t;
# 229 "/opt/arm-gnu-toolchain-14.3/lib/gcc/arm-none-eabi/14.3.1/include/stddef.h" 3 4
typedef unsigned int size_t;
# 344 "/opt/arm-gnu-toolchain-14.3/lib/gcc/arm-none-eabi/14.3.1/include/stddef.h" 3 4
typedef unsigned int wchar_t;
# 440 "/opt/arm-gnu-toolchain-14.3/lib/gcc/arm-none-eabi/14.3.1/include/stddef.h" 3 4
typedef struct {
  long long __max_align_ll __attribute__((__aligned__(__alignof__(long long))));
  long double __max_align_ld __attribute__((__aligned__(__alignof__(long double))));
# 451 "/opt/arm-gnu-toolchain-14.3/lib/gcc/arm-none-eabi/14.3.1/include/stddef.h" 3 4
} max_align_t;
# 15 "/opt/arm-gnu-toolchain-14.3/arm-none-eabi/include/sys/reent.h" 2 3
# 1 "/opt/arm-gnu-toolchain-14.3/arm-none-eabi/include/sys/cdefs.h" 1 3
# 47 "/opt/arm-gnu-toolchain-14.3/arm-none-eabi/include/sys/cdefs.h" 3
# 1 "/opt/arm-gnu-toolchain-14.3/lib/gcc/arm-none-eabi/14.3.1/include/stddef.h" 1 3 4
# 48 "/opt/arm-gnu-toolchain-14.3/arm-none-eabi/include/sys/cdefs.h" 2 3
# 16 "/opt/arm-gnu-toolchain-14.3/arm-none-eabi/include/sys/reent.h" 2 3
# 1 "/opt/arm-gnu-toolchain-14.3/arm-none-eabi/include/sys/_types.h" 1 3
# 24 "/opt/arm-gnu-toolchain-14.3/arm-none-eabi/include/sys/_types.h" 3
# 1 "/opt/arm-gnu-toolchain-14.3/lib/gcc/arm-none-eabi/14.3.1/include/stddef.h" 1 3 4
# 374 "/opt/arm-gnu-toolchain-14.3/lib/gcc/arm-none-eabi/14.3.1/include/stddef.h" 3 4
typedef unsigned int wint_t;
# 25 "/opt/arm-gnu-toolchain-14.3/arm-none-eabi/include/sys/_types.h" 2 3


# 1 "/opt/arm-gnu-toolchain-14.3/arm-none-eabi/include/machine/_types.h" 1 3
# 28 "/opt/arm-gnu-toolchain-14.3/arm-none-eabi/include/sys/_types.h" 2 3


typedef long __blkcnt_t;



typedef long __blksize_t;



typedef __uint64_t __fsblkcnt_t;



typedef __uint32_t __fsfilcnt_t;



typedef long _off_t;





typedef int __pid_t;



typedef short __dev_t;



typedef unsigned short __uid_t;


typedef unsigned short __gid_t;



typedef __uint32_t __id_t;







typedef unsigned short __ino_t;
# 90 "/opt/arm-gnu-toolchain-14.3/arm-none-eabi/include/sys/_types.h" 3
typedef __uint32_t __mode_t;





__extension__ typedef long long _off64_t;





typedef _off_t __off_t;


typedef _off64_t __loff_t;


typedef long __key_t;







typedef long _fpos_t;
# 131 "/opt/arm-gnu-toolchain-14.3/arm-none-eabi/include/sys/_types.h" 3
typedef unsigned int __size_t;
# 147 "/opt/arm-gnu-toolchain-14.3/arm-none-eabi/include/sys/_types.h" 3
typedef signed int _ssize_t;
# 158 "/opt/arm-gnu-toolchain-14.3/arm-none-eabi/include/sys/_types.h" 3
typedef _ssize_t __ssize_t;



typedef struct
{
  int __count;
  union
  {
    wint_t __wch;
    unsigned char __wchb[4];
  } __value;
} _mbstate_t;




typedef void *_iconv_t;






typedef unsigned long __clock_t;






typedef __int_least64_t __time_t;





typedef unsigned long __clockid_t;


typedef long __daddr_t;



typedef unsigned long __timer_t;


typedef __uint8_t __sa_family_t;



typedef __uint32_t __socklen_t;


typedef int __nl_item;
typedef unsigned short __nlink_t;
typedef long __suseconds_t;
typedef unsigned long __useconds_t;







typedef __builtin_va_list __va_list;
# 17 "/opt/arm-gnu-toolchain-14.3/arm-none-eabi/include/sys/reent.h" 2 3






typedef unsigned long __ULong;
# 35 "/opt/arm-gnu-toolchain-14.3/arm-none-eabi/include/sys/reent.h" 3
# 1 "/opt/arm-gnu-toolchain-14.3/arm-none-eabi/include/sys/lock.h" 1 3
# 33 "/opt/arm-gnu-toolchain-14.3/arm-none-eabi/include/sys/lock.h" 3
struct __lock;
typedef struct __lock * _LOCK_T;






extern void __retarget_lock_init(_LOCK_T *lock);

extern void __retarget_lock_init_recursive(_LOCK_T *lock);

extern void __retarget_lock_close(_LOCK_T lock);

extern void __retarget_lock_close_recursive(_LOCK_T lock);

extern void __retarget_lock_acquire(_LOCK_T lock);

extern void __retarget_lock_acquire_recursive(_LOCK_T lock);

extern int __retarget_lock_try_acquire(_LOCK_T lock);

extern int __retarget_lock_try_acquire_recursive(_LOCK_T lock);


extern void __retarget_lock_release(_LOCK_T lock);

extern void __retarget_lock_release_recursive(_LOCK_T lock);
# 36 "/opt/arm-gnu-toolchain-14.3/arm-none-eabi/include/sys/reent.h" 2 3
typedef _LOCK_T _flock_t;







struct _reent;

struct __locale_t;






struct _Bigint
{
  struct _Bigint *_next;
  int _k, _maxwds, _sign, _wds;
  __ULong _x[1];
};


struct __tm
{
  int __tm_sec;
  int __tm_min;
  int __tm_hour;
  int __tm_mday;
  int __tm_mon;
  int __tm_year;
  int __tm_wday;
  int __tm_yday;
  int __tm_isdst;
};







struct _on_exit_args {
 void * _fnargs[32];
 void * _dso_handle[32];

 __ULong _fntypes;


 __ULong _is_cxa;
};


struct _atexit {
 struct _atexit *_next;
 int _ind;
 void (*_fns[32])(void);
        struct _on_exit_args * _on_exit_args_ptr;
};
# 116 "/opt/arm-gnu-toolchain-14.3/arm-none-eabi/include/sys/reent.h" 3
struct __sbuf {
 unsigned char *_base;
 int _size;
};
# 153 "/opt/arm-gnu-toolchain-14.3/arm-none-eabi/include/sys/reent.h" 3
struct __sFILE {
  unsigned char *_p;
  int _r;
  int _w;
  short _flags;
  short _file;
  struct __sbuf _bf;
  int _lbfsize;


  struct _reent *_data;



  void * _cookie;

  int (*_read) (struct _reent *, void *,
        char *, int);
  int (*_write) (struct _reent *, void *,
         const char *,
         int);
  _fpos_t (*_seek) (struct _reent *, void *, _fpos_t, int);
  int (*_close) (struct _reent *, void *);


  struct __sbuf _ub;
  unsigned char *_up;
  int _ur;


  unsigned char _ubuf[3];
  unsigned char _nbuf[1];


  struct __sbuf _lb;


  int _blksize;
  _off_t _offset;






  _flock_t _lock;

  _mbstate_t _mbstate;
  int _flags2;
};
# 270 "/opt/arm-gnu-toolchain-14.3/arm-none-eabi/include/sys/reent.h" 3
typedef struct __sFILE __FILE;



extern __FILE __sf[3];

struct _glue
{
  struct _glue *_next;
  int _niobs;
  __FILE *_iobs;
};

extern struct _glue __sglue;
# 306 "/opt/arm-gnu-toolchain-14.3/arm-none-eabi/include/sys/reent.h" 3
struct _rand48 {
  unsigned short _seed[3];
  unsigned short _mult[3];
  unsigned short _add;


  __extension__ unsigned long long _rand_next;

};
# 348 "/opt/arm-gnu-toolchain-14.3/arm-none-eabi/include/sys/reent.h" 3
struct _mprec
{

  struct _Bigint *_result;
  int _result_k;
  struct _Bigint *_p5s;
  struct _Bigint **_freelist;
};


struct _misc_reent
{

  char *_strtok_last;
  _mbstate_t _mblen_state;
  _mbstate_t _wctomb_state;
  _mbstate_t _mbtowc_state;
  char _l64a_buf[8];
  int _getdate_err;
  _mbstate_t _mbrlen_state;
  _mbstate_t _mbrtowc_state;
  _mbstate_t _mbsrtowcs_state;
  _mbstate_t _wcrtomb_state;
  _mbstate_t _wcsrtombs_state;



};



struct _reent
{


  int _errno;




  __FILE *_stdin, *_stdout, *_stderr;

  int _inc;

  char *_emergency;





  struct __locale_t *_locale;

  struct _mprec *_mp;

  void (*__cleanup) (struct _reent *);

  int _gamma_signgam;


  int _cvtlen;
  char *_cvtbuf;

  struct _rand48 *_r48;
  struct __tm *_localtime_buf;
  char *_asctime_buf;


  void (** _sig_func)(int);







  __FILE *__sf;
  struct _misc_reent *_misc;
  char *_signal_buf;
};
# 462 "/opt/arm-gnu-toolchain-14.3/arm-none-eabi/include/sys/reent.h" 3
# 1 "/opt/arm-gnu-toolchain-14.3/arm-none-eabi/include/assert.h" 1 3
# 39 "/opt/arm-gnu-toolchain-14.3/arm-none-eabi/include/assert.h" 3
void __assert (const char *, int, const char *)
     __attribute__ ((__noreturn__));
void __assert_func (const char *, int, const char *, const char *)
     __attribute__ ((__noreturn__));
# 463 "/opt/arm-gnu-toolchain-14.3/arm-none-eabi/include/sys/reent.h" 2 3
# 804 "/opt/arm-gnu-toolchain-14.3/arm-none-eabi/include/sys/reent.h" 3
extern struct _reent *_impure_ptr ;





extern struct _reent _impure_data ;
# 924 "/opt/arm-gnu-toolchain-14.3/arm-none-eabi/include/sys/reent.h" 3
extern struct _atexit *__atexit;
extern struct _atexit __atexit0;

extern void (*__stdio_exit_handler) (void);

void _reclaim_reent (struct _reent *);

extern int _fwalk_sglue (struct _reent *, int (*)(struct _reent *, __FILE *),
    struct _glue *);
# 12 "/opt/arm-gnu-toolchain-14.3/arm-none-eabi/include/string.h" 2 3





# 1 "/opt/arm-gnu-toolchain-14.3/lib/gcc/arm-none-eabi/14.3.1/include/stddef.h" 1 3 4
# 18 "/opt/arm-gnu-toolchain-14.3/arm-none-eabi/include/string.h" 2 3


# 1 "/opt/arm-gnu-toolchain-14.3/arm-none-eabi/include/sys/_locale.h" 1 3
# 9 "/opt/arm-gnu-toolchain-14.3/arm-none-eabi/include/sys/_locale.h" 3
struct __locale_t;
typedef struct __locale_t *locale_t;
# 21 "/opt/arm-gnu-toolchain-14.3/arm-none-eabi/include/string.h" 2 3



# 1 "/opt/arm-gnu-toolchain-14.3/arm-none-eabi/include/strings.h" 1 3
# 44 "/opt/arm-gnu-toolchain-14.3/arm-none-eabi/include/strings.h" 3


int bcmp(const void *, const void *, size_t) __attribute__((__pure__));
void bcopy(const void *, void *, size_t);
void bzero(void *, size_t);


void explicit_bzero(void *, size_t);


int ffs(int) __attribute__((__const__));


int ffsl(long) __attribute__((__const__));
int ffsll(long long) __attribute__((__const__));
int fls(int) __attribute__((__const__));
int flsl(long) __attribute__((__const__));
int flsll(long long) __attribute__((__const__));


char *index(const char *, int) __attribute__((__pure__));
char *rindex(const char *, int) __attribute__((__pure__));

int strcasecmp(const char *, const char *) __attribute__((__pure__));
int strncasecmp(const char *, const char *, size_t) __attribute__((__pure__));


int strcasecmp_l (const char *, const char *, locale_t);
int strncasecmp_l (const char *, const char *, size_t, locale_t);


# 25 "/opt/arm-gnu-toolchain-14.3/arm-none-eabi/include/string.h" 2 3




void * memchr (const void *, int, size_t);
int memcmp (const void *, const void *, size_t);
void * memcpy (void *restrict, const void *restrict, size_t);
void * memmove (void *, const void *, size_t);
void * memset (void *, int, size_t);
char *strcat (char *restrict, const char *restrict);
char *strchr (const char *, int);
int strcmp (const char *, const char *);
int strcoll (const char *, const char *);
char *strcpy (char *restrict, const char *restrict);
size_t strcspn (const char *, const char *);
char *strerror (int);
size_t strlen (const char *);
char *strncat (char *restrict, const char *restrict, size_t);
int strncmp (const char *, const char *, size_t);
char *strncpy (char *restrict, const char *restrict, size_t);
char *strpbrk (const char *, const char *);
char *strrchr (const char *, int);
size_t strspn (const char *, const char *);
char *strstr (const char *, const char *);

char *strtok (char *restrict, const char *restrict);

size_t strxfrm (char *restrict, const char *restrict, size_t);


int strcoll_l (const char *, const char *, locale_t);
char *strerror_l (int, locale_t);
size_t strxfrm_l (char *restrict, const char *restrict, size_t, locale_t);


char *strtok_r (char *restrict, const char *restrict, char **restrict);


int timingsafe_bcmp (const void *, const void *, size_t);
int timingsafe_memcmp (const void *, const void *, size_t);


void * memccpy (void *restrict, const void *restrict, int, size_t);
# 76 "/opt/arm-gnu-toolchain-14.3/arm-none-eabi/include/string.h" 3
char *stpcpy (char *restrict, const char *restrict);
char *stpncpy (char *restrict, const char *restrict, size_t);






char *strdup (const char *) __attribute__((__malloc__)) __attribute__((__warn_unused_result__));

char *_strdup_r (struct _reent *, const char *);

char *strndup (const char *, size_t) __attribute__((__malloc__)) __attribute__((__warn_unused_result__));

char *_strndup_r (struct _reent *, const char *, size_t);
# 100 "/opt/arm-gnu-toolchain-14.3/arm-none-eabi/include/string.h" 3
int strerror_r (int, char *, size_t)

             __asm__ ("" "__xpg_strerror_r")

  ;







char * _strerror_r (struct _reent *, int, int, int *);


size_t strlcat (char *, const char *, size_t);
size_t strlcpy (char *, const char *, size_t);


size_t strnlen (const char *, size_t);


char *strsep (char **, const char *);


char *strnstr(const char *, const char *, size_t) __attribute__((__pure__));



char *strlwr (char *);
char *strupr (char *);



char *strsignal (int __signo);
# 175 "/opt/arm-gnu-toolchain-14.3/arm-none-eabi/include/string.h" 3
# 1 "/opt/arm-gnu-toolchain-14.3/arm-none-eabi/include/sys/string.h" 1 3
# 176 "/opt/arm-gnu-toolchain-14.3/arm-none-eabi/include/string.h" 2 3


# 36 "/home/shrey_shah/STM32F103C8T6/BareMetal/Core/Inc/cmsis_gcc.h" 2
# 1 "/opt/arm-gnu-toolchain-14.3/arm-none-eabi/include/stdlib.h" 1 3
# 10 "/opt/arm-gnu-toolchain-14.3/arm-none-eabi/include/stdlib.h" 3
# 1 "/opt/arm-gnu-toolchain-14.3/arm-none-eabi/include/machine/ieeefp.h" 1 3
# 11 "/opt/arm-gnu-toolchain-14.3/arm-none-eabi/include/stdlib.h" 2 3





# 1 "/opt/arm-gnu-toolchain-14.3/lib/gcc/arm-none-eabi/14.3.1/include/stddef.h" 1 3 4
# 17 "/opt/arm-gnu-toolchain-14.3/arm-none-eabi/include/stdlib.h" 2 3



# 1 "/opt/arm-gnu-toolchain-14.3/arm-none-eabi/include/machine/stdlib.h" 1 3
# 21 "/opt/arm-gnu-toolchain-14.3/arm-none-eabi/include/stdlib.h" 2 3

# 1 "/opt/arm-gnu-toolchain-14.3/arm-none-eabi/include/alloca.h" 1 3
# 23 "/opt/arm-gnu-toolchain-14.3/arm-none-eabi/include/stdlib.h" 2 3
# 33 "/opt/arm-gnu-toolchain-14.3/arm-none-eabi/include/stdlib.h" 3


typedef struct
{
  int quot;
  int rem;
} div_t;

typedef struct
{
  long quot;
  long rem;
} ldiv_t;


typedef struct
{
  long long int quot;
  long long int rem;
} lldiv_t;




typedef int (*__compar_fn_t) (const void *, const void *);







int __locale_mb_cur_max (void);



void abort (void) __attribute__ ((__noreturn__));
int abs (int);

__uint32_t arc4random (void);
__uint32_t arc4random_uniform (__uint32_t);
void arc4random_buf (void *, size_t);

int atexit (void (*__func)(void));
double atof (const char *__nptr);

float atoff (const char *__nptr);

int atoi (const char *__nptr);
int _atoi_r (struct _reent *, const char *__nptr);
long atol (const char *__nptr);
long _atol_r (struct _reent *, const char *__nptr);
void * bsearch (const void *__key,
         const void *__base,
         size_t __nmemb,
         size_t __size,
         __compar_fn_t _compar);
void *calloc(size_t, size_t) __attribute__((__malloc__)) __attribute__((__warn_unused_result__))
      __attribute__((__alloc_size__(1, 2))) ;
div_t div (int __numer, int __denom);
void exit (int __status) __attribute__ ((__noreturn__));
void free (void *) ;
char * getenv (const char *__string);
char * _getenv_r (struct _reent *, const char *__string);



char * _findenv (const char *, int *);
char * _findenv_r (struct _reent *, const char *, int *);

extern char *suboptarg;
int getsubopt (char **, char * const *, char **);

long labs (long);
ldiv_t ldiv (long __numer, long __denom);
void *malloc(size_t) __attribute__((__malloc__)) __attribute__((__warn_unused_result__)) __attribute__((__alloc_size__(1))) ;
int mblen (const char *, size_t);
int _mblen_r (struct _reent *, const char *, size_t, _mbstate_t *);
int mbtowc (wchar_t *restrict, const char *restrict, size_t);
int _mbtowc_r (struct _reent *, wchar_t *restrict, const char *restrict, size_t, _mbstate_t *);
int wctomb (char *, wchar_t);
int _wctomb_r (struct _reent *, char *, wchar_t, _mbstate_t *);
size_t mbstowcs (wchar_t *restrict, const char *restrict, size_t);
size_t _mbstowcs_r (struct _reent *, wchar_t *restrict, const char *restrict, size_t, _mbstate_t *);
size_t wcstombs (char *restrict, const wchar_t *restrict, size_t);
size_t _wcstombs_r (struct _reent *, char *restrict, const wchar_t *restrict, size_t, _mbstate_t *);


char * mkdtemp (char *);






int mkstemp (char *);


int mkstemps (char *, int);


char * mktemp (char *) __attribute__ ((__deprecated__("the use of `mktemp' is dangerous; use `mkstemp' instead")));


char * _mkdtemp_r (struct _reent *, char *);
int _mkostemp_r (struct _reent *, char *, int);
int _mkostemps_r (struct _reent *, char *, int, int);
int _mkstemp_r (struct _reent *, char *);
int _mkstemps_r (struct _reent *, char *, int);
char * _mktemp_r (struct _reent *, char *) __attribute__ ((__deprecated__("the use of `mktemp' is dangerous; use `mkstemp' instead")));
void qsort (void *__base, size_t __nmemb, size_t __size, __compar_fn_t _compar);
int rand (void);
void *realloc(void *, size_t) __attribute__((__warn_unused_result__)) __attribute__((__alloc_size__(2))) ;

void *reallocarray(void *, size_t, size_t) __attribute__((__warn_unused_result__)) __attribute__((__alloc_size__(2, 3)));
void *reallocf(void *, size_t) __attribute__((__warn_unused_result__)) __attribute__((__alloc_size__(2)));


char * realpath (const char *restrict path, char *restrict resolved_path);


int rpmatch (const char *response);




void srand (unsigned __seed);
double strtod (const char *restrict __n, char **restrict __end_PTR);
double _strtod_r (struct _reent *,const char *restrict __n, char **restrict __end_PTR);

float strtof (const char *restrict __n, char **restrict __end_PTR);







long strtol (const char *restrict __n, char **restrict __end_PTR, int __base);
long _strtol_r (struct _reent *,const char *restrict __n, char **restrict __end_PTR, int __base);
unsigned long strtoul (const char *restrict __n, char **restrict __end_PTR, int __base);
unsigned long _strtoul_r (struct _reent *,const char *restrict __n, char **restrict __end_PTR, int __base);
# 191 "/opt/arm-gnu-toolchain-14.3/arm-none-eabi/include/stdlib.h" 3
int system (const char *__string);


long a64l (const char *__input);
char * l64a (long __input);
char * _l64a_r (struct _reent *,long __input);


int on_exit (void (*__func)(int, void *),void *__arg);


void _Exit (int __status) __attribute__ ((__noreturn__));


int putenv (char *__string);

int _putenv_r (struct _reent *, char *__string);
void * _reallocf_r (struct _reent *, void *, size_t);

int setenv (const char *__string, const char *__value, int __overwrite);

int _setenv_r (struct _reent *, const char *__string, const char *__value, int __overwrite);
# 225 "/opt/arm-gnu-toolchain-14.3/arm-none-eabi/include/stdlib.h" 3
char * __itoa (int, char *, int);
char * __utoa (unsigned, char *, int);

char * itoa (int, char *, int);
char * utoa (unsigned, char *, int);



int rand_r (unsigned *__seed);



double drand48 (void);
double _drand48_r (struct _reent *);
double erand48 (unsigned short [3]);
double _erand48_r (struct _reent *, unsigned short [3]);
long jrand48 (unsigned short [3]);
long _jrand48_r (struct _reent *, unsigned short [3]);
void lcong48 (unsigned short [7]);
void _lcong48_r (struct _reent *, unsigned short [7]);
long lrand48 (void);
long _lrand48_r (struct _reent *);
long mrand48 (void);
long _mrand48_r (struct _reent *);
long nrand48 (unsigned short [3]);
long _nrand48_r (struct _reent *, unsigned short [3]);
unsigned short *
       seed48 (unsigned short [3]);
unsigned short *
       _seed48_r (struct _reent *, unsigned short [3]);
void srand48 (long);
void _srand48_r (struct _reent *, long);


char * initstate (unsigned, char *, size_t);
long random (void);
char * setstate (char *);
void srandom (unsigned);


long long atoll (const char *__nptr);

long long _atoll_r (struct _reent *, const char *__nptr);

long long llabs (long long);
lldiv_t lldiv (long long __numer, long long __denom);
long long strtoll (const char *restrict __n, char **restrict __end_PTR, int __base);

long long _strtoll_r (struct _reent *, const char *restrict __n, char **restrict __end_PTR, int __base);

unsigned long long strtoull (const char *restrict __n, char **restrict __end_PTR, int __base);

unsigned long long _strtoull_r (struct _reent *, const char *restrict __n, char **restrict __end_PTR, int __base);



void cfree (void *);


int unsetenv (const char *__string);

int _unsetenv_r (struct _reent *, const char *__string);



int posix_memalign (void **, size_t, size_t) __attribute__((__nonnull__ (1)))
     __attribute__((__warn_unused_result__));


char * _dtoa_r (struct _reent *, double, int, int, int *, int*, char**);

void * _malloc_r (struct _reent *, size_t) ;
void * _calloc_r (struct _reent *, size_t, size_t) ;
void _free_r (struct _reent *, void *) ;
void * _realloc_r (struct _reent *, void *, size_t) ;
void _mstats_r (struct _reent *, char *);

int _system_r (struct _reent *, const char *);

void __eprintf (const char *, const char *, unsigned int, const char *);
# 314 "/opt/arm-gnu-toolchain-14.3/arm-none-eabi/include/stdlib.h" 3
void qsort_r (void *__base, size_t __nmemb, size_t __size, void *__thunk, int (*_compar)(void *, const void *, const void *))
             __asm__ ("" "__bsd_qsort_r");
# 324 "/opt/arm-gnu-toolchain-14.3/arm-none-eabi/include/stdlib.h" 3
extern long double _strtold_r (struct _reent *, const char *restrict, char **restrict);

extern long double strtold (const char *restrict, char **restrict);







void * aligned_alloc(size_t, size_t) __attribute__((__malloc__)) __attribute__((__alloc_align__(1)))
     __attribute__((__alloc_size__(2))) __attribute__((__warn_unused_result__));
int at_quick_exit(void (*)(void));
_Noreturn void
 quick_exit(int);



# 37 "/home/shrey_shah/STM32F103C8T6/BareMetal/Core/Inc/cmsis_gcc.h" 2



 
# 40 "/home/shrey_shah/STM32F103C8T6/BareMetal/Core/Inc/cmsis_gcc.h"
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wsign-conversion"
#pragma GCC diagnostic ignored "-Wconversion"
#pragma GCC diagnostic ignored "-Wunused-parameter"
# 85 "/home/shrey_shah/STM32F103C8T6/BareMetal/Core/Inc/cmsis_gcc.h"
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpacked"
#pragma GCC diagnostic ignored "-Wattributes"
  struct __attribute__((packed)) T_UINT32 { uint32_t v; };
#pragma GCC diagnostic pop



#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpacked"
#pragma GCC diagnostic ignored "-Wattributes"
  struct __attribute__((packed, aligned(1))) T_UINT16_WRITE { uint16_t v; };
#pragma GCC diagnostic pop



#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpacked"
#pragma GCC diagnostic ignored "-Wattributes"
  struct __attribute__((packed, aligned(1))) T_UINT16_READ { uint16_t v; };
#pragma GCC diagnostic pop



#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpacked"
#pragma GCC diagnostic ignored "-Wattributes"
  struct __attribute__((packed, aligned(1))) T_UINT32_WRITE { uint32_t v; };
#pragma GCC diagnostic pop



#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpacked"
#pragma GCC diagnostic ignored "-Wattributes"
  struct __attribute__((packed, aligned(1))) T_UINT32_READ { uint32_t v; };
#pragma GCC diagnostic pop
# 143 "/home/shrey_shah/STM32F103C8T6/BareMetal/Core/Inc/cmsis_gcc.h"
__attribute__((always_inline)) static inline void __enable_irq(void)
{
  __asm volatile ("cpsie i" : : : "memory");
}







__attribute__((always_inline)) static inline void __disable_irq(void)
{
  __asm volatile ("cpsid i" : : : "memory");
}







__attribute__((always_inline)) static inline uint32_t __get_CONTROL(void)
{
  uint32_t result;

  __asm volatile ("MRS %0, control" : "=r" (result) );
  return(result);
}
# 195 "/home/shrey_shah/STM32F103C8T6/BareMetal/Core/Inc/cmsis_gcc.h"
__attribute__((always_inline)) static inline void __set_CONTROL(uint32_t control)
{
  __asm volatile ("MSR control, %0" : : "r" (control) : "memory");
}
# 219 "/home/shrey_shah/STM32F103C8T6/BareMetal/Core/Inc/cmsis_gcc.h"
__attribute__((always_inline)) static inline uint32_t __get_IPSR(void)
{
  uint32_t result;

  __asm volatile ("MRS %0, ipsr" : "=r" (result) );
  return(result);
}







__attribute__((always_inline)) static inline uint32_t __get_APSR(void)
{
  uint32_t result;

  __asm volatile ("MRS %0, apsr" : "=r" (result) );
  return(result);
}







__attribute__((always_inline)) static inline uint32_t __get_xPSR(void)
{
  uint32_t result;

  __asm volatile ("MRS %0, xpsr" : "=r" (result) );
  return(result);
}







__attribute__((always_inline)) static inline uint32_t __get_PSP(void)
{
  uint32_t result;

  __asm volatile ("MRS %0, psp" : "=r" (result) );
  return(result);
}
# 291 "/home/shrey_shah/STM32F103C8T6/BareMetal/Core/Inc/cmsis_gcc.h"
__attribute__((always_inline)) static inline void __set_PSP(uint32_t topOfProcStack)
{
  __asm volatile ("MSR psp, %0" : : "r" (topOfProcStack) : );
}
# 315 "/home/shrey_shah/STM32F103C8T6/BareMetal/Core/Inc/cmsis_gcc.h"
__attribute__((always_inline)) static inline uint32_t __get_MSP(void)
{
  uint32_t result;

  __asm volatile ("MRS %0, msp" : "=r" (result) );
  return(result);
}
# 345 "/home/shrey_shah/STM32F103C8T6/BareMetal/Core/Inc/cmsis_gcc.h"
__attribute__((always_inline)) static inline void __set_MSP(uint32_t topOfMainStack)
{
  __asm volatile ("MSR msp, %0" : : "r" (topOfMainStack) : );
}
# 396 "/home/shrey_shah/STM32F103C8T6/BareMetal/Core/Inc/cmsis_gcc.h"
__attribute__((always_inline)) static inline uint32_t __get_PRIMASK(void)
{
  uint32_t result;

  __asm volatile ("MRS %0, primask" : "=r" (result) :: "memory");
  return(result);
}
# 426 "/home/shrey_shah/STM32F103C8T6/BareMetal/Core/Inc/cmsis_gcc.h"
__attribute__((always_inline)) static inline void __set_PRIMASK(uint32_t priMask)
{
  __asm volatile ("MSR primask, %0" : : "r" (priMask) : "memory");
}
# 453 "/home/shrey_shah/STM32F103C8T6/BareMetal/Core/Inc/cmsis_gcc.h"
__attribute__((always_inline)) static inline void __enable_fault_irq(void)
{
  __asm volatile ("cpsie f" : : : "memory");
}







__attribute__((always_inline)) static inline void __disable_fault_irq(void)
{
  __asm volatile ("cpsid f" : : : "memory");
}







__attribute__((always_inline)) static inline uint32_t __get_BASEPRI(void)
{
  uint32_t result;

  __asm volatile ("MRS %0, basepri" : "=r" (result) );
  return(result);
}
# 505 "/home/shrey_shah/STM32F103C8T6/BareMetal/Core/Inc/cmsis_gcc.h"
__attribute__((always_inline)) static inline void __set_BASEPRI(uint32_t basePri)
{
  __asm volatile ("MSR basepri, %0" : : "r" (basePri) : "memory");
}
# 530 "/home/shrey_shah/STM32F103C8T6/BareMetal/Core/Inc/cmsis_gcc.h"
__attribute__((always_inline)) static inline void __set_BASEPRI_MAX(uint32_t basePri)
{
  __asm volatile ("MSR basepri_max, %0" : : "r" (basePri) : "memory");
}







__attribute__((always_inline)) static inline uint32_t __get_FAULTMASK(void)
{
  uint32_t result;

  __asm volatile ("MRS %0, faultmask" : "=r" (result) );
  return(result);
}
# 571 "/home/shrey_shah/STM32F103C8T6/BareMetal/Core/Inc/cmsis_gcc.h"
__attribute__((always_inline)) static inline void __set_FAULTMASK(uint32_t faultMask)
{
  __asm volatile ("MSR faultmask, %0" : : "r" (faultMask) : "memory");
}
# 780 "/home/shrey_shah/STM32F103C8T6/BareMetal/Core/Inc/cmsis_gcc.h"
__attribute__((always_inline)) static inline uint32_t __get_FPSCR(void)
{
# 796 "/home/shrey_shah/STM32F103C8T6/BareMetal/Core/Inc/cmsis_gcc.h"
  return(0U);

}







__attribute__((always_inline)) static inline void __set_FPSCR(uint32_t fpscr)
{
# 819 "/home/shrey_shah/STM32F103C8T6/BareMetal/Core/Inc/cmsis_gcc.h"
  (void)fpscr;

}
# 880 "/home/shrey_shah/STM32F103C8T6/BareMetal/Core/Inc/cmsis_gcc.h"
__attribute__((always_inline)) static inline void __ISB(void)
{
  __asm volatile ("isb 0xF":::"memory");
}







__attribute__((always_inline)) static inline void __DSB(void)
{
  __asm volatile ("dsb 0xF":::"memory");
}







__attribute__((always_inline)) static inline void __DMB(void)
{
  __asm volatile ("dmb 0xF":::"memory");
}
# 914 "/home/shrey_shah/STM32F103C8T6/BareMetal/Core/Inc/cmsis_gcc.h"
__attribute__((always_inline)) static inline uint32_t __REV(uint32_t value)
{

  return __builtin_bswap32(value);






}
# 933 "/home/shrey_shah/STM32F103C8T6/BareMetal/Core/Inc/cmsis_gcc.h"
__attribute__((always_inline)) static inline uint32_t __REV16(uint32_t value)
{
  uint32_t result;

  __asm volatile ("rev16 %0, %1" : "=r" (result) : "r" (value) );
  return result;
}
# 948 "/home/shrey_shah/STM32F103C8T6/BareMetal/Core/Inc/cmsis_gcc.h"
__attribute__((always_inline)) static inline int16_t __REVSH(int16_t value)
{

  return (int16_t)__builtin_bswap16(value);






}
# 968 "/home/shrey_shah/STM32F103C8T6/BareMetal/Core/Inc/cmsis_gcc.h"
__attribute__((always_inline)) static inline uint32_t __ROR(uint32_t op1, uint32_t op2)
{
  op2 %= 32U;
  if (op2 == 0U)
  {
 return op1;
  }
  return (op1 >> op2) | (op1 << (32U - op2));
}
# 995 "/home/shrey_shah/STM32F103C8T6/BareMetal/Core/Inc/cmsis_gcc.h"
__attribute__((always_inline)) static inline uint32_t __RBIT(uint32_t value)
{
  uint32_t result;




   __asm volatile ("rbit %0, %1" : "=r" (result) : "r" (value) );
# 1015 "/home/shrey_shah/STM32F103C8T6/BareMetal/Core/Inc/cmsis_gcc.h"
  return result;
}
# 1038 "/home/shrey_shah/STM32F103C8T6/BareMetal/Core/Inc/cmsis_gcc.h"
__attribute__((always_inline)) static inline uint8_t __LDREXB(volatile uint8_t *addr)
{
 uint32_t result;


   __asm volatile ("ldrexb %0, %1" : "=r" (result) : "Q" (*addr) );






   return ((uint8_t) result);
}
# 1060 "/home/shrey_shah/STM32F103C8T6/BareMetal/Core/Inc/cmsis_gcc.h"
__attribute__((always_inline)) static inline uint16_t __LDREXH(volatile uint16_t *addr)
{
 uint32_t result;


   __asm volatile ("ldrexh %0, %1" : "=r" (result) : "Q" (*addr) );






   return ((uint16_t) result);
}
# 1082 "/home/shrey_shah/STM32F103C8T6/BareMetal/Core/Inc/cmsis_gcc.h"
__attribute__((always_inline)) static inline uint32_t __LDREXW(volatile uint32_t *addr)
{
 uint32_t result;

   __asm volatile ("ldrex %0, %1" : "=r" (result) : "Q" (*addr) );
   return(result);
}
# 1099 "/home/shrey_shah/STM32F103C8T6/BareMetal/Core/Inc/cmsis_gcc.h"
__attribute__((always_inline)) static inline uint32_t __STREXB(uint8_t value, volatile uint8_t *addr)
{
   uint32_t result;

   __asm volatile ("strexb %0, %2, %1" : "=&r" (result), "=Q" (*addr) : "r" ((uint32_t)value) );
   return(result);
}
# 1116 "/home/shrey_shah/STM32F103C8T6/BareMetal/Core/Inc/cmsis_gcc.h"
__attribute__((always_inline)) static inline uint32_t __STREXH(uint16_t value, volatile uint16_t *addr)
{
   uint32_t result;

   __asm volatile ("strexh %0, %2, %1" : "=&r" (result), "=Q" (*addr) : "r" ((uint32_t)value) );
   return(result);
}
# 1133 "/home/shrey_shah/STM32F103C8T6/BareMetal/Core/Inc/cmsis_gcc.h"
__attribute__((always_inline)) static inline uint32_t __STREXW(uint32_t value, volatile uint32_t *addr)
{
   uint32_t result;

   __asm volatile ("strex %0, %2, %1" : "=&r" (result), "=Q" (*addr) : "r" (value) );
   return(result);
}






__attribute__((always_inline)) static inline void __CLREX(void)
{
  __asm volatile ("clrex" ::: "memory");
}
# 1199 "/home/shrey_shah/STM32F103C8T6/BareMetal/Core/Inc/cmsis_gcc.h"
__attribute__((always_inline)) static inline uint32_t __RRX(uint32_t value)
{
  uint32_t result;

  __asm volatile ("rrx %0, %1" : "=r" (result) : "r" (value) );
  return(result);
}
# 1214 "/home/shrey_shah/STM32F103C8T6/BareMetal/Core/Inc/cmsis_gcc.h"
__attribute__((always_inline)) static inline uint8_t __LDRBT(volatile uint8_t *ptr)
{
 uint32_t result;


   __asm volatile ("ldrbt %0, %1" : "=r" (result) : "Q" (*ptr) );






   return ((uint8_t) result);
}
# 1236 "/home/shrey_shah/STM32F103C8T6/BareMetal/Core/Inc/cmsis_gcc.h"
__attribute__((always_inline)) static inline uint16_t __LDRHT(volatile uint16_t *ptr)
{
 uint32_t result;


   __asm volatile ("ldrht %0, %1" : "=r" (result) : "Q" (*ptr) );






   return ((uint16_t) result);
}
# 1258 "/home/shrey_shah/STM32F103C8T6/BareMetal/Core/Inc/cmsis_gcc.h"
__attribute__((always_inline)) static inline uint32_t __LDRT(volatile uint32_t *ptr)
{
 uint32_t result;

   __asm volatile ("ldrt %0, %1" : "=r" (result) : "Q" (*ptr) );
   return(result);
}
# 1273 "/home/shrey_shah/STM32F103C8T6/BareMetal/Core/Inc/cmsis_gcc.h"
__attribute__((always_inline)) static inline void __STRBT(uint8_t value, volatile uint8_t *ptr)
{
   __asm volatile ("strbt %1, %0" : "=Q" (*ptr) : "r" ((uint32_t)value) );
}
# 1285 "/home/shrey_shah/STM32F103C8T6/BareMetal/Core/Inc/cmsis_gcc.h"
__attribute__((always_inline)) static inline void __STRHT(uint16_t value, volatile uint16_t *ptr)
{
   __asm volatile ("strht %1, %0" : "=Q" (*ptr) : "r" ((uint32_t)value) );
}
# 1297 "/home/shrey_shah/STM32F103C8T6/BareMetal/Core/Inc/cmsis_gcc.h"
__attribute__((always_inline)) static inline void __STRT(uint32_t value, volatile uint32_t *ptr)
{
   __asm volatile ("strt %1, %0" : "=Q" (*ptr) : "r" (value) );
}
# 2097 "/home/shrey_shah/STM32F103C8T6/BareMetal/Core/Inc/cmsis_gcc.h"
#pragma GCC diagnostic pop
# 47 "/home/shrey_shah/STM32F103C8T6/BareMetal/Driver/reg_map.h" 2
# 1 "/home/shrey_shah/STM32F103C8T6/BareMetal/Core/Inc/stm32f1xx_helper.h" 1
# 48 "/home/shrey_shah/STM32F103C8T6/BareMetal/Driver/reg_map.h" 2


# 1 "/home/shrey_shah/STM32F103C8T6/BareMetal/Core/Inc/stm32f1xx_flash.h" 1
# 14 "/home/shrey_shah/STM32F103C8T6/BareMetal/Core/Inc/stm32f1xx_flash.h"
typedef struct {

    union {

        uint32_t REG;

        struct {
            uint32_t LATENCY: 3;
            uint32_t HLFCYA: 1;
            uint32_t PRFTBE: 1;
            uint32_t PRFTBS: 1;
            uint32_t reserved: 26;
        } BIT;
    } ACR;

    union {

        uint32_t REG;

        struct {
            uint32_t demo: 1;
        } BIT;
    } KEYR;

    union {

        uint32_t REG;

        struct {
            uint32_t demo: 1;
        } BIT;
    } OPTKEYR;

    union {

        uint32_t REG;

        struct {
            uint32_t demo: 1;
        } BIT;
    } SR;

    union {

        uint32_t REG;

        struct {
            uint32_t demo: 1;
        } BIT;
    } AR;

    uint32_t RESERVED;

    union {

        uint32_t REG;

        struct {
            uint32_t demo: 1;
        } BIT;
    } OBR;

    union {

        uint32_t REG;

        struct {
            uint32_t demo: 1;
        } BIT;
    } WRPR;
} FLASH_TypeDef;
# 51 "/home/shrey_shah/STM32F103C8T6/BareMetal/Driver/reg_map.h" 2
# 1 "/home/shrey_shah/STM32F103C8T6/BareMetal/Core/Inc/stm32f1xx_scb.h" 1
# 22 "/home/shrey_shah/STM32F103C8T6/BareMetal/Core/Inc/stm32f1xx_scb.h"
typedef struct {

 uint32_t CPUID;

 uint32_t ICSR;

 uint32_t VTOR;

 uint32_t AIRCR;

 uint32_t SCR;

 uint32_t CCR;

 uint32_t SHPR1;

 uint32_t SHPR2;

 uint32_t SHPR3;

 uint32_t SHCSR;

 uint32_t CFSR;

 uint32_t HFSR;

 uint32_t DFSR;

 uint32_t MMFAR;

 uint32_t BFAR;

 uint32_t AFSR;
} SCB_TypeDef;
# 52 "/home/shrey_shah/STM32F103C8T6/BareMetal/Driver/reg_map.h" 2
# 1 "/home/shrey_shah/STM32F103C8T6/BareMetal/Core/Inc/stm32f1xx_nvic.h" 1
# 17 "/home/shrey_shah/STM32F103C8T6/BareMetal/Core/Inc/stm32f1xx_nvic.h"
typedef struct {

 uint32_t ISER[8];

 uint32_t RESERVED_0[24];

 uint32_t ICER[8];

 uint32_t RESERVED_1[24];

 uint32_t ISPR[8];

 uint32_t RESERVED_2[24];

 uint32_t ICPR[8];

 uint32_t RESERVED_3[24];

 uint32_t IABR[8];

 uint32_t RESERVED_4[56];

 uint32_t IPR[60];

 uint32_t RESERVED_5[644];

 uint32_t STIR;
} NVIC_TypeDef;
# 53 "/home/shrey_shah/STM32F103C8T6/BareMetal/Driver/reg_map.h" 2
# 1 "/home/shrey_shah/STM32F103C8T6/BareMetal/Core/Inc/stm32f1xx_systick.h" 1
# 14 "/home/shrey_shah/STM32F103C8T6/BareMetal/Core/Inc/stm32f1xx_systick.h"
typedef struct {

 union{

  uint32_t REG;

  struct {
   volatile uint32_t EN: 1;
   volatile uint32_t TICKINT: 1;
   volatile uint32_t CLKSRC: 1;
   volatile uint32_t resereved_1: 13;
   volatile uint32_t CNTFLAG: 1;
   volatile uint32_t reserved_2: 15;
  } BIT;
 } CTRL;


 uint32_t LOAD: 24;


 uint32_t VAL: 24;


 union {

  uint32_t REG;

  struct {
   volatile uint32_t TENMS: 24;
   volatile uint32_t reserved: 6;
   volatile uint32_t SKEW: 1;
   volatile uint32_t NOREF: 1;
  } BIT;
 } CALIB;
} SysTick_TypeDef;
# 54 "/home/shrey_shah/STM32F103C8T6/BareMetal/Driver/reg_map.h" 2
# 1 "/home/shrey_shah/STM32F103C8T6/BareMetal/Core/Inc/stm32f1xx_watchdog.h" 1
# 14 "/home/shrey_shah/STM32F103C8T6/BareMetal/Core/Inc/stm32f1xx_watchdog.h"
typedef struct
{






 union {

  uint32_t REG;

  struct
  {

   uint32_t KEY: 16;
   uint32_t RESERVED: 16;
  } BIT;
 } KR;





 union
 {

  uint32_t REG;

  struct
  {
   uint32_t PR: 3;
   uint32_t RESERVED: 29;
  } BIT;
 } PR;





 union
 {

  uint32_t REG;

  struct
  {
   uint32_t RLR: 12;
   uint32_t RESERVED: 20;
  } BIT;
 } RLR;

 union
 {

  uint32_t REG;

  struct
  {

   uint32_t PVU: 1;

   uint32_t RVU: 1;
   uint32_t RESERVED: 30;
  } BIT;
 } SR;
} IWDG_TypeDef;



typedef struct {

 union
 {

  uint32_t REG;

  struct {
   volatile uint32_t T: 7;
   volatile uint32_t WDGA: 1;
   volatile uint32_t reserved: 24;
  } BIT;
 } CR;

 union
 {
  uint32_t REG;
  struct
  {
   volatile uint32_t W: 7;
   volatile uint32_t WDGTB: 2;
   volatile uint32_t EWI: 1;
   volatile uint32_t RESERVED: 22;
  } BIT;
 } CFGR;

 union
 {
  uint32_t REG;
  struct
  {

   uint32_t EWIF: 1;
   uint32_t RESERVED: 31;
  } BIT;
 } SR;
} WWDG_TypeDef;
# 55 "/home/shrey_shah/STM32F103C8T6/BareMetal/Driver/reg_map.h" 2





# 1 "/home/shrey_shah/STM32F103C8T6/BareMetal/Core/Inc/stm32f1xx_adc.h" 1
# 13 "/home/shrey_shah/STM32F103C8T6/BareMetal/Core/Inc/stm32f1xx_adc.h"
typedef struct
{

 union
 {

  uint32_t REG;

  struct
  {
   volatile uint32_t AWD : 1;
   volatile uint32_t EOC : 1;
   volatile uint32_t JEOC : 1;
   volatile uint32_t JSTRT : 1;
   volatile uint32_t STRT : 1;
  } BIT;
 } SR;


 union
 {

  uint32_t REG;

  struct
  {
   volatile uint32_t AWDCH : 5;
   volatile uint32_t EOCIE : 1;
   volatile uint32_t AWDIE : 1;
   volatile uint32_t JEOCIE : 1;
   volatile uint32_t SCAN : 1;
   volatile uint32_t AWDSGL : 1;
   volatile uint32_t JAUTO : 1;
   volatile uint32_t DISCEN : 1;
   volatile uint32_t JDISCEN : 1;
   volatile uint32_t DISCNUM : 3;
   volatile uint32_t DUALMOD : 4;
   volatile uint32_t reserved_1 : 2;
   volatile uint32_t JAWDEN : 1;
   volatile uint32_t AWDEN : 1;
   volatile uint32_t reserved_2 : 8;
  } BIT;
 } CR1;


 union
 {

  uint32_t REG;

  struct
  {
   volatile uint32_t ADON : 1;
   volatile uint32_t CONT : 1;
   volatile uint32_t CAL : 1;
   volatile uint32_t RSTCAL : 1;
   volatile uint32_t reserved_1 : 4;
   volatile uint32_t DMA : 1;
   volatile uint32_t reserved_2 : 2;
   volatile uint32_t ALIGN : 1;
   volatile uint32_t JEXTSEL : 3;
   volatile uint32_t JEXTTRIG : 1;
   volatile uint32_t reserved_3 : 1;
   volatile uint32_t EXTSEL : 3;
   volatile uint32_t EXTTRIG : 1;
   volatile uint32_t JSWSTART : 1;
   volatile uint32_t SWSTART : 1;
   volatile uint32_t TSVREFE : 1;
   volatile uint32_t reserved_4 : 8;
  } BIT;
 } CR2;


 union
 {

  uint32_t REG;

  struct
  {
   volatile uint32_t SMP10 : 3;
   volatile uint32_t SMP11 : 3;
   volatile uint32_t SMP12 : 3;
   volatile uint32_t SMP13 : 3;
   volatile uint32_t SMP14 : 3;
   volatile uint32_t SMP15 : 3;
   volatile uint32_t SMP16 : 3;
   volatile uint32_t SMP17 : 3;
   volatile uint32_t reserved : 8;
  } BIT;
 } SMPR1;


 union
 {

  uint32_t REG;

  struct
  {
   volatile uint32_t SMP0 : 3;
   volatile uint32_t SMP1 : 3;
   volatile uint32_t SMP2 : 3;
   volatile uint32_t SMP3 : 3;
   volatile uint32_t SMP4 : 3;
   volatile uint32_t SMP5 : 3;
   volatile uint32_t SMP6 : 3;
   volatile uint32_t SMP7 : 3;
   volatile uint32_t SMP8 : 3;
   volatile uint32_t SMP9 : 3;
   volatile uint32_t reserved : 2;
  } BIT;
 } SMPR2;


 union
 {

  uint32_t REG;

  struct
  {
   volatile uint32_t JOFFSET1 : 12;
   volatile uint32_t reserved : 20;
  } BIT;
 } JOFR1;


 union
 {

  uint32_t REG;

  struct
  {
   volatile uint32_t JOFFSET2 : 12;
   volatile uint32_t reserved : 20;
  } BIT;
 } JOFR2;


 union
 {

  uint32_t REG;

  struct
  {
   volatile uint32_t JOFFSET3 : 12;
   volatile uint32_t reserved : 20;
  } BIT;
 } JOFR3;


 union
 {

  uint32_t REG;

  struct
  {
   volatile uint32_t JOFFSET4 : 12;
   volatile uint32_t reserved : 20;
  } BIT;
 } JOFR4;


 union
 {

  uint32_t REG;

  struct
  {
   volatile uint32_t HT : 12;
   volatile uint32_t reserved : 20;
  } BIT;
 } HTR;


 union
 {

  uint32_t REG;

  struct
  {
   volatile uint32_t LT : 12;
   volatile uint32_t reserved : 20;
  } BIT;
 } LTR;


 union
 {

  uint32_t REG;

  struct
  {
   volatile uint32_t SQ13 : 5;
   volatile uint32_t SQ14 : 5;
   volatile uint32_t SQ15 : 5;
   volatile uint32_t SQ16 : 5;
   volatile uint32_t L : 5;
   volatile uint32_t reserved : 7;
  } BIT;
 } SQR1;


 union
 {

  uint32_t REG;

  struct
  {
   volatile uint32_t SQ7 : 5;
   volatile uint32_t SQ8 : 5;
   volatile uint32_t SQ9 : 5;
   volatile uint32_t SQ10 : 5;
   volatile uint32_t SQ11 : 5;
   volatile uint32_t SQ12 : 5;
   volatile uint32_t reserved : 2;
  } BIT;
 } SQR2;


 union
 {

  uint32_t REG;

  struct
  {
   volatile uint32_t SQ1 : 5;
   volatile uint32_t SQ2 : 5;
   volatile uint32_t SQ3 : 5;
   volatile uint32_t SQ4 : 5;
   volatile uint32_t SQ5 : 5;
   volatile uint32_t SQ6 : 5;
   volatile uint32_t reserved : 2;
  } BIT;
 } SQR3;


 union
 {

  uint32_t REG;

  struct
  {
   volatile uint32_t JSQ1 : 5;
   volatile uint32_t JSQ2 : 5;
   volatile uint32_t JSQ3 : 5;
   volatile uint32_t JSQ4 : 5;
   volatile uint32_t JL : 2;
   volatile uint32_t reserved : 10;
  } BIT;
 } JSQR;


 union
 {

  uint32_t REG;

  struct
  {
   volatile uint32_t JDATA1 : 16;
   volatile uint32_t reserved : 16;
  } BIT;
 } JDR1;


 union
 {

  uint32_t REG;

  struct
  {
   volatile uint32_t JDATA2 : 16;
   volatile uint32_t reserved : 16;
  } BIT;
 } JDR2;


 union
 {

  uint32_t REG;

  struct
  {
   volatile uint32_t JDATA3 : 16;
   volatile uint32_t reserved : 16;
  } BIT;
 } JDR3;


 union
 {

  uint32_t REG;

  struct
  {
   volatile uint32_t JDATA4 : 16;
   volatile uint32_t reserved : 16;
  } BIT;
 } JDR4;


 union
 {

  uint32_t REG;

  struct
  {
   volatile uint32_t ADC2DATA : 16;
   volatile uint32_t DATA : 16;
  } BIT;
 } DR;
} ADC_TypeDef;
# 61 "/home/shrey_shah/STM32F103C8T6/BareMetal/Driver/reg_map.h" 2
# 1 "/home/shrey_shah/STM32F103C8T6/BareMetal/Core/Inc/stm32f1xx_advtim.h" 1
# 14 "/home/shrey_shah/STM32F103C8T6/BareMetal/Core/Inc/stm32f1xx_advtim.h"
typedef struct {

 union {

        uint32_t REG;

        struct {
            volatile uint32_t CEN : 1;
            volatile uint32_t UDIS : 1;
            volatile uint32_t URS : 1;
            volatile uint32_t OPM : 1;
            volatile uint32_t DIR : 1;
            volatile uint32_t CMS : 2;
            volatile uint32_t ARPE : 1;
            volatile uint32_t CKD : 2;
            volatile uint32_t reserved : 22;
        } BIT;
 } CR1;

 union {

        uint32_t REG;

        struct {
            volatile uint32_t CCPC : 1;
            volatile uint32_t reserved_1 : 1;
            volatile uint32_t CCUS : 1;
            volatile uint32_t CDUS : 1;
            volatile uint32_t MMS : 3;
            volatile uint32_t TI1S : 1;
            volatile uint32_t OIS1 : 1;
            volatile uint32_t OIS1N : 1;
            volatile uint32_t OIS2 : 1;
            volatile uint32_t OIS2N : 1;
            volatile uint32_t OIS3 : 1;
            volatile uint32_t OIS3N : 1;
            volatile uint32_t OIS4 : 1;
            volatile uint32_t reserved_2 : 17;
        } BIT;
 } CR2;

 union {

        uint32_t REG;

        struct {
            volatile uint32_t SMS : 3;
            volatile uint32_t reserved_1 : 1;
            volatile uint32_t TS : 3;
            volatile uint32_t MSM : 1;
            volatile uint32_t ETF : 4;
            volatile uint32_t ETPS : 2;
            volatile uint32_t ECE : 1;
            volatile uint32_t ETP : 1;
   volatile uint32_t reserved_2 : 16;
        } BIT;
 } SMCR;

 union {

        uint32_t REG;

        struct {
            volatile uint32_t UIE : 1;
            volatile uint32_t CC1IE : 1;
            volatile uint32_t CC2IE : 1;
            volatile uint32_t CC3IE : 1;
            volatile uint32_t CC4IE : 1;
            volatile uint32_t COMIE : 1;
            volatile uint32_t TIE : 1;
            volatile uint32_t BIE : 1;
            volatile uint32_t UDE : 1;
            volatile uint32_t CC1DE : 1;
            volatile uint32_t CC2DE : 1;
            volatile uint32_t CC3DE : 1;
            volatile uint32_t CC4DE : 1;
            volatile uint32_t COMDE : 1;
            volatile uint32_t TDE : 1;
            volatile uint32_t reserved : 17;
        } BIT;
 } DIER;

 union {

        uint32_t REG;

        struct {
            volatile uint32_t UIF: 1;
            volatile uint32_t CC1IF: 1;
            volatile uint32_t CC2IF: 1;
            volatile uint32_t CC3IF: 1;
            volatile uint32_t CC4IF: 1;
            volatile uint32_t COMIF: 1;
            volatile uint32_t TIF: 1;
            volatile uint32_t BIF: 1;
            volatile uint32_t reserved_1: 1;
            volatile uint32_t CC1OF: 1;
            volatile uint32_t CC2OF: 1;
            volatile uint32_t CC3OF: 1;
            volatile uint32_t CC4OF: 1;
            volatile uint32_t reserved_2: 19;
        } BIT;
 } SR;

 union {

        uint32_t REG;

        struct {
            volatile uint32_t UG: 1;
            volatile uint32_t CC1G: 1;
            volatile uint32_t CC2G: 1;
            volatile uint32_t CC3G: 1;
            volatile uint32_t CC4G: 1;
            volatile uint32_t COMG: 1;
            volatile uint32_t TG: 1;
            volatile uint32_t BG: 1;
            volatile uint32_t reserved: 24;
        } BIT;
 } EGR;

 union {

        uint32_t REG;

        union {
            struct{
                volatile uint32_t CC1S: 2;
                volatile uint32_t OC1FE: 1;
                volatile uint32_t OC1PE: 1;
                volatile uint32_t OC1M: 3;
                volatile uint32_t OC1CE: 1;
                volatile uint32_t CC2S: 2;
                volatile uint32_t OC2FE: 1;
                volatile uint32_t OC2PE: 1;
                volatile uint32_t OC2M: 3;
                volatile uint32_t OC2CE: 1;
                volatile uint32_t reserved: 16;
            } OCM;
            struct{
                volatile uint32_t CC1S: 2;
                volatile uint32_t IC1PSC: 2;
                volatile uint32_t IC1F: 4;
                volatile uint32_t CC2S: 2;
                volatile uint32_t IC2PSC: 2;
                volatile uint32_t IC2F: 4;
                volatile uint32_t reserved: 16;
            } ICM;
        } BIT;
 } CCMR1;

 union {

        uint32_t REG;

        union {
            struct{
                volatile uint32_t CC3S: 2;
                volatile uint32_t OC3FE: 1;
                volatile uint32_t OC3PE: 1;
                volatile uint32_t OC3M: 3;
                volatile uint32_t OC3CE: 1;
                volatile uint32_t CC4S: 2;
                volatile uint32_t OC4FE: 1;
                volatile uint32_t OC4PE: 1;
                volatile uint32_t OC4M: 3;
                volatile uint32_t OC4CE: 1;
                volatile uint32_t reserved: 16;
            } OCM;
            struct{
                volatile uint32_t CC3S: 2;
                volatile uint32_t IC3PSC: 2;
                volatile uint32_t IC3F: 4;
                volatile uint32_t CC4S: 2;
                volatile uint32_t IC4PSC: 2;
                volatile uint32_t IC4F: 4;
                volatile uint32_t reserved: 16;
            } ICM;
        } BIT;
 } CCMR2;

 union {

        uint32_t REG;

        struct {
            volatile uint32_t CC1E: 1;
            volatile uint32_t CC1P: 1;
            volatile uint32_t CC1NE: 1;
            volatile uint32_t CC1NP: 1;
            volatile uint32_t CC2E: 1;
            volatile uint32_t CC2P: 1;
            volatile uint32_t CC2NE: 1;
            volatile uint32_t CC2NP: 1;
            volatile uint32_t CC3E: 1;
            volatile uint32_t CC3P: 1;
            volatile uint32_t CC3NE: 1;
            volatile uint32_t CC3NP: 1;
            volatile uint32_t CC4E: 1;
            volatile uint32_t CC4P: 1;
            volatile uint32_t reserved_1: 1;
            volatile uint32_t CC4NP: 1;
            volatile uint32_t reserved_2: 16;
        } BIT;
 } CCER;

 volatile uint32_t CNT;

    volatile uint32_t PSC;

 volatile uint32_t ARR;

    volatile uint32_t RCR;

    union {
        volatile uint32_t CC1_IN;
        volatile uint32_t CC1_OUT;
    } CCR1;

 union {
        volatile uint32_t CC2_IN;
        volatile uint32_t CC2_OUT;
 } CCR2;

 union {
        volatile uint32_t CC3_IN;
        volatile uint32_t CC3_OUT;
 } CCR3;

 union {
        volatile uint32_t CC3_IN;
        volatile uint32_t CC3_OUT;
 } CCR4;

 union {

        uint32_t REG;

        struct {
            volatile uint32_t DTG: 8;
            volatile uint32_t LOCK: 2;
            volatile uint32_t OSSI: 1;
            volatile uint32_t OSSR: 1;
            volatile uint32_t BKE: 1;
            volatile uint32_t BKP: 1;
            volatile uint32_t AOE: 1;
            volatile uint32_t MOE: 1;
            volatile uint32_t reserved: 16;
        } BIT;
 } BDTR;

 union {

        uint32_t REG;

        struct {
            volatile uint32_t DBA: 5;
            volatile uint32_t reserved_1: 3;
            volatile uint32_t DBL: 5;
            volatile uint32_t reserved_2: 19;
        } BIT;
 } DCR;

    volatile uint32_t DMAR;
} Adv_TIM_TypeDef;
# 62 "/home/shrey_shah/STM32F103C8T6/BareMetal/Driver/reg_map.h" 2
# 1 "/home/shrey_shah/STM32F103C8T6/BareMetal/Core/Inc/stm32f1xx_afio.h" 1
# 14 "/home/shrey_shah/STM32F103C8T6/BareMetal/Core/Inc/stm32f1xx_afio.h"
typedef struct {

    union {

        uint32_t REG;

        struct {
            volatile uint32_t PIN: 4;
            volatile uint32_t PORT: 3;
            volatile uint32_t EVOE: 1;
            volatile uint32_t reserved: 24;

        } BIT;
    } EVCR;

    union {

        uint32_t REG;

        struct {
            volatile uint32_t SPI1_REMAP: 1;
            volatile uint32_t I2C1_REMAP: 1;
            volatile uint32_t USART1_REMAP: 1;
            volatile uint32_t USART2_REMAP: 1;
            volatile uint32_t USART3_REMAP: 2;
            volatile uint32_t TIM1_REMAP: 2;
            volatile uint32_t TIM2_REMAP: 2;
            volatile uint32_t TIM3_REMAP: 2;
            volatile uint32_t TIM4_REMAP: 1;
            volatile uint32_t CAN_REMAP: 2;
            volatile uint32_t PD01_REMAP: 1;
            volatile uint32_t TIM5CH4_IREMAP: 1;
            volatile uint32_t ADC1_ETRGINJ_REMAP: 1;
            volatile uint32_t ADC1_ETGREG_REMAP: 1;
            volatile uint32_t ADC2_ETRGINJ_REMAP: 1;
            volatile uint32_t ADC2_ETGREG_REMAP: 1;
            volatile uint32_t reserved_1: 3;
            volatile uint32_t SWJ_CFG: 3;
            volatile uint32_t reserved_2: 5;
        } BIT;
    } MAPR;

    union {

        uint32_t REG;

        struct {
            volatile uint32_t EXTI0: 4;
            volatile uint32_t EXTI1: 4;
            volatile uint32_t EXTI2: 4;
            volatile uint32_t EXTI3: 4;
            volatile uint32_t reserved: 16;
        } BIT;
    } EXTICR1;

    union {

        uint32_t REG;

        struct {
            volatile uint32_t EXTI4: 4;
            volatile uint32_t EXTI5: 4;
            volatile uint32_t EXTI6: 4;
            volatile uint32_t EXTI7: 4;
            volatile uint32_t reserved: 16;

        } BIT;
    } EXTICR2;

    union {

        uint32_t REG;

        struct {
            volatile uint32_t EXTI8: 4;
            volatile uint32_t EXTI9: 4;
            volatile uint32_t EXTI10: 4;
            volatile uint32_t EXTI11: 4;
            volatile uint32_t reserved: 16;
        } BIT;
    } EXTICR3;

    union {

        uint32_t REG;

        struct {
            volatile uint32_t EXTI12: 4;
            volatile uint32_t EXTI13: 4;
            volatile uint32_t EXTI14: 4;
            volatile uint32_t EXTI15: 4;
            volatile uint32_t reserved: 16;
        } BIT;
    } EXTICR4;
} AFIO_TypeDef;
# 63 "/home/shrey_shah/STM32F103C8T6/BareMetal/Driver/reg_map.h" 2
# 1 "/home/shrey_shah/STM32F103C8T6/BareMetal/Core/Inc/stm32f1xx_dma.h" 1
# 14 "/home/shrey_shah/STM32F103C8T6/BareMetal/Core/Inc/stm32f1xx_dma.h"
typedef struct {

 union {

  uint32_t REG;

  struct {
   volatile uint32_t EN: 1;
   volatile uint32_t TCIE: 1;
   volatile uint32_t HTIE: 1;
   volatile uint32_t TEIE: 1;
   volatile uint32_t DIR: 1;
   volatile uint32_t CIRC: 1;
   volatile uint32_t PINC: 1;
   volatile uint32_t MINC: 1;
   volatile uint32_t PSIZE: 2;
   volatile uint32_t MSIZE: 2;
   volatile uint32_t PL: 2;
   volatile uint32_t MEM2MEM: 1;

   volatile uint32_t RESERVED: 17;
  } BIT;
 } CCR;

 union {

  uint32_t REG;

  struct {

   volatile uint32_t NDT0: 1;
   volatile uint32_t NDT1: 1;
   volatile uint32_t NDT2: 1;
   volatile uint32_t NDT3: 1;
   volatile uint32_t NDT4: 1;
   volatile uint32_t NDT5: 1;
   volatile uint32_t NDT6: 1;
   volatile uint32_t NDT7: 1;
   volatile uint32_t NDT8: 1;
   volatile uint32_t NDT9: 1;
   volatile uint32_t NDT10: 1;
   volatile uint32_t NDT11: 1;
   volatile uint32_t NDT12: 1;
   volatile uint32_t NDT13: 1;
   volatile uint32_t NDT14: 1;
   volatile uint32_t NDT15: 1;

   volatile uint32_t RESERVED: 16;
  } BIT;
 } CNDTR;

 union {

  uint32_t REG;

  struct {

   volatile uint32_t PA0: 1;
   volatile uint32_t PA1: 1;
   volatile uint32_t PA2: 1;
   volatile uint32_t PA3: 1;
   volatile uint32_t PA4: 1;
   volatile uint32_t PA5: 1;
   volatile uint32_t PA6: 1;
   volatile uint32_t PA7: 1;
   volatile uint32_t PA8: 1;
   volatile uint32_t PA9: 1;
   volatile uint32_t PA10: 1;
   volatile uint32_t PA11: 1;
   volatile uint32_t PA12: 1;
   volatile uint32_t PA13: 1;
   volatile uint32_t PA14: 1;
   volatile uint32_t PA15: 1;
   volatile uint32_t PA16: 1;
   volatile uint32_t PA17: 1;
   volatile uint32_t PA18: 1;
   volatile uint32_t PA19: 1;
   volatile uint32_t PA20: 1;
   volatile uint32_t PA21: 1;
   volatile uint32_t PA22: 1;
   volatile uint32_t PA23: 1;
   volatile uint32_t PA24: 1;
   volatile uint32_t PA25: 1;
   volatile uint32_t PA26: 1;
   volatile uint32_t PA27: 1;
   volatile uint32_t PA28: 1;
   volatile uint32_t PA29: 1;
   volatile uint32_t PA30: 1;
   volatile uint32_t PA31: 1;
  } BIT;
 } CPAR;

 union {

  uint32_t REG;

  struct {

   volatile uint32_t MA0: 1;
   volatile uint32_t MA1: 1;
   volatile uint32_t MA2: 1;
   volatile uint32_t MA3: 1;
   volatile uint32_t MA4: 1;
   volatile uint32_t MA5: 1;
   volatile uint32_t MA6: 1;
   volatile uint32_t MA7: 1;
   volatile uint32_t MA8: 1;
   volatile uint32_t MA9: 1;
   volatile uint32_t MA10: 1;
   volatile uint32_t MA11: 1;
   volatile uint32_t MA12: 1;
   volatile uint32_t MA13: 1;
   volatile uint32_t MA14: 1;
   volatile uint32_t MA15: 1;
   volatile uint32_t MA16: 1;
   volatile uint32_t MA17: 1;
   volatile uint32_t MA18: 1;
   volatile uint32_t MA19: 1;
   volatile uint32_t MA20: 1;
   volatile uint32_t MA21: 1;
   volatile uint32_t MA22: 1;
   volatile uint32_t MA23: 1;
   volatile uint32_t MA24: 1;
   volatile uint32_t MA25: 1;
   volatile uint32_t MA26: 1;
   volatile uint32_t MA27: 1;
   volatile uint32_t MA28: 1;
   volatile uint32_t MA29: 1;
   volatile uint32_t MA30: 1;
   volatile uint32_t MA31: 1;
  } BIT;
 } CMAR;
} DMA_Channel_TypeDef;


typedef struct {

 union {

  uint32_t REG;

  struct {

   volatile uint32_t GIF1: 1;
   volatile uint32_t TCIF1: 1;
   volatile uint32_t HTIF1: 1;
   volatile uint32_t TEIF1: 1;

   volatile uint32_t GIF2: 1;
   volatile uint32_t TCIF2: 1;
   volatile uint32_t HTIF2: 1;
   volatile uint32_t TEIF2: 1;

   volatile uint32_t GIF3: 1;
   volatile uint32_t TCIF3: 1;
   volatile uint32_t HTIF3: 1;
   volatile uint32_t TEIF3: 1;

   volatile uint32_t GIF4: 1;
   volatile uint32_t TCIF4: 1;
   volatile uint32_t HTIF4: 1;
   volatile uint32_t TEIF4: 1;

   volatile uint32_t GIF5: 1;
   volatile uint32_t TCIF5: 1;
   volatile uint32_t HTIF5: 1;
   volatile uint32_t TEIF5: 1;

   volatile uint32_t GIF6: 1;
   volatile uint32_t TCIF6: 1;
   volatile uint32_t HTIF6: 1;
   volatile uint32_t TEIF6: 1;

   volatile uint32_t GIF7: 1;
   volatile uint32_t TCIF7: 1;
   volatile uint32_t HTIF7: 1;
   volatile uint32_t TEIF7: 1;

   volatile uint32_t RESERVED: 4;
  } BIT;
 } ISR;

 union {

  uint32_t REG;

  struct {

   volatile uint32_t CGIF1: 1;
   volatile uint32_t CTCIF1: 1;
   volatile uint32_t CHTIF1: 1;
   volatile uint32_t CTEIF1: 1;

   volatile uint32_t CGIF2: 1;
   volatile uint32_t CTCIF2: 1;
   volatile uint32_t CHTIF2: 1;
   volatile uint32_t CTEIF2: 1;

   volatile uint32_t CGIF3: 1;
   volatile uint32_t CTCIF3: 1;
   volatile uint32_t CHTIF3: 1;
   volatile uint32_t CTEIF3: 1;

   volatile uint32_t CGIF4: 1;
   volatile uint32_t CTCIF4: 1;
   volatile uint32_t CHTIF4: 1;
   volatile uint32_t CTEIF4: 1;

   volatile uint32_t CGIF5: 1;
   volatile uint32_t CTCIF5: 1;
   volatile uint32_t CHTIF5: 1;
   volatile uint32_t CTEIF5: 1;

   volatile uint32_t CGIF6: 1;
   volatile uint32_t CTCIF6: 1;
   volatile uint32_t CHTIF6: 1;
   volatile uint32_t CTEIF6: 1;

   volatile uint32_t CGIF7: 1;
   volatile uint32_t CTCIF7: 1;
   volatile uint32_t CHTIF7: 1;
   volatile uint32_t CTEIF7: 1;

   volatile uint32_t RESERVED: 4;
  } BIT;
 } IFCR;

    DMA_Channel_TypeDef CHANNEL[7];
} DMA_TypeDef;
# 64 "/home/shrey_shah/STM32F103C8T6/BareMetal/Driver/reg_map.h" 2
# 1 "/home/shrey_shah/STM32F103C8T6/BareMetal/Core/Inc/stm32f1xx_exti.h" 1
# 14 "/home/shrey_shah/STM32F103C8T6/BareMetal/Core/Inc/stm32f1xx_exti.h"
typedef struct
{

    union {

        uint32_t REG;

        struct {
            volatile uint32_t MR0: 1;
            volatile uint32_t MR1: 1;
            volatile uint32_t MR2: 1;
            volatile uint32_t MR3: 1;
            volatile uint32_t MR4: 1;
            volatile uint32_t MR5: 1;
            volatile uint32_t MR6: 1;
            volatile uint32_t MR7: 1;
            volatile uint32_t MR8: 1;
            volatile uint32_t MR9: 1;
            volatile uint32_t MR10: 1;
            volatile uint32_t MR11: 1;
            volatile uint32_t MR12: 1;
            volatile uint32_t MR13: 1;
            volatile uint32_t MR14: 1;
            volatile uint32_t MR15: 1;
            volatile uint32_t MR16: 1;
            volatile uint32_t MR17: 1;
            volatile uint32_t MR18: 1;
            volatile uint32_t MR19: 1;
            volatile uint32_t reserved: 12;
        } BIT;
    } IMR;

    union {

        uint32_t REG;

        struct {
            volatile uint32_t MR0: 1;
            volatile uint32_t MR1: 1;
            volatile uint32_t MR2: 1;
            volatile uint32_t MR3: 1;
            volatile uint32_t MR4: 1;
            volatile uint32_t MR5: 1;
            volatile uint32_t MR6: 1;
            volatile uint32_t MR7: 1;
            volatile uint32_t MR8: 1;
            volatile uint32_t MR9: 1;
            volatile uint32_t MR10: 1;
            volatile uint32_t MR11: 1;
            volatile uint32_t MR12: 1;
            volatile uint32_t MR13: 1;
            volatile uint32_t MR14: 1;
            volatile uint32_t MR15: 1;
            volatile uint32_t MR16: 1;
            volatile uint32_t MR17: 1;
            volatile uint32_t MR18: 1;
            volatile uint32_t MR19: 1;
            volatile uint32_t reserved: 12;
        } BIT;
    } EMR;

    union {

        uint32_t REG;

        struct {
            volatile uint32_t TR0: 1;
            volatile uint32_t TR1: 1;
            volatile uint32_t TR2: 1;
            volatile uint32_t TR3: 1;
            volatile uint32_t TR4: 1;
            volatile uint32_t TR5: 1;
            volatile uint32_t TR6: 1;
            volatile uint32_t TR7: 1;
            volatile uint32_t TR8: 1;
            volatile uint32_t TR9: 1;
            volatile uint32_t TR10: 1;
            volatile uint32_t TR11: 1;
            volatile uint32_t TR12: 1;
            volatile uint32_t TR13: 1;
            volatile uint32_t TR14: 1;
            volatile uint32_t TR15: 1;
            volatile uint32_t TR16: 1;
            volatile uint32_t TR17: 1;
            volatile uint32_t TR18: 1;
            volatile uint32_t TR19: 1;
            volatile uint32_t reserved: 12;
        } BIT;
    } RTSR;

    union {

        uint32_t REG;

        struct {
            volatile uint32_t TR0: 1;
            volatile uint32_t TR1: 1;
            volatile uint32_t TR2: 1;
            volatile uint32_t TR3: 1;
            volatile uint32_t TR4: 1;
            volatile uint32_t TR5: 1;
            volatile uint32_t TR6: 1;
            volatile uint32_t TR7: 1;
            volatile uint32_t TR8: 1;
            volatile uint32_t TR9: 1;
            volatile uint32_t TR10: 1;
            volatile uint32_t TR11: 1;
            volatile uint32_t TR12: 1;
            volatile uint32_t TR13: 1;
            volatile uint32_t TR14: 1;
            volatile uint32_t TR15: 1;
            volatile uint32_t TR16: 1;
            volatile uint32_t TR17: 1;
            volatile uint32_t TR18: 1;
            volatile uint32_t TR19: 1;
            volatile uint32_t reserved: 12;
        } BIT;
    } FTSR;

    union {

        uint32_t REG;

        struct {
            volatile uint32_t SWIER0: 1;
            volatile uint32_t SWIER1: 1;
            volatile uint32_t SWIER2: 1;
            volatile uint32_t SWIER3: 1;
            volatile uint32_t SWIER4: 1;
            volatile uint32_t SWIER5: 1;
            volatile uint32_t SWIER6: 1;
            volatile uint32_t SWIER7: 1;
            volatile uint32_t SWIER8: 1;
            volatile uint32_t SWIER9: 1;
            volatile uint32_t SWIER10: 1;
            volatile uint32_t SWIER11: 1;
            volatile uint32_t SWIER12: 1;
            volatile uint32_t SWIER13: 1;
            volatile uint32_t SWIER14: 1;
            volatile uint32_t SWIER15: 1;
            volatile uint32_t SWIER16: 1;
            volatile uint32_t SWIER17: 1;
            volatile uint32_t SWIER18: 1;
            volatile uint32_t SWIER19: 1;
            volatile uint32_t reserved: 12;
        } BIT;
    } SWIER;

    union {

        uint32_t REG;

        struct {
            volatile uint32_t PR0: 1;
            volatile uint32_t PR1: 1;
            volatile uint32_t PR2: 1;
            volatile uint32_t PR3: 1;
            volatile uint32_t PR4: 1;
            volatile uint32_t PR5: 1;
            volatile uint32_t PR6: 1;
            volatile uint32_t PR7: 1;
            volatile uint32_t PR8: 1;
            volatile uint32_t PR9: 1;
            volatile uint32_t PR10: 1;
            volatile uint32_t PR11: 1;
            volatile uint32_t PR12: 1;
            volatile uint32_t PR13: 1;
            volatile uint32_t PR14: 1;
            volatile uint32_t PR15: 1;
            volatile uint32_t PR16: 1;
            volatile uint32_t PR17: 1;
            volatile uint32_t PR18: 1;
            volatile uint32_t PR19: 1;
            volatile uint32_t reserved: 12;
        } BIT;
    } PR;
} EXTI_REG_STRUCT;
# 65 "/home/shrey_shah/STM32F103C8T6/BareMetal/Driver/reg_map.h" 2
# 1 "/home/shrey_shah/STM32F103C8T6/BareMetal/Core/Inc/stm32f1xx_gpio.h" 1
# 14 "/home/shrey_shah/STM32F103C8T6/BareMetal/Core/Inc/stm32f1xx_gpio.h"
typedef struct {

    union {

        uint32_t REG;

        struct {
            volatile uint32_t MODE0 : 2;
            volatile uint32_t CNF0 : 2;
            volatile uint32_t MODE1 : 2;
            volatile uint32_t CNF1 : 2;
            volatile uint32_t MODE2 : 2;
            volatile uint32_t CNF2 : 2;
            volatile uint32_t MODE3 : 2;
            volatile uint32_t CNF3 : 2;
            volatile uint32_t MODE4 : 2;
            volatile uint32_t CNF4 : 2;
            volatile uint32_t MODE5 : 2;
            volatile uint32_t CNF5 : 2;
            volatile uint32_t MODE6 : 2;
            volatile uint32_t CNF6 : 2;
            volatile uint32_t MODE7 : 2;
            volatile uint32_t CNF7 : 2;
        } BIT;
    } CRL;

    union {

        uint32_t REG;

        struct {
            volatile uint32_t MODE8 : 2;
            volatile uint32_t CNF8 : 2;
            volatile uint32_t MODE9 : 2;
            volatile uint32_t CNF9 : 2;
            volatile uint32_t MODE10 : 2;
            volatile uint32_t CNF10 : 2;
            volatile uint32_t MODE11 : 2;
            volatile uint32_t CNF11 : 2;
            volatile uint32_t MODE12 : 2;
            volatile uint32_t CNF12 : 2;
            volatile uint32_t MODE13 : 2;
            volatile uint32_t CNF13 : 2;
            volatile uint32_t MODE14 : 2;
            volatile uint32_t CNF14 : 2;
            volatile uint32_t MODE15 : 2;
            volatile uint32_t CNF15 : 2;
        } BIT;
    } CRH;

    union {

        uint32_t REG;

        struct {
            volatile uint32_t IDR0 : 1;
            volatile uint32_t IDR1 : 1;
            volatile uint32_t IDR2 : 1;
            volatile uint32_t IDR3 : 1;
            volatile uint32_t IDR4 : 1;
            volatile uint32_t IDR5 : 1;
            volatile uint32_t IDR6 : 1;
            volatile uint32_t IDR7 : 1;
            volatile uint32_t IDR8 : 1;
            volatile uint32_t IDR9 : 1;
            volatile uint32_t IDR10 : 1;
            volatile uint32_t IDR11 : 1;
            volatile uint32_t IDR12 : 1;
            volatile uint32_t IDR13 : 1;
            volatile uint32_t IDR14 : 1;
            volatile uint32_t IDR15 : 1;
            volatile uint32_t reserved : 16;
        } BIT;
    } IDR;

    union {

        uint32_t REG;

        struct {
            volatile uint32_t ODR0 : 1;
            volatile uint32_t ODR1 : 1;
            volatile uint32_t ODR2 : 1;
            volatile uint32_t ODR3 : 1;
            volatile uint32_t ODR4 : 1;
            volatile uint32_t ODR5 : 1;
            volatile uint32_t ODR6 : 1;
            volatile uint32_t ODR7 : 1;
            volatile uint32_t ODR8 : 1;
            volatile uint32_t ODR9 : 1;
            volatile uint32_t ODR10 : 1;
            volatile uint32_t ODR11 : 1;
            volatile uint32_t ODR12 : 1;
            volatile uint32_t ODR13 : 1;
            volatile uint32_t ODR14 : 1;
            volatile uint32_t ODR15 : 1;
            volatile uint32_t reserved : 16;
        } BIT;
    } ODR;

    union {

        uint32_t REG;

        struct {
            volatile uint32_t BS0 : 1;
            volatile uint32_t BS1 : 1;
            volatile uint32_t BS2 : 1;
            volatile uint32_t BS3 : 1;
            volatile uint32_t BS4 : 1;
            volatile uint32_t BS5 : 1;
            volatile uint32_t BS6 : 1;
            volatile uint32_t BS7 : 1;
            volatile uint32_t BS8 : 1;
            volatile uint32_t BS9 : 1;
            volatile uint32_t BS10 : 1;
            volatile uint32_t BS11 : 1;
            volatile uint32_t BS12 : 1;
            volatile uint32_t BS13 : 1;
            volatile uint32_t BS14 : 1;
            volatile uint32_t BS15 : 1;
            volatile uint32_t BR0 : 1;
            volatile uint32_t BR1 : 1;
            volatile uint32_t BR2 : 1;
            volatile uint32_t BR3 : 1;
            volatile uint32_t BR4 : 1;
            volatile uint32_t BR5 : 1;
            volatile uint32_t BR6 : 1;
            volatile uint32_t BR7 : 1;
            volatile uint32_t BR8 : 1;
            volatile uint32_t BR9 : 1;
            volatile uint32_t BR10 : 1;
            volatile uint32_t BR11 : 1;
            volatile uint32_t BR12 : 1;
            volatile uint32_t BR13 : 1;
            volatile uint32_t BR14 : 1;
            volatile uint32_t BR15 : 1;
        } BIT;
    } BSRR;

    union {

        uint32_t REG;

        struct {
            volatile uint32_t BR0 : 1;
            volatile uint32_t BR1 : 1;
            volatile uint32_t BR2 : 1;
            volatile uint32_t BR3 : 1;
            volatile uint32_t BR4 : 1;
            volatile uint32_t BR5 : 1;
            volatile uint32_t BR6 : 1;
            volatile uint32_t BR7 : 1;
            volatile uint32_t BR8 : 1;
            volatile uint32_t BR9 : 1;
            volatile uint32_t BR10 : 1;
            volatile uint32_t BR11 : 1;
            volatile uint32_t BR12 : 1;
            volatile uint32_t BR13 : 1;
            volatile uint32_t BR14 : 1;
            volatile uint32_t BR15 : 1;
            volatile uint32_t reserved : 16;
        } BIT;
    } BRR;

    union {

        uint32_t REG;

        struct {
            volatile uint32_t LCK0 : 1;
            volatile uint32_t LCK1 : 1;
            volatile uint32_t LCK2 : 1;
            volatile uint32_t LCK3 : 1;
            volatile uint32_t LCK4 : 1;
            volatile uint32_t LCK5 : 1;
            volatile uint32_t LCK6 : 1;
            volatile uint32_t LCK7 : 1;
            volatile uint32_t LCK8 : 1;
            volatile uint32_t LCK9 : 1;
            volatile uint32_t LCK10 : 1;
            volatile uint32_t LCK11 : 1;
            volatile uint32_t LCK12 : 1;
            volatile uint32_t LCK13 : 1;
            volatile uint32_t LCK14 : 1;
            volatile uint32_t LCK15 : 1;
            volatile uint32_t LCKK : 1;
            volatile uint32_t reserved : 15;
        } BIT;
    } LCKR;
} GPIO_TypeDef;
# 66 "/home/shrey_shah/STM32F103C8T6/BareMetal/Driver/reg_map.h" 2
# 1 "/home/shrey_shah/STM32F103C8T6/BareMetal/Core/Inc/stm32f1xx_i2c.h" 1
# 14 "/home/shrey_shah/STM32F103C8T6/BareMetal/Core/Inc/stm32f1xx_i2c.h"
typedef struct {

 union {
  uint32_t REG;
  struct {

   volatile uint32_t PE: 1;

   volatile uint32_t SMBUS: 1;
   volatile uint32_t RESERVED_1: 1;
   volatile uint32_t SMBTYPE: 1;

   volatile uint32_t ENARP: 1;

   volatile uint32_t ENPEC: 1;

   volatile uint32_t ENGC: 1;

   volatile uint32_t NOSTRETCH: 1;

   volatile uint32_t START: 1;

   volatile uint32_t STOP: 1;

   volatile uint32_t ACK: 1;

   volatile uint32_t POS: 1;
   volatile uint32_t PEC: 1;
   volatile uint32_t ALERT: 1;
   volatile uint32_t RESERVED_2: 1;

   volatile uint32_t SWRST: 1;
   volatile uint32_t RESERVED_3: 16;
  } BIT;
 } CR1;

 union {
  uint32_t REG;
  struct {

   volatile uint32_t FREQ: 6;
   volatile uint32_t RESERVED_1: 2;

   volatile uint32_t ITERREN: 1;

   volatile uint32_t ITEVTEN: 1;

   volatile uint32_t ITBUFEN: 1;

   volatile uint32_t DMAEN: 1;

   volatile uint32_t LAST: 1;
   volatile uint32_t RESERVED_2: 19;
  } BIT;
 } CR2;

 union {
  uint32_t REG;
  struct {
   volatile uint32_t ADD0: 1;
   volatile uint32_t ADD1_7: 7;
   volatile uint32_t ADD8_9: 2;
   volatile uint32_t RESERVED_1: 5;
   volatile uint32_t ADDMODE: 1;
   volatile uint32_t RESERVED_2: 16;
  } BIT;
 } OAR1;

 union {
  uint32_t REG;
  struct {
   volatile uint32_t ENDUAL: 1;
   volatile uint32_t ADD2_1_7: 7;
   volatile uint32_t RESERVED: 24;
  } BIT;
 } OAR2;

 union {
  uint32_t REG;
  struct {
   volatile uint32_t DR: 8;
   volatile uint32_t RESERVED: 24;
  } BIT;
 } DR;

 union {
  uint32_t REG;
  struct {

   volatile uint32_t SB: 1;

   volatile uint32_t ADDR: 1;

   volatile uint32_t BTF: 1;

   volatile uint32_t ADD10: 1;

   volatile uint32_t STOPF: 1;
   volatile uint32_t RESERVED_1: 1;

   volatile uint32_t RxNE: 1;

   volatile uint32_t TxE: 1;

   volatile uint32_t BERR: 1;

   volatile uint32_t ARLO: 1;

   volatile uint32_t AF: 1;

   volatile uint32_t OVR: 1;
   volatile uint32_t PECERR: 1;
   volatile uint32_t RESERVED_2: 1;

   volatile uint32_t TIMEOUT: 1;
   volatile uint32_t SMBALERT: 1;
   volatile uint32_t RESERVED_3: 16;
  } BIT;
 } SR1;

 union {
  uint32_t REG;
  struct {
   volatile uint32_t MSL: 1;
   volatile uint32_t BUSY: 1;

   volatile uint32_t TRA: 1;
   volatile uint32_t RESERVED_1: 1;
   volatile uint32_t GENCALL: 1;
   volatile uint32_t SMBDEFAULT: 1;
   volatile uint32_t SMBHOST: 1;
   volatile uint32_t DUALF: 1;
   volatile uint32_t PEC: 8;
   volatile uint32_t RESERVED_2: 16;
  } BIT;
 } SR2;

 union {
  uint32_t REG;
  struct {
   volatile uint32_t CCR: 12;
   volatile uint32_t RESERVED_1: 2;

   volatile uint32_t DUTY: 1;

   volatile uint32_t F_S: 1;
   volatile uint32_t RESERVED_2: 16;
  } BIT;
 } CCR;

 union {
  uint32_t REG;
  struct {

   volatile uint32_t TRISE: 6;
   volatile uint32_t RESERVED: 26;
  } BIT;
 } TRISE;
} I2C_TypeDef;
# 67 "/home/shrey_shah/STM32F103C8T6/BareMetal/Driver/reg_map.h" 2
# 1 "/home/shrey_shah/STM32F103C8T6/BareMetal/Core/Inc/stm32f1xx_timer.h" 1
# 14 "/home/shrey_shah/STM32F103C8T6/BareMetal/Core/Inc/stm32f1xx_timer.h"
typedef struct {

 union {

  uint32_t REG;

  struct {
   volatile uint32_t CEN : 1;
   volatile uint32_t UDIS : 1;
   volatile uint32_t URS : 1;
   volatile uint32_t OPM : 1;
   volatile uint32_t DIR : 1;
   volatile uint32_t CMS : 2;
   volatile uint32_t ARPE : 1;
   volatile uint32_t CKD : 2;
   volatile uint32_t reserved : 22;
  } BIT;
 } CR1;

 union {

  uint32_t REG;

  struct {
   volatile uint32_t reserved_1 : 3;
   volatile uint32_t CCDS : 1;
   volatile uint32_t MMS : 3;
   volatile uint32_t TI1S : 1;
   volatile uint32_t reserved_2 : 24;
  } BIT;
 } CR2;

 union {

  uint32_t REG;

  struct {
   volatile uint32_t SMS : 3;
   volatile uint32_t reserved_1 : 1;
   volatile uint32_t TS : 3;
   volatile uint32_t MSM : 1;
   volatile uint32_t ETF : 4;
   volatile uint32_t ETPS : 2;
   volatile uint32_t ECE : 1;
   volatile uint32_t ETP : 1;
   volatile uint32_t reserved_2 : 16;
  } BIT;
 } SMCR;

 union {

  uint32_t REG;

  struct {
   volatile uint32_t UIE : 1;
   volatile uint32_t CC1IE : 1;
   volatile uint32_t CC2IE : 1;
   volatile uint32_t CC3IE : 1;
   volatile uint32_t CC4IE : 1;
   volatile uint32_t reserved_1 : 1;
   volatile uint32_t TIE : 1;
   volatile uint32_t reserved_2 : 1;
   volatile uint32_t UDE : 1;
   volatile uint32_t CC1DE : 1;
   volatile uint32_t CC2DE : 1;
   volatile uint32_t CC3DE : 1;
   volatile uint32_t CC4DE : 1;
   volatile uint32_t reserved_3 : 1;
   volatile uint32_t TDE : 1;
   volatile uint32_t reserved_4 : 17;
  } BIT;
 } DIER;

 union {

  uint32_t REG;

  struct {
   volatile uint32_t UIF: 1;
   volatile uint32_t CC1IF: 1;
   volatile uint32_t CC2IF: 1;
   volatile uint32_t CC3IF: 1;
   volatile uint32_t CC4IF: 1;
   volatile uint32_t reserved_1: 1;
   volatile uint32_t TIF: 1;
   volatile uint32_t reserved_2: 2;
   volatile uint32_t CC1OF: 1;
   volatile uint32_t CC2OF: 1;
   volatile uint32_t CC3OF: 1;
   volatile uint32_t CC4OF: 1;
   volatile uint32_t reserved_3: 19;
  } BIT;
 } SR;

 union {

  uint32_t REG;

  struct {
   volatile uint32_t UG: 1;
   volatile uint32_t CC1G: 1;
   volatile uint32_t CC2G: 1;
   volatile uint32_t CC3G: 1;
   volatile uint32_t CC4G: 1;
   volatile uint32_t reserved_1: 1;
   volatile uint32_t TG: 1;
   volatile uint32_t reserved_2: 25;
  } BIT;
 } EGR;

 union {

  uint32_t REG;

  union {
   struct{
    volatile uint32_t CC1S: 2;
    volatile uint32_t OC1FE: 1;
    volatile uint32_t OC1PE: 1;
    volatile uint32_t OC1M: 3;
    volatile uint32_t OC1CE: 1;
    volatile uint32_t CC2S: 2;
    volatile uint32_t OC2FE: 1;
    volatile uint32_t OC2PE: 1;
    volatile uint32_t OC2M: 3;
    volatile uint32_t OC2CE: 1;
    volatile uint32_t reserved: 16;
   } OCM;
   struct{
    volatile uint32_t CC1S: 2;
    volatile uint32_t IC1PSC: 2;
    volatile uint32_t IC1F: 4;
    volatile uint32_t CC2S: 2;
    volatile uint32_t IC2PSC: 2;
    volatile uint32_t IC2F: 4;
    volatile uint32_t reserved: 16;
   } ICM;
  } BIT;
 } CCMR1;

 union {

  uint32_t REG;

  union {
   struct{
    volatile uint32_t CC3S: 2;
    volatile uint32_t OC3FE: 1;
    volatile uint32_t OC3PE: 1;
    volatile uint32_t OC3M: 3;
    volatile uint32_t OC3CE: 1;
    volatile uint32_t CC4S: 2;
    volatile uint32_t OC4FE: 1;
    volatile uint32_t OC4PE: 1;
    volatile uint32_t OC4M: 3;
    volatile uint32_t OC4CE: 1;
    volatile uint32_t reserved: 16;
   } OCM;
   struct{
    volatile uint32_t CC3S: 2;
    volatile uint32_t IC3PSC: 2;
    volatile uint32_t IC3F: 4;
    volatile uint32_t CC4S: 2;
    volatile uint32_t IC4PSC: 2;
    volatile uint32_t IC4F: 4;
    volatile uint32_t reserved: 16;
   } ICM;
  } BIT;
 } CCMR2;

 union {

  uint32_t REG;

  struct {
   volatile uint32_t CC1E: 1;
   volatile uint32_t CC1P: 1;
   volatile uint32_t reserved_1: 2;
   volatile uint32_t CC2E: 1;
   volatile uint32_t CC2P: 1;
   volatile uint32_t reserved_2: 2;
   volatile uint32_t CC3E: 1;
   volatile uint32_t CC3P: 1;
   volatile uint32_t reserved_3: 2;
   volatile uint32_t CC4E: 1;
   volatile uint32_t CC4P: 1;
   volatile uint32_t reserved_4: 18;
  } BIT;
 } CCER;

 volatile uint32_t CNT;

 volatile uint32_t PSC;

 volatile uint32_t ARR;

 volatile uint32_t RESERVED_1;

 union {
  volatile uint32_t CC1_IN;
  volatile uint32_t CC1_OUT;
 } CCR1;

 union {
  volatile uint32_t CC2_IN;
  volatile uint32_t CC2_OUT;
 } CCR2;

 union {
  volatile uint32_t CC3_IN;
  volatile uint32_t CC3_OUT;
 } CCR3;

 union {
  volatile uint32_t CC4_IN;
  volatile uint32_t CC4_OUT;
 } CCR4;

 volatile uint32_t RESERVED_2;

 union {

  uint32_t REG;

  struct {
   volatile uint32_t DBA: 5;
   volatile uint32_t reserved_1: 3;
   volatile uint32_t DBL: 5;
   volatile uint32_t reserved_2: 19;
  } BIT;
 } DCR;

 volatile uint32_t DMAR;
} TIM_TypeDef;
# 68 "/home/shrey_shah/STM32F103C8T6/BareMetal/Driver/reg_map.h" 2
# 1 "/home/shrey_shah/STM32F103C8T6/BareMetal/Core/Inc/stm32f1xx_rcc.h" 1
# 14 "/home/shrey_shah/STM32F103C8T6/BareMetal/Core/Inc/stm32f1xx_rcc.h"
typedef struct {

 union {

  uint32_t REG;

  struct {
   volatile uint32_t HSION: 1;
   volatile uint32_t HSIRDY: 1;
   volatile uint32_t reserved_1: 1;
   volatile uint32_t HSITRIM: 5;
   volatile uint32_t HSICAL: 8;
   volatile uint32_t HSEON: 1;
   volatile uint32_t HSERDY: 1;
   volatile uint32_t HSEBYP: 1;
   volatile uint32_t CSSON: 1;
   volatile uint32_t reserved_2: 4;
   volatile uint32_t PLLON: 1;
   volatile uint32_t PLLRDY: 1;
   volatile uint32_t reserved_3: 6;
  } BIT;
 } CR;

 union {

  uint32_t REG;

  struct {
   volatile uint32_t SW: 2;
   volatile uint32_t SWS: 2;
   volatile uint32_t HPRE: 4;
   volatile uint32_t PPRE1: 3;
   volatile uint32_t PPRE2: 3;
   volatile uint32_t ADCPRE: 2;
   volatile uint32_t PLLSRC: 1;
   volatile uint32_t PLLXTPRE: 1;
   volatile uint32_t PLLMUL: 4;
   volatile uint32_t USBPRE: 1;
   volatile uint32_t reserved_1: 1;
   volatile uint32_t MCO: 3;
   volatile uint32_t reserved_2: 5;
  } BIT;
 } CFGR;

 union {

  uint32_t REG;

  struct {
   volatile uint32_t LSIRDYF: 1;
   volatile uint32_t LSERDYF: 1;
   volatile uint32_t HSIRDYF: 1;
   volatile uint32_t HSERDYF: 1;
   volatile uint32_t PLLRDYF: 1;
   volatile uint32_t reserved_1: 2;
   volatile uint32_t CSFF: 1;
   volatile uint32_t LSIRDYIE: 1;
   volatile uint32_t LSERDYIE: 1;
   volatile uint32_t HSIRDYIE: 1;
   volatile uint32_t HSERDYIE: 1;
   volatile uint32_t PLLRDYIE: 1;
   volatile uint32_t reserved_2: 3;
   volatile uint32_t LSIRDYC: 1;
   volatile uint32_t LSERDYC: 1;
   volatile uint32_t HSIRDYC: 1;
   volatile uint32_t HSERDYC: 1;
   volatile uint32_t PLLRDYC: 1;
   volatile uint32_t reserved_3: 2;
   volatile uint32_t CSSC: 1;
   volatile uint32_t reserved_4: 8;
  } BIT;
 } CIR;

 union {

  uint32_t REG;

  struct {
   volatile uint32_t AFIORST: 1;
   volatile uint32_t reserved_1: 1;
   volatile uint32_t IOPARST: 1;
   volatile uint32_t IOPBRST: 1;
   volatile uint32_t IOPCRST: 1;
   volatile uint32_t IOPDRST: 1;
   volatile uint32_t IOPERST: 1;
   volatile uint32_t IOPFRST: 1;
   volatile uint32_t IOPGRST: 1;
   volatile uint32_t ADC1RST: 1;
   volatile uint32_t ADC2RST: 1;
   volatile uint32_t TIM1RST: 1;
   volatile uint32_t SPI1RST: 1;
   volatile uint32_t TIM8RST: 1;
   volatile uint32_t USART1RST: 1;
   volatile uint32_t ADC3RST: 1;
   volatile uint32_t reserved_2: 3;
   volatile uint32_t TIM9RST: 1;
   volatile uint32_t TIM10RST: 1;
   volatile uint32_t TIM11RST: 1;
   volatile uint32_t reserved_3: 10;
  } BIT;
 } APB2RSTR;

 union {

  uint32_t REG;

  struct {
   volatile uint32_t TIM2RST: 1;
   volatile uint32_t TIM3RST: 1;
   volatile uint32_t TIM4RST: 1;
   volatile uint32_t TIM5RST: 1;
   volatile uint32_t TIM6RST: 1;
   volatile uint32_t TIM7RST: 1;
   volatile uint32_t TIM12RST: 1;
   volatile uint32_t TIM13RST: 1;
   volatile uint32_t TIM14RST: 1;
   volatile uint32_t reserved_1: 1;
   volatile uint32_t WWDGRST: 1;
   volatile uint32_t reserved_2: 2;
   volatile uint32_t SPI2RST: 1;
   volatile uint32_t SPI3RST: 1;
   volatile uint32_t reserved_3: 1;
   volatile uint32_t USART2RST: 1;
   volatile uint32_t USART3RST: 1;
   volatile uint32_t UART4RST: 1;
   volatile uint32_t UART5RST: 1;
   volatile uint32_t I2C1RST: 1;
   volatile uint32_t I2C2RST: 1;
   volatile uint32_t USBRST: 1;
   volatile uint32_t reserved_4: 1;
   volatile uint32_t CANRST: 1;
   volatile uint32_t reserved_5: 1;
   volatile uint32_t BKPRST: 1;
   volatile uint32_t PWRRST: 1;
   volatile uint32_t DACRST: 1;
   volatile uint32_t reserved_6: 2;
  } BIT;
 } APB1RSTR;

 union {

  uint32_t REG;

  struct {
   volatile uint32_t DMA1EN: 1;
   volatile uint32_t DMA2EN: 1;
   volatile uint32_t SRAMEN: 1;
   volatile uint32_t reserved_1: 1;
   volatile uint32_t FLITFEN: 1;
   volatile uint32_t reserved_2: 1;
   volatile uint32_t CRCEN: 1;
   volatile uint32_t reserved_3: 1;
   volatile uint32_t FSMCEN: 1;
   volatile uint32_t reserved_4: 1;
   volatile uint32_t SDIOEN: 1;
   volatile uint32_t reserved_5: 21;
  } BIT;
 } AHBENR;

 union {

  uint32_t REG;

  struct {
   volatile uint32_t AFIOEN: 1;
   volatile uint32_t reserved_1: 1;
   volatile uint32_t IOPAEN: 1;
   volatile uint32_t IOPBEN: 1;
   volatile uint32_t IOPCEN: 1;
   volatile uint32_t IOPDEN: 1;
   volatile uint32_t IOPEEN: 1;
   volatile uint32_t IOPFEN: 1;
   volatile uint32_t IOPGEN: 1;
   volatile uint32_t ADC1EN: 1;
   volatile uint32_t ADC2EN: 1;
   volatile uint32_t TIM1EN: 1;
   volatile uint32_t SPI1EN: 1;
   volatile uint32_t TIM8EN: 1;
   volatile uint32_t USART1EN: 1;
   volatile uint32_t ADC3EN: 1;
   volatile uint32_t reserved_2: 3;
   volatile uint32_t TIM9EN: 1;
   volatile uint32_t TIM10EN: 1;
   volatile uint32_t TIM11EN: 1;
   volatile uint32_t reserved_3: 10;
  } BIT;
 } APB2ENR;

 union {

  uint32_t REG;

  struct {
   volatile uint32_t TIM2EN: 1;
   volatile uint32_t TIM3EN: 1;
   volatile uint32_t TIM4EN: 1;
   volatile uint32_t TIM5EN: 1;
   volatile uint32_t TIM6EN: 1;
   volatile uint32_t TIM7EN: 1;
   volatile uint32_t TIM12EN: 1;
   volatile uint32_t TIM13EN: 1;
   volatile uint32_t TIM14EN: 1;
   volatile uint32_t reserved_1: 2;
   volatile uint32_t WWDGEN: 1;
   volatile uint32_t reserved_2: 2;
   volatile uint32_t SPI2EN: 1;
   volatile uint32_t SPI3EN: 1;
   volatile uint32_t reserved_3: 1;
   volatile uint32_t USART2EN: 1;
   volatile uint32_t USART3EN: 1;
   volatile uint32_t UART4EN: 1;
   volatile uint32_t UART5EN: 1;
   volatile uint32_t I2C1EN: 1;
   volatile uint32_t I2C2EN: 1;
   volatile uint32_t USBEN: 1;
   volatile uint32_t reserved_4: 1;
   volatile uint32_t CANEN: 1;
   volatile uint32_t reserved_5: 1;
   volatile uint32_t BKPEN: 1;
   volatile uint32_t PWREN: 1;
   volatile uint32_t DACEN: 1;
   volatile uint32_t reserved_6: 2;
  } BIT;
 } APB1ENR;

 union {

  uint32_t REG;

  struct {
   volatile uint32_t LSEON: 1;
   volatile uint32_t LSERDY: 1;
   volatile uint32_t LSEBYP: 1;
   volatile uint32_t reserved_1: 5;
   volatile uint32_t RTCSEL: 2;
   volatile uint32_t reserved_2: 5;
   volatile uint32_t RTCEN: 2;
   volatile uint32_t BDRST: 2;
   volatile uint32_t reserved_3: 15;
  } BIT;
 } BDCR;

 union {

  uint32_t REG;

  struct {
   volatile uint32_t LSION: 1;
   volatile uint32_t LSIRDY: 1;
   volatile uint32_t reserved_1: 22;
   volatile uint32_t RMVF: 1;
   volatile uint32_t reserved_2: 1;
   volatile uint32_t PINRSTF: 1;
   volatile uint32_t PORRSTF: 1;
   volatile uint32_t SFTRSTF: 1;
   volatile uint32_t IWDGRSTF: 1;
   volatile uint32_t WWDGRSTF: 1;
   volatile uint32_t LPWRRSTF: 1;
  } BIT;
 } CSR;
} RCC_TypeDef;
# 69 "/home/shrey_shah/STM32F103C8T6/BareMetal/Driver/reg_map.h" 2
# 1 "/home/shrey_shah/STM32F103C8T6/BareMetal/Core/Inc/stm32f1xx_usart.h" 1
# 14 "/home/shrey_shah/STM32F103C8T6/BareMetal/Core/Inc/stm32f1xx_usart.h"
typedef struct {

 union {

  uint32_t REG;

  struct {
   volatile uint32_t PE: 1;
   volatile uint32_t FE: 1;
   volatile uint32_t NE: 1;
   volatile uint32_t ORE: 1;
   volatile uint32_t IDLE: 1;
   volatile uint32_t RXNE: 1;
   volatile uint32_t TC: 1;
   volatile uint32_t TXE: 1;
   volatile uint32_t LBD: 1;
   volatile uint32_t CTS: 1;
   volatile uint32_t reserved: 22;
  } BIT;
 } SR;


    union {

  uint32_t REG;

  struct {
   volatile uint32_t DR: 9;
   volatile uint32_t reserved: 23;
  } BIT;
 } DR;


    union {

  uint32_t REG;

  struct {
   volatile uint32_t DIV_FRACTION: 4;
   volatile uint32_t DIV_MANTISSA: 12;
   volatile uint32_t reserved: 16;
  } BIT;
 } BRR;


    union {

  uint32_t REG;

  struct {
   volatile uint32_t SBK: 1;
   volatile uint32_t RWU: 1;
   volatile uint32_t RE: 1;
   volatile uint32_t TE: 1;
   volatile uint32_t IDLEIE: 1;
   volatile uint32_t RXNIE: 1;
   volatile uint32_t TCIE: 1;
   volatile uint32_t TXEIE: 1;
   volatile uint32_t PEIE: 1;
   volatile uint32_t PS: 1;
   volatile uint32_t PCE: 1;
   volatile uint32_t WAKE: 1;
   volatile uint32_t M: 1;
   volatile uint32_t UE: 1;
   volatile uint32_t reserved: 18;
  } BIT;
 } CR1;


    union {

  uint32_t REG;

  struct {
   volatile uint32_t ADD: 4;
   volatile uint32_t reserved_1: 1;
   volatile uint32_t LBDL: 1;
   volatile uint32_t LBDIE: 1;
   volatile uint32_t reserved_2: 1;
   volatile uint32_t LBCL: 1;
   volatile uint32_t CPHA: 1;
   volatile uint32_t CPOL: 1;
   volatile uint32_t CLKEN: 1;
   volatile uint32_t STOP: 2;
   volatile uint32_t LINEN: 2;
   volatile uint32_t reserved_3: 17;
  } BIT;
 } CR2;


    union {

  uint32_t REG;

  struct {
   volatile uint32_t EIE: 1;
   volatile uint32_t IREN: 1;
   volatile uint32_t IRLP: 1;
   volatile uint32_t HDSEL: 1;
   volatile uint32_t NACK: 1;
   volatile uint32_t SCEN: 1;
   volatile uint32_t DMAR: 1;
   volatile uint32_t DMAT: 1;
   volatile uint32_t RTSE: 1;
   volatile uint32_t CTSE: 1;
   volatile uint32_t CTSIE: 1;
   volatile uint32_t reserved: 17;
  } BIT;
 } CR3;


    union {

  uint32_t REG;

  struct {
   volatile uint32_t PSC: 8;
   volatile uint32_t GT: 8;
   volatile uint32_t reserved: 16;
  } BIT;
 } GTPR;

} USART_TypeDef;
# 70 "/home/shrey_shah/STM32F103C8T6/BareMetal/Driver/reg_map.h" 2
# 87 "/home/shrey_shah/STM32F103C8T6/BareMetal/Driver/reg_map.h"
typedef enum
{
 DRIVER_SUCCESS = (uint8_t) 0x00,
 DRIVER_FAIL = (uint8_t) 0x01
} driver_status_t;
# 176 "/home/shrey_shah/STM32F103C8T6/BareMetal/Driver/reg_map.h"
typedef uint8_t irq_t;
# 360 "/home/shrey_shah/STM32F103C8T6/BareMetal/Driver/reg_map.h"
typedef enum
{

 TIMx_CHANNEL_NONE = 0x00,

 TIMx_CHANNEL_1 = 0x01,

 TIMx_CHANNEL_2 = 0x02,

 TIMx_CHANNEL_3 = 0x04,

 TIMx_CHANNEL_4 = 0x08,

 TIMx_CHANNEL_ALL = 0x0F
} tim_channel_t;





typedef enum
{




 TIMx_MODE_NORMAL = 0x00,





 TIMx_MODE_ALTERNATE_INTERRUPT_DOWN_COUNTING = 0x01,





 TIMx_MODE_ALTERNATE_INTERRUPT_UP_COUNTING = 0x02,





 TIMx_MODE_ALTERNATE_INTERRUPT_BOTH_COUNTING = 0x03
} tim_count_mode_t;





typedef enum
{




 TIMx_DIR_COUNT_UP = 0x00,




 TIMx_DIR_COUNT_DOWN = 0x01
} tim_direction_t;





typedef enum
{




 TIMx_ARPE_DISABLE = 0x00,




 TIMx_ARPE_ENABLE = 0x01
} tim_arpe_t;





typedef enum
{




 TIMx_OPM_DISABLE = 0x00,




 TIMx_OPM_ENABLE = 0x01
} tim_opm_t;





typedef enum
{
# 476 "/home/shrey_shah/STM32F103C8T6/BareMetal/Driver/reg_map.h"
 TIMx_UPDATE_SOURCE_ANY = 0x00,







 TIMx_UPDATE_SOURCE_OVF_DMA = 0x01
} tim_update_source_t;


typedef enum
{
 TIMx_IRQ_DISABLE = 0x00,
 TIMx_IRQ_ENABLE = 0x01
} tim_irq_enable_t;





typedef enum
{

 TIMx_IRQ_OVF_UVF = 0x01,

 TIMx_IRQ_OUT_CMP_CH1 = 0x02,

 TIMx_IRQ_OUT_CMP_CH2 = 0x04,

 TIMx_IRQ_OUT_CMP_CH3 = 0x08,

 TIMx_IRQ_OUT_CMP_CH4 = 0x10,

 TIMx_IRQ_IN_CAP_CH1 = 0x02,

 TIMx_IRQ_IN_CAP_CH2 = 0x04,

 TIMx_IRQ_IN_CAP_CH3 = 0x08,

 TIMx_IRQ_IN_CAP_CH4 = 0x10,

 TIMx_IRQ_ALL = 0x1F
} tim_irq_t;
# 555 "/home/shrey_shah/STM32F103C8T6/BareMetal/Driver/reg_map.h"
typedef enum
{




 TIMx_CHANNEL_MODE_FREEZE = 0x00,





 TIMx_CHANNEL_MODE_SET_CH = 0x01,





 TIMx_CHANNEL_MODE_RESET_CH = 0x02,





 TIMx_CHANNEL_MODE_TOGGLE = 0x03,





 TIMx_CHANNEL_MODE_FORCE_RESET = 0x04,





 TIMx_CHANNEL_MODE_FORCE_SET = 0x05,





 TIMx_CHANNEL_MODE_PWM1 = 0x06,





 TIMx_CHANNEL_MODE_PWM2 = 0x07
} tim_channel_mode_t;





typedef enum
{




 TIMx_CHANNEL_CCS_OUTPUT = 0x00,




 TIMx_CHANNEL_CCS_INPUT_TIx = 0x01,
# 631 "/home/shrey_shah/STM32F103C8T6/BareMetal/Driver/reg_map.h"
 TIMx_CHANNEL_CCS_INPUT_TIx_1 = 0x02,





 TIMx_CHANNEL_CCS_INPUT_TRC = 0x03
} tim_channel_ccs_t;






typedef enum
{




 TIMx_CHANNEL_OC_PRELOAD_DISABLE = 0x00,




 TIMx_CHANNEL_OC_PRELOAD_ENABLE = 0x01
} tim_channel_oc_preload_t;







typedef enum
{





 TIMx_CHANNEL_OC_FAST_DISABLE = 0x00,







 TIMx_CHANNEL_OC_FAST_ENABLE = 0x01
} tim_channel_oc_fast_t;







typedef enum
{




 TIMx_CHANNEL_OC_CLEAR_DISABLE = 0x00,




 TIMx_CHANNEL_OC_CLEAR_ENABLE = 0x01
} tim_channel_oc_clear_t;






typedef enum
{




 TIMx_CHANNEL_POLARITY_HIGH = 0x00,




 TIMx_CHANNEL_POLARITY_LOW = 0x01
} tim_channel_polarity_t;
# 878 "/home/shrey_shah/STM32F103C8T6/BareMetal/Driver/reg_map.h"
__attribute__((always_inline)) static inline uint8_t Is_Power_Of_2(uint16_t num)
{

 return (num && (!(num & (num - 1))));
}






__attribute__((always_inline)) static inline uint16_t Logical_Round_Up_Power_Of_2(uint16_t n)
{

 if (n == 0)
  return 1;

 n--;


 n |= n >> 1;
 n |= n >> 2;
 n |= n >> 4;
 n |= n >> 8;

 return n + 1;
}






__attribute__((always_inline)) static inline uint32_t Round_Up_Power_of_2(uint32_t x)
{

 if (x == 0)
  return 0x00000001;
# 924 "/home/shrey_shah/STM32F103C8T6/BareMetal/Driver/reg_map.h"
 return (1 << (32 - __builtin_clz(x - 1)));
}
# 17 "/home/shrey_shah/STM32F103C8T6/BareMetal/Driver/GPIO/Inc/gpio_config.h" 2
# 1 "/home/shrey_shah/STM32F103C8T6/BareMetal/Driver/RCC/Inc/rcc.h" 1
# 22 "/home/shrey_shah/STM32F103C8T6/BareMetal/Driver/RCC/Inc/rcc.h"
# 1 "/home/shrey_shah/STM32F103C8T6/BareMetal/Driver/RCC/Inc/rcc_config.h" 1
# 25 "/home/shrey_shah/STM32F103C8T6/BareMetal/Driver/RCC/Inc/rcc_config.h"
typedef uint32_t freq_t;
# 119 "/home/shrey_shah/STM32F103C8T6/BareMetal/Driver/RCC/Inc/rcc_config.h"
typedef struct {



 uint8_t latency: 3;


 uint8_t prefetch: 5;
} rcc_flash_config_t;


typedef uint8_t rcc_bus_prescaler_t;



typedef struct
{





 rcc_bus_prescaler_t AHB: 4;





 rcc_bus_prescaler_t APB1: 3;





 rcc_bus_prescaler_t APB2: 3;
} rcc_bus_prescaler_config_t;


typedef uint8_t rcc_pll_src_t;
typedef uint8_t rcc_pll_mul_t;
typedef uint8_t rcc_pll_src_prescaler_t;



typedef struct {







 rcc_pll_mul_t mul_fact: 4;





 rcc_pll_src_t src: 1;





 rcc_pll_src_prescaler_t src_prescaler: 1;
} rcc_pll_config_t;


typedef uint8_t component_prescaler_t;



typedef struct {





 component_prescaler_t ADC: 2;





 component_prescaler_t USB: 1;
} rcc_component_prescaler_config_t;


typedef uint8_t system_clock_t;



typedef struct {





 system_clock_t clk_src;





 rcc_pll_config_t pll;
} rcc_sys_clk_config_t;





typedef struct {

 rcc_bus_prescaler_config_t bus_prescaler;

 rcc_sys_clk_config_t system;

 rcc_flash_config_t flash;

 rcc_component_prescaler_config_t component_prescaler;
} rcc_config_t;





typedef struct {

 freq_t Core;

 freq_t AHB;

 freq_t APB1;

 freq_t APB2;
} rcc_clk_freq_t;


extern const rcc_bus_prescaler_t __ahbPrescalerDriverMapping__[8];
extern const rcc_bus_prescaler_t __apbPrescalerDriverMapping__[4];





__attribute__((always_inline)) static inline void RCC_AFIO_Clk_Enable(void)
{

 ((RCC_TypeDef *) (0x40018000 + 0x00009000))->APB2ENR.REG |= (0x1UL << (0U));
}




__attribute__((always_inline)) static inline void RCC_AFIO_Clk_Disable(void)
{

 ((RCC_TypeDef *) (0x40018000 + 0x00009000))->APB2ENR.REG &= ~(0x1UL << (0U));
}





__attribute__((always_inline)) static inline void RCC_HSE_ON(void)
{

 ((RCC_TypeDef *) (0x40018000 + 0x00009000))->CR.REG |= (0x1UL << (16U));

 while(!(((RCC_TypeDef *) (0x40018000 + 0x00009000))->CR.REG & (0x1UL << (17U))));
}





__attribute__((always_inline)) static inline void RCC_HSE_OFF(void)
{

 ((RCC_TypeDef *) (0x40018000 + 0x00009000))->CR.REG &= ~(0x1UL << (16U));

 while(((RCC_TypeDef *) (0x40018000 + 0x00009000))->CR.REG & (0x1UL << (17U)));
}





__attribute__((always_inline)) static inline void RCC_PLL_ON(void)
{

 ((RCC_TypeDef *) (0x40018000 + 0x00009000))->CR.REG |= (0x1UL << (24U));

 while(!(((RCC_TypeDef *) (0x40018000 + 0x00009000))->CR.REG & (0x1UL << (25U))));
}





__attribute__((always_inline)) static inline void RCC_PLL_OFF(void)
{

 ((RCC_TypeDef *) (0x40018000 + 0x00009000))->CR.REG &= ~(0x1UL << (24U));

 while(((RCC_TypeDef *) (0x40018000 + 0x00009000))->CR.REG & (0x1UL << (25U)));
}






__attribute__((always_inline)) static inline void RCC_SysClkSrc_Set(const system_clock_t systemClk)
{

 ((RCC_TypeDef *) (0x40018000 + 0x00009000))->CFGR.REG |= (uint32_t)(((systemClk & 0x03) << (0U)));

 while((((RCC_TypeDef *) (0x40018000 + 0x00009000))->CFGR.REG & (0x3UL << (2U))) != ((systemClk & 0x03) << (2U)));
}





__attribute__((always_inline)) static inline system_clock_t RCC_SysClkSrc_Get(void)
{

 return ((system_clock_t) ((((RCC_TypeDef *) (0x40018000 + 0x00009000))->CFGR.REG & (0x3UL << (2U))) >> (2U)));
}






__attribute__((always_inline)) static inline rcc_pll_src_t RCC_PLLClkSrc_Get(void)
{

 return ((rcc_pll_src_t) ((((RCC_TypeDef *) (0x40018000 + 0x00009000))->CFGR.REG & (0x1UL << (16U))) >> (16U)));
}






__attribute__((always_inline)) static inline rcc_pll_src_prescaler_t RCC_PLLExtClkSrcPscRightShift_Get(void)
{

 return ((rcc_pll_src_prescaler_t) ((((RCC_TypeDef *) (0x40018000 + 0x00009000))->CFGR.REG & (0x1UL << (17U))) >> (17U)));
}






__attribute__((always_inline)) static inline rcc_pll_src_prescaler_t RCC_PLLClkSrcPscRightShift_Get(void)
{

 rcc_pll_src_t rccPLLSrc = RCC_PLLClkSrc_Get();

 rcc_pll_src_prescaler_t rccPLLSrcPrescaler = ((rcc_pll_src_prescaler_t) 0x00);

 switch(rccPLLSrc){

  case ((rcc_pll_src_t) 0x00):

   rccPLLSrcPrescaler = ((rcc_pll_src_prescaler_t) 0x01);
  break;

  case ((rcc_pll_src_t) 0x01):

   rccPLLSrcPrescaler = RCC_PLLExtClkSrcPscRightShift_Get();
  break;
 }

 return rccPLLSrcPrescaler;
}






__attribute__((always_inline)) static inline rcc_pll_mul_t RCC_PLLMulFactor_Get(void)
{

 return ((rcc_pll_mul_t) (((((RCC_TypeDef *) (0x40018000 + 0x00009000))->CFGR.REG & (0xFUL << (18U))) >> (18U)) + 2));
}
# 424 "/home/shrey_shah/STM32F103C8T6/BareMetal/Driver/RCC/Inc/rcc_config.h"
__attribute__((always_inline)) static inline rcc_bus_prescaler_t RCC_Get_AHB_Prescaler(void)
{
 uint32_t reg = ((RCC_TypeDef *) (0x40018000 + 0x00009000))->CFGR.REG;
 reg &= (0xFUL << (4U));
 reg >>= (4U);
 return (rcc_bus_prescaler_t) reg;
}
# 441 "/home/shrey_shah/STM32F103C8T6/BareMetal/Driver/RCC/Inc/rcc_config.h"
__attribute__((always_inline)) static inline rcc_bus_prescaler_t RCC_Get_APB1_Prescaler(void)
{
 uint32_t reg = ((RCC_TypeDef *) (0x40018000 + 0x00009000))->CFGR.REG;
 reg &= (0x7UL << (8U));
 reg >>= (8U);
 return (rcc_bus_prescaler_t) reg;
}
# 458 "/home/shrey_shah/STM32F103C8T6/BareMetal/Driver/RCC/Inc/rcc_config.h"
__attribute__((always_inline)) static inline rcc_bus_prescaler_t RCC_Get_APB2_Prescaler(void)
{
 uint32_t reg = ((RCC_TypeDef *) (0x40018000 + 0x00009000))->CFGR.REG;
 reg &= (0x7UL << (11U));
 reg >>= (11U);
 return (rcc_bus_prescaler_t) reg;
}





__attribute__((always_inline)) static inline rcc_bus_prescaler_t __RCC_AHBPscRightShift_Get__(void)
{

 rcc_bus_prescaler_t index = ((rcc_bus_prescaler_t) 0x00);

 rcc_bus_prescaler_t reg = RCC_Get_AHB_Prescaler();

 if(reg >= ((rcc_bus_prescaler_t) 0x08))
 {

  index = (reg & 0x07);
 }

 return __ahbPrescalerDriverMapping__[index];
}





__attribute__((always_inline)) static inline rcc_bus_prescaler_t __RCC_APB1PscRightShift_Get__(void)
{

 rcc_bus_prescaler_t index = ((rcc_bus_prescaler_t) 0x00);

 rcc_bus_prescaler_t reg = RCC_Get_APB1_Prescaler();

 if(reg >= ((rcc_bus_prescaler_t) 0x04))
 {

  index = (reg & 0x03);
 }

 return __apbPrescalerDriverMapping__[index];
}





__attribute__((always_inline)) static inline rcc_bus_prescaler_t __RCC_APB2PscRightShift_Get__(void)
{

 rcc_bus_prescaler_t index = ((rcc_bus_prescaler_t) 0x00);

 rcc_bus_prescaler_t reg = RCC_Get_APB2_Prescaler();

 if(reg >= ((rcc_bus_prescaler_t) 0x04))
 {

  index = (reg & 0x03);
 }

 return __apbPrescalerDriverMapping__[index];
}
# 534 "/home/shrey_shah/STM32F103C8T6/BareMetal/Driver/RCC/Inc/rcc_config.h"
driver_status_t RCC_CoreClockFreq_Update(freq_t* coreClockFrequencyHz);
# 543 "/home/shrey_shah/STM32F103C8T6/BareMetal/Driver/RCC/Inc/rcc_config.h"
driver_status_t RCC_AHBClockFreq_Update(freq_t* ahbClockFrequencyHz);
# 552 "/home/shrey_shah/STM32F103C8T6/BareMetal/Driver/RCC/Inc/rcc_config.h"
driver_status_t RCC_APB1ClockFreq_Update(freq_t* apb1ClockFrequencyHz);
# 561 "/home/shrey_shah/STM32F103C8T6/BareMetal/Driver/RCC/Inc/rcc_config.h"
driver_status_t RCC_APB2ClockFreq_Update(freq_t* apb2ClockFrequencyHz);






__attribute__((always_inline)) static inline void RCC_AHBClockFreqFromCoreClock_Update(const freq_t coreClockFrequencyHz, freq_t* ahbClockFrequencyHz){

 *ahbClockFrequencyHz = (coreClockFrequencyHz >> __RCC_AHBPscRightShift_Get__());
}






__attribute__((always_inline)) static inline void RCC_APB1ClockFreqFromAHBClock_Update(const freq_t ahbClockFrequencyHz, freq_t* apb1ClockFrequencyHz){

 *apb1ClockFrequencyHz = (ahbClockFrequencyHz >> __RCC_APB1PscRightShift_Get__());
}






__attribute__((always_inline)) static inline void RCC_APB2ClockFreqFromAHBClock_Update(const freq_t ahbClockFrequencyHz, freq_t* apb2ClockFrequencyHz){

 *apb2ClockFrequencyHz = (ahbClockFrequencyHz >> __RCC_APB2PscRightShift_Get__());
}
# 600 "/home/shrey_shah/STM32F103C8T6/BareMetal/Driver/RCC/Inc/rcc_config.h"
driver_status_t RCC_ClockFreq_Update(rcc_clk_freq_t* clkFreq);






__attribute__((always_inline)) static inline rcc_bus_prescaler_t RCC_AHBComputePrescaler(const rcc_bus_prescaler_t prescaler){
 return ((rcc_bus_prescaler_t) (0x01 << __RCC_AHBPscRightShift_Get__()));
}






__attribute__((always_inline)) static inline rcc_bus_prescaler_t RCC_APB1ComputePrescaler(const rcc_bus_prescaler_t prescaler){
 return ((rcc_bus_prescaler_t) (0x01 << __RCC_APB1PscRightShift_Get__()));
}






__attribute__((always_inline)) static inline rcc_bus_prescaler_t RCC_APB2ComputePrescaler(const rcc_bus_prescaler_t prescaler){
 return ((rcc_bus_prescaler_t) (0x01 << __RCC_APB2PscRightShift_Get__()));;
}
# 23 "/home/shrey_shah/STM32F103C8T6/BareMetal/Driver/RCC/Inc/rcc.h" 2


extern rcc_clk_freq_t __systemFrequency__;
# 36 "/home/shrey_shah/STM32F103C8T6/BareMetal/Driver/RCC/Inc/rcc.h"
driver_status_t RCC_FlashConfig(const rcc_flash_config_t flash, uint32_t* reg);
# 46 "/home/shrey_shah/STM32F103C8T6/BareMetal/Driver/RCC/Inc/rcc.h"
driver_status_t RCC_PLLConfig(const rcc_pll_config_t pllConfig, uint32_t* reg);
# 56 "/home/shrey_shah/STM32F103C8T6/BareMetal/Driver/RCC/Inc/rcc.h"
driver_status_t RCC_BusConfig(const rcc_bus_prescaler_config_t busPrescalerConfig, uint32_t* reg);
# 66 "/home/shrey_shah/STM32F103C8T6/BareMetal/Driver/RCC/Inc/rcc.h"
driver_status_t RCC_ComponentConfig(const rcc_component_prescaler_config_t componentPrescalerConfig, uint32_t* reg);
# 75 "/home/shrey_shah/STM32F103C8T6/BareMetal/Driver/RCC/Inc/rcc.h"
driver_status_t RCC_Config(const rcc_config_t* rccConfig);





void RCC_72MHz_FlashDefaultConfig(rcc_flash_config_t* flashConfig);





void RCC_72MHz_PLLDefaultConfig(rcc_pll_config_t* pllConfig);





void RCC_72MHz_SystemDefaultConfig(rcc_sys_clk_config_t* sysClkConfig);





void RCC_72MHz_BusPrescalerDefaultConfig(rcc_bus_prescaler_config_t* busPrescalerConfig);





void RCC_72MHz_ComponentPrescalerDefaultConfig(rcc_component_prescaler_config_t* componentPrescalerConfig);





void RCC_72MHz_LoadDefaultConfig(rcc_config_t* rccConfig);





__attribute__((always_inline)) static inline driver_status_t RCC_Config_72MHz(void)
{
 static rcc_config_t rcc72MHzConfig = {0};
 RCC_72MHz_LoadDefaultConfig(&rcc72MHzConfig);
 driver_status_t status = RCC_Config(&rcc72MHzConfig);
 do { if ((status) != DRIVER_SUCCESS) { return (status); } } while (0);
 return status;
}





__attribute__((always_inline)) static inline freq_t RCC_CoreClockFreq_Get(void)
{
 return (__systemFrequency__.Core);
}





__attribute__((always_inline)) static inline freq_t RCC_AHBClockFreq_Get(void)
{
 return (__systemFrequency__.AHB);
}





__attribute__((always_inline)) static inline freq_t RCC_APB1ClockFreq_Get(void)
{
 return (__systemFrequency__.APB1);
}





__attribute__((always_inline)) static inline freq_t RCC_APB2ClockFreq_Get(void)
{
 return (__systemFrequency__.APB2);
}
# 18 "/home/shrey_shah/STM32F103C8T6/BareMetal/Driver/GPIO/Inc/gpio_config.h" 2


typedef uint8_t gpio_port_t;
typedef uint16_t gpio_pin_t;
typedef uint8_t gpio_pin_mode_t;
typedef uint8_t gpio_pin_cnf_t;
typedef uint8_t gpio_exti_trigger_t;
typedef uint8_t gpio_exti_port_t;
# 87 "/home/shrey_shah/STM32F103C8T6/BareMetal/Driver/GPIO/Inc/gpio_config.h"
typedef struct
{

 gpio_pin_t pin;

 gpio_pin_mode_t mode : 2;

 gpio_pin_cnf_t config : 2;
} gpio_config_t;


extern const GPIO_TypeDef* const __gpioDriverMapping__[7];






__attribute__((always_inline)) static inline void __GPIO_enableClock__(const gpio_port_t thisPort)
{

 ((RCC_TypeDef *) (0x40018000 + 0x00009000))->APB2ENR.REG |= (1 << (2 + thisPort));
}





__attribute__((always_inline)) static inline void __GPIO_disableClock__(const gpio_port_t thisPort)
{

 ((RCC_TypeDef *) (0x40018000 + 0x00009000))->APB2ENR.REG &= ~(1 << (2 + thisPort));
}






__attribute__((always_inline)) static inline GPIO_TypeDef* __GPIO_getPort__(const gpio_port_t thisPort){

 return __gpioDriverMapping__[thisPort];
}






__attribute__((always_inline)) static inline uint8_t __GPIO_getPin__(const gpio_pin_t pinMask)
{

 return ((uint8_t) ((pinMask == ((gpio_pin_t) 0x0000))? (0x00) : (__builtin_ctz(pinMask))));
}







__attribute__((always_inline)) static inline void __GPIO_resetPullConfig__(const gpio_pin_t pinMask, uint32_t *gpioODRReg)
{
 *gpioODRReg &= ~(pinMask);
}
# 162 "/home/shrey_shah/STM32F103C8T6/BareMetal/Driver/GPIO/Inc/gpio_config.h"
void __GPIO_updateCtrlRegister__(const gpio_pin_t pinMask, const gpio_pin_mode_t gpioMode, gpio_pin_cnf_t gpioCnf, uint32_t *gpioCtrlReg);







void __GPIO_resetCtrlRegister__(const gpio_pin_t pinMask, uint32_t *gpioCtrlReg);
# 179 "/home/shrey_shah/STM32F103C8T6/BareMetal/Driver/GPIO/Inc/gpio_config.h"
void __GPIO_updatePullConfig__(const gpio_pin_t pinMask, gpio_pin_cnf_t gpioCnf, uint32_t *gpioODRReg);
# 7 "/home/shrey_shah/STM32F103C8T6/BareMetal/Driver/GPIO/Inc/gpio.h" 2
# 1 "/home/shrey_shah/STM32F103C8T6/BareMetal/Driver/GPIO/Inc/gpio_exti.h" 1
# 16 "/home/shrey_shah/STM32F103C8T6/BareMetal/Driver/GPIO/Inc/gpio_exti.h"
# 1 "/home/shrey_shah/STM32F103C8T6/BareMetal/Driver/nvic.h" 1
# 84 "/home/shrey_shah/STM32F103C8T6/BareMetal/Driver/nvic.h"
# 1 "/home/shrey_shah/STM32F103C8T6/BareMetal/Driver/reg_map.h" 1
# 85 "/home/shrey_shah/STM32F103C8T6/BareMetal/Driver/nvic.h" 2
# 98 "/home/shrey_shah/STM32F103C8T6/BareMetal/Driver/nvic.h"
typedef uint8_t priority_group_t;
typedef uint8_t priority_t;
typedef uint8_t sub_priority_t;
typedef uint32_t scb_exception_t;
# 185 "/home/shrey_shah/STM32F103C8T6/BareMetal/Driver/nvic.h"
__attribute__((always_inline)) static inline void NVIC_SetPriorityGrouping(priority_group_t priorityGroup)
{
 uint32_t reg = ((SCB_TypeDef *) (0xE000ED00))->AIRCR;


 reg &= ~((0xFFFFUL << 16U) | (7UL << 8U));
 reg |= (((0x5FA) << 16U) | (priorityGroup & 0x07) << 8U);
 ((SCB_TypeDef *) (0xE000ED00))->AIRCR = reg;
}





__attribute__((always_inline)) static inline priority_group_t NVIC_GetPriorityGrouping(void)
{
 uint32_t reg = ((SCB_TypeDef *) (0xE000ED00))->AIRCR & (7UL << 8U);
 reg >>= 8U;
 return ((priority_group_t) reg);
}





__attribute__((always_inline)) static inline void SCB_EnableException(scb_exception_t exception)
{

 ((SCB_TypeDef *) (0xE000ED00))->SHCSR |= exception;
}






__attribute__((always_inline)) static inline priority_t NVIC_GetPriority(const irq_t IRQn)
{
 uint32_t reg = ((NVIC_TypeDef *) (0xE000E100))->IPR[((IRQn) >> 2)];
 reg >>= (((IRQn) & 0x03) << 3);
 reg &= 0xFF;
 return ((priority_t) reg);
}
# 236 "/home/shrey_shah/STM32F103C8T6/BareMetal/Driver/nvic.h"
__attribute__((always_inline)) static inline void NVIC_SetPriority(const irq_t IRQn, const priority_t priority)
{
 uint32_t reg = ((NVIC_TypeDef *) (0xE000E100))->IPR[((IRQn) >> 2)];
 reg &= ~(0xFF << (((IRQn) & 0x03) << 3));
 reg |= (priority & 0xFF) << (((IRQn) & 0x03) << 3);
 ((NVIC_TypeDef *) (0xE000E100))->IPR[((IRQn) >> 2)] = reg;
}
# 251 "/home/shrey_shah/STM32F103C8T6/BareMetal/Driver/nvic.h"
__attribute__((always_inline)) static inline void NVIC_ConfigPriority(irq_t IRQn, priority_t priority, sub_priority_t subPriority)
{
 priority_t priorityGroup = NVIC_GetPriorityGrouping();
 NVIC_SetPriority(IRQn, (uint8_t) ((priority << (4 + priorityGroup)) | (subPriority << (4 - priorityGroup))));
}






__attribute__((always_inline)) static inline void NVIC_IRQEnable(uint8_t IRQn){

 ((NVIC_TypeDef *) (0xE000E100))->ISER[(IRQn) >> 5] |= (uint32_t) (1 << (IRQn & 0x1F));
}






__attribute__((always_inline)) static inline void NVIC_IRQDisable(uint8_t IRQn){

 ((NVIC_TypeDef *) (0xE000E100))->ICER[(IRQn) >> 5] |= (uint32_t) (1 << (IRQn & 0x1F));
}





__attribute__((always_inline)) static inline void NVIC_IRQ_SoftwareTrigger(uint8_t IRQn){

 ((NVIC_TypeDef *) (0xE000E100))->ISPR[(IRQn >> 5)] |= (uint32_t) (1 << (IRQn & 0x1F));
}
# 17 "/home/shrey_shah/STM32F103C8T6/BareMetal/Driver/GPIO/Inc/gpio_exti.h" 2






__attribute__((always_inline)) static inline void GPIO_EXTI_Enable(const gpio_pin_t pin){

 ((EXTI_REG_STRUCT *) (0x40010000 + 0x00000400))->IMR.REG |= pin;
}





__attribute__((always_inline)) static inline void GPIO_EXTI_Disable(const gpio_pin_t pin){

 ((EXTI_REG_STRUCT *) (0x40010000 + 0x00000400))->IMR.REG &= ~(pin);
}






__attribute__((always_inline)) static inline uint16_t GPIO_EXTI_IsTriggered(const gpio_pin_t pin){

 return (uint16_t) (((EXTI_REG_STRUCT *) (0x40010000 + 0x00000400))->PR.REG & pin);
}





__attribute__((always_inline)) static inline void GPIO_EXTI_Ack(const gpio_pin_t pin){

 ((EXTI_REG_STRUCT *) (0x40010000 + 0x00000400))->PR.REG |= pin;
}







__attribute__((always_inline)) static inline uint32_t* __GPIO_EXTI_GetCR__(const gpio_pin_t pin){

 return (uint32_t *) (&((AFIO_TypeDef *) (0x40010000))->EXTICR1.REG + (__GPIO_getPin__(pin) >> 2));
}
# 75 "/home/shrey_shah/STM32F103C8T6/BareMetal/Driver/GPIO/Inc/gpio_exti.h"
void GPIO_EXTI_MapPort(const gpio_port_t gpio, const gpio_pin_t pin, uint32_t* extiConfigReg);
# 84 "/home/shrey_shah/STM32F103C8T6/BareMetal/Driver/GPIO/Inc/gpio_exti.h"
void GPIO_EXTI_UnmapPort(const gpio_port_t gpio, const gpio_pin_t pin, uint32_t* extiConfigReg);






void GPIO_EXTI_SetTrigger(const gpio_pin_t pin, const gpio_exti_trigger_t trigger);






void GPIO_EXTI_ResetTrigger(const gpio_pin_t pin, const gpio_exti_trigger_t trigger);
# 111 "/home/shrey_shah/STM32F103C8T6/BareMetal/Driver/GPIO/Inc/gpio_exti.h"
driver_status_t GPIO_EXTI_Init(const gpio_port_t gpio, const gpio_pin_t pin, const gpio_exti_trigger_t trigger);
# 124 "/home/shrey_shah/STM32F103C8T6/BareMetal/Driver/GPIO/Inc/gpio_exti.h"
driver_status_t GPIO_EXTI_Deinit(const gpio_port_t gpio, const gpio_pin_t pin, const gpio_exti_trigger_t trigger);
# 8 "/home/shrey_shah/STM32F103C8T6/BareMetal/Driver/GPIO/Inc/gpio.h" 2
# 22 "/home/shrey_shah/STM32F103C8T6/BareMetal/Driver/GPIO/Inc/gpio.h"
__attribute__((always_inline)) static inline void GPIO_Set(gpio_port_t gpioPort, gpio_pin_t gpioPin){
 GPIO_TypeDef* GPIOx = __GPIO_getPort__(gpioPort);
 if(GPIOx != 
# 24 "/home/shrey_shah/STM32F103C8T6/BareMetal/Driver/GPIO/Inc/gpio.h" 3 4
            ((void *)0)
# 24 "/home/shrey_shah/STM32F103C8T6/BareMetal/Driver/GPIO/Inc/gpio.h"
                ){
  GPIOx->BSRR.REG |= gpioPin;
 }
}







__attribute__((always_inline)) static inline void GPIO_Reset(gpio_port_t gpioPort, gpio_pin_t gpioPin){
 GPIO_TypeDef* GPIOx = __GPIO_getPort__(gpioPort);
 if(GPIOx != 
# 37 "/home/shrey_shah/STM32F103C8T6/BareMetal/Driver/GPIO/Inc/gpio.h" 3 4
            ((void *)0)
# 37 "/home/shrey_shah/STM32F103C8T6/BareMetal/Driver/GPIO/Inc/gpio.h"
                )
  GPIOx->BRR.REG |= gpioPin;
}






__attribute__((always_inline)) static inline void GPIO_Toggle(gpio_port_t gpioPort, gpio_pin_t gpioPin){
 GPIO_TypeDef* GPIOx = __GPIO_getPort__(gpioPort);
 if(GPIOx != 
# 48 "/home/shrey_shah/STM32F103C8T6/BareMetal/Driver/GPIO/Inc/gpio.h" 3 4
            ((void *)0)
# 48 "/home/shrey_shah/STM32F103C8T6/BareMetal/Driver/GPIO/Inc/gpio.h"
                )
  GPIOx->ODR.REG ^= gpioPin;
}






__attribute__((always_inline)) static inline uint8_t GPIO_Get(gpio_port_t gpioPort, gpio_pin_t gpioPin){
 GPIO_TypeDef* GPIOx = __GPIO_getPort__(gpioPort);
 if(GPIOx != 
# 59 "/home/shrey_shah/STM32F103C8T6/BareMetal/Driver/GPIO/Inc/gpio.h" 3 4
            ((void *)0)
# 59 "/home/shrey_shah/STM32F103C8T6/BareMetal/Driver/GPIO/Inc/gpio.h"
                ){
  return ((uint8_t) ((GPIOx->IDR.REG & gpioPin) ? (0x01) : (0x00)));
 }
}





__attribute__((always_inline)) static inline void OB_LED_Set(void){
 GPIO_Reset(((gpio_port_t) 0x02), ((gpio_pin_t) 0x2000));
}





__attribute__((always_inline)) static inline void OB_LED_Reset(void){
 GPIO_Set(((gpio_port_t) 0x02), ((gpio_pin_t) 0x2000));
}





__attribute__((always_inline)) static inline void OB_LED_Toggle(void){
 GPIO_Toggle(((gpio_port_t) 0x02), ((gpio_pin_t) 0x2000));
}
# 97 "/home/shrey_shah/STM32F103C8T6/BareMetal/Driver/GPIO/Inc/gpio.h"
driver_status_t GPIO_Init(const gpio_port_t gpio, gpio_config_t* const gpioConfig);
# 107 "/home/shrey_shah/STM32F103C8T6/BareMetal/Driver/GPIO/Inc/gpio.h"
driver_status_t GPIO_LED_Init(const gpio_port_t gpio, gpio_config_t* gpioConfig);
# 117 "/home/shrey_shah/STM32F103C8T6/BareMetal/Driver/GPIO/Inc/gpio.h"
driver_status_t GPIO_Deinit(const gpio_port_t gpio, gpio_config_t* const gpioConfig);







driver_status_t OB_LED_Init(void);







driver_status_t OB_LED_Deinit(void);
# 3 "/home/shrey_shah/STM32F103C8T6/BareMetal/Driver/GPIO/Src/gpio.c" 2
# 19 "/home/shrey_shah/STM32F103C8T6/BareMetal/Driver/GPIO/Src/gpio.c"
driver_status_t GPIO_Init(const gpio_port_t gpio, gpio_config_t* const gpioConfig){

 GPIO_TypeDef* GPIOx = __GPIO_getPort__(gpio);
 if(GPIOx == 
# 22 "/home/shrey_shah/STM32F103C8T6/BareMetal/Driver/GPIO/Src/gpio.c" 3 4
            ((void *)0)
# 22 "/home/shrey_shah/STM32F103C8T6/BareMetal/Driver/GPIO/Src/gpio.c"
                ){
  return DRIVER_FAIL;
 }

 __GPIO_enableClock__(gpio);

 if((gpioConfig->config == ((gpio_pin_cnf_t) 0x02)) || (gpioConfig->config == ((gpio_pin_cnf_t) 0x03))){
  RCC_AFIO_Clk_Enable();
 }

 uint32_t gpioX_CRH = GPIOx->CRH.REG;
 uint32_t gpioX_CRL = GPIOx->CRL.REG;
 uint32_t gpioX_ODR = GPIOx->ODR.REG;
 gpio_pin_t pinMask = gpioConfig->pin;
 uint8_t regStatus = 0x00;

 while(pinMask){

  gpio_pin_t currentPin = (gpio_pin_t) (pinMask & -pinMask);

  if(__GPIO_getPin__(currentPin) > 7){
   __GPIO_updateCtrlRegister__(currentPin, gpioConfig->mode, gpioConfig->config, &gpioX_CRH);
   regStatus |= ((uint8_t) 0x02);
  }

  else{
   __GPIO_updateCtrlRegister__(currentPin, gpioConfig->mode, gpioConfig->config, &gpioX_CRL);
   regStatus |= ((uint8_t) 0x01);
  }

  if((gpioConfig->mode == ((gpio_pin_mode_t) 0x00)) && (((gpioConfig->config) == ((gpio_pin_cnf_t) 0x03) || (gpioConfig->config) == ((gpio_pin_cnf_t) 0x02)))){
   __GPIO_updatePullConfig__(currentPin, gpioConfig->config, &gpioX_ODR);
   regStatus |= ((uint8_t) 0x04);
  }

  pinMask &= ~currentPin;
 }

 if(regStatus & ((uint8_t) 0x02))
  GPIOx->CRH.REG = gpioX_CRH;
 if(regStatus & ((uint8_t) 0x01))
  GPIOx->CRL.REG = gpioX_CRL;
 if(regStatus & ((uint8_t) 0x04))
  GPIOx->ODR.REG = gpioX_ODR;

 return DRIVER_SUCCESS;
}
# 78 "/home/shrey_shah/STM32F103C8T6/BareMetal/Driver/GPIO/Src/gpio.c"
driver_status_t GPIO_Deinit(const gpio_port_t gpio, gpio_config_t* const gpioConfig){

 GPIO_TypeDef* GPIOx = __GPIO_getPort__(gpio);
 if(GPIOx == 
# 81 "/home/shrey_shah/STM32F103C8T6/BareMetal/Driver/GPIO/Src/gpio.c" 3 4
            ((void *)0)
# 81 "/home/shrey_shah/STM32F103C8T6/BareMetal/Driver/GPIO/Src/gpio.c"
                ){
  return DRIVER_FAIL;
 }

 uint32_t gpioX_CRH = GPIOx->CRH.REG;
 uint32_t gpioX_CRL = GPIOx->CRL.REG;
 uint32_t gpioX_ODR = GPIOx->ODR.REG;
 gpio_pin_t pinMask = gpioConfig->pin;
 uint8_t regStatus = 0x00;

 while(pinMask){

  gpio_pin_t currentPin = (gpio_pin_t) (pinMask & -pinMask);

  if(__GPIO_getPin__(currentPin) > 7){
   __GPIO_resetCtrlRegister__(currentPin, &gpioX_CRH);
   regStatus |= ((uint8_t) 0x02);
  }

  else{
   __GPIO_resetCtrlRegister__(currentPin, &gpioX_CRL);
   regStatus |= ((uint8_t) 0x01);
  }

  if((gpioConfig->mode == ((gpio_pin_mode_t) 0x00)) && (((gpioConfig->config) == ((gpio_pin_cnf_t) 0x03) || (gpioConfig->config) == ((gpio_pin_cnf_t) 0x02)))){
   __GPIO_resetPullConfig__(currentPin, &gpioX_ODR);
   regStatus |= ((uint8_t) 0x04);
  }

  pinMask &= ~currentPin;
 }

 if(regStatus & ((uint8_t) 0x02))
  GPIOx->CRH.REG = gpioX_CRH;
 if(regStatus & ((uint8_t) 0x01))
  GPIOx->CRL.REG = gpioX_CRL;
 if(regStatus & ((uint8_t) 0x04))
  GPIOx->ODR.REG = gpioX_ODR;
 return DRIVER_SUCCESS;
}
# 130 "/home/shrey_shah/STM32F103C8T6/BareMetal/Driver/GPIO/Src/gpio.c"
driver_status_t GPIO_LED_Init(const gpio_port_t gpio, gpio_config_t* gpioConfig){

 GPIO_TypeDef* GPIOx = __GPIO_getPort__(gpio);
 if(GPIOx == 
# 133 "/home/shrey_shah/STM32F103C8T6/BareMetal/Driver/GPIO/Src/gpio.c" 3 4
            ((void *)0)
# 133 "/home/shrey_shah/STM32F103C8T6/BareMetal/Driver/GPIO/Src/gpio.c"
                ){
  return DRIVER_FAIL;
 }

 gpioConfig->mode = ((gpio_pin_mode_t) 0x01);
 gpioConfig->config = ((gpio_pin_cnf_t) 0x00);

 return GPIO_Init(gpio, gpioConfig);
}







driver_status_t OB_LED_Init(void){

 gpio_config_t obLedConfig = {
  .pin = ((gpio_pin_t) 0x2000),
  .mode = ((gpio_pin_mode_t) 0x02),
  .config = ((gpio_pin_cnf_t) 0x00)
 };

 return GPIO_Init(((gpio_port_t) 0x02), &obLedConfig);
}







driver_status_t OB_LED_Deinit(void){

 gpio_config_t obLedConfig = {
  .pin = ((gpio_pin_t) 0x2000),
  .mode = ((gpio_pin_mode_t) 0x02),
  .config = ((gpio_pin_cnf_t) 0x00)
 };

 return GPIO_Deinit(((gpio_port_t) 0x02), &obLedConfig);
}
