#define _GNU_SOURCE
#include <link.h>
#include <string.h>
#include <pthread.h>
#include <dlfcn.h>

typedef int tg_file_test(const char*,int);
typedef const char*tg_get_user_runtime_dir(void);
typedef char*tg_build_filename(const char*,...);
typedef void tg_free(void*);
enum mycookie:unsigned char{
	mycookie_misc,
	mycookie_libglib,
	mycookie_libgtk
};

static tg_file_test*real_g_file_test,fake_g_file_test;

unsigned la_version(unsigned){
	return LAV_CURRENT;
}

unsigned la_objopen(struct link_map*map,long,ElfW(Addr)*cookie){
	const char *libpath=map->l_name;
	unsigned long libpathlen=strlen(libpath),i;
#define ifsuffix(suffix) if(!(__builtin_usubl_overflow(libpathlen,sizeof suffix-1,&i)||memcmp(suffix,&libpath[i],sizeof suffix-1)))
	ifsuffix("/libglib-2.0.so.0"){
		*(enum mycookie*)cookie=mycookie_libglib;
		return LA_FLG_BINDTO;
	}
	ifsuffix("/libgtk-3.so.0"){
		*(enum mycookie*)cookie=mycookie_libgtk;
		return LA_FLG_BINDFROM;
	}
#undef ifsuffix
	*(enum mycookie*)cookie=mycookie_misc;
	return 0;
}

ElfW(Addr)
#ifdef _LP64
la_symbind64
#else
la_symbind32
#endif
(ElfW(Sym)*sym,unsigned,ElfW(Addr)*refcookie,ElfW(Addr)*defcookie,unsigned*,const char*symname){
	unsigned long result=sym->st_value;
	if(!real_g_file_test&&*(enum mycookie*)refcookie==mycookie_libgtk&&*(enum mycookie*)defcookie==mycookie_libglib&&!strcmp("g_file_test",symname)){
		real_g_file_test=(tg_file_test*)result;
		result=(unsigned long)fake_g_file_test;
	}
	return result;
}

static int fake_g_file_test(const char*path,int test_type){
	static char*fakepath;
	if(16!=test_type||1==(unsigned long)fakepath)goto vanilla;
	static pthread_mutex_t m=PTHREAD_MUTEX_INITIALIZER;
	if(pthread_mutex_lock(&m))__builtin_trap();
	static tg_free*real_g_free;
	switch((unsigned long)fakepath){
	case 1:
		goto unlock_and_vanilla;
	case 0:
		void*h=dlmopen(LM_ID_BASE,"libglib-2.0.so.0",RTLD_NOW|RTLD_NOLOAD);
		if(!h)__builtin_trap();
		fakepath=(tg_build_filename*){dlsym(h,"g_build_filename")}(
			(tg_get_user_runtime_dir*){dlsym(h,"g_get_user_runtime_dir")}(),
			"flatpak-info",
			nullptr
		);
		real_g_free=dlsym(h,"g_free");
	}
	if(strcmp(path,fakepath))goto unlock_and_vanilla;
	char*oldfakepath=fakepath;
	fakepath=(char*)1;
	if(pthread_mutex_unlock(&m))__builtin_trap();
	real_g_free(oldfakepath);
	return 0;
unlock_and_vanilla:
	if(pthread_mutex_unlock(&m))__builtin_trap();
vanilla:
	return real_g_file_test(path,test_type);
}
