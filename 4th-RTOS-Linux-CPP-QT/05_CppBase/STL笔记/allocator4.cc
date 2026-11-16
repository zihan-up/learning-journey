
template <class _Tp>
class allocator {
  typedef alloc _Alloc;          // The underlying allocator.
public:
  typedef size_t     size_type;
  typedef ptrdiff_t  difference_type;
  typedef _Tp*       pointer;
  typedef const _Tp* const_pointer;
  typedef _Tp&       reference;
  typedef const _Tp& const_reference;
  typedef _Tp        value_type;

  template <class _Tp1> struct rebind {
    typedef allocator<_Tp1> other;
  };

  allocator() __STL_NOTHROW {}
  allocator(const allocator&) __STL_NOTHROW {}
  template <class _Tp1> allocator(const allocator<_Tp1>&) __STL_NOTHROW {}
  ~allocator() __STL_NOTHROW {}

  pointer address(reference __x) const { return &__x; }
  const_pointer address(const_reference __x) const { return &__x; }


  _Tp* allocate(size_type __n, const void* = 0) 
  {
    return __n != 0 ? static_cast<_Tp*>(_Alloc::allocate(__n * sizeof(_Tp))) : nullptr;
  }

  // __p is not permitted to be a null pointer.
  void deallocate(pointer __p, size_type __n)
    { _Alloc::deallocate(__p, __n * sizeof(_Tp)); }

  size_type max_size() const __STL_NOTHROW 
    { return size_t(-1) / sizeof(_Tp); }

  void construct(pointer __p, const _Tp& __val) { new(__p) _Tp(__val); }
  void destroy(pointer __p) { __p->~_Tp(); }
};





//---------------------------------------------------------------------------------







//一级空间配置器
# ifdef __USE_MALLOC
typedef __malloc_alloc_template<0> malloc_alloc;
typedef malloc_alloc alloc;
template <int __inst>
class __malloc_alloc_template 
{
public:
  static void* allocate(size_t __n)
  {
      void* __result = malloc(__n);
      if (0 == __result) 
        __result = _S_oom_malloc(__n);

      return __result;
  }
  
   static void deallocate(void* __p, size_t /* __n */)
  {
      free(__p);
  }

};

//二级空间配置器（默认的空间配置器）
#else
typedef __default_alloc_template<__NODE_ALLOCATOR_THREADS, 0> alloc;
template <bool threads, int inst>
class __default_alloc_template {
public:
	 static void* allocate(size_t __n)
	 {
		void* __ret = 0;
		if (__n > 128) 
		{
			 _ret = malloc_alloc::allocate(__n);//malloc
		}
		else//核心点：搞清楚else里面怎么实现
		{
			//16维的自由链表 + 内存池（认为128以下的空间是小片空间）
			//1、如果频繁的申请小片空间与释放小片空间，就会导致申请与释放非常的频繁，会导致
			//效率不高
			//2、频繁申请空间与释放空间，会带来内存碎片的问题，也就是空间的利用率不高
			//3、频繁申请的时候，会在用户态与内核态之间进行频繁的切换，会导致时间开销比较大
			
		}

    return __ret;
  };


    static void deallocate(void* __p, size_t __n)
	{
		if (__n > 128)
			malloc_alloc::deallocate(__p, __n);//free
		else 
		{
			//二级空间配置器的第二个部分，回收空间的时候，将节点重新挂回对应的自由链表
			_Obj**  __my_free_list = _S_free_list + _S_freelist_index(__n);//_S_free_list[3]
			_Obj* __q = (_Obj*)__p;
			__q -> _M_free_list_link = *__my_free_list;
			*__my_free_list = __q;
		}
	}
};

#endif

//第一个分支：也就是一级空间配置器，底层申请空间的时候使用的是malloc申请堆空间
//第二个分支：也就是二级空间配置器（默认的空间配置器），如果申请的大小大于128的时候，底层会使用malloc申请堆空间，如果申请的空间小于128，16维度的自由链表 + 内存池的思想


union _Obj 
{
	union _Obj* _M_free_list_link;
    char _M_client_data[1];    /* The client sees this.        */
};

enum {_ALIGN = 8};
enum {_MAX_BYTES = 128};
enum {_NFREELISTS = 16}; 


typename __default_alloc_template::_Obj*  __default_alloc_template::_S_free_list[
# if defined(__SUNPRO_CC) || defined(__GNUC__) || defined(__HP_aCC)
    _NFREELISTS
# else
    __default_alloc_template<__threads, __inst>::_NFREELISTS
# endif
] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, };


template <class _Tp>
class allocator {
	typedef alloc _Alloc;
public:	
     //申请空间
	_Tp* allocate(size_type __n, const void * = 0) {
		return __n != 0 ? static_cast<_Tp*>(_Alloc::allocate(__n * sizeof(_Tp))) : nullptr;
  }	
  
    //释放空间
    void deallocate(pointer __p, size_type __n)
    { 
		_Alloc::deallocate(__p, __n * sizeof(_Tp));
	}
	
	//构建对象
	void construct(pointer __p, const _Tp& __val) 
	{ 
	    //定位new表达式，也就是在指定的空间上构建对象
		new(__p) _Tp(__val); 
	}
	
	//销毁对象
	void destroy(pointer __p)
	{ 
		__p->~_Tp(); 
	}
};







//------------------------研究空间配置器的源码过程--------------------------
enum {_ALIGN = 8};
enum {_MAX_BYTES = 128};
enum {_NFREELISTS = 16}; 


char* __default_alloc_template::_S_start_free = nullptr;

char* __default_alloc_template::_S_end_free = nullptr;

size_t __default_alloc_template::_S_heap_size = 0;


_Obj* _S_free_list[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

//在自由链表中取下标
 static  size_t _S_freelist_index(size_t __bytes) 
 {
     return (((__bytes) + (size_t)_ALIGN-1)/(size_t)_ALIGN - 1);
		(32 + 8 - 1)/8 - 1 = 39/8 - 1 = 4 - 1 = 3
 }
 
 //向上取整，得到8的整数倍
 static size_t _S_round_up(size_t __bytes) 
 { return (((__bytes) + (size_t) _ALIGN-1) & ~((size_t) _ALIGN - 1)); }
   (32 + 8 - 1) & ~ (8 - 1) = 39 & ~7
   39 = 32 + 4 + 2 + 1 = 0010 0111
   
   7 = 4 + 2 + 1 = 0000 0111
   ~7 = 1111 1000
   
    0010 0111
 &  1111 1000
    0010 0000------------->32
	
    0010 1000
 &  1111 1000
    0010 1000
	
    0010 0110
 &  1111 1000
    0010 0000
	
	0010 0000
 &  1111 1000
    0010 0000
	
	31 = 16 + 8 + 4 +2 + 1 = 0001 1111
	0001 1111
 &  1111 1000
    0001 1000
	
	
	
	33--------------->40 = 8 * 5     33/8 = 4.xx---->5
	[25, 32]--------->32 = 8 * 4     25/8 = 3.xx---->4
	24--------------->24 = 8 * 3     24/8 = 3
	
    
			
	

//1、申请32字节的时候，堆空间与内存池都是充足的
//__n = 32
//如果第一次想申请32字节的时候，会比较麻烦，会调用_S_refill，但是该函数并不会申请空间，而是间接的调用_S_chunk_alloc进行申请空间，然后将其中的640字节返回，交给_S_refill进行切割，当第二次想再申请32字节的时候，会直接在自由链表取出第一个节点，这个节点就是32字节，所以从第二次到第20次再需要32字节的时候，会以O(1)的时间复杂度取出一个32字节的节点
 static void* allocate(size_t __n)
 {
	 void* __ret = 0;
	 else
	 {
		_Obj** __my_free_list = _S_free_list + _S_freelist_index(__n);//_S_free_list[3]
		 
		_Obj*  __result = *__my_free_list;
		 
		if (__result == nullptr)
			__ret = _S_refill(_S_round_up(__n));
		else 
		{
			*__my_free_list = __result -> _M_free_list_link;
			__ret = __result;
		}
	 }
	 
	 return __ret;
 }
 
 //__n = 32
 //本函数的作用将调用_S_chunk_alloc申请回来的640字节以32字节为标准，分成20份（也就是执行了切割的操作），其中的第一份使用__result进行返回，剩下的19等份会挂接在下标为3的自由链表下面
void* __default_alloc_template::_S_refill(size_t __n)
{
    int __nobjs = 20;
    char* __chunk = _S_chunk_alloc(__n, __nobjs);//指向的是一块大小为640的空间
    _Obj** __my_free_list;
    _Obj* __result;
    _Obj* __current_obj;
    _Obj* __next_obj;
    int __i;
	
	 __my_free_list = _S_free_list + _S_freelist_index(__n);//_S_free_list[3]

    /* Build free list in chunk */
      __result = (_Obj*)__chunk;
      *__my_free_list = __next_obj = (_Obj*)(__chunk + __n);
      for (__i = 1; ; __i++) {
        __current_obj = __next_obj;
        __next_obj = (_Obj*)((char*)__next_obj + __n);
        if (__nobjs - 1 == __i) {
            __current_obj -> _M_free_list_link = 0;
            break;
        } else {
            __current_obj -> _M_free_list_link = __next_obj;
        }
      }
    return (__result);
}

//__size = 32
//__nobjs = 20
//本函数的作用会使用malloc申请1280字节，然后会将其中的640字节使用__result进行返回，剩下的640字节使用两个指针 _S_start_free 与 _S_end_free 进行控制
char*__default_alloc_template::_S_chunk_alloc(size_t __size, int& __nobjs)
{
    char* __result;
    size_t __total_bytes = __size * __nobjs = 32 * 20 = 640;
    size_t __bytes_left = _S_end_free - _S_start_free = 0;
	
	else {
        size_t __bytes_to_get = 2 * __total_bytes + _S_round_up(_S_heap_size >> 4)
		                      = 2 * 640 + _S_round_up(0 >> 4) 
							  = 1280;
		_S_start_free = (char*)malloc(__bytes_to_get) = malloc(1280);
		
		_S_heap_size += __bytes_to_get = 1280;
        _S_end_free = _S_start_free + __bytes_to_get;
        return(_S_chunk_alloc(__size, __nobjs));
	}
	//递归调用
	char* __result;
    size_t __total_bytes = __size * __nobjs = 32 * 20 = 640;
    size_t __bytes_left = _S_end_free - _S_start_free = 1280;
	
	if (__bytes_left >= __total_bytes) {
        __result = _S_start_free;
        _S_start_free += __total_bytes;
        return(__result);
    }

}

//2、申请64字节的时候，堆空间与内存池都是充足的
//__n = 64
 static void* allocate(size_t __n)
 {
	 void* __ret = 0;
	 else
	 {
		_Obj** __my_free_list = _S_free_list + _S_freelist_index(__n);//_S_free_list[7]
		 
		_Obj*  __result = *__my_free_list;
		 
		if (__result == nullptr)
			__ret = _S_refill(_S_round_up(__n));
		else 
		{
			*__my_free_list = __result -> _M_free_list_link;
			__ret = __result;
		}
	 }
	 
	 return __ret;
 }

//__n = 64
//本函数在此次将通过_S_chunk_alloc 函数返回的640字节以64字节为一个等分，分成10等分，其中第一等分通过
//__result进行返回，剩下的9个64字节会挂接在下标为7的自由链表下面
void* __default_alloc_template::_S_refill(size_t __n)
{
    int __nobjs = 20;
    char* __chunk = _S_chunk_alloc(__n, __nobjs);//指向的是一块大小为640的空间
    _Obj** __my_free_list;
    _Obj* __result;
    _Obj* __current_obj;
    _Obj* __next_obj;
    int __i;
	
	 __my_free_list = _S_free_list + _S_freelist_index(__n);//_S_free_list[7]

    /* Build free list in chunk */
      __result = (_Obj*)__chunk;
      *__my_free_list = __next_obj = (_Obj*)(__chunk + __n);
      for (__i = 1; ; __i++) {
        __current_obj = __next_obj;
        __next_obj = (_Obj*)((char*)__next_obj + __n);
        if (__nobjs - 1 == __i) {
            __current_obj -> _M_free_list_link = 0;
            break;
        } else {
            __current_obj -> _M_free_list_link = __next_obj;
        }
      }
    return (__result);
}

//__size = 64
//__nobjs = 20
//本函数这一次会将申请32字节的时候，没有用完的640字节直接返回，该函数执行完毕之后_S_start_free 与 //_S_end_free之间的差值0
char*__default_alloc_template::_S_chunk_alloc(size_t __size, int& __nobjs)
{
    char* __result;
    size_t __total_bytes = __size * __nobjs = 64 * 20 = 1280;
    size_t __bytes_left = _S_end_free - _S_start_free = 640;
	
	else if (__bytes_left >= __size) {
        __nobjs = (int)(__bytes_left/__size) = 640/64 = 10;
        __total_bytes = __size * __nobjs = 64 * 10 = 640;
        __result = _S_start_free;
        _S_start_free += __total_bytes;
        return(__result);
    }
}

//3、申请96字节的时候，堆空间与内存池都是充足的
//__n = 96
 static void* allocate(size_t __n)
 {
	 void* __ret = 0;
	 else
	 {
		_Obj** __my_free_list = _S_free_list + _S_freelist_index(__n);//_S_free_list[11]
		 
		_Obj*  __result = *__my_free_list;
		 
		if (__result == nullptr)
			__ret = _S_refill(_S_round_up(__n));
		else 
		{
			*__my_free_list = __result -> _M_free_list_link;
			__ret = __result;
		}
	 }
	 
	 return __ret;
 }

//__n = 96
//本函数会将调用_S_chunk_alloc返回的1920字节，以96字节为一个等分，分成20等分，其中第一个96字节会
//通过__result直接进行返回，剩下的19个96字节会挂接在下标为11的自由链表下面
void* __default_alloc_template::_S_refill(size_t __n)
{
    int __nobjs = 20;
    char* __chunk = _S_chunk_alloc(__n, __nobjs);//指向的是一块大小为640的空间
    _Obj** __my_free_list;
    _Obj* __result;
    _Obj* __current_obj;
    _Obj* __next_obj;
    int __i;
	
	
    __my_free_list = _S_free_list + _S_freelist_index(__n);//_S_free_list[11]

    /* Build free list in chunk */
      __result = (_Obj*)__chunk;
      *__my_free_list = __next_obj = (_Obj*)(__chunk + __n);
      for (__i = 1; ; __i++) {
        __current_obj = __next_obj;
        __next_obj = (_Obj*)((char*)__next_obj + __n);
        if (__nobjs - 1 == __i) {
            __current_obj -> _M_free_list_link = 0;
            break;
        } else {
            __current_obj -> _M_free_list_link = __next_obj;
        }
      }
    return (__result);
}

// __size = 96
// __nobjs = 20
//本函数会调用malloc申请3920字节，其中的1920字节会通过__result进行返回，剩下的2000字节会使用
//_S_start_free 与 _S_end_free进行控制
char*__default_alloc_template::_S_chunk_alloc(size_t __size, int& __nobjs)
{
    char* __result;
    size_t __total_bytes = __size * __nobjs = 96 * 20 = 1920;
    size_t __bytes_left = _S_end_free - _S_start_free = 0;
	
	else {
        size_t __bytes_to_get = 2 * __total_bytes + _S_round_up(_S_heap_size >> 4)
		                      = 2 * 1920 + _S_round_up(1280 >> 4)
							  = 3840 + 80 = 3920;
		_S_start_free = (char*)malloc(__bytes_to_get) = malloc(3920);
		_S_heap_size += __bytes_to_get = 1280 + 3920 = 5200;
        _S_end_free = _S_start_free + __bytes_to_get;
        return(_S_chunk_alloc(__size, __nobjs));
	}
	//递归调用
	char* __result;
    size_t __total_bytes = __size * __nobjs = 96 * 20 = 1920;
    size_t __bytes_left = _S_end_free - _S_start_free = 3920;
	
	if (__bytes_left >= __total_bytes) {
        __result = _S_start_free;
        _S_start_free += __total_bytes;
        return(__result);
    } 
}

//4、申请72字节的时候，堆空间与内存池都没有连续的72字节
//__n = 72
 static void* allocate(size_t __n)
 {
	 void* __ret = 0;
	 else
	 {
		_Obj** __my_free_list = _S_free_list + _S_freelist_index(__n);//_S_free_list[8]
		 
		_Obj*  __result = *__my_free_list;
		 
		if (__result == nullptr)
			__ret = _S_refill(_S_round_up(__n));
		else 
		{
			*__my_free_list = __result -> _M_free_list_link;
			__ret = __result;
		}
	 }
	 
	 return __ret;
 }

//__n = 72
void* __default_alloc_template::_S_refill(size_t __n)
{
    int __nobjs = 20;
    char* __chunk = _S_chunk_alloc(__n, __nobjs);//指向的是一块大小为640的空间
    _Obj** __my_free_list;
    _Obj* __result;
    _Obj* __current_obj;
    _Obj* __next_obj;
    int __i;
	
	
	if (1 == __nobjs) return(__chunk);
}

//__size = 72
//__nobjs = 20
//本次会将从96那里借过来的一个节点分成两部分，其中一部分是72字节，直接返回，剩下的24字节会使用 
//_S_start_free 与 _S_end_free 进行指向，并且__nobjs传进去的是20， 传出来的时候是1.
char*__default_alloc_template::_S_chunk_alloc(size_t __size, int& __nobjs)
{
    char* __result;
    size_t __total_bytes = __size * __nobjs = 72 * 20 = 1440;
    size_t __bytes_left = _S_end_free - _S_start_free = 0;
	
	else {
        size_t __bytes_to_get = 2 * __total_bytes + _S_round_up(_S_heap_size >> 4) > 2880 ;
		
		_S_start_free = (char*)malloc(__bytes_to_get);
		
		 if (nullptr == _S_start_free) 
		 {
            size_t __i;
            _Obj** __my_free_list;
	        _Obj* __p;
           
		    //72 80 88 96，就是在向上“借”一个节点
            for (__i = 72; __i <= 128;__i += 8) 
			{
				//_S_free_list[8]、_S_free_list[9]、_S_free_list[10]、_S_free_list[11]
				__my_free_list = _S_free_list + _S_freelist_index(__i);
                __p = *__my_free_list;
				
				if (0 != __p) {
                    *__my_free_list = __p -> _M_free_list_link;
                    _S_start_free = (char*)__p;
                    _S_end_free = _S_start_free + __i;
                    return(_S_chunk_alloc(__size, __nobjs));
                   
                }
			}
	}
	
	//递归调用
	char* __result;
    size_t __total_bytes = __size * __nobjs = 72 * 20 = 1440;
    size_t __bytes_left = _S_end_free - _S_start_free = 96;
	
	else if (__bytes_left >= __size) {
        __nobjs = (int)(__bytes_left/__size) = 96/72 = 1;
        __total_bytes = __size * __nobjs = 72 * 1 = 72;
        __result = _S_start_free;
        _S_start_free += __total_bytes;
        return(__result);
    }
}


//为何申请72字节的时候，不直接申请两个64字节，而是向上找到一个大于72字节？
//两个64字节并不一定是地址连续的，所以两个64没有作用


//总结：
//在STL的空间配置器中，有四个核心函数，特别需要研究的就是申请空间的函数allocate（只研究小片空间）
//allocate函数调用会申请空间，但是该函数的底层会调用_S_freelist_index在自由链表下取下标；还会调用
//_S_round_up函数向上取整得到8的整数倍；allocate函数会调用_S_refill函数，但是_S_refill函数并不会真正
//申请空间，而是调用_S_chunk_alloc申请空间，该函数有可能会递归调用，但是该函数如果要申请空间的话，底层
//还是调用的malloc。

//_S_freelist_index函数就是在自由链表取下标;
//_S_round_up函数:向上取整得到8的整数倍;
//_S_refill函数:将从_S_chunk_alloc函数中返回的结果进行切割，然后挂接在对应的自由链表下面;
//_S_chunk_alloc函数：申请空间，该函数有可能会递归调用，申请空间的时候使用的是malloc；


//在STL中，所有的容器的底层申请的都是堆空间



