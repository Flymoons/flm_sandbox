#include <iostream>

using namespace std;

class BaseClass {
    private:
        int _a, _b;
        double _w;

    public:
        BaseClass() : _a(2), _b(3), _w(0.9) {}
        BaseClass(int a, int b, double w) : _a(a), _b(b), _w(w) {}

        double weighted_addition() { return static_cast<double>(_a + _b) * _w; }
};

class DerivedClass : public BaseClass {
    public:
        using BaseClass::weighted_addition;

    private:
        double _bias;

    public:
        DerivedClass() : BaseClass(), _bias(0.0) {}
        DerivedClass(int a, int b, double w) : BaseClass(a, b, w), _bias(0.0) {}

        double weighted_addition(double bias) {
            _bias = bias;
            return weighted_addition() + _bias;
        }

        double& bias() { return _bias; }
};

class myMethod {
    private:
        double _mean;
        BaseClass _bc;

    public:
        myMethod() : _mean(0.3), _bc() {}
        myMethod(double mean) : _mean(mean), _bc() {}

        double measurement(BaseClass bc) {
            _bc = bc;
            return _bc.weighted_addition() - _mean;
        }

        double measurement(DerivedClass dc) {
            _bc = dc; // ここで親クラス BaseClass に 子クラス DerivedClass が入っていて欲しい
            return _bc.weighted_addition(_bc.bias()) - (_mean + _bc.bias()); 
            // _bc が DerivedClass として機能して欲しいが、もちろんno member named 'get_bias()'... みたいなエラーが出てコンパイルエラー
        }

};

int main() {
    BaseClass bc(2, 3, 0.9);
    DerivedClass dc(2, 3, 0.9);
    myMethod met;

    dc.bias() = 0.2;
    cout << met.measurement(bc) << endl;
    //cout << met.measurement(dc) << endl;

    return 0;

}