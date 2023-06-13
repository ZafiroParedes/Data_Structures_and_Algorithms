// this is testlib.h

#ifndef ___testlib_included___
#define ___testlib_included___

#include <string>
#include <vector>

using namespace std;

class tester
{ protected:
    int minwidth, maxwidth, seed, length, argc;
    double frac, time1, time2;
    bool isvec, isstr, unrandom, bigcheck, printthem;
    char * * argv, * * origs;
    char * randy;
    vector <string> & vs;
    vector <char *> & vcs;
    string * & as;
    char * * & acs;
    static vector <string> dvs;
    static vector <char *> dvcs;
    static string * das;
    static char * * dacs;
    void prepare();
    void set_number(int len);
    char * make_random();
    void generate_random();
    void generate_rough();
    void set_entry(int i, char * s);
    const char * get_entry(int i);
    bool compare_entry(int i, char * s);
    void exchange(int p, int q);
    double getcputime();
    bool verify();
  public:
    tester(int c, char * * p, vector <string> & v);
    tester(int c, char * * p, vector <char *> & v);
    tester(int c, char * * p, string * & a);
    tester(int c, char * * p, char * * & a);
    ~tester();
    int get_number();
    double how_long();
    void printall();
    bool finish(); };

#endif
