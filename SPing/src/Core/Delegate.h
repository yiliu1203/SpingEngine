#pragma once
#include <vector>
template<typename R, typename A1, typename A2>
class Delegate2 {

public:
	// typedef R (*F) (A1, A2);
	typedef R(*FNew)(void*, A1, A2);
	// typedef R (C::*CF)(A1, A2);
	// void * p_;
	// FNew f_;
public:
	class Handle
	{
	public:
		Handle(void* p, FNew f) : p_(p), f_(f) {}
		R Execute(A1 a1, A2 a2) {
			return f_(p_, a1, a2);
		}
		void* p_;
		FNew f_;

	public:
		bool operator == (const Handle& h) {
			return p_ == h.p_ && f_ == h.f_;
		}
	};

public:
	Delegate2() = default;
	Delegate2(const Handle&& h)
	{
		handles_.push_back(h);
	}
	~Delegate2() {
	};

	// // F 既是类型，也是地址
	template<class C, R(C::* CF)(A1, A2)>
	static R MethodStub(void* p, A1 a1, A2 a2) {
		C* c = (C*)p;
		return (c->*CF)(a1, a2);
	}

	// F 既是类型，也是地址
	template<R(*F)(A1, A2)>
	static R FunStub(void* p, A1 a1, A2 a2) {
		// 这里要和 MethodStub 保持参数接口一致，真正执行的时候 *p=null
		return (F)(a1, a2);
	}

	template<typename C, R(C::* CF)(A1, A2)>
	static Handle FromMethod(C* p) {
		return Handle(p, &MethodStub<C, CF>);
	}

	template<R(*F)(A1, A2)>
	static Handle FromFun() {
		return Handle(nullptr, &FunStub<F>);
	}

	void operator +=(Handle d) {
		handles_.push_back(d);
	}

	void operator ()(A1 a1, A2 a2) {
		for (auto h : handles_) {
			std::cout << h.Execute(a1, a2) << std::endl;
		}
	}

	void Has(Handle d) {

	}

public:
	std::vector<Handle> handles_;
};


template<typename R, typename A1>
class Delegate1 {

public:
	typedef R(*FNew)(void*, A1);
public:
	class Handle
	{
	public:
		Handle(void* p, FNew f) : p_(p), f_(f) {}
		R Execute(A1 a1) {
			return f_(p_, a1);
		}
		void* p_;
		FNew f_;

	public:
		bool operator == (const Handle& h) {
			return p_ == h.p_ && f_ == h.f_;
		}
	};

public:
	Delegate1() = default;
	Delegate1(const Handle&& h)
	{
		handles_.push_back(h);
	}
	~Delegate1() {
	};

	// // F 既是类型，也是地址
	template<class C, R(C::* CF)(A1)>
	static R MethodStub(void* p, A1 a1) {
		C* c = (C*)p;
		return (c->*CF)(a1);
	}

	// F 既是类型，也是地址
	template<R(*F)(A1)>
	static R FunStub(void* p, A1 a1) {
		// 这里要和 MethodStub 保持参数接口一致，真正执行的时候 *p=null
		return (F)(a1);
	}

	template<typename C, R(C::* CF)(A1)>
	static Handle FromMethod(C* p) {
		return Handle(p, &MethodStub<C, CF>);
	}

	template<R(*F)(A1)>
	static Handle FromFun() {
		return Handle(nullptr, &FunStub<F>);
	}

	void operator +=(Handle d) {
		handles_.push_back(d);
	}

	void operator ()(A1 a1) {
		for (auto h : handles_) {
			std::cout << h.Execute(a1) << std::endl;
		}
	}

	void Has(Handle d) {

	}

public:
	std::vector<Handle> handles_;
};