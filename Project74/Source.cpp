#include <memory>
using namespace std;
class X
{
	int a;
	double b;
public:
	int ffunc() { return 1; };
	int ffunc2() { return 0; };
};
void func(unique_ptr<X> a) {};
class Owner
{
public:
	shared_ptr<X> owingPtr;
	Owner()
	{
		owingPtr = make_shared<X>();
	}
};
class User
{
	weak_ptr<X> usingPtr;
public:
	User(weak_ptr<X> object)
	{
		usingPtr = object;
	}
	void use()
	{
		if (shared_ptr<X> object = usingPtr.lock())//Попытка получить оригинальный shared_ptr из weak_ptr, если возврщён
			//пустой shared_ptr, значит, объект уже был удалён
			object->ffunc();
	}
};
int main()
{
	unique_ptr<X> ptr(new X());
	auto a = make_unique<X>();
	func(move(a));
	Owner owner;
	User user(owner.owingPtr);
	user.use();
}