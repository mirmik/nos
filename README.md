# nos
Printing, tracing and loging library.

# Printing

## Основные функции:
Функция ```print```. ```print``` может объекты различных типов:
```c++
nos::print("Hello");
nos::print(42);
nos::print(0.45);
//output: Hello420.45
```

При указании нескольких аргументов - выводит их через пробел.
```c++
nos::print("Hello", 42); //output: Hello 42
```

Функция ```println```. Поведение аналогично ```print```. В конце выводится "\r\n":
```c++
nos::println("Hello", 42); //output: Hello 42\r\n
```

## Переопределение вывода типов.
Существует множество способов подружить nos с кастомными типами.

1. Перегрузка оператора вывода std::ostream.  
nos умеет выводить на печать стандартные типы. Форматирование ввода-вывода также поддерживается.

```c++
struct A 
{
	int a = 42;
	friend std::ostream& operator << ( std::ostream& os, const A&);
};

std::ostream& operator << ( std::ostream& os, const A& a) 
{
	os << std::hex << a.a << "A!!!"; 
}

...

nos::println(A()); //2aA!!!
```

2. Перегрузка функции ```ssize_t nos_print ( nos::ostream& os, const A& a )```.
```c++
struct A 
{
	int a = 42;
};

ssize_t nos_print ( nos::ostream& os, const A& a ) 
{
	ssize_t ret = 0;
	ret += os.print("A(");
	ret += os.print(a.a); 
	ret += os.print(")");
	return ret;
}

...

nos::println(A()); //A(42)
```

2. Определение метода ```ssize_t print_to (nos::ostream& os)``` const для класса.
```c++
struct A 
{
	int a = 42;

	ssize_t print_to (nos::ostream& os) const 
	{
		ssize_t ret = 0;
		ret += os.print("A(");
		ret += os.print(a.a); 
		ret += os.print(")");
		return ret;
	}
};

...

nos::println(A()); //A(42)
```

3. Специализация структуры ```nos::print_implementation``` для типа.
```c++
struct A 
{
	int a = 42;
};

template <> struct print_implementation<A>
{
	static ssize_t print_to ( nos::ostream& os, const A& a ) 
	{
		ssize_t ret = 0;
		ret += os.print("A(");
		ret += os.print(a.a); 
		ret += os.print(")");
		return ret;
	}
};


...

nos::println(A()); //A(42)
```

