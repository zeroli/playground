#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <type_traits>
#include <functional>
#include <unordered_map>
#include <bitset>
#include <typeinfo>
#ifndef _MSC_VER
#   include <cxxabi.h>
#endif
#include <memory>

using namespace std;

struct InPlaceClass {
	struct A_ {
		int d_i = 3;
		A_(int i) : d_i(i) { }
	};
	int d_i = 2;
	const char* d_charp = "hello world";
	double d_d = (3.2); // can not use d_d(3.2)
	double d_d2{ 3.2 }; // can not use d_d(3.2)
	std::string d_str = "this is one in-place string";
	A_ d_a{ 4 };
};

struct A {
	// need add default ctor, otherwise, compiler will generate it for us, since we have 1-argument ctor
	A() {}
	A(int) {}
};
// if A does not have default ctor, and B also does not,
// B b; will not compile, since we don't derive any default non-argument ctor, or define it
struct B : A { using A::A; };

template <typename T>
class FixedCapacityArray {
public:
	void push_back(T t) { }

	alignas(T) char data[1024] = { 0 };
	// int length = 1024 / sizeof(T)
};

template <class T>
std::string type_name()
{
	typedef typename std::remove_reference<T>::type TR;
	std::unique_ptr<char, void(*)(void*)> own
	(
#ifndef _MSC_VER
		abi::__cxa_demangle(typeid(TR).name(), nullptr,
			nullptr, nullptr),
#else
		nullptr,
#endif
		std::free
	);
	std::string r = own != nullptr ? own.get() : typeid(TR).name();
	if (std::is_const<TR>::value)
		r += " const";
	if (std::is_volatile<TR>::value)
		r += " volatile";
	if (std::is_lvalue_reference<T>::value)
		r += "&";
	else if (std::is_rvalue_reference<T>::value)
		r += "&&";
	return r;
}

#define print_typename(x) { std::cerr << "type of '" #x "' is " << type_name<x>() << std::endl; }

struct Config {
	Config() : d_own(true), d_ptr(0) { std::cerr << "ctor\n"; }

	Config(const Config& other) : d_own(false), d_ptr(other.d_ptr) { std::cerr << "copy-ctor\n"; }

#if defined(MOVE) and __cplusplus >= 201103L
	Config(Config&& other) : d_own(other.d_own), d_ptr(other.d_ptr) { other.d_ptr = 0, other.d_own = false; std::cerr << "move-ctor\n"; }
	Config& operator=(Config&& other) { d_own = other.d_own, d_ptr = other.d_ptr; other.d_own = false, other.d_ptr = 0; std::cerr << "move-assignment\n"; }
#endif

	friend std::ostream& operator <<(std::ostream& out, const Config& c) { out << "own=" << c.d_own; return out; }

	//private:
	Config& operator=(const Config& other) { d_own = other.d_own, d_ptr = other.d_ptr; std::cerr << "copy-assignment\n"; }

	bool d_own;
	int* d_ptr;
};

int main()
{
	int i = 32, &ri = i;
	decltype(i) d = 30; // type(i) is int
	decltype(ri) d1 = i; // type of d1 is int&
	std::cerr << "i=" << i << ", d=" << d << "\n";

	//decltype((i)) d2; // error: type of d1 is int&, need to be initialized
	if (not (i > 0)) {
		std::cerr << "i<=0\n";
	}

	// class member in-place initialization
	InPlaceClass ipc;

	// derived class derive-ctor from base class
	B b;

	// auto deduction
	{
		int x = 1;
		const auto* m = &x, n = 1;
		//*m = 20; // type(m) = const int*
		//n = 2; // type(n) = const int

		auto* a = &x; // type(a) = int*, auto => int
		auto  b = &x; // type(b) = int*, auto => int*
		auto& c = x;  // type(c) = int&, auto => int
		auto  d = c;   // type(d) = int, auto => int
		// rule#1: without pointer/reference, 
		// expression with reference(only, no pointer) and cv modifier
		// will be discarded, when deducing auto
		// so d will be deduced as int, instead of int&, even though c is type of int&

		const auto e = x;  // type(e) = const int, auto => int
		auto f = e;  // type(f) = int, auto => int
		// so f will be deduced as int, instead of const int, even though e if type of const int
		// according to rule#1

		// rule#2: with pointer/reference,
		// expression with cv modifier will be kept
		const auto& g = x;  // type(g) = const int&, auto => int
		auto& h = g; // type(h) = cons int&, auto => const int
		// if we have to keep deduced expression type, we have to use pointer or reference
		// like h above		
	}
	
	// decltype deduction
	{
		int x = 1;
		const int x1 = x;
		const int& x2 = x;
		{ decltype(x) _x = x; print_typename(decltype(x)); } // int
		{ const decltype(x) _x = x; print_typename(const decltype(x)); } // const int
		{ const decltype(x)& _x = x; print_typename(const decltype(x)&); } // const int&

		{ decltype(x1) _x1 = x1; print_typename(decltype(x1)); } // const int
		{ const decltype(x1) _x1 = x1; print_typename(const decltype(x1)); } // const int
		{ const decltype(x1)& _x1 = x1; print_typename(const decltype(x1)&); } // const int&

		{ decltype(x2) _x2 = x2; print_typename(decltype(x2)); } // const int&
		{ const decltype(x2) _x2 = x2; print_typename(const decltype(x2)); } // const int&
		{ const decltype(x2)& _x2 = x2; print_typename(const decltype(x2)&); } // const int&

		struct Foo { int x = 0; };
		Foo foo;
		const Foo foo1 = foo;
		const Foo& foo2 = foo;
		{ decltype(foo.x) _foo = foo.x; print_typename(decltype(foo.x)); } // int
		{ decltype(foo) _foo = foo; print_typename(decltype(foo)); } // Foo
		{ const decltype(foo) _foo = foo; print_typename(const decltype(foo)); } // const Foo
		{ const decltype(foo)& _foo = foo; print_typename(const decltype(foo)&); } // const Foo&

		{ decltype(foo1) _foo1 = foo1; print_typename(decltype(foo1)); } // const Foo
		{ decltype(foo2) _foo2 = foo2; print_typename(decltype(foo2)); } // const Foo&

		std::vector<Foo> foos = { Foo() };
		// this one will deduce to be "Foo&", because foos[0] is left reference
		{ decltype(foos[0]) _foo = foos[0]; print_typename(decltype(foos[0])); } // Foo&
		// below two will deduce to be STILL "Foo&"
		{ const decltype(foos[0]) _foo = foos[0]; print_typename(const decltype(foos[0])); } // Foo&
		{ const decltype(foos[0])& _foo = foos[0]; print_typename(const decltype(foos[0])&); } // Foo&

		const Foo& foo3 = foos[0];
		// below 3 will be all type of "const Foo&"
		{ decltype(foo3) _foo = foo3; print_typename(decltype(foo3)); } // const Foo&
		{ const decltype(foo3) _foo = foo3; print_typename(const decltype(foo3)); } // const Foo&
		{ const decltype(foo3)& _foo = foo3; print_typename(const decltype(foo3)&); } // const Foo&

		Foo& foo4 = foos[0];
		// below 3 will be all type of "Foo&"
		{ decltype(foo4) _foo = foo4; print_typename(decltype(foo4)); } // Foo&
		{ const decltype(foo4) _foo = foo4; print_typename(const decltype(foo4)); } // Foo&
		{ const decltype(foo4)& _foo = foo4; print_typename(const decltype(foo4)&); } // Foo&

		const std::vector<Foo> foos1 = foos;
		// below 3 will deduce to be "const Foo&"
		{ decltype(foos1[0]) _foo = foos1[0]; print_typename(decltype(foos1[0])); } // const Foo&
		{ const decltype(foos1[0]) _foo = foos1[0]; print_typename(const decltype(foos1[0])); } // const Foo&
		{ const decltype(foos1[0])& _foo = foos1[0]; print_typename(const decltype(foos1[0])&); } // const Foo&

		const std::vector<Foo>& foos2 = foos;
		// below 3 will deduce to be "const Foo&"
		{ decltype(foos2[0]) _foo = foos2[0]; print_typename(decltype(foos2[0])); } // const Foo&
		{ const decltype(foos2[0]) _foo = foos2[0]; print_typename(const decltype(foos2[0])); } // const Foo&
		{ const decltype(foos2[0])& _foo = foos2[0]; print_typename(const decltype(foos2[0])&); } // const Foo&

		const std::vector<Foo>* foos3 = &foos;
		// below 3 will deduce to be "const Foo&"
		{ decltype((*foos3)[0]) _foo = (*foos3)[0]; print_typename(decltype((*foos3)[0])); } // const Foo&
		{ const decltype((*foos3)[0]) _foo = (*foos3)[0]; print_typename(const decltype((*foos3)[0])); } // const Foo&
		{ const decltype((*foos3)[0])& _foo = (*foos3)[0]; print_typename(const decltype((*foos3)[0])&); } // const Foo&

		struct Buffer {
			int* pix = new int[1];
		};
		std::map<int, Buffer*> m = { {1, new Buffer} };
		const Buffer* buf = m[1];
		// below will deduce to 'int&', since buf->pix[0] is left reference
		{ decltype(buf->pix[0]) pix = buf->pix[0]; print_typename(decltype(buf->pix[0])); } // int&
		buf->pix[0] = 10; // WORK, since it's reference

		const int* bufs = new int[1];
		// below will deduce to 'const int&', since bufs[0] is const int&
		{ decltype(bufs[0]) pix = bufs[0]; print_typename(decltype(bufs[0])); } // const int&
		{ decltype(bufs[0])& pix = bufs[0]; print_typename(decltype(bufs[0])&); } // const int&
		{ const decltype(bufs[0])& pix = bufs[0]; print_typename(const decltype(bufs[0])&); } // const int&
	}
	// move semantics
	{
		std::vector<Config> v1(1);
		std::cerr << "v1[0]: " << v1[0] << "\n";  // own = true
		std::vector<Config> v2(1, Config());
		std::cerr << "v2[0]: " << v2[0] << "\n"; // own = false

		v2.push_back(Config());
		std::cerr << "v2[1]: " << v2[1] << "\n"; // own = false

		std::vector<Config> v3;
		v3.reserve(10);
		v3.push_back(Config());
		std::cerr << "v3[0]: " << v3[0] << "\n"; // own = false

#if __cplusplus >= 201103L
		v3.push_back(std::move(Config())); // 1 copy-ctor take place, or 1 move-ctor take place if move-ctor provided
		std::cerr << "v3[1]: " << v3[1] << "\n"; // own = false

		Config c;
		v3.push_back(std::move(c)); // 1 copy-ctor take place or 1 move-ctor take place if move-ctor provided
		std::cerr << "v3[2]: " << v3[2] << "\n"; // own = false

		Config c1 = std::move(Config()); // 1 copy-ctor take place or 1 move-ctor take if move-ctor provided
		std::cerr << "c1: " << c1 << "\n"; // own = false
#endif

		std::vector<Config> v4;
		v4 = std::vector<Config>(1);
		std::cerr << "v4[0]: " << v4[0] << "\n"; // own = true
	}

	// lambda expression
	// format as below:
	// [capture] (params) opt -> return type { body; };
	// lambda is just like functor, capture will be like functor class's member data
	// its function {} is like operator (...) const function
	// lambda mutable is make its member data to be 'mutable' attribute
	{
		int val = 1;
		// cannot compile
		//auto const_val_lambda = [=]() { val = 3; };

		// mutable will make captures to be mutable property, so you could modify it in lambda function
		// while it will not reflect back to enclosing scope, it just change functor object's member data
		auto mutable_val_lambda = [=]() mutable { val = 3; };
		mutable_val_lambda();
		std::cerr << "val = " << val << "\n"; // 1

		struct KK {
			KK(int& i) : d_i(i) { }

			void operator()() const {
				d_i = 10;
			}
			int& d_i;
		};
		{
			// this lambda is like KK functor
			// the enclosing scope is function scope, not upper scope
			auto const_ref_lambda = [&]() { val = 4; };
			const_ref_lambda();
			std::cerr << "val = " << val << "\n"; // 4
		}
		do {
			// this lambda is like KK functor
			auto const_ref_lambda = [&]() { i += 4; };
			const_ref_lambda();
			std::cerr << "i = " << i << "\n"; // 36
		} while (0);
		auto const_param_lambda = [&](int v) { v = 5; };
		const_param_lambda(val);
		std::cerr << "val = " << val << "\n"; // 4

		class TestLambda {
		public:
			int i_ = 0;
			void func(int x, int y) {
				//auto x1 = [] { return i_; } // error, no capturing
				auto x2 = [=] { return i_ + x + y; }; // OK, capture all enclosing scopes
				auto x3 = [&] { return i_ + x + y; }; // OK, capture all enclosing scopes with reference
				auto x4 = [this] { return i_; }; // OK, capture this pointer
				//auto x5 = [this] { return i_ + x + y; }; // error, no x/y capture
				auto x6 = [this, x, y] { return i_ + x + y; }; // OK, capture this, x, y
				auto x7 = [this] { return i_++; }; // OK, capture this pointer, and modify its member
				auto x8 = [=] { return i_++; }; // OK, capture this pointer, and modify its member

				x2();
				x3();
				x4();
				x6();
				x7();
				x8();
				std::cerr << "test lambda: " << i_ << std::endl;
			}
		};
		TestLambda().func(1, 1);
	}
	// alignof and alignas
	{
		struct alignas(alignof(double) * 4) ColorVector {
			double r;
			double g;
			double b;
			double a;
		};

		FixedCapacityArray<char> arrCh;
		std::cerr << "alignof(char): " << alignof(char) << std::endl;
		// !!!visual studio cannot compile:
		//std::cerr << "alignof(arrCh.data): " << alignof(arrCh.data) << std::endl;

		FixedCapacityArray<ColorVector> arrCV;
		std::cerr << "alignof(ColorVector): " << alignof(ColorVector) << std::endl;
		// !!!visual studio cannot compile:
		//std::cerr << "alignof(arrCV.data): " << alignof(arrCV.data) << std::endl;
	}
	// aligned_storage
	{
		struct IntAligned {
			int a;
			char b;
		};
		typedef std::aligned_storage<sizeof(IntAligned), alignof(long double)>::type StrictAligned;

		StrictAligned sa;
		IntAligned* pia = new (&sa) IntAligned;
		std::cerr << alignof(IntAligned) << std::endl;
		std::cerr << alignof(StrictAligned) << std::endl;
		//std::cerr << alignof(*pia) << std::endl; // cannot compile on VS
		//std::cerr << alignof(sa) << std::endl;  // cannot compile on VS
	}
	// functor object
	{
		auto func = [](void) {}; // lambda function, local defined
		struct Foo { void operator()(void) { } }; // functor object
		struct Bar {
			using fr_t = void(*)(void);
			static void func(void) { }
			operator fr_t(void) { return func; }
		};
		struct Aar {
			int a_;
			void mem_func(void) { }
		};

		void(*func_ptr)(void) = func;
		func_ptr();

		Foo foo;
		foo();

		Bar bar;
		bar();

		void (Aar::*mem_func_ptr)(void) = &Aar::mem_func;
		int Aar::*mem_obj_ptr = &Aar::a_;

		Aar aa;
		(aa.*mem_func_ptr)();
		aa.*mem_obj_ptr = 123;
	}
	// std::function / std::bind
	{
		// lambda function is just like one functor with operator () function
		// it could be converted to std::function with same signature
		// and also it could be bind to form another function, or with some real arguments
		std::function<int(int)> f1 = [](int a) { return a; };
		std::function<int(void)> f2 = std::bind([](int a) { return a; }, 123);

		// any lambda with no any capture could e converted to function pointer with same signature
		// that's because functor object which lambda represented internally will drop its 'this' in conversion
		using func_t = int(*)(int);
		func_t f = [](int a) { return a; };
		f(123);
	}
	// std::tuple
	{
		char buf[10];
		std::tuple<const char*, int> tp = std::make_tuple(buf, sizeof buf);
		int x = 1, y = 2;
		auto tp1 = std::tie(x, "aa", y);
		auto print_tuple = [](const std::tuple<int, const char*, int>& t) {
			std::cerr << "("
				<< std::get<0>(t) << ","
				<< std::get<1>(t) << ","
				<< std::get<2>(t) << ")";
		};
		print_tuple(tp1);
		std::tuple<int, std::string, float> t1(10, "Test", 3.14f);
		int n = 7;
		auto t2 = std::tuple_cat(t1, std::make_pair("Foo", "bar"), t1, std::tie(n));
		n = 10;
		// n will printed as 10, sinc std::tie will bind reference &
	}
	// std::unordered_map
	{
		struct Key {
			std::string first;
			std::string second;
		};
		struct KeyHash {
			std::size_t operator() (const Key& k) const {
				return std::hash<std::string>()(k.first) ^ (std::hash<std::string>()(k.second) << 1);
			}
		};
		struct KeyEqual {
			bool operator()(const Key& lhs, const Key& rhs) const {
				return lhs.first == rhs.first && lhs.second == rhs.second;
			}
		};
		// default ctor 
		std::unordered_map<std::string, std::string> m1;
		// list ctor
		std::unordered_map<int, std::string> m2 = {
			{ 1, "foo"},
			{ 3, "bar"},
			{2, "baz"},
		};
		// copy ctor
		std::unordered_map<int, std::string> m3 = m2;
		// move ctor
		std::unordered_map<int, std::string> m4 = std::move(m2);
		// range ctor
		std::vector<std::pair<std::bitset<8>, int>> v = { { 0x12, 1 } };
		std::unordered_map<std::bitset<8>, double> m5(v.begin(), v.end());

		// ctor for a custom type
		std::unordered_map<Key, std::string, KeyHash, KeyEqual> m6 = {
			{ { "John", "Doe" }, "example"},
			{ { "Mary", "Sue" }, "another"},
		};
	}
	return 0;
}
