import std;

export module AModule;

namespace Webjasiek {

	using namespace std;

	export class A {
	private:
		int _x = 0; // podkr. bo private
	protected:
		int prop;
	public: 
		string name;
		A(int i = 1) : prop(i) {
			cout << "[+] " << typeid(*this).name() << ".prop = " << this->prop << "\n";
		}
		~A() { // destruktor
			cout << "[-] " << typeid(*this).name() << " prop = " << this->prop << "\n";
		}
		friend static void _tempFunc(A*);
	};

	static void _tempFunc(A* obj = nullptr) {
		if (obj != nullptr) {
			cout << obj->name << "\n";
			cout << obj->prop << "\n";
			cout << obj->_x << "\n";
		}
		cout << "huk\n";
	}

	export void MyFunc(A* obj = nullptr) {
		cout << "MyFunc() w AModule.\n";
		_tempFunc(obj);
	}

	//export class B : public A { };

}
