#include <iostream>
#include <string>//stoi

using namespace std;
using ll = int64_t;

class fraction{
    ll rui(ll n, ll r){
        ll res = 1;
        for(int i = 0 ; i < r ; i++)res *= n;
        return res;
    }
    ll euclidean(ll n, ll m){//n>m
        n = abs(n);
        m = abs(m);
        if(n < m)swap(n,m);
        while(n % m != 0){
            n %= m;
            swap(n,m);
        }
        return m;
    }
    fraction make_f(ll n, ll m){
        fraction res(n,m);
        return res;
    }
    public:
        /*コンストラクタ*/
        fraction(){}
        fraction(ll numerator,ll denominator){
            n = numerator;
            d = denominator;
            if(d < 0){
                n *= -1;
                d *= -1;
            }
        }
        fraction(string num){
            string s = num;
            string numerator;
            ll denominator = 0;
            for(int i = 0 ; i < s.size() ; i++){
                if(s[i] == '.'){
                    numerator += s.substr(0,i);
                    i++;
                    denominator = s.size() - i;
                    numerator += s.substr(i);
                    break;
                }
            }
            n = stol(numerator);
            d = rui(10,denominator);
            yakubun();
        }
        fraction(const fraction& old){
            n = old.n;
            d = old.d;
            yakubun();
        }

        fraction yakubun(){
            if(d == 0){
                puts("分母に0が代入されています");
                return make_f(-1,1);
            }
            if(d < 0){
                d *= -1;
                n *= -1;
            }
            if(n == 0)return make_f(n,d);

            ll gcm = euclidean(n,d);
            n /= gcm;
            d /= gcm;
            return make_f(n,d);
        }

        
        ll n = 1;  //numerator(子)
        ll d = 1;  //denominator(母)
        
/*オーバーロード地獄*/
        fraction operator + (const fraction& a){
            fraction res;
            res.n = this->n * a.d + a.n * this->d;
            res.d = this->d * a.d;
            res.yakubun();
            return res;
        }
        fraction operator - (const fraction& a){
            fraction res;
            res.n = this->n * a.d - a.n * this->d;
            res.d = this->d * a.d;
            res.yakubun();
            return res;
        }
        fraction operator * (const fraction& a){
            fraction res;
            res.n = this->n * a.n;
            res.d = this->d * a.d;
            res.yakubun();
            return res;
        }
        fraction operator / (const fraction& a){
            fraction res;
            res.n = this->n * a.d;
            res.d = this->d * a.n;
            res.yakubun();
            return res;
        }
        fraction operator + (ll a){
            fraction res = *this;
            res.n += res.d * a;
            return res;
        }
        fraction operator - (ll a){
            fraction res = *this;
            res.n -= res.d * a;
            return res;
        }
        fraction operator * (ll a){
            fraction res = *this;
            res.n *= a;
            res.yakubun();
            return res;
        }
        fraction operator / (ll a){
            fraction res = *this;
            res.d *= a;
            res.yakubun();
            return res;
        }
        fraction operator ++ (){
            n += d;
            return *this;
        }
        fraction operator -- (){
            n -= d;
            return *this;
        }
        bool operator == (fraction& a){
            ll compa, compb;
            this->yakubun(); a.yakubun();
            return (this->n == a.n && this->d == a.d);
        }
        bool operator != (fraction& a){
            ll compa, compb;
            this->yakubun(); a.yakubun();
            return !(this->n == a.n && this->d == a.d);
        }
        bool operator == (ll a){
            ll compa, compb;
            this->yakubun();
            return (this->d == 1 && this->n == a);
        }
        bool operator != (ll a){
            ll compa, compb;
            this->yakubun();
            return !(this->d == 1 && this->n == a);
        }
        void operator += (const fraction& a){
            *this = *this + a;
        }
        void operator -= (const fraction& a){
            *this = *this - a;
        }
        void operator *= (const fraction& a){
            *this = *this * a;
        }
        void operator /= (const fraction& a){
            *this = *this / a;
        }
        void operator += (ll a){
            *this = *this + a;
        }
        void operator -= (ll a){
            *this = *this - a;
        }
        void operator *= (ll a){
            *this = *this * a;
        }
        void operator /= (ll a){
            *this = *this / a;
        }
};
fraction operator + (ll a, const fraction& b){
    fraction res(b);
    res += a;
    return res;
}
fraction operator - (ll a, const fraction& b){
    fraction res(b);
    res -= a;
    return res;
}
fraction operator * (ll a, const fraction& b){
    fraction res(b);
    res *= a;
    res.yakubun();
    return res;
}
fraction operator / (ll a, const fraction& b){
    fraction res(b);
    res /= a;
    res.yakubun();
    return res;
}
bool operator < (fraction& a, fraction& b){
    a.yakubun();b.yakubun();
    ll compa, compb;
    compa = a.n * b.d;
    compb = b.n * a.d;
    return compa < compb;
}
bool operator > (fraction& a, fraction& b){
    a.yakubun();b.yakubun();
    ll compa, compb;
    compa = a.n * b.d;
    compb = b.n * a.d;
    return compa > compb;
}
bool operator <= (fraction& a, fraction& b){
    a.yakubun();b.yakubun();
    ll compa, compb;
    compa = a.n * b.d;
    compb = b.n * a.d;
    return compa <= compb;
}
bool operator >= (fraction& a, fraction& b){
    a.yakubun();b.yakubun();
    ll compa, compb;
    compa = a.n * b.d;
    compb = b.n * a.d;
    return compa >= compb;
}
ostream& operator<<(ostream& os, fraction a){
    if(a.d < 0){
        a.n *= -1;
        a.d *= -1;
    }
    if(a.d == 1)os << a.n;
    else os << a.n << " / " << a.d;
    return os;
}
/*ここまで*/
namespace bunsu{
    double tod(const fraction& a){//fraction -> double
        return (double)a.n/a.d;
    }
    long double told(const fraction& a){//fraction -> long double
        return (long double)a.n/a.d;
    }
    fraction make_fraction(ll n, ll m){//make_pairのノリ
        fraction res(n,m);
        return res;
    }
};
