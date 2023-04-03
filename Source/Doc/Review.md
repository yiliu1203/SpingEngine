# 记录一些开发中需要Review的点

## 静态反射和动态反射在实现上的区别

- 动态反射一般使用静态局部变量保存元类实例，是在运行时才构造，运行时注册元信息，典型的就是 URho3D 里面的实现，大概的流程：

```c++
    class Object() {}

    class Foo : public Object
    {
        // RIIT(Foo, Object);
        // 展开就是下面的
        public: 
            using CurClass = Foo;
            using BaseClass = Object;
            virtual const TypeInfo * GetTypeInfo() {
                return GetMetaTypeInfo();
            }
            static const TypeInfo * GetMetaTypeInfo() {
                static const TypeInfoStatic TypeInfoStaticFoo("Foo", BaseClass::GetMetaTypeInfo());
                return &TypeInfoStaticFoo;
            }
    };
    // TypeInfoStatic 则保存了类的元信息，包括继承链，对提供是否继承、属性查询等接口。 提供静态方法和成员函数都可以拿到元类信息。注册属性、方法等元信息时一般在启动时运行时通过静态方法去注册

```

- 静态反射 则是发生在编译期，主要涉及大量模板推导、类型声明、模板特化。