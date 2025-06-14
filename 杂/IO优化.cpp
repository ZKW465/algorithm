constexpr int MAXSIZE = 1 << 20;
struct Input {
    char buf[MAXSIZE], *p1 = buf, *p2 = buf;
    #define isdigit(x) ('0' <= x && x <= '9')
    
    #define gc()                                                                 \
       (p1 == p2 &&(p2 =(p1 = buf) + fread(buf, 1, MAXSIZE, stdin), p1 == p2)    \
            ? EOF                                                                \
            : *p1++)

    bool blank(char ch) {
        return ch == ' ' || ch == '\n' || ch == '\r' || ch == '\t' || ch == EOF;
    }
    void tie(void* x) {}
    template <typename T>
    Input &operator>>(T &x) {
        x = 0;
        bool neg = false;
        char ch = gc();
        for (; !isdigit(ch); ch = gc()) {
            if(ch == '-') {
                neg = true;
            }
        }
        for (; isdigit(ch); ch = gc()) {
            x = (x << 3) + (x << 1) + ch - '0';
        }
        if (neg) {
            x = -x;
        }
        return *this;
    }
    Input &operator>>(char &x) {
        x = ' ';
        for (; blank(x); x = gc());
        return *this;
    }
    Input &operator>>(double &x) {
        x = 0;
        double tmp = 1;
        bool neg = 0;
        char ch = gc();
        for (; !isdigit(ch); ch = gc()) {
            if (ch == '-') {
                neg = 1;
            }
        }
        for (; isdigit(ch); ch = gc()) {
            x = x * 10 + ch - '0';
        }
        if (ch == '.') {
            for (ch = gc(); isdigit(ch); ch = gc()) {
                tmp /= 10.0, x += tmp *(ch - '0');
            }
        }
        if(neg) x = -x;
        return *this;
    }
    Input &operator>>(string &s) {
        s.clear();
        char ch = gc();
        for (; blank(ch); ch = gc());
        for (; !blank(ch); ch = gc()) {
            s += ch;
        }
        return *this;
    }
    # undef isdigit
    # undef gc
} input;
# define cin input

struct Output {
    struct setprecision {
        int precision;
    };
    char pbuf[MAXSIZE], *pp = pbuf;
    void push(const char &c) { 
        if(pp - pbuf == MAXSIZE)                         
            fwrite(pbuf, 1, MAXSIZE, stdout), pp = pbuf; 
        *pp++ = c;\
    }
    int precision;
    Output() { precision = 6;}
    ~Output() { fwrite(pbuf, 1, pp - pbuf, stdout);}
    char stk[40];
    int top = 0;
    template<class T>
    Output &operator<<(const T &x) {
        T tmp = x;
        bool neg = tmp < 0;
        if (neg) {
            tmp *= -1;
        }
        for (; tmp; tmp /= 10) {
            stk[++ top] = '0' + tmp % 10;
        }
        if (neg) {
            stk[++ top] = '-';
        }
        for (; top; top --) {
            push(stk[top]);
        }
        if (x == 0) {
            push('0');
        }
        return *this;
    }
    Output &operator<<(const string &x) {
        for (auto &u : x) {
            push(u);
        }
        return *this;
    }
    template<size_t N>
    Output &operator<<(const char(&x)[N]) {
        *this << string(x);
        return *this;
    }
    Output &operator<<(const char* const &x) {
        for (const char* ptr = x; *ptr != '\0'; ++ptr) {
            push(*ptr);
        }
        return *this;
    }
    Output &operator<<(const char &x) {
        push(x);
        return *this;
    }
    Output &operator<<(const bool &x) {
        push(x ? '1' : '0');
        return *this;
    }
    Output &operator<<(const double &x) {
        int intPart = static_cast<int>(x);
        *this << intPart;

        push('.');
        
        double decimalPart = x - intPart;
        for (int i = 0; i < precision; ++i) {
            decimalPart *= 10;
            int digit = static_cast<int>(decimalPart);
            *this << char('0' + digit);
            decimalPart -= digit;
        }
        return *this;
    }
    Output &operator<<(setprecision x) {
        precision = x.precision;
        return *this;
    }
    # undef push
}output;
# define cout output