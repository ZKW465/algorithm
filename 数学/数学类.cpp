/**
 * ��ѧ������
*/

namespace Math {
    using i64 = long long;
    using Int = __int128;
    using ui64 = unsigned long long;
    std::mt19937 rng(std::chrono::system_clock::now().time_since_epoch().count());

    struct math {

/**
 * @brief   ��ģ��
 * @return  (a ^ b)% m
*/
        i64 static mul(i64 a, i64 b, i64 m);


/**
 * @brief   ������
*/
        template<class T>
        constexpr static T power(T a, i64 b);

        i64 static power(i64 a, i64 b, i64 m);

/**
 * @brief   ���
*/
        template<typename T>
        constexpr static T __sum1(T it);

        template<typename T>
        constexpr static T __sum2(T it);

/**
 * ŷ������㷨���
*/

/**
 * �㷨����չŷ������㷨
 * ���ã���� ax + by = gcd ( a , b )
 * ���أ�gcd,x,y
 */
        template<typename T = i64>
        constexpr array<T, 3> static Exgcd(T a, T b);

/**
 * �㷨����չŷ������㷨
 * ���ã���� ax + by = res
 * ���ƣ�gcd(a, b) | res 
 */
        template<typename T = i64>
        constexpr array<T, 3> static __Exgcd(T a, T b, T res);

/**
 * �㷨������ͬ�෽��
 * ���ã���� ax == b ( mod n )
 *       ����С������
 * Ҫ��gcd ( a , n ) | b
 */
        template<typename T = i64>
        constexpr T static Linear_congruence_equation(i64 a, i64 b, i64 mod);

/**
 * �㷨����չŷ������㷨����Ԫ
 * ���ã���� ax == 1 ( mod n )����С������
 * Ҫ��a �� n ����
 */
        template<typename T = i64>
        constexpr T static inv(i64 a, i64 mod);

/**
 * ��չŷ����ý���
*/

/**
 * �㷨��Miller_Rabin_Test
 * ���ã���long long��Χ�ڿ����ж�����
 * ʱ�临�Ӷȣ�O(log^3(n))
 */
        constexpr static bool Miller_Rabin_Test(i64 n);

/**
 * �㷨��Pollard_Rho
 * ���ã��ܿ����ҵ���������һ����1������������ӵ��㷨
 * ʱ�临�Ӷȣ�O(n^{1/4}log(n))
 */
        static i64 Pollard_Rho(i64 N);

/**
 * �㷨��ʹ��Pollard_Rho�����������ֽ�
 * ���أ�˳������������(�ظ�)
*/
        std::vector <i64> static factorize(i64 n);

/**
 * �㷨���й�ʣ�ඨ��
 * ���ã����һԪ����ͬ�෽�̣� x == a �� mod m ������ģn�����е�ģ�����Ľ�
 * ���ƣ�����ģ����
 */
        template<typename T = i64>
        constexpr static T Chinese_remainder_theorem
                (vector <i64> &a, vector <i64> &m);

/**
 * �㷨����չ�й�ʣ�ඨ��
 * ���ã����һԪ����ͬ�෽�̣� x == a �� mod m ������ģn������ģ����С���������Ľ�
 * �����ƣ�����ģ����
*/
        template<typename T = i64>
        constexpr static T Extend_the_Chinese_remainder_theorem
                (vector <i64> &a, vector <i64> &m);

/**
 * �㷨��ŷ������
 * ���ã���ŷ������
 * ʱ�临�Ӷȣ�O(sqrt ( n ))
 */
        template<typename T = i64>
        constexpr static T Euler_phi(T n);

/**
 * �㷨����չŷ������ŷ�����ݣ�
 * ���ã���ָ��������
 * ʱ�临�Ӷȣ�O(sqrt ( m ))
 */
        static i64 Extending_Euler_theorem(i64 a, string b, i64 m);


/**
 * �㷨������Сԭ��
 * Ҫ�������б�֤�������ԭ��(2,4,p^q,2*p^q)
 * ʱ�临�Ӷȣ�O(sqrt(n))
*/
        static i64 min_primitive_root(i64 m);

/**
 * ��һ����������ԭ��
 * ע����ǰʹ������ɸ������Ϊs������n����ɸ��ŷ������
 * ��ҪLinear_sieves_max��s
 * ʱ�临�Ӷȣ�O(sqrt ( m ))
 */
# ifdef _Linear_sieves
        std::vector <i64> static primitive_root(i64 n);
# endif


/**
 * �㷨����չBSGS
 * ���ã���� a ^ x = b ( mod m )
 * ��Ҫ��: a��m����
 * ���أ��������С�Ǹ�x���޽ⷵ��-1
 * ����ʹ���Զ���Hash
*/
        constexpr i64 static exBSGS(i64 a, i64 b, i64 m, i64 k = 1);

/**
 * �㷨��n��ʣ��
 * ���ã���� x ^ a = b ( mod m )
 * Ҫ��: m������
 * ���أ�x���޽ⷵ��-1e15
 * ����ʹ���Զ���Hash
*/
        static std::vector <i64> n_times_remaining(i64 a, i64 b, i64 m);


/**
 * �㷨����չlucas
 * ���ã���pΪ����������£����������C(n,m)
 * ��Ҫ����£�Ԥ�����͸��Ӷ�
*/

        static i64 Exlucas(i64 n, i64 m, i64 P);

        //struct math
    };


    i64 math::mul(i64 a, i64 b, i64 m) {
        return static_cast<__int128>(a) * b % m;
    }


    template<class T>
    constexpr T math::power(T a, i64 b) {
        T res = 1;
        for (; b; b /= 2, a *= a)
            if (b % 2) res *= a;
        return res;
    }

    i64 math::power(i64 a, i64 b, i64 m) {
        i64 res = 1 % m;
        for (; b; b >>= 1, a = mul(a, a, m))
            if (b & 1)
                res = mul(res, a, m);
        return res;
    }


    template<typename T>
    constexpr T math::__sum1(T it) { return (it * (it + 1)) / ((T) 2); }

    template<typename T>
    constexpr T math::__sum2(T it) { return it * (it + 1) * (2 * it + 1) / ((T) 6); }


    template<typename T>
    constexpr array<T, 3> math::Exgcd(T a, T b) {
        T x1 = 1, x2 = 0, x3 = 0, x4 = 1;
        while (b != 0) {
            T c = a / b;
            std::tie(x1, x2, x3, x4, a, b) =
                    std::make_tuple(x3, x4, x1 - x3 * c, x2 - x4 * c, b, a - b * c);
        }
        return {a, x1, x2}; //x = x1, y = x2;
    }

    template<typename T>
    constexpr array<T, 3> math::__Exgcd(T a, T b, T res) {
        assert(res % __gcd(a, b) == 0);
        auto [gcd, x, y] = Exgcd(a, b);
        return {gcd, res / gcd * x, res / gcd * y};
    }

    template<typename T>
    constexpr T math::Linear_congruence_equation(i64 a, i64 b, i64 mod) {
        auto [gcd, x, k] = __Exgcd<T>((T) a, (T) mod, (T) b);
        T t = mod / gcd;
        return (x % t + t) % t;
    }

    template<typename T>
    constexpr T math::inv(i64 a, i64 mod) {
        auto [gcd, x, k] = Exgcd<T>((T) a, (T) mod);
        return (x % mod + mod) % mod;
    }


    constexpr bool math::Miller_Rabin_Test(i64 n) {
        if (n < 3 || n % 2 == 0) return n == 2;//����
        i64 u = n - 1, t = 0;
        while (u % 2 == 0) u /= 2, ++t;
        constexpr std::array<i64, 7> ud = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};
        for (i64 a: ud) {
            i64 v = power(a, u, n);
            if (v == 1 || v == n - 1 || v == 0) continue;
            for (int j = 1; j <= t; j++) {
                v = mul(v, v, n);
                if (v == n - 1 && j != t) {
                    v = 1;
                    break;
                }//����һ��n-1�����涼��1��ֱ������
                if (v == 1) return 0;//�������ǰ��û�г���n-1����⣬���μ���ʧ��
            }
            if (v != 1) return 0;//Fermat����
        }
        return 1;
    }

    i64 math::Pollard_Rho(i64 N) {
        if (N == 4) // ����4
            return 2;
        if (Miller_Rabin_Test(N)) // ��������
            return N;
        auto randint = [&](i64 l, i64 r) {
            return l + rng() % (r - l + 1);
        };
        while (true) {
            i64 c = randint(1, N - 1); // ���������c
            auto f = [=](i64 x) { return ((Int) x * x + c) % N; }; // Int��ʾ__int128�������
            i64 t = f(0), r = f(f(0));
            while (t != r) {
                i64 d = gcd(abs(t - r), N);
                if (d > 1)
                    return d;
                t = f(t), r = f(f(r));
            }
        }
    }

    std::vector <i64> math::factorize(i64 n) {
        std::vector <i64> p;
        std::function<void(i64)> f = [&](i64 n) {
            if (n <= 10000) {
                for (int i = 2; i * i <= n; ++i)
                    for (; n % i == 0; n /= i)
                        p.push_back(i);
                if (n > 1)
                    p.push_back(n);
                return;
            }
            if (Miller_Rabin_Test(n)) {
                p.push_back(n);
                return;
            }
            auto g = [&](i64 x) {
                return (mul(x, x, n) + 1) % n;
            };
            i64 x0 = 2;
            while (true) {
                i64 x = x0;
                i64 y = x0;
                i64 d = 1;
                i64 power = 1, lam = 0;
                i64 v = 1;
                while (d == 1) {
                    y = g(y);
                    ++lam;
                    v = mul(v, std::abs(x - y), n);
                    if (lam % 127 == 0) {
                        d = std::gcd(v, n);
                        v = 1;
                    }
                    if (power == lam) {
                        x = y;
                        power *= 2;
                        lam = 0;
                        d = std::gcd(v, n);
                        v = 1;
                    }
                }
                if (d != n) {
                    f(d);
                    f(n / d);
                    return;
                }
                ++x0;
            }
        };
        f(n);
        std::sort(p.begin(), p.end());
        return p;
    }

    template<typename T>
    constexpr T math::Chinese_remainder_theorem
            (vector <i64> &a, vector <i64> &m) {
        T n = accumulate(m.begin(), m.end(), (T) 1, multiplies<T>()), ans = 0;

        for (int i = 0; i < (i64) a.size(); ++i) {
            T m1 = n / m[i], b;
            b = inv(m1, m[i]);
            ans = (ans + a[i] * m1 * b % n) % n;
        }
        return (ans % n + n) % n;
    }

    template<typename T>
    constexpr T math::Extend_the_Chinese_remainder_theorem
            (vector <i64> &a, vector <i64> &m) {
        T m1 = m[0], a1 = a[0];
        for (int i = 1; i < (i64) a.size(); ++i) {
            T m2 = m[i], a2 = a[i];
            auto [gcd, p, q] = __Exgcd(m1, m2, a2 - a1);
            a1 = m1 * p + a1;
            m1 = m1 * m2 / gcd;
            a1 = (a1 % m1 + m1) % m1;
        }
        return a1;
    }

    template<typename T>
    constexpr T math::Euler_phi(T n) {
        T ans = n;
        for (i64 i = 2; i * i <= n; i++)
            if (n % i == 0) {
                ans = ans / i * (i - 1);
                while (n % i == 0) n /= i;
            }
        if (n > 1) ans = ans / n * (n - 1);
        return ans;
    }

    i64 math::Extending_Euler_theorem(i64 a, string b, i64 m) {
        i64 gcd = __gcd(a, m);
        i64 phi = Euler_phi(m);
        i64 res = 0;
        bool flag = 0;
        for (auto u: b) {
            res = res * 10 + u - '0';
            while (res >= phi) {
                res -= phi;
                if (!flag) flag = 1;
            }
        }
        if (gcd != 1 && flag) res += phi;
        return power(a, res, m);
    }

    i64 math::min_primitive_root(i64 m) {
        i64 phi = math::Euler_phi(m);
        auto div = [&](i64 x) {
            vector <i64> f;
            for (i64 i = 2; i * i <= x; ++i) {
                if (x % i != 0) continue;
                f.push_back(i);
                while (x % i == 0) x /= i;
            }
            if (x != 1 && x != phi) f.push_back(x);
            return f;
        };
        auto d = div(phi);
        i64 root = -1;
        auto check = [&](i64 x) {
            for (auto u: d)
                if (math::power(x, u, m) == 1)
                    return false;
            root = x;
            return true;
        };
        for (i64 i = 1;; ++i) {
            if (__gcd(i, m) != 1)
                continue;
            if (check(i)) break;
        }
        return root;
    }

# ifdef _Linear_sieves
    std::vector <i64> math::primitive_root(i64 n) {
        static vector<bool> exist(Linear_sieves_max + 1);
        auto __exist = [&]() {
            static bool __existed = 0;
            if (__existed) return;
            __existed = 1;
            exist[2] = 1;
            exist[4] = 1;
            for (ll p: s.Prime) {
                if ((p & 1) == 0) continue;
                for (ll now = p; now <= (ll) exist.size() - 1; now *= p) {
                    exist[now] = 1;
                    if (now * 2 <= (ll) exist.size() - 1)
                        exist[now * 2] = 1;
                }
            }
        };
        __exist();
        if (!exist[n]) return vector<i64>();
        vector <ll> f;
        ll phi = s.eu(n);
        ll pphi = s.eu(phi);
        ll m = phi;
        for (int i = 2; i * i <= m; ++i) {
            if (m % i == 0) {
                f.push_back(i);
                while (m % i)
                    m /= i;
            }
        }
        if (m != 1) f.push_back(m);
        // Debug ( f ) ;
        ll root = -1;
        auto check = [&](ll x) {
            for (auto u: f)
                if (power(x, phi / u, n) == 1)
                    return false;
            root = x;
            return true;
        };
        for (i64 i = 1;; ++i) {
            if (__gcd(i, n) != 1) continue;
            if (check(i)) break;
        }
        vector <ll> ans;
        for (i64 now = root, i = 1; i <= phi; ++i) {
            if (__gcd(phi, i) == 1)
                ans.push_back(now);
            now = (now * root) % n;
        }
        sort(ans.begin(), ans.end());
        return ans;
    }

# endif

    constexpr i64 math::exBSGS(i64 a, i64 b, i64 m, i64 k) {
        constexpr i64 inf = 1e15;
        auto BSGS = [&](i64 a, i64 b, i64 m, i64 k = 1) {
# ifdef _Hash
            unordered_map <ui64, ui64, Hash> map;
# else
            std::map <ui64, ui64> map;
# endif
            i64 cur = 1, t = sqrt(m) + 1;
            for (i64 B = 1; B <= t; ++B) {
                (cur *= a) %= m;
                map[b * cur % m] = B;
            }
            ll now = cur * k % m;
            for (i64 A = 1; A <= t; ++A) {
                auto it = map.find(now);
                if (it != map.end())
                    return A * t - (i64) it->second;
                (now *= cur) %= m;
            }
            return -inf; // �޽�
        };
        i64 A = a %= m, B = b %= m, M = m;
        if (b == 1) return 0;
        i64 cur = 1 % m;
        for (int i = 0;; i++) {
            if (cur == B) return i;
            cur = cur * A % M;
            i64 d = __gcd(a, m);
            if (b % d) return -inf;
            if (d == 1) {
                auto ans = BSGS(a, b, m, k * a % m);
                if (ans == -inf) return -1;
                else return ans + i + 1;
            }
            k = k * a / d % m, b /= d, m /= d;
        }
    }

    std::vector <i64> math::n_times_remaining(i64 a, i64 b, i64 m) {
        auto root = min_primitive_root(m);
        i64 now = math::power(root, a, m);
        i64 c = math::exBSGS(now, b, m);
        if (c == -1) return vector<i64>();
        i64 x0 = math::power(root, c, m);
        i64 phi = math::Euler_phi(m);
        i64 gcd = __gcd(a, phi);
        vector <i64> ans;
        i64 cnt = math::power(root, phi / gcd, m);
        for (int i = 0; i < gcd; ++i) {
            ans.push_back(x0);
            x0 = math::mul(x0, cnt, m);
        }
        return ans;
    }

    i64 math::Exlucas(i64 n, i64 m, i64 P) {
        std::vector <i64> p, a;
        function <i64(i64, i64, i64)> calc = [&](i64 n, i64 x, i64 P) mutable -> i64 {
            if (!n) return 1;
            i64 s = 1;
            for (i64 i = 1; i <= P; ++i)  //��׳ˣ���Ԥ�����͸��Ӷ�
                if (i % x != 0) s = math::mul(s, i, P);
            s = math::power(s, n / P, P);
            for (i64 i = n / P * P + 1; i <= n; ++i)
                if (i % x != 0) s = math::mul(i, s, P);
            return math::mul(s, calc(n / x, x, P), P);
        };
        function <i64(i64, i64, i64, i64)> multilucas = [&](i64 n, i64 m, i64 x, i64 P) -> i64 {
            i64 cnt = 0;
            for (i64 i = n; i != 0; i /= x) cnt += i / x;
            for (i64 i = m; i != 0; i /= x) cnt -= i / x;
            for (i64 i = n - m; i != 0; i /= x) cnt -= i / x;
            return static_cast<__int128>(1) * math::power(x, cnt, P) % P * calc(n, x, P) % P
                   * math::inv(calc(m, x, P), P) % P * math::inv(calc(n - m, x, P), P) % P;
        };
        for (i64 i = 2; i * i <= P; ++i) {
            if (P % i == 0) {
                p.emplace_back(1);
                while (P % i == 0) p.back() *= i, P /= i;
                a.emplace_back(multilucas(n, m, i, p.back()));
            }
        }
        if (P > 1) p.emplace_back(P), a.emplace_back(multilucas(n, m, P, P));
        return math::Extend_the_Chinese_remainder_theorem(a, p);
    }
    // namespace Math
}

using namespace Math;